#include <stdio.h>

int main (int argc, char *argv)
{
	//Creazione file
	FILE *fp;
	fp=fopen("rca4.net", "w");
	//scrittura config, librerie, parametri globali
	fprintf(fp, "RIPPLE CARRY ADDER\n\n.option filetype=ascii\n\n.INCLUDE ST65LIKE_cell_library_v2020_1.net\n.INCLUDE 16nm_HP.pm\n.PARAM vthVARn=0.3423\n\n.PARAM vthVARp=-0.23122\n.PARAM ndepVARn=3.96e+018\n.PARAM ndepVARp=1.68e+018\n.PARAM toxpVAR=5.21e-010\n.PARAM Lmin=51.71336n\n.PARAM Wmin=36.05883n\n.PARAM XXX=1\n.PARAM tr=50p\n\n");
	
	return 0;
}
