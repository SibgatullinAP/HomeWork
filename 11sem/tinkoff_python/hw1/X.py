# X. Удалить элемент

def task_x():
    tokenized_str = input().split()
    numbers = [int(x) for x in tokenized_str]
    tokenized_str = input().split()
    index_to_add = [int(x) for x in tokenized_str][0]
    value_to_add = [int(x) for x in tokenized_str][1]

    numbers.append(0)
    for i in range(len(numbers) - 1, index_to_add, -1):
        numbers[i] = numbers[i - 1]

    numbers[index_to_add] = value_to_add
    print(' '.join(str(x) for x in numbers))


task_x()
