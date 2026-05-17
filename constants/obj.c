#include <stdio.h>
#include <string.h>

#include "../common/memory.h"
#include "obj.h"
#include "value.h"

#define ALLOCATE_OBJ(type, objectType)                                         \
  (type *)allocate_object(sizeof(type), objectType)

ObjString *copy_string(const char *str, int len) {
  char *heap_chars = ALLOCATE(char, len - 1);
  memcpy(heap_chars, str, len);
  heap_chars[len] = '\0';
  return allocate_string(heap_chars, len);
}

static ObjString *allocate_string(char *chars, int length) {
  ObjString *string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
  string->length = length;
  string->chars = chars;
  return string;
}

static Obj *allocate_object(size_t size, ObjType type) {
  Obj *object = (Obj *)reallocate(NULL, 0, size);
  object->type = type;
  return object;
}

void print_object(Value value) {
  switch (OBJ_TYPE(value)) {
  case OBJ_STRING:
    printf("%s", AS_CSTRING(value));
    break;
  }
}