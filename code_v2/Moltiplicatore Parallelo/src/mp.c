#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define COLOR_OFF "\e[0m"
#define MAGENTA(text) "\e[0;35m"

int main (int argc, char **argv)
{
//Inizializzazione variabili
	float alim=atof(argv[5]);;
	//variabili di loop
	short int i, j, count, count2;
	//variabili di parametri
	int a, max, max_var, max_var2;
	char *str[10]={"out", "xin", "sum", "ain", "bin", "z", "xin_", "yin_", "s", "c"};
	char fileInput[50]={"netlist/"};
	strcat(fileInput, argv[1]);
//Apertura file
	FILE *fp;
	fp=fopen(fileInput, "w");
	if(fp==NULL)
	{
		printf("File doesen't exist.\n");
		return-1;
	}
	max = atoi(argv[2]);
//Stampe netlist iniziali fisse
	fprintf(fp, "MOLTIPLICATORE PARALLELO\n\n.option filetype=ascii\n.INCLUDE ../lib/ST65LIKE_cell_library_v2020_1.net \n.INCLUDE ../lib/16nm_HP.pm\n");
	fprintf(fp, ".PARAM ALIM=%f\n.PARAM Lmin=16n\n.PARAM Wmin=16n\n.PARAM XXX=1\n.TRAN ", alim);
	if(max==4 || max ==8)
	{
		fprintf(fp, "0.1p 820p");
	}
	else
	{
		fprintf(fp, "4p 4000p");
	}
	fprintf(fp, "\n\n.subckt PART_SUB 0 Vdd ");
//DICHIARAZIONE SOTTOCIRCUITO .subckt PART_SUB (and)
	a=0;
	for(i=0; i<max; i++)
	{
		fprintf(fp, "%s%d ", str[a], i);
		if(i==max-1 && a==0){a=1; i=-1;}
	}
	fprintf(fp, "y XX=1\n");
	for(i=0; i<max; i++)
	{
		fprintf(fp, "\txand%d 0 Vdd %s%d %s%d y AND2_SUB XX=XXX\n", i, str[0], i, str[1], i);
	}
	fprintf(fp, ".ends\n\n.subckt RCA_SUB 0 Vdd ");
//DICHIARAZIONE SOTTOCIRCUITO .subckt RCA_SUB (full adder)
	a=2;
	for(i=0; i<max; i++)
	{
		fprintf(fp, "%s%d ", str[a], i);
		if(i==max-1 && a!=4)
		{
			if(a==2){	fprintf(fp, "cout%d cin ", max-1);	}
			i=-1; a++;
		}
	}
	fprintf(fp, "XX=1\n");
	fprintf(fp, "\txfa0 0 Vdd sum0 cout0 0 ain0 bin0 FA_SUB XX=XXX\n");
	for(i=1; i<max; i++)
	{
		fprintf(fp, "\txfa%d 0 Vdd sum%d cout%d cout%d ain%d bin%d FA_SUB XX=XXX\n", i, i, i, i-1, i, i);
	}
	fprintf(fp, ".ends\n\n***numeroOut=uscita porte and\n***snumero znumero=uscita sommatori\n.subckt MP_SUB 0 Vdd ");
//DICHIARAZIONE SOTTOCIRCUITO .subckt MP_SUB(4 and+full adder)
	max=max+max; a=5;
	for(i=0; i<max; i++)
	{
		fprintf(fp, "%s%d ", str[a], i);
		if(i==max-1)
		{
			if(a==5)
			{
				max=max/2;
				fprintf(fp, "c0 ");
			}
			if(a!=7)
			{i=-1;}
			a++;
		}
	}
	fprintf(fp, "XX=1\n");
	a=8; j=1, count=1; count2=1; max_var=max; max_var2=max;
	for(i=0; i<max; i++)
	{
		fprintf(fp, "\txpart%d 0 Vdd ", i);
		if(i==0)
		{
			fprintf(fp, "z0 ");
		}
		while(j<max)
		{
			fprintf(fp, "%dout%d ", i, j);
			j++;
		}
		for(j=0; j<max; j++)
		{
			fprintf(fp, "xin_%d ", j);
		}
		fprintf(fp, "yin_%d PART_SUB XX=XXX\n", i);
		if(i!=0)
		{
			fprintf(fp, "\txadd%d 0 Vdd z%d ", i-1, i);
			if(i==max-1)
			{
				for(j=max; j<max*2; j++)
				{
					fprintf(fp, "z%d ", j);
				}
			}
			else
			{
				for(j=count; j<max_var; j++)
				{
					fprintf(fp, "s%d ", j);
				}
				fprintf(fp, "c%d ", j-1);
				count=j;
				max_var=max_var+max-1;
			}
			fprintf(fp, "c0 ");
			if(i==1)
			{
				for(j=1; j<max; j++)
				{
					fprintf(fp, "%dout%d ", i-1, j);
				}
				fprintf(fp, "0 ");
			}
			else
			{
				for(j=count2; j<max_var2; j++)
				{
					fprintf(fp, "s%d ", j);
				}
				fprintf(fp, "c%d ", j-1);
				count2=j;
				max_var2=max_var2+max-1;
			}
			for(j=0; j<max; j++)
			{
				fprintf(fp, "%dout%d ", i, j);
			}
			fprintf(fp, "RCA_SUB XX=XXX\n");
		}
		j=0;
	}
	fprintf(fp, ".ends\n\n");
	//FINE DICHIARAZIONE SOTTOCIRCUITI
//DICHIARAZIONE DEL COMPONENTE
	fprintf(fp, "xmp 0 Vcc ");
	for(i=0; i<max*2; i++)
	{
		fprintf(fp, "zz%d ", i);
	}
	fprintf(fp, "zc0 ");
	for(i=0; i<max; i++)
	{
		fprintf(fp, "x%d ", i);
	}
	for(i=0; i<max; i++)
	{
		fprintf(fp, "y%d ", i);
	}
	fprintf(fp, "MP_SUB XX=XXX\n\n");
	//FINE DICHIARAZIONE COMPONENTE
	//Fine codice generazione netlist
//Conversione operandi di ingresso
	unsigned long long int x, y;
/*TEST*/unsigned long long int p;
	x=atof(argv[3]);
	y=atof(argv[4]);
//Controllo ingressi
	if( (x> (pow(2, max)-1)) || (y> (pow(2, max)-1)))
	{
		printf("%sWARNING%s: inserted number aren't representable with %d bit\n", MAGENTA(text), COLOR_OFF, max);
		return -1;
	}
	int X_binary[max];
	int Y_binary[max];
///*TEST*/int P_binary[max*2];
	for (i = max-1; i >= 0; i--)
	{	//conversione operandi da decimale a binario
		X_binary[i] = x%2;
		x = x/2;
		Y_binary[i] = y%2;
		y = y/2;
	}
/*TEST*/for (i = 2*max-1; i >= 0; i--)
/*TEST*/{	//conversione prodotto da decimale a binario
///*TEST*/	P_binary[i] = p%2;
/*TEST*/	p = p/2;
/*TEST*/}
//Scrittura ingressi convertiti nella netlist
	for (i = max-1, j = 0; j < max; i--, j++)
	{	//inizializzazione valori di X sulla netlist
		fprintf(fp, "VinX%d X%d 0 ", i, i);
		if(X_binary[j]==1)
		{	fprintf(fp, "ALIM\n");}
		else
		{	fprintf(fp, "0\n");}
	}
	for (i = max-1, j = 0; j < max; i--, j++)
	{	//inizializzazione valori di Y sulla netlist
		fprintf(fp, "VinY%d Y%d 0 ", i, i);
		if(Y_binary[j]==1)
		{	fprintf(fp, "ALIM\n");}
		else
		{	fprintf(fp, "0\n");}
	}
	fprintf(fp, "\nV_dd Vcc 0 ALIM\n");	//ALIMENTAZIONE E TERMINAZIONE NETLIST
//Scrittura parametri control nella netlist
	fprintf(fp, "\n.control\nrun\nlet k= length(time)-1\nprint ");
	for(i=0; i<max*2; i++)
	{
		fprintf(fp, " zz%d[k]", i);
	}
	fprintf(fp, ">outputValue.txt\nquit\n.endc\n.end");	//TERMINAZIONE NETLIST
//Chiusura file
	fclose(fp);
	return 0;
}
