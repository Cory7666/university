#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include <unistd.h>
#include <sys/types.h>

#define M 4

int main (int argc, char **argv, char **envp)
{
    char arg_char[1023]; memset (arg_char, 0, sizeof(arg_char));
    pid_t ppid = getppid(),
          pid  = getpid();
    
    /* Вывод PID и PPID Master-процесса */
    printf("MASTER. PPID/PID: %d/%d.\n", ppid, pid);

    for (int i = 0; i < M; i++)
    {
        sprintf(arg_char, "%d", i + 1);

        /* Запустить другую программу, если форк, иначе продолжить выполнение цикла */
        if (!fork())
            execlp ("./sort", "sort", arg_char, NULL);
    }

    sleep(1);
    return 0;
}