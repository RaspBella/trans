#include "parse.h"

#include "bestline.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define pop(argc, argv) *argv++; argc--;

int main(int argc, char **argv) {
  char *program = pop(argc, argv);

  printf("program name: %s\n", program);

  char *line = NULL;

  while ((line = bestlineWithHistory("trans >>> ", "trans"))) {
    bool ret = parse(line);

    free(line);

    if (!ret) {
      fprintf(stderr, "Couldn't parse: `%s`\n", line);

      exit(EXIT_FAILURE);
    }
  }
}
