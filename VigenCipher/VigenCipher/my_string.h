#ifndef MY_STRING_H
#define MY_STRING_H

int isDelimiter(char c);

char* allocateString(int length);

int stringLength(const char* str);

int convertStringToInt(const char* str);

void copyString(char* dest, const char* src, int n);

void removeSubstring(char* str, int start, int length);

int myStrNCmp(const char* str1, const char* str2, int n);

#endif 