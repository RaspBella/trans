#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "utils.h"

#define STATION(CODE, NAME) { \
  .code = #CODE, \
  .name = NAME \
},

struct {
  const char code[4];
  const char *name;
} crs[] = {
#include "stations.def"
};

int main(void) {
  FILE *fp = fopen("crs_lit.h", "w");

  assert(fp != NULL);

  for (int i = 0; i < ARRAY_LEN(crs); ++i) {
    fprintf(
      fp,
      "#define ___%.3s___ \"%s\"\n",
      crs[i].code,
      crs[i].name
    );
  }

  fclose(fp);
}
