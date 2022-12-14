a = 0;
b = 1.5;
h = 0.15;
params = 'r:d';

x = a:h:b;
y = (2 .* exp(-x)) ./ (2 * pi + x .^ 3);

plot (x, y, params);

% Настройка внешнего вида
title ('График функции по Варианту');             % Изменить название графика
legend ('f(x) = (2 * e^{-x}) / (2 * pi + x^3)');  % Изменить легенду
xlabel ('Ось X');                                 % Изменить подписи осей
ylabel ('Ось Y');
grid on;                                          % Изменить отображение сетки