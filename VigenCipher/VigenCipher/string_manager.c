#include "memory_manager.h"
#include "string_manager.h"

#include <stdio.h>


#define START_BUFFER_SIZE 4


char toLowerCase(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
        return ch - 'A' + 'a';

    return ch;
}

char* allocateString(int length)
{
    char* str = (char*)safeMemoryAllocate((length + 1) * sizeof(char));
    return str;
}

int stringLength(const char* str)
{
    int length = 0;
    while (str[length] != '\0')
        length++;
    return length;
}

int compareStrings(const char* str1, const char* str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return (unsigned char)*str1 - (unsigned char)*str2;
}

char* duplicateString(const char* str)
{
    int len = stringLength(str) + 1;
    char* copy = safeMemoryAllocate(len);
    if (copy)
        copyMemory(copy, str, len);
    return copy;
}

static char* manageBuffer(char* buffer, int currentLength, int* capacity)
{
    if (currentLength == *capacity)
    {
        *capacity *= 2;
        char* temp = safeReallocateMemory(buffer, currentLength, *capacity);
        if (temp == NULL)
        {
            printf("Failed to reallocate memory\n");
            free(buffer);
            return NULL;
        }
        buffer = temp;
    }

    return buffer;
}

static char* readStringFromInputStream(FILE* stream, int readingMode)
{
    char* buffer = allocateString(START_BUFFER_SIZE);
    int capacity = START_BUFFER_SIZE;
    int length = 0;
    char ch = getc(stream);
    int isPrevCharScipLine = 0;

    while (ch != EOF)
    {
        switch (readingMode)
        {
        case 0:
            if (ch == ' ' || ch == '\n')
                goto exit_loop;
        case 1:
            if (ch == '\n')
                goto exit_loop;
        case 2:
            if (ch == '\n')
            {
                if (isPrevCharScipLine)
                    goto exit_loop;
                else
                    isPrevCharScipLine = 1;
            }
            else
                isPrevCharScipLine = 0;
            break;
        }

        buffer[length++] = ch;
        buffer = manageBuffer(buffer, length, &capacity);
        if (buffer == NULL)
            return NULL;

        ch = getc(stream);
    }

exit_loop:
    buffer[length] = '\0';

    char* temp = safeReallocateMemory(buffer, capacity, length + 1);
    if (temp == NULL)
        return buffer;

    return temp;
}


char* enterWordFromConsole(void)
    { return readStringFromInputStream(stdin, 0); }

char* enterLineFromConsole(void)
    { return readStringFromInputStream(stdin, 1); }

char* enterTextFromConsole(void)
    { return readStringFromInputStream(stdin, 2); }

char* readWordFromFile(FILE* file)
    { return readStringFromInputStream(file, 0); }

char* readLineFromFile(FILE* file)
    { return readStringFromInputStream(file, 1); }

char* readTextFromFile(FILE* file)
    { return readStringFromInputStream(file, 2); }

