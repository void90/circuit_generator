# circuit_generator

## Utilizzo
La cartella contenente i codici definitivi è "code_v2". All'interno della cartella sono presenti 4 sottocartelle, ognuna delle quali avente il nome del circuito associato.

Per compilare il singolo programma contenuto all'interno della cartella, dopo avervi acceduto, utilizzare il Makefile:

e.g.
```
    make
```
Per eliminare il prodotto delle compilazioni 
```
    make clean
```
Per eseguire il programma è necessario utilizzare lo script contenuto in ogni sottocartella chiamato "script.sh", il quale deve essere lanciato con nomeNetlist.net e num_bit. L'alimentazione ha come valore di default 1V e, nel caso in cui si volesse usare tale valore, non è necessario inserirla. E' possibile definire un nuovo valore della tensione di alimentazione del circuito attraverso il parametro opzionale **alim**, inseribile come parametro aggiuntivo da riga di comando.

```
Sintassi:
./script.sh nomeNetlist.net num_bit [alim]
e.g.

    ./script.sh rippleCarryAdder4.net 4 1.1
```

Gli operandi d'ingresso vengono automaticamente prelevati dallo script dal file **inputFile.txt**, all'interno del quale sono inseriti nel formato: 

OPERANDO_A OPERANDO_B RISULTATO 
    
Per ogni riga vengono predi i primi 2 operandi e viene generata una netlist, con la quale viene avviata una simulazione automatica. Nel caso di inbutFile composto da piu righe, ogni netlist prodotta viene sovrascritta con la generazione della successiva.

Al termine di tutte le simulazioni viene effettuato il confronto tra il valore calcolato dal simulatore con il valore atteso, prelevato dalla terza colonna del file **inputFile.txt**. L'esito di tale confronto, lanciato in automatico dallo script, produce delle stampe sul terminale di colore verde o rosso e genera un file **outputFile.txt** contenente:

Risultato atteso: XX	Risultato ottenuto: XX	    Matched 

oppure

Risultato atteso: XX	Risultato ottenuto: XX	    NOT Matched 

