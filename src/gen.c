#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

#include "state.h"
#include "crs.h"
#include "json.h"
#include "utils.h"

#define IMAGES_DIR "../images"

void gen_head(FILE *fp, char *title) {
  fprintf(
    fp,
    "<!DOCTYPE html>\n"
    "<html lang=\"en\">\n"
    "  <head>\n"
    "    <title>%s - RaspBella</title>\n"
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
    "    </ul>\n",
    title
  );
}

void gen_root_head(FILE *fp) {
  gen_head(fp, "transportation");

  fprintf(
    fp,
    "    <div>\n"
    "      <ul class=\"nav\">\n"
    "        <li id=\"today\"><a id=\"today_link\" href=\"today\">today?</a></li>\n"
    "        <li><a href=\"crs\">crs</a></li>\n"
    "        <li><a href=\"tww\">tww</a><li>\n"
    "        <li>\n"
    "          <input id=\"query\" type=\"text\" placeholder=\"query...\">\n"
    "          <button id=\"submit_query\">Submit query</button>\n"
    "        </li>\n"
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
    "        </tbody>\n"
    "      </table>\n"
    "    </div>\n"
    "  </body>\n"
    "  <script src=\"trans.js\"></script>\n"
    "</html>"
  );
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
  char *to = property2string(elem, "to");

  if (!from || !to) {
    fclose(fp);

    exit(EXIT_FAILURE);
  }

  fprint_place(fp, from);

  fprintf(
    fp,
    "</td>\n"
    "            <td>"
  );

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
      fclose(fp);

      IT_ERR();
    }

    for (Json *elem = json_iterate(&it); elem; elem = json_iterate(&it)) {
      fprintf(
        fp,
        "                  <tr>\n"
        "                    <td>"
      );

      char *from = property2string(elem, "from");
      char *to = property2string(elem, "to");

      if (!from || !to) {
        fclose(fp);

        exit(EXIT_FAILURE);
      }

      fprint_place(fp, from);

      fprintf(
        fp,
        "</td>\n"
        "                    <td>"
      );

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

      if (object_get(elem, "link")) {
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

  if (object_get(elem, "link")) {
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
    fclose(fp);

    IT_ERR();
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
  char *to = property2string(object, "to");

  if (!from || !to) {
    fclose(fp);

    exit(EXIT_FAILURE);
  }

  fprint_place(fp, from);

  fprintf(
    fp,
    "</td>\n"
    "            <td>"
  );

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
      fclose(fp);

      IT_ERR();
    }

    for (Json *elem = json_iterate(&it); elem; elem = json_iterate(&it)) {
      fprintf(
        fp,
        "                  <tr>\n"
        "                    <td>"
      );

      char *from = property2string(elem, "from");
      char *to = property2string(elem, "to");

      if (!from || !to) {
        fclose(fp);

        exit(EXIT_FAILURE);
      }

      fprint_place(fp, from);

      fprintf(
        fp,
        "</td>\n"
        "                    <td>"
      );

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

      if (object_get(elem, "link")) {
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

  if (object_get(object, "link")) {
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
    fclose(fp);

    IT_ERR();
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

void gen_yyyy_mm_dd_head(FILE *fp) {
  fprintf(
    fp,
    "      <table>\n"
    "        <thead>\n"
    "          <tr>\n"
    "            <th>From</th>\n"
    "            <th>To</th>\n"
    "            <th>Sub</th>\n"
    "            <th>Info</th>\n"
    "          </tr>\n"
    "        </thead>\n"
    "        <tbody>\n"
  );
}

void gen_yyyy_mm_dd_tail(FILE *fp) {
  fprintf(
    fp,
    "        </tbody>\n"
    "      </table>\n"
    "    </div>\n"
    "  </body>\n"
    "</html>"
  );
}

void gen_yyyy_mm_dd_row(FILE *fp, Json *object) {
  char *from = property2string(object, "from");
  char *to = property2string(object, "to");

  if (!from || !to) {
    fclose(fp);

    exit(EXIT_FAILURE);
  }

  fprintf(
    fp,
    "          <tr>\n"
    "            <td>"
  );

  fprint_place(fp, from);

  fprintf(
    fp,
    "</td>\n"
    "            <td>"
  );

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
      fclose(fp);

      IT_ERR();
    }

    for (Json *elem = json_iterate(&it); elem; elem = json_iterate(&it)) {
      fprintf(
        fp,
        "                  <tr>\n"
        "                    <td>"
      );

      char *from = property2string(elem, "from");
      char *to = property2string(elem, "to");

      if (!from || !to) {
        fclose(fp);

        exit(EXIT_FAILURE);
      }

      fprint_place(fp, from);

      fprintf(
        fp,
        "</td>\n"
        "                    <td>"
      );

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

      if (object_get(elem, "link")) {
        char *link = property2string(elem, "link");

        if (!link) {
          fclose(fp);

          exit(EXIT_FAILURE);
        }

        fprintf(
          fp,
          "                    <td><a href=\"%s->%s\">%s</td>\n",
          from, to, text
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

  if (object_get(object, "link")) {
    char *link = property2string(object, "link");

    if (!link) {
      fclose(fp);

      exit(EXIT_FAILURE);
    }

    fprintf(
      fp,
      "            <td><a href=\"%s->%s\">%s</td>\n",
      from, to, text
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

void gen_yyyy_mm_dd(FILE *fp, char *date, Json *data) {
  const char *iso = "yyyy-mm-dd";
  const char *template = "yyyy-mm-dd - transportation";

  char title[strlen(template) + 1];

  memcpy(title, date, strlen(iso));

  memcpy(
    title + strlen(iso),
    template + strlen(iso),
    strlen(template + strlen(iso))
  );

  title[strlen(template)] = 0;

  gen_head(fp, title);

  fprintf(
    fp,
    "    <div>\n"
    "      <h1>%s</h1>\n",
    date
  );
  
  gen_yyyy_mm_dd_head(fp);

  switch (json_type(data)) {
    case Json_Array:
      struct Iterable it;

      if (!iterable(&it, data)) {
        fclose(fp);

        IT_ERR();
      }

      for (Json *elem = json_iterate(&it); elem; elem = json_iterate(&it)) {
        gen_yyyy_mm_dd_row(fp, elem);
      }

      break;

    case Json_Object:
      gen_yyyy_mm_dd_row(fp, data);

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

  gen_yyyy_mm_dd_tail(fp);
}

void gen_link(FILE *fp, char *link) {
  fprintf(
    fp,
    "<meta http-equiv=\"Refresh\" content=\"0; %s\" />",
    link
  );
}

void gen_links(FILE **fp, char *buf, Json *json, char *output, char *date) {
  switch (json_type(json)) {
    case Json_Array:
      struct Iterable it;

      if (!iterable(&it, json)) {
        fclose(*fp);

        IT_ERR();
      }

      for (Json *elem = json_iterate(&it); elem; elem = json_iterate(&it)) {
        gen_links(fp, buf, elem, output, date);
      }

      break;

    case Json_Object:
      if (object_get(json, "link")) {
        char *link = property2string(json, "link");

        char *from = property2string(json, "from");
        char *to = property2string(json, "to");

        if (!from || !to) {
          fclose(*fp);

          exit(EXIT_FAILURE);
        }

        memcpy(
          buf + strlen(output) + strlen("/yyyy-mm-dd/"),
          from,
          3
        );

        memcpy(
          buf + strlen(output) + strlen("/yyyy-mm-dd/..."),
          "->",
          2
        );

        memcpy(
          buf + strlen(output) + strlen("/yyyy-mm-dd/...->"),
          to,
          3
        );

        buf[strlen(output) + strlen("/yyyy-mm-dd/...->...")] = 0;

        // buf = "path/yyyy-mm-dd/...->..."

        make_dir(buf);

        memcpy(
          buf + strlen(output) + strlen("/yyyy-mm-dd/...->..."),
          "/index.html",
          strlen("/index.html")
        );

        // buf = "path/yyyy-mm-dd/...->.../index.html"

        *fp = freopen(buf, "w", *fp);

        gen_link(*fp, link);
      }

      Json *sub = object_get(json, "sub");

      if (sub) {
        gen_links(fp, buf, sub, output, date);
      }

      break;

    default:
      fprintf(
        stderr,
        "%s: expected %s or %s got %s\n",
        __func__,
        json_type_string(Json_Array),
        json_type_string(Json_Object),
        json_type_string(json_type(json))
      );

      fclose(*fp);

      exit(EXIT_FAILURE);
  }
}

void gen_station_page(char *buf, char *output, char code[4]) {
  make_dir(buf);

  memcpy(
    buf + strlen(output) + strlen("/..."),
    "/index.html",
    strlen("/index.html")
  );

  buf[strlen(output) + strlen("/.../index.html")] = 0;

  FILE *fp = fopen(buf, "w");

  if (!fp) {
    fprintf(
      stderr,
      "%s: Couldn't open file: `%s`\n",
      __func__,
      buf
    );

    exit(EXIT_FAILURE);
  }

  fclose(fp);

  fprintf(
    stderr,
    "%s: crs(%s) = %s\n",
    __func__, code, crs(code)
  );
}

void gen_station_pages(char *buf, char *output) {
  DIR *dir = opendir(IMAGES_DIR);

  if (!dir) {
    fprintf(
      stderr,
      "%s: failed to open dir: " IMAGES_DIR,
      __func__
    );

    exit(EXIT_FAILURE);
  }

  for (struct dirent *i = readdir(dir); i != NULL; i = readdir(dir)) {
    if (strlen(i->d_name) == 3) {
      memcpy(
        buf + strlen(output) + 1,
        i->d_name,
        3
      );

      buf[strlen(output) + strlen("/...")] = 0;

      gen_station_page(buf, output, i->d_name);
    }
  }

  closedir(dir);
}

void gen(int argc, char **argv, enum mode mode) {
  if (argc < 2) {
    usage(program, mode);

    exit(EXIT_FAILURE);
  }

  input = pop(argc, argv);
  output = pop(argc, argv);
  
  if (!load(input)) {
    fprintf(
      stderr,
      "%s: error reading file: `%s`\n",
      __func__, input
    );

    exit(EXIT_FAILURE);
  }

  make_dir(output);

  size_t len = strlen(output) + strlen("/yyyy-mm-dd/abc->xyz/index.html");
  char *buf = calloc(len + 1, sizeof(char));

  memcpy(
    buf,
    output,
    strlen(output)
  );

  memcpy(
    buf + strlen(output),
    "/index.html",
    strlen("/index.html")
  );
 
  // buf = "path/index.html"

  FILE *fp = fopen(buf, "w");

  gen_root(fp);

  struct Iterable its[2];

  if (!iterable(&its[0], root) || !iterable(&its[1], root)) {
    fclose(fp);

    IT_ERR();
  }

  char *date = key_iterate(&its[0]);
  Json *data = json_iterate(&its[1]);

  do {
    memcpy(
      buf + strlen(output) + 1,
      date,
      strlen(date)
    );

    buf[strlen(output) + strlen("/yyyy-mm-dd")] = 0;

    // buf = "path/date"

    make_dir(buf);

    memcpy(
      buf + strlen(output) + 1 + strlen(date),
      "/index.html",
      strlen("/index.html")
    );

    buf[strlen(output) + strlen("/yyyy-mm-dd/index.html")] = 0;

    // buf = "path/date/index.html"

    fp = freopen(buf, "w", fp);

    gen_yyyy_mm_dd(fp, date, data);

    gen_links(&fp, buf, data, output, date);

    date = key_iterate(&its[0]);
    data = json_iterate(&its[1]);
  } while (date && data);

  gen_station_pages(buf, output);

  fclose(fp);
  free(buf);

  exit(EXIT_SUCCESS);
}
