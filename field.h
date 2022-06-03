#ifndef jolt_field_h
#define jolt_field_h

#include "common.h"


typedef struct {
    char* Name;
    char* Data;
} Attribute;

typedef struct {
    uint16_t Flags;
    char* Name;
    char* Descriptor;
    Attribute* Attributes;
} Field;


#endif