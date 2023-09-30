from dataclasses import dataclass

TEST = True

@dataclass(frozen=True)
class OperatorContext:
    succeeds: list[list[int]]
    equivs: list[list[int]]

    def iterate_succeeds(self):
        for i in range(len(self.succeeds)):
            for j in range(len(self.succeeds[i])):
                if self.succeeds[i][j] == 1:
                    yield (i, j)
    
    def iterate_equivs(self):
        for i in range(len(self.equivs)):
            for j in range(len(self.equivs[i])):
                if self.is_equiv(i, j):
                    yield (i, j)
    
    def is_succeed(self, i1: int, i2: int) -> bool:
        #return self.succeeds[i1][i2] == 1
        result = False
        if self.succeeds[i1][i2] == 1:
            result = True
        else:
            for sub in self.iterate_succeeds():
                if sub[0] == i1:
                    # для каждого доминируемого элемента в таблице эквивалентности
                    for eqiv in self.iterate_equivs():
                        if eqiv[0] == sub[1]:
                            # для каждого эквивалентного доминируемому элементу элемента
                            if eqiv[1] == i2:
                                return True
                            else:
                                result = self.is_succeed(eqiv[1], i2)
        return result


    def is_equiv(self, i1, i2):
        return self.equivs[i1][i2] == 1

@dataclass(frozen=True)
class Solution:
    values: tuple[float]

    def swap(self, i1: int, i2: int) -> 'SwappedSolution':
        v = list(self.values)
        v[i1], v[i2] = v[i2], v[i1]
        return SwappedSolution(values=tuple(v), swapped_values_indexes=(i1, i2))

    def __str__(self) -> str:
        return f"x = [{', '.join(str(x) for x in self.values)}]"

    def __gt__(self, other: 'Solution') -> bool:
        return len([1 for (x, y) in zip(self.values, other.values) if x > y]) == len(self.values)
    
    def __eq__(self, other: 'Solution') -> bool:
        dominant = False
        dominated = False

        for (x, y) in zip(self.values, other.values):
            if x > y:
                dominant = True
            elif x < y:
                dominated = True
            else:
                continue
        
        return True if dominant == dominated else False

    def is_better_with_context(self, other: 'Solution', ctx: OperatorContext):
        is_better = self > other
        if not is_better:
            dominant, dominated = False, False
            for (i, j) in ctx.iterate_succeeds():
                #print("[DEBUG][/compare]", self.values[i] > other.values[i], self.values[j] > other.values[j])
                if self.values[i] > other.values[i]:
                    dominant = True
                elif self.values[i] < other.values[i]:
                    dominated = True
                elif self.values[i] == other.values[i] and self.values[j] != other.values[j]:
                    dominated = self.values[j] < other.values[j]
                else:
                    continue
            #print("[DEBUG][/is_better]", dominant, dominated)
            is_better = dominant and not dominated
                    
        return is_better
            

@dataclass(frozen=True)
class SwappedSolution(Solution):
    swapped_values_indexes: tuple[int, int]

    def __str__(self) -> str:
        return "x^{%d %d} = [%s]" % (self.swapped_values_indexes[0],
                                     self.swapped_values_indexes[1],
                                     ', '.join(str(x) for x in self.values))

if TEST:
    solutions = [
        Solution((3, 5, 5, 4)),
        Solution((4, 4, 4, 5)),
        Solution((5, 4, 3, 3)),
        Solution((3, 5, 3, 5)),
        Solution((4, 2, 4, 5)),
        Solution((3, 5, 3, 5)),
        Solution((5, 3, 4, 3)),
    ]

    succeeds = [
        [0, 1, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 1],
        [0, 0, 0, 0],
    ]

    equivs = [
        [0, 0, 0, 0],
        [0, 0, 1, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0],
    ]

else:
    # Значения критериев
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

    # Матрица A1

    succeeds = [
        [0, 1, 0, 0, 0],
        [0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0],
        [0, 0, 0, 0, 1],
        [0, 0, 0, 0, 0],
    ]

    # Матрица A2
    equivs = [
        [0, 0, 0, 0, 0],
        [0, 0, 1, 0, 0],
        [0, 0, 0, 1, 0],
        [0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0],
    ]

def main():
    x_omega: list[Solution] = solutions.copy()
    exclude_sols_indexes: set[int] = set()
    ctx = OperatorContext(succeeds, equivs)

    for (index1, sol1) in enumerate(solutions):
        print("Process", sol1)
        for (x, y) in ctx.iterate_succeeds():
            s = sol1.swap(x, y)
            result = sol1.is_better_with_context(s, ctx)

            if result:
                print(f"\n* {sol1} > {s}")
                for (index2, sol2) in enumerate(solutions):
                    if index1 != index2:
                        if index2 not in exclude_sols_indexes:
                            print(f"  * with {sol2}:")
                            result = s.is_better_with_context(sol2, ctx)
                            if result:
                                print(f"      {sol1} > {s} > {sol2}")
                                exclude_sols_indexes.add(index2)
                            else:
                                print(f"      {sol1} > {s} not > {sol2}")
                        else:
                            print(f"  * skip {sol2}")
            else:
                print(f"* {sol1} not > {s}")

        print("Excluded points set:", exclude_sols_indexes)
        print()
        print()

main()
