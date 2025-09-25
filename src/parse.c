#include "parse.h"
#include "lex.h"
#include "token.h"
#include "keyword.h"

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

  Token open = this.token;

  if (!eat('(')) {
    return false;
  }

  if (this.token.type == ')') {
    this.token = lex();

    printf("call: exit()\n");

    return true;
  }

  else if (this.token.type == Token_Num) {
    Token num = this.token;

    this.token = lex();

    if (!eat(')')) {
      return false;
    }

    printf("call: exit(%d)\n", num.value.num);

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

  Token open = this.token;

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

    printf("call: print(%s)\n", date);

    return true;
  }

  return false;
}

static bool statement_obj(void) {
  return false;
}

static bool statement(void) {
  switch (this.token.type) {
    case Token_Keyword:
      switch (this.token.value.num) {
        case Keyword_Exit:
          return statement_exit();

        case Keyword_Print:
          return statement_print();
      }

    case '[':
      char date[DATE_SIZE] = { 0 };

      if (!statement_select(date)) {
        return false;
      }

      Token token = this.token;

      if (token.type == '+') {
        this.token = lex();

        if (!eat('=')) {
          return false;
        }
      }

      else if (token.type == '=') {
        this.token = lex();
      }

      if (!statement_obj()) {
        return false;
      }

      return true;
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
