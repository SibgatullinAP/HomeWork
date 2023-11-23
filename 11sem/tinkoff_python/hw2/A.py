# A. Пунктуация

def task():
    input_str = input()
    ref_str = '.,;:!?'

    counter = 0
    for symbol in input_str:
        if symbol in ref_str:
            counter += 1

    print(counter)


task()
