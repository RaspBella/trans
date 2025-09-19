#include "parse.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
  if (argc == 1) {
    printf(
      "Provide arguments!\n"
      "Notice how a `+` or `-` followed by an integer and a unit (y/m/w/d) parses successfully\n"
    );

    exit(EXIT_SUCCESS);
  }

  for (int i = 1; i < argc; i++) {
    if (!parse(argv[i])) {
      fprintf(stderr, "Failed to parse: \"%s\"\n", argv[i]);

      exit(EXIT_FAILURE);
    }
  }
}
