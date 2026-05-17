#ifndef clox_obj_h
#define clox_obj_h

#include "../common/common.h"
#include "value.h"

#define OBJ_TYPE(value) (AS_OBJ(value)->type)
// the reason that we're not just defining the fn here itself
// is that macros evaluate their args(eg. value in this case)
// as many times as they appear in the expanded code
// meaning if the arg was something like pop(), it would call pop twice!
#define IS_STRING(value) isObjType(value, OBJ_STRING)
#define AS_STRING(value) ((ObjString *)AS_OBJ(value))
#define AS_CSTRING(value) ((ObjString *)AS_OBJ(value)->chars)

typedef enum { OBJ_STRING } ObjType;

struct Obj {
  ObjType type;
};

struct ObjString {
  Obj obj;
  int length;
  char *chars;
};

static inline bool isObjType(Value value, ObjType type) {
  return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif