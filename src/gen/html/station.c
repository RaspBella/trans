#include <stdio.h>
#include <string.h>

#include "index.h"

void station(FILE *fp, const char *crs, int count, const char **filenames) {
  char title[] = "... - trans - RaspBella";

  memcpy(title, crs, 3);

  OPEN_INDEX(fp, title);

  fprintf(
    fp,
    "    <div>\n"
  );

  for (int i = 0; i < count; ++i) {
    fprintf(
      fp,
      "      <img src=\"%s\">\n",
      filenames[i]
    );
  }

  fprintf(
    fp,
    "    </div>\n"
  );

  CLOSE_BODY(fp);

  CLOSE_HTML(fp);
}
