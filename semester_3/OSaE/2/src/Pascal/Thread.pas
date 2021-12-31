Program Thread;

Uses Windows, SysUtils;

Const arr_size = 50;
Type arr = array [0..arr_size - 1] of Integer;

VAR a:        arr;

procedure shell_sort ();
var d, i, j, tmp: Integer;
begin
     d := arr_size div 2;
     while (d > 0) do
     begin
          for i := 0 to arr_size do
          begin
               j := i + d;
               while (j < arr_size) do
               begin
                    if (a[i] < a[j]) then
                    begin
                         tmp := a[i];
                         a[i] := a[j];
                         a[j] := tmp;
                    end;
                    j := j + d;
               end;
          end;
          d := d div 2
     end;

     writeln('Sorting is complete.');
end;

procedure fill_array (var a: arr);
var i: Integer;
begin
     for i := 0 to arr_size do
         a[i] := 100;
end;

procedure print_array ();
var i: Integer;
begin
     write('arr = [');
     for i := 0 to (arr_size - 1) do
         write(a[i], ', ');
     writeln(a[arr_size - 1], ']');

     writeln('Printing is complete.');
end;

Var ti1, ti2: DWORD;
    th1, th2: HANDLE;

BEGIN
     fill_array(a);

     th1 := CreateThread(nil, 0, @print_array, nil, CREATE_SUSPENDED, ti1);
     th2 := CreateThread(nil, 0, @shell_sort,  nil, CREATE_SUSPENDED, ti2);

     SetThreadPriority(th1, THREAD_PRIORITY_TIME_CRITICAL);
     SetThreadPriority(th2, THREAD_PRIORITY_LOWEST);

     ResumeThread(th1);
     ResumeThread(th2);

     WaitForSingleObject(th1, INFINITE);
     WaitForSingleObject(th2, INFINITE);
END.
