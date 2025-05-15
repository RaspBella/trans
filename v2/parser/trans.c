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



typedef enum {
  PUNCT_RIGHT_ARROW,
  PUNCT_ADDON,
  PUNCT_LEFT_PAREN,
  PUNCT_RIGHT_PAREN,
  PUNCT_LEFT_BRACKET,
  PUNCT_RIGHT_BRACKET,
  PUNCT_COMMA,
  PUNCT_QUOTE,
  COUNT_PUNCTS
} Punct_Index;

static_assert(COUNT_PUNCTS == 8, "Amount of puncts has changed");
static const char *puncts[COUNT_PUNCTS] = {
  [PUNCT_RIGHT_ARROW] = "->",
  [PUNCT_ADDON] =  "+=",
  [PUNCT_LEFT_PAREN] = "(",
  [PUNCT_RIGHT_PAREN] = ")",
  [PUNCT_LEFT_BRACKET] = "[",
  [PUNCT_RIGHT_BRACKET] = "]",
  [PUNCT_COMMA] = ",",
  [PUNCT_QUOTE] = "\""
};

typedef enum {
  KEYWORD_EXIT,
  KEYWORD_PRINT,
  KEYWORD_HELP,
  KEYWORD_DATA,
  COUNT_KEYWORDS
} Keyword_Index;

static_assert(COUNT_KEYWORDS == 4, "Amount of keywords has changed");
static const char *keywords[COUNT_KEYWORDS] = {
  [KEYWORD_EXIT] = "exit",
  [KEYWORD_PRINT] = "print",
  [KEYWORD_HELP] = "help",
  [KEYWORD_DATA] = "data"
};

const char *sl_comments[] = {
  "//"
};

Alexer_ML_Comments ml_comments[] = {
  { "/*", "*/" }
};



void parse_trans(Json *json, const char *filename, char *str) {
  Alexer lexer = alexer_create(filename, str, strlen(str));

  lexer.puncts = puncts;
  lexer.puncts_count = ALEXER_ARRAY_LEN(puncts);
  lexer.keywords = keywords;
  lexer.keywords_count = ALEXER_ARRAY_LEN(keywords);
  lexer.sl_comments = sl_comments;
  lexer.sl_comments_count = ALEXER_ARRAY_LEN(sl_comments);
  lexer.ml_comments = ml_comments;;
  lexer.ml_comments_count = ALEXER_ARRAY_LEN(ml_comments);

  struct Tokens tokens = { 0 };

  if (!get_tokens(&lexer, &tokens, filename, str, PUNCT_QUOTE)) {
    return;
  }

  for (size_t i = 0; i < tokens.count; i++) {
    if (ALEXER_KIND(tokens.items[i].id) == ALEXER_STRING) {
      printf("%zu: \"%.*s\"\n", i, (int) (tokens.items[i].end - tokens.items[i].begin), tokens.items[i].begin);
    }

    else {
      printf("%zu: %.*s\n", i, (int) (tokens.items[i].end - tokens.items[i].begin), tokens.items[i].begin);
    }
  }

  if (tokens.capacity > 0) free(tokens.items);
}
