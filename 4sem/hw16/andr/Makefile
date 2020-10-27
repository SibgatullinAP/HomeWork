a.out: main.o record.o 
	g++ -g -O3 -DZACHET -Wall -Wextra -Wunused -Werror -pedantic   main.o record.o -o a.out
main.o: main.cpp record.h command.h database.h
	g++ -c -g -O3 -DZACHET -Wall -Wextra -Wunused -Werror -pedantic   main.cpp 
record.o: record.cpp record.h command.h database.h
	g++ -c -g -O3 -DZACHET -Wall -Wextra -Wunused -Werror -pedantic  record.cpp

	
clean:
	rm -f *.o *.out *.exe
