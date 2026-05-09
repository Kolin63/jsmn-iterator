/*
   jsmn-iterator.h - from the jsmn-iterator library by Colin Melican (Kolin63)

   https://github.com/kolin63/jsmn-iterator

   Under the MIT License

   Copyright (c) 2026 Colin Melican

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
 */

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
