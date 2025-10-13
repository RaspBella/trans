#include "utils.h"

#include <stdio.h>
#include <libgen.h>

void add_usage(void) {
  fprintf(
    stderr,
    "add mode commands:\n"
    "  exit(`n`)                                          Default arg(integer) is 0\n"
    "  print(`date`)                                      No arg will print all in-use dates`\n"
    "  [`date`] = `journey`                               Set a journey to a date\n"
    "  [`date`] += `journey`                              Append a journey to a date\n"
    "\n"
    "  `date`:\n"
    "    `yyyy`-`mm`-`dd`                                 ISO 8601\n"
    "\n"
    "  `journey`:\n"
    "    `code`->`code` `string` `link` `journey-list`    `link` and `journey-list` are optional\n"
    "\n"
    "  `code`:                                            A CRS code comprised of 3 capital letters\n"
    "\n"
    "  `link`:\n"
    "    - `string`\n"
    "\n"
    "  `journey-list`:\n"
    "    [ `journeys` ]                                   `journeys` is a comma seperated sequence of `journey`\n"
  );
}

void usage(const char *program, enum mode mode) {
  switch (mode) {
    case ADD_CMD:
      fprintf(stderr, "usage: %s `file`\n", program);

      add_usage();

      break;

    case GEN_CMD:
      fprintf(stderr, "usage: %s `input file` `output dir`\n", program);

      break;

    case ADD_MODE:
      fprintf(stderr, "usage: %s add `file`\n", program);

      add_usage();

      break;

    case GEN_MODE:
      fprintf(stderr, "usage: %s gen `input file` `output dir`\n", program);

      break;

    case NO_MODE:
      fprintf(
        stderr,
        "usage: %s add `file`\n"
        "usage: %s gen `input file` `output dir`\n",
        program,
        program
      );

      add_usage();

      break;
  }
}
