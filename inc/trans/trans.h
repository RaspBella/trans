#ifndef TRANS_H
#define TRANS_H

#include <trans/bus.h>
#include <trans/train.h>
#include <trans/ferry.h>
#include <trans/plane.h>
#include <stddef.h>

enum trans_type {
  TRANS_BUS,
  TRANS_TRAIN,
  TRANS_FERRY,
  TRANS_PLANE,
};

struct trans {
  const enum trans_type type;
  const char *from;
  const char *to;
  const union {
    const struct trans_bus bus;
    const struct trans_train train;
    const struct trans_ferry ferry;
    const struct trans_plane plane;
  } as;
};

struct route {
  const char iso[11];
  const char *info;
  const size_t count;
  const struct trans items[];
};

#endif /* TRANS_H */
