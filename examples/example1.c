/*
   this example iterates over user data and prints it out
   */

#include <stdio.h>
#include <string.h>

#include "jsmn_iterator.h"

// normally this would be read from a file
const char* json_str =
    "\
{\n\
  \"data_version\": 27,\n\
  \"save_date\": \"2026/05/09\",\n\
  \"users\": [ \"Colin\", \"Bob\", \"Dave\", \"John\", \"Cornelius\" ]\n\
}";

int main() {
  // parse json into jsmn tokens
  jsmn_parser parser;
  jsmntok_t tokens[128];
  jsmn_init(&parser);
  jsmn_parse(&parser, json_str, strlen(json_str), tokens, 128);

  // make iterator. we pass in the first element of tokens, meaning that we will
  // iterate over the entire json object (aka the root object)
  struct jsmn_iterator iter;
  jsmn_iterator_init(&iter, tokens, json_str);

  // iterate using the already initialized iterator
  while (jsmn_iterator_next(&iter)) {
    // here we get the string value of iter.val
    // (in jsmn, values are always represented by strings. the type is in iter.type)
    //
    // we are using jsmn_iterator_get_string() to get the string. the other
    // function we could use is jsmn_iterator_get_string_heap(), which
    // automatically determines the size needed for a string and puts it on the
    // heap.
    //
    // on the other hand, jsmn_iterator_get_string() is passed a buffer and puts
    // as much of the value string into it as it can, without overflowing the
    // buffer.
    //
    // we don't expect the length of the value string to be more than 128 chars
    // (including \0), so we make a buf of size 128
    char val[128];
    jsmn_iterator_get_string(val, 128, json_str, iter.val);

    // print the type, key, and value. the iterator stores the key as its string
    // value, so we don't need to convert that
    printf("(%s) %s: %s\n", jsmn_iterator_type_to_str(iter.val->type), iter.key, val);

    // we also want to iterate over the users array. if the key of the current
    // value is users, we make a new iterator and iterate over the array
    if (strcmp(iter.key, "users") == 0) {
      struct jsmn_iterator user_iter;
      jsmn_iterator_init(&user_iter, iter.val, json_str);

      while (jsmn_iterator_next(&user_iter)) {
        char name[128];
        jsmn_iterator_get_string(name, 128, json_str, user_iter.val);

        // rather than printing the key, we print the index. the key is null in
        // an array printing the index in this way makes it look like a
        // one-indexed array because index 0 is the root, so index 1 is the
        // first value
        printf("(%s) %i: %s\n", jsmn_iterator_type_to_str(user_iter.val->type), user_iter.i, name);
      }
    }
  }

  /*
    output:

    (JSMN_PRIMITIVE) data_version: 27
    (JSMN_STRING) save_date: 2026/05/09
    (JSMN_ARRAY) users: [ "Colin", "Bob", "Dave", "John", "Cornelius" ]
    (JSMN_STRING) 1: Colin
    (JSMN_STRING) 2: Bob
    (JSMN_STRING) 3: Dave
    (JSMN_STRING) 4: John
    (JSMN_STRING) 5: Cornelius

   */

  return 0;
}
