#pragma once

#define VT "Avanti West Coast"
#define GR "London North Eastern Railway"
#define SR "Scotrail"
#define SW "South Western Railway"
#define TL "London Underground"
#define TP "Transpennine Express"

#define AWC VT
#define LNER GR
#define SWR SW
#define TFL TL
#define TPE TP

enum trans_t {
  MANY,
  WALK,
  BUS,
  TRAM,
  TRAIN,
  PLANE,
  LONDON_TUBE,
  TRANS_T_COUNT
};

char *trans_t_string[TRANS_T_COUNT] = {
  [MANY] = "Many",
  [WALK] = "Walk",
  [BUS] = "Bus",
  [TRAM] = "Tram",
  [TRAIN] = "Train",
  [PLANE] = "Plane",
  [LONDON_TUBE] = "London Tube"
};

struct place {
  enum trans_t type;
  char *name;
};

struct service {
  enum trans_t type;
  char *op;
  struct place from;
  struct place to;
  char *info;
  char *link;
};

struct route {
  enum trans_t type;
  struct place from;
  struct place to;
  char *info;
  unsigned service_count;
  struct service *services;
};

struct date {
  char iso[11];
  unsigned route_count;
  struct route *routes;
};

#define ARRAY(...) { \
  __VA_ARGS__ \
}

#define ARRAY_LEN(ARRAY) (sizeof(ARRAY) / sizeof((ARRAY)[0]))

#define PLACE(TYPE, NAME) { \
  .type = TYPE, \
  .name = NAME \
}

#define SERVICE(TYPE, OP, FROM, TO, ...) { \
  .type = TYPE, \
  .op = OP, \
  .from = FROM, \
  .to = TO, \
  __VA_ARGS__ \
}

#define SERVICES(...) (struct service[]) ARRAY(__VA_ARGS__)

#define ROUTE(FROM, TO, SERVICES, ...) { \
  .from = FROM, \
  .to = TO, \
  .service_count = sizeof(SERVICES) / sizeof(struct service), \
  .services = SERVICES, \
  __VA_ARGS__ \
}

#define ROUTES(...) (struct route[]) ARRAY(__VA_ARGS__)

#define DATE(ISO, ROUTES) { \
  .iso = ISO, \
  .route_count = sizeof(ROUTES) / sizeof(struct route), \
  .routes = ROUTES \
}

#define DATA(...) struct date data[] = { \
  __VA_ARGS__ \
}
