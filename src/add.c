#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "state.h"
#include "utils.h"
#include "parse.h"

#include "bestline.h"

void add(int argc, char **argv, enum mode mode) {
  if (!argc) {
    usage(program, mode);

    exit(EXIT_FAILURE);
  }

  input = pop(argc, argv);

  if (!load(input)) {
    fprintf(
      stderr,
      "%s: error reading file: `%s`\n",
      __func__,
      input
    );

    exit(EXIT_FAILURE);
  }

  while ((line = bestlineWithHistory("trans >>> ", "trans"))) {
    bool ret = parse(line, .indent = indent);

    if (!ret) {
      fprintf(
        stderr,
        "couldn't parse: `%s`\n",
        line
      );
    }

    free(line);
  }

  printf("exit()\n");

  exit(EXIT_SUCCESS);
}

