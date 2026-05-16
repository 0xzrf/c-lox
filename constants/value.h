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

void init_value_array(ValueArray *);
void write_value_array(ValueArray *, Value);
void free_value_array(ValueArray *);
void print_value(Value, bool);

#endif
