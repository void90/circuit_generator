#make -f Makefile
CC=gcc
CC_OPTS=-Wall
.phony:	clean all

all: src/mcs.c  
	$(CC) $(CC_OPTS) -o bin/mcs.out $< 
clean:
	rm -rf bin/*.o bin/*.out
	
