#include "parse.h"

#include <stdlib.h>
#include <stdio.h>

#define pop(argc, argv) *argv++; argc--;

int main(int argc, char **argv) {
  char *program = pop(argc, argv);

  printf("program name: %s\n", program);

  for (int i = 0; i < argc; i++) {
    char *string = argv[i];

    if (!parse(string)) {
      fprintf(stderr, "Couldn't parse: `%s`\n", string);

      exit(EXIT_FAILURE);
    }
  }
}
