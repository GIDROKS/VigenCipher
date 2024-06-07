#include "text_file_manager.h"
#include "vigenere_cipher.h"
#include "string_manager.h"
#include "memory_manager.h"
#include "common.h"

#include <stdio.h>

#include <SDL.h>


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

void checkEncryption()
{
    char** textAndKey = inputTextData();

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

//int main(int args, char* argv[])
//{
//    printf("Print Sample Texts (1 - yes, 2 - no): ");
//    int printChoice = inputIntegerNumberInRange(1, 2);
//    if (printChoice == 1)
//        printSampleDataFromFiles();
//
//    while (1)
//        checkEncryption();
//
//    return 0;
//}


// Инициализация SDL
int init(SDL_Window** window, SDL_Renderer** renderer, int screenWidth, int screenHeight)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    *window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (*window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    return 1;
}

// Главная функция
int main(int argc, char* args[])
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    int screenWidth = 640;
    int screenHeight = 480;

    // Инициализация
    if (!init(&window, &renderer, screenWidth, screenHeight))
    {
        printf("Failed to initialize!\n");
        return -1;
    }

    int quit = 0;
    SDL_Event e;

    // Основной цикл приложения
    while (!quit)
    {
        // Обработка событий
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }
        }

        // Очистка экрана
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // Установка цвета отрисовки
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

        // Отрисовка прямоугольника
        SDL_Rect fillRect = { screenWidth / 4, screenHeight / 4, screenWidth / 2, screenHeight / 2 };
        SDL_RenderFillRect(renderer, &fillRect);

        // Обновление экрана
        SDL_RenderPresent(renderer);
    }

    // Освобождение ресурсов и завершение работы SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}