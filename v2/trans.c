#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "json.h"
#include "trans.h"
#include "bestline.h"
#include "usage.h"

const char data_filename[] = "data.json";

extern Json *root;

void parse_json(FILE*);
//void parse_trans(FILE*);

char *buffer = NULL;

void clean_up(void) {
  FILE *fp = fopen(data_filename, "w");

  fprint_json(root, fp);

  fclose(fp);

  free_json(root);
}

void init(void) {
  FILE *fp = fopen(data_filename, "r");

  if (fp) {
    parse_json(fp);

    fclose(fp);
  }

  if (!root) {
    root = new_json(JsonObject, NULL);

    map_set(root->data.object, strdup("version"), new_json(JsonNumber, new_number(TRANS_VERSION)));
  }
    
  atexit(clean_up);
}

int main(int argc, char **argv) {
  if (argc == 1) {
    init();

    while ((buffer = bestlineWithHistory("> ", "trans"))) {
      FILE *fp = fmemopen(buffer, strlen(buffer) + 1, "r");

      //parse_trans(fp);

      fclose(fp);

      free(buffer);
    }

    exit(EXIT_SUCCESS);
  }

  else if (argc == 3) {
    if (argv[1][0] == '-') {
      if (argv[1][1] == 'h' && argv[1][2] == 0) {
        usage(stdout, NULL);

        exit(EXIT_SUCCESS);
      }

      else if (argv[1][1] == 'c' && argv[1][2] == 0) {
        init();

        FILE *fp = fmemopen(buffer, strlen(buffer) + 1, "r");

        //parse_trans(fp);

        fclose(fp);

        exit(EXIT_SUCCESS);
      }

      else if (argv[1][1] == 'f' && argv[1][2] == 0) {
        init();

        FILE *fp = fmemopen(buffer, strlen(buffer) + 1, "r");

        //parse_trans(fp);

        fclose(fp);
        
        exit(EXIT_SUCCESS);
      }
    }
  }

  usage(stderr, NULL);
  exit(EXIT_FAILURE);
}
