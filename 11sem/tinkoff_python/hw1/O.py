# O. Самое длинное слово
def task_n():
    input_str = input()
    tokenized_str = input_str.split(' ')
    max_substr = max(tokenized_str, key=len)
    print(max_substr)
    print(len(max_substr))


task_n()
