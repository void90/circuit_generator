#make -f Makefile
CC=gcc
CC_OPTS=-Wall
.phony:	clean all

all: src/csa.c src/confronta.c
	$(CC) src/csa.c $(CC_OPTS) -o bin/csa.out 
	$(CC) src/confronta.c $(CC_OPTS) -o bin/confronta.out 
clean:
	rm -rf bin/*.o bin/*.out

