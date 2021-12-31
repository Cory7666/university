.PHONY: all clean


GCC = gcc


all: Master3.old.exe Master3.mtx.exe Sort3.old.exe Sort3.mtx.exe Master3.crit.exe
clean:
	del *.exe

%.exe: %.c
	$(GCC) -g $^ -o $@