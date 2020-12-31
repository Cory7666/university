Program LW_5;

Const nrow = 1000;
      ncol = 1000;

Type matrix=array[1..nrow] of array[1..ncol] of integer;

Var a: matrix;
    answer: longint;

{функция-вычисления-суммы-элементов-в-строках}
Function sumElem(const a: matrix): integer;
Var i, j, sumRow, sumAnswer: integer;
begin
  sumRow    := 0;
  sumAnswer := 0;
  for i := 1 to nrow do
  begin
    sumRow := 0;
    for j := 1 to ncol do
    begin
      if a[i][j] < 0 then
      begin
        sumRow := 0;
        break
      end;
      sumRow := sumRow + a[i][j]
    end;
    sumAnswer := sumAnswer + sumRow
  end;
  sumElem := sumAnswer
end;

{Функция-вычисления-суммы-элементов}
{в-диагонали,-параллельной-главной}
Function sumDiagElem(const a: matrix; const row: integer; const col: integer): longint;
Var sum: longint;
    i: integer;
begin
  i := 0; sum := 0;
  {Магическая функция...}
  while ((row + i <= nrow) and (col + i <= ncol)) do
  begin
    sum := sum + a[row + i][col + i];
    i := i + 1
  end;
  sumDiagElem := sum;
end;

{Функция-вычисления-минимальной-суммы}
{элементов-по-диагонали}
Function minSumDiagElem(const a: matrix): longint;
Var minSum, sum: longint;
    i: integer;
begin
  minSum := sumDiagElem(a, 1, 1);
  
  {Подсчёт сумм, диагонали которых начинаются с первой строчки}
  for i := 2 to ncol do
  begin
    sum := sumDiagElem(a, 1, i);
    minSum := (sum < minSum) ? sum : minSum
  end;
  
  {Подсчёт сумм, диагонали которых начинаются с первого столбца}
  for i := 2 to nrow do
  begin
    sum := sumDiagElem(a, i, 1);
    minSum := (sum < minSum) ? sum : minSum
  end;
  
  minSumDiagElem := minSum
end;

{----Функция-ввода-матрицы----}
Function inputMatrix(): matrix;
Var i, j: integer;
    a: matrix;
begin
  for i := 1 to nrow do
    for j := 1 to ncol do
      a[i][j] := random(200) - 100;
  inputMatrix := a;
end;

{----Процедура-вывода-матрицы----}
Procedure printMatrix(const a: matrix);
Var i, j: integer;
begin
  for i := 1 to nrow do
  begin
    write('( ');
    for j := 1 to ncol do
      write(a[i][j]:4, ' ');
    writeln()
  end
end;



{----Основная-программа-------}
BEGIN
  writeln('Введите элементы матрицы ', nrow, 'x', ncol, ':');
  a := inputMatrix();
  writeln('Введена матрица:');
  printMatrix(a);
  writeln('Ответ 1: ', sumElem(a));
  writeln('Ответ 2: ', minSumDiagElem(a));
  writeln(‘Конец работы программы.’);
  readln();
END.