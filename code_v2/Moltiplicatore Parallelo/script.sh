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
	echo "generates a 4/8/16/32 bit netlist and starts running the NGspice simulation; input numbers from the inputFile.txt are taken"
	echo -e "\n\t-h, --help\t print this help"
	echo -e "\n\t-a, --ALIM\t to define the chosen power supply - (default 1V) - decimal values are accepted"
	echo -e "\te.g:\vUsage: $scriptName adderExample.net 4"
	echo -e "\t           $scriptName adderExample.net 4 -a 3.3"
	echo -e "input test numbers are shown in the first two columns of the inputFile.txt, the third one is the expected result\nthis file is automatically read\n maximum input value is (2^n)-1 (n is the number of the bit)\nsimulation will not start and a Error message is shown, if inputs value are out of the representation interval"
	echo  "NGspice prints are redirected to netlist/displayNG.txt"
	echo -e "at the end of simulation the outputFile.txt is generated; every line shows: \nOperandoA\tOperandoB\tOut_Atteso\tOut_simulato\tMatch|NotMatch\n"
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
	echo "Too few arguments. Please read the help File:"
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
	echo -e "PARALLEL MULTIPLIER $numBit bits\n">$fileout
	echo -e "inA\tinB\tout atteso\tout simul\t\t time">>$fileout
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
		echo "bin/mp.out $netName $numBit ${stringa[i]} ${stringa[i+1]} $alim"
		bin/mp.out $netName $numBit ${stringa[i]} ${stringa[i+1]} $alim
		#avvio simulazione con ngspice		
		control=$?
		if [ $control -eq 0 ]
		then
			echo "ngspice $netName"
			echo "running $netName"
			cd netlist
			start_time=$(date +%s)
			ngspice $netName 1>&displayNG.txt
			end_time=$(date +%s)
			cd ..
			bin/confronta.out ${stringa[i]} ${stringa[i+1]} ${stringa[i+2]} $alim
			diff=$(($end_time-$start_time))
			sec=$(($diff%60))
			min=$((($sec/60)%60))
			h=$(($sec/3600))
			echo -e "\t" $h "h" $min "m" $sec "s\n">>$fileout
		fi
		(( i= i+3 ))
	done
	lscpu>>$fileout
else
	echo "$file doesen't exist"
	exit -1	
fi
exit 0
