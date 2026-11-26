# Nozioni di base

{{messages}}


Benvenuti in XOScript
Il progetto XOScript mira a creare un linguaggio di scripting semplice e verificabile.
Semplice non significa necessariamente facile.
Un linguaggio di programmazione familiare può essere più facile da usare di XOScript.
Qui semplicità significa qualcosa di diverso:
essere in grado di formarsi un modello mentale completo del linguaggio e del suo comportamento.

XOScript è progettato per stare tutto nella vostra testa.
La sua grammatica e il numero dei suoi concetti sono volutamente ridotti.
Non esistono classi; gli oggetti possono essere estesi direttamente.
Gli oggetti vengono passati per riferimento, la copia è esplicita
e le funzioni hanno un unico punto di uscita.

Alcune di queste scelte si discostano notevolmente dai linguaggi più diffusi.
XOScript, per esempio, non ha un sistema di tipi e usa lo scoping dinamico.
I messaggi che non possono essere gestiti vengono ignorati invece di generare un'eccezione.
Queste scelte hanno delle conseguenze e non hanno lo scopo di eliminare gli errori.
Servono a mantenere piccolo e coerente il modello su cui si basa il linguaggio.

XOScript può anche essere localizzato, il che permette di esprimere le regole
di business in una lingua naturale e, potenzialmente, di condividerle con interlocutori non tecnici.

Verificabilità significa applicare la stessa filosofia all'implementazione.
Il runtime è scritto in C, con un piccolo lexer, un parser e un tree walker scritti a mano.
La libreria standard e il runtime rispecchiano in gran parte la struttura del linguaggio,
il che rende relativamente diretto il rapporto tra il codice XOScript e la sua implementazione.

Anche i test sono strettamente legati alla documentazione.
Ogni metodo dovrebbe avere un test associato che può essere incluso nel manuale,
così da mantenere la documentazione allineata con l'implementazione.

XOScript non intende competere con i linguaggi più diffusi per
funzionalità o familiarità. Esplora un obiettivo diverso:
un ambiente di programmazione che uno sviluppatore possa comprendere nella sua interezza.

La speranza è che un linguaggio piccolo e una piccola
implementazione rendano possibile comprendere il software
dal byte all'oggetto, dalla sintassi al runtime, e scrivere codice con
sicurezza, perché si capisce sia ciò che accade nello
script sia ciò che accade dietro le quinte.

L'architettura di un'installazione server di xoscript
è semplice, ma flessibile.

{{architecture.png}}

Per usare xoscript come linguaggio lato server, dovete installare il
plugin server in una cartella chiamata /mods/server. 

Questo perché preferiamo
separare il linguaggio di base dalle funzionalità specifiche del server,
a differenza per esempio di PHP o Python. Altrimenti dovremmo distribuire a tutti
l'intero armamentario senza alcuno scopo, il che sarebbe semplicemente sciocco.
Se volete, potete installare anche altri moduli. Il sistema è molto
flessibile.

Inoltre alcune funzioni sono implementate meglio nel linguaggio di scripting
stesso, come i template e la gestione delle sessioni; per questo
distribuiamo anche le librerie template.xo e webtools.xo per vostra comodità.
Il motivo di tutto ciò è che non sappiamo come vorrete
usare xoscript. Potete usarlo come linguaggio di scripting lato server,
ma anche per interfacce grafiche, dispositivi embedded o semplice elaborazione batch.
Anche se lo usate come linguaggio di scripting lato server (che è
attualmente uno dei casi d'uso principali), potreste comunque voler
usare un altro motore di template o un altro gestore delle sessioni.
Chi siamo noi per decidere che dovete usare i nostri?

Uno dei vantaggi di usare il nostro motore di template, comunque, è che
non dovete imparare una sintassi aggiuntiva per creare i template.
Il motore di template predefinito fornito con xoscript applica una separazione
al 100% tra presentazione e logica. Invece di una sintassi speciale
per i template, usa semplicemente un sistema di marcatori di slot molto flessibile.
Per maggiori informazioni, consultate il capitolo Server.

Notate che, se non volete usare il motore di template predefinito o
i webtools predefiniti, va da sé che dovete fornire
i vostri.

Se eseguite il vostro server web in un chroot, in una jail o in un altro tipo di sandbox,
dovete installare anche le dipendenze di xo in quell'ambiente; potete
vedere quali librerie vi servono usando ldd (consultate la pagina man di Linux o BSD).
Se volete usare comandi di shell nei vostri script xo, copiate anche una shell
(come bash o ksh) in questo ambiente.

Ci teniamo anche a sottolineare che prendiamo molto sul serio la retrocompatibilità.
Esiste persino una funzionalità speciale di retrocompatibilità chiamata
'version'. In generale, il nostro obiettivo è che il vostro codice funzioni per sempre. Quindi
non dovrete mai aggiornare il vostro codice per restare compatibili con le nuove versioni
di xoscript. Il nostro obiettivo è: scrivi una volta, esegui per sempre.

Il resto di questo manuale è dedicato a spiegare in dettaglio il linguaggio
di programmazione xoscript. Lo scripting lato server è trattato nel capitolo
chiamato Server. Se siete sviluppatori esperti, potreste voler
saltare alcuni capitoli, perché alcuni sono un po' troppo dettagliati o
molto simili alle pratiche di programmazione generali. Quindi chi di voi
ha già esperienza con diversi altri linguaggi di programmazione
farebbe meglio a usare questo manuale come guida di riferimento.

## Installazione su Linux

Scaricate apache2 e mariadb:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Scaricate xoscript.
Sostituite X con il numero di versione corretto!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Copiate i file nella webroot e in /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Modificate la configurazione di apache2:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Sostituite Virtualhost con:

```
<VirtualHost *:80>
    <Directory /var/www/html>
        Options +ExecCGI
        AllowOverride All
        AddHandler cgi-script .xo
        Require all granted
    </Directory>
    DocumentRoot /var/www/html
</VirtualHost>
```

Create una pagina di prova:

```
sudo nano /var/www/html/test.xo
```

e scrivete un piccolo programma di prova:

```
#!/bin/xo
Server inizializzare.
Programma uso: ['webtools.xo'].
>> web := Documento-Web nuovo.
web emettere: ['Hello World'].
```

Consentite ad apache2 di eseguire il vostro programma tramite CGI:

```
sudo chmod uog+x /var/www/html/test.xo
```

Riavviate apache2:

```
sudo systemctl restart apache2
```

Aprite la pagina di prova nel browser:

```
http://localhost/test.xo
```

Dovreste vedere:

```
Hello World
```


## Installazione su OpenBSD

Modificate /etc/httpd.conf e aggiungete:


```
server "mydomain.com" {
    listen on * port 80
    root "/htdocs/mydomain/"

    location "*.xo" {
        fastcgi
        fastcgi socket "/run/slowcgi.sock"   # inside chroot
    }
}
```

Se volete usare SSL:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Per proteggere lo scambio delle chiavi dagli attacchi quantistici,
selezionate il cifrario mlkem:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Aggiungete il binario xo e i mods, oltre a tutte le dipendenze, nel
chroot (individuatele con ldd).

## Eseguire gli esempi


Per eseguire uno dei programmi di esempio inclusi nel pacchetto:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Per esempio, per eseguire l'esempio FizzBuzz su Linux:

```
./example.sh fizzbuzz Linux
```

Per eseguire lo stesso esempio su OpenBSD:

```
./example.sh fizzbuzz OBSD
```

Per eseguire l'esempio con una compilazione pulita:

```
./example.sh fizzbuzz OBSD clean
```

## Test unitari

Per eseguire i test unitari:

```
./runtests.sh
```

Per eseguire i test unitari senza compilare (solo test):

```
./runtests.sh nobuild
```

## Compilazione

Per compilare dai sorgenti su Linux:

```
make clean
ISO="en" make
```

Su OpenBSD:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

Per compilare il plugin server su Linux:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

Per compilare il plugin server su OpenBSD:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Hello world

Dopo averlo trasferito sul vostro computer, potete estrarre il file
e avviare xo con il seguente comando:

```
xo
```

Per eseguire uno XOScript, salvate il programma in un file aggiungendo il suffisso
-xo (facoltativo). Inoltre, inserite il nome del file del vostro programma
dopo il comando XOScript:

```
xo myprogram.xo
```

Quando eseguite un comando XOScript usando il file del vostro programma come
parametro, xo leggerà ed eseguirà il file del programma.

{{note}}
Potete anche avviare il vostro programma trascinandolo sull'icona di xo.
{{/note}}

{{warning}}
Su alcuni sistemi dovete prima concedere a xo i permessi per caricare
librerie dinamiche.
{{/warning}}

La tradizione vuole che il primo programma in un nuovo linguaggio
di programmazione sia una sorta di saluto al mondo. In XOScript, un
programma **Hello world** di questo tipo ha questo aspetto:

@test598

Quando questo testo viene salvato in un file, per esempio hello.xo, può essere eseguito
come segue: .

xo hello.xo

Hello world


Potete vedere l'output del programma nella finestra nera mostrata sopra.
In tutto questo manuale verrà usata la stessa rappresentazione per mostrare
l'output.

{{note}}
Uscita si scrive con la U maiuscola.
In generale gli oggetti iniziano con una lettera maiuscola,
a meno che non fungano da istanza (non hanno metodi
propri, solo dati). Questo rispecchia le convenzioni classe/istanza
di altri linguaggi di programmazione.
{{/note}}


## Sintassi 

XOScript è un linguaggio di programmazione *puramente* *orientato agli oggetti*. Ciò significa
che xoscript considera ogni cosa un oggetto, per cui non esistono
altri *tipi di dati*. Un programma scritto in XOScript si basa essenzialmente
su tre azioni di base: *assegnare*, *inviare messaggi*
e *rispondere*. Lo scambio di messaggi tra oggetti è la parte fondamentale di
un programma XOScript. Le tre singole azioni sono illustrate
di seguito:


Azione             | Esempio
------------------ | --------
assegnazione       |  \>\> x := 1. 
messaggi unari     | x pari?.
messaggio binario  | 1 + 2.
messaggio a parola chiave | x da: 0 lunghezza: 10.
risposta           | <- answer.  


Questo capitolo vi darà un'impressione generale del linguaggio XOScript
e ne descrive i principi di base. XOScript è un linguaggio piccolo,
fondato su tre azioni (vedi illustrazione) che si traducono in
circa sei regole grammaticali. Non serve altro per padroneggiare il
linguaggio.

Non preoccupatevi se le cose non vi sono subito chiare: tutti i mattoni
verranno esaminati nel prossimo capitolo (3) e le regole di base verranno
ripetute. Il capitolo attuale serve però soprattutto come introduzione
generale al linguaggio. I principi di base verranno spiegati brevemente
e illustrati con diversi esempi pertinenti. I dettagli mancanti
verranno descritti in un secondo momento.

In XOScript i commenti sono preceduti dal simbolo \#. Quindi la riga seguente
verrà ignorata:

```
# questo è solo un commento
```

## Variabili

Per assegnare
una variabile si usa il simbolo di dichiarazione delle variabili: >>. Il nome di una
variabile può contenere tutti i segni tranne: <-, :=, spazi,
punti, virgole, due punti, virgolette [' '] e parentesi ().
Inoltre, una variabile non può estendersi su più righe. Notate
che una variabile non può iniziare con un numero o con un segno meno.

Questi sono esempi di variabili valide:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dollaro'].
>> +plus := Vero.
>> parola-segreta-utente := ['Psst!'].
```

Sono invece variabili non valide, per esempio:


```
>> -123 := ['numero negativo'].
>> password of utente := ['Riservato'].
>> password.of:utente := ['Riservato'].
>> ,x := 10.
```

{{note}}
Non dovete fare l'escape di alcun carattere
(comprese virgolette, doppie virgolette, delimitatori
di stringa) in
un letterale stringa, purché ciò non
crei ambiguità per il lexer.
{{/note}}

Dopo che una variabile è stata dichiarata, può essere usata liberamente. Ciò significa
che il simbolo di dichiarazione è necessario solo la prima volta
che usate la variabile (la dichiarazione).

Più precisamente, non potete iniziare ad assegnare a caso un valore alla
vostra variabile *(x := 2)*, perché dovete prima dichiarare la variabile *(\>\>
x := 2)*. Tuttavia, una volta dichiarata, potete modificarne il valore
senza usare il simbolo di dichiarazione*(\>\> x := 2. x := 3.)*.

Notate che è obbligatorio assegnare un valore a una variabile al momento
della dichiarazione. A differenza di altri linguaggi di programmazione, non è consentito
dichiarare una variabile senza valore. È indispensabile legare esplicitamente
ogni variabile a un valore iniziale. Ciononostante, potete tranquillamente inizializzare
la variabile con l'oggetto **Nil**. In questo caso la variabile può essere
considerata vuota *(\>\> x := Nil.)*. In breve, dichiarare una
variabile senza valore iniziale non è consentito. Quindi,

```
>> x.
```

non è valido e produrrà un messaggio di errore.

{{note}}
xoscript usa lo scoping dinamico delle variabili; per
i dettagli consultate il capitolo Funzioni.
{{/note}}


## Letterali

XOScript considera ogni cosa un oggetto, cioè tutti i numeri, le stringhe
e i frammenti di codice. I numeri, come 1, 2, 100, -999 e 1,234, sono
oggetti Numero. Tutti i testi tra virgolette singole sono oggetti
Testo. Tutti i frammenti di codice racchiusi tra parentesi graffe {...} sono
oggetti Compito.

Letterale       | Oggetto radice | Esempio
--------------- | -------------- | ----------
numeri          | Numero         | 1,2,3... 
stringhe        | Testo          | \['hello'\]
funzione        | Compito        | { 1 + 2. }.
                
     
Oggetti come numeri e stringhe hanno sempre origine in un oggetto
radice. Per esempio, tutti i numeri derivano dall'oggetto **Numero**. Tutte
le stringhe derivano da **Testo** e tutti i frammenti di codice da **Compito**. A
loro volta, tutti questi oggetti discendono da **Oggetto**, che è di fatto
l'oggetto radice di tutti gli oggetti.


## Messaggi

Programmare in XOScript significa fondamentalmente
inviare messaggi agli oggetti. La notazione generale per inviare un messaggio a
un oggetto è la seguente:

```
<object> <message>
```

Per sapere se il numero **2**, per esempio, è un numero pari, si invia
il messaggio **pari?** all'oggetto **2**:

```
2 pari?
```

La risposta sarà **Vero** (anche questo un oggetto). I messaggi sconosciuti vengono
di solito ignorati dagli oggetti, quindi non si verifica alcun errore. Alcuni oggetti (per esempio
numeri o stringhe) rispondono a un messaggio sconosciuto in modo predefinito
(se ne parlerà più avanti).

Un oggetto può ricevere tre tipi di messaggi. 

Tipo            | Numero di argomenti
--------------- | -------------------
Unario          | 0      
Binario         | 1     
A parola chiave | 1+    


In primo luogo ci sono i **messaggi
unari**, vedi l'esempio sopra, che non hanno argomenti. In secondo luogo
ci sono i **messaggi a parola chiave**, che hanno uno o più argomenti,
per esempio:

```
>> x := Numero tra: 1 e: 10.
```

In questo caso il messaggio **tra:e:** viene inviato a **Numero**, che
è l'oggetto radice di tutti i numeri. Il risultato sarà un numero casuale
tra 1 e 10. Infine ci sono i **messaggi binari**, che hanno
un solo carattere e un solo argomento:

```
2 + 3
```

Sembra una somma matematica, ma in realtà è solo un altro messaggio. Il
messaggio **+** viene inviato a **2**, con argomento **3**, e restituisce
la risposta **5**. I messaggi binari possono essere scritti senza due punti.

I messaggi binari possono essere concatenati:

```
>> x := 3 + 2 - 1.
```

In questo frammento **+ 2** viene inviato prima all'oggetto **Numero** **3**, il che
produce l'oggetto Numero **5**, dopodiché **-1** viene inviato a questo
numero. I lettori attenti noteranno giustamente la discrepanza che
questo protocollo mostra rispetto alla precedenza convenzionale degli
operatori matematici. XOScript ignora la precedenza matematica a favore della
coerenza del suo sistema di messaggi. Di conseguenza, la somma:

```
2 + 3 * 5 = 25
```

e non 17.

È una scelta voluta. Le parentesi possono essere usate per modificare l'ordine:

```
2 + (3 * 5) = 17
```

La maggior parte degli oggetti restituisce sé stessa come risultato in risposta a un
messaggio. Questo è utile perché favorisce un ulteriore dialogo con questo
oggetto, inviandogli un messaggio successivo:

```
Uscita scrivi:
[' ciao '] trim maiuscolo.
```

```
CIAO
```

Qui vengono inviati due messaggi all'oggetto **Testo**: **trim**, seguito
da **maiuscolo**.

Nel frammento seguente l'uso di una virgola è necessario per indicare
che sta arrivando un nuovo messaggio. Altrimenti XOScript si confonderebbe.

```
Uscita scrivi: ['Hello!'], stop.
```

Prima viene inviato il messaggio **scrivi:** al simbolo della matita, seguito da
**stop**. Senza la virgola, XOScript penserebbe che vogliate inviare
**stop** alla **stringa** **Hello!**, un esercizio inutile.

L'ordine di elaborazione dei messaggi è il seguente: da sinistra a destra;
si inizia con i messaggi tra parentesi, seguiti dai messaggi unari. Poi
i messaggi binari e infine i messaggi a parola chiave. Vedete l'esempio
seguente:

```
Uscita scrivi: 0.5 arrotondato + (2 - 1), stop.
```

XOScript legge sempre da sinistra a destra: prima il messaggio **scrivi:**
viene inviato a Uscita ed è seguito dal messaggio **stop**. All'interno
dell'argomento stesso, XOScript legge da sinistra a destra, quindi prima **0.5 arrotondato**
e poi **+**.

{{note}}
Il messaggio stop aggiunge un carattere di nuova riga alla stringa.
Il nome di questo messaggio è ispirato ai sistemi telegrafici.
Nei messaggi telegrafici
si usava spesso la parola STOP per segnare la fine di una frase
(poiché la punteggiatura era inaffidabile o costosa).
{{/note}}

Inoltre **arrotondato** ha la precedenza su **+**, perché è un
**messaggio unario**. Date le parentesi, **2 - 1** viene calcolato
per primo, dopodiché **1** viene aggiunto al risultato di **0.5 arrotondato** (1).

L'intero processo darà come risultato **2**, che è anche la risposta
scritta. Dopo la virgola segue il messaggio stop, che sposta il cursore
su una nuova riga. Naturalmente il modo migliore per comprendere appieno l'ordine
di esecuzione dei programmi XOScript è la pratica.

Vale la pena notare che in XOScript, a differenza di molti altri linguaggi
di programmazione, gli spazi sono una parte fondamentale della sintassi. In
particolare con i messaggi binari, gli spazi possono creare una certa
confusione. Usate sempre uno spazio dopo un messaggio binario. Non potete
attaccare direttamente un numero al messaggio, per esempio: 

```
3 + 2
```

è diverso da 

```
3 +2
```

Il primo esempio (**3 + 2**) invia il
messaggio **+** al numero **3**, con argomento il numero **2**. Il
risultato, in questo caso, sarà **5**. Nel secondo esempio (**3 +2**)
il messaggio unario **+2** viene inviato al numero **3**. A seconda del
contesto, ciò può produrre un risultato molto diverso.

## Metodi inesistenti

Inviare un messaggio a un oggetto invoca la funzione che è stata
associata a questo oggetto con quel nome di messaggio. Se inviate un messaggio
che non viene compreso, l'oggetto ricevente ignorerà il vostro messaggio
e restituirà invece un riferimento a sé stesso per ulteriori comunicazioni.
Questo si chiama passaggio di messaggi tollerante.

Esempio:

```
Uscita scrivi: Oggetto blah, stop.
```

Questo non produrrà un errore. Stamperà semplicemente il testo **Oggetto**.


## Flusso di controllo

In XOScript non servono regole grammaticali separate per i *cicli* e
gli *if*. Un'istruzione if è semplicemente un messaggio **vero:** o **falso:**
inviato a un oggetto **Vero** o a un oggetto **Falso**:

```
2 pari? vero: {
	Uscita scrivi: ['Due è un numero pari'], stop.
}.
```
Nell'esempio precedente il messaggio **vero:** viene inviato a **Vero** (la
risposta alla domanda: 2 è un numero pari?). Come argomento viene inviato un ulteriore
frammento di codice: un oggetto **Compito**. Questa funzione scrive sullo
schermo che 2 è, in effetti, un numero pari.

Non servono nemmeno regole di scrittura separate per un *ciclo*. Per
eseguire un frammento di codice tre volte, inviate semplicemente **\*** con argomento
**3** a quel **Compito**:

@test5

In questo frammento di codice **i** è l'indice. Quindi la prima volta che il Compito
viene eseguito, **i** vale 0, la volta successiva **i** = 1 e
così via.

Consideriamo un altro esempio. Quando si deve stampare una tabella di conversione
da *kJ* (kilojoule) a *kcal* (kilocalorie) a passi di 100,
la notazione corretta è la seguente:

@test599

Qui il numero della riga corrente viene trasmesso al parametro
**:line**. All'inizio di una funzione vengono definiti i parametri
della funzione. I parametri non usati restano vuoti (**Nil**). I parametri vengono
sempre posti all'inizio della funzione, subito dopo la parentesi graffa
iniziale, e sono preceduti da due punti.

Il messaggio **mentre:** è una combinazione di un *ciclo* e di una *condizione*.
Due funzioni possono essere collegate con il messaggio **mentre:**. La funzione ricevente
continuerà a essere eseguita finché la funzione dopo i due punti non darà un risultato
negativo. Esempio:

@test600

Nel frammento di codice illustrato sopra, **1** viene aggiunto a **x** finché
**x** è minore di **5**. Quando ciò non è più vero, la seconda
funzione risponderà con **Falso** e di conseguenza l'esecuzione della
prima funzione terminerà. Notate che **x** è stata definita fuori dalla
funzione ed è una variabile globale. Per saperne di più sulle regole di scoping,
consultate il capitolo sulle Funzioni.

## Interpolazione di stringhe

L'elenco *kJ/kcal* potrebbe essere reso più
presentabile. Sarebbe preferibile un elenco come questo:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Se convertite l'output desiderato in un template, la sua notazione
potrebbe essere:

```
number1 kJ ➞ number2 kcal
```

Ciò significa che **number1** sta per il valore in kJ e **number2** per il
valore in kcal. Ecco come funziona l'interpolazione di stringhe in XOScript. In
XOScript non servono regole grammaticali separate per questo. Inviate semplicemente
al testo la parola da sostituire, con il testo sostitutivo
come argomento:

```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

Il risultato:

```
100 kj ➞ 23.9 kcal
```

Questa regola di sostituzione vale per ogni messaggio non definito che viene ricevuto
da un oggetto **testo**. Ogni messaggio che non viene riconosciuto dall'oggetto
**testo** verrà interpretato come segue: *sostituisci il testo del messaggio
con il testo contenuto nell'argomento del messaggio.* Potete adattare il
programma come segue:


@test601


Per evitare confusione su quali messaggi possano o non possano essere usati come
sostituti, è meglio introdurre un marcatore di template come &lt; &gt;
per i segmenti di testo del template che
devono essere sostituiti.

## Valori di ritorno

Per rispondere a un messaggio si usa la freccia
di ritorno (*<-*). L'esempio seguente illustra come creare un compito
che calcola una percentuale:

@test602

Dopo che il compito è stato definito e assegnato alla variabile **percentage**,
viene inviato il messaggio **applica:e:** con argomenti **100** e **7**.

Questo eseguirà il compito applicato a **100** e **7**, cioè il 7% di 100.
Con la freccia di ritorno, la risposta viene restituita dal compito
al programma principale.

## Estendere

Anche se questo codice è valido, ha uno svantaggio:
bisogna ricordare l'ordine degli argomenti. Allora perché non
scriverlo così: *7 percent of: 100 *? Sembrerebbe molto più
*naturale*. Per renderlo possibile, dobbiamo adattare l'oggetto genitore di
**7**, cioè l'oggetto **Numero**, in modo che comprenda il
messaggio **percent of:**. Ciò si ottiene inviando **on:fare:** all'oggetto
Numero, in questo modo:

@test603

Poiché in questo caso la percentuale è il numero stesso, facciamo riferimento a io,
la parola chiave *io*. In breve, il simbolo io significa: *invia questo
messaggio a me stesso*.

# Oggetti

{{messages}}

Oltre ad adattare ed estendere gli oggetti esistenti, potete anche creare
voi stessi nuovi oggetti semplicemente inviando il messaggio **nuovo**. Supponete
di voler creare un oggetto fattura che imponga una sequenza di
numerazione: in tal caso vi servirà prima di tutto un oggetto fattura.

Sapendo che ogni oggetto deriva da un altro oggetto, che a sua volta
discende in ultima analisi dall'oggetto radice di tutti gli oggetti, chiamato Oggetto,
bisogna scegliere su quale di questi altri oggetti si fonderà
il vostro nuovo oggetto. Il nuovo oggetto eredita tutte le proprietà
dell'oggetto su cui è fondato, cioè quello a cui è stato inviato
inizialmente il messaggio **nuovo**.

In questo esempio è preferibile un oggetto piuttosto neutro, senza troppe
proprietà ereditate. La scelta è facile, perché in questo
caso il nuovo oggetto può basarsi sull'oggetto radice stesso, cioè
**Oggetto**. La notazione del sistema di fatturazione previsto sarà quindi
la seguente:

@test604

Il numero di fattura corrente viene memorizzato nell'oggetto; per questo motivo
davanti a esso è posta la parola chiave **mio**. Questa si chiama *proprietà*;
seguiranno maggiori dettagli.

Alcune aziende preferiscono includere l'anno nei numeri di
fattura. In questo caso potete creare un nuovo oggetto fattura fondato su un
oggetto fattura precedente, ma che offre al suo utente la possibilità di
indicare un anno specifico:

@test605

Non è necessario scrivere di nuovo l'implementazione del messaggio **numero**,
perché viene ereditata dall'**oggetto fattura** scritto in
precedenza; di conseguenza il vecchio codice può essere riutilizzato. XOScript non ha concetti
come le classi e altri concetti correlati. Ciò significa che gli oggetti possono
ereditare soltanto da altri oggetti; questo è noto anche come *ereditarietà
prototipale*.

Torniamo ora alle proprietà. Alle proprietà di un oggetto si può accedere solo
*dall'interno della gerarchia dell'oggetto*, quindi queste proprietà
non possono essere viste da altri oggetti.

A differenza di altri linguaggi di programmazione, tutte le proprietà degli oggetti sono
visibili esclusivamente all'oggetto che ha creato la proprietà e agli
oggetti derivati. 

Una tecnica molto usata consiste nell'impiegare un oggetto come una sorta di *modello*,
come avviene per esempio con le fatture viste prima.
Un altro buon esempio è il **Point**. Supponiamo che creiate un
programma che esegue calcoli usando punti su una mappa. Potete
sviluppare l'oggetto **Point** contenente le proprietà di una
coordinata x e di una coordinata y, che verranno rese disponibili al
mondo esterno tramite messaggi:

@test606

Il messaggio **=** confronta i due punti usando il messaggio **e:**. Il
primo confronto dà come risultato un **Vero** o un **Falso**. Questi sono oggetti
booleani. Quando inviate il messaggio **e:** a un oggetto Vero, e
anche l'oggetto argomento dopo i due punti è **Vero**, riceverete
di nuovo come risposta **Vero**. Quando uno dei due è **Falso**, riceverete
la risposta **Falso**. Notate che un punto non può leggere le coordinate
dell'altro. È necessario inviare un messaggio all'altro punto per chiedere
questi dati: **x-coordinate** e **y-coordinate**. Dopotutto, come è già
stato spiegato, le proprietà sono accessibili solo dall'interno
della famiglia dell'oggetto stessa. 

Notate che qui il messaggio **=** viene usato per eseguire il confronto
tra punti. Si sarebbe potuto usare anche un messaggio diverso, come
**is:** o **equal:**, ma in questo caso riutilizzare il carattere **=** sembrava
appropriato.

## Ereditarietà

Potete riutilizzare codice scritto in precedenza per creare una gerarchia
di oggetti. Per esempio:

```
>> Animale := Oggetto nuovo.
>> Cane := Animale nuovo.
>> Barboncino := Cane nuovo.
```

In questo caso **Dog** eredita tutto il comportamento e le proprietà
di **Animal** e, a sua volta, l'oggetto **Animal** eredita tutto il comportamento di
**Oggetto**, l'oggetto radice di tutti gli oggetti.


## Ridefinizione


Nell'esempio seguente viene creato un nuovo tipo di lista:
**Combination**, in cui si garantisce che ogni elemento sia unico. Le
funzioni della lista vengono riutilizzate tramite l'ereditarietà:

@test607

Osservate come il secondo **red** venga escluso dalla lista.

A volte può essere necessario ridefinire un comportamento di un oggetto.
Per esempio, quando si sommano numeri e bisogna tenere conto delle unità
di misura. Nell'esempio seguente viene creato l'oggetto **Size**.
Questo oggetto restituisce un numero che, durante la somma, tiene
conto dell'unità del numero da sommare. L'oggetto **Numero**
verifica se si tratta di *pollici* o di *piedi*. Il codice
potrebbe essere simile al seguente:

@test608

## Ricorsione

Nell'esempio precedente il **segno** più viene ridefinito. Notate
che alla fine la somma finale deve comunque essere eseguita, cosa che in effetti
avviene nella riga seguente:

```
>> responso := io + (numero x fattore).
```

Ora, come fa XOScript a capire che questo **segno** più si riferisce
alla logica originale della somma?** Un'altra interpretazione, per esempio,
potrebbe essere che XOScript invii ripetutamente lo stesso messaggio allo stesso
oggetto, il che a sua volta porterebbe a un **ciclo infinito**. Chiaramente
non è questa l'intenzione. Non appena inviate a un oggetto un messaggio
che eseguirebbe esattamente lo stesso codice, XOScript capisce
che in questo caso si intende il messaggio sottostante, quello ridefinito. Il vostro
programma è quindi protetto automaticamente da questa forma di cicli
infiniti. Se invece il vostro scopo è proprio eseguire la stessa funzione dalla
funzione corrente, sarà necessario inviare prima il messaggio
**ricorsivo**. In questo caso il risultato sarà un ciclo
infinito. Esistono però applicazioni utili dei compiti ricorsivi:
supponete per esempio di voler calcolare il fattoriale di un dato
numero. In tal caso aggiungete semplicemente il messaggio **factorial** a
Numero:

@test609

Questo richiede la ricorsione. Infatti il compito collegato al
messaggio **factorial** deve essere eseguito di nuovo all'interno di quella funzione.
Quindi è necessario invocare la funzione fattoriale dall'interno della
funzione fattoriale stessa. Di norma XOScript impedisce questa procedura,
a causa del rischio di finire in un ciclo infinito. Per questo motivo
è fondamentale far precedere il messaggio dalla parola **ricorsivo**. Ciò
serve a rendere XOScript consapevole del fatto che è vostra
intenzione eseguire lo stesso compito e che non avete commesso un errore.

## Oggetti simili a classi

Anche se xoscript non offre classi, imitare un comportamento
simile a quello delle classi è banale. Basta ridefinire il messaggio nuovo.

```
>> Animale := Oggetto nuovo.
Animale on: ['nuovo'] fare: {
	<- io nuovo inizializzare.
}.

Animale on: ['inizializzare'] fare: {
	mio verso := ['?'].
	mio zampe  := 4.
}.
```

Nel frammento di codice qui sopra creiamo un oggetto chiamato Animal.
Questo oggetto funge da *modello* per ogni tipo di animale,
come cani e gatti. L'oggetto genitore Animal è scritto
con la A maiuscola per indicare che si tratta di un oggetto simile a una classe.
Poi ridefiniamo il messaggio nuovo scrivendo il nostro metodo nuovo.
In questo caso esso invia il messaggio nuovo a io, seguito dal messaggio
inizializzare. Poiché xoscript blocca la ricorsione per impostazione predefinita, questo non provoca
un ciclo infinito. Invece, il messaggio nuovo viene inviato all'oggetto
genitore (Oggetto), producendo una nuova istanza di Animal. Creiamo quindi
un nuovo oggetto, basato sullo stesso oggetto per cui abbiamo creato il nostro metodo nuovo.
Questo è perfettamente valido. Inviamo anche il messaggio inizializzare, che garantisce
che l'oggetto Animal abbia valori predefiniti per le sue proprietà. Per impostazione predefinita
un animale ha 4 zampe e il verso è sconosciuto (da qui il punto interrogativo).
Per creare una nuova istanza del nostro Animal, potremmo semplicemente scrivere:

```
>> a := Animale nuovo.
```

Ora otteniamo una nuova istanza di Animal con 4 zampe, verso sconosciuto e
un metodo inizializzare. Proprio come in altri linguaggi OOP, possiamo anche
estendere il nostro Animal:

```
>> Cane := Animale nuovo.
Cane on: ['inizializzare'] fare: {
	io inizializzare.
	mio verso := ['abbaia'].
}.
```

Possiamo verificarlo facilmente aggiungendo un metodo testo:

```
Animale on: ['testo'] fare: {
	<- mio zampe testo + mio verso.
}.
```

Mettiamo tutto insieme:

@test13


Creare un oggetto che si trovi in un determinato stato iniziale è un
problema frequente. Supponete di dover creare un oggetto **Rectangle**
per calcolarne perimetro e area. Una possibile notazione sarebbe:


```
>> Rettangolo := Oggetto nuovo.

Rettangolo on: ['area'] fare: {
	<- mio lunghezza * mio larghezza.
}.
```

Ovviamente impostare lunghezza e larghezza è un prerequisito. A tale
scopo si possono aggiungere i messaggi **lunghezza:** e **width:**:


```
Rettangolo on: ['length:'] fare: { :lunghezza
	mio lunghezza := lunghezza.
}.

Rettangolo on: ['width:'] fare: { :larghezza
	mio larghezza := larghezza.
}.

```

Questo rettangolo può poi essere utilizzato come segue:


```
>> rettangolo := Rettangolo nuovo length: 2, width: 3.
Uscita scrivi: rettangolo area.
```

Tuttavia, se si trascurano le impostazioni iniziali di lunghezza e larghezza,
si verificherà un messaggio di errore:

```
>> rettangolo := Rettangolo nuovo.
Uscita scrivi: rettangolo area.
```

produrrà il seguente errore:

```
Chiave non trovata:lunghezza
```

Per evitarlo, è preferibile che un rettangolo abbia
sempre una lunghezza e una larghezza iniziali, per esempio 0. Quindi, in questo
caso, è necessario **ridefinire** il messaggio **nuovo**.

@test610

Se ridefiniamo il messaggio nuovo, in sostanza stiamo imitando una **classe**.

Il mondo di XOScript è pieno di oggetti diversi, che sono
disponibili per il vostro programma fin dall'inizio. Nei prossimi capitoli
verranno trattati tutti questi oggetti fondamentali.

## Snapshot

Potete salvare un oggetto (insieme al suo stato corrente) su disco con:

```
mioggetto save-as: ['saved.bin'].
```

Per ricaricare l'oggetto dal disco:

```
>> mioggetto := Oggetto load-from: ['saved.bin'].
```

Gli snapshot possono essere usati per salvare un determinato stato o per migliorare le prestazioni.
Caricare uno snapshot evita l'analisi lessicale, il parsing e la configurazione dell'applicazione.
Inoltre, in futuro, gli snapshot potrebbero introdurre ulteriori vantaggi
in termini di prestazioni, come l'ottimizzazione di determinati schemi o il rilevamento e
l'ottimizzazione dei percorsi critici.

{{warning}}
Gli snapshot sono una funzionalità sperimentale: non usateli in produzione.
Per attivare le funzionalità sperimentali, compilate con -D EXPERIMENTS.
{{/warning}}


@test712

# Oggetto Nil

{{messages}}

L'oggetto Nil
rappresenta il vuoto o, meglio ancora, l'assenza di informazione. A
volte riceverete questo oggetto come risposta a un messaggio, nel
caso in cui il risultato sia **niente**. La domanda più essenziale
che potete porre all'oggetto **Nil** è: **nil?**. La
risposta sarà sempre **Vero**.

```
Uscita scrivi: Nil nil?.
```

risultato:

```
Vero
```

Qualsiasi oggetto diverso da **Nil** risponderà con **Falso**. Il
frammento di codice qui sopra può sembrare un po' filosofico, eppure l'oggetto **Nil**
ha senza dubbio applicazioni estremamente pratiche. Per esempio,
riceverete l'oggetto Nil come risposta se chiedete un
elemento di una lista che non esiste. Potete usare l'oggetto Nil anche
se volete dichiarare una variabile ma non volete ancora specificarne
un valore. In tal caso **assegnate** semplicemente il valore speciale **Nil**. In
XOScript non è consentito dichiarare una variabile senza valore, come per esempio:


```
>> valore.
```

Dovete invece scrivere quanto segue:

```
>> valore := Nil.
```

@api_None_base

# Booleani

{{messages}}

A differenza della maggior parte dei linguaggi di programmazione diffusi al momento della stesura,
XOScript prevede un solo oggetto Vero e un solo oggetto
Falso. Per chiarire: ogni volta che scrivete **Vero**, ciò non significa che
sia stato creato un nuovo oggetto. Usate invece sempre un riferimento. Ciò
significa che quando scrivete quanto segue:

\>\> x := Vero.

la **x** si riferisce all'oggetto **Vero**. Anche il codice condizionale e i cicli
verificano questo riferimento. In XOScript il significato di **Vero** e **Falso**
non è fisso. Anzi, un programma XOScript viene parecchio sconvolto da
un'istruzione come questa:

Vero := Falso.

Il risultato di simili azioni è indefinito, tuttavia resta un'azione
valida e quindi formalmente consentita. Esiste inoltre un oggetto
Booleano, che è l'oggetto radice sia di **Vero** sia di **Falso**, poiché entrambi
derivano da questo oggetto radice. L'oggetto Booleano in sé, tuttavia,
non ha alcuna applicazione pratica.

## Insidie

Fate attenzione nell'uso di **e:** e **o:**

```
Uscita scrivi: (Falso or: Vero or: Vero), stop.
Uscita scrivi: (Falso o: Vero, o: Vero), stop.
```

Produce

```
Falso
Vero
```
perché il messaggio **o:** accetta un solo argomento. Il primo messaggio
invia **o:o:** a Falso, che non esiste, quindi l'oggetto ignora
il messaggio e restituisce sé stesso (Falso). La seconda riga invece
invia **o:** seguito da un altro **o:** (usando un simbolo di concatenazione, cioè una virgola: ,).


@api_Boolean_base

# Numeri

{{messages}}

Ogni volta che scrivete un numero, per esempio 9, -10 o 3,12, dietro le
quinte XOScript converte questi numeri in un oggetto **Numero**. Potete
inviare messaggi a questo oggetto Numero, oppure assegnare il numero
a una variabile e inviare i messaggi in seguito:

```
10 pari?

>> banconotaDaDieci := 10.
banconotaDaDieci pari?

```

Entrambe le notazioni sono valide. L'oggetto Numero risponde ai seguenti
messaggi...

La maggior parte di questi messaggi è autoesplicativa e vi permette di eseguire
operazioni matematiche o confronti.

{{note}}
Notate che potete usare ≤ ≥ ≠ × e ÷ al posto dei loro equivalenti ASCII.
È una questione di preferenza.
{{/note}}

La differenza tra i messaggi matematici binari (+) e
le loro varianti a parola chiave (inserisci:) è che i primi restituiscono
un nuovo numero, che è il risultato dell'operazione, mentre con i
secondi viene modificato l'oggetto stesso. Ciò è illustrato nel
seguente esempio:

@test597

Nell'esempio qui sopra b = 4 e a = 3. Con **inserisci: 2** il valore
di a viene aumentato di 2, mentre **+ 3** crea un nuovo numero che è
uguale ad a + 3. Lo stesso vale per altre operazioni matematiche, per esempio
le moltiplicazioni. Usando il simbolo di moltiplicazione riceverete come
risposta un nuovo oggetto. Se invece usate il messaggio **moltiplicato-per:**,
moltiplicherete il numero stesso.

Con il messaggio **tra:e:**, per esempio in **Numero
tra: X e: Y**, otterrete un numero compreso tra X e Y. In questo
modo si può generare qualsiasi numero casuale:

```
>> a := Numero tra: 1 e: 10.
Uscita scrivi: a, stop.
```

A partire dalla versione 1.4, il generatore di numeri casuali integrato in xoscript è,
per quanto ne sappiamo, crittograficamente sicuro.

Potete associare un **qual** (qualificatore) a un numero, per esempio **6
apples**. Ogni messaggio che non viene riconosciuto da un
numero viene considerato un qualificatore. Potete recuperare il qualificatore di
un numero tramite il messaggio qual:

Un qualificatore è fondamentalmente un oggetto Testo memorizzato insieme all'oggetto
Numero. Il qualificatore viene anche stampato dopo il numero in un'istruzione
**scrivi:**. I qualificatori possono essere usati, per esempio, per sommare importi
in valute diverse. Sommando gli importi, potete chiedere
i qualificatori. Il seguente programma di esempio illustra questo
principio usando un convertitore di valute storiche (poiché il tasso
di cambio resta ragionevolmente stabile!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Stringhe

{{messages}}

Ogni volta che un testo viene posto tra **parentesi quadre e virgolette** ['...'],
XOScript crea per voi un nuovo oggetto stringa. Assicuratevi però
di usare le virgolette corrette. La virgoletta all'inizio
del testo è diversa da quella alla fine (questo vi permette
di usare l'apice singolo senza doverne fare l'escape).

## UTF8

Le stringhe in xoscript contengono di solito testo codificato in utf8. Anche se
tecnicamente è possibile avere contenuto binario o non utf8 in
una stringa, per questo si consiglia di usare i blob. I blob sono
forniti dal plugin server (vedi il capitolo ffi).
In generale blob/ffi vengono forniti
per plugin/piattaforma, poiché sono legati alla piattaforma
e all'architettura (ffi/blob). Il nucleo del linguaggio di scripting cerca di
restare il più possibile indipendente dalla piattaforma.

## Conversione di tipo

Potete creare una copia di qualsiasi oggetto
con un tipo diverso usando i seguenti messaggi:

Messaggio | Risultato
--------- | ---------
numero    | Converte in un numero
testo     | Converte in una stringa
booleano  | Converte in un booleano
  
Valgono le seguenti regole:

messaggio | Nil       | Booleano           | Numero                | Testo     | Altro              
--------- | --------- | --------           | --------              | --------  | --------
booleano  | Falso     | n/d                | 0→Falso altro→Vero    | Vero      | Per lo più Vero
numero    | 0         | Falso→0 Vero→1     | n/d                   | ['n']→n   | Per lo più 1
testo     | ['Nil']   | ['Falso']/['Vero'] | ['n']                 | n/d       | Dipende

## Copiare

In XOScript i valori vengono sempre passati **per riferimento**. In altri linguaggi
dipende dal tipo di valore; in XOScript c'è un solo modo,
per riferimento. XOScript non fa mai una copia di un valore. Per copiare un oggetto
dovete inviare il messaggio **copia**. 

@test611

Qui forse vi sareste aspettati che l'output fosse Dolly invece
di Donny. Non è così, però, perché entrambi i nomi si riferiscono allo stesso
oggetto. Lavorando con un ciclo succede qualcosa di simile:

@test612

In effetti XOScript usa **sempre** i riferimenti, quindi su **:quantity**
anche il ciclo illustrato sopra indica il riferimento all'elemento
della lista.

Per copiare un oggetto dovete specificare questa azione in modo
**esplicito**:

@test613

Inviando il messaggio unario **copia** a una stringa, l'oggetto
restituisce una copia di quello stesso oggetto stringa. Allo stesso modo è possibile copiare oggetti
Numero, oggetti booleani, liste e dizionari.

Potete anche definire una vostra implementazione della copia; questo è perfino una
necessità se create oggetti vostri. L'implementazione
predefinita di copia per una lista esegue una copia superficiale: crea una
nuova lista con gli stessi elementi.

@test614

In questo caso 4 viene aggiunto solo alla copia.
Tuttavia, poiché la copia è superficiale, gli oggetti in entrambe le liste
sono gli stessi.

@test615

Quindi, se aggiungiamo 2 a ogni nome nella copia, anche la lista
originale ne risente.

Per rimediare dobbiamo fare una **copia profonda**. Un'operazione di copia di questo tipo
per una lista potrebbe essere composta come segue:

@test616

Notate anche il messaggio ricorsivo: è necessario inviarlo
prima del messaggio copia.

È essenziale tenere presente che, sebbene una copia di un oggetto
abbia spesso lo stesso aspetto dell'originale, in realtà non sarà
mai lo stesso oggetto. L'oggetto radice definisce un messaggio **equal:**,
che può essere usato per confrontare l'identità degli oggetti. Osservate il
seguente esempio:

@test617

## Conversione implicita

XOScript usa la **conversione implicita** per convertire gli oggetti. Per stampare una
lista sullo schermo, per esempio, XOScript invia internamente il messaggio
*testo* alla lista. Questo può rivelarsi molto utile nel
caso in cui vogliate stampare una lista come elenco separato da virgole. Il
messaggio *testo* può essere ridefinito: 

@test620

@api_String_base
@api_Format_base


## Stringhe del server

Le seguenti funzionalità di Testo vengono aggiunte dal
plugin Server.

@api_String_server

# Funzioni

{{messages}}

Potete raggruppare del codice tra { e }: diventa così una funzione.
In xoscript a volte usiamo anche il termine compito o semplicemente
blocco di codice.

Potete eseguire una funzione inviando il messaggio *correre*.


```
{ Uscita scrivi: 123, stop. } correre.
```

Se la vostra funzione accetta argomenti, usate **applica:**.

```
{ :a Uscita scrivi: a, stop. } applica: a.
```

Vedete anche gli esempi qui sotto.
A causa dell'architettura semplice, una funzione può avere un solo
punto di ritorno. Per evitare overhead o un annidamento eccessivo delle
condizioni, potete usare una procedura (che equivale a usare il
segno di moltiplicazione con argomento 1):

```
{
  (a = 1) vero: { x := 1. }, interrompere.
  (a = 2) vero: { x := 2. }, interrompere.
} procedura.
```

In questo modo (a = 2) non verrà valutato se a = 1.
Inoltre, così non servono messaggi vero annidati.
Ogni volta che vi trovate ad annidare condizioni, pensate
al messaggio procedura. Potrebbe rendere il vostro codice
più leggibile.


Ecco un'insidia importante:

```
{
	Falso falso: {
		Uscita scrivi: ['Termina il ciclo.'].
	}, interrompere.
	
	Uscita scrivi: ['Non mostrarmi.'].

} procedura.

```

In questo caso il testo 'Dont show me' verrà mostrato,
perché **interrompere** viene inviato a Falso. Se volete eseguire
un'interruzione, essa deve essere inviata come messaggio a **Vero**.
 

```
{
	Falso non vero: {
		Uscita scrivi: ['Termina il ciclo.'].
	}, interrompere.
	
	Uscita scrivi: ['Non mostrarmi.'].

} procedura.

```

Funzionerà come previsto.

## Eccezioni

Le eccezioni possono essere gestite così:

```
{ Incarico 1 } catturare: { Incarico 2 }, correre.
```

Potete anche provocare intenzionalmente un errore nel vostro programma e,
così facendo, attivare il blocco di gestione. Ciò si fa inviando il
messaggio **errore:** al compito corrente, come mostrato nella prossima
illustrazione:

```
{
questo-compito errore: ['Ops!'].
} catturare: { :sbaglio
Uscita scrivi: sbaglio.
}, correre.
```

## Iniettare valori

XOScript offre ai compiti la possibilità di iniettare valori. Osservate
il compito qui sotto:

```
>> invio := {
	Notiziario destinatario: mio recipient.
}.
invio valore: ['recipient']
impostato: ['info@recipient.org'].
invio correre.
```


Questa illustrazione presenta un compito immaginario che invia una newsletter
a un indirizzo email o **recipient**. Questo destinatario può essere iniettato
nel compito dall'esterno, prima che il compito venga avviato, inviando
al compito il messaggio **valore:impostato:**. In questo modo il valore di
**recipient** viene preimpostato nel compito. Questo valore può anche essere modificato
e il compito può poi essere eseguito di nuovo. È un metodo utile quando si usano
oggetti Compito.

## Funzioni vuote

I compiti vuoti non sono consentiti. In teoria un compito vuoto avrebbe questo
aspetto: **{}**, ma XOScript lo considera un errore di linguaggio. Se
volete dichiarare un compito vuoto, potete usare l'oggetto Nil:

```
>> incarico := Nil.
```

Anche se questo non è un vero compito ma un oggetto Nil, gli si può
comunque inviare un messaggio correre:

```
>> responso := incarico correre.
```

In effetti è lo stesso di:

```
>> responso := Nil correre.
```

Poiché l'oggetto **Nil** non riconosce il messaggio **correre**,
restituisce sé stesso come risposta, e la risposta è ancora una volta **Nil**.
Quindi non c'è alcuna necessità di avere un compito vuoto. Grazie all'elegante
progettazione del linguaggio di programmazione XOScript, potete semplicemente usare l'oggetto
Nil a questo scopo.

## Scoping dinamico

Quando un Compito ha bisogno di una variabile ma non riesce a trovarla,
controlla le variabili del Compito che lo ha **chiamato**
e continua a controllare risalendo la catena dei Compiti.
Questa ricerca prosegue finché la variabile non viene trovata.
Se la variabile non viene comunque trovata, compare un messaggio di errore. Questo metodo di ricerca di una
variabile si chiama **scoping dinamico**.

Per illustrare questo principio:

@test618

@api_Code_base

# Oggetto radice

{{messages}}

L'oggetto chiamato **Oggetto** è l'oggetto radice di tutti gli oggetti in
XOScript e fornisce le funzionalità fondamentali del linguaggio. 

Il messaggio inviato più spesso
è **on:fare:**, che estende le funzionalità di un oggetto. Questo
messaggio viene ricevuto dall'oggetto radice, che di conseguenza collega il
compito specificato al messaggio e, così facendo, estende l'oggetto
derivato.

## Metodi catch-all

Normalmente, se inviate un messaggio che non corrisponde a
un metodo dell'oggetto, questo viene ignorato. Potete però specificare
i cosiddetti **metodi magici** o metodi **catch-all**, che vengono
invocati se il messaggio non viene compreso dall'oggetto.

Sono disponibili 4 metodi catch-all. Ogni messaggio corrisponde
a un numero specifico di argomenti.

Messaggio catch-all      | Numero di argomenti
------------------------ | -------------------
rispondere:              | 0
rispondere:e:            | 1
rispondere:e:e:          | 2
rispondere:e:e:e:        | 3


@test619

## Messaggi programmatici

Invece di inviare un messaggio direttamente a un oggetto, è possibile anche
inviarlo tramite una variabile. A tale scopo si usa il messaggio
**messaggio:argomenti:**. 

@test396

@api_Object_base

# Liste

{{messages}}

XOScript conosce due tipi di collezioni: le *liste* e i *dizionari*.
Le **liste** sono enumerazioni di oggetti in un *ordine fisso*. I dizionari non hanno
un ordine; somigliano piuttosto a una legenda con una chiave (o termine) e il
valore corrispondente. Le liste sono paragonabili agli array (PHP, Java, C)
e alle liste (Python). I dizionari sono paragonabili agli array associativi (PHP) o ai
dizionari (Python) di altri linguaggi di programmazione. Per creare
una nuova Serie scrivete:

```
>> fibonacci := Serie nuovo.
```

Questa lista vuota può essere riempita usando **aggiungere:** :

```
fibonacci aggiungere: 0.
fibonacci aggiungere: 1.
fibonacci aggiungere: 1.
fibonacci aggiungere: 2.
fibonacci aggiungere: 3.
fibonacci aggiungere: 5.
fibonacci aggiungere: 8.
fibonacci aggiungere: 13.
```

Se scriviamo la lista sullo schermo:

```
Uscita scrivi: fibonacci, stop.
```

Vedremo:

```
Serie ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

Invece di aggiungere potete usare anche ; per aggiungere elementi a una lista:


```
>> fibonacci := Serie nuovo ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

I punti e virgola (;) sono tutti messaggi binari che inseriscono un
valore nella lista.

## Concatenazione

Supponete di avere una lista come:

```
>> x := Serie nuovo ; 1 ; 2 ; 3.
```

Se voleste eliminare il primo e l'ultimo elemento, il vostro
messaggio sarebbe:

```
x tagsin tagdes.
```

Purtroppo la notazione precedente non funziona correttamente. Il
messaggio **tagsin** restituisce il primo elemento della lista, che
a sua volta diventa il destinatario del messaggio **tagdes**. Quindi il
messaggio **tagdes** non viene inviato a **x**, ma a 2. Una
possibile soluzione a questo problema sarebbe scrivere due frasi
separate, come: 

```
x tagsin.
x tagdes.
```

Questo è però piuttosto scomodo, in particolare quando dovete
eliminare più di due elementi. Per questo XOScript offre una
struttura di messaggi alternativa per situazioni di questo tipo. Nelle
strutture di messaggi **alternative**, le risposte degli oggetti vengono ignorate
e ricevete ogni volta come risposta l'oggetto ricevente.
Una struttura di messaggi **alternativa** si avvia inviando il
messaggio **fare** a un oggetto, e la struttura di messaggi **alternativa**
può essere chiusa inviando il messaggio **fatto**. Nell'esempio
illustrato, ciò si potrebbe applicare come segue:

```
>> x := Serie nuovo ; 1 ; 2 ; 3.
x fare tagsin tagdes fatto.
```

@api_List_collections

# Dizionari

{{messages}}

**Sia Serie sia Elenco sono collezioni. Tuttavia, a differenza di una
lista, un dizionario **non ha** un ordine. Un'altra differenza tra i due
è che un dizionario è composto da coppie di oggetti. Un oggetto funge da voce (o
parola chiave) per cercare l'altro oggetto. Un buon esempio di
lista di questo tipo è un listino prezzi, come:


```
>> menù := Elenco nuovo
	met: ['£5'] a: ['torta di mele'],
	met: ['£6'] a: ['torta di carote'],
	met: ['£3'] a: ['fudge'].
```

Come per una lista, il messaggio met:a:
si usa per aggiungere un oggetto a una lista. La differenza è che, a differenza di
una lista, vengono collegati due oggetti. Il primo oggetto è, come
per una lista, l'oggetto che memorizzerete nella lista. Il secondo
oggetto non è la sua posizione all'interno della collezione, ma la **voce**
che permette di recuperare in seguito l'oggetto precedente. In
breve, un dizionario funziona un po' come un vocabolario: usando la parola chiave
si trova il significato. Per esempio, per recuperare dalla
lista sopra indicata il prezzo di un fudge:

```
>> price := menù a: ['fudge'].
```

Potete usare anche la notazione concisa:

```
>> price := menù ? ['fudge'].
```

Se le voci che usate per memorizzare gli oggetti non contengono spazi
(e non entrano in conflitto con altri messaggi predefiniti),
si può usare anche la notazione seguente:

```
>> menù := Elenco nuovo
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Senza dubbio la notazione qui sopra si legge in modo un po' più naturale.
Per chiedere il prezzo di un
fudge si può usare la seguente notazione semplificata:

```
>> price := menù fudge.
```

@api_Dict_collections

# File

{{messages}}

L'oggetto **File** fornisce un accesso di base al file system.
Potete usare questo oggetto per leggere interi file in una variabile in
una sola volta, o per scrivere variabili su file in una sola volta. È supportata anche
la lettura riga per riga. Queste sono le operazioni di I/O su file più comuni
in un linguaggio di scripting. Le operazioni avanzate sui file richiedono
l'uso dell'FFI tramite il plugin server o un plugin IO separato.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Data/Ora

{{messages}}

Per una rappresentazione strutturata di data e ora, XOScript usa
l'oggetto **Momento**. Se un nuovo oggetto Momento viene stampato sullo schermo, vengono
mostrate la data e l'ora correnti:

```
Uscita scrivi: Momento nuovo, stop.
```

Potrebbe produrre qualcosa come:

```
2020-10-10 12:16:39
```

È anche facile leggere i singoli componenti temporali. Quindi,
per esempio, se serve conoscere solo l'anno corrente, si può inviare
il messaggio **anno** al momento e la risposta sarà
un oggetto Numero contenente solo l'anno:

```
>> m := Momento nuovo.
Uscita scrivi: m anno, stop.
```

@api_Moment_system

# Programma/StdOut

{{messages}}

L'oggetto Programma rappresenta l'applicazione attualmente in esecuzione. Questo oggetto
offre funzionalità per eseguire comandi di sistema, includere sottoprogrammi,
leggere argomenti e altro ancora: tutte le funzioni legate al sistema.

## StdOut

Uscita è l'oggetto di output standard. Ha fondamentalmente due metodi:
**scrivi:** e **stop**. Il messaggio scrivi: serve a inviare una stringa
a stdout, il messaggio stop stampa un carattere di nuova riga.
Invece di **stop** potete usare anche \\n.

Esempio:

```
Uscita scrivi: ['Hello World'], stop.
```

risultato:

```
Hello World
```

## Moduli/Plugin

Il mondo di XOScript può essere ampliato con nuovi oggetti di sistema
installando moduli. Un nuovo oggetto di sistema può essere aggiunto al mondo di
XOScript collocando il file del modulo (di solito un file con il suffisso .so
) nella cartella mods. 

Quando inviate un messaggio all'oggetto reso disponibile dal
modulo plugin, questo viene caricato automaticamente da XOScript.

Potete anche scrivere plugin voi stessi. I plugin sono scritti nel
linguaggio di programmazione C. Trovate un plugin di esempio nel pacchetto
dei sorgenti in src/plugins/example.


## Riflessione

Esistono vari modi per esplorare
il sistema durante l'esecuzione del programma. XOScript dispone di alcuni metodi per
rilevare quali oggetti sono presenti e a quali messaggi questi oggetti
rispondono. Innanzitutto, a ogni oggetto si può chiedere di che **genere** è;
tuttavia in XOScript i tipi sono malleabili e quindi inaffidabili.

È anche possibile chiedere all'oggetto Programma se un
dato oggetto è già presente nel programma:

```
Programma Strumento vero: { ... }.
```

Nel caso di un nome di oggetto
composto da un solo simbolo, è meglio usare la
seguente notazione per evitare confusione:

```
Programma trova: ['X'], vero: { ... }.
```

Oltre che sugli oggetti, è possibile interrogare l'oggetto
Programma anche sui messaggi. Per esempio, gli si può chiedere se
l'oggetto **Numero** conosce il messaggio **tra:e:**, nel modo
illustrato qui sotto:

```
Programma Number: ['between:and:'], stop.
```

@api_Program_system

# server

{{messages}}

Il plugin Server di xoscript offre funzionalità per
creare applicazioni lato server. Per caricare il plugin
server usate:

```
Server inizializzare.
```

Per comodità si consiglia anche di caricare
i file webtools.xo e template.xo.

```
Programma uso: ['webtools.xo'].
Programma uso: ['template.xo'].

```

## Impostazioni del server

Potete configurare le seguenti impostazioni del server:

```
	# vengono dati valori predefiniti
	# quindi se non imposti niente, questi
	# valori vengono usati...

	Programma 
	instelling: ['max-campi']
	is: 40.

	Programma 
	instelling: ['max-contenuto']
	is: 2000000. # 2MB

	Programma 
	instelling: ['max-time']
	is: 5000. # 5sec

```

## Hello World

Ecco un programma web molto semplice che potete usare con un
server CGI standard come Apache2, NGINX, OpenHTTPD o qualsiasi altro
server noto.

```
#!/bin/xo

Server inizializzare.
Programma uso: ['webtools.xo'].

>> doc-web := Documento-Web nuovo.

doc-web emettere: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Se non volete usare l'oggetto Documento-Web va benissimo, ma
in tal caso dovete scrivere voi stessi le intestazioni HTTP:

```
#!/bin/xo
Uscita scrivi: ['Content-type: text/html; charset=utf-8 \n\n'], stop.
Uscita scrivi: ['ciao mondo!'], stop.
``` 

## Richiesta

L'oggetto Richiesta-HTTP può essere usato per ottenere i dati GET/POST/COOKIE e
UPLOAD:

```
>> richiesta  := Richiesta-HTTP nuovo.
>> search   := richiesta get: ['search']. # ?ricerca=libri
>> password := richiesta post: ['password']. # dal modulo
>> selezionati := richiesta get-lista: ['sel[]']. #?sel[]=1&sel[]=2
>> selezionati := richiesta post-lista: ['sel[]'].
>> cookie   := richiesta cookie: ['session-id'].
>> caricamento   := richiesta upload: ['file'].
>> percorsotemp := caricamento ? 1.
>> nomefile := caricamento ? 0.
```

## Maxpost/length

Il numero massimo predefinito di campi POST è 40 e la lunghezza massima
predefinita del contenuto è 2MB. Per configurarli diversamente per singolo script:

```
Programma instelling: ['max-contenuto'] is: 1. 
Programma instelling: ['max-campi'] is: 1. 
```

{{note}}
Se la lunghezza del contenuto supera il massimo, il
processo viene terminato, perché non possiamo più essere sicuri
che il payload sia sicuro.
{{/note}}

Il limite maxtime determina il tempo massimo in ms
per leggere stdin/i dati POST.

```
Programma instelling: ['max-time'] is: 5000. # 5sec
```

Questo vale solo per la lettura I/O del POST e previene
attacchi di tipo slowloris. Se volete davvero limitare il
tempo di esecuzione di qualsiasi operazione, usate Programma tempo-massimo.

## Database

L'oggetto Database può essere usato per interrogare MariaDB/MySQL.
Per connettervi a un database:

```
>> db := MariaDB nuovo host: ['localhost'],
	utente: ['xo'],
	password: ['pass123'],
	nome-database: ['xobase'],
	connetti.

```

Per inserire un record usate:

```
>> parametri := db query: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parametri: ( Serie nuovo ; ['abc'] ; 12.35 ; 6 ). # query parametrizzate

{  parametri esegui. db commit. }
catturare: { :e db rollback.  }, correre.
```

Notate che xoscript lavora *solo* con le transazioni e non esegue mai l'autocommit.
Se l'autocommit non può essere disattivato, otterrete un errore di connessione.
Usate sempre il binding dei parametri per le query, non aggiungete mai l'input dell'utente direttamente
all'SQL.

Ottenete l'id inserito così:

```
Uscita scrivi: ['INSERITO: '] + parametri insert-id, stop. # id di inserimento
```

Per recuperare i record:

```
>> parametri :=
db
	query: ['SELECT * FROM book order by id desc limit 2'], 
	recupera: { :fila 
		Uscita scrivi: fila id + [' '] + fila description + [': '] + fila price, stop.
	}. # lettura delle righe

```

## Sessioni

Per la persistenza potete memorizzare e recuperare dati da un oggetto sessione.
Create prima un nuovo **Documento-Web**. L'oggetto Documento-Web riunisce
la richiesta, le intestazioni, l'HTML e la sessione. Questo perché, quando
visitate un sito web con il browser, vedete solo l'HTML. Ma
l'intero Documento-Web è composto anche da **intestazioni**. Per esempio,
la maggior parte delle risposte HTTP include un'intestazione come Content-type:text/html per
indicare al browser che i dati che seguono devono essere visualizzati come HTML
(e non, per esempio, scaricati come un file). Le sessioni sono un modo per
memorizzare i dati dell'utente tra una richiesta e l'altra. Per tenere traccia di questi dati dobbiamo
impostare un cookie, e anche questo cookie viene impostato tramite un'intestazione. Ecco perché
tutto si riunisce nel Documento-Web (perché è il documento completo
che contiene sia le intestazioni sia l'HTML o altri dati).


```
# Prima creiamo una nuova istanza di Documento-Web
>> web := Documento-Web nuovo.

# Ora avviamo una sessione, questo genererà un'intestazione per un cookie e
# creerà un file per salvare i tuoi dati, associato a quel cookie
>> sessione := web avviare-sessione.

# Ora possiamo trattare sessione come un Elenco
sessione userid: 123.
```

Per distruggere la sessione (al logout):

```
web distruggere-sessione.
```

## Intestazioni

Il Documento-Web vi permette anche di impostare altre intestazioni note.
Per esempio, se volete reindirizzare l'utente a un altro URL:

```
web vai-a: ['/other.html'].
```

Dietro le quinte, questo comando genera anche l'intestazione HTTP da inviare
insieme agli altri dati o all'HTML, per indicare al browser di navigare
verso l'indirizzo di destinazione specificato.

Per aggiungere un'intestazione personalizzata:

```
web intestazione: ( 
	Intestazione-HTTP nuovo
	chiave: ['Content-Length']
	valore: 400
).
```

Per mostrare una pagina 404:

```
web non-trovato: ['Ahia..'].
```


## Template

Il sistema di template predefinito è molto semplice. Non dovete imparare
una nuova sintassi di template. Inoltre il motore di template garantisce una vera separazione
tra presentazione e logica di business.

Per creare un template da un file:

```
>> tpl := web sagoma: ['templates/ux.tpl'].
```

Il sistema di template usa dei marcatori. 
Esistono tre tipi di marcatori: marcatori di taglio, marcatori di incolla e
marcatori di slot. L'idea di base è davvero semplice: ritagliate
le aree identificate dai marcatori di taglio e potete incollarle nelle
aree identificate dai marcatori di incolla. Potete iniettare stringhe nei
marcatori di slot.

Per esempio, dato il template seguente, mettiamo la
gemma nel portagioie e aggiungiamo un cartellino del prezzo.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Potete farlo come segue:

```
>> gem := tpl tagliare: ['gem'], copia.
gem price: 99.
tpl incollare: gem a: ['jewels'].
web emettere: tpl pulire.
```

L'ultima riga invia semplicemente il template come stringa al client,
insieme alle intestazioni HTTP necessarie.

Risultato:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

Per servire in modo sicuro i file caricati dagli utenti potete affidarvi a passthru:

```
>> caricato := ['smile.gif'].
Server passaggio: caricato prefisso: ['/uploads/images/'].
Programma fine.
```

Questo serve il contenuto caricato dall'utente con il tipo
MIME appropriato. Sono supportati solo i tipi MIME presenti nella lista consentita:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF e SVG.
I file SVG, ZIP e GZIP vengono inviati come download, perché un SVG
può contenere script che altrimenti verrebbero eseguiti sul vostro dominio.
Questo metodo previene attacchi TOCTOU, path traversal,
esecuzione di codice malevolo (injection), attacchi tramite symlink,
attacchi DDoS (limite dei file = 50MB), attacchi di sniffing e
vari altri problemi di sicurezza.


## JSON

Per codificare un oggetto come JSON:

```
>> json := ( JSON jsonifica: ( 
	Elenco nuovo met: ( 
		Serie nuovo ; 1 ; 2 ; 3
	) a: ['abc']
)).
```

Per decodificare JSON in un oggetto xoscript:

```
>> diz := ((JSON oggetto: json) abc ? 1).
```

Il JSON con più di 500 livelli di annidamento viene rifiutato come non valido.

Per emettere direttamente un Elenco come json con le intestazioni corrette:

```
web json: diz.
```


## Regex

Potete usare le espressioni regolari creando un modello.
Per esempio, per trovare gli href e i target dei collegamenti ipertestuali:

```
Modello nuovo: ['href="([^"]+)" target="([^"]+)"'].
```

Applicate ora il modello alla stringa da esaminare in questo modo:

```
criterio corrispondenza: soggetto fai: { :m :x .... }
```

Esempio completo:

```
>> soggetto := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> criterio := Modello nuovo: ['href="([^"]+)" target="([^"]+)"'].
>> risultato  := criterio corrispondenza: soggetto fai: { :m :x
	Uscita scrivi: m, stop.
	Uscita scrivi: x, stop.
	<- ['XXX'].
}.
Uscita scrivi: risultato, stop.
```

## Rete

Usate l'oggetto Rete per eseguire una richiesta web.
L'oggetto Rete invia sempre una richiesta POST, a meno che non inviate Nil come
dati: in tal caso invia una richiesta GET.


```
Rete 
post: Nil 
a: ['https://redbeanphp.com'].
```

## Crittografia

Il plugin server include una crittografia basata su XChaCha20 e Argon2.

Esempio:

```
>> cifrato := Caveau critta: ['hello'] chiave: ['world'].
>> decifrato := Caveau critta: cifrato chiave: ['world'].
```

## Token

Per generare un token crittograficamente sicuro di una lunghezza specifica:

```
>> miotok := Caveau token: 40.
```

Questo genera un token di 40 caratteri.

## Formattazione

L'oggetto Formato vi permette di formattare i dati, per esempio con il padding o
aggiungendo zeri. Usa la sintassi di printf.

```
>> fmt := Formato nuovo: ['%06.0f'].
fmt applica: 56. # dà 000056
```

Un formato può contenere una sola conversione, che deve corrispondere al valore,
altrimenti si ottiene un errore:

- `applica:` con una stringa: `%s`
- `applica:` con un numero: `%f`, `%e`, `%g` o `%a`
- `applica-int:` con un numero: `%d`, `%i`, `%o`, `%u`, `%x` o `%c`

I valori provenienti da una richiesta sono stringhe. Per formattarne uno come numero,
convertitelo prima:

```
fmt applica: (richiesta get: ['amount']) numero.
```

## Codificatori

Sono disponibili diversi codificatori e decodificatori.
Il codificatore url prepara un url per l'uso in HTML come collegamento:

```
Server url-codifica: ['https://example.com?a=6&b=1 2'].
```

Per inserire in sicurezza l'input dell'utente nel vostro HTML senza rischiare
iniezioni XSS, usate sempre:

```
Server html-codifica: ['<innocuo>'].
```

Notate che il motore di template esegue sempre la codifica html
quando scrivete in un marcatore di slot. Quindi, se usate il sistema di template,
non avete bisogno di usarlo.

## Invio di email

Per inviare un'email usate la libreria mailtools.xo.

Esempio:

```
Server inizializzare.
Programma uso: ['mailtools.xo'].

>> e-mail := Email-HTML nuovo.
>> img := e-mail allegare: ( File nuovo: ['myimage.png'] ).

e-mail
mittente: ['xo@xoscript.com'] nome: ['xo'],
destinatario: ( Serie nuovo ; ['xo2@xoscipt.com'] ),
soggetto: ['xoxo'],
corpo: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), inviare.

```



## Collegamento

Con il messaggio collega: potete collegare una libreria esterna al
vostro programma usando libffi. Per i dettagli vedete il capitolo su ffi.


@api_Request_http
@api_URL_http
@api_Pattern_pattern
@api_Maria-DB_mariadb
@api_Maria-Query_mariadb
@api_Net_net
@api_Vault_vault
@api_Server_server
@api_JSON_json

# ffi

{{messages}}

L'FFI viene fornita per piattaforma/plugin perché è
legata all'architettura del sistema sottostante, cosa che il
nucleo non dovrebbe fare.
Il plugin server offre un'implementazione conforme di ffi/blob.
Per impostazione predefinita il nucleo si collega alla piattaforma di destinazione
tramite stdin/stdout, servizi limitati di I/O su file e la shell (Programma sistema:).
L'integrazione aggiuntiva è fornita da ffi/blob tramite plugin orientati
all'applicazione, come il plugin server.

FFI sta per Foreign Function Interface. Vi permette di usare funzionalità scritte da altri in
linguaggi di programmazione diversi, fornite tramite file DLL, file SO o file Dylib. Può trattarsi
di funzioni di ogni tipo, e con questo metodo è disponibile una vastissima gamma di funzionalità.
Cominciamo con un esempio:

```
Server collega: (
 Serie nuovo ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Serie nuovo ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s libero.
```

Il risultato di questo codice è che sulla riga di comando vedrete quanto segue:
FFI has 3 letters.
Ora probabilmente state pensando: "È un sacco di codice per qualcosa di così semplice."
Insomma, non potremmo risolverlo con un comando Gui show? La risposta è un sonoro sì!
Ma questo vuole essere un esempio illustrativo.
L'FFI si usa di solito per compiti più complessi, ma quelli non sono buoni
esempi, quindi ho scelto qualcosa di banale.

Gli argomenti del metodo collega:

- Argomento n. 1: il file DLL o SO che volete usare.
- Argomento n. 2: la funzione di quel file che volete collegare.
- Argomento n. 3: una lista con i nomi dei tipi di dati degli argomenti della funzione.
- Argomento n. 4: il nome del tipo di ritorno della funzione.
- Argomento n. 5: il nome dell'oggetto a cui volete collegare questa funzione (se non esiste, verrà creato
automaticamente).
- Argomento n. 6: il messaggio a cui questa funzione deve essere collegata.

Nell'esempio qui sopra vogliamo collegare la funzione printf di libc.so. Trovate i nomi dei
tipi di dati nella documentazione del software a cui vi collegate. I tipi disponibili sono:
void, pointer, float, double, int, uint, char, uchar, intX e uintX,
dove X può essere 8, 16, 32 o 64.

Questi tipi indicano il numero di byte necessari per memorizzare i dati. Per printf ci colleghiamo a un
nuovo oggetto chiamato Printf e al messaggio template:number:. La funzione esterna
viene tradotta nel dialetto XOScript prima di usarla. Il messaggio template:number: si aspetta come
primo parametro un buffer con il testo del template. Creiamo questo buffer con un oggetto Blob, che
vi permette di allocare memoria manualmente. Siete responsabili di liberare in seguito questa memoria
con il messaggio libero.

Potete riempire un blob di memoria in vari modi. Nel nostro esempio lo riempiamo con del testo, quindi usiamo il
messaggio utf8: (UTF-8 è una codifica per convertire il testo in byte). Potete anche riempire un blob con
bytes:, passando una lista di valori di byte. Per leggere il contenuto di un blob usate da:lunghezza:.
Riceverete i byte sotto forma di lista. Con un Blob potete perfino creare una struct C usando il
messaggio struttura:, passando una sequenza di tipi C. Ciò può essere necessario quando si chiama una funzione
C di una libreria software esterna che si aspetta un puntatore a una struct.

{warning}
Dovete liberare i blob voi stessi.
I blob non vengono ripuliti dal garbage collector.
{/warning}

Poiché i blob possono essere scambiati con funzioni esterne di librerie,
non possono essere raccolti automaticamente dal garbage collector (potrebbero restare in uso da parte di
funzioni esterne, oppure queste funzioni esterne potrebbero volerli liberare
da sé). Per questo, se necessario, dovete liberare i blob voi stessi.

Per liberare un blob usate:

```
mioblob libero.
```

Per liberare una struct usate:

```
miastruttura strutturalibera libero.
```

Quindi, per una struct, dovete inviare due messaggi, strutturalibera e libero, per
deallocare il blocco di memoria.

@api_Blob_fficonnect
