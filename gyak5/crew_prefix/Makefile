CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -fopenmp
LDFLAGS = -fopenmp

all: crew_prefix

crew_prefix: crew_prefix.o
	$(CC) $(LDFLAGS) -o $@ $^

crew_prefix.o: crew_prefix.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o crew_prefix
