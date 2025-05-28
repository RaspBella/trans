#pragma once

#include <stdio.h>
#include <stddef.h>

#include "utils.h"

#define MAP_DEFAULT_CAPACITY 256
#define MAP_MULT_FACTOR 2

struct MapEntry {
  void *key;
  void *value;
};

typedef struct Map Map;

Map *new_map(size_t init_capacity, unsigned long (*hash_func)(void*), int (*key_cmp)(void*,void*));
void free_map(Map*, void (*pre_free_key)(void*), void (*pre_free_value)(void*));

void map_set(Map*, void *key, void *value);
void *map_get(Map*, void *key);

Map *map_extend(Map*);

void fprint_map(Map*, void (*print_key)(void *key, FILE *fp), void (*print_value)(void *value, FILE *fp), FILE *fp);

struct MapEntry *get_keys_and_values(Map*, size_t*);
