#pragma once

struct service {
  const char *info;
  const char *id;
  char from[4];
  char to[4];
};

#define service(INFO, ID, FROM, TO) { \
  INFO, \
  ID, \
  FROM, \
  TO \
}
