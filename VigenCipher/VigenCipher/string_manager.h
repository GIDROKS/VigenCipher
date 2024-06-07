#include <stdio.h>

#ifndef STRING_MANAGER_H
#define STRING_MANAGER_H

char toLowerCase(char ch);

char* enterLineFromConsole(void);
char* enterWordFromConsole(void);
char* enterTextFromConsole(void);

char* readLineFromFile(FILE* file);
char* readWordFromFile(FILE* file);
char* readTextFromFile(FILE* file);

int compareStrings(const char* str1, const char* str2);
int stringLength(const char* str);

char* duplicateString(const char* str);
char* allocateString(int length);

#endif 