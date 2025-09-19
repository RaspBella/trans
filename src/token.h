#pragma once

typedef enum {
  Token_EOF = 256,
  Token_Unknown,
  Token_Op,
  Token_Num,
  Token_Unit
} TokenType;

typedef union {
  int num;
  char c;
  char *string;
} TokenValue;

typedef struct {
  TokenType type;
  TokenValue value;
} Token;
