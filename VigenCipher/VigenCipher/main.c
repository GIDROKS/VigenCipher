#include "memory_manager.h"
#include "my_string.h"

#include <stdio.h>


#define LETTERS_COUNT 26


void encryptVigenere(char* text, char* key)
{
    int textLen = stringLength(text), keyLen = stringLength(key), i, j;

    for (i = 0, j = 0; i < textLen; i++)
    {
        char textChar = text[i];
        char keyChar = key[j % keyLen];

        textChar = toUpperCase(textChar);
        keyChar = toUpperCase(keyChar);

        if (textChar < 'A' || textChar > 'Z')
        {
            printf("%c", text[i]);
            continue;
        }

        char encryptedChar = ((textChar - 'A' + (keyChar - 'A')) % LETTERS_COUNT) + 'A';

        printf("%c", encryptedChar);

        j++;
    }
}


int main(int args, char* argv[])
{
    printf("Enter text: ");
    char* text = readLine();

    printf("Enter key: ");
    char* key = readLine();

    printf("Encrypted text: ");
    encryptVigenere(text, key);

    free(text); 
    free(key);

    return 0;
}
