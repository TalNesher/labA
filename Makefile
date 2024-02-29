all: encoder
encoder: encoder.c
	gcc -g -Wall -o encoder encoder.c

clean:
	rm -f encoder