#pragma once

#define ISO_FMT "%04d-%02d-%02d"
#define ISO_ARG(DATE) DATE.year, DATE.month, DATE.day

#define STATION_FMT "%s (%3s)"
#define STATION_ARG(CODE) *crs[CODE[0]-'A'][CODE[1]-'A'][CODE[2]-'A'], CODE

#define LINK_FMT "<a href=\"/trans/?code=%s&date=" ISO_FMT "\">%s</a>"
#define LINK_ARG(ID, DATE, INFO) ID, ISO_ARG(DATE), INFO

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
  "  <body>\n" \
  "    <ul class=\"nav\">\n" \
  "      <li><a href=\"/\">home</a></li>\n" \
  "      <li><a href=\"/RaspBella\">about</a></li>\n" \
  "      <li><a href=\"/cubing\">cubing</a></li>\n" \
  "      <li><a href=\"/linux\">linux</a></li>\n" \
  "      <li><a href=\"/media\">media</a></li>\n" \
  "      <li><a class=\"active\" href=\"/trans\">trans</a></li>\n" \
  "      <li><a href=\"/blog\">blog</a></li>\n" \
  "      <li><a href=\"/calendar\">calendar</a></li>\n" \
  "    </ul>\n", \
  TITLE \
)

#define CLOSE_BODY(FP) fprintf(FP, "  </body>\n");

#define CLOSE_HTML(FP) fprintf(FP, "</html>");
