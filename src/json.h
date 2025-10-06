#pragma once

#include <stdio.h>
#include <stdbool.h>

typedef struct Json Json;

extern Json *root;

void fprintj(FILE *fp, Json *j, int indent);

Json *object_get(Json *o, char *k);
Json *object_set(Json *o, char *k, Json *v);

bool load(const char *file);
bool dump(const char *file, int indent);
