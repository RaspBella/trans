#pragma once

#include <stddef.h>

#include "utils.h"

#define MAP_DEFAULT_CAPACITY 256
#define MAP_MULT_FACTOR 2

typedef struct Map Map;

Map *new_map(size_t init_capacity, unsigned long (*hash_func)(void*), int (*key_cmp)(void*,void*));
void free_map(Map*, void (*pre_free_key)(void*), void (*pre_free_value)(void*));

void map_set(Map*, void *key, void *value);
void *map_get(Map*, void *key);

void map_extend(Map*);

void print_map(Map*, void (*print_key)(void*), void (*print_value)(void*));
