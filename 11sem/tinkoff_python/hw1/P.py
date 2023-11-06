# P. Переставить два слова
def task_p():
    input_str = input()
    tokenized_str = input_str.split(' ')
    tokenized_str[0], tokenized_str[1] = tokenized_str[1], tokenized_str[0]
    print(' '.join(tokenized_str))


task_p()
