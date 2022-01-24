# makefile for FPGA final project

all: main

main: main.o 
	g++ -o ../bin/main main.o

main.o: main.cpp
	g++ -c main.cpp

clean: 
	rm -rf *.o ../bin/main ../outputs/*