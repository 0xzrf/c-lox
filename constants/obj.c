#include <stdio.h>
#include <string.h>

#include "../vm/vm.h"
#include "memory.h"
#include "obj.h"
#include "value.h"

#define ALLOCATE_OBJ(type, objectType)                                         \
  (type *)allocate_object(sizeof(type), objectType)

ObjString *copy_string(const char *str, int len) {
  char *heapChars = ALLOCATE(char, len + 1);
  memcpy(heapChars, str, len);
  heapChars[len] = '\0';
  return allocate_string(heapChars, len);
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