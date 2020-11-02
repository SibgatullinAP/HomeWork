
CFLAGS=-O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wno-suggest-attribute=format  
#CFLAGS=-O3 -Wall -Wextra -pedantic -Werror #-fsanitize=address 
OFLAGS= -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition


All: 1.out 2.out 3.out 4.out 5.out 7.out 9.out

1.out: main1.o
	g++ $(CFLAGS) $(OFLAGS) main1.o -o 1.out

main1.o: main1.cpp
	g++ -c $(CFLAGS) main1.cpp

2.out: main2.o
	g++ $(CFLAG S) $(OFLAGS) main2.o -o 2.out

main2.o: main2.cpp
	g++ -c $(CFLAGS) main2.cpp

3.out: main3.o
	g++ $(CFLAG S) $(OFLAGS) main3.o -o 3.out

main3.o: main3.cpp
	g++ -c $(CFLAGS) main3.cpp

4.out: main4.o
	g++ $(CFLAG S) $(OFLAGS) main4.o -o 4.out

main4.o: main4.cpp
	g++ -c $(CFLAGS) main4.cpp

5.out: main5.o
	g++ $(CFLAG S) $(OFLAGS) main5.o -o 5.out

main5.o: main5.cpp
	g++ -c $(CFLAGS) main5.cpp

7.out: main7.o
	g++ $(CFLAG S) $(OFLAGS) main7.o -o 7.out

main7.o: main7.cpp
	g++ -c $(CFLAGS) main7.cpp

9.out: main9.o
	g++ $(CFLAG S) $(OFLAGS) main9.o -o 9.out

main9.o: main9.cpp
	g++ -c $(CFLAGS) main9.cpp

	
clean:
	rm -rf *.o *.out
