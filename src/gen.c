#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>
#include <errno.h>
#include "route.h"

#define ME "RaspBella"

#define OUTPUT_DIR "../docs"
#define INDEX "/index.html"

#define INDEX_FMT "<!DOCTYPE html>\n" \
"<html lang=\"en\">\n" \
"  <head>\n" \
"    <title>%s</title>\n" \
"    <link rel=\"stylesheet\" href=\"/main.css\">\n" \
"    <meta charset=\"UTF-8\">\n" \
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n" \
"    <link rel=\"apple-touch-icon\" sizes=\"180x180\" href=\"/favicon/apple-touch-icon.png\">\n" \
"    <link rel=\"icon\" type=\"image/png\" sizes=\"32x32\" href=\"/favicon/favicon-32x32.png\">\n" \
"    <link rel=\"icon\" type=\"image/png\" sizes=\"16x16\" href=\"/favicon/favicon-16x16.png\">\n" \
"    <link rel=\"manifest\" href=\"/favicon/site.webmanifest\">\n" \
"  </head>\n" \
"  <body>\n" \
"    <ul class=\"nav\">\n" \
"      <li><a href=\"/\">home</a></li>\n" \
"      <li><a href=\"/" ME "\">about</a></li>\n" \
"      <li><a href=\"/cubing\">cubing</a></li>\n" \
"      <li><a href=\"/linux\">linux</a></li>\n" \
"      <li><a href=\"/media\">media</a></li>\n" \
"      <li><a class=\"active\" href=\"/trans\">trans</a></li>\n" \
"      <li><a href=\"/blog\">blog</a></li>\n" \
"      <li><a href=\"/calendar\">calendar</a></li>\n" \
"    </ul>\n" \
"%s\n" \
"  </body>\n" \
"%s" \
"</html>"

#define ROOT_FMT \
  "    <div>\n" \
  "      <ul class=\"nav\">\n" \
  "        <li id=\"today\"><a id=\"today_link\" href=\"today\">today?</a></li>\n" \
  "        <li><a href=\"tww\">tww</a></li>\n" \
  "        <li>\n" \
  "          <input id=\"query\" type=\"text\" placeholder=\"query...\">\n" \
  "          <button id=\"submit_query\">Submit query</button>\n" \
  "        </li>\n" \
  "      </ul>\n" \
  "      <table>\n" \
  "        <thead>\n" \
  "          <tr>\n" \
  "            <th>Date</th>\n" \
  "            <th>From</th>\n" \
  "            <th>To</th>\n" \
  "            <th>Services</th>\n" \
  "            <th>Info</th>\n" \
  "          <tr>\n" \
  "        </thead>\n" \
  "        <tbody>\n" \
  "%s\n" \
  "        </tbody>\n" \
  "      </table>\n" \
  "    </div>\n"

#define ROOT_TR_FMT \
  "          <tr>\n" \
  "            <td><a href=\"" ISO_FMT "\">" ISO_FMT "</a></td>\n" \
  "            <td>%s(%s)</td>\n" \
  "            <td>%s(%s)</td>\n" \
  "            <td>\n" \
  "              <table>\n" \
  "                <thead>\n" \
  "                  <tr>\n" \
  "                    <td>From</td>\n" \
  "                    <td>To</td>\n" \
  "                    <td>RTT</td>\n" \
  "                  </tr>\n" \
  "                </thead>\n" \
  "                <tbody>\n" \
  "%s\n" \
  "                </tbody>\n" \
  "              </table>\n" \
  "            </td>\n" \
  "            <td>%s</td>\n" \
  "          </tr>\n"

#define ROOT_SERVICES_TR_FMT \
  "                  <tr>\n" \
  "                    <td>%s(%s)</td>\n" \
  "                    <td>%s(%s)</td>\n" \
  "                    <td><a href=\"https://realtimetrains.co.uk/service/gb-nr:%s/" ISO_FMT "/detailed\">%s</a></td>\n" \
  "                  </tr>\n"

#define PAGE_FMT \
  "    <div>\n" \
  "      <h1>" ISO_FMT "</h1>\n" \
  "      <h2>%s</h2>\n" \
  "      <table>\n" \
  "        <thead>\n" \
  "          <tr>\n" \
  "            <th>From</th>\n" \
  "            <th>To</th>\n" \
  "            <th>RTT</th>\n" \
  "          <tr>\n" \
  "        </thead>\n" \
  "        <tbody>\n" \
  "%s\n" \
  "        </tbody>\n" \
  "      </table>\n" \
  "    </div>\n"

#define PAGE_TR_FMT \
  "        <tr>\n" \
  "          <td>%s(%s)</td>\n" \
  "          <td>%s(%s)</td>\n" \
  "          <td><a href=\"https://realtimetrains.co.uk/service/gb-nr:%s/" ISO_FMT "/detailed\">%s</a></td>\n" \
  "        </tr>\n"

#define ISO_FMT "%04d-%02d-%02d"
#define ISO_ARG(DATE) DATE.year, DATE.month, DATE.day

#define ARRAY_LEN(xs) sizeof(xs)/sizeof((xs)[0])

char *root(char *tbody) {
  int len = snprintf(
    NULL,
    0,
    ROOT_FMT,
    tbody
  );

  assert(!(len < 0));

  char *string = calloc(len + 1, sizeof(char));

  assert(string != NULL);

  int ret = snprintf(
    string,
    len,
    ROOT_FMT,
    tbody
  );

  assert(ret == len);

  return string;
}

char *root_services(struct route route) {
  int len = 0;
  int written = 0;

  for (int i = 0; i < route.count; ++i) {
    int from = route.services[i].from;
    int to = route.services[i].to;

    len += snprintf(
      NULL,
      0,
      ROOT_SERVICES_TR_FMT,
      crs[from].name, crs[from].code,
      crs[to].name, crs[to].code,
      route.services[i].id,
      ISO_ARG(route.on),
      route.services[i].info
    );
  }

  char *string = calloc(len + 1, sizeof(char));

  for (int i = 0; i < route.count; ++i) {
    int from = route.services[i].from;
    int to = route.services[i].to;

    written += snprintf(
      string + written,
      len - written,
      ROOT_SERVICES_TR_FMT,
      crs[from].name, crs[from].code,
      crs[to].name, crs[to].code,
      route.services[i].id,
      ISO_ARG(route.on),
      route.services[i].info
    );
  }

  return string;
}

char *root_tbody(int count, struct route *routes) {
  int len = 0;
  int written = 0;

  char **pointers = calloc(count, sizeof(char*));

  for (int i = 0; i < count; ++i) {
    pointers[i] = root_services(routes[i]);

    int from = routes[i].services[0].from;
    int to = routes[i].services[routes[i].count - 1].to;

    len += snprintf(
      NULL,
      0,
      ROOT_TR_FMT,
      ISO_ARG(routes[i].on),
      ISO_ARG(routes[i].on),
      crs[from].name, crs[from].code,
      crs[to].name, crs[to].code,
      pointers[i],
      routes[i].info
    );
  }

  char *string = calloc(len + 1, sizeof(char));

  for (int i = 0; i < count; ++i) {
    int from = routes[i].services[0].from;
    int to = routes[i].services[routes[i].count - 1].to;

    written += snprintf(
      string + written,
      len - written,
      ROOT_TR_FMT,
      ISO_ARG(routes[i].on),
      ISO_ARG(routes[i].on),
      crs[from].name, crs[from].code,
      crs[to].name, crs[to].code,
      pointers[i],
      routes[i].info
    );

    free(pointers[i]);
  }

  free(pointers);

  return string;
}

char *page(struct route route, char *tbody) {
  int len = snprintf(
    NULL,
    0,
    PAGE_FMT,
    ISO_ARG(route.on),
    route.info,
    tbody
  );

  assert(!(len < 0));

  char *string = calloc(len + 1, sizeof(char));

  assert(string != NULL);

  int ret = snprintf(
    string,
    len,
    PAGE_FMT,
    ISO_ARG(route.on),
    route.info,
    tbody
  );

  assert(ret == len);

  return string;
}

char *page_tbody(struct route route) {
  int len = 0;
  int written = 0;

  for (int i = 0; i < route.count; ++i) {
    int from = route.services[i].from;
    int to = route.services[i].to;

    len += snprintf(
      NULL,
      0,
      PAGE_TR_FMT,
      crs[from].name, crs[from].code,
      crs[to].name, crs[to].code,
      route.services[i].id,
      ISO_ARG(route.on),
      route.services[i].info
    );
  }

  char *string = calloc(len + 1, sizeof(char));

  for (int i = 0; i < route.count; ++i) {
    int from = route.services[i].from;
    int to = route.services[i].to;

    written += snprintf(
      string + written,
      len - written,
      PAGE_TR_FMT,
      crs[from].name, crs[from].code,
      crs[to].name, crs[to].code,
      route.services[i].id,
      ISO_ARG(route.on),
      route.services[i].info
    );
  }

  return string;
}

int main(void) {
  struct route routes[] = {
#include "trans.c"
  };

  FILE *fp = fopen(OUTPUT_DIR INDEX, "w");

  assert(fp != NULL);

  int count = ARRAY_LEN(routes);

  char *data = root_tbody(count, routes);

  char *body = root(data);

  free(data);

  fprintf(
    fp,
    INDEX_FMT,
    "transportation - " ME,
    body,
    "  <script src=\"trans.js\"></script>\n"
  );

  free(body);

  char filename[] = OUTPUT_DIR "/yyyy-mm-dd" INDEX;

  for (int i = 0; i < count; ++i) {
    int ret = snprintf(
      filename + sizeof(OUTPUT_DIR),
      11,
      ISO_FMT,
      ISO_ARG(routes[i].on)
    );

    assert(ret == 10);

    if (mkdir(filename, 0755) != 0) {
      assert(errno == EEXIST);
    }

    filename[sizeof(OUTPUT_DIR) + 10] = '/';

    fp = freopen(filename, "w", fp);

    filename[sizeof(OUTPUT_DIR) + 10] = 0;

    char title[] = "yyyy-mm-dd - transportation - " ME;

    ret = snprintf(
      title,
      sizeof(title),
      ISO_FMT " - transportation - " ME,
      ISO_ARG(routes[i].on)
    );

    data = page_tbody(routes[i]);

    body = page(routes[i], data);

    free(data);

    fprintf(
      fp,
      INDEX_FMT,
      title,
      body,
      ""
    );

    free(body);
  }

  fp = freopen(OUTPUT_DIR "/data.json", "w", fp);

  assert(fp != NULL);

  fprintf(fp, "{");

  for (int i = 0; i < count; ++i) {
    fprintf(
      fp,
      "\"" ISO_FMT "\":{"
      "\"info\":\"%s\","
      "\"services\":[",
      ISO_ARG(routes[i].on),
      routes[i].info
    );

    for (int j = 0; j < routes[i].count; ++j) {
      fprintf(
        fp,
        "{\"info\":\"%s\","
        "\"id\":\"%s\","
        "\"from\":\"%s\","
        "\"to\":\"%s\"}",
        routes[i].services[j].info,
        routes[i].services[j].id,
        crs[routes[i].services[j].from].code,
        crs[routes[i].services[j].to].code
      );

      if (j < (routes[i].count - 1)) {
        fprintf(fp, ",");
      }
    }

    fprintf(
      fp,
      "]}"
    );

    if (i < (count - 1)) {
      fprintf(fp, ",");
    }
  }

  fprintf(fp, "}");

  fclose(fp);
}
