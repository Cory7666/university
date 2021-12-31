Program Sort;

Uses Crt, Windows, SysUtils;

Const arr_size = 4200;
      repl_count = 100;

Type arr = array [0..arr_size - 1] of Integer;

procedure shell_sort (var a: arr);
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
end;

procedure fill_array (var a: arr);
var i: Integer;
begin
     for i := 0 to arr_size do
         a[i] := 100;
end;

Var Tstart, Tstop, t_start, t_stop: SYSTEMTIME;
    tmp: DWORD;
    counter: Integer; a: arr;
begin
     SetConsoleCP(1251);
     SetConsoleOutputCP(1251);

     GetSystemTime(Tstart);
     with Tstart do
          writeln('Время Tstart: ', wMinute, ':', wSecond, '.', wMilliseconds);

     GetSystemTime(t_start);

     for counter := 0 to repl_count do
     begin
          fill_array(a);
          shell_sort(a);
     end;

     GetSystemTime(t_stop);
     tmp := (t_stop.wMilliseconds + t_stop.wSecond * 1000 + t_stop.wMinute * 60000) - (t_start.wMilliseconds + t_start.wSecond * 1000 + t_start.wMinute * 60000);
     writeln('Общее время сортировки, мс: ', tmp);
     writeln('Время одной сортировки, мс: ', tmp / repl_count);

     GetSystemTime(Tstop);
     with Tstop do
          writeln('Время Tstop: ', wMinute, ':', wSecond, '.', wMilliseconds);

     Readln();
end.
