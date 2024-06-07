#include "text_file_manager.h"

#include "string_manager.h"
#include "memory_manager.h"
#include "common.h"

#include <stdlib.h>
#include <stdio.h>


#define DELIMITER "\n==================================================================\n"

#define SAMPLE_FILES_COUNT 3
#define MAX_WORD_LENGTH 255


const char* sampleFilePaths[SAMPLE_FILES_COUNT] =
{
    "Data\\SampleText1.txt",
    "Data\\SampleText2.txt",
    "Data\\SampleText3.txt"
};
const char* resultFilePath = "Data\\ResultText.txt";


FILE* openFile(char* filePath, char* mode)
{
    FILE* file;
    if (fopen_s(&file, filePath, mode) != 0)
    {
        printf("Error opening the file %s\n", filePath);
        exit(EXIT_FAILURE);
    }
    return file;
}

void printDataFromFile(const char* filePath)
{
    FILE* file = openFile(filePath, "r");

    char** fileContent = readDataFromFile(file);
    if (fileContent != NULL)
    {
        printf("Text:\n%s\n", fileContent[0]);
        printf("Key: %s%s\n", fileContent[1], DELIMITER);

        free(fileContent[0]);
        free(fileContent[1]);
        free(fileContent);
    }
    else
        printf("Failed to read data from file\n");

    fclose(file);
}

void printSampleDataFromFiles()
{
    printf("Sample Arrays:\n%s", DELIMITER);
    for (int i = 0; i < SAMPLE_FILES_COUNT; i++)
        printDataFromFile(sampleFilePaths[i]);
    printf("\n");
}

char** readDataFromFile(FILE* file)
{
    char** result = (char**)safeMemoryAllocate(2 * sizeof(char*));

    result[0] = readTextFromFile(file);
    result[1] = readWordFromFile(file);

    return result;
}

void writeTextToResultFile(const char* text)
{
    FILE* file = openFile(resultFilePath, "w");

    if (fputs(text, file) == EOF)
        printf("Error writing to the file %s\n", resultFilePath);
    else
        printf("Text written successfully to %s\n", resultFilePath);

    fclose(file);
}

char* chooseArrayFilePath()
{
    printf("Enter the file number (1-3) or 4 for manualy input: ");
    int choice;

    while (1)
    {
        choice = inputIntegerNumberInRange(1, SAMPLE_FILES_COUNT + 1);
        if (choice == 4)
            return NULL;
        return sampleFilePaths[choice - 1];
    }
}
