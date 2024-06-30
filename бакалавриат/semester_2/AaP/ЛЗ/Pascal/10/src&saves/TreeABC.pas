unit TreeABC;
interface
Uses Crt;
Type Data = record
      name: string[32];
      year: integer;
      sex: string[10];
      familyPos: string[16];
      childrenCnt: word;
      salary: integer;
    end;
    
    Tree = record
      info: Data;
      pL, pR: ^Tree;
    end;
    
    BinTree = class
      private
        rootElem: ^Tree;
        
        procedure __DeleteElems(var p: ^Tree);
        begin
          if p <> nil then
          begin
            self.__DeleteElems(p^.pL);
            self.__DeleteElems(p^.pR);
            dispose(p);
            p := nil;
          end;
        end;
        
        procedure __AddElem(var p: ^Tree; const elem: Data);
        begin
          if p = nil then
          begin
            new(p);
            p^.pL := nil; p^.pR := nil;
            p^.info := elem
          end
          else
            if p^.info.name > elem.name then
              self.__AddElem(p^.pL, elem)
            else
              self.__AddElem(p^.pR, elem);
        end;
        
        function __SearchElem(const root:^Tree; const elem: Data; const level: integer): integer;
        begin
          Result := -1;
          if root = nil then exit;
          if root^.info.name = elem.name then
            Result := level
          else
            if root^.info.name < elem.name then
              Result := self.__SearchElem(root^.pR, elem, level + 1)
            else
              Result := self.__SearchElem(root^.pL, elem, level + 1);
        end;
      
      public
        constructor();
        begin
          self.rootElem := nil;
        end;
        
        procedure DeleteAll;
        begin
          self.__DeleteElems(self.rootElem);
        end;
        
        procedure AddElem(const elem: Data);
        begin
          self.__AddElem(self.rootElem, elem);
        end;
        
        function GetRoot() := self.rootElem;
        
        function GetPathToElem(const elem: Data) := self.__SearchElem(self.rootElem, elem, 1);
    end;
    
    // Процедура создания нового дерева или нового поддерева
    procedure Tree_Create (var c: BinTree);
    // Процедура отображения дерева или его подчасти
    procedure Tree_Print(const root: ^Tree; const level: integer);
    // Процедура интерактивного вывода сообщений
    procedure alert(const messageType: word; const message: string);
    
    
    
implementation
  procedure Tree_Create (var c: BinTree);
  var i: Data;
  begin
    c.DeleteAll();
    
    alert(020, 'ФИО товарища (выйти нельзя)'); readln(i.name);
    alert(020, 'год рождения');         readln(i.year);
    alert(020, 'пол товарища');         readln(i.sex);
    alert(020, 'семейное положение');   readln(i.familyPos);
    alert(020, 'количество детей');     readln(i.childrenCnt);
    alert(020, 'оклад');                readln(i.salary);
    
    c.AddElem(i);
    
    alert(110, 'Подготовка к вводу второго товарища (ввод можно будет отменить).');
    alert(120, 'любую кнопку для ввода товарища...');
    readkey;
    
    while true do
    begin
        clrscr;
      
        alert(110, 'Переход к вводу следующего товарища...');
        alert(020, 'ФИО (* для выхода)');   readln(i.name);
        if i.name = '*' then
        begin
          break
        end;
        alert(020, 'год рождения');         readln(i.year);
        alert(020, 'пол товарища');         readln(i.sex);
        alert(020, 'семейное положение');   readln(i.familyPos);
        alert(020, 'количество детей');     readln(i.childrenCnt);
        alert(020, 'оклад');                readln(i.salary);
        
        c.AddElem(i);
        
        alert(110, 'Подготовка к вводу следующего товарища.');
        alert(120, 'любую кнопку для ввода следующего товарища...');
        readkey;
    end;
  end;
  
  procedure Tree_Print(const root: ^Tree; const level: integer);
  var m: integer;
  begin
    if root = nil then
      exit;
    
    m := round( ( log(level) + 0.2 ) * 8 );
    
    writeln();
    Tree_Print(root^.pR, level + 1);
    
    write('':(m*(level-1))); alert(050, concat('     Уровень: ',       intToStr(level)));
    write('':(m*(level-1))); alert(050, concat('         ФИО: ',       root^.info.name));
    write('':(m*(level-1))); alert(050, concat('Год рождения: ',       intToStr(root^.info.year)));
    write('':(m*(level-1))); alert(050, concat('Пол товарища: ',       root^.info.sex));
    write('':(m*(level-1))); alert(050, concat('Семейное положение: ', root^.info.familyPos));
    write('':(m*(level-1))); alert(050, concat('Количество детей:   ', intToStr(root^.info.childrenCnt)));
    write('':(m*(level-1))); alert(050, concat('       Оклад: ',       intToStr(root^.info.salary)));
    
    writeln();
    Tree_Print(root^.pL, level + 1);
  end;
  
  procedure alert(const messageType: word; const message: string);
  const maxWidth = 68;
  begin
    case (messageType div 100) of
      1:
          writeln('<===================>', ' ':(maxWidth-40), '<===================>');
    end;
    case ((messageType mod 100) div 10) of
      1:
          begin
              { Обычное сообщение }
              writeln('| ', message, ' |':(maxWidth-length(message)));
          end;
      2:
          begin
              { Сообщение с приглашением для ввода}
              writeln('| Введите ', message);
              write  ('| пользователь$: ')
          end;
      3:
          begin
              { Сообщение с предупреждением }
              writeln('| ', '  ( ! ) Внимание ( ! )', ' |':(maxWidth-22));
              writeln('| ', message, ' |':(maxWidth-length(message)));
          end;
      4:
          begin
            { Сообщение с ошибкой }
            writeln('| ', '  ( x ) Ошибка ( x )', ' |':(maxWidth-20));
            writeln('| ', message, ' |':(maxWidth-length(message)));
          end;
      5:
          begin
            { Обычное сообщение (только левая грань) }
            writeln('| ', message);
          end;
    end;
    case (messageType mod 10) of
      1:
          writeln('<===================>', ' ':(maxWidth-40), '<===================>');
    end;
  end;

//initialization

//finalization

end.