#include "memory_manager.h"
#include "my_string.h"

#include <stdio.h>
#include <stdlib.h>


#define START_BUFFER_SIZE 4


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

static char* manageBuffer(char* buffer, int currentLength, int* capacity){
    if (currentLength == *capacity)
    {
        *capacity *= 2;
        char* temp = reallocateMemory(buffer, currentLength, *capacity);
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

char* readLine()
{
    char* buffer = malloc(START_BUFFER_SIZE);
    if (buffer == NULL)
    {
        printf("Failed to allocate memory\n");
        return NULL;
    }

    int capacity = START_BUFFER_SIZE;
    int length = 0;
    char ch = getc(stdin);

    while (ch != '\n' && ch != EOF)
    {
        buffer[length++] = ch;
        buffer = manageBuffer(buffer, length, &capacity);
        if (buffer == NULL) 
            return NULL;

        ch = getc(stdin);
    }

    buffer[length] = '\0';

    char* temp = reallocateMemory(buffer, capacity, length + 1);
    if (temp == NULL)
        return buffer;

    return temp;
}

