.PHONY: all

N?=2

PROGRAM=program
MPI_PACKAGE_NAME=ompi-c
MPIRUN=mpirun

CC=gcc
CXX=g++
CFLAGS+=-Wall -fanalyzer -O0 -ggdb
CFLAGS+=$(shell pkg-config --cflags "$(MPI_PACKAGE_NAME)")
CLIBS+=$(shell pkg-config --libs "$(MPI_PACKAGE_NAME)") -lm

SOURCES=main.c intstack.c
OBJS=$(patsubst %.c,%.o,$(SOURCES))

all: $(PROGRAM)

run: $(PROGRAM)
	$(MPIRUN) --use-hwthread-cpus -n $(N) $<

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(CLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(CLIBS)

%.o: %.cxx
	$(CXX) $(CFLAGS) -c -o $@ $< $(CLIBS)

