#include <assert.h>
#include <string.h>
#include "trans_extra.h"
#include "../map.h"
#include "../json.h"
#include "../utils.h"
#include "../crs.h"

void print_var(char *id) {
  assert(vars->type == JsonObject);

  Json *var = map_get(vars->data.object, id);

  if (var) {
    print_json(var);
  }

  else {
    fprintf(stderr, "Undefined var: %s\n", id);
  }
}

void add_journey(Json *data, char *key, Json *journey) {
  assert(data->type == JsonObject);

  Json *json = map_get(data->data.object, key);

  if (json) {
    assert(json->type == JsonArray || json->type == JsonObject);

    if (json->type == JsonArray) {
      da_append(json->data.array, journey);
    }

    else if (json->type == JsonObject) {
      Json *array = new_json(JsonArray, NULL);

      da_append(array->data.array, json);
      da_append(array->data.array, journey);

      map_set(data->data.object, key, array);
    }
  }

  else {
    map_set(data->data.object, key, journey);
  }
}

void add_var(Json *data, char *key, char *id) {
  assert(vars->type == JsonObject);
  assert(data->type == JsonObject);

  Json *var = map_get(vars->data.object, id);

  if (var) {
    Json *json = map_get(data->data.object, key);

    if (json) {
      assert(json->type == JsonArray || json->type == JsonObject);

      if (json->type == JsonArray) {
        da_append(json->data.array, json_dup(var));
      }

      else if (json->type == JsonObject) {
        Json *array = new_json(JsonArray, NULL);

        da_append(array->data.array, json);
        da_append(array->data.array, json_dup(var));

        map_set(data->data.object, key, array);
      }
    }

    else {
      map_set(data->data.object, key, var);
    }
  }

  else {
    fprintf(stderr, "Undefined var: %s\n", id);
  }
}

void assign_journey(char *id, Json *journey) {
  assert(vars->type == JsonObject);

  Json *var = map_get(vars->data.object, id);

  if (var) {
    free_json(var);
  }

  map_set(vars->data.object, id, journey);
}

void assign_var(char *new_id, char *old_id) {
  if (strcmp(new_id, old_id) == 0) return; // if x = x do nothing

  Json *new_var = map_get(vars->data.object, new_id);

  if (new_var) {
    free_json(new_var);
  }

  Json *old_var = map_get(vars->data.object, old_id);

  if (old_var) {
    map_set(vars->data.object, new_id, json_dup(old_var));
  }

  else {
    fprintf(stderr, "Undefined var: %s\n", old_id);
  }
}

Json *new_station(char *code) {
  char *name = crs(code);

  if (name) {
    Json *new = new_json(JsonObject, NULL);

    map_set(new->data.object, code, new_json(JsonString, strdup(name)));

    return new;
  }

  else {
    fprintf(stderr, "Unknown station code: %3s\n", code);

    return NULL;
  }
}

Json *new_journey(Json *from, Json *to, Json *info, Json *sub) {
  assert(from);
  assert(to);

  Json *new = new_json(JsonObject, NULL);

  map_set(new->data.object, strdup("from"), from);
  map_set(new->data.object, strdup("to"), to);

  if (info) map_set(new->data.object, strdup("info"), info);
  if (sub) map_set(new->data.object, strdup("sub"), sub);

  return new;
}
