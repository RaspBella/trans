#pragma once

#include "service.h"
#include "utils.h"

struct route {
  const char *info;
  const char iso[11];
  int count;
  struct service *services;
};

#define route(INFO, ISO, ...) (struct route){ \
  INFO, \
  ISO, \
  .count = ARRAY_LEN(((struct service[]){__VA_ARGS__})), \
  .services = (struct service[]){__VA_ARGS__} \
},
