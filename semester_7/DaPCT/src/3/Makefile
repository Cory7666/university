.PHONY: all

N?=4

PROGRAM=program
MPI_PACKAGE_NAME=ompi-c
MPIRUN=mpirun
CC=gcc
CFLAGS+=-Wall -fanalyzer -O0 -ggdb
CFLAGS+=$(shell pkg-config --cflags "$(MPI_PACKAGE_NAME)")
CLIBS+=$(shell pkg-config --libs "$(MPI_PACKAGE_NAME)") -lm

all: $(PROGRAM)

run: $(PROGRAM)
	$(MPIRUN) --use-hwthread-cpus -n $(N) $<

$(PROGRAM): main.o
	$(CC) $(CFLAGS) -o $@ main.o $(CLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(CLIBS)
