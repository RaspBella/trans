#include "parse.h"
#include "utils.h"
#include "json.h"

#include "bestline.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define pop(argc, argv) *argv++; argc--;

char *file;
char *line;

void cleanup(void) {
  if (file) {
    if (!dump(file, 2)) {
      fprintf(stderr, "Error writing file: `%s`\n", file);

      exit(EXIT_FAILURE);
    }
  }

  if (line) free(line);
}

int main(int argc, char **argv) {
  char *program = pop(argc, argv);

  printf("program name: %s\n", program);

  if (!argc) {
    usage(program);

    exit(EXIT_FAILURE);
  }

  file = pop(argc, argv);

  if (!load(file)) {
    fprintf(stderr, "Error reading file: `%s`\n", file);

    exit(EXIT_FAILURE);
  }

  if (atexit(cleanup)) {
    fprintf(stderr, "atexit: Failed to register function: cleanup\n");

    exit(EXIT_FAILURE);
  }

  while ((line = bestlineWithHistory("trans >>> ", "trans"))) {
    bool ret = parse(line);

    if (!ret) {
      fprintf(stderr, "Couldn't parse: `%s`\n", line);
    }

    free(line);
  }

  fprintf(stderr, "call: exit()\n");

  exit(EXIT_SUCCESS);
}
