#pragma once

#include <stdio.h>
#include <stdbool.h>

enum JsonType{
  Json_Null,
  Json_String,
  Json_Array,
  Json_Object,
};

typedef struct Json Json;

extern Json *root;

Json *new_json(enum JsonType type, char *init);

void fprintj(FILE *fp, Json *j, int indent);

Json *object_get(Json *o, const char *k);
void object_set(Json *o, const char *k, Json *v);
void object_sort(Json *o);

void array_append(Json *a, Json *v);

bool load(const char *file);
bool dump(const char *file, int indent);
