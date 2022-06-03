
#include "memory.h"
#include "constpool.h"

void initConstPool(ConstPool* cp) {
    cp->constants = NULL;
    cp->count = 0;
    cp->capacity = 0;
}

void writeConstPool(ConstPool* cp, Const value) {
  if (cp->capacity < cp->count + 1) {
    int oldCapacity = cp->capacity;
    cp->capacity = GROW_CAPACITY(oldCapacity, value);
    cp->constants = GROW_ARRAY(Const, cp->constants, oldCapacity, cp->capacity);
  }

  cp->constants[cp->count] = value;
  cp->count++;
}

void freeConstPool(ConstPool* cp) {
  FREE_ARRAY(Const, cp->constants, cp->capacity);
  initConstPool(cp);
}

char* getConstPoolString(ConstPool* cp, uint16_t index) {
  Const c = cp->constants[index - 1];
  switch (c.Tag) {
    case String: return c.String;
    case NameIndex: return getConstPoolString(cp, c.NameIndex);
    default: return c.Tag;
  }
}
