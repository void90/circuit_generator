#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
	FILE *outVal;
	float valF=0, up, down;
	int alim=1;
//	int bin_intero[64];
	char count=0, bin[64], rows=0;
	char val[100];
//	outVal=fopen("netlist/outputValue.txt", "r");
/*TEST*/outVal=fopen("output.txt", "r");
	if(outVal==NULL)
	{
		printf("File \"outputValue.txt\" doesen't exist.\n");
		return-1;
	}
	if(argc==2)
	{	alim=atoi(argv[1]);}
	up=0.7*alim;
	down=0.3*alim;
	while(	fscanf(outVal, "%s", val)!= EOF )
	{
		count++;
		if(count==3)
		{
			valF=atof(val);
			if(valF >= up)
			{
				bin[rows]=1;
//				bin_intero[rows]=1;
			}
			else if (valF<= down)
			{
				bin[rows]=0;	
//				bin_intero[rows]=0;
			}
			else
			{
				printf("WARNING: param bin[%d] is between %f and %f\n", rows, down, up);
				if( valF>=0.50*alim)
				{	bin[rows]=1;}
				else
				{	bin[rows]=0;}
			}
			count=0;
			rows++;
		}
	}
printf("Stampa in binario come interi\nArray bin_dec di CHAR salvati in decimale:");
for(int i=0; i<rows; i++)
{printf("%d ", bin[i]);
}
printf("\n");
	fclose(outVal);
	return 0;
}
