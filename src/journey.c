#include "journey.h"

#include <stdlib.h>
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
