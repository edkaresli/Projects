# this is a makefile

CC=g++ -pthread -std=c++11

CFLAGS=-c -Wall -pthread -std=c++11

all: test

test: main.o
	$(CC) main.o -o ./bin/test

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean: 
	rm *.o ./bin/test

