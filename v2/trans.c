#include <assert.h>
#include <stdio.h>

#include "trans.h"

static_assert(COUNT_TRANS == 6, "Amount of forms of transport has changed");
const char *transport_strings[COUNT_TRANS] = {
  [TRANS_WALK] = "walk",
  [TRANS_BUS] = "bus",
  [TRANS_TRAM] = "tram",
  [TRANS_TUBE] = "tube",
  [TRANS_NATRAIL] = "natrail",
  [TRANS_MANY] = "many"
};

Transport *table[DIGIT][DIGIT][DIGIT][DIGIT][DIGIT][DIGIT][DIGIT][DIGIT];

void print_trans(const Transport *trans) {
  printf("%s %.3s->%.3s", transport_strings[trans->type], trans->from, trans->to);

  if (trans->info) {
    printf(" info=\"%s\"", trans->info);
  }

  if (trans->child) {
    printf(" [");
    print_trans(trans->child);
    printf("]");
  }

  if (trans->next) {
    printf(", ");
    print_trans(trans->next);
  }
}

void read_in_table(const char *filename) {
}

void write_out_table(const char *filename) {
}
