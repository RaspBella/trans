#include "lex.h"
#include "token.h"
#include "keyword.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static Lexer this;

static void skip_whitespace(void) {
  do { 
    this.pos++;
  } while (isspace(this.input[this.pos]));
}

static Token num(void) {
  int number = atoi(this.input + this.pos);

  do {
    this.pos++;
  } while (isdigit(this.input[this.pos]));

  return (Token){
    .type = Token_Num,
    .value.num = number
  };
}

static Token __lex(void) {
  while (this.input[this.pos]) {
    if (isspace(this.input[this.pos])) {
      skip_whitespace();
    }

    switch (this.input[this.pos]) {
                case '0':
      case '1': case '2': case '3':
      case '4': case '5': case '6':
      case '7': case '8': case '9':
        return num();

      case '[':
      case ']':
      case '-':
      case '+':
      case '=':
        return (Token){
          .type = this.input[this.pos++]
        };

      default:
        for (int i = 0; i < KEYWORD_COUNT; i++) {
          size_t len = strlen(keywords[i]);

          if (!strncmp(this.input + this.pos, keywords[i], len)) {
            this.pos += len;

            return (Token){
              .type = Token_Keyword,
              .value.num = i
            };
          }
        }

        fprintf(stderr, "Lex: Unknown character: %c\n", this.input[this.pos++]);

        return (Token){ .type = Token_Unknown };
    }
  }

  return (Token){ .type = Token_EOF };
}

Token __lex_opt(Lexer opt) {
  if (opt.input) {
    this.input = opt.input;
    this.pos = 0;
  }

  return __lex();
}
