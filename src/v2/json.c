#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "map.h"
#include "json.h"
#include "utils.h"

double *new_number(double number) {
  double *new = malloc(sizeof(double));

  *new = number;

  return new;
}

double *dup_number(double *number) {
  double *new = malloc(sizeof(double));

  *new = *number;

  return new;
}

Json *new_json(JsonType type, void *data) {
  Json *new = malloc(sizeof(Json));

  new->type = type;

  switch (type) {
    case JsonNull:
      break;

    case JsonBool:
      new->data.boolean = data;
      break;

    case JsonNumber:
      assert(data);
      new->data.number = data;
      break;

    case JsonString:
      new->data.string = data;
      break;

    case JsonArray:
      if (data) new->data.array = data;
      else new->data.array = calloc(1, sizeof(struct JsonArray));
      break;

    case JsonObject:
      if (data) new->data.object = data;
      else new->data.object = new_map(0, NULL, NULL);
      break;
  }

  return new;
}

void free_json(Json *json) {
  switch (json->type) {
    case JsonNull:
    case JsonBool:
    case JsonNumber:
      free(json->data.number);
      free(json);

      break;

    case JsonString:
      free(json->data.string);
      free(json);

      break;

    case JsonArray:
      for (size_t i = 0; i < json->data.array->count; i++) {
        free_json(json->data.array->items[i]);
      }

      if (json->data.array->capacity) {
        free(json->data.array->items);
        free(json->data.array);
      }

      free(json);

      break;

    case JsonObject:
      free_map(json->data.object, free, (void (*)(void*)) free_json);
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
      new = new_json(JsonBool, (void*) json->data.boolean);
      return new;

    case JsonNumber:
      new = new_json(JsonNumber, dup_number(json->data.number));
      return new;

    case JsonString:
      new = new_json(JsonString, strdup(json->data.string));
      return new;

    case JsonArray:
      new = new_json(JsonArray, NULL);

      for (size_t i = 0; i < json->data.array->count; i++) {
        da_append(new->data.array, json_dup(json->data.array->items[i]));
      }

      return new;

    case JsonObject:
      size_t count;
      struct MapEntry *array = get_keys_and_values(json->data.object, &count);

      new = new_json(JsonObject, new_map(count * MAP_MULT_FACTOR, NULL, NULL));

      for (size_t i = 0; i < count; i++) {
        map_set(new->data.object, strdup(array[i].key), json_dup(array[i].value));
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
        fprintf(fp, json->data.boolean ? "true" : "false");

        break;

      case JsonNumber:
        fprintf(fp, "%F", *json->data.number);

        break;

      case JsonString:
        fprintf(fp, "\"%s\"", json->data.string);

        break;

      case JsonArray:
        fprintf(fp, "[");

        if (json->data.array->count > 0) {
          fprint_json(json->data.array->items[0], fp);

          for (size_t i = 1; i < json->data.array->count; i++) {
            fprintf(fp, ", ");

            fprint_json(json->data.array->items[i], fp);
          }
        }

        fprintf(fp, "]");

        break;

      case JsonObject:
        fprintf(fp, "{");

        fprint_map(json->data.object, NULL, fprint_value, fp);

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
