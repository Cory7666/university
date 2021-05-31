type 
    form = record
        surname, name, otch: string[64];
        marks: record
            math, history, physics: 0..100;
        end;
    end;
    Tstr = record
        data: form;
        next: ^Tstr;
    end;
    fileName = string[128];

// Удаление списка
procedure TableDelete (var first: ^Tstr);
var toDelete: ^Tstr;
begin
  while first <> nil do
  begin
    toDelete := first;
    first := first^.next;
    dispose(toDelete);
  end
end;

// Создание таблицы
procedure TableCreateNew (var first: ^Tstr);
var thisStr, prevStr: ^Tstr; i:form;
begin
  // Удаление таблицы и создание новой
  writeln();
  writeln('=========================================');
  writeln('Инициализация процедуры создания таблицы.');
  writeln('(!) Внимание: таблица в оперативной памяти');
  writeln('    была удалена.                        ');
  writeln('=========================================');
  writeln();
  
  TableDelete(first);
  new(first);
  
  thisStr := first;
  i.marks.history := 0;
  // Ввод новых значений
  while true do
  begin
    write('Введите Фамилию (* для выхода): '); readln(i.surname);
    if i.surname = '*' then
    begin
      if prevStr <> nil then
        dispose(prevStr^.next);
      if first^.data.marks.history = 0 then
        begin
          dispose(first);
          first := nil
        end;
      break
    end;
    write('Введите Имя:                    '); readln(i.name);
    write('Введите Отчество:               '); readln(i.otch);
    write('Введите Оценку: Математика:     '); readln(i.marks.math);
    write('Введите Оценку: История:        '); readln(i.marks.history);
    write('Введите Оценку: Физика:         '); readln(i.marks.physics);
    
    new(thisStr^.next);
    thisStr^.data := i;
    prevStr := thisStr;
    thisStr := thisStr^.next;
    
    writeln();
    writeln('======= Ввод следующей строки =======');
    writeln();
  end;
end;

// Добавление элемента в список
procedure TableElemAdd (var first: ^Tstr);
var lastStr: ^Tstr; i: form;
begin
  
  writeln();
  writeln('=========================================');
  writeln('Инициализация процедуры добавления       ');
  writeln('  строки в конец!                        ');
  writeln('=========================================');
  writeln();
  
  // Получение данных от пользователя
  write('Введите Фамилию:            '); readln(i.surname);
  write('Введите Имя:                '); readln(i.name);
  write('Введите Отчество:           '); readln(i.otch);
  write('Введите Оценку: Математика: '); readln(i.marks.math);
  write('Введите Оценку: История:    '); readln(i.marks.history);
  write('Введите Оценку: Физика:     '); readln(i.marks.physics);
  
  if first = nil then
  begin
    // Если таблица отсутствует, то создадим новую
    new(first);
    lastStr := first
  end
  else
  begin
    // Если таблица существует, то найдём последний элемент
    lastStr := first;
    while lastStr^.next <> nil do
      lastStr := lastStr^.next;
    new(lastStr^.next);
    lastStr := lastStr^.next
  end;
  lastStr^.data := i;
  
  writeln();
  writeln('=========================================');
  writeln('Операция завершена: строка была успешно  ');
  writeln('   добавлена!                            ');
  writeln('=========================================');
  writeln();
end;

// Исключение первого элемента из списка
procedure TableElemDel (var first: ^Tstr);
var toDelete: ^Tstr;
begin
  if first = nil then
  begin
    writeln();
    writeln('=========================================');
    writeln('ERROR: Таблица и так пуста!!!            ');
    writeln('=========================================');
    writeln();
  end
  else
  begin
    toDelete := first;
    first := first^.next;
    dispose(toDelete);
    
    writeln();
    writeln('=========================================');
    writeln('Операция завершена: строка была успешно  ');
    writeln('   удалена!                            ');
    writeln('=========================================');
    writeln();
  end;
end;

// Печать списка
procedure TablePrint (thisStr: ^Tstr);
var counter: integer;
begin
  if thisStr = nil then
  begin
    writeln();
    writeln('=========================================');
    writeln('ERROR: Таблица и так пуста!!!            ');
    writeln('=========================================');
    writeln();
  end
  else
  begin
    counter := 0;
    while thisStr <> nil do
    begin
        counter := counter + 1;
        writeln(
            counter,                       ' | ',
            thisStr^.data.surname:20,      ' | ',
            thisStr^.data.name:20,         ' | ',
            thisStr^.data.otch:20,         ' | ',
            thisStr^.data.marks.math:3,    ' | ',
            thisStr^.data.marks.history:3, ' | ',
            thisStr^.data.marks.physics:3
        );
        thisStr := thisStr^.next
    end;
  end;
end;

// Сохранение в файл
procedure TableSave (var first: ^Tstr; const fN: fileName);
var f: file of form;
    thisStr: ^Tstr;
begin
  assign(f, fN);
  rewrite(f);
  
  thisStr := first;
  
  while thisStr <> nil do
  begin
    write(f, thisStr^.data);
    thisStr := thisStr^.next
  end;
  
  close(f);
  
  writeln();
  writeln('=========================================');
  writeln('Операция завершена: таблица была сохранена');
  writeln('   и может быть загружена!               ');
  writeln('=========================================');
  writeln();
end;

// Загрузка из файла
procedure TableLoad (var first: ^Tstr; const fN: fileName);
var f: file of form;
    thisStr, prevStr: ^Tstr;
    counter: integer;
begin
  TableDelete(first);
  
  counter := 0;
  assign(f, fN);
  if not fileExists(fN) then
  begin
    writeln();
    writeln('=========================================');
    writeln('ERROR: Файл не возможно прочитать!!!     ');
    writeln('=========================================');
    writeln();
  end
  else
  begin
      reset(f);
      
      new(first);
      thisStr := first;
      
      while not eof(f) do
      begin
        prevStr := thisStr;
        read(f, thisStr^.data);
        new(thisStr^.next);
        thisStr := thisStr^.next;
        counter := counter + 1
      end;
      
      if first <> thisStr then
        dispose(prevStr^.next)
      else
        dispose(first);
      close(f);
      
      writeln();
      writeln('=========================================');
      writeln('Операция завершена: таблица была загружена!');
      writeln('=========================================');
      writeln();
  end;
end;


// *new* Удаление последнего элемента
procedure myProcedure (var first: ^Tstr);
var prev, toDelete: ^Tstr;
begin
  if first = nil then
  begin
    writeln();
    writeln('=========================================');
    writeln('ERROR: Таблица и так пуста!!!            ');
    writeln('=========================================');
    writeln();
  end
  else 
    if first^.next = nil then
      dispose(first)
    else
    begin
        toDelete := first^.next;
        prev := first;
        while toDelete^.next <> nil do
        begin
            prev := toDelete;
            toDelete := prev^.next
        end;
        dispose(prev^.next)
    end;
    writeln();
    writeln('=========================================');
    writeln('Операция завершена: Элемент удалён!      ');
    writeln('=========================================');
    writeln();
end;


var answer: integer;
    myTable: ^Tstr;
    defaultFileName: fileName;

begin
  // ...
  myTable := nil;
  defaultFileName := 'dont_delete_this_data';
  
  // Основная программа
  while true do
  begin
    writeln();
    writeln('=========================================');
    writeln('Выберите действие:                              ');
    writeln('1 - Загрузить из файла (файл: ', defaultFileName, '). ');
    writeln('2 - Сохранить в файл   (файл: ', defaultFileName, '). ');
    writeln('3 - Очистить таблицу в памяти и создать новую.  ');
    writeln('4 - Показать таблицу из памяти.                 ');
    writeln('5 - Добавить в конец.                           ');
    writeln('6 - Удалить первый.                             ');
    writeln('7 - Удалить последний. * my *                   ');
    writeln('8 - Выход из программы.                         ');
    
    write('Ввод: -> '); readln(answer);
    case answer of
      1: TableLoad(myTable, defaultFileName);
      2: TableSave(myTable, defaultFileName);
      3: TableCreateNew(myTable);
      4: TablePrint(myTable);
      5: TableElemAdd(myTable);
      6: TableElemDel(myTable);
      7: myProcedure(myTable);
      8: break;
      else writeln('(!) Неверная команда!');
    end;
  end;
end.