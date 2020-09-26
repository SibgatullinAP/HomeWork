all: clean build

C_LINKER_FLAGS = -c -Wall -Wextra -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -Werror
С_FLAGS_DEBUG = -O0 -g
C_FLAGS_RELEASE = -O3

build: main.o sort.o
	gcc $^ $(С_FLAGS_DEBUG)

sort.o: sort.c
	gcc $< $(C_LINKER_FLAGS)
	
main.o: main.c
	gcc $< $(C_LINKER_FLAGS)

clean:
	rm -rf *.o *.out