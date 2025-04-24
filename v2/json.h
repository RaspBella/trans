#pragma once

#include <stdio.h>

typedef enum {
  JsonNull,
  JsonBool,
  JsonNumber,
  JsonString,
  JsonArray,
  JsonObject,
} JsonType;

typedef struct Json {
  JsonType type;
  void *data;
} Json;

struct JsonArray {
  Json **items;
  size_t capacity;
  size_t count;
};

Json *new_json(JsonType, void*);
void free_json(Json*);

void fprint_json(Json*, FILE*);
void print_json(Json*);
