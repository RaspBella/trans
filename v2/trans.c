#include "trans.h"

#include <assert.h>

static_assert(COUNT_TRANS == 6, "Amount of forms of transport has changed");
const char *transport_strings[COUNT_TRANS] = {
  [TRANS_WALK] = "walk",
  [TRANS_BUS] = "bus",
  [TRANS_TRAM] = "tram",
  [TRANS_TUBE] = "tube",
  [TRANS_NATRAIL] = "natrail",
  [TRANS_MANY] = "many"
};
