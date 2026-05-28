#pragma once

#define STATION_FMT "%s (%3s)"
#define STATION_ARG(CODE) *crs[CODE[0]-'A'][CODE[1]-'A'][CODE[2]-'A'], CODE

#define LINK_FMT(BASE_FMT) "<a href=\"" BASE_FMT "\">%s</a>"

#define RTT_FMT LINK_FMT("https://realtimetrains.co.uk/service/gb-nr:%s/%s/detailed")
#define RTT_ARG(NR, ISO) NR.id, ISO, NR.op

#define BT_FMT LINK_FMT("https://bustimes.org/journeys/%d")
#define BT_ARG(BUS) BUS.id, BUS.n

#define OPEN_INDEX(FP, TITLE) fprintf(FP, "<!DOCTYPE html>\n" \
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
  "  <body>\n", \
  TITLE \
)

#define CLOSE_BODY(FP) fprintf(FP, "  </body>\n");

#define CLOSE_HTML(FP) fprintf(FP, "</html>");
