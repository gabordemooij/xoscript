# Osnove

{{messages}}


Dobro došli u XOScript
Cilj projekta XOScript je stvoriti skriptni jezik koji je jednostavan i provjerljiv.
Jednostavno ne znači nužno i lako.
Poznati programski jezik možda je lakši za korištenje od XOScripta.
Ovdje jednostavnost znači nešto drugo:
mogućnost stvaranja potpunog mentalnog modela jezika i njegova ponašanja.

XOScript je osmišljen tako da ga možete u cijelosti držati u glavi.
Njegova gramatika i broj koncepata namjerno su mali.
Nema klasa; objekti se mogu izravno proširivati.
Objekti se prenose po referenci, kopiranje je eksplicitno,
a funkcije imaju jednu izlaznu točku.

Neki od tih izbora znatno se razlikuju od uobičajenih jezika.
XOScript, primjerice, nema sustav tipova i koristi dinamički doseg.
Poruke koje se ne mogu obraditi zanemaruju se umjesto da izazovu iznimku.
Ti izbori imaju posljedice i nisu namijenjeni uklanjanju pogrešaka.
Namijenjeni su tome da temeljni model jezika ostane malen i dosljedan.

XOScript se također može lokalizirati, što omogućuje izražavanje poslovnih
pravila na prirodnom jeziku i potencijalno njihovo dijeljenje s netehničkim dionicima.

Provjerljivost znači primjenu iste filozofije na implementaciju.
Izvršno okruženje napisano je u C-u, s malim ručno pisanim lekserom, parserom i obilaznikom stabla.
Standardna biblioteka i izvršno okruženje uvelike odražavaju strukturu jezika,
pa je odnos između XOScript koda i njegove implementacije relativno izravan.

Testovi su također usko povezani s dokumentacijom.
Svaka metoda trebala bi imati pripadajući test koji se može uključiti u priručnik,
što pomaže da dokumentacija ostane usklađena s implementacijom.

XOScript nije zamišljen kao konkurent uobičajenim jezicima po
mogućnostima ili poznatosti. On istražuje drugačiji cilj:
programsko okruženje koje programer može razumjeti kao cjelinu.

Nadamo se da mali jezik i mala
implementacija čine praktičnim razumijevanje softvera
od bajta do objekta, od sintakse do izvršnog okruženja, te pisanje koda sa
sigurnošću jer razumijete i što se događa u
skripti i što se događa ispod haube.

Arhitektura poslužiteljskog okruženja za xoscript
jednostavna je, a ipak fleksibilna.

{{architecture.png}}

Da biste koristili xoscript kao poslužiteljski jezik, morate instalirati
poslužiteljski dodatak u mapu /mods/server. 

To je zato što želimo
odvojiti osnovni jezik od funkcionalnosti specifičnih za poslužitelj,
za razliku od, primjerice, PHP-a ili Pythona. Inače bismo svima morali isporučiti
cijeli sudoper bez ikakve svrhe, što je jednostavno besmisleno.
Ako želite, možete instalirati i druge module. Sustav je vrlo
fleksibilan.

Također, neke je funkcije bolje implementirati u samom skriptnom jeziku,
poput predložaka i upravljanja sesijama, pa dodatno
isporučujemo biblioteke template.xo i webtools.xo radi vaše udobnosti.
Razlog za sve to je što ne znamo kako želite
koristiti xoscript. Možete ga koristiti kao poslužiteljski skriptni jezik,
ali i za grafička sučelja, ugrađene uređaje ili jednostavno skupnu obradu.
Čak i ako ga koristite kao poslužiteljski skriptni jezik (što je
trenutačno jedan od glavnih slučajeva upotrebe), možda ipak želite
koristiti drugi sustav predložaka ili drugi upravitelj sesija.
Tko smo mi da odlučujemo da morate koristiti naše?

Jedna od prednosti korištenja našeg sustava predložaka ipak je to što
ne morate učiti dodatnu sintaksu za izradu predložaka.
Zadani sustav predložaka koji dolazi s xoscriptom koristi 100%
odvajanje prikaza i logike. Umjesto posebne
sintakse predložaka, jednostavno koristi vrlo fleksibilan sustav oznaka utora.
Više informacija potražite u poglavlju Poslužitelj.

Imajte na umu da, ako ne želite koristiti zadani sustav predložaka ili
zadane webtools, podrazumijeva se da morate osigurati
vlastite.

Ako svoj web-poslužitelj pokrećete u chrootu, jailu ili nekoj drugoj vrsti sandboxa,
u tom okruženju morate instalirati i ovisnosti programa xo; koje
biblioteke trebate možete vidjeti pomoću ldd (pogledajte man stranicu za Linux ili BSD).
Ako u svojim xo-skriptama želite koristiti naredbe ljuske, u to okruženje kopirajte i ljusku
(poput bash ili ksh).

Također želimo napomenuti da vrlo ozbiljno shvaćamo kompatibilnost unatrag.
Postoji čak i posebna značajka za kompatibilnost unatrag pod nazivom
'version'. Općenito, cilj nam je da vaš kod radi zauvijek. Dakle, nikada
nećete morati ažurirati svoj kod kako bi ostao kompatibilan s novijim verzijama
xoscripta. Naš je cilj: napiši jednom, pokreći zauvijek.

Ostatak ovog priručnika posvećen je detaljnom objašnjenju programskog
jezika xoscript. Poslužiteljsko skriptiranje obrađeno je u poglavlju
pod nazivom Poslužitelj. Ako ste iskusan programer, možda ćete htjeti
preskočiti nekoliko poglavlja jer su neka od njih malo previše detaljna ili
vrlo slična općim programerskim praksama. Stoga, oni od vas
koji već imaju iskustva s nekoliko drugih programskih jezika
bolje je da ovaj priručnik koriste kao referentni vodič.

## Postavljanje na Linuxu

Preuzmite apache2 i mariadb:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Preuzmite xoscript.
Zamijenite X ispravnim brojem verzije!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Kopirajte datoteke u korijensku mapu weba i u /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Uredite konfiguraciju za apache2:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Zamijenite Virtualhost sa:

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

Napravite testnu stranicu:

```
sudo nano /var/www/html/test.xo
```

i napišite mali testni program:

```
#!/bin/xo
Server inicijaliziraj.
Program koristi: ['webtools.xo'].
>> web := Web-dokument novi.
web ispiši: ['Hello World'].
```

Dopustite programu apache2 da izvršava vaš program putem CGI-ja:

```
sudo chmod uog+x /var/www/html/test.xo
```

Ponovno pokrenite apache2:

```
sudo systemctl restart apache2
```

Otvorite svoju testnu stranicu u pregledniku:

```
http://localhost/test.xo
```

Trebali biste vidjeti:

```
Hello World
```


## Postavljanje na OpenBSD-u

Uredite /etc/httpd.conf i dodajte:


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

Ako želite koristiti SSL:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Da biste razmjenu ključeva zaštitili od kvantnih napada,
odaberite šifru mlkem:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Dodajte izvršnu datoteku xo i module, kao i sve ovisnosti, u
chroot (otkrijte ih pomoću ldd).

## Pokretanje primjera


Za pokretanje jednog od primjera programa iz paketa:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Primjerice, za pokretanje primjera FizzBuzz na Linuxu:

```
./example.sh fizzbuzz Linux
```

Za pokretanje istog primjera na OpenBSD-u:

```
./example.sh fizzbuzz OBSD
```

Za pokretanje primjera s čistom izgradnjom:

```
./example.sh fizzbuzz OBSD clean
```

## Jedinični testovi

Za pokretanje jediničnih testova:

```
./runtests.sh
```

Za pokretanje jediničnih testova bez izgradnje (samo testiranje):

```
./runtests.sh nobuild
```

## Izgradnja

Za izgradnju iz izvornog koda na Linuxu:

```
make clean
ISO="en" make
```

Na OpenBSD-u:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

Za izgradnju poslužiteljskog dodatka na Linuxu:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

Za izgradnju poslužiteljskog dodatka na OpenBSD-u:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Pozdrav svijetu

Nakon što je datoteka prenesena na vaše računalo, možete je raspakirati
i pokrenuti xo sljedećom naredbom:

```
xo
```

Da biste pokrenuli XOScript, spremite program kao datoteku s nastavkom -xo
(nije obavezno). Osim toga, nakon naredbe XOScript upišite naziv datoteke
svog programa:

```
xo myprogram.xo
```

Kada pokrenete naredbu XOScript s datotekom programa kao
parametrom, xo će pročitati i izvršiti datoteku vašeg programa.

{{note}}
Program možete pokrenuti i tako da ga povučete na ikonu programa xo.
{{/note}}

{{warning}}
Na nekim sustavima morate unaprijed dopustiti programu xo da učitava dinamičke
biblioteke.
{{/warning}}

Tradicija nalaže da prvi program u svakom novom programskom
jeziku bude neka vrsta pozdrava svijetu. U XOScriptu takav
program **Hello world** izgleda ovako:

@test598

Kada se ovaj tekst spremi u datoteku, npr. hello.xo, može se izvršiti
na sljedeći način: .

xo hello.xo

Hello world


Izlaz programa možete vidjeti u gore prikazanom crnom prozoru.
U cijelom ovom priručniku isti će se prikaz koristiti za prikazivanje
izlaza.

{{note}}
Izlaz se piše velikim slovom I.
Općenito, objekti počinju velikim slovom,
osim ako djeluju kao instanca (nemaju vlastite
metode, samo podatke). To odražava konvencije klase i instance
u drugim programskim jezicima.
{{/note}}


## Sintaksa 

XOScript je *čisto* *objektno orijentiran* programski jezik. To znači
da xoscript sve doživljava kao objekt, pa stoga ne postoje
drugi *tipovi podataka*. U programu napisanom u XOScriptu postoje u biti tri osnovne
radnje: *dodjeljivanje*, *slanje poruka*
i *odgovaranje*. Razmjena poruka između objekata ključni je dio
XOScript programa. Te tri pojedinačne radnje prikazane su
u nastavku:


Radnja          | Primjer
--------------- | --------
dodjela         |  \>\> x := 1. 
unarne poruke   | x paran?.
binarna poruka  | 1 + 2.
poruka s ključnim riječima | x od: 0 duljina: 10.
odgovor         | <- answer.  


Ovo poglavlje daje opći dojam o jeziku XOScript
i opisuje njegova osnovna načela. XOScript je mali jezik
utemeljen na tri radnje (vidi ilustraciju) koje se pretvaraju u
otprilike šest gramatičkih pravila. To je sve što je potrebno za ovladavanje
jezikom.

Ne brinite ako vam nešto nije odmah jasno: svi gradivni
elementi bit će istraženi u sljedećem poglavlju (3), a osnovna pravila bit će
ponovljena. Ovo poglavlje, međutim, služi uglavnom kao opći
uvod u jezik. Osnovna načela bit će ukratko
objašnjena i ilustrirana s nekoliko relevantnih primjera. Svi nedostajući
detalji bit će opisani kasnije.

Komentari u XOScriptu započinju simbolom \#. Stoga će sljedeći redak
biti zanemaren:

```
# ovo je samo komentar
```

## Varijable

Za dodjelu
varijable koristite simbol za deklaraciju varijable: >>. Naziv
varijable može sadržavati sve znakove osim: <-, :=, razmaka,
točaka, zareza, dvotočaka, navodnika [' '] i zagrada ().
Nadalje, varijabla se ne može protezati kroz više redaka. Imajte na umu
da varijabla ne može započeti brojem ili znakom minus.

Ovo su primjeri valjanih varijabli:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dolar'].
>> +plus := Istina.
>> korisnička-lozinka := ['Pssst!'].
```

Nevaljane varijable su, primjerice:


```
>> -123 := ['negativan broj'].
>> password of korisnik := ['Povjerljivo'].
>> password.of:korisnik := ['Povjerljivo'].
>> ,x := 10.
```

{{note}}
Ne morate izbjegavati nijedan znak
(uključujući navodnike, dvostruke navodnike, granice
teksta) u
tekstualnom literalu, sve dok to ne
uzrokuje dvosmislenost za lekser.
{{/note}}

Nakon što je varijabla deklarirana, može se slobodno koristiti. To znači
da je simbol deklaracije potrebno upotrijebiti samo prvi put
kada koristite varijablu (deklaracija).

Točnije, ne možete jednostavno početi dodjeljivati vrijednost
svojoj varijabli *(x := 2)*, jer najprije morate deklarirati varijablu *(\>\>
x := 2)*. Međutim, nakon deklaracije smijete mijenjati njezinu vrijednost
bez korištenja simbola deklaracije*(\>\> x := 2. x := 3.)*.

Imajte na umu da je obavezno dodijeliti vrijednost varijabli u trenutku
deklaracije. Za razliku od drugih programskih jezika, nije dopušteno
deklarirati varijablu bez vrijednosti. Ključno je svaku varijablu
izričito povezati s početnom vrijednošću. Ipak, slobodno
inicijalizirajte varijablu objektom **Ništa**. U tom se slučaju varijabla može
smatrati praznom *(\>\> x := Ništa.)*. Ukratko, deklarirati
varijablu bez početne vrijednosti nije dopušteno. Dakle,

```
>> x.
```

nije valjano i dat će poruku o pogrešci.

{{note}}
xoscript koristi dinamički doseg varijabli; za
detalje pogledajte poglavlje Funkcije.
{{/note}}


## Literali

XOScript sve doživljava kao objekt, tj. sve brojeve, tekstove
i fragmente koda. Brojevi, poput 1, 2, 100, -999 i 1,234, objekti su
tipa Broj. Svi tekstovi između jednostrukih navodnika objekti su
tipa Tekst. Svi fragmenti koda grupirani unutar vitičastih zagrada {...} objekti su
tipa Funkcija.

Literal         | Korijenski objekt | Primjer
--------------- | ------------ | ----------
brojevi         | Broj         | 1,2,3... 
tekstovi        | Tekst        | \['hello'\]
funkcija        | Funkcija     | { 1 + 2. }.
                
     
Objekti poput brojeva i tekstova uvijek potječu od nekog korijenskog
objekta. Primjerice, svi brojevi potječu od objekta **Broj**. Svi
tekstovi potječu od objekta **Tekst**, a svi fragmenti koda od objekta **Funkcija**. Zauzvrat,
svi ti objekti potječu od objekta **Objekt**, koji je zapravo
korijenski objekt svih objekata.


## Poruke

Programiranje u XOScriptu u osnovi znači
slanje poruka objektima. Opći zapis slanja poruke
objektu je sljedeći:

```
<object> <message>
```

Da bismo, primjerice, saznali je li broj **2** paran, objektu **2**
šalje se poruka **paran?**:

```
2 paran?
```

Odgovor će biti **Istina** (opet, objekt). Objekti nepoznate poruke
obično zanemaruju, pa neće doći do pogreške. Neki objekti (npr.
brojevi ili tekstovi) na nepoznatu poruku odgovaraju na unaprijed određen način
(više o tome kasnije).

Objekt može primiti tri vrste poruka. 

Vrsta           | Broj argumenata
--------------- | -------------------
Unarna          | 0      
Binarna         | 1     
S ključnim riječima | 1+    


Prvo, postoje **unarne
poruke**, vidi primjer iznad, koje nemaju argumente. Drugo,
postoje **poruke s ključnim riječima**, koje imaju jedan ili više argumenata,
na primjer:

```
>> x := Broj između: 1 i: 10.
```

U ovom se slučaju poruka **između:i:** šalje objektu **Broj**, koji
je korijenski objekt svih brojeva. Rezultat će biti nasumičan broj
između 1 i 10. Konačno, postoje **binarne poruke**, koje imaju
samo jedan znak i jedan argument:

```
2 + 3
```

Ovo izgleda kao matematički zbroj, ali zapravo je samo još jedna poruka.
Poruka **+** šalje se objektu **2** s argumentom **3**, što će vratiti
odgovor **5**. Binarne poruke smiju se pisati bez dvotočke.

Binarne poruke mogu se ulančavati:

```
>> x := 3 + 2 - 1.
```

U ovom se fragmentu **+ 2** najprije šalje objektu **Broj** **3**, što
rezultira objektom Broj **5**, nakon čega se ovom broju šalje **-1**.
Pažljivi čitatelji s pravom će primijetiti nesklad koji
ovaj protokol pokazuje u odnosu na uobičajeni matematički redoslijed
operatora. XOScript zanemaruje matematički redoslijed u korist
dosljednosti svog sustava poruka. Kao rezultat toga, zbroj:

```
2 + 3 * 5 = 25
```

a ne 17.

To je namjerno. Zagrade se mogu koristiti za promjenu redoslijeda:

```
2 + (3 * 5) = 17
```

Većina objekata kao rezultat odgovora na određenu poruku vraća
sebe. To je korisno jer potiče daljnji dijalog s tim
objektom slanjem sljedeće poruke:

```
Izlaz piši:
[' zdravo '] skrati velika-slova.
```

```
ZDRAVO
```

Ovdje se objektu **Tekst** šalju dvije poruke: **skrati**, a zatim
**velika-slova**.

U sljedećem je fragmentu upotreba zareza nužna kako bi se naznačilo
da stiže nova poruka. U suprotnom će se XOScript zbuniti.

```
Izlaz piši: ['Hello!'], novi-red.
```

Najprije se simbolu olovke šalje poruka **piši:**, a zatim
**novi-red**. Bez zareza XOScript bi mislio da želite poslati
**novi-red** **tekstu** **Hello!**, što bi bio uzaludan pokušaj.

Redoslijed obrade poruka je sljedeći: s lijeva na desno;
počinje se porukama u zagradama, a zatim unarnim porukama. Potom
slijede binarne poruke, a na kraju poruke s ključnim riječima. Pogledajte primjer
u nastavku:

```
Izlaz piši: 0.5 zaokruži + (2 - 1), novi-red.
```

XOScript uvijek čita s lijeva na desno: najprije se poruka **piši:**
šalje objektu Izlaz, a zatim slijedi poruka **novi-red**. Unutar
samog argumenta XOScript čita s lijeva na desno, dakle najprije **0.5 zaokruži**,
a zatim **+**.

{{note}}
Poruka novi-red dodaje znak za novi redak tekstu.
Izvorni naziv ove poruke (stop) inspiriran je telegrafskim sustavima.
Poruke u telegrafskim sustavima 
često su koristile riječ STOP za označavanje kraja rečenice
(budući da je interpunkcija bila nepouzdana ili skupa).
{{/note}}

Štoviše, **zaokruži** ima prednost pred **+**, jer je to
**unarna poruka**. Zbog zagrada se najprije izračunava **2 - 1**,
nakon čega se **1** dodaje rezultatu izraza **0.5 zaokruži** (1).

Cijeli će postupak dati rezultat **2**, što je ujedno i ispisani
odgovor. Nakon zareza slijedi poruka novi-red, koja pomiče kursor
u novi redak. Naravno, najbolji način da se potpuno shvati redoslijed
izvođenja XOScript programa je vježba.

Vrijedi napomenuti da su u XOScriptu, za razliku od mnogih drugih programskih
jezika, razmaci temeljni dio sintakse. Posebno
kod binarnih poruka razmaci mogu izazvati određenu
zbrku. Uvijek stavite razmak nakon binarne poruke. Broj ne možete
izravno spojiti s porukom, na primjer: 

```
3 + 2
```

razlikuje se od 

```
3 +2
```

Prvi primjer (**3 + 2**) šalje
poruku **+** broju **3**, s brojem **2** kao argumentom.
Rezultat će u ovom slučaju biti **5**. U drugom primjeru (**3 +2**)
broju **3** šalje se unarna poruka **+2**. Ovisno o
kontekstu, to može dati vrlo različit rezultat.

## Nepostojeće metode

Slanje poruke objektu poziva funkciju koja je
pridružena tom objektu pod nazivom te poruke. Ako pošaljete poruku
koju objekt ne razumije, objekt primatelj zanemarit će vašu poruku
i umjesto toga vratiti referencu na sebe za daljnju komunikaciju.
To se naziva tolerantno prosljeđivanje poruka.

Primjer:

```
Izlaz piši: Objekt blah, novi-red.
```

Ovo neće dati pogrešku. Jednostavno će ispisati tekst **Objekt**.


## Tijek izvođenja

U XOScriptu nema potrebe za zasebnim gramatičkim pravilima za *petlje* i
*uvjete*. Naredba if samo je jednostavna poruka **istina:** ili **laž:**
objektu **Istina** ili objektu **Laž**:

```
2 paran? istina: {
	Izlaz piši: ['Dva je paran broj'], novi-red.
}.
```
U prethodnom primjeru poruka **istina:** šalje se objektu **Istina** (odgovoru
na pitanje: je li 2 paran broj?). Kao argument šalje se i dodatni
fragment koda: objekt **Funkcija**. Ova funkcija ispisuje na
zaslon da je 2 doista paran broj.

Nema potrebe ni za zasebnim pravilima pisanja za *petlju*. Da biste
fragment koda izvršili tri puta, jednostavno toj **Funkciji** pošaljite **\***
s argumentom **3**:

@test5

U ovom je fragmentu koda **i** indeks. Dakle, prvi put kada se Funkcija
izvrši, **i** je jednak 0, sljedeći put kada se izvrši, **i** = 1 i
tako dalje.

Razmotrimo još jedan primjer. Kada treba ispisati tablicu pretvorbe
iz *kJ* (kilodžula) u *kcal* (kilokalorije) u koracima od 100,
ispravan zapis prikazan je u nastavku:

@test599

Ovdje se broj trenutačnog retka prenosi parametru
**:line**. Na početku funkcije definiraju se parametri
funkcije. Neiskorišteni parametri ostaju prazni (**Ništa**). Parametri se
uvijek nalaze na početku funkcije, neposredno nakon početne
vitičaste zagrade, a ispred njih stoji dvotočka.

Poruka **dok:** kombinacija je *petlje* i *uvjeta*.
Dvije funkcije mogu se povezati porukom **dok:**. Funkcija primateljica
nastavit će se izvoditi sve dok funkcija nakon dvotočke ne da negativan
rezultat. Primjer:

@test600

U gore prikazanom fragmentu koda **x** se uvećava za **1** sve dok
je **x** manji od **5**. Kada to više nije slučaj, druga
funkcija odgovorit će s **Laž**, pa će se izvođenje
prve funkcije završiti. Imajte na umu da je **x** definiran izvan
funkcije i da je globalna varijabla. Da biste saznali više o pravilima dosega,
pogledajte poglavlje o Funkcijama.

## Interpolacija teksta

Popis *kJ/kcal* mogao bi biti
pregledniji. Poželjno bi bilo da popis izgleda ovako:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Kada željeni izlaz pretvorite u predložak, njegov bi zapis
mogao biti:

```
number1 kJ ➞ number2 kcal
```

To znači da **number1** predstavlja vrijednost u kJ, a **number2**
vrijednost u kcal. Tako funkcionira interpolacija teksta u XOScriptu.
Za to u XOScriptu nisu potrebna zasebna gramatička pravila. Jednostavno
tekstu pošaljite riječ koju treba zamijeniti, sa zamjenskim tekstom
kao argumentom:

```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

Rezultat:

```
100 kj ➞ 23.9 kcal
```

Ovo pravilo zamjene vrijedi za svaku nedefiniranu poruku koju
primi objekt **tekst**. Svaka poruka koju objekt
**tekst** ne prepozna tumačit će se na sljedeći način: *zamijeni tekst poruke
tekstom iz argumenta poruke.* Program možete prilagoditi
na sljedeći način:


@test601


Da biste izbjegli zabunu oko toga koja se poruka može, a koja ne može koristiti kao
zamjena, najbolje je uvesti oznaku predloška poput &lt; &gt;
za dijelove teksta u predlošku koje
treba zamijeniti.

## Povratne vrijednosti

Za odgovor na poruku koristi se povratna strelica
(*<-*). Sljedeći primjer pokazuje kako stvoriti zadatak
za izračun postotka:

@test602

Nakon što je zadatak definiran i dodijeljen varijabli **percentage**,
šalje joj se poruka **primijeni:i:** s argumentima **100** i **7**.

Time će se zadatak izvršiti primijenjen na **100** i **7**, tj. 7% od 100.
Pomoću povratne strelice odgovor se iz zadatka vraća
u glavni program.

## Proširivanje

Iako je ovaj kod valjan, ima nedostatak
jer treba pamtiti redoslijed argumenata. Pa zašto to ne
napisati ovako: *7 percent of: 100 *? To bi izgledalo mnogo
*prirodnije*. Da bismo to omogućili, moramo prilagoditi roditeljski objekt
broja **7**, a to je objekt **Broj**, tako da razumije
poruku **percent of:**. To se može postići slanjem poruke **na:učini:**
objektu Broj, ovako:

@test603

Budući da je postotak u ovom slučaju sam broj, pozivamo se na sebe,
ključnu riječ *sebe*. Ukratko, simbol sebe znači: *pošalji ovu
poruku meni samom*.

# Objekti

{{messages}}

Osim prilagođavanja i proširivanja postojećih objekata, možete i sami
stvarati nove objekte jednostavnim slanjem poruke **novi**. Pretpostavimo
da želite stvoriti objekt računa koji nameće redoslijed
numeriranja; u tom će vam slučaju najprije trebati objekt računa.

Budući da svaki objekt potječe od drugog objekta, koji pak
u konačnici potječe od korijenskog objekta svih objekata pod nazivom Objekt,
treba odlučiti na kojem će se od tih drugih objekata temeljiti vaš
novi objekt. Vaš novi objekt nasljeđuje sva svojstva
objekta na kojem se temelji, dakle onog kojem je poruka **novi**
izvorno poslana.

U ovom je primjeru poželjan prilično neutralan objekt, onaj bez previše
naslijeđenih svojstava. To olakšava izbor, jer se u tom
slučaju novi objekt može temeljiti na samom korijenskom objektu, a to je
**Objekt**. Zapis zamišljenog sustava računa tada će izgledati
ovako:

@test604

Trenutačni broj računa pohranjen je u objektu, zbog čega se
ispred njega nalazi ključna riječ **svoj**. To se naziva *svojstvo*;
više detalja slijedi.

Neke tvrtke radije u brojeve računa uključuju godinu.
U tom slučaju možete stvoriti novi objekt računa utemeljen na
prethodnom objektu računa, ali koji svom korisniku nudi mogućnost
unosa određene godine:

@test605

Nema potrebe ponovno pisati implementaciju poruke **broj**,
jer se nasljeđuje od prethodno napisanog **objekta
računa**; stoga se stari kod može ponovno upotrijebiti. XOScript nema koncepte
poput klasa i drugih srodnih koncepata. To znači da objekti mogu
nasljeđivati isključivo od drugih objekata, što je poznato i kao *prototipno
nasljeđivanje*.

Vratimo se sada svojstvima. Svojstvima objekta može se pristupiti samo
*unutar hijerarhije objekta*, pa ta svojstva
ne mogu vidjeti drugi objekti.

Za razliku od drugih programskih jezika, sva su svojstva objekata
vidljiva isključivo objektu koji je stvorio svojstvo i
izvedenim objektima. 

Uobičajena tehnika je korištenje objekta kao svojevrsnog *nacrta*,
što je, primjerice, slučaj s ranije opisanim računima.
Još jedan dobar primjer je **Point**. Recimo da izrađujete
računalni program koji izvodi izračune pomoću točaka na karti. Možete
razviti objekt **Point** sa svojstvima
x-koordinate i y-koordinate, koja će vanjskom svijetu biti dostupna
putem poruka:

@test606

Poruka **=** uspoređuje dvije točke pomoću poruke **i:**.
Prva usporedba daje **Istina** ili **Laž**. To su logički
objekti. Kada pošaljete poruku **i:** objektu Istina, a
objekt argumenta nakon dvotočke također je **Istina**, tada ćete
kao odgovor ponovno dobiti **Istina**. Kada je bilo koji od njih **Laž**,
dobit ćete odgovor **Laž**. Imajte na umu da jedna točka ne može čitati koordinate
druge. Potrebno je poslati poruku drugoj točki kako bi se zatražili
ti podaci: **x-coordinate** i **y-coordinate**. Uostalom, kao što je
već objašnjeno, svojstva se mogu dohvatiti isključivo unutar
same obitelji objekata. 

Imajte na umu da se ovdje za usporedbu točaka koristi poruka **=**.
Jednako se tako mogla upotrijebiti i neka druga poruka, poput
**is:** ili **equal:**, no ponovna upotreba znaka **=** činila se
prikladnom u ovom slučaju.

## Nasljeđivanje

Prethodno napisani kod možete ponovno upotrijebiti za stvaranje hijerarhije
objekata. Na primjer:

```
>> Životinja := Objekt novi.
>> Pas := Životinja novi.
>> Pudl := Pas novi.
```

U ovom slučaju **Dog** nasljeđuje sva ponašanja i svojstva
objekta **Animal**, a objekt **Animal** pak nasljeđuje sva ponašanja
objekta **Objekt**, korijenskog objekta svih objekata.


## Nadjačavanje


U sljedećem se primjeru stvara nova vrsta popisa:
**Combination**, u kojoj je zajamčeno da je svaki element jedinstven.
Funkcije popisa ponovno se koriste putem nasljeđivanja:

@test607

Primijetite kako je drugi **red** isključen s popisa.

Ponekad je potrebno nadjačati ponašanje objekta.
Primjerice, kada se zbrajaju brojevi, a pritom treba uzeti u obzir
mjerne jedinice. U sljedećem se primjeru stvara objekt **Size**.
Ovaj objekt vraća broj koji pri zbrajanju uzima
u obzir jedinicu broja koji se dodaje. Objekt **Broj**
provjerava radi li se o *inčima* ili *stopama*. Programski kod
mogao bi izgledati ovako:

@test608

## Rekurzija

U prethodnom se primjeru nadjačava **znak** plus. Imajte na umu
da se konačno zbrajanje ipak mora obaviti, a to se zapravo
događa u sljedećem retku:

```
>> odgovor := sebe + (broj x faktor).
```

Kako XOScript razumije da se ovaj **znak** plus odnosi na
izvornu logiku zbrajanja?** Primjerice, drugo bi tumačenje
moglo biti da će XOScript opetovano slati istu poruku istom
objektu, što bi pak rezultiralo **beskonačnom petljom**. Jasno,
to nije namjera. Čim pošaljete poruku objektu
koja bi izvršila potpuno isti kod, XOScript će shvatiti
da se u ovom slučaju misli na temeljnu, nadjačanu poruku. Tako će vaš
program automatski biti zaštićen od ovog oblika beskonačnih
petlji. Međutim, kada vam je doista cilj pokrenuti istu funkciju iz
trenutačne funkcije, bit će potrebno najprije poslati poruku
**rekurzivan**. U tom će slučaju rezultat biti beskonačna
petlja. Ipak, postoje korisne primjene rekurzivnih zadataka;
pretpostavimo, primjerice, da želite izračunati faktorijel zadanog
broja. U tom slučaju jednostavno dodajte poruku **factorial** objektu
Broj:

@test609

Ovo zahtijeva rekurziju. Naime, zadatak koji je povezan s
porukom **factorial** treba se ponovno izvršiti unutar te funkcije.
Dakle, potrebno je pozvati funkciju faktorijela iz same
funkcije faktorijela. U pravilu će XOScript spriječiti takav postupak
zbog rizika od završetka u beskonačnoj petlji. Zbog toga
je ključno da ispred poruke stoji riječ **rekurzivan**. To
se čini kako bi XOScript znao da vam je
namjera izvršiti isti zadatak i da niste pogriješili.

## Objekti nalik klasama

Iako xoscript ne nudi klase, oponašanje ponašanja nalik
klasama je trivijalno. Jednostavno nadjačajte poruku novi.

```
>> Životinja := Objekt novi.
Životinja na: ['novi'] učini: {
	<- sebe novi inicijaliziraj.
}.

Životinja na: ['inicijaliziraj'] učini: {
	svoj zvuk := ['?'].
	svoj noge  := 4.
}.
```

U gornjem fragmentu koda stvaramo objekt pod nazivom Animal.
Ovaj objekt služi kao *nacrt* za sve vrste životinja
poput pasa i mačaka. Roditeljski objekt Animal piše se
velikim slovom A kako bi se naznačilo da je to objekt nalik klasi.
Zatim nadjačavamo poruku novi pisanjem vlastite metode novi.
U ovom slučaju ona šalje poruku novi samoj sebi (sebe), a zatim poruku
inicijaliziraj. Budući da xoscript prema zadanim postavkama blokira rekurziju, to neće uzrokovati
beskonačnu petlju. Umjesto toga, poslat će poruku novi roditeljskom
objektu (Objekt), što rezultira novom instancom objekta Animal. Dakle, stvaramo
novi objekt, temeljen na istom objektu za koji smo stvorili metodu novi.
To je potpuno valjano. Sada šaljemo i poruku inicijaliziraj, čime se osigurava
da objekt Animal ima zadane vrijednosti svojih svojstava. Prema zadanim postavkama
životinja ima 4 noge, a zvuk je nepoznat (otuda upitnik).
Da bismo stvorili novu instancu našeg objekta Animal, jednostavno možemo napisati:

```
>> a := Životinja novi.
```

Sada dobivamo novu instancu objekta Animal s 4 noge, nepoznatim zvukom i
metodom inicijaliziraj. Baš kao i u drugim OOP jezicima, možemo
proširiti i naš Animal:

```
>> Pas := Životinja novi.
Pas na: ['inicijaliziraj'] učini: {
	sebe inicijaliziraj.
	svoj zvuk := ['laje'].
}.
```

To lako možemo testirati dodavanjem metode tekst:

```
Životinja na: ['tekst'] učini: {
	<- svoj noge tekst + svoj zvuk.
}.
```

Spojimo sve zajedno:

@test13


Stvaranje objekta koji je postavljen u zadano početno stanje čest je
problem. Pretpostavimo da treba stvoriti objekt **Rectangle**
kako bi se izračunali opseg i površina. Mogući zapis bio bi:


```
>> Pravokutnik := Objekt novi.

Pravokutnik na: ['površina'] učini: {
	<- svoj duljina * svoj širina.
}.
```

Očito je postavljanje duljine i širine preduvjet. U tu
svrhu mogu se dodati poruke **duljina:** i **width:**:


```
Pravokutnik na: ['length:'] učini: { :duljina
	svoj duljina := duljina.
}.

Pravokutnik na: ['width:'] učini: { :širina
	svoj širina := širina.
}.

```

Ovaj se pravokutnik tada može koristiti na sljedeći način:


```
>> pravokutnik := Pravokutnik novi length: 2, width: 3.
Izlaz piši: pravokutnik površina.
```

Međutim, ako se zanemare početne postavke duljine i širine,
pojavit će se poruka o pogrešci:

```
>> pravokutnik := Pravokutnik novi.
Izlaz piši: pravokutnik površina.
```

proizvest će sljedeću pogrešku:

```
Ključ nije pronađen:duljina
```

Da bi se to spriječilo, poželjno je da pravokutnik
uvijek ima početnu duljinu i širinu, na primjer 0. Dakle, u ovom
je slučaju potrebno **nadjačati** poruku **novi**.

@test610

Ako nadjačamo poruku novi, u osnovi oponašamo **klasu**.

Svijet XOScripta ispunjen je raznolikim objektima koji su
vašem programu dostupni od samog početka. U sljedećim poglavljima
bit će opisani svi ti osnovni objekti.

## Snimke stanja

Objekt (zajedno s njegovim trenutačnim stanjem) možete spremiti na disk pomoću:

```
mojobjekt save-as: ['saved.bin'].
```

Za ponovno učitavanje objekta s diska:

```
>> mojobjekt := Objekt load-from: ['saved.bin'].
```

Snimke stanja mogu se koristiti za spremanje određenog stanja ili za poboljšanje performansi.
Učitavanje snimke stanja izbjegava leksičku analizu, parsiranje i postavljanje aplikacije.
Također, u budućnosti bi se sa snimkama stanja mogle uvesti dodatne prednosti
u performansama, poput optimizacije određenih obrazaca ili otkrivanja i
optimizacije često izvođenih putanja.

{{warning}}
Snimke stanja eksperimentalna su značajka; nemojte ih koristiti u produkciji.
Za aktiviranje eksperimentalnih značajki prevedite s -D EXPERIMENTS.
{{/warning}}


@test712

# Objekt Ništa

{{messages}}

Objekt Ništa
predstavlja prazninu, ili još bolje, odsutnost informacije.
Ponekad ćete ovaj objekt dobiti kao odgovor na poruku,
kada je rezultat **ništa**. Najvažnije pitanje
koje možete postaviti objektu **Ništa** je: **Ništa?**.
Odgovor će uvijek glasiti **Istina**.

```
Izlaz piši: Ništa Ništa?.
```

rezultat:

```
Istina
```

Svaki objekt osim objekta **Ništa** odgovorit će s **Laž**.
Gornji fragment koda može se činiti pomalo filozofskim, no objekt **Ništa**
svakako ima iznimno praktične primjene. Primjerice,
objekt Ništa dobit ćete kao odgovor ako zatražite
element popisa koji ne postoji. Objekt Ništa možete koristiti i
kada želite deklarirati varijablu, ali još ne želite navesti
vrijednost. Umjesto toga, jednostavno **dodijelite** posebnu vrijednost **Ništa**. U
XOScriptu nije dopušteno deklarirati varijablu bez vrijednosti, poput:


```
>> vrijednost.
```

Umjesto toga morate napisati sljedeće:

```
>> vrijednost := Ništa.
```

@api_None_base

# Logičke vrijednosti

{{messages}}

Za razliku od većine popularnih programskih jezika u trenutku pisanja,
XOScript ima samo jedan jedini objekt Istina i jedan jedini objekt
Laž. Pojašnjenja radi, svaki put kada napišete **Istina**, to ne znači da
je stvoren novi objekt. Umjesto toga, uvijek koristite referencu. To
znači da kada napišete sljedeće:

\>\> x := Istina.

**x** se odnosi na objekt **Istina**. Uvjetni kod i petlje također
provjeravaju tu referencu. U XOScriptu značenje objekata **Istina** i **Laž**
nije fiksno. Zapravo, XOScript program prilično se uzdrma zbog
ovakve naredbe:

Istina := Laž.

Rezultat takvih radnji nije definiran, no to ostaje valjana
radnja i stoga je formalno dopuštena. Nadalje, postoji objekt
Logički, koji je korijenski objekt i za **Istina** i za **Laž**, jer su oba
izvedena iz tog korijenskog objekta. Sam objekt Logički, međutim,
nema nikakvu praktičnu primjenu.

## Zamke

Budite oprezni pri korištenju poruka **i:** i **ili:**

```
Izlaz piši: (Laž or: Istina or: Istina), novi-red.
Izlaz piši: (Laž ili: Istina, ili: Istina), novi-red.
```

Daje

```
Laž
Istina
```
jer poruka **ili:** prima samo 1 argument. Prvi redak
šalje **ili:ili:** objektu Laž, a ta poruka ne postoji, pa objekt zanemaruje
poruku i vraća sebe (Laž). S druge strane, drugi redak
šalje **ili:**, a zatim još jednu poruku **ili:** (pomoću simbola ulančavanja, tj. zareza: ,).


@api_Boolean_base

# Brojevi

{{messages}}

Svaki put kada napišete broj, na primjer 9, -10 ili 3,12, XOScript će
u pozadini te brojeve pretvoriti u objekt **Broj**. Ovom
objektu Broj možete slati poruke, ili možete broj dodijeliti
varijabli i zatim slati poruke:

```
10 paran?

>> desetka := 10.
desetka paran?

```

Oba su zapisa valjana. Objekt Broj odgovara na sljedeće
poruke...

Većina tih poruka sama je po sebi razumljiva i omogućuje izvođenje
matematičkih operacija ili usporedbi.

{{note}}
Imajte na umu da umjesto njihovih ASCII ekvivalenata možete koristiti ≤ ≥ ≠ × i ÷.
To je stvar osobnog izbora.
{{/note}}

Razlika između binarnih matematičkih poruka (+) i
njihovih inačica s ključnim riječima (dodaj:) je u tome što prve vraćaju
novi broj, koji je rezultat operacije, dok se kod
drugih mijenja sam objekt. To je prikazano u
sljedećem primjeru:

@test597

U gornjem primjeru b = 4, a a = 3. Porukom **dodaj: 2** vrijednost
od a povećava se za 2, dok **+ 3** stvara novi broj koji je
jednak a + 3. Isto vrijedi i za druge matematičke postupke, npr.
množenje. Korištenjem simbola množenja kao odgovor ćete dobiti
novi objekt. Ako koristite poruku **pomnoži-s:**,
pomnožit ćete sam broj.

Porukom **između:i:**, na primjer u: **Broj
između: X i: Y**, dobit ćete broj između X i Y. Na taj
se način može generirati bilo koji nasumični broj:

```
>> a := Broj između: 1 i: 10.
Izlaz piši: a, novi-red.
```

Od verzije 1.4 ugrađeni generator nasumičnih brojeva u xoscriptu je,
koliko nam je poznato, kriptografski siguran.

Broju možete pridružiti **odrednicu**, na primjer **6
apples**. Svaka poruka koju broj ne prepozna
smatrat će se odrednicom. Odrednicu
broja možete dohvatiti pomoću poruke odrednica:

Odrednica je u osnovi objekt Tekst koji je pohranjen uz objekt
Broj. Odrednica se također ispisuje nakon broja pri
naredbi **piši:**. Odrednice se mogu koristiti, primjerice, za zbrajanje iznosa
u različitim valutama. Pri zbrajanju iznosa možete zatražiti
odrednice. Sljedeći primjer programa prikazuje ovo
načelo pomoću povijesnog kalkulatora valuta (jer tečaj
ostaje razmjerno stabilan!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Tekstovi

{{messages}}

Svaki put kada se tekst stavi između **uglatih zagrada i navodnika** ['...'],
XOScript će za vas stvoriti novi tekstualni objekt. Međutim, pazite
da koristite ispravne navodnike. Navodnik na
početku teksta razlikuje se od onog na kraju (to vam omogućuje
korištenje jednostrukog navodnika bez potrebe za njegovim izbjegavanjem).

## UTF8

Tekstovi u xoscriptu obično sadrže tekst kodiran u utf8. Iako
je tehnički moguće imati binarni sadržaj ili sadržaj koji nije utf8 u
tekstu, za to se preporučuje korištenje blobova. Blobove
pruža poslužiteljski dodatak (vidi poglavlje ffi).
Općenito, blobovi/ffi pružaju se
ovisno o dodatku/platformi, budući da su vezani uz platformu
i arhitekturu (ffi/blobovi). Jezgra skriptnog jezika nastoji
ostati što neovisnija o platformi.

## Pretvorba tipova

Od svakog objekta možete stvoriti kopiju
drugog tipa pomoću sljedećih poruka:

Poruka  | Rezultat
------- | ------
broj    | Pretvara u broj
tekst   | Pretvara u tekst
logički | Pretvara u logičku vrijednost
  
Vrijede sljedeća **pravila**:

poruka   | Ništa     | Logički            | Broj                  | Tekst     | Ostalo              
-------- | --------- | --------           | --------              | --------  | --------
logički  | Laž       | n/p                | 0→Laž inače→Istina    | Istina    | Uglavnom Istina
broj     | 0         | Laž→0 Istina→1 | n/p                       | ['n']→n | Uglavnom 1
tekst    | ['Ništa'] | ['Laž']/['Istina'] | ['n']                 | n/p       | Ovisi

## Kopiranje

Vrijednosti se u XOScriptu uvijek prenose **po referenci**. U drugim jezicima
to ovisi o tipu vrijednosti, a u XOScriptu postoji samo jedan način,
po referenci. XOScript nikada ne stvara kopiju vrijednosti. Da biste kopirali objekt,
morate poslati poruku **kopiraj**. 

@test611

Ovdje ste možda očekivali da će izlaz biti Dolly, a ne
Donny. Međutim, to nije slučaj jer se oba imena odnose na isti
objekt. Pri radu s petljom događa se nešto slično:

@test612

Zapravo, XOScript **uvijek** koristi reference, pa i u **:quantity**
gore prikazana petlja također označava referencu na element
popisa.

Da biste kopirali objekt, tu radnju morate navesti
**izričito**:

@test613

Slanjem unarne poruke **kopiraj** tekstu objekt
vraća kopiju tog istog tekstualnog objekta. Na isti je način moguće kopirati objekte
Broj, logičke objekte, popise i rječnike.

Možete definirati i vlastitu implementaciju kopiranja; to je čak
nužno ako stvarate vlastite objekte. Zadana
implementacija kopiranja za popis stvara plitku kopiju, odnosno stvara
novi popis s istim elementima.

@test614

U ovom se slučaju 4 dodaje samo kopiji.
Međutim, budući da je kopija plitka, objekti u oba popisa
su isti.

@test615

Dakle, ako svakom imenu u kopiji dodamo 2, to utječe i na izvorni
popis.

Da bismo to ispravili, moramo napraviti **duboku kopiju**. Takva radnja kopiranja
za popis mogla bi se sastaviti na sljedeći način:

@test616

Također, obratite pozornost na poruku rekurzivan; tu je poruku potrebno
poslati prije poruke kopiraj.

Ključno je imati na umu da, iako kopija objekta
često izgleda jednako kao izvornik, ona zapravo
nikada nije isti objekt. Korijenski objekt definira poruku **equal:**,
koja se može koristiti za usporedbu identiteta objekata. Pogledajte
sljedeći primjer:

@test617

## Implicitna pretvorba

XOScript koristi **implicitnu pretvorbu** za pretvaranje objekata. Da bi ispisao
popis na zaslon, XOScript će, primjerice, interno poslati poruku
*tekst* popisu. To se može pokazati vrlo korisnim
ako želite ispisati popis kao popis odvojen zarezima.
Poruka *tekst* može se nadjačati: 

@test620

@api_String_base
@api_Format_base


## Poslužiteljski tekstovi

Sljedeće mogućnosti objekta Tekst dodaje
poslužiteljski dodatak.

@api_String_server

# Funkcije

{{messages}}

Kod možete grupirati između { i }; tada on postaje funkcija.
U xoscriptu ponekad koristimo i izraz zadatak ili jednostavno
blok koda.

Funkciju možete pokrenuti slanjem poruke *pokreni*.


```
{ Izlaz piši: 123, novi-red. } pokreni.
```

Ako vaša funkcija prima argumente, koristite **primijeni:**.

```
{ :a Izlaz piši: a, novi-red. } primijeni: a.
```

Pogledajte i primjere u nastavku.
Zbog jednostavne arhitekture funkcija može imati samo
jednu točku povratka. Da biste izbjegli dodatno opterećenje ili pretjerano ugniježđivanje
uvjeta, možete koristiti postupak (što je isto kao korištenje
znaka množenja s argumentom 1):

```
{
  (a = 1) istina: { x := 1. }, prekini.
  (a = 2) istina: { x := 2. }, prekini.
} postupak.
```

Na taj se način (a = 2) neće evaluirati ako je a = 1.
Također, na taj vam način nisu potrebne ugniježđene poruke istina.
Kad god primijetite da ugnježđujete uvjete, sjetite se
poruke postupak. Ona može učiniti vaš kod
čitljivijim.


Evo jedne važne zamke:

```
{
	Laž laž: {
		Izlaz piši: ['Završi petlju.'].
	}, prekini.
	
	Izlaz piši: ['Nemoj me prikazati.'].

} postupak.

```

U ovom će se slučaju prikazati tekst 'Dont show me'.
Jer se **prekini** šalje objektu Laž. Ako želite izvršiti
prekid, on se mora poslati kao poruka objektu **Istina**.
 

```
{
	Laž ne istina: {
		Izlaz piši: ['Završi petlju.'].
	}, prekini.
	
	Izlaz piši: ['Nemoj me prikazati.'].

} postupak.

```

Radit će prema očekivanjima.

## Iznimke

Iznimke se mogu obraditi ovako:

```
{ Zadatak 1 } uhvati: { Zadatak 2 }, pokreni.
```

Također možete namjerno izazvati pogrešku u svom programu i
time aktivirati blok za obradu. To se čini slanjem
poruke **pogreška:** trenutačnom zadatku, kao što je prikazano u sljedećoj
ilustraciji:

```
{
ovaj-zadatak pogreška: ['Ups!'].
} uhvati: { :propust
Izlaz piši: propust.
}, pokreni.
```

## Ubacivanje vrijednosti

XOScript zadacima omogućuje ubacivanje vrijednosti. Pogledajte
sljedeći zadatak:

```
>> slanje := {
	Bilten prima: svoj recipient.
}.
slanje postavi: ['recipient']
vrijednost: ['info@recipient.org'].
slanje pokreni.
```


Ova ilustracija prikazuje zamišljeni zadatak koji šalje bilten
na adresu e-pošte ili **primatelju**. Taj se primatelj može ubaciti
u zadatak izvana i prije pokretanja zadatka, slanjem
poruke **postavi:vrijednost:** zadatku. Na taj se način vrijednost
**recipient** unaprijed postavlja u zadatak. Ta se vrijednost također može izmijeniti,
a zadatak se tada može ponovno pokrenuti. To je korisna metoda pri korištenju
objekata zadataka.

## Prazne funkcije

Prazni zadaci nisu dopušteni. U teoriji bi prazan zadatak izgledao
ovako: **{}**, no XOScript to smatra jezičnom pogreškom. Ako
želite deklarirati prazan zadatak, možete koristiti objekt Ništa:

```
>> zadatak := Ništa.
```

Iako to nije pravi zadatak, nego objekt Ništa, poruka pokreni
i dalje se može poslati:

```
>> odgovor := zadatak pokreni.
```

Zapravo je to isto kao:

```
>> odgovor := Ništa pokreni.
```

Budući da objekt **Ništa** ne prepoznaje poruku **pokreni**,
vratit će sebe kao odgovor, pa je odgovor ponovno **Ništa**.
Dakle, nema potrebe za praznim zadatkom. Zahvaljujući elegantnom
dizajnu programskog jezika XOScript, za to jednostavno možete koristiti
objekt Ništa.

## Dinamički doseg

Kada Funkciji treba varijabla koju ne može pronaći,
ona će provjeriti varijable Funkcije koja ju je **pozvala**
i nastaviti provjeravati prema gore kroz lanac Funkcija.
Ovaj se postupak pretraživanja nastavlja sve dok se varijabla ne pronađe.
Ako varijabla ni tada nije pronađena, pojavit će se poruka o pogrešci. Ovaj način traženja
varijable naziva se **dinamički doseg**.

Za ilustraciju ovog načela:

@test618

@api_Code_base

# Korijenski objekt

{{messages}}

Objekt pod nazivom **Objekt** korijenski je objekt svih objekata u
XOScriptu i pruža osnovne jezične mogućnosti. 

Najčešće slana poruka
je **na:učini:**, koja proširuje funkcionalnosti objekta. Ovu
poruku prima korijenski objekt, koji zatim povezuje
navedeni zadatak s porukom i time proširuje izvedeni
objekt.

## Metode za sve poruke

Obično se poruka koja ne odgovara nijednoj
metodi objekta zanemaruje. Međutim, možete navesti
takozvane **čarobne metode** ili metode **za sve poruke** koje će se
pozvati ako objekt ne razumije poruku.

Dostupne su 4 metode za sve poruke. Svaka poruka odgovara
određenom broju argumenata.

Poruka za sve poruke | Broj argumenata
-------------------- | -------------------
odgovori:            | 0
odgovori:i:          | 1
odgovori:i:i:        | 2
odgovori:i:i:i:      | 3


@test619

## Programske poruke

Umjesto da se poruka izravno pošalje objektu, može se
poslati i putem varijable. Za to koristite poruku
**poruka:argumenti:**. 

@test396

@api_Object_base

# Popisi

{{messages}}

XOScript poznaje dvije vrste kolekcija: *popise* i *rječnike*.
**Popisi** su nabrajanja objekata u *fiksnom redoslijedu*. Rječnici nemaju
redoslijed, nego nalikuju legendi koja se sastoji od ključa (ili pojma) i njegove
odgovarajuće vrijednosti. Popisi su usporedivi s nizovima (PHP, Java, C)
i listama (Python). Rječnici su usporedivi s asocijativnim nizovima (PHP) ili
rječnicima (Python) u drugim programskim jezicima. Da biste stvorili
novi Popis, napišite:

```
>> fibonacci := Popis novi.
```

Ovaj prazni popis može se popuniti pomoću **dodaj-na-kraj:** :

```
fibonacci dodaj-na-kraj: 0.
fibonacci dodaj-na-kraj: 1.
fibonacci dodaj-na-kraj: 1.
fibonacci dodaj-na-kraj: 2.
fibonacci dodaj-na-kraj: 3.
fibonacci dodaj-na-kraj: 5.
fibonacci dodaj-na-kraj: 8.
fibonacci dodaj-na-kraj: 13.
```

Ako popis ispišemo na zaslon:

```
Izlaz piši: fibonacci, novi-red.
```

Vidjet ćemo:

```
Popis ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

Umjesto dodaj-na-kraj možete koristiti i ; za dodavanje elemenata u popis:


```
>> fibonacci := Popis novi ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Točke sa zarezom (;) binarne su poruke koje stavljaju
vrijednost u popis.

## Ulančavanje

Pretpostavimo da imate popis poput:

```
>> x := Popis novi ; 1 ; 2 ; 3.
```

Ako želite izbrisati prvi i posljednji element, vaša
bi poruka bila:

```
x izvadi-prvi izvadi-zadnji.
```

Nažalost, prethodni zapis neće ispravno funkcionirati.
Poruka **izvadi-prvi** vraća prvi element popisa, koji
će pak postati primatelj poruke **izvadi-zadnji**. Dakle,
poruka **izvadi-zadnji** ne šalje se objektu **x**, nego broju 2.
Moguće rješenje ovog problema bilo bi stvaranje dviju zasebnih
rečenica, poput: 

```
x izvadi-prvi.
x izvadi-zadnji.
```

Međutim, to je prilično nepraktično, posebno kada trebate
izbrisati više od dva elementa. Stoga XOScript nudi
alternativnu strukturu poruka za takve situacije. U
**alternativnim** strukturama poruka odgovori objekata se zanemaruju
i kao odgovor uvijek iznova dobivate objekt primatelj.
**Alternativna** struktura poruka započinje slanjem
poruke **čini** objektu, a **alternativna** struktura poruka
može se završiti slanjem poruke **gotovo**. U
prikazanom primjeru to bi se moglo primijeniti na sljedeći način:

```
>> x := Popis novi ; 1 ; 2 ; 3.
x čini izvadi-prvi izvadi-zadnji gotovo.
```

@api_List_collections

# Rječnici

{{messages}}

**I Popis i Rječnik su kolekcije. Međutim, za razliku od
popisa, rječnik **nema** redoslijed. Još jedna razlika između njih
je u tome što se rječnik sastoji od parova objekata. Jedan objekt djeluje kao unos (ili
ključna riječ) pomoću kojeg se traži drugi objekt. Dobar primjer takvog
popisa je cjenik, poput:


```
>> jelovnik := Rječnik novi
	stavi: ['£5'] na: ['pita od jabuka'],
	stavi: ['£6'] na: ['torta od mrkve'],
	stavi: ['£3'] na: ['fudge'].
```

Slično kao kod popisa, poruka stavi:na:
koristi se za dodavanje objekta u popis. Razlika je u tome što se, za razliku od
popisa, povezuju dva objekta. Prvi je objekt, slično kao
kod popisa, objekt koji ćete pohraniti u popis. Drugi
objekt nije njegov položaj unutar kolekcije, nego **unos**
koji omogućuje da se prethodni objekt kasnije dohvati.
Ukratko, rječnik funkcionira pomalo kao pravi rječnik: pomoću ključne riječi
može se pronaći značenje. Primjerice, da biste iz
gore navedenog popisa dohvatili cijenu karamele:

```
>> price := jelovnik na: ['fudge'].
```

Možete koristiti i sažeti zapis:

```
>> price := jelovnik ? ['fudge'].
```

Ako unosi koje koristite za pohranu objekata ne sadrže razmake
(i ne sudaraju se s drugim unaprijed definiranim porukama),
može se koristiti i sljedeći zapis:

```
>> jelovnik := Rječnik novi
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Nema sumnje da se gornji zapis čita nešto prirodnije.
Za dohvaćanje cijene
karamele može se koristiti sljedeći pojednostavljeni zapis:

```
>> price := jelovnik fudge.
```

@api_Dict_collections

# Datoteka

{{messages}}

Objekt **Datoteka** pruža osnovni pristup datotečnom sustavu.
Ovaj objekt možete koristiti za učitavanje cijelih datoteka u varijablu
odjednom ili za zapisivanje varijabli u datoteke odjednom. Podržano je i
čitanje redak po redak. To su najčešće datotečne U/I operacije
u skriptnom jeziku. Napredne datotečne operacije zahtijevaju
korištenje FFI-ja putem poslužiteljskog dodatka ili zasebnog IO dodatka.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Datum/Vrijeme

{{messages}}

Za strukturirani prikaz vremena i datuma XOScript koristi
objekt **Trenutak**. Kada se novi objekt Trenutak ispiše na zaslon,
prikazuju se trenutačni datum i vrijeme:

```
Izlaz piši: Trenutak novi, novi-red.
```

Može rezultirati nečim poput:

```
2020-10-10 12:16:39
```

Također je lako očitati pojedine vremenske sastavnice. Tako,
primjerice, ako je potrebno znati samo trenutačnu godinu, trenutku se
može poslati poruka **godina**, a odgovor će biti
objekt Broj koji sadrži samo godinu:

```
>> m := Trenutak novi.
Izlaz piši: m godina, novi-red.
```

@api_Moment_system

# Program/StdOut

{{messages}}

Objekt Program predstavlja aplikaciju koja se trenutačno izvodi. Ovaj objekt
nudi funkcionalnost za izvršavanje sistemskih naredbi, uključivanje potprograma,
čitanje argumenata i još mnogo toga. Sve funkcije povezane sa sustavom.

## StdOut

Izlaz je objekt standardnog izlaza. U osnovi ima dvije metode:
**piši:** i **novi-red**. Poruka piši: koristi se za slanje teksta
na stdout, a poruka novi-red ispisuje znak za novi redak.
Umjesto **novi-red** možete koristiti i \\n.

Primjer:

```
Izlaz piši: ['Hello World'], novi-red.
```

rezultat:

```
Hello World
```

## Moduli/Dodaci

Svijet XOScripta može se proširiti novim sistemskim objektima
instaliranjem modula. Novi sistemski objekt može se dodati u svijet
XOScripta postavljanjem datoteke modula (obično datoteke s nastavkom .so
) u mapu mods. 

Kada pošaljete poruku objektu koji je dostupan putem
modula dodatka, XOScript će ga automatski učitati.

Dodatke možete pisati i sami. Dodaci se pišu u
programskom jeziku C. Primjer dodatka možete pronaći u paketu izvornog
koda pod src/plugins/example.


## Refleksija

Postoje različiti načini istraživanja
sustava tijekom izvođenja programa. XOScript ima nekoliko metoda za
otkrivanje koji su objekti prisutni i na koje poruke ti objekti
odgovaraju. Prvo, svaki se objekt može upitati kojeg je **tipa**,
no tipovi su u XOScriptu promjenjivi i stoga nepouzdani.

Također je moguće upitati objekt Program je li
određeni objekt već prisutan u programu:

```
Program Alat istina: { ... }.
```

Ako se naziv
objekta sastoji od jednog jedinog simbola, najbolje je koristiti
sljedeći zapis kako bi se izbjegla zabuna:

```
Program pronađi: ['X'], istina: { ... }.
```

Osim pitanja o objektima, objekt Program jednako se tako može
pitati i o porukama. Primjerice, može se upitati zna li
objekt **Broj** poruku **između:i:**, na način
prikazan u nastavku:

```
Program Number: ['between:and:'], novi-red.
```

@api_Program_system

# poslužitelj

{{messages}}

Poslužiteljski dodatak u xoscriptu nudi funkcionalnost za
izradu poslužiteljskih aplikacija. Za učitavanje poslužiteljskog
dodatka koristite:

```
Server inicijaliziraj.
```

Radi vaše udobnosti preporučuje se učitati i
datoteke webtools.xo i template.xo.

```
Program koristi: ['webtools.xo'].
Program koristi: ['template.xo'].

```

## Postavke poslužitelja

Možete postaviti sljedeće postavke poslužitelja:

```
	# zadane vrijednosti su dane,
	# pa ako ništa ne postavite, koriste se
	# ove vrijednosti...

	Program 
	postavka: ['max-postfields']
	vrijednost: 40.

	Program 
	postavka: ['max-contentlength']
	vrijednost: 2000000. # 2MB

	Program 
	postavka: ['max-time']
	vrijednost: 5000. # 5sec

```

## Pozdrav svijetu

Evo vrlo jednostavnog web-programa koji možete koristiti sa
standardnim CGI poslužiteljem poput Apache2, NGINX, OpenHTTPD ili bilo kojim drugim
poznatim poslužiteljem.

```
#!/bin/xo

Server inicijaliziraj.
Program koristi: ['webtools.xo'].

>> web-stranica := Web-dokument novi.

web-stranica ispiši: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Ako ne želite koristiti objekt Web-dokument, to je u redu, ali
tada HTTP zaglavlja morate napisati sami:

```
#!/bin/xo
Izlaz piši: ['Content-type: text/html; charset=utf-8 \n\n'], novi-red.
Izlaz piši: ['zdravo svijete!'], novi-red.
``` 

## Zahtjev

Objekt HTTP-Zahtjev može se koristiti za dohvaćanje podataka GET/POST/COOKIE i
UPLOAD:

```
>> zahtjev  := HTTP-Zahtjev novi.
>> search   := zahtjev get: ['search']. # ?search=books
>> password := zahtjev post: ['password']. # iz obrasca
>> odabrano := zahtjev get-popis: ['sel[]']. #?sel[]=1&sel[]=2
>> odabrano := zahtjev post-popis: ['sel[]'].
>> kolačić   := zahtjev cookie: ['session-id'].
>> prijenos   := zahtjev upload: ['file'].
>> privputanja := prijenos ? 1.
>> imedatoteke := prijenos ? 0.
```

## Maxpost/length

Zadani najveći broj POST polja je 40, a zadana najveća duljina
sadržaja je 2MB. Za drugačiju konfiguraciju za pojedinu skriptu:

```
Program postavka: ['max-contentlength'] vrijednost: 1. 
Program postavka: ['max-postfields'] vrijednost: 1. 
```

{{note}}
Ako duljina sadržaja premaši najveću dopuštenu, 
proces se prekida jer više ne možemo biti sigurni
da je sadržaj siguran.
{{/note}}

Ograničenje maxtime određuje najdulje vrijeme u ms
za čitanje stdin/postdata.

```
Program postavka: ['max-time'] vrijednost: 5000. # 5sec
```

To se odnosi samo na U/I čitanje POST podataka i sprječava
napade nalik slowlorisu. Ako doista želite ograničiti
vrijeme izvođenja bilo koje operacije, koristite Program alarm.

## Baza podataka

Objekt Database može se koristiti za upite prema MariaDB/MySQL.
Za povezivanje s bazom podataka:

```
>> bp := Maria-DB novi domaćin: ['localhost'],
	korisnik: ['xo'],
	lozinka: ['pass123'],
	naziv-baze: ['xobase'],
	poveži-se.

```

Za umetanje zapisa koristite:

```
>> parametri-pretrage := bp upit: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parametri: ( Popis novi ; ['abc'] ; 12.35 ; 6 ). # parametrizirani upiti

{  parametri-pretrage izvrši. bp potvrdi. }
uhvati: { :e bp poništi.  }, pokreni.
```

Imajte na umu da xoscript radi *isključivo* s transakcijama i nikada ne izvodi automatsku potvrdu (autocommit).
Ako se autocommit ne može isključiti, dobit ćete pogrešku povezivanja.
Za upite uvijek koristite vezanje parametara; nikada korisnički unos ne dodajte izravno
u SQL.

Umetnuti id dohvatite ovako:

```
Izlaz piši: ['UMETNUTO: '] + parametri-pretrage insert-id, novi-red. # id umetanja
```

Za dohvaćanje zapisa:

```
>> parametri-pretrage :=
bp
	upit: ['SELECT * FROM book order by id desc limit 2'], 
	dohvati: { :red 
		Izlaz piši: red id + [' '] + red description + [': '] + red price, novi-red.
	}. # dohvaćanje redaka

```

## Sesije

Za trajnost podataka možete pohranjivati i dohvaćati podatke iz objekta sesije.
Najprije stvorite novi **Web-dokument**. Objekt Web-dokument povezuje
zahtjev, zaglavlja, HTML i sesiju. To je zato što, kad god
posjetite web-mjesto svojim preglednikom, vidite samo HTML. No
cijeli se Web-dokument sastoji i od **Zaglavlja**. Primjerice,
većina HTTP odgovora sadrži zaglavlje poput: Content-type:text/html kako bi
se pregledniku reklo da podatke koji slijede treba prikazati kao HTML
(a ne, primjerice, preuzeti kao datoteku). Sesije su način
pohranjivanja korisničkih podataka između zahtjeva. Da bismo pratili te podatke, moramo
postaviti kolačić, a i taj se kolačić postavlja putem Zaglavlja. Zato se
sve objedinjuje u objektu Web-dokument (jer je to cjeloviti
dokument koji sadrži i zaglavlja i HTML ili druge podatke).


```
# Najprije izrađujemo novu instancu Web-dokument
>> web := Web-dokument novi.

# Sada pokrećemo sesiju; to će generirati zaglavlje za kolačić i
# stvoriti datoteku za vaše podatke, povezanu s tim kolačićem
>> sesija := web pokreni-sesiju.

# Sada sesiju možemo tretirati kao Rječnik
sesija userid: 123.
```

Za uništavanje sesije (pri odjavi):

```
web uništi-sesiju.
```

## Zaglavlja

Web-dokument također omogućuje postavljanje drugih poznatih zaglavlja.
Primjerice, ako korisnika želite preusmjeriti na drugi URL:

```
web idi-na: ['/other.html'].
```

U pozadini ova naredba također generira HTTP zaglavlje koje se šalje
zajedno s vašim ostalim podacima ili HTML-om kako bi uputilo preglednik da prijeđe
na navedenu odredišnu adresu.

Za dodavanje prilagođenog zaglavlja:

```
web zaglavlje: ( 
	HTTP-Zaglavlje novi
	ključ: ['Content-Length']
	vrijednost: 400
).
```

Za prikaz stranice 404:

```
web nije-pronađeno: ['Ups..'].
```


## Predlošci

Zadani sustav predložaka vrlo je jednostavan. Ne morate učiti
novu sintaksu predložaka. Također, sustav predložaka osigurava stvarno odvajanje
prikaza i poslovne logike.

Za stvaranje predloška iz datoteke:

```
>> tpl := web predložak: ['templates/ux.tpl'].
```

Sustav predložaka koristi oznake. 
Postoje tri vrste oznaka: oznake za izrezivanje, oznake za lijepljenje i
oznake utora. Osnovna je ideja doista jednostavna: izrežete
područja označena oznakama za izrezivanje i možete ih zalijepiti na
područja označena oznakama za lijepljenje. Tekstove možete ubaciti u
oznake utora.

Tako, primjerice, uz sljedeći predložak, stavimo
dragulj u kutiju za nakit i dodajmo cijenu.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

To možete učiniti ovako:

```
>> gem := tpl izreži: ['gem'], kopiraj.
gem price: 99.
tpl zalijepi: gem na: ['jewels'].
web ispiši: tpl očisti.
```

Posljednji redak jednostavno šalje predložak kao tekst klijentu
zajedno s potrebnim HTTP zaglavljima.

Rezultat:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

Za sigurno posluživanje datoteka koje su prenijeli korisnici možete se osloniti na passthru:

```
>> preneseno := ['smile.gif'].
Server proslijedi: preneseno prefiks: ['/uploads/images/'].
Program kraj.
```

Time će se sadržaj koji je prenio korisnik poslužiti s odgovarajućom
vrstom mime. Podržane su samo vrste mime s popisa dopuštenih:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF i SVG.
Datoteke SVG, ZIP i GZIP šalju se kao preuzimanje, jer SVG
može sadržavati skripte koje bi se inače izvodile na vašoj domeni.
Ova metoda sprječava TOCTOU napade, obilazak putanja (path traversal), 
izvršavanje zlonamjernog koda (injekcije), napade simboličkim poveznicama,
DDoS napade (ograničenje datoteke = 50MB), napade prisluškivanjem i 
razne druge sigurnosne probleme.


## JSON

Za kodiranje objekta kao JSON:

```
>> json := ( JSON jsonify: ( 
	Rječnik novi stavi: ( 
		Popis novi ; 1 ; 2 ; 3
	) na: ['abc']
)).
```

Za dekodiranje JSON-a u xoscript objekt:

```
>> rječ := ((JSON objekt: json) abc ? 1).
```

JSON s više od 500 razina ugniježđivanja odbacuje se kao nevaljan.

Za izravni ispis Rječnika kao json s ispravnim zaglavljima:

```
web json: rječ.
```


## Regularni izrazi

Regularne izraze možete koristiti stvaranjem uzorka.
Primjerice, za podudaranje atributa href i target u hipervezama:

```
Uzorak novi: ['href="([^"]+)" target="([^"]+)"'].
```

Sada primijenite uzorak na tekst koji se pretražuje, ovako:

```
obrazac podudaranje: predmet učini: { :m :x .... }
```

Cjeloviti primjer:

```
>> predmet := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> obrazac := Uzorak novi: ['href="([^"]+)" target="([^"]+)"'].
>> rezultat  := obrazac podudaranje: predmet učini: { :m :x
	Izlaz piši: m, novi-red.
	Izlaz piši: x, novi-red.
	<- ['XXX'].
}.
Izlaz piši: rezultat, novi-red.
```

## Umrežavanje

Za izvođenje web-zahtjeva koristite objekt Mreža.
Objekt Mreža uvijek šalje zahtjev POST, osim ako kao
podatke pošaljete Ništa; tada šalje zahtjev GET.


```
Mreža 
post: Ništa 
na: ['https://redbeanphp.com'].
```

## Šifriranje

Poslužiteljski dodatak dolazi sa šifriranjem temeljenim na XChaCha20 i Argon2.

Primjer:

```
>> šifrirano := Sef šifriraj: ['hello'] ključ: ['world'].
>> dešifrirano := Sef šifriraj: šifrirano ključ: ['world'].
```

## Tokeni

Za generiranje kriptografski sigurnog tokena određene duljine:

```
>> mojtoken := Sef token: 40.
```

Time će se generirati token od 40 znakova.

## Formatiranje

Objekt Format omogućuje formatiranje podataka, poput dopunjavanja ili
dodavanja nula. Koristi sintaksu printf.

```
>> fmt := Format novi: ['%06.0f'].
fmt primijeni: 56. # daje 000056
```

Format može sadržavati jednu pretvorbu i ona mora odgovarati vrijednosti,
inače ćete dobiti pogrešku:

- `primijeni:` s tekstom: `%s`
- `primijeni:` s brojem: `%f`, `%e`, `%g` ili `%a`
- `primijeni-cijeli:` s brojem: `%d`, `%i`, `%o`, `%u`, `%x` ili `%c`

Vrijednosti iz zahtjeva su tekstovi. Da biste jednu od njih formatirali kao broj,
najprije je pretvorite:

```
fmt primijeni: (zahtjev get: ['amount']) broj.
```

## Koderi

Dostupno je nekoliko kodera i dekodera.
Koder url priprema url za korištenje u HTML-u kao poveznicu:

```
Server url-kodiraj: ['https://example.com?a=6&b=1 2'].
```

Da biste korisnički unos sigurno ubacili u svoj HTML bez rizika od XSS
injekcija, uvijek koristite:

```
Server html-kodiraj: ['<harmless>'].
```

Imajte na umu da će sustav predložaka uvijek izvesti html kodiranje
kada pišete u oznaku utora. Dakle, ako koristite sustav predložaka,
ovo ne morate koristiti.

## Slanje pošte

Za slanje pošte koristite biblioteku mailtools.xo.

Primjer:

```
Server inicijaliziraj.
Program koristi: ['mailtools.xo'].

>> e-pošta := HTML-Email novi.
>> img := e-pošta priloži: ( Datoteka novi: ['myimage.png'] ).

e-pošta
pošiljatelj: ['xo@xoscript.com'] naziv: ['xo'],
prima: ( Popis novi ; ['xo2@xoscipt.com'] ),
predmet: ['xoxo'],
tijelo: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), pošalji.

```



## Povezivanje

Pomoću poruke poveži: možete vanjsku biblioteku povezati sa
svojim programom koristeći libffi. Za detalje pogledajte poglavlje o ffi.


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

FFI se pruža ovisno o platformi/dodatku jer je
vezan uz temeljnu arhitekturu sustava, a to nešto što
jezgra ne bi trebala raditi.
Poslužiteljski dodatak nudi sukladnu implementaciju ffi/blobova.
Prema zadanim postavkama jezgra se povezuje s ciljnom platformom
putem stdin/stdout, ograničenih usluga datotečnog U/I-ja i ljuske (Program sustav:).
Dodatnu integraciju pružaju ffi/blobovi putem dodataka usmjerenih
na aplikacije, poput poslužiteljskog dodatka.

FFI je kratica za Foreign Function Interface (sučelje za strane funkcije). Omogućuje vam korištenje funkcionalnosti koju su drugi napisali u
drugim programskim jezicima, a koja se pruža putem DLL datoteka, SO datoteka ili Dylib datoteka. To može
biti mnoštvo različitih funkcija, a ovom je metodom dostupan golem raspon funkcionalnosti.
Počnimo s primjerom:

```
Server poveži: (
 Popis novi ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Popis novi ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s oslobodi.
```

Rezultat ovog koda je da ćete u naredbenom retku vidjeti sljedeće:
FFI has 3 letters.
Sada vjerojatno mislite: "To je puno koda za nešto tako jednostavno."
Mislim, zar to ne bismo mogli riješiti naredbom Gui show? Odgovor je odlučno da!
No ovo je zamišljeno kao ilustrativni primjer.
FFI se obično koristi za složenije zadatke, ali oni nisu dobri
primjeri, pa sam odabrao nešto trivijalno.

Argumenti metode link:

- Argument #1: DLL ili SO datoteka koju želite koristiti.
- Argument #2: Funkcija u toj datoteci koju želite povezati.
- Argument #3: Popis s nazivima tipova podataka argumenata funkcije.
- Argument #4: Naziv povratnog tipa funkcije.
- Argument #5: Naziv objekta s kojim želite povezati ovu funkciju (ako ne postoji, bit će
automatski stvoren).
- Argument #6: Poruka s kojom ova funkcija treba biti povezana.

U gornjem primjeru želimo povezati funkciju printf iz libc.so. Nazive tipova podataka
možete pronaći u dokumentaciji softvera s kojim se povezujete. Dostupni tipovi su:
void, pointer, float, double, int, uint, char, uchar, intX i uintX,
gdje X može biti 8, 16, 32 ili 64.

Ti se tipovi odnose na broj bajtova potrebnih za pohranu podataka. Za printf povezujemo se s
novim objektom pod nazivom Printf i porukom template:number:. Vanjsku
funkciju prevodite u dijalekt XOScripta prije nego što je upotrijebite. Poruka template:number: kao prvi
parametar očekuje međuspremnik s tekstom predloška. Taj međuspremnik stvaramo pomoću objekta Blob, koji
omogućuje ručno dodjeljivanje memorije. Vi ste odgovorni za naknadno oslobađanje te memorije
porukom oslobodi.

Memorijski blob možete ispuniti na različite načine. U našem ga primjeru ispunjavamo tekstom, pa koristimo
poruku utf8: (UTF-8 je kodiranje za pretvaranje teksta u bajtove). Blob možete ispuniti i
porukom bytes:, prosljeđujući popis vrijednosti bajtova. Za čitanje sadržaja bloba koristite od:duljina:.
Bajtove ćete dobiti natrag kao popis. Pomoću Bloba možete čak stvoriti i C-strukturu porukom
struct:, prosljeđujući niz C tipova. To može biti potrebno pri pozivanju C
funkcije u vanjskoj softverskoj biblioteci koja očekuje pokazivač na strukturu.

{warning}
Blobove morate osloboditi sami.
Sakupljač smeća ne čisti blobove.
{/warning}

Budući da se blobovi mogu razmjenjivati s vanjskim funkcijama iz biblioteka, sakupljač smeća
ih ne može automatski očistiti (vanjske ih funkcije možda još uvijek koriste
ili ih te vanjske funkcije možda žele same
osloboditi). Stoga blobove po potrebi morate osloboditi sami.

Za oslobađanje bloba koristite:

```
mojblob oslobodi.
```

Za oslobađanje strukture koristite:

```
mojastruktura oslobodi-struct oslobodi.
```

Dakle, za strukturu morate poslati dvije poruke: oslobodi-struct i oslobodi kako biste
oslobodili memorijski blok.

@api_Blob_fficonnect
