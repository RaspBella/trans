#pragma once

struct nr {
  const char *id;
  const char *op;
  const char from[4];
  const char to[4];
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

struct bus {
  int id;
  const char *n;
  const char *op;
  const char *from;
  const char *to;
};

#define bus(ID, N, OP, FROM, TO) { \
  .type = SERVICE_BUS, \
  .as.bus = { \
    ID, \
    N, \
    OP, \
    FROM, \
    TO, \
  } \
}

enum service_type {
  SERVICE_NR = 1,
  SERVICE_BUS
};

struct service {
  enum service_type type;
  union {
    struct nr nr;
    struct bus bus;
  } as;
};
