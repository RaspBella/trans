#include "parse.h"
#include "lex.h"
#include "token.h"

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

static bool exec() {
  Token op = this.token;

  if (!eat(Token_Op)) {
    fprintf(stderr, "Expected Op\n");

    return false;
  }

  Token num = this.token;

  if (!eat(Token_Num)) {
    fprintf(stderr, "Expected Num\n");

    return false;
  }

  Token unit = this.token;

  if (!eat(Token_Unit)) {
    fprintf(stderr, "Expected Unit\n");

    return false;
  }

  switch (op.value.c) {
    case '+':
      printf("Add");

      break;

    case '-':
      printf("Sub");

      break;

    default:
      fprintf(stderr, "Unreachable\n");

      return false;
  }

  printf("(%d ", num.value.num);

  switch (unit.value.c) {
    case 'y':
      printf("Year");

      break;

    case 'm':
      printf("Month");

      break;

    case 'w':
      printf("Week");

      break;

    case 'd':
      printf("Day");

      break;

    default:
      fprintf(stderr, "Unreachable\n");

      return false;
  }

  printf("%s)\n", num.value.num != 1 ? "s" : "");

  return true;
}

static bool __parse(void) {
  while (this.token.type != Token_EOF && this.token.type != Token_Unknown) {
    if (!exec()) {
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
