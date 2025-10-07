#include "parse.h"
#include "utils.h"
#include "json.h"

#include "bestline.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define pop(argc, argv) *argv++; argc--;

#define INDENT 2

char *input;
char *output;

char *line;

int indent;

void cleanup(void) {
  if (root) {
    if (!output) {
      if (!dump(input, indent)) {
        fprintf(stderr, "Error writing file: `%s`\n", input);

        exit(EXIT_FAILURE);
      }
    }

    else {
      free_json(root);
    }
  }

  if (line) free(line);
}

void add(int argc, char **argv) {
  if (!argc) {
    usage("add");

    exit(EXIT_FAILURE);
  }

  input = pop(argc, argv);

  fprintf(stderr, "add mode\n");

  if (!load(input)) {
    fprintf(stderr, "Error reading file: `%s`\n", input);

    exit(EXIT_FAILURE);
  }

  while ((line = bestlineWithHistory("trans >>> ", "trans"))) {
    bool ret = parse(line, .indent = indent);

    if (!ret) {
      fprintf(stderr, "Couldn't parse: `%s`\n", line);
    }

    free(line);
  }

  printf("exit()\n");

  exit(EXIT_SUCCESS);
}

void gen(int argc, char **argv) {
  if (argc < 2) {
    usage("gen");

    exit(EXIT_FAILURE);
  }

  input = pop(argc, argv);
  output = pop(argc, argv);

  fprintf(stderr, "gen mode\n");

  if (!load(input)) {
    fprintf(stderr, "Error reading file: `%s`\n", input);

    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
  if (atexit(cleanup)) {
    fprintf(stderr, "atexit: Failed to register function: cleanup\n");

    exit(EXIT_FAILURE);
  }

  indent = INDENT;

  char *program = pop(argc, argv);

  printf("program name: %s\n", program);

  if (!strcmp(program, "add")) {
    add(argc, argv);
  }

  else if (!strcmp(program, "gen")) {
    gen(argc, argv);
  }

  if (!argc) {
    usage(program);

    exit(EXIT_FAILURE);
  }

  char *mode = pop(argc, argv);

  if (!strcmp(mode, "add")) {
    add(argc, argv);
  }

  else if (!strcmp(mode, "gen")) {
    gen(argc, argv);
  }

  usage(program);

  exit(EXIT_FAILURE);
}
