#ifndef jolt_compiler_h
#define jolt_compiler_h

#include "vm.h"

void compiler(const char* source);
void parse(const char* source);
bool isCompiled(const char* source, Chunk* chunk);

#endif
