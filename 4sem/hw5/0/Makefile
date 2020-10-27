CFLASGS = -c -Wall -Wextra -pedantic -Werror 
GDBFLAGS = -O0 -g

all: main1 main2 main3 main4 main5

clean:
	rm -f *.o *.out

main1: main1.o tree.o treeNode.o student.o addons.o
	g++ $^ -o 1.out
main1.o: main1.cpp tree.h treeNode.h
	g++ $< $(CFLASGS) $(GDBFLAGS)

main2: main2.o tree.o treeNode.o student.o addons.o
	g++ $^ -o 2.out
main2.o: main2.cpp tree.h treeNode.h
	g++ $< $(CFLASGS) $(GDBFLAGS)

main3: main3.o tree.o treeNode.o student.o addons.o
	g++ $^ -o 3.out
main3.o: main3.cpp tree.h treeNode.h
	g++ $< $(CFLASGS) $(GDBFLAGS)

main4: main4.o tree.o treeNode.o student.o addons.o
	g++ $^ -o 4.out
main4.o: main4.cpp tree.h treeNode.h
	g++ $< $(CFLASGS) $(GDBFLAGS)

main5: main5.o tree.o treeNode.o student.o addons.o
	g++ $^ -o 5.out
main5.o: main5.cpp tree.h treeNode.h
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

