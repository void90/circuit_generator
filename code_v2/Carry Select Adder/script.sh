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
alim=1
#definizione stampe help
display_help() {
	scriptName=$0
	echo "Usage: $scriptName netlistName.net bitNumber [Option]"
	echo "Produce una netlist ad N bit e lancia la simulazione NGspice prendendo come operandi d'ingresso i valori nel file inputFile.txt"
	echo -e "\n\t-h, --help\t Stampa questo l'help testuale"
	echo -e "\n\t-a, --ALIM\t Definisce valore di alimentazione in base alla tecnologia. (Default 1V). Accetta valori decimali."
	echo -e "\te.g:\vUsage: $scriptName adderExample.net 4"
	echo -e "\t           $scriptName adderExample.net 4 -a 3.3"
	echo -e "I valori dei segnali d'ingresso alla netlist sono riportati nelle prime 2 colonne del file inputFile.txt, la terza colonna contiene il risultato atteso dall'operazione"
	echo -e "Al termine delle simulazioni viene prodotto un file outputFile.txt contenente per ogni riga: \nOperandoA\tOperandoB\tOut_Atteso\tOut_simulato\tMatch|NotMatch\n"
	echo
	exit 1
}
#se non si passano parametri stmpare usage:

paramSimulation() {
	echo "Netlist Name = $netName"
	echo "Num bits = $numBit"
	echo "Power Supply = $alim"
	echo "Input File = $file"
	echo "Output File = $fileout"
}

if [ $# -lt 2 ]
then
	echo "Few arguments. Please read the help File:"
	display_help
elif [ $# -gt  2 ]
then
	while [ $# -gt  0 ]
	do
		case $1 in
		-h | --help)
			display_help
			#shift
			;;
		-a | --ALIM)
#si potrebbe aggiungere un controllo se $2 è nullo
			alim=$2
#			echo "--->$1"
#			echo "Simulazione con alimentazione V_dd = $alim"
			#shift 
			;;	
		*)
			echo "parametri non corretti."
			display_help
		esac
		shift
	done
fi

paramSimulation

#exit 1
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
