CC = gcc
CFLAGS = -Wall -g
LIBS = -lcmocka

all: test

test: test_quicksort.c quicksort.c
	$(CC) $(CFLAGS) -o test test_quicksort.c quicksort.c $(LIBS)

run:
	./test

clean:
	rm -f test