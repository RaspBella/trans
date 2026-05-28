#pragma once

struct nr {
  const char *id;
  const char *op;
  char from[4];
  char to[4];
};

#define nr(ID, OP, FROM, TO) { \
  .type = SERVICE_NR, \
  .as.nr = { \
    ID, \
    OP, \
    FROM, \
    TO \
  } \
}

enum service_type {
  SERVICE_NR = 1
};

struct service {
  enum service_type type;
  union {
    struct nr nr;
  } as;
};
