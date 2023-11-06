# H. Високосный год

def is_leap_year(year: int):
    if year % 4 == 0 and year % 100 != 0 or year % 400 == 0:
        return True

    return False


def task_h():
    year = int(input())

    if is_leap_year(year):
        print('YES')
    else:
        print('NO')


task_h()
