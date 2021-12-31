Program Master;

Uses Crt, Windows, SysUtils;

Var ProcInfo:  array [1..2] of PROCESS_INFORMATION;
    StartInfo: array [1..2] of STARTUPINFOA;

begin
     StartInfo[1].cb := sizeof(STARTUPINFOA);
     StartInfo[2].cb := sizeof(STARTUPINFOA);


     {// Тест №1
     StartInfo[1].lpTitle := 'Test #1; Process: 01; Priority: 01';
     StartInfo[2].lpTitle := 'Test #1; Process: 02; Priority: 02';

     CreateProcess(nil, '.\sort.exe', nil, nil, false, CREATE_NEW_CONSOLE or CREATE_SUSPENDED, nil, nil, StartInfo[1], ProcInfo[1]);
     CreateProcess(nil, '.\sort.exe', nil, nil, false, CREATE_NEW_CONSOLE or CREATE_SUSPENDED, nil, nil, StartInfo[2], ProcInfo[2]);

     SetPriorityClass(ProcInfo[1].hProcess, IDLE_PRIORITY_CLASS);
     SetPriorityClass(ProcInfo[2].hProcess, NORMAL_PRIORITY_CLASS);
     SetThreadAffinityMask(ProcInfo[1].hThread, 2);
     SetThreadAffinityMask(ProcInfo[2].hThread, 2);

     ResumeThread(ProcInfo[1].hThread);
     ResumeThread(ProcInfo[2].hThread);

     WaitForSingleObject(ProcInfo[1].hProcess, INFINITE);
     WaitForSingleObject(ProcInfo[2].hProcess, INFINITE);
     }


     // Тест №2
     StartInfo[1].lpTitle := 'Test #2; Process: 01; Priority: 01';  // Задать имя для процессов
     StartInfo[2].lpTitle := 'Test #2; Process: 02; Priority: 03';

     // Создать процессы
     CreateProcess(nil, '.\sort.exe', nil, nil, false, CREATE_NEW_CONSOLE or 0, nil, nil, StartInfo[1], ProcInfo[1]);
     SetProcessAffinityMask(ProcInfo[1].hProcess, 1);
     SetPriorityClass(ProcInfo[1].hProcess, NORMAL_PRIORITY_CLASS);

     CreateProcess(nil, '.\sort.exe', nil, nil, false, CREATE_NEW_CONSOLE or 0, nil, nil, StartInfo[2], ProcInfo[2]);
     SetProcessAffinityMask(ProcInfo[2].hProcess, 1);
     SetPriorityClass(ProcInfo[2].hProcess, HIGH_PRIORITY_CLASS);


     // Изменить приоритеты и ядра, на которых будут выполняться потоки процессов
     {SetPriorityClass(ProcInfo[1].hProcess, IDLE_PRIORITY_CLASS);
     SetPriorityClass(ProcInfo[2].hProcess, HIGH_PRIORITY_CLASS);
     SetProcessAffinityMask(ProcInfo[1].hThread, 2);
     SetProcessAffinityMask(ProcInfo[2].hThread, 2);

     // Запустить выполнение потоков
     ResumeThread(ProcInfo[1].hThread);
     ResumeThread(ProcInfo[2].hThread);}

     // Ждать завершения работы процессов
     WaitForSingleObject(ProcInfo[1].hProcess, INFINITE);
     WaitForSingleObject(ProcInfo[2].hProcess, INFINITE);



     {// Тест №3
     StartInfo[1].lpTitle := 'Test #3; Process: 01; Priority: 02';
     StartInfo[2].lpTitle := 'Test #3; Process: 02; Priority: 02';

     CreateProcess(nil, '.\sort.exe', nil, nil, false, CREATE_NEW_CONSOLE or CREATE_SUSPENDED, nil, nil, StartInfo[1], ProcInfo[1]);
     CreateProcess(nil, '.\sort.exe', nil, nil, false, CREATE_NEW_CONSOLE or CREATE_SUSPENDED, nil, nil, StartInfo[2], ProcInfo[2]);

     SetPriorityClass(ProcInfo[1].hProcess, NORMAL_PRIORITY_CLASS);
     SetPriorityClass(ProcInfo[2].hProcess, NORMAL_PRIORITY_CLASS);
     SetThreadAffinityMask(ProcInfo[1].hThread, 2);
     SetThreadAffinityMask(ProcInfo[2].hThread, 2);

     ResumeThread(ProcInfo[1].hThread);
     ResumeThread(ProcInfo[2].hThread);

     WaitForSingleObject(ProcInfo[1].hProcess, INFINITE);
     WaitForSingleObject(ProcInfo[2].hProcess, INFINITE);   }
end.

