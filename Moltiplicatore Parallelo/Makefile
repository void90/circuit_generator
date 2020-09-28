#make -f Makefile
CC=gcc
CC_OPTS=-Wall -lm
.phony:	clean all

all: src/mp.c src/confronta.c
	$(CC) src/mp.c $(CC_OPTS) -o bin/mp.out 
	$(CC) src/confronta.c $(CC_OPTS) -o bin/confronta.out 
clean:
	rm -rf bin/*.o bin/*.out

