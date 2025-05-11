#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "alexer.h"
#include "utils.h"
#include "trans.h"
#include "../trans.h"
#include "../json.h"
#include "../builtins.h"



typedef enum {
  PUNCT_RIGHT_ARROW,
  PUNCT_ADDON,
  PUNCT_LEFT_BRACKET,
  PUNCT_RIGHT_BRACKET,
  PUNCT_COMMA,
  PUNCT_QUOTE,
  COUNT_PUNCTS
} Punct_Index;

static_assert(COUNT_PUNCTS == 6, "Amount of puncts has changed");
static const char *puncts[COUNT_PUNCTS] = {
  [PUNCT_RIGHT_ARROW] = "->",
  [PUNCT_ADDON] =  "+=",
  [PUNCT_LEFT_BRACKET] = "[",
  [PUNCT_RIGHT_BRACKET] = "]",
  [PUNCT_COMMA] = ",",
  [PUNCT_QUOTE] = "\""
};



bool parse_trans(Json *json, char *program_name, const char *filename, char *str) {
  Alexer lexer = alexer_create(filename, str, strlen(str));

  lexer.puncts = puncts;
  lexer.puncts_count = ALEXER_ARRAY_LEN(puncts);
  lexer.keywords = built_in_strings;
  lexer.keywords_count = ALEXER_ARRAY_LEN(built_in_strings);
  lexer.sl_comments = NULL;
  lexer.sl_comments_count = 0;
  lexer.ml_comments = NULL;
  lexer.ml_comments_count = 0;

  struct Tokens tokens = { 0 };

  if (!get_tokens(&lexer, &tokens, filename, str, PUNCT_QUOTE)) {
    return false;
  }

  for (size_t i = 0; i < tokens.count; i++) {
    printf("%zu: \"%.*s\"\n", i, (int) (tokens.items[i].end - tokens.items[i].begin), tokens.items[i].begin);
  }

  return true;
}
