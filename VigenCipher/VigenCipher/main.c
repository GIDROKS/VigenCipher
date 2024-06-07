#include "text_file_manager.h"
#include "vigenere_cipher.h"
#include "string_manager.h"
#include "memory_manager.h"
#include "common.h"

#include <stdio.h>


char** inputTextData()
{
    char** data;
    char* filePath = chooseArrayFilePath();
    if (filePath)
    {
        FILE* currentFile = openFile(filePath, "r");
        data = readDataFromFile(currentFile);
        fclose(currentFile);
        printDataFromFile(filePath);
    }
    else
    {
        data = (char**)safeMemoryAllocate(2 * sizeof(char*));

        printf("Enter the text:\n");
        data[0] = enterTextFromConsole();

        printf("Enter the key: ");
        data[1] = enterWordFromConsole();
    }

    return data;
}

int main(int args, char* argv[])
{
    char** textAndKey;
    printf("Print Sample Texts (1 - yes, 2 - no): ");
    int printChoice = inputIntegerNumberInRange(1, 2);
    if (printChoice == 1)
        printSampleDataFromFiles();

    while (1)
    {
        textAndKey = inputTextData();

        if (!encryptVigenere(textAndKey[0], textAndKey[1]))
        {
            printf("Encryption failed.\n");
            free(textAndKey[0]);
            free(textAndKey[1]);
            return 1;
        }

        printf("Encrypted text:\n%s\n", textAndKey[0]);

        if (!decryptVigenere(textAndKey[0], textAndKey[1]))
        {
            printf("Decryption failed.\n");
            free(textAndKey[0]);
            free(textAndKey[1]);
            return 1;
        }

        printf("Decrypted text:\n%s\n", textAndKey[0]);

        writeTextToResultFile(textAndKey[0]);
        printf("\n\n");

        free(textAndKey[0]);
        free(textAndKey[1]);
    }
    return 0;
}
