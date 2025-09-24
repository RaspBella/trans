#pragma once

typedef enum {
  Token_EOF = 256,
  Token_Unknown,
  Token_Keyword,
  Token_Num
} TokenType;

typedef union {
  int num;
} TokenValue;

typedef struct {
  TokenType type;
  TokenValue value;
} Token;
