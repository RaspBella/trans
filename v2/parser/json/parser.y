%{
#include <stdio.h>
#include "../../json.h"
#include "../helper.h"

int yylex(void);
void yyerror(const char*);

extern FILE *yyin;
Json *root = NULL;
%}

%defines

%code requires {
  #include "../../json.h"
  #include "../helper.h"
}

%union {
  Json *Json;
  double number;
  char *string;
  struct da_pairs *pairs;
  struct MapEntry *pair;
  struct JsonArray *JsonArray;
}

%token TOK_TRUE TOK_FALSE TOK_NULL TOK_NUMBER TOK_STRING

%type <number> TOK_NUMBER
%type <string> TOK_STRING

%type <JsonArray> items
%type <pair> pair
%type <pairs> pairs

%type <Json> JsonValue JsonObject JsonArray JsonString JsonNumber JsonBool JsonNull

%start Json

%%

Json: JsonValue { root = $1; };

JsonValue: JsonObject
         | JsonArray
         | JsonString
         | JsonNumber
         | JsonBool
         | JsonNull
         ;

JsonObject: '{' pairs '}'      { $$ = new_json(JsonObject, new_map_from_pairs($2)); }
          | '{' '}'            { $$ = new_json(JsonObject, NULL); }
          ;

pairs: pair                    { $$ = new_pairs($1); }
     | pairs ',' pair          { $$ = append_pair($1, $3); }
     ;

pair: TOK_STRING ':' JsonValue { $$ = new_pair($1, $3); }
    ;

JsonArray: '[' items ']'       { $$ = new_json(JsonArray, $2); }
         | '[' ']'             { $$ = new_json(JsonArray, NULL); }
         ;

items: JsonValue               { $$ = new_array($1); }
     | items ',' JsonValue     { $$ = append_item($1, $3); }
     ;

JsonString: TOK_STRING         { $$ = new_json(JsonString, $1); }
          ;

JsonNumber: TOK_NUMBER         { $$ = new_json(JsonNumber, new_number($1)); }
          ;

JsonBool: TOK_TRUE             { $$ = new_json(JsonBool, (void*) true); }
        | TOK_FALSE            { $$ = new_json(JsonBool, (void*) false); }
        ;

JsonNull: TOK_NULL             { $$ = new_json(JsonNull, NULL); }
        ;

%%

#define yylex json_lex

int yylex_destroy(void);

void parse_json(FILE *fp) {
  yyin = fp;

  yyparse();

  yylex_destroy();
}

void yyerror(const char *msg) {
  fprintf(stderr, "Syntax error: %s\n", msg);
}
