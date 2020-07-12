#make -f Makefile
CC=gcc
CC_OPTS=-Wall
.phony:	clean all

all: src/mp.c  
	$(CC) $(CC_OPTS) -o bin/mp.out $< 
clean:
	rm -rf bin/*.o bin/*.out
	
