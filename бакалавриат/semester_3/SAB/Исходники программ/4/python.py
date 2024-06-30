#####!/bin/python3

from typing import Iterable
import math


def print_matrix (a):
    for i in range (0, len(a)):
        for j in range (0, len(a[i])):
            print ("%6.4f" % a[i][j], end=" |")
        print ()

def print_array (a: Iterable) -> None:
    for row in range (0, len (a)):
        print ("%2d -> %2.4f" % (row + 1, a[row]))

def prod (a: Iterable) -> float:
    if len(a) > 0:
        return a[-1] * prod (a[:-1])
    else:
        return 1.0

def main ():
    # Получение минимальных данных
    crit_cnt = int ( input ("Введите количество критериев: ") )
    altern_cnt = int ( input ("Введите кольчество альтернатив: ") )

    # Составление необходимых матриц
    altern_matrix       = [[0 for i in range (0, altern_cnt)] for j in range (0, crit_cnt)]
    expert_score_matrix = [[0 for i in range (0, crit_cnt)] for j in range (0, crit_cnt)]
    priorities_2_level_matrix = []

    # Заполнение матриц
    print ("Ввод значений для матрицы критериев альтернатив: ")
    for col in range (0, altern_cnt):
        for row in range (0, crit_cnt):
            altern_matrix[row][col] = float ( input (" *  Матрица [%2d][%2d]: " % (row + 1, col + 1)) )
    
    print ("Заполнение матрицы альтернатив:")
    for col in range (0, crit_cnt - 1):
        for row in range (col + 1, crit_cnt):
            expert_score_matrix[row][col] = float ( input (" *  Матрица [%2d][%2d]: " % (row + 1, col + 1)) )
            expert_score_matrix[col][row] = 1 / expert_score_matrix[row][col]
    for i in range (0, crit_cnt):
        expert_score_matrix[i][i] = 1.0;

    # Вывод только что введённых матриц
    print ("Введены матрицы:")
    print (" *  Матрица альтернатив:")
    print_matrix (altern_matrix)
    print (" *  Матрица оценок:")
    print_matrix (expert_score_matrix)

    # Определение вектора приоритетов для 2 уровня
    priorities_2_level_matrix = [
            (
                (
                    math.pow (
                        prod (expert_score_matrix[row]),
                        1/crit_cnt
                    )
                ) / sum (
                    [
                        math.pow (
                            prod (expert_score_matrix[i]),
                            1/crit_cnt
                        ) for i in range (0, crit_cnt)
                    ]
                )
            ) for row in range (0, crit_cnt)
        ]
    
    print ()
    print ("Вектора приоритетов для второго уровня:")
    print_array (priorities_2_level_matrix)
    
    # Определение вектора приоритетов для 3 уровня
    priorities_3_level_matrix = [[0 for j in range (0, crit_cnt)] for i in range (0, altern_cnt)]
    for table_num in range (0, crit_cnt):
        tmp_table = [[0.0 for j in range (0, altern_cnt)] for i in range (0, altern_cnt)]
        for i in range (0, altern_cnt):
            for j in range (0, altern_cnt):
                tmp_table[j][i] = altern_matrix[table_num][j] / altern_matrix[table_num][i]
        abcde = [
            (
                (
                    math.pow (
                        prod (tmp_table[row]),
                        1/altern_cnt
                    )
                ) / sum (
                    [
                        math.pow (
                            prod (tmp_table[abcd]),
                            1/altern_cnt
                        ) for abcd in range (0, altern_cnt)
                    ]
                )
            ) for row in range (0, altern_cnt)
        ]
        for i in range (0, len(abcde)):
            priorities_3_level_matrix[i][table_num] = abcde[i]
    
    print ()
    print ("Вектора приоритетов для третьего уровня:")
    print_matrix (priorities_3_level_matrix)

    # Вычисление глобальных приоритетов
    K = [0.0 for i in range (0, altern_cnt)]
    for alternative_num in range (0, altern_cnt):
        for criteria_num in range (0, crit_cnt):
            K[alternative_num] += priorities_2_level_matrix[criteria_num] * priorities_3_level_matrix[alternative_num][criteria_num]
    
    print ()
    print ("Глобальные приоритеты:")
    print_array (K)

    print ("Ответ: %d вариант наиболее оптимален." % (K.index(max(K)) + 1))
    


main ()
