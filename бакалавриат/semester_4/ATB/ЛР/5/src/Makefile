.PHONY: all

CXX=clang++
CXX_FLAGS=-O0 -g
PROGRAM_NAME=prog

all: $(PROGRAM_NAME)

$(PROGRAM_NAME): main.o graphs.o
	$(CXX) $(CXX_FLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c -o $@ $^
