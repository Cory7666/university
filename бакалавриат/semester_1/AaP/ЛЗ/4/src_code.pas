Program LW_4_29;

Const arrayLen = 50;
Var
  a: array [1..arrayLen] of double;
  maxElem, sumElem, tmpVal: double;
  countTrans, countComp,
  n, tmpI, i, j, index1,
  secPosIndex: integer;
  firPosIsFind: boolean;
  {
    maxElem          - ответ на 1 задание.
    sumElem          - ответ на 2 задание.
    countTrans       - количество пересылок.
    countComp        - количество сравнений.
    n                - количество элементов в массиве.
    tmpVal, tmpIndex, i - временные переменные.
    secPosIndex      - индекс второго полож. элемента.
    firPosIsFind     - true, если найден полож. элемент.
  }

BEGIN
  firPosIsFind := false;
  secPosIndex := 0;
  sumElem := 0;
  countComp := 0;
  countTrans := 0;
  
  {Ввод данных}
  write('Введите количество элементов (не более ', arrayLen, '): ');
  readln(n);
  
  for i := 1 to n do
  begin
    write('Введите ', i, ' элемент: ');
    //readln(a[i]);
    a[i] := (random(200000) * 0.01) - 1000; writeln(a[i])
  end;
  
  {Поиск максимального по модулю элемента}
  maxElem := abs(a[1]);
  for i := 2 to n do
    if abs(a[i]) > maxElem then
      maxElem := abs(a[i]);
  
  {Вывод Результата №1}
  writeln('Результат №1: ', maxElem, '.');
  
  {Поиск второго положительного элемента}
  for i := 1 to n do
  begin
    if a[i] > 0 then
      if firPosIsFind then
      begin
        secPosIndex := i;
        break
      end
      else
        firPosIsFind := true;
  end;
  
  {Суммирование элементов после второго  }
  {положительного (если такой был найден)}
  write('Результат №2: ');
  if secPosIndex <> 0 then
    if (secPosIndex + 1) < n then
      begin
        for i := (secPosIndex + 1) to n do
          sumElem := sumElem + a[i];
        writeln(sumElem);
      end
    else
      writeln('Нет элементов после второго положительного.')
  else
    writeln('В массиве отсутствует второй положительный элемент.');
  
  {Сортировка массива по возрастанию }
  for i := 1 to (n - 1) do
  begin
    tmpI   := i;
    tmpVal := a[i];
    
    for j := i + 1 to n do
      if tmpVal > a[j] then
      begin
        tmpI   := j;
        tmpVal := a[j];
      end;
    
    a[tmpI] := a[i];
    a[i]    := tmpVal;
  end;
  
  {Поиск индекса элемента, большего 1}
  
  for i := 1 to n do
    if a[i] > 1 then
    begin
      index1 := i;
      break;
    end;
  
  {Отладочная печать}
  writeln();
  writeln('-----------Отладочная печать----------------');
  writeln('Результат промежуточной сортировки массива: ', a);
  if index1 < (n + 1) then
    writeln('Номер элемента, большего 1: ', index1)
  else
    writeln('В массиве нет элемента, большего 1.');
  writeln();
  
  {Сортировка левой части массива}
  for i := 1 to (index1 - 1) do
  begin
    tmpVal := a[i];
    tmpI   := i;
    
    for j := i + 1 to (index1 - 1) do
    begin
      countComp := countComp + 1;
      if tmpVal < a[j] then
        tmpI := j;
    end;
    
    tmpVal := a[tmpI];
    a[tmpI] := a[i];
    a[i]    := tmpVal;
    countTrans := countTrans + 1;
  end;
  
  {Сортировка правой части массива}
  for i := index1 to n do
  begin
    tmpVal := a[i];
    tmpI   := i;
    
    for j := i + 1 to n do
    begin
      countComp := countComp + 1;
      if tmpVal < a[j] then
        tmpI := j;
    end;
    
    tmpVal := a[tmpI];
    a[tmpI] := a[i];
    a[i]    := tmpVal;
    countTrans := countTrans + 1;
  end;
  
  {Печать результата №3}
  writeln('Преобразованный массив', a);
  writeln('Количество пересылок: ', countTrans);
  writeln('Количество сравнений: ', countComp);
  
  writeln();
  writeln('Конец работы.');
  read();
END.