#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

#include "utils.h"
#include "json.h"

#define INDENT 2

char *program;

char *input;
char *output;

char *line;

int indent;

void add(int argc, char **argv, int mode);
void gen(int argc, char **argv, int mode);

void cleanup(void) {
  if (root) {
    if (!output) {
      if (!dump(input, indent)) {
        fprintf(
          stderr,
          "%s: error writing file: `%s`\n",
          __func__,
          input
        );

        exit(EXIT_FAILURE);
      }
    }

    else {
      free_json(root);
    }
  }

  if (line) free(line);
}

int main(int argc, char **argv) {
  if (atexit(cleanup)) {
    fprintf(
      stderr,
      "atexit: Failed to register function: cleanup\n"
    );

    exit(EXIT_FAILURE);
  }

  indent = INDENT;

  program = pop(argc, argv);

  if (!strcmp(basename(program), "trans-add")) {
    add(argc, argv, ADD_CMD);
  }

  else if (!strcmp(basename(program), "trans-gen")) {
    gen(argc, argv, GEN_CMD);
  }

  if (!argc) {
    usage(program, NO_MODE);

    exit(EXIT_FAILURE);
  }

  char *mode = pop(argc, argv);

  if (!strcmp(mode, "add")) {
    add(argc, argv, ADD_MODE);
  }

  else if (!strcmp(mode, "gen")) {
    gen(argc, argv, GEN_MODE);
  }

  usage(program, NO_MODE);

  exit(EXIT_FAILURE);
}
