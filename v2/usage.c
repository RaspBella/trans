#include "usage.h"

#include <stdlib.h>
#include <stdio.h>

void usage(FILE* fp, char *program_name) {
  fprintf(
    fp,
    "Usage: %s [OPTION]\n"
    "  Options:\n"
    "    -c STRING         exec STRING\n"
    "    -f FILE           exec FILE\n"
    "    -h                prints help\n"
    "  String:\n"
    "    Built ins:\n"
    "      exit [Integer]  exits with an optional exit code (default is %d)\n"
    "      help            prints help\n",
    program_name,
    EXIT_SUCCESS
  );
}
