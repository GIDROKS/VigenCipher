#include <stdlib.h>

#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

void* safeMemoryAllocate(size_t size);
void copyMemory(void* dest, const void* src, size_t n);
void* safeReallocateMemory(void* currentPtr, size_t oldSize, size_t newSize);

#endif