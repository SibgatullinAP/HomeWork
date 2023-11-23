# G. Словарь синонимов

def task():
    N = int(input())
    synonyms_data = []
    left_to_right = {}
    right_to_left = {}

    i = 0
    for _ in range(N):
        left, right = input().split()
        synonyms_data.append(left)
        synonyms_data.append(right)
        left_to_right[left] = i + 1
        right_to_left[right] = i
        i += 2

    word_to_change = input()
    if word_to_change in left_to_right:
        print(synonyms_data[left_to_right[word_to_change]])
    elif word_to_change in right_to_left:
        print(synonyms_data[right_to_left[word_to_change]])


task()
