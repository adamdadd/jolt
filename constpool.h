#ifndef jolt_constpool_h
#define jolt_constpool_h

#include "common.h"


typedef enum {
    ClassIndex,
    NameIndex,
    FieldAndMethod,
    NameAndType,
    StringIndex,
    DescIndex,
    String,
} TagCode;

typedef struct {
    TagCode Tag;
    uint16_t NameIndex;
    uint16_t ClassIndex;
    uint16_t NameAndTypeIndex;
    uint16_t StringIndex;
    uint16_t DescIndex;
    char String[256];
} Const;

typedef struct {
    int count;
    int capacity;
    Const* constants;
} ConstPool;

void initConstPool(ConstPool* cp);
void writeConstPool(ConstPool* cp, Const value);
void freeConstPool(ConstPool* cp);
char* getConstPoolString(ConstPool* cp, uint16_t index);

#endif
