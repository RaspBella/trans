#include "helper.h"
#include "../map.h"
#include "../json.h"
#include "../utils.h"

struct MapEntry *new_pair(void *key, void *value) {
  struct MapEntry *pair = malloc(sizeof(struct MapEntry));

  pair->key = key;
  pair->value = value;

  return pair;
}

struct da_pairs *new_pairs(struct MapEntry *pair) {
  struct da_pairs *pairs = calloc(1, sizeof(struct da_pairs));

  da_append(pairs, pair);

  return pairs;
}

struct da_pairs *append_pair(struct da_pairs *pairs, struct MapEntry *pair) {
  da_append(pairs, pair);

  return pairs;
}

Map *new_map_from_pairs(struct da_pairs *pairs) {
  Map *map = new_map(pairs->count, NULL, NULL);

  if (pairs->count) {
    for (size_t i = 0; i < pairs->count; i++) {
      map_set(map, pairs->items[i]->key, pairs->items[i]->value);
      free(pairs->items[i]);
    }

    free(pairs->items);
    free(pairs);
  }

  return map;
}

struct JsonArray *new_array(Json *json) {
  struct JsonArray *array = calloc(1, sizeof(struct JsonArray));

  da_append(array, json);

  return array;
}

struct JsonArray *append_item(struct JsonArray *array, Json *json) {
  da_append(array, json);

  return array;
}
