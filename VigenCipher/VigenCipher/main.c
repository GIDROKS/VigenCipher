#include <stdio.h>
#include <string.h>


char toUpperCase(char ch)
{
    if (ch >= 'a' && ch <= 'z')
        return ch - 'a' + 'A';

    return ch;
}

void encryptVigenere(char* text, char* key)
{
    int textLen = strlen(text), keyLen = strlen(key), i, j;

    for (i = 0, j = 0; i < textLen; i++) {
        char textChar = text[i];
        char keyChar = key[j % keyLen];

        textChar = toUpperCase(textChar);
        keyChar = toUpperCase(keyChar);

        if (textChar < 'A' || textChar > 'Z')
            continue; // Пропускаем символ, если он не является буквой

        char encryptedChar = ((textChar - 'A' + (keyChar - 'A')) % 26) + 'A'; // Шифрование

        printf("%c", encryptedChar);

        j++; // Переходим к следующему символу ключа
    }
}

int main(int args, char* argv[])
{
    char text[1024], key[256];

    printf("Enter text to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0; // Удаляем символ новой строки

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0; // Удаляем символ новой строки

    printf("Encrypted text: ");
    encryptVigenere(text, key);

    return 0;
}
