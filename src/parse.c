#include "parse.h"
#include "lex.h"
#include "token.h"
#include "keyword.h"
#include "utils.h"
#include "json.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define DATE_SIZE 11

static Parser this;

static bool eat(TokenType type) {
  if (this.token.type == type) {
    this.token = lex();

    return true;
  }

  return false;
}

static bool statement_exit(void) {
  Token keyword = this.token;

  if (!eat(Token_Keyword)) {
    return false;
  }

  if (keyword.value.num != Keyword_Exit) {
    return false;
  }

  if (!eat('(')) {
    return false;
  }

  if (this.token.type == ')') {
    this.token = lex();

    exit(EXIT_SUCCESS);
  }

  else if (this.token.type == Token_Num) {
    Token num = this.token;

    this.token = lex();

    if (!eat(')')) {
      return false;
    }

    exit(num.value.num);
  }

  return false;
}

static bool statement_date(char *date) {
  Token year = this.token;

  if (!eat(Token_Num)) {
    return false;
  }

  if (!eat('-')) {
    return false;
  }

  Token month = this.token;

  if (!eat(Token_Num)) {
    return false;
  }

  if (!eat('-')) {
    return false;
  }

  Token day = this.token;

  if (!eat(Token_Num)) {
    return false;
  }

  snprintf(date, DATE_SIZE, "%04d-%02d-%02d", year.value.num, month.value.num, day.value.num);

  return true;
}

static bool statement_print(void) {
  Token keyword = this.token;

  if (!eat(Token_Keyword)) {
    return false;
  }

  if (keyword.value.num != Keyword_Print) {
    return false;
  }

  if (!eat('(')) {
    return false;
  }

  if (this.token.type == ')') {
    this.token = lex();

    fprintj(stdout, root, this.indent);

    putchar('\n');

    return true;
  }

  else if (this.token.type == Token_Num) {
    char date[DATE_SIZE] = { 0 };

    if (!statement_date(date)) {
      return false;
    }

    if (!eat(')')) {
      return false;
    }

    printf("%s = ", date);

    Json *value = object_get(root, date);

    if (value) {
      fprintj(stdout, value, this.indent);

      putchar('\n');
    }

    else {
      printf("null\n");
    }

    return true;
  }

  return false;
}

Json *statement_object(bool can_have_sub) {
  Token from = this.token;

  if (!eat(Token_CRS)) {
    return NULL;
  }

  if (!eat(Token_Arrow)) {
    return NULL;
  }

  Token to = this.token;

  if (!eat(Token_CRS)) {
    return NULL;
  }

  Token text = this.token;

  if (!eat(Token_Str)) {
    return NULL;
  }

  Token link = {
    .type = Token_Unknown,
    .value.str = NULL
  };

  if (eat('-')) {
    link = this.token;

    if (!eat(Token_Str)) {
      return NULL;
    }
  }

  Json *sub = new_json(Json_Array, NULL);

  if (can_have_sub) {
    if (eat('[')) {
get_next:
      Json *new = statement_object(false);

      if (new) {
        array_append(sub, new);

        if (eat(',')) {
          goto get_next;
        }

        if (!eat(']')) {
          return NULL;
        }
      }
    }
  }

  Json *object = new_json(Json_Object, NULL);

  object_set(object, "from", new_json(Json_String, strdup(from.value.crs)), false);

  object_set(object, "to", new_json(Json_String, strdup(to.value.crs)), false);

  object_set(object, "text", new_json(Json_String, text.value.str), false);

  if (link.value.str) {
    object_set(object, "link", new_json(Json_String, link.value.str), false);
  }

  if (length(sub) > 0) {
    object_set(object, "sub", sub, false);
  }

  else {
    free_json(sub);
  }
 
  return object;
}

static bool statement(void) {
  switch (this.token.type) {
    case Token_Keyword:
      switch (this.token.value.num) {
        case Keyword_Exit:
          return statement_exit();

        case Keyword_Print:
          return statement_print();

        default:
          return false;
      }

    case Token_Num:
      char date[DATE_SIZE] = { 0 };

      if (!statement_date(date)) {
        return false;
      }

      Token op = this.token;

      if (op.type != Token_Append && op.type != '=') {
        return false;
      }
      
      this.token = lex();

      Json *object = statement_object(true);

      if (!object) {
        return false;
      }

      if (op.type == '=') {
        printf("set %s to ", date);
        fprintj(stdout, object, this.indent);
        putchar('\n');

        object_set(root, date, object, true);

        object_sort(root);
      }

      else if (op.type == Token_Append) {
        printf("append ");
        fprintj(stdout, object, this.indent);
        printf(" to %s\n", date);

        Json *json = object_get(root, date);

        if (json) {
          enum JsonType type = json_type(json);

          switch (type) {
            case Json_Array:
              array_append(json, object);

              break;

            case Json_Object:
              Json *array = new_json(Json_Array, NULL);

              array_append(array, json);

              array_append(array, object);

              object_set(root, date, array, false);

              break;

            default:
              fprintf(
                stderr,
                "Unexpected Json type\n"
                "Expected: %s or %s, got: %s\n",
                json_type_string(Json_Array),
                json_type_string(Json_Object),
                json_type_string(type)
              );

              free_json(json);

              free_json(object);

              return false;
          }
        }

        else{
          object_set(root, date, object, false);

          object_sort(root);
        }
      }

      return true;

    default:
      return false;
  }

  return false;
}

static bool __parse(void) {
  while (this.token.type != Token_EOF && this.token.type != Token_Unknown) {
    if (!statement()) {
      return false;
    }
  }

  return this.token.type == Token_EOF;
}

bool __parse_opt(Parser opt) {
  if (opt.lexer) {
    this.lexer = opt.lexer;

    this.token = lex(.input = this.lexer->input);
  }

  this.indent = opt.indent;

  return __parse();
}
