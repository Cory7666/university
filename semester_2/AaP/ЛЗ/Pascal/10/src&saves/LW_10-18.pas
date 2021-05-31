Program LW_10;

Uses Crt;
Uses TreeABC;
Uses IOFile;

var answer: integer; answerChar: char;
    fileName: string[128];
    i: Data; isDataChanged: boolean;

BEGIN
  var c := new BinTree();
  isDataChanged := false;
  fileName := 'database-v9.18.db';
  
  repeat
    clrscr;
    
    alert(110, 'Интерактивное меню программы');
    alert(010, concat('1 -> Загрузить дерево из файла (по умолчанию "', fileName, '").'));
    alert(010, concat('2 -> Сохранить дерево в файл   (по умолчанию "', fileName, '").'));
    alert(010, '3 -> Удалить старое и создать новое дерево.');
    alert(010, '4 -> Добавить элемент в дерево.');
    alert(010, '5 -> Печать дерева на экран (слева направо).');
    alert(010, '6 -> * my * Найти элемент и вывести длину пути.');
    alert(010, '7 -> Выход из программы.');
    alert(120, 'номер действия');
    readln(answer);
    
    clrscr;
    case answer of
      1:
      begin
        alert(130, 'Дерево в памяти будет удалено.');
        alert(011, 'Запущен процесс загрузки нового дерева...');
        Tree_LoadFromFile(c, fileName);
        alert(020, 'какой-то символ для продолжения...');
        isDataChanged := false;
      end;
      2:
      begin
        alert(130, 'Сохранённое в файле дерево будет удалено.');
        alert(011, 'Запущен процесс сохранения дерева...');
        Tree_SaveToFile(c, fileName);
        alert(020, 'какой-то символ для продолжения...');
        isDataChanged := false;
      end;
      3:
      begin
        alert(130, 'Старое дерево удалено.');
        alert(011, 'Запущен процесс создания нового дерева...');
        Tree_Create(c);
        alert(110, 'Новые элементы были успешно добавлены.');
        alert(020, 'какой-то символ для продолжения...');
        isDataChanged := true;
      end;
      4:
      begin
        alert(111, 'Запуск процесса добавления элемента в дерево...');
        alert(020, 'ФИО (выйти нельзя)');   readln(i.name);
        alert(020, 'год рождения');         readln(i.year);
        alert(020, 'пол товарища');         readln(i.sex);
        alert(020, 'семейное положение');   readln(i.familyPos);
        alert(020, 'количество детей');     readln(i.childrenCnt);
        alert(020, 'оклад');                readln(i.salary);
        
        c.AddElem(i);
        
        alert(110, 'Новый элемент был успешно добавлен.');
        alert(020, 'какой-то символ для продолжения...');
        isDataChanged := true;
      end;
      5:
      begin
        alert(111, 'Запуск процесса печати дерева на экран...');
        if c.GetRoot() = nil then
          alert(040, 'Дерево в оперативной памяти не существует.')
        else
        begin
          Tree_Print(c.GetRoot(), 1);
          alert(110, 'Всё дерево расположилось на ЖК экране.');
        end;
        
        alert(020, 'какой-то символ для продолжения...');
      end;
      6:
      begin
        alert(111, 'Запуск процесса поиска элемента в дереве...');
        
        if c.GetRoot() <> nil then
        begin
            alert(020, 'ФИО (выйти нельзя)');   readln(i.name);
            {alert(020, 'год рождения');         readln(i.year);
            alert(020, 'пол товарища');         readln(i.sex);
            alert(020, 'семейное положение');   readln(i.familyPos);
            alert(020, 'количество детей');     readln(i.childrenCnt);
            alert(020, 'оклад');                readln(i.salary);
            }
            answer := c.GetPathToElem(i);
            
            if answer = -1 then
              alert(141, 'Увы, но введённый элемент не найден...')
            else
              alert(111, concat('Найдено. Длина пути: ', intToStr(answer - 1), ' у.е.'));
        end
        else
          alert(041, 'Для начала заполните дерево.');
        alert(020, 'какой-то символ для продолжения...')
      end;
      7:
      begin
        alert(110, 'Поступило предложение выйти из программы.');
        if isDataChanged then
        begin
          alert(130, 'Есть несохранённые данные.');
          alert(020, 'символ для выбора действия (Y,Д/n,н)');
          readln(answerChar);
          if not ( (lowerCase(answerChar) = 'n') or (lowerCase(answerChar) = 'н') ) then
            Tree_SaveToFile(c, fileName);
        end;
        alert(020, 'какой-то символ для выхода...');
      end;
    end;
    readkey;
  until answer = 7;
END.