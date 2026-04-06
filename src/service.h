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
