Program LW_6_19;

Type 
  type_fN = string[80];
Var 
  fileName: type_fN;
  inputFile: text;

{процедура-для-получения-от-пользователя-пути-к-файлу}
{с-текстом-и-проверкой-на-существование-файла}
procedure getFilePath(var fileName: type_fN);
Begin
  write('Введите путь к файлу: '); readln(fileName);
  while not fileExists(fileName) do
  begin
    writeln('(x) Ошибка: файла "', fileName, '" не существует.');
    write('Введите путь к файлу ещё раз: '); readln(fileName)
  end
End;

{-Процедура-печати-предложений-из-файла.-Если-второй-параметр}
{-true,-то-выводятся-предложения,-начинающиеся-с-одной-буквы}
procedure writeSent(var inputFile: text; const oneCharSent: boolean);
Const delimiters = [' ', ',', ':', ';', '-', '—', #10, #13];
      eos        = ['!', '?', '.'];
Var writeSent: boolean;
    symb, buff_symb: char;
begin
  while not eof(inputFile) do
  begin
    buff_symb := ' ';
    //-Считываение-первой-буквы
    while buff_symb in delimiters do
      read(inputFile, buff_symb);
    //-Считывание-следующего-символа
    read(inputFile, symb);
    //-Если-второй-символ-в-предложении-есть-буква,-то
    //-предложение-начинается-с-многобуквенного-слова
    if ( (symb in delimiters) or (symb in eos) ) then
      writeSent := oneCharSent
    else
      writeSent := not oneCharSent;
    
    if writeSent then write(buff_symb, symb);
    
    while not ( (symb in eos) or eof(inputFile) ) do
    begin
      read(inputFile, symb);
      if writeSent then
      begin
        write(symb);
        if symb in eos then writeln();
      end;
    end;
  end;
end;

BEGIN
  //-Получение-пути-к-файлу
  getFilePath(fileName);
  
  //-Открытие-файла-для-чтения
  assign(inputFile, fileName);
  reset(inputFile);
  
  writeln('Предложения, начинающиеся с однобуквенных слов:');
  writeSent(inputFile, true);
  
  //-Переоткрытие-файла
  close(inputFile);
  reset(inputFile);
  
  writeln();
  writeln('Остальные предложения:');
  writeSent(inputFile, false);
  
  //-Конец-программы
  close(inputFile);
  writeln('Конец работы программы. Выход...');
  halt(0)
END.