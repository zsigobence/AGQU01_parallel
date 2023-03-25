CC=gcc
CFLAGS=-Wall -Wextra -pthread

all: main

main: posix1.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f main
