# E. Буквы, которых нет

def task():
    str_1 = input()
    str_2 = input()

    input_symbol_set = set()

    for symbol in str_1:
        input_symbol_set |= set(symbol.lower())

    for symbol in str_2:
        input_symbol_set |= set(symbol.lower())

    eth_symbol_set = set()
    for ascii_code in range (ord('a'), ord('z') + 1):
        eth_symbol_set |= set(chr(ascii_code))

    diff_set = eth_symbol_set.difference(input_symbol_set)
    diff_list = list(diff_set)
    sorted_str = ''.join(sorted(diff_list, key=ord)).upper()
    if sorted_str:
        print(sorted_str)
    else:
        print(0)


task()
