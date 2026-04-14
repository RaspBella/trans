#pragma once

#define STATION(code, name) code,

enum {
#include "stations.def"
  CRS_COUNT
};

#undef STATION

#define STATION(CODE, NAME) { \
  .code = #CODE, \
  .name = NAME \
},

struct {
  const char code[4];
  const char *name;
} crs[CRS_COUNT] = {
#include "stations.def"
};

#undef STATION
