% Получение матрицы L %
L = rand(4, 1000);

% Образование матриц-строк с бинарными элементами %
A = f1(0.4, 0.9, L(1,:));
B = f1(0.2, 0.6, L(2,:));
C = f1(0.5, 0.8, L(3,:));

% Образование аналогичных матриц-строк *1 %
A1 = f1(0.4, 0.9, L(4,:));
B1 = f1(0.2, 0.6, L(4,:));
C1 = f1(0.5, 0.8, L(4,:));

% Из A, B, C в F %
F = createF(A, B, C);
F1 = createF(A1, B1, C1);

% Нахождение частоты %
myFrequency = calculateFrequency(F);
myFrequency1 = calculateFrequency(F1);

% Вывод ответа %
myFrequency
myFrequency1
