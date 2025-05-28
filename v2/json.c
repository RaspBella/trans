#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "map.h"
#include "json.h"
#include "utils.h"

Json *new_json(JsonType type, void *data) {
  Json *new = malloc(sizeof(Json));

  new->type = type;

  switch (type) {
    case JsonNull:
      new->data = NULL;
      break;

    case JsonBool:
    case JsonNumber:
    case JsonString:
      new->data = data;
      break;

    case JsonArray:
      if (data) new->data = data;
      else new->data = calloc(1, sizeof(struct JsonArray));
      break;

    case JsonObject:
      if (data) new->data = data;
      else new->data = new_map(0, NULL, NULL);
      break;
  }

  return new;
}

static void free_json_value(void *json) {
  free_json(json);
}

void free_json(Json *json) {
  switch (json->type) {
    case JsonNull:
    case JsonBool:
    case JsonNumber:
      free(json);

      break;

    case JsonString:
      free(json->data);
      free(json);

      break;

    case JsonArray:
      for (int i = 0; i < ((struct JsonArray*) json->data)->count; i++) {
        free_json(((struct JsonArray*) json->data)->items[i]);
      }

      if (((struct JsonArray*) json->data)->capacity) free(((struct JsonArray*) json->data)->items);

      free(json->data);
      free(json);

      break;

    case JsonObject:
      free_map(json->data, free, free_json_value);
      free(json);

      break;
  }
}

Json *json_dup(Json *json) {
  Json *new = NULL;

  switch (json->type) {
    case JsonNull:
      new = new_json(JsonNull, NULL);
      return new;

    case JsonBool:
      new = new_json(JsonBool, json->data);
      return new;

    case JsonNumber:
      new = new_json(JsonNumber, json->data);
      return new;

    case JsonString:
      new = new_json(JsonString, strdup(json->data));
      return new;

    case JsonArray:
      new = new_json(JsonArray, NULL);

      for (size_t i = 0; i < ((struct JsonArray*) json->data)->count; i++) {
        da_append((struct JsonArray*) new->data, json_dup(((struct JsonArray*) json->data)->items[i]));
      }

      return new;

    case JsonObject:
      size_t count;
      struct MapEntry *array = get_keys_and_values(json->data, &count);

      new = new_json(JsonObject, new_map(count * MAP_MULT_FACTOR, NULL, NULL));

      for (size_t i = 0; i < count; i++) {
        map_set(new->data, strdup(array[i].key), json_dup(array[i].value));
      }

      return new;
  }

  return new;
}

void fprint_value(void *json, FILE *fp) {
  fprint_json(json, fp);
}

void fprint_json(Json *json, FILE *fp) {
  if (json) {
    switch (json->type) {
      case JsonNull:
        fprintf(fp, "null");

        break;

      case JsonBool:
        fprintf(fp, json->data ? "true" : "false");

        break;

      case JsonNumber:
        fprintf(fp, "%zu", (uintptr_t) json->data);

        break;

      case JsonString:
        fprintf(fp, "\"%s\"", (char*) json->data);

        break;

      case JsonArray:
        fprintf(fp, "[");

        if (((struct JsonArray*) json->data)->count > 0) {
          fprint_json(*((struct JsonArray*) json->data)->items, fp);

          for (int i = 1; i < ((struct JsonArray*) json->data)->count; i++) {
            fprintf(fp, ", ");

            fprint_json(((struct JsonArray*) json->data)->items[i], fp);
          }
        }

        fprintf(fp, "]");

        break;

      case JsonObject:
        fprintf(fp, "{");

        fprint_map(json->data, NULL, fprint_value, fp);

        fprintf(fp, "}");

        break;
    }
  }

  else {
    fprintf(fp, "{}");
  }
}

void print_json(Json *json) {
  fprint_json(json, stdout);
}
