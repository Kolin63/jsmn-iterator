#ifndef KOLIN_JSMN_ITERATOR_H_
#define KOLIN_JSMN_ITERATOR_H_

#define JSMN_STATIC
#include "jsmn.h"

struct jsmn_iterator {
  jsmntype_t type;
  unsigned int i;
  char* key;
  const jsmntok_t* val;

  const jsmntok_t* root;
  const char* json;
};

void jsmn_iterator_get_string(char* buf, unsigned long size, const char* json, const jsmntok_t* tok);
char* jsmn_iterator_get_string_heap(const char* json, const jsmntok_t* tok);

const char* jsmn_iterator_type_to_str(int err);

void jsmn_iterator_init(struct jsmn_iterator* iter, const jsmntok_t* root, const char* json);
int jsmn_iterator_next(struct jsmn_iterator* iter);

#endif
