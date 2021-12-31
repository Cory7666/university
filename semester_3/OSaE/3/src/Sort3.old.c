// Вариант 19

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define N 65

// Функция заполнения массива массива случайными числами
void fill_array (int *arr, size_t size)
{
    srand(time(NULL));
    for (size_t i = 0; i < size; i++)
        arr[i] = rand();
}

// Сортировка массива
void sort_quick(int *arr, int f, int l)
{
    if (f < l)
    {
        int left = f, right = l, middle = arr[(left + right) / 2];
        do
        {
            while (arr[left] < middle) left++;
            while (arr[right] > middle) right--;
            if (left <= right)
            {
                int tmp = arr[left];
                arr[left] = arr[right];
                arr[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        sort_quick(arr, f, right);
        sort_quick(arr, left, l);
    }
}
// Печать массива
void print_arr (int *arr, size_t size, char *string)
{
    for (size_t i = 0; i < size; i += 2)
        printf("%s: A[%2u] = %3d.    %s: A[%2u] = %3d.\r\n", string, i, arr[i], string, i + 1, arr[i + 1]);
}



int main (int argc, char **argv)
{
    if (argc != 2) return 1;

    int arr[N];

    // Заполнить и Сортировать массив
    fill_array(arr, N);
    sort_quick(arr, 0, N - 1);

    // Печать массива
    print_arr(arr, N, argv[1]);

    return 0;
}