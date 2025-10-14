#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

enum JsonType{
  Json_Null,
  Json_String,
  Json_Array,
  Json_Object,
  JSON_TYPE_COUNT
};

const char *json_type_string(enum JsonType type);

typedef struct Json Json;

struct Iterable {
  enum JsonType type;
  Json *json;
  size_t i;
};

extern Json *root;

enum JsonType json_type(Json *j);

Json *new_json(enum JsonType type, char *init);
void free_json(Json *j);

void fprintj(FILE *fp, Json *j, int indent);

Json *object_get(Json *o, const char *k);
void object_set(Json *o, const char *k, Json *v, bool free_prev);
void object_sort(Json *o);

void array_append(Json *a, Json *v);

bool iterable(struct Iterable *it, Json *j);
Json *json_iterate(struct Iterable *it);
char *key_iterate(struct Iterable *it);

bool load(const char *file);
bool dump(const char *file, int indent);
