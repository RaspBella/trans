#include "lex.h"
#include "token.h"
#include "keyword.h"
#include "crs.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define a_z(c) (c >= 'a' && c <= 'z')

#define A_Z(c) (c >= 'A' && c <= 'Z')

#define a_z_A_Z(c) (a_z(c) || A_Z(c))

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

      case '(':
      case ')':
      case '[':
      case ']':
      case '=':
      case ',':
        this.pos++;

        return (Token){
          .type = this.input[this.pos - 1]
        };
      
      case '-':
        switch (this.input[this.pos + 1]) {
          case '>':
            this.pos += 2;

            return (Token){
              .type = Token_Arrow
            };

          default:
            this.pos++;

            return (Token){
              .type = '-'
            };
        }

      case '+':
        switch (this.input[this.pos + 1]) {
          case '=':
            this.pos += 2;

            return (Token){
              .type = Token_Append
            };

          default:
            this.pos++;

            return (Token){
              .type = Token_Unknown
            };
        }

      case '"':
        char *close = strchr(this.input + this.pos + 1, '"');

        size_t len = close - (this.input + this.pos) - 1;

        if (close) {
          this.pos += len + 2;

          return (Token){
            .type = Token_Str,
            .value.str = strndup(this.input + this.pos - len - 1, len)
          };
        }

        else {
          fprintf(stderr, "No matching `\"` found\n");

          return (Token){
            .type = Token_Unknown
          };
        }

      default:
        if (strlen(this.input + this.pos) >= 3 && !a_z_A_Z(this.input[this.pos + 3]) && CASE_I_VALID_CRS(this.input + this.pos)) {
          this.pos += 3;

          return (Token){
            .type = Token_CRS,
            .value.crs = {
              [0] = this.input[this.pos - 3],
              [1] = this.input[this.pos + 1 - 3],
              [2] = this.input[this.pos + 2 - 3],
              [3] = 0
            }
          };
        }

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

        fprintf(stderr, "Lex: Unknown character: %c\n", this.input[this.pos]);

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
