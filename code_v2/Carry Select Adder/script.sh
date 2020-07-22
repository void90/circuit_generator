#!/bin/bash
#variabili di loop
i=0
j=0	
#file contenente i valori da simulare e il valore atteso
file="inputFile.txt"
fileout="outputFile.txt" 
#Variabili di ingresso
netName=$1
numBit=$2
if [ $# -eq 3 ]
then
	alim=$3
fi
#cancellazione file outputFile.txt
if [ -e $fileout ]
then
	rm $fileout
	touch $fileout
	echo -e "inA\tinB\tout atteso\tout simul" >$fileout
fi
#controllo esistenza del file
if [ -e $file ] && [ -r $file ]
then
	#lettura del file
	for word in $(<$file)
	do
		stringa[i]=$word
		((i++))
		if [ i%3==0 ]
		then 
			((j++))
		fi
	done
	i=0
	#inizio del loop per simulazione
	while [ $i -lt $j ]
	do
		#programma di scrittura netlist (nomeNetlist numeroBit operando1 operando2)
		echo "bin/csa.out $netName $numBit ${stringa[i]} ${stringa[i+1]} $alim"
		bin/csa.out $netName $numBit ${stringa[i]} ${stringa[i+1]} $alim
		#avvio simulazione con ngspice		
		echo "ngspice $netName"
		cd netlist
		ngspice $netName
		cd ..
		bin/confronta.out ${stringa[i]} ${stringa[i+1]} ${stringa[i+2]} $alim
		(( i= i+3 ))
	done
else
	echo "$file doesen't exist"
	exit -1	
fi
exit 0
