#pragma once

#include "bus.h"
#include "tube.h"
#include "nr.h"
#include "plane.h"

enum trans {
  MANY,
  WALK,
  BUS,
  TRAM,
  TRAIN,
  PLANE,
  LONDON_TUBE,
  TRANS_COUNT
};

struct service {
  enum trans type;
  union {
    struct bus_service bus;
    struct london_tube_service tube;
    struct nr_service nr;
    struct plane_service plane;
  };
};

struct route {
  enum trans type;
  unsigned service_count;
  struct service *services;
  char *info;
};

struct day {
  char iso[11];
  unsigned route_count;
  struct route *routes;
};

#define ARRAY_LEN(ARRAY) (sizeof(ARRAY) / sizeof(ARRAY[0]))

#define Services(...) ((struct service[]){ __VA_ARGS__ })

#define Route(TYPE, SERVICE_ARRAY, ...) \
  (struct route){ \
    .type = TYPE, \
    .service_count = ARRAY_LEN(SERVICE_ARRAY), \
    .services = SERVICE_ARRAY, \
    __VA_ARGS__ \
  }

#define Routes(...) ((struct route[]){ __VA_ARGS__ })

#define Day(ISO, ROUTE_ARRAY) \
  (struct day){ \
    .iso = ISO, \
    .route_count = ARRAY_LEN(ROUTE_ARRAY), \
    .routes = ROUTE_ARRAY \
  }

void print_service(struct service);
void print_route(struct route);
void print_day(struct day);
