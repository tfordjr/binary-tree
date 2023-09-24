GCC = gcc
CFLAGS = -g -Wall -Wshadow

make:
	$(GCC) $(CFLAGS) -o P0 tree.c

clean: 
	rm -f P0 *.preorder *.postorder *.inorder
