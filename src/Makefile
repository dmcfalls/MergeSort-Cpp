# Makefile

CC = g++ -pthread

CFLAGS = -c -std=c++11 -O3 -Wall -pedantic

all: mergetest

mergetest: mergetest.o mergesort.o
	$(CC) mergetest.o mergesort.o -o mergetest

mergetest.o:
	$(CC) $(CFLAGS) mergetest.cc

mergesort.o: mergesort.cc mergesort.h
	$(CC) $(CFLAGS) mergesort.cc

clean:
	rm -f mergetest core *.o

.PHONY: clean all
