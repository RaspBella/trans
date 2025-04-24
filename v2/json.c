#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "map.h"
#include "json.h"
#include "utils.h"

Json *new_json(JsonType type, void *data) {
  Json *new = malloc(sizeof(Json));

  new->type = type;
  new->data = data;

  return new;
}

void free_json_key(void *str) {
  free(str);
}

void free_json_value(void *json) {
  free_json(json);
}

void free_json(Json *json) {
  switch (json->type) {
    case JsonNull:
      free(json);

      break;

    case JsonBool:
      free(json);

      break;

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

      free(((struct JsonArray*) json->data)->items);

      free(json->data);
      free(json);

      break;

    case JsonObject:
      free_map(json->data, free_json_key, free_json_value);
      free(json);

      break;
  }
}

void fprint_json_recursive(Json *json, FILE *fp, int depth) {
  if (json) {
    switch (json->type) {
      case JsonNull:
        if (depth) fprintf(fp, "null");

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

        struct Pair pair = { .first = NULL, .second = NULL };

        if (iter_map(json->data, &pair)) {
          fprintf(fp, "\"%s\": ", (char*) pair.first);

          fprint_json(pair.second, fp);

          while (iter_map(json->data, &pair)) {
            fprintf(fp, ", \"%s\": ", (char*) pair.first);

            fprint_json(pair.second, fp);
          }
        }

        fprintf(fp, "}");

        break;
    }
  }

  else fprintf(fp, "{}");
}

void fprint_json(Json *json, FILE *fp) {
  fprint_json_recursive(json, fp, 0);
}

void print_json(Json *json) {
  fprint_json(json, stdout);
}
