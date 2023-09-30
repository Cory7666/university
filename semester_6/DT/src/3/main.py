from typing import Callable
from matplotlib import pyplot as pp


class UsefulnessFunction:
    def __init__(self, a: float, b: float) -> None:
        self.a = a
        self.b = b

    def __call__(self, x: float) -> float:
        return self.b + self.a * x

    def __str__(self) -> str:
        return f"U(x) = {self.b} + ({self.a}) * x"


def plot_indifference_curves(
    values1: list[float],
    values2: list[float],
    f1: Callable[[float], float],
    f2: Callable[[float], float]
):
    crit1 = sorted(f1(value) for value in values1)
    crit2 = sorted(f2(value) for value in values2)

    for level in range(1, len(crit1)):
        pp.plot(
            list(crit1[i] for i in range(level+1)),
            list(crit2[level - i] for i in range(level+1)),
            marker='.'
        )
    pp.grid(True)
    pp.title('Кривые безразличия для двух критериев')
    pp.show()

def plot_usefulness_curves(
    values1: list[float],
    values2: list[float],
    f1: Callable[[float], float],
    f2: Callable[[float], float]
):
    pp.plot(list(f1(x) for x in sorted(values1, reverse=True)), list(range(len(values1))), marker='.')
    pp.grid(True)
    pp.title('Функция полезности по первому критерию')
    pp.show()

    pp.plot(list(f2(x) for x in sorted(values2, reverse=True)), list(range(len(values2))), marker='.')
    pp.grid(True)
    pp.title('Функция полезности по второму критерию')
    pp.show()


def get_usefulness_functions(
    values1: list[float],
    values2: list[float],
    disc_step_1: int,
    disc_step_2: int
) -> tuple[UsefulnessFunction, UsefulnessFunction]:

    disc_param1 = tuple(min(values1) + disc_step_1 *
                        i for i in range(len(values1)))
    disc_param2 = tuple(min(values2) + disc_step_2 *
                        i for i in range(len(values2)))
    usefulness = tuple(x for x in range(len(values1) - 1, -1, -1))

    param1_sum = sum(disc_param1)
    param2_sum = sum(disc_param2)
    usefulness_sum = sum(usefulness)
    xi_param1_sum = sum(disc_param1[i] * usefulness[i]
                        for i in range(len(usefulness)))
    xi_param2_sum = sum(disc_param2[i] * usefulness[i]
                        for i in range(len(usefulness)))
    param1_sq_sum = sum(x ** 2 for x in disc_param1)
    param2_sq_sum = sum(x ** 2 for x in disc_param2)

    a1 = ((len(disc_param1) * xi_param1_sum - param1_sum * usefulness_sum)
          / (len(disc_param1) * param1_sq_sum - (param1_sum ** 2)))
    a2 = ((len(disc_param2) * xi_param2_sum - param2_sum * usefulness_sum)
          / (len(disc_param2) * param2_sq_sum - (param2_sum ** 2)))

    b1 = (usefulness_sum - a1 * param1_sum) / len(disc_param1)
    b2 = (usefulness_sum - a2 * param2_sum) / len(disc_param2)

    return (UsefulnessFunction(a1, b1), UsefulnessFunction(a2, b2))


def main():
    values1 = (30, 50, 80, 25)
    values2 = (45, 30, 20, 55)

    plot_usefulness_curves(values1, values2, lambda x: 1/x, lambda x: 1/x)
    plot_indifference_curves(values1, values2, lambda x: 1/x, lambda x: 1/x)
    f1, f2 = get_usefulness_functions(values1, values2, 25, 20)

    print(f1)
    print(f2)

    result = []
    for x1, x2 in zip(values1, values2):
        result.append(f1(x1) + f2(x2))

    print(result)

    print(f"Максимальное значение у index={result.index(max(result))}")


main()
