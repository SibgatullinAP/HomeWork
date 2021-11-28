#!/bin/sh
all: build

LINKER_FLAGS = -c
FLAGS_DEBUG = -O0 -g
FLAGS_RELEASE = -O3

C_FLAGS_COMPATABILITY = -c -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Wcast-qual -Wno-suggest-attribute=format
CPP_FLAGS_COMPATABILITY = -c -lm -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format

CC = g++
FLAGS_COMPATABILITY = $(CPP_FLAGS_COMPATABILITY)

build: build_1

build_1: main_1.o main_2.o main_3.o main_4.o main_5.o main_6.o main_7.o main_8.o main_9.o string_.o
	$(CC) main_1.o string_.o $(FLAGS_DEBUG) -o 1.out
	$(CC) main_2.o string_.o $(FLAGS_DEBUG) -o 2.out
	$(CC) main_3.o string_.o $(FLAGS_DEBUG) -o 3.out
	$(CC) main_4.o string_.o $(FLAGS_DEBUG) -o 4.out
	$(CC) main_5.o string_.o $(FLAGS_DEBUG) -o 5.out
	$(CC) main_6.o string_.o $(FLAGS_DEBUG) -o 6.out
	$(CC) main_7.o string_.o $(FLAGS_DEBUG) -o 7.out
	$(CC) main_8.o string_.o $(FLAGS_DEBUG) -o 8.out
	$(CC) main_9.o string_.o $(FLAGS_DEBUG) -o 9.out 

main_1.o: main_1.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_1.o
main_2.o: main_2.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_2.o
main_3.o: main_3.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_3.o
main_4.o: main_4.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_4.o
main_5.o: main_5.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_5.o
main_6.o: main_6.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_6.o
main_7.o: main_7.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_7.o
main_8.o: main_8.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_8.o
main_9.o: main_9.cpp
	$(CC) $< $(FLAGS_COMPATABILITY) -o main_9.o

string_.o: string_.cpp string_.h constants.h
	$(CC) $< $(FLAGS_COMPATABILITY)


clean:
	rm -rf *.o *.out
