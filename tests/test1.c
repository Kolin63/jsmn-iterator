#include <stdio.h>
#include <string.h>

#include "jsmn_iterator.h"
#include "jsmn.h"

static int tests_passed = 0;
static int tests_total = 0;

void equals_check_int(int x, int y, const char* file, int line) {
  tests_total++;
  if (x == y) {
    printf("\e[0;92m%s:%i: Equality: %i == %i\e[0m\n", file, line, x, y);
    tests_passed++;
  } else {
    printf("\e[0;91m%s:%i: Inequality: %i != %i\e[0m\n", file, line, x, y);
  }
}

void equals_check_string(const char* x, const char* y, const char* file, int line) {
  tests_total++;
  if ((x == NULL && y != NULL) || (y == NULL && x != NULL)) {
    printf("\e[0;91m%s:%i: Inequality: %p != %p\e[0m\n", file, line, x, y);
  } else if (x == y) {
    printf("\e[0;92m%s:%i: Equality: %p == %p\e[0m\n", file, line, x, y);
    tests_passed++;
  } else if (strcmp(x, y) == 0) {
    printf("\e[0;92m%s:%i: Equality: %s == %s\e[0m\n", file, line, x, y);
    tests_passed++;
  } else {
    printf("\e[0;91m%s:%i: Inequality: %s != %s\e[0m\n", file, line, x, y);
  }
}

void iter_check(const struct jsmn_iterator* iter, const char* valstr,
                const jsmntype_t type, const char* key, const char* val,
                const char* file, const int line) {
  equals_check_int(type, iter->type, file, line);
  equals_check_string(key, iter->key, file, line);
  equals_check_string(val, valstr, file, line);
}

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

  for (int i = 0; i < used; i++) {
    const jsmntok_t* tok = tokens + i;
    if (tok == NULL) break;
    printf("%i: %s size %i start %i end %i\n",
           i, jsmn_iterator_type_to_str(tok->type), tok->size, tok->start, tok->end);
  }

  struct jsmn_iterator iter;
  jsmn_iterator_init(&iter, tokens + 0, content);

  struct jsmn_iterator subiter;

  char val[128];

  equals_check_int(jsmn_iterator_next(&iter), 1, __FILE_NAME__, __LINE__);
  jsmn_iterator_get_string(val, 128, iter.json, iter.val);
  iter_check(&iter, val, JSMN_STRING, "name", "colin", __FILE_NAME__, __LINE__);

  equals_check_int(jsmn_iterator_next(&iter), 1, __FILE_NAME__, __LINE__);
  jsmn_iterator_get_string(val, 128, iter.json, iter.val);
  iter_check(&iter, val, JSMN_STRING, "foo", "bar", __FILE_NAME__, __LINE__);

  equals_check_int(jsmn_iterator_next(&iter), 1, __FILE_NAME__, __LINE__);
  jsmn_iterator_get_string(val, 128, iter.json, iter.val);
  iter_check(&iter, val, JSMN_OBJECT, "zap", "{\n    \"bob\": \"frank\",\n    \"dave\": \"bowman\",\n  }",
             __FILE_NAME__, __LINE__);

  jsmn_iterator_init(&subiter, iter.val, content);

  equals_check_int(jsmn_iterator_next(&subiter), 1, __FILE_NAME__, __LINE__);
  jsmn_iterator_get_string(val, 128, subiter.json, subiter.val);
  iter_check(&subiter, val, JSMN_STRING, "bob", "frank", __FILE_NAME__, __LINE__);

  equals_check_int(jsmn_iterator_next(&subiter), 1, __FILE_NAME__, __LINE__);
  jsmn_iterator_get_string(val, 128, subiter.json, subiter.val);
  iter_check(&subiter, val, JSMN_STRING, "dave", "bowman", __FILE_NAME__, __LINE__);

  equals_check_int(jsmn_iterator_next(&subiter), 0, __FILE_NAME__, __LINE__);

  equals_check_int(jsmn_iterator_next(&iter), 1, __FILE_NAME__, __LINE__);
  jsmn_iterator_get_string(val, 128, iter.json, iter.val);
  iter_check(&iter, val, JSMN_PRIMITIVE, "baz", "26", __FILE_NAME__, __LINE__);

  equals_check_int(jsmn_iterator_next(&iter), 1, __FILE_NAME__, __LINE__);
  jsmn_iterator_get_string(val, 128, iter.json, iter.val);
  iter_check(&iter, val, JSMN_ARRAY, "bop", "[ 2, 3, 5, 7, 11, 13 ]", __FILE_NAME__, __LINE__);

  jsmn_iterator_init(&subiter, iter.val, content);

  equals_check_int(jsmn_iterator_next(&subiter), 1, __FILE_NAME__, __LINE__);
  jsmn_iterator_get_string(val, 128, subiter.json, subiter.val);
  iter_check(&subiter, val, JSMN_PRIMITIVE, NULL, "2", __FILE_NAME__, __LINE__);

  equals_check_int(jsmn_iterator_next(&subiter), 1, __FILE_NAME__, __LINE__);
  jsmn_iterator_get_string(val, 128, subiter.json, subiter.val);
  iter_check(&subiter, val, JSMN_PRIMITIVE, NULL, "3", __FILE_NAME__, __LINE__);

  equals_check_int(jsmn_iterator_next(&subiter), 1, __FILE_NAME__, __LINE__);
  jsmn_iterator_get_string(val, 128, subiter.json, subiter.val);
  iter_check(&subiter, val, JSMN_PRIMITIVE, NULL, "5", __FILE_NAME__, __LINE__);

  equals_check_int(jsmn_iterator_next(&subiter), 1, __FILE_NAME__, __LINE__);
  jsmn_iterator_get_string(val, 128, subiter.json, subiter.val);
  iter_check(&subiter, val, JSMN_PRIMITIVE, NULL, "7", __FILE_NAME__, __LINE__);

  equals_check_int(jsmn_iterator_next(&subiter), 1, __FILE_NAME__, __LINE__);
  jsmn_iterator_get_string(val, 128, subiter.json, subiter.val);
  iter_check(&subiter, val, JSMN_PRIMITIVE, NULL, "11", __FILE_NAME__, __LINE__);

  equals_check_int(jsmn_iterator_next(&subiter), 1, __FILE_NAME__, __LINE__);
  jsmn_iterator_get_string(val, 128, subiter.json, subiter.val);
  iter_check(&subiter, val, JSMN_PRIMITIVE, NULL, "13", __FILE_NAME__, __LINE__);

  equals_check_int(jsmn_iterator_next(&subiter), 0, __FILE_NAME__, __LINE__);

  equals_check_int(jsmn_iterator_next(&iter), 1, __FILE_NAME__, __LINE__);
  jsmn_iterator_get_string(val, 128, iter.json, iter.val);
  iter_check(&iter, val, JSMN_PRIMITIVE, "zip", "51", __FILE_NAME__, __LINE__);

  equals_check_int(jsmn_iterator_next(&iter), 0, __FILE_NAME__, __LINE__);

  if (tests_passed == tests_total) {
    printf("\n\e[0;102m\e[1;30m\e[4;30mAll Tests Passed (%i/%i)\e[0m\n",
           tests_passed, tests_total);
    return 0;
  } else {
    printf("\n\e[0;101m\e[1;30m\e[4;30mFailed Tests (%i/%i)\e[0m\n",
           tests_passed, tests_total);
    return tests_total - tests_passed;
  }
}
