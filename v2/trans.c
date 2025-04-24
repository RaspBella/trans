#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "trans.h"
#include "json.h"
#include "parser/json.h"
#include "map.h"

#define TRANS_VERSION 2

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

void free_trans(Transport *trans) {
  if (trans->next) {
    free_trans(trans->next);
  }

  if (trans->child) {
    free_trans(trans->child);
  }

  if (trans->info) {
    free(trans->info);
  }

  free(trans);
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

// forward declaration
Json *trans_to_json(Transport*);

Json *trans_to_json_object(Transport *trans) {
  Json *new = new_json(JsonObject, new_map(0, NULL, NULL));
  
  map_set(new->data, strdup("type"), new_json(JsonString, strdup(transport_strings[trans->type])));

  map_set(new->data, strdup("from"), new_json(JsonString, strdup(trans->from)));

  map_set(new->data, strdup("to"), new_json(JsonString, strdup(trans->to)));

  if (trans->info) {
    map_set(new->data, strdup("info"), new_json(JsonString, strdup(trans->info)));
  }

  else {
    map_set(new->data, strdup("info"), new_json(JsonNull, NULL));
  }

  if (trans->child) {
    map_set(new->data, strdup("child"), trans_to_json(trans->child));
  }

  return new;
}

Json *trans_to_json(Transport *trans) {
  Json *new;

  if (trans->next) {
    new = new_json(JsonArray, calloc(1, sizeof(struct JsonArray)));

    while (trans->next) {
      da_append((struct JsonArray*) new->data, trans_to_json_object(trans));

      trans = trans->next;
    }
  }

  else {
    new = trans_to_json_object(trans);
  }

  return new;
}

void write_out_table(const char *filename) {
  FILE *fp = fopen(filename, "w");

  if (fp == NULL) {
    fprintf(stderr, "Couldn't write to file: %s\n", filename);

    exit(EXIT_FAILURE);
  }

  Json *json = new_json(JsonObject, new_map(0, NULL, NULL));
  map_set(json->data, strdup("version"), new_json(JsonNumber, (void*) TRANS_VERSION));

  for (int i = 0; i < DIGIT; i++) {
    for (int j = 0; j < DIGIT; j++) {
      for (int k = 0; k < DIGIT; k++) {
        for (int l = 0; l < DIGIT; l++) {
          for (int m = 0; m < DIGIT; m++) {
            for (int n = 0; n < DIGIT; n++) {
              for (int o = 0; o < DIGIT; o++) {
                for (int p = 0; p < DIGIT; p++) {
                  if (table[i][j][k][l][m][n][o][p]) {
                    char *isodate = calloc(sizeof("yyyy-mm-dd") + 1, sizeof(char));

                    // init isodate
                    isodate[0] = '0' + i;
                    isodate[1] = '0' + j;
                    isodate[2] = '0' + k;
                    isodate[3] = '0' + l;

                    isodate[4] = '-';

                    isodate[5] = '0' + m;
                    isodate[6] = '0' + n;

                    isodate[7] = '-';

                    isodate[8] = '0' + o;
                    isodate[9] = '0' + p;

                    map_set(json->data, isodate, trans_to_json(table[i][j][k][l][m][n][o][p]));

                    free_trans(table[i][j][k][l][m][n][o][p]);
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  fprint_json(json, fp);

  free_json(json);

  fclose(fp);
}
