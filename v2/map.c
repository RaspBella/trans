#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "map.h"
#include "utils.h"

struct MapEntry {
  bool is_used;
  void *key;
  void *value;
};

struct Map {
  size_t capacity;
  size_t count;
  unsigned long (*hash)(void*);
  int (*key_cmp)(void*,void*);
  struct MapEntry *entries;
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

  new->entries = calloc(new->capacity, sizeof(struct MapEntry));

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
  if (map->count > 0) {
    for (int i = 0; i < map->capacity; i++) {
      if (map->entries[i].is_used) {
        if (pre_free_key) {
          pre_free_key(map->entries[i].key);
        }

        if (pre_free_value) {
          pre_free_value(map->entries[i].value);
        }
      }
    }
  }

  free(map->entries);
  free(map);
}

void map_set(Map *map, void *key, void *value) {
  int hash = map->hash(key);
  int index = hash % map->capacity;

  if (!map->entries[index].is_used || map->key_cmp(map->entries[index].key, key) == 0) {
    if (!map->entries[index].is_used) map->count++;

    map->entries[index].key = key;
    map->entries[index].value = value;
    map->entries[index].is_used = true;

    return;
  }

  if (map->count < map->capacity) {
    do {
      index++;
      index %= map->capacity;
    } while (map->entries[index].is_used && map->key_cmp(map->entries[index].key, key));

    if (!map->entries[index].is_used) map->count++;

    map->entries[index].key = key;
    map->entries[index].value = value;
    map->entries[index].is_used = true;

    return;
  }

  else {
    map = map_extend(map);

    map_set(map, key, value);
  }
}

void *map_get(Map *map, void *key) {
  int hash = map->hash(key);
  int index = hash % map->capacity;

  if (map->key_cmp(map->entries[index].key, key) == 0) {
    return map->entries[index].value;
  }

  int start_index = index;
  index++;

  do {
    index++;
    index %= map->capacity;

    printf("%d\n", index);
  } while (map->key_cmp(map->entries[index].key, key) && index != start_index);

  if (map->key_cmp(map->entries[index].key, key) == 0) {
    return map->entries[index].value;
  }

  else return NULL;
}

Map *map_extend(Map *map) {
  Map *new = new_map(
    map->capacity * MAP_MULT_FACTOR,
    map->hash,
    map->key_cmp
  );

  for (size_t i = 0; i < map->capacity; i++) {
    if (map->entries[i].is_used) {
      map_set(new, map->entries[i].key, map->entries[i].value);
    }
  }

  free_map(map, NULL, NULL);

  return new;
}

void print_map(Map *map) {
  for (int i = 0; i < map->capacity; i++) {
    if (map->entries[i].is_used) {
      printf("[%p]=%p\n", map->entries[i].key, map->entries[i].value);
    }
  }
}

static int iter_value = 0;

void reset_iter_map(void) {
  iter_value = 0;
}

bool iter_map(Map *map, struct Pair *pair) {
  if (map->count == 0) return false;

  while (iter_value < map->capacity) {
    if (map->entries[iter_value].is_used) {
      pair->first = map->entries[iter_value].key;
      pair->second = map->entries[iter_value].value;

      iter_value++;

      return true;
    }

    else {
      iter_value++;
    }
  }

  return false;
}
