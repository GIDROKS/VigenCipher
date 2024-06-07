#include "vigenere_cipher.h"

#include "memory_manager.h"
#include "string_manager.h"
#include <stdio.h>


#define LETTERS_COUNT 26


// Вспомогательная функция для обработки символов шифрования и дешифрования
static char processChar(char textChar, char keyChar, int mode)
{
    // Преобразуем символы в нижний регистр для унифицированной обработки
    textChar = toLowerCase(textChar);
    keyChar = toLowerCase(keyChar);

    // Если символ не является буквой, возвращаем его без изменений
    if (textChar < 'a' || textChar > 'z')
        return textChar;

    if (mode == 1) // Режим шифрования
        return ((textChar - 'a' + (keyChar - 'a')) % LETTERS_COUNT) + 'a';
    else // Режим дешифрования
        return ((textChar - keyChar + LETTERS_COUNT) % LETTERS_COUNT) + 'a';
}

// Вспомогательная функция для проверки входных данных
static int validateInput(const char* text, const char* key, int* textLen, int* keyLen)
{
    // Проверка на нулевые указатели
    if (!text || !key)
    {
        printf("Invalid input.\n");
        return 0;
    }

    // Получение длин строк
    *textLen = stringLength(text);
    *keyLen = stringLength(key);

    // Проверка на пустые строки
    if (*textLen <= 0 || *keyLen <= 0)
    {
        printf("Invalid input.\n");
        return 0;
    }
    return 1;
}

// Функция для шифрования текста по методу Виженера
int encryptVigenere(char* text, char* key)
{
    int textLen, keyLen;

    // Проверка входных данных
    if (!validateInput(text, key, &textLen, &keyLen))
        return 0;

    // Шифрование текста
    for (int i = 0, j = 0; i < textLen; i++)
    {
        char encryptedChar = processChar(text[i], key[j % keyLen], 1);
        text[i] = encryptedChar;

        // Увеличиваем индекс ключа только для букв
        if (encryptedChar >= 'a' && encryptedChar <= 'z')
            j++;
    }
    return 1;
}

// Функция для дешифрования текста по методу Виженера
int decryptVigenere(char* text, char* key)
{
    int textLen, keyLen;

    // Проверка входных данных
    if (!validateInput(text, key, &textLen, &keyLen))
        return 0;

    // Дешифрование текста
    for (int i = 0, j = 0; i < textLen; i++)
    {
        char decryptedChar = processChar(text[i], key[j % keyLen], 0);
        text[i] = decryptedChar;

        // Увеличиваем индекс ключа только для букв
        if (decryptedChar >= 'a' && decryptedChar <= 'z')
            j++;
    }
    return 1;
}
