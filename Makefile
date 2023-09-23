GCC = gcc
CFLAGS = -g -Wall -Wshadow

make:
	$(GCC) $(CFLAGS) -o P tree.c

clean: 
	rm -f P P0
