all : clean main
FLAGS = -O3 -g
#FLAGS = -O3 -g -DDEBUG
#WARNINGS = -Wall -Wextra -pedantic -Werror
WARNINGS = -fsanitize=address -mfpmath=sse -fstack-protector-all -Wall -Wextra -pedantic -Werror
#WARNINGS = -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
main: main.o solve.o command.o list.o record.o command_action.o database.o hash.o megabase.o
	g++ $(FLAGS) $(WARNINGS) main.o solve.o command.o list.o record.o command_action.o database.o hash.o megabase.o
main.o: main.cpp
	g++ -c $(FLAGS) $(WARNINGS) main.cpp
solve.o: solve.cpp solve.h defenitions.h
	g++ -c $(FLAGS) $(WARNINGS) solve.cpp
command.o: command.cpp command.h
	g++ -c $(FLAGS) $(WARNINGS) command.cpp
list.o: list.cpp list.h
	g++ -c $(FLAGS) $(WARNINGS) list.cpp
record.o: record.cpp record.h
	g++ -c $(FLAGS) $(WARNINGS) record.cpp
command_action.o: command_action.cpp command.h
	g++ -c $(FLAGS) $(WARNINGS) command_action.cpp
database.o: database.cpp database.h
	g++ -c $(FLAGS) $(WARNINGS) database.cpp
hash.o: hash.cpp hash.h
	g++ -c $(FLAGS) $(WARNINGS) hash.cpp
megabase.o: megabase.cpp megabase.h
	g++ -c $(FLAGS) $(WARNINGS) megabase.cpp
clean:
	rm -f *.o *.out

