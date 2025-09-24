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

static bool exec() {
  if (this.token.type < 256) {
    printf("Character: %c\n", this.token.type);
  }

  else {
    switch (this.token.type) {
      case Token_Keyword:
        printf("Token_Keyword: %s\n", keywords[this.token.value.num]);

        break;

      case Token_Num:
        printf("Token_Num: %d\n", this.token.value.num);

        break;
    }
  }

  this.token = lex();

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
