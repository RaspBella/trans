#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <sys/stat.h>

#include "utils.h"
#include "crs.h"

void make_dir(const char *dir) {
  static struct stat sb;

  if (stat(dir, &sb)) {
    mkdir(
      dir,
      S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH
    );
  }

  else if (!S_ISDIR(sb.st_mode)) {
    fprintf(
      stderr,
      "%s: error: `%s` not a dir\n",
      __func__,
      dir
    );

    exit(EXIT_FAILURE);
  }
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
    const char *str = crs(place);

    if (str) {
      char *has_sep = strchr(str, *SEP);

      if (has_sep) {
        fprintf(fp, "%.*s(%s)", (int)(has_sep - str), str, place);
      }

      else {
        fprintf(fp, "%s(%s)", crs(place), place);
      }
    }

    else {
      fprintf(fp, "UNKNOWN(%s)", place);
    }
  }

  else {
    fprintf(fp, "%s", place);
  }
}

void add_usage(void) {
  fprintf(
    stderr,
    "add mode commands:\n"
    "  exit(`n`)                                                  Default arg(integer) is 0\n"
    "  print(`date`)                                              No arg will print all in-use dates`\n"
    "  `date` = `journey`                                         Set a journey to a date\n"
    "  `date` += `journey`                                        Append a journey to a date\n"
    "\n"
    "  `date`:\n"
    "    `yyyy`-`mm`-`dd`                                         ISO 8601\n"
    "\n"
    "  `journey`:\n"
    "    `location`->`location` `string` `link` `journey-list`    `link` and `journey-list` are optional\n"
    "\n"
    "  `location`:                                                `string` or `code`\n"
    "\n"
    "  `code`:                                                    A CRS code comprised of 3 capital letters\n"
    "\n"
    "  `link`:\n"
    "    - `string`\n"
    "\n"
    "  `journey-list`:\n"
    "    [ `journeys` ]                                           `journeys` is a comma seperated sequence of `journey`\n"
  );
}

void usage(const char *program, enum mode mode) {
  switch (mode) {
    case ADD_CMD:
      fprintf(stderr, "usage: %s `file`\n", program);

      add_usage();

      break;

    case GEN_CMD:
      fprintf(stderr, "usage: %s `input file` `output dir`\n", program);

      break;

    case ADD_MODE:
      fprintf(stderr, "usage: %s add `file`\n", program);

      add_usage();

      break;

    case GEN_MODE:
      fprintf(stderr, "usage: %s gen `input file` `output dir`\n", program);

      break;

    case NO_MODE:
      fprintf(
        stderr,
        "usage: %s add `file`\n"
        "usage: %s gen `input file` `output dir`\n",
        program,
        program
      );

      add_usage();

      break;
  }
}
