from math import pi, exp, atan, sin
import matplotlib.pyplot as pp


def discrete_signal_decor(f_d: float, n: int = 20):
    def discrete_signal(func):
        def __wrap(omega: float, *args):
            s = 0
            for n_current in range(-(n // 2), n // 2):
                s += func(omega - 2 * pi * f_d * n_current, *args)
            return s
        return __wrap
    return discrete_signal


def angle(c: complex) -> float:
    return atan(c.imag / c.real)


def f(t: float, A: float, k: float) -> float:
    return A * exp(-k * abs(t))


@discrete_signal_decor(20)
def f_fourier(alpha: float, ampl: float, omega: float) -> float:
    return ampl * (2 * alpha) / (alpha ** 2 + omega ** 2)


def f_yield(func, A: float, k: float, x_delta: float, x_start: float, x_stop: float):
    current_value = x_start
    while current_value <= x_stop:
        yield (current_value, func(current_value, A, k))
        current_value += x_delta

#@discrete_signal_decor(20)
def f_digital_fourier(omega: float, A: float, tau: float) -> complex:
    t = omega * tau / 2
    return complex(A * tau * (sin(t) / t))


# with open('f.dots', 'w') as file:
#    dot_number = 0
#    for (x, y) in f_yield(f_fourier, 5, 0.5, 0.001, -10, 10):
#        print(x, y, file=file)

def main():
    values = list(f_yield(f_fourier, 1, 0.5, 0.1, -100, +1000))

    pp.plot([x[0].real for x in values], [abs(x[1]) for x in values])
    pp.show()

    pp.plot([x[0].real for x in values], [angle(x[1]) for x in values])
    pp.show()


main()
