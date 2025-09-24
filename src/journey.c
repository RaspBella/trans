#include "journey.h"

#include <stddef.h>

struct Journey {
  char from[4];
  char to[4];
  char *text;
  char *link;
  struct JourneyArray {
    size_t count;
    size_t capacity;
    struct Journey *items;
  } sub;
};
