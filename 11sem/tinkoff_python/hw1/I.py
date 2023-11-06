# I. Список квадратов

import math


def task_h():
    n = int(input())

    for i in range(1, int(math.sqrt(n)) + 1):
        sqr = i*i
        if sqr <= n:
            print(sqr)
        else:
            break


task_h()
