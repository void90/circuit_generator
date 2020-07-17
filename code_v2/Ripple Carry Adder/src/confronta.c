#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
	FILE *outVal;
	float valF=0, up=0.70;
	int bin_intero[32];
	char count=0, bin_dec[32], bin_car[32], rows=0;
	char val[100];
//	outVal=fopen("netlist/outputValue.txt", "r");
/*TEST*/outVal=fopen("output.txt", "r");
	if(outVal==NULL)
	{
		printf("File \"outputValue.txt\" doesen't exist.\n");
		return-1;
	}
	while(	fscanf(outVal, "%s", val)!= EOF )
	{
		count++;
		if(count==3)
		{
			valF=atof(val);
			if(valF >= up)
			{
				bin_dec[rows]=1;
				bin_car[rows]='1';
			}
			else
			{
				bin_dec[rows]=0;	
				bin_car[rows]='0';
			}
			count=0;
			rows++;
		}
	}
printf("Stampa in binario come interi\nArray bin_dec di CHAR salvati in decimale:");
for(int i=0; i<rows; i++)
{printf("%d ", bin_dec[i]);
}
printf("\nStampa in binario come caratteri\nArray bin_car di CHAR salvati come caratteri");
for(int i=0; i<rows; i++)
{printf("%c ", bin_car[i]);
}
printf("\nStampa in binario come interi\nArray bin_int di INT salvati in decimale:");
for(int i=0; i<rows; i++)
{printf("%c ", bin_car[i]);
}
printf("\n");
	fclose(outVal);
	return 0;
}
