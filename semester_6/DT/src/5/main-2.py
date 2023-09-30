from dataclasses import dataclass
from typing import Iterable, List, Tuple
from fractions import Fraction as Frac


@dataclass
class Solution:
    values: Tuple[int]

    def to_n_model(self, model: List[int], do_sort: bool = False) -> 'Solution':
        model = [4, 1, 6, 2, 1]
        vals: List[int] = []
        for (index, val) in enumerate(self.values):
            vals += [val] * model[index]
        if do_sort:
            vals.sort(reverse=True)
        return Solution(values=tuple(vals))

    def __gt__(self, other: 'Solution') -> bool:
        dominant_flag, dominated_flag = False, False
        for (x, y) in zip(self.values, other.values):
            if x > y:
                dominant_flag = True
            elif x < y:
                dominated_flag = True
        return dominant_flag and not dominated_flag
    
    def get_n_model(self):
        return [4, 1, 6, 2, 1]

    def __str__(self) -> str:
        return "x = {%s}" % (', '.join([str(num) for num in self.values]))

@dataclass
class CountableInfoCriteria:
    name: int
    compare_table: list[int]

    def compare_with(self, idx: int) -> int:
        return self.compare_table[idx]


def print_solutions(sols: Iterable[Solution]):
    for sol_index, sol in enumerate(sols):
        print("%2d) " % sol_index, end='')
        for val in sol.values:
            print("%2d " % val, end='')
        print()

@dataclass
class NModelElement:
    idx: int

    def update(self, value: int):
        self.idx = value
    
    def mult(self, val: int):
        self.update(self.idx * val)
    
    def __int__(self):
        return self.idx

def to_n_model(n_model, criteria_info_table):
    for idx in range(len(n_model)):
        p = 1
        for i in range(len(n_model)):
            if criteria_info_table[idx][i] > 0:
                p *= criteria_info_table[idx][i]
        if isinstance(p, Frac):
            for row in range(len(n_model)):
                if criteria_info_table[row][idx] > 1:
                    n_model[row] *= p.denominator
            p = int(p.denominator * p)
        n_model[idx] = p * n_model[idx]

def main():
    m = {0: 4, 2: 6}
    solutions = [
        Solution(values=(3, 5, 5, 4, 4)),
        Solution(values=(4, 4, 4, 5, 4)),
        Solution(values=(5, 4, 3, 3, 5)),
        Solution(values=(3, 5, 3, 5, 3)),
        Solution(values=(4, 2, 4, 5, 5)),
        Solution(values=(3, 5, 3, 5, 3)),
        Solution(values=(5, 3, 4, 3, 4)),
        Solution(values=(4, 5, 3, 4, 3)),
    ]

    criteria_info_table = [
        [          1, 0,           0,           2, 0],
        [          0, 1,           0, Frac('1/2'), 1],
        [          0, 0,           1,           3, 0],
        [Frac('1/2'), 2, Frac('1/3'),           1, 0],
        [          1, 0,           0,           0, 1],
    ]

    print("Информация о важности критериев:")
    for i in range(len(criteria_info_table)):
        for j in range(len(criteria_info_table[i])):
            print("%5s " % str(criteria_info_table[i][j]), end='')
        print()

    n_model = [1, 1, 1, 1, 1]
    to_n_model(n_model, criteria_info_table)

    mapped_solutions = [sol.to_n_model(n_model, True) for sol in solutions]

    print("Решения:")
    print_solutions(solutions)
    print("N-модель:", solutions[0].get_n_model())
    print_solutions([sol.to_n_model(n_model, False) for sol in solutions])
    print()
    print_solutions(mapped_solutions)

    exclude_set: set[int] = set()

    for sol_index, sol in enumerate(mapped_solutions):
        for other_sol_index, other_sol in enumerate(mapped_solutions):
            if sol_index != other_sol_index:
                if other_sol > sol:
                    exclude_set.add(sol_index)

    print("Исключённые из рассмотрения решения:",
          ', '.join([str(x) for x in exclude_set]))

    print("Ответ:")
    for (index, sol) in enumerate(solutions):
        if index not in exclude_set:
            print(f"{index} -> {sol}")


if __name__ == '__main__':
    main()

