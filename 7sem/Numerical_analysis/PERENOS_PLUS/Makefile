SRCS = \
    func.c \
    input.c \
    normi.c \
    otl_glad.c \
    peren_h2.c \
    print.c \
    progon.c \
    tabtex.c

OBJS = $(SRCS:.c=.o)

all: peren_h2

peren_h2: $(OBJS)
	gcc -o $@ $^ -lm

%.o: %.c
	gcc -o $@ $< -c

clean:
	rm *.o peren_h2