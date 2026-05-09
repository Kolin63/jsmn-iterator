#include <stdio.h>
#include <string.h>

#include "jsmn-iterator.h"
#include "jsmn.h"

const char* content =
    "\
{\n\
  \"name\": \"colin\",\n\
  \"foo\": \"bar\",\n\
  \"zap\": {\n\
    \"bob\": \"frank\",\n\
    \"dave\": \"bowman\",\n\
  },\n\
  \"baz\": 26,\n\
  \"bop\": [ 2, 3, 5, 7, 11, 13 ],\n\
  \"zip\": 51\n\
}";

int main() {
  printf("%s\n", content);

  jsmn_parser parser;
  jsmntok_t tokens[128];
  jsmn_init(&parser);

  const int used = jsmn_parse(&parser, content, strlen(content), tokens, 128);

  switch (used) {
  case JSMN_ERROR_NOMEM:
    printf("JSMN_ERROR_NOMEM - not enough tokens, JSON string is too large\n");
    return used;
  case JSMN_ERROR_INVAL:
    printf("JSMN_ERROR_INVAL - bad token, JSON string is corrupted\n");
    return used;
  case JSMN_ERROR_PART:
    printf("JSMN_ERROR_PART - JSON string is too short, expecting more JSON data\n");
    return used;
  default:
    printf("No error\n");
    break;
  }

  for (int i = 0; i < used; i++) {
    const jsmntok_t* tok = tokens + i;
    if (tok == NULL) break;
    printf("%i: %s size %i start %i end %i\n",
           i, jsmn_iterator_type_to_str(tok->type), tok->size, tok->start, tok->end);
  }

  struct jsmn_iterator iter;
  jsmn_iterator_init(&iter, tokens + 0, content);

  while (jsmn_iterator_next(&iter)) {
    char val[128];
    jsmn_iterator_get_string(val, 128, iter.json, iter.val);
    printf("%i: (%s) %s = %s\n", iter.i, jsmn_iterator_type_to_str(iter.type), iter.key, val);
  }

  return 0;
}
