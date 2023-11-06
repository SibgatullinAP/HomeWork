import argparse
import math


def read_csv(input_file_path: str, separator: str):
    result = []
    with open(input_file_path, 'r') as input_file:
        header = input_file.readline()
        keys = [i.replace('\n', '') for i in header.split(separator)]
        for line in input_file.readlines():
            row = [i.replace('\n', '') for i in line.split(separator)]
            assert len(row) == len(keys)
            tmp = dict()
            for key, elem in zip(keys, row):
                tmp.setdefault(key, elem)

            result.append(tmp)
    return result


def write_csv(output_file_path: str, separator: str, table):
    header = separator.join(table[0].keys())

    with open(output_file_path, 'w') as output_file:
        output_file.write(header + '\n')
        for row in table[1:]:
            output_file.write(separator.join(str(val) for val in row.values()) + '\n')


# Number of different objects
def task1(objects):
    return len(objects)


# Longest path
def TIMESTAMP_getter(obj):
    return float(obj['TIMESTAMP'])


def X_getter(obj):
    return float(obj['X'])


def Y_getter(obj):
    return float(obj['Y'])


def task2(objects):
    max_path_len = 0
    for obj in objects.values():
        sorted_by_timesteps = sorted(obj, key=TIMESTAMP_getter)
        curr_path_len = 0
        for i in range(len(sorted_by_timesteps) - 1):
            curr_state = sorted_by_timesteps[i]
            next_state = sorted_by_timesteps[i + 1]
            dx = X_getter(next_state) - X_getter(curr_state)
            dy = Y_getter(next_state) - Y_getter(curr_state)
            curr_path_len += math.sqrt(dx * dx + dy * dy)
        max_path_len = max(curr_path_len, max_path_len)

    return max_path_len


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-i', '--input', required=True, dest='input_csv', help='Input .csv file')
    parser.add_argument('-o', '--output', required=True, dest='output_csv', help='Output .csv file')
    args = parser.parse_args()

    input_table = read_csv(args.input_csv, ',')
    objects = dict()
    for row in input_table:
        TRACK_ID = row['TRACK_ID']
        row.pop('TRACK_ID')
        objects.setdefault(
            TRACK_ID,
            []
        ).append(row)

    task1_answer = task1(objects)
    task2_answer = round(task2(objects), 2)
    result_table = [{'task1': None, 'task2': None},
                    {'task1': task1_answer, 'task2': task2_answer}]
    write_csv(args.output_csv, ',', result_table)
    return 0


if __name__ == "__main__":
    exit(main())
