# JSMN Iterator
A 2-file C99 library that implements an easy to use iterator for
[JSMN](https://github.com/zserge/jsmn).

**Contents**
- [Usage](#usage)
- [Examples](#examples)
- [Documentation](#documentation)
  - [struct jsmn_iterator](#struct-jsmn_iterator)
  - [jsmn_iterator_get_string()](#jsmn_iterator_get_string)
  - [jsmn_iterator_get_string_heap()](#jsmn_iterator_get_string_heap)
  - [jsmn_iterator_type_to_str()](#jsmn_iterator_type_to_str)
  - [jsmn_iterator_init()](#jsmn_iterator_init)
  - [jsmn_iterator_next()](#jsmn_iterator_next)

## Usage
You can add `src/jsmn-iterator.c` and `src/jsmn-iterator.h` to your project
(this code is under the MIT License).

Alternatively, you can build the library from source using CMake. Then, put
`src/jsmn-iterator.h` in an include directory and `libjsmn-iterator.a` in a lib
directory.

## Examples
This can also be found in the examples folder.
```c
// TODO
```

## Documentation
### struct jsmn_iterator
```c
struct jsmn_iterator {
  // type of value
  jsmntype_t type;

  // index of value. first value is 0
  unsigned int i;

  // string value of key. NULL if root is an array
  char* key;

  // token of value. to get string value, use jsmn_iterator_get_string() or
  // jsmn_iterator_get_string_heap()
  const jsmntok_t* val;

  // token of root object / array
  const jsmntok_t* root;

  // string of json content. the same string that is passed to jsmn_parse()
  const char* json;
};
```
used to iterate through JSMN tokens. initialized with jsmn_iterator_init(). do
not write to any of these fields

### jsmn_iterator_get_string()
```c
void jsmn_iterator_get_string(char* buf, unsigned long size, const char* json, const jsmntok_t* tok);
```
gets the string value of a JSMN token and puts it in a string buffer. size is
the length of the buffer, including the null terminator. json is the string of
the json content, and the same string that is passed to `jsmn_parse()`

### jsmn_iterator_get_string_heap()
```c
char* jsmn_iterator_get_string_heap(const char* json, const jsmntok_t* tok);
```
gets the string value of a JSMN token and puts it on the heap. the string must
be freed after use. json is the string of the json content, and the same string
that is passed to jsmn_parse()

### jsmn_iterator_type_to_str()
```c
const char* jsmn_iterator_type_to_str(jsmntype_t type);
```
converts JSMN integer error code into a string return values:
      0: "JSMN_UNDEFINED"
      1: "JSMN_OBJECT"
      2: "JSMN_ARRAY"
      4: "JSMN_STRING"
      8: "JSMN_PRIMITIVE"
default: "ERROR - NOT A TYPE"

### jsmn_iterator_init()
```c
void jsmn_iterator_init(struct jsmn_iterator* iter, const jsmntok_t* root, const char* json);
```
root is the root object/array to iterate over. json is the string of the json
content, and the same string that is passed to jsmn_parse()

### jsmn_iterator_next()
```c
int jsmn_iterator_next(struct jsmn_iterator* iter);
```
iterates to next value. returns 1 if iteration can continue, and 0 if not
