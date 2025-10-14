#include "parse.h"
#include "utils.h"
#include "json.h"

#include "bestline.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <libgen.h>
#include <sys/stat.h>

#define pop(argc, argv) *argv++; argc--;

#define INDENT 2

char *program;

char *input;
char *output;

char *line;

int indent;

void cleanup(void) {
  if (root) {
    if (!output) {
      if (!dump(input, indent)) {
        fprintf(stderr, "Error writing file: `%s`\n", input);

        exit(EXIT_FAILURE);
      }
    }

    else {
      free_json(root);
    }
  }

  if (line) free(line);
}

void add(int argc, char **argv, enum mode mode) {
  if (!argc) {
    usage(program, mode);

    exit(EXIT_FAILURE);
  }

  input = pop(argc, argv);

  if (!load(input)) {
    fprintf(stderr, "Error reading file: `%s`\n", input);

    exit(EXIT_FAILURE);
  }

  while ((line = bestlineWithHistory("trans >>> ", "trans"))) {
    bool ret = parse(line, .indent = indent);

    if (!ret) {
      fprintf(stderr, "Couldn't parse: `%s`\n", line);
    }

    free(line);
  }

  printf("exit()\n");

  exit(EXIT_SUCCESS);
}

void gen_head(FILE *fp) {
  fprintf(
    fp,
    "<!DOCTYPE html>\n"
    "<html lang=\"en\">\n"
    "  <head>\n"
    "    <title>transportation - RaspBella</title>\n"
    "    <link rel=\"stylesheet\" href=\"/main.css\">\n"
    "    <meta charset=\"UTF-8\">\n"
    "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
    "\n"
    "    <link rel=\"apple-touch-icon\" sizes=\"180x180\" href=\"/favicon/apple-touch-icon.png\">\n"
    "    <link rel=\"icon\" type=\"image/png\" sizes=\"32x32\" href=\"/favicon/favicon-32x32.png\">\n"
    "    <link rel=\"icon\" type=\"image/png\" sizes=\"16x16\" href=\"/favicon/favicon-16x16.png\">\n"
    "    <link rel=\"manifest\" href=\"/favicon/site.webmanifest\">\n"
    "  </head>\n"
    "  <body>\n"
    "    <ul class=\"nav\">\n"
    "      <li><a href=\"/\">home</a></li>\n"
    "      <li><a href=\"/RaspBella\">about</a></li>\n"
    "      <li><a href=\"/cubing\">cubing</a></li>\n"
    "      <li><a href=\"/linux\">linux</a></li>\n"
    "      <li><a href=\"/media\">media</a></li>\n"
    "      <li><a class=\"active\" href=\"/trans\">transportation</a></li>\n"
    "    </ul>\n"
  );
}

void gen_tail(FILE *fp) {
  fprintf(
    fp,
    "  </body>\n"
    "</html>"
  );
}

void gen_root(FILE *fp) {
  gen_head(fp);

  fprintf(
    fp,
    "    <table>\n"
    "      <thead>\n"
    "        <tr>\n"
    "          <th>Date</th>\n"
    "          <th>From</th>\n"
    "          <th>To</th>\n"
    "          <th>Sub</th>\n"
    "          <th>Info</th>\n"
    "        </tr>\n"
    "      </thead>\n"
    "      <tbody>\n"
  );

  struct Iterable date_it;
  struct Iterable data_it;

  if (!iterable(&date_it, root)) return;
  if (!iterable(&data_it, root)) return;

  char *date = key_iterate(&date_it);
  Json *data = json_iterate(&data_it);

  do {
    fprintf(stderr, "date: \"%s\"\ndata: ", date);
    fprintj(stderr, data, indent);
    fprintf(stderr, "\n");

    date = key_iterate(&date_it);
    data = json_iterate(&data_it);
  } while (date && data);

  fprintf(
    fp,
    "      </tbody>\n"
    "    </table>\n"
  );

  gen_tail(fp);
}

void gen(int argc, char **argv, enum mode mode) {
  if (argc < 2) {
    usage(program, mode);

    exit(EXIT_FAILURE);
  }

  input = pop(argc, argv);
  output = pop(argc, argv);

  if (!load(input)) {
    fprintf(stderr, "Error reading file: `%s`\n", input);

    exit(EXIT_FAILURE);
  }

  struct stat sb;

  if (stat(output, &sb)) {
    mkdir(output, S_IRWXU);
  }

  else {
    if (!S_ISDIR(sb.st_mode)) {
      fprintf(stderr, "error: `%s` not a dir\n", output);

      exit(EXIT_FAILURE);
    }
  }

  size_t len = strlen(output) + strlen("/yyyy-mm-dd/abc->xyz/index.html");
  char *file = calloc(len + 1, sizeof(char));

  memcpy(file, output, strlen(output));
  memcpy(file + strlen(output), "/index.html", strlen("/index.html"));

  FILE *fp = fopen(file, "w");

  gen_root(fp);

  fclose(fp);
  free(file);

  exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
  if (atexit(cleanup)) {
    fprintf(stderr, "atexit: Failed to register function: cleanup\n");

    exit(EXIT_FAILURE);
  }

  indent = INDENT;

  program = pop(argc, argv);

  if (!strcmp(basename(program), "trana-add")) {
    add(argc, argv, ADD_CMD);
  }

  else if (!strcmp(basename(program), "trans-gen")) {
    gen(argc, argv, GEN_CMD);
  }

  if (!argc) {
    usage(program, NO_MODE);

    exit(EXIT_FAILURE);
  }

  char *mode = pop(argc, argv);

  if (!strcmp(mode, "add")) {
    add(argc, argv, ADD_MODE);
  }

  else if (!strcmp(mode, "gen")) {
    gen(argc, argv, GEN_MODE);
  }

  usage(program, NO_MODE);

  exit(EXIT_FAILURE);
}
