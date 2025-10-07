#include "parse.h"
#include "utils.h"
#include "json.h"

#include "bestline.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define pop(argc, argv) *argv++; argc--;

char *mode;
bool write_back;

char *file;

char *line;

int indent;

void cleanup(void) {
  if (file) {
    if (root) {
      if (write_back) {
        if (!dump(file, indent)) {
          fprintf(stderr, "Error writing file: `%s`\n", file);

          exit(EXIT_FAILURE);
        }
      }

      else {
        free_json(root);
      }
    }
  }

  if (line) free(line);
}

int main(int argc, char **argv) {
  indent = 2;

  char *program = pop(argc, argv);

  printf("program name: %s\n", program);

  if (!argc) {
    usage(program);

    exit(EXIT_FAILURE);
  }

  mode = pop(argc, argv);

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

  if (!strcmp(mode, "add")) {
    write_back = true;

    while ((line = bestlineWithHistory("trans >>> ", "trans"))) {
      bool ret = parse(line, .indent = indent);

      if (!ret) {
        fprintf(stderr, "Couldn't parse: `%s`\n", line);
      }

      free(line);
    }

    printf("exit()\n");
  }

  else if (!strcmp(mode, "gen")) {
    fprintf(stderr, "gen mode\n");
  }

  else {
    usage(program);

    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
