#include <stdlib.h>
#include <assert.h>

char **crs_db[26][26][26];

#define X(CODE, ...) \
  crs_db[(int)((#CODE)[0]-'A')][(int)((#CODE)[1]-'A')][(int)((#CODE)[2]-'A')] = (char*[]){ \
    __VA_ARGS__, \
    NULL \
  };

__attribute__((constructor))
static void init_crs(void) {
#include "crs.def"
}

#undef X

#define CTOI(C) \
  C >= 'A' && C <= 'Z' ? C - 'A' : \
  C >= 'a' && C <= 'z' ? C - 'a' : \
  -1

char **crs(char code[4]) {
  int index[3] = {
    [0] = CTOI(code[0]),
    [1] = CTOI(code[1]),
    [2] = CTOI(code[2])
  };

  if (index[0] >= 0 && index[1] >= 0 && index[2] >= 0) {
    return crs_db[index[0]][index[1]][index[2]];
  }

  return NULL;
}
