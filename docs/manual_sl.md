# Osnove

{{messages}}


Dobrodošli v XOScript
Cilj projekta XOScript je ustvariti skriptni jezik, ki je preprost in preverljiv.
Preprosto ne pomeni nujno lahko.
Znan programski jezik je morda lažji za uporabo kot XOScript.
Tukaj preprostost pomeni nekaj drugega:
zmožnost oblikovati popoln miselni model jezika in njegovega delovanja.

XOScript je zasnovan tako, da ga lahko obvladate v glavi.
Njegova slovnica in število konceptov sta namerno majhna.
Razredov ni; objekte je mogoče razširiti neposredno.
Objekti se prenašajo po referenci, kopiranje je izrecno,
funkcije pa imajo eno samo izhodno točko.

Nekatere od teh odločitev se precej razlikujejo od uveljavljenih jezikov.
XOScript na primer nima sistema tipov in uporablja dinamični doseg.
Sporočila, ki jih ni mogoče obdelati, se prezrejo, namesto da bi sprožila izjemo.
Te odločitve imajo posledice in niso namenjene odpravljanju napak.
Njihov namen je, da osnovni model jezika ostane majhen in dosleden.

XOScript je mogoče tudi lokalizirati, kar omogoča, da poslovna pravila
izrazite v naravnem jeziku in jih morda delite z netehničnimi deležniki.

Preverljivost pomeni uporabo iste filozofije pri implementaciji.
Izvajalno okolje je napisano v jeziku C, z majhnim ročno napisanim lekserjem, razčlenjevalnikom in obhodnikom drevesa.
Standardna knjižnica in izvajalno okolje v veliki meri sledita strukturi jezika,
zato je povezava med kodo XOScript in njeno implementacijo razmeroma neposredna.

Tudi testi so tesno povezani z dokumentacijo.
Vsaka metoda naj bi imela pripadajoč test, ki ga je mogoče vključiti v priročnik,
kar pomaga ohranjati dokumentacijo usklajeno z implementacijo.

XOScript ni namenjen tekmovanju z uveljavljenimi jeziki po
zmožnostih ali domačnosti. Raziskuje drugačen cilj:
programsko okolje, ki ga razvijalec lahko razume kot celoto.

Upamo, da majhen jezik in majhna
implementacija omogočata praktično razumevanje programske opreme
od bajta do objekta, od sintakse do izvajalnega okolja, in pisanje kode
z zaupanjem, ker razumete tako dogajanje v
skripti kot dogajanje v ozadju.

Arhitektura strežniške postavitve xoscript
je preprosta, a prilagodljiva.

{{architecture.png}}

Če želite xoscript uporabljati kot strežniški jezik, morate namestiti
strežniški vtičnik v mapo z imenom /mods/server. 

Razlog je v tem, da želimo
jedro jezika ločiti od strežniško specifičnih funkcionalnosti,
za razliko od na primer PHP ali Pythona. Sicer bi morali vsem brez potrebe
dostaviti vse živo in mrtvo, kar je preprosto nesmiselno.
Po želji lahko namestite tudi druge module. Sistem je zelo
prilagodljiv.

Poleg tega so nekatere funkcije bolje implementirane v samem skriptnem
jeziku, na primer predloge in upravljanje sej, zato dodatno
za vaše udobje dostavljamo knjižnici template.xo in webtools.xo.
Razlog za vse to je, da ne vemo, kako želite
uporabljati xoscript. Uporabljate ga lahko kot strežniški skriptni jezik,
pa tudi za grafične vmesnike, vgrajene naprave ali preprosto paketno obdelavo.
Tudi če ga uporabljate kot strežniški skriptni jezik (kar je
trenutno eden glavnih primerov uporabe), boste morda vseeno želeli
uporabiti drug pogon predlog ali drug upravljalnik sej.
Kdo smo mi, da bi odločali, da morate uporabljati naše?

Ena od prednosti uporabe našega pogona predlog je sicer ta, da se
za ustvarjanje predlog ni treba učiti dodatne sintakse.
Privzeti pogon predlog, ki je priložen xoscript, uporablja 100-odstotno
ločitev med predstavitvijo in logiko. Namesto posebne
sintakse predlog preprosto uporablja zelo prilagodljiv sistem oznak rež.
Za več informacij glejte poglavje Strežnik.

Upoštevajte, da morate, če ne želite uporabljati privzetega pogona predlog ali
privzetih spletnih orodij, samoumevno zagotoviti
lastne.

Če vaš spletni strežnik teče v chrootu, jailu ali drugem peskovniku,
morate v tem okolju namestiti tudi odvisnosti xo; katere
knjižnice potrebujete, lahko ugotovite z ldd (glejte priročnik (manpage) za Linux ali BSD).
Če želite v svojih skriptah xo uporabljati ukaze lupine, v to okolje kopirajte tudi lupino
(na primer bash ali ksh).

Radi bi tudi poudarili, da vzvratno združljivost jemljemo zelo resno.
Na voljo je celo posebna zmožnost za vzvratno združljivost z imenom
'version'. Na splošno želimo, da bi vaša koda delovala večno. Tako vam
nikoli ne bo treba posodabljati kode, da bi ostala združljiva z novejšimi različicami
xoscript. Naš cilj je: napiši enkrat, izvajaj večno.

Preostanek tega priročnika je namenjen podrobni razlagi programskega
jezika xoscript. Strežniško skriptiranje je obravnavano v poglavju
z naslovom Strežnik. Če ste izkušen razvijalec programske opreme, boste morda želeli
preskočiti nekaj poglavij, ker so nekatera nekoliko preveč podrobna ali
so zelo podobna splošnim programerskim praksam. Tisti, ki
že imate izkušnje z več drugimi programskimi jeziki,
ta priročnik raje uporabljajte kot referenčni vodnik.

## Namestitev v Linuxu

Prenesite apache2 in mariadb:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Prenesite xoscript.
X zamenjajte s pravilno številko različice!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Kopirajte datoteke v korensko mapo spletnega strežnika in v /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Uredite konfiguracijo apache2:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Virtualhost zamenjajte z:

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

Ustvarite testno stran:

```
sudo nano /var/www/html/test.xo
```

in napišite majhen testni program:

```
#!/bin/xo
Server inicializiraj.
Program uporabljaj: ['webtools.xo'].
>> splet := Spletni-dokument nov.
splet izpiši: ['Hello World'].
```

Dovolite apache2, da vaš program izvaja prek CGI:

```
sudo chmod uog+x /var/www/html/test.xo
```

Znova zaženite apache2:

```
sudo systemctl restart apache2
```

V brskalniku odprite svojo testno stran:

```
http://localhost/test.xo
```

Videti bi morali:

```
Hello World
```


## Namestitev v OpenBSD

Uredite /etc/httpd.conf in dodajte:


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

Če želite uporabljati SSL:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Za zaščito izmenjave ključev pred kvantnimi napadi
izberite šifrirni algoritem mlkem:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

V chroot dodajte izvršljivo datoteko xo in module ter vse odvisnosti
(ugotovite jih z ldd).

## Zagon primerov


Za zagon enega od primerov programov v paketu:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Na primer, za zagon primera FizzBuzz v Linuxu:

```
./example.sh fizzbuzz Linux
```

Za zagon istega primera v OpenBSD:

```
./example.sh fizzbuzz OBSD
```

Za zagon primera s čisto gradnjo:

```
./example.sh fizzbuzz OBSD clean
```

## Enotski testi

Za zagon enotskih testov:

```
./runtests.sh
```

Za zagon enotskih testov brez gradnje (samo testiranje):

```
./runtests.sh nobuild
```

## Gradnja

Za gradnjo iz izvorne kode v Linuxu:

```
make clean
ISO="en" make
```

V OpenBSD:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

Za gradnjo strežniškega vtičnika v Linuxu:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

Za gradnjo strežniškega vtičnika v OpenBSD:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Pozdravljen, svet

Ko je datoteka prenesena v vaš računalnik, jo lahko razširite
in xo zaženete z naslednjim ukazom:

```
xo
```

Za zagon programa XOScript program shranite kot datoteko s pripono
-xo (neobvezno). Poleg tega za ukazom XOScript vstavite ime datoteke
svojega programa:

```
xo myprogram.xo
```

Ko zaženete ukaz XOScript in mu kot parameter podate datoteko
s svojim programom, bo xo prebral in izvedel vašo programsko datoteko.

{{note}}
Program lahko zaženete tudi tako, da ga povlečete na ikono xo.
{{/note}}

{{warning}}
V nekaterih sistemih morate xo vnaprej dovoliti nalaganje dinamičnih
knjižnic.
{{/warning}}

Po tradiciji mora biti prvi program v vsakem novem programskem
jeziku nekakšen pozdrav svetu. V XOScript je takšen
program **Hello world** videti takole:

@test598

Ko to besedilo shranite v datoteko, npr. hello.xo, ga lahko izvedete
takole: .

xo hello.xo

Hello world


Izpis programa vidite v zgoraj prikazanem črnem oknu.
V celotnem priročniku bo za prikaz izpisa uporabljen
enak način prikaza.

{{note}}
Izhod se piše z veliko začetnico I.
Na splošno se objekti začnejo z veliko začetnico,
razen če delujejo kot primerek (nimajo lastnih
metod, le podatke). To odraža dogovore o razredih in primerkih
v drugih programskih jezikih.
{{/note}}


## Sintaksa 

XOScript je *čisto* *objektno usmerjen* programski jezik. To pomeni,
da xoscript vse obravnava kot objekt, zato drugih *podatkovnih tipov*
ni. V programu, napisanem v XOScript, so v bistvu tri osnovna rutinska dejanja:
*prirejanje*, *pošiljanje sporočil*
in *odgovarjanje*. Izmenjava sporočil med objekti je ključni del
programa XOScript. Tri posamezna rutinska dejanja so prikazana
spodaj:


Dejanje         | Primer
--------------- | --------
prirejanje      |  \>\> x := 1. 
unarna sporočila | x sodo?.
binarno sporočilo | 1 + 2.
sporočilo s ključnimi besedami | x od: 0 dolžina: 10.
odgovor         | <- answer.  


To poglavje vam bo dalo splošen vtis o jeziku XOScript
in opisuje njegova osnovna načela. XOScript je majhen jezik,
utemeljen na treh dejanjih (glejte prikaz), ki se prevedejo v
približno šest slovničnih pravil. To je vse, kar potrebujete za obvladovanje
jezika.

Nič hudega, če vam stvari niso takoj jasne: vsi gradniki
bodo raziskani v naslednjem poglavju (3), osnovna pravila pa bodo
ponovljena. Pričujoče poglavje je predvsem splošen
uvod v jezik. Osnovna načela bodo na kratko
razložena in ponazorjena z več ustreznimi primeri. Manjkajoče
podrobnosti bodo opisane pozneje.

Komentarji v XOScript se začnejo z znakom \#. Naslednja vrstica
bo torej prezrta:

```
# to je samo komentar
```

## Spremenljivke

Za prirejanje
spremenljivke uporabite simbol za deklaracijo spremenljivke: >>. Ime
spremenljivke lahko vsebuje vse znake razen: <-, :=, presledkov,
pik, vejic, dvopičij, narekovajev [' '] in oklepajev ().
Poleg tega spremenljivka ne sme obsegati več vrstic. Upoštevajte,
da se spremenljivka ne sme začeti s številko ali znakom minus.

To so primeri veljavnih spremenljivk:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dolar'].
>> +plus := Resnično.
>> geslo-uporabnika := ['Pssst!'].
```

Neveljavne spremenljivke so na primer:


```
>> -123 := ['negativno število'].
>> password of uporabnika := ['Zaupno'].
>> password.of:uporabnika := ['Zaupno'].
>> ,x := 10.
```

{{note}}
V besedilnem literalu vam ni treba ubežati
nobenega znaka (vključno z narekovaji, dvojnimi
narekovaji in mejami besedila), dokler to
lekserju ne povzroča dvoumnosti.
{{/note}}

Ko je spremenljivka deklarirana, jo lahko prosto uporabljate. To pomeni,
da je simbol za deklaracijo treba uporabiti le prvič, ko
uporabite spremenljivko (deklaracija).

Natančneje: spremenljivki ne morete kar tako začeti prirejati vrednosti
*(x := 2)*, saj morate spremenljivko najprej deklarirati *(\>\>
x := 2)*. Ko pa je deklarirana, lahko njeno vrednost spreminjate
brez simbola za deklaracijo *(\>\> x := 2. x := 3.)*.

Upoštevajte, da je spremenljivki ob deklaraciji obvezno prirediti vrednost.
Za razliko od drugih programskih jezikov spremenljivke ne smete
deklarirati brez vrednosti. Vsako spremenljivko je nujno izrecno povezati
z začetno vrednostjo. Kljub temu jo lahko brez zadržkov inicializirate
z objektom **Nič**. V tem primeru lahko spremenljivko
obravnavate kot prazno *(\>\> x := None.)*. Skratka, deklaracija
spremenljivke brez začetne vrednosti ni dovoljena. Torej je

```
>> x.
```

neveljavno in bo povzročilo sporočilo o napaki.

{{note}}
xoscript uporablja dinamični doseg
spremenljivk; za podrobnosti glejte poglavje Funkcije.
{{/note}}


## Literali

XOScript vse obravnava kot objekt; tj. vsa števila, besedila
in fragmente kode. Števila, kot so 1, 2, 100, -999 in 1,234, so
objekti Število. Vsa besedila med enojnimi narekovaji so objekti
Besedilo. Vsi fragmenti kode, združeni med zavitimi oklepaji {...}, so
objekti Funkcija.

Literal         | Korenski objekt | Primer
--------------- | ------------ | ----------
števila         | Število      | 1,2,3... 
besedila        | Besedilo     | \['hello'\]
funkcija        | Funkcija     | { 1 + 2. }.
                
     
Objekti, kot so števila in besedila, vedno izvirajo iz korenskega
objekta. Vsa števila na primer izhajajo iz objekta **Število**. Vsa
besedila izhajajo iz **Besedilo**, vsi fragmenti kode pa iz **Funkcija**. Vsi
ti objekti pa izvirajo iz **Objekt**, ki je pravzaprav
korenski objekt vseh objektov.


## Sporočila

Programiranje v XOScript v bistvu pomeni
pošiljanje sporočil objektom. Splošni zapis za pošiljanje sporočila
objektu je naslednji:

```
<object> <message>
```

Če želite na primer ugotoviti, ali je število **2** sodo, se
objektu **2** pošlje sporočilo **sodo?**:

```
2 sodo?
```

Odgovor bo **Resnično** (spet objekt). Neznana sporočila objekti
običajno prezrejo; napaka torej ne nastane. Nekateri objekti (npr.
števila ali besedila) se na neznano sporočilo odzovejo na vnaprej določen način
(več o tem pozneje).

Objekt lahko prejme tri vrste sporočil. 

Vrsta           | Število argumentov
--------------- | -------------------
Unarno          | 0      
Binarno         | 1     
S ključnimi besedami | 1+    


Prvič, obstajajo **unarna
sporočila** (glejte zgornji primer), ki nimajo argumentov. Drugič,
obstajajo **sporočila s ključnimi besedami**, ki imajo enega ali več argumentov,
na primer:

```
>> x := Število med: 1 in: 10.
```

V tem primeru se sporočilo **med:in:** pošlje objektu **Število**, ki
je korenski objekt vseh števil. Rezultat bo naključno število
med 1 in 10. Nazadnje obstajajo **binarna sporočila**, ki imajo
le en znak in en argument:

```
2 + 3
```

To je videti kot matematična vsota, vendar je pravzaprav le še eno sporočilo.
Sporočilo **+** se pošlje objektu **2** z argumentom **3**, kar vrne
odgovor **5**. Binarna sporočila se lahko pišejo brez dvopičja.

Binarna sporočila je mogoče veriženo pošiljati:

```
>> x := 3 + 2 - 1.
```

V tem fragmentu se **+ 2** najprej pošlje objektu **Število** **3**, kar
da objekt Število **5**, nato pa se temu številu pošlje **-1**.
Pozorni bralci bodo upravičeno opazili neskladje, ki ga
ta protokol kaže glede na običajni matematični vrstni red
operatorjev. XOScript zanemari matematični vrstni red v prid
doslednosti svojega sistema sporočil. Zato je rezultat vsote:

```
2 + 3 * 5 = 25
```

in ne 17.

Tako je zasnovano. Z oklepaji lahko spremenite vrstni red:

```
2 + (3 * 5) = 17
```

Večina objektov se kot odziv na določeno sporočilo vrne sama.
To je koristno, saj spodbuja nadaljnji dialog s tem
objektom s pošiljanjem naslednjega sporočila:

```
Izhod piši:
[' zdravo '] obreži velike-črke.
```

```
ZDRAVO
```

Tukaj se objektu **Besedilo** pošljeta dve sporočili: **obreži**, ki mu sledi
**velike-črke**.

V naslednjem fragmentu je vejica nujna za označitev,
da prihaja novo sporočilo. Sicer se XOScript zmede.

```
Izhod piši: ['Hello!'], nova-vrstica.
```

Najprej se simbolu svinčnika pošlje sporočilo **piši:**, ki mu sledi
**nova-vrstica**. Brez vejice bi XOScript mislil, da želite
**nova-vrstica** poslati **besedilu** **Hello!**, kar bi bilo jalovo početje.

Vrstni red obdelave sporočil je naslednji: od leve proti desni;
najprej sporočila v oklepajih, nato unarna sporočila. Zatem
binarna sporočila, na koncu pa sporočila s ključnimi besedami. Glejte primer
spodaj:

```
Izhod piši: 0.5 zaokroži + (2 - 1), nova-vrstica.
```

XOScript vedno bere od leve proti desni: najprej se sporočilo **piši:**
pošlje objektu Izhod, nato sledi sporočilo **nova-vrstica**. Tudi znotraj
samega argumenta XOScript bere od leve proti desni, torej **0.5 zaokroži**
in nato **+**.

{{note}}
Sporočilo nova-vrstica besedilu doda znak za novo vrstico.
Ime tega sporočila je navdihnjeno s telegrafskimi sistemi.
V sporočilih telegrafskih sistemov 
se je pogosto uporabljala beseda STOP za označitev konca stavka
(ker so bila ločila nezanesljiva ali draga).
{{/note}}

Poleg tega ima **zaokroži** prednost pred **+**, ker je
**unarno sporočilo**. Zaradi oklepajev se najprej izračuna **2 - 1**,
nato pa se **1** prišteje rezultatu **0.5 zaokroži** (1).

Celoten postopek da rezultat **2**, ki je tudi izpisani
odgovor. Za vejico sledi sporočilo nova-vrstica, ki premakne kazalec
v novo vrstico. Seveda je najboljši način za popolno razumevanje vrstnega
reda v programih XOScript vaja.

Velja omeniti, da so v XOScript, za razliko od mnogih drugih programskih
jezikov, presledki temeljni del sintakse. Zlasti
pri binarnih sporočilih lahko presledki povzročijo nekaj
zmede. Za binarnim sporočilom vedno uporabite presledek. Števila ne morete
pripeti neposredno k sporočilu, na primer: 

```
3 + 2
```

se razlikuje od 

```
3 +2
```

Prvi primer (**3 + 2**) pošlje
sporočilo **+** številu **3** z argumentom, številom **2**.
Rezultat bo v tem primeru **5**. V drugem primeru (**3 +2**)
se številu **3** pošlje unarno sporočilo **+2**. Glede na
kontekst je lahko rezultat zelo drugačen.

## Neobstoječe metode

Pošiljanje sporočila objektu sproži funkcijo, ki je bila
temu objektu pripeta pod tem imenom sporočila. Če pošljete sporočilo,
ki ga objekt ne razume, ga bo prejemni objekt prezrl
in namesto tega vrnil referenco nase za nadaljnjo komunikacijo.
Temu pravimo strpno posredovanje sporočil.

Primer:

```
Izhod piši: Objekt blah, nova-vrstica.
```

To ne bo povzročilo napake. Preprosto bo izpisalo besedilo **Objekt**.


## Nadzor toka

V XOScript ni potrebe po ločenih slovničnih pravilih za *zanke* in
*pogoje*. Pogojni stavek je le preprosto sporočilo **resnično:** ali **neresnično:**
objektu **Resnično** ali objektu **Neresnično**:

```
2 sodo? resnično: {
	Izhod piši: ['Dva je sodo število'], nova-vrstica.
}.
```
V prejšnjem primeru se sporočilo **resnično:** pošlje objektu **Resnično** (
odgovoru na vprašanje: ali je 2 sodo število?). Kot argument se pošlje
še dodaten fragment kode: objekt **Funkcija**. Ta funkcija na
zaslon izpiše, da je 2 res sodo število.

Tudi za *zanko* ni potrebe po ločenih pravilih zapisa. Če želite
fragment kode izvesti trikrat, preprosto pošljite **\*** z argumentom
**3** tej **Funkcija**:

@test5

V tem fragmentu kode je **i** indeks. Ko se Funkcija izvede prvič,
je **i** enak 0, ko se izvede naslednjič, je **i** = 1 in
tako naprej.

Oglejmo si še en primer. Ko je treba izpisati pretvorbeno tabelo
iz *kJ* (kilojoulov) v *kcal* (kilokalorije) v korakih po 100,
je pravilni zapis naslednji:

@test599

Tukaj se številka trenutne vrstice prenese v parameter
**:vrstica**. Na začetku funkcije se definirajo parametri
funkcije. Neuporabljeni parametri ostanejo prazni (**Nič**). Parametri so
vedno postavljeni na začetek funkcije, neposredno za začetnim
zavitim oklepajem, pred njimi pa je dvopičje.

Sporočilo **dokler:** je kombinacija *zanke* in *pogoja*.
S sporočilom **dokler:** lahko povežete dve funkciji. Prejemna funkcija
se izvaja, dokler funkcija za dvopičjem ne da negativnega
rezultata. Primer:

@test600

V zgoraj prikazanem fragmentu kode se **x** prišteva **1**, dokler
je **x** manjši od **5**. Ko to ne drži več, druga
funkcija odgovori z **Neresnično**, zato se izvajanje
prve funkcije konča. Upoštevajte, da je **x** definiran zunaj
funkcije in je globalna spremenljivka. Če želite izvedeti več o pravilih dosega,
glejte poglavje o funkcijah.

## Interpolacija besedila

Seznam *kJ/kcal* bi bil lahko
preglednejši. Najbolje bi bilo, da bi bil seznam takšen:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Ko želeni izpis pretvorite v predlogo, bi bil njen zapis lahko
takšen:

```
number1 kJ ➞ number2 kcal
```

To pomeni, da **number1** predstavlja vrednost v kJ, **number2** pa
vrednost v kcal. Tako deluje interpolacija besedila v XOScript.
Za to v XOScript niso potrebna ločena slovnična pravila. Besedilu preprosto
pošljite besedo, ki jo je treba zamenjati, z nadomestnim besedilom
kot argumentom:

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

To pravilo zamenjave velja za vsako nedefinirano sporočilo, ki ga prejme
objekt **besedilo**. Vsako sporočilo, ki ga objekt **besedilo**
ne prepozna, bo razloženo takole: *besedilo sporočila zamenjaj
z besedilom v argumentu sporočila.* Program lahko prilagodite
takole:


@test601


Da bi se izognili zmedi glede tega, katero sporočilo je mogoče uporabiti kot
nadomestek in katero ne, je najbolje uvesti oznako predloge, kot je &lt; &gt;,
za dele besedila v predlogi, ki jih
je treba zamenjati.

## Vrnjene vrednosti

Za odgovor na sporočilo se uporablja puščica za vračanje
(*<-*). Naslednji primer prikazuje, kako ustvariti nalogo
za izračun odstotka:

@test602

Ko je naloga definirana in prirejena spremenljivki **percentage**,
se ji pošlje sporočilo **uporabi:in:** z argumentoma **100** in **7**.

To izvede nalogo na **100** in **7**, tj. 7 % od 100.
S puščico za vračanje se odgovor iz naloge vrne
v glavni program.

## Razširjanje

Čeprav je ta koda veljavna, ima pomanjkljivost,
saj si je treba zapomniti vrstni red argumentov. Zakaj torej ne bi
zapisali takole: *7 percent of: 100 *? To bi bilo videti precej bolj
*naravno*. Da bi to omogočili, moramo prilagoditi starševski objekt
**7**, torej objekt **Število**, tako da bo razumel
sporočilo **percent of:**. To dosežemo tako, da objektu Število pošljemo
**ob:izvedi:**, takole:

@test603

Ker je odstotek v tem primeru kar število samo, se sklicujemo na sebe,
s ključno besedo *sebe*. Skratka, simbol sebe pomeni: *pošlji to
sporočilo meni samemu*.

# Objekti

{{messages}}

Poleg prilagajanja in razširjanja obstoječih objektov lahko nove
objekte ustvarite tudi sami, preprosto s pošiljanjem sporočila **nov**. Recimo,
da bi radi ustvarili objekt računa, ki zagotavlja zaporedno
številčenje; v tem primeru najprej potrebujete objekt računa.

Ker vsak objekt izhaja iz drugega objekta, ta pa
na koncu izvira iz korenskega objekta vseh objektov, imenovanega Objekt,
se je treba odločiti, na katerem od teh drugih objektov bo
temeljil vaš novi objekt. Novi objekt podeduje vse lastnosti
objekta, na katerem temelji, torej objekta, ki mu je bilo sporočilo **nov**
prvotno poslano.

V tem primeru je zaželen razmeroma nevtralen objekt, brez preveč
podedovanih lastnosti. Izbira je preprosta, saj lahko v tem primeru
novi objekt temelji kar na samem korenskem objektu, torej na
**Objekt**. Zapis predvidenega sistema računov bo potem
takšen:

@test604

Trenutna številka računa je shranjena v objektu, zato je
pred njo postavljena ključna beseda **svoj**. Temu pravimo *lastnost*;
več podrobnosti sledi.

Nekatera podjetja želijo, da je leto vključeno v številke
računov. V tem primeru lahko ustvarite nov objekt računa, ki temelji na
prejšnjem objektu računa, vendar uporabniku omogoča
vnos določenega leta:

@test605

Implementacije sporočila **število** ni treba pisati
znova, saj je podedovana od prej napisanega **objekta
računa**; tako je mogoče staro kodo ponovno uporabiti. XOScript nima konceptov,
kot so razredi in drugi sorodni koncepti. To pomeni, da lahko objekti
dedujejo le od drugih objektov, kar imenujemo tudi *prototipno
dedovanje*.

Vrnimo se k lastnostim. Do lastnosti objekta je mogoče dostopati le
*znotraj hierarhije objekta*, zato teh lastnosti
drugi objekti ne morejo zaznati.

Za razliko od drugih programskih jezikov so vse lastnosti objektov
vidne izključno objektu, ki je lastnost ustvaril, in
izpeljanim objektom. 

Pogosto uporabljena tehnika je uporaba objekta kot nekakšnega *načrta*,
kar velja na primer za prej obravnavane račune.
Še en dober primer je **Point**. Recimo, da ustvarite
računalniški program, ki izvaja izračune s točkami na zemljevidu. Lahko
razvijete objekt **Point** z lastnostma
x-koordinata in y-koordinata, ki bosta zunanjemu svetu na voljo
prek sporočil:

@test606

Sporočilo **=** primerja točki s sporočilom **in:**. Prva
primerjava da **Resnično** ali **Neresnično**. To sta logična
objekta. Ko objektu Resnično pošljete sporočilo **in:** in je
objekt argumenta za dvopičjem prav tako **Resnično**, boste
kot odgovor spet prejeli **Resnično**. Kadar je kateri koli od njiju **Neresnično**,
boste prejeli odgovor **Neresnično**. Upoštevajte, da ena točka ne more brati koordinat
druge. Drugi točki je treba poslati sporočilo, s katerim jo vprašamo
za te podatke: **x-coordinate** in **y-coordinate**. Kot je bilo že
razloženo, so lastnosti dosegljive le znotraj
same družine objektov. 

Upoštevajte, da se tukaj za primerjavo točk uporablja sporočilo **=**.
Prav tako bi lahko uporabili drugo sporočilo, na primer
**is:** ali **equal:**, vendar se je ponovna uporaba znaka **=** v tem primeru zdela
primerna.

## Dedovanje

Prej napisano kodo lahko ponovno uporabite za ustvarjanje hierarhije
objektov. Na primer:

```
>> Žival := Objekt nov.
>> Pes := Žival nov.
>> Pudelj := Pes nov.
```

V tem primeru **Dog** podeduje vse vedenje in lastnosti
objekta **Animal**, objekt **Animal** pa podeduje vse vedenje
objekta **Objekt**, korenskega objekta vseh objektov.


## Prepisovanje


V naslednjem primeru se ustvari nova vrsta seznama:
**Combination**, v katerem je zagotovljeno, da je vsak element edinstven.
Funkcije seznama se ponovno uporabijo z dedovanjem:

@test607

Opazite, kako je drugi **red** izključen s seznama.

Občasno je treba prepisati vedenje objekta.
Na primer, kadar je treba pri seštevanju števil upoštevati merske
enote. V naslednjem primeru se ustvari objekt **Size**.
Ta objekt vrne število, ki pri seštevanju
upošteva enoto števila, ki se prišteva. Objekt **Število**
preveri, ali gre za *palce* ali *čevlje*. Programska koda
bi lahko bila podobna naslednji:

@test608

## Rekurzija

V prejšnjem primeru je **znak** plus prepisan. Upoštevajte,
da je treba končno seštevanje na koncu vseeno izvesti, kar se
pravzaprav zgodi v naslednji vrstici:

```
>> odgovor := sebe + (število x faktor).
```

Kako torej XOScript razume, da se ta **znak** plus nanaša na
izvirno logiko seštevanja?** Druga razlaga bi na primer lahko
bila, da bo XOScript isto sporočilo vedno znova pošiljal istemu
objektu, kar bi povzročilo **neskončno zanko**. Jasno je,
da to ni namen. Takoj ko objektu pošljete sporočilo,
ki bi izvedlo popolnoma isto kodo, XOScript ugotovi,
da je v tem primeru mišljeno spodaj ležeče, prepisano sporočilo. Vaš
program je tako samodejno zaščiten pred to obliko neskončnih
zank. Kadar pa je res vaš namen iz trenutne funkcije zagnati isto
funkcijo, morate najprej poslati sporočilo
**rekurziven**. V tem primeru bo rezultat neskončna
zanka. Vendar obstajajo koristne uporabe rekurzivnih nalog,
recimo, da želite izračunati fakulteto danega
števila. V tem primeru objektu Število preprosto dodajte sporočilo **factorial**:

@test609

To zahteva rekurzijo. Naloga, povezana s
sporočilom **factorial**, se mora namreč znova izvesti znotraj te funkcije.
Funkcijo fakultete je torej treba poklicati iz same
funkcije fakultete. XOScript praviloma prepreči ta postopek
zaradi nevarnosti neskončne zanke. Zato
je ključno, da pred sporočilo postavite besedo **rekurziven**. S tem
XOScript obvestite, da je vaš
namen izvesti isto nalogo in da se niste zmotili.

## Objekti, podobni razredom

Čeprav xoscript ne ponuja razredov, je posnemanje vedenja, podobnega
razredom, trivialno. Preprosto prepišite sporočilo nov.

```
>> Žival := Objekt nov.
Žival ob: ['nov'] izvedi: {
	<- sebe nov inicializiraj.
}.

Žival ob: ['inicializiraj'] izvedi: {
	svoj zvok := ['?'].
	svoj noge  := 4.
}.
```

V zgornjem fragmentu kode ustvarimo objekt z imenom Animal.
Ta objekt služi kot *načrt* za vse vrste živali,
kot so psi in mačke. Starševski objekt Animal je zapisan
z veliko začetnico A, kar pomeni, da gre za objekt, podoben razredu.
Nato prepišemo sporočilo nov tako, da napišemo lastno metodo nov.
V tem primeru ta pošlje sporočilo nov objektu sebe, nato pa še sporočilo
inicializiraj. Ker xoscript rekurzijo privzeto blokira, to ne bo povzročilo
neskončne zanke. Namesto tega bo sporočilo nov poslano starševskemu
objektu (Objekt), kar ustvari nov primerek objekta Animal. Tako ustvarimo
nov objekt, ki temelji na istem objektu, za katerega smo ustvarili metodo nov.
To je povsem veljavno. Zdaj pošljemo še sporočilo inicializiraj, ki zagotovi,
da ima objekt Animal privzete vrednosti svojih lastnosti. Privzeto
ima žival 4 noge, oglašanje pa je neznano (od tod vprašaj).
Za ustvarjanje novega primerka objekta Animal lahko preprosto zapišemo:

```
>> a := Žival nov.
```

Zdaj dobimo nov primerek objekta Animal s 4 nogami, neznanim oglašanjem in
metodo inicializiraj. Tako kot v drugih objektno usmerjenih jezikih lahko
svoj objekt Animal tudi razširimo:

```
>> Pes := Žival nov.
Pes ob: ['inicializiraj'] izvedi: {
	sebe inicializiraj.
	svoj zvok := ['laja'].
}.
```

To lahko preprosto preizkusimo z dodajanjem metode besedilo:

```
Žival ob: ['besedilo'] izvedi: {
	<- svoj noge besedilo + svoj zvok.
}.
```

Združimo vse skupaj:

@test13


Ustvarjanje objekta, ki je postavljen v dano začetno stanje, je
pogosta težava. Recimo, da je treba ustvariti objekt **Rectangle**
za izračun obsega in ploščine. Možen zapis bi bil:


```
>> Pravokotnik := Objekt nov.

Pravokotnik ob: ['ploščina'] izvedi: {
	<- svoj dolžina * svoj širina.
}.
```

Očitno je nastavitev dolžine in širine predpogoj. V ta
namen lahko dodamo sporočili **dolžina:** in **width:**:


```
Pravokotnik ob: ['length:'] izvedi: { :dolžina
	svoj dolžina := dolžina.
}.

Pravokotnik ob: ['width:'] izvedi: { :širina
	svoj širina := širina.
}.

```

Ta pravokotnik lahko nato uporabimo takole:


```
>> pravokotnik := Pravokotnik nov length: 2, width: 3.
Izhod piši: pravokotnik ploščina.
```

Če pa začetni nastavitvi dolžine in širine spregledamo,
se pojavi sporočilo o napaki:

```
>> pravokotnik := Pravokotnik nov.
Izhod piši: pravokotnik ploščina.
```

bo povzročilo naslednjo napako:

```
Ključa ni mogoče najti:dolžina
```

Da bi to preprečili, je bolje, da ima pravokotnik
vedno začetno dolžino in širino, na primer 0. V tem
primeru je torej treba **prepisati** sporočilo **nov**.

@test610

Če prepišemo sporočilo nov, v bistvu posnemamo **razred**.

Svet XOScript je poln raznovrstnih objektov, ki so
vašemu programu na voljo že od začetka. V naslednjih poglavjih
bodo obravnavani vsi ti osnovni objekti.

## Posnetki

Objekt (skupaj z njegovim trenutnim stanjem) lahko shranite na disk z:

```
mojobjekt save-as: ['saved.bin'].
```

Za ponovno nalaganje objekta z diska:

```
>> mojobjekt := Objekt load-from: ['saved.bin'].
```

Posnetke lahko uporabite za shranjevanje določenega stanja ali za izboljšanje zmogljivosti.
Nalaganje posnetka se izogne leksikalni analizi, razčlenjevanju in nastavitvi aplikacije.
Poleg tega bodo v prihodnosti s posnetki morda uvedene dodatne prednosti
glede zmogljivosti, na primer optimizacija določenih vzorcev ali zaznavanje in
optimizacija vročih poti.

{{warning}}
Posnetki so poskusna zmožnost; ne uporabljajte je v produkciji.
Za vklop poskusnih zmožnosti prevajajte z -D EXPERIMENTS.
{{/warning}}


@test712

# Objekt Nič

{{messages}}

Objekt Nič
predstavlja praznino ali, še bolje, odsotnost informacije.
Občasno boste ta objekt prejeli kot odgovor na sporočilo,
kadar je rezultat **nič**. Najpomembnejše vprašanje,
ki ga lahko zastavite objektu **Nič**, je: **Nič?**.
Odgovor bo vedno **Resnično**.

```
Izhod piši: Nič Nič?.
```

rezultat:

```
Resnično
```

Vsak objekt razen **Nič** bo odgovoril z **Neresnično**. Zgornji
fragment kode se morda zdi nekoliko filozofski, vendar ima objekt **Nič**
vsekakor izjemno praktične uporabe. Objekt Nič boste na primer
prejeli kot odgovor, če zahtevate
element seznama, ki ne obstaja. Objekt Nič lahko uporabite tudi,
če želite deklarirati spremenljivko, vendar ji še ne želite določiti
vrednosti. Namesto tega ji preprosto **priredite** posebno vrednost **Nič**. V
XOScript ni dovoljeno deklarirati spremenljivke brez vrednosti, na primer:


```
>> vrednost.
```

Namesto tega morate zapisati naslednje:

```
>> vrednost := Nič.
```

@api_None_base

# Logične vrednosti

{{messages}}

Za razliko od večine priljubljenih programskih jezikov v času pisanja
XOScript zagotavlja le en sam objekt Resnično in en sam objekt
Neresnično. Natančneje: vsakič, ko zapišete **Resnično**, to ne pomeni,
da je bil ustvarjen nov objekt. Namesto tega vedno uporabite referenco. To
pomeni, da ko zapišete naslednje:

\>\> x := Resnično.

se **x** nanaša na objekt **Resnično**. Pogojna koda in zanke prav tako
preverjajo to referenco. V XOScript pomen **Resnično** in **Neresnično**
ni nespremenljiv. Program XOScript pravzaprav pošteno pretrese
stavek, kot je ta:

Resnično := Neresnično.

Rezultat takšnih dejanj ni definiran, vendar ostaja veljavno
dejanje in je zato formalno dovoljeno. Poleg tega obstaja objekt
Logični, ki je korenski objekt tako za **Resnično** kot za **Neresnično**, saj sta oba
izpeljanki korenskega objekta. Sam objekt Logični pa
nima nobene praktične uporabe.

## Pasti

Bodite previdni pri uporabi **in:** in **ali:**

```
Izhod piši: (Neresnično or: Resnično or: Resnično), nova-vrstica.
Izhod piši: (Neresnično ali: Resnično, ali: Resnično), nova-vrstica.
```

Vrne

```
Neresnično
Resnično
```
ker sporočilo **ali:** sprejme le 1 argument. Prvo sporočilo
objektu Neresnično pošlje **ali:ali:**, ki ne obstaja, zato objekt
sporočilo prezre in vrne samega sebe (Neresnično). Druga vrstica pa
pošlje **ali:**, ki mu sledi še en **ali:** (z uporabo simbola za veriženje, tj. vejice: ,).


@api_Boolean_base

# Števila

{{messages}}

Vsakič, ko zapišete število, na primer 9, -10 ali 3,12, ga XOScript
v ozadju pretvori v objekt **Število**. Temu
objektu Število lahko pošiljate sporočila ali pa število priredite
spremenljivki in sporočila pošljete pozneje:

```
10 sodo?

>> desetak := 10.
desetak sodo?

```

Oba zapisa sta veljavna. Objekt Število se odziva na naslednja
sporočila ...

Večina teh sporočil je samoumevnih in omogoča izvajanje
matematičnih operacij ali primerjav.

{{note}}
Namesto njihovih ustreznic v ASCII lahko uporabite ≤ ≥ ≠ × in ÷.
To je stvar okusa.
{{/note}}

Razlika med binarnimi matematičnimi sporočili (+) in
njihovimi različicami s ključnimi besedami (prištej:) je v tem, da prva vrnejo
novo število, ki je rezultat operacije, pri drugih pa se
spremeni sam objekt. To ponazarja
naslednji primer:

@test597

V zgornjem primeru je b = 4 in a = 3. S **prištej: 2** se vrednost
a poveča za 2, medtem ko **+ 3** ustvari novo število, ki je
enako a + 3. Enako velja za druge matematične postopke, npr.
množenje. Z uporabo simbola za množenje prejmete
nov objekt kot odgovor. Če uporabite sporočilo **pomnoži-z:**,
pomnožite samo število.

S sporočilom **med:in:**, na primer v: **Število
med: X in: Y**, dobite število med X in Y. Na ta
način je mogoče ustvariti poljubno naključno število:

```
>> a := Število med: 1 in: 10.
Izhod piši: a, nova-vrstica.
```

Od različice 1.4 je vgrajeni generator naključnih števil v xoscript
po našem najboljšem vedenju kriptografsko varen.

Številu lahko pripnete **določilo**, na primer **6
jabolk**. Vsako sporočilo, ki ga število ne prepozna,
se obravnava kot določilo. Določilo števila lahko pridobite
s sporočilom določilo:

Določilo je v bistvu objekt besedila, ki je shranjen skupaj z objektom
Število. Določilo se pri izpisu s **piši:** izpiše tudi za
številom. Določila lahko uporabite na primer za seštevanje zneskov
v mešanih valutah. Pri seštevanju zneskov lahko povprašate
po določilih. Naslednji primer programa ponazarja to
načelo s preračunavanjem zgodovinskih valut (saj ostaja menjalni
tečaj razmeroma stabilen!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Besedila

{{messages}}

Vsakič, ko je besedilo postavljeno med **oglate oklepaje in narekovaje** ['...'],
XOScript za vas ustvari nov objekt besedila. Vendar
pazite, da uporabite pravilne narekovaje. Narekovaj na
začetku besedila se razlikuje od tistega na koncu (tako lahko
uporabite enojni narekovaj, ne da bi ga bilo treba ubežati).

## UTF8

Besedila v xoscript običajno vsebujejo besedilo, kodirano v utf8. Čeprav
je tehnično mogoče imeti v besedilu binarno vsebino ali vsebino, ki ni utf8,
je za to priporočljivo uporabiti blobe. Blobe
zagotavlja strežniški vtičnik (glejte poglavje ffi).
Na splošno so blobi/ffi zagotovljeni
glede na vtičnik/platformo, saj so vezani na platformo
in arhitekturo (ffi/blobi). Jedro skriptnega jezika skuša
ostati čim bolj neodvisno od platforme.

## Pretvorba tipov

Z naslednjimi sporočili lahko ustvarite kopijo vsakega objekta
z drugim tipom:

Sporočilo | Rezultat
------- | ------
število  | Pretvori v število
besedilo  | Pretvori v besedilo
logični    | Pretvori v logično vrednost
  
**Veljajo** naslednja pravila:

sporočilo  | Nič      | Logični               | Število                | Besedilo      | Drugo              
-------- | --------- | --------           | --------              | --------  | --------
logični     | Neresnično     | n/a                | 0→Neresnično sicer→Resnično     | Resnično      | Večinoma Resnično
število   | 0         | Neresnično→0 Resnično→1 | n/a                       | ['n']→n | Večinoma 1
besedilo   | ['None']  | ['False']/['True'] | ['n']                 | n/a       | Odvisno

## Kopiranje

Vrednosti se v XOScript vedno prenašajo **po referenci**. V drugih jezikih
je to odvisno od tipa vrednosti, v XOScript pa obstaja le en način,
po referenci. XOScript nikoli ne naredi kopije vrednosti. Za kopiranje objekta
morate poslati sporočilo **kopiraj**. 

@test611

Tukaj bi morda pričakovali, da bo izpis Dolly namesto
Donny. Vendar ni tako, saj se obe imeni nanašata na isti
objekt. Pri delu z zanko se zgodi nekaj podobnega:

@test612

XOScript namreč **vedno** uporablja reference, zato tudi
zgoraj prikazana zanka pri **:quantity** kaže referenco na element
v seznamu.

Če želite objekt kopirati, morate to dejanje navesti
**izrecno**:

@test613

S pošiljanjem unarnega sporočila **kopiraj** besedilu objekt
vrne kopijo istega objekta besedila. Na enak način je mogoče kopirati
objekte Število, logične objekte, sezname in slovarje.

Definirate lahko tudi lastno implementacijo kopiranja; to je celo
nujno, če ustvarjate lastne objekte. Privzeta
implementacija kopiranja za seznam naredi plitvo kopijo: ustvari
nov seznam z istimi elementi.

@test614

V tem primeru se 4 doda le kopiji.
Ker pa je kopija plitva, so objekti v obeh seznamih
isti.

@test615

Če torej vsakemu imenu v kopiji pripnemo 2, to vpliva tudi na
izvirni seznam.

Da bi to odpravili, moramo narediti **globoko kopijo**. Takšno kopiranje
za seznam bi lahko sestavili takole:

@test616

Upoštevajte tudi sporočilo rekurziven; to sporočilo je treba
poslati pred sporočilom kopiraj.

Bistveno je upoštevati, da čeprav je kopija objekta
pogosto videti enako kot izvirnik, v resnici
nikoli ni isti objekt. Korenski objekt definira sporočilo **equal:**,
s katerim je mogoče primerjati identiteto objektov. Oglejte si
naslednji primer:

@test617

## Implicitna pretvorba

XOScript za pretvarjanje objektov uporablja **implicitno pretvorbo**. Za izpis
seznama na zaslon bo XOScript na primer seznamu interno poslal sporočilo
*besedilo*. To se lahko izkaže za zelo koristno, kadar
želite seznam izpisati kot seznam, ločen z vejicami.
Sporočilo *besedilo* je mogoče prepisati: 

@test620

@api_String_base
@api_Format_base


## Strežniška besedila

Naslednje zmožnosti objekta Besedilo doda
strežniški vtičnik.

@api_String_server

# Funkcije

{{messages}}

Kodo lahko združite med { in }, tako postane funkcija.
V xoscript včasih uporabljamo tudi izraz naloga ali preprosto
blok kode.

Funkcijo zaženete s pošiljanjem sporočila *zaženi*.


```
{ Izhod piši: 123, nova-vrstica. } zaženi.
```

Če vaša funkcija sprejema argumente, uporabite **uporabi:**.

```
{ :a Izhod piši: a, nova-vrstica. } uporabi: a.
```

Glejte tudi spodnje primere.
Zaradi preproste arhitekture ima lahko funkcija le
eno točko vračanja. Da bi se izognili dodatnim stroškom ali pretiranemu gnezdenju
pogojev, lahko uporabite postopek (kar je enako uporabi
znaka za množenje z argumentom 1):

```
{
  (a = 1) resnično: { x := 1. }, prekini.
  (a = 2) resnično: { x := 2. }, prekini.
} postopek.
```

Tako se (a = 2) ne bo ovrednotil, če je a = 1.
Poleg tega vam tako ni treba gnezditi sporočil resnično.
Kadar koli ugotovite, da gnezdite pogoje, pomislite
na sporočilo postopek. Vaša koda bo morda
lažje berljiva.


Tu je pomembna past:

```
{
	Neresnično neresnično: {
		Izhod piši: ['Končaj zanko.'].
	}, prekini.
	
	Izhod piši: ['Ne prikaži me.'].

} postopek.

```

V tem primeru bo prikazano besedilo 'Dont show me'.
Ker je **prekini** poslan objektu Neresnično. Če želite izvesti
prekinitev, jo morate kot sporočilo poslati objektu **Resnično**.
 

```
{
	Neresnično ne resnično: {
		Izhod piši: ['Končaj zanko.'].
	}, prekini.
	
	Izhod piši: ['Ne prikaži me.'].

} postopek.

```

Bo delovalo po pričakovanjih.

## Izjeme

Izjeme lahko obravnavate takole:

```
{ Naloga 1 } ujemi: { Naloga 2 }, zaženi.
```

V programu lahko napako sprožite tudi namerno in
s tem aktivirate blok za obravnavo. To storite tako, da trenutni nalogi
pošljete sporočilo **napaka:**, kot je prikazano v naslednjem
prikazu:

```
{
ta-naloga napaka: ['Ojoj!'].
} ujemi: { :zmota
Izhod piši: zmota.
}, zaženi.
```

## Vstavljanje vrednosti

XOScript nalogam omogoča vstavljanje vrednosti. Oglejte si
spodnjo nalogo:

```
>> pošiljanje := {
	Novice komu: svoj recipient.
}.
pošiljanje nastavi: ['recipient']
vrednost: ['info@recipient.org'].
pošiljanje zaženi.
```


Ta prikaz predstavlja namišljeno nalogo, ki pošilja novice
na e-poštni naslov ali **prejemniku** (**recipient**). Tega prejemnika je mogoče vstaviti
v nalogo od zunaj, preden se naloga zažene, s pošiljanjem
sporočila **nastavi:vrednost:** nalogi. S tem je vrednost
**recipient** vnaprej nastavljena v nalogi. To vrednost je mogoče tudi spremeniti
in nalogo nato znova zagnati. To je uporabna metoda pri uporabi
objektov nalog.

## Prazne funkcije

Prazne naloge niso dovoljene. Teoretično bi bila prazna naloga videti
takole: **{}**, vendar XOScript to obravnava kot jezikovno napako. Če
želite deklarirati prazno nalogo, lahko uporabite objekt Nič:

```
>> opravilo := Nič.
```

Čeprav to ni prava naloga, ampak objekt Nič, mu je sporočilo zaženi
še vedno mogoče poslati:

```
>> odgovor := opravilo zaženi.
```

To je pravzaprav enako kot:

```
>> odgovor := Nič zaženi.
```

Ker objekt **Nič** ne prepozna sporočila **zaženi**,
kot odgovor vrne samega sebe, tako da je odgovor spet **Nič**.
Prazna naloga torej ni potrebna. Zaradi elegantne
zasnove programskega jezika XOScript lahko za to preprosto uporabite objekt
Nič.

## Dinamični doseg

Ko Funkcija potrebuje spremenljivko, a je ne najde,
preveri spremenljivke Funkcije, ki jo je **poklicala**,
in nadaljuje s preverjanjem navzgor po verigi Funkcij.
Ta postopek iskanja traja, dokler spremenljivka ni najdena.
Če spremenljivke še vedno ni mogoče najti, se prikaže sporočilo o napaki. Temu načinu iskanja
spremenljivke pravimo **dinamični doseg**.

Za ponazoritev tega načela:

@test618

@api_Code_base

# Korenski objekt

{{messages}}

Objekt z imenom **Objekt** je korenski objekt vseh objektov v
XOScript in zagotavlja osnovne zmožnosti jezika. 

Najpogosteje poslano sporočilo
je **ob:izvedi:**, ki razširi funkcionalnosti objekta. To
sporočilo prejme korenski objekt, ki nato podano
nalogo poveže s sporočilom in s tem razširi izpeljani
objekt.

## Metode za vse ostalo

Če pošljete sporočilo, ki ne ustreza nobeni
metodi v objektu, je običajno prezrto. Lahko pa določite
tako imenovane **čarobne metode** ali metode **za vse ostalo**, ki se
sprožijo, kadar objekt sporočila ne razume.

Na voljo so 4 metode za vse ostalo. Vsako sporočilo ustreza
določenemu številu argumentov.

Sporočilo za vse ostalo    | Število argumentov
-------------------- | -------------------
odgovori:             | 0
odgovori:in:         | 1
odgovori:in:in:     | 2
odgovori:in:in:in: | 3


@test619

## Programska sporočila

Namesto da sporočilo pošljete neposredno objektu, ga lahko
pošljete tudi prek spremenljivke. Za to uporabite sporočilo
**sporočilo:argumenti:**. 

@test396

@api_Object_base

# Seznami

{{messages}}

XOScript pozna dve vrsti zbirk: *sezname* in *slovarje*.
**Seznami** so naštevanja objektov v *nespremenljivem vrstnem redu*. Slovarji
nimajo vrstnega reda, temveč so podobni legendi s ključem (ali pojmom) in
pripadajočo vrednostjo. Seznami so primerljivi s polji (PHP, Java, C)
in seznami (Python). Slovarji so primerljivi z asociativnimi polji (PHP) ali
slovarji (Python) v drugih programskih jezikih. Za ustvarjanje
novega Seznama zapišite:

```
>> fibonacci := Seznam nov.
```

Ta prazen seznam lahko napolnite z **dodaj-na-konec:** :

```
fibonacci dodaj-na-konec: 0.
fibonacci dodaj-na-konec: 1.
fibonacci dodaj-na-konec: 1.
fibonacci dodaj-na-konec: 2.
fibonacci dodaj-na-konec: 3.
fibonacci dodaj-na-konec: 5.
fibonacci dodaj-na-konec: 8.
fibonacci dodaj-na-konec: 13.
```

Če seznam izpišemo na zaslon:

```
Izhod piši: fibonacci, nova-vrstica.
```

Bomo videli:

```
Seznam ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

Namesto dodaj-na-konec lahko za dodajanje elementov v seznam uporabite tudi ;:


```
>> fibonacci := Seznam nov ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Podpičja (;) so vsa binarna sporočila, ki vrednost postavijo
v seznam.

## Veriženje

Recimo, da imate seznam, kot je:

```
>> x := Seznam nov ; 1 ; 2 ; 3.
```

Če bi radi izbrisali prvi in zadnji element, bi bilo vaše
sporočilo:

```
x vzemi-prvega vzemi-zadnjega.
```

Žal prejšnji zapis ne bo deloval pravilno.
Sporočilo **vzemi-prvega** vrne prvi element seznama, ta pa
postane prejemnik sporočila **vzemi-zadnjega**. Sporočilo
**vzemi-zadnjega** torej ni poslano objektu **x**, temveč številu 2.
Možna rešitev te težave bi bila, da napišete dva ločena
stavka, na primer: 

```
x vzemi-prvega.
x vzemi-zadnjega.
```

To pa je precej nepraktično, zlasti kadar morate
izbrisati več kot dva elementa. Zato XOScript za takšne primere ponuja
alternativno strukturo sporočil. V
**alternativnih** strukturah sporočil se odgovori objektov prezrejo
in kot odgovor vedno znova dobite prejemni objekt.
**Alternativna** struktura sporočil se začne s pošiljanjem
sporočila **stori** objektu, **alternativno** strukturo
sporočil pa končate s pošiljanjem sporočila **končano**. V
prikazanem primeru bi to lahko uporabili takole:

```
>> x := Seznam nov ; 1 ; 2 ; 3.
x stori vzemi-prvega vzemi-zadnjega končano.
```

@api_List_collections

# Slovarji

{{messages}}

**Tako Seznam kot Slovar sta zbirki. Vendar za razliko od
seznama slovar **nima** vrstnega reda. Druga razlika med njima
je, da je slovar sestavljen iz parov objektov. En objekt služi kot vnos (ali
ključna beseda) za iskanje drugega objekta. Dober primer
takšnega seznama je cenik, na primer:


```
>> jedilnik := Slovar nov
	postavi: ['£5'] na: ['jabolčna pita'],
	postavi: ['£6'] na: ['korenčkova torta'],
	postavi: ['£3'] na: ['fudge'].
```

Podobno kot pri seznamu se za dodajanje objekta v seznam uporablja sporočilo postavi:na:.
Razlika je v tem, da se za razliko od
seznama povežeta dva objekta. Prvi objekt je, podobno
kot pri seznamu, objekt, ki ga boste shranili v seznam. Drugi
objekt ni njegov položaj v zbirki, temveč **vnos**,
ki omogoča, da prejšnji objekt pozneje pridobite. Skratka,
slovar deluje nekoliko kot pravi slovar; s ključno besedo
je torej mogoče najti pomen. Na primer, za pridobitev cene
fudža iz zgoraj omenjenega seznama:

```
>> price := jedilnik na: ['fudge'].
```

Uporabite lahko tudi jedrnat zapis:

```
>> price := jedilnik ? ['fudge'].
```

Če vnosi, ki jih uporabljate za shranjevanje objektov, nimajo presledkov
(in ne trčijo z drugimi vnaprej določenimi sporočili),
lahko uporabite tudi naslednji zapis:

```
>> jedilnik := Slovar nov
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Zgornji zapis se nedvomno bere nekoliko bolj naravno.
Za poizvedbo po ceni
fudža lahko uporabite naslednji poenostavljeni zapis:

```
>> price := jedilnik fudge.
```

@api_Dict_collections

# Datoteka

{{messages}}

Objekt **Datoteka** zagotavlja osnovni dostop do datotečnega sistema.
S tem objektom lahko naenkrat preberete celotne datoteke v spremenljivko
ali naenkrat zapišete spremenljivke v datoteke. Podprto je tudi branje
po vrsticah. To so najpogostejše datotečne V/I operacije
v skriptnem jeziku. Napredne datotečne operacije zahtevajo
uporabo FFI prek strežniškega vtičnika ali ločenega V/I vtičnika.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Datum/čas

{{messages}}

Za strukturiran prikaz časa in datuma XOScript uporablja
objekt **Trenutek**. Če nov objekt Trenutek izpišete na zaslon, se
prikažeta trenutni datum in čas:

```
Izhod piši: Trenutek nov, nova-vrstica.
```

Rezultat je lahko na primer takšen:

```
2020-10-10 12:16:39
```

Preprosto je tudi prebrati posamezne sestavine časa. Če na primer
potrebujete le trenutno leto, lahko trenutku pošljete sporočilo
**leto**, odgovor pa bo
objekt Število, ki vsebuje le leto:

```
>> m := Trenutek nov.
Izhod piši: m leto, nova-vrstica.
```

@api_Moment_system

# Program/StdOut

{{messages}}

Objekt Program predstavlja trenutno delujočo aplikacijo. Ta objekt
ponuja funkcionalnost za izvajanje sistemskih ukazov, vključevanje podprogramov,
branje argumentov in drugo. Vse funkcije, povezane s sistemom.

## StdOut

Izhod je objekt standardnega izhoda. V bistvu ima dve metodi:
**piši:** in **nova-vrstica**. Sporočilo piši: se uporablja za pošiljanje besedila
na stdout, sporočilo nova-vrstica pa izpiše znak za novo vrstico.
Namesto **nova-vrstica** lahko uporabite tudi \\n.

Primer:

```
Izhod piši: ['Hello World'], nova-vrstica.
```

rezultat:

```
Hello World
```

## Moduli/vtičniki

Svet XOScript je mogoče razširiti z novimi sistemskimi objekti z
namestitvijo modulov. Nov sistemski objekt lahko svetu
XOScript dodate tako, da datoteko modula (običajno datoteko s pripono .so)
postavite v mapo mods. 

Ko pošljete sporočilo objektu, ki je na voljo prek
modula vtičnika, ga XOScript samodejno naloži.

Vtičnike lahko pišete tudi sami. Vtičniki so napisani v
programskem jeziku C. Primer vtičnika najdete v paketu izvorne
kode pod src/plugins/example.


## Refleksija

Obstajajo različni načini za raziskovanje
sistema med izvajanjem programa. XOScript ima nekaj metod za
ugotavljanje, kateri objekti so prisotni in na katera sporočila se ti objekti
odzivajo. Najprej lahko vsak objekt vprašate, kateri je njegov **tip**,
vendar so tipi v XOScript spremenljivi in zato nezanesljivi.

Objekt Program lahko vprašate tudi, ali je
dani objekt že prisoten v programu:

```
Program Orodje resnično: { ... }.
```

Pri imenu objekta,
ki je sestavljeno iz enega samega simbola, je za preprečitev zmede najbolje uporabiti
naslednji zapis:

```
Program najdi: ['X'], resnično: { ... }.
```

Poleg spraševanja o objektih lahko objekt Program sprašujete tudi
o sporočilih. Vprašate ga lahko na primer, ali
objekt **Število** pozna sporočilo **med:in:**, na način,
kot je prikazan spodaj:

```
Program Number: ['between:and:'], nova-vrstica.
```

@api_Program_system

# Strežnik

{{messages}}

Strežniški vtičnik v xoscript ponuja funkcionalnost za
ustvarjanje strežniških aplikacij. Za nalaganje strežniškega
vtičnika uporabite:

```
Server inicializiraj.
```

Za vaše udobje je priporočljivo naložiti tudi
datoteki webtools.xo in template.xo.

```
Program uporabljaj: ['webtools.xo'].
Program uporabljaj: ['template.xo'].

```

## Nastavitve strežnika

Nastavite lahko naslednje nastavitve strežnika:

```
	# podane so privzete vrednosti,
	# zato se, če ničesar ne nastavite, uporabijo
	# te vrednosti...

	Program 
	nastavitev: ['max-postfields']
	vrednost: 40.

	Program 
	nastavitev: ['max-contentlength']
	vrednost: 2000000. # 2MB

	Program 
	nastavitev: ['max-time']
	vrednost: 5000. # 5sec

```

## Pozdravljen, svet

Tukaj je zelo preprost spletni program, ki ga lahko uporabite s
standardnim strežnikom CGI, kot so Apache2, NGINX, OpenHTTPD ali kateri koli drug
znan strežnik.

```
#!/bin/xo

Server inicializiraj.
Program uporabljaj: ['webtools.xo'].

>> spletni-dok := Spletni-dokument nov.

spletni-dok izpiši: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Če objekta Spletni-dokument ne želite uporabljati, ni težav, vendar
morate potem glave HTTP napisati sami:

```
#!/bin/xo
Izhod piši: ['Content-type: text/html; charset=utf-8 \n\n'], nova-vrstica.
Izhod piši: ['pozdravljen svet!'], nova-vrstica.
``` 

## Zahteva

Objekt HTTP-Zahteva lahko uporabite za pridobivanje podatkov GET/POST/COOKIE in
UPLOAD:

```
>> zahteva  := HTTP-Zahteva nov.
>> search   := zahteva get: ['search']. # ?search=books
>> password := zahteva post: ['password']. # iz obrazca
>> izbrano := zahteva get-seznam: ['sel[]']. #?sel[]=1&sel[]=2
>> izbrano := zahteva post-seznam: ['sel[]'].
>> piškotek   := zahteva cookie: ['session-id'].
>> nalaganje   := zahteva upload: ['file'].
>> začasnapot := nalaganje ? 1.
>> imedatoteke := nalaganje ? 0.
```

## Maxpost/length

Privzeto največje število polj POST je 40, privzeta največja dolžina
vsebine pa je 2MB. Za drugačno nastavitev za posamezno skripto:

```
Program nastavitev: ['max-contentlength'] vrednost: 1. 
Program nastavitev: ['max-postfields'] vrednost: 1. 
```

{{note}}
Če dolžina vsebine preseže največjo vrednost, se
proces ustavi, ker ne moremo več biti prepričani,
da je vsebina varna.
{{/note}}

Omejitev maxtime določa največji čas v ms
za branje stdin/podatkov POST.

```
Program nastavitev: ['max-time'] vrednost: 5000. # 5sec
```

To velja le za V/I branje podatkov POST in preprečuje
napade, podobne slowloris. Če res želite omejiti
čas izvajanja katere koli operacije, uporabite Program alarm:.

## Podatkovna baza

Objekt Database lahko uporabite za poizvedbe v MariaDB/MySQL.
Za povezavo s podatkovno bazo naredite:

```
>> pb := Maria-DB nov gostitelj: ['localhost'],
	uporabnik: ['xo'],
	geslo: ['pass123'],
	ime-baze: ['xobase'],
	poveži-se.

```

Za vstavljanje zapisa uporabite:

```
>> iskalni-parametri := pb poizvedba: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parametri: ( Seznam nov ; ['abc'] ; 12.35 ; 6 ). # parametrizirane poizvedbe

{  iskalni-parametri izvedi. pb potrdi. }
ujemi: { :e pb razveljavi.  }, zaženi.
```

Upoštevajte, da xoscript deluje *samo* s transakcijami in nikoli samodejno ne potrjuje (autocommit).
Če samodejnega potrjevanja ni mogoče onemogočiti, boste prejeli napako povezave.
Za poizvedbe vedno uporabljajte vezavo parametrov in uporabniškega vnosa nikoli ne dodajajte neposredno
v SQL.

Vstavljeni id pridobite takole:

```
Izhod piši: ['VSTAVLJENO: '] + iskalni-parametri insert-id, nova-vrstica. # id vstavljanja
```

Za pridobivanje zapisov:

```
>> iskalni-parametri :=
pb
	poizvedba: ['SELECT * FROM book order by id desc limit 2'], 
	pridobi: { :vrsta 
		Izhod piši: vrsta id + [' '] + vrsta description + [': '] + vrsta price, nova-vrstica.
	}. # pridobivanje vrstic

```

## Seje

Za trajnost lahko podatke shranjujete v objekt seje in jih iz njega pridobivate.
Najprej ustvarite nov **Spletni-dokument**. Objekt Spletni-dokument povezuje
zahtevo, glave, HTML in sejo. Ko namreč
s svojim brskalnikom obiščete spletno mesto, vidite le HTML. Vendar je
celoten Spletni-dokument sestavljen tudi iz **glav**. Na primer,
večina odgovorov HTTP vsebuje glavo, kot je: Content-type:text/html, ki
brskalniku sporoči, da je treba podatke, ki sledijo, prikazati kot HTML
(in ne na primer prenesti kot datoteko). Seje so način za
shranjevanje uporabniških podatkov med zahtevami. Za sledenje tem podatkom moramo
nastaviti piškotek, ta piškotek pa se prav tako nastavi prek glave. Zato
se vse združi v objektu Spletni-dokument (ker je to celoten
dokument, ki vsebuje tako glave kot HTML ali druge podatke).


```
# Najprej ustvarimo nov primerek Spletni-dokument
>> splet := Spletni-dokument nov.

# Zdaj začnemo sejo; to ustvari glavo za piškotek in
# datoteko za vaše podatke, povezano s tem piškotkom
>> trenutna-seja := splet začni-sejo.

# Zdaj lahko sejo obravnavamo kot Slovar
trenutna-seja userid: 123.
```

Za uničenje seje (ob odjavi):

```
splet uniči-sejo.
```

## Glave

Spletni-dokument omogoča tudi nastavitev drugih znanih glav.
Na primer, če želite uporabnika preusmeriti na drug URL:

```
splet pojdi-na: ['/other.html'].
```

V ozadju ta ukaz ustvari tudi glavo HTTP, ki se pošlje
skupaj z drugimi podatki ali HTML in brskalniku naroči, naj se premakne
na podani ciljni naslov.

Za dodajanje lastne glave:

```
splet glava: ( 
	Glava-HTTP nov
	ključ: ['Content-Length']
	vrednost: 400
).
```

Za prikaz strani 404:

```
splet ni-najdeno: ['Opsa..'].
```


## Predloge

Privzeti sistem predlog je zelo preprost. Ni se vam treba učiti
nove sintakse predlog. Poleg tega pogon predlog zagotavlja resnično ločitev
med predstavitvijo in poslovno logiko.

Za ustvarjanje predloge iz datoteke:

```
>> tpl := splet predloga: ['templates/ux.tpl'].
```

Sistem predlog uporablja oznake. 
Obstajajo tri vrste oznak: oznake za izrez, oznake za lepljenje in
oznake rež. Osnovna zamisel je res preprosta: izrežete
območja, označena z oznakami za izrez, in jih lahko prilepite na
območja, označena z oznakami za lepljenje. V oznake rež lahko vstavite
besedila.

Recimo, da imamo naslednjo predlogo; postavimo
dragulj v škatlico za nakit in dodajmo ceno.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

To lahko storite takole:

```
>> gem := tpl izreži: ['gem'], kopiraj.
gem price: 99.
tpl prilepi: gem na: ['jewels'].
splet izpiši: tpl pospravi.
```

Zadnja vrstica preprosto pošlje predlogo kot besedilo odjemalcu
skupaj z zahtevanimi glavami HTTP.

Rezultat:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

Za varno streženje datotek, ki so jih naložili uporabniki, se lahko zanesete na passthru:

```
>> naložena := ['smile.gif'].
Server posreduj: naložena predpona: ['/uploads/images/'].
Program konec.
```

To bo vsebino, ki so jo naložili uporabniki, postreglo z ustreznim
tipom mime. Podprti so le dovoljeni tipi mime:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF in SVG.
Datoteke SVG, ZIP in GZIP se pošljejo kot prenos, ker lahko SVG
vsebuje skripte, ki bi se sicer izvajale v vaši domeni.
Ta metoda preprečuje napade TOCTOU, prehajanje poti (path traversal), 
izvajanje zlonamerne kode (vrivanje), napade s simbolnimi povezavami,
napade DDoS (omejitev datoteke = 50MB), napade z vohanjem in 
različne druge varnostne težave.


## JSON

Za kodiranje objekta v JSON:

```
>> json := ( JSON jsonify: ( 
	Slovar nov postavi: ( 
		Seznam nov ; 1 ; 2 ; 3
	) na: ['abc']
)).
```

Za dekodiranje JSON v objekt xoscript:

```
>> slv := ((JSON objekt: json) abc ? 1).
```

JSON z več kot 500 ravnmi gnezdenja je zavrnjen kot neveljaven.

Za neposreden izpis Slovarja kot json s pravilnimi glavami:

```
splet json: slv.
```


## Regularni izrazi

Regularne izraze lahko uporabljate tako, da ustvarite vzorec.
Na primer, za ujemanje atributov href in target hiperpovezav:

```
Vzorec nov: ['href="([^"]+)" target="([^"]+)"'].
```

Zdaj vzorec uporabite na besedilu takole:

```
regIzraz ujemanje: zadeva izvedi: { :m :x .... }
```

Celoten primer:

```
>> zadeva := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> regIzraz := Vzorec nov: ['href="([^"]+)" target="([^"]+)"'].
>> rezultat  := regIzraz ujemanje: zadeva izvedi: { :m :x
	Izhod piši: m, nova-vrstica.
	Izhod piši: x, nova-vrstica.
	<- ['XXX'].
}.
Izhod piši: rezultat, nova-vrstica.
```

## Omrežje

Za izvedbo spletne zahteve uporabite objekt Omrežje.
Objekt Omrežje vedno pošlje zahtevo POST, razen če kot
podatke pošljete Nič; takrat pošlje zahtevo GET.


```
Omrežje 
post: Nič 
na: ['https://redbeanphp.com'].
```

## Šifriranje

Strežniški vtičnik vključuje šifriranje na osnovi XChaCha20 in Argon2.

Primer:

```
>> šifrirano := Sef šifriraj: ['hello'] ključ: ['world'].
>> dešifrirano := Sef šifriraj: šifrirano ključ: ['world'].
```

## Žetoni

Za ustvarjanje kriptografsko varnega žetona določene dolžine:

```
>> mojžeton := Sef žeton: 40.
```

To ustvari žeton s 40 znaki.

## Oblikovanje

Objekt Format omogoča oblikovanje podatkov, na primer dopolnjevanje ali
dodajanje ničel. Uporablja sintakso printf.

```
>> fmt := Format nov: ['%06.0f'].
fmt uporabi: 56. # da 000056
```

Format lahko vsebuje eno pretvorbo, ki se mora ujemati z vrednostjo,
sicer prejmete napako:

- `uporabi:` z besedilom: `%s`
- `uporabi:` s številom: `%f`, `%e`, `%g` ali `%a`
- `uporabi-celo:` s številom: `%d`, `%i`, `%o`, `%u`, `%x` ali `%c`

Vrednosti iz zahteve so besedila. Če želite eno oblikovati kot število,
ga najprej pretvorite:

```
fmt uporabi: (zahteva get: ['amount']) število.
```

## Kodirniki

Na voljo je več kodirnikov in dekodirnikov.
Kodirnik url pripravi url za uporabo v HTML kot povezavo:

```
Server url-kodiraj: ['https://example.com?a=6&b=1 2'].
```

Za varno vstavljanje uporabniškega vnosa v HTML brez nevarnosti vrivanja
XSS vedno uporabite:

```
Server html-kodiraj: ['<harmless>'].
```

Upoštevajte, da pogon predlog vedno izvede kodiranje html,
ko pišete v oznako reže. Če torej uporabljate sistem predlog,
tega ne potrebujete.

## Pošiljanje pošte

Za pošiljanje pošte uporabite knjižnico mailtools.xo.

Primer:

```
Server inicializiraj.
Program uporabljaj: ['mailtools.xo'].

>> e-pošta := HTML-Email nov.
>> img := e-pošta priloži: ( Datoteka nov: ['myimage.png'] ).

e-pošta
pošiljatelj: ['xo@xoscript.com'] ime: ['xo'],
komu: ( Seznam nov ; ['xo2@xoscipt.com'] ),
zadeva: ['xoxo'],
telo: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), pošlji.

```



## Povezovanje

S sporočilom poveži: lahko svojemu programu z uporabo libffi
povežete zunanjo knjižnico. Za podrobnosti glejte poglavje o ffi.


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

FFI je zagotovljen glede na platformo/vtičnik, ker je
vezan na spodaj ležečo sistemsko arhitekturo, česar
jedro ne bi smelo početi.
Strežniški vtičnik ponuja skladno implementacijo ffi/blobov.
Jedro se privzeto povezuje s ciljno platformo
prek stdin/stdout, omejenih storitev za datotečni V/I in lupine (Program sistem:).
Dodatno integracijo zagotavljajo ffi/blobi prek vtičnikov, usmerjenih
v aplikacije, kot je strežniški vtičnik.

FFI pomeni Foreign Function Interface (vmesnik za tuje funkcije). Omogoča uporabo funkcionalnosti, ki so jo drugi napisali v
drugih programskih jezikih in je na voljo prek datotek DLL, SO ali Dylib. To so lahko
najrazličnejše funkcije, in na ta način je na voljo ogromno funkcionalnosti.
Začnimo s primerom:

```
Server poveži: (
 Seznam nov ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Seznam nov ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s sprosti.
```

Rezultat te kode je, da boste v ukazni vrstici videli naslednje:
FFI has 3 letters.
Zdaj si verjetno mislite: "To je veliko kode za nekaj tako preprostega."
Mar ne bi tega lahko rešili kar z ukazom Gui show? Odgovor je odločen da!
Vendar je to mišljeno kot ponazoritveni primer.
FFI se običajno uporablja za zahtevnejše naloge, vendar te niso dobri
primeri, zato sem izbral nekaj trivialnega.

Argumenti metode poveži:

- Argument #1: Datoteka DLL ali SO, ki jo želite uporabiti.
- Argument #2: Funkcija v tej datoteki, ki jo želite povezati.
- Argument #3: Seznam z imeni podatkovnih tipov argumentov funkcije.
- Argument #4: Ime tipa vrnjene vrednosti funkcije.
- Argument #5: Ime objekta, s katerim želite povezati to funkcijo (če ne obstaja, bo ustvarjen
samodejno).
- Argument #6: Sporočilo, s katerim naj bo ta funkcija povezana.

V zgornjem primeru želimo povezati funkcijo printf iz libc.so. Imena podatkovnih
tipov najdete v dokumentaciji programske opreme, s katero se povezujete. Razpoložljivi tipi so:
void, pointer, float, double, int, uint, char, uchar, intX in uintX,
pri čemer je X lahko 8, 16, 32 ali 64.

Ti tipi se nanašajo na število bajtov, potrebnih za shranjevanje podatkov. Za printf se povezujemo z
novim objektom Printf in sporočilom template:number:. Zunanjo
funkcijo pred uporabo prevedete v narečje XOScript. Sporočilo template:number: kot prvi parameter
pričakuje medpomnilnik z besedilom predloge. Ta medpomnilnik ustvarimo z objektom Blob, ki
omogoča ročno dodeljevanje pomnilnika. Za poznejše sproščanje tega pomnilnika
s sporočilom sprosti ste odgovorni sami.

Pomnilniški blob lahko napolnite na različne načine. V našem primeru ga napolnimo z besedilom, zato uporabimo
sporočilo utf8: (UTF-8 je kodiranje za pretvorbo besedila v bajte). Blob lahko napolnite tudi z
bytes:, kateremu podate seznam vrednosti bajtov. Za branje vsebine bloba uporabite od:dolžina:.
Bajte dobite nazaj kot seznam. Z Blobom lahko celo ustvarite C-strukturo s
sporočilom struct:, kateremu podate zaporedje tipov C. To je lahko potrebno pri klicanju funkcije C
v zunanji programski knjižnici, ki pričakuje kazalec na strukturo.

{warning}
Blobe morate sprostiti sami.
Smetar (garbage collector) blobov ne počisti.
{/warning}

Ker je blobe mogoče izmenjevati z zunanjimi funkcijami iz knjižnic,
jih smetar ne more samodejno počistiti (morda jih še uporabljajo
zunanje funkcije ali pa jih te zunanje funkcije želijo sprostiti
same). Zato morate blobe po potrebi sprostiti sami.

Za sprostitev bloba uporabite:

```
mojblob sprosti.
```

Za sprostitev strukture uporabite:

```
mojstruct sprosti-struct sprosti.
```

Za strukturo morate torej poslati dve sporočili: sprosti-struct in sprosti, da
sprostite pomnilniški blok.

@api_Blob_fficonnect
