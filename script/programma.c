#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	printf("Nome netlist:%s \n", argv[3]);
	printf("Numero bit:%s \n", argv[4]);
	int a=atoi(argv[1]);
	int b=atoi(argv[2]);
	printf("Operandi: 1o:%d 2o:%d\n", a, b);
	return 0;
}
