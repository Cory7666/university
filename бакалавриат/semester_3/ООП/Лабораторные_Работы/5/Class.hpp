#include <iostream>
#include <stdio.h>
#include <cstring>

using std::string;
using std::cin;
using std::cout;
using std::endl;

typedef double elem_t;    /* Тип элементов матрицы */

class DMatr;

elem_t operator+  (const DMatr & obj);
bool   operator== (const DMatr & obj_1, const DMatr & obj_2);
std::ostream & operator<< (std::ostream & stream, const DMatr & obj);    /* Вывод матрицы в поток */
std::istream & operator>> (std::istream & stream, DMatr & obj);    /* Ввод матрицы из потока */



class DMatr final
{
    private:
        elem_t ** _m;    // Указатель на матрицу.
        size_t _lines;   // Количество строк в матрице.
        size_t _cols;    // Количество столбцов в матрице.
    
    public:
        DMatr () : _m (nullptr), _lines (0), _cols (0) { }
        DMatr (size_t lines, size_t cols, elem_t * array, size_t array_size);
        DMatr (size_t lines, size_t cols) : DMatr (lines, cols, nullptr, 0) { }
        DMatr (const DMatr &);
        ~DMatr ();

        size_t getLines () const { return _lines; }
        size_t getCols  () const { return _cols;  }

        bool operator! ();    /* Проверить на наличие нулевых элементов */
        friend elem_t operator+ (const DMatr & obj);    /* Вычислить сумму элементов матрицы */
        elem_t operator* (const DMatr & obj);    /* Вычисление суммы произведений соответствующих элементов матрицы */
        friend bool operator== (const DMatr & obj_1, const DMatr & obj_2);    /* Проверка равенства двух матриц */
        friend std::istream & operator>> (std::istream & stream, DMatr & obj); /* Перегрузка оператора ввода данных из потока */
        friend std::ostream & operator<< (std::ostream & stream, const DMatr & obj); /* Перегрузка оператора вывода матрицы в поток */
};