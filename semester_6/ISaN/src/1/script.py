#!/bin/python

from decimal import Decimal as D

# R_п, L_п, C_п
R_p, L_p, C_p = D('86'), D('11e-3'), D('5e-6')
elements_count = D(2)  # количество резисторов и катушек
l = D(14)  # длина кабеля в км

print(f"F = {(L_p / C_p).sqrt()}")
for segments_count in [1, 5, 8]:
    ratio = l / segments_count
    R, L, C = (D(x) * D(ratio) for x in (R_p, L_p, C_p))

    print(f"For segments = {segments_count}")
    print(f"* R = {R / elements_count}")
    print(f"* L = {L * (10**6) / elements_count} *10^-6")
    print(f"* C = {C * (10**6)} *10^-6")
