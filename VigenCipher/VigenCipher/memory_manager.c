#include "memory_manager.h"

#include <stdio.h>


void copyMemory(void* dest, const void* src, size_t n)
{
    char* destBytes = (char*)dest;
    const char* srcBytes = (const char*)src;

    for (size_t i = 0; i < n; i++)
        destBytes[i] = srcBytes[i];
}


void* reallocateMemory(void* currentPtr, size_t oldSize, size_t newSize)
{
    if (newSize == 0) {
        free(currentPtr);
        return NULL;
    }

    if (!currentPtr)
        return malloc(newSize);

    if (newSize <= oldSize)
        return currentPtr;


    void* newPtr = malloc(newSize);
    if (!newPtr)
        return NULL;

    size_t sizeToCopy = oldSize < newSize ? oldSize : newSize;
    copyMemory(newPtr, currentPtr, sizeToCopy);

    free(currentPtr);

    return newPtr;
}
