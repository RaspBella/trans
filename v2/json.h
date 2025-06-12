#pragma once

#include <stdio.h>
#include <stdbool.h>
#include "map.h"

typedef enum {
  JsonNull,
  JsonBool,
  JsonNumber,
  JsonString,
  JsonArray,
  JsonObject,
} JsonType;

struct Json;

struct JsonArray {
  struct Json **items;
  size_t capacity;
  size_t count;
};

typedef struct Json {
  JsonType type;
  union {
    bool boolean;
    double *number;
    char *string;
    struct JsonArray *array;
    Map *object;
  } data;
} Json;

double *new_number(double);

Json *new_json(JsonType, void*);
void free_json(Json*);

Json *json_dup(Json*);

void fprint_json(Json*, FILE*);
void print_json(Json*);
