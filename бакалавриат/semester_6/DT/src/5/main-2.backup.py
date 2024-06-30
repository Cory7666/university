from dataclasses import dataclass
from typing import Iterable, List, Tuple


@dataclass
class Solution:
    values: Tuple[int]

    def to_n_model(self, model: List[int]) -> 'Solution':
        vals: List[int] = []
        for (index, val) in enumerate(self.values):
            vals += [val] * model[index]
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

    def __str__(self) -> str:
        return "x = {%s}" % (', '.join([str(num) for num in self.values]))


def print_solutions(sols: Iterable[Solution]):
    for sol_index, sol in enumerate(sols):
        print("%2d) " % sol_index, end='')
        for val in sol.values:
            print("%2d " % val, end='')
        print()


def main():
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

    n_model = [4, 1, 6, 2, 1]

    mapped_solutions = [sol.to_n_model(n_model) for sol in solutions]

    print_solutions(solutions)
    print("N-модель:", n_model)
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
