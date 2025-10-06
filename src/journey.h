#pragma once

#include "json.h"

#include <stdlib.h>

typedef struct Journey Journey;
typedef struct {
  size_t count;
  size_t capacity;
  Journey **items;
} JourneyArray;

Journey *new_journey(char from[4], char to[4], char *text, char *link, JourneyArray sub);
void free_journey(Journey*);
void print_journey(Journey*);

Json *journey_to_json(Journey*);
