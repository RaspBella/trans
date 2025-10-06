#pragma once

#include "lex.h"
#include "token.h"

#include <stdbool.h>

typedef struct {
  Lexer *lexer;
  Token token;
  int indent;
} Parser;

bool __parse_opt(Parser);

#define parse(string, ...) \
  __parse_opt((Parser){ .lexer = &(Lexer){ .input = string }, __VA_ARGS__ })
