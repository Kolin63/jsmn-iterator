#include "jsmn-iterator.h"

#include <stdlib.h>
#include <string.h>

#define JSMN_HEADER
#include "jsmn.h"

void jsmn_iterator_get_string(char* buf, unsigned long size, const char* json, const jsmntok_t* tok) {
  unsigned long len = tok->end - tok->start + 1;
  if (len > size) len = size;
  for (unsigned long i = 0; i < len - 1; i++) {
    buf[i] = json[tok->start + i];
  }
  buf[len - 1] = '\0';
}

char* jsmn_iterator_get_string_heap(const char* json, const jsmntok_t* tok) {
  const unsigned long len = tok->end - tok->start + 1;
  char* str = malloc(len);
  jsmn_iterator_get_string(str, len, json, tok);
  return str;
}

const char* jsmn_iterator_type_to_str(int err) {
  switch (err) {
  case (0):
    return "JSMN_UNDEFINED";
  case (1 << 0):
    return "JSMN_OBJECT";
  case (1 << 1):
    return "JSMN_ARRAY";
  case (1 << 2):
    return "JSMN_STRING";
  case (1 << 3):
    return "JSMN_PRIMITIVE";
  }
  return "ERROR - NOT A TYPE";
}

int jsmn_iterator_get_size_recursive(const jsmntok_t* root) {
  int size = 0;
  const jsmntok_t* tok = root + 1;

  for (int i = 0; i < root->size; i++) {
    int diff = jsmn_iterator_get_size_recursive(tok);
    tok += 1 + diff;
    size += 1 + diff;
  }
  return size;
}

void jsmn_iterator_init(struct jsmn_iterator* iter, const jsmntok_t* root, const char* json) {
  iter->type = root->type;
  iter->i = 0;
  iter->key = NULL;
  iter->val = NULL;

  iter->root = root;
  iter->json = json;
}

int jsmn_iterator_next(struct jsmn_iterator* iter) {
  if (iter->key != NULL) {
    free(iter->key);
    iter->key = NULL;
  }

  if (iter->i >= iter->root->size) return 0;
  iter->i++;

  // if it's an object (not an array) the values have keys
  if (iter->root->type == JSMN_OBJECT) {
    const jsmntok_t* key;
    if (iter->val == NULL) {
      key = iter->root + 1;
    } else {
      key = iter->val + 1 + jsmn_iterator_get_size_recursive(iter->val);
    }
    iter->key = jsmn_iterator_get_string_heap(iter->json, key);
    iter->val = key + 1;
  } else if (iter->root->type == JSMN_ARRAY) {
    // otherwise, root is an array, so no key
    iter->key = NULL;
    iter->val += 1 + jsmn_iterator_get_size_recursive(iter->val);
  }

  iter->type = iter->val->type;

  return 1;
}
