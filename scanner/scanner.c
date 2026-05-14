#include <stdio.h>
#include <string.h>

#include "../common/common.h"
#include "scanner.h"

Scanner scanner;

void init_scanner(char* source) {
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}
