#include <stdio.h>
#include <stdlib.h>
#define COLOR_OFF "\e[0m"
#define RED(text) "\e[0;31m"
#define GREEN(text) "\e[0;32m"

int main(int argc, char **argv)
{
	FILE *outVal, *outputFile;
	float valF=0, up, down, alim=1;
	unsigned long long int bin=0;
	char count=0, rows=0;
	char val[100];
	outputFile=fopen("outputFile.txt", "a");
	if(outputFile==NULL)
	{
		printf("File \"outputFile.txt\" doesen't exist.\n");
		return -1;
	}
	outVal=fopen("netlist/outputValue.txt", "r");
///*TEST*/outVal=fopen("output.txt", "r");
	if(outVal==NULL)
	{
		printf("File \"outputValue.txt\" doesen't exist.\n");
		return-1;
	}
	if(argc==3)
	{	alim=atof(argv[2]);}
	up=0.7*alim;
	down=0.3*alim;
	while(	fscanf(outVal, "%s", val)!= EOF )
	{
		count++;
		if(count==3)
		{
			valF=atof(val);
			if(valF >= up)
			{	bin |= (1 <<rows) ;	}
			else if (valF<= down)
			{	bin &=~ (1 <<rows);	}
			else
			{
				printf("WARNING: param [%d] is between %f and %f\n", rows, down, up);
				fprintf(outputFile, "WARNING: param [%d] of %s is between %f and %f\n", rows, argv[1], down, up);
				if( valF>=0.50*alim)
				{
					bin |= (1 <<rows) ;
				}
				else
				{
					bin &=~ (1 <<rows);
				}
			}
			count=0;
			rows++;
		}
	}
	printf("Risultato atteso: %s\tRisultato ottenuto: %llu\t", argv[1], bin);
	fprintf(outputFile, "Risultato atteso: %s\tRisultato ottenuto: %llu\t", argv[1], bin);
	if( bin == atoi(argv[1]))
	{
		printf("%sMatched%s\n", GREEN(text), COLOR_OFF);
		fprintf(outputFile, "Matched\n");
	}
	else
	{
		printf("%sNot matched%s\n", RED(text), COLOR_OFF);
		fprintf(outputFile, "Not matched\n");
	}
	fclose(outVal);
	fclose(outputFile);
	return 0;
}
