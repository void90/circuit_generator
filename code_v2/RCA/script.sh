#!/bin/bash
i=0	
file="fileInput.txt" 

if [ -e $file && -r $file ]
then
	for word in $(<$file)
	do
		stringa[i]=$word
		((i++))
	done
else
	echo "$file doesen't exist"
	exit -1	
fi

echo "./rca.out $1 $2 ${stringa[0]} ${stringa[1]}"
./rca.out $1 $2 ${stringa[0]} ${stringa[1]} 
echo "ngspice $1"
ngspice $1
exit 0
