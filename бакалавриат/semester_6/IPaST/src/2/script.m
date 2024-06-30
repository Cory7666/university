A = [-20 -14.1421 0 0; 14.1421 0 0 0; -26 -13.2229 -12 -20.8806; 0 0 20.8806 0]
B = [1; 0; 1; 0]
C = [0 0 0 0.0479]
D = 0

[b, a] = ss2tf(A, B, C, D)

% Получение функции передачи
[r, p, C0] = residue(b, a)

% Расчет значений импульсной характеристики системы
t = [0:0.01:2];         % вектор отсчетов времени
h = zeros(1, length(t)); % значения импульсной характеристики
for n=[1:length(r)]
h = h + r(n).*exp(p(n).*t); % n-e слагаемое
end

% График импульсной характеристики
plot(t, real(h));
grid on;
title('Импульсная характеристика системы');
xlabel('t');
ylabel('h(t)');

% График нулей и полюсов системы
figure
[z, p, k] = residue(b, a)
plot(p, 'x')
hold on;
plot(z, 'o');
hold off;
axis equal;
grid on;
axis([-5 5 -5 5]);

% Расчет комплексного коэффициента передачи
w = [0 logspace(-2, 2, 500) inf];
K = freqs(b, a, w);

% Построение годографа
figure;
plot(K)
axis equal
grid on
xlabel('Re');
ylabel('Im');

% Расчет АЧХ и ФЧХ системы
K_amp = abs(K);     % АЧХ
K_phase = angle(K); % ФЧХ
% Устранение скачков в ФЧХ
K_phase_unwrap = unwrap(K_phase);

% Графики АЧХ и ФЧХ
figure
subplot(3, 1, 1);
plot(w, K_amp);
title('Амплитудно-частотная характеристика системы');
xlabel('\omega');
ylabel('|K(\omega)|');
subplot(3, 1, 2);
plot(w, K_phase);
title('Фазочастотная характеристика системы');
xlabel('\omega');
ylabel('arg(K(\omega))');
subplot(3, 1, 3);
plot(w, K_phase_unwrap);
title('Фазочастотная характеристика системы (без скачков)');
xlabel('\omega');
ylabel('arg(K(\omega))');
