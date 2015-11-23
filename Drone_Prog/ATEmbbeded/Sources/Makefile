CC = gcc
CFLAGS = -W -Wall
EXEC = test_com

SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)

ifdef DEBUG
    CFLAGS += -DDEBUG
endif

ifdef EMBED
    CFLAGS += -DEMBED
endif

all : $(EXEC)

test_com : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c $(wildcard %.h) debug.h
	$(CC) $(CFLAGS) -c $< -o $@
	
clean :
	rm -rf *.o

mrproper : clean
	rm -rf $(EXEC)
