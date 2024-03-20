from random import randint

def qsort(lst):
    return ((qsort([x for x in lst[1:] if x < lst[0]]) + [lst[0]]
            + qsort([x for x in lst[1:] if x >= lst[0]]))
            if len(lst) > 1
            else lst)


nums = [randint(0, 20) for idx in range(10)]
sorted_nums = qsort(nums)

print(nums)
print(sorted_nums)
