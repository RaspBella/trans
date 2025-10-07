#include "utils.h"

#include <stdio.h>

void usage(const char *program) {
  fprintf(
    stderr,
    "usage: %s `mode` `filename`\n"
    "modes: `add`, `gen`\n"
    "`gen`: generates output pages from data file\n"
    "`add`: data entry mode described below\n"
    "`add` mode commands:\n"
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
    "    [ `journeys` ]                                   `journeys` is a comma seperated sequence of `journey`\n",
    program
  );
}
