# E. Электронные часы - 1
def task_e():
    minutes_from_midnight = int(input())

    hours_on_clock = (minutes_from_midnight // 60) % 24
    minutes_on_clock = minutes_from_midnight % 60

    print(f'{hours_on_clock} {minutes_on_clock}')


task_e()
