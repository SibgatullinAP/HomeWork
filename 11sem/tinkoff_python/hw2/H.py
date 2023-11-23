# I. Страны и города

def task():
    words_counter = {}
    whole_str = sys.stdin.read()
    for word in whole_str.split():
        if word in words_counter:
            words_counter[word] += 1
        else:
            words_counter[word] = 1

    maximum_counts = max(words_counter.values())
    maximum_words = [key for key in words_counter if words_counter[key] == maximum_counts]
    maximum_words.sort()
    print(maximum_words[0])


task()
