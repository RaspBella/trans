#include <stdio.h>
#include "index.h"
#include "../../route.h"
#include "../../crs.h"

void yyyy_mm_dd(FILE *fp, char *title, struct route route) {
  OPEN_INDEX(fp, title);

  fprintf(
    fp,
    "    <div>\n"
    "      <h1><u>%s</u></h1>\n"
    "      <h2>%s</h2>\n"
    "      <table>\n"
    "        <thead>\n"
    "          <tr>\n"
    "            <th>From</th>\n"
    "            <th>To</th>\n"
    "            <th>Link</th>\n"
    "          <tr>\n"
    "        </thead>\n"
    "        <tbody>\n",
    route.iso,
    route.info
  );

  for (int i = 0; i < route.count; ++i) {
    fprintf(
      fp,
      "        <tr>\n"
      "          <td>" STATION_FMT "</td>\n"
      "          <td>" STATION_FMT "</td>\n"
      "          <td>" LINK_FMT "</td>\n"
      "        </tr>\n",
      STATION_ARG(route.services[i].from),
      STATION_ARG(route.services[i].to),
      LINK_ARG(route.services[i].id, route.iso, route.services[i].info)
    );
  }

  fprintf(
    fp,
    "        </tbody>\n"
    "      </table>\n"
    "    </div>\n"
  );

  CLOSE_BODY(fp);

  CLOSE_HTML(fp);
}
