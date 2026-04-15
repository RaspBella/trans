#pragma once

#include "crs.h"
#include "op.h"

struct service {
  const char *info;
  const char *id;
  int from;
  int to;
};

#define service(INFO, ID, FROM, TO) { \
  INFO, \
  ID, \
  FROM, \
  TO \
}

#define COMMON_CRE_TO_GLC \
  service( \
    .info = VT, \
    .id = "L02283", \
    .from = CRE, \
    .to = GLC \
  )

#define COMMON_GLC_TO_CRE \
  service( \
    .info = VT, \
    .id = "W02480", \
    .from = GLC, \
    .to = CRE \
  )
