# W. Переставить min и max

def task_w():
    tokenized_str = input().split()
    numbers = [int(x) for x in tokenized_str]
    max_ind = numbers.index(max(numbers))
    min_ind = numbers.index(min(numbers))
    numbers[max_ind], numbers[min_ind] = numbers[min_ind], numbers[max_ind]
    print(' '.join([str(x) for x in numbers]))


task_w()
