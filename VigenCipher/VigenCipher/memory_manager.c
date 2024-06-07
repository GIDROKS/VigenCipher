#include "memory_manager.h"

#include <stdio.h>


#define MEMORY_REDUCTION_THRESHOLD 256


void* safeMemoryAllocate(size_t size)
{
    void* ptr = malloc(size);
    if (ptr == NULL)
    {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void copyMemory(void* dest, const void* src, size_t size)
{
    char* destBytes = (char*)dest;
    const char* srcBytes = (const char*)src;

    for (size_t i = 0; i < size; i++)
        destBytes[i] = srcBytes[i];
}

static void* reallocateMemory(void* currentPtr, size_t oldSize, size_t newSize)
{
    if (newSize == 0)
    {
        free(currentPtr);
        return NULL;
    }

    if (!currentPtr)
        return malloc(newSize);

    if (newSize == oldSize)
        return currentPtr;

    if (newSize < oldSize && (oldSize - newSize) > MEMORY_REDUCTION_THRESHOLD)
    {
        void* newPtr = malloc(newSize);
        if (newPtr)
        {
            copyMemory(newPtr, currentPtr, newSize);
            free(currentPtr);
            return newPtr;
        }
        return NULL;
    }

    if (newSize > oldSize)
    {
        void* newPtr = malloc(newSize);
        if (!newPtr)
            return NULL;
        copyMemory(newPtr, currentPtr, oldSize);
        free(currentPtr);
        return newPtr;
    }

    return currentPtr;
}

void* safeReallocateMemory(void* currentPtr, size_t oldSize, size_t newSize)
{
    void* newPtr = reallocateMemory(currentPtr, oldSize, newSize);
    if (!newPtr && newSize != 0)
    {
        fprintf(stderr, "Error: Failed to reallocate memory!\n");
        free(currentPtr);
        exit(EXIT_FAILURE);
    }
    return newPtr;
}