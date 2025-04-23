#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "trans.h"
#include "json.h"
#include "parser/json.h"

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
  FILE *fp = fopen(filename, "r");

  if (fp == NULL) {
    return;
  }

  fseek(fp, 0, SEEK_END);

  long file_size = ftell(fp);

  if (file_size == 0) {
    fclose(fp);

    return;
  }

  char *str = calloc(file_size + 1, sizeof(char));

  rewind(fp);

  if (fread(str, sizeof(char), file_size, fp) != file_size) {
    fprintf(stderr, "Failed to read %zu bytes from file: %s\n", file_size, filename);

    fclose(fp);
    free(str);

    exit(EXIT_FAILURE);
  }

  fclose(fp);

  Json *data = json_parser(filename, str);

  print_json(data);

  if (data) {
    free_json(data);
  }

  free(str);
}

void write_out_table(const char *filename) {
}
