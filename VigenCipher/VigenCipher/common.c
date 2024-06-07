#include "common.h"

#include <stdlib.h>
#include <stdio.h>


int inputIntegerNumber()
{
    int number;
    while (1)
    {
        int isCorrectInput = scanf_s("%d", &number);
        while (getchar() != '\n');

        if (!isCorrectInput)
            printf("Invalid input! The number must be positive.\n");
        else break;
    }
    return number;
}

int inputIntegerNumberInRange(int minValue, int maxValue)
{
    int number;
    while (1)
    {
        number = inputIntegerNumber();
        if (number >= minValue && number <= maxValue)
            return number;
        printf("The number must be between %d and %d.\n", minValue, maxValue);
    }
}