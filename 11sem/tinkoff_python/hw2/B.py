# B. Повторяющиеся цифры

def task():
    input_str = input()
    digit_counters = {
        '0': 0,
        '1': 0,
        '2': 0,
        '3': 0,
        '4': 0,
        '5': 0,
        '6': 0,
        '7': 0,
        '8': 0,
        '9': 0,
    }
    for symbol in input_str:
        if symbol in digit_counters.keys():
            digit_counters[symbol] += 1

    print_NO = True
    for digit in digit_counters:
        if digit_counters[digit] > 1:
            print(digit, end='')
            print_NO = False

    if print_NO:
        print('NO')


task()
