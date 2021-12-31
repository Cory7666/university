/*
    Дополнительные параметры компиляции:
    * -DUSE_SYNC -> Использовать синхронизацию потоков.
*/

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>
#include <time.h>

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

#ifndef USE_SYNC
#define USE_SYNC 0
#endif

#define RANGE_MIN 0
#define RANGE_MAX 100
#define N         48



/* Структура экспорта данных в поток */
typedef struct export_data_struct
{
    pthread_t neighbor_thread_id; // идентификатор соседского потока
    int  * array_ptr;             // Указатель на массив
    int    array_size;            // Размер массива
}
export_data_t;



/* Сортировка данных в массиве */
void sort(int array[], int size)
{
    int tmp;
    for (int startIndex = 0; startIndex < size - 1; ++startIndex)
	{
		int smallestIndex = startIndex;
		for (int currentIndex = startIndex + 1; currentIndex < size; currentIndex++)
			if (array[currentIndex] < array[smallestIndex])
				smallestIndex = currentIndex;
        tmp = array[startIndex];
        array[startIndex] = array[smallestIndex];
        array[smallestIndex] = tmp;
	}
    return;
}

/* Заполнение массива случайными числами */
void fill_array (int *array, int size)
{
    if (size > 0)
    {
        *array = rand() % (RANGE_MAX + 1) + RANGE_MIN;
        fill_array(array + 1, size - 1);
    }
}

/* Печать массива на экран */
void print_array (int *array, int size, char * prefix)
{
    for (int i = 0; i < size; i++)
        printf("%s: array[%2d]: %3d.\n", prefix, i, array[i]);
}



/* Обёртка для sort для работы с потоками */
void * sort_wrap (void * import_data)
{
    /* Печать имени потока */
    printf("sort:phreadId=%lu\n", pthread_self());

    /* Выполнить основное действие потока */
    sort (
        ((export_data_t *) import_data)->array_ptr,
        ((export_data_t *) import_data)->array_size
    );

    return NULL;
}

/* Обёртка для print_array для работы с потоками */
void * print_array_wrap (void * import_data)
{
    /* Печать имени потока */
    printf("print:phreadId=%lu\n", pthread_self());

    #if USE_SYNC
    /* Ожидать завершения сортировки массива */
    pthread_join(((export_data_t *) import_data)->neighbor_thread_id, NULL);
    #endif

    /* Выполнить основное действие потока */
    print_array(
        ((export_data_t *) import_data)->array_ptr,
        ((export_data_t *) import_data)->array_size,
        "PRINT_THREAD"
    );

    return NULL;
}



int main (int argc, char ** argv, char ** envp)
{
    int array[N]; // Массив
    export_data_t print_st, sort_st; // export-структуры

    /* Заполнение массива числами */
    fill_array (array, N);

    /* Запись в структуры размеров массива и указателя на этот массив */
    print_st.array_size = sort_st.array_size = N;
    print_st.array_ptr  = sort_st.array_ptr  = ((int *) array);

    /* Создание потоков */
    pthread_create(&print_st.neighbor_thread_id, NULL, sort_wrap,        (void *) &sort_st);
    pthread_create(&sort_st.neighbor_thread_id,  NULL, print_array_wrap, (void *) &print_st);

    /* Ожидание завершения работы потока печати массива */
    pthread_join(sort_st.neighbor_thread_id, NULL);

    return 0;
}