#make -f Makefile
CC=gcc
CC_OPTS=-Wall
.phony:	clean all

all: src/rca.c  
	$(CC) $(CC_OPTS) -o bin/rca.out $< 
clean:
	rm -rf bin/*.o bin/*.out
	
