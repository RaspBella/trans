#pragma once

#include "../json.h"
#include "../map.h"

extern Map *vars;

void print_temp_json(Json*);
void print_var(char*);
void add_journey(Json*, char*, Json*);
void add_var(Json*, char*, char*);
void assign_journey(char*, Json*);
void assign_var(char*, char*);
Json *new_station(char*);
Json *new_journey(Json*, Json*, Json*, Json*);
