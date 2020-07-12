#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char **argv)
{
//Inizializzazione variabili
	int i, j, n, out_idx = 0;
	char *param[3]={"out", "x", "y"};
	char *param2[4] = {"sum", " Cout", "a", "b"};
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
	n = atoi(argv[2]);
//Stampe netlist iniziali fisse
	fprintf(fp, "*MOLTIPLICATORE CARRY SAVE\n\n.option filetype=ascii\n.INCLUDE ../lib/ST65LIKE_cell_library_v2020_1.net\n.INCLUDE ../lib/16nm_HP.pm\n.PARAM Lmin=16n\n.PARAM Wmin=16n\n.TRAN 0.1p 500p\n.PARAM XXX=1\n");
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
	for(i=0; i<n*2; i++)
	{
		fprintf(fp, "z%d ", i);
	}
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
	fprintf(fp, "MCS_SUB XX = XXX\n");
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
