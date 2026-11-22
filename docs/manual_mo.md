# Noțiuni de bază

{{messages}}


Bine ați venit în XOScript
Proiectul XOScript își propune să creeze un limbaj de scripting simplu și auditabil.
Simplu nu înseamnă neapărat ușor.
Un limbaj de programare familiar poate fi mai ușor de folosit decât XOScript.
Aici, simplitatea înseamnă altceva:
posibilitatea de a vă forma un model mental complet al limbajului și al comportamentului său.

XOScript este conceput astfel încât să vă încapă în minte.
Gramatica și numărul de concepte sunt intenționat reduse.
Nu există clase; obiectele pot fi extinse direct.
Obiectele sunt transmise prin referință, copierea este explicită,
iar funcțiile au un singur punct de ieșire.

Unele dintre aceste alegeri diferă considerabil de limbajele uzuale.
XOScript nu are, de exemplu, un sistem de tipuri și folosește domeniul de vizibilitate dinamic.
Mesajele care nu pot fi tratate sunt ignorate în loc să producă o excepție.
Aceste alegeri au consecințe și nu au scopul de a elimina erorile.
Ele au scopul de a menține modelul de bază al limbajului mic și coerent.

XOScript poate fi și localizat, ceea ce face posibilă exprimarea regulilor
de business într-o limbă naturală și, eventual, împărtășirea lor cu părțile interesate fără pregătire tehnică.

Auditabilitatea înseamnă aplicarea aceleiași filozofii în implementare.
Mediul de execuție este scris în C, cu un lexer, un parser și un tree walker mici, scrise de mână.
Biblioteca standard și mediul de execuție reflectă în mare parte structura limbajului,
ceea ce face ca relația dintre codul XOScript și implementarea sa să fie relativ directă.

Testele sunt, de asemenea, strâns legate de documentație.
Fiecare metodă ar trebui să aibă un test asociat care poate fi inclus în manual,
ceea ce ajută la menținerea documentației sincronizate cu implementarea.

XOScript nu urmărește să concureze cu limbajele uzuale în privința
funcționalităților sau a familiarității. El explorează un alt obiectiv:
un mediu de programare pe care un dezvoltator îl poate înțelege în întregime.

Speranța este că un limbaj mic și o implementare
mică fac posibilă în practică înțelegerea software-ului
de la octet la obiect, de la sintaxă la mediul de execuție, și scrierea codului cu
încredere, pentru că înțelegeți atât ce se întâmplă în
script, cât și ce se întâmplă în culise.

Arhitectura unei configurații de server xoscript
este simplă, dar flexibilă.

{{architecture.png}}

Pentru a folosi xoscript ca limbaj de server, trebuie să instalați
pluginul de server într-un dosar numit /mods/server. 

Motivul este că ne place să
separăm limbajul de bază de funcționalitățile specifice serverului,
spre deosebire, de exemplu, de PHP sau Python. Altfel ar trebui să livrăm tuturor
absolut totul fără niciun rost, ceea ce ar fi pur și simplu absurd.
Puteți instala și alte module, dacă doriți. Sistemul este foarte
flexibil.

De asemenea, unele funcții sunt mai bine implementate chiar în limbajul
de scripting, de exemplu șabloanele și gestionarea sesiunilor, așa că, în plus,
livrăm bibliotecile template.xo și webtools.xo pentru comoditatea dumneavoastră.
Motivul pentru toate acestea este că nu știm cum doriți să
folosiți xoscript. Îl puteți folosi ca limbaj de scripting pe server,
dar și pentru interfețe grafice, dispozitive încorporate sau simplă procesare în loturi.
Chiar dacă îl folosiți ca limbaj de scripting pe server (care este
în prezent unul dintre principalele cazuri de utilizare), poate doriți totuși să
folosiți un alt motor de șabloane sau un alt gestionar de sesiuni.
Cine suntem noi să hotărâm că trebuie să le folosiți pe ale noastre?

Unul dintre avantajele folosirii propriului nostru motor de șabloane este totuși că
nu trebuie să învățați o sintaxă suplimentară pentru a crea șabloane.
Motorul de șabloane implicit livrat cu xoscript asigură o
separare de 100% între prezentare și logică. În loc de o sintaxă specială
pentru șabloane, folosește pur și simplu un sistem foarte flexibil de marcaje de loc.
Pentru mai multe informații, consultați capitolul Server.

Rețineți că, dacă nu doriți să folosiți motorul de șabloane implicit sau
instrumentele web implicite, este de la sine înțeles că trebuie să furnizați
propriile variante.

Dacă rulați serverul web într-un chroot, jail sau alt tip de sandbox,
trebuie să instalați și dependențele lui xo în acel mediu; puteți
afla de ce biblioteci aveți nevoie folosind ldd (consultați pagina de manual din Linux sau BSD).
Dacă doriți să folosiți comenzi shell în scripturile xo, copiați și un shell
(de exemplu bash sau ksh) în acest mediu.

Dorim de asemenea să menționăm că tratăm compatibilitatea cu versiunile anterioare foarte serios.
Există chiar o funcționalitate specială de compatibilitate cu versiunile anterioare, numită
'version'. În general, ne propunem ca codul dumneavoastră să ruleze pentru totdeauna. Astfel, nu va
trebui niciodată să vă actualizați codul pentru a rămâne compatibil cu versiunile mai noi
ale xoscript. Obiectivul nostru este: scrii o dată, rulează pentru totdeauna.

Restul acestui manual este dedicat explicării în detaliu a limbajului de
programare xoscript. Scriptingul pe server este tratat în capitolul
numit Server. Dacă sunteți un dezvoltator de software experimentat, poate doriți
să săriți peste câteva capitole, deoarece unele dintre ele sunt puțin prea detaliate sau
sunt foarte asemănătoare cu practicile generale de programare. Așadar, cei care
au deja experiență cu mai multe alte limbaje de programare
ar face mai bine să trateze acest manual ca pe un ghid de referință.

## Instalare pe Linux

Descărcați apache2 și mariadb:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Descărcați xoscript.
Înlocuiți X cu numărul corect al versiunii!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Copiați fișierele în rădăcina web și în /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Editați configurația apache2:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Înlocuiți Virtualhost cu:

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

Creați o pagină de test:

```
sudo nano /var/www/html/test.xo
```

și scrieți un mic program de test:

```
#!/bin/xo
Server inițializează.
Program folosește: ['webtools.xo'].
>> web := Document-Web nou.
web scrie-ieșire: ['Hello World'].
```

Permiteți lui apache2 să execute programul prin CGI:

```
sudo chmod uog+x /var/www/html/test.xo
```

Reporniți apache2:

```
sudo systemctl restart apache2
```

Deschideți pagina de test în browser:

```
http://localhost/test.xo
```

Ar trebui să vedeți:

```
Hello World
```


## Instalare pe OpenBSD

Editați /etc/httpd.conf și adăugați:


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

Dacă doriți să folosiți SSL:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Pentru a proteja schimbul de chei împotriva atacurilor cuantice,
selectați cifrul mlkem:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Adăugați executabilul xo și modulele, precum și toate dependențele, în
chroot (aflați-le cu ldd).

## Rularea exemplelor


Pentru a rula unul dintre programele exemplu din pachet:

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

Pentru a compila din sursă pe Linux:

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

După ce fișierul a fost transferat pe calculatorul dumneavoastră, îl puteți dezarhiva
și porni xo cu următoarea comandă:

```
xo
```

Pentru a rula un XOScript, salvați programul ca fișier, adăugând sufixul -xo
(opțional). În plus, introduceți numele fișierului programului
după comanda XOScript:

```
xo myprogram.xo
```

Când rulați o comandă XOScript folosind fișierul programului ca
parametru, xo va citi și va executa fișierul programului.

{{note}}
Puteți porni programul și trăgându-l pe pictograma xo.
{{/note}}

{{warning}}
Pe unele sisteme trebuie mai întâi să acordați lui xo permisiunea de a încărca
biblioteci dinamice.
{{/warning}}

Tradiția cere ca primul program într-un limbaj de programare nou
să fie un fel de salut adresat lumii. În XOScript, un astfel de
program **Hello world** arată așa:

@test598

Când acest text este salvat într-un fișier, de exemplu hello.xo, el poate fi executat
astfel: .

xo hello.xo

Hello world


Puteți vedea rezultatul programului în fereastra neagră de mai sus.
Pe parcursul acestui manual, aceeași reprezentare va fi folosită pentru a afișa
rezultatul.

{{note}}
Ieșire se scrie cu I majusculă.
În general, obiectele încep cu literă majusculă,
cu excepția cazului în care acționează ca instanță (nu are metode
proprii, doar date). Aceasta reflectă convențiile
clasă versus instanță din alte limbaje de programare.
{{/note}}


## Sintaxă 

XOScript este un limbaj de programare *pur* *orientat pe obiecte*. Aceasta înseamnă
că xoscript consideră totul ca fiind un obiect, prin urmare nu există
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
răspuns         | <- answer.  


Acest capitol vă va oferi o impresie generală despre limbajul XOScript
și descrie principiile sale de bază. XOScript este un limbaj mic,
întemeiat pe trei acțiuni (vezi ilustrația), care se traduc în
aproximativ șase reguli gramaticale. Asta este tot ce trebuie pentru a stăpâni
limbajul.

Nu vă îngrijorați dacă lucrurile nu vă sunt imediat clare: toate elementele
de construcție vor fi explorate în capitolul următor (3), iar regulile de bază vor
fi repetate. Capitolul de față servește însă în principal ca o introducere
generală în limbaj. Principiile de bază vor fi explicate pe scurt
și ilustrate prin câteva exemple relevante. Toate detaliile lipsă
vor fi prezentate mai târziu.

Comentariile în XOScript sunt precedate de simbolul \#. Astfel, următorul rând
va fi ignorat:

```
# this is just a comment
```

## Variabile

Pentru a atribui
o variabilă folosiți simbolul de declarare a variabilei: >>. Numele unei
variabile poate conține orice semne, cu excepția: <-, :=, spațiilor albe,
punctelor, virgulelor, două puncte, ghilimelelor [' '] și parantezelor ().
În plus, o variabilă nu se poate întinde pe mai multe rânduri. Rețineți
că o variabilă nu poate începe cu o cifră sau cu semnul minus.

Iată exemple de variabile valide:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dollar'].
>> +plus := Adevărat.
>> user-password := ['Pssst!'].
```

Variabile invalide sunt, de exemplu:


```
>> -123 := ['negative number'].
>> password of user := ['Classified'].
>> password.of:user := ['Classified'].
>> ,x := 10.
```

{{note}}
Nu trebuie să escapați niciun caracter
(inclusiv apostrofuri, ghilimele duble, delimitatori
de text) într-un
literal de text, atâta timp cât acesta nu
creează ambiguitate pentru lexer.
{{/note}}

După ce o variabilă a fost declarată, ea poate fi folosită liber. Aceasta înseamnă
că simbolul de declarare trebuie folosit doar prima dată
când folosiți variabila (la declarare).

Mai exact, nu puteți începe pur și simplu să atribuiți o valoare
variabilei *(x := 2)*, deoarece mai întâi trebuie să declarați variabila *(\>\>
x := 2)*. Însă, odată declarată, aveți voie să-i schimbați valoarea
fără a folosi simbolul de declarare *(\>\> x := 2. x := 3.)*.

Rețineți că este obligatoriu să atribuiți o valoare unei variabile în momentul
declarării. Spre deosebire de alte limbaje de programare, nu aveți voie
să declarați o variabilă fără valoare. Este esențial să legați explicit
fiecare variabilă de o valoare inițială. Totuși, puteți inițializa liber
variabila cu obiectul **Nimic**. În acest caz, variabila poate fi
considerată goală *(\>\> x := Nimic.)*. Pe scurt, declararea unei
variabile fără valoare inițială nu este permisă. Așadar,

```
>> x.
```

este invalid și va produce un mesaj de eroare.

{{note}}
xoscript folosește domeniul de vizibilitate dinamic al variabilelor; pentru
detalii consultați capitolul Funcții.
{{/note}}


## Literali

XOScript consideră totul ca fiind un obiect, adică toate numerele, textele
și fragmentele de cod. Numerele, precum 1, 2, 100, -999 și 1,234, sunt
obiecte Număr. Toate textele dintre apostrofuri simple sunt obiecte
Text. Toate fragmentele de cod grupate între acolade {...} sunt
obiecte Funcție.

Literal         | Obiect rădăcină | Exemplu
--------------- | ------------ | ----------
numere          | Număr        | 1,2,3... 
texte           | Text         | \['hello'\]
funcție         | Funcție      | { 1 + 2. }.
                
     
Obiectele precum numerele și textele își au întotdeauna originea într-un obiect
rădăcină. De exemplu, toate numerele derivă din obiectul **Număr**. Toate
textele derivă din **Text**, iar toate fragmentele de cod din **Funcție**. La
rândul lor, toate aceste obiecte provin din **Obiect**, care este, de fapt,
obiectul rădăcină al tuturor obiectelor.


## Mesaje

A programa în XOScript înseamnă, în esență,
a trimite mesaje obiectelor. Notația generală pentru a trimite un mesaj
unui obiect este următoarea:

```
<object> <message>
```

Pentru a afla, de exemplu, dacă numărul **2** este par,
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

În acest caz, mesajul **între:și:** este trimis către **Număr**, care
este obiectul rădăcină al tuturor numerelor. Rezultatul va fi un număr aleatoriu
între 1 și 10. În sfârșit, există **mesaje binare**, care au
un singur caracter și un singur argument:

```
2 + 3
```

Aceasta arată ca o adunare matematică, dar de fapt este doar un alt mesaj.
Mesajul **+** este trimis către **2**, cu argumentul **3**, ceea ce va returna
răspunsul **5**. Mesajele binare pot fi scrise fără două puncte.

Mesajele binare pot fi înlănțuite:

```
>> x := 3 + 2 - 1.
```

În acest fragment, **+ 2** este trimis mai întâi obiectului **Număr** **3**, ceea ce
are ca rezultat obiectul Număr **5**, după care **-1** este trimis acestui
număr. Cititorii atenți observă pe bună dreptate discrepanța pe care
acest protocol o prezintă față de ordinea matematică convențională a
operatorilor. XOScript ignoră ordinea matematică în favoarea
coerenței sistemului său de mesaje. Ca urmare, expresia:

```
2 + 3 * 5 = 25
```

nu 17.

Acest lucru este intenționat. Parantezele pot fi folosite pentru a modifica ordinea:

```
2 + (3 * 5) = 17
```

Majoritatea obiectelor se returnează pe ele însele ca rezultat al unui anumit
mesaj. Acest lucru este util, deoarece încurajează continuarea dialogului cu acest
obiect prin trimiterea unui mesaj următor:

```
Ieșire scrie:
[' hello '] curăță-spații majuscule.
```

```
HELLO
```

Aici, obiectului **Text** îi sunt trimise două mesaje: **curăță-spații**, urmat
de **majuscule**.

În fragmentul următor, folosirea virgulei este necesară pentru a indica
faptul că urmează un mesaj nou. Altfel, XOScript se va încurca.

```
Ieșire scrie: ['Hello!'], rând-nou.
```

Mai întâi, mesajul **scrie:** este trimis simbolului creionului, urmat de
**rând-nou**. Fără virgulă, XOScript ar crede că doriți să trimiteți
**rând-nou** către **textul** **Hello!**, un exercițiu inutil.

Ordinea de procesare a mesajelor este următoarea: de la stânga la dreapta;
se începe cu mesajele din paranteze, urmate de mesajele unare. Apoi
mesajele binare, iar la final mesajele cu cuvinte-cheie. Vedeți exemplul
de mai jos:

```
Ieșire scrie: 0.5 rotunjește + (2 - 1), rând-nou.
```

XOScript citește întotdeauna de la stânga la dreapta: mai întâi, mesajul **scrie:**
este trimis către Ieșire, urmat de mesajul **rând-nou**. În cadrul
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
**mesaj unar**. Datorită parantezelor, **2 - 1** se calculează
primul, după care **1** este adunat la rezultatul lui **0.5 rotunjește** (1).

Întregul proces va da rezultatul **2**, care este și răspunsul
afișat. După virgulă urmează mesajul rând-nou, care mută cursorul
pe un rând nou. Desigur, cea mai bună cale de a înțelege pe deplin ordinea
de execuție a programelor XOScript este practica.

Merită remarcat faptul că în XOScript, spre deosebire de multe alte limbaje
de programare, spațiile albe sunt o parte fundamentală a sintaxei. Mai
ales în cazul mesajelor binare, spațiile albe pot crea o oarecare
confuzie. Folosiți întotdeauna un spațiu după un mesaj binar. Nu puteți
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
context, aceasta poate produce un rezultat cu totul diferit.

## Metode inexistente

Trimiterea unui mesaj către un obiect invocă funcția care a fost
atașată acestui obiect sub numele mesajului respectiv. Dacă trimiteți un mesaj
care nu este înțeles, obiectul care îl primește va ignora mesajul
și va returna în schimb o referință la sine pentru comunicarea ulterioară.
Aceasta se numește transmitere tolerantă a mesajelor.

Exemplu:

```
Ieșire scrie: Obiect blah, rând-nou.
```

Aceasta nu va produce o eroare. Pur și simplu va afișa textul **Obiect**.


## Controlul fluxului

În XOScript nu este nevoie de reguli gramaticale separate pentru *bucle* și
*condiții if*. O instrucțiune if este doar un simplu mesaj **adevărat:** sau **fals:**
trimis fie unui obiect **Adevărat**, fie unui obiect **Fals**:

```
2 par? adevărat: {
	Ieșire scrie: ['Two is an even number'], rând-nou.
}.
```
În exemplul anterior, mesajul **adevărat:** este trimis către **Adevărat** (răspunsul
la întrebarea: este 2 un număr par?). Ca argument este trimis suplimentar
un fragment de cod: un obiect **Funcție**. Această funcție scrie
pe ecran că 2 este, într-adevăr, un număr par.

Nu este nevoie nici de reguli de scriere separate pentru o *buclă*. Pentru a
executa un fragment de cod de trei ori, trimiteți pur și simplu **\*** cu argumentul
**3** acelei **Funcții**:

@test5

În acest fragment de cod, **i** este indexul. Astfel, prima dată când Funcția
este executată, **i** este egal cu 0, a doua oară când este executată, **i** = 1 și
așa mai departe.

Să analizăm un alt exemplu. Când trebuie tipărit un tabel de conversie
din *kJ* (kilojouli) în *kcal* (kilocalorii) cu pasul de 100,
notația corectă este cea de mai jos:

@test599

Aici, numărul rândului curent este transmis parametrului
**:line**. La începutul unei funcții sunt definiți parametrii
funcției. Parametrii nefolosiți rămân goi (**Nimic**). Parametrii sunt
plasați întotdeauna la începutul funcției, imediat după acolada
de deschidere, și sunt precedați de două puncte.

Mesajul **cât-timp:** este o combinație între o *buclă* și o *condiție*.
Două funcții pot fi legate folosind mesajul **cât-timp:**. Funcția care îl primește
va continua să ruleze până când funcția de după două puncte va da un rezultat
negativ. Exemplu:

@test600

În fragmentul de cod ilustrat mai sus, la **x** se adaugă **1** atâta timp cât
**x** este mai mic decât **5**. Când acest lucru nu mai este adevărat, a doua
funcție va răspunde cu **Fals** și, în consecință, execuția
primei funcții se va încheia. Rețineți că **x** a fost definit în afara
funcției și este o variabilă globală. Pentru a afla mai multe despre regulile de domeniu de vizibilitate,
consultați capitolul despre Funcții.

## Interpolarea textelor

Lista *kJ/kcal* ar putea fi făcută mai
prezentabilă. Ideal ar fi ca lista să arate astfel:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Când transformați rezultatul dorit într-un șablon, notația sa
ar putea fi:

```
number1 kJ ➞ number2 kcal
```

Aceasta înseamnă că **number1** reprezintă valoarea în kJ, iar **number2** valoarea
în kcal. Așa funcționează interpolarea textelor în XOScript. Nu
sunt necesare reguli gramaticale separate pentru aceasta în XOScript. Trimiteți pur și simplu
cuvântul care trebuie înlocuit către text, cu textul înlocuitor ca
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

Această regulă de substituție funcționează pentru fiecare mesaj nedefinit primit
de un obiect **text**. Fiecare mesaj care nu este recunoscut de obiectul
**text** va fi interpretat astfel: *înlocuiește textul mesajului
cu textul din argumentul mesajului.* Puteți adapta
programul astfel:


@test601


Pentru a evita confuzia privind mesajele care pot sau nu pot fi folosite ca
substitut, cel mai bine este să introduceți un marcaj de șablon precum &lt; &gt;
pentru segmentele de text din șablon care
trebuie înlocuite.

## Valori returnate

Pentru a răspunde la un mesaj se folosește săgeata
de returnare (*<-*). Exemplul următor ilustrează cum se creează o sarcină
care calculează un procent:

@test602

După ce sarcina a fost definită și atribuită variabilei **percentage**,
i se trimite mesajul **aplică:și:** cu argumentele **100** și **7**.

Aceasta va executa sarcina aplicată lui **100** și **7**, adică 7% din 100.
Cu ajutorul săgeții de returnare, răspunsul este returnat din sarcină înapoi
în programul principal.

## Extindere

Deși acest cod este valid, are un dezavantaj,
deoarece trebuie reținută ordinea argumentelor. Așadar, de ce să nu
îl scriem astfel: *7 percent of: 100 *? Ar arăta mult mai
*natural*. Pentru a face acest lucru posibil, trebuie să adaptăm obiectul părinte al lui
**7**, adică obiectul **Număr**, astfel încât să înțeleagă
mesajul **percent of:**. Acest lucru se poate realiza trimițând **la:execută:** către
obiectul Număr, astfel:

@test603

Deoarece procentul este, în acest caz, numărul însuși, ne referim la sine,
cuvântul-cheie *sine*. Pe scurt, simbolul sine înseamnă: *trimite acest
mesaj mie însumi*.

# Obiecte

{{messages}}

Pe lângă ajustarea și extinderea obiectelor existente, puteți crea și
obiecte noi, pur și simplu trimițând mesajul **nou**. Să presupunem că
doriți să creați un obiect factură care impune o secvență de
numerotare; în acest caz, veți avea nevoie mai întâi de un obiect factură.

Știind că fiecare obiect derivă dintr-un alt obiect, care, la rândul său,
provine în cele din urmă din obiectul rădăcină al tuturor obiectelor, numit Obiect,
trebuie să alegeți pe care dintre aceste obiecte se va
întemeia noul obiect. Noul obiect moștenește toate proprietățile
obiectului pe care se întemeiază, adică ale obiectului căruia i-a fost
trimis inițial mesajul **nou**.

În acest exemplu este preferabil un obiect mai degrabă neutru, unul fără prea
multe proprietăți moștenite. Alegerea este simplă, deoarece în acest
caz noul obiect se poate baza chiar pe obiectul rădăcină, adică
**Obiect**. Notația sistemului de facturi dorit va fi atunci
următoarea:

@test604

Numărul curent al facturii este stocat în obiect; de aceea, în fața lui
este plasat cuvântul-cheie **propriu**. Aceasta se numește *proprietate*;
mai multe detalii vor urma.

Unele firme preferă ca anul să fie inclus în numerele
facturilor. În acest caz, puteți crea un nou obiect factură întemeiat pe un
obiect factură anterior, dar care îi oferă utilizatorului posibilitatea
de a introduce un anumit an:

@test605

Nu este nevoie să scrieți din nou implementarea mesajului **număr**,
deoarece este moștenită de la **obiectul factură** scris
anterior; în consecință, codul vechi poate fi reutilizat. XOScript nu are concepte
precum clasele și alte concepte înrudite. Aceasta înseamnă că obiectele pot
moșteni doar de la alte obiecte, ceea ce se mai numește *moștenire
prototipală*.

Acum să revenim la proprietăți. Proprietățile obiectelor pot fi accesate
doar *din interiorul ierarhiei obiectului*, așa că aceste proprietăți
nu pot fi percepute de alte obiecte.

Spre deosebire de alte limbaje de programare, toate proprietățile obiectelor sunt
vizibile exclusiv pentru obiectul care a creat proprietatea și pentru
obiectele derivate. 

O tehnică des folosită este utilizarea unui obiect ca un fel de *plan*,
cum este, de exemplu, cazul facturilor discutate mai devreme.
Un alt exemplu bun este **Point**. Să spunem că creați un
program care face calcule folosind puncte pe o hartă. Puteți
dezvolta obiectul **Point**, care conține proprietățile unei
coordonate x și ale unei coordonate y, puse la dispoziția
lumii exterioare prin mesaje:

@test606

Mesajul **=** compară cele două puncte folosind mesajul **și:**. Prima
comparație are ca rezultat **Adevărat** sau **Fals**. Acestea sunt obiecte
booleene. Când trimiteți mesajul **și:** unui obiect Adevărat, iar
obiectul argument de după două puncte este de asemenea **Adevărat**, veți
primi din nou ca răspuns **Adevărat**. Când unul dintre ele este **Fals**, veți
primi răspunsul **Fals**. Rețineți că un punct nu poate citi coordonatele
celuilalt. Este necesar să trimiteți un mesaj celuilalt punct pentru a cere
aceste date: **x-coordinate** și **y-coordinate**. La urma urmei, așa cum s-a
explicat deja, proprietățile pot fi obținute doar din interiorul
familiei de obiecte înseși. 

Rețineți că mesajul **=** este folosit aici pentru a efectua comparația
punctelor. La fel de bine s-ar fi putut folosi un alt mesaj, de exemplu:
**is:** sau **equal:**, însă reutilizarea caracterului **=** a părut
potrivită în acest caz.

## Moștenire

Puteți reutiliza codul scris anterior pentru a crea o ierarhie
de obiecte. De exemplu:

```
>> Animal := Obiect nou.
>> Dog := Animal nou.
>> Poodle := Dog nou.
```

În acest caz, **Dog** moștenește tot comportamentul și toate proprietățile
lui **Animal**, iar obiectul **Animal**, la rândul său, moștenește tot comportamentul lui
**Obiect**, obiectul rădăcină al tuturor obiectelor.


## Suprascriere


În exemplul următor este creat un nou tip de listă:
**Combination**, în care fiecare element este garantat unic.
Funcțiile listei sunt reutilizate prin moștenire:

@test607

Observați cum al doilea **red** este exclus din listă.

Uneori poate fi necesar să suprascrieți un comportament al unui obiect.
De exemplu, când la adunarea numerelor trebuie luate în considerare unitățile
de măsură. În exemplul următor este creat obiectul **Size**.
Acest obiect returnează un număr care, la adunare, ține cont
de unitatea numărului care se adună. Obiectul **Număr**
verifică dacă este vorba de *inci* sau *picioare*. Codul
ar putea arăta astfel:

@test608

## Recursivitate

În exemplul anterior, **semnul** plus este suprascris. Rețineți
că, în cele din urmă, adunarea finală tot trebuie efectuată, ceea ce, de fapt,
are loc pe rândul următor:

```
>> answer := sine + (număr x factor).
```

Cum înțelege însă XOScript că acest **semn** plus se referă la
logica originală a adunării?** De exemplu, o altă interpretare
ar putea fi că XOScript va trimite în mod repetat același mesaj aceluiași
obiect, ceea ce, la rândul său, ar duce la o **buclă infinită**. Evident,
aceasta nu este intenția. De îndată ce trimiteți unui obiect un mesaj
care ar executa exact același cod, XOScript își va da seama
că, în acest caz, este vorba de mesajul subiacent, suprascris. Astfel,
programul dumneavoastră va fi protejat automat împotriva acestei forme de bucle
infinite. Totuși, când chiar doriți să rulați aceeași funcție din
funcția curentă, va fi necesar să trimiteți mai întâi mesajul
**recursiv**. În acest caz, rezultatul va fi o buclă
infinită. Există totuși aplicații utile pentru sarcinile recursive; de
exemplu, să presupunem că doriți să calculați factorialul unui număr
dat. În acest caz, adăugați pur și simplu mesajul **factorial** la
Număr:

@test609

Aceasta necesită recursivitate. De fapt, sarcina legată de
mesajul **factorial** trebuie executată din nou în cadrul acelei funcții.
Așadar, este necesar să invocați funcția factorial din interiorul
funcției factorial înseși. În mod normal, XOScript va împiedica această rutină
din cauza riscului de a ajunge într-o buclă infinită. Din acest motiv,
este esențial să precedați mesajul de cuvântul **recursiv**. Acest
lucru se face pentru ca XOScript să știe că intenția dumneavoastră
este să executați aceeași sarcină și că nu ați greșit.

## Obiecte asemănătoare claselor

Deși xoscript nu oferă clase, imitarea comportamentului
asemănător claselor este banală. Suprascrieți pur și simplu mesajul nou.

```
>> Animal := Obiect nou.
Animal la: ['nou'] execută: {
	<- sine nou inițializează.
}.

Animal la: ['inițializează'] execută: {
	propriu sound := ['?'].
	propriu legs  := 4.
}.
```

În fragmentul de cod de mai sus creăm un obiect numit Animal.
Acest obiect servește drept *plan* pentru tot felul de animale,
precum câinii și pisicile. Obiectul părinte Animal este scris
cu A majusculă pentru a arăta că este un obiect asemănător unei clase.
Apoi suprascriem mesajul nou scriind propria metodă nou.
În acest caz, ea trimite mesajul nou către sine, urmat de mesajul
inițializează. Deoarece xoscript blochează implicit recursivitatea, aceasta nu va provoca
o buclă infinită. În schimb, va trimite mesajul nou obiectului părinte
(Obiect), rezultând o nouă instanță a lui Animal. Astfel creăm
un obiect nou, bazat pe același obiect pentru care am creat metoda nou.
Acest lucru este perfect valid. Acum trimitem și mesajul inițializează, care asigură
că obiectul Animal are valori implicite pentru proprietățile sale. Implicit,
un animal are 4 picioare, iar sunetul este necunoscut (de aici semnul întrebării).
Pentru a crea o nouă instanță a lui Animal, am putea spune pur și simplu:

```
>> a := Animal nou.
```

Acum obținem o nouă instanță a lui Animal cu 4 picioare, sunet necunoscut și
o metodă inițializează. La fel ca în alte limbaje OOP, putem de asemenea
să extindem Animal:

```
>> Dog := Animal nou.
Dog la: ['inițializează'] execută: {
	sine inițializează.
	propriu sound := ['barks'].
}.
```

Putem testa ușor acest lucru adăugând o metodă text:

```
Animal la: ['text'] execută: {
	<- propriu legs text + propriu sound.
}.
```

Să punem totul laolaltă:

@test13


Crearea unui obiect aflat într-o anumită stare inițială este o problemă
frecventă. Să presupunem că trebuie creat un obiect **Rectangle**
pentru a calcula perimetrul și aria. O notație posibilă ar fi:


```
>> Rectangle := Obiect nou.

Rectangle la: ['area'] execută: {
	<- propriu lungime * propriu width.
}.
```

Evident, stabilirea lungimii și lățimii este o condiție prealabilă. În acest
scop pot fi adăugate mesajele **lungime:** și **width:**:


```
Rectangle la: ['length:'] execută: { :lungime
	propriu lungime := lungime.
}.

Rectangle la: ['width:'] execută: { :width
	propriu width := width.
}.

```

Acest dreptunghi poate fi apoi folosit astfel:


```
>> rectangle := Rectangle nou length: 2, width: 3.
Ieșire scrie: rectangle area.
```

Totuși, dacă setarea inițială a lungimii și lățimii este omisă,
va apărea un mesaj de eroare:

```
>> rectangle := Rectangle nou.
Ieșire scrie: rectangle area.
```

va produce următoarea eroare:

```
kej ban fūnd:lungime
```

Pentru a preveni acest lucru, este preferabil ca un dreptunghi să aibă
întotdeauna o lungime și o lățime inițiale, de exemplu 0. Așadar, în acest
caz, este necesar să **suprascrieți** mesajul **nou**.

@test610

Dacă suprascriem mesajul nou, practic imităm o **clasă**.

Lumea XOScript este plină de o diversitate de obiecte care sunt
disponibile programului dumneavoastră încă de la început. În capitolele următoare
vor fi discutate toate aceste obiecte de bază.

## Instantanee

Puteți salva un obiect (împreună cu starea sa curentă) pe disc cu:

```
myobject save-as: ['saved.bin'].
```

Pentru a reîncărca obiectul de pe disc:

```
>> myobject := Obiect load-from: ['saved.bin'].
```

Instantaneele pot fi folosite pentru a salva o anumită stare sau pentru a îmbunătăți performanța.
Încărcarea unui instantaneu evită analiza lexicală, analiza sintactică și configurarea aplicației.
De asemenea, în viitor, instantaneele ar putea aduce beneficii suplimentare de performanță,
precum optimizarea anumitor tipare sau detectarea și
optimizarea căilor fierbinți.

{{warning}}
Instantaneele sunt o funcționalitate experimentală; nu le folosiți în producție.
Pentru a activa funcționalitățile experimentale, compilați cu -D EXPERIMENTS.
{{/warning}}


@test712

# Obiectul Nimic

{{messages}}

Obiectul Nimic
reprezintă golul sau, mai bine zis, absența informației.
Uneori veți primi acest obiect ca răspuns la un mesaj,
atunci când rezultatul este **nimic**. Cea mai esențială întrebare
pe care o puteți pune obiectului **Nimic** este: **Nimic?**.
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
veți primi obiectul Nimic ca răspuns atunci când cereți un
element de listă care nu există. Puteți folosi obiectul Nimic și
atunci când doriți să declarați o variabilă, dar nu vreți încă să specificați
o valoare. În schimb, îi **atribuiți** pur și simplu valoarea specială **Nimic**. În
XOScript nu este permisă declararea unei variabile fără valoare, de exemplu:


```
>> valoare.
```

În schimb, trebuie să scrieți următoarele:

```
>> valoare := Nimic.
```

@api_None_base

# Valori booleene

{{messages}}

Spre deosebire de majoritatea limbajelor de programare populare la momentul scrierii,
XOScript oferă un singur obiect Adevărat și un singur obiect
Fals. Mai exact, de fiecare dată când scrieți **Adevărat**, aceasta nu înseamnă că
a fost creat un obiect nou. În schimb, folosiți întotdeauna o referință. Aceasta
înseamnă că atunci când scrieți următoarele:

\>\> x := Adevărat.

**x** se referă la obiectul **Adevărat**. Codul condițional și buclele
verifică de asemenea această referință. În XOScript, semnificația lui **Adevărat** și **Fals**
nu este fixă. De fapt, un program XOScript este dat serios peste cap de o
instrucțiune ca aceasta:

Adevărat := Fals.

Rezultatul unor astfel de acțiuni este nedefinit, însă rămâne o acțiune
validă și, prin urmare, permisă formal. În plus, există un obiect
Boolean, care este obiectul rădăcină atât pentru **Adevărat**, cât și pentru **Fals**, deoarece ambele
sunt derivate din acest obiect rădăcină. Obiectul Boolean însuși, însă,
nu are nicio aplicație practică.

## Capcane

Aveți grijă când folosiți **și:** și **sau:**

```
Ieșire scrie: (Fals or: Adevărat or: Adevărat), rând-nou.
Ieșire scrie: (Fals sau: Adevărat, sau: Adevărat), rând-nou.
```

Produce

```
Fals
Adevărat
```
deoarece mesajul **sau:** primește doar 1 argument. Primul rând
trimite **sau:sau:** către Fals, mesaj care nu există, așa că obiectul ignoră
mesajul și se returnează pe sine (Fals). Pe de altă parte, al doilea rând
trimite **sau:** urmat de un alt **sau:** (folosind un simbol de înlănțuire, adică o virgulă: ,).


@api_Boolean_base

# Numere

{{messages}}

De fiecare dată când scrieți un număr, de exemplu 9, -10 sau 3,12, în
culise XOScript va converti aceste numere într-un obiect **Număr**. Puteți
trimite mesaje acestui obiect Număr sau puteți atribui numărul
unei variabile și trimite mesaje ulterior:

```
10 par?

>> tenner := 10.
tenner par?

```

Ambele notații sunt valide. Obiectul Număr răspunde la următoarele
mesaje...

Majoritatea acestor mesaje se explică de la sine și vă permit să efectuați
operații matematice sau comparații.

{{note}}
Rețineți că puteți folosi ≤ ≥ ≠ × și ÷ în locul echivalentelor lor ASCII.
Este o chestiune de preferință.
{{/note}}

Diferența dintre mesajele matematice binare (+) și
variantele lor cu cuvinte-cheie (adaugă:) este că primele returnează
un număr nou, care este rezultatul operației, în timp ce în cazul
celor din urmă este modificat obiectul însuși. Acest lucru este ilustrat în
exemplul următor:

@test597

În exemplul de mai sus, b = 4 și a = 3. Cu **adaugă: 2** valoarea
lui a crește cu 2, în timp ce **+ 3** creează un număr nou, egal
cu a + 3. Același lucru este valabil și pentru alte operații matematice, de exemplu
înmulțirile. Folosind simbolul înmulțirii, veți primi un
obiect nou ca răspuns. Dacă folosiți mesajul **înmulțește-cu:**,
veți înmulți numărul însuși.

Cu mesajul **între:și:**, de exemplu în: **Număr
între: X și: Y**, veți obține un număr între X și Y. În acest
mod poate fi generat orice număr aleatoriu:

```
>> a := Număr între: 1 și: 10.
Ieșire scrie: a, rând-nou.
```

Începând cu versiunea 1.4, generatorul încorporat de numere aleatorii din xoscript este,
din câte știm, sigur din punct de vedere criptografic.

Puteți atașa un **calificativ** unui număr, de exemplu **6
apples**. Fiecare mesaj care nu este recunoscut de un
număr va fi considerat calificativ. Puteți obține calificativul
unui număr cu ajutorul mesajului calificativ:

Un calificativ este, în esență, un obiect Text stocat împreună cu obiectul
Număr. Calificativul este de asemenea afișat după număr la o
instrucțiune **scrie:**. Calificativele pot fi folosite, de exemplu, pentru a aduna sume
în valute diferite. La adunarea sumelor, puteți cere
calificativele. Exemplul de program următor ilustrează acest
principiu folosind un calculator de valute istorice (deoarece cursul
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
XOScript va crea pentru dumneavoastră un nou obiect text. Totuși, aveți
grijă să folosiți ghilimelele corecte. Ghilimeaua de la
începutul textului diferă de cea de la sfârșit (acest lucru vă permite
să folosiți apostroful fără a fi nevoie să-l escapați).

## UTF8

Textele în xoscript conțin de obicei text codificat utf8. Deși
din punct de vedere tehnic este posibil ca un text să aibă conținut binar sau non-utf8,
este recomandat să folosiți blob-uri pentru aceasta. Blob-urile sunt
furnizate de pluginul de server (vezi capitolul ffi).
În general, blob-urile/ffi sunt furnizate
pe bază de plugin/platformă, deoarece sunt legate de platformă
și arhitectură (ffi/blob-uri). Nucleul limbajului de scripting încearcă să
rămână cât mai independent de platformă.

## Conversie de tip

Puteți crea o copie a oricărui obiect
cu un alt tip folosind următoarele mesaje:

Mesaj   | Rezultat
------- | ------
număr   | Convertește în număr
text    | Convertește în text
boolean | Convertește în boolean
  
Se **aplică** următoarele reguli:

mesaj    | Nimic     | Boolean            | Număr                 | Text      | Altele              
-------- | --------- | --------           | --------              | --------  | --------
boolean  | Fals      | n/a                | 0→Fals altfel→Adevărat | Adevărat | De obicei Adevărat
număr    | 0         | Fals→0 Adevărat→1 | n/a                    | ['n']→n | De obicei 1
text     | ['Nimic'] | ['Fals']/['Adevărat'] | ['n']              | n/a       | Depinde

## Copiere

Valorile în XOScript sunt transmise întotdeauna **prin referință**. În alte limbaje
aceasta depinde de tipul valorii; în XOScript există o singură cale:
prin referință. XOScript nu face niciodată o copie a unei valori. Pentru a copia un obiect,
trebuie să trimiteți mesajul **copiază**. 

@test611

Aici v-ați fi putut aștepta ca rezultatul să fie Dolly, în loc
de Donny. Totuși, nu este cazul, deoarece ambele nume se referă la același
obiect. Când lucrați cu o buclă, se întâmplă ceva asemănător:

@test612

De fapt, XOScript folosește **întotdeauna** referințe, așa că la **:quantity**
bucla ilustrată mai sus indică de asemenea referința la elementul
din listă.

Pentru a copia un obiect, trebuie să specificați această acțiune
**explicit**:

@test613

Trimițând mesajul unar **copiază** unui text, obiectul
returnează o copie a aceluiași obiect text. În același mod pot fi copiate
obiecte Număr, obiecte booleene, liste și dicționare.

Puteți defini și propria implementare a copierii; aceasta este chiar o
necesitate dacă vă creați propriile obiecte. Implementarea
implicită a copierii pentru o listă face o copie superficială: creează o
listă nouă cu aceleași elemente.

@test614

În acest caz, 4 este adăugat doar la copie.
Totuși, deoarece copia este superficială, obiectele din ambele liste
sunt aceleași.

@test615

Așadar, dacă adăugăm 2 la fiecare nume din copie, lista originală
este și ea afectată.

Pentru a remedia acest lucru, trebuie să facem o **copie profundă**. O astfel de acțiune de copiere
pentru o listă ar putea fi compusă astfel:

@test616

Rețineți de asemenea mesajul recursiv; acest mesaj trebuie
trimis înaintea mesajului copiază.

Este esențial să rețineți că, deși copia unui obiect
are adesea aceeași înfățișare ca originalul, de fapt ea nu va fi
niciodată același obiect. Obiectul rădăcină definește un mesaj **equal:**,
care poate fi folosit pentru a compara identitatea obiectelor. Priviți
exemplul următor:

@test617

## Conversie implicită

XOScript folosește **conversia implicită** pentru a converti obiecte. Pentru a afișa o
listă pe ecran, XOScript va trimite, de exemplu, mesajul
*text* intern listei. Acest lucru se poate dovedi foarte util
atunci când doriți să afișați o listă ca listă separată prin virgule.
Mesajul *text* poate fi suprascris: 

@test620

@api_String_base
@api_Format_base


## Texte pe server

Următoarele funcționalități ale obiectului Text sunt adăugate de
pluginul Server.

@api_String_server

# Funcții

{{messages}}

Puteți grupa cod între { și }; acesta devine atunci o funcție.
În xoscript folosim uneori și termenul sarcină sau, simplu,
bloc de cod.

Puteți rula o funcție trimițându-i mesajul *pornește*.


```
{ Ieșire scrie: 123, rând-nou. } pornește.
```

Dacă funcția primește argumente, folosiți **aplică:**.

```
{ :a Ieșire scrie: a, rând-nou. } aplică: a.
```

Vedeți și exemplele de mai jos.
Din cauza arhitecturii simple, o funcție poate avea doar
un singur punct de returnare. Pentru a evita surplusul de cod sau imbricarea excesivă a
condițiilor, puteți folosi o procedură (ceea ce este același lucru cu folosirea
semnului înmulțirii cu argumentul 1):

```
{
  (a = 1) adevărat: { x := 1. }, întrerupe.
  (a = 2) adevărat: { x := 2. }, întrerupe.
} procedură.
```

În acest fel, (a = 2) nu va fi evaluat dacă a = 1.
De asemenea, astfel nu aveți nevoie de mesaje adevărat imbricate.
Ori de câte ori vă surprindeți imbricând condiții, gândiți-vă
la mesajul procedură. Ar putea face codul
mai ușor de citit.


Iată o capcană importantă:

```
{
	Fals fals: {
		Ieșire scrie: ['End the loop.'].
	}, întrerupe.
	
	Ieșire scrie: ['Dont show me.'].

} procedură.

```

În acest caz, textul 'Dont show me' va fi afișat,
deoarece **întrerupe** este trimis către Fals. Dacă doriți să executați
o întrerupere, ea trebuie trimisă ca mesaj către **Adevărat**.
 

```
{
	Fals nu adevărat: {
		Ieșire scrie: ['End the loop.'].
	}, întrerupe.
	
	Ieșire scrie: ['Dont show me.'].

} procedură.

```

Va funcționa conform așteptărilor.

## Excepții

Excepțiile pot fi tratate astfel:

```
{ Task 1 } prinde: { Task 2 }, pornește.
```

Puteți de asemenea provoca intenționat o eroare în program și,
procedând astfel, activa blocul de tratare. Aceasta se face trimițând
mesajul **eroare:** sarcinii curente, așa cum se arată în următoarea
ilustrație:

```
{
această-sarcină eroare: ['Whoops!'].
} prinde: { :mistake
Ieșire scrie: mistake.
}, pornește.
```

## Injectarea valorilor

XOScript oferă sarcinilor posibilitatea de a injecta valori. Priviți
sarcina de mai jos:

```
>> sending := {
	Newsletter către: propriu recipient.
}.
sending setează: ['recipient']
valoare: ['info@recipient.org'].
sending pornește.
```


Această ilustrație prezintă o sarcină imaginară, care trimite un buletin informativ
la o adresă de email sau unui **destinatar**. Acest destinatar poate fi injectat
în sarcină din exterior, înainte de pornirea sarcinii, trimițând
sarcinii mesajul **setează:valoare:**. Procedând astfel, valoarea lui
**recipient** este prestabilită în sarcină. Această valoare poate fi de asemenea modificată,
iar sarcina poate fi apoi rulată din nou. Aceasta este o metodă utilă când folosiți
obiecte Task.

## Funcții goale

Sarcinile goale nu sunt permise. Teoretic, o sarcină goală ar arăta
așa: **{}**, însă XOScript consideră aceasta o eroare de limbaj. Dacă
doriți să declarați o sarcină goală, puteți folosi obiectul Nimic:

```
>> task := Nimic.
```

Deși aceasta nu este o sarcină reală, ci un obiect Nimic, i se poate
totuși trimite un mesaj pornește:

```
>> answer := task pornește.
```

De fapt, este același lucru cu:

```
>> answer := Nimic pornește.
```

Deoarece obiectul **Nimic** nu recunoaște mesajul **pornește**,
se va returna pe sine ca răspuns, astfel încât răspunsul este din nou **Nimic**.
Așadar, nu este nevoie de o sarcină goală. Datorită designului
elegant al limbajului de programare XOScript, puteți folosi pur și simplu obiectul
Nimic pentru aceasta.

## Domeniu de vizibilitate dinamic

Când o Funcție are nevoie de o variabilă, dar nu o găsește,
va verifica variabilele Funcției care a **apelat-o**
și va continua verificarea în sus pe lanțul de Funcții.
Acest proces de căutare continuă până când variabila este găsită.
Dacă variabila tot nu este găsită, va apărea un mesaj de eroare. Această metodă de căutare a
unei variabile se numește **domeniu de vizibilitate dinamic**.

Pentru a ilustra acest principiu:

@test618

@api_Code_base

# Obiectul rădăcină

{{messages}}

Obiectul numit **Obiect** este obiectul rădăcină al tuturor obiectelor din
XOScript și oferă funcționalitățile de bază ale limbajului. 

Mesajul trimis cel mai des
este **la:execută:**, care extinde funcționalitățile unui obiect. Acest
mesaj este primit de obiectul rădăcină, care, în consecință, leagă
sarcina specificată de mesaj și, procedând astfel, extinde obiectul
derivat.

## Metode universale

În mod normal, dacă trimiteți un mesaj care nu corespunde unei
metode a obiectului, acesta este ignorat. Totuși, puteți specifica
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

În loc să trimiteți un mesaj direct unui obiect, îl puteți
trimite și printr-o variabilă. Pentru aceasta folosiți mesajul
**mesaj:argumente:**. 

@test396

@api_Object_base

# Liste

{{messages}}

XOScript cunoaște două tipuri de colecții: *liste* și *dicționare*.
**Listele** sunt enumerări de obiecte într-o *ordine fixă*. Dicționarele nu au
ordine; în schimb, seamănă cu o legendă formată dintr-o cheie (sau termen) și
valoarea corespunzătoare. Listele sunt comparabile cu tablourile (PHP, Java, C)
și cu listele (Python). Dicționarele sunt comparabile cu tablourile asociative (PHP) sau
cu dicționarele (Python) din alte limbaje de programare. Pentru a crea
o Listă nouă scrieți:

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

Dacă afișăm lista pe ecran:

```
Ieșire scrie: fibonacci, rând-nou.
```

Vom vedea:

```
Listă ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

În loc de adaugă-la-sfârșit puteți folosi și ; pentru a adăuga elemente într-o listă:


```
>> fibonacci := Listă nou ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Punctele și virgulă (;) sunt toate mesaje binare care pun o
valoare în listă.

## Înlănțuire

Să presupunem că aveți o listă precum:

```
>> x := Listă nou ; 1 ; 2 ; 3.
```

Dacă doriți să ștergeți primul și ultimul element, mesajul
ar fi:

```
x scoate-primul scoate-ultimul.
```

Din păcate, notația anterioară nu va funcționa corect.
Mesajul **scoate-primul** returnează primul element al listei, care,
la rândul său, va deveni destinatarul mesajului **scoate-ultimul**. Astfel,
mesajul **scoate-ultimul** nu este trimis către **x**, ci către 2. O
soluție posibilă la această problemă ar fi crearea a două propoziții
separate, de exemplu: 

```
x scoate-primul.
x scoate-ultimul.
```

Totuși, acest lucru este destul de nepractic, mai ales când trebuie să
ștergeți mai mult de două elemente. De aceea, XOScript oferă o
structură alternativă a mesajelor pentru astfel de situații. În
structurile de mesaje **alternative**, răspunsurile obiectelor sunt ignorate
și primiți de fiecare dată înapoi obiectul destinatar ca răspuns.
O structură de mesaje **alternativă** este inițiată trimițând
mesajul **fă** unui obiect, iar structura de mesaje **alternativă**
poate fi încheiată trimițând mesajul **gata**. În
exemplul ilustrat, aceasta s-ar aplica astfel:

```
>> x := Listă nou ; 1 ; 2 ; 3.
x fă scoate-primul scoate-ultimul gata.
```

@api_List_collections

# Dicționare

{{messages}}

**Atât Lista, cât și Dicționarul sunt colecții. Totuși, spre deosebire de o
listă, un dicționar **nu are** ordine. O altă diferență între cele două
este că un dicționar constă din perechi de obiecte. Un obiect servește drept intrare (sau
cuvânt-cheie) pentru a căuta celălalt obiect. Un bun exemplu de
listă este o listă de prețuri, de exemplu:


```
>> menu := Dicționar nou
	pune: ['£5'] la: ['apple pie'],
	pune: ['£6'] la: ['carrot cake'],
	pune: ['£3'] la: ['fudge'].
```

La fel ca la o listă, mesajul pune:la:
este folosit pentru a adăuga un obiect într-o listă. Diferența este că, spre deosebire de
o listă, sunt legate două obiecte. Primul obiect este, la fel ca
la o listă, obiectul pe care îl veți stoca în listă. Al doilea
obiect nu este poziția sa în colecție, ci **intrarea**
care permite ca obiectul anterior să fie obținut mai târziu. Pe
scurt, un dicționar funcționează cam ca un dicționar obișnuit: folosind cuvântul-cheie,
poate fi găsită semnificația. De exemplu, pentru a obține din
lista menționată mai sus prețul unui fudge:

```
>> price := menu la: ['fudge'].
```

Puteți folosi și notația concisă:

```
>> price := menu ? ['fudge'].
```

Dacă intrările pe care le folosiți pentru a stoca obiecte nu conțin spații
(și nu intră în conflict cu alte mesaje predefinite),
poate fi folosită și notația următoare:

```
>> menu := Dicționar nou
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Fără îndoială, notația de mai sus se citește ceva mai natural.
Pentru a cere prețul unui
fudge, se poate folosi următoarea notație simplificată:

```
>> price := menu fudge.
```

@api_Dict_collections

# Fișier

{{messages}}

Obiectul **Fișier** oferă acces de bază la sistemul de fișiere.
Puteți folosi acest obiect pentru a citi fișiere întregi într-o variabilă
dintr-o dată sau pentru a scrie variabile în fișiere dintr-o dată. Citirea rând cu rând
este de asemenea acceptată. Acestea sunt cele mai obișnuite operații de I/O cu fișiere
într-un limbaj de scripting. Operațiile avansate cu fișiere necesită
folosirea FFI prin pluginul de server sau printr-un plugin IO separat.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Dată/Oră

{{messages}}

Pentru o reprezentare structurată a orei și a datei, XOScript folosește
obiectul **Moment**. Dacă un nou obiect Moment este afișat pe ecran,
sunt afișate data și ora curente:

```
Ieșire scrie: Moment nou, rând-nou.
```

Ar putea avea un rezultat de felul:

```
2020-10-10 12:16:39
```

Este de asemenea ușor să citiți componentele individuale ale timpului. Astfel,
de exemplu, dacă trebuie aflat doar anul curent, mesajul
**an** poate fi trimis momentului, iar răspunsul va fi un
obiect Număr care conține doar anul:

```
>> m := Moment nou.
Ieșire scrie: m an, rând-nou.
```

@api_Moment_system

# Program/StdOut

{{messages}}

Obiectul Program reprezintă aplicația care rulează în acest moment. Acest obiect
oferă funcționalități pentru a executa comenzi de sistem, a include subprograme,
a citi argumente și altele. Toate funcțiile legate de sistem.

## StdOut

Ieșire este obiectul de ieșire standard. Are, în esență, două metode:
**scrie:** și **rând-nou**. Mesajul scrie: este folosit pentru a trimite un text
la stdout, iar mesajul rând-nou afișează un caracter de linie nouă.
În loc de **rând-nou** puteți folosi și \\n.

Exemplu:

```
Ieșire scrie: ['Hello World'], rând-nou.
```

rezultat:

```
Hello World
```

## Module/Pluginuri

Lumea XOScript poate fi extinsă cu noi obiecte de sistem prin
instalarea de module. Un nou obiect de sistem poate fi adăugat în lumea
XOScript plasând fișierul modulului (de obicei un fișier cu sufixul .so)
în dosarul mods. 

Când trimiteți un mesaj obiectului pus la dispoziție prin
modulul plugin, acesta va fi încărcat automat de XOScript.

Puteți scrie și pluginuri proprii. Pluginurile sunt scrise în
limbajul de programare C. Găsiți un exemplu de plugin în pachetul
de cod sursă, în src/plugins/example.


## Reflecție

Există diverse moduri de a explora
sistemul în timpul execuției programului. XOScript dispune de câteva metode pentru a
detecta ce obiecte sunt prezente și la ce mesaje răspund aceste obiecte.
În primul rând, oricărui obiect i se poate cere de ce **tip** este,
însă tipurile în XOScript sunt maleabile și, prin urmare, nesigure.

Este de asemenea posibil să întrebați obiectul Program dacă un
anumit obiect este deja prezent în program:

```
Program Tool adevărat: { ... }.
```

În cazul unui nume de obiect
format dintr-un singur simbol, cel mai bine este să folosiți
notația următoare pentru a evita confuzia:

```
Program caută: ['X'], adevărat: { ... }.
```

Pe lângă întrebări despre obiecte, este la fel de posibil să întrebați
obiectul Program despre mesaje. De exemplu, se poate întreba dacă
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
de server folosiți:

```
Server inițializează.
```

Pentru comoditate, este recomandat să încărcați și
fișierele webtools.xo și template.xo.

```
Program folosește: ['webtools.xo'].
Program folosește: ['template.xo'].

```

## Setările serverului

Puteți configura următoarele setări ale serverului:

```
	# default values are given
	# so if you do not set anything these
	# values are used...

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

Iată un program web foarte simplu pe care îl puteți folosi cu un
server CGI standard precum Apache2, NGINX, OpenHTTPD sau orice alt
server cunoscut.

```
#!/bin/xo

Server inițializează.
Program folosește: ['webtools.xo'].

>> web-document := Document-Web nou.

web-document scrie-ieșire: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Dacă nu doriți să folosiți obiectul Document-Web, nu este nicio problemă, dar
atunci trebuie să scrieți singuri antetele HTTP:

```
#!/bin/xo
Ieșire scrie: ['Content-type: text/html; charset=utf-8 \n\n'], rând-nou.
Ieșire scrie: ['hello world!'], rând-nou.
``` 

## Cererea

Obiectul Cerere-HTTP poate fi folosit pentru a obține datele GET/POST/COOKIE și
UPLOAD:

```
>> cerere  := Cerere-HTTP nou.
>> search   := cerere get: ['search']. # ?search=books
>> password := cerere post: ['password']. # from form
>> selected := cerere get-listă: ['sel[]']. #?sel[]=1&sel[]=2
>> selected := cerere post-listă: ['sel[]'].
>> cookie   := cerere cookie: ['session-id'].
>> upload   := cerere upload: ['file'].
>> temppath := upload ? 1.
>> filename := upload ? 0.
```

## Maxpost/length

Numărul maxim implicit de câmpuri POST este 40, iar lungimea maximă implicită
a conținutului este 2MB. Pentru o configurare diferită pentru fiecare script în parte:

```
Program setare: ['max-contentlength'] valoare: 1. 
Program setare: ['max-postfields'] valoare: 1. 
```

{{note}}
Dacă lungimea conținutului depășește maximul,
procesul este oprit, deoarece nu mai putem fi siguri
că datele transmise sunt sigure.
{{/note}}

Limita maxtime determină timpul maxim în ms
pentru citirea stdin/datelor POST.

```
Program setare: ['max-time'] valoare: 5000. # 5sec
```

Aceasta se aplică doar citirii I/O a datelor POST, prevenind
atacurile de tip slowloris. Dacă doriți cu adevărat să limitați
timpul de execuție al oricărei operații, folosiți alarma din Program.

## Bază de date

Obiectul Database poate fi folosit pentru a interoga MariaDB/MySQL.
Pentru a vă conecta la o bază de date:

```
>> db := Maria-DB nou gazdă: ['localhost'],
	utilizator: ['xo'],
	parolă: ['pass123'],
	nume-bază: ['xobase'],
	conectează.

```

Pentru a insera o înregistrare folosiți:

```
>> parametri-căutare := db interogare: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parametri: ( Listă nou ; ['abc'] ; 12.35 ; 6 ). # parameterized queries

{  parametri-căutare execută-interogare. db confirmă. }
prinde: { :e db anulează.  }, pornește.
```

Rețineți că xoscript lucrează *doar* cu tranzacții și nu face niciodată autocommit.
Dacă autocommit nu poate fi dezactivat, veți primi o eroare de conexiune.
Folosiți întotdeauna legarea parametrilor în interogări; nu adăugați niciodată datele introduse de utilizator direct
în SQL.

Obțineți id-ul inserat astfel:

```
Ieșire scrie: ['INSERTED: '] + parametri-căutare insert-id, rând-nou. # insert id
```

Pentru a prelua înregistrări:

```
>> parametri-căutare :=
db
	interogare: ['SELECT * FROM book order by id desc limit 2'], 
	preia: { :row 
		Ieșire scrie: row id + [' '] + row description + [': '] + row price, rând-nou.
	}. # fetching rows

```

## Sesiuni

Pentru persistență puteți stoca și prelua date dintr-un obiect sesiune.
Mai întâi creați un nou **Document-Web**. Obiectul Document-Web leagă
cererea, antetele, HTML-ul și sesiunea. Aceasta deoarece, ori de câte ori
vizitați un site web cu browserul, vedeți doar HTML-ul. Dar
întregul Document-Web constă și din **antete**. De exemplu,
majoritatea răspunsurilor HTTP includ un antet precum: Content-type:text/html, pentru
a-i spune browserului că datele care urmează trebuie redate ca HTML
(și nu descărcate ca fișier, de exemplu). Sesiunile sunt o modalitate de a
stoca datele utilizatorului între cereri. Pentru a ține evidența acestor date, trebuie
să setăm un cookie, iar acest cookie este setat tot printr-un antet. De aceea
totul se reunește în Document-Web (deoarece este documentul complet,
care conține atât antetele, cât și HTML-ul sau alte date).


```
# First we make a new Web Document instance
>> web := Document-Web nou.

# Now we start a session, this will generate a Header for a cookie and
# create a file to store your data, associated with that cookie
>> session := web pornește-sesiune.

# Now we can treat session like a dict
session userid: 123.
```

Pentru a distruge sesiunea (la deconectare):

```
web distruge-sesiune.
```

## Antete

Document-Web vă permite de asemenea să setați alte antete cunoscute.
De exemplu, dacă doriți să redirecționați utilizatorul către un alt URL:

```
web mergi-la: ['/other.html'].
```

În culise, această comandă generează și antetul HTTP care se trimite
împreună cu celelalte date sau HTML-ul, pentru a-i indica browserului să navigheze
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
web negăsit: ['OOps..'].
```


## Șabloane

Sistemul de șabloane implicit este foarte simplu. Nu trebuie să învățați
o nouă sintaxă de șabloane. De asemenea, motorul de șabloane asigură o separare reală
între prezentare și logica de business.

Pentru a crea un șablon dintr-un fișier:

```
>> tpl := web model: ['templates/ux.tpl'].
```

Sistemul de șabloane folosește marcaje. 
Există trei tipuri de marcaje: marcaje de tăiere, marcaje de lipire și
marcaje de loc. Ideea de bază este foarte simplă: decupați
zonele identificate prin marcaje de tăiere și le puteți lipi în
zonele identificate prin marcaje de lipire. Puteți injecta texte în
marcajele de loc.

Astfel, de exemplu, având șablonul următor, să punem
gema în cutia de bijuterii și să adăugăm o etichetă de preț.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Puteți face acest lucru astfel:

```
>> gem := tpl taie: ['gem'], copiază.
gem price: 99.
tpl lipește: gem la: ['jewels'].
web scrie-ieșire: tpl epurează.
```

Ultimul rând trimite pur și simplu șablonul ca text către client,
împreună cu antetele HTTP necesare.

Rezultat:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

Pentru a servi în siguranță fișierele încărcate de utilizatori vă puteți baza pe passthru:

```
>> uploaded := ['smile.gif'].
Server transmite: uploaded prefix: ['/uploads/images/'].
Program sfârșit.
```

Aceasta va servi conținutul încărcat de utilizator cu tipul mime
corespunzător. Sunt acceptate doar tipurile mime din lista albă:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF și SVG.
Fișierele SVG, ZIP și GZIP sunt trimise ca descărcare, deoarece un SVG
poate conține scripturi care altfel ar rula pe domeniul dumneavoastră.
Această metodă previne atacurile TOCTOU, traversarea căilor,
executarea de cod rău intenționat (injecție), atacurile prin legături simbolice,
atacurile DDoS (limita fișierului = 50MB), atacurile de interceptare și
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
>> dict := ((JSON obiect: json) abc ? 1).
```

JSON cu mai mult de 500 de niveluri de imbricare este respins ca invalid.

Pentru a trimite direct un Dicționar ca json cu antetele corecte:

```
web json: dict.
```


## Regex

Puteți folosi expresii regulate creând un șablon.
De exemplu, pentru a găsi atributele href și target ale hiperlegăturilor:

```
Șablon nou: ['href="([^"]+)" target="([^"]+)"'].
```

Acum aplicați șablonul textului subiect astfel:

```
pattern potrivire: subiect fă: { :m :x .... }
```

Exemplu complet:

```
>> subiect := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> pattern := Șablon nou: ['href="([^"]+)" target="([^"]+)"'].
>> result  := pattern potrivire: subiect fă: { :m :x
	Ieșire scrie: m, rând-nou.
	Ieșire scrie: x, rând-nou.
	<- ['XXX'].
}.
Ieșire scrie: result, rând-nou.
```

## Rețea

Folosiți obiectul Rețea pentru a efectua o cerere web.
Obiectul Rețea trimite întotdeauna o cerere POST, cu excepția cazului în care trimiteți Nimic ca
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
>> encrypted := Seif criptează: ['hello'] cheie: ['world'].
>> decrypted := Seif criptează: encrypted cheie: ['world'].
```

## Jetoane

Pentru a genera un jeton sigur din punct de vedere criptografic, de o anumită lungime:

```
>> mytok := Seif jeton: 40.
```

Aceasta va genera un jeton de 40 de caractere.

## Formatare

Obiectul Format vă permite să formatați date, de exemplu prin completare cu spații sau
adăugarea de zerouri. Folosește sintaxa printf.

```
>> fmt := Format nou: ['%06.0f'].
fmt aplică: 56. # gives 000056
```

Un format poate conține o singură conversie, iar aceasta trebuie să se potrivească valorii,
altfel primiți o eroare:

- `aplică:` cu un text: `%s`
- `aplică:` cu un număr: `%f`, `%e`, `%g` sau `%a`
- `aplică-întreg:` cu un număr: `%d`, `%i`, `%o`, `%u`, `%x` sau `%c`

Valorile dintr-o cerere sunt texte. Pentru a formata una ca număr,
convertiți-o mai întâi:

```
fmt aplică: (cerere get: ['amount']) număr.
```

## Codificatoare

Sunt disponibile mai multe codificatoare și decodificatoare.
Codificatorul url pregătește un url pentru a fi folosit în HTML ca legătură:

```
Server url-codifică: ['https://example.com?a=6&b=1 2'].
```

Pentru a injecta în siguranță datele introduse de utilizator în HTML fără a risca
injecții XSS, folosiți întotdeauna:

```
Server html-codifică: ['<harmless>'].
```

Rețineți că motorul de șabloane va face întotdeauna codificarea html
atunci când scrieți într-un marcaj de loc. Așadar, dacă folosiți sistemul de șabloane,
nu trebuie să folosiți acest lucru.

## Trimiterea de emailuri

Pentru a trimite un email folosiți biblioteca mailtools.xo.

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

Folosind mesajul leagă: puteți lega o bibliotecă externă de
programul dumneavoastră folosind libffi. Pentru detalii, consultați capitolul despre ffi.


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

FFI este furnizat pe bază de platformă/plugin, deoarece
este legat de arhitectura sistemului subiacent, lucru pe care
nucleul nu ar trebui să-l facă.
Pluginul de server oferă o implementare conformă ffi/blob.
Implicit, nucleul se conectează la platforma țintă
prin stdin/stdout, servicii limitate de I/O cu fișiere și shell (Program sistem).
Integrarea suplimentară este oferită de ffi/blob-uri prin pluginuri
orientate spre aplicații, precum pluginul de server.

FFI înseamnă Foreign Function Interface (interfață pentru funcții externe). Vă permite să folosiți funcționalități scrise de alții în
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

Rezultatul acestui cod este că veți vedea următoarele în linia de comandă:
FFI has 3 letters.
Acum probabil vă gândiți: „Este mult cod pentru ceva atât de simplu.”
Adică, nu am putea rezolva asta cu o comandă Gui show? Răspunsul este un da categoric!
Dar acesta este gândit ca un exemplu ilustrativ.
FFI este folosit de obicei pentru sarcini mai complexe, dar acestea nu sunt exemple
bune, așa că am ales ceva banal.

Argumentele metodei leagă:

- Argumentul #1: Fișierul DLL sau SO pe care doriți să-l folosiți.
- Argumentul #2: Funcția din acel fișier pe care doriți să o legați.
- Argumentul #3: O listă cu numele tipurilor de date ale argumentelor funcției.
- Argumentul #4: Numele tipului returnat de funcție.
- Argumentul #5: Numele obiectului de care doriți să legați această funcție (dacă nu există, va fi creat
automat).
- Argumentul #6: Mesajul de care trebuie legată această funcție.

În exemplul de mai sus, dorim să legăm funcția printf din libc.so. Numele tipurilor
de date le găsiți în documentația software-ului de care vă legați. Tipurile disponibile sunt:
void, pointer, float, double, int, uint, char, uchar, intX și uintX,
unde X poate fi 8, 16, 32 sau 64.

Aceste tipuri se referă la numărul de octeți necesari pentru a stoca datele. Pentru printf, ne legăm de un
obiect nou numit Printf și de mesajul template:number:. Traduceți funcția externă
în dialectul XOScript înainte de a o folosi. Mesajul template:number: așteaptă ca
prim parametru un buffer cu textul șablonului. Creăm acest buffer folosind un obiect Blob, care
vă permite să alocați memorie manual. Sunteți responsabil de eliberarea acestei memorii ulterior,
cu mesajul eliberează.

Puteți umple un blob de memorie în diverse moduri. În exemplul nostru îl umplem cu text, așa că folosim
mesajul utf8: (UTF-8 este o codificare pentru conversia textului în octeți). Puteți umple un blob și cu
bytes:, transmițând o listă de valori de octeți. Pentru a citi conținutul unui blob, folosiți de-la:lungime:.
Veți primi octeții înapoi sub formă de listă. Puteți crea chiar și o structură C cu un Blob folosind
mesajul struct:, transmițând o secvență de tipuri C. Acest lucru poate fi necesar când apelați o funcție C
dintr-o bibliotecă software externă care așteaptă un pointer la o structură.

{warning}
Trebuie să eliberați singuri blob-urile.
Blob-urile nu sunt curățate de colectorul de gunoi.
{/warning}

Deoarece blob-urile pot fi schimbate cu funcții externe din biblioteci,
ele nu pot fi colectate automat de colectorul de gunoi (ar putea rămâne în uz de către
funcțiile externe sau aceste funcții externe ar putea dori să le elibereze
ele însele). Prin urmare, trebuie să eliberați singuri blob-urile, dacă este necesar.

Pentru a elibera un blob folosiți:

```
myblob eliberează.
```

Pentru a elibera o structură folosiți:

```
mystruct eliberează-struct eliberează.
```

Așadar, pentru o structură trebuie să trimiteți două mesaje, eliberează-struct și eliberează, pentru
a dealoca blocul de memorie.

@api_Blob_fficonnect
