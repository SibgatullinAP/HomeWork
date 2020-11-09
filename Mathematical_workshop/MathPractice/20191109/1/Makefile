CC = g++
FLAGS = -O3 -pthread -lpthread
#FLAGS = -g -pthread -lpthread

all: a.out

a.out: main.o thread_func.o time.o
	$(CC) $(FLAGS) $^ -o $@

main.o: main.cpp thread_func.hpp common.hpp
	$(CC) $(FLAGS) $< -c -o $@

thread_func.o: thread_func.cpp thread_func.hpp common.hpp
	$(CC) $(FLAGS) $< -c -o $@

time.o: time.cpp common.hpp
	$(CC) $(FLAGS) $< -c -o $@

clean:
	@ rm -f main.o thread_func.o time.o a.out leak.out
