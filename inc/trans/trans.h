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
  enum trans_type type;
  char *from;
  char *to;
  union {
    struct trans_bus bus;
    struct trans_train train;
    struct trans_ferry ferry;
    struct trans_plane plane;
  } as;
};

struct route {
  char iso[11];
  char *info;
  size_t count;
  struct trans items[];
};

#endif /* TRANS_H */
