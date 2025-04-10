#pragma once

typedef enum {
  TRANS_WALK,
  TRANS_BUS,
  TRANS_TRAM,
  TRANS_TUBE,
  TRANS_NATRAIL,
  TRANS_MANY,
  COUNT_TRANS
} Transport_Index;

typedef struct Trans {
  Transport_Index type;
  char from[4];
  char to[4];
  char *info;
  struct Trans *child;
  struct Trans *next;
} Transport;

extern const char *transport_strings[COUNT_TRANS];

#define DIGIT 10

extern Transport *table[DIGIT][DIGIT][DIGIT][DIGIT][DIGIT][DIGIT][DIGIT][DIGIT];

void print_trans(const Transport *trans);
void read_in_table(const char *filename);
void write_out_table(const char *filename);
