CFLASGS = -c -Wall -Wextra -pedantic -Werror
GDBFLAGS = -O0 -g

a.out: main.o student.o sort.o addons.o
	g++ -g $^ -o a.out
student.o: student.cpp student.h
	g++ $< $(CFLASGS) $(GDBFLAGS)
sort.o: sort.cpp sort.h student.h
	g++ $< $(CFLASGS) $(GDBFLAGS)
addons.o: addons.cpp addons.h student.h
	g++ $< $(CFLASGS) $(GDBFLAGS)
clean:
	rm -f *.o *.out
