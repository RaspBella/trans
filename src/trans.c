#include "parse.h"
#include "utils.h"
#include "json.h"
#include "crs.h"

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

void gen_root_head(FILE *fp) {
  gen_head(fp);

  fprintf(
    fp,
    "    <div>\n"
    "      <ul class=\"nav\">\n"
    "        <li id=\"today\"><a id=\"today-link\" href=\"today\">today?</a></li>\n"
    "        <li><a href=\"crs\">crs</a></li>\n"
    "      </ul>\n"
    "      <table>\n"
    "        <thead>\n"
    "          <tr>\n"
    "            <th>Date</th>\n"
    "            <th>From</th>\n"
    "            <th>To</th>\n"
    "            <th>Sub</th>\n"
    "            <th>Info</th>\n"
    "          </tr>\n"
    "        </thead>\n"
    "        <tbody>\n"
  );
}

void gen_root_tail(FILE *fp) {
  fprintf(
    fp,
    "      </tbody>\n"
    "    </table>\n"
    "  </div>\n"
    "  </body>\n"
    "  <script src=\"trans.js\"></script>\n"
    "</html>"
  );
}

char *property2string(Json *json, char *property) {
  Json *value = object_get(json, property);

  if (!value) {
    fprintf(
      stderr,
      "%s: couldn't access `%s` property\n",
      __func__,
      property
    );

    return NULL;
  }

  if (json_type(value) != Json_String) {
    fprintf(
      stderr,
      "%s: expected %s got %s\n",
      __func__,
      json_type_string(Json_String),
      json_type_string(json_type(value))
    );

    return NULL;
  }

  return json_string2string(value);
}

void fprint_place(FILE *fp, char *place) {
  if (strlen(place) == 3 && VALID_CRS(place)) {
    fprintf(fp, "%s [%s]", crs(place), place);
  }

  else {
    fprintf(fp, "%s", place);
  }
}

void gen_root_row_array_elem(FILE *fp, char *date, Json *elem) {
  if (json_type(elem) != Json_Object) {
    fprintf(
      stderr,
      "%s: expected %s got %s\n",
      __func__,
      json_type_string(Json_Object),
      json_type_string(json_type(elem))
    );

    fclose(fp);

    exit(EXIT_FAILURE);
  }

  fprintf(
    fp,
    "            <td>"
  );

  char *from = property2string(elem, "from");

  if (!from) {
    fclose(fp);

    exit(EXIT_FAILURE);
  }

  fprint_place(fp, from);

  fprintf(
    fp,
    "</td>\n"
    "            <td>"
  );

  char *to = property2string(elem, "to");

  if (!to) {
    fclose(fp);

    exit(EXIT_FAILURE);
  }

  fprint_place(fp, to);

  fprintf(
    fp,
    "</td>\n"
  );

  Json *sub = object_get(elem, "sub");

  if (sub) {
    fprintf(
      fp,
      "            <td>\n"
      "              <table>\n"
      "                <thead>\n"
      "                  <tr>\n"
      "                    <td>From</td>\n"
      "                    <td>To</td>\n"
      "                    <td>Info</td>\n"
      "                  </tr>\n"
      "                </thead>\n"
      "                <tbody>\n"
    );

    struct Iterable it;

    if (!iterable(&it, sub)) {
      fprintf(stderr, "%s: failed to init iterator\n", __func__);

      fclose(fp);

      exit(EXIT_FAILURE);
    }

    for (Json *elem = json_iterate(&it); elem; elem = json_iterate(&it)) {
      fprintf(
        fp,
        "                  <tr>\n"
        "                    <td>"
      );

      char *from = property2string(elem, "from");
    
      if (!from) {
        fclose(fp);
    
        exit(EXIT_FAILURE);
      }
    
      fprint_place(fp, from);
    
      fprintf(
        fp,
        "</td>\n"
        "                    <td>"
      );
    
      char *to = property2string(elem, "to");
    
      if (!to) {
        fclose(fp);
    
        exit(EXIT_FAILURE);
      }
    
      fprint_place(fp, to);
    
      fprintf(
        fp,
        "</td>\n"
      );

      char *text = property2string(elem, "text");
    
      if (!text) {
        fclose(fp);
    
        exit(EXIT_FAILURE);
      }
    
      Json *link = object_get(elem, "link");
    
      if (link) {
        char *link = property2string(elem, "link");
    
        if (!link) {
          fclose(fp);
    
          exit(EXIT_FAILURE);
        }
    
        fprintf(
          fp,
          "                    <td><a href=\"%s/%s->%s\">%s</td>\n",
          date, from, to, text
        );
      }
    
      else {
        fprintf(
          fp,
          "                    <td>%s</td>\n",
          text
        );
      }
      
      fprintf(
        fp,
        "                  </tr>\n"
      );
    }

    fprintf(
      fp,
      "                </tbody>\n"
      "              </table>\n"
      "            </td>\n"
    );
  }

  else {
    fprintf(
      fp,
      "            <td>N/A</td>\n"
    );
  }

  char *text = property2string(elem, "text");

  if (!text) {
    fclose(fp);

    exit(EXIT_FAILURE);
  }

  Json *link = object_get(elem, "link");

  if (link) {
    char *link = property2string(elem, "link");

    if (!link) {
      fclose(fp);

      exit(EXIT_FAILURE);
    }

    fprintf(
      fp,
      "            <td><a href=\"%s/%s->%s\">%s</td>\n",
      date, from, to, text
    );
  }

  else {
    fprintf(
      fp,
      "            <td>%s</td>\n",
      text
    );
  }
}

void gen_root_row_array(FILE *fp, char *date, Json *array) {
  fprintf(
    fp,
    "          <tr>\n"
    "            <td rowspan=\"%zu\"><a href=\"%s\">%s</a></td>\n",
    length(array), date, date
  );

  struct Iterable it;

  if (!iterable(&it, array)) {
    fprintf(stderr, "%s: failed to init iterator\n", __func__);

    fclose(fp);

    exit(EXIT_FAILURE);
  }

  Json *elem = json_iterate(&it);

  gen_root_row_array_elem(fp, date, elem);

  fprintf(
    fp,
    "          </tr>\n"
  );

  for (elem = json_iterate(&it); elem; elem = json_iterate(&it)) {
    fprintf(
      fp,
      "          <tr>\n"
    );

    gen_root_row_array_elem(fp, date, elem);

    fprintf(
      fp,
      "          </tr>\n"
    );
  }
}

void gen_root_row_object(FILE *fp, char *date, Json *object) {
  fprintf(
    fp,
    "          <tr>\n"
    "            <td><a href=\"%s\">%s</a></td>\n"
    "            <td>",
    date, date
  );

  char *from = property2string(object, "from");

  if (!from) {
    fclose(fp);

    exit(EXIT_FAILURE);
  }

  fprint_place(fp, from);

  fprintf(
    fp,
    "</td>\n"
    "            <td>"
  );

  char *to = property2string(object, "to");

  if (!to) {
    fclose(fp);

    exit(EXIT_FAILURE);
  }

  fprint_place(fp, to);

  fprintf(
    fp,
    "</td>\n"
  );

  Json *sub = object_get(object, "sub");

  if (sub) {
    fprintf(
      fp,
      "            <td>\n"
      "              <table>\n"
      "                <thead>\n"
      "                  <tr>\n"
      "                    <td>From</td>\n"
      "                    <td>To</td>\n"
      "                    <td>Info</td>\n"
      "                  </tr>\n"
      "                </thead>\n"
      "                <tbody>\n"
    );

    struct Iterable it;

    if (!iterable(&it, sub)) {
      fprintf(stderr, "%s: failed to init iterator\n", __func__);

      fclose(fp);

      exit(EXIT_FAILURE);
    }

    for (Json *elem = json_iterate(&it); elem; elem = json_iterate(&it)) {
      fprintf(
        fp,
        "                  <tr>\n"
        "                    <td>"
      );

      char *from = property2string(elem, "from");
    
      if (!from) {
        fclose(fp);
    
        exit(EXIT_FAILURE);
      }
    
      fprint_place(fp, from);
    
      fprintf(
        fp,
        "</td>\n"
        "                    <td>"
      );
    
      char *to = property2string(elem, "to");
    
      if (!to) {
        fclose(fp);
    
        exit(EXIT_FAILURE);
      }
    
      fprint_place(fp, to);
    
      fprintf(
        fp,
        "</td>\n"
      );

      char *text = property2string(elem, "text");
    
      if (!text) {
        fclose(fp);
    
        exit(EXIT_FAILURE);
      }
    
      Json *link = object_get(elem, "link");
    
      if (link) {
        char *link = property2string(elem, "link");
    
        if (!link) {
          fclose(fp);
    
          exit(EXIT_FAILURE);
        }
    
        fprintf(
          fp,
          "                    <td><a href=\"%s/%s->%s\">%s</td>\n",
          date, from, to, text
        );
      }
    
      else {
        fprintf(
          fp,
          "                    <td>%s</td>\n",
          text
        );
      }
      
      fprintf(
        fp,
        "                  </tr>\n"
      );
    }

    fprintf(
      fp,
      "                </tbody>\n"
      "              </table>\n"
      "            </td>\n"
    );
  }

  else {
    fprintf(
      fp,
      "            <td>N/A</td>\n"
    );
  }

  char *text = property2string(object, "text");

  if (!text) {
    fclose(fp);

    exit(EXIT_FAILURE);
  }

  Json *link = object_get(object, "link");

  if (link) {
    char *link = property2string(object, "link");

    if (!link) {
      fclose(fp);

      exit(EXIT_FAILURE);
    }

    fprintf(
      fp,
      "            <td><a href=\"%s/%s->%s\">%s</td>\n",
      date, from, to, text
    );
  }

  else {
    fprintf(
      fp,
      "            <td>%s</td>\n",
      text
    );
  }

  fprintf(
    fp,
    "          </tr>\n"
  );
}

void gen_root_row(FILE *fp, char *date, Json *data) {
  switch (json_type(data)) {
    case Json_Array:
      gen_root_row_array(fp, date, data);

      break;

    case Json_Object:
      gen_root_row_object(fp, date, data);

      break;

    default:
      fprintf(
        stderr,
        "%s: expected %s or %s got %s\n",
        __func__,
        json_type_string(Json_Array),
        json_type_string(Json_Object),
        json_type_string(json_type(data))
      );

      fclose(fp);

      exit(EXIT_FAILURE);
  }
}

void gen_root_rows(FILE *fp) {
  struct Iterable its[2];

  if (!iterable(&its[0], root) || !iterable(&its[1], root)) {
    fprintf(stderr, "%s: Failed to init iterable(s)\n", __func__);

    fclose(fp);

    exit(EXIT_FAILURE);
  }

  char *date = key_iterate(&its[0]);
  Json *data = json_iterate(&its[1]);

  do {
    gen_root_row(fp, date, data);

    date = key_iterate(&its[0]);
    data = json_iterate(&its[1]);
  } while (date && data);
}

void gen_root(FILE *fp) {
  gen_root_head(fp);

  gen_root_rows(fp);

  gen_root_tail(fp);
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

  const char *slash_index = "/index.html";

  memcpy(file, output, strlen(output));
  memcpy(file + strlen(output), slash_index, strlen(slash_index));

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

  if (!strcmp(basename(program), "trans-add")) {
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
