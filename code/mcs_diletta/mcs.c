#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char **argv)
{
//Inizializzazione variabili
	short int i, j, z, a, b;
	char *param[3]={"out", "xin", "yin"};
	char *param2[6] = {"sum", "Cout", "Cin", "a", "b", "out"};
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
	int n = atoi(argv[2]);
//Stampe netlist iniziali fisse
	fprintf(fp, "*MOLTIPLICATORE CARRY SAVE\n\n.option filetype=ascii\n.INCLUDE ../lib/ST65LIKE_cell_library_v2020_1.net\n.INCLUDE ../lib/16nm_HP.pm\n.PARAM Lmin=16n\n.PARAM Wmin=16n\n.TRAN 0.1p 500p\n.PARAM XXX=1\n\n* x & y sono ingressi\n.subckt AND_ARRAY_SUB 0 Vdd ");
	//.subckt AND_ARRAY_SUB
	for(i=0; i<2; i++)
	{
		for(j=0; j<n; j++)
		{
			fprintf(fp, "%s%d ", param[i], j);
		}
	}
	fprintf(fp, "y XX = 1\n");
	for(i=0; i<n; i++)
	{
		fprintf(fp, "\txand%d 0 Vdd %s%d %s%d y AND2_SUB XX=XXX\n", i, param[0], i, param[1], i);
	}
	//.subckt ADD_ARRAY_SUB
	fprintf(fp, ".ends\n\n*ai &bi (i=0..2) sono in Adder\n.subckt ADD_ARRAY_SUB 0 Vdd ");
	for(i=0; i<5; i++)
	{
		for(j=0; j<n-1; j++)
		{
			fprintf(fp, "%s%d ", param2[i], j);
		}
	}
	fprintf(fp, "XX = 1\n");
	for(i=0; i<n-1; i++)
	{
		fprintf(fp, "\txadd%d 0 Vdd sum%d cout%d cin%d a%d b%d FA_SUB XX = XXX\n", i, i, i, i, i, i);
	}
	//.subckt MCS_SUB
	fprintf(fp, ".ends\n\n* Zi->Uscute moltiplicatore; c->Carry d'uscita; Mj,Nj->Fattori d'ingresso. 	-----	Con [i=0,..,7; j=0,..,3]\n*xadd_array0 0 vdd z1 0sum1 0sum2 0cout0 0cout1 0cout2 0 0 0 1out0 1out1 1out2 0out1 0out2 0out3 ADD_ARRAY_SUB XX = XXX\n*xadd_array1 0 vdd z2 1sum1 1sum2 1cout0 1cout1 1cout2 0cout0 0cout1 0cout2 2out0 2out1 2out2 0sum1 0sum2 1out3 ADD_ARRAY_SUB XX = XXX\n*xadd_array2 0 vdd z3 2sum1 2sum2 2cout0 2cout1 2cout2 1cout0 1cout1 1cout2 3out0 3out1 3out2 1sum1 1sum2 2out3 ADD_ARRAY_SUB XX = XXX\n*xadd_level3 0 vdd z4 z5 z6 3cout0 3cout1 z7 0 3cout0 3cout1 2cout0 2cout1 2cout2 2sum1 2sum2 3out3 ADD_ARRAY_SUB XX = XXX\n\n.subckt MCS_SUB 0 Vdd ");
	for(i=0; i<n*2; i++)
	{
		fprintf(fp, "z%d ", i);
	}
	for(i=1; i<3; i++)
	{
		for(j=0; j<n; j++)
		{
			fprintf(fp, "%s%d ", param[i], j);
		}
	}
	fprintf(fp, "XX = 1\n");
	for(i=0; i<=n; i++)
	{
		if(i!=n)
		{
			fprintf(fp, "\txand4_level%d 0 Vdd ", i);
			for(j=0; j<n; j++)
			{
				if(i==0 && j==0)
				{	fprintf(fp, "z0 "); j=1;}
				fprintf(fp, "%dout%d ", i, j);
			}
			for(j=0; j<n; j++)
			{
				fprintf(fp, "xin%d ", j);
			}
			fprintf(fp, "yin%d AND_ARRAY_SUB XX = XXX\n", i);
		}
		if(i!=0)
		{
			fprintf(fp, "\txadd_array%d 0 Vdd z%d ", i-1, i);
			if(i==n)
			{
				for(j=n+1; j<n*2-1; j++)
				{
					fprintf(fp, "z%d ", j);
				}
			}
			else
			{
				for(j=1; j<n-1; j++)
				{
					fprintf(fp, "%dsum%d ", i-1, j);
				}
			}
			for(j=i-1; j>i-3; j--)
			{
				for(z=0; z<n-1; z++)
				{
					if(j>=0)
					{
						fprintf(fp, "%dcout%d ", j, z);
					}
					else if(j==-1 && i==1)
					{
						fprintf(fp, "0 ");
					}
				}
				
			}
			a=5; b=0;
			for(j=i; j>=i-1; j--)
			{
				for(z=b; z<n-1; z++)
				{
					if(j==i-1 && i>1)
					{	fprintf(fp, "%d", j-1);}
					else
					{	fprintf(fp, "%d", j);}
					fprintf(fp, "%s%d ", param2[a], z);
				}
				b=1;
				if(j==i && i!=1)
				{a=0;}
				
			}
fprintf(fp, "%dout%d ADD_ARRAY_SUB XX = XXX\n", i-1, n-1);
		}
	}
	fprintf(fp, ".ends\n\n");
	//DICHIARAZIONE COMPONENTE
	fprintf(fp, "\n\nxmcs 0 Vcc ");
	for(i=0; i<n*2; i++)
	{
		fprintf(fp, "zz%d ", i);
	}
	for(i=1; i<3; i++)
	{
		for(j=0; j<n; j++)
		{
			fprintf(fp, "z%c%d ", param[i][0], j);
		}
	}
	fprintf(fp, " MCS_SUB XX = XXX\n");
//Fine codice generazione netlist
//Conversione operandi di ingresso
	int x, y;
	x=atoi(argv[3]);
	y=atoi(argv[4]);
	int X_binary[n], Y_binary[n];
/*TEST*/int P_binary[n*2];
/*TEST*/int p = x*y;
/*TEST*/printf ("Risultato atteso: %d\n", p);	//risultato decimale atteso
/*TEST*/for (i = 2*n-1; i >= 0; i--) {		//risultato binario atteso
/*TEST*/	P_binary[i] = p%2;
/*TEST*/	p = p/2;
/*TEST*/}
	for (i = n-1; i >= 0; i--)
	{
		X_binary[i] = x%2;
		x = x/2;
		Y_binary[i] = y%2;
		y = y/2;
	}
//Scrittura ingressi convertiti nella netlist
	for (i = n-1, j = 0; j < n; i--, j++)
	{	//VALORI DI X
		fprintf(fp, "VinX%d XX%d 0 %d\n", i, i, X_binary[j]);
	}
	for (i = n-1, j = 0; j < n; i--, j++)
	{	//VALORI DI Y
		fprintf(fp, "VinY%d XY%d 0 %d\n", i, i, Y_binary[j]);
	}
	fprintf(fp, "V_dd Vcc 0 1\n");	//ALIMENTAZIONE
//--------------STAMPA PER VERIFICA CONVERSIONE INGRESSI E RISULTATO ATTESO------------------------------------
/*TEST*/printf ("Operando X:\n");
/*TEST*/for (i = 0; i < n; i++) {
/*TEST*/	printf ("%d ", X_binary[i]);
/*TEST*/}
/*TEST*/printf ("\nOperando Y:\n");
/*TEST*/for (i = 0; i < n; i++) {
/*TEST*/	printf ("%d ", Y_binary[i]);
/*TEST*/}
/*TEST*/printf ("\nRisultato atteso:\n");
/*TEST*/for (i = 1; i < 2*n; i++) {
/*TEST*/	printf ("%d ", P_binary[i]);
/*TEST*/}
//----------------------------------------------------------------------------------
//Scrittura parametri control nella netlist
	fprintf(fp, "\n.control\nrun\n");
/*TEST*/for(i=0; i<n*2; i++)
/*TEST*/{
/*TEST*/	fprintf(fp, "plot xz%d\n", i);
/*TEST*/}
	fprintf(fp, "\n.endc\n.end");	//TERMINAZIONE NETLIST
//Chiusura file
	fclose(fp);
	return 0;
}
