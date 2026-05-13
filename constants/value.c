#include <stdio.h>
#include "value.h"
#include "../common/memory.h"

void init_value_array(ValueArray* array) {
    array->count = 0;
    array->capacity = 0;
    array->value = NULL;
}

void write_value_array(ValueArray * array, Value value) {
    if (array->capacity < array->count + 1) {
        int old_cap = array->capacity;
        array->capacity = GROW_CAPACITY(old_cap);
        array->value = GROW_ARRAY(Value, array->value, old_cap, array->capacity);
    }

    array->value[array->count++] = value;
}

void free_value_array(ValueArray* array) {
    FREE_ARRAY(Value, array->value, array->capacity);
    init_value_array(array);
}

void print_value(Value value, bool nl) {
    printf("%g", value);
    if (nl) {
        printf("\n");
    }
}
