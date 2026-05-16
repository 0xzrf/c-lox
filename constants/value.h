#ifndef clox_value_h
#define clox_value_h

#include "../common/common.h"

typedef enum { VAL_BOOL, VAL_NIL, VAL_NUM } ValueType;

typedef struct {
  ValueType type;
  union {
    bool boolean;
    double number;
  } as;
} Value;

typedef struct {
  int count;
  int capacity;
  Value *value;
} ValueArray;

#define IS_BOOL(value) ((value).type == VAL_BOOL)
#define IS_NIL(value) ((value).type == VAL_NIL)
#define IS_NUM(value) ((value).type == VAL_NUM)

#define AS_BOOL(value) ((value).as.boolean)
#define AS_NUMBER(value) ((value).as.number)

#define BOOL_VAL(value) ((Value){VAL_BOOL, {.boolean = value}})
#define NIL_VAL ((Value){VAL_NIL, {.number = 0}})
#define NUMBER_VAL(value) ((Value){VAL_NUM, {.number = value}})

void init_value_array(ValueArray *);
void write_value_array(ValueArray *, Value);
void free_value_array(ValueArray *);
void print_value(Value, bool);

#endif
