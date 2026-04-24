#include <stdio.h>
#include "index.h"
#include "../../route.h"
#include "../../crs.h"

static void root_route(FILE *fp, struct route route) {
  fprintf(
    fp,
    "          <tr>\n"
    "            <td><a href=\"" ISO_FMT "\">" ISO_FMT "</a></td>\n"
    "            <td>" STATION_FMT "</td>\n"
    "            <td>" STATION_FMT "</td>\n"
    "            <td>\n"
    "              <table>\n"
    "                <thead>\n"
    "                  <tr>\n"
    "                    <td>From</td>\n"
    "                    <td>To</td>\n"
    "                    <td>Link</td>\n"
    "                  </tr>\n"
    "                </thead>\n"
    "                <tbody>\n",
    ISO_ARG(route.on), ISO_ARG(route.on),
    STATION_ARG(route.services[0].from),
    STATION_ARG(route.services[route.count - 1].to)
  );

  for (int i = 0; i < route.count; ++i) {
    fprintf(
      fp,
      "                  <tr>\n"
      "                    <td>" STATION_FMT "</td>\n"
      "                    <td>" STATION_FMT "</td>\n"
      "                    <td>" LINK_FMT "</td>\n"
      "                  </tr>\n",
      STATION_ARG(route.services[i].from),
      STATION_ARG(route.services[i].to),
      LINK_ARG(route.services[i].id, route.on, route.services[i].info)
    );
  }

  fprintf(
    fp,
    "                </tbody>\n"
    "              </table>\n"
    "            </td>\n"
    "            <td>%s</td>\n"
    "          </tr>\n",
    route.info
  );
}

void root(FILE *fp, const char *title, int count, struct route *routes) {
  OPEN_INDEX(fp, title);

  fprintf(
    fp,
    "    <div>\n"
    "      <ul class=\"nav\">\n"
    "        <li id=\"today\"><a id=\"today_link\" href=\"today\">today?</a></li>\n"
    "        <li><a href=\"tww\">tww</a></li>\n"
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
    "            <th>Services</th>\n"
    "            <th>Info</th>\n"
    "          <tr>\n"
    "        </thead>\n"
    "        <tbody>\n"
  );

  for (int i = 0; i < count; ++i) {
    root_route(fp, routes[i]);
  }

  fprintf(
    fp,
    "        </tbody>\n"
    "      </table>\n"
    "    </div>\n"
  );

  CLOSE_BODY(fp);
    
  fprintf(fp, "  <script src=\"trans.js\"></script>\n");

  CLOSE_HTML(fp);
}
