#include <stdio.h>
#include <math.h>


int main (int argc, char **argv) {

	int i, j, n, out_idx = 0;
	printf("Inserire numero di bit dei fattori in ingresso al Moltiplicatore Carry Save da generare:\n");
	scanf("%d", &n);
	char *param[3]={"out", "x", "y"};
	char *param2[4] = {"sum", " Cout", "a", "b"};
	
	FILE *fp;
	fp=fopen(argv[1], "w");
	fprintf(fp, "*MOLTIPLICATORE CARRY SAVE\n\n.option filetype=ascii\n\n.INCLUDE ST65LIKE_cell_library_v2020_1.net\n.INCLUDE 16nm_HP.pm\n.INCLUDE param.net\n\n");

//DICHIARAZIONE SOTTOCIRCUITO 4xAND2_SUB	
	fprintf (fp, ".subckt AND_ARRAY_SUB\t0 Vdd ");
	for( i = 0; i < 2; i++ ) 
	{
		for( j = 0; j < n; j++ )
		{
			fprintf(fp, "%s%d ", param[i], j);
		}
	}
	fprintf(fp, "y\tXX=1\n");
	for ( i = 0; i < n; i++)
	{
		fprintf (fp,"xand%d\t0 Vdd out%d x%d y\tAND2_SUB XX=XXX\n", i, i, i);
	}
	fprintf(fp, ".ends \n\n");

//DICHIARAZIONE SOTTOCIRCUITO 3xFA_SUB	
	fprintf (fp, ".subckt ADD_ARRAY_SUB\t0 Vdd ");
	for( i = 0; i < 4; i++ ) 
	{
		for( j = 0; j < n; j++)
		{
			fprintf(fp, "%s%d ", param2[i], j);
		}
	}
	fprintf(fp, "\tXX=1\n");
	for ( i = 0; i < n; i++)	//non è fino ad n!!!!!!
	{
		fprintf (fp,"xadd%d\t 0 vdd sum%d cout%d cin%d b%d a%d\t FA_SUB XX=XXX\n", i, i, i, i, i, i);
	}
	fprintf(fp, ".ends \n\n");
	
//DICHIARAZIONE MCS_SUB
	fprintf (fp, ".subckt MCS_SUB\t0 Vdd ");
	for( i = 0; i < 3; i++ ) 
	{
		for( j = 0; j < n; j++)
		{
			fprintf(fp, "%s%d ", param[i], j);
		}
	}
	fprintf(fp, "\tXX=1\n");
	
	int num_level = n*2;
	//Gestire: se n=1 deve essere solo una porta AND

	for ( i = 0; i < num_level; i++)	//Il num totale di livelli AND+ADD è pari al doppio dei bit
	{
		if ( i == 0 )
		{
			fprintf (fp,"xand_Level%d\t 0 vdd\tz%d ", i, out_idx++);	//out_idx con post increment
			for ( j = 0; j < n; j++)
			{
				fprintf (fp,"%dout%d ", i, j+1);
			} 
			fprintf (fp,"\t");
			for ( j = 0; j < n; j++)
			{
				fprintf (fp,"x%d ", j);
			} 
			fprintf (fp,"\ty%d\tAND_ARRAY_SUB XX = XXX\n", i);
		}
		
		if ( i == 1 )
		{
			fprintf (fp,"xand_Level%d\t 0 vdd\t", i);		
			for ( j = 0; j < n; j++)
			{
				fprintf (fp,"%dout%d ", i, j);
			} 
			fprintf (fp,"\t");
			for ( j = 0; j < n; j++)
			{
				fprintf (fp,"x%d ", j);
			} 
			fprintf (fp,"\ty%d\tAND_ARRAY_SUB XX = XXX\n", i);
		}
		
		// Ogni Array di somatori sono in numero pari a Num_bit_fattore - 1
		if ( (i > 1) && (i%2 == 0) && (i < (num_level - 1)) )		//Livelli intermedi di ADDIZIONE
		{			
			fprintf (fp,"xadd_Level%d\t 0 vdd\tz%d ", i, out_idx++);	//out_idx con post increment		
			for ( j = 0; j < (n-2); j++)					// n-2 perchè il primo termine di somma è sempre Zi
			{
				fprintf (fp,"%dsum%d ", i, j+1);
			} 
			fprintf (fp,"\t");
			for ( j = 0; j < (n-1); j++)
			{
				fprintf (fp,"%dcout%d ", i, j);
			}
			fprintf (fp,"\t");
			// Connessione Cin: livello 2 sono sempre tutti HA
			if ( i == 2 )
			{
				for ( j = 0; j < (n-1); j++)
				{
					fprintf (fp,"0     ");
				}
			} else 
			{
				for ( j = 0; j < (n-1); j++)
				{
					fprintf (fp,"%dcout%d ", i-2, j );
				}
			}
			fprintf (fp,"\t");
			// Connessione Ai e Bi: nel Livello 2 gli ingressi sono solo da porte and, altrimenti gli ingressi sono dalle porte and e dalle somme
			for ( j = 0; j < (n-1); j++)		//Ai
			{
				fprintf (fp,"%dout%d ", i-1, j);
			}
			fprintf (fp,"\t");
			if ( i == 2 )					//Bi
			{
				for ( j = 0; j < (n-1); j++)		//Livello 2: gli ingressi vengono solo dalle porte and e non dalle uscite dei sommatori precedenti
				{
					fprintf (fp,"%dout%d ", i-2, j+1 );
				}
			} else 
			{
				for ( j = 0; j < (n-2); j++)
				{
					fprintf (fp,"%dsum%d ", i-2, j+1 );
				}
				fprintf (fp,"%dout%d ", i-3, n-1 );
			}
			fprintf (fp,"\t");				
			fprintf (fp,"\tADD_ARRAY_SUB XX = XXX\n");
		} else if ( (i > 1) && (i%2 == 1) && (i < (num_level - 1)) )		//Livelli intermedi di ADDIZIONE
		{
			fprintf (fp,"xand_Level%d\t 0 vdd\t", i);		
			for ( j = 0; j < n; j++)
			{
				fprintf (fp,"%dout%d ", i, j);
			} 
			fprintf (fp,"\t");
			for ( j = 0; j < n; j++)
			{
				fprintf (fp,"x%d ", j);
			} 
			fprintf (fp,"\ty%d\tAND_ARRAY_SUB XX = XXX\n", i-2);

		} else if ( (i > 1) && (i >= (num_level - 2)) )			//Ultimi 2 livelli finali di ADDIZIONE
		{
			fprintf (fp,"xadd_Level%d\t 0 vdd\tz%d ", i, out_idx++);	//out_idx con post increment		
			for ( j = 0; j < (n-2); j++)
			{
				out_idx += j;
				fprintf (fp,"z%d    ", out_idx);
			} 
			fprintf (fp,"\t");
			for ( j = 0; j < (n-2); j++)
			{
				fprintf (fp,"%dcout%d ", i, j);
			}
			fprintf (fp,"z%d    \t", ++out_idx);				//pre incremento
			// Connessione Cin: livello 2 sono sempre tutti HA
					fprintf (fp,"0     ");
			{
				for ( j = 1; j < (n-1); j++)
				{
					fprintf (fp,"%dcout%d ", i, j-1 );
				}
			}
			fprintf (fp,"\t");
			// Connessione Ai e Bi: nel Livello 2 gli ingressi sono solo da porte and, altrimenti gli ingressi sono dalle porte and e dalle somme
			for ( j = 0; j < (n-1); j++)		//Ai
			{
				fprintf (fp,"%dcout%d ", i-1, j);
			}
			fprintf (fp,"\t");
			
			for ( j = 0; j < (n-2); j++)
				{
				fprintf (fp,"%dsum%d ", i-2, j+1 );
			}
			fprintf (fp,"%dout%d ", i-3, n-1 );
			fprintf (fp,"\tADD_ARRAY_SUB XX = XXX\n");
			
			fprintf (fp,"\t");
		}
	}
	fprintf(fp, ".ends \n\n");
	
//Dichiarazione del componente 
	fprintf(fp, "xmcs%d 0 Vcc ",n );
	for ( i = 0; i<num_level; i++)
	{
		fprintf(fp, "xz%d ",i);
	}
	for ( i = 0; i<n; i++)
	{
		fprintf(fp, "xx%d ",i);
	}
	for ( i = 0; i<n; i++)
	{
		fprintf(fp, "xy%d ",i);
	}
	fprintf(fp, "MCS_SUB XX = XXX\n\n.TRAN 0.1p 500p\n");
	
	// ----------------------IMMISSIONE OPERANDI ED INIZIALIZZAZIONE INGRESSI----------------------

	int x, y;
//	int n = max;
	int N = n;
	int X_binary[N];
	int Y_binary[N];
	int P_binary[N*2];
	for (i = 0; i < N; i++) {
		X_binary[i] = 0;
		Y_binary[i] = 0;
	}
	for (i = 0; i < N*2; i++) {
		P_binary[i] = 0;
	}

//	start: 
	printf ("Digitare gli operandi da moltiplicare:\n");
	scanf ("%d %d", &x, &y);
	int p = x*y;
/*	if (p > pow(2, 2*N)-1) {
		printf ("Numero di bit insufficienti alla rappresentazione del risultato e/o degli operandi.\n");
		goto start;
	}
*/	
	printf ("Risultato atteso: %d\n", p);	//risultato decimale atteso

	for (i = 2*N-1; i >= 0; i--) {		//risultato binario atteso
		P_binary[i] = p%2;
		p = p/2;
	}
	for (i = N-1; i >= 0; i--) {
		X_binary[i] = x%2;
		x = x/2;
		Y_binary[i] = y%2;
		y = y/2;
	}
	printf ("Operando X:\n");
	for (i = 0; i < N; i++) {
		printf ("%d ", X_binary[i]);
	}
	printf ("\nOperando Y:\n");
	for (i = 0; i < N; i++) {
		printf ("%d ", Y_binary[i]);
	}
	printf ("\nRisultato atteso:\n");
	for (i = 0; i < 2*N; i++) {
		printf ("%d", P_binary[i]);
	}
	printf ("\n");

	
	for (i = n-1, j = 0; i >= 0, j < N; i--, j++) {			//VALORI DI X
		fprintf(fp, "VinX%d X%d 0 %d\n", i, i, X_binary[j]);
	}
	for (i = n-1, j = 0; i >= 0, j < N; i--, j++) {			//VALORI DI Y
		fprintf(fp, "VinY%d Y%d 0 %d\n", i, i, Y_binary[j]);
	}

	fprintf(fp, "V_dd Vcc 0 1\n.end");	//ALIMENTAZIONE E TERMINAZIONE NETLIST
	
	fclose(fp);
	
	return 0;
}
	
