# S. Удалить каждый третий символ
def task_s():
    input_str = list(input())
    del input_str[::3]
    print(''.join(input_str))


task_s()
