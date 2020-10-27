CFLASGS = -c -Wall -Wextra -pedantic -Werror
GDBFLAGS = -O0 -g

main: main.o func.o command.o
	g++ $^ -o 1.out

main.o: main.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)
func.o: func.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)
command.o: command.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)

clean:
	rm -f *.o *.out
