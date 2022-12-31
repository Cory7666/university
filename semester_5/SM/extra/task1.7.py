#!/bin/python

from decimal import Decimal
from math import e, factorial

def P_m (t: Decimal, m: int, a: Decimal) -> Decimal:
  t, a = Decimal(t), Decimal(a)
  return ((a * t) ** m) / factorial(m) * (-a * t).exp()

a, b = Decimal(1.5), Decimal(1)

print("Среднее время заявок:", a * (-a * b).exp())
print("Среднее число заявок:", 1 / a)
print("Ни одной заявки:", P_m(b, 0, a))
print("Хотя бы одна заявка:", P_m(b, 1, a))
print("Больше одной заявки:", 1 - P_m(b, 0, a) - P_m(b, 1, a))
