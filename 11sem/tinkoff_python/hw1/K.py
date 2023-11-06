# K. Исполнитель Раздвоитель
def task_k():
    src = int(input())  # A
    dst = int(input())  # B

    while src > dst:
        if src % 2 == 0 and src // 2 >= dst:
            src /= 2
            print(':2')
        else:
            src -= 1
            print('-1')


task_k()
