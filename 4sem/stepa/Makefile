IDIR = .
ODIR = .
SDIR = .

NAME = a.out

#CFLAGS = -Wall -Wextra -pedantic -Werror -lm -O3 -g
CFLAGS =

####################

vpath %.h   $(IDIR)
vpath %.cpp $(SDIR)

all: $(NAME)

$(NAME): $(ODIR)/main.o $(ODIR)/database.o $(ODIR)/hash.o $(ODIR)/tree.o $(ODIR)/list.o $(ODIR)/command.o $(ODIR)/record.o
	g++ $(CFLAGS) $^ -o $@
#	echo CFLAGS = $(CFLAGS)

$(ODIR)/main.o: main.cpp database.h record.h errors.h
$(ODIR)/database.o: database.cpp database.h list.h list_node.h tree.h hash.h command.h record.h errors.h
$(ODIR)/hash.o: hash.cpp hash.h tree.h list_node.h command.h record.h errors.h
$(ODIR)/tree.o: tree.cpp tree.h tree_node.h list_node.h command.h record.h errors.h
$(ODIR)/list.o: list.cpp list.h list_node.h command.h record.h errors.h
$(ODIR)/command.o: command.cpp command.h record.h errors.h
$(ODIR)/record.o: record.cpp record.h errors.h

$(ODIR)/%.o: %.cpp
	g++ -c -I $(IDIR) $(CFLAGS) $< -o $@

clean:
	rm $(ODIR)/*.o $(NAME) -f -v
