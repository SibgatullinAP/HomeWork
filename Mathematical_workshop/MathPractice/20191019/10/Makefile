DEBUG	= -g
CC	= gcc -c
LD	= gcc
CFLAGS	= $(DEBUG) -W -Wall
LIBS	=
LDFLAGS = $(DEBUG)

OBJS = process.o task.o

all : process

process  : $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

process.o : process.c task.h
	$(CC) $(CFLAGS) $< -o $@

task.o : task.c task.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) process
