CFLASGS = -c -Wall -Wextra -pedantic -Werror
GDBFLAGS = -O0 -g

a.out: main.o student.o func.o addons.o list.o
	g++ -g $^ -o a.out
student.o: student.cpp student.h list.h
	g++ $< $(CFLASGS) $(GDBFLAGS)
func.o: func.cpp func.h student.h list.h
	g++ $< $(CFLASGS) $(GDBFLAGS)
addons.o: addons.cpp addons.h student.h list.h
	g++ $< $(CFLASGS) $(GDBFLAGS)
list.o: list.cpp list.h listNode.h
	g++ $< $(CFLASGS) $(GDBFLAGS)
clean:
	rm -f *.o *.out
