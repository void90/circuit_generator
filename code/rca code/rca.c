#include <stdio.h>

int main (int argc, char *argv)
{
	//Creazione file
	FILE *fp;
	char *param[5]={"sum", "cout", "ina", "inb"};
	int i, j, max;
	fp=fopen("rca.net", "w");
	//scrittura config, librerie, parametri globali
	printf("Inserire numero di bit:\n");
	scanf("%d", &max);
	char *bin[max];
	fprintf(fp, "RIPPLE CARRY ADDER\n\n.option filetype=ascii\n\n.INCLUDE ST65LIKE_cell_library_v2020_1.net\n.INCLUDE 16nm_HP.pm\n.PARAM Lmin=51.71336n\n.PARAM Wmin=36.05883n\n.PARAM XXX=1\n\n.subckt RCA_SUB 0 Vdd ");
	for(i=0; i<4; i++)
	{
		for(j=0; j<max; j++)
		{
			if(i==1){j=max-1;}
			fprintf(fp, "%s%d ", param[i], j);
			if(i==1){fprintf(fp, "cout-1 ");}
		}
	}
	fprintf(fp, " XX=1");
	for(i=0; i<max; i++)
	{
		fprintf(fp, "\n\txfa%d\t0 Vdd sum%d cout%d cout%d  ina%d inb%d FA_SUB XX=XXX", i, i, i, i-1, i,i);
	}
	fprintf(fp, "\n.ends\n");
	fprintf(fp, "\nxrca 0 Vcc ");
	for(i=0; i<4; i++)
	{
		for(j=0; j<max; j++)
		{
			if(i==1){j=max-1;}
			fprintf(fp, "%s%d ", param[i], j);
			if(i==1){fprintf(fp, "Xcout-1 ");}
		}
	}
	fprintf(fp, "RCA_SUB XX=XXX\n");
////SIMULAZIONE INIZIO CODICE DI PROVA
	

///FINE CODICE DI PROVA
	fprintf(fp, "\nV_dd Vcc 0 1\n.TRAN 0.1p 820p\n.end");
	fclose(fp);
	return 0;
}
