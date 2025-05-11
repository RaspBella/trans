#pragma once

#include <stdbool.h>
#include "../json.h"

bool parse_trans(Json *json, char *program_name, const char *filename, char *str);
