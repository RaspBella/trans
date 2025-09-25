#include "parse.h"
#include "lex.h"
#include "token.h"
#include "keyword.h"

#include <stdbool.h>
#include <stdio.h>

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

    printf("Call exit: exit()\n");

    return true;
  }

  else if (this.token.type == Token_Num) {
    Token num = this.token;

    this.token = lex();

    if (!eat(')')) {
      return false;
    }

    printf("call exit with n=%d: exit(n)\n", num.value.num);

    return true;
  }

  return false;
}

static bool statement_select(char *date) {
}

static bool statement_print(void) {
}

static bool statement_op(void) {
}

static bool statement_obj(void) {
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
      char date[11] = { 0 };

      if (!statement_select(date)) {
        return false;
      }

      if (!statement_op()) {
        return false;
      }

      if (!statement_obj()) {
        return false;
      }
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
