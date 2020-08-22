#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define COLOR_OFF "\e[0m"
#define RED(text) "\e[0;31m"
#define GREEN(text) "\e[0;32m"

#define MASK4 0x0000000F
#define MASK8 0x000000FF
#define MASK16 0x0000FFFF
#define MASK32 0xFFFFFFFF

int main(int argc, char **argv)
{
	FILE *outVal, *outputFile;
	char count=0, rows=0;
	double valF=0, up, down, alim=1;
	unsigned long long int bin=0;
//	long double bin=0;
//	long double a=strtold(argv[1], &endptr), b=strtold(argv[2], &endptr), out_atteso=0;
	unsigned long long int a=atoll(argv[1]), b=atoll(argv[2]), out_atteso=0;
	int n=atoi(argv[5]);
	//short int i;
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
	alim=atof(argv[4]);
	up=0.7*alim;
	down=0.3*alim;
	while(	fscanf(outVal, "%s", val)!= EOF )
	{
		count++;
		if(count==3)
		{
			valF=atof(val);
			if(valF >= up)
			{	bin+=pow(2, rows);}
/*			{	bin |= (1 <<rows) ;	}
			else if (valF<= down)
			{	bin &=~ (1 <<rows);	}
			else
*/
			if(valF<up && valF>down)
			{
				printf("WARNING: param [%d] is between %f and %f\n", rows, down, up);
				fprintf(outputFile, "WARNING: param [%d] of %s is between %f and %f\n", rows, argv[3], down, up);
				if( valF>=0.50*alim)
				{	bin+=pow(2, rows);}
/*				{
					bin |= (1 <<rows) ;
				}
				else
				{
					bin &=~ (1 <<rows);
				}
*/			}
			count=0;
			rows++;
		}
	}
//	long double mask;
	unsigned long long int mask;
	switch (n)
	{
		case 4:
			mask = MASK4;
			break;
		case 8:
			mask = MASK8;
			break;
		case 16:
			mask = MASK16;
			break;
		case 32:
			mask = MASK32;
			break;
	}
//Controllo ingressi
	if (a> pow(2, n)-1)
	{	a = (a&mask);	}
	if (b>pow(2, n)-1)
	{	b = (b&mask);	}
	out_atteso=a*b;
	printf("inA\tinB\tout atteso\tout simul\n");
//	printf("%Lf\t%Lf\t%Lf\t\t%Lf\n", a, b, out_atteso, bin);
	printf("%lld\t%lld\t%lld\t\t%lld\n", a, b, out_atteso, bin);
	if (out_atteso != atoll(argv[3]))
	{
		fprintf(outputFile, "***WARNING: next line is different with input file ***\n");
	}
//	fprintf(outputFile, "%Lf\t%Lf\t%Lf\t\t%Lf\t", a, b, out_atteso, bin);
	fprintf(outputFile, "%lld\t%lld\t%lld\t\t%lld\t", a, b, out_atteso, bin);	
	if( bin == out_atteso )
	{
		printf("%sMatched%s\n", GREEN(text), COLOR_OFF);
//		fprintf(outputFile, "Matched\n");
	}
	else
	{
		printf("%sNot matched%s\n", RED(text), COLOR_OFF);
//		fprintf(outputFile, "Not matched\n");
	}
	fclose(outVal);
	fclose(outputFile);
	return 0;
}
