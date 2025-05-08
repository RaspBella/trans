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

struct Token *current_token(struct Tokens *tokens, size_t index) {
  return (index < tokens->count) ? tokens->items + index : NULL;
}

Json *parse_value(struct Tokens *tokens, size_t *index); // forward decl

Json *parse_keyword(struct Tokens *tokens, size_t *index) {
  struct Token *token = current_token(tokens, *index);

  if (!token || ALEXER_KIND(token->id) != ALEXER_KEYWORD) return NULL;

  switch (ALEXER_INDEX(token->id)) {
    case KEYWORD_NULL:
      return new_json(JsonNull, NULL);

    case KEYWORD_TRUE:
      return new_json(JsonBool, (void*) true);

    case KEYWORD_FALSE:
      return new_json(JsonBool, (void*) false);
  }

  return NULL;
}

Json *parse_number(struct Tokens *tokens, size_t *index) {
  struct Token *token = current_token(tokens, *index);

  if (!token || ALEXER_KIND(token->id) != ALEXER_INT) return NULL;

  (*index)++;

  return new_json(JsonNumber, (void*) token->int_value);
}

Json *parse_string(struct Tokens *tokens, size_t *index) {
  struct Token *token = current_token(tokens, *index);

  if (!token || ALEXER_KIND(token->id) != ALEXER_STRING) return NULL;

  size_t len = token->end - token->begin;

  char *str = calloc(len + 1, sizeof(char));

  assert(str);

  memcpy(str, token->begin, len);

  (*index)++;

  return new_json(JsonString, str);
}

Json *parse_array(struct Tokens *tokens, size_t *index) {
  struct Token *token = current_token(tokens, *index);

  if (!token || token->id != ALEXER_ID(ALEXER_PUNCT, PUNCT_LEFT_BRACKET)) return NULL;

  (*index)++;

  Json *array = new_json(JsonArray, calloc(1, sizeof(struct JsonArray)));

  while (true) {
    token = current_token(tokens, *index);

    if (!token) break;

    if (token->id == ALEXER_ID(ALEXER_PUNCT, PUNCT_RIGHT_BRACKET)) {
      (*index)++;

      break;
    }

    Json *value = parse_value(tokens, index);

    if (!value) {
      free_json(array);

      return NULL;
    }

    da_append((struct JsonArray*) array->data, value);

    token = current_token(tokens, *index);

    if (token && token->id == ALEXER_ID(ALEXER_PUNCT, PUNCT_COMMA)) {
      (*index)++;

      continue;
    }

    else if (token && token->id == ALEXER_ID(ALEXER_PUNCT, PUNCT_RIGHT_BRACKET)) {
      (*index)++;

      break;
    }

    else {
      free_json(array);

      return NULL;
    }
  }

  return array;
}

Json *parse_object(struct Tokens *tokens, size_t *index) {
  struct Token *token = current_token(tokens, *index);

  if (!token || token->id != ALEXER_ID(ALEXER_PUNCT, PUNCT_LEFT_BRACE)) return NULL;

  (*index)++;

  Json *obj = new_json(JsonObject, new_map(0, NULL, NULL));

  while (true) {
    token = current_token(tokens, *index);

    if (!token) break;

    if (token->id == ALEXER_ID(ALEXER_PUNCT, PUNCT_RIGHT_BRACE)) {
      (*index)++;
      break;
    }


    // raw string in map is easier and better i recon
    char *str = NULL;
    Json *json_string = parse_string(tokens, index);

    if (json_string) {
      str = json_string->data;

      free(json_string);
    }

    else {
      free_json(obj);

      return NULL;
    }


    token = current_token(tokens, *index);

    if (!token || token->id != ALEXER_ID(ALEXER_PUNCT, PUNCT_COLON)) {
      free(str);
      free_json(obj);

      return NULL;
    }

    (*index)++;


    Json *value = parse_value(tokens, index);

    if (!value) {
      free(str);
      free_json(obj);

      return NULL;
    }


    map_set(obj->data, str, value);


    token = current_token(tokens, *index);

    if (token && token->id == ALEXER_ID(ALEXER_PUNCT, PUNCT_COMMA)) {
      (*index)++;

      continue;
    }

    else if (token && token->id == ALEXER_ID(ALEXER_PUNCT, PUNCT_RIGHT_BRACE)) {
      (*index)++;

      break;
    }

    else {
      free_json(obj);

      return NULL;
    }
  }

  return obj;
}

Json *parse_value(struct Tokens *tokens, size_t *index) {
  struct Token *token = current_token(tokens, *index);

  if (!token) return NULL;

  if (ALEXER_KIND(token->id) == ALEXER_KEYWORD) {
    return parse_keyword(tokens, index);
  }

  else if (ALEXER_KIND(token->id) == ALEXER_INT) {
    return parse_number(tokens, index);
  }

  else if (ALEXER_KIND(token->id) == ALEXER_STRING) {
    return parse_string(tokens, index);
  }

  else if (token->id == ALEXER_ID(ALEXER_PUNCT, PUNCT_LEFT_BRACKET)) {
    return parse_array(tokens, index);
  }

  else if (token->id == ALEXER_ID(ALEXER_PUNCT, PUNCT_LEFT_BRACE)) {
    return parse_object(tokens, index);
  }

  return NULL;
}

Json *parse_json(const char *filename, char *str) {
  struct Tokens tokens = { 0 };

  if (!get_tokens(&tokens, filename, str)) {
    return NULL;
  }
  
  size_t index = 0;
  Json *new = parse_value(&tokens, &index);

  if (tokens.capacity) free(tokens.items);

  return new;
}
