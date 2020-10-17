#!/bin/sh
all: build

LINKER_FLAGS = -c
FLAGS_DEBUG = -O0 -g
FLAGS_RELEASE = -O3

C_FLAGS_COMPATABILITY = -c -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Wcast-qual -Wno-suggest-attribute=format
CPP_FLAGS_COMPATABILITY = -c -lm -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format

CC = g++
FLAGS_COMPATABILITY = $(CPP_FLAGS_COMPATABILITY)


build: build_1 build_2 build_3 build_4

build_1: main_1_1.o main_1_2.o main_1_3.o main_1_4.o sequences.o
	$(CC) main_1_1.o sequences.o $(FLAGS_DEBUG) -o 1_1.out
	$(CC) main_1_2.o sequences.o $(FLAGS_DEBUG) -o 1_2.out
	$(CC) main_1_3.o sequences.o $(FLAGS_DEBUG) -o 1_3.out
	$(CC) main_1_4.o sequences.o $(FLAGS_DEBUG) -o 1_4.out
	@tput setaf 2
	printf "Tasks with sequences were built succesfully\n"
	@tput sgr0

build_2: main_2_1.o main_2_2.o main_2_3.o array.o
	$(CC) main_2_1.o array.o $(FLAGS_DEBUG) -o 2_1.out
	$(CC) main_2_3.o array.o $(FLAGS_DEBUG) -o 2_2.out
	$(CC) main_2_3.o array.o $(FLAGS_DEBUG) -o 2_3.out
	@tput setaf 2
	printf "Tasks with strings were built succesfully\n"
	@tput sgr0

build_3: main_3_1.o main_3_2.o main_3_3.o main_3_4.o main_3_4.o main_3_5.o main_3_6.o main_3_7.o sort.o
	$(CC) main_3_1.o sort.o $(FLAGS_DEBUG) -o 3_1.out
	$(CC) main_3_2.o sort.o $(FLAGS_DEBUG) -o 3_2.out
	$(CC) main_3_3.o sort.o $(FLAGS_DEBUG) -o 3_3.out
	$(CC) main_3_4.o sort.o $(FLAGS_DEBUG) -o 3_4.out
	$(CC) main_3_5.o sort.o $(FLAGS_DEBUG) -o 3_5.out
	$(CC) main_3_6.o sort.o $(FLAGS_DEBUG) -o 3_6.out
	$(CC) main_3_7.o sort.o $(FLAGS_DEBUG) -o 3_7.out
	@tput setaf 2
	printf "Tasks with sortings were built succesfully\n"
	@tput sgr0

build_4: main_4_1.o main_4_2.o main_4_3.o main_4_4.o string_.o
	$(CC) main_4_1.o string_.o $(FLAGS_DEBUG) -o 4_1.out
	$(CC) main_4_2.o string_.o $(FLAGS_DEBUG) -o 4_2.out
	$(CC) main_4_3.o string_.o $(FLAGS_DEBUG) -o 4_3.out
	$(CC) main_4_4.o string_.o $(FLAGS_DEBUG) -o 4_4.out
	@tput setaf 2
	printf "Tasks with strings were built succesfully\n"
	@tput sgr0 

main_1_1.o: main_1_1.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_1_1.o
main_1_2.o: main_1_2.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_1_2.o
main_1_3.o: main_1_3.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_1_3.o
main_1_4.o: main_1_4.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_1_4.o

main_2_1.o: main_2_1.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_2_1.o
main_2_2.o: main_2_2.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_2_2.o
main_2_3.o: main_2_3.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_2_3.o

main_3_1.o: main_3_1.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_3_1.o
main_3_2.o: main_3_2.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_3_2.o
main_3_3.o: main_3_3.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_3_3.o
main_3_4.o: main_3_4.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_3_4.o
main_3_5.o: main_3_5.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_3_5.o
main_3_6.o: main_3_6.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_3_6.o
main_3_7.o: main_3_7.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_3_7.o

main_4_1.o: main_4_1.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_4_1.o
main_4_2.o: main_4_2.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_4_2.o
main_4_3.o: main_4_3.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_4_3.o
main_4_4.o: main_4_4.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_4_4.o

sequences.o: sequences.cpp sequences.h constants.h
	$(CC) $< $(FLAGS_COMPATABILITY)
array.o: array.cpp array.h constants.h
	$(CC) $< $(FLAGS_COMPATABILITY)
sort.o: sort.cpp array.h constants.h
	$(CC) $< $(FLAGS_COMPATABILITY)
string_.o: string_.cpp string_.h constants.h
	$(CC) $< $(FLAGS_COMPATABILITY)


clean:
	rm -rf *.o *.out
