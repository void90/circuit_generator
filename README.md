# circuit_generator

## Utilizzo
La cartella contenente i codici definitivi è "code_v2". All'interno della cartella sono presenti 4 sottocartelle, ognuna delle quali avente il nome del circuito associato.

Per compilare il singolo programma contenuto all'interno della cartella, dopo avervi acceduto, utilizzare il Makefile:
e.g.
```
    **>$ make**
```
Per eliminare il prodotto delle compilazioni 
```
    **>$ make clean**
```
Per eseguire il programma è necessario utilizzare lo script contenuto in ogni sottocartella chiamato "script.sh", il quale deve essere lanciato con nomeNetlist.net e num_bit. Possibile definire la tenzione di alimentazione del circuito attraverso il parametro opzionale **alim**
Sintassi:
**>$ ./script.sh nomeNetlist.net num_bit [alim]**
e.g.
```
    **>$ ./script.sh rippleCarryAdder4.net 4 1.1**
```

Gli operandi d'ingresso vengono automaticamente prelevati dallo script dal file **inputFile.txt**, all'interno del quale sono inseriti nel formato: 

*OPERANDO_A OPERANDO_B RISULTATO*
*OPERANDO_A OPERANDO_B RISULTATO*
*...*
    
Per ogni riga vengono predi i primi 2 operandi e viene generata una netlist, con la quale viene avviata una simulazione automatica. Nel caso di inbutFile composto da piu righe, ogni netlist prodotta viene sovrascritta con la generazione della successiva.
