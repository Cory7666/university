from random import randint

kRows, kColumns = 1000000, 20

with open("output-matrix3", "w") as file:
    file.write(f"{kColumns} {kRows}\n")

    file.write("100 100 100 ")

    for i in range(kRows * kColumns - 4):
        file.write(f"{randint(-10, 10)} ")

    file.write("1000")
