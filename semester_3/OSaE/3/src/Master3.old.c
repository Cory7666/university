#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define PROC_COUNT 5

int main (void)
{
    PROCESS_INFORMATION p[PROC_COUNT];
    STARTUPINFO s[PROC_COUNT];
    
    memset(&s, 0, sizeof(s));
    memset(&p, 0, sizeof(p));
    
    char tmp[1024];
    for (size_t i = 0; i < PROC_COUNT; i++)
    {
        s[i].cb = sizeof(STARTUPINFO);
        s[i].lpTitle = calloc(sizeof(char), sprintf(tmp, "Proc_%d", i + 1));
        strcpy(s[i].lpTitle, tmp);
    };

    for (size_t i = 0; i < PROC_COUNT; i++)
    {
        sprintf(tmp, ".\\Sort3.old.exe Proc%02d", i);
        CreateProcess(NULL, tmp, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &s[i], &p[i]);
    }

    for (size_t i = 0; i < PROC_COUNT; i++)
        ResumeThread(p[i].hThread);
    
    WaitForSingleObject(p[0].hProcess, INFINITE);
    WaitForSingleObject(p[1].hProcess, INFINITE);
    WaitForSingleObject(p[2].hProcess, INFINITE);
    WaitForSingleObject(p[3].hProcess, INFINITE);
    WaitForSingleObject(p[4].hProcess, INFINITE);
}