#include "lex.h"
#include "token.h"

#include <stdlib.h>
#include <stdio.h>
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

static bool is_unit(char c) {
  switch (c) {
    case 'y':
    case 'Y':
    case 'm':
    case 'M':
    case 'w':
    case 'W':
    case 'd':
    case 'D':
      return true;

    default:
      return false;
  }
}

static Token __lex(void) {
  while (this.input[this.pos]) {
    if (isspace(this.input[this.pos])) {
      skip_whitespace();
    }

    if (isdigit(this.input[this.pos])) {
      return num();
    }

    if (this.input[this.pos] == '+') {
      this.pos++;

      return (Token){
        .type = Token_Op,
        .value.c = '+'
      };
    }

    if (this.input[this.pos] == '-') {
      this.pos++;

      return (Token){
        .type = Token_Op,
        .value.c = '-'
      };
    }

    if (is_unit(this.input[this.pos])) {
      this.pos++;

      return (Token){
        .type = Token_Unit,
        .value.c = tolower(this.input[this.pos - 1])
      };
    }

    fprintf(stderr, "Lex: Unknown character: %c\n", this.input[this.pos]);

    this.pos++;

    return (Token){ .type = Token_Unknown };
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
