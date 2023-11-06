# L. a + b = c

def fuzzy_equal(lhs: float, rhs: float, eps: float = 1e-15):
    return abs(lhs - rhs) < eps * max(lhs, rhs)

def task_l():
    a = float(input())
    b = float(input())
    c = float(input())

    if fuzzy_equal(a + b, c):
        print('YES')
    else:
        print('NO')


task_l()
