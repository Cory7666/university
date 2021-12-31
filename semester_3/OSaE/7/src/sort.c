#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

#define N         48
#define RANGE_MIN 0
#define RANGE_MAX 100

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

void fill_array (int *array, int size)
{
    if (size > 0)
    {
        *array = rand() % (RANGE_MAX + 1) + RANGE_MIN;
        fill_array(array + 1, size - 1);
    }
}

void print_array (int *array, int size, char * prefix)
{
    for (int i = 0; i < size; i++)
        printf("%s: array[%2d]: %3d.\n", prefix, i, array[i]);
}

int main (int argc, char **argv, char **envp)
{
    if (argc != 2) return 1;

    pid_t ppid = getppid(),
          pid  = getpid();

    char prefix[1023];
    memset(prefix, 0, sizeof(prefix));
    sprintf(prefix, "PROC_NUM: %s. PPID/PID: %d/%d", argv[1], ppid, pid);

    int arr[N];
    fill_array (arr, N);
    print_array(arr, N, prefix);
    sort(arr, N);
    print_array(arr, N, prefix);
    return 0;
}