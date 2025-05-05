#include <assert.h>

#include "alexer.h"
#include "json.h"
#include "../json.h"
#include "../utils.h"
#include "../map.h"

typedef enum {
  PUNCT_LEFT_BRACE,
  PUNCT_RIGHT_BRACE,
  PUNCT_LEFT_BRACKET,
  PUNCT_RIGHT_BRACKET,
  PUNCT_COLON,
  PUNCT_COMMA,
  PUNCT_QUOTE,
  COUNT_PUNCTS
} Punct_Index;

static_assert(COUNT_PUNCTS == 7, "Amount of puncts has changed");
static const char *puncts[COUNT_PUNCTS] = {
  [PUNCT_LEFT_BRACE] = "{",
  [PUNCT_RIGHT_BRACE] = "}",
  [PUNCT_LEFT_BRACKET] = "[",
  [PUNCT_RIGHT_BRACKET] = "]",
  [PUNCT_COLON] = ":",
  [PUNCT_COMMA] = ",",
  [PUNCT_QUOTE] = "\""
};

typedef enum {
  KEYWORD_NULL,
  KEYWORD_TRUE,
  KEYWORD_FALSE,
  COUNT_KEYWORDS
} Keyword_Index;

static_assert(COUNT_KEYWORDS == 3, "Amount of keywords has changed");
static const char *keywords[COUNT_KEYWORDS] = {
  [KEYWORD_NULL] = "null",
  [KEYWORD_TRUE] = "true",
  [KEYWORD_FALSE] = "false"
};



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

bool get_tokens(struct Tokens *tokens, const char *filename, char *str) {
  Alexer lexer = alexer_create(filename, str, strlen(str));

  lexer.puncts = puncts;
  lexer.puncts_count = ALEXER_ARRAY_LEN(puncts);
  lexer.keywords = keywords;
  lexer.keywords_count = ALEXER_ARRAY_LEN(keywords);
  lexer.sl_comments = NULL;
  lexer.sl_comments_count = 0;
  lexer.ml_comments = NULL;
  lexer.ml_comments_count = 0;

  Alexer_Token token = { 0 };

  while (alexer_get_token(&lexer, &token)) {
    // Check for string without supporting escapes

    if (ALEXER_KIND(token.id) == ALEXER_PUNCT && ALEXER_INDEX(token.id) == PUNCT_QUOTE) {
      char *end = strchr(token.begin + 1, '"');

      if (end == NULL) {
        return false;
      }

      struct Token string = {
        .id = ALEXER_ID(ALEXER_STRING, 0),
        .begin = token.begin + 1,
        .end = end,
        .int_value = 0
      };

      da_append(tokens, string);

      while (token.begin != end) {
        alexer_get_token(&lexer, &token);
      }
    }

    else {
      struct Token new = {
        .id = token.id,
        .begin = token.begin,
        .end = token.end,
        .int_value = token.int_value
      };

      da_append(tokens, new);
    }
  }

  return true;
}

Json *json_parser(const char *filename, char *str) {
  struct Tokens tokens = { 0 };

  if (!get_tokens(&tokens, filename, str)) {
    return NULL;
  }

  // Check and see tokens are real
  for (size_t i = 0; i < tokens.count; i++) {
    printf("token#%zu: %.*s\n", i, (int) (tokens.items[i].end - tokens.items[i].begin), tokens.items[i].begin);
  }

  Json *new = NULL;

  void *orig = tokens.items;

  // Asume top level is Object `{` ... `}`
  if (tokens.count < 2) {
    if (tokens.items) free(tokens.items);
    return NULL; // Need atleast 2 tokens
  }

  if (!(ALEXER_KIND(tokens.items->id) == ALEXER_PUNCT && ALEXER_INDEX(tokens.items->id) == PUNCT_LEFT_BRACE && ALEXER_KIND(tokens.items[tokens.count - 1].id) == ALEXER_PUNCT && ALEXER_INDEX(tokens.items[tokens.count - 1].id))) {
    return NULL;
  }

  new = new_json(JsonObject, new_map(0, NULL, NULL));

  tokens.items += 1;
  tokens.count -= 2;

  printf("Tokens within braces:\n");

  for (size_t i = 0; i < tokens.count; i++) {
    printf("token#%zu: %.*s\n", i, (int) (tokens.items[i].end - tokens.items[i].begin), tokens.items[i].begin);
  }

  free(orig);

  return new;
}
