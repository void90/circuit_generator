#!/bin/bash
#file="prova.txt"
#while IFS=: read -r f1 f2
#do
        # display fields using f1, f2,..,f7
#        printf 'Primo valore: %s\nSecondo valore: %s' "$f1" "$f2"
#done <"$file"

i=0	
file="prova.txt" 
for word in $(<$file)
do
	stringa[i]=$word
	((i++))
done

echo "./programma.out $@ ${stringa[0]} ${stringa[1]}"
./programma.out  $@ ${stringa[0]} ${stringa[1]}
exit 0
