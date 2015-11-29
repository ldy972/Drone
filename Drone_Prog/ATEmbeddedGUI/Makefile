CC = gcc
CFLAGS = -W -Wall
EXEC = test_com test_nav

TESTS = TestHl1.c test_navdata.c
SRC = $(filter-out $(TESTS), $(wildcard *.c))
OBJS = $(SRC:.c=.o)

ifdef DEBUG
    CFLAGS += -DDEBUG
endif

ifdef EMBED
    CFLAGS += -DEMBED
endif

all : $(EXEC)

test_com : TestHl1.o $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

test_nav : test_navdata.o $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c $(wildcard %.h) debug.h
	$(CC) $(CFLAGS) -c $< -o $@
	
clean :
	rm -rf *.o

mrproper : clean
	rm -rf $(EXEC)
