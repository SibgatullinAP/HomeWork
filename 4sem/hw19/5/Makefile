all: clean solver

CFLASGS = -c -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
OPTFLAGS = -O3 -mfpmath=sse -Ofast -flto -march=native -funroll-loops

solver: main.o 
	g++ $^ $(GDBFLAGS) $(OPTFLAGS) -o server

main.o: main.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS) $(OPTFLAGS)

clean:
	rm -f *.o *.out