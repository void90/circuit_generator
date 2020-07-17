#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char **argv)
{
//Inizializzazione variabili
	int n = atoi(argv[2]), alim=1;
	short int i, j;
	char *param[4]={"sum", " cout", " ain", " bin"};
	char *param2[4] = {"S", " Cout", " A", " B"};
	char fileInput[50]={"netlist/"};
	strcat(fileInput, argv[1]);
//Apertura file
	FILE *fp;
	fp=fopen(fileInput, "w");
//fp=fopen(argv[1], "w");
	if(fp==NULL)
	{
		printf("File doesen't exist.\n");
		return-1;
	}
//Inserimento eventuale dell'alimentazione
	if(argc==6)
	{	alim=atoi(argv[5]);	}
//Stampe netlist iniziali fisse
	fprintf(fp, "*RIPPLE CARRY ADDER\n.option filetype=ascii\n.INCLUDE ../lib/ST65LIKE_cell_library_v2020_1.net \n.INCLUDE ../lib/16nm_HP.pm\n");
	fprintf(fp, ".PARAM ALIM=%d\n.PARAM Lmin=16n\n.PARAM Wmin=16n\n.PARAM XXX=1\n.TRAN 0.1p 820p\n", alim);	
//Codice generazione netlist cartella code
	//DICHIARAZIONE SOTTOCIRCUITO
	fprintf (fp, ".subckt RCA_SUB 0 Vdd ");	
	for(i=0; i<4; i++)
	{		
		for(j=0; j<n; j++)
		{
			if(i==1)
				{j=n-1;}
			fprintf(fp, "%s%d ", param[i], j);
			if(i==1)
				{fprintf(fp, "cin0 ");}
		}
	}
	fprintf(fp, "XX=1");
	fprintf(fp, "\nxfa0 0 Vdd sum0 cout0 cin0 ain0 bin0 FA_SUB XX=XXX \n");
	for (i = 1; i < n; i++)
	{
		fprintf(fp, "xfa%d 0 Vdd sum%d cout%d cout%d  ain%d  bin%d FA_SUB XX=XXX \n",i, i, i, i-1, i, i);
	}
	fprintf(fp, ".ends \n");		
	//FINE DICHIARAZIONE SOTTOCIRCUITO
	//DICHIARAZIONE DEL COMPONENTE
	fprintf(fp, "xrca 0 Vcc ");
	for(i=0; i<4; i++)
	{
		for(j=0; j<n; j++)
		{
			if(i==1)
				{j=n-1;}
			fprintf(fp, "%s%d ", param2[i], j);
			if(i==1)
				{fprintf(fp, "Cin ");}
		}
	}
	fprintf(fp, "RCA_SUB XX=XXX\n");
	//FINE DICHIARAZIONE COMPONENTE
//Fine codice generazione netlist
//Conversione operandi di ingresso
	int a, b;
/*TEST*/int s;
	a = atoi (argv[3]);
	b = atoi (argv[4]);
	int A_binary[n], B_binary[n];
///*TEST*/int S_binary[n+1];		//comprende anche il bit di carry
/*TEST*/for (i = n; i >= 0; i--)
/*TEST*/{	//conversione somma da decimale a binario
///*TEST*/	S_binary[i] = s%2;		
/*TEST*/	s = s/2;
/*TEST*/}
	for (i = n-1; i >= 0; i--)
	{	//conversione operandi da decimale a binario
		A_binary[i] = a%2;
		a = a/2;
		B_binary[i] = b%2;
		b = b/2;
	}
//Scrittura ingressi convertiti nella netlist
	for (i = n-1, j = 0; j < n; i--, j++)
	{	//inizializzazione valori di A sulla netlist
		fprintf(fp, "VinA%d A%d 0 ", i, i);
		if(A_binary[j]==1)
		{	fprintf(fp, "ALIM\n");}	
		else
		{	fprintf(fp, "0\n");}		
	}
	for (i = n-1, j = 0; j < n; i--, j++)
	{	//inizializzazione valori di B sulla netlist
		fprintf(fp, "VinB%d B%d 0 ", i, i);
		if(B_binary[j]==1)
		{	fprintf(fp, "ALIM\n");}	
		else
		{	fprintf(fp, "0\n");}		
	}
	fprintf(fp, "V_dd Vcc 0 ALIM\n");	//ALIMENTAZIONE E TERMINAZIONE NETLIST
//--------------STAMPA PER VERIFICA CONVERSIONE INGRESSI E RISULTATO ATTESO------------------------------------
/*TEST*/printf ("Operando A:\n");
/*TEST*/for (i = 0; i < n; i++) {
/*TEST*/	printf ("%d ", A_binary[i]);
/*TEST*/}
/*TEST*/printf ("\nOperando B:\n");
/*TEST*/for (i = 0; i < n; i++) {
/*TEST*/	printf ("%d ", B_binary[i]);
/*TEST*/}
///*TEST*/printf ("\nRisultato atteso:\n");
///*TEST*/for (i = 1; i <= n; i++) {
///*TEST*/	printf ("%d ", S_binary[i]);
///*TEST*/}
///*TEST*/printf ("\nCarry_out = %d\n", S_binary[0]);	//stampa del carry_out
	printf("\n");
//----------------------------------------------------------------------------------
//Scrittura parametri control nella netlist
	fprintf(fp, "\n.control\nrun\nlet k= length(time)-1\nprint");
	for(i=0; i<n; i++)
	{
		fprintf(fp, " s%d[k]", i);
	}
	fprintf(fp, ">outputValue.txt\nquit\n.endc\n.end");	//TERMINAZIONE NETLIST
//Chiusura file
	fclose(fp);
	return 0;
}
