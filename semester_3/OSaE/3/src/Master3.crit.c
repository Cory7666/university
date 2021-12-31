#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define N            66
#define THREAD_COUNT 5



CRITICAL_SECTION c;

void fill_array (int *, size_t);
void sort_quick(int *, int, int);
void print_arr (int *, size_t, char *);
DWORD WINAPI Sort (LPVOID);
int main (void);

int main (void)
{
    char tmp[THREAD_COUNT][1024];
    DWORD th[THREAD_COUNT];
    HANDLE hth[THREAD_COUNT];

    // Создание критической секции
    memset(&c, 0, sizeof(c));

    #ifdef USE_CRITICAL_SECTIONS
    InitializeCriticalSection(&c);
    #endif

    for (size_t i = 0; i < THREAD_COUNT; i++)
    {
        sprintf(tmp[i], "Thr%02d", i + 1);
        hth[i] = CreateThread(NULL, 0, Sort, (LPVOID) (tmp + i), CREATE_SUSPENDED, &th[i]);
    }
    for (size_t i = 0; i < THREAD_COUNT; i++) ResumeThread(hth[i]);

    WaitForMultipleObjects(THREAD_COUNT, hth, TRUE, INFINITE);

    #ifdef USE_CRITICAL_SECTIONS
    DeleteCriticalSection(&c);
    #endif

    return 0;
}

DWORD WINAPI Sort (LPVOID p)
{
    int string[N];
    fill_array(string, N);
    sort_quick(string, 0, N - 1);

    #ifdef USE_CRITICAL_SECTIONS
    EnterCriticalSection(&c);
    #endif

    print_arr(string, N, (char *) p);

    #ifdef USE_CRITICAL_SECTIONS
    LeaveCriticalSection(&c);
    #endif

    return 0;
}

void fill_array (int *arr, size_t size)
{
    srand(time(NULL));
    for (size_t i = 0; i < size; i++)
        arr[i] = rand() % 1000;
}

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

void print_arr (int *arr, size_t size, char *string)
{
    for (size_t i = 0; i < size; i++)
        printf("%s: A[%2u] = %3d.\r\n", string, i, arr[i]);
}