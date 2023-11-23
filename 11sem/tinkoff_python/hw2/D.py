# D. Общие символы

def task():
    str_1 = input()
    str_2 = input()

    symbol_set_1 = set()
    symbol_set_2 = set()

    for symbol in str_1:
        symbol_set_1 |= set(symbol)

    for symbol in str_2:
        symbol_set_2 |= set(symbol)

    intersection_set = symbol_set_1 & symbol_set_2
    intersection_list = list(intersection_set)
    sorted_str = ''.join(sorted(intersection_list, key=ord))
    if sorted_str:
        print(sorted_str)
    else:
        print('NO')


task()
