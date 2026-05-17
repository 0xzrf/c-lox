#include "value.h"
#include "../common/memory.h"
#include "obj.h"
#include "string.h"
#include <stdio.h>
#include <string.h>

void init_value_array(ValueArray *array) {
  array->count = 0;
  array->capacity = 0;
  array->value = NULL;
}

void write_value_array(ValueArray *array, Value value) {
  if (array->capacity < array->count + 1) {
    int old_cap = array->capacity;
    array->capacity = GROW_CAPACITY(old_cap);
    array->value = GROW_ARRAY(Value, array->value, old_cap, array->capacity);
  }

  array->value[array->count++] = value;
}

void free_value_array(ValueArray *array) {
  FREE_ARRAY(Value, array->value, array->capacity);
  init_value_array(array);
}

void print_value(Value value, bool nl) {
  switch (value.type) {
  case VAL_BOOL:
    printf(AS_BOOL(value) ? "true" : "false");
    break;
  case VAL_NIL:
    printf("nil");
    break;
  case VAL_NUM:
    printf("%g", AS_NUMBER(value));
    break;
  case VAL_OBJ:
    print_object(value);
    break;
  }
  if (nl) {
    printf("\n");
  }
}

static bool values_equal(Value a, Value b) {
  if (a.type != b.type)
    return false;

  switch (a.type) {
  case VAL_BOOL:
    return AS_BOOL(a) == AS_BOOL(b);
  case VAL_NIL:
    return true; // both are def. equals
  case VAL_NUM:
    return AS_NUMBER(a) == AS_NUMBER(b);
  case VAL_OBJ:
    ObjString *string_a = AS_STRING(a);
    ObjString *string_b = AS_STRING(b);
    return string_a->length == string_b->length &&
           memcmp(string_a, string_b, string_a->length) == 0;
  }
}