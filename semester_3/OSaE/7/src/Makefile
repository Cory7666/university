.PHONY: all compile clean

CC = gcc
CFLAGS = -g
CLIBS = -lpthread

SORT_PROG_NAME =    sort
MASTER_PROG_NAME =  master
THREADS_PROG_NAME = threads

all: compile
compile: $(SORT_PROG_NAME) $(MASTER_PROG_NAME) $(THREADS_PROG_NAME)
clean:
	rm -rf ./*.o

$(SORT_PROG_NAME): sort.o
$(MASTER_PROG_NAME): master.o
$(THREADS_PROG_NAME): threads.o
	$(CC) $(CFLAGS) -o "$@" "$^" $(CLIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o "$@" "$^"