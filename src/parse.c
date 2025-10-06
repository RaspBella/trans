#include "parse.h"
#include "lex.h"
#include "token.h"
#include "keyword.h"
#include "journey.h"
#include "utils.h"

#include <stdbool.h>
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

    return true;
  }

  else if (this.token.type == Token_Num) {
    Token num = this.token;

    this.token = lex();

    if (!eat(')')) {
      return false;
    }

    exit(num.value.num);

    return true;
  }

  return false;
}

static bool statement_select(char *date) {
  if (!eat('[')) {
    return false;
  }

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

  if (!eat(']')) {
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

    printf("call: print()\n");

    return true;
  }

  else if (this.token.type == '[') {
    char date[DATE_SIZE] = { 0 };

    if (!statement_select(date)) {
      return false;
    }

    if (!eat(')')) {
      return false;
    }

    printf("call: print([%s])\n", date);

    return true;
  }

  return false;
}

static Journey *statement_obj(bool can_have_sub) {
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

  JourneyArray sub = { 0 };

  if (can_have_sub) {
    if (eat('[')) {
get_next:
      Journey *new = statement_obj(false);

      if (new) {
        da_append(&sub, new);

        if (eat(',')) {
          goto get_next;
        }

        if (!eat(']')) {
          return NULL;
        }
      }
    }
  }
 
  return new_journey(from.value.crs, to.value.crs, text.value.str, link.value.str, sub);
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

    case '[':
      char date[DATE_SIZE] = { 0 };

      if (!statement_select(date)) {
        return false;
      }

      Token op = this.token;

      if (op.type != Token_Append && op.type != '=') {
        return false;
      }
      
      this.token = lex();

      Journey *new = statement_obj(true);

      if (!new) {
        return false;
      }

      if (op.type == '=') {
        printf("set %s to ", date);
        print_journey(new);
        printf("\n");
      }

      else if (op.type == Token_Append) {
        printf("append ");
        print_journey(new);
        printf(" to %s\n", date);
      }

      free_journey(new);

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

  return __parse();
}
