#include "main.h"
#include <wchar.h>

int main ()
{
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    LPPROCESS_INFORMATION pi = calloc(sizeof(PROCESS_INFORMATION), 1);
    LPSTARTUPINFO         si = calloc(sizeof(STARTUPINFO), 1);
    si->cb = sizeof(STARTUPINFO);
    si->lpTitle = "Test Process";
    wcscpy()

    CreateProcess(NULL, "./sort.exe", 0, NULL, FALSE, CREATE_NEW_CONSOLE | CREATE_SUSPENDED, NULL, NULL, si, pi);
    SetPriorityClass(pi->hProcess, HIGH_PRIORITY_CLASS);
    SetThreadAffinityMask(pi->hThread, 1<<0);
    ResumeThread(pi->hThread);

    WaitForSingleObject(pi->hProcess, INFINITE);
    
    return 0;
}