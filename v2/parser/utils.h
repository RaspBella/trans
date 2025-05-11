#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "alexer.h"
#include "../utils.h"

struct Token {
  uint64_t id;
  const char *begin;
  const char *end;
  long int_value;
};

struct Tokens {
  struct Token *items;
  size_t count;
  size_t capacity;
};

bool get_tokens(Alexer *lexer, struct Tokens *tokens, const char *filename, char *str, uint64_t quote_id);

struct Token *current_token(struct Tokens *tokens, size_t index);
