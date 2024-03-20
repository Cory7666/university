.PHONY: test-cycbuffer-compile test-cycbuffer-debug run compile

CFLAGS += -fanalyzer -I./syntax_analyzer -I.

ifdef NDEBUG
CFLAGS += -DNDEBUG -O2 -flto -fno-asynchronous-unwind-tables -Wl,--strip-all \
		  -ffunction-sections -Wl,--gc-sections
else
CFLAGS += -DDEBUG -O0 -ggdb
endif

run: compile
	./program

debug: compile
	gdb program

compile: cycbuffer libsyntaxanalyzer.a
	gcc $(CFLAGS) -L. \
				  -o program main.c \
				  buffer.o -lsyntaxanalyzer

test-cycbuffer-compile: cycbuffer
	gcc $(CFLAGS) -o test-cycbuffer test_cycbuffer.c buffer.c

test-cycbuffer-debug: test-cycbuffer-compile
	gdb test-cycbuffer

cycbuffer: buffer.c
	gcc $(CFLAGS) -c -o buffer.o $^

libsyntaxanalyzer.a: syntax_analyzer/syntax_analyzer_states.c syntax_analyzer/syntax_analyzer.c
	gcc $(CFLAGS) -c -o syntax_analyzer_states.o syntax_analyzer/syntax_analyzer_states.c
	gcc $(CFLAGS) -c -o syntax_analyzer.o        syntax_analyzer/syntax_analyzer.c
	ar rcs libsyntaxanalyzer.a syntax_analyzer_states.o syntax_analyzer.o
