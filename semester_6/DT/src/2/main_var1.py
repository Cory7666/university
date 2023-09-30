input_matrix = [
    [0, 0, 0, 0, 0, 0, 0],
    [1, 0, 1, 0, 0, 0, 0],
    [0, 0, 0, 1, 0, 0, 1],
    [0, 1, 0, 0, 1, 1, 0],
    [0, 1, 0, 0, 0, 0, 0],
    [1, 0, 0, 1, 0, 0, 0],
    [0, 0, 1, 0, 0, 1, 0]
]

other_matrix = [
    [0, 0, 1, 1, 0],
    [1, 0, 0, 0, 0],
    [0, 0, 0, 0, 0],
    [1, 0, 0, 0, 1],
    [1, 0, 0, 0, 0]
]

def is_set_empty(s: set) -> bool:
    return len(s) == 0


def get_dominants(matrix: list[list[int]], number: int) -> set[int]:
    return {i for i in range(number) if matrix[number][i] != 0}


def get_dominated(matrix: list[list[int]], number: int) -> set[int]:
    return {i for i in range(number) if matrix[i][number] != 0}


def get_usefulness_koeff(matrix: list[list[int]], number: int, __cache: dict[int, float] = dict()) -> float:
    if number in __cache.keys():
        return __cache[number]

    return_value = None

    if number == 0:
        return_value = 0
    else:
        dominants = get_dominated(matrix, number)
        dominated = get_dominants(matrix, number)

        R_plus = {
            get_usefulness_koeff(matrix, i, __cache)
            for i in dominated
        }

        R_minus = {
            get_usefulness_koeff(matrix, i, __cache)
            for i in dominants
        }

        if is_set_empty(dominated):
            print(f"* for x{number} return min(R_minus) - 1")
            return_value = min(R_minus) - 1
        elif is_set_empty(dominants):
            print(f"* for x{number} return max(R_plus) + 1")
            return_value = min(R_plus) + 1
        else:
            intersection = dominants & dominated

            if is_set_empty(intersection):
                print(f"* for x{number} return (min(R_plus) + max(R_minus)) / 2")
                return_value = (min(R_plus) + max(R_minus)) / 2
            else:
                print(f"* for x{number} return U(dominants & dominated)")
                return_value = get_usefulness_koeff(
                    matrix, max(intersection), __cache)

    __cache[number] = return_value
    return return_value


def main():
    target_matrix = other_matrix
    for i in range(len(target_matrix)):
        print("Dot:", i,
              "Dominants:", get_dominated(target_matrix, i),
              "Dominated:", get_dominants(target_matrix, i),
              "Usefulness:", get_usefulness_koeff(target_matrix, i))


main()
