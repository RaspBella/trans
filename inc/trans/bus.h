#ifndef TRANS_BUS_H
#define TRANS_BUS_H

#define _BT_BASE_FMT "https://bustimes.org"
#define BT_TRIP_FMT _BT_BASE_FMT"/trips/%u"
#define BT_JOURNEY_FMT _BT_BASE_FMT"/map#journey=%u"

#define BT_JOURNEY TRANS_BUS_BT_JOURNEY
#define BT_TRIP TRANS_BUS_BT_TRIP

enum trans_bus_type {
  TRANS_BUS_NO_BT,
  TRANS_BUS_BT_TRIP,
  TRANS_BUS_BT_JOURNEY,
};

struct trans_bus {
  enum trans_bus_type type;
  union {
    struct {
      char *op;
      char *number;
    } no_bt;
    unsigned bt;
  } as;
};

#define bus(OP, NUMBER, FROM, TO) { \
  .type = TRANS_BUS, \
  .from = FROM, \
  .to = TO, \
  .as.bus = { \
    .type = TRANS_BUS_NO_BT, \
    .as.no_bt = { \
      .op = OP, \
      .number = NUMBER \
    } \
  } \
}

#define bt(TYPE, ID, FROM, TO) { \
  .type = TRANS_BUS, \
  .from = FROM, \
  .to = TO, \
  .as.bus = { \
    .type = TYPE, \
    .as.bt = ID \
  } \
}

#endif /* TRANS_BUS_H */
