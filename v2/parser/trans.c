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
#include "../map.h"
#include "../usage.h"



Map *vars = NULL;



typedef enum {
  PUNCT_RIGHT_ARROW,
  PUNCT_LEFT_PAREN,
  PUNCT_RIGHT_PAREN,
  PUNCT_LEFT_BRACKET,
  PUNCT_RIGHT_BRACKET,
  PUNCT_ASSIGN,
  PUNCT_COLON,
  PUNCT_COMMA,
  PUNCT_QUOTE,
  COUNT_PUNCTS
} Punct_Index;

static_assert(COUNT_PUNCTS == 9, "Amount of puncts has changed");
static const char *puncts[COUNT_PUNCTS] = {
  [PUNCT_RIGHT_ARROW] = "->",
  [PUNCT_LEFT_PAREN] = "(",
  [PUNCT_RIGHT_PAREN] = ")",
  [PUNCT_LEFT_BRACKET] = "[",
  [PUNCT_RIGHT_BRACKET] = "]",
  [PUNCT_ASSIGN] = "=",
  [PUNCT_COLON] = ":",
  [PUNCT_COMMA] = ",",
  [PUNCT_QUOTE] = "\""
};

typedef enum {
  KEYWORD_EXIT,
  KEYWORD_PRINT,
  KEYWORD_HELP,
  KEYWORD_ADD,
  COUNT_KEYWORDS
} Keyword_Index;

static_assert(COUNT_KEYWORDS == 4, "Amount of keywords has changed");
static const char *keywords[COUNT_KEYWORDS] = {
  [KEYWORD_EXIT] = "exit",
  [KEYWORD_PRINT] = "print",
  [KEYWORD_HELP] = "help",
  [KEYWORD_ADD] = "add"
};

const char *sl_comments[] = {
  "//"
};

Alexer_ML_Comments ml_comments[] = {
  { "/*", "*/" }
};



static char *parse_string(struct Tokens *tokens, size_t *index) {
  struct Token *token = current_token(tokens, *index);

  if (token && ALEXER_KIND(token->id) == ALEXER_STRING) {
    (*index)++;
    return strndup(token->begin, token->end - token->begin);
  }

  return NULL;
}

Json *parse_from_to(struct Tokens *tokens, size_t *index) {
  char *from = parse_string(tokens, index);

  if (from) {
    struct Token *token = current_token(tokens, *index);

    if (token && ALEXER_ID(ALEXER_PUNCT, PUNCT_RIGHT_ARROW) == token->id) {
      (*index)++;

      char *to = parse_string(tokens, index);

      if (to) {
        Json *json = new_json(JsonObject, NULL);

        map_set(json->data, strdup("from"), new_json(JsonString, from));
        map_set(json->data, strdup("to"), new_json(JsonString, to));

        return json;
      }
    }
  }

  return NULL;
}

Json *parse_base(struct Tokens *tokens, size_t *index) {
  Json *json = parse_from_to(tokens, index);

  if (json) {
    struct Token *token = current_token(tokens, *index);

    if (token && ALEXER_ID(ALEXER_PUNCT, PUNCT_COLON) == token->id) {
      (*index)++;

      char *info = parse_string(tokens, index);

      if (info) {
        map_set(json->data, strdup("info"), new_json(JsonString, info));
      }
    }

    return json;
  }

  return NULL;
}

Json *parse_journey(struct Tokens *tokens, size_t *index) {
  Json *base = parse_base(tokens, index);

  if (base) {
    struct Token *token = current_token(tokens, *index);

    if (token && ALEXER_ID(ALEXER_PUNCT, PUNCT_LEFT_BRACKET) == token->id) {
      (*index)++;

      Json *sub = parse_journey(tokens, index);

      if (sub) {
sub_comma:
        token = current_token(tokens, *index);

        if (token && ALEXER_ID(ALEXER_PUNCT, PUNCT_COMMA) == token->id) {
          (*index)++;

          sub = parse_journey(tokens, index);

          if (sub) {
            goto sub_comma;
          }
        }

        else if (token && ALEXER_ID(ALEXER_PUNCT, PUNCT_RIGHT_BRACKET) == token->id) {
          (*index)++;
        }

        map_set(base->data, strdup("sub"), sub);
      }
    }

    Json *array = NULL;

comma:
    token = current_token(tokens, *index);

    if (token && ALEXER_ID(ALEXER_PUNCT, PUNCT_COMMA) == token->id) {
      (*index)++;

      Json *more = parse_journey(tokens, index);

      if (more) {
        if (!array) {
          array = new_json(JsonArray, NULL);

          da_append((struct JsonArray*) array->data, base);
        }

        da_append((struct JsonArray*) array->data, more);

        goto comma;
      }
    }



    if (array) return array;
    else return base;
  }

  return NULL;
}

static void free_json_value(void *json) {
  free_json(json);
}

void free_vars(void) {
  if (vars) {
    free_map(vars, free, free_json_value);
  }
}

bool parse_exit(struct Tokens *tokens, size_t *index) {
  struct Token *token = current_token(tokens, *index);

  if (token && ALEXER_ID(ALEXER_KEYWORD, KEYWORD_EXIT) == token->id) {
    (*index)++;
    token = current_token(tokens, *index);

    if (token && ALEXER_ID(ALEXER_PUNCT, PUNCT_LEFT_PAREN) == token->id) {
      (*index)++;
      token = current_token(tokens, *index);

      if (token && ALEXER_KIND(token->id) == ALEXER_INT) {
        int value = token->int_value;

(*index)++;
        token = current_token(tokens, *index);

        if (token && ALEXER_ID(ALEXER_PUNCT, PUNCT_RIGHT_PAREN) == token->id) {
          free(tokens->items);

          exit(value);
        }
      }
    }
  }

  return false;
}

bool parse_print(Json *json, struct Tokens *tokens, size_t *index) {
  struct Token *token = current_token(tokens, *index);

  if (token && ALEXER_ID(ALEXER_KEYWORD, KEYWORD_PRINT) == token->id) {
    (*index)++;
    token = current_token(tokens, *index);

    if (token && ALEXER_ID(ALEXER_PUNCT, PUNCT_LEFT_PAREN) == token->id) {
      (*index)++;
      token = current_token(tokens, *index);

      if (token && ALEXER_ID(ALEXER_PUNCT, PUNCT_RIGHT_PAREN) == token->id) {
        print_json(json);
        printf("\n");

        (*index)++;
        return true;
      }

      else if (token && ALEXER_KIND(token->id) == ALEXER_SYMBOL) {
        char *var = strndup(token->begin, token->end - token->begin);

        (*index)++;
        token = current_token(tokens, *index);

        if (token && ALEXER_ID(ALEXER_PUNCT, PUNCT_RIGHT_PAREN) == token->id) {
          Json *value = map_get(vars, var);

          if (value) {
            print_json(value);
            printf("\n");

            free(var);

            (*index)++;
            return true;
          }

          else {
            fprintf(stderr, "undefined variable: %s\n", var);

            free(var);

            return false;
          }
        }
      }

      else {
        Json *value = parse_journey(tokens, index);

        token = current_token(tokens, *index);

        if (token && ALEXER_ID(ALEXER_PUNCT, PUNCT_RIGHT_PAREN) == token->id) {
          if (value) {
            print_json(value);
            printf("\n");

            free_json(value);

            (*index)++;
            return true;
          }
        }
      }
    }
  }

  return false;
}

bool parse_help(struct Tokens *tokens, size_t *index) {
  struct Token *token = current_token(tokens, *index);

  if (token && ALEXER_ID(ALEXER_KEYWORD, KEYWORD_HELP) == token->id) {
    (*index)++;
    token = current_token(tokens, *index);

    if (token && ALEXER_ID(ALEXER_PUNCT, PUNCT_LEFT_PAREN) == token->id) {
      (*index)++;
      token = current_token(tokens, *index);

      if (token && ALEXER_ID(ALEXER_PUNCT, PUNCT_RIGHT_PAREN) == token->id) {
        usage(stdout, NULL);

        (*index)++;
        return true;
      }
    }
  }

  return false;
}

void add(Json *json, char *key, Json *new_val) {
  Json *old_val = map_get(json->data, key);

  if (old_val) {
    if (old_val->type == JsonArray) {
      da_append((struct JsonArray*) old_val->data, new_val);
    }

    else {
      assert(old_val->type == JsonObject);

      Json *array = new_json(JsonArray, NULL);

      da_append((struct JsonArray*) array->data, old_val);
      da_append((struct JsonArray*) array->data, new_val);

      map_set(json->data, key, array);
    }
  }

  else {
    map_set(json->data, key, new_val);
  }
}

bool parse_add(Json *json, struct Tokens *tokens, size_t *index) {
  struct Token *token = current_token(tokens, *index);

  if (token && ALEXER_ID(ALEXER_KEYWORD, KEYWORD_ADD) == token->id) {
    (*index)++;
    token = current_token(tokens, *index);

    if (token && ALEXER_ID(ALEXER_PUNCT, PUNCT_LEFT_PAREN) == token->id) {
      (*index)++;

      char *key = parse_string(tokens, index);

      if (key) {
        token = current_token(tokens, *index);

        if (token && ALEXER_ID(ALEXER_PUNCT, PUNCT_COMMA) == token->id) {
          (*index)++;
          token = current_token(tokens, *index);

          if (token && ALEXER_KIND(token->id) == ALEXER_SYMBOL) {
            char *var = strndup(token->begin, token->end - token->begin);

            (*index)++;
            token = current_token(tokens, *index);

            if (token && ALEXER_ID(ALEXER_PUNCT, PUNCT_RIGHT_PAREN) == token->id) {
              Json *value = map_get(vars, var);

              if (value) {
                add(json, strdup(key), json_dup(value));

                free(var);
                free(key);

                (*index)++;
                return true;
              }

              else {
                fprintf(stderr, "undefined variable: %s\n", var);

                free(var);
                free(key);

                return false;
              }
            }
          }

          else {
            Json *value = parse_journey(tokens, index);

            token = current_token(tokens, *index);

            if (token && ALEXER_ID(ALEXER_PUNCT, PUNCT_RIGHT_PAREN) == token->id) {
              if (value) {
                add(json, strdup(key), json_dup(value));

                free(key);
                free_json(value);

                (*index)++;
                return true;
              }
            }
          }
        }

        free(key);
      }
    }
  }

  return false;
}

bool parse_assignment(struct Tokens *tokens, size_t *index) {
  struct Token *token = current_token(tokens, *index);

  if (token && ALEXER_KIND(token->id) == ALEXER_SYMBOL) {
    char *var = strndup(token->begin, token->end - token->begin);

    (*index)++;
    token = current_token(tokens, *index);

    if (token && ALEXER_ID(ALEXER_PUNCT, PUNCT_ASSIGN) == token->id) {
      (*index)++;
      token = current_token(tokens, *index);

      if (token && ALEXER_KIND(token->id) == ALEXER_STRING) {
        Json *new_journey = parse_journey(tokens, index);

        if (new_journey) {
          Json *old_journey = map_get(vars, var);

          if (old_journey) {
            free_json(old_journey);
          }

          map_set(vars, var, new_journey);

          return true;
        }
      }
    }
  }

  return false;
}

bool parse_statement(Json *json, struct Tokens *tokens, size_t *index) {
  struct Token *token = current_token(tokens, *index);

  if (token && ALEXER_KIND(token->id) == ALEXER_KEYWORD) {
    if (ALEXER_INDEX(token->id) == KEYWORD_EXIT) {
      return parse_exit(tokens, index);
    }

    else if (ALEXER_INDEX(token->id) == KEYWORD_PRINT) {
      return parse_print(json, tokens, index);
    }

    else if (ALEXER_INDEX(token->id) == KEYWORD_HELP) {
      return parse_help(tokens, index);
    }

    else if (ALEXER_INDEX(token->id) == KEYWORD_ADD) {
      return parse_add(json, tokens, index);
    }
  }

  else if (token && ALEXER_KIND(token->id) == ALEXER_SYMBOL) {
    return parse_assignment(tokens, index);
  }

  return false;
}

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

  if (!vars) {
    vars = new_map(0, NULL, NULL);

    atexit(free_vars);
  }

  size_t index = 0;

  while (parse_statement(json, &tokens, &index));

  if (tokens.capacity > 0) free(tokens.items);
}
