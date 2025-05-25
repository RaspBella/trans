#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "map.h"
#include "utils.h"

struct MapEntry {
  void *key;
  void *value;
};

struct Map {
  size_t capacity;
  size_t count;
  unsigned long (*hash)(void*);
  int (*key_cmp)(void*,void*);
  struct MapEntry **lookup;
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

  new->lookup = calloc(new->capacity, sizeof(void*));
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
    for (int i = 0; i < map->count; i++) {
      if (pre_free_key) {
        pre_free_key(map->entries[i].key);
      }

      if (pre_free_value) {
        pre_free_value(map->entries[i].value);
      }
    }
  }

  if (map->capacity > 0) {
    free(map->lookup);
    free(map->entries);
  }

  free(map);
}

void map_set(Map *map, void *key, void *value) {
  int hash = map->hash(key);
  int index = hash % map->capacity;

  if (!map->lookup[index] || map->key_cmp(map->lookup[index]->key, key) == 0) {
    if (!map->lookup[index]) map->count++;
      
    map->entries[map->count - 1].key = key;
    map->entries[map->count - 1].value = value;

    map->lookup[index] = map->entries + map->count - 1;

    return;
  }

  if (map->count < map->capacity) {
    do {
      index++;
      index %= map->capacity;
    } while (map->lookup[index] && map->key_cmp(map->lookup[index]->key, key));

    if (!map->lookup[index]) map->count++;

    map->entries[map->count - 1].key = key;
    map->entries[map->count - 1].value = value;

    map->lookup[index] = map->entries + map->count - 1;

    return;
  }

  else {
    map = map_extend(map);

    map_set(map, key, value);
  }
}

void *map_get(Map *map, void *key) {
  if (!map->count) return NULL;

  int hash = map->hash(key);
  int index = hash % map->capacity;

  if (map->key_cmp(map->lookup[index]->key, key) == 0) {
    return map->lookup[index]->value;
  }

  int start_index = index;

  do {
    index++;
    index %= map->capacity;
  } while (map->key_cmp(map->lookup[index]->key, key) && index != start_index);

  if (map->key_cmp(map->lookup[index]->key, key) == 0) {
    return map->lookup[index]->value;
  }

  else return NULL;
}

Map *map_extend(Map *map) {
  Map *new = new_map(
    map->capacity * MAP_MULT_FACTOR,
    map->hash,
    map->key_cmp
  );

  for (size_t i = 0; i < map->count; i++) {
    map_set(new, map->entries[i].key, map->entries[i].value);
}

  free_map(map, NULL, NULL);

  return new;
}

void default_print_key(void *key, FILE *fp) {
  fprintf(fp, "\"%s\": ", (char*) key);
}

void default_print_value(void *value, FILE *fp) {
  fprintf(fp, "%p", value);
}

void fprint_map(Map *map, void (*print_key)(void *key, FILE *fp), void (*print_value)(void *value, FILE *fp), FILE *fp) {
  if (!fp) fp = stdout;

  if (!print_key) print_key = default_print_key;
  if (!print_value) print_value = default_print_value;

  if (map->count > 0) {
    print_key(map->entries->key, fp);
    print_value(map->entries->value, fp);

    for (size_t i = 1; i < map->count; i++) {
      fprintf(fp, ", ");

      print_key(map->entries[i].key, fp);
      print_value(map->entries[i].value, fp);
    }
  }
}
