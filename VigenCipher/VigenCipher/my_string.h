#ifndef MY_STRING_H
#define MY_STRING_H

char* readLine();

char toUpperCase(char ch);

char* allocateString(int length);

int stringLength(const char* str);

void copyString(char* dest, const char* src, int n);

int myStrNCmp(const char* str1, const char* str2, int n);

#endif 