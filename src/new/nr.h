#pragma once

struct nr_service {
  char *op;
  char from[4];
  char to[4];
  char *rtt;
};

#define NatRail(OP, FROM, TO, ...) \
  (struct service){ \
    .type = TRAIN, \
    .nr = { \
      .op = OP, \
      .from = FROM, \
      .to = TO, \
      __VA_ARGS__ \
    } \
  }
