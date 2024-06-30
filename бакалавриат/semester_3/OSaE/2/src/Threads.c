#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <conio.h>
#include <windows.h>

typedef long long          arr_elem_t;
typedef unsigned long long arr_len_t;

void sort (arr_elem_t *arr, arr_len_t size);
void fill_array (arr_elem_t *arr, arr_len_t size);
void print_array (const arr_elem_t *arr, const arr_len_t size);
DWORD WINAPI sort_wrap (LPVOID *t);
DWORD WINAPI print_wrap (LPVOID *t);


const  arr_len_t  g_s = 50;

int main ()
{
    arr_elem_t *g_arr = (arr_elem_t *) calloc(sizeof(arr_elem_t), g_s);
    fill_array(g_arr, g_s);

    printf("INPUT "); print_array(g_arr, g_s);

    DWORD p1 = 0;
    CreateThread(NULL, 0, (LPVOID) sort_wrap, NULL, CREATE_SUSPENDED, &p1);
    printf("\n\n\n");
    ResumeThread(p1);

    printf("AFTER: "); print_array(g_arr, g_s);

    getch();

    return 0;
}

//============================================================================================================//

DWORD WINAPI sort_wrap (LPVOID *t)  { sort((arr_elem_t *) t, g_s);        return 0; }
DWORD WINAPI print_wrap (LPVOID *t) { print_array((arr_elem_t *) t, g_s); return 0; }

//============================================================================================================//

void sort (arr_elem_t *arr, arr_len_t size)
{
    for (arr_len_t d = size / 2; d > 0; d /= 2)
        for (arr_len_t i = 0; i < size; i++)
            for (arr_len_t j = i + d; j < size; j += d)
                if (arr[i] < arr[j])
                {
                    int tmp = arr[j];
                    arr[j] = arr[i];
                    arr[i] = tmp;
                }
}

//============================================================================================================//

void fill_array (arr_elem_t *arr, arr_len_t size)
{
    srand(time(NULL));

    for (arr_len_t i = 0; i < size; i++)
        *(arr + i) = (arr_len_t) (rand() % 30001);
}

//============================================================================================================//

void print_array (const arr_elem_t *arr, const arr_len_t size)
{
    fprintf(stdout, "array = [");
    for(arr_len_t i = 0; i < size; i++)
        fprintf(stdout, (i + 1 != size) ? "%lld, " : "%lld", arr[i]);
    fprintf(stdout, "]\r\n");
}

//============================================================================================================//