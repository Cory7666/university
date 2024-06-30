#!/bin/python3

from os import system
from math import fsum

def clear_screen (): # Очистить экран консоли
    system("cls")

def print_array (arr: list, arr_name: str): # Печать массива
    print ("%s = [" % arr_name, end="")

    for i in range (len(arr)):
        print (("%5.2f, " if i + 1 != len (arr) else "%5.2f") % arr[i], end="")
    
    print ("]")

def print_matrix (m: list, highest_level: str, lowest_level: str): # Вывод матрицы на экран
    lines, cols = len(m), len(m[0])
    
    print("       ", end="")
    for i in range(cols):
        print("%.1s%-2d" % (highest_level, i + 1), end="   ")
    print()

    for i in range(lines):
        print("%.1s%-2d" % (lowest_level, i + 1), end="  ")
        for j in range(cols):
            print("%5.2f" % m[i][j], end=" ")
        print()



count = {
    "a": 0,
    "b": 0,
    "c": 0
}

matrix = {
    "ab": [],
    "bc": [],
    "cd": []
}

level = {
    "a": [],
    "b": [],
    "c": [],
    "d": []
}

tmp = 0



def main ():
    clear_screen()

    # Ввод количества элементов на уровнях a, b, c, d
    for level_char in ("a", "b", "c", "d"):
        count[level_char] = int( input(f"Введите количесво элементов на уровне \"{level_char}\": ") )

    # Создание шаблона значений
    for level_char in ("a", "b", "c", "d"):
        level[level_char] = [0 for i in range(count[level_char])]

    # Ввод значений элементов на уровне a
    for i in range(count["a"]):
        clear_screen ()
        print_array(level["a"], "a")
        level["a"][i] = float( input("Введите значение веса a[%02d]: " % (i + 1)) )

    # Создание шаблонов матриц
    for level_1, level_2 in (("a", "b"), ("b", "c"), ("c", "d")):
        matrix[level_1 + level_2] = [[0 for i in range(count[level_1])] for j in range(count[level_2])]

    # Заполнение матриц весов
    for level_1, level_2 in (("a", "b"), ("b", "c"), ("c", "d")):
        for col in range(count[level_1]):
            for line in range(count[level_2]):
                clear_screen()
                print_matrix(matrix[level_1 + level_2], level_1, level_2)
                matrix[level_1 + level_2][line][col] = float(input(f"Введите {level_1}{level_2}[{line}][{col}]: "))
    
    # Подсчёт значений
    for level_1, level_2 in (("a", "b"), ("b", "c"), ("c", "d")):
        for i in range(count[level_2]):
            level[level_2][i] = fsum([(level[level_1][j] * matrix[level_1 + level_2][i][j]) for j in range(count[level_1])])

        sum = fsum(level[level_2])
        for i in range(count[level_2]):
            level[level_2][i] = level[level_2][i] / sum
    
    clear_screen ()

    # Выводы
    print ("Заданы матрицы весов:")
    for level_1, level_2 in (("a", "b"), ("b", "c"), ("c", "d")):
        print_matrix(matrix[level_1 + level_2], level_1, level_2)
        print()
    
    print("Получены значения:")
    for level_char in ("a", "b", "c", "d"):
        print_array(level[level_char], level_char)
    
    print( "Таким образом, вариант d%d оказывает наибольшее влияние на проектирование всей системы." % (level["d"].index(max(level["d"])) + 1) )
    

    
# Запуск основной программы
main ()