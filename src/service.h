#pragma once

#include "crs.h"

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

#define WEEKDAY_WYSI_FROM_CRE \
  service( \
    .info = "AWC", \
    .id = "L02283", \
    .from = CRE, \
    .to = GLC \
  )
