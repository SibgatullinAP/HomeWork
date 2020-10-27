CFLASGS = -c -Wall -Wextra -pedantic -Werror
GDBFLAGS = -O0 -g

main: main.o student.o addons.o 
	g++ $^ -o 1.out

main.o: main.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)
student.o: student.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)
addons.o: addons.cpp addons.h 
	g++ $< $(CFLASGS) $(GDBFLAGS)

clean:
	rm -f *.o *.out
