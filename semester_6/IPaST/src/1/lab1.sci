A = 1                // Амплитуда
a = 0.5              // Скорость затухания
t = [-10:0.1:10]     // Отсчёты времени
omega = [-20:0.1:20] // Частоты
Fs = 2               // Частота дискретизации
n = [-10:9]          // Копии спектра

function y = s(t)
    y = A * exp(-a * abs(t))
endfunction

function y = S(o)
    y = (2 * a) ./ (a^2 + o.^2)
endfunction

function y = Samp(o)
    y = abs(S(o))
endfunction

function y = Sphase(o)
    _t = S(o)
    y = atan(imag(_t),real(_t))
endfunction



plot(t, s)
xlabel('$t$')
ylabel('$s(t)$')
xgrid()

scf()
plot(omega, Samp)
plot(omega, Samp(0) * 0.9)
xlabel('$\omega$')
ylabel('$|S(\omega)|$')
xgrid()

scf()
plot(omega, Sphase)
xlabel('$\omega$')
ylabel('$\phi_s (\omega)$')
xgrid()

omega = [-100:0.1:100]
omega2 = repmat(omega, size(n)(1,2), 1)
shift = (-2 * %pi * Fs) * n
shift = repmat(shift', 1, size(omega2)(1,2))
omega2_sum = omega2 + shift
S_omega = S(omega2_sum)
S_omega = sum(S_omega, 1)
S_omega = S_omega * Fs

scf()
plot(omega, abs(S_omega))
xgrid()
xlabel('$\omega$')
ylabel('$|S(\omega`)|$')
