Program lw2;

Var a, b, x, z: real;

{
  a, b, x - вводимые пользователем числа.
  z - результат работы алгоритма.
}

BEGIN
  write('Введите числа a, b и x: ');
  readln(a, b, x); {Считывание значений переменных}
  
  if (x <= a) then
    z := x - 2 * power(cos(x), 2)
  else if (a < x) and (x < b) then
    z := ln(x) * sin(x)
  else
    {Значит x >= b.}
    z := 1.3 + sin(x);
  
  writeln('Результат: ', z);
END.