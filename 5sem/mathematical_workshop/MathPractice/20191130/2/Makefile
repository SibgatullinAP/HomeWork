CC = g++
FLAGS = -g -pthread -lpthread

all: a.out

a.out: main.o thread_func.o task.o time.o
	$(CC) $(FLAGS) $^ -o $@

main.o: main.cpp thread_func.hpp task.hpp common.hpp
	$(CC) $(FLAGS) $< -c -o $@

thread_func.o: thread_func.cpp thread_func.hpp common.hpp
	$(CC) $(FLAGS) $< -c -o $@

task.o: task.cpp task.hpp common.hpp
	$(CC) $(FLAGS) $< -c -o $@

time.o: time.cpp common.hpp
	$(CC) $(FLAGS) $< -c -o $@

clean:
	@ rm -f main.o thread_func.o task.o time.o a.out leak.out
