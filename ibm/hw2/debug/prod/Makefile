all: clean build

LINKER_FLAGS = -c
FLAGS_DEBUG = -O0 -g -pg
FLAGS_RELEASE = -O3 
FLAGS_COMPILE = $(FLAGS_RELEASE)

C_FLAGS_COMPATABILITY = -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Wcast-qual -Wno-suggest-attribute=format
CPP_FLAGS_COMPATABILITY = -lm -mfpmath=sse -fsignaling-nans -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format

CC = g++
FLAGS_COMPATABILITY = $(CPP_FLAGS_COMPATABILITY)

build: main.o solver.o
	$(CC) $(FLAGS_COMPILE) $^

solver.o: solver.cpp
	$(CC) $(LINKER_FLAGS) $(FLAGS_COMPATABILITY) $(FLAGS_COMPILE) $<
	
main.o: main.cpp
	$(CC) $(LINKER_FLAGS) $(FLAGS_COMPATABILITY) $(FLAGS_COMPILE) $<

clean:
	rm -rf *.o *.out
