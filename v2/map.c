#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "map.h"
#include "utils.h"

struct Map {
  size_t capacity;
  size_t count;
  unsigned long (*hash)(void*);
  int (*key_cmp)(void*,void*);
  void **keys;
  void **values;
};

unsigned long map_default_hash(void *key) {
  int hash = 5381;
  char *str = key;
  int c;

  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + c;
  }

  return hash;
}

int map_default_key_cmp(void *a, void *b) {
  return strcmp(a, b);
}

Map *new_map(size_t init_capacity, unsigned long (*hash_func)(void*), int (*key_cmp)(void*,void*)) {
  Map *new = calloc(1, sizeof(Map));

  if (init_capacity) {
    new->capacity = init_capacity;
  }

  else {
    new->capacity = MAP_DEFAULT_CAPACITY;
  }

  new->keys = calloc(new->capacity, sizeof(void*));
  new->values = calloc(new->capacity, sizeof(void*));

  if (hash_func) {
    new->hash = hash_func;
  }

  else {
    new->hash = map_default_hash;
  }

  if (key_cmp) {
    new->key_cmp = key_cmp;
  }

  else {
    new->key_cmp = map_default_key_cmp;
  }

  return new;
}

void free_map(Map *map, void (*pre_free_key)(void*), void (*pre_free_value)(void*)) {
  for (int i = 0; i < map->capacity; i++) {
    if (map->keys[i]) {
      if (pre_free_key) {
        pre_free_key(map->keys[i]);
      }
    }

    if (map->values[i]) {
      if (pre_free_value) {
        pre_free_value(map->values[i]);
      }
    }
  }

  free(map->keys);
  free(map->values);
  free(map);
}

void map_set(Map *map, void *key, void *value) {
  int hash = map->hash(key);
  int index = hash % map->capacity;

  if (map->keys[index] == key || map->keys[index] == NULL) {
    if (map->keys[index] == NULL) map->count++;

    map->keys[index] = key;
    map->values[index] = value;

    return;
  }

  if (map->count < map->capacity) {
    do {
      index++;
      index %= map->capacity;
    } while (map->keys[index] != key && map->keys[index] != NULL);

    if (map->keys[index] == NULL) map->count++;

    map->keys[index] = key;
    map->values[index] = value;

    return;
  }

  else {
    map_extend(map);

    map_set(map, key, value);
  }
}

void *map_get(Map *map, void *key) {
  int hash = map->hash(key);
  int index = hash % map->capacity;

  if (map->keys[index] == key) {
    return map->values[index];
  }

  int start_index = index;
  index++;

  do {
    index++;
    index %= map->capacity;

    printf("%d\n", index);
  } while (map->keys[index] != key && index != start_index);

  if (map->keys[index] == key) {
    return map->values[index];
  }

  else return NULL;
}

void map_extend(Map *map) {
  map->keys = realloc(map->keys, map->capacity * MAP_MULT_FACTOR);
  map->values = realloc(map->values, map->capacity * MAP_MULT_FACTOR);
}

void print_map(Map *map) {
  for (int i = 0; i < map->capacity; i++) {
    if (map->keys[i]) {
      printf("[%p]=%p\n", map->keys[i], map->values[i]);
    }
  }
}

bool iter_map(Map *map, struct Pair *pair) {
  static int i = 0;

  if (map->count) {
    while (i < map->capacity) {
      if (map->keys[i] != NULL) {
        pair->first = map->keys[i];
        pair->second = map->values[i];

        i++;

        return true;
      }
      
      i++;
    }

    i = 0;
  }

  return false;
}
