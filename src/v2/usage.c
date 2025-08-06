#include <stdlib.h>
#include <stdio.h>

#include "usage.h"

void usage(FILE* fp, char *program_name) {
  if (program_name) {
    fprintf(fp, "Usage: %s [OPTION]\n", program_name);
  }

  else {
    fprintf(fp, "Usage [OPTION]\n");
  }

  fprintf(
    fp,
    "  Options:\n"
    "    -c STRING -> exec STRING\n"
    "    -f FILE -> exec FILE\n"
    "    -h -> prints help\n"
    "  Code:\n"
    "    Functions:\n"
    "      exit(n) -> exits with integer status provided\n"
    "      exit() -> same as exit(0)\n"
    "      help() -> prints help\n"
    "      print(j) -> prints a journey provided\n"
    "      print() -> prints the data\n"
    "      add(key, j) -> adds a key and journey to the data table\n"
    "    Variable Assignment (of journey type only):\n"
    "      london = {EDB}->{KGX}:\"lumo my beloved\" -> assigns a value to a variable for convenience\n"
  );
}
