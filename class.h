#ifndef jolt_class_h
#define jolt_class_h

#include "common.h"
#include "constpool.h"
#include "field.h"


typedef struct {
    ConstPool cp;
    char* Name;
    char* Super;
    uint16_t Flags;
    char* Interfaces;
    Field* Fields;
    Field* Methods;
    Attribute* Attributes;
} Class;


 #endif