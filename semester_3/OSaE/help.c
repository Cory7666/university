#include "windows.h"

BOOL bInheriteHandles, DisablePrioBoost;
DWORD dwCreationFlags, dwPrioClass;
UINT uExitCode;
HANDLE hProc;
LPCTSTR lpAppName, lpCWD;
LPTSTR  lpCommLine;
LPDWORD lpThreadId, lpExitCode;
LPFILETIME lpCreationTime, lpExitTime, lpKernelTime, lpUserTime;
LPPROCESS_INFORMATION lpProcInfo;
LPSECURITY_ATTRIBUTES lpProcAttrs, lpThreadAttrs;
LPSTARTUPINFO lpStartupInfo;
LPTHREAD_START_ROUTINE lpStartAddr;
LPVOID lpEnv, lpParam;
PBOOL pDisablePrioBoost;
SIZE_T dwStackSize;

void help_Types (void)
{
     /* DWORD */
    dwPrioClass = 
        ABOVE_NORMAL_PRIORITY_CLASS || // Приоритет процесса между NORMAL_PRIORITY_CLASS и HIGH_PRIORITY_CLASS.
        BELOW_NORMAL_PRIORITY_CLASS || // Приоритет процесса иежду IDLE_PRIORITY_CLASS и NORMAL_PRIORITY_CLASS.
        HIGH_PRIORITY_CLASS         || // Приоритет процесса ОЧЕНЬ_ВЫСОКИЙ.
        IDLE_PRIORITY_CLASS         || // Приоритет процесса НАИМЕНЬШИЙ.
        NORMAL_PRIORITY_CLASS       || // Приоритет процесса НОРМАЛЬНЫЙ.
        REALTIME_PRIORITY_CLASS      ; // Приоритет процесса в режиме РЕАЛЬНОГО_ВРЕМЕНИ.
    
    dwCreationFlags = \
        CREATE_DEFAULT_ERROR_MODE  | // He наследовать текущий режим сообщений об ошибках
        CREATE_NEW_CONSOLE         | // Создать новую консоль.
        CREATE_NEW_PROCESS_GROUP   | // Создать новую группу процессов.
        CREATE_SEPARATE_WOW_VDM    | //
        CREATE_SHARED_WOW_VDM      | //
        CREATE_SUSPENDED           | // Создать в приостановленном состоянии.
        CREATE_UNICODE_ENVIRONMENT | // Блок переменных окружения записан в формате UNICODE.
        DEBUG_PROCESS              | // Запустить процесс в отладочном режим.
        DEBUG_ONLY_THIS_PROCESS    | // Предотвратить отладку процесса текущим отладчиком.
        DETACHED_PROCESS           ; // Новый консольный процесс не имеет доступа к консоли родительского консольного процесса.
    


    /* LPSTARTUPINFO, STARTUPINFO */
    lpStartupInfo->cb = sizeof(STARTUPINFO); // Размер структуры в байтах.
    lpStartupInfo->lpDesktop = NULL;         // Привязать к рабочему столу.
    lpStartupInfo->lpTitle = NULL;           // Заголовок окна.
    lpStartupInfo->dwX = 0;                  // Смещение по X относительно начального окна.  \ 
    lpStartupInfo->dwY = 0;                  // Смещение по Y относительно начального окна.  /-----> Требуется this->dwFlags == STARTF_USEPOSITION
    lpStartupInfo->dwXSize = 100;            // Ширина окна. \ 
    lpStartupInfo->dwYSize = 100;            // Высота окна. /-----> Требуется this->dwFlags == STARTF_USESIZE
}

void help_Processes (void)
{   
    /**
     * @brief Создать новый процесс. После создания процесса программа продолжает своё выполнение.
     * 
     * @param lpAppName Имя процесса.
     * @param lpCommLine Команда для запуска программы.
     * @param lpProcAttrs Дескриптор безопасности для процесса.
     * @param lpThreadAttrs Дескриптор безопасности для потоков.
     * @param bInheriteHandles Дескриптор параметра наследования.
     * @param dwCreationFlags Флаги создания.
     * @param lpEnv Блок конфигураций нового процесса (NULL - наследование конфигураций из вызывающего процесса).
     * @param lpCWD Определение текущей рабочей директории для нового процесса (NULL - наследуется от вызывающего процесса).
     * @param lpStartupInfo Информация о запуске процесса.
     * @param lpProcInfo Возращаемые PID и PD процесса.
     * 
     * @return BOOL 1, если процесс был успешно создан.
     * 
     */
    CreateProcess(
        lpAppName, lpCommLine,
        lpProcAttrs, lpThreadAttrs,
        bInheriteHandles,
        dwCreationFlags,
        lpEnv, lpCWD, lpStartupInfo, lpProcInfo
    );
    
    /**
     * @brief Создать поток в виртуальном адресном пространстве другого потока.
     * 
     * @param hProc Дескриптор процесса.
     * @param lpThreadAttrs Дескриптор защиты.
     * @param dwStackSize Размер начального процесса.
     * @param lpStartAddr Функция.
     * @param lpParam Указатель на переменную, передающуюся в поток.
     * @param dwCreationFlags Флаги создания потока.
     * @param lpThreadId Указатель на переменную, которая принимает указатель потока.
     */
    CreateRemoteThread(
        hProc, lpThreadAttrs,
        dwStackSize, lpStartAddr,
        lpParam, dwCreationFlags, lpThreadId
    );

    /**
     * @brief Получить данные о состоянии завершения работы процесса.
     * 
     * @param hProc Дескриптор процесса.
     * @param lpExitCode Данные о статусе завершения.
     */
    GetExitCodeProcess(hProc, lpExitCode);

    /**
     * @brief Получить значение класса приоритета для данного процесса.
     * 
     * @param hProc Дескриптор процесса.
     */
    GetPriorityClass(hProc);

    /**
     * @brief Установить значение класса приоритета для данного процесса.
     * 
     * @param hProc Дескриптор процесса.
     * @param dwPrioClass Значение класса приоритета.
     */
    SetPriorityClass(hProc, dwPrioClass);


    
    GetProcessAffinityMask();

    /**
     * @brief Установить ядро, на котором будет работать процесс.
     * 
     * @param hProc Дескриптор процесса.
     * @param 1<<2 Выбор ядра.
     */
    SetProcessAffinityMask(hProc, 1<<2);

    /**
     * @brief Получить значение динамического форсажа для данного процесса.
     * 
     * @param hProc Дескриптор процесса.
     * @param pDisablePrioBoost TRUE, если динамический форсаж запрещён.
     */
    GetProcessPriorityBoost(hProc, pDisablePrioBoost);

    /**
     * @brief Установить значение динамического форсажа для данного процесса.
     * 
     * @param hProc Дескриптор процесса.
     * @param DisablePrioBoost TRUE, если динамический форсаж запрещён.
     */
    SetThreadPriorityBoost(hProc, DisablePrioBoost);

    GetProcessShutdownParameters();
    SetProcessShutdownParameters();

    GetProcessWorkingSetSize();
    SetProcessWorkingSetSize();

    /**
     * @brief Убить процесс и все его потоки. Не убивает дочерние процессы.
     * 
     * @param hProc Дескриптор процесса.
     * @param uExitCode Код выхода.
     */
    TerminateProcess(hProc, uExitCode);

    /**
     * @brief Завершить работу процесса (Вызывается изнутри этого процесса).
     * 
     * @param uExitCode Код выхода.
     */
    ExitProcess(uExitCode);

    GetProcessVersion();

    /**
     * @brief Получить информацию о распределении интервалов времени для данного процесса.
     * 
     * @param hProc Дескриптор процесса.
     * @param lpCreationTime Время создания процесса.
     * @param lpExitTime Время выхода из работы процесса.
     * @param lpKernelTime Время работы процесса. в режиме ядра.
     * @param lpUserTime Время работы процессса в режиме пользователя.
     */
    GetProcessTimes(
        hProc,
        lpCreationTime, lpExitTime, lpKernelTime, lpUserTime
    );

    /**
     * @brief Получить информацию о запуске текущего процесса.
     * 
     * @param lpStartupInfo Информация о текущем процессе.
     */
    GetStartupInfo(lpStartupInfo);
}


int nPriority;
DWORD dwMilliseconds, dwExitCode;
HANDLE hHandle, hThread;

void help_Threads (void)
{
    /**
     * @brief Создать поток в вызывающем процессе.
     * 
     * @param lpThreadAttrs Дескриптор безопасности для потоков.
     * @param dwStackSize Размер стека для создаваемого потока в байтах. 0 - значение по умолчанию (1Мб).
     * @param lpStartAddr Функция.
     * @param lpParam Указатель на переменную, передающуюся в поток.
     * @param dwCreationFlags Флаги создания потока.
     * @param lpThreadId Указатель на переменную, которая принимает указатель потока. 
     */
    CreateThread(
        lpThreadAttrs, dwStackSize, lpStartAddr,
        lpParam, dwCreationFlags, lpThreadId
    );
    AttachThreadInput();

    /**
     * @brief Завершить работу текущего потока.
     * 
     * @param uExitCode Код завершения.
     */
    ExitThread(uExitCode);

    /**
     * @brief Убить указанный поток.
     * 
     * @param hThread Дескриптор потока.
     * @param dwExitCode Код завершения.
     */
    TerminateThread(hThread, dwExitCode);

    /**
     * @brief Получить дескриптор для текущего потока.
     */
    GetCurrentThread();

    /**
     * @brief Получить TID текущего потока.
     */
    GetCurrentThreadId();

    /**
     * @brief Получить данные о состоянии завершения данного потока.
     * 
     * @param hThread Дескриптор потока.
     * @param lpExitCode Статус завершения.
     */
    GetExitCodeThread(hThread, lpExitCode);

    /**
     * @brief Получить значение приоритета для данного потока.
     * 
     * @param hThread Дескриптор потока.
     * 
     * @return int Значение приоритета.
     */
    GetThreadPriority(hThread);

    /**
     * @brief Установить занчение приоритета для заданного потока.
     * 
     * @param hThread Дескриптор потока.
     * @param nPriority Приоритет.
     * 
     * @return BOOL Успещно ли завершена операция.
     */
    SetThreadPriority(hThread, nPriority);
    GetThreadPriorityBoost();
    SetThreadPriorityBoost();

    /**
     * @brief Получить информацию о распределении интервалов времени для заданного потока.
     * 
     * @param hThread Дескриптор потока.
     * @param lpCreationTime Время создания потока.
     * @param lpExitTime Время выхода потока.
     * @param lpKernelTime Время работы в режиме ядра.
     * @param lpUserTime Время работы в режиме пользователя.
     * 
     * @return BOOL 0, если команда завершилась с ошибкой.
     */
    GetThreadTimes(
        hThread,
        lpCreationTime, lpExitTime, lpKernelTime, lpUserTime
    );

    /**
     * @brief Приостановить работу данного потока.
     * 
     * @param hThread Дескриптор потока.
     * 
     * @return DWORD -1, если не удалось приостановить поток, иначе счёт времени предыдущей приостановки потока.
     */
    SuspendThread(hThread);

    /**
     * @brief Уменьшает счёт времени приостановки потока. При достижении значения 0 продолжается выполнение потока.
     * 
     * @param hThread Дескриптор потока.
     * 
     * @return DWORD -1, если выполнение команды завершилось с ошибкой, иначе значение счета времени приостановки работы потока.
     */
    ResumeThread(hThread);

    SetThreadAffinityMask();
    SetThreadIdealProcessor();

    /**
     * @brief Передать выполнение программы другому, готовому потоку.
     * 
     * @return BOOL 0, если не удалось переключиться на другой поток, иначе не нулевое значение.
     */
    SwitchToThread();


    /**
     * @brief Приостановить выполнение указанного процесса/потока до указанного состояния или до истечения времени.
     * 
     * @param hHandle Дескриптор потока/процесса.
     * @param dwMilliseconds Время ожидания в миллисекундах (INFINITE - ждать бесконечно долго).
     */
    WaitForSingleObject(hHandle, dwMilliseconds);
}
