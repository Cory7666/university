#include "Class.hpp"

int main (int argc, char **argv)
{
    long long int data_1[7] = {1, -6, 80, -30, 30, -100, -90},
                  data_2[5] = {-90, 65, -1, 0, 54};

    Integer i = -7;
    IntVector vec_1 = IntVector(data_1, ARR_LEN(data_1)),
              vec_2 = IntVector(data_2, ARR_LEN(data_2));

    cout << "Класс Число: " << i.getValue() << endl;
    cout << "Класс Вектор. Объект 1: " << string(vec_1) << endl;
    cout << "Класс Вектор. Объект 2: " << string(vec_2) << endl << endl;

    cout << "Вызов 1: " << f(i, vec_1) << endl;
    cout << "Вызов 2: " << f(i, vec_2) << endl;

    return 0;
}