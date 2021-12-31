#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>

#define MEMPAGE_COUNT 3
#define MEMPAGE_SIZE 4096
#define TOTAL_MEMSIZE ((MEMPAGE_COUNT) * (MEMPAGE_SIZE))

#define MAX 256

#define MUTEX_NAME L"mutex_lab5"
#define MAP_NAME L"memshare_lab5"

typedef char arr_elem_t;

/* Заполнить массив случайными данными */
void fill_array (arr_elem_t * arrv, size_t arrc)
{
    for (size_t i = 0; i < arrc; i++)
        arrv[i] = rand() % MAX;
}



int main ()
{
    /* Создание процесса и Мьютекса */
    HANDLE mutex = CreateMutex(NULL, TRUE, MUTEX_NAME);
    STARTUPINFO si; PROCESS_INFORMATION pi;
    memset(&si, 0, sizeof(STARTUPINFO)); memset(&pi, 0, sizeof(PROCESS_INFORMATION));
    si.cb = sizeof(STARTUPINFO); si.lpTitle = "MemSorter 3000";
    CreateProcess(NULL, "MemSort.exe", 0, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

    /* Выделение участка виртуальной памяти */
    DWORD old_sec_attrs;
    LPVOID base_address = VirtualAlloc(NULL, TOTAL_MEMSIZE, MEM_COMMIT, PAGE_READWRITE);
    arr_elem_t *arr = (arr_elem_t *) base_address;
    /* Заполнение памяти */
    fill_array (arr, TOTAL_MEMSIZE / sizeof(arr_elem_t));

    /* Создание общей памяти */
    HANDLE file_map = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, TOTAL_MEMSIZE, "memshare_lab5");
    /* Отображение файла в адресное пространство программы */
    LPVOID view = MapViewOfFile(file_map, FILE_MAP_ALL_ACCESS, 0, 0, TOTAL_MEMSIZE);
    /* Копирование в файл из Виртуальной памяти */
    CopyMemory(view, base_address, TOTAL_MEMSIZE);

    /* Изменение прав доступа к памяти */
    VirtualProtect(base_address, TOTAL_MEMSIZE, PAGE_READONLY, &old_sec_attrs);

    /* Освобождение мьютекса и ожидание завершения процесса */
    ReleaseMutex(mutex);
    WaitForSingleObject(pi.hProcess, INFINITE);

    /* Изменение прав доступа к памяти */
    VirtualProtect(base_address, TOTAL_MEMSIZE, PAGE_READWRITE, &old_sec_attrs);

    /* Копирование из общей памяти в виртуальную память */
    CopyMemory(base_address, view, TOTAL_MEMSIZE);
    
    /* Печать данных на экран */
    for (size_t i = 0; i < TOTAL_MEMSIZE / sizeof(arr_elem_t); i++)
        printf("%d ", (int) arr[i]);
    printf("\r\n");

    /* Освобождение памяти и Выход */
    UnmapViewOfFile(view);
    CloseHandle(file_map);
    VirtualFree(base_address, TOTAL_MEMSIZE, MEM_RELEASE);
    return 0;
}