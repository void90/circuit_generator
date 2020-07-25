#make -f Makefile
CC=gcc
CC_OPTS=-Wall -lm
.phony:	clean all

all: src/mcs.c src/confronta.c
	$(CC) src/mcs.c $(CC_OPTS) -o bin/mcs.out 
	$(CC) src/confronta.c $(CC_OPTS) -o bin/confronta.out 
clean:
	rm -rf bin/*.o bin/*.out

