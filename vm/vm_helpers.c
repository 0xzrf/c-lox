#include "vm_helpers.h"

void _negate_last_stack_var(VM *vm) {
  *(vm->stack_top - 1) = NUMBER_VAL(-AS_NUMBER(*(vm->stack_top - 1)));
}
