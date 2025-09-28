#pragma once

typedef enum {
  Token_Open_Paren = '(',
  Token_Close_Paren = ')',
  Token_Open_Bracket = '[',
  Token_Close_Bracket = ']',
  Token_Open_Brace = '{',
  Token_Close_Brace = '}',
  Token_Hyphen = '-',
  Token_Equal = '=',
  Token_EOF = 256,
  Token_Unknown,
  Token_Keyword,
  Token_Num,
  Token_Arrow,
  Token_Append,
} TokenType;

typedef union {
  int num;
} TokenValue;

typedef struct {
  TokenType type;
  TokenValue value;
} Token;
