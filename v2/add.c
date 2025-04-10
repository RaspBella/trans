#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <editline.h>

#include "trans.h"
#include "parser.h"
#include "usage.h"

const char *data_file = "data.json";
const char *hist_file = ".trans_history";

const char *prompt = "> ";

FILE *fp = NULL;
char *buffer = NULL;

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
  write_history(hist_file);
  write_out_table(data_file);

  if (fp) fclose(fp);

  if (buffer) free(buffer);
}

int main(int argc, char **argv) {
  read_history(hist_file);
  read_in_table(data_file);

  atexit(clean_up);

  if (argc == 1) {
    char *line = readline(prompt);

    while (line) {
      if (!parser(*argv, "<stdin>", line)) {
        fprintf(stderr, "Failed to parse: %s\n", line);
      }

      free(line);

      line = readline(prompt);
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
            long offset = 0;

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

            if (!parser(*argv, argv[2], buffer)) {
              fprintf(stderr, "Failed to parse: %s\n", buffer);

              exit(EXIT_FAILURE);
            }
          }

          break;

        case SUB_COMMAND_CODE:
          if (!parser(*argv, "<args>", argv[2])) {
            fprintf(stderr, "Failed to parse: %s\n", argv[2]);

            exit(EXIT_FAILURE);
          }
          break;

        case SUB_COMMAND_HELP:
          usage(stdout, *argv);

          exit(EXIT_SUCCESS);

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
