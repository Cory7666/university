unit IOFile;
interface
  Uses TreeABC;
  
  // Процедура сохранение одного элемента
  procedure Tree_SaveToFile_ForEachElem(const elem: ^Tree; var fileP: file of Data);
  // Процедура сохранения дерева в файл
  procedure Tree_SaveToFile(const c: BinTree; const fileName: string);
  // Процедура загрузки дерева из файла
  procedure Tree_LoadFromFile(var c: BinTree; const fileName: string);
  
implementation
  procedure Tree_SaveToFile_ForEachElem(const elem: ^Tree; var fileP: file of Data);
  begin
    if elem = nil then exit;
    write(fileP, elem^.info);
    Tree_SaveToFile_ForEachElem(elem^.pL, fileP);
    Tree_SaveToFile_ForEachElem(elem^.pR, fileP);
  end;
  
  procedure Tree_SaveToFile(const c: BinTree; const fileName: string);
  var fileP: file of Data;
  begin
    if c.GetRoot() = nil then
    begin
      alert(040, 'Нечего сохранять в файл, а значит данные в файле сохранены.');
      exit
    end;
    
    assign(fileP, fileName);
    rewrite(fileP);
    
    Tree_SaveToFile_ForEachElem(c.GetRoot(), fileP);
    
    close(fileP);
    alert(010, 'Данные успешно загружены в файл.');
  end;
  
  procedure Tree_LoadFromFile(var c: BinTree; const fileName: string);
  var fileP: file of Data;
      counter: integer;
      i: Data;
  begin
    assign(fileP, fileName);
    if not fileExists(fileName) then
    begin
      alert(040, 'Файл сохранений не доступен для чтения. Будет создан новый файл.');
      rewrite(fileP);
    end
    else
    begin
      reset(fileP);
      if fileSize(fileP) < 1 then
          alert(040, 'Данные в файле отсутствуют. Ничего не загруженено, всё сохранено.')
      else
      begin
        c.DeleteAll();
        counter := 0;
        reset(fileP);
        while not eof(fileP) do
        begin
          read(fileP, i); c.AddElem(i);
          counter := counter + 1;
        end;
        alert(010, concat('Успешно импортировано записей: ', intToStr(counter), '.'));
      end
    end;
    close(fileP)
  end;

initialization
end.