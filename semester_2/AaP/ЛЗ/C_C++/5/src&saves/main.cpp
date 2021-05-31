#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

#define PROG_NAME "reverse"
#define BUFF_SIZE 1024

const char DELIMITERS[] = ".?!";

void printHelp();
int getCharPosition(const char arr[], const char a);
int copyStr1ToStr2 (char *str1, unsigned long a, unsigned long b, char *str2, unsigned long offset);
int getStrLenght(char *str);

int main (int argc, char **argv)
{
    char **sentArray = (char **) malloc(sizeof(char *) * 1024),
           tmpSent[BUFF_SIZE];
    int delType = -1,
        sentArray_rows = 0,
        sentStart = 0,
        i = -1;
    
    // Если было передано не два аргумента,
    // то вывести справку и выйти
    if (argc != 3)
    {
        printHelp();
        return 0;
    }

    cout << "Открытие файлов...  ";

    ifstream inFile(argv[1], ios::in);
    ofstream outFile(argv[2], ios::out);

    // Проверка, открыт ли файл для чтения
    if (!inFile)
    {
        cout << "Ошибка: невозножно открыть для чтения '" << argv[1] << "'." << endl;
        return 1;
    }
    
    // Проверка, открыт ли файл для записи
    if (!outFile)
    {
        cout << "Ошибка: невозножно открыть для записи '" << argv[2] << "'." << endl;
        return 2;
    }

    cout << "ОТКРЫТО" << endl;
    cout << "Начало перемещения предложений..." << endl;

    // Начало выполнения алгоритма

    while(inFile)
    {
        inFile.read(tmpSent, BUFF_SIZE);
        *(tmpSent + BUFF_SIZE) = '\0';

        while (*(tmpSent + ++i))
        {
            delType = getCharPosition(DELIMITERS, *(tmpSent + i));

            if  (delType + 1)
            {
                //realloc(sentArray, sizeof(char *) * (++sentArray_rows));
                cout << "Обнаружено предложение. Началось перемещение в файл...  ";
                ++sentArray_rows;
                *(sentArray + sentArray_rows - 1) = (char *) malloc(sizeof(char) * (i - sentStart + 1));
                sentArray[sentArray_rows - 1][i - sentStart + 1] = '\0';
                std::cout << "ЗАВЕРШЕНО. Нескопировано символов: " << copyStr1ToStr2(tmpSent, sentStart, i, sentArray[sentArray_rows - 1], 0) << "." << std::endl;
                sentStart = i + 1;
            }
        }
    }
    
    for (i = sentArray_rows - 1; i >= 0; i--)
    {
        outFile.write(*(sentArray + i), getStrLenght(*(sentArray + i)));
    }

    // Закрытие файлов и выход из программы
    inFile.close();
    outFile.close();

    cout << "Все файлы закрыты. Завершение работы программы." << endl;

    return 0;
}

// Функция поиска первого вхождения символа a в строку arr
// Возвращет позицию первого вхождения. Иначе возвращает -1
int getCharPosition(const char arr[], const char a)
{
    int i = -1;

    while (arr[++i])
        if (arr[i] == a)
            return i;

    return -1;
}

// Функция копирования символов str1[a; b] в str2, начиная с позиции offset
// Возвращает 0, если копирование прошло успешно, иначе возвращает количество символов,
//     которое не удалось скопировать в строку str2

int copyStr1ToStr2 (char *str1, unsigned long a, unsigned long b, char *str2, unsigned long offset)
{
    int i = a, j = offset;
    for (; i <= b; i++, j++)
    {
        //if (*(str2 + j) == '\0') break;
        *(str2 + j) = *(str1 + i);
    }
    return b - i + 1;
}

// Напечатать справку
void printHelp()
{
    cout << "Использование: " << PROG_NAME << " [ФАЙЛ 1] [ФАЙЛ 2]" << endl;
    cout << "Берёт предложения из [ФАЙЛ 1] и выводит их же в [ФАЙЛ 2], но в обратном порядке." << endl;
    cout << endl;
    cout << "Параметры:" << endl;
    cout << "    -h,          --help                   Показать эту справку и выйти" << endl;
}

int getStrLenght(char *str)
{
    int l = 0;
    while (*(str++) != '\0') l++;
    return l;
}