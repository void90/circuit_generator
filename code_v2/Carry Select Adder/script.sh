#!/bin/bash
#variabili di loop
i=0
j=0	
numberInputMax=3
#file contenente i valori da simulare e il valore atteso
file="inputFile.txt"
fileout="outputFile.txt" 
#Variabili di ingresso
netName=$1
numBit=$2
alim=1
#definizione stampe help
display_help() {
	scriptName=$0
	echo "Usage: $scriptName netlistName.net bitNumber [Option]"
	echo "Produce una netlist a 4/8/16/32 bit e avvia la simulazione NGspice, prendendo come operandi d'ingresso i valori nel file inputFile.txt"
	echo -e "\n\t-h, --help\t Stampa questo file, l'help testuale"
	echo -e "\n\t-a, --ALIM\t Definisce il valore di alimentazione in base alla tecnologia. (Default 1V). Accetta valori decimali."
	echo -e "\te.g:\vUsage: $scriptName adderExample.net 4"
	echo -e "\t           $scriptName adderExample.net 4 -a 3.3"
	echo -e "I valori dei segnali d'ingresso la netlist sono riportati nelle prime 2 colonne del file inputFile.txt, la terza colonna contiene il risultato atteso dall'operazione"
	echo -e "Al termine delle simulazioni viene prodotto un file outputFile.txt contenente per ogni riga: \nOperandoA\tOperandoB\tOut_Atteso\tOut_simulato\tMatch|NotMatch\n"
	echo
	exit 1
}
#se non si passano parametri stmpare usage:

paramSimulation() {
	echo "****************************"
	echo "Netlist Name = $netName"
	echo "Num bits = $numBit"
	echo "Power Supply = $alim V"
	echo "Input File = $file"
	echo "Output File = $fileout"
	echo "****************************"
}

if [ $# -lt 2 ]
then
	echo "Few arguments. Please read the help File:"
	display_help	
elif [ $# -ge  2 ] && [ $# -le $numberInputMax ]
then
#controllo sul numero bit netlist
	if [ $numBit -ne 4 ] && [ $numBit -ne 8 ] && [ $numBit -ne 16 ] && [ $numBit -ne 32 ]
	then
		display_help
	fi
#controllo su Option_Param
	while [ $# -gt  0 ]
	do
		case $1 in
		-h | --help)
			display_help
			;;
		-a | --ALIM)
			alim=$2
			;;	
		esac
		shift
	done
else
	display_help
fi

paramSimulation

#cancellazione file outputFile.txt
if [ -e $fileout ]
then
	rm $fileout
	touch $fileout
	echo -e "inA\tinB\tout atteso\tout simul">$fileout
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
