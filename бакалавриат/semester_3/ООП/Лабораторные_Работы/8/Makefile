.PHONE: all run compile debug clean

PROG_NAME = program

SRC_FILES = main.cpp
HEADER_FILES = main.hpp

CC = g++
CWARNINGS = 
CLIBS = 
CFLAGS = -O0 $(CWARNINGS)

all: run
compile: $(subst .cpp,.o,$(SRC_FILES))
	$(CC) -g $(CFLAGS) -o $(PROG_NAME) $^ $(addprefix -l,$(CLIBS));

run: $(subst .cpp,.o,$(SRC_FILES))
	$(CC) $(CFLAGS) -o /tmp/$(PROG_NAME) $^ $(addprefix -l,$(CLIBS));
	if [ -f /tmp/$(PROG_NAME) ]; then /tmp/$(PROG_NAME); rm -rf /tmp/$(PROG_NAME); fi;

debug: $(subst .cpp,.o,$(SRC_FILES))
	$(CC) -g $(CFLAGS) -o /tmp/$(PROG_NAME) $^ $(addprefix -l,$(CLIBS));
	if [ -f /tmp/$(PROG_NAME) ]; then gdb /tmp/$(PROG_NAME); rm -rf /tmp/$(PROG_NAME); fi;

clean:
	rm -rf *.o $(PROG_NAME)



%.o: %.cpp $(HEADER_FILES)
	$(CC) -c -g $(CFLAGS) -o $@ $< $(addprefix -l,$(CLIBS));