#include <iostream>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;



template <class T1>
void printArray (const T1 * arr, const size_t arr_size)
{
    cout << "arr = [";
    for (size_t i = 0; i < arr_size; i ++) cout << arr[i] << " ";
    cout << "]" << endl;

    return;
}

template <class T1>
void shiftElements (T1 * arr, const size_t arr_size, const size_t k)
{
    for (int i = 0; i < k; ++i)
    {
        T1 aLast = arr [arr_size - 1];
        for (int j = arr_size - 1; j > 0; j--)
            arr [j] = arr [j - 1];
        arr [0] = aLast;
    }

    return;
}



int main (void)
{
    int array1[] = {1, 2, 3, 4, 5};
    char array2[] = "abcdef";

    cout << "Массив чисел:" << endl;
    printArray (array1, sizeof(array1) / sizeof(array1[0]));
    shiftElements (array1, sizeof(array1) / sizeof(array1[0]), 1);
    printArray (array1, sizeof(array1) / sizeof(array1[0]));


    cout << "Массив символов:" << endl;
    printArray (array2, sizeof(array2) / sizeof(array2[0]) - 1);
    shiftElements (array2, sizeof(array2) / sizeof(array2[0]) - 1, 3);
    printArray (array2, sizeof(array2) / sizeof(array2[0]) - 1);

    return 0;
}
