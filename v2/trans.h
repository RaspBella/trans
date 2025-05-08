#pragma once

#define TRANS_VERSION 2

typedef enum {
  TRANS_WALK,
  TRANS_BUS,
  TRANS_TRAM,
  TRANS_TUBE,
  TRANS_NATRAIL,
  TRANS_MANY,
  COUNT_TRANS
} Transport_Index;

extern const char *transport_strings[COUNT_TRANS];
