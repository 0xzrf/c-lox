#ifndef clox_value_h
#define clox_value_h

#include "../common/common.h"

typedef double Value;

typedef struct {
    int count;
    int capacity;
    Value* value;
} ValueArray;

void init_value_array(ValueArray*);
void write_value_array(ValueArray*, Value);
void free_value_array(ValueArray*);

#endif
