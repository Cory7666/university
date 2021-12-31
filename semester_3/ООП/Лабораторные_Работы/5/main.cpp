#include "Class.hpp"

int main (int argc, char **argv)
{
    elem_t arr[6] = {1, 2, 3, 4, 5, 6};
    DMatr d_1 (2, 3, arr, 6);

    DMatr d_2 (2, 3);

    cout << "Введите " << d_2.getLines() * d_2.getCols() << " элементов матрица." << endl;
    cin >> d_2;

    cout << "Действие оператора \"*\": " << (d_1 * d_2) << endl
         << "Действие оператора \"==\": " << ((d_1 == d_2) ? "true" : "false") << endl
         << "Действие унарного оператора \"+\" над d_2: " << +d_2 << endl
         << "Действие унарного \"!\" над d_2: " << ((!d_2) ? "true" : "false") << endl;

    return 0;
}