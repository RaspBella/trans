#pragma once

struct london_tube_service {
  char from[4];
  char to[4];
};

#define London_Tube(FROM, TO) \
  (struct service){ \
    .type = LONDON_TUBE, \
    .tube = { \
      .from = FROM, \
      .to = TO \
    } \
  }
