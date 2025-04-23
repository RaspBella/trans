#pragma once

typedef enum {
  JsonNull,
  JsonBool,
  JsonNumber,
  JsonString,
  JsonArray,
  JsonObject,
} JsonType;

typedef struct Json Json;

Json *new_json(JsonType, void*);
void free_json(Json*);

void print_json(Json*);
