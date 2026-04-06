#pragma once

#include "service.h"

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

#define route(INFO, ON, COUNT, ...) (struct route){ \
  INFO, \
  ON, \
  COUNT, \
  .services = (struct service[]){ \
    __VA_ARGS__ \
  } \
}

#define date(YEAR, MONTH, DAY) (struct date){ \
  YEAR, \
  MONTH, \
  DAY \
}
