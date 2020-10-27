CFLASGS = -c -Wall -Wextra -pedantic -Werror
GDBFLAGS = -O0 -g

all: main biDirMain

main: main.o list.o student.o addons.o
	g++ $^ -o 1.out
main.o: main.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)
biDirMain: biDirMain.o biDirList.o student.o biDirAddons.o
	g++ $^ -o 1b.out
biDirMain.o: biDirMain.cpp biDirList.h
	g++ $< $(CFLASGS) $(GDBFLAGS)

student.o: student.cpp
	g++ $< $(CFLASGS) $(GDBFLAGS)

addons.o: addons.cpp addons.h student.h list.h
	g++ $< $(CFLASGS) $(GDBFLAGS)
biDirAddons.o: biDirAddons.cpp biDirAddons.h student.h biDirList.h
	g++ $< $(CFLASGS) $(GDBFLAGS)

list.o: list.cpp list.h listNode.h
	g++ $< $(CFLASGS) $(GDBFLAGS)
biDirList.o: biDirList.cpp biDirList.h biDirListNode.h
	g++ $< $(CFLASGS) $(GDBFLAGS)

clean:
	rm -f *.o *.out
