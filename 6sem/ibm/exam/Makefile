all: build

LINKER_FLAGS = -c
FLAGS_DEBUG = -O0 -g
FLAGS_RELEASE = -O3 -ffast-math
FLAGS_COMPILE = $(FLAGS_DEBUG)

C_FLAGS_COMPATABILITY = -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Wcast-qual -Wno-suggest-attribute=format
CPP_FLAGS_COMPATABILITY = -pthread -lm -fsignaling-nans -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format -fno-exceptions

CC = mpicxx -cxx=g++
FLAGS_COMPATABILITY = $(CPP_FLAGS_COMPATABILITY)

build: main.o io.o solve.o
	$(CC) $(FLAGS_COMPILE) $^

io.o: io.cpp
	$(CC) $(LINKER_FLAGS) $(FLAGS_COMPATABILITY) $(FLAGS_COMPILE) $<

solve.o: solve.cpp
	$(CC) $(LINKER_FLAGS) $(FLAGS_COMPATABILITY) $(FLAGS_COMPILE) $<
	
main.o: main.cpp
	$(CC) $(LINKER_FLAGS) $(FLAGS_COMPATABILITY) $(FLAGS_COMPILE) $<

clean:
	rm -rf *.o *.out
