CFLASGS = -c -Wall -Wextra -pedantic -Werror
GDBFLAGS = -O0 -g

main: main.o list.o tree.o treeNode.o student.o queue.o addons.o 
	g++ $^ -o 1.out
main.o: main.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)


list.o: list.cpp list.h listNode.h
	g++ $< $(CFLASGS) $(GDBFLAGS)
tree.o: tree.cpp tree.h treeNode.h
	g++ $< $(CFLASGS) $(GDBFLAGS)
treeNode.o: treeNode.cpp treeNode.h
	g++ $< $(CFLASGS) $(GDBFLAGS)
queue.o: queue.cpp queue.h queueNode.h
	g++ $< $(CFLASGS) $(GDBFLAGS)
student.o: student.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)

addons.o: addons.cpp addons.h 
	g++ $< $(CFLASGS) $(GDBFLAGS)

clean:
	rm -f *.o *.out
