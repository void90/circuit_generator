#!/bin/bash
i=0
j=0	
file="inputFile.txt" 
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
		echo "bin/mcs.out $1 $2 ${stringa[i]} ${stringa[i+1]}"
		bin/mcs.out $1 $2 ${stringa[i]} ${stringa[i+1]} 
		(( i= i+3 ))		
		echo "ngspice $1"
		cd netlist
		ngspice $1
		cd ..
	done
else
	echo "$file doesen't exist"
	exit -1	
fi
exit 0
