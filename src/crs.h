#pragma once

#define STATION(code, name) code,

enum {
#include "stations.def"
  CRS_COUNT
};

#undef STATION

#define STATION(CODE, NAME) { .name = NAME, #CODE },

struct {
  const char *name;
  const char code[4];
} crs[CRS_COUNT] = {
#include "stations.def"
};

#undef STATION
