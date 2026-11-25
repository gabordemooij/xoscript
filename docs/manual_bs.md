# Osnove

{{messages}}


Dobro došli u XOScript
Cilj projekta XOScript je stvoriti skriptni jezik koji je jednostavan i provjerljiv.
Jednostavno ne znači nužno i lako.
Poznati programski jezik može biti lakši za korištenje od XOScripta.
Ovdje jednostavnost znači nešto drugo:
mogućnost da se izgradi potpun mentalni model jezika i njegovog ponašanja.

XOScript je osmišljen tako da vam stane u glavu.
Njegova gramatika i broj koncepata namjerno su mali.
Nema klasa; objekti se mogu direktno proširivati.
Objekti se prenose po referenci, kopiranje je eksplicitno,
a funkcije imaju jednu tačku izlaza.

Neki od ovih izbora znatno se razlikuju od uobičajenih jezika.
XOScript, na primjer, nema sistem tipova i koristi dinamički doseg.
Poruke koje se ne mogu obraditi ignorišu se umjesto da izazovu izuzetak.
Ovi izbori imaju posljedice i nisu namijenjeni uklanjanju grešaka.
Njihova svrha je da osnovni model jezika ostane mali i dosljedan.

XOScript se također može lokalizovati, što omogućava da se poslovna
pravila izraze prirodnim jezikom i potencijalno podijele sa netehničkim zainteresovanim stranama.

Provjerljivost znači primjenu iste filozofije na implementaciju.
Okruženje za izvršavanje napisano je u C-u, sa malim ručno napisanim lekserom, parserom i obilaznikom stabla.
Standardna biblioteka i okruženje za izvršavanje u velikoj mjeri odražavaju strukturu jezika,
pa je veza između XOScript koda i njegove implementacije relativno direktna.

Testovi su također usko povezani sa dokumentacijom.
Svaka metoda treba imati pripadajući test koji se može uključiti u priručnik,
što pomaže da dokumentacija ostane usklađena sa implementacijom.

XOScript nije namijenjen da se takmiči sa uobičajenim jezicima po
mogućnostima ili poznatosti. On istražuje drugačiji cilj:
programsko okruženje koje programer može razumjeti kao cjelinu.

Nada je da mali jezik i mala
implementacija čine praktično mogućim razumijevanje softvera
od bajta do objekta, od sintakse do okruženja za izvršavanje, i pisanje koda sa
samopouzdanjem jer razumijete i šta se dešava u
skripti i šta se dešava ispod haube.

Arhitektura serverske postavke xoscripta
je jednostavna, a ipak fleksibilna.

{{architecture.png}}

Da biste koristili xoscript kao serverski jezik, morate instalirati
serverski dodatak u folder pod nazivom /mods/server. 

To je zato što želimo
odvojiti osnovni jezik od funkcionalnosti specifičnih za server,
za razliku od, na primjer, PHP-a ili Pythona. Inače bismo svima morali isporučiti
sve i svašta bez ikakve svrhe, što je jednostavno besmisleno.
Možete instalirati i druge module ako želite. Sistem je vrlo
fleksibilan.

Također, neke funkcije je bolje implementirati u samom skriptnom
jeziku, kao što su šabloni i upravljanje sesijama, pa dodatno
isporučujemo biblioteke template.xo i webtools.xo radi vaše udobnosti.
Razlog za sve ovo je to što ne znamo kako želite
koristiti xoscript. Možete ga koristiti kao serverski skriptni jezik,
ali i za grafička sučelja, ugrađene uređaje ili jednostavno serijsku obradu.
Čak i ako ga koristite kao serverski skriptni jezik (što je
trenutno jedan od glavnih slučajeva upotrebe), možda ćete ipak htjeti
koristiti drugi mehanizam šablona ili drugi upravitelj sesija.
Ko smo mi da odlučujemo da trebate koristiti naše?

Ipak, jedna od prednosti korištenja našeg mehanizma šablona je to što
ne morate učiti dodatnu sintaksu za pravljenje šablona.
Zadani mehanizam šablona koji dolazi uz xoscript koristi 100%
razdvajanje prezentacije i logike. Umjesto posebne
sintakse šablona, on jednostavno koristi vrlo fleksibilan sistem oznaka utora.
Za više informacija pogledajte poglavlje Server.

Imajte na umu da, ako ne želite koristiti zadani mehanizam šablona ili
zadane web alate, podrazumijeva se da morate obezbijediti
vlastite.

Ako vaš web server radi u chrootu, jailu ili nekoj drugoj vrsti sandboxa,
u tom okruženju morate instalirati i zavisnosti za xo; koje
biblioteke su vam potrebne možete vidjeti pomoću ldd (pogledajte man stranicu za Linux ili BSD).
Ako želite koristiti shell naredbe u svojim xo skriptama, kopirajte i shell
(kao što je bash ili ksh) u to okruženje.

Također želimo napomenuti da vrlo ozbiljno shvatamo kompatibilnost unazad.
Postoji čak i posebna mogućnost za kompatibilnost unazad pod nazivom
'version'. Općenito, cilj nam je da vaš kod radi zauvijek. Dakle, nikada
nećete morati ažurirati svoj kod da bi ostao kompatibilan sa novijim verzijama
xoscripta. Naš cilj je: napiši jednom, pokreći zauvijek.

Ostatak ovog priručnika posvećen je detaljnom objašnjenju programskog
jezika xoscript. Serversko skriptiranje obrađeno je u poglavlju
pod nazivom Server. Ako ste iskusan programer, možda ćete htjeti
preskočiti nekoliko poglavlja jer su neka od njih malo previše detaljna ili
su vrlo slična općim programerskim praksama. Zato onima od vas
koji već imaju iskustva sa nekoliko drugih programskih jezika
savjetujemo da ovaj priručnik koriste kao referentni vodič.

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

Kopirajte datoteke u webroot i /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Uredite svoju apache2 konfiguraciju:

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
>> veb := Web-dokument novi.
veb ispiši: ['Hello World'].
```

Dozvolite apache2 da izvršava vaš program putem CGI-ja:

```
sudo chmod uog+x /var/www/html/test.xo
```

Ponovo pokrenite apache2:

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
odaberite mlkem šifru:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Dodajte xo izvršnu datoteku i module, kao i sve zavisnosti, u
chroot (saznajte koje pomoću ldd).

## Pokretanje primjera


Da biste pokrenuli jedan od primjera programa iz paketa:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Na primjer, da biste pokrenuli primjer FizzBuzz na Linuxu:

```
./example.sh fizzbuzz Linux
```

Da biste pokrenuli isti primjer na OpenBSD-u:

```
./example.sh fizzbuzz OBSD
```

Da biste pokrenuli primjer uz čisto prevođenje:

```
./example.sh fizzbuzz OBSD clean
```

## Jedinični testovi

Da biste pokrenuli jedinične testove:

```
./runtests.sh
```

Da biste pokrenuli jedinične testove bez prevođenja (samo testiranje):

```
./runtests.sh nobuild
```

## Prevođenje

Da biste preveli iz izvornog koda na Linuxu:

```
make clean
ISO="en" make
```

Na OpenBSD-u:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

Da biste preveli serverski dodatak na Linuxu:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

Da biste preveli serverski dodatak na OpenBSD-u:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Zdravo, svijete

Nakon što je datoteka prenesena na vaš računar, možete je raspakovati
i pokrenuti xo sljedećom naredbom:

```
xo
```

Da biste pokrenuli XOScript, sačuvajte program kao datoteku dodavanjem
sufiksa -xo (opcionalno). Pored toga, nakon XOScript naredbe upišite
naziv datoteke vašeg programa:

```
xo myprogram.xo
```

Kada pokrenete XOScript naredbu i kao parametar navedete datoteku
svog programa, xo će pročitati i izvršiti vašu programsku datoteku.

{{note}}
Program možete pokrenuti i tako što ćete ga prevući na ikonu xo.
{{/note}}

{{warning}}
Na nekim sistemima morate prethodno dati xo dozvolu za učitavanje dinamičkih
biblioteka.
{{/warning}}

Tradicija nalaže da prvi program u svakom novom programskom
jeziku bude neka vrsta pozdrava svijetu. U XOScriptu takav
program **Hello world** izgleda ovako:

@test598

Kada se ovaj tekst sačuva u datoteku, npr. hello.xo, može se izvršiti na
sljedeći način: .

xo hello.xo

Hello world


Izlaz programa možete vidjeti u crnom prozoru prikazanom iznad.
Kroz cijeli ovaj priručnik isti prikaz koristit će se za prikazivanje
izlaza.

{{note}}
Izlaz se piše velikim slovom I.
Općenito, objekti počinju velikim slovom,
osim ako se ponašaju kao instanca (nemaju vlastite
metode, samo podatke). Ovo odražava konvencije
klase i instance u drugim programskim jezicima.
{{/note}}


## Sintaksa 

XOScript je *čisto* *objektno orijentisan* programski jezik. To znači
da xoscript sve doživljava kao objekat, pa stoga ne postoje
drugi *tipovi podataka*. U programu napisanom u XOScriptu u suštini postoje
tri osnovne rutinske radnje: *dodjeljivanje*, *slanje poruka*
i *odgovaranje*. Razmjena poruka između objekata ključni je dio
XOScript programa. Tri pojedinačne rutinske radnje prikazane su
u nastavku:


Radnja          | Primjer
--------------- | --------
dodjela         |  \>\> x := 1. 
unarne poruke   | x paran?.
binarna poruka  | 1 + 2.
poruka s ključnim riječima | x od: 0 dužina: 10.
odgovor         | <- answer.  


Ovo poglavlje dat će vam opći utisak o jeziku XOScript
i opisuje njegove osnovne principe. XOScript je mali jezik
zasnovan na tri radnje (pogledajte ilustraciju) koje se prevode u
otprilike šest gramatičkih pravila. To je sve što je potrebno da savladate
jezik.

Ne brinite ako vam stvari odmah nisu jasne: svi gradivni
elementi bit će istraženi u sljedećem poglavlju (3), a osnovna pravila bit će
ponovljena. Ovo poglavlje, međutim, služi uglavnom kao opći
uvod u jezik. Osnovni principi bit će ukratko
objašnjeni i ilustrovani s nekoliko relevantnih primjera. Svi detalji koji nedostaju
bit će opisani kasnije.

Komentari u XOScriptu počinju simbolom \#. Dakle, sljedeći red
bit će ignorisan:

```
# ovo je samo komentar
```

## Varijable

Da biste dodijelili
varijablu, koristite simbol za deklaraciju varijable: >>. Naziv
varijable može sadržavati sve znakove osim: <-, :=, razmaka,
tačaka, zareza, dvotačaka, navodnika [' '] i zagrada ().
Nadalje, varijabla se ne može protezati kroz više redova. Imajte na umu
da varijabla ne može počinjati brojem ili znakom minus.

Ovo su primjeri ispravnih varijabli:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dolar'].
>> +plus := Tačno.
>> lozinka-korisnika := ['Pssst!'].
```

Neispravne varijable su, na primjer:


```
>> -123 := ['negativan broj'].
>> password of korisnik := ['Povjerljivo'].
>> password.of:korisnik := ['Povjerljivo'].
>> ,x := 10.
```

{{note}}
Ni jedan znak ne morate escapeovati
(uključujući navodnike, dvostruke navodnike, granice
teksta) u
tekstualnom literalu sve dok to ne
izaziva dvosmislenost za lekser.
{{/note}}

Nakon što je varijabla deklarisana, može se slobodno koristiti. To znači
da je simbol za deklaraciju potrebno koristiti samo prvi put
kada koristite varijablu (deklaracija).

Preciznije, ne možete tek tako početi dodjeljivati vrijednost
svojoj varijabli *(x := 2)*, jer prvo morate deklarisati varijablu *(\>\>
x := 2)*. Međutim, nakon deklaracije smijete mijenjati njenu vrijednost
bez korištenja simbola za deklaraciju*(\>\> x := 2. x := 3.)*.

Imajte na umu da je obavezno dodijeliti vrijednost varijabli u trenutku
deklarisanja. Za razliku od drugih programskih jezika, nije dozvoljeno
deklarisati varijablu bez vrijednosti. Neophodno je svaku varijablu eksplicitno
vezati za početnu vrijednost. Ipak, slobodno inicijalizirajte
varijablu objektom **Ništa**. U tom slučaju varijabla se može
smatrati praznom *(\>\> x := None.)*. Ukratko, deklarisanje
varijable bez početne vrijednosti nije dozvoljeno. Dakle,

```
>> x.
```

je neispravno i dat će poruku o grešci.

{{note}}
xoscript koristi dinamički doseg varijabli; za
detalje pogledajte poglavlje Funkcije.
{{/note}}


## Literali

XOScript sve doživljava kao objekat, tj. sve brojeve, tekstove
i fragmente koda. Brojevi, kao što su 1, 2, 100, -999 i 1,234, jesu
objekti Broj. Svi tekstovi između jednostrukih navodnika su objekti
Tekst. Svi fragmenti koda grupisani između vitičastih zagrada {...} su
objekti Funkcija.

Literal         | Korijenski objekat | Primjer
--------------- | ------------ | ----------
brojevi         | Broj         | 1,2,3... 
tekstovi        | Tekst        | \['hello'\]
funkcija        | Funkcija     | { 1 + 2. }.
                
     
Objekti kao što su brojevi i tekstovi uvijek potiču od korijenskog
objekta. Na primjer, svi brojevi potiču od objekta **Broj**. Svi
tekstovi potiču od **Tekst**, a svi fragmenti koda od **Funkcija**. Svi ovi
objekti, opet, potiču od **Objekat**, koji je, zapravo,
korijenski objekat svih objekata.


## Poruke

Programiranje u XOScriptu u osnovi znači
slanje poruka objektima. Opća notacija za slanje poruke
objektu je sljedeća:

```
<object> <message>
```

Da bismo saznali da li je broj **2**, na primjer, paran broj,
objektu **2** šalje se poruka **paran?**:

```
2 paran?
```

Odgovor će biti **Tačno** (opet, objekat). Objekti nepoznate poruke
obično ignorišu, tako da neće doći do greške. Neki objekti (npr.
brojevi ili tekstovi) na nepoznatu poruku odgovaraju na unaprijed definisan način
(više o ovoj temi kasnije).

Objekat može primiti tri vrste poruka. 

Vrsta           | Broj argumenata
--------------- | -------------------
Unarna          | 0      
Binarna         | 1     
S ključnim riječima | 1+    


Prvo, postoje **unarne
poruke**, pogledajte primjer iznad, koje nemaju argumente. Drugo,
postoje **poruke s ključnim riječima**, koje imaju jedan ili više argumenata,
na primjer:

```
>> x := Broj između: 1 i: 10.
```

U ovom slučaju poruka **između:i:** šalje se objektu **Broj**, koji
je korijenski objekat svih brojeva. Rezultat će biti nasumičan broj
između 1 i 10. Konačno, postoje **binarne poruke**, koje imaju
samo jedan znak i jedan argument:

```
2 + 3
```

Ovo izgleda kao matematički zbir, ali je zapravo samo još jedna poruka.
Poruka **+** šalje se broju **2** sa argumentom **3**, što će vratiti
odgovor **5**. Binarne poruke smiju se pisati bez dvotačke.

Binarne poruke mogu se ulančavati:

```
>> x := 3 + 2 - 1.
```

U ovom fragmentu **+ 2** se prvo šalje objektu **Broj** **3**, što
rezultira objektom Broj **5**, nakon čega se **-1** šalje ovom
broju. Pažljivi čitaoci s pravom primjećuju odstupanje koje
ovaj protokol pokazuje u odnosu na uobičajeni matematički redoslijed
operatora. XOScript ignoriše matematički redoslijed u korist
dosljednosti svog sistema poruka. Kao rezultat toga, zbir:

```
2 + 3 * 5 = 25
```

a ne 17.

To je namjerno. Zagrade se mogu koristiti za promjenu redoslijeda:

```
2 + (3 * 5) = 17
```

Većina objekata kao odgovor na određenu poruku vraća same sebe
kao rezultat. To je korisno jer podstiče nastavak dijaloga s ovim
objektom slanjem nove poruke:

```
Izlaz piši:
[' zdravo '] skrati velika-slova.
```

```
ZDRAVO
```

Ovdje se objektu **Tekst** šalju dvije poruke: **skrati**, a zatim
**velika-slova**.

U sljedećem fragmentu upotreba zareza je neophodna da bi se naznačilo
da dolazi nova poruka. U suprotnom, XOScript će se zbuniti.

```
Izlaz piši: ['Hello!'], novi-red.
```

Prvo se poruka **piši:** šalje simbolu olovke, a zatim
**novi-red**. Bez zareza, XOScript bi mislio da želite poslati
**novi-red** objektu **tekst** **Hello!**, što je uzaludan posao.

Redoslijed obrade poruka je sljedeći: s lijeva na desno;
počnite s porukama u zagradama, a zatim unarnim porukama. Zatim
binarne poruke, i na kraju poruke s ključnim riječima. Pogledajte primjer
u nastavku:

```
Izlaz piši: 0.5 zaokruži + (2 - 1), novi-red.
```

XOScript uvijek čita s lijeva na desno: prvo se poruka **piši:**
šalje objektu Izlaz, a zatim poruka **novi-red**. Unutar
samog argumenta XOScript čita s lijeva na desno, dakle prvo **0.5 zaokruži**,
a zatim **+**.

{{note}}
Poruka novi-red dodaje znak za novi red u tekst.
Naziv ove poruke inspirisan je telegrafskim sistemima.
Poruke u telegrafskim sistemima 
često su koristile riječ STOP da označe kraj rečenice
(jer je interpunkcija bila nepouzdana ili skupa).
{{/note}}

Osim toga, **zaokruži** ima prednost nad **+**, jer je to
**unarna poruka**. Zbog zagrada se **2 - 1** računa
prvo, nakon čega se **1** dodaje rezultatu od **0.5 zaokruži** (1).

Cijeli proces dat će rezultat **2**, što je ujedno i ispisani
odgovor. Nakon zareza slijedi poruka novi-red, koja pomjera kursor
u novi red. Naravno, najbolji način da potpuno shvatite redoslijed
izvršavanja XOScript programa jeste vježba.

Vrijedi napomenuti da su u XOScriptu, za razliku od mnogih drugih programskih
jezika, razmaci temeljni dio sintakse. Naročito
kada je riječ o binarnim porukama, razmaci mogu izazvati određenu
zabunu. Uvijek koristite razmak nakon binarne poruke. Broj ne možete
direktno spojiti s porukom, na primjer: 

```
3 + 2
```

razlikuje se od 

```
3 +2
```

Prvi primjer (**3 + 2**) šalje
poruku **+** broju **3**, sa argumentom brojem **2**.
Rezultat će u ovom slučaju biti **5**. U drugom primjeru (**3 +2**)
broju **3** šalje se unarna poruka **+2**. Zavisno od
konteksta, to može dati sasvim drugačiji rezultat.

## Nepostojeće metode

Slanje poruke objektu poziva funkciju koja je
vezana za taj objekat pod nazivom te poruke. Ako pošaljete poruku
koja nije razumljiva, objekat primalac ignorisat će vašu poruku
i umjesto toga vratiti referencu na samog sebe za daljnju komunikaciju.
To se naziva tolerantno prenošenje poruka.

Primjer:

```
Izlaz piši: Objekat blah, novi-red.
```

Ovo neće izazvati grešku. Jednostavno će ispisati tekst **Objekat**.


## Kontrola toka

U XOScriptu nema potrebe za zasebnim gramatičkim pravilima za *petlje* i
*uslove*. If-naredba je samo jednostavna poruka **tačno:** ili **netačno:**
objektu **Tačno** ili objektu **Netačno**:

```
2 paran? tačno: {
	Izlaz piši: ['Dva je paran broj'], novi-red.
}.
```
U prethodnom primjeru poruka **tačno:** šalje se objektu **Tačno** (
odgovoru na pitanje: da li je 2 paran broj?). Kao argument se šalje i dodatni
fragment koda: objekat **Funkcija**. Ova funkcija ispisuje na
ekran da je 2 zaista paran broj.

Nema potrebe ni za zasebnim pravilima pisanja za *petlju*. Da biste
izvršili fragment koda tri puta, jednostavno pošaljite **\*** sa argumentom
**3** toj **Funkciji**:

@test5

U ovom fragmentu koda **i** je indeks. Dakle, prvi put kada se Funkcija
izvrši, **i** je jednako 0, sljedeći put kada se izvrši, **i** = 1 i
tako dalje.

Razmotrimo još jedan primjer. Kada treba ispisati tabelu pretvaranja
iz *kJ* (kilodžula) u *kcal* (kilokalorije) u koracima od 100,
ispravna notacija je prikazana u nastavku:

@test599

Ovdje se broj trenutnog reda prenosi parametru
**:line**. Na početku funkcije definišu se parametri
funkcije. Neiskorišteni parametri ostaju prazni (**Ništa**). Parametri se
uvijek nalaze na početku funkcije, odmah nakon početne
vitičaste zagrade, i ispred njih stoji dvotačka.

Poruka **dok:** je kombinacija *petlje* i *uslova*.
Dvije funkcije mogu se povezati pomoću poruke **dok:**. Funkcija primalac
nastavit će se izvršavati sve dok funkcija nakon dvotačke ne da negativan
rezultat. Primjer:

@test600

U gore prikazanom fragmentu koda **1** se dodaje na **x** sve dok je
**x** manje od **5**. Kada to više nije slučaj, druga
funkcija odgovorit će s **Netačno**, pa će se izvršavanje
prve funkcije završiti. Imajte na umu da je **x** definisan izvan
funkcije i da je globalna varijabla. Da biste saznali više o pravilima dosega,
pogledajte poglavlje o Funkcijama.

## Interpolacija teksta

Lista *kJ/kcal* mogla bi se učiniti
preglednijom. Poželjno bi bilo da lista izgleda ovako:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Kada željeni izlaz pretvorite u šablon, njegova notacija
mogla bi biti:

```
number1 kJ ➞ number2 kcal
```

To znači da **number1** predstavlja vrijednost u kJ, a **number2**
vrijednost u kcal. Ovako funkcioniše interpolacija teksta u XOScriptu. Za to
u XOScriptu nisu potrebna zasebna gramatička pravila. Jednostavno pošaljite
tekstu riječ koju treba zamijeniti, sa zamjenskim tekstom
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

Ovo pravilo zamjene važi za svaku nedefinisanu poruku koju
primi objekat **tekst**. Svaka poruka koju objekat **tekst**
ne prepozna bit će protumačena na sljedeći način: *zamijeni tekst
poruke tekstom iz argumenta poruke.* Program možete
prilagoditi na sljedeći način:


@test601


Da biste izbjegli zabunu oko toga koja se poruka može ili ne može koristiti kao
zamjena, najbolje je uvesti oznaku šablona kao što je &lt; &gt;
za dijelove teksta u šablonu koje
treba zamijeniti.

## Povratne vrijednosti

Za odgovor na poruku koristi se povratna strelica
(*<-*). Sljedeći primjer pokazuje kako napraviti zadatak
za izračunavanje procenta:

@test602

Nakon što je zadatak definisan i dodijeljen varijabli **percentage**,
šalje se poruka **primijeni:i:** sa argumentima **100** i **7**.

Ovo će izvršiti zadatak primijenjen na **100** i **7**, tj. 7% od 100.
Pomoću povratne strelice odgovor se vraća iz zadatka nazad
u glavni program.

## Proširivanje

Iako je ovaj kod ispravan, ima nedostatak
jer se mora pamtiti redoslijed argumenata. Pa zašto ga ne bismo
napisali ovako: *7 percent of: 100 *? To bi izgledalo mnogo
*prirodnije*. Da bismo to omogućili, moramo prilagoditi roditeljski objekat
od **7**, a to je objekat **Broj**, tako da razumije
poruku **percent of:**. To se može postići slanjem **na:uradi:**
objektu Broj, ovako:

@test603

Kako je procenat u ovom slučaju sam broj, pozivamo se na sebe,
ključnu riječ *sebe*. Ukratko, simbol sebe znači: *pošalji ovu
poruku meni samom*.

# Objekti

{{messages}}

Osim prilagođavanja i proširivanja postojećih objekata, možete i sami
praviti nove objekte jednostavnim slanjem poruke **novi**. Pretpostavimo da
želite napraviti objekat fakture koji nameće redoslijed
numerisanja; u tom slučaju prvo vam je potreban objekat fakture.

Znajući da svaki objekat potiče od nekog drugog objekta, koji, opet,
na kraju potiče od korijenskog objekta svih objekata pod nazivom Objekat,
treba odlučiti na kojem od tih drugih objekata će se zasnivati vaš
novi objekat. Vaš novi objekat nasljeđuje sva svojstva
objekta na kojem je zasnovan, dakle onog kojem je poruka **novi**
prvobitno poslana.

U ovom primjeru poželjan je prilično neutralan objekat, bez previše
naslijeđenih svojstava. To olakšava izbor, jer se u tom
slučaju novi objekat može zasnovati na samom korijenskom objektu, a to je
**Objekat**. Notacija namjeravanog sistema faktura tada će biti
sljedeća:

@test604

Trenutni broj fakture čuva se u objektu, zbog čega se ispred njega
nalazi ključna riječ **svoj**. To se naziva *svojstvo*;
više detalja slijedi.

Neke firme više vole da godina bude uključena u brojeve
faktura. U tom slučaju možete napraviti novi objekat fakture zasnovan na
prethodnom objektu fakture, ali koji svom korisniku nudi mogućnost
da unese određenu godinu:

@test605

Nema potrebe ponovo pisati implementaciju poruke **broj**,
jer se ona nasljeđuje od prethodno napisanog **objekta
fakture**; stoga se stari kod može ponovo iskoristiti. XOScript nema koncepte
kao što su klase i drugi srodni koncepti. To znači da objekti mogu
nasljeđivati isključivo od drugih objekata, što je poznato i kao *prototipsko
nasljeđivanje*.

Vratimo se sada svojstvima. Svojstvima objekta može se pristupiti samo
*unutar hijerarhije objekata*, pa ta svojstva
ne mogu vidjeti drugi objekti.

Za razliku od drugih programskih jezika, sva svojstva objekata
vidljiva su isključivo objektu koji je napravio svojstvo i
izvedenim objektima. 

Često korištena tehnika je upotreba objekta kao neke vrste *nacrta*,
što je, na primjer, slučaj s ranije opisanim fakturama.
Još jedan dobar primjer je **Point**. Recimo da pravite
računarski program koji vrši proračune koristeći tačke na mapi. Možete
razviti objekat **Point** koji sadrži svojstva
x-koordinate i y-koordinate, koja će biti dostupna
vanjskom svijetu putem poruka:

@test606

Poruka **=** upoređuje dvije tačke pomoću poruke **i:**. Prvo
poređenje rezultira objektom **Tačno** ili **Netačno**. To su logički
objekti. Kada pošaljete poruku **i:** objektu Tačno, a
objekat argumenta nakon dvotačke je također **Tačno**, tada ćete
kao odgovor ponovo dobiti **Tačno**. Kada je bilo koji od njih **Netačno**, dobit ćete
odgovor **Netačno**. Imajte na umu da jedna tačka ne može čitati koordinate
druge. Neophodno je poslati poruku drugoj tački kako bi se zatražili
ti podaci: **x-coordinate** i **y-coordinate**. Uostalom, kao što je
već objašnjeno, svojstva se mogu dohvatiti isključivo unutar
same porodice objekata. 

Imajte na umu da se poruka **=** ovdje koristi za izvršavanje poređenja
tačaka. Jednako tako se mogla koristiti i neka druga poruka, kao što je
**is:** ili **equal:**, ali ponovna upotreba znaka **=** činila se
prikladnom u ovom slučaju.

## Nasljeđivanje

Prethodno napisani kod možete ponovo iskoristiti za pravljenje hijerarhije
objekata. Na primjer:

```
>> Životinja := Objekat novi.
>> Pas := Životinja novi.
>> Pudlica := Pas novi.
```

U ovom slučaju **Dog** nasljeđuje sva ponašanja i svojstva
objekta **Animal**, a objekat **Animal**, opet, nasljeđuje sva ponašanja objekta
**Objekat**, korijenskog objekta svih objekata.


## Nadjačavanje


U sljedećem primjeru pravi se nova vrsta liste:
**Combination**, u kojoj je osigurano da je svaki element jedinstven.
Funkcije liste ponovo se koriste putem nasljeđivanja:

@test607

Primijetite kako je drugi **red** isključen iz liste.

Ponekad može biti potrebno nadjačati ponašanje objekta.
Na primjer, kada se pri sabiranju brojeva moraju uzeti u obzir mjerne
jedinice. U sljedećem primjeru pravi se objekat **Size**.
Ovaj objekat vraća broj koji pri sabiranju uzima
u obzir jedinicu broja koji se dodaje. Objekat **Broj**
provjerava da li se radi o *inčima* ili *stopama*. Programski kod
mogao bi izgledati ovako:

@test608

## Rekurzija

U prethodnom primjeru nadjačan je **znak** plus. Imajte na umu
da se konačno sabiranje ipak mora izvršiti, što se, zapravo,
dešava u sljedećem redu:

```
>> odgovor := sebe + (broj x faktor).
```

Kako XOScript razumije da se ovaj **znak** plus odnosi na
izvornu logiku sabiranja?** Na primjer, drugo tumačenje
moglo bi biti da će XOScript uzastopno slati istu poruku istom
objektu, što bi, opet, rezultiralo **beskonačnom petljom**. Očito
to nije namjera. Čim pošaljete poruku objektu
koja bi izvršila potpuno isti kod, XOScript će shvatiti
da se u ovom slučaju misli na osnovnu, nadjačanu poruku. Dakle, vaš
program bit će automatski zaštićen od ovog oblika beskonačnih
petlji. Međutim, kada vam je zaista cilj pokrenuti istu funkciju iz
trenutne funkcije, prvo će biti potrebno poslati poruku
**rekurzivan**. U tom slučaju rezultat će biti beskonačna
petlja. Ipak, postoje korisne primjene rekurzivnih zadataka, na
primjer, pretpostavimo da želite izračunati faktorijel datog
broja. U tom slučaju jednostavno dodajte poruku **factorial** objektu
Broj:

@test609

Ovo zahtijeva rekurziju. Zapravo, zadatak koji je povezan s
porukom **factorial** treba ponovo izvršiti unutar te funkcije.
Dakle, neophodno je pozvati funkciju faktorijela iz same
funkcije faktorijela. Po pravilu, XOScript će spriječiti ovu rutinu
zbog rizika od završavanja u beskonačnoj petlji. Iz tog razloga
je ključno da se ispred poruke stavi riječ **rekurzivan**. To
se radi kako bi XOScript bio svjestan činjenice da vam je
namjera izvršiti isti zadatak i da niste napravili grešku.

## Objekti nalik klasama

Iako xoscript ne nudi klase, oponašanje ponašanja nalik
klasama je trivijalno. Jednostavno nadjačajte poruku novi.

```
>> Životinja := Objekat novi.
Životinja na: ['novi'] uradi: {
	<- sebe novi inicijaliziraj.
}.

Životinja na: ['inicijaliziraj'] uradi: {
	svoj zvuk := ['?'].
	svoj noge  := 4.
}.
```

U fragmentu koda iznad pravimo objekat pod nazivom Animal.
Ovaj objekat služi kao *nacrt* za sve vrste životinja,
kao što su psi i mačke. Roditeljski objekat Animal piše se
velikim slovom A kako bi se označilo da je to objekat nalik klasi.
Zatim nadjačavamo poruku novi pisanjem vlastite metode novi.
U ovom slučaju ona šalje poruku novi sebi, a zatim poruku
inicijaliziraj. Budući da xoscript podrazumijevano blokira rekurziju, to neće izazvati
beskonačnu petlju. Umjesto toga, poslat će poruku novi roditeljskom
objektu (Objekat), što rezultira novom instancom objekta Animal. Dakle, pravimo
novi objekat, zasnovan na istom objektu za koji smo napravili metodu novi.
To je potpuno ispravno. Sada šaljemo i poruku inicijaliziraj, čime se osigurava
da objekat Animal ima zadane vrijednosti za svoja svojstva. Podrazumijevano,
životinja ima 4 noge, a zvuk je nepoznat (otuda upitnik).
Da bismo napravili novu instancu našeg objekta Animal, mogli bismo jednostavno reći:

```
>> a := Životinja novi.
```

Sada dobijamo novu instancu objekta Animal sa 4 noge, nepoznatim zvukom i
metodom inicijaliziraj. Baš kao u drugim OOP jezicima, možemo i
proširiti naš Animal:

```
>> Pas := Životinja novi.
Pas na: ['inicijaliziraj'] uradi: {
	sebe inicijaliziraj.
	svoj zvuk := ['laje'].
}.
```

To možemo lako testirati dodavanjem metode tekst:

```
Životinja na: ['tekst'] uradi: {
	<- svoj noge tekst + svoj zvuk.
}.
```

Sastavimo sve zajedno:

@test13


Pravljenje objekta koji je postavljen u određeno početno stanje predstavlja
čest problem. Pretpostavimo da treba napraviti objekat **Rectangle**
kako bi se izračunali obim i površina. Moguća notacija bila bi:


```
>> Pravougaonik := Objekat novi.

Pravougaonik na: ['površina'] uradi: {
	<- svoj dužina * svoj širina.
}.
```

Očito je postavljanje dužine i širine preduslov. U tu
svrhu mogu se dodati poruke **dužina:** i **width:**:


```
Pravougaonik na: ['length:'] uradi: { :dužina
	svoj dužina := dužina.
}.

Pravougaonik na: ['width:'] uradi: { :širina
	svoj širina := širina.
}.

```

Ovaj pravougaonik se tada može koristiti na sljedeći način:


```
>> pravougaonik := Pravougaonik novi length: 2, width: 3.
Izlaz piši: pravougaonik površina.
```

Međutim, ako se previde početne postavke dužine i širine,
pojavit će se poruka o grešci:

```
>> pravougaonik := Pravougaonik novi.
Izlaz piši: pravougaonik površina.
```

proizvest će sljedeću grešku:

```
Ključ nije pronađen:dužina
```

Da bi se to spriječilo, poželjno je da pravougaonik
uvijek ima početnu dužinu i širinu, na primjer 0. Dakle, u ovom
slučaju neophodno je **nadjačati** poruku **novi**.

@test610

Ako nadjačamo poruku novi, u osnovi oponašamo **klasu**.

Svijet XOScripta ispunjen je raznovrsnim objektima koji su
dostupni vašem programu od samog početka. U sljedećim poglavljima
bit će opisani svi ovi osnovni objekti.

## Snimci

Objekat (zajedno s njegovim trenutnim stanjem) možete sačuvati na disk pomoću:

```
mojobjekat save-as: ['saved.bin'].
```

Da biste ponovo učitali objekat s diska:

```
>> mojobjekat := Objekat load-from: ['saved.bin'].
```

Snimci se mogu koristiti za čuvanje određenog stanja ili za poboljšanje performansi.
Učitavanje snimka izbjegava leksičku analizu, parsiranje i postavljanje aplikacije.
Također, u budućnosti bi sa snimcima mogle biti uvedene dodatne prednosti
u performansama, kao što je optimizacija određenih obrazaca ili otkrivanje i
optimizacija često izvršavanih putanja.

{{warning}}
Snimci su eksperimentalna mogućnost, nemojte ih koristiti u produkciji.
Da biste aktivirali eksperimentalne mogućnosti, prevedite s -D EXPERIMENTS.
{{/warning}}


@test712

# Objekat Ništa

{{messages}}

Objekat Ništa
predstavlja prazninu, ili još bolje, odsustvo informacije.
Povremeno ćete ovaj objekat dobiti kao odgovor na poruku, u
slučaju da je rezultat **ništa**. Najvažnije pitanje
koje možete postaviti objektu **Ništa** je: **Ništa?**.
Odgovor će uvijek glasiti **Tačno**.

```
Izlaz piši: Ništa Ništa?.
```

rezultat:

```
Tačno
```

Svaki objekat osim **Ništa** odgovorit će s **Netačno**. Gornji
fragment koda može se činiti pomalo filozofskim, ali objekat **Ništa**
svakako ima izuzetno praktične primjene. Na primjer,
objekat Ništa dobit ćete kao odgovor ako zatražite
element liste koji ne postoji. Objekat Ništa možete koristiti i
ako želite deklarisati varijablu, ali još ne želite navesti
vrijednost. Umjesto toga, jednostavno **dodijelite** posebnu vrijednost **Ništa**. U
XOScriptu nije dozvoljeno deklarisati varijablu bez vrijednosti, kao npr.:


```
>> vrijednost.
```

Umjesto toga, morate napisati sljedeće:

```
>> vrijednost := Ništa.
```

@api_None_base


# Logičke vrijednosti

{{messages}}

Za razliku od većine popularnih programskih jezika u trenutku pisanja,
XOScript ima samo jedan jedini objekat Tačno i jedan jedini objekat
Netačno. Pojašnjenja radi, svaki put kada napišete **Tačno**, to ne znači
da je napravljen novi objekat. Umjesto toga, uvijek koristite referencu. To
znači da kada napišete sljedeće:

\>\> x := Tačno.

**x** se odnosi na objekat **Tačno**. Uslovni kod i petlje također
provjeravaju ovu referencu. U XOScriptu značenje objekata **Tačno** i **Netačno**
nije fiksno. Zapravo, XOScript program se prilično uzdrma zbog
naredbe poput ove:

Tačno := Netačno.

Rezultat takvih radnji je nedefinisan, ali to ostaje ispravna
radnja i stoga je formalno dozvoljena. Nadalje, postoji objekat
Logički, koji je korijenski objekat i za **Tačno** i za **Netačno**, jer su oba
izvedena iz tog korijenskog objekta. Sam objekat Logički, međutim,
nema nikakvu praktičnu primjenu.

## Zamke

Budite oprezni s upotrebom **i:** i **ili:**

```
Izlaz piši: (Netačno or: Tačno or: Tačno), novi-red.
Izlaz piši: (Netačno ili: Tačno, ili: Tačno), novi-red.
```

Daje

```
Netačno
Tačno
```
jer poruka **ili:** prima samo 1 argument. Prvi red
šalje **ili:ili:** objektu Netačno, a ta poruka ne postoji, pa objekat ignoriše
poruku i vraća samog sebe (Netačno). S druge strane, drugi red
šalje **ili:**, a zatim još jedno **ili:** (koristeći simbol za ulančavanje, tj. zarez: ,).


@api_Boolean_base


# Brojevi

{{messages}}

Svaki put kada napišete broj, na primjer 9, -10 ili 3,12, XOScript će
iza kulisa pretvoriti te brojeve u objekat **Broj**. Ovom
objektu Broj možete slati poruke, ili možete dodijeliti broj
varijabli i nakon toga slati poruke:

```
10 paran?

>> desetka := 10.
desetka paran?

```

Obje notacije su ispravne. Objekat Broj odgovara na sljedeće
poruke...

Većina ovih poruka je samoobjašnjiva i omogućava izvršavanje
matematičkih operacija ili poređenja.

{{note}}
Imajte na umu da umjesto njihovih ASCII ekvivalenata možete koristiti ≤ ≥ ≠ × i ÷.
To je stvar ličnog izbora.
{{/note}}

Razlika između binarnih matematičkih poruka (+) i
njihovih varijanti s ključnim riječima (saberi:) je u tome što prve vraćaju
novi broj, koji je rezultat operacije, dok se kod
drugih mijenja sam objekat. To je prikazano u
sljedećem primjeru:

@test597

U gornjem primjeru b = 4, a a = 3. Sa **saberi: 2** vrijednost
od a povećava se za 2, dok **+ 3** pravi novi broj koji je
jednak a + 3. Isto važi i za druge matematičke procese, npr.
množenje. Korištenjem simbola za množenje dobit ćete
novi objekat kao odgovor. Ako koristite poruku **pomnoži-sa:**,
pomnožit ćete sam broj.

Porukom **između:i:**, na primjer u: **Broj
između: X i: Y**, dobit ćete broj između X i Y. Na ovaj
način može se generisati bilo koji nasumičan broj:

```
>> a := Broj između: 1 i: 10.
Izlaz piši: a, novi-red.
```

Od verzije 1.4 ugrađeni generator nasumičnih brojeva u xoscriptu je,
koliko nam je poznato, kriptografski siguran.

Broju možete pridružiti **odrednicu**, na primjer **6
apples**. Svaka poruka koju broj ne prepozna
smatrat će se odrednicom. Odrednicu broja možete dohvatiti
pomoću poruke odrednica:

Odrednica je u osnovi objekat Tekst koji se čuva uz objekat
Broj. Odrednica se također ispisuje nakon broja pri
dodjeli **piši:**. Odrednice bi se mogle koristiti, na primjer, za sabiranje iznosa
u različitim valutama. Pri sabiranju iznosa možete zatražiti
odrednice. Sljedeći primjer programa prikazuje ovaj
princip pomoću kalkulatora historijske valute (jer kurs
ostaje prilično stabilan!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Tekstovi

{{messages}}

Svaki put kada se tekst stavi između **uglastih zagrada i navodnika** ['...'],
XOScript će za vas napraviti novi objekat teksta. Međutim, pazite
da koristite ispravne navodnike. Navodnik na
početku teksta razlikuje se od onog na kraju (to vam omogućava
da koristite jednostruki navodnik bez potrebe da ga escapeujete).

## UTF8

Tekstovi u xoscriptu obično sadrže tekst kodiran u utf8. Iako
je tehnički moguće imati binarni sadržaj ili sadržaj koji nije utf8 u
tekstu, za to se preporučuje korištenje blobova. Blobove
obezbjeđuje serverski dodatak (pogledajte poglavlje ffi).
Općenito, blobovi/ffi se obezbjeđuju
po dodatku/platformi, jer su vezani za platformu
i arhitekturu (ffi/blobovi). Jezgro skriptnog jezika nastoji
ostati što je moguće više neovisno o platformi.

## Pretvaranje tipova

Možete napraviti kopiju svakog objekta
s drugim tipom pomoću sljedećih poruka:

Poruka  | Rezultat
------- | ------
broj    | Pretvara u broj
tekst   | Pretvara u tekst
logički | Pretvara u logičku vrijednost
  
**Važe** sljedeća pravila:

poruka   | Ništa     | Logički            | Broj                  | Tekst     | Ostalo              
-------- | --------- | --------           | --------              | --------  | --------
logički  | Netačno   | n/p                | 0→Netačno inače→Tačno | Tačno     | Uglavnom Tačno
broj     | 0         | Netačno→0 Tačno→1 | n/p                    | ['n']→n | Uglavnom 1
tekst    | ['Ništa'] | ['Netačno']/['Tačno'] | ['n']              | n/p       | Zavisi

## Kopiranje

Vrijednosti se u XOScriptu uvijek prenose **po referenci**. U drugim jezicima
to zavisi od tipa vrijednosti, a u XOScriptu postoji samo jedan način,
po referenci. XOScript nikada ne pravi kopiju vrijednosti. Da biste kopirali objekat,
morate poslati poruku **kopiraj**. 

@test611

Ovdje ste možda očekivali da će izlaz biti Dolly, a ne
Donny. Međutim, to nije slučaj jer se oba imena odnose na isti
objekat. Pri radu s petljom dešava se nešto slično:

@test612

Zapravo, XOScript **uvijek** koristi reference, pa i u **:quantity**
gore prikazana petlja također označava referencu na element
u listi.

Da biste kopirali objekat, ovu radnju morate navesti
**eksplicitno**:

@test613

Slanjem unarne poruke **kopiraj** tekstu, objekat
vraća kopiju tog istog objekta teksta. Na isti način moguće je kopirati objekte
Broj, logičke objekte, liste i rječnike.

Možete definisati i vlastitu implementaciju kopiranja, a to je čak
neophodno ako pravite vlastite objekte. Zadana
implementacija kopiranja za listu pravi plitku kopiju, odnosno pravi
novu listu s istim elementima.

@test614

U ovom slučaju 4 se dodaje samo kopiji.
Međutim, budući da je kopija plitka, objekti u obje liste
su isti.

@test615

Dakle, ako svakom imenu u kopiji dodamo 2, i izvorna
lista bit će promijenjena.

Da bismo to ispravili, moramo napraviti **duboku kopiju**. Takva radnja kopiranja
za listu mogla bi se sastaviti na sljedeći način:

@test616

Također, obratite pažnju na poruku rekurzivan; ovu poruku je neophodno
poslati prije poruke kopiraj.

Ključno je imati na umu da iako kopija objekta
često izgleda isto kao original, ona zapravo
nikada nije isti objekat. Korijenski objekat definiše poruku **equal:**,
koja se može koristiti za poređenje identiteta objekata. Pogledajte
sljedeći primjer:

@test617

## Implicitno pretvaranje

XOScript koristi **implicitno pretvaranje** za pretvaranje objekata. Da bi ispisao
listu na ekran, XOScript će, na primjer, interno poslati listi poruku
*tekst*. To se može pokazati vrlo korisnim u
slučaju da želite ispisati listu kao listu odvojenu zarezima.
Poruka *tekst* može se prepisati: 

@test620

@api_String_base
@api_Format_base


## Serverski tekstovi

Sljedeće mogućnosti objekta Tekst dodaje
serverski dodatak.

@api_String_server


# Funkcije

{{messages}}

Kod možete grupisati između { i }, i on tada postaje funkcija.
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
Zbog jednostavne arhitekture, funkcija može imati samo
jednu tačku povratka. Da biste izbjegli opterećenje ili pretjerano ugnježđivanje
uslova, možete koristiti postupak (što je isto kao korištenje
znaka za množenje sa argumentom 1):

```
{
  (a = 1) tačno: { x := 1. }, prekini.
  (a = 2) tačno: { x := 2. }, prekini.
} postupak.
```

Na ovaj način (a = 2) neće biti izračunato ako je a = 1.
Također, na ovaj način vam nisu potrebne ugniježđene poruke tačno.
Kad god primijetite da ugnježđujete uslove, sjetite se
poruke postupak. Ona može učiniti vaš kod
lakšim za čitanje.


Evo jedne važne zamke:

```
{
	Netačno netačno: {
		Izlaz piši: ['Završi petlju.'].
	}, prekini.
	
	Izlaz piši: ['Nemoj me prikazati.'].

} postupak.

```

U ovom slučaju bit će prikazan tekst 'Dont show me'.
Zato što se **prekini** šalje objektu Netačno. Ako želite izvršiti
prekid, on se mora poslati kao poruka objektu **Tačno**.
 

```
{
	Netačno ne tačno: {
		Izlaz piši: ['Završi petlju.'].
	}, prekini.
	
	Izlaz piši: ['Nemoj me prikazati.'].

} postupak.

```

Radit će prema očekivanjima.

## Izuzeci

Izuzeci se mogu obraditi ovako:

```
{ Zadatak 1 } uhvati: { Zadatak 2 }, pokreni.
```

U svom programu možete i namjerno izazvati grešku i
time aktivirati blok za obradu. To se radi slanjem
poruke **greška:** trenutnom zadatku, kao što je prikazano u sljedećoj
ilustraciji:

```
{
ovaj-zadatak greška: ['Ups, pardon!'].
} uhvati: { :propust
Izlaz piši: propust.
}, pokreni.
```

## Ubacivanje vrijednosti

XOScript zadacima nudi mogućnost ubacivanja vrijednosti. Pogledajte
zadatak u nastavku:

```
>> slanje := {
	Bilten prima: svoj recipient.
}.
slanje postavi: ['recipient']
vrijednost: ['info@recipient.org'].
slanje pokreni.
```


Ova ilustracija prikazuje zamišljeni zadatak koji šalje bilten
na email adresu ili **recipient**. Ovaj primalac može se ubaciti
u zadatak izvana i prije pokretanja zadatka, slanjem
poruke **postavi:vrijednost:** zadatku. Na taj način vrijednost
**recipient** unaprijed se postavlja u zadatak. Ta vrijednost se može i promijeniti,
a zadatak se zatim može ponovo pokrenuti. Ovo je korisna metoda pri korištenju
objekata Task.

## Prazne funkcije

Prazni zadaci nisu dozvoljeni. Teoretski bi prazan zadatak izgledao
ovako: **{}**, međutim XOScript to doživljava kao grešku u jeziku. Ako
želite deklarisati prazan zadatak, možete koristiti objekat Ništa:

```
>> zadatak := Ništa.
```

Iako ovo nije pravi zadatak, nego objekat Ništa, poruka pokreni
mu se ipak može poslati:

```
>> odgovor := zadatak pokreni.
```

Zapravo, ovo je isto kao:

```
>> odgovor := Ništa pokreni.
```

Budući da objekat **Ništa** ne prepoznaje poruku **pokreni**, on
će vratiti samog sebe kao odgovor, pa je odgovor ponovo **Ništa**.
Dakle, nema potrebe za praznim zadatkom. Zahvaljujući elegantnom
dizajnu programskog jezika XOScript, za to možete jednostavno koristiti objekat
Ništa.

## Dinamički doseg

Kada Funkciji treba varijabla, a ne može je pronaći,
ona će provjeriti varijable Funkcije koja ju je **pozvala**
i nastaviti provjeravati dalje uz lanac Funkcija.
Ovaj proces pretrage traje dok se varijabla ne pronađe.
Ako varijabla i dalje nije pronađena, pojavit će se poruka o grešci. Ovaj način traženja
varijable naziva se **dinamički doseg**.

Da bismo ilustrovali ovaj princip:

@test618

@api_Code_base

# Korijenski objekat

{{messages}}

Objekat pod nazivom **Objekat** korijenski je objekat svih objekata u
XOScriptu i obezbjeđuje osnovne mogućnosti jezika. 

Najčešće slana poruka
je **na:uradi:**, koja proširuje funkcionalnosti objekta. Ovu
poruku prima korijenski objekat, koji zatim povezuje
navedeni zadatak s porukom i na taj način proširuje izvedeni
objekat.

## Metode za hvatanje svih poruka

Obično, ako pošaljete poruku koja ne odgovara
nijednoj metodi u objektu, ona se ignoriše. Međutim, možete navesti
takozvane **magične metode** ili metode **za hvatanje svih poruka** koje će
biti pozvane ako objekat ne razumije poruku.

Dostupne su 4 metode za hvatanje svih poruka. Svaka poruka odgovara
određenom broju argumenata.

Poruka za hvatanje svih poruka | Broj argumenata
-------------------- | -------------------
odgovori:             | 0
odgovori:i:         | 1
odgovori:i:i:     | 2
odgovori:i:i:i: | 3


@test619

## Programske poruke

Umjesto da se pošalje direktno objektu, poruka se može
poslati i putem varijable. Za to koristite poruku
**poruka:argumenti:**. 

@test396

@api_Object_base

# Liste

{{messages}}

XOScript poznaje dvije vrste kolekcija: *liste* i *rječnike*.
**Liste** su nabrajanja objekata u *fiksnom redoslijedu*. Rječnici nemaju
redoslijed, nego podsjećaju na legendu koja sadrži ključ (ili pojam) i njegovu
odgovarajuću vrijednost. Liste su uporedive s nizovima (PHP, Java, C)
i listama (Python). Rječnici su uporedivi s asocijativnim nizovima (PHP) ili
rječnicima (Python) u drugim programskim jezicima. Da biste napravili
novu Listu, napišite:

```
>> fibonacci := Lista novi.
```

Ova prazna lista može se popuniti pomoću **dodaj-na-kraj:** :

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

Ako listu ispišemo na ekran:

```
Izlaz piši: fibonacci, novi-red.
```

Vidjet ćemo:

```
Lista ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

Umjesto dodaj-na-kraj možete koristiti i ; za dodavanje elemenata u listu:


```
>> fibonacci := Lista novi ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Tačka-zarezi (;) su sve binarne poruke koje stavljaju
vrijednost u listu.

## Ulančavanje

Pretpostavimo da imate listu poput:

```
>> x := Lista novi ; 1 ; 2 ; 3.
```

Ako želite izbrisati prvi i zadnji element, vaša
poruka bila bi:

```
x izvadi-prvi izvadi-zadnji.
```

Nažalost, prethodna notacija neće ispravno funkcionisati.
Poruka **izvadi-prvi** vraća prvi element liste, koji
će, opet, postati primalac poruke **izvadi-zadnji**. Dakle,
poruka **izvadi-zadnji** ne šalje se objektu **x**, nego broju 2.
Moguće rješenje ovog problema bilo bi napraviti dvije zasebne
rečenice, kao npr.: 

```
x izvadi-prvi.
x izvadi-zadnji.
```

Međutim, ovo je prilično nepraktično, naročito kada trebate
izbrisati više od dva elementa. Zato XOScript nudi
alternativnu strukturu poruka za ovakve situacije. U
**alternativnim** strukturama poruka odgovori objekata se ignorišu
i kao odgovor uvijek iznova dobijate objekat primalac.
**Alternativna** struktura poruka započinje se slanjem
poruke **radi** objektu, a **alternativna** struktura
poruka može se završiti slanjem poruke **gotovo**. U
prikazanom primjeru to bi se moglo primijeniti na sljedeći način:

```
>> x := Lista novi ; 1 ; 2 ; 3.
x radi izvadi-prvi izvadi-zadnji gotovo.
```

@api_List_collections


# Rječnici

{{messages}}

**I Lista i Rječnik su kolekcije. Međutim, za razliku od
liste, rječnik **nema** redoslijed. Još jedna razlika između njih
je to što se rječnik sastoji od parova objekata. Jedan objekat služi kao unos (ili
ključna riječ) za traženje drugog objekta. Dobar primjer
liste je cjenovnik, kao npr.:


```
>> meni := Rječnik novi
	stavi: ['£5'] na: ['pita od jabuka'],
	stavi: ['£6'] na: ['kolač od mrkve'],
	stavi: ['£3'] na: ['fudge'].
```

Slično kao kod liste, poruka stavi:na:
koristi se za dodavanje objekta u listu. Razlika je u tome što se, za razliku od
liste, povezuju dva objekta. Prvi objekat je, slično
kao kod liste, objekat koji ćete sačuvati u listi. Drugi
objekat nije njegova pozicija unutar kolekcije, nego **unos**
koji omogućava da se prethodni objekat kasnije dohvati.
Ukratko, rječnik funkcioniše pomalo kao pravi rječnik; dakle, pomoću ključne riječi
može se pronaći značenje. Na primjer, da biste iz
gore navedene liste dohvatili cijenu fudža:

```
>> price := meni na: ['fudge'].
```

Možete koristiti i sažetu notaciju:

```
>> price := meni ? ['fudge'].
```

Ako su unosi koje koristite za čuvanje objekata bez razmaka
(i ne sukobljavaju se s drugim unaprijed definisanim porukama),
može se koristiti i sljedeća notacija:

```
>> meni := Rječnik novi
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Nema sumnje da se gornja notacija čita nešto prirodnije.
Da biste zatražili cijenu
fudža, može se koristiti sljedeća pojednostavljena notacija:

```
>> price := meni fudge.
```

@api_Dict_collections

# Datoteka

{{messages}}

Objekat **Datoteka** obezbjeđuje osnovni pristup sistemu datoteka.
Ovaj objekat možete koristiti za čitanje cijelih datoteka u varijablu
odjednom ili za upisivanje varijabli u datoteke odjednom. Čitanje red
po red je također podržano. To su najčešće operacije ulaza/izlaza s datotekama
u skriptnom jeziku. Napredne operacije s datotekama zahtijevaju
upotrebu FFI putem serverskog dodatka ili zasebnog IO dodatka.

@api_File_file
@api_File_vault
@api_File_fficonnect


# Datum/vrijeme

{{messages}}

Za strukturirani prikaz vremena i datuma XOScript koristi
objekat **Trenutak**. Ako se novi objekat Trenutak ispiše na ekran,
prikazuju se trenutni datum i vrijeme:

```
Izlaz piši: Trenutak novi, novi-red.
```

Može rezultirati nečim poput:

```
2020-10-10 12:16:39
```

Također je lako očitati pojedinačne komponente vremena. Tako,
na primjer, ako je potrebno znati samo trenutnu godinu, poruka
**godina** može se poslati trenutku, a odgovor će biti
objekat Broj koji sadrži samo godinu:

```
>> m := Trenutak novi.
Izlaz piši: m godina, novi-red.
```

@api_Moment_system


# Program/StdOut

{{messages}}

Objekat Program predstavlja aplikaciju koja se trenutno izvršava. Ovaj objekat
nudi funkcionalnost za izvršavanje sistemskih naredbi, uključivanje podprograma,
čitanje argumenata i još mnogo toga. Sve funkcije vezane za sistem.

## StdOut

Izlaz je objekat standardnog izlaza. U osnovi ima dvije metode:
**piši:** i **novi-red**. Poruka piši: koristi se za slanje teksta
na stdout, a poruka novi-red ispisuje znak za novi red.
Umjesto **novi-red** možete koristiti i \\n.

Primjer:

```
Izlaz piši: ['Hello World'], novi-red.
```

rezultat:

```
Hello World
```

## Moduli/dodaci

Svijet XOScripta može se proširiti novim sistemskim objektima
instaliranjem modula. Novi sistemski objekat može se dodati u svijet
XOScripta postavljanjem datoteke modula (obično datoteke sa sufiksom .so
) u folder mods. 

Kada pošaljete poruku objektu koji je dostupan putem
modula dodatka, XOScript će ga automatski učitati.

Dodatke možete pisati i sami. Dodaci se pišu u
programskom jeziku C. Primjer dodatka možete pronaći u paketu izvornog
koda pod src/plugins/example.


## Refleksija

Postoje različiti načini za istraživanje
sistema tokom izvršavanja programa. XOScript ima nekoliko metoda za
otkrivanje koji su objekti prisutni i na koje poruke ti objekti
odgovaraju. Prvo, svaki objekat se može pitati kojeg je **tipa**,
međutim tipovi su u XOScriptu promjenjivi i stoga nepouzdani.

Također je moguće pitati objekat Program da li je
određeni objekat već prisutan u programu:

```
Program Alat tačno: { ... }.
```

Kada se naziv objekta
sastoji od samo jednog simbola, najbolje je koristiti
sljedeću notaciju kako bi se izbjegla zabuna:

```
Program pronađi: ['X'], tačno: { ... }.
```

Osim pitanja o objektima, jednako je moguće pitati
objekat Program o porukama. Na primjer, može se pitati da li
objekat **Broj** poznaje poruku **između:i:**, na način
kako je prikazano u nastavku:

```
Program Number: ['between:and:'], novi-red.
```

@api_Program_system

# server

{{messages}}

Serverski dodatak u xoscriptu nudi funkcionalnost za
pravljenje serverskih aplikacija. Da biste učitali serverski
dodatak, koristite:

```
Server inicijaliziraj.
```

Radi vaše udobnosti preporučuje se i učitavanje
datoteka webtools.xo i template.xo.

```
Program koristi: ['webtools.xo'].
Program koristi: ['template.xo'].

```

## Postavke servera

Možete podesiti sljedeće postavke servera:

```
	# zadane vrijednosti su date,
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

## Zdravo, svijete

Evo vrlo jednostavnog web programa koji možete koristiti sa
standardnim CGI serverom kao što su Apache2, NGINX, OpenHTTPD ili bilo kojim drugim
poznatim serverom.

```
#!/bin/xo

Server inicijaliziraj.
Program koristi: ['webtools.xo'].

>> veb-stranica := Web-dokument novi.

veb-stranica ispiši: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Ako ne želite koristiti objekat Web-dokument, to je u redu, ali
tada HTTP zaglavlja morate pisati sami:

```
#!/bin/xo
Izlaz piši: ['Content-type: text/html; charset=utf-8 \n\n'], novi-red.
Izlaz piši: ['zdravo svijete!'], novi-red.
``` 

## Zahtjev

Objekat HTTP-Zahtjev može se koristiti za dobijanje GET/POST/COOKIE i
UPLOAD podataka:

```
>> zahtjev  := HTTP-Zahtjev novi.
>> search   := zahtjev get: ['search']. # ?search=books
>> password := zahtjev post: ['password']. # iz obrasca
>> odabrano := zahtjev get-lista: ['sel[]']. #?sel[]=1&sel[]=2
>> odabrano := zahtjev post-lista: ['sel[]'].
>> kolačić   := zahtjev cookie: ['session-id'].
>> prijenos   := zahtjev upload: ['file'].
>> privremenaPutanja := prijenos ? 1.
>> imeDatoteke := prijenos ? 0.
```

## Maxpost/length

Zadani najveći broj POST polja je 40, a zadana najveća dužina
sadržaja je 2MB. Da biste to drugačije podesili za pojedinačnu skriptu:

```
Program postavka: ['max-contentlength'] vrijednost: 1. 
Program postavka: ['max-postfields'] vrijednost: 1. 
```

{{note}}
Ako dužina sadržaja premaši maksimum,
proces se prekida jer više ne možemo biti sigurni
da je sadržaj bezbjedan.
{{/note}}

Ograničenje maxtime određuje najduže vrijeme u ms
za čitanje stdin/POST podataka.

```
Program postavka: ['max-time'] vrijednost: 5000. # 5sec
```

Ovo se odnosi samo na I/O čitanje POST podataka i sprječava
napade poput slowlorisa. Ako zaista želite ograničiti
vrijeme izvršavanja bilo koje operacije, koristite Program alarm.

## Baza podataka

Objekat Database može se koristiti za upite prema MariaDB/MySQL.
Da biste se povezali s bazom podataka, uradite:

```
>> bp := Maria-DB novi domaćin: ['localhost'],
	korisnik: ['xo'],
	lozinka: ['pass123'],
	naziv-baze: ['xobase'],
	poveži-se.

```

Da biste umetnuli zapis, koristite:

```
>> parametri-pretrage := bp upit: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parametri: ( Lista novi ; ['abc'] ; 12.35 ; 6 ). # parametrizirani upiti

{  parametri-pretrage izvrši. bp potvrdi. }
uhvati: { :e bp poništi.  }, pokreni.
```

Imajte na umu da xoscript radi *isključivo* s transakcijama i nikada ne radi automatsku potvrdu (autocommit).
Ako se autocommit ne može isključiti, dobit ćete grešku pri povezivanju.
Za upite uvijek koristite vezivanje parametara, nikada ne dodajite korisnički unos direktno
u SQL.

ID umetnutog zapisa dobijate ovako:

```
Izlaz piši: ['UMETNUTO: '] + parametri-pretrage insert-id, novi-red. # id umetanja
```

Da biste dohvatili zapise:

```
>> parametri-pretrage :=
bp
	upit: ['SELECT * FROM book order by id desc limit 2'], 
	dohvati: { :redak 
		Izlaz piši: redak id + [' '] + redak description + [': '] + redak price, novi-red.
	}. # dohvatanje redova

```

## Sesije

Za trajnost podataka možete čuvati i dohvatati podatke iz objekta sesije.
Prvo napravite novi **Web-dokument**. Objekat Web-dokument povezuje
zahtjev, zaglavlja, HTML i sesiju. To je zato što, kad god
posjetite web stranicu svojim preglednikom, vidite samo HTML. Ali
cijeli Web-dokument sastoji se i od **Zaglavlja**. Na primjer,
većina HTTP odgovora uključuje zaglavlje poput: Content-type:text/html kako bi
se pregledniku reklo da podatke koji slijede treba prikazati kao HTML
(a ne, na primjer, preuzeti kao datoteku). Sesije su način
čuvanja korisničkih podataka između zahtjeva. Da bismo pratili te podatke, moramo
postaviti kolačić, a i taj kolačić se postavlja putem Zaglavlja. Zato se
sve objedinjuje u Web-dokumentu (jer je to cijeli
dokument koji sadrži i zaglavlja i HTML ili druge podatke).


```
# Prvo pravimo novu instancu Web-dokument
>> veb := Web-dokument novi.

# Sada pokrećemo sesiju; to će generisati zaglavlje za kolačić i
# kreirati datoteku za vaše podatke, povezanu s tim kolačićem
>> sesijaKorisnika := veb pokreni-sesiju.

# Sada sesiju možemo tretirati kao Rječnik
sesijaKorisnika userid: 123.
```

Da biste uništili sesiju (pri odjavi):

```
veb uništi-sesiju.
```

## Zaglavlja

Web-dokument vam također omogućava postavljanje drugih poznatih zaglavlja.
Na primjer, ako želite preusmjeriti korisnika na drugi URL:

```
veb idi-na: ['/other.html'].
```

Ispod haube ova naredba također generiše HTTP zaglavlje koje se šalje
zajedno s vašim ostalim podacima ili HTML-om kako bi uputilo preglednik da ode
na navedenu ciljnu adresu.

Da biste dodali prilagođeno zaglavlje:

```
veb zaglavlje: ( 
	HTTP-Zaglavlje novi
	ključ: ['Content-Length']
	vrijednost: 400
).
```

Da biste prikazali stranicu 404:

```
veb nije-pronađeno: ['Upsić..'].
```


## Šabloni

Zadani sistem šablona je vrlo jednostavan. Ne morate učiti
novu sintaksu šablona. Također, mehanizam šablona osigurava stvarno razdvajanje
prezentacije i poslovne logike.

Da biste napravili šablon iz datoteke:

```
>> tpl := veb šablon: ['templates/ux.tpl'].
```

Sistem šablona koristi oznake. 
Postoje tri vrste oznaka: oznake za izrezivanje, oznake za lijepljenje i
oznake utora. Osnovna ideja je zaista jednostavna: izrezujete
područja označena oznakama za izrezivanje i možete ih zalijepiti na
područja označena oznakama za lijepljenje. U oznake utora možete
ubacivati tekstove.

Tako, na primjer, uz sljedeći šablon, stavimo
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

To možete uraditi na sljedeći način:

```
>> gem := tpl izreži: ['gem'], kopiraj.
gem price: 99.
tpl zalijepi: gem na: ['jewels'].
veb ispiši: tpl očisti.
```

Zadnji red jednostavno šalje šablon kao tekst klijentu
zajedno s potrebnim HTTP zaglavljima.

Rezultat:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

Da biste sigurno posluživali datoteke koje su korisnici učitali, možete se osloniti na passthru:

```
>> otpremljeno := ['smile.gif'].
Server proslijedi: otpremljeno prefiks: ['/uploads/images/'].
Program kraj.
```

Ovo će poslužiti sadržaj koji je korisnik učitao s odgovarajućim
mime tipom. Podržani su samo mime tipovi s bijele liste:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF i SVG.
SVG, ZIP i GZIP datoteke šalju se kao preuzimanje, jer SVG
može sadržavati skripte koje bi se inače izvršavale na vašoj domeni.
Ova metoda sprječava TOCTOU napade, prelaske putanje (path traversal), 
izvršavanje zlonamjernog koda (injection), napade simboličkim vezama,
DDoS napade (ograničenje datoteke = 50MB), napade prisluškivanjem i 
razne druge sigurnosne probleme.


## JSON

Da biste objekat kodirali kao JSON:

```
>> json := ( JSON jsonify: ( 
	Rječnik novi stavi: ( 
		Lista novi ; 1 ; 2 ; 3
	) na: ['abc']
)).
```

Da biste JSON dekodirali u xoscript objekat:

```
>> rječ := ((JSON objekat: json) abc ? 1).
```

JSON s više od 500 nivoa ugnježđivanja odbija se kao neispravan.

Da biste Rječnik direktno ispisali kao json s ispravnim zaglavljima:

```
veb json: rječ.
```


## Regex

Regularne izraze možete koristiti pravljenjem uzorka.
Na primjer, da biste pronašli href atribute i ciljeve hiperveza:

```
Uzorak novi: ['href="([^"]+)" target="([^"]+)"'].
```

Sada primijenite uzorak na tekst koji se pretražuje ovako:

```
obrazac podudaranje: predmet uradi: { :m :x .... }
```

Potpuni primjer:

```
>> predmet := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> obrazac := Uzorak novi: ['href="([^"]+)" target="([^"]+)"'].
>> rezultat  := obrazac podudaranje: predmet uradi: { :m :x
	Izlaz piši: m, novi-red.
	Izlaz piši: x, novi-red.
	<- ['XXX'].
}.
Izlaz piši: rezultat, novi-red.
```

## Mrežna komunikacija

Koristite objekat Mreža za izvršavanje web zahtjeva.
Objekat Mreža uvijek šalje POST zahtjev, osim ako kao
podatke ne pošaljete Ništa, tada šalje GET zahtjev.


```
Mreža 
post: Ništa 
na: ['https://redbeanphp.com'].
```

## Šifrovanje

Serverski dodatak dolazi sa šifrovanjem zasnovanim na XChaCha20 i Argon2.

Primjer:

```
>> šifrovano := Sef šifriraj: ['hello'] ključ: ['world'].
>> dešifrovano := Sef šifriraj: šifrovano ključ: ['world'].
```

## Tokeni

Da biste generisali kriptografski siguran token određene dužine:

```
>> mojtok := Sef token: 40.
```

Ovo će generisati token od 40 znakova.

## Formatiranje

Objekat Format omogućava formatiranje podataka, kao što je dopunjavanje ili
dodavanje nula. Koristi printf sintaksu.

```
>> fmt := Format novi: ['%06.0f'].
fmt primijeni: 56. # daje 000056
```

Format može sadržavati jednu konverziju i ona mora odgovarati vrijednosti,
inače ćete dobiti grešku:

- `primijeni:` s tekstom: `%s`
- `primijeni:` s brojem: `%f`, `%e`, `%g` ili `%a`
- `primijeni-cijeli:` s brojem: `%d`, `%i`, `%o`, `%u`, `%x` ili `%c`

Vrijednosti iz zahtjeva su tekstovi. Da biste jednu od njih formatirali kao broj,
prvo je pretvorite:

```
fmt primijeni: (zahtjev get: ['amount']) broj.
```

## Koderi

Dostupno je nekoliko kodera i dekodera.
URL koder priprema url za upotrebu u HTML-u kao vezu:

```
Server url-kodiraj: ['https://example.com?a=6&b=1 2'].
```

Da biste korisnički unos sigurno ubacili u svoj HTML bez rizika od XSS
napada, uvijek koristite:

```
Server html-kodiraj: ['<bezopasno>'].
```

Imajte na umu da će mehanizam šablona uvijek izvršiti html kodiranje
ako pišete u oznaku utora. Dakle, ako koristite sistem šablona,
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
pošiljalac: ['xo@xoscript.com'] naziv: ['xo'],
prima: ( Lista novi ; ['xo2@xoscipt.com'] ),
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

Pomoću poruke poveži: možete povezati vanjsku biblioteku sa
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

FFI se obezbjeđuje po platformi/dodatku jer je
vezan za arhitekturu sistema ispod, a to je nešto što
jezgro ne bi trebalo raditi.
Serverski dodatak nudi usklađenu ffi/blob implementaciju.
Podrazumijevano, jezgro se povezuje s ciljnom platformom
putem stdin/stdout, ograničenih usluga ulaza/izlaza s datotekama i shella (Program sistem:).
Dodatnu integraciju obezbjeđuju ffi/blobovi putem dodataka usmjerenih
na aplikacije, kao što je serverski dodatak.

FFI je skraćenica za Foreign Function Interface (sučelje za strane funkcije). Omogućava vam korištenje funkcionalnosti koju su drugi napisali u
drugim programskim jezicima, a koja se obezbjeđuje putem DLL datoteka, SO datoteka ili Dylib datoteka. To mogu
biti razne funkcije, a ovom metodom dostupan je ogroman raspon funkcionalnosti.
Počnimo s primjerom:

```
Server poveži: (
 Lista novi ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Lista novi ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s oslobodi.
```

Rezultat ovog koda je da ćete u komandnoj liniji vidjeti sljedeće:
FFI has 3 letters.
Sada vjerovatno mislite: "To je mnogo koda za nešto tako jednostavno."
Mislim, zar ovo ne bismo mogli riješiti naredbom Gui show? Odgovor je odlučno da!
Ali ovo je zamišljeno kao ilustrativan primjer.
FFI se obično koristi za složenije zadatke, ali oni nisu dobri
primjeri, pa sam izabrao nešto trivijalno.

Argumenti metode poveži:

- Argument #1: DLL ili SO datoteka koju želite koristiti.
- Argument #2: Funkcija u toj datoteci koju želite povezati.
- Argument #3: Lista s nazivima tipova podataka argumenata funkcije.
- Argument #4: Naziv povratnog tipa funkcije.
- Argument #5: Naziv objekta s kojim želite povezati ovu funkciju (ako ne postoji, bit će napravljen
automatski).
- Argument #6: Poruka s kojom ova funkcija treba biti povezana.

U gornjem primjeru želimo povezati funkciju printf iz libc.so. Nazive tipova
podataka možete pronaći u dokumentaciji softvera s kojim se povezujete. Dostupni tipovi su:
void, pointer, float, double, int, uint, char, uchar, intX i uintX,
gdje X može biti 8, 16, 32 ili 64.

Ovi tipovi odnose se na broj bajtova potrebnih za čuvanje podataka. Za printf povezujemo se s
novim objektom pod nazivom Printf i porukom template:number:. Vanjsku
funkciju prevodite u XOScript dijalekt prije nego što je upotrijebite. Poruka template:number: očekuje
bafer s tekstom šablona kao prvi parametar. Ovaj bafer pravimo pomoću objekta Blob, koji
vam omogućava ručno alociranje memorije. Vi ste odgovorni za oslobađanje te memorije nakon toga
porukom oslobodi.

Memorijski blob možete popuniti na razne načine. U našem primjeru popunjavamo ga tekstom, pa koristimo
poruku utf8: (UTF-8 je kodiranje za pretvaranje teksta u bajtove). Blob možete popuniti i
porukom bytes:, prosljeđujući listu vrijednosti bajtova. Da biste pročitali sadržaj bloba, koristite od:dužina:.
Bajtove ćete dobiti nazad kao listu. Pomoću objekta Blob možete čak napraviti i C strukturu koristeći
poruku struct:, prosljeđujući niz C tipova. To može biti potrebno pri pozivanju C
funkcije u vanjskoj softverskoj biblioteci koja očekuje pokazivač na strukturu.

{warning}
Blobove morate sami osloboditi.
Sakupljač smeća ne čisti blobove.
{/warning}

Budući da se blobovi mogu razmjenjivati s vanjskim funkcijama iz biblioteka,
sakupljač smeća ih ne može automatski očistiti (vanjske funkcije ih možda
i dalje koriste ili te vanjske funkcije možda žele same
da ih oslobode). Zato blobove morate sami osloboditi kada je to potrebno.

Da biste oslobodili blob, koristite:

```
mojblob oslobodi.
```

Da biste oslobodili strukturu, koristite:

```
mojstruct oslobodi-struct oslobodi.
```

Dakle, za strukturu morate poslati dvije poruke: oslobodi-struct i oslobodi kako biste
dealocirali memorijski blok.

@api_Blob_fficonnect
