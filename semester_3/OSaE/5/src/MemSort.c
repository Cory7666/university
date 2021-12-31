#include <stdio.h>
#include <stdlib.h>

#include <windows.h>

#define MEMPAGE_COUNT 3
#define MEMPAGE_SIZE 4096
#define TOTAL_MEMSIZE ((MEMPAGE_COUNT) * (MEMPAGE_SIZE))

#define MAX 256

#define MUTEX_NAME L"mutex_lab5"
#define MAP_NAME "memshare_lab5"

typedef char arr_elem_t;

void sort(arr_elem_t *arrv, size_t arrc)
{
    arr_elem_t tmp = 0;
    for (int i = arrc - 1; i >= 0; i--)
        for (int j = 0; j < i; j++)
        {
            if (arrv[j] > arrv[j + 1])
            {
                tmp = arrv[j];
                arrv[j] = arrv[j + 1];
                arrv[j + 1] = tmp;
            }
        }
}

int main()
{
    /* Открытие мьютекса */
    HANDLE mutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, MUTEX_NAME);
    WaitForSingleObject(mutex, INFINITE);

    /* Открытие общей памяти и отображение её в программе */
    HANDLE shared_mem = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, MAP_NAME);
    arr_elem_t *arr = (arr_elem_t *) MapViewOfFile(shared_mem, FILE_MAP_ALL_ACCESS, 0, 0, TOTAL_MEMSIZE);

    sort(arr, TOTAL_MEMSIZE / sizeof(arr_elem_t));

    ReleaseMutex(mutex);
    UnmapViewOfFile((LPVOID) arr);
    CloseHandle(shared_mem);

    return 0;
}