#include <stdlib.h>

#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

void copyMemory(void* dest, const void* src, size_t n);
void* reallocateMemory(void* currentPtr, size_t oldSize, size_t newSize);

#endif