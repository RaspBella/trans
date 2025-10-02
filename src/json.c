#include "json.h"

#include <stdio.h>
#include <stdbool.h>

bool load(const char *file) {
  fprintf(stderr, "load: file=%s\n", file);

  return false;
}

bool dump(const char *file, int indent) {
  fprintf(stderr, "dump: file=%s indent=%d\n", file, indent);

  return false;
}
