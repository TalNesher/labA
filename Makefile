all: encoder
encoder: encoder.c
	gcc -g -Wall -m32 -o encoder encoder.c

clean:
	rm -f encoder