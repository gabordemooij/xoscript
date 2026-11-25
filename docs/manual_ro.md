# Noțiuni de bază

{{messages}}


Bun venit în XOScript
Proiectul XOScript își propune să creeze un limbaj de scripting simplu și auditabil.
Simplu nu înseamnă neapărat ușor.
Un limbaj de programare familiar poate fi mai ușor de folosit decât XOScript.
Aici, simplitatea înseamnă altceva:
posibilitatea de a-ți forma un model mental complet al limbajului și al comportamentului său.

XOScript este conceput să încapă în mintea ta.
Gramatica și numărul de concepte sunt intenționat reduse.
Nu există clase; obiectele pot fi extinse direct.
Obiectele sunt transmise prin referință, copierea este explicită,
iar funcțiile au un singur punct de ieșire.

Unele dintre aceste alegeri diferă considerabil de limbajele obișnuite.
XOScript nu are, de exemplu, un sistem de tipuri și folosește domeniu de vizibilitate dinamic.
Mesajele care nu pot fi tratate sunt ignorate în loc să producă o excepție.
Aceste alegeri au consecințe și nu au scopul de a elimina erorile.
Scopul lor este să păstreze modelul de bază al limbajului mic și coerent.

XOScript poate fi și localizat, ceea ce face posibilă exprimarea regulilor
de business într-o limbă naturală și, eventual, partajarea lor cu părți interesate fără pregătire tehnică.

Auditabilitatea înseamnă aplicarea aceleiași filozofii și implementării.
Mediul de execuție este scris în C, cu un lexer, un parser și un tree walker mici, scrise de mână.
Biblioteca standard și mediul de execuție reflectă în mare parte structura limbajului,
astfel încât legătura dintre codul XOScript și implementarea sa este relativ directă.

Testele sunt și ele strâns legate de documentație.
Fiecare metodă ar trebui să aibă un test asociat care poate fi inclus în manual,
ceea ce ajută la menținerea documentației în acord cu implementarea.

XOScript nu își propune să concureze cu limbajele obișnuite în privința
funcționalităților sau a familiarității. Explorează un alt obiectiv:
un mediu de programare pe care un dezvoltator îl poate înțelege în întregime.

Speranța este că un limbaj mic și o implementare
mică fac posibilă în practică înțelegerea software-ului
de la byte la obiect, de la sintaxă la mediul de execuție, și scrierea codului cu
încredere, pentru că înțelegi atât ce se întâmplă în
script, cât și ce se întâmplă în culise.

Arhitectura unei configurări de server xoscript
este simplă, dar flexibilă.

{{architecture.png}}

Pentru a folosi xoscript ca limbaj de server, trebuie să instalezi
pluginul de server într-un director numit /mods/server. 

Motivul este că preferăm
să separăm limbajul de bază de funcționalitățile specifice serverului,
spre deosebire, de exemplu, de PHP sau Python. Altfel ar trebui să livrăm
tuturor absolut totul, fără niciun rost, ceea ce ar fi pur și simplu absurd.
Poți instala și alte module, dacă dorești. Sistemul este foarte
flexibil.

De asemenea, unele funcții sunt mai bine implementate în limbajul de scripting
însuși, cum ar fi șabloanele și gestionarea sesiunilor, așa că livrăm
în plus bibliotecile template.xo și webtools.xo, pentru comoditatea ta.
Motivul pentru toate acestea este că nu știm cum vrei să
folosești xoscript. Îl poți folosi ca limbaj de scripting pe server,
dar și pentru interfețe grafice, dispozitive embedded sau simplă procesare în loturi.
Chiar dacă îl folosești ca limbaj de scripting pe server (care este
în prezent unul dintre principalele cazuri de utilizare), s-ar putea totuși să vrei
să folosești alt motor de șabloane sau alt gestionar de sesiuni.
Cine suntem noi să decidem că trebuie să le folosești pe ale noastre?

Unul dintre avantajele folosirii propriului nostru motor de șabloane este însă
că nu trebuie să înveți o sintaxă suplimentară pentru a crea șabloane.
Motorul de șabloane implicit livrat cu xoscript separă 100%
prezentarea de logică. În loc de o sintaxă specială
pentru șabloane, folosește pur și simplu un sistem foarte flexibil de marcaje de poziție.
Pentru mai multe informații, vezi capitolul Server.

Reține că, dacă nu vrei să folosești motorul de șabloane implicit sau
webtools implicit, este de la sine înțeles că trebuie să le furnizezi
pe ale tale.

Dacă rulezi serverul web într-un chroot, jail sau alt tip de sandbox,
trebuie să instalezi și dependențele lui xo în acel mediu; poți
vedea de ce biblioteci ai nevoie folosind ldd (vezi pagina man din Linux sau BSD).
Dacă vrei să folosești comenzi shell în scripturile xo, copiază și un shell
(cum ar fi bash sau ksh) în acest mediu.

Dorim de asemenea să menționăm că luăm compatibilitatea retroactivă foarte în serios.
Există chiar o funcționalitate specială de compatibilitate retroactivă numită
'version'. În general, ne propunem ca codul tău să ruleze pentru totdeauna. Așadar,
nu va trebui niciodată să-ți actualizezi codul pentru a rămâne compatibil cu versiunile mai noi
de xoscript. Obiectivul nostru este: scrii o dată, rulezi pentru totdeauna.

Restul acestui manual este dedicat explicării în detaliu a limbajului de programare
xoscript. Scriptingul pe server este discutat în capitolul
numit Server. Dacă ești un dezvoltator software cu experiență, poate vrei
să sari peste câteva capitole, deoarece unele dintre ele sunt puțin prea detaliate sau
sunt foarte asemănătoare cu practicile generale de programare. Așadar, pentru cei
care au deja experiență cu mai multe alte limbaje de programare,
este mai bine să trateze acest manual ca pe un ghid de referință.

## Instalare pe Linux

Descarcă apache2 și mariadb:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Descarcă xoscript.
Înlocuiește X cu numărul corect al versiunii!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Copiază fișierele în rădăcina web și în /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Editează configurația apache2:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Înlocuiește Virtualhost cu:

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

Creează o pagină de test:

```
sudo nano /var/www/html/test.xo
```

și scrie un mic program de test:

```
#!/bin/xo
Server inițializează.
Program folosește: ['webtools.xo'].
>> web := Document-Web nou.
web scrie-ieșire: ['Hello World'].
```

Permite lui apache2 să execute programul tău prin CGI:

```
sudo chmod uog+x /var/www/html/test.xo
```

Repornește apache2:

```
sudo systemctl restart apache2
```

Deschide pagina de test în browser:

```
http://localhost/test.xo
```

Ar trebui să vezi:

```
Hello World
```


## Instalare pe OpenBSD

Editează /etc/httpd.conf și adaugă:


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

Dacă vrei să folosești SSL:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Pentru a proteja schimbul de chei împotriva atacurilor cuantice,
selectează cifrul mlkem:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Adaugă binarul xo și modulele, precum și toate dependențele, în
chroot (află-le cu ldd).

## Rularea exemplelor


Pentru a rula unul dintre programele de exemplu din pachet:

```
./example.sh <name> <Linux/OBSD> [clean]
```

De exemplu, pentru a rula exemplul FizzBuzz pe Linux:

```
./example.sh fizzbuzz Linux
```

Pentru a rula același exemplu pe OpenBSD:

```
./example.sh fizzbuzz OBSD
```

Pentru a rula exemplul cu o compilare curată:

```
./example.sh fizzbuzz OBSD clean
```

## Teste unitare

Pentru a rula testele unitare:

```
./runtests.sh
```

Pentru a rula testele unitare fără compilare (doar testare):

```
./runtests.sh nobuild
```

## Compilare

Pentru a compila din surse pe Linux:

```
make clean
ISO="en" make
```

Pe OpenBSD:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

Pentru a compila pluginul de server pe Linux:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

Pentru a compila pluginul de server pe OpenBSD:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Hello world

După ce fișierul a fost transferat pe computerul tău, îl poți dezarhiva
și poți porni xo folosind următoarea comandă:

```
xo
```

Pentru a rula un XOScript, salvează programul ca fișier, adăugând sufixul -xo
(opțional). În plus, introdu numele fișierului programului tău
după comanda XOScript:

```
xo myprogram.xo
```

Când rulezi o comandă XOScript folosind fișierul programului tău ca
parametru, xo va citi și va executa fișierul programului.

{{note}}
Îți poți porni programul și trăgându-l pe pictograma xo.
{{/note}}

{{warning}}
Pe unele sisteme trebuie să acorzi în prealabil lui xo permisiunea de a încărca
biblioteci dinamice.
{{/warning}}

Tradiția cere ca primul program în orice limbaj de programare nou
să fie un fel de salut adresat lumii. În XOScript, un astfel de
program **Hello world** arată astfel:

@test598

Când acest text este salvat într-un fișier, de exemplu hello.xo, poate fi executat
astfel: .

xo hello.xo

Hello world


Poți vedea ieșirea programului în fereastra neagră de mai sus.
Pe parcursul acestui manual, aceeași reprezentare va fi folosită pentru a arăta
ieșirea.

{{note}}
Ieșire se scrie cu I majuscul.
În general, obiectele încep cu literă mare,
cu excepția cazului în care acționează ca o instanță (nu are metode
proprii, ci doar date). Aceasta reflectă convențiile clasă vs instanță
din alte limbaje de programare.
{{/note}}


## Sintaxă 

XOScript este un limbaj de programare *pur* *orientat pe obiecte*. Aceasta înseamnă
că xoscript consideră totul a fi un obiect, așa că nu există
alte *tipuri de date*. Există în esență trei acțiuni de bază
într-un program scris în XOScript: *atribuirea*, *trimiterea de mesaje*
și *răspunsul*. Schimbul de mesaje între obiecte este partea esențială a
unui program XOScript. Cele trei acțiuni de bază sunt ilustrate
mai jos:


Acțiune         | Exemplu
--------------- | --------
atribuire       |  \>\> x := 1. 
mesaje unare    | x par?.
mesaj binar     | 1 + 2.
mesaj cu cuvinte-cheie | x de-la: 0 lungime: 10.
răspuns         | <- răspuns.  


Acest capitol îți va oferi o impresie generală despre limbajul XOScript
și descrie principiile sale de bază. XOScript este un limbaj mic,
fondat pe trei acțiuni (vezi ilustrația), care se traduc în
aproximativ șase reguli gramaticale. Asta este tot ce trebuie pentru a stăpâni
limbajul.

Nu-ți face griji dacă lucrurile nu îți sunt imediat evidente: toate elementele
de construcție vor fi explorate în capitolul următor (3), iar regulile de bază vor
fi repetate. Capitolul de față servește însă în principal ca o introducere
generală în limbaj. Principiile de bază vor fi explicate pe scurt
și ilustrate prin câteva exemple relevante. Orice detalii lipsă
vor fi prezentate mai târziu.

Comentariile în XOScript sunt precedate de simbolul \#. Așadar, următoarea linie
va fi ignorată:

```
# acesta este doar un comentariu
```

## Variabile

Pentru a atribui
o variabilă folosești simbolul de declarare a variabilei: >>. Numele unei
variabile poate conține toate semnele, cu excepția: <-, :=, spații albe,
puncte, virgule, două puncte, ghilimele [' '] și paranteze ().
În plus, o variabilă nu se poate întinde pe mai multe linii. Reține
că o variabilă nu poate începe cu o cifră sau cu semnul minus.

Acestea sunt exemple de variabile valide:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dolar'].
>> +plus := Adevărat.
>> parola-utilizatorului := ['Pssst!'].
```

Variabile invalide sunt, de exemplu:


```
>> -123 := ['număr negativ'].
>> password of utilizator := ['Confidențial'].
>> password.of:utilizator := ['Confidențial'].
>> ,x := 10.
```

{{note}}
Nu trebuie să escapezi niciun caracter
(inclusiv apostrofuri, ghilimele duble, delimitatori
de text) într-un
literal de tip text, atâta timp cât acesta nu
creează ambiguitate pentru lexer.
{{/note}}

După ce o variabilă a fost declarată, poate fi folosită liber. Aceasta înseamnă
că este necesar să folosești simbolul de declarare doar prima dată
când folosești variabila (declararea).

Mai concret, nu poți începe pur și simplu să atribui o valoare
variabilei tale *(x := 2)*, deoarece trebuie mai întâi să declari variabila *(\>\>
x := 2)*. Totuși, odată declarată, ai voie să-i schimbi valoarea
fără a folosi simbolul de declarare*(\>\> x := 2. x := 3.)*.

Reține că este obligatoriu să atribui o valoare unei variabile în momentul
declarării. Spre deosebire de alte limbaje de programare, nu ai voie
să declari o variabilă fără valoare. Este esențial să legi explicit
fiecare variabilă de o valoare inițială. Cu toate acestea, poți
inițializa variabila cu obiectul **Nimic**. În acest caz, variabila poate fi
considerată goală *(\>\> x := Nimic.)*. Pe scurt, declararea unei
variabile fără valoare inițială nu este permisă. Așadar,

```
>> x.
```

este invalid și va produce un mesaj de eroare.

{{note}}
xoscript folosește domeniu de vizibilitate dinamic pentru
variabile; pentru detalii, consultă capitolul Funcții.
{{/note}}


## Literali

XOScript consideră totul a fi un obiect, adică toate numerele, textele
și fragmentele de cod. Numerele, cum ar fi 1, 2, 100, -999 și 1,234, sunt
obiecte Număr. Toate textele dintre apostrofuri sunt obiecte
Text. Toate fragmentele de cod grupate între acolade {...} sunt
obiecte Funcție.

Literal         | Obiect rădăcină | Exemplu
--------------- | --------------- | ----------
numere          | Număr           | 1,2,3... 
texte           | Text            | \['hello'\]
funcție         | Funcție         | { 1 + 2. }.
                
     
Obiecte precum numerele și textele își au întotdeauna originea într-un obiect
rădăcină. De exemplu, toate numerele derivă din obiectul **Număr**. Toate
textele derivă din **Text**, iar toate fragmentele de cod din **Funcție**. La
rândul lor, toate aceste obiecte provin din **Obiect**, care este, de fapt,
obiectul rădăcină al tuturor obiectelor.


## Mesaje

A programa în XOScript înseamnă, în esență,
a trimite mesaje obiectelor. Notația generală pentru a trimite un mesaj unui
obiect este următoarea:

```
<object> <message>
```

Pentru a afla dacă numărul **2**, de exemplu, este un număr par,
mesajul **par?** este trimis obiectului **2**:

```
2 par?
```

Răspunsul va fi **Adevărat** (din nou, un obiect). Mesajele necunoscute sunt
de obicei ignorate de obiecte, așa că nu va apărea nicio eroare. Unele obiecte (de exemplu,
numerele sau textele) răspund la un mesaj necunoscut într-un mod predefinit
(mai multe despre acest subiect mai târziu).

Un obiect poate primi trei tipuri de mesaje. 

Tip             | Număr de argumente
--------------- | -------------------
Unar            | 0      
Binar           | 1     
Cu cuvinte-cheie | 1+    


În primul rând, există **mesaje
unare**, vezi exemplul de mai sus, care nu au argumente. În al doilea rând,
există **mesaje cu cuvinte-cheie**, care au unul sau mai multe argumente,
de exemplu:

```
>> x := Număr între: 1 și: 10.
```

În acest caz, mesajul **între:și:** este trimis lui **Număr**, care
este obiectul rădăcină al tuturor numerelor. Rezultatul va fi un număr aleatoriu
între 1 și 10. În sfârșit, există **mesaje binare**, care au
un singur caracter și un singur argument:

```
2 + 3
```

Aceasta arată ca o adunare matematică, dar este de fapt doar un alt mesaj.
Mesajul **+** este trimis lui **2**, cu argumentul **3**, ceea ce va returna
răspunsul **5**. Mesajele binare pot fi scrise fără două puncte.

Mesajele binare pot fi înlănțuite:

```
>> x := 3 + 2 - 1.
```

În acest fragment, **+ 2** este trimis mai întâi obiectului **Număr** **3**, ceea ce
are ca rezultat obiectul Număr **5**, după care **-1** este trimis acestui
număr. Cititorii atenți vor observa pe bună dreptate discrepanța pe care
acest protocol o prezintă față de ordinea matematică convențională a
operatorilor. XOScript ignoră ordinea matematică în favoarea
consecvenței sistemului său de mesaje. Ca urmare, calculul:

```
2 + 3 * 5 = 25
```

nu 17.

Acest lucru este intenționat. Parantezele pot fi folosite pentru a modifica ordinea:

```
2 + (3 * 5) = 17
```

Majoritatea obiectelor se returnează pe ele însele ca rezultat ca răspuns la un anumit
mesaj. Acest lucru este util, deoarece încurajează continuarea dialogului cu acest
obiect prin trimiterea unui mesaj ulterior:

```
Ieșire scrie:
[' salut '] curăță-spații majuscule.
```

```
SALUT
```

Aici, obiectului **Text** îi sunt trimise două mesaje: **curăță-spații**, urmat
de **majuscule**.

În fragmentul următor, folosirea unei virgule este necesară pentru a indica
faptul că urmează un mesaj nou. Altfel, XOScript se va încurca.

```
Ieșire scrie: ['Hello!'], rând-nou.
```

Mai întâi, mesajul **scrie:** este trimis simbolului creionului, urmat de
**rând-nou**. Fără virgulă, XOScript ar crede că vrei să trimiți
**rând-nou** **textului** **Hello!**, un exercițiu inutil.

Ordinea de procesare a mesajelor este următoarea: de la stânga la dreapta;
se începe cu mesajele din paranteze, urmate de mesajele unare. Apoi
mesajele binare și, la final, mesajele cu cuvinte-cheie. Vezi exemplul
de mai jos:

```
Ieșire scrie: 0.5 rotunjește + (2 - 1), rând-nou.
```

XOScript citește întotdeauna de la stânga la dreapta: mai întâi, mesajul **scrie:**
este trimis lui Ieșire și este urmat de mesajul **rând-nou**. În cadrul
argumentului însuși, XOScript citește de la stânga la dreapta, deci mai întâi **0.5 rotunjește**,
apoi **+**.

{{note}}
Mesajul rând-nou adaugă un caracter de linie nouă la text.
Numele acestui mesaj este inspirat de sistemele telegrafice.
Mesajele din sistemele telegrafice
foloseau adesea cuvântul STOP pentru a marca sfârșitul unei propoziții
(deoarece punctuația era nesigură sau costisitoare).
{{/note}}

Mai mult, **rotunjește** are prioritate față de **+**, deoarece este un
**mesaj unar**. Datorită parantezelor, **2 - 1** este calculat
mai întâi, după care **1** este adunat la rezultatul lui **0.5 rotunjește** (1).

Întregul proces va da rezultatul **2**, care este și răspunsul
scris. După virgulă urmează mesajul rând-nou, care mută cursorul
pe o linie nouă. Desigur, cel mai bun mod de a înțelege pe deplin ordinea
de execuție a programelor XOScript este prin practică.

Merită menționat că în XOScript, spre deosebire de multe alte limbaje
de programare, spațiile albe sunt o parte fundamentală a sintaxei. În
special în cazul mesajelor binare, spațiile albe pot provoca o oarecare
confuzie. Folosește întotdeauna un spațiu alb după un mesaj binar. Nu poți
lipi direct un număr de mesaj, de exemplu: 

```
3 + 2
```

diferit de 

```
3 +2
```

Primul exemplu (**3 + 2**) trimite
mesajul **+** numărului **3**, cu argumentul numărul **2**.
Rezultatul, în acest caz, va fi **5**. În al doilea exemplu (**3 +2**),
mesajul unar **+2** este trimis numărului **3**. În funcție de
context, aceasta poate produce un rezultat foarte diferit.

## Metode inexistente

Trimiterea unui mesaj către un obiect invocă funcția care a fost
atașată acestui obiect sub numele acelui mesaj. Dacă trimiți un mesaj
care nu este înțeles, obiectul care îl primește îți va ignora mesajul
și va returna în schimb o referință la sine pentru continuarea comunicării.
Aceasta se numește transmitere tolerantă a mesajelor.

Exemplu:

```
Ieșire scrie: Obiect blah, rând-nou.
```

Aceasta nu va produce o eroare. Va afișa pur și simplu textul **Obiect**.


## Controlul fluxului

În XOScript nu este nevoie de reguli gramaticale separate pentru *bucle* și
*condiții if*. O instrucțiune if este doar un simplu mesaj **adevărat:** sau **fals:**
trimis fie unui obiect **Adevărat**, fie unui obiect **Fals**:

```
2 par? adevărat: {
	Ieșire scrie: ['Doi este un număr par'], rând-nou.
}.
```
În exemplul anterior, mesajul **adevărat:** este trimis lui **Adevărat** (răspunsul
la întrebarea: este 2 un număr par?). Ca argument este trimis împreună un
fragment suplimentar de cod: un obiect **Funcție**. Această funcție scrie pe
ecran că 2 este, într-adevăr, un număr par.

Nu este nevoie nici de reguli de scriere separate pentru o *buclă*. Pentru a
executa un fragment de cod de trei ori, trimite pur și simplu **\*** cu argumentul
**3** acelei **Funcții**:

@test5

În acest fragment de cod, **i** este indexul. Așadar, prima dată când Funcția
este executată, **i** este egal cu 0, data următoare când este executată, **i** = 1 și
așa mai departe.

Să considerăm un alt exemplu. Când trebuie afișat un tabel de conversie
din *kJ* (kilojouli) în *kcal* (kilocalorii) în pași de 100,
vezi mai jos notația corectă:

@test599

Aici, numărul liniei curente este transmis parametrului
**:line**. La începutul unei funcții sunt definiți parametrii
funcției. Parametrii nefolosiți rămân goi (**Nimic**). Parametrii sunt
plasați întotdeauna la începutul funcției, imediat după acolada
de deschidere, și sunt precedați de două puncte.

Mesajul **cât-timp:** este o combinație între o *buclă* și o *condiție*.
Două funcții pot fi legate folosind mesajul **cât-timp:**. Funcția care îl primește
va continua să ruleze până când funcția de după două puncte va da un rezultat
negativ. Exemplu:

@test600

În fragmentul de cod ilustrat mai sus, **1** este adunat la **x** atâta timp
cât **x** este mai mic decât **5**. Când acest lucru nu mai este valabil, a doua
funcție va răspunde cu **Fals** și, în consecință, execuția
primei funcții se va încheia. Reține că **x** a fost definit în afara
funcției și este o variabilă globală. Pentru a afla mai multe despre regulile de domeniu de vizibilitate,
consultă capitolul despre Funcții.

## Interpolarea textelor

Lista *kJ/kcal* ar putea fi făcută mai
prezentabilă. Ideal ar fi ca lista să arate astfel:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Când transformi ieșirea dorită într-un șablon, notația sa
ar putea fi:

```
number1 kJ ➞ number2 kcal
```

Aceasta înseamnă că **number1** reprezintă valoarea în kJ, iar **number2** valoarea
în kcal. Așa funcționează interpolarea textelor în XOScript.
Nu sunt necesare reguli gramaticale separate pentru aceasta în XOScript. Trimite pur și simplu
textului cuvântul care trebuie înlocuit, cu textul de înlocuire ca
argument:

```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

Rezultatul:

```
100 kj ➞ 23.9 kcal
```

Această regulă de înlocuire funcționează pentru fiecare mesaj nedefinit primit
de un obiect **text**. Fiecare mesaj care nu este recunoscut de obiectul
**text** va fi interpretat după cum urmează: *înlocuiește textul mesajului
cu textul din argumentul mesajului.* Poți adapta
programul după cum urmează:


@test601


Pentru a evita confuzia privind mesajele care pot sau nu pot fi folosite ca
înlocuitori, cel mai bine este să introduci un marcaj de șablon precum &lt; &gt;
pentru segmentele de text din șablon care
trebuie înlocuite.

## Valori returnate

Pentru a răspunde la un mesaj se folosește săgeata de returnare
(*<-*). Exemplul următor ilustrează cum se creează o sarcină
care calculează un procent:

@test602

După ce sarcina a fost definită și atribuită variabilei **percentage**,
mesajul **aplică:și:** este trimis cu argumentele **100** și **7**.

Aceasta va executa sarcina aplicată lui **100** și **7**, adică 7% din 100.
Cu ajutorul săgeții de returnare, răspunsul este returnat din sarcină înapoi
în programul principal.

## Extindere

Deși acest cod este valid, are un dezavantaj,
deoarece ordinea argumentelor trebuie ținută minte. Așadar, de ce să nu
îl scriem astfel: *7 percent of: 100 *? Ar arăta mult mai
*natural*. Pentru a face acest lucru posibil, trebuie să adaptăm obiectul părinte al lui
**7**, care este obiectul **Număr**, astfel încât să înțeleagă
mesajul **percent of:**. Acest lucru se poate realiza trimițând **la:execută:**
obiectului Număr, astfel:

@test603

Deoarece procentul este, în acest caz, numărul însuși, ne referim la sine,
cuvântul-cheie *sine*. Pe scurt, simbolul sine înseamnă: *trimite acest
mesaj mie însumi*.

# Obiecte

{{messages}}

Pe lângă ajustarea și extinderea obiectelor existente, poți crea și
obiecte noi, pur și simplu trimițând mesajul **nou**. Să presupunem că
ai dori să creezi un obiect factură care impune o secvență
de numerotare; în acest caz, vei avea mai întâi nevoie de un obiect factură.

Știind că fiecare obiect derivă dintr-un alt obiect, care, la rândul său,
provine în cele din urmă din obiectul rădăcină al tuturor obiectelor, numit Obiect,
trebuie făcută o alegere privind obiectul pe care se va baza
noul tău obiect. Noul tău obiect moștenește toate proprietățile
obiectului pe care se bazează, adică ale obiectului căruia i-a fost trimis
inițial mesajul **nou**.

În acest exemplu este preferat un obiect destul de neutru, unul fără prea
multe proprietăți moștenite. Alegerea este ușoară, deoarece în acest
caz noul obiect se poate baza chiar pe obiectul rădăcină, adică
**Obiect**. Notația sistemului de facturare propus va fi atunci
următoarea:

@test604

Numărul curent al facturii este stocat în obiect, de aceea în fața lui
este plasat cuvântul-cheie **propriu**. Aceasta se numește *proprietate*;
mai multe detalii vor urma.

Unele firme preferă ca anul să fie inclus în numerele
facturilor. În acest caz, poți crea un nou obiect factură bazat pe un
obiect factură anterior, dar care oferă utilizatorului posibilitatea de
a introduce un an anume:

@test605

Nu este nevoie să scrii din nou implementarea mesajului **număr**,
deoarece este moștenită de la **obiectul factură** scris
anterior; în consecință, codul vechi poate fi reutilizat. XOScript nu are concepte
precum clasele și alte concepte înrudite. Aceasta înseamnă că obiectele pot
moșteni doar de la alte obiecte, ceea ce se numește și *moștenire
prototipală*.

Să revenim acum la proprietăți. Proprietățile obiectelor pot fi accesate doar
*din interiorul ierarhiei obiectului*, deci aceste proprietăți
nu pot fi văzute de alte obiecte.

Spre deosebire de alte limbaje de programare, toate proprietățile obiectelor sunt
vizibile exclusiv pentru obiectul care a creat proprietatea și pentru
obiectele derivate. 

O tehnică folosită frecvent este utilizarea unui obiect ca un fel de *plan*,
cum este, de exemplu, cazul facturilor discutate mai devreme.
Un alt exemplu bun este **Point**. Să spunem că creezi un
program care face calcule folosind puncte pe o hartă. Poți
dezvolta obiectul **Point**, care conține proprietățile unei
coordonate x și ale unei coordonate y, puse la dispoziția
lumii exterioare prin mesaje:

@test606

Mesajul **=** compară cele două puncte folosind mesajul **și:**.
Prima comparație are ca rezultat un **Adevărat** sau un **Fals**. Acestea sunt obiecte
booleene. Când trimiți mesajul **și:** unui obiect Adevărat, iar
obiectul argument de după două puncte este de asemenea **Adevărat**, vei
primi din nou ca răspuns **Adevărat**. Când oricare dintre ele este **Fals**, vei
primi răspunsul **Fals**. Reține că un punct nu poate citi coordonatele
celuilalt. Este necesar să trimiți un mesaj celuilalt punct pentru a cere
aceste date: **x-coordinate** și **y-coordinate**. La urma urmei, după cum s-a
explicat deja, proprietățile pot fi obținute doar din interiorul
familiei obiectului. 

Reține că mesajul **=** este folosit aici pentru a efectua comparația
punctelor. La fel de bine ar fi putut fi folosit un alt mesaj, cum ar fi:
**is:** sau **equal:**, însă reutilizarea caracterului **=** a părut
potrivită în acest caz.

## Moștenire

Poți reutiliza cod scris anterior pentru a crea o ierarhie
de obiecte. De exemplu:

```
>> Animal := Obiect nou.
>> Câine := Animal nou.
>> Pudel := Câine nou.
```

În acest caz, **Dog** moștenește tot comportamentul și toate proprietățile
lui **Animal**, iar obiectul **Animal**, la rândul său, moștenește tot comportamentul lui
**Obiect**, obiectul rădăcină al tuturor obiectelor.


## Suprascriere


În exemplul următor este creat un nou tip de listă:
**Combination**, în care fiecare element este garantat unic.
Funcțiile listei sunt reutilizate prin moștenire:

@test607

Observă cum al doilea **red** este exclus din listă.

Uneori poate fi necesar să suprascrii un comportament al unui obiect.
De exemplu, atunci când se adună numere și trebuie luate în considerare
unitățile de măsură. În exemplul următor este creat obiectul **Size**.
Acest obiect returnează un număr care, la adunare, ține
cont de unitatea numărului care se adună. Obiectul **Număr**
verifică dacă este vorba de *inches* sau *foot*. Codul
ar putea arăta astfel:

@test608

## Recursivitate

În exemplul anterior, **semnul** plus este suprascris. Reține
că în cele din urmă adunarea finală trebuie totuși efectuată, ceea ce, de fapt,
are loc pe linia următoare:

```
>> răspunsul := sine + (număr x factor).
```

Cum înțelege însă XOScript că acest **semn** plus se referă la
logica originală a adunării?** De exemplu, o altă interpretare
ar putea fi că XOScript va trimite în mod repetat același mesaj aceluiași
obiect, ceea ce, la rândul său, ar duce la o **buclă infinită**. Evident,
aceasta nu este intenția. De îndată ce trimiți unui obiect un mesaj
care ar executa exact același cod, XOScript își va da seama,
în acest caz, că se are în vedere mesajul subiacent, suprascris. Astfel,
programul tău va fi protejat automat împotriva acestui tip de bucle
infinite. Totuși, atunci când chiar îți propui să rulezi aceeași funcție din
funcția curentă, va fi necesar să trimiți mai întâi mesajul
**recursiv**. În acest caz, rezultatul va fi o buclă
infinită. Există însă aplicații utile pentru sarcinile recursive; de
exemplu, să presupunem că vrei să calculezi factorialul unui
număr dat. În acest caz, adaugă pur și simplu mesajul **factorial** la
Număr:

@test609

Aceasta necesită recursivitate. De fapt, sarcina legată de
mesajul **factorial** trebuie executată din nou în interiorul acelei funcții.
Așadar, este necesar să invoci funcția factorial din interiorul
funcției factorial însăși. Ca regulă, XOScript va împiedica această rutină,
din cauza riscului de a ajunge într-o buclă infinită. Din acest motiv,
este esențial să precezi mesajul de cuvântul **recursiv**. Acest
lucru se face pentru ca XOScript să știe că
intenția ta este să execuți aceeași sarcină și că nu ai făcut o greșeală.

## Obiecte asemănătoare claselor

Deși xoscript nu oferă clase, imitarea comportamentului
asemănător claselor este banală. Suprascrie pur și simplu mesajul nou.

```
>> Animal := Obiect nou.
Animal la: ['nou'] execută: {
	<- sine nou inițializează.
}.

Animal la: ['inițializează'] execută: {
	propriu sunet := ['?'].
	propriu picioare  := 4.
}.
```

În fragmentul de cod de mai sus, creăm un obiect numit Animal.
Acest obiect servește drept *plan* pentru tot felul de animale,
precum câini și pisici. Obiectul părinte Animal este scris
cu A majuscul pentru a arăta că este un obiect asemănător unei clase.
Apoi suprascriem mesajul nou scriind propria noastră metodă nou.
În acest caz, ea trimite un mesaj nou lui sine, urmat de mesajul
inițializează. Deoarece xoscript blochează implicit recursivitatea, aceasta nu va provoca
o buclă infinită. În schimb, va trimite mesajul nou obiectului
părinte (Obiect), rezultând o nouă instanță a lui Animal. Astfel creăm
un obiect nou, bazat pe același obiect pentru care am creat metoda nou.
Acest lucru este perfect valid. Acum trimitem și mesajul inițializează, care asigură
că obiectul Animal are valori implicite pentru proprietățile sale. Implicit,
un animal are 4 picioare, iar sunetul este necunoscut (de aici semnul întrebării).
Pentru a crea o nouă instanță a lui Animal, am putea spune pur și simplu:

```
>> a := Animal nou.
```

Acum obținem o nouă instanță a lui Animal cu 4 picioare, sunet necunoscut și
o metodă inițializează. La fel ca în alte limbaje OOP, putem și
extinde Animal:

```
>> Câine := Animal nou.
Câine la: ['inițializează'] execută: {
	sine inițializează.
	propriu sunet := ['latră'].
}.
```

Putem testa acest lucru ușor adăugând o metodă text:

```
Animal la: ['text'] execută: {
	<- propriu picioare text + propriu sunet.
}.
```

Să punem totul laolaltă:

@test13


Crearea unui obiect care se află într-o stare inițială dată reprezintă o
problemă frecventă. Să presupunem că trebuie creat un obiect **Rectangle**
pentru a calcula perimetrul și aria. O notație posibilă ar fi:


```
>> Dreptunghi := Obiect nou.

Dreptunghi la: ['arie'] execută: {
	<- propriu lungime * propriu lățime.
}.
```

Evident, setarea unei lungimi și a unei lățimi este o condiție prealabilă. În acest
scop pot fi adăugate mesajele **lungime:** și **width:**:


```
Dreptunghi la: ['length:'] execută: { :lungime
	propriu lungime := lungime.
}.

Dreptunghi la: ['width:'] execută: { :lățime
	propriu lățime := lățime.
}.

```

Acest dreptunghi poate fi apoi utilizat astfel:


```
>> dreptunghi := Dreptunghi nou length: 2, width: 3.
Ieșire scrie: dreptunghi arie.
```

Totuși, dacă setările inițiale pentru lungime și lățime sunt omise,
va apărea un mesaj de eroare:

```
>> dreptunghi := Dreptunghi nou.
Ieșire scrie: dreptunghi arie.
```

va produce următoarea eroare:

```
Cheia nu a fost găsită: lungime
```

Pentru a preveni acest lucru, este de preferat ca un dreptunghi să aibă
întotdeauna o lungime și o lățime inițiale, de exemplu 0. Așadar, în acest
caz, este necesar să **suprascrii** mesajul **nou**.

@test610

Dacă suprascriem mesajul nou, imităm de fapt o **clasă**.

Lumea XOScript este plină de o diversitate de obiecte, care sunt
disponibile programului tău chiar de la început. În capitolele următoare
vor fi discutate toate aceste obiecte de bază.

## Instantanee

Poți salva un obiect (împreună cu starea sa curentă) pe disc cu:

```
obiectulmeu save-as: ['saved.bin'].
```

Pentru a reîncărca obiectul de pe disc:

```
>> obiectulmeu := Obiect load-from: ['saved.bin'].
```

Instantaneele pot fi folosite pentru a salva o anumită stare sau pentru a îmbunătăți performanța.
Încărcarea unui instantaneu evită analiza lexicală, analiza sintactică și configurarea aplicației.
De asemenea, în viitor ar putea fi introduse beneficii suplimentare de performanță
cu ajutorul instantaneelor, precum optimizarea anumitor tipare sau detectarea și
optimizarea căilor fierbinți.

{{warning}}
Instantaneele sunt o funcționalitate experimentală; nu le folosi în producție.
Pentru a activa funcționalitățile experimentale, compilează cu -D EXPERIMENTS.
{{/warning}}


@test712

# Obiectul Nimic

{{messages}}

Obiectul Nimic
reprezintă vidul sau, mai bine zis, absența informației.
Ocazional, vei primi acest obiect ca răspuns la un mesaj, în
cazul în care rezultatul este **nimic**. Cea mai esențială întrebare
pe care i-o poți pune obiectului **Nimic** este: **Nimic?**.
Răspunsul va fi întotdeauna **Adevărat**.

```
Ieșire scrie: Nimic Nimic?.
```

rezultat:

```
Adevărat
```

Orice alt obiect în afară de **Nimic** va răspunde cu **Fals**.
Fragmentul de cod de mai sus poate părea puțin filozofic, însă obiectul **Nimic**
are cu siguranță aplicații extrem de practice. De exemplu,
vei primi obiectul Nimic ca răspuns dacă ceri un
element al unei liste care nu există. Ai putea folosi obiectul Nimic și
atunci când vrei să declari o variabilă, dar nu vrei încă să specifici o
valoare. În schimb, îi **atribui** pur și simplu valoarea specială **Nimic**. În
XOScript nu este permisă declararea unei variabile fără valoare, cum ar fi:


```
>> valoare.
```

În schimb, trebuie să scrii următoarele:

```
>> valoare := Nimic.
```

@api_None_base

# Valori booleene

{{messages}}

Spre deosebire de majoritatea limbajelor de programare populare în momentul scrierii,
XOScript oferă un singur obiect Adevărat și un singur obiect
Fals. Mai precis, de fiecare dată când scrii **Adevărat**, aceasta nu înseamnă
că a fost creat un obiect nou. În schimb, folosești întotdeauna o referință. Aceasta
înseamnă că atunci când scrii următoarele:

\>\> x := Adevărat.

**x** se referă la obiectul **Adevărat**. Codul condițional și buclele
verifică și ele această referință. În XOScript, semnificația lui **Adevărat** și **Fals**
nu este fixă. De fapt, un program XOScript este destul de zdruncinat de o
instrucțiune ca aceasta:

Adevărat := Fals.

Rezultatul unor astfel de acțiuni este nedefinit, însă rămâne o acțiune
validă și, prin urmare, permisă formal. În plus, există un obiect
Boolean, care este obiectul rădăcină atât pentru **Adevărat**, cât și pentru **Fals**, deoarece ambele
sunt derivate din acest obiect rădăcină. Obiectul Boolean însuși, însă,
nu are nicio aplicație practică.

## Capcane

Ai grijă când folosești **și:** și **sau:**

```
Ieșire scrie: (Fals or: Adevărat or: Adevărat), rând-nou.
Ieșire scrie: (Fals sau: Adevărat, sau: Adevărat), rând-nou.
```

Produce

```
Fals
Adevărat
```
deoarece mesajul **sau:** primește doar 1 argument. Primul mesaj
trimite **sau:sau:** lui Fals, care nu există, așa că obiectul ignoră
mesajul și se returnează pe sine (Fals). Pe de altă parte, a doua linie
trimite **sau:** urmat de un alt **sau:** (folosind un simbol de înlănțuire, adică o virgulă: ,).


@api_Boolean_base

# Numere

{{messages}}

De fiecare dată când scrii un număr, de exemplu 9, -10 sau 3,12, în
culise XOScript va converti aceste numere într-un obiect **Număr**. Poți
trimite mesaje acestui obiect Număr sau poți atribui numărul
unei variabile și trimite mesaje ulterior:

```
10 par?

>> zecar := 10.
zecar par?

```

Ambele notații sunt valide. Obiectul Număr răspunde la următoarele
mesaje...

Majoritatea acestor mesaje se explică de la sine și îți permit să execuți
operații matematice sau comparații.

{{note}}
Reține că poți folosi ≤ ≥ ≠ × și ÷ în locul echivalentelor lor ASCII.
Aceasta este o chestiune de preferință.
{{/note}}

Diferența dintre mesajele matematice binare (+) și
variantele lor cu cuvinte-cheie (adaugă:) este că primele returnează
un număr nou, care este rezultatul operației, în timp ce în cazul
celor din urmă obiectul însuși este modificat. Acest lucru este ilustrat în
exemplul următor:

@test597

În exemplul de mai sus, b = 4 și a = 3. Cu **adaugă: 2** valoarea
lui a crește cu 2, în timp ce **+ 3** creează un număr nou, egal
cu a + 3. Același lucru este valabil și pentru alte operații matematice, de exemplu
înmulțirile. Folosind simbolul înmulțirii, vei primi un
obiect nou ca răspuns. Dacă folosești mesajul **înmulțește-cu:**,
vei înmulți numărul însuși.

Cu mesajul **între:și:**, de exemplu în: **Număr
între: X și: Y**, vei obține un număr între X și Y. În acest
mod poate fi generat orice număr aleatoriu:

```
>> a := Număr între: 1 și: 10.
Ieșire scrie: a, rând-nou.
```

Începând cu versiunea 1.4, generatorul încorporat de numere aleatorii din xoscript este,
după cunoștințele noastre, sigur din punct de vedere criptografic.

Poți atașa un **calificativ** unui număr, de exemplu **6
apples**. Fiecare mesaj care nu este recunoscut de un
număr va fi considerat un calificativ. Poți obține calificativul unui
număr prin intermediul mesajului calificativ:

Un calificativ este, în esență, un obiect Text stocat împreună cu obiectul
Număr. Calificativul este afișat și după număr la o
atribuire **scrie:**. Calificativele ar putea fi folosite, de exemplu, pentru a aduna sume
în monede diferite. La adunarea sumelor, poți cere
calificativele. Exemplul de program următor ilustrează acest
principiu folosind un calculator de monede istorice (deoarece cursul
de schimb rămâne destul de stabil!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Texte

{{messages}}

De fiecare dată când un text este plasat între **paranteze drepte și apostrofuri** ['...'],
XOScript va crea pentru tine un nou obiect text. Asigură-te însă
că folosești ghilimelele corecte. Ghilimeaua de la
începutul textului diferă de cea de la sfârșit (acest lucru îți permite
să folosești apostroful fără a fi nevoie să-l escapezi).

## UTF8

Textele din xoscript conțin de obicei text codificat utf8. Deși
din punct de vedere tehnic este posibil să ai conținut binar sau non-utf8 într-un
text, se recomandă folosirea blob-urilor pentru aceasta. Blob-urile sunt
furnizate de pluginul de server (vezi capitolul ffi).
În general, blob-urile/ffi sunt furnizate
pe bază de plugin/platformă, deoarece sunt legate de platformă
și de arhitectură (ffi/blob-uri). Nucleul limbajului de scripting încearcă să
rămână cât mai independent de platformă posibil.

## Conversie de tip

Poți crea o copie a oricărui obiect
cu un tip diferit folosind următoarele mesaje:

Mesaj   | Rezultat
------- | ------
număr   | Convertește într-un număr
text    | Convertește într-un text
boolean | Convertește într-o valoare booleană
  
Se **aplică** următoarele reguli:

mesaj    | Nimic     | Boolean            | Număr                 | Text      | Altele
-------- | --------- | --------           | --------              | --------  | --------
boolean  | Fals      | n/a                | 0→Fals altfel→Adevărat | Adevărat | De obicei Adevărat
număr    | 0         | Fals→0 Adevărat→1  | n/a                   | ['n']→n   | De obicei 1
text     | ['Nimic'] | ['Fals']/['Adevărat'] | ['n']              | n/a       | Depinde

## Copiere

Valorile în XOScript sunt transmise întotdeauna **prin referință**. În alte limbaje
depinde de tipul valorii; în XOScript există o singură modalitate,
prin referință. XOScript nu face niciodată o copie a unei valori. Pentru a copia un obiect,
trebuie să trimiți mesajul **copiază**. 

@test611

Aici te-ai fi putut aștepta ca rezultatul să fie Dolly, în loc
de Donny. Totuși, nu este cazul, deoarece ambele nume se referă la același
obiect. Când lucrezi cu o buclă, se întâmplă ceva asemănător:

@test612

De fapt, XOScript folosește **întotdeauna** referințe, așa că la **:quantity**
bucla ilustrată mai sus indică și ea referința la elementul
din listă.

Pentru a copia un obiect, trebuie să specifici această acțiune
**explicit**:

@test613

Trimițând mesajul unar **copiază** unui text, obiectul
returnează o copie a aceluiași obiect text. Este posibil să copiezi în același mod obiecte
Număr, obiecte booleene, liste și dicționare.

Poți defini și propria implementare a copierii; aceasta este chiar o
necesitate dacă îți creezi propriile obiecte. Implementarea
implicită a copierii pentru o listă face o copie superficială: creează o
listă nouă cu aceleași elemente.

@test614

În acest caz, 4 este adăugat doar la copie.
Totuși, deoarece copia este superficială, obiectele din ambele liste
sunt aceleași.

@test615

Așadar, dacă adăugăm 2 la fiecare nume din copie, lista
originală este și ea afectată.

Pentru a remedia acest lucru, trebuie să facem o **copie profundă**. O astfel de operație de copiere
pentru o listă ar putea fi alcătuită astfel:

@test616

De asemenea, observă mesajul recursiv; acest mesaj trebuie
trimis înaintea mesajului copiază.

Este esențial să reții că, deși o copie a unui obiect
are adesea același aspect ca originalul, ea nu va fi, de fapt,
niciodată același obiect. Obiectul rădăcină definește un mesaj **equal:**,
care poate fi folosit pentru a compara identitatea obiectelor. Uită-te la
exemplul următor:

@test617

## Conversie implicită

XOScript folosește **conversia implicită** pentru a converti obiecte. Pentru a afișa o
listă pe ecran, XOScript va trimite, de exemplu, intern mesajul
*text* listei. Acest lucru se poate dovedi foarte util în
cazul în care vrei să afișezi o listă ca listă separată prin virgule.
Mesajul *text* poate fi suprascris: 

@test620

@api_String_base
@api_Format_base


## Texte pentru server

Următoarele funcționalități Text sunt adăugate de
pluginul Server.

@api_String_server

# Funcții

{{messages}}

Poți grupa cod între { și }; acesta devine astfel o funcție.
În xoscript folosim uneori și termenul sarcină sau pur și simplu
bloc de cod.

Poți rula o funcție trimițându-i mesajul *pornește*.


```
{ Ieșire scrie: 123, rând-nou. } pornește.
```

Dacă funcția ta primește argumente, folosește **aplică:**.

```
{ :a Ieșire scrie: a, rând-nou. } aplică: a.
```

Vezi și exemplele de mai jos.
Datorită arhitecturii simple, o funcție poate avea doar
un singur punct de returnare. Pentru a evita costurile suplimentare sau imbricarea excesivă a
condițiilor, poți folosi o procedură (ceea ce este același lucru cu folosirea
semnului înmulțirii cu argumentul 1):

```
{
  (a = 1) adevărat: { x := 1. }, întrerupe.
  (a = 2) adevărat: { x := 2. }, întrerupe.
} procedură.
```

Astfel, (a = 2) nu va fi evaluat dacă a = 1.
De asemenea, în acest fel nu ai nevoie de mesaje adevărat imbricate.
De fiecare dată când te trezești imbricând condiții, gândește-te
la mesajul procedură. S-ar putea să facă codul
mai ușor de citit.


Iată o capcană importantă:

```
{
	Fals fals: {
		Ieșire scrie: ['Încheie bucla.'].
	}, întrerupe.
	
	Ieșire scrie: ['Nu mă afișa.'].

} procedură.

```

În acest caz, textul 'Dont show me' va fi afișat,
deoarece **întrerupe** este trimis lui Fals. Dacă vrei să execuți
o întrerupere, aceasta trebuie trimisă ca mesaj lui **Adevărat**.
 

```
{
	Fals nu adevărat: {
		Ieșire scrie: ['Încheie bucla.'].
	}, întrerupe.
	
	Ieșire scrie: ['Nu mă afișa.'].

} procedură.

```

Va funcționa conform așteptărilor.

## Excepții

Excepțiile pot fi tratate astfel:

```
{ Sarcină 1 } prinde: { Sarcină 2 }, pornește.
```

Poți provoca și intenționat o eroare în programul tău și,
făcând acest lucru, poți activa blocul de tratare. Acest lucru se face trimițând
mesajul **eroare:** sarcinii curente, așa cum se arată în
ilustrația următoare:

```
{
această-sarcină eroare: ['Ups!'].
} prinde: { :greșeală
Ieșire scrie: greșeală.
}, pornește.
```

## Injectarea valorilor

XOScript oferă sarcinilor posibilitatea de a injecta valori. Uită-te acum
la sarcina de mai jos:

```
>> trimitere := {
	Buletin către: propriu recipient.
}.
trimitere setează: ['recipient']
valoare: ['info@recipient.org'].
trimitere pornește.
```


Această ilustrație prezintă o sarcină imaginară, care trimite un buletin informativ
la o adresă de email sau unui **recipient** (destinatar). Acest destinatar poate fi injectat
în sarcină din exterior, înainte ca sarcina să fie pornită, trimițând
sarcinii mesajul **setează:valoare:**. Astfel, valoarea lui
**recipient** este presetată în sarcină. Această valoare poate fi și modificată,
iar sarcina poate fi apoi rulată din nou. Aceasta este o metodă utilă atunci când folosești
obiecte Task.

## Funcții goale

Sarcinile goale nu sunt permise. Teoretic, o sarcină goală ar arăta
astfel: **{}**, însă XOScript consideră aceasta o eroare de limbaj. Dacă
vrei să declari o sarcină goală, poți folosi obiectul Nimic:

```
>> sarcină := Nimic.
```

Deși aceasta nu este o sarcină reală, ci un obiect Nimic, i se poate
totuși trimite un mesaj pornește:

```
>> răspunsul := sarcină pornește.
```

De fapt, acesta este același lucru cu:

```
>> răspunsul := Nimic pornește.
```

Deoarece obiectul **Nimic** nu recunoaște mesajul **pornește**, el
se va returna pe sine ca răspuns, iar răspunsul rămâne din nou **Nimic**.
Așadar, nu este nevoie de o sarcină goală. Datorită designului elegant
al limbajului de programare XOScript, poți folosi pur și simplu obiectul Nimic
în acest scop.

## Domeniu de vizibilitate dinamic

Când o Funcție are nevoie de o variabilă, dar nu o poate găsi,
va verifica variabilele Funcției care a **apelat-o**
și va continua să verifice în sus pe lanțul de Funcții.
Acest proces de căutare continuă până când variabila este găsită.
Dacă variabila tot nu este găsită, va apărea un mesaj de eroare. Această metodă de căutare a
unei variabile se numește **Domeniu de vizibilitate dinamic**.

Pentru a ilustra acest principiu:

@test618

@api_Code_base

# Obiectul rădăcină

{{messages}}

Obiectul numit **Obiect** este obiectul rădăcină al tuturor obiectelor din
XOScript și oferă funcționalitățile de bază ale limbajului. 

Mesajul trimis cel mai frecvent
este **la:execută:**, care extinde funcționalitățile unui obiect. Acest
mesaj este primit de obiectul rădăcină, care leagă în consecință
sarcina specificată de mesaj și, făcând acest lucru, extinde obiectul
derivat.

## Metode universale

În mod normal, dacă trimiți un mesaj care nu corespunde unei
metode din obiect, acesta este ignorat. Poți însă specifica
așa-numitele **metode magice** sau metode **universale** (catch-all), care vor
fi invocate dacă mesajul nu este înțeles de obiect.

Sunt disponibile 4 metode universale. Fiecare mesaj corespunde
unui anumit număr de argumente.

Mesaj universal      | Număr de argumente
-------------------- | -------------------
răspunde:            | 0
răspunde:și:         | 1
răspunde:și:și:      | 2
răspunde:și:și:și:   | 3


@test619

## Mesaje programatice

În loc să fie trimis direct unui obiect, un mesaj poate fi
trimis și prin intermediul unei variabile. Pentru aceasta folosești mesajul
**mesaj:argumente:**. 

@test396

@api_Object_base

# Liste

{{messages}}

XOScript cunoaște două tipuri de colecții: *liste* și *dicționare*.
**Listele** sunt enumerări de obiecte într-o *ordine fixă*. Dicționarele nu au
ordine; în schimb, seamănă cu o legendă formată dintr-o cheie (sau un termen) și
valoarea corespunzătoare. Listele sunt comparabile cu array-urile (PHP, Java, C)
și cu listele (Python). Dicționarele sunt comparabile cu array-urile asociative (PHP) sau
cu dicționarele (Python) din alte limbaje de programare. Pentru a crea
o Listă nouă, scrie:

```
>> fibonacci := Listă nou.
```

Această listă goală poate fi umplută folosind **adaugă-la-sfârșit:** :

```
fibonacci adaugă-la-sfârșit: 0.
fibonacci adaugă-la-sfârșit: 1.
fibonacci adaugă-la-sfârșit: 1.
fibonacci adaugă-la-sfârșit: 2.
fibonacci adaugă-la-sfârșit: 3.
fibonacci adaugă-la-sfârșit: 5.
fibonacci adaugă-la-sfârșit: 8.
fibonacci adaugă-la-sfârșit: 13.
```

Dacă scriem lista pe ecran:

```
Ieșire scrie: fibonacci, rând-nou.
```

Vom vedea:

```
Listă ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

În loc de adaugă-la-sfârșit poți folosi și ; pentru a adăuga elemente într-o listă:


```
>> fibonacci := Listă nou ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Punctele și virgulă (;) sunt toate mesaje binare care pun o
valoare în listă.

## Înlănțuire

Să presupunem că ai o listă precum:

```
>> x := Listă nou ; 1 ; 2 ; 3.
```

Dacă ai dori să ștergi primul și ultimul element, atunci mesajul
tău ar fi:

```
x scoate-primul scoate-ultimul.
```

Din păcate, notația anterioară nu va funcționa corect.
Mesajul **scoate-primul** returnează primul element al listei, care,
la rândul său, devine receptorul mesajului **scoate-ultimul**. Așadar,
mesajul **scoate-ultimul** nu este trimis lui **x**, ci lui 2. O
soluție posibilă la această problemă ar fi crearea a două propoziții
separate, cum ar fi: 

```
x scoate-primul.
x scoate-ultimul.
```

Totuși, acest lucru este destul de nepractic, în special când trebuie să
ștergi mai mult de două elemente. De aceea, XOScript oferă o
structură alternativă de mesaje pentru astfel de situații. În
structurile de mesaje **alternative**, răspunsurile obiectelor sunt ignorate
și primești înapoi ca răspuns, de fiecare dată, obiectul receptor.
O structură de mesaje **alternativă** este inițiată trimițând
mesajul **fă** unui obiect, iar structura de mesaje **alternativă**
poate fi încheiată trimițând mesajul **gata**. În
exemplul ilustrat, aceasta ar putea fi aplicată astfel:

```
>> x := Listă nou ; 1 ; 2 ; 3.
x fă scoate-primul scoate-ultimul gata.
```

@api_List_collections

# Dicționare

{{messages}}

**Atât Lista, cât și Dicționarul sunt colecții. Totuși, spre deosebire de o
listă, un dicționar **nu are** ordine. O altă distincție între cele două
este că un dicționar este format din perechi de obiecte. Un obiect acționează ca intrare (sau
cuvânt-cheie) pentru a căuta celălalt obiect. Un bun exemplu de
listă este o listă de prețuri, cum ar fi:


```
>> meniu := Dicționar nou
	pune: ['£5'] la: ['plăcintă cu mere'],
	pune: ['£6'] la: ['prăjitură cu morcovi'],
	pune: ['£3'] la: ['fudge'].
```

La fel ca la o listă, mesajul pune:la:
este folosit pentru a adăuga un obiect într-o listă. Diferența este că, spre deosebire de
o listă, sunt legate două obiecte. Primul obiect este, la fel
ca la o listă, obiectul pe care îl vei stoca în listă. Al doilea
obiect nu este poziția sa în colecție, ci **intrarea**
care permite ca obiectul anterior să fie regăsit ulterior. Pe
scurt, un dicționar funcționează puțin ca un dicționar obișnuit: folosind cuvântul-cheie,
poate fi găsită semnificația. De exemplu, pentru a obține din
lista de mai sus prețul unui fudge:

```
>> price := meniu la: ['fudge'].
```

Poți folosi și notația concisă:

```
>> price := meniu ? ['fudge'].
```

Dacă intrările pe care le folosești pentru a stoca obiecte nu conțin spații
(și nu intră în conflict cu alte mesaje predefinite),
poate fi folosită și următoarea notație:

```
>> meniu := Dicționar nou
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Fără îndoială, notația de mai sus se citește ceva mai natural.
Pentru a cere prețul unui
fudge, poate fi folosită următoarea notație simplificată:

```
>> price := meniu fudge.
```

@api_Dict_collections

# Fișier

{{messages}}

Obiectul **Fișier** oferă acces de bază la sistemul de fișiere.
Poți folosi acest obiect pentru a citi fișiere întregi într-o variabilă
dintr-o dată sau pentru a scrie variabile în fișiere dintr-o dată. Citirea linie cu linie
este de asemenea suportată. Acestea sunt cele mai comune operații I/O cu fișiere
într-un limbaj de scripting. Operațiile avansate cu fișiere necesită
folosirea FFI prin pluginul de server sau printr-un plugin IO separat.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Dată/Oră

{{messages}}

Pentru o reprezentare structurată a orei și a datei, XOScript folosește
obiectul **Moment**. Dacă un obiect Moment nou este afișat pe ecran, sunt
afișate data și ora curente:

```
Ieșire scrie: Moment nou, rând-nou.
```

Ar putea avea ca rezultat ceva de genul:

```
2020-10-10 12:16:39
```

Este de asemenea ușor să citești componentele individuale ale timpului. Așadar,
de exemplu, dacă este necesar să știi doar anul curent, mesajul
**an** poate fi trimis momentului, iar răspunsul va fi un
obiect Număr care conține doar anul:

```
>> m := Moment nou.
Ieșire scrie: m an, rând-nou.
```

@api_Moment_system

# Program/StdOut

{{messages}}

Obiectul Program reprezintă aplicația care rulează în prezent. Acest obiect
oferă funcționalități pentru executarea comenzilor de sistem, includerea subprogramelor,
citirea argumentelor și multe altele. Toate funcțiile legate de sistem.

## StdOut

Ieșire este obiectul de ieșire standard. Are, în esență, două metode:
**scrie:** și **rând-nou**. Mesajul scrie: este folosit pentru a trimite un text
la stdout, iar mesajul rând-nou afișează un caracter de linie nouă.
În loc de **rând-nou** poți folosi și \\n.

Exemplu:

```
Ieșire scrie: ['Hello World'], rând-nou.
```

rezultat:

```
Hello World
```

## Module/Pluginuri

Lumea XOScript poate fi extinsă cu noi obiecte de sistem
prin instalarea de module. Un nou obiect de sistem poate fi adăugat în lumea
XOScript plasând fișierul modulului (de obicei un fișier cu sufixul .so
) în directorul mods. 

Când trimiți un mesaj obiectului pus la dispoziție prin
modulul plugin, acesta va fi încărcat automat de XOScript.

Poți scrie și tu pluginuri. Pluginurile sunt scrise în
limbajul de programare C. Poți găsi un exemplu de plugin în pachetul
de cod sursă, în src/plugins/example.


## Reflecție

Există diverse moduri de explorare
a sistemului în timpul execuției programului. XOScript are câteva metode pentru a
detecta ce obiecte sunt prezente și la ce mesaje răspund aceste
obiecte. În primul rând, fiecare obiect poate fi întrebat ce **tip** este,
însă tipurile în XOScript sunt maleabile și, prin urmare, nesigure.

Este de asemenea posibil să întrebi obiectul Program dacă un
anumit obiect este deja prezent în program:

```
Program Unealtă adevărat: { ... }.
```

În cazul unui nume de obiect
format dintr-un singur simbol, cel mai bine este să folosești
notația următoare pentru a evita confuzia:

```
Program caută: ['X'], adevărat: { ... }.
```

Pe lângă întrebările despre obiecte, este la fel de posibil să întrebi
obiectul Program despre mesaje. De exemplu, poate fi întrebat dacă
obiectul **Număr** cunoaște mesajul **între:și:**, în modul
ilustrat mai jos:

```
Program Number: ['between:and:'], rând-nou.
```

@api_Program_system

# server

{{messages}}

Pluginul Server din xoscript oferă funcționalități pentru
crearea aplicațiilor pe partea de server. Pentru a încărca pluginul
de server, folosește:

```
Server inițializează.
```

Pentru comoditate, se recomandă și încărcarea
fișierelor webtools.xo și template.xo.

```
Program folosește: ['webtools.xo'].
Program folosește: ['template.xo'].

```

## Setări de server

Poți configura următoarele setări de server:

```
	# sunt date valori implicite,
	# deci dacă nu setați nimic, se folosesc
	# aceste valori...

	Program 
	setare: ['max-postfields']
	valoare: 40.

	Program 
	setare: ['max-contentlength']
	valoare: 2000000. # 2MB

	Program 
	setare: ['max-time']
	valoare: 5000. # 5sec

```

## Hello World

Iată un program web foarte simplu pe care îl poți folosi cu un
server CGI standard precum Apache2, NGINX, OpenHTTPD sau orice alt
server cunoscut.

```
#!/bin/xo

Server inițializează.
Program folosește: ['webtools.xo'].

>> documentul-web := Document-Web nou.

documentul-web scrie-ieșire: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Dacă nu vrei să folosești obiectul Document-Web, nu e nicio problemă, dar
atunci trebuie să scrii singur antetele HTTP:

```
#!/bin/xo
Ieșire scrie: ['Content-type: text/html; charset=utf-8 \n\n'], rând-nou.
Ieșire scrie: ['salut lume!'], rând-nou.
``` 

## Cerere

Obiectul Cerere-HTTP poate fi folosit pentru a obține date GET/POST/COOKIE și
UPLOAD:

```
>> cerere  := Cerere-HTTP nou.
>> search   := cerere get: ['search']. # ?search=books
>> password := cerere post: ['password']. # din formular
>> selectate := cerere get-listă: ['sel[]']. #?sel[]=1&sel[]=2
>> selectate := cerere post-listă: ['sel[]'].
>> cookie   := cerere cookie: ['session-id'].
>> încărcare   := cerere upload: ['file'].
>> caletemp := încărcare ? 1.
>> numefișier := încărcare ? 0.
```

## Maxpost/length

Numărul maxim implicit de câmpuri POST este 40, iar lungimea maximă implicită
a conținutului este 2MB. Pentru a configura altfel, per script:

```
Program setare: ['max-contentlength'] valoare: 1. 
Program setare: ['max-postfields'] valoare: 1. 
```

{{note}}
Dacă lungimea conținutului depășește maximul,
procesul este oprit, deoarece nu mai putem fi siguri
că datele primite sunt sigure.
{{/note}}

Limita maxtime determină timpul maxim, în ms,
pentru citirea stdin/datelor POST.

```
Program setare: ['max-time'] valoare: 5000. # 5sec
```

Aceasta se aplică doar citirii I/O a datelor POST, prevenind
atacurile de tip slowloris. Dacă vrei cu adevărat să limitezi
timpul de execuție al oricărei operații, folosește alarma din Program.

## Bază de date

Obiectul Database poate fi folosit pentru a interoga MariaDB/MySQL.
Pentru a te conecta la o bază de date:

```
>> bd := Maria-DB nou gazdă: ['localhost'],
	utilizator: ['xo'],
	parolă: ['pass123'],
	nume-bază: ['xobase'],
	conectează.

```

Pentru a insera o înregistrare, folosește:

```
>> parametri-căutare := bd interogare: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parametri: ( Listă nou ; ['abc'] ; 12.35 ; 6 ). # interogări parametrizate

{  parametri-căutare execută-interogare. bd confirmă. }
prinde: { :e bd anulează.  }, pornește.
```

Reține că xoscript funcționează *doar* cu tranzacții și nu face niciodată autocommit.
Dacă autocommit nu poate fi dezactivat, vei primi o eroare de conexiune.
Folosește întotdeauna legarea parametrilor pentru interogări; nu adăuga niciodată datele introduse de utilizator direct
în SQL.

Obține id-ul inserat astfel:

```
Ieșire scrie: ['INSERAT: '] + parametri-căutare insert-id, rând-nou. # id-ul inserat
```

Pentru a prelua înregistrări:

```
>> parametri-căutare :=
bd
	interogare: ['SELECT * FROM book order by id desc limit 2'], 
	preia: { :rând 
		Ieșire scrie: rând id + [' '] + rând description + [': '] + rând price, rând-nou.
	}. # preluarea rândurilor

```

## Sesiuni

Pentru persistență, poți stoca și prelua date dintr-un obiect sesiune.
Mai întâi creează un nou **Document-Web**. Obiectul Document-Web leagă laolaltă
cererea, antetele, HTML-ul și sesiunea. Motivul este că, ori de câte ori
vizitezi un site web cu browserul, vezi doar HTML-ul. Dar
întregul Document-Web conține și **antete**. De exemplu,
majoritatea răspunsurilor HTTP includ un antet precum: Content-type:text/html, pentru a
spune browserului că datele care urmează trebuie afișate ca HTML
(și nu descărcate ca un fișier, de exemplu). Sesiunile sunt o modalitate de a
stoca datele utilizatorului între cereri. Pentru a ține evidența acestor date, trebuie
să setăm un cookie, iar acest cookie este setat tot printr-un antet. De aceea
totul se reunește în Document-Web (deoarece este documentul complet,
care conține atât antetele, cât și HTML-ul sau alte date).


```
# Mai întâi creăm o nouă instanță Document-Web
>> web := Document-Web nou.

# Acum pornim o sesiune; aceasta va genera un antet pentru un cookie și
# va crea un fișier pentru datele dumneavoastră, asociat cu acel cookie
>> sesiunea := web pornește-sesiune.

# Acum putem trata sesiunea ca pe un Dicționar
sesiunea userid: 123.
```

Pentru a distruge sesiunea (la deconectare):

```
web distruge-sesiune.
```

## Antete

Document-Web îți permite și să setezi alte antete cunoscute.
De exemplu, dacă vrei să redirecționezi utilizatorul către un alt URL:

```
web mergi-la: ['/other.html'].
```

În culise, această comandă generează și antetul HTTP care este trimis
împreună cu celelalte date sau cu HTML-ul tău, pentru a instrui browserul să navigheze
la adresa țintă specificată.

Pentru a adăuga un antet personalizat:

```
web antet: ( 
	Antet-HTTP nou
	cheie: ['Content-Length']
	valoare: 400
).
```

Pentru a afișa o pagină 404:

```
web negăsit: ['Hopa..'].
```


## Șabloane

Sistemul implicit de șabloane este foarte simplu. Nu trebuie să înveți
o nouă sintaxă pentru șabloane. De asemenea, motorul de șabloane asigură o separare reală
între prezentare și logica de business.

Pentru a crea un șablon dintr-un fișier:

```
>> tpl := web model: ['templates/ux.tpl'].
```

Sistemul de șabloane folosește marcaje. 
Există trei tipuri de marcaje: marcaje de tăiere, marcaje de lipire și
marcaje de poziție (slot). Ideea de bază este foarte simplă: tai
zone identificate prin marcaje de tăiere și le poți lipi în
zone identificate prin marcaje de lipire. Poți injecta texte în
marcajele de poziție.

Așadar, de exemplu, pornind de la șablonul următor, să punem
piatra prețioasă în cutia de bijuterii și să adăugăm o etichetă de preț.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Poți face acest lucru astfel:

```
>> gem := tpl taie: ['gem'], copiază.
gem price: 99.
tpl lipește: gem la: ['jewels'].
web scrie-ieșire: tpl epurează.
```

Ultima linie trimite pur și simplu șablonul ca text către client,
împreună cu antetele HTTP necesare.

Rezultat:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

Pentru a servi în siguranță fișierele încărcate de utilizatori, te poți baza pe passthru:

```
>> încărcat := ['smile.gif'].
Server transmite: încărcat prefix: ['/uploads/images/'].
Program sfârșit.
```

Aceasta va servi conținutul încărcat de utilizator cu tipul
mime corespunzător. Sunt suportate doar tipurile mime de pe lista albă:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF și SVG.
Fișierele SVG, ZIP și GZIP sunt trimise ca descărcare, deoarece un SVG
poate conține scripturi care altfel ar rula pe domeniul tău.
Această metodă previne atacurile TOCTOU, traversarea căilor,
executarea de cod malițios (injecție), atacurile prin legături simbolice,
atacurile DDoS (limita fișierului = 50MB), atacurile de tip sniffing și
diverse alte probleme de securitate.


## JSON

Pentru a codifica un obiect ca JSON:

```
>> json := ( JSON jsonify: ( 
	Dicționar nou pune: ( 
		Listă nou ; 1 ; 2 ; 3
	) la: ['abc']
)).
```

Pentru a decodifica JSON într-un obiect xoscript:

```
>> dicț := ((JSON obiect: json) abc ? 1).
```

JSON-ul cu mai mult de 500 de niveluri de imbricare este respins ca invalid.

Pentru a trimite direct un Dicționar ca json, cu antetele corecte:

```
web json: dicț.
```


## Regex

Poți folosi expresii regulate creând un șablon (pattern).
De exemplu, pentru a potrivi atributele href și target ale hiperlinkurilor:

```
Șablon nou: ['href="([^"]+)" target="([^"]+)"'].
```

Acum aplică șablonul textului subiect astfel:

```
șablonul potrivire: subiect fă: { :m :x .... }
```

Exemplu complet:

```
>> subiect := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> șablonul := Șablon nou: ['href="([^"]+)" target="([^"]+)"'].
>> rezultat  := șablonul potrivire: subiect fă: { :m :x
	Ieșire scrie: m, rând-nou.
	Ieșire scrie: x, rând-nou.
	<- ['XXX'].
}.
Ieșire scrie: rezultat, rând-nou.
```

## Rețea

Folosește obiectul Rețea pentru a efectua o cerere web.
Obiectul Rețea trimite întotdeauna o cerere POST, cu excepția cazului în care trimiți Nimic ca
date; atunci va trimite o cerere GET.


```
Rețea 
post: Nimic 
către: ['https://redbeanphp.com'].
```

## Criptare

Pluginul de server vine cu criptare bazată pe XChaCha20 și Argon2.

Exemplu:

```
>> criptat := Seif criptează: ['hello'] cheie: ['world'].
>> decriptat := Seif criptează: criptat cheie: ['world'].
```

## Jetoane

Pentru a genera un jeton sigur din punct de vedere criptografic, de o anumită lungime:

```
>> jetonulmeu := Seif jeton: 40.
```

Aceasta va genera un jeton de 40 de caractere.

## Formatare

Obiectul Format îți permite să formatezi date, de exemplu completarea cu spații sau
adăugarea de zerouri. Folosește sintaxa printf.

```
>> fmt := Format nou: ['%06.0f'].
fmt aplică: 56. # dă 000056
```

Un format poate conține o singură conversie și aceasta trebuie să se potrivească valorii,
altfel primești o eroare:

- `aplică:` cu un text: `%s`
- `aplică:` cu un număr: `%f`, `%e`, `%g` sau `%a`
- `aplică-întreg:` cu un număr: `%d`, `%i`, `%o`, `%u`, `%x` sau `%c`

Valorile dintr-o cerere sunt texte. Pentru a formata una ca număr,
convertește-o mai întâi:

```
fmt aplică: (cerere get: ['amount']) număr.
```

## Codificatoare

Sunt disponibile mai multe codificatoare și decodificatoare.
Codificatorul url pregătește un url pentru a fi folosit în HTML ca link:

```
Server url-codifică: ['https://example.com?a=6&b=1 2'].
```

Pentru a injecta în siguranță datele introduse de utilizator în HTML, fără riscul
injecțiilor XSS, folosește întotdeauna:

```
Server html-codifică: ['<harmless>'].
```

Reține că motorul de șabloane va efectua întotdeauna codificarea html
atunci când scrii într-un marcaj de poziție. Așadar, dacă folosești sistemul de șabloane,
nu trebuie să folosești aceasta.

## Trimiterea de emailuri

Pentru a trimite un email, folosește biblioteca mailtools.xo.

Exemplu:

```
Server inițializează.
Program folosește: ['mailtools.xo'].

>> e-mail := Email-HTML nou.
>> img := e-mail atașează: ( Fișier nou: ['myimage.png'] ).

e-mail
expeditor: ['xo@xoscript.com'] nume: ['xo'],
către: ( Listă nou ; ['xo2@xoscipt.com'] ),
subiect: ['xoxo'],
corp: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), trimite.

```



## Legare

Folosind mesajul leagă: poți lega o bibliotecă externă de
programul tău folosind libffi. Pentru detalii, vezi capitolul despre ffi.


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

FFI este furnizat pe bază de platformă/plugin, deoarece este
legat de arhitectura sistemului subiacent, lucru pe care
nucleul nu ar trebui să-l facă.
Pluginul de server oferă o implementare ffi/blob conformă.
Implicit, nucleul se conectează la platforma țintă
prin stdin/stdout, servicii limitate de I/O cu fișiere și shell (Program sistem).
Integrarea suplimentară este oferită de ffi/blob-uri prin pluginuri
orientate pe aplicație, precum pluginul de server.

FFI înseamnă Foreign Function Interface (interfață pentru funcții externe). Îți permite să folosești funcționalități scrise de alții în
alte limbaje de programare, furnizate prin fișiere DLL, fișiere SO sau fișiere Dylib. Acestea pot
fi funcții foarte variate, iar prin această metodă este disponibilă o gamă vastă de funcționalități.
Să începem cu un exemplu:

```
Server leagă: (
 Listă nou ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Listă nou ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s eliberează.
```

Rezultatul acestui cod este că vei vedea următoarele în linia de comandă:
FFI has 3 letters.
Acum probabil te gândești: „Este mult cod pentru ceva atât de simplu.”
Adică, nu am putea rezolva asta pur și simplu cu o comandă Gui show? Răspunsul este un da categoric!
Dar acesta este gândit ca un exemplu ilustrativ.
FFI este folosit de obicei pentru sarcini mai complexe, dar acestea nu sunt exemple
bune, așa că am ales ceva banal.

Argumentele metodei de legare:

- Argumentul #1: Fișierul DLL sau SO pe care vrei să-l folosești.
- Argumentul #2: Funcția din acel fișier pe care vrei s-o legi.
- Argumentul #3: O listă cu numele tipurilor de date ale argumentelor funcției.
- Argumentul #4: Numele tipului returnat de funcție.
- Argumentul #5: Numele obiectului de care vrei să legi această funcție (dacă nu există, va fi creat
automat).
- Argumentul #6: Mesajul de care ar trebui legată această funcție.

În exemplul de mai sus, vrem să legăm funcția printf din libc.so. Poți găsi numele
tipurilor de date în documentația software-ului pe care îl legi. Tipurile disponibile sunt:
void, pointer, float, double, int, uint, char, uchar, intX și uintX,
unde X poate fi 8, 16, 32 sau 64.

Aceste tipuri se referă la numărul de bytes necesari pentru stocarea datelor. Pentru printf, legăm funcția de un
obiect nou numit Printf și de mesajul template:number:. Traduci funcția externă
în dialectul XOScript înainte de a o folosi. Mesajul template:number: așteaptă ca
prim parametru un buffer cu textul șablonului. Creăm acest buffer folosind un obiect Blob, care
îți permite să aloci memorie manual. Ești responsabil să eliberezi ulterior această memorie
cu mesajul eliberează.

Poți umple un blob de memorie în diverse moduri. În exemplul nostru îl umplem cu text, așa că folosim
mesajul utf8: (UTF-8 este o codificare pentru convertirea textului în bytes). Poți umple un blob și cu
bytes:, transmițând o listă de valori de bytes. Pentru a citi conținutul unui blob, folosește de-la:lungime:.
Vei primi bytes înapoi sub forma unei liste. Poți chiar să creezi un C-struct cu un Blob folosind
mesajul struct:, transmițând o secvență de tipuri C. Acest lucru poate fi necesar când apelezi o funcție
C dintr-o bibliotecă software externă care așteaptă un pointer la un struct.

{warning}
Trebuie să eliberezi singur blob-urile.
Blob-urile nu sunt curățate de colectorul de gunoi.
{/warning}

Deoarece blob-urile pot fi schimbate cu funcții externe din biblioteci,
ele nu pot fi colectate automat de colectorul de gunoi (ar putea rămâne în uz de către
funcțiile externe sau aceste funcții externe ar putea dori să le elibereze
ele însele). Prin urmare, trebuie să eliberezi singur blob-urile, dacă este necesar.

Pentru a elibera un blob, folosește:

```
blobulmeu eliberează.
```

Pentru a elibera un struct, folosește:

```
structuramea eliberează-struct eliberează.
```

Așadar, pentru un struct trebuie să trimiți două mesaje: eliberează-struct și eliberează, pentru a
dealoca blocul de memorie.

@api_Blob_fficonnect
