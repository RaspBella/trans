#pragma once

typedef enum {
  BUILT_IN_INVALID = -1,
  BUILT_IN_EXIT,
  BUILT_IN_HELP,
  COUNT_BUILT_INS
} Built_In_Index;

extern const char *built_in_strings[COUNT_BUILT_INS];
extern void (*built_in_functions[COUNT_BUILT_INS])(void*);
