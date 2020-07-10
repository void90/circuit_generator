#include <stdio.h>
#include <math.h>



int main (int argc, char **argv) {

	int i, j, n;
	n = atoi(argv[2]);
	char *param[]={"sum", " cout", " ain", " bin"};
	char *param2[] = {"S", " Cout", " A", " B"};
	
	
	FILE *fp;
	FILE *fpr;
	fp=fopen(argv[1], "w");
	fprintf(fp, "*RIPPLE CARRY ADDER\n.option filetype=ascii\n.INCLUDE ST65LIKE_cell_library_v2020_1.net\n.INCLUDE 16nm_HP.pm\n.");
	fprintf(fp, ".PARAM vthVARn=0.3423\n.PARAM vthVARp=-0.23122.PARAM ndepVARn=3.96e+018\n.PARAM ndepVARp=1.68e+018\n.PARAM toxpVAR=5.21e-010\n.");
	fprintf(fp, "PARAM Lmin=16n\n.PARAM Wmin=16n\n.PARAM XXX=1\n.PARAM tr=50p\n");

	fprintf (fp, ".subckt RCA_SUB 0 Vdd ");		//DICHIARAZIONE SOTTOCIRCUITO

	for(i=0; i<4; i++) {
		for(j=0; j<n; j++)
		{
			if(i==1){j=n-1;}
			fprintf(fp, "%s%d ", param[i], j);
			if(i==1){fprintf(fp, "cin0 ");}
		}
	}

	fprintf(fp, " XX=1");
	fprintf(fp, "\nxfa0 0 Vdd sum0 cout0 cin0 ain0 bin0 FA_SUB XX=XXX \n");
	
	for (i = 1; i < n; i++) {
		fprintf(fp, "xfa%d 0 Vdd sum%d cout%d cout%d  ain%d  bin%d FA_SUB XX=XXX \n",i, i, i, i-1, i, i);
	}
	fprintf(fp, ".ends \n");		//FINE DICHIARAZIONE SOTTOCIRCUITO

	
	fprintf(fp, "xrca 0 Vcc ");		//DICHIARAZIONE DEL COMPONENTE


	for(i=0; i<4; i++)
	{
		for(j=0; j<n; j++)
		{
			if(i==1){j=n-1;}
			fprintf(fp, "%s%d ", param2[i], j);
			if(i==1){fprintf(fp, "Cin ");}
		}
	}



	fprintf(fp, "RCA_SUB XX=XXX\n");				//FINE DICHIARAZIONE COMPONENTE

	fprintf(fp, ".TRAN 0.1p 820p\n");
			
// ----------------------IMMISSIONE OPERANDI ED INIZIALIZZAZIONE INGRESSI----------------------

	int a, b, s;
	int N = n;
	int A_binary[N];
	int B_binary[N];
	int S_binary[N+1];		//comprende anche il bit di carry
	for (i = 0; i < N; i++) {
		A_binary[i] = 0;
		B_binary[i] = 0;
		S_binary[i] = 0;
	}
	S_binary[N] = 0;	//inizializzazione a zero del bit di carry_out

	fpr = fopen ("RCAdata.txt", "r");		//apertura file di lettura dati
	fscanf (fpr, "%d %d %d", &a, &b, &s);

	
	for (i = N; i >= 0; i--) {		//conversione somma da decimale a binario
		S_binary[i] = s%2;		
		s = s/2;
	}
	for (i = N-1; i >= 0; i--) {		//conversione operandi da decimale a binario
		A_binary[i] = a%2;
		a = a/2;
		B_binary[i] = b%2;
		b = b/2;
	}

//--------------STAMPA PER VERIFICA SOLO PER NOI------------------------------------
	printf ("Operando A:\n");
	for (i = 0; i < N; i++) {
		printf ("%d ", A_binary[i]);
	}
	printf ("\nOperando B:\n");
	for (i = 0; i < N; i++) {
		printf ("%d ", B_binary[i]);
	}
	printf ("\nRisultato atteso:\n");
	for (i = 1; i <= N; i++) {
		printf ("%d ", S_binary[i]);
	}
	printf ("\nCarry_out = %d\n", S_binary[0]);	//stampa del carry_out
//----------------------------------------------------------------------------------



	
	for (i = n-1, j = 0; i >= 0, j < N; i--, j++) {			//inizializzazione valori di A sulla netlist
			fprintf(fp, "VinA%d A%d 0 %d\n", i, i, A_binary[j]);	
	}
	for (i = n-1, j = 0; i >= 0, j < N; i--, j++) {			//inizializzazione valori di B sulla netlist
			fprintf(fp, "VinB%d B%d 0 %d\n", i, i, B_binary[j]);
	}


	fprintf(fp, "V_dd Vcc 0 1 \n.end");	//ALIMENTAZIONE E TERMINAZIONE NETLIST
	fclose(fpr);
	fclose(fp);
	return 0;
}