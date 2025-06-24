#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

static char *db[26][26][26];
static bool setup = false;

#define CTOI(c) c - 'A'
#define INDEX_DB(code) db[CTOI(code[0])][CTOI(code[1])][CTOI(code[2])]
#define STATION(name, code) INDEX_DB(code) = name

static void init(void);

char *crs(char *code) {
  assert(code && strlen(code) >= 3);

  if (!setup) {
    init();

    setup = true;
  }

  code[0] = toupper(code[0]);
  code[1] = toupper(code[1]);
  code[2] = toupper(code[2]);

  return INDEX_DB(code);
}

static void init(void) {
}
