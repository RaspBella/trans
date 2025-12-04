#include <stdio.h>
#include <assert.h>

#include "trans.h"

#include "../crs.h"

const char *TRANS_STRINGS[TRANS_COUNT] = {
  [MANY] = "Many",
  [WALK] = "Walk",
  [BUS] = "Bus",
  [TRAM] = "Tram",
  [TRAIN] = "Train",
  [PLANE] = "Plane",
  [LONDON_TUBE] = "London Tube"
};

void print_service(struct service s) {
  assert(s.type >= 0 && s.type < TRANS_COUNT);

  printf("    %s:\n", TRANS_STRINGS[s.type]);

  switch (s.type) {
    case BUS:
      printf(
        "      %s %s:\n"
        "        %s->%s\n"
        "        bt: \"%s\"\n",
        s.bus.op, s.bus.number,
        s.bus.from, s.bus.to,
        s.bus.bt
      );

      break;

    case LONDON_TUBE:
      printf("      %s(%s)->%s(%s)\n", crs(s.tube.from), s.tube.from, crs(s.tube.to), s.tube.to);

      break;

    case TRAIN:
      printf(
        "      %s:\n"
        "        %s(%s)->%s(%s)\n"
        "        rtt: \"%s\"\n",
        s.nr.op,
        crs(s.nr.from), s.nr.from, crs(s.nr.to), s.nr.to,
        s.nr.rtt
      );

      break;

    case PLANE:
      printf(
        "      %s\n"
        "      %s\n"
        "      %s\n"
        "      %s\n",
        s.plane.op,
        s.plane.number,
        s.plane.from,
        s.plane.to
      );

      break;
  }
}

void print_route(struct route r) {
  assert(r.type >= 0 && r.type < TRANS_COUNT);

  printf("  %s:\n", TRANS_STRINGS[r.type]);

  for (unsigned i = 0; i < r.service_count; ++i) {
    print_service(r.services[i]);
  }
}

void print_day(struct day d) {
  printf("%s:\n", d.iso);

  for (unsigned i = 0; i < d.route_count; ++i) {
    print_route(d.routes[i]);
  }
}
