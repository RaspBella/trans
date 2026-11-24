#include <gen/html.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

void index_html(FILE *fp, size_t count, const struct route *routes[]) {
  fprintf(
    fp,
    "<!DOCTYPE html>"
    "<html lang=\"en\">"
    HTML_HEAD(HTML_TITLE("transportation - RaspBella"))
    "<body>"
    "<ul class=\"nav\">"
    "<li><a href=\"db\">db</a></li>"
    "<li><a href=\"tww\">tww</a></li>"
    "<li id=\"day\" style=\"display:none;\"></li>"
    "</ul>"
    "<table>"
    "<tr>"
    "<th>#</th>"
    "<th>Date</th>"
    "<th>Info</th>"
    "</tr>"
  );

  for (size_t i = 0; i < count; ++i) {
    fprintf(
      fp,
      "<tr>"
      "<td>%zu</td>"
      "<td><a href=\"%s\">%s</a></td>"
      "<td>%s</td>"
      "</tr>",
      i + 1,
      routes[i]->iso, routes[i]->iso,
      routes[i]->info ? routes[i]->info : ""
    );
  }

  fprintf(
    fp,
    "</table>"
    "</body>"
    "<script>"
    "fetch('/db/routes')"
    ".then(res => res.json())"
    ".then(data => {"
    "const today = new Date().toISOString().substring(0, 10);"
    "if (Object.hasOwn(data, today)) {"
    "day.innerHTML=`<a href=\"${today}\">r = ${today}</a>`;"
    "day.style.display=\"inline\";"
    "}"
    "else {"
    "const next = Object.keys(data)"
    ".filter((day) => day > today)"
    ".sort();"
    "if (next.length > 0) {"
    "day.innerHTML=`<a href=\"${next[0]}\">r = ${next[0]}</a>`;"
    "day.style.display=\"inline\";"
    "}"
    "else {"
    "const prev = Object.keys(data)"
    ".filter((day) => day < today)"
    ".sort();"
    "if (prev.length > 0) {"
    "day.innerHTML=`<a href=\"${prev[prev.length - 1]}\">r = ${prev[prev.length - 1]}</a>`;"
    "day.style.display=\"inline\";"
    "}"
    "}"
    "}"
    "});"
    "</script>"
    "</html>"
  );
}

static void bus_html(FILE *fp, const char *from, const char *to, struct trans_bus b) {
  fprintf(
    fp,
    "<td>%s</td>"
    "<td>%s</td>"
    "<td>",
    from,
    to
  );

  switch (b.type) {
    case TRANS_BUS_NO_BT:
      fprintf(
        fp,
        "%s %s",
        b.as.no_bt.op,
        b.as.no_bt.number
      );

      break;

    case TRANS_BUS_BT_TRIP:
      fprintf(
        fp,
        "<a href=\""BT_TRIP_FMT"\">bustimes</a>",
        b.as.bt
      );

      break;

    case TRANS_BUS_BT_JOURNEY:
      fprintf(
        fp,
        "<a href=\""BT_JOURNEY_FMT"\">bustimes</a>",
        b.as.bt
      );

      break;
  }

  fprintf(fp, "</td>");
}

static void train_html(FILE *fp, const char *iso, const char *from, const char *to, const struct trans_train t) {
  void *handle = dlopen("./gb_nr.so", RTLD_LAZY);

  if (!handle) {
    fprintf(stderr, "Error: %s\n", dlerror());

    exit(EXIT_FAILURE);
  }

  char symbol[] = "crs_gb_nr_???";

  memcpy(&symbol[sizeof("crs_gb_nr")], from, 3);
  char **from_name = dlsym(handle, symbol);

  memcpy(&symbol[sizeof("crs_gb_nr")], to, 3);
  char **to_name = dlsym(handle, symbol);

  assert(from_name);
  assert(to_name);

  fprintf(
    fp,
    "<td>%s(%s)</td>"
    "<td>%s(%s)</td>"
    "<td>%s("
    "<a href=\""TRAINSPLIT_FMT"\">trainsplit</a>"
    ", "
    "<a href=\""RTT_FMT"\">rtt</a>"
    ")</td>",
    *from_name, from,
    *to_name, to,
    t.id,
    TRAINSPLIT_FMT_ARG(t.id, iso),
    RTT_FMT_ARG(t.id, iso)
  );

  dlclose(handle);
}

static void ferry_html(FILE *fp, const char *from, const char *to, const struct trans_ferry f) {
  fprintf(
    fp,
    "<td>%s</td>"
    "<td>%s</td>"
    "<td>%s %s</td>",
    from,
    to,
    f.op, f.dep
  );
}

static void plane_html(FILE *fp, const char *from, const char *to, const struct trans_plane p) {
  void *handle = dlopen("./iata.so", RTLD_LAZY);

  if (!handle) {
    fprintf(stderr, "Error: %s\n", dlerror());

    exit(EXIT_FAILURE);
  }

  char symbol[] = "crs_iata_???";

  memcpy(&symbol[sizeof("crs_iata")], from, 3);
  char **from_name = dlsym(handle, symbol);

  memcpy(&symbol[sizeof("crs_iata")], to, 3);
  char **to_name = dlsym(handle, symbol);

  assert(from_name);
  assert(to_name);

  fprintf(
    fp,
    "<td>%s(%s)</td>"
    "<td>%s(%s)</td>"
    "<td>%s</td>",
    *from_name, from,
    *to_name, to,
    p.number
  );

  dlclose(handle);
}

static void trans_html(FILE *fp, size_t number, const char *iso, const struct trans t) {
  fprintf(fp, "<tr><td>%zu</td>", number);

  switch (t.type) {
    case TRANS_BUS:
      bus_html(fp, t.from, t.to, t.as.bus);

      break;

    case TRANS_TRAIN:
      train_html(fp, iso, t.from, t.to, t.as.train);

      break;

    case TRANS_FERRY:
      ferry_html(fp, t.from, t.to, t.as.ferry);

      break;

    case TRANS_PLANE:
      plane_html(fp, t.from, t.to, t.as.plane);

      break;
  }

  fprintf(fp, "</tr>");
}

void route_index_html(FILE *fp, const char *prev, const struct route *route, const char *next) {
  fprintf(
    fp,
    "<!DOCTYPE html>"
    "<html lang=\"en\">"
    HTML_HEAD(HTML_TITLE("%s - transportation - RaspBella"))
    "<body>"
    "<h1><a href=\"/\">home</a></h1>",
    route->iso
  );

  if (prev) {
    fprintf(
      fp,
      "<h1><a href=\"/%s\">prev</a></h1>",
      prev
    );
  }

  fprintf(
    fp,
    "<h1><u>%s</u></h1>",
    route->iso
  );

  if (next) {
    fprintf(
      fp,
      "<h1><a href=\"/%s\">next</a></h1>",
      next
    );
  }

  if (route->info) {
    fprintf(fp, "<h1>%s</h1>", route->info);
  }

  if (route->count) {
    fprintf(
      fp,
      "<table>"
      "<tr>"
      "<th>#</th>"
      "<th>From</th>"
      "<th>To</th>"
      "<th>Service</th>"
      "</tr>"
    );

    for (size_t i = 0; i < route->count; ++i) {
      trans_html(fp, i + 1, route->iso, route->items[i]);
    }
  }

  fprintf(
    fp,
    "</table>"
    "</body>"
    "</html>"
  );
}
