import pandas as pd

INPUT_FILE_NAME = 'data.csv'
OUTPUT_FILE_NAME = 'result.csv'


def main():
    # 0.CSV to DataFrame
    df = pd.read_csv(INPUT_FILE_NAME)

    # 1.Filter rows with NaN.
    df = df.dropna()

    # 2.Filter AV, AGENT data
    df = df.drop(df[df['OBJECT_TYPE'] == 'AV'].index)
    df = df.drop(df[df['OBJECT_TYPE'] == 'AGENT'].index)

    # 3.Delete trajectories with less than 10 points
    df = df.groupby('TRACK_ID').filter(lambda x: len(x) > 10)

    # 4.Delete static objects
    df = df.groupby('TRACK_ID').filter(
        lambda x: abs(x['X'].max() - x['X'].min()) > 1 or abs(x['Y'].max() - x['Y'].min()) > 1)

    # 5.Sort data by ID and Time
    df = df.sort_values(['TRACK_ID', 'TIMESTAMP'])

    # 6.Write results
    df.to_csv(OUTPUT_FILE_NAME, sep=',', index=False, encoding='utf-8')
    return 0


if __name__ == '__main__':
    exit(main())
