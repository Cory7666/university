.PHONY: compile run

MPI_PACKAGE_NAME:=ompi-c
N?=3

PROGRAM=program
CC=gcc
CFLAGS += -Wall -fanalyzer -O0 -ggdb
CFLAGS += $(shell pkg-config --cflags "${MPI_PACKAGE_NAME}")
LIBS += $(shell pkg-config --libs "${MPI_PACKAGE_NAME}")

all: compile

compile: $(PROGRAM)

$(PROGRAM): main.o matrix.o
	$(CC) $(CFLAGS) -o $@ main.o matrix.o $(LIBS)

run: $(PROGRAM)
	mpirun -n ${N} $<

debug: $(PROGRAM)
	@gdb $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(LIBS)

matrix.c: matrix.h
main.c: matrix.h
