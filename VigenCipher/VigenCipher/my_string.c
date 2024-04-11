#include "memory_manager.h"
#include "my_string.h"

#include <stdio.h>
#include <stdlib.h>


int isDelimiter(char c)
{
    return c == ' ' || c == '\n' || c == '\t' || c == '\0';
}

int isSpaceChar(char c) {
    return (c == ' ' || c == '\n' || c == '\t' || c == '\v');
}

int isNumericChar(char c)
{
    return (c >= '0' && c <= '9');
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

void removeSubstring(char* str, int start, int length)
{
    int i = start;
    int oldLength = stringLength(str);

    while (str[i + length] != '\0')
    {
        str[i] = str[i + length];
        i++;
    }
    str[i] = '\0';

    char* newStr = reallocateMemory(str, oldLength, i + 1);
    if (newStr == NULL && i > 0)
        printf("Memory reallocation failed\n");
    else
        str = newStr;
}

int convertStringToInt(const char* str)
{
    int result = 0;
    int sign = 1;   // 1 для положительного, -1 для отрицательного

    while (isSpaceChar(*str))
        str++;

    if (*str == '-' || *str == '+') {
        sign = (*str == '-') ? -1 : 1;
        str++;
    }

    while (isNumericChar(*str)) {
        result = result * 10 + (*str - '0');
        str++;
    }

    return sign * result;
}

