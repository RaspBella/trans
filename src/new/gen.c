#include <stdio.h>

#include "trans.h"
#include "data.c"

int main(void) {
  for (unsigned i = 0; i < ARRAY_LEN(data); i++) {
    printf("%s:\n", data[i].iso);

    for (unsigned j = 0; j < data[i].route_count; j++) {
      printf(
        "  Route #%u: (%s) %s->%s\n",
        j + 1,
        trans_t_string[data[i].routes[j].type],
        data[i].routes[j].from.name,
        data[i].routes[j].to.name
      );

      if (data[i].routes[j].info) {
        printf("    (info: \"%s\")\n", data[i].routes[j].info);
      }

      for (unsigned k = 0; k < data[i].routes[j].service_count; k++) {
        printf(
          "    Service #%u: (%s %s) %s->%s\n",
          k + 1,
          data[i].routes[j].services[k].op,
          trans_t_string[data[i].routes[j].services[k].type],
          data[i].routes[j].services[k].from.name,
          data[i].routes[j].services[k].to.name
        );

        if (data[i].routes[j].services[k].info) {
          printf("      (info: \"%s\")\n", data[i].routes[j].services[k].info);
        }

        if (data[i].routes[j].services[k].link) {
          printf("      (link: \"%s\")\n", data[i].routes[j].services[k].link);
        }
      }
    }
  }
}
