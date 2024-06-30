
/*
    USE_SEMAPHORE -> ��� ���������� ������������ ��������
    RANDOM_PROGRESSION -> ���������� ��������� ������ ���� ����������
    WRITE_DELAY -> ��������� ����� ������ � �����
    PRINT_DELAY -> ��������� ����� ������ �� ������
*/

#include <iostream>
#include <ctime>
#include <windows.h>

#define N_buf 5
#define N     240
#define PROGRES_DIFF 3

#define NSEM_FREE "MySem_Free"
#define NSEM_FULL "MySem_Full"
#define NSEM_BOOL "MySem_Bool"

using std::cout;
using std::endl;

typedef int elem_t;

elem_t arr[N_buf];

DWORD WINAPI print_from_buff (LPVOID);
DWORD WINAPI write_to_buff   (LPVOID);

int main ()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    HANDLE hth[2], sem[3];

    #ifdef USE_SEMAPHORE
    sem[0] = CreateSemaphore(NULL, N_buf, N_buf, NSEM_FREE);
    sem[1] = CreateSemaphore(NULL, 0,     N_buf, NSEM_FULL);
    sem[2] = CreateSemaphore(NULL, 1,     1,     NSEM_BOOL);
    #endif

    // ������� 2 ������
    hth[0] = CreateThread(NULL, 0, print_from_buff, NULL, 0, NULL);
    hth[1] = CreateThread(NULL, 0, write_to_buff, NULL, 0, NULL);

    // ����� ���������� ������ ���� �������
    WaitForMultipleObjects(2, hth, TRUE, INFINITE);

    for (int i = 0; i < 3; i++)
        CloseHandle(sem[i]);

    return 0;
}

DWORD WINAPI print_from_buff (LPVOID p)
{
    #ifdef USE_SEMAPHORE
    HANDLE sem[3];
    sem[0] = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, NSEM_FREE);
    sem[1] = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, NSEM_FULL);
    sem[2] = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, NSEM_BOOL);
    #endif

    for (size_t i = 0; i < N; i++)
    {
        #ifdef USE_SEMAPHORE
        // ������ �� ���������� ������������� ������
        WaitForSingleObject(sem[1], INFINITE);
        // ������ �� ������� � ����������� ����� ������ ��� �������
        WaitForSingleObject(sem[2], INFINITE);
        #endif

        cout << arr[i % N_buf] << "  ";

        #ifdef WRITE_DELAY
        // ������������� �������� ������
        Sleep(100);
        #endif

        #ifdef USE_SEMAPHORE
        // ��������� ����������� ������
        ReleaseSemaphore(sem[0], 1, NULL);
        // ����� �� ������������ ������
        ReleaseSemaphore(sem[2], 1, NULL);
        #endif
    }

    cout << endl;

    return 0;
}

DWORD WINAPI write_to_buff   (LPVOID p)
{
    #ifdef RANDOM_PROGRESSION
    srand(time(NULL));
    #else
    srand(1);
    InitializeCriticalSection
    #endif

    #ifdef USE_SEMAPHORE
    HANDLE sem[3];
    sem[0] = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, NSEM_FREE);
    sem[1] = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, NSEM_FULL);
    sem[2] = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, NSEM_BOOL);
    #endif

    elem_t curr = rand() % 5 - PROGRES_DIFF;

    for (size_t i = 0; i < N; i++)
    {
        #ifdef USE_SEMAPHORE
        // ������ �� ���������� ����������� ������
        WaitForSingleObject(sem[0], INFINITE);
        // ������ �� ������� � ����������� ����� ������ ��� �������
        WaitForSingleObject(sem[2], INFINITE);
        #endif

        arr[i % N_buf] = (curr += PROGRES_DIFF);

        #ifdef PRINT_DELAY
        // ������������� �������� ������
        Sleep(250);
        #endif

        #ifdef USE_SEMAPHORE
        // ��������� ������������� ������
        ReleaseSemaphore(sem[1], 1, NULL);
        // ����� �� ������������ ������
        ReleaseSemaphore(sem[2], 1, NULL);
        #endif
    }

    return 0;
}