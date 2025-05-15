#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "bestline.h"
#include "map.h"
#include "json.h"
#include "trans.h"
#include "parser/json.h"
#include "parser/trans.h"
#include "usage.h"

const char data_file[] = "data.json";

char *buffer = NULL;
Json *json = NULL;

typedef enum {
  SUB_COMMAND_INVALID = -1,
  SUB_COMMAND_INPUT_FILE,
  SUB_COMMAND_CODE,
  SUB_COMMAND_HELP,
  COUNT_SUB_COMMANDS
} Sub_Command_Index;

static_assert(COUNT_SUB_COMMANDS == 3, "Amount of sub commands has changed");
const char *sub_commands[COUNT_SUB_COMMANDS] = {
  [SUB_COMMAND_INPUT_FILE] = "-f",
  [SUB_COMMAND_CODE] = "-c",
  [SUB_COMMAND_HELP] = "-h"
};

void clean_up(void) {
  FILE *fp = fopen(data_file, "w");

  if (fp) {
    fprint_json(json, fp);

    fclose(fp);
  }

  else {
    fprintf(stderr, "Couldn't write to file: %s\n", data_file);
  }

  if (buffer) free(buffer);

  if (json) free_json(json);
}

int main(int argc, char **argv) {
  FILE *fp = fopen(data_file, "r");

  if (fp) {
    fseek(fp, 0, SEEK_END);

    long file_size = ftell(fp);

    if (file_size > 0) {
      char *str = calloc(file_size + 1, sizeof(char));

      rewind(fp);

      if (fread(str, sizeof(char), file_size, fp) != file_size) {
        fprintf(stderr, "Failed to read %zu bytes from file: %s\n", file_size, data_file);

        fclose(fp);
        free(str);

        exit(EXIT_FAILURE);
      }

      json = parse_json(data_file, str);

      free(str);
    }

    fclose(fp);
  }

  if (!json) {
    json = new_json(JsonObject, new_map(0, NULL, NULL));

    map_set(json->data, strdup("version"), new_json(JsonNumber, (void*) TRANS_VERSION));
  }

  // TODO remove when redundant
  print_json(json);
  printf("\n");

  atexit(clean_up);

  if (argc == 1) {
    char *line;

    while ((line = bestlineWithHistory("> ", "trans"))) {
      parse_trans(json, "<stdin>", line);

      free(line);
    }
  }

  else if (argc == 3) {
    Sub_Command_Index sub_command = SUB_COMMAND_INVALID;

    for (int i = 0; i < COUNT_SUB_COMMANDS; i++) {
      if (strlen(sub_commands[i]) == strlen(argv[1])) {
        if (!strncmp(sub_commands[i], argv[1], strlen(argv[1]))) {
          sub_command = i;
          break;
        }
      }
    }

    if (sub_command != SUB_COMMAND_INVALID) {
      switch (sub_command) {
        case SUB_COMMAND_INPUT_FILE:
          fp = fopen(argv[2], "r");
          long file_size = 0;

          if (!fp) {
            fprintf(stderr, "Can't read file: %s\n", argv[2]);

            exit(EXIT_FAILURE);
          }

          fseek(fp, 0, SEEK_END);

          file_size = ftell(fp);

          rewind(fp);

          if (file_size < 0) {
            fprintf(stderr, "Error getting file size: %s\n", argv[2]);

            exit(EXIT_FAILURE);
          }

          else if (file_size == 0) {
            exit(EXIT_SUCCESS);
          }

          else {
            buffer = calloc(file_size + 1, sizeof(char));

            if (!buffer) {
              fprintf(stderr, "Failed to allocate memory\n");

              exit(EXIT_FAILURE);
            }

            size_t bytes_read = fread(buffer, 1, file_size, fp);
            if (bytes_read != file_size) {
              fprintf(stderr, "Failed to read correct amount of file bytes: %zu/%zu\n", bytes_read, file_size);

              exit(EXIT_FAILURE);
            }

            parse_trans(json, argv[2], buffer);
          }

          fclose(fp);

          break;

        case SUB_COMMAND_CODE:
          parse_trans(json, "<args>", argv[2]);

          break;

        case SUB_COMMAND_HELP:
          usage(stdout, *argv);

          exit(EXIT_SUCCESS);

          break;

        default:
          break;
      }
    }

    else {
      usage(stderr, *argv);

      exit(EXIT_FAILURE);
    }
  }

  else {
    usage(stderr, *argv);

    exit(EXIT_FAILURE);
  }
}
