# N. Минимум 4 чисел

def task():
    a = int(input())
    b = int(input())
    c = int(input())
    d = int(input())
    print(min(min(a, b), min(c, d)))


task()
