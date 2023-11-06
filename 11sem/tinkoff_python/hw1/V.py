# V. Шеренга

def task_v():
    tokenized_str = input().split()
    heights = [int(x) for x in tokenized_str]

    height = int(input())

    pos = 1
    for i in range(len(heights)):
        if heights[i] < height:
            break
        pos += 1

    print(pos)


task_v()
