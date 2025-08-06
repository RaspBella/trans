#pragma once

#include "../map.h"
#include "../json.h"

struct da_pairs {
  struct MapEntry **items;
  size_t capacity;
  size_t count;
};

struct MapEntry *new_pair(void *key, void *value);
struct da_pairs *new_pairs(struct MapEntry *pair);
struct da_pairs *append_pair(struct da_pairs *pairs, struct MapEntry *pair);
Map *new_map_from_pairs(struct da_pairs *pairs);

struct JsonArray *new_array(Json *json);
struct JsonArray *append_item(struct JsonArray *array, Json *json);
