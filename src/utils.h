#pragma once

#include <stdlib.h>
#include <string.h>

// https://gist.github.com/rexim/b5b0c38f53157037923e7cdd77ce685d
#define da_append(xs, x)                                                                   \
  do {                                                                                     \
    if ((xs)->count >= (xs)->capacity) {                                                   \
      size_t old_cap = (xs)->capacity;                                                     \
      if ((xs)->capacity == 0) (xs)->capacity = 256;                                       \
      else (xs)->capacity *= 2;                                                            \
      (xs)->items = realloc((xs)->items, (xs)->capacity*sizeof(*(xs)->items));             \
      memset((xs)->items + old_cap, 0, ((xs)->capacity - old_cap) * sizeof(*(xs)->items)); \
    }                                                                                      \
    (xs)->items[(xs)->count++] = (x);                                                      \
  } while (0)

enum mode {
  NO_MODE,
  ADD_CMD,
  GEN_CMD,
  ADD_MODE,
  GEN_MODE
};

void usage(const char *program, enum mode mode);
