% ### АНАЛИЗ СТОХАСТИЧЕСКОЙ УСТОЙЧИВОСТИ ### %

%====Блок-начальных-данных===%
m = 5;   n = 1000;

a_min = [
    0.30; 0.30;
    0.30; 0.10;
    0.04;
];

a_max = [
    0.72; 0.72;
    0.72; 0.20;
    0.94;
];

B = zeros ([m, n]);
q = zeros([m, n]);



%====Блок-основного-тела-скрипта====%
clc;

A = rand ([m, n]);                % Создание матрицы чисел
A(:,1:10);                         % Вывод первых 10-ти столбцов

% Заполнение матрицы B
for row = 1:m
    for col = 1:n
        B(row, col) = log_zn (a_min(row), a_max(row), A(row, col));
    end;
end;

% Вычисление q
for i = 1:m
    q(i,:) = fregp (B(i,:));
end;

% Отображение полученных значений в виде графиков
tiledlayout(3, 2);

for i = 1:(m - 1)
    t = nexttile;
    semilogx (q(i,:));
    title(t, "a_{" + i + "min} = " + a_min(i) + "             a_{" + i + "max} = " + a_max(i));
end;

t = nexttile ([1, 2]);
semilogx (q(m,:));
title(t, "a_{" + m + "min} = " + a_min(m) + "             a_{" + m + "max} = " + a_max(m));
