#include <stdio.h>


#ifndef TEXT_FILE_MANAGER_H
#define TEXT_FILE_MANAGER_H

void printDataFromFile(const char* filePath);
void writeTextToResultFile(const char* text);
FILE* openFile(char* filePath, char* mode);
char** readDataFromFile(FILE* file);
void printSampleDataFromFiles();
char* chooseArrayFilePath();

#endif