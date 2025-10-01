#pragma once

// https://gist.github.com/rexim/b5b0c38f53157037923e7cdd77ce685d
#define da_append(xs, x)                                                       \
  do {                                                                         \
    if ((xs)->count >= (xs)->capacity) {                                       \
      if ((xs)->capacity == 0) (xs)->capacity = 256;                           \
      else (xs)->capacity *= 2;                                                \
      (xs)->items = realloc((xs)->items, (xs)->capacity*sizeof(*(xs)->items)); \
    }                                                                          \
    (xs)->items[(xs)->count++] = (x);                                          \
  } while (0)

void usage(const char *program);
