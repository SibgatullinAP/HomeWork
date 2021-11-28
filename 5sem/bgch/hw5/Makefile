#!/bin/sh
all: build

LINKER_FLAGS = -c
FLAGS_DEBUG = -O0 -g
FLAGS_RELEASE = -O3

C_FLAGS_COMPATABILITY = -c -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Wcast-qual -Wno-suggest-attribute=format
CPP_FLAGS_COMPATABILITY = -c -lm -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format

CC = g++
FLAGS_COMPATABILITY = $(CPP_FLAGS_COMPATABILITY)

build: main.o student.o list2_node.o list2.o
	$(CC) $^ $(FLAGS_DEBUG) 

main.o: main.cpp tree.h tree_node.h
	$(CC) $< $(FLAGS_COMPATABILITY) -o main.o

student.o: student.cpp student.h common.h
	$(CC) $< $(FLAGS_COMPATABILITY) -o student.o

list2_node.o: list2_node.cpp list2_node.h
	$(CC) $< $(FLAGS_COMPATABILITY) -o list2_node.o

list2.o: list2.cpp list2.h
	$(CC) $< $(FLAGS_COMPATABILITY) -o list2.o

clean:
	rm -rf *.o *.out
