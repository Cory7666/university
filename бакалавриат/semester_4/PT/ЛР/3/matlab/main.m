% Начальные параметры %
B = 0.7;
m = 1;
n = 1000;

% Создание массива случайных величин %
arr = raylrnd (B, m, n);

% Математическое ожидание %
M = calculateMathExpect (arr);
% Найти мю_1 %
me_1 = calculateMew (arr, 1);
% Найти мю_2 (дисперсия) %
me_2 = calculateMew (arr, 2);
% Найти мю_3 %
me_3 = calculateMew (arr, 3);
% Найти мю_4 %
me_4 = calculateMew (arr, 4);
% Найти гамма_1 %
gamma_1 = gamma1 (arr);
% Найти гамма_2 %
gamma_2 = gamma2 (arr);
