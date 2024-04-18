#include "memory_manager.h"
#include "my_string.h"

#include <stdio.h>
#include <stdlib.h>


#define LETTERS_COUNT 4


char toUpperCase(char ch)
{
    if (ch >= 'a' && ch <= 'z')
        return ch - 'a' + 'A';

    return ch;
}

char* allocateString(int length)
{
    char* str = (char*)malloc((length + 1) * sizeof(char));
    if (str == NULL) {
        printf("Memory allocation error!");
        return NULL;
    }
    str[0] = '\0';
    return str;
}

int stringLength(const char* str)
{
    int length = 0;
    while (str[length] != '\0')
        length++;
    return length;
}

int myStrNCmp(const char* str1, const char* str2, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (str1[i] != str2[i])
            return 0;

        if (str1[i] == '\0')
            break;
    }
    return 1;
}

void copyString(char* dest, const char* src, int n)
{
    for (int i = 0; i < n; i++)
    {
        dest[i] = src[i];
        if (src[i] == '\0')
            break;
    }
}

char* readLine() {
    char* buffer = malloc(LETTERS_COUNT);
    if (buffer == NULL) {
        printf("Failed to allocate memory\n");
        return NULL;
    }

    int capacity = LETTERS_COUNT;
    int length = 0;
    char ch = getchar();

    while (ch != '\n' && ch != EOF) {
        buffer[length++] = ch;

        if (length == capacity)
        {
            capacity *= 2;
            char* temp = reallocateMemory(buffer, length, capacity);
            if (temp == NULL) {
                printf("Failed to reallocate memory\n");
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }

        ch = getchar();
    }

    buffer[length] = '\0';

    char* temp = realloc(buffer, capacity, length + 1);
    if (temp == NULL)
        return buffer;

    return temp;
}

