#pragma once

#include "service.h"
#include "utils.h"

struct date {
  int year;
  int month;
  int day;
};

struct route {
  const char *info;
  struct date on;
  int count;
  struct service *services;
};

#define route(INFO, ON, ...) (struct route){ \
  INFO, \
  ON, \
  .count = ARRAY_LEN(((struct service[]){__VA_ARGS__})), \
  .services = (struct service[]){__VA_ARGS__} \
}

#define date(YEAR, MONTH, DAY) (struct date){ \
  YEAR, \
  MONTH, \
  DAY \
}
