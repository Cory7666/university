Program LW_7;

Uses Crt;

Type tPrice = record
  prName, stName: string[20]; // Наименование товара и Название магазина
  cost: 1..maxint;
end;
  tFile = file of tPrice;
  tPath = string[255];

Var dbFile: tFile;
    command: 0..3;

{Сортирует-базу-данных}
procedure sordDB(var dbFile: tFile);
Var prodA, prodB: tPrice;
    i, j: integer;
begin
  reset(dbFile);
  
  for i := filesize(dbFile) - 2 downto 0 do
  begin
    for j := 0 to i do 
    begin
      seek(dbFile, j); read(dbFile, prodA, prodB);
      if prodA.stName > prodB.stName then
      begin
        seek(dbFile, j);
        write(dbFile, prodB, prodA);
      end;
    end;
  end;
  
  close(dbFile)
end;

{Запись-данных-в-файл}
procedure writeToDB(var dbFile: tFile);
Var prod: tPrice;
begin
  reset(dbFile);
  seek(dbFile, filesize(dbFile));
  
  with prod do
    while true do
    begin
      clrscr();
      writeln('Введите Наименование товара (* для выхода):');
      write(': '); readln(prName);
      
      if prName = '*' then break;
      
      writeln('Введите Название магазина:');
      write(': '); readln(stName);
      writeln('Введите Цену товара:');
      write(': '); readln(cost);
      
      write(dbFile, prod);
    end;
  
  close(dbFile);
  
  sordDB(dbFIle);
end;

{Чтение-всех-данных-из-файла}
procedure readFullDB(var dbFile: tFile);
Var prod: tPrice;
begin
  clrscr;
  reset(dbFile);
  
  writeln('|', ' Название магазина  ', '|', 'Наименование товара ', '|', 'Стоимость товара', '|');
  
  while not eof(dbFile) do
  begin
    read(dbFIle, prod);
    
    with prod do
    begin
      writeln('|', stName:20, '|', prName:20, '|', cost:16, '|');
    end;
  end;
  
  readkey;
  close(dbFile);
end;


{Получает-от-пользователя-путь-к-файлу}
function getFilePath(): tPath;
Var path: tPath;
begin
  writeln(' Введите путь к файлу: ');
  write(': '); readln(path);
  while not fileExists(path) do
  begin
    writeln(' (*) Ошибка: файл не найден.');
    writeln(' Введите путь к файлу ещё раз:');
    write(': '); readln(path)
  end;
  getFilePath := path
end;

{Вывод-товаров-данного-магазина}
procedure findFromStore(var dbFile: tFile);
Var count: integer; prod: tPrice; store: string[20];
begin
  
  clrscr();
  
  count := 0;
  writeln(' Введите название магазина:');
  write(': '); readln(store);
  
  writeln('|', ' №  ', '|', ' Название магазина  ', '|', 'Наименование товара ', '|', 'Стоимость товара', '|');
  
  reset(dbFile);
  
  while not eof(dbFile) do
  begin
    read(dbFile, prod);
    with prod do
      if stName = store then
      begin
        count := count + 1;
        writeln('|', count:4, '|', stName:20, '|', prName:20, '|', cost:16, '|');
      end;
  end;
  
  if count < 1 then writeln('Магазин "', store, '" не найден.');
  
  close(dbFile);
  
  readkey;
end;

BEGIN
  // Получение-пути-к-файлу
  assign(dbFile, getFilePath() );
  
  while true do
  begin
    clrscr();
    writeln('              Меню                 ');
    writeln(' 1 - ввод данных.                  ');
    writeln(' 2 - вывод содержимого базы данных.');
    writeln(' 3 - поиск по магазину.            ');
    writeln(' 0 - выход из программы.           ');
    write(': '); readln(command);
    
    case (command) of
      0: break;
      1: writeToDB(dbFile);
      2: readFullDB(dbFile);
      3: findFromStore(dbFile);
    end;
  end;
  
  // Конец-работы-программы
  writeln();
  writeln(' Выход из программы...');
  readkey;
  halt(0)
END.