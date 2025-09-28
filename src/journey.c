#include "journey.h"
#include "crs.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Journey {
  char from[4];
  char to[4];
  char *text;
  char *link;
  JourneyArray sub;
};

Journey *new_journey(char from[4], char to[4], char *text, char *link, JourneyArray sub) {
  Journey *new = calloc(1, sizeof(Journey));

  memcpy(new->from, from, 3);
  memcpy(new->to, to, 3);

  new->text = text;
  new->link = link;

  new->sub = sub;

  return new;
}

void free_journey(Journey *j) {
  free(j->text);

  if (j->link) free(j->link);

  if (j->sub.capacity) {
    for (size_t i = 0; i < j->sub.count; i++) {
      free_journey(j->sub.items[i]);
    }

    free(j->sub.items);
  }

  free(j);
}

void print_journey(Journey *j) {
  printf("%s(%3s)->%s(%3s) .text = \"%s\"",
    crs(j->from), j->from,
    crs(j->to), j->to,
    j->text
  );

  if (j->link) printf(" .link = \"%s\"", j->link);

  if (j->sub.count) {
    printf(" [ ");

    print_journey(*j->sub.items);

    for (size_t i = 1; i < j->sub.count; i++) {
      printf(", ");

      print_journey(j->sub.items[i]);
    }

    printf(" ]");
  }
}
