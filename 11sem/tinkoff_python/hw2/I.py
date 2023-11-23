# H. Самое частое слово

def task():
    N = int(input())
    cities_countires = {}
    for _ in range(N):
        tokenized_str = input().split()
        for city in tokenized_str[1:]:
            cities_countires[city] = tokenized_str[0]

    M = int(input())
    requests = []
    for _ in range(M):
        requests.append(input())

    for city in requests:
        print(cities_countires[city])


task()
