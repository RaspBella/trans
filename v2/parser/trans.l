%option noyywrap
%option never-interactive
%option reentrant
%option bison-bridge

%{
#include "trans.tab.h"
%}

U           "u"[[:xdigit:]]{4}
ESCAPED     \\(["\\\/bfnrt]|{U})
PRINT       [\x20-\x21\x23-\x7E]
CHAR        {ESCAPED}|{PRINT}

CODE        \{[A-Z]{3}|[a-z]{3}\}
ID          [_a-zA-Z][_a-zA-Z0-9]*

%%

"exit"      { return TOK_EXIT; }
"help"      { return TOK_HELP; }
"print"     { return TOK_PRINT; }
"add"       { return TOK_ADD; }
"="         { return '='; }
":"         { return ':'; }
"("         { return '('; }
")"         { return ')'; }
"["         { return '['; }
"]"         { return ']'; }
"->"        { return TOK_RIGHT_ARROW; }
","         { return ','; }
\d+         { yylval->integer = atoi(yytext); return TOK_INT; }
\"{CHAR}*\" { yylval->string = strndup(yytext + 1, strlen(yytext+1) - 1); return TOK_STRING; }
{CODE}      { yylval->string = strndup(yytext + 1, 3); return TOK_CODE; }
{ID}        { yylval->string = strdup(yytext); return TOK_ID; }

[ \t\r\n]+  ;

%%
