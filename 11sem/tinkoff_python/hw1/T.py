# T. Четные индексы
def task_t():
    input_str = input()
    tokenized_str = input_str.split(' ')
    print(' '.join(tokenized_str[::2]))


task_t()
