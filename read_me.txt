
English / Italian 

This is an exercise that was asked to me in an interview for a C++ position:

Prioritizing the object-oriented approach, and using the style and libraries that you consider most appropriate, implement a (working) program in C++ language that simulates a service that communicates with the outside world through a simple text protocol.

This protocol respects the following message structure:

- Start character: $
- Four characters for the command: XXXX
- Parameter separator character: #
- List of comma-separated parameters (optional): X,X,X, ...
- End character: &
- Two checksum characters: XX

The protocol characters are mandatory. The checksum is composed of the two final characters of the command: for example if the command is "INIT", the checksum will be "IT".

Here are some examples of possible messages:

- $INIT#&IT
- $RSTT#&TT
- $INVT#2,6,10,5,7&VT
- $STOR#12365&OR

The program will receive the message as input and will have to perform the following operations:

Verify that the message is correct, in case of error return:
i. If checksum is wrong: $RERR#CRC&RR
  ii. If message is malformed: $RERR#MSG&RR
  iii. If command is not recognized:$RERR#CMD: **** &RR (where **** will be the four characters that make up the unrecognized command)
  iv. If command does not respect the protocol: $RERR# PROTO: **** &RR (where **** will be the four characters that make up the sent command)

2. If the command requires it, execute the requested operation.

3. Return the original message replacing the first letter of the command with the letter 'R' and, if the sent command provides for it, report the response in the area reserved for the parameters.
The following is the list of accepted commands.

Command     Parameters*                     Operation to be performed                       Limits*

INIT        -                               Returns the command itself                      Only accepted as the first command or after a STOP command.

STOP        -                               Returns the command itself                      Only accepted if there was an INIT command before. No commands except INIT will be accepted after STOP.

ECHO        text (from 1 to 15 characters)  Returns the command itself                      Only accepted if an INIT command was sent previously.

SORT        integers                        Returns the command itself but with the         Only accepted if an INIT command was sent previously.
            (from 1 to 50 elements)         elements of the parameters sorted in 
                                            descending order.                                  
                     
        
SUMM        integer number                  Returns the command itself, but with each       Only accepted if an INIT command was sent previously.
                                            reception of the command, it returns, as a
                                            parameter, the sum of the parameter and the
                                            value of the result of the previous call.
                                            The INIT command resets the initial value.
                                            Example:
                                            1) SUMM#3&MM -> parameter: 3
                                            2) SUMM#1&MM -> parameter: 4
                                            3) SUMM#5&MM -> parameter: 9

VMAX        integers                        Returns the command itself but as a parameter   Only accepted if an INIT command was sent previously.
            (from 1 to 50 elements)         the maximum value of the input parameters

VAVG        integer number                  Returns the command itself but as a parameter   Only accepted if an INIT command was sent previously.
            (from 1 to 50 elements)         the arithmetic mean (one decimal digit) of the 
                                            input parameters

HHEX        integer number                  Returns the command itself but as a parameter   Only accepted if an INIT command was sent previously.
                                            the hexadecimal conversion of the input 
                                            parameter    

DDEC        two characters that represent   Returns the command itself but as a parameter   Only accepted if an INIT command was sent previously.
            a hexadecimal number (from 00   the decimal conversion of the input parameter
            to FF)


*Violation of parameter definitions generates a malformed message error (also in the case of the presence of a parameter when not required and vice versa).
**Violation of limits generates a protocol error.

___________________________________________________________________________________________________________________________________

Italian version

Questo è una esercitazione che mi è stata richiesta in un colloquio per una posizione di c++

Privilegiando l'approccio ad oggetti, ed utilizzando to stile e le librerie che più si ritengono opportune, implementare un programma (funzionante) in linguaggio C++ che simuli un servizio che comunica con l'esterno tramite un semplice protocollo testuale.

Tale protocollo rispetta la seguente struttura dei messaggi:

- Carattere di inizio: $
- Quattro caratteri per il comando: XXXX
- Carattere separatore di parametri: #
- Elenco parametri separati da virgola (opzionale): X,X,X, ...
- Carattere di fine: &
- Due caratteri di checksum: XX

I caratteri di protocollo sono obbligatori. Il checksum è composto da i due caratteri finali del comando: ad esempio se il comando è "INIT", il checksum sarà "IT".

Vediamo alcuni esempi di possibili messaggi:

- $INIT#&IT
- $RSTT#&TT
- $INVT#2,6,10,5,7&VT
- $STOR#12365&OR

Il programma riceverà in ingresso il messaggio e dovrà effettuare le seguenti operazioni:

1. Verificare che il messaggio sia corretto, in caso di errore ritornare:

    i. Se checksum errato: $RERR#CRC&RR
    ii. Se messaggio malformato: $RERR#MSG&RR
    iii. Se comando non riconosciuto:$RERR#CMD: **** &RR (dove al posto di **** ci saranno i quattro caratteri che compongono il comando non riconosciuto
    iv. Se comando non rispetta il protocollo: $RERR# PROTO: **** &RR (dove al posto di **** ci saranno i quattro caratteri che compongono il comando inviato)

2. Se il comando lo richiede eseguire l'operazione richiesta.
  
3. Ritornare il messaggio originale sostituendo la prima lettera del comando con la lettera 'R' e, se il comando inviato lo prevede, riportare la risposta nell'area destinata ai parametri.


Di seguito l'elenco dei comandi accettati.



Comando     Parametri*                      Operazione da svolgere                              Limiti**        

INIT        -                               Ritorna il comando stesso                           Accettato solo come primo comando o dopo un comando di STOP.

STOP        -                               Ritorna il comando stesso                           Accettato solo se prima c'è stato un comando di INIT. Dopo lo STOP nessun comando, eccetto INIT, verrà accettato.

ECHO        testo (da 1 a 15 caratteri)     Ritorna il comando stesso                           Accettato solo se è stato inviato un comando INIT in precedenza.

SORT        numeri interi                   Ritorna il comando stesso ma con gli elementi       Accettato solo se è stato inviato un comando INIT in precedenza.
            (da 1 a 50 elementi)            dei parametri ordinati in ordine decrescente
               
SUMM        numero intero                   Ritorna il comando stesso, ma ad ogni ricezione     Accettato solo se è stato inviato un comando INIT in precedenza.
                                            del comando, ritorna, come parametro, la somma 
                                            tra il parametro ed il valore del risultato 
                                            della chiamata precedente.
                                            Il comando INIT azzera il valore iniziale.
                                            Esempio:
                                            1) SUMM#3&MM -> parametro: 3
                                            2) SUMM#1&MM -> parametro: 4
                                            3) SUMM#5&MM -> parametro: 9

VMAX        numeri interi                   Ritorna il comando stesso ma come parametro il      Accettato solo se è stato inviato un comando INIT in precedenza.
            (da 1 a 20 elementi)            valore massimo dei parametri di input                 

VAVG        numeri interi                   Ritorna il comando stesso ma come parametro la      Accettato solo se è stato inviato un comando INIT in precedenza.
            (da 1 a 20 elementi)            media aritmetica (una cifra decimale) 
                                            dei parametri di input  

HHEX        numero intero                   Ritorna il comando stesso ma come parametro la      Accettato solo se è stato inviato un comando INIT in precedenza.
                                            conversione in esadecimale del parametro di input    

DDEC        due caratteri che               Ritorna il comando stesso ma come parametro la      Accettato solo se è stato inviato un comando INIT in precedenza.
            rappresentano un numero         conversione in decimale del parametro di input      
            esadecimale (da 00 a FF)

                                            
* La violazione delle definizioni dei parametri genera un errore di messaggio malformato (anche nel caso della presenza di un parametro quando non richiesto e viceversa).
* La violazione dei limiti genera un errore di protocollo.








