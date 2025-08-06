%option noyywrap
%option never-interactive
%option reentrant
%option bison-bridge

%{
#include "json.tab.h"
#include <string.h>
#include <stdlib.h>
%}

NUMBER      -?(0|[1-9][0-9]*)(\.[0-9]+)?([eE][+-]?[0-9]+)?

U           "u"[[:xdigit:]]{4}
ESCAPED     \\(["\\\/bfnrt]|{U})
PRINT       [\x20-\x21\x23-\x7E]
CHAR        {ESCAPED}|{PRINT}

%%

"{"         { return '{'; }
"}"         { return  '}'; }
"["         { return  '['; }
"]"         { return  ']'; }
":"         { return  ':'; }
","         { return  ','; }
"true"      { return TOK_TRUE; }
"false"     { return TOK_FALSE; }
"null"      { return TOK_NULL; }
{NUMBER}    { yylval->number = atof(yytext); return TOK_NUMBER; }
\"{CHAR}*\" { yylval->string = strndup(yytext + 1, strlen(yytext+1) - 1); return TOK_STRING; }

[ \t\r\n]+  ;
.           { return yytext[0]; }

%%
