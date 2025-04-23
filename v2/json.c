#include <stdlib.h>
#include <stdio.h>
#include "map.h"
#include "json.h"

struct Json {
  JsonType type;
  void *data;
};

struct JsonArray {
  Json **items;
  size_t capacity;
  size_t count;
};

Json *new_json(JsonType type, void *data) {
  Json *new = malloc(sizeof(Json));

  new->type = type;
  new->data = data;

  return new;
}

void free_json_callback(void *json) {
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
        free_json(
          (
            (
               (struct JsonArray*) json->data
            )->items
          )[i]
        );
      }

      free(json->data);
      free(json);

      break;

    case JsonObject:
      free_map(json->data, free_json_callback, free_json_callback);
      free(json);

      break;
  }
}

void print_json_recursive(Json *json, int depth) {
  printf("{");

  if (json) {
    switch (json->type) {
      case JsonNull:
        if (depth) printf("null");

        break;

      case JsonBool:
        printf(json->data ? "true" : "false");

        break;

      case JsonNumber:
        union { float floaty; void *pointy; } onion;

        onion.pointy = json->data;

        printf("%f", onion.floaty);

        break;

      case JsonString:
        printf("\"%s\"", (char*) json->data);

        break;

      case JsonArray:
        break;

      case JsonObject:
        break;
    }
  }

  printf("}");
}

void print_json(Json *json) {
  print_json_recursive(json, 0);
}
