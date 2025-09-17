
SRC = utils.o jacobi_eigensolver.o arg_parser.o triDag.o
TESTS = tests.o
INCL = -I./include
BUILD =  build

outfolder:
	mkdir -p $(BUILD)

compile:
	g++ -c tests/test.cpp $(INCL) -o test.o
	g++ -c src/utils.cpp $(INCL) -o utils.o
	g++ -c src/triDag.cpp $(INCL) -o triDag.o
	g++ -c src/jacobi_eigensolver.cpp $(INCL) -o jacobi_eigensolver.o
	g++ -c src/arg_parser.cpp $(INCL) -o arg_parser.o
	g++ -c main.cpp $(INCL) -o main.o

link:
	g++ main.o $(SRC)  -larmadillo -o $(BUILD)/main
	g++ test.o $(SRC) -larmadillo -o $(BUILD)/test

clean:
	rm -f *.o

test:
	./$(BUILD)/test

build: outfolder compile link clean

all: build test