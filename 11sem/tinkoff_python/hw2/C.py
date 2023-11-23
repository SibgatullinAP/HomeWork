# C. Удалить повторы

def task():
    input_str = input()
    symbol_set = set ()
    for symbol in input_str:
        if symbol in symbol_set:
            continue

        symbol_set |= set(symbol)
        print(symbol, end='')


task()
