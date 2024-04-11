#include <stdio.h>


#define INITIAL_BUF_SIZE 4


char* readLine() {
    char* buffer = malloc(INITIAL_BUF_SIZE);
    if (buffer == NULL) {
        printf("Failed to allocate memory\n");
        return NULL;
    }

    int capacity = INITIAL_BUF_SIZE;
    int length = 0;
    char ch = getchar(); 

    while (ch != '\n' && ch != EOF) {
        buffer[length++] = ch;

        if (length == capacity) {
            capacity *= 2; 
            char* temp = realloc(buffer, capacity);
            if (temp == NULL) {
                printf("Failed to reallocate memory\n");
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }

        ch = getchar();
    }

    buffer[length] = '\0';

    char* temp = realloc(buffer, length + 1);
    if (temp == NULL)
        return buffer;

    return temp;
}

char toUpperCase(char ch)
{
    if (ch >= 'a' && ch <= 'z')
        return ch - 'a' + 'A';

    return ch;
}

void encryptVigenere(char* text, char* key) {
    int textLen = strlen(text), keyLen = strlen(key), i, j;

    for (i = 0, j = 0; i < textLen; i++) {
        char textChar = text[i];
        char keyChar = key[j % keyLen];

        textChar = toUpperCase(textChar);
        keyChar = toUpperCase(keyChar);

        if (textChar < 'A' || textChar > 'Z') {
            printf("%c", text[i]);
            continue;
        }

        char encryptedChar = ((textChar - 'A' + (keyChar - 'A')) % 26) + 'A';

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
