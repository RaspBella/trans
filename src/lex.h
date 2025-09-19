#pragma once

#include "token.h"

typedef struct {
  const char *input;
  int pos;
} Lexer;

Token __lex_opt(Lexer);

#define lex(...) \
  __lex_opt((Lexer){ __VA_ARGS__ })
