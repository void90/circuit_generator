#include <stdio.h>

int main (int argc, char **argv)
{
	FILE *fp;
	fp=fopen("mp.net", "w");
	char *str[10]={"out", "xin", "sum", "ain", "bin", "z", "xin_", "yin_", "s", "c"};
	//variabili di loop
	int i, j, count, count2;
	//variabili di parametri
	int a, b, max, max_var, max_var2;
	printf("Inserire numero di bit:\n");
	scanf("%d", &max);
	fprintf(fp, "MOLTIPLICATORE PARALLELO\n\n.option filetype=ascii\n.INCLUDE ST65LIKE_cell_library_v2020_1.net\n.INCLUDE 16nm_HP.pm\n.PARAM Lmin=51.71336n\n.PARAM Wmin=36.05883n\n.PARAM XXX=1\n\n.subckt PART_SUB 0 Vdd ");
//.subckt PART_SUB (and)
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
//.subckt RCA_SUB (full adder)
	a=2;
	for(i=0; i<max; i++)
	{
		fprintf(fp, "%s%d ", str[a], i);
		if(i==max-1 && a!=4)
		{
			if(a==2){	fprintf(fp, "cout%d cout-1 ", max-1);	}
			i=-1; a++;
		}
	}
	fprintf(fp, "XX=1\n");
	for(i=0; i<max; i++)
	{
		fprintf(fp, "\txfa%d 0 Vdd sum%d cout%d cout%d ain%d bin%d FA_SUB XX=XXX\n", i, i, i, i-1, i, i);
	}
	fprintf(fp, ".ends\n\n***numeroOut=uscita porte and\n***snumero znumero=uscita sommatori\n.subckt MP_SUB 0 Vdd ");
//.subckt MP_SUB(insieme)
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
	a=8; b=9; j=1, count=1; count2=1; max_var=max; max_var2=max;
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
	fprintf(fp, "xmp 0 Vcc ");
	for(i=0; i<max*2; i++)
	{
		fprintf(fp, "zz%d ", i);
	}
	fprintf(fp, "zc0 ");
	for(i=0; i<max; i++)
	{
		fprintf(fp, "zx%d ", i);
	}
	for(i=0; i<max; i++)
	{
		fprintf(fp, "zy%d ", i);
	}
	fprintf(fp, "MP_SUB XX=XXX\n\n.TRAN 0.1p 500p\nV_dd Vcc 0 1\n.end");
	fclose(fp);
	return 0;
}
