#include "Sort.h"

clock_t WATCH_START = 0;



int main ()
{
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    arr_len_t  size = 1000000;
    arr_elem_t arr[size];

    shell_sort_wrap(arr, size);

    getch();
    return 0;
}



//=============================================================================================================//

double get_diff_time (clock_t tstart)
{
    return (( (double) (clock() - tstart) ) / CLOCKS_PER_SEC);
}

//============================================================================================================//

void print_time (double t)
{
    fprintf(stdout, "%02d:%02lu:%03.3lu\r\n", (int) (t / 60), ((unsigned long) t) % 60, ((unsigned long) (t * 1000)) % 1000);
}

//============================================================================================================//

void shell_sort_wrap (arr_elem_t *arr, arr_len_t size)
{
    const unsigned int REP_COUNT = 100;
    double total_sort_time = 0.0;
    clock_t prog_start = clock();

    for (unsigned int i = 0; i < REP_COUNT; i++)
    {
        fill_array(arr, size);

        total_sort_time -= clock() / CLOCKS_PER_SEC;
        shell_sort(arr, size);
        total_sort_time += clock() / CLOCKS_PER_SEC;
    }

    printf("Total program execution time:           "); print_time(get_diff_time(prog_start));
    printf("Time spent on sorting (total/per call): "); print_time(total_sort_time);
    printf("                                        "); print_time(total_sort_time / REP_COUNT);
}

//============================================================================================================//

void shell_sort (arr_elem_t *arr, arr_len_t size)
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