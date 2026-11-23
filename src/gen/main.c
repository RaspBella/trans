#include <trans/trans.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gen/html.h>
#include <gen/json.h>

pid_t die_on_error_fork(void) {
  pid_t p = fork();

  if (p < 0) {
    perror("Fork failed");

    exit(EXIT_FAILURE);
  }

  return p;
}

FILE *die_on_error_fopen(const char *path, const char *mode) {
  FILE *fp = fopen(path, mode);

  if (!fp) {
    fprintf(stderr, "Couldn't open: %s\n", path);

    exit(EXIT_FAILURE);
  }

  return fp;
}

void write_data(const char *filename, void (*fn)(FILE *fp)) {
  FILE *fp = die_on_error_fopen(filename, "w");

  fn(fp);

  fclose(fp);
}

void write_routes(const char *filename, size_t count, const struct route *routes[], void (*fn)(FILE*, size_t, const struct route*[])) {
  FILE *fp = die_on_error_fopen(filename, "w");

  fn(fp, count, routes);

  fclose(fp);
}

void write_route(const char *filename, const char *prev, const struct route *route, const char *next, void (*fn)(FILE*, const char *prev, const struct route*, const char *next)) {
  FILE *fp = die_on_error_fopen(filename, "w");

  fn(fp, prev, route, next);

  fclose(fp);
}

int main(void) {
  extern const struct route *routes[];
  extern const size_t route_count;

  if (die_on_error_fork()) {
    for (size_t i = 0; i < route_count; ++i) {
      if (die_on_error_fork()) {
        char filename[] = "docs/yyyy-mm-dd/index.html";

        memcpy(filename + sizeof("docs/") - 1, routes[i]->iso, sizeof("yyyy-mm-dd") - 1);

        const char *prev = i == 0 ? NULL
          : routes[i - 1]->iso;

        const char *next = i == route_count - 1 ? NULL
          : routes[i - 1]->iso;

        write_route(filename, prev, routes[i], next, route_index_html);
      }

      break;
    }
  }

  else {
    die_on_error_fork() ? write_routes("docs/index.html", route_count, routes, index_html)
      : die_on_error_fork() ? write_data("docs/db/index.json", index_json)
      : die_on_error_fork() ? write_routes("docs/db/routes/index.json", route_count, routes, routes_index_json)
      : die_on_error_fork() ? write_data("docs/db/crs/index.json", crs_index_json)
      : die_on_error_fork() ? write_data("docs/db/crs/gb_nr/index.json", crs_gb_nr_index_json)
      : write_data("docs/db/crs/iata/index.json", crs_iata_index_json);
  }
}
