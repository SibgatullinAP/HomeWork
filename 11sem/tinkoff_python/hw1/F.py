# F. Электронные часы - 2
def task_f():
    seconds_from_midnight = int(input())

    seconds_on_clock = seconds_from_midnight % 60
    minutes_on_clock = (seconds_from_midnight // 60) % 60
    hours_on_clock = (seconds_from_midnight // 3600) % 24

    print(f'{hours_on_clock}:{minutes_on_clock:02}:{seconds_on_clock:02}')


task_f()
