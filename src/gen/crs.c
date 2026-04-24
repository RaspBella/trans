#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <unistd.h>
#include "../utils.h"

struct crs {
  const char code[4];
  const char **rest;
};

int main(void) {
#define CRS(CODE, ...) { .code = #CODE, .rest = (const char*[]){ __VA_ARGS__, NULL } },
  struct crs crs[] = {
#include "../crs.def"
  };
#undef CRS

  pid_t p = fork();

  assert(p != -1);

  FILE *fp = fopen(p == 0 ? "crs.c" : "crs.h", "w");

  assert(fp);

  if (p == 0) {
    fprintf(
      fp,
      "#include <stddef.h>\n"
      "const char **crs[26][26][26] = {\n"
    );

    for (unsigned i = 0; i < ARRAY_LEN(crs); ++i) {
      fprintf(
        fp,
        "  [%d][%d][%d] = (const char*[]){\n",
        crs[i].code[0] - 'A', crs[i].code[1] - 'A', crs[i].code[2] - 'A'
      );

      for (int j = 0; crs[i].rest[j]; ++j) {
        fprintf(fp, "    \"%s\",\n", crs[i].rest[j]);
      }

      fprintf(
        fp,
        "    NULL\n"
        "  },\n"
      );
    }

    fprintf(fp, "};\n");
  }

  else {
    fprintf(
      fp,
      "#pragma once\n"
      "extern const char **crs[26][26][26];\n"
    );

    for (unsigned i = 0; i < ARRAY_LEN(crs); ++i) {
      fprintf(fp, "#define %3s \"%s\"\n", crs[i].code, *crs[i].rest);
    }
  }

  fclose(fp);
}
