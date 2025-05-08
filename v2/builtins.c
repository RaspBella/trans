#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#include "builtins.h"

void built_in_exit(void *arg) {
  int exit_code = (intptr_t)arg;

  exit(exit_code);
}

void built_in_help(void *arg) {
  printf(
    "Help:\n"
    "  Built ins:\n"
    "    exit [Integer]  exits with an optional exit code (default is %d)\n"
    "    help            prints help\n",
    EXIT_SUCCESS
  );
}

static_assert(COUNT_BUILT_INS == 2, "Amount of built-ins has changed");
const char *built_in_strings[COUNT_BUILT_INS] = {
  [BUILT_IN_EXIT] = "exit",
  [BUILT_IN_HELP] = "help"
};

void (*built_in_functions[COUNT_BUILT_INS])(void*) = {
  [BUILT_IN_EXIT] = built_in_exit,
  [BUILT_IN_HELP] = built_in_help
};
