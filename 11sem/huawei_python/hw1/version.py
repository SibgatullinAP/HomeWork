import sys

if __name__ == "__main__":
    with open("version.txt", "w") as fd:
        info = sys.version_info
        fd.write(f'{info.major}.{info.minor}.{info.micro}\n')

    exit (0)