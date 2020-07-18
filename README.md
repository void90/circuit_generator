# circuit_generator

## Utilizzo
La cartella contenente i codici definitivi è "code_v2". All'interno della cartella sono presenti 4 sottocartelle, ognuna delle quali avente il nome del circuito associato.

Per compilare il singolo programma contenuto all'interno della cartella, dopo avervi acceduto, utilizzare il Makefile:
e.g.

**>$ make**

Per eseguire il programma è necessario utilizzare lo script contenuto in ogni sottocartella chiamato "script.sh", il quale deve essere lanciato con nomeNetlist.net e num_bit.
e.g.

**>$ ./script.sh nomeNetlist.net num_bit**
    
Gli operandi d'ingresso vengono automaticamente prelevati dallo script dal file inputFile.txt, all'interno del quale sono inseriti nel formato: 
    OPERANDO_A OPERANDO_B RISULTATO
    
Per ogni riga viene generata una netlist e avviata una simulazione automatica. La netlist prodotta viene sovrascritta nel caso in cui siano presenti più operandi.
