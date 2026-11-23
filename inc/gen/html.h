#ifndef GEN_HTML_H
#define GEN_HTML_H

#include <stdio.h>
#include <trans/trans.h>

#define HTML_TITLE(TITLE) "<title>"TITLE"</title>"
#define HTML_HEAD(HTML_TITLE) "<head>" \
    HTML_TITLE \
    "<link rel=\"stylesheet\" href=\"/main.css\">" \
    "<meta charset=\"UTF-8\">" \
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">" \
    "<link rel=\"apple-touch-icon\" sizes=\"180x180\" href=\"/favicon/apple-touch-icon.png\">" \
    "<link rel=\"icon\" type=\"image/png\" sizes=\"32x32\" href=\"/favicon/favicon-32x32.png\">" \
    "<link rel=\"icon\" type=\"image/png\" sizes=\"16x16\" href=\"/favicon/favicon-16x16.png\">" \
    "<link rel=\"manifest\" href=\"/favicon/site.webmanifest\">" \
    "</head>"

void index_html(FILE *fp, size_t count, const struct route *routes[]);
void route_index_html(FILE *fp, const char *prev, const struct route *route, const char *next);

#endif /* GEN_HTML_H */
