%{
#include <stdlib.h>
#include <stdio.h>
#include "trans_extra.h"
#include "json_extra.h"
#include "../usage.h"
%}

%code requires {
  #include <stdlib.h>
  #include <stdio.h>
  #include "trans_extra.h"
  #include "json_extra.h"
  #include "../usage.h"
  typedef void* yyscan_t;
  typedef union YYSTYPE YYSTYPE;
  int yylex(YYSTYPE *yylval, yyscan_t scanner);
  void yyerror(yyscan_t scanner, Json *data, const char *msg);
}

%define api.pure full

%parse-param {void * scanner}
%parse-param {Json *data}
%lex-param {yyscan_t scanner}

%union {
  Json *Json;
  int integer;
  char *string;
  struct JsonArray *JsonArray;
}

%token TOK_EXIT TOK_HELP TOK_PRINT TOK_ADD TOK_ASSIGN TOK_RIGHT_ARROW
%token TOK_CODE TOK_ID TOK_STRING TOK_INT

%type <string> TOK_CODE
%type <string> TOK_ID
%type <string> TOK_STRING
%type <integer> TOK_INT

%type <JsonArray> items

%type <Json> From
%type <Json> To
%type <Json> Place

%type <Json> MaybeInfo
%type <Json> MaybeSub

%type <Json> Journey

%start Action

%%

Action: Exit
      | Help
      | Print
      | Add
      | Assign
      ;

Exit: TOK_EXIT '(' TOK_INT ')' { exit($3); }
    | TOK_EXIT '(' ')'         { exit(0); }
    ;

Help: TOK_HELP '(' ')' { usage(stdout, NULL); }
    ;

Print: TOK_PRINT '(' Journey ')' { print_json($3); }
     | TOK_PRINT '(' TOK_ID ')'  { print_var($3); }
     ;

Add: TOK_ADD '(' TOK_STRING ',' Journey ')' { add_journey(data, $3, $5); }
      | TOK_ADD '(' TOK_STRING ',' TOK_ID ')'  { add_var(data, $3, $5); }
      ;

Assign: TOK_ID '=' Journey { assign_journey($1, $3); }
      | TOK_ID '=' TOK_ID  { assign_var($1, $3); }
      ;

Journey: From TOK_RIGHT_ARROW To MaybeInfo MaybeSub { $$ = new_journey($1, $3, $4, $5); }
       ;

From: Place
    ;

To: Place
  ;

Place: TOK_CODE   { $$ = new_station($1); }
     | TOK_STRING { $$ = new_json(JsonString, $1); }
     ;

MaybeInfo: ':' TOK_STRING { $$ = new_json(JsonString, $2); }
         | %empty         { $$ = NULL; }
         ;

MaybeSub: '[' items ']'   { $$ = new_json(JsonArray, $2); }
        | '[' Journey ']' { $$ = new_json(JsonObject, $2); }
        | %empty          { $$ = NULL; }
        ;

items: Journey           { $$ = new_array($1); }
     | items ',' Journey { $$ = append_item($1, $3); }
     ;

%%

void yyerror(yyscan_t scanner, Json *data, const char *msg) {
  fprintf(stderr, "Parse error: %s\n", msg);
}
