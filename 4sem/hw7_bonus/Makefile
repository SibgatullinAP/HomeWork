CFLASGS = -c -Wall -Wextra -pedantic -Werror 
GDBFLAGS = -O0 -g

main: main.o tree.o treeNode.o student.o addons.o
	g++ $^ -o a.out
main.o: main.cpp tree.h treeNode.h
	g++ $< $(CFLASGS) $(GDBFLAGS)
student.o: student.cpp student.h tree.h
	g++ $< $(CFLASGS) $(GDBFLAGS)
func.o: func.cpp func.h student.h tree.h
	g++ $< $(CFLASGS) $(GDBFLAGS)
addons.o: addons.cpp addons.h
	g++ $< $(CFLASGS) $(GDBFLAGS)
tree.o: tree.cpp tree.h treeNode.h
	g++ $< $(CFLASGS) $(GDBFLAGS)
treeNode.o: treeNode.cpp treeNode.h treeNode.h
	g++ $< $(CFLASGS) $(GDBFLAGS)

clean:
	rm -f *.o *.out