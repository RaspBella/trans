#include "json.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct Key_Value {
  char *key;
  Json *value;
};

enum JsonType{
  Json_Null,
  Json_String,
  Json_Array,
  Json_Object,
};

struct Json {
  enum JsonType type;
  union {
    char *string;
    struct {
      size_t count;
      size_t capacity;
      Json **items;
    } array;
    struct {
      size_t count;
      size_t capacity;
      struct Key_Value *items;
    } object;
  };
};

enum TokenType {
  Token_Open_Paren = '{',
  Token_Close_Paren = '}',
  Token_Open_Bracket = '[',
  Token_Close_Bracket = ']',
  Token_Colon = ':',
  Token_Comma = ',',
  Token_EOF = 256,
  Token_Invalid,
  Token_String
};

struct Token {
  enum TokenType type;
  union {
    char *string;
  };
};

struct lexer {
  char *input;
  unsigned pos;
  struct Token cur_tok;
};

Json *root;

static Json *new_json(enum JsonType type) {
  Json *j = calloc(1, sizeof(Json));

  j->type = type;

  return j;
}

static void free_json(Json *j) {
  switch (j->type) {
    case Json_Null:
      break;

    case Json_String:
      free(j->string);

      break;

    case Json_Array:
      if (j->array.capacity) {
        if (j->array.count) {
          for (size_t i = 0; i < j->array.count; i++) {
            free_json(j->array.items[i]);
          }
        }

        free(j->array.items);
      }

      break;

    case Json_Object:
      if (j->object.capacity) {
        if (j->object.count) {
          for (size_t i = 0; i < j->object.count; i++) {
            free(j->object.items[i].key);
            free_json(j->object.items[i].value);
          }
        }

        free(j->object.items);
      }

      break;
  }

  free(j);
}

static void skip_whitespace(struct lexer *l) {
  do {
    l->pos++;
  } while (isspace(l->input[l->pos]));
}

static struct Token lex(struct lexer *l) {
  while (l->input[l->pos]) {
    if (isspace(l->input[l->pos])) {
      skip_whitespace(l);
    }

    switch (l->input[l->pos]) {
      case '{':
      case '}':
      case '[':
      case ']':
      case ':':
      case ',':
        l->pos++;

        return (struct Token){
          .type = l->input[l->pos - 1]
        };

      case '"':
        char *open = l->input + l->pos;

        int len = 0;

        while (open[len + 1]) {
          switch (open[len + 1]) {
            case '"':
              l->pos += len + 2;

              return (struct Token){
                .type = Token_String,
                .string = strndup(open + 1, len)
              };

            default:
              len++;
          }
        }

        return (struct Token){
          .type = Token_Invalid
        };

      default:
        fprintf(stderr, "Invalid character %c\n", l->input[l->pos]);

        return (struct Token){
          .type = Token_Invalid
        };
    }
  }

  return (struct Token){
    .type = Token_EOF
  };
}

static bool eat(struct lexer *l, enum TokenType type) {
  if (l->cur_tok.type == type) {
    l->cur_tok = lex(l);

    return true;
  }

  return false;
}

static Json *parse_value(struct lexer *l);

static Json *parse_array(struct lexer *l) {
  if (!eat(l, '[')) {
    return NULL;
  }

  Json *array = new_json(Json_Array);

  if (eat(l, ']')) {
    return array;
  }

get_value:
  Json *elem = parse_value(l);

  if (elem) {
    if (eat(l, ',')) {
      da_append(&array->array, elem);

      goto get_value;
    }

    else if (eat(l, ']')) {
      da_append(&array->array, elem);

      return array;
    }
  }

  free_json(array);

  return NULL;
}

static Json *parse_object(struct lexer *l) {
  if (!eat(l, '{')) {
    return NULL;
  }

  Json *object = new_json(Json_Object);

  if (eat(l, '}')) {
    return object;
  }

get_pair:
  struct Token string = l->cur_tok;

  if (eat(l, Token_String)) {
    if (eat(l, ':')) {
      Json *value = parse_value(l);

      if (value) {
        if (eat(l, ',')) {
          struct Key_Value kvp = {
            .key = string.string,
            .value = value
          };

          da_append(&object->object, kvp);

          goto get_pair;
        }

        else if (eat(l, '}')) {
          struct Key_Value kvp = {
            .key = string.string,
            .value = value
          };

          da_append(&object->object, kvp);

          return object;
        }
      }
    }
  }

  free_json(object);

  return NULL;
}

static Json *parse_value(struct lexer *l) {
  switch (l->cur_tok.type) {
    case '{':
      return parse_object(l);

    case '[':
      return parse_array(l);

    case Token_String:
      Json *string = new_json(Json_String);

      string->string = l->cur_tok.string;

      l->cur_tok = lex(l);

      return string;

    default:
      return NULL;
  }
}

static void fprinti(FILE *fp, int indent) {
  for (int i = 0; i < indent; i++) {
    fputc(' ', fp);
  }
}

static void fprintj_r(FILE *fp, Json *j, int indent, int depth) {
  switch (j->type) {
    case Json_Null:
      fprintf(fp, "null");

      break;

    case Json_String:
      fprintf(fp, "\"%s\"", j->string);

      break;

    case Json_Array:
      fprintf(fp, "[");

      if (j->array.count) {
        if (indent) {
          fputc('\n', fp);
          fprinti(fp, indent * (depth + 1));
        }

        fprintj_r(fp, j->array.items[0], indent, depth + 1);

        for (size_t i = 1; i < j->array.count; i++) {
          if (indent) {
            fprintf(fp, ",\n");
            fprinti(fp, indent * (depth + 1));
          }

          else {
            fprintf(fp, ", ");
          }

          fprintj_r(fp, j->array.items[i], indent, depth + 1);
        }
      }

      if (indent) {
        fputc('\n', fp);
        fprinti(fp, indent * depth);
      }

      fprintf(fp, "]");

      break;

    case Json_Object:
      fprintf(fp, "{");

      if (j->object.count) {
        if (indent) {
          fputc('\n', fp);
          fprinti(fp, indent * (depth + 1));
        }

        fprintf(fp, "\"%s\": ", j->object.items[0].key);

        fprintj_r(fp, j->object.items[0].value, indent, depth + 1);

        for (size_t i = 1; i < j->object.count; i++) {
          if (indent) {
            fprintf(fp, ",\n");
            fprinti(fp, indent * (depth + 1));
          }

          else {
            fprintf(fp, ", ");
          }

          fprintf(fp, "\"%s\": ", j->object.items[i].key);

          fprintj_r(fp, j->object.items[i].value, indent, depth + 1);
        }
      }

      if (indent) {
        fputc('\n', fp);
        fprinti(fp, indent * depth);
      }

      fprintf(fp, "}");

      break;
  }
}

void fprintj(FILE *fp, Json *j, int indent) {
  fprintj_r(fp, j, indent, 0);
}

Json *object_get(Json *o, char *k) {
  if (o->type != Json_Object) return NULL;

  if (!o->object.count) return NULL;

  for (size_t i = 0; i < o->object.count; i++) {
    if (strlen(k) == strlen(o->object.items[i].key)) {
      if (!strncmp(k, o->object.items[i].key, strlen(k))) {
        return o->object.items[i].value;
      }
    }
  }

  return NULL;
}

bool load(const char *file) {
  FILE *fp = fopen(file, "r");
  struct stat st;

  if (!fp || fstat(fileno(fp), &st) == -1) {
    fprintf(stderr, "could not read file: %s\n", file);

    if (fp) fclose(fp);

    return false;
  }

  char *buffer = calloc(st.st_size + 1, sizeof(char));

  off_t ret = fread(buffer, sizeof(char), st.st_size, fp);

  fclose(fp);

  if (ret != st.st_size) {
    fprintf(stderr, "read %zu bytes instead of %zu bytes\n", ret, st.st_size);

    free(buffer);

    return false;
  }

  struct lexer l = {
    .input = buffer,
    .pos = 0,
    .cur_tok = lex(&l)
  };

  root = parse_value(&l);

  free(buffer);

  if (!root) {
    return false;
  }

  return true;
}

bool dump(const char *file, int indent) {
  FILE *fp = fopen(file, "w");

  fprintj(fp, root, indent);

  fclose(fp);

  free_json(root);

  return true;
}
