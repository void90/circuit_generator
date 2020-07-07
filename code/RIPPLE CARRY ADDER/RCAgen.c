#include <stdio.h>
#include <math.h>



int main (int argc, char **argv) {

	int i, j, n;
	printf("Inserire numero di bit del Ripple Carry Adder da generare:\n");
	scanf("%d", &n);
	char *param[]={"sum", " cout", " ain", " bin"};
	char *param2[] = {"S", " Cout", " A", " B"};
	
	
	FILE *fp;
	fp=fopen("argv[1]", "w");
	fprintf(fp, "*RIPPLE CARRY ADDER\n.option filetype=ascii\n.INCLUDE ST65LIKE_cell_library_v2020_1.net\n.INCLUDE 16nm_HP.pm\n.INCLUDE param.net\n");
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

	int a, b;
	int N = n;
	int A_binary[N];
	int B_binary[N];
	int S_binary[N];
	for (i = 0; i < N; i++) {
		A_binary[i] = 0;
		B_binary[i] = 0;
		S_binary[i] = 0;
	}

	start: printf ("Digitare gli operandi da sommare:\n");
	scanf ("%d %d", &a, &b);
	int s = a+b;
	if (s > pow(2, n)-1) {
		printf ("Numero di bit insufficienti alla rappresentazione del risultato e/o degli operandi.\n");
		goto start;
	}
	
	printf ("Risultato atteso: %d\n", s);	//risultato decimale atteso

	for (i = N-1; i >= 0; i--) {		//risultato binario atteso
		S_binary[i] = s%2;
		s = s/2;
	}
	for (i = N-1; i >= 0; i--) {
		A_binary[i] = a%2;
		a = a/2;
		B_binary[i] = b%2;
		b = b/2;
	}
	printf ("Operando A:\n");
	for (i = 0; i < N; i++) {
		printf ("%d ", A_binary[i]);
	}
	printf ("\nOperando B:\n");
	for (i = 0; i < N; i++) {
		printf ("%d ", B_binary[i]);
	}
	printf ("\nRisultato atteso:\n");
	for (i = 0; i < N; i++) {
		printf ("%d ", S_binary[i]);
	}




	
	for (i = n-1, j = 0; i >= 0, j < N; i--, j++) {			//VALORI DI A
			fprintf(fp, "VinA%d A%d 0 %d\n", i, i, A_binary[j]);	
	}
	for (i = n-1, j = 0; i >= 0, j < N; i--, j++) {			//VALORI DI B
			fprintf(fp, "VinB%d B%d 0 %d\n", i, i, B_binary[j]);
	}


	fprintf(fp, "V_dd Vcc 0 1 \n.end");	//ALIMENTAZIONE E TERMINAZIONE NETLIST

	fclose(fp);
	return 0;
}
