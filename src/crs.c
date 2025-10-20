#define _GNU_SOURCE

#include <assert.h>
#include <string.h>

#include "crs.h"

#define CTOI(c) c - 'A'
#define INDEX_DB(code) db[CTOI(code[0])][CTOI(code[1])][CTOI(code[2])]
#define STATION(name, code) INDEX_DB(code) = name

static const char *db[26][26][26];

__attribute__((constructor)) static void init(void) {
#include "stations.c"
}

const char *crs(const char *code) {
  assert(code && strlen(code) >= 3 && VALID_CRS(code));

  return INDEX_DB(code);
}

const char *src(const char *name) {
  assert(name);

  static char code[4];

  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < 26; j++) {
      for (int k = 0; k < 26; k++) {
        const char *entry = db[i][j][k];

        if (entry) {
          char *p = strchrnul(entry, *SEP);

          if (*p) {
            if (!strncasecmp(entry, name, p - name - 1)) {
              code[0] = i + 'A';
              code[1] = j + 'A';
              code[2] = k + 'A';

              return code;
            }
          }

          else {
            if (!strcasecmp(entry, name)) {
              code[0] = i + 'A';
              code[1] = j + 'A';
              code[2] = k + 'A';

              return code;
            }
          }
        }
      }
    }
  }

  return NULL;
}
