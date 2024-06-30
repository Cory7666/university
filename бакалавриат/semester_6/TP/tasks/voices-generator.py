#!/usr/bin/python

from random import Random

sigma = 0.9
people_count = int(input("Количество людей: "))
treshold = float(input('Введите отступ от 1: '))
voice_groups_count = 2

r = Random()
voices: dict[int, int] = {0: 0, 1: 0}

for _ in range(people_count):
    voice = (abs(r.gauss(1, sigma)))

    voices[0 if voice < treshold else 1] += 1

print()
print(voices)
