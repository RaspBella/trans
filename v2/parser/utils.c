#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "alexer.h"
#include "../utils.h"
#include "utils.h"

bool get_tokens(Alexer *lexer, struct Tokens *tokens, const char *filename, char *str, uint64_t quote_id) {
  Alexer_Token token = { 0 };

  while (alexer_get_token(lexer, &token)) {
    // Check for string without supporting escapes

    if (token.id == quote_id) {
      char *end = strchr(token.begin + 1, '"');

      if (end == NULL) {
        return false;
      }

      struct Token string = {
        .id = ALEXER_ID(ALEXER_STRING, 0),
        .begin = token.begin + 1,
        .end = end,
        .int_value = 0
      };

      da_append(tokens, string);

      while (token.begin != end) {
        alexer_get_token(lexer, &token);
      }
    }

    else {
      struct Token new = {
        .id = token.id,
        .begin = token.begin,
        .end = token.end,
        .int_value = token.int_value
      };

      da_append(tokens, new);
    }
  }

  return true;
}

struct Token *current_token(struct Tokens *tokens, size_t index) {
  return (index < tokens->count) ? tokens->items + index : NULL;
}
