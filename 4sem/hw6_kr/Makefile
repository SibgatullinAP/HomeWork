CFLASGS = -c -Wall -Wextra -pedantic -Werror 

a.out: main.o tree.o treeNode.o student.o addons.o
	g++ $^ -o 5.out

main.o: main.cpp tree.h treeNode.h
	g++ $< $(CFLASGS) 
student.o: student.cpp student.h tree.h
	g++ $< $(CFLASGS) 
func.o: func.cpp func.h student.h tree.h
	g++ $< $(CFLASGS) 
addons.o: addons.cpp addons.h
	g++ $< $(CFLASGS) 
tree.o: tree.cpp tree.h treeNode.h
	g++ $< $(CFLASGS) 
treeNode.o: treeNode.cpp treeNode.h treeNode.h
	g++ $< $(CFLASGS) 

clean:
	rm -f *.o *.out