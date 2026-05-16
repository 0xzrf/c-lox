#ifndef clox_common_h
#define clox_common_h

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define DEBUG_TRACE_EXECUTION
#define DEBUG_PRINT_CODE
#define DEBUG_COMPILE_LOGS

#include "../logs/logs.h"

#define INFINITE_LOOP for (;;)

typedef enum {
  RUNTIME_ERROR_CODE = 70,
  COMPILATION_ERROR_CODE = 65,
  INVALID_CMD_ARGS = 64,
  FILE_POINTER_NULL = 74,
  MALLOC_ERR = 75,
  INVALID_READ = 76,
  MAIN_SUCCESS = 0
} Errors;

#endif
