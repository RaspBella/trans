#pragma once

#include "json.h"

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

#define pop(argc, argv) *argv++; argc--;

#define IT_ERR() fprintf(stderr, "%s: failed to init iterator\n", __func__); exit(EXIT_FAILURE);

enum mode {
  NO_MODE,
  ADD_CMD,
  GEN_CMD,
  ADD_MODE,
  GEN_MODE
};

void make_dir(const char *dir);

char *property2string(Json*, char *property);

void fprint_place(FILE *fp, char *place);

void usage(const char *program, enum mode mode);
