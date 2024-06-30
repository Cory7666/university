#include <stdio.h>
#include "locale.h"
#include "windows.h"

int main ()
{
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("Output 1.\n");
    Sleep(1000);
    printf("Output 2.\n");
    Sleep(2000);
    printf("Output 3\n");
    printf("Work is done.\n");
    getchar();
}