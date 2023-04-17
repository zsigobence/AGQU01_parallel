CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 -fopenmp
LDFLAGS=-fopenmp

all: erew_prefix

erew_prefix: erew_prefix.o
	$(CC) $(LDFLAGS) $^ -o $@

erew_prefix.o: erew_prefix.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f erew_prefix erew_prefix.o
