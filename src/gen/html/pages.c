#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>
#include <errno.h>
#include "root.h"
#include "yyyy_mm_dd.h"
#include "index.h"
#include "../../route.h"
#include "../../crs.h"
#include "../../op.h"
#include "../../utils.h"

#define OUTDIR "../docs"
#define INDEX "/index.html"

int main(void) {
  struct route routes[] = {
#include "../../trans.def"
  };

  int count = ARRAY_LEN(routes);

  FILE *fp = fopen(OUTDIR INDEX, "w");

  assert(fp);

  root(fp, "transportation - RaspBella", count, routes);

  char filename[] = OUTDIR "/yyyy-mm-dd" INDEX;

  for (int i = 0; i < count; ++i) {
    int ret = snprintf(
      filename + sizeof(OUTDIR),
      11,
      "%s",
      routes[i].iso
    );

    assert(ret == 10);

    if (mkdir(filename, 0755) != 0) {
      assert(errno == EEXIST);
    }

    filename[sizeof(OUTDIR) + 10] = '/';

    fp = freopen(filename, "w", fp);

    assert(fp);

    filename[sizeof(OUTDIR) + 10] = 0;

    char title[] = "yyyy-mm-dd - transportation - RaspBella";

    ret = snprintf(
      title,
      sizeof(title),
      "%s - transportation - RaspBella",
      routes[i].iso
    );

    assert(ret == sizeof(title) - 1);

    yyyy_mm_dd(fp, title, routes[i], i > 0 ? routes[i - 1].iso : NULL, i < count - 1 ? routes[i + 1].iso : NULL);
  }

  fp = freopen(OUTDIR "/data.json", "w", fp);

  assert(fp);

  fprintf(fp, "{");

  for (int i = 0; i < count; ++i) {
    fprintf(
      fp,
      "\"%s\":{"
      "\"info\":\"%s\","
      "\"services\":[",
      routes[i].iso,
      routes[i].info
    );

    for (int j = 0; j < routes[i].count; ++j) {
      switch (routes[i].services[j].type) {
        case SERVICE_NR:
          fprintf(
            fp,
            "{\"nr\":{"
            "\"id\":\"%s\","
            "\"op\":\"%s\","
            "\"from\":\"%s\","
            "\"to\":\"%s\"}}",
            routes[i].services[j].as.nr.id,
            routes[i].services[j].as.nr.op,
            routes[i].services[j].as.nr.from,
            routes[i].services[j].as.nr.to
          );
    
          break;

        case SERVICE_BUS:
          fprintf(
            fp,
            "{\"bus\":{"
            "\"id\":\"%d\","
            "\"number\":\"%s\","
            "\"op\":\"%s\","
            "\"from\":\"%s\","
            "\"to\":\"%s\"}}",
            routes[i].services[j].as.bus.id,
            routes[i].services[j].as.bus.n,
            routes[i].services[j].as.bus.op,
            routes[i].services[j].as.bus.from,
            routes[i].services[j].as.bus.to
          );

          break;
      }

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
