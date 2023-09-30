from dataclasses import dataclass
from functools import cached_property
from typing import Callable, Iterable
from numpy import linalg
from matplotlib import pyplot as pp


@dataclass
class Point:
    value: tuple[float]


@dataclass
class InputData:
    values: tuple[float]
    criteria_func: Callable[[float], float]

    @cached_property
    def criteria_values(self):
        return tuple(self.criteria_func(x) for x in self.values)

    @cached_property
    def sorted_criteria_values(self):
        return tuple(sorted(self.criteria_values))


@dataclass
class IndifferenceCurve:
    level: int
    points: tuple[Point]


def calc_indifference_curves(input_data: list[InputData]) -> tuple[IndifferenceCurve]:
    result: list[IndifferenceCurve] = []
    tmp_list: list[Point] = []

    for level in range(1, len(input_data[0].values)):
        for i in range(level+1):
            tmp_list.append(Point(
                (input_data[0].sorted_criteria_values[i], input_data[1].sorted_criteria_values[level-i])
            ))
        result.append(IndifferenceCurve(level, tuple(tmp_list)))
        tmp_list = []

    return tuple(result)


def calc_usefulness_coeffs() -> tuple[float, float]:
    pass

def plot_indifference_curves(curves: Iterable[IndifferenceCurve]):
    for curve in curves:
        pp.plot(*list(
            tuple(point.value[dot_index]
                  for point in curve.points
                  ) for dot_index in range(len(curve.points[0].value))
        ))
    pp.show()


def main():
    input_data = [
        InputData((25, 50, 75, 100), lambda x: 1/x),
        InputData((20, 40, 60, 80), lambda x: 1/x),
    ]

    for d in input_data:
        print(d.sorted_criteria_values)

    plot_indifference_curves(calc_indifference_curves(input_data))


main()
