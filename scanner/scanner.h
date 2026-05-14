#ifndef clox_scanner_h
#define clox_scanner_h

void init_scanner(char*);

typedef struct {
    char* start;
    char* current;
    int line;
} Scanner;


#endif
