#!/bin/bash
i=0
j=0	
file="inputFile.txt" 
netName=$1
numBit=$2
if [ -e $file ] && [ -r $file ]
then
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
	while [ $i -lt $j ]
	do
		echo "bin/mcs.out $netName $numBit ${stringa[i]} ${stringa[i+1]}"
		bin/mcs.out $netName $numBit ${stringa[i]} ${stringa[i+1]} 
		(( i= i+3 ))		
		echo "ngspice $netName"
		cd netlist
		ngspice $netName
		cd ..
	done
else
	echo "$file doesen't exist"
	exit -1	
fi
exit 0
