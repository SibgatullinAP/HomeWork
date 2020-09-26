all: clean build

LINKER_FLAGS = -c
FLAGS_DEBUG = -O0 -g
FLAGS_RELEASE = -O3

C_FLAGS_COMPATABILITY = -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Wcast-qual -Wno-suggest-attribute=format
CPP_FLAGS_COMPATABILITY = -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format

CC = g++
FLAGS_COMPATABILITY = $(CPP_FLAGS_COMPATABILITY)

build: main.o sequences.o
	$(CC) $^ $(С_FLAGS_DEBUG)

sequences.o: sequences.c
	$(CC) $< $(LINKER_FLAGS) $(FLAGS_COMPATABILITY)
	
main.o: main.c
	$(CC) $< $(LINKER_FLAGS) $(FLAGS_COMPATABILITY)

clean:
	rm -rf *.o *.out
