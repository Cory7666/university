#include <stdio.h>
#include <stdlib.h>

#define CLRSCR() fflush(NULL); system("clear")
#define pause(a) fflush(NULL); printf("Для продолжения нажмите %c ...\n", a); while (getchar() != a);
#define printTitle(title) printf("Запущена функция: %s ...\n\n", title)

// Раздел описания цифр для выбора действия
#define PROGRAM_EXIT 4
#define PROGRAM_DO_JOB 3
#define PROGRAM_INPUT_ARR 1
#define PROGRAM_PRINT_ARR 2

// Раздел описания соответствий названий цветов их последовательностям
#define FONT_DEFAULT "\e[0m"
#define FONT_RED     "\e[0;91m"
#define FONT_YELLOW  "\e[0;93m"
#define FONT_GREEN   "\e[0;92m"
#define FONT_BLUE    "\e[0;94m"

// Раздел объявления прототипов функций
void printMenu   (); // Печать меню
int **matrixInput (int rows, int cols); // Функция создания матрицы и ввода значений элементов
void matrixOutput(int **arr, int rows, int cols, int HLCol, int HLRow, char HLColor[]); // Функция печати матрицы
int **matrixCreate(int rows, int cols);           // Функция выделения памяти под матрицу
void matrixDelete(int **arr, int rows, int cols); // Функция удаления матрицы
void doJob(int **arr, int rows, int cols);        // Функция запуска выполнения задания по варианту
int  getColWithMinNeg (int **arr, int rows, int cols); // Функция нахождения столбца с минимальным количеством отрицательных элементов
int  getRowWithMaxSer (int **arr, int rows, int cols); // Функция нахождения строки с максимальной серией


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main ()
{

    int answer,
        rows = 0,
        cols = 0;
    int **arr = 0;

    do
    {
        printMenu();
        printf("> "); scanf("%d", &answer);

        switch (answer)
        {
        case PROGRAM_EXIT:
            printTitle("Выход из программы");
            matrixDelete(arr, rows, cols);
            break;

        case PROGRAM_INPUT_ARR:
            printTitle("Ввод матрицы");

            matrixDelete(arr, cols, rows);

            printf("Для начала введите количество строк в матрице:  "); scanf("%d", &rows);
            printf("А теперь введите количество столбцов в матрице: "); scanf("%d", &cols);

            arr = matrixInput(rows, cols);
            break;
        
        case PROGRAM_PRINT_ARR:
            printTitle("Вывод матрицы на экран");
            if (arr)
                matrixOutput(arr, rows, cols, -1, -1, "");
            else
                printf("Матрица не существует в памяти. Для начала создайте её.");
            
            printf("\n");
            break;

        case PROGRAM_DO_JOB:
            printTitle("Выполнение задания по варианту");
            if (arr)
                doJob(arr, rows, cols);
            else
                printf("Над несуществующей матрицей невозможно выполнить работу.");

            printf("\n");
            break;
        
        default:
            printf("Введена неверная цифра: %d. Повторите попытку...", answer);
            break;
        }

        pause('=');
    } while (answer != PROGRAM_EXIT);
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printMenu()
{
    CLRSCR();
    printf("=====Меню программы=====\n");
    printf("%2d) %s.\n", PROGRAM_INPUT_ARR, "Ввод матрицы"                      );
    printf("%2d) %s.\n", PROGRAM_PRINT_ARR, "Вывести матрицу на экран"          );
    printf("%2d) %s.\n", PROGRAM_DO_JOB,    "*my* Выполнить задание по варианту");
    printf("%2d) %s.\n", PROGRAM_EXIT,      "Выйти из программы"                );

    return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void matrixDelete(int **arr, int rows, int cols)
{
    if (arr)
    {
        for (int i = 0; i < cols; free(*(arr + i++)));
        free(arr);
        arr = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int **matrixCreate(int rows, int cols)
{
    int **arr = 0;
    arr = (int **) malloc( sizeof(int *) * rows );
    for (int i = 0; i < rows; i++)
        *(arr + i) = (int *) calloc(cols, sizeof(int));
    
    return arr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int **matrixInput (int rows, int cols)
{
    int **arr = 0;
    arr = matrixCreate(rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            CLRSCR();
            matrixOutput(arr, rows, cols, i, j, FONT_RED);
            printf("Введите элемент arr[%d][%d]: ", i + 1, j + 1); scanf("%d", *(arr + i) + j);
        }
    }
    CLRSCR();
    printf("Отлично! Новая матрица была создана!\n");

    return arr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void matrixOutput(int **arr, int rows, int cols, int HLCol, int HLRow, char HLColor[])
{
    if (arr)
    {
        printf("     ");
        for (int i = 0; i++ < cols; printf("%3d ", i));
        printf("\n");

        printf("    _");
        for (int i = 0; i++ < cols; printf("____"));
        printf("__\n");

        for (int i = 0; i < rows; i++)
        {
            printf("%3d| ", i + 1);

            for (int j = 0; j < cols; j++)
                if ( (HLCol == i && HLRow == j) || ( HLRow < 0 && HLCol == i ) || ( HLCol < 0 && HLRow == j ) )
                    printf("%s%3d \e[0m", HLColor, arr[i][j]);
                else
                    printf("%3d ", arr[i][j]);

            printf("\n");
        }

        printf("   |\n");
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void doJob(int **arr, int rows, int cols)
{
    int colI= 0,  // Номер столбца, содержащий минимальное количество отрицательных элементов
        rowI = 0; // Номер строки, содержащей самую длинную серию отрицательных элементов
    
    colI = getColWithMinNeg(arr, rows, cols);
    rowI = getRowWithMaxSer(arr, rows, cols);


    printf("Действие 1: поиск столбца, содержащего минимальное количество отрицательных элементов.\n");
    printf("Результат:\n * ");
    
    if (colI >= 0)
    {
        printf("Был найден столбец под номером %d. Для удобства он выделен ЗЕЛЁНЫМ цветом.\n", colI + 1);
        matrixOutput(arr, rows, cols, -1, colI, FONT_GREEN);
    }
    else
        printf("Не был найден ни один столбец, содержащий хотя бы один отрицательный элемент.\n");

    printf("\n================================================================\n\n");
    printf("Действие 2: поиск строки, содержащей максимальную серию из отрицательных элементов.\n");
    printf("Результат:\n * ");

    if (rowI >= 0)
    {
        printf("Была найдена строка под номером %d. Для удобства она выделена СИНИМ цветом.\n", rowI + 1);
        matrixOutput(arr, rows, cols, rowI, -1, FONT_BLUE);
    }
    else
        printf("Не была найдена ни одина строка, содержащая хотя бы один отрицательный элемент.\n");

    printf("\n================================================================\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int getColWithMinNeg(int **arr, int rows, int cols)
{
    int i = 0, j = 0,          // Переменные для циклов
        minI      = -1,        // Содержит номер столбца (если таковой будет найден)
        countMin  = rows + 99, // Минимальное количество отрицательных элементов в найденном столбце
        count     = 0;         // Количество отрицательных элементов в рассматриваемом столбце
    
    for (j = 0; j < cols; j++) // Номер каждого столбца
    {
        count = 0;
        for (i = 0; i < rows; i++) // Номер каждой строчки
            if ( arr[i][j] < 0 )
                count++;
        
        if (count > 0 && count < countMin)
        {
            countMin = count;
            minI = j;
        }
    }
    
    return minI;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int getRowWithMaxSer(int **arr, int rows, int cols)
{
    int serLength = 0,    // Длина текущей серии
        serLengthMax = 0, // Максимальная длина серии
        maxI = -1,        // Номер строки с максимально длинной серией (если таковая будет найдена)
        i, j;             // Переменные для циклов

    for (i = 0; i < rows; i++) // Каждая строчка
    {
        serLength = 0;

        for (j = 0; j < cols; j++) // Каждый столбец
        {
            if (arr[i][j] < 0)
            {
                serLength++;
            }
            else
            {
                if (serLength > serLengthMax)
                {
                    serLengthMax = serLength;
                    maxI = i;
                }
                serLength = 0;
            }
        }

        if (serLength > serLengthMax)
        {
            serLengthMax = serLength;
            maxI = i;
        }
    }

    return maxI;
}
