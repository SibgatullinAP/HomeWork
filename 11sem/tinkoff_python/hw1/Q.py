# Q. Удаление фрагмента
def task_q():
    input_str = input()
    symbol_to_find = 'h'
    symbol_positions = [i for i, ltr in enumerate(input_str) if ltr == symbol_to_find]
    first_half = input_str[:symbol_positions[0]:]
    last_half = input_str[symbol_positions[-1] + 1::]
    print(first_half+last_half)


task_q()
