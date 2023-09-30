from typing import Iterable


task_desc = {
    'eq': [
        [1, 0, 1, 0, 0, 1, 0],
        [0, 1, 0, 0, 1, 0, 0],
        [1, 0, 1, 0, 0, 1, 0],
        [0, 0, 0, 1, 0, 0, 1],
        [0, 1, 0, 0, 1, 0, 0],
        [1, 0, 1, 0, 0, 1, 0],
        [0, 0, 0, 1, 0, 0, 1]
    ],
    "rel": [
        [0, 0, 0, 0, 0, 0, 0],
        [1, 0, 1, 0, 0, 1, 0],
        [0, 0, 0, 0, 0, 0, 0],
        [0, 1, 0, 0, 1, 0, 0],
        [1, 0, 1, 0, 0, 1, 0],
        [0, 0, 0, 0, 0, 0, 0],
        [0, 1, 0, 0, 1, 0, 0]
    ]
}


def range_of_rational_number(numerator: int):
    denominator = 1
    while True:
        yield numerator / denominator


def is_set_empty(s: set) -> bool:
    return len(s) == 0


def iterate_equivalence_classes(equiv_matrix: list[list[int]]):
    """
    Итерировать по классам эквивалентности в переданной матрице эквивалентности.
    """
    n = len(equiv_matrix)
    for row in range(n):
        return_set = {
            col
            for col in range(n)
            if equiv_matrix[row][col]
        }

        if not is_set_empty(return_set):
            yield return_set


def get_set_of_equivalence_classes(equiv_matrix: list[list[int]]) -> set[set[int]]:
    """
    Получить все существующие классы эквивалентности в матрице эквивалентности
    в виде множества.
    """
    return_set = set()
    for clazz in iterate_equivalence_classes(equiv_matrix):
        return_set.add(frozenset(clazz))
    return return_set


def compare_decisions(
    rel_matrix: list[list[int]],
    first_des: int,
    second_des: int
) -> int:
    """
    Сравнить два решения в соответствие с матрицей отношений предпочтения.
    Вернуть:
    * 0, если решения эквивалентны;
    * больше нуля, если first_des лучше second_des;
    * меньше нуля, если second_des лучше first_des.
    """
    return rel_matrix[first_des][second_des] - rel_matrix[second_des][first_des]


def compare_equivalence_classes(
        rel_matrix: list[list[int]],
        first_class: Iterable[int],
        second_class: Iterable[int]
) -> int:
    """
    Сравнить два класса эквивалентности. Вернуть:
    * больше нуля, если first_class лучше second_class;
    * меньше нуля, если second_class лучше first_class;
    * 0, если классы несравнимы.
    """
    for fc_el in first_class:
        for sc_cl in second_class:
            comparison_result = compare_decisions(rel_matrix, fc_el, sc_cl)
            if comparison_result != 0:
                return comparison_result
    return 0


def find_nearest_values(
        d: dict[frozenset, float],
        better_classes: set[frozenset[int]],
        worse_classes: set[frozenset[int]]
) -> tuple[float, float]:
    minimum_from_better = min({d[i] for i in better_classes})
    maximum_from_worse = max({d[i] for i in worse_classes})
    return (minimum_from_better, maximum_from_worse)


def do_job(
        rel_matrix: list[list[int]],
        classes: set[set[int]]
) -> dict[set, float]:
    return_dict: dict[frozenset, float] = dict()
    need_to_compare_classes = classes
    while not is_set_empty(need_to_compare_classes):
        for index, clazz in enumerate(need_to_compare_classes):
            if index == 0:
                return_dict[frozenset(clazz)] = 1
            else:

                # Найти классы, которые лучше и хуже рассматриваемого
                better_classes, worse_classes = set(), set()

                for other_clazz in return_dict.keys():
                    comparison_result = compare_equivalence_classes(
                        rel_matrix, clazz, other_clazz)
                    if comparison_result > 0:
                        better_classes |= other_clazz
                    elif comparison_result < 0:
                        worse_classes |= other_clazz

                if not is_set_empty(worse_classes):
                    # Есть классы, которые лучше текущего.
                    if not is_set_empty(better_classes):
                        # Также есть классы, которые хуже текущего.

                        better_value, worse_value = find_nearest_values(return_dict)

                        # Найти подходящее рациональное число из множества
                        # последовательных рациональных чисел. Поиск начать с
                        # округлённого в большую сторону U(x`).  
                        for number in range_of_rational_number(int(better_value) + 1):
                            if better_value > number and number > worse_value:
                                return_dict[frozenset(clazz)] = number
                                break
                    else:
                        # Текущий класс хуже всех обработанных ранее.
                        return_dict[frozenset(clazz)] = -(index + 1)
                else:
                    # Текущий класс лучше всех обработанных ранее.
                    return_dict[frozenset(clazz)] = index + 1

        need_to_compare_classes = classes - return_dict.keys()

    return return_dict


def main(rel_matrix: list[list[int]], equiv_matrix: list[list[int]]) -> None:
    classes = get_set_of_equivalence_classes(equiv_matrix)

    if is_set_empty(classes):
        print("Нет классов эквивалентности.")
    else:
        print("Найдены классы:", classes)
        print("Полезность каждого из классов:",
              do_job(rel_matrix, classes))


main(task_desc['rel'], task_desc['eq'])
