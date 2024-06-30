#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "conio.h"
#include "windows.h"



typedef long long          arr_elem_t;
typedef unsigned long long arr_len_t;




void print_time (double t);

void shell_sort_wrap (arr_elem_t *arr, arr_len_t size);
void shell_sort (arr_elem_t *arr, arr_len_t size);
void fill_array (arr_elem_t *arr, arr_len_t size);
void print_array (const arr_elem_t *arr, const arr_len_t size);