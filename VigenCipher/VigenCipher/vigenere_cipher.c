#include "vigenere_cipher.h"

#include "memory_manager.h"
#include "string_manager.h"
#include <stdio.h>


#define LETTERS_COUNT 26


static char processChar(char textChar, char keyChar, int mode)
{
    textChar = toLowerCase(textChar);
    keyChar = toLowerCase(keyChar);

    if (textChar < 'a' || textChar > 'z')
        return textChar;

    if (mode == 1) 
        return ((textChar - 'a' + (keyChar - 'a')) % LETTERS_COUNT) + 'a';
    else 
        return ((textChar - keyChar + LETTERS_COUNT) % LETTERS_COUNT) + 'a';
}

static int validateInput(const char* text, const char* key, int* textLen, int* keyLen)
{
    if (!text || !key)
    {
        printf("Invalid input.\n");
        return 0;
    }

    *textLen = stringLength(text);
    *keyLen = stringLength(key);

    if (*textLen <= 0 || *keyLen <= 0)
    {
        printf("Invalid input.\n");
        return 0;
    }
    return 1;
}

int encryptVigenere(char* text, char* key)
{
    int textLen, keyLen;

    if (!validateInput(text, key, &textLen, &keyLen))
        return 0;

    for (int i = 0, j = 0; i < textLen; i++)
    {
        char encryptedChar = processChar(text[i], key[j % keyLen], 1);
        text[i] = encryptedChar;

        if (encryptedChar >= 'a' && encryptedChar <= 'z')
            j++;
    }
    return 1;
}

int decryptVigenere(char* text, char* key)
{
    int textLen, keyLen;

    if (!validateInput(text, key, &textLen, &keyLen))
        return 0;

    for (int i = 0, j = 0; i < textLen; i++)
    {
        char decryptedChar = processChar(text[i], key[j % keyLen], 0);
        text[i] = decryptedChar;

        if (decryptedChar >= 'a' && decryptedChar <= 'z')
            j++;
    }
    return 1;
}
