#include <stdio.h>
#include <stdlib.h>

#define PROG_NAME "reverse"

void printHelp();

int main (int argc, char **argv)
{
    // Если было передано не два аргумента
    // то вывести справку и выйти
    if (argc != 3)
    {
        printHelp();
        return 0;
    }

    // Открытие файлов

    printf("Открытие файлов...   ");
    FILE *inputFile = fopen(argv[1], "r"),
         *outputFile = fopen(argv[2], "w");
    char c;

    // Проверка файлов на возможность работы с ними
    // Возвращает ненулевое число
    if (!inputFile)
    {
        printf("\nОшибка: невозможно открыть \"%s\" для чтения.\n", argv[1]);
        return 1;
    }
    if (!outputFile)
    {
        printf("\nОшибка: невозможно отрыть \"%s\" для записи.\n", argv[2]);
        return 2;
    }

    printf("ОТКРЫТО!\n");
    printf("Начало перемещения предложений...\n");

    fseek(inputFile, 0, SEEK_END);
    int sentStart = ftell(inputFile) - 1, sentEnd = 0;

    while (ftell(inputFile) > 0)
    {
        c = fgetc(inputFile);

        if (c == '.' || c == '!' || c == '?')
        {
            printf("Обнаружено предложение. Начало перемещения...   ");

            sentEnd = sentStart;
            sentStart = ftell(inputFile);

            for (int i = sentStart; i <= sentEnd; i++)
            {
                char ch = fgetc(inputFile);
                fwrite(&ch, 1, 1, outputFile);
            }

            printf("ЗАВЕРШЕНО!\n");

            fseek(inputFile, sentStart, SEEK_SET);
        }

        fseek(inputFile, -2, SEEK_CUR);
    }

    if (sentEnd)
    {
        sentEnd = sentStart;
        sentStart = 0;
        fseek(inputFile, sentStart, SEEK_SET);

        for (int i = sentStart; i <= sentEnd; i++)
        {
            char ch = fgetc(inputFile);
            fwrite(&ch, 1, 1, outputFile);
        }

        fwrite("\n", 1, 1, outputFile);
    }

    // Закрытие файлов и выход из программы
    fclose(inputFile);
    fclose(outputFile);

    printf("Все файлы закрыты. Программа зарвешила свою работу.\n");

    return 0;
}

// Напечатать справку
// Не возвращает ничего
void printHelp()
{
    printf("Использование: %s [ФАЙЛ 1] [ФАЙЛ 2]\n", PROG_NAME);
    printf("Берёт предложения из [ФАЙЛ 1] и выводит их же в [ФАЙЛ 2], но в обратном порядке.\n");
    printf("\n");
    printf("Параметры:\n");
    printf("    -h,          --help                   Показать эту справку и выйти\n");
    fflush(stdout);
}
