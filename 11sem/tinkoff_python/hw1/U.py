# U. Наибольший элемент и его индекс
def task_u():
    input_str = input()
    tokenized_str = input_str.split(' ')
    int_list = [int(x) for x in tokenized_str]
    max_el = max(int_list)
    max_ind = int_list.index(max_el)
    print(max_el, max_ind)


task_u()
