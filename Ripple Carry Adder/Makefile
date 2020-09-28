#make -f Makefile
CC=gcc
CC_OPTS=-Wall -lm
.phony:	clean all

all: src/rca.c src/confronta.c
	$(CC) src/rca.c $(CC_OPTS) -o bin/rca.out 
	$(CC) src/confronta.c $(CC_OPTS) -o bin/confronta.out 
clean:
	rm -rf bin/*.o bin/*.out
	
