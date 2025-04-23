#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "alexer.h"
#include "trans.h"
#include "../trans.h"
#include "../builtins.h"



typedef enum {
  PUNCT_RIGHT_ARROW,
  PUNCT_ADDON,
  PUNCT_HYPHEN,
  PUNCT_LEFT_BRACKET,
  PUNCT_RIGHT_BRACKET,
  PUNCT_COMMA,
  COUNT_PUNCTS
} Punct_Index;

static_assert(COUNT_PUNCTS == 6, "Amount of puncts has changed");
static const char *puncts[COUNT_PUNCTS] = {
  [PUNCT_RIGHT_ARROW] = "->",
  [PUNCT_ADDON] =  "+=",
  [PUNCT_HYPHEN] = "-",
  [PUNCT_LEFT_BRACKET] = "[",
  [PUNCT_RIGHT_BRACKET] = "]",
  [PUNCT_COMMA] = ","
};



bool trans_parser(char *program_name, const char *filename, char *str) {
  Alexer lexer = alexer_create(filename, str, strlen(str));

  lexer.puncts = puncts;
  lexer.puncts_count = ALEXER_ARRAY_LEN(puncts);
  lexer.keywords = transport_strings;
  lexer.keywords_count = ALEXER_ARRAY_LEN(transport_strings);
  lexer.sl_comments = NULL;
  lexer.sl_comments_count = 0;
  lexer.ml_comments = NULL;
  lexer.ml_comments_count = 0;

  Alexer_Token token = { 0 };

  while (alexer_get_token(&lexer, &token)) {
    // Print token
    lexer.diagf(
      token.loc,
      "INFO",
      "%s: %.*s",
      alexer_kind_name(ALEXER_KIND(token.id)),
      token.end - token.begin,
      token.begin
    );



    // Check for built in

    int built_in = BUILT_IN_INVALID;

    if (ALEXER_KIND(token.id) == ALEXER_SYMBOL) {
      for (int i = 0; i < COUNT_BUILT_INS; i++) {
        if (!strncmp(token.begin, built_in_strings[i], token.end -token.begin)) {
          built_in = i;
          break;
        }
      }
    }

    if (built_in != BUILT_IN_INVALID) {
      switch (built_in) {
        case BUILT_IN_EXIT:
          Alexer_Token next = { 0 };

          alexer_get_token(&lexer, &next);
    
          // Print token
          lexer.diagf(
            next.loc,
            "INFO",
            "%s: %.*s",
            alexer_kind_name(ALEXER_KIND(next.id)),
            next.end - next.begin,
            next.begin
          );

          if (ALEXER_KIND(next.id) == ALEXER_INT)
          {
            Alexer_Token end = { 0 };

            alexer_get_token(&lexer, &end);

            if (!alexer_expect_id(&lexer, end, ALEXER_END)) {
              return false;
            }

            built_in_functions[built_in]((void*)next.int_value);
          }
          
          else {
            built_in_functions[built_in](0);
          }

          break;

        case BUILT_IN_HELP:
          built_in_functions[built_in](program_name);

          break;
      }
    }
  }

  return true;
}
