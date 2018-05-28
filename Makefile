CC=g++
CFLAGS=-O4 -Wall -Wextra -Wno-unused-parameter -ggdb -march=native
TESTFLAGS=-lgtest -pthread -L./ -lmplib 

SRCDIR=./src
OBJDIR=./objs
TESTDIR=./test

_TESTDEPS=test.cpp
TESTDEPS=$(patsubst %, $(TESTDIR)/%, $(_TESTDEPS))

_DEPS=mpnumber.h
DEPS=$(patsubst %, $(SRCDIR)/%, $(_DEPS))

_OBJ=mpnumber.o addition.o subtraction.o multiplication.o division.o utils.o multiplication_algos.o
OBJ=$(patsubst %, $(OBJDIR)/%, $(_OBJ))


$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

build: $(OBJ)
	ar cr libmplib.a $(OBJ)

test: $(TESTDEPS) libmplib.a
	$(CC) -o $(TESTDIR)/test.elf $(TESTDIR)/test.cpp $(CFLAGS) $(TESTFLAGS)
	./test/test.elf

clean:
	rm -rf $(OBJDIR)/* $(TESTDIR)/*.elf libmplib.a