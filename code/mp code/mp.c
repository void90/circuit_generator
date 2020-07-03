#include <stdio.h>

int main (int argc, char *argv)
{
	FILE *fp;
	fp=fopen("mp.net", "w");
	char *and[2]={"out", "xin"};
	char *adds[5]={"sum", "cout", "ain", "bin"};
	char *mulcomp[7]={"z", "out", "xin_", "yin_", "s", "c"}
	char *mul[3]={"z", "xin_", "yin_"};
	int i, j, max, max2;
	printf("Inserire numero di bit:\n");
	scanf("%d", &max);
	max2=max*2;
	fprintf(fp, "MOLTIPLICATORE PARALLELO\n\n.option filetype=ascii\n.INCLUDE ST65LIKE_cell_library_v2020_1.net\n.INCLUDE 16nm_HP.pm\n.PARAM Lmin=51.71336n\n.PARAM Wmin=36.05883n\n.PARAM XXX=1\n\n.subckt PART_SUB 0 Vdd ");
//.subckt schiera and
	for(i=0; i<2; i++)
	{
		for(j=0; j<max; j++)
		{
			fprintf(fp, "%s%d ", and[i], j);
		}
	}
	fprintf(fp, "y XX=1\n");
	for(i=0; i<max; i++)
	{
		fprintf(fp, "\txand%d 0 Vdd out%d xin%d y AND2_SUB XX=XXX\n", i, i, i);
	}
	fprintf(fp, ".ends\n\n");
//.subckt schiera full adder
	fprintf(fp, ".subckt RCA_SUB 0 Vdd ");	
	for(i=0; i<4; i++)
	{
		for(j=0; j<max; j++)
		{
			if(i==1){j=max-1;}
			fprintf(fp, "%s%d ", adds[i], j);
			if(i==1){fprintf(fp, "cout-1 ");}
		}
	}
	fprintf(fp, "XX=1\n");
	for(i=0; i<max; i++)
	{
		fprintf(fp, "\txfa%d\t0 Vdd sum%d cout%d cout%d ain%d bin%d FA_SUB XX=XXX\n", i, i, i, i-1, i, i);
	}
//.subckt del componente
	fprintf(fp, ".ends\n\n***numeroOut= uscita schiera di porte and\n***snumero znumero= uscita sommatori\n.subckt MP_SUB 0 Vdd ");
	for(i=0; i<3; i++)
	{
		for(j=0; j<max2; j++)
		{
			fprintf(fp, "%s%d ", mul[i], j);
			if(j==7){fprintf(fp, "c0 ");}
			max2=max;
		}
	}
	fprintf(fp, "XX=1\n");
//Corpo del componente MANCA QUESTA PARTEEEEEE
	for(i=0; i<max; i++)
	{
		fprintf(fp, "\txpart%d 0 Vdd", i, );
		
	}
	fprintf(fp, ".ends\n\n");
//Macrocomponente
	fprintf(fp, "xmp 0 Vcc ");
	for(i=0; i<3; i++)
	{
		for(j=0; j<max2; j++)
		{
			fprintf(fp, "X%s%d ", mul[i], j);
			if(j==7){fprintf(fp, "c0 ");}
			max2=max;
		}
	}
	fprintf(fp, "MP_SUB XX=XXX\n\n");
//Simulazione
	fprintf(fp, "\nV_dd Vcc 0 1\n.TRAN 0.1p 820p\n.end");
	fclose(fp);
	return 0;
}
