#include <stdio.h>

int main()
{
	FILE *fp;
	char *param[4]={"sum", "cin", "ain", "bin"};
	//Variabili loop
	int i, j, z;
	//Variabili parametri
	int max, sum;
	printf("Inserire numero di bit:\n");
	scanf("%d", &max);
	fp=fopen("csa.net", "w");
	fprintf(fp, "CARRY SELECT ADDER\n.option filetype=ascii\n\n***LIBRERIE***\n.INCLUDE ST65LIKE_cell_library_v2020_1.net\n.INCLUDE 16nm_HP.pm\n\n***PARAMETRI GLOBALI***\n.PARAM Lmin=51.71336n\n.PARAM Wmin=36.05883n\n.PARAM XXX=1\n.TRAN 0.1p 820p\n\n***Setup logic\n***Indipendente Numero dei bit nel circuito finale (NO CAMBIARE)\n.subckt SETUP_SUB 0 Vdd p g inA inB XX=1\n\txp 0 Vdd p inA inB XOR2_SUB XX=1\n\txg 0 Vdd g inA inB AND2_SUB XX=1\n.ends\n\n***Cout Logic\n\n***Indipendente Numero dei bit nel circuito finale (NO CAMBIARE)\n.subckt COUT_SUB 0 Vdd cout g p cin XX=1\n\txand 0 Vdd node p cin AND2_SUB XX=1\n\txnor 0 Vdd Coutnot g node NOR2_SUB XX=1\n\txor 0 Vdd cout Coutnot NOT_SUB XX=1\n.ends\n\n***Adder 4 bit\n***Indipendente Numero dei bit nel circuito finale (NO CAMBIARE)\n.subckt FAcsa_SUB 0 Vdd sum0 sum1 sum2 sum3 cout3 cout-1 p0 p1 p2 p3 g0 g1 g2 g3 XX=1\n\txsum0 0 Vdd sum0 p0 cout-1 XOR2_SUB XX=1\n\txcout0 0 Vdd cout0 g0 p0 cout-1 COUT_SUB XX=1 \n\txsum1 0 Vdd sum1 p1 cout0 XOR2_SUB XX=1\n\txcout1 0 Vdd cout1 g1 p1 cout0 COUT_SUB XX=1\n\txsum2 0 Vdd sum2 p2 cout1 XOR2_SUB XX=1\n\txcout2 0 Vdd cout2 g2 p2 cout1 COUT_SUB XX=1\n\txsum3 0 Vdd sum3 p3 cout2 XOR2_SUB XX=1\n\txcout3 0 Vdd cout3 g3 p3 cout2 COUT_SUB XX=1\n.ends \n\n***CSA 4 bit\n***Indipendente Numero dei bit nel circuito finale (NO CAMBIARE)\n.subckt CSA4_SUB 0 Vdd sum0 sum1 sum2 sum3 cout cin0 cin1 cin ain0 ain1 ain2 ain3 bin0 bin1 bin2 bin3 XX=1\n\txsetup0 0 Vdd p0 g0 ain0 bin0 SETUP_SUB XX=1\n\txsetup1 0 Vdd p1 g1 ain1 bin1 SETUP_SUB XX=1\n\txsetup2 0 Vdd p2 g2 ain2 bin2 SETUP_SUB XX=1\n\txsetup3 0 Vdd p3 g3 ain3 bin3 SETUP_SUB XX=1\n\txadd0 0 Vdd sum00 sum01 sum02 sum03 cout03 cin0 p0 p1 p2 p3 g0 g1 g2 g3 FAcsa_SUB XX=1\n\txadd1 0 Vdd sum10 sum11 sum12 sum13 cout13 cin1 p0 p1 p2 p3 g0 g1 g2 g3 FAcsa_SUB XX=1\n\txmuxcout 0 Vdd cout cout03 cout13 cin mux21_SUB XX=1\n\txmuxs0 0 Vdd sum0 sum00 sum10 cin mux21_SUB XX=1\n\txumxs1 0 Vdd sum1 sum01 sum11 cin mux21_SUB XX=1\n\txmuxs2 0 Vdd sum2 sum02 sum12 cin mux21_SUB XX=1\n\txmuxs3 0 Vdd sum3 sum03 sum13 cin mux21_SUB XX=1\n.ends\n\n***Questo componente racchiude per numeroBit>4 più CSA4_SUB quindi cambia in base al numero dei bit\n.subckt CSA_SUB 0 Vdd ");
	for(i=0; i<4; i++)
	{
		for(j=0; j<max; j++)
		{
			fprintf(fp, "%s%d ", param[i], j);
			if(i==1 && j==1)
			{
				j=max;
				fprintf(fp, "cin ");
			}
		}
		if(i==0)
		{	fprintf(fp, "cout%d ", max-1);	}
		
	}
	fprintf(fp, "XX=1\n");
	sum=0;
	for(i=0; i<max/4; i++)
	{
		fprintf(fp, "\txcsa4_%d 0 Vdd ", i);
		for(j=0; j<4; j++)
		{
			fprintf(fp, "sum%d ", sum);
			sum++;
		}
		fprintf(fp, "cout%d cin0 cin1 ", sum-1);
		if(i==0)
		{	fprintf(fp, "cin ");	}
		else
		{	fprintf(fp, "cout%d ", sum-5);}
		for(j=2; j<4; j++)
		{
			for(z=sum-4; z<sum; z++ )
			{
				fprintf(fp, "%s%d ", param[j], z);
			}
		}
		fprintf(fp, "CSA4_SUB XX=1\n");
	}
	fprintf(fp, ".ends\n\nxcsa 0 Vcc ");
	for(i=0; i<4; i++)
	{
		for(j=0; j<max; j++)
		{
			fprintf(fp, "%c%d ", param[i][0], j);
		}
		if(i==0)
		{
			fprintf(fp, "CCout C0 C1 Ci ");
			i=1;
		}
	}
	fprintf(fp, "CSA_SUB XX=1\n\n***Tensioni Fisse\nV_C0 C0 0 PWL(0 0 820p 0);\nV_C1 C1 0 PWL(0 0 5p 0 6p 1 820p 1);\nV_dd Vcc 0 1\n.end");
	fclose(fp);
	return 0;
}
