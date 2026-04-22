#include <stdio.h>
#include <assert.h>

#define X(CODE, NAME, ...) fprintf(fp, "#define %s \"%s\"\n", #CODE, NAME);

int main(void) {
  FILE *fp = fopen("crs_lit.h", "w");

  assert(fp);

#include "crs.def"

  fclose(fp);
}
