# Basiese beginsels

{{messages}}


Welkom by XOScript
Die XOScript-projek beoog om 'n skriptaal te skep wat eenvoudig en ouditeerbaar is.
Eenvoudig beteken nie noodwendig maklik nie.
'n Bekende programmeertaal kan makliker wees om te gebruik as XOScript.
Hier beteken eenvoud iets anders:
om 'n volledige geestesbeeld van die taal en sy gedrag te kan vorm.

XOScript is ontwerp om in jou kop te pas.
Die grammatika en die aantal konsepte is doelbewus klein.
Daar is geen klasse nie; objekte kan direk uitgebrei word.
Objekte word per verwysing deurgegee, kopiëring is eksplisiet,
en funksies het 'n enkele uitgangspunt.

Sommige van hierdie keuses verskil aansienlik van hoofstroomtale.
XOScript het byvoorbeeld geen tipestelsel nie en gebruik dinamiese omvang.
Boodskappe wat nie hanteer kan word nie, word geïgnoreer eerder as om 'n uitsondering te veroorsaak.
Hierdie keuses het gevolge en is nie bedoel om foute uit te skakel nie.
Hulle is bedoel om die onderliggende model van die taal klein en konsekwent te hou.

XOScript kan ook gelokaliseer word, wat dit moontlik maak om besigheidsreëls
in 'n natuurlike taal uit te druk en dit moontlik met nie-tegniese belanghebbendes te deel.

Ouditeerbaarheid beteken dat dieselfde filosofie op die implementering toegepas word.
Die looptydomgewing is in C geskryf, met 'n klein, met die hand geskrewe lekser, ontleder en boomdeurloper.
Die standaardbiblioteek en die looptydomgewing weerspieël grootliks die struktuur van die taal,
wat die verband tussen XOScript-kode en die implementering daarvan relatief direk maak.

Toetse is ook nou met die dokumentasie verbind.
Elke metode behoort 'n gepaardgaande toets te hê wat in die handleiding opgeneem kan word,
wat help om die dokumentasie in pas met die implementering te hou.

XOScript is nie bedoel om met hoofstroomtale te kompeteer op
funksies of bekendheid nie. Dit verken 'n ander doel:
'n programmeeromgewing wat 'n ontwikkelaar as 'n geheel kan verstaan.

Die hoop is dat 'n klein taal en 'n klein
implementering dit prakties maak om sagteware te verstaan
van greep tot objek, van sintaksis tot looptyd, en om kode met
selfvertroue te skryf omdat jy verstaan wat in
die skrip gebeur én wat agter die skerms gebeur.

Die argitektuur van 'n xoscript-bedieneropstelling
is eenvoudig, maar tog buigsaam.

{{architecture.png}}

Om xoscript as bedienertaal te gebruik, moet jy die
bedienerinprop in 'n gids genaamd /mods/server installeer. 

Dit is omdat ons die kerntaal graag
van bedienerspesifieke funksionaliteit skei,
anders as byvoorbeeld PHP of Python. Andersins sou ons die
hele kombuis sonder enige doel aan almal moes saamstuur, wat net dwaas is.
Jy kan ook ander modules installeer as jy wil. Die stelsel is baie
buigsaam.

Sommige funksies word ook beter in die skriptaal self
geïmplementeer, soos sjablone en sessiehantering, daarom
lewer ons boonop die biblioteke template.xo en webtools.xo vir jou gerief.
Die rede vir dit alles is dat ons nie weet hoe jy
xoscript wil gebruik nie. Jy kan dit as 'n bedienerkant-skriptaal gebruik,
maar ook vir grafiese koppelvlakke, ingebedde toestelle of bloot bondelverwerking.
Selfs as jy dit as 'n bedienerkant-skriptaal gebruik (wat
tans een van die vernaamste gebruike is), wil jy dalk steeds
'n ander sjabloonenjin of 'n ander sessiehanteerder gebruik.
Wie is ons om te besluit dat jy ons s'n moet gebruik?

Een van die voordele van ons eie sjabloonenjin is egter dat
jy geen bykomende sintaksis hoef te leer om sjablone te skep nie.
Die standaard sjabloonenjin wat saam met xoscript kom, skei
aanbieding en logika 100%. In plaas van spesiale
sjabloonsintaksis gebruik dit bloot 'n baie buigsame stelsel van gleufmerkers.
Sien die hoofstuk Server vir meer inligting.

Let daarop dat, as jy nie die standaard sjabloonenjin of
die standaard webtools wil gebruik nie, jy vanselfsprekend
jou eie moet voorsien.

As jy jou webbediener in 'n chroot, jail of 'n ander soort sandput laat loop,
moet jy ook die afhanklikhede van xo in daardie omgewing installeer; jy kan
sien watter biblioteke jy nodig het deur ldd te gebruik (sien die manpage van Linux of BSD).
As jy shell-opdragte in jou xo-skripte wil gebruik, kopieer ook 'n shell
(soos bash of ksh) na hierdie omgewing.

Ons wil ook daarop wys dat ons terugwaartse versoenbaarheid baie ernstig opneem.
Daar is selfs 'n spesiale funksie vir terugwaartse versoenbaarheid genaamd
'version'. In die algemeen streef ons daarna dat jou kode vir altyd loop. Jy sal dus
nooit jou kode hoef by te werk om versoenbaar te bly met nuwer weergawes
van xoscript nie. Ons doel is: skryf een keer, loop vir altyd.

Die res van hierdie handleiding word daaraan gewy om die programmeertaal
xoscript in besonderhede te verduidelik. Bedienerskripte word bespreek in die hoofstuk
genaamd Server. As jy 'n ervare sagteware-ontwikkelaar is, wil jy dalk
'n paar hoofstukke oorslaan, omdat sommige daarvan 'n bietjie te gedetailleerd is of
baie ooreenstem met algemene programmeerpraktyke. Vir dié van julle
wat reeds ervaring met verskeie ander programmeertale het,
is dit dus beter om hierdie handleiding as 'n naslaangids te gebruik.

## Opstelling op Linux

Laai apache2 en mariadb af:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Laai xoscript af.
Vervang X met die korrekte weergawenommer!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Kopieer die lêers na die webwortel en /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Wysig jou apache2-konfigurasie:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Vervang Virtualhost met:

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

Skep 'n toetsbladsy:

```
sudo nano /var/www/html/test.xo
```

en skryf 'n klein toetsprogram:

```
#!/bin/xo
Server inisialiseer.
Program gebruik: ['webtools.xo'].
>> web := Webdokument nuut.
web uitvoer: ['Hello World'].
```

Laat apache2 toe om jou program via CGI uit te voer:

```
sudo chmod uog+x /var/www/html/test.xo
```

Herbegin apache2:

```
sudo systemctl restart apache2
```

Gaan na jou toetsbladsy in die blaaier:

```
http://localhost/test.xo
```

Jy behoort te sien:

```
Hello World
```


## Opstelling op OpenBSD

Wysig /etc/httpd.conf en voeg by:


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

As jy SSL wil gebruik:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Om die sleuteluitruiling teen kwantumrekenaars te beskerm,
kies die mlkem-sifer:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Voeg die xo-uitvoerlêer en mods, asook alle afhanklikhede, by die
chroot (vind dit uit met ldd).

## Voorbeelde uitvoer


Om een van die voorbeeldprogramme in die pakket uit te voer:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Byvoorbeeld, om die FizzBuzz-voorbeeld op Linux uit te voer:

```
./example.sh fizzbuzz Linux
```

Om dieselfde voorbeeld op OpenBSD uit te voer:

```
./example.sh fizzbuzz OBSD
```

Om die voorbeeld met 'n skoon bou uit te voer:

```
./example.sh fizzbuzz OBSD clean
```

## Eenheidstoetse

Om die eenheidstoetse uit te voer:

```
./runtests.sh
```

Om die eenheidstoetse sonder bou uit te voer (net toets):

```
./runtests.sh nobuild
```

## Bou

Om vanaf die bronkode op Linux te bou:

```
make clean
ISO="en" make
```

Op OpenBSD:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

Om die bedienerinprop op Linux te bou:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

Om die bedienerinprop op OpenBSD te bou:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Hallo wêreld

Nadat dit na jou rekenaar oorgedra is, kan jy die lêer uitpak
en xo begin met die volgende opdrag:

```
xo
```

Om 'n XOScript uit te voer, stoor die program as 'n lêer met die agtervoegsel
-xo (opsioneel). Voeg boonop die lêernaam van jou program
na die XOScript-opdrag in:

```
xo myprogram.xo
```

Wanneer jy 'n XOScript-opdrag uitvoer met jou programlêer as
parameter, sal xo jou programlêer lees en uitvoer.

{{note}}
Jy kan jou program ook begin deur dit na die xo-ikoon te sleep.
{{/note}}

{{warning}}
Op sommige stelsels moet jy xo vooraf toestemming gee om dinamiese
biblioteke te laai.
{{/warning}}

Tradisie bepaal dat die eerste program in enige nuwe programmeertaal
'n soort groet aan die wêreld moet wees. In XOScript lyk so 'n
**Hello world**-program soos volg:

@test598

Wanneer hierdie teks in 'n lêer gestoor word, bv. hello.xo, kan dit soos volg
uitgevoer word: .

xo hello.xo

Hello world


Jy kan die uitvoer van die program in die swart venster hierbo sien.
Deur hierdie hele handleiding sal dieselfde voorstelling gebruik word om
die uitvoer te wys.

{{note}}
Uitvoer word met 'n hoofletter U geskryf.
In die algemeen begin objekte met 'n hoofletter,
tensy dit as 'n instansie optree (geen eie metodes
het nie, net data). Dit weerspieël die konvensies van klas teenoor instansie
in ander programmeertale.
{{/note}}


## Sintaksis 

XOScript is 'n *suiwer* *objekgeoriënteerde* programmeertaal. Dit beteken
dat xoscript alles as 'n objek beskou; daarom is daar
geen ander *datatipes* nie. Daar is in wese drie basiese roetine-aksies
in 'n program wat in XOScript geskryf is: *toeken*, *boodskappe stuur*
en *antwoord*. Die uitruil van boodskappe tussen objekte is die kern van
'n XOScript-program. Die drie afsonderlike roetine-aksies word hieronder
geïllustreer:


Aksie                | Voorbeeld
-------------------- | --------
toeken               |  \>\> x := 1. 
unêre boodskappe     | x ewe?.
binêre boodskap      | 1 + 2.
sleutelwoordboodskap | x vanaf: 0 lengte: 10.
antwoord             | <- answer.  


Hierdie hoofstuk gee jou 'n algemene indruk van die taal XOScript
en beskryf die basiese beginsels daarvan. XOScript is 'n klein taal en
gegrond op drie aksies (sien illustrasie) wat neerkom op
ongeveer ses grammatikareëls. Dit is al wat nodig is om die
taal te bemeester.

Moenie bekommer as dinge nie dadelik vir jou duidelik is nie: alle
boustene word in die volgende hoofstuk (3) ondersoek en die basiese reëls sal
herhaal word. Hierdie hoofstuk dien egter hoofsaaklik as 'n algemene
inleiding tot die taal. Die basiese beginsels word kortliks
verduidelik en met verskeie toepaslike voorbeelde geïllustreer. Ontbrekende
besonderhede word op 'n later stadium uiteengesit.

Kommentaar in XOScript begin met 'n \#-simbool. Die volgende reël
word dus geïgnoreer:

```
# this is just a comment
```

## Veranderlikes

Om 'n veranderlike
toe te ken, gebruik jy die simbool vir veranderlike-verklaring: >>. Die naam van 'n
veranderlike mag alle tekens bevat behalwe: <-, :=, witspasies,
punte, kommas, dubbelpunte, aanhalingstekens [' '] en hakies ().
Verder kan 'n veranderlike nie uit meer as een reël bestaan nie. Let asseblief
daarop dat 'n veranderlike nie met 'n syfer of 'n minusteken kan begin nie.

Dit is voorbeelde van geldige veranderlikes:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dollar'].
>> +plus := Ja.
>> user-password := ['Pssst!'].
```

Ongeldige veranderlikes is byvoorbeeld:


```
>> -123 := ['negative number'].
>> password of user := ['Classified'].
>> password.of:user := ['Classified'].
>> ,x := 10.
```

{{note}}
Jy hoef geen enkele teken te ontsnap nie
(insluitend aanhalingstekens, dubbele aanhalingstekens,
teksgrense) in
'n teksletterlike, solank dit nie
dubbelsinnigheid vir die lekser veroorsaak nie.
{{/note}}

Nadat 'n veranderlike verklaar is, kan dit vrylik gebruik word. Dit beteken
dat dit slegs nodig is om die verklaringsimbool die eerste keer
te gebruik wanneer jy die veranderlike gebruik (die verklaring).

Om meer spesifiek te wees: jy kan nie sommer net begin om 'n waarde aan
jou veranderlike toe te ken nie *(x := 2)*, aangesien jy die veranderlike eers moet verklaar *(\>\>
x := 2)*. Sodra dit egter verklaar is, mag jy die waarde daarvan verander
sonder om die verklaringsimbool te gebruik *(\>\> x := 2. x := 3.)*.

Let daarop dat dit verpligtend is om 'n waarde aan 'n veranderlike toe te ken wanneer
dit verklaar word. Anders as in ander programmeertale mag jy
nie 'n veranderlike sonder waarde verklaar nie. Dit is noodsaaklik om
elke veranderlike uitdruklik aan 'n beginwaarde te koppel. Jy is nietemin vry om
die veranderlike met die **Niks**-objek te inisialiseer. In hierdie geval kan die veranderlike
as leeg beskou word *(\>\> x := Niks.)*. Kortom, om 'n
veranderlike sonder 'n beginwaarde te verklaar, is nie toegelaat nie. Dus is

```
>> x.
```

ongeldig en sal dit 'n foutboodskap gee.

{{note}}
xoscript gebruik dinamiese omvang vir veranderlikes;
raadpleeg die hoofstuk Funksies vir besonderhede.
{{/note}}


## Letterlikes

XOScript beskou alles as 'n objek, d.w.s. alle getalle, teks
en kodefragmente. Getalle, soos 1, 2, 100, -999 en 1,234, is
Getal-objekte. Alle teks tussen enkele aanhalingstekens is Teks-objekte.
Alle kodefragmente wat tussen krulhakies {...} gegroepeer is, is
Funksie-objekte.

Letterlike      | Wortelobjek  | Voorbeeld
--------------- | ------------ | ----------
getalle         | Getal        | 1,2,3... 
teks            | Teks         | \['hello'\]
funksie         | Funksie      | { 1 + 2. }.
                
     
Objekte soos getalle en teks het altyd hul oorsprong in 'n wortelobjek.
Alle getalle stam byvoorbeeld af van die objek **Getal**. Alle
teks stam af van **Teks** en alle kodefragmente van **Funksie**. Op
hul beurt stam al hierdie objekte af van **Objek**, wat in werklikheid die
wortelobjek van alle objekte is.


## Boodskappe

Programmering in XOScript beteken basies
om boodskappe aan objekte te stuur. Die algemene notasie om 'n boodskap aan
'n objek te stuur, is soos volg:

```
<object> <message>
```

Om byvoorbeeld uit te vind of die getal **2** 'n ewe getal is, word die
boodskap **ewe?** aan objek **2** gestuur:

```
2 ewe?
```

Die antwoord sal **Ja** wees (weer eens 'n objek). Onbekende boodskappe word
gewoonlik deur objekte geïgnoreer; daar sal dus geen fout voorkom nie. Sommige objekte (bv.
getalle of teks) reageer op 'n voorafbepaalde manier op 'n onbekende boodskap
(later meer hieroor).

'n Objek kan drie soorte boodskappe ontvang. 

Tipe            | Aantal argumente
--------------- | -------------------
Unêr            | 0      
Binêr           | 1     
Sleutelwoord    | 1+    


Eerstens is daar **unêre
boodskappe**, sien die voorbeeld hierbo, wat geen argumente het nie. Tweedens
is daar **sleutelwoordboodskappe**, wat een of meer argumente het,
byvoorbeeld:

```
>> x := Getal tussen: 1 en: 10.
```

In hierdie geval word die boodskap **tussen:en:** aan **Getal** gestuur, wat
die wortelobjek van alle getalle is. Die resultaat sal 'n lukrake getal
tussen 1 en 10 wees. Laastens is daar **binêre boodskappe**, wat
slegs een teken en een argument het:

```
2 + 3
```

Dit lyk soos 'n wiskundige som, maar dit is eintlik net nog 'n boodskap. Die
boodskap **+** word aan **2** gestuur, met argument **3**, wat die
antwoord **5** sal teruggee. Binêre boodskappe mag sonder 'n dubbelpunt geskryf word.

Binêre boodskappe kan aaneengeskakel word:

```
>> x := 3 + 2 - 1.
```

In hierdie fragment word **+ 2** eers aan die **Getal**-objek **3** gestuur, wat
die Getal-objek **5** oplewer, waarna **-1** aan hierdie
getal gestuur word. Oplettende lesers merk tereg die teenstrydigheid op wat
hierdie protokol toon ten opsigte van die gebruiklike wiskundige volgorde van
bewerkings. XOScript ignoreer die wiskundige volgorde ten gunste van
konsekwentheid in sy boodskapstelsel. Gevolglik is die som:

```
2 + 3 * 5 = 25
```

nie 17 nie.

Dit is doelbewus so ontwerp. Hakies kan gebruik word om die volgorde te verander:

```
2 + (3 * 5) = 17
```

Die meeste objekte gee hulself as resultaat terug in reaksie op 'n sekere
boodskap. Dit is nuttig, aangesien dit verdere gesprek met hierdie
objek aanmoedig deur 'n opvolgboodskap daaraan te stuur:

```
Uitvoer skryf:
[' hello '] snoei hoofletters.
```

```
HELLO
```

Hier word twee boodskappe aan die **Teks**-objek gestuur: **snoei**, gevolg
deur **hoofletters**.

In die volgende fragment is die gebruik van 'n komma nodig om aan te dui
dat 'n nuwe boodskap volg. Indien nie, sal XOScript deurmekaar raak.

```
Uitvoer skryf: ['Hello!'], nuwe-reël.
```

Eers word die boodskap **skryf:** aan die potloodsimbool gestuur, gevolg deur
**nuwe-reël**. Sonder die komma sou XOScript dink dat jy
**nuwe-reël** aan die **teks** **Hello!** wil stuur, 'n nuttelose oefening.

Die verwerkingsvolgorde van boodskappe is soos volg: van links na regs;
begin met boodskappe tussen hakies, gevolg deur unêre boodskappe. Daarna
binêre boodskappe en eindig dan met sleutelwoordboodskappe. Sien die voorbeeld
hieronder:

```
Uitvoer skryf: 0.5 afgerond + (2 - 1), nuwe-reël.
```

XOScript lees altyd van links na regs: eers word die boodskap **skryf:**
aan Uitvoer gestuur, gevolg deur die boodskap **nuwe-reël**. Binne die
argument self lees XOScript van links na regs, dus eers **0.5 afgerond**
en dan **+**.

{{note}}
Die boodskap nuwe-reël voeg 'n nuwereël-teken by die teks.
Die Engelse naam van hierdie boodskap, stop, is geïnspireer deur telegraafstelsels.
Boodskappe in telegraafstelsels 
het dikwels die woord STOP gebruik om die einde van 'n sin aan te dui
(aangesien leestekens onbetroubaar of duur was).
{{/note}}

Verder het **afgerond** voorrang bo **+**, omdat dit 'n
**unêre boodskap** is. Weens die hakies word **2 - 1** eerste
bereken, waarna **1** by die resultaat van **0.5 afgerond** (1) getel word.

Die hele proses gee die resultaat **2**, wat ook die geskrewe
antwoord is. Ná die komma volg die boodskap nuwe-reël, wat die wyser
na 'n nuwe reël skuif. Die beste manier om die volgorde
van XOScript-programme ten volle te begryp, is natuurlik deur te oefen.

Dit is die moeite werd om op te let dat in XOScript, anders as in baie ander
programmeertale, witspasies 'n fundamentele deel van die sintaksis is. Veral
by binêre boodskappe kan witspasies tot
verwarring lei. Gebruik altyd 'n witspasie ná 'n binêre boodskap. Jy kan nie
'n getal direk aan die boodskap vasheg nie, byvoorbeeld: 

```
3 + 2
```

verskil van 

```
3 +2
```

Die eerste voorbeeld (**3 + 2**) stuur die
boodskap **+** aan die getal **3**, met die getal **2** as argument. Die
resultaat sal in hierdie geval **5** wees. In die tweede voorbeeld (**3 +2**)
word die unêre boodskap **+2** aan die getal **3** gestuur. Afhangende van die
konteks kan dit 'n heel ander resultaat oplewer.

## Nie-bestaande metodes

Om 'n boodskap aan 'n objek te stuur, roep die funksie op wat
onder daardie boodskapnaam aan hierdie objek gekoppel is. As jy 'n boodskap stuur
wat nie verstaan word nie, sal die ontvangende objek jou boodskap ignoreer
en in plaas daarvan 'n verwysing na homself teruggee vir verdere kommunikasie.
Dit word verdraagsame boodskapoordrag genoem.

Voorbeeld:

```
Uitvoer skryf: Objek blah, nuwe-reël.
```

Dit sal nie 'n fout gee nie. Dit sal bloot die teks **Objek** druk.


## Programvloei

In XOScript is daar geen behoefte aan aparte grammatikareëls vir *lusse* en
*as-stellings* nie. 'n As-stelling is net 'n eenvoudige **ja:**- of **nee:**-boodskap
aan óf 'n **Ja**-objek óf 'n **Nee**-objek:

```
2 ewe? ja: {
	Uitvoer skryf: ['Two is an even number'], nuwe-reël.
}.
```
In die vorige voorbeeld word die boodskap **ja:** aan **Ja** gestuur (die
antwoord op die vraag: is 2 'n ewe getal?). As argument word 'n bykomende
kodefragment saamgestuur: 'n **Funksie**-objek. Hierdie funksie skryf op
die skerm dat 2 inderdaad 'n ewe getal is.

Daar is ook geen behoefte aan aparte skryfreëls vir 'n *lus* nie. Om
'n kodefragment drie keer uit te voer, stuur eenvoudig **\*** met argument
**3** aan daardie **Funksie**:

@test5

In hierdie kodefragment is **i** die indeks. Die eerste keer dat die Funksie
uitgevoer word, is **i** gelyk aan 0, die volgende keer is **i** = 1 en
so meer.

Kom ons kyk na nog 'n voorbeeld. Wanneer 'n omskakelingstabel
van *kJ* (kilojoule) na *kcal* (kilokalorie) in stappe van 100 gedruk moet word,
sien hieronder vir die korrekte notasie:

@test599

Hier word die nommer van die huidige reël aan die parameter
**:line** oorgedra. Aan die begin van 'n funksie word die funksieparameters
gedefinieer. Ongebruikte parameters bly leeg (**Niks**). Parameters word
altyd aan die begin van die funksie geplaas, direk ná die openende
krulhakie, en word deur 'n dubbelpunt voorafgegaan.

Die boodskap **terwyl:** is 'n kombinasie van 'n *lus* en 'n *voorwaarde*.
Twee funksies kan met die boodskap **terwyl:** gekoppel word. Die ontvangende funksie
sal aanhou loop totdat die funksie ná die dubbelpunt 'n negatiewe
resultaat gee. Voorbeeld:

@test600

In die kodefragment hierbo word **1** by **x** getel solank
**x** kleiner as **5** is. Wanneer dit nie meer die geval is nie, sal die tweede
funksie met **Nee** antwoord, gevolglik eindig die uitvoering van die
eerste funksie. Let daarop dat **x** buite die
funksie gedefinieer is en 'n globale veranderlike is. Om meer oor omvangreëls te leer,
raadpleeg die hoofstuk oor Funksies.

## Teksinterpolasie

Die *kJ/kcal*-lys kan meer
aanbiedbaar gemaak word. Die lys sou verkieslik soos volg lyk:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Wanneer jy die verlangde uitvoer in 'n sjabloon omskakel, kan die notasie
daarvan wees:

```
number1 kJ ➞ number2 kcal
```

Dit beteken dat **number1** vir die kJ-waarde staan en **number2** vir die
kcal-waarde. Dit is hoe teksinterpolasie in XOScript werk. Daar
is geen aparte grammatikareëls hiervoor in XOScript nodig nie. Stuur eenvoudig
die woord wat vervang moet word aan die teks, met die vervangende teks
as argument:

```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

Die resultaat:

```
100 kj ➞ 23.9 kcal
```

Hierdie vervangingsreël werk vir elke ongedefinieerde boodskap wat
deur 'n **teks**-objek ontvang word. Elke boodskap wat nie deur die
**teks**-objek herken word nie, word soos volg geïnterpreteer: *vervang die boodskapteks
met die teks in die boodskapargument.* Jy kan die
program soos volg aanpas:


@test601


Om verwarring te vermy oor watter boodskap wel of nie as
plaasvervanger gebruik kan word, is dit die beste om 'n sjabloonmerker soos &lt; &gt;
in te voer vir teksgedeeltes in die sjabloon wat
vervang moet word.

## Terugkeerwaardes

Om 'n boodskap te beantwoord, word die terugkeerpyl
(*<-*) gebruik. Die volgende voorbeeld illustreer hoe om 'n taak te skep
om 'n persentasie te bereken:

@test602

Nadat die taak gedefinieer en aan die veranderlike **percentage** toegeken is,
word die boodskap **pas-toe:en:** met die argumente **100** en **7** gestuur.

Dit voer die taak uit toegepas op **100** en **7**, d.w.s. 7% van 100.
Met behulp van die terugkeerpyl word die antwoord van die taak terug
na die hoofprogram gestuur.

## Uitbreiding

Hoewel hierdie kode geldig is, het dit 'n nadeel,
want die volgorde van die argumente moet onthou word. Waarom dit dus nie
so skryf nie: *7 percent of: 100 *? Dit sou baie meer
*natuurlik* lyk. Om dit moontlik te maak, moet ons die ouerobjek van
**7** aanpas, wat die **Getal**-objek is, sodat dit die
boodskap **percent of:** verstaan. Dit kan bereik word deur **by:doen:** aan
die Getal-objek te stuur, soos volg:

@test603

Aangesien die persentasie in hierdie geval die getal self is, verwys ons na self,
die sleutelwoord *self*. Kortom, die simbool self beteken: *stuur hierdie
boodskap aan myself*. 

# Objekte

{{messages}}

Behalwe om bestaande objekte aan te pas en uit te brei, kan jy ook
self nuwe objekte skep deur eenvoudig die boodskap **nuut** te stuur. Gestel jy
wil 'n faktuurobjek skep wat 'n nommervolgorde afdwing;
in daardie geval sal jy eers 'n faktuurobjek nodig hê.

Aangesien elke objek van 'n ander objek afstam, wat op sy beurt
uiteindelik ontstaan uit die wortelobjek van alle objekte, genaamd Objek,
moet 'n keuse gemaak word oor op watter van daardie ander objekte jou
nuwe objek gegrond sal word. Jou nuwe objek erf al die eienskappe van
die objek waarop dit gegrond is, dus die objek waaraan die boodskap **nuut**
oorspronklik gestuur is.

In hierdie voorbeeld word 'n taamlik neutrale objek verkies, een sonder te
veel geërfde eienskappe. Dit maak die keuse maklik, want in daardie
geval kan die nuwe objek op die wortelobjek self gegrond word, naamlik
**Objek**. Die notasie van die beoogde faktuurstelsel lyk dan soos
volg:

@test604

Die huidige faktuurnommer word in die objek gestoor; daarom staan
die sleutelwoord **eie** voor dit. Dit word 'n *eienskap* genoem;
meer besonderhede volg later.

Sommige besighede verkies om die jaar in die faktuurnommers
op te neem. In hierdie geval kan jy 'n nuwe faktuurobjek skep wat op 'n
vorige faktuurobjek gegrond is, maar wat die gebruiker die moontlikheid bied om
'n bepaalde jaar in te voer:

@test605

Dit is nie nodig om die implementering vir die boodskap **getal**
weer te skryf nie, aangesien dit van die voorheen geskrewe **faktuurobjek**
geërf word; gevolglik kan ou kode hergebruik word. XOScript het geen konsepte
soos klasse en ander verwante konsepte nie. Dit beteken dat objekte
slegs van ander objekte kan erf, ook bekend as *prototipiese
oorerwing*.

Kom ons keer nou terug na eienskappe. Objekeienskappe kan slegs
van *binne die objekhiërargie* bereik word, dus kan hierdie eienskappe
nie deur ander objekte waargeneem word nie.

Anders as in ander programmeertale is alle eienskappe van objekte
uitsluitlik sigbaar vir die objek wat die eienskap geskep het en vir
afgeleide objekte. 

'n Algemeen gebruikte tegniek is om 'n objek as 'n soort *bloudruk* te gebruik,
wat byvoorbeeld die geval is met die fakture wat vroeër bespreek is.
Nog 'n goeie voorbeeld is die **Point**. Gestel jy skep 'n
rekenaarprogram wat berekeninge maak met punte op 'n kaart. Jy
kan die objek **Point** ontwikkel wat die eienskappe van 'n
x-koördinaat en 'n y-koördinaat bevat, wat deur middel van boodskappe aan die
buitewêreld beskikbaar gestel word:

@test606

Die boodskap **=** vergelyk die twee punte met behulp van die boodskap **en:**. Die
eerste vergelyking lewer 'n **Ja** of 'n **Nee** op. Dit is Boolese
objekte. Wanneer jy die boodskap **en:** aan 'n Ja-objek stuur, en die
argumentobjek ná die dubbelpunt is eweneens **Ja**, sal jy
weer **Ja** as antwoord ontvang. Wanneer een van die twee **Nee** is, sal jy
die antwoord **Nee** ontvang. Let daarop dat die een punt nie die koördinate van die
ander een kan lees nie. Dit is nodig om 'n boodskap aan die ander punt te stuur om
vir hierdie data te vra: **x-coordinate** en **y-coordinate**. Soos reeds
verduidelik is, kan eienskappe immers slegs van binne
die objekfamilie self verkry word. 

Let daarop dat die boodskap **=** hier gebruik word om die punte
te vergelyk. Net so goed kon 'n ander boodskap gebruik gewees het, soos:
**is:** of **equal:**; om die teken **=** te hergebruik, het egter in hierdie geval
gepas gelyk.

## Oorerwing

Jy kan voorheen geskrewe kode hergebruik om 'n hiërargie
van objekte te skep. Byvoorbeeld:

```
>> Animal := Objek nuut.
>> Dog := Animal nuut.
>> Poodle := Dog nuut.
```

In hierdie geval erf **Dog** al die gedrag en eienskappe
van **Animal**, en op sy beurt erf die objek **Animal** al die gedrag van
**Objek**, die wortelobjek van alle objekte.


## Oorskrywing


In die volgende voorbeeld word 'n nuwe soort lys geskep:
**Combination**, waarin elke element gewaarborg uniek is. Die
funksies van die lys word deur oorerwing hergebruik:

@test607

Let op hoe die tweede **red** van die lys uitgesluit word.

Soms kan dit nodig wees om 'n gedrag van 'n objek te oorskryf.
Byvoorbeeld wanneer getalle bymekaargetel word en daar met meeteenhede
rekening gehou moet word. In die volgende voorbeeld word die objek **Size**
geskep. Hierdie objek gee 'n getal terug wat by die optelling rekening
hou met die eenheid van die getal wat bygetel word. Die **Getal**-objek
kyk of dit om *duim* of *voet* gaan. Die programkode
kan soos volg lyk:

@test608

## Rekursie

In die vorige voorbeeld word die plus**teken** oorskryf. Let daarop
dat die finale optelling uiteindelik steeds gedoen moet word, wat in werklikheid
op die volgende reël plaasvind:

```
>> answer := self + (getal x factor).
```

Hoe verstaan XOScript nou dat hierdie plus**teken** na
die oorspronklike logika van optelling verwys?** 'n Ander interpretasie
kan byvoorbeeld wees dat XOScript herhaaldelik dieselfde boodskap aan dieselfde
objek stuur, wat op sy beurt tot 'n **eindelose lus** sou lei. Dit is duidelik
nie die bedoeling nie. Sodra jy 'n boodskap aan 'n objek stuur
wat presies dieselfde kode sou uitvoer, besef XOScript
in hierdie geval dat die onderliggende, oorskryfde boodskap bedoel word. Jou
program word dus outomaties teen hierdie soort eindelose
lusse beskerm. Wanneer dit egter wel jou doel is om dieselfde funksie vanuit die
huidige funksie uit te voer, sal dit nodig wees om eers die boodskap
**rekursief** te stuur. In daardie geval sal die resultaat 'n oneindige
lus wees. Daar is egter nuttige toepassings vir rekursiewe take;
gestel byvoorbeeld dat jy die fakulteit van 'n gegewe
getal wil bereken. Voeg in daardie geval eenvoudig die boodskap **factorial** by
Getal:

@test609

Dit vra vir rekursie. Die taak wat aan die
boodskap **factorial** gekoppel is, moet inderdaad weer binne daardie funksie uitgevoer word.
Dit is dus nodig om die fakulteitsfunksie van binne die
fakulteitsfunksie self op te roep. As reël sal XOScript hierdie roetine verhoed,
weens die gevaar om in 'n oneindige lus te beland. Om hierdie rede
is dit noodsaaklik om die woord **rekursief** voor die boodskap te plaas. Dit
word gedoen om XOScript bewus te maak daarvan dat dit jou
bedoeling is om dieselfde taak uit te voer, en dat jy nie 'n fout gemaak het nie.

## Klasagtige objekte

Hoewel xoscript nie klasse bied nie, is dit eenvoudig om klasagtige
gedrag na te boots. Oorskryf eenvoudig die boodskap nuut.

```
>> Animal := Objek nuut.
Animal by: ['nuut'] doen: {
	<- self nuut inisialiseer.
}.

Animal by: ['inisialiseer'] doen: {
	eie sound := ['?'].
	eie legs  := 4.
}.
```

In die kodefragment hierbo skep ons 'n objek genaamd Animal.
Hierdie objek dien as 'n *bloudruk* vir allerlei diere
soos honde en katte. Die ouerobjek Animal word
met 'n hoofletter A geskryf om aan te dui dat dit 'n klasagtige objek is.
Vervolgens oorskryf ons die boodskap nuut deur ons eie nuut-metode te skryf.
In hierdie geval stuur dit 'n boodskap nuut aan self, gevolg deur die boodskap
inisialiseer. Omdat xoscript rekursie by verstek blokkeer, sal dit nie
'n oneindige lus veroorsaak nie. In plaas daarvan stuur dit die boodskap nuut aan die ouer-
objek (Objek), wat 'n nuwe instansie van Animal oplewer. Ons skep dus
'n nuwe objek, gegrond op dieselfde objek waarvoor ons ons nuut-metode geskep het.
Dit is heeltemal geldig. Nou stuur ons ook die boodskap inisialiseer; dit verseker
dat die Animal-objek verstekwaardes vir sy eienskappe het. By verstek
het 'n dier 4 bene en is die klank onbekend (vandaar die vraagteken).
Om 'n nuwe instansie van ons Animal te skep, kan ons eenvoudig sê:

```
>> a := Animal nuut.
```

Nou kry ons 'n nuwe instansie van Animal met 4 bene, 'n onbekende klank en
'n inisialiseer-metode. Net soos in ander OOP-tale kan ons ook
ons Animal uitbrei:

```
>> Dog := Animal nuut.
Dog by: ['inisialiseer'] doen: {
	self inisialiseer.
	eie sound := ['barks'].
}.
```

Ons kan dit maklik toets deur 'n teks-metode by te voeg:

```
Animal by: ['teks'] doen: {
	<- eie legs teks + eie sound.
}.
```

Kom ons sit alles saam:

@test13


Om 'n objek te skep wat in 'n gegewe begintoestand gestel is, is 'n
algemene probleem. Gestel 'n objek **Rectangle** moet geskep word
om omtrek en oppervlakte te bereken. 'n Moontlike notasie sou wees:


```
>> Rectangle := Objek nuut.

Rectangle by: ['area'] doen: {
	<- eie lengte * eie width.
}.
```

Dit is natuurlik 'n voorvereiste om 'n lengte en breedte te stel. Vir
daardie doel kan die boodskappe **length:** en **width:** bygevoeg word:


```
Rectangle by: ['length:'] doen: { :lengte
	eie lengte := lengte.
}.

Rectangle by: ['width:'] doen: { :width
	eie width := width.
}.

```

Hierdie reghoek kan dan soos volg gebruik word:


```
>> rectangle := Rectangle nuut length: 2, width: 3.
Uitvoer skryf: rectangle area.
```

As die beginwaardes van lengte en breedte egter vergeet word,
sal 'n foutboodskap verskyn:

```
>> rectangle := Rectangle nuut.
Uitvoer skryf: rectangle area.
```

sal die volgende fout gee:

```
Sleutel nie gevind nie:lengte
```

Om dit te voorkom, is dit verkieslik dat 'n reghoek
altyd 'n beginlengte en -breedte het, byvoorbeeld 0. In hierdie
geval is dit dus nodig om die boodskap **nuut** te **oorskryf**.

@test610

As ons die nuut-boodskap oorskryf, boots ons in wese 'n **klas** na.

Die wêreld van XOScript is gevul met 'n verskeidenheid objekte wat
van die begin af aan jou program beskikbaar is. In die volgende hoofstukke
word al hierdie kernobjekte bespreek.

## Momentopnames

Jy kan 'n objek (saam met sy huidige toestand) op skyf stoor met:

```
myobject save-as: ['saved.bin'].
```

Om die objek weer van skyf te laai:

```
>> myobject := Objek load-from: ['saved.bin'].
```

Momentopnames kan gebruik word om 'n sekere toestand te stoor of om werkverrigting te verbeter.
Om 'n momentopname te laai, vermy leksing, ontleding en die opstelling van die toepassing.
In die toekoms kan bykomende werkverrigtingsvoordele ook met
momentopnames ingevoer word, soos optimering van sekere patrone of die opsporing en
optimering van warm paaie.

{{warning}}
Momentopnames is 'n eksperimentele funksie; moenie dit in produksie gebruik nie.
Om eksperimentele funksies te aktiveer, kompileer met -D EXPERIMENTS.
{{/warning}}


@test712

# Die objek Niks

{{messages}}

Die objek Niks
verteenwoordig leegheid, of nog beter, die afwesigheid van inligting. Soms
sal jy hierdie objek as antwoord op 'n boodskap ontvang wanneer
die resultaat **niks** is. Die belangrikste vraag
wat jy aan die objek **Niks** kan stel, is: **Niks?**. Die
antwoord sal altyd **Ja** wees.

```
Uitvoer skryf: Niks Niks?.
```

resultaat:

```
Ja
```

Enige ander objek as **Niks** sal met **Nee** antwoord. Die
kodefragment hierbo mag dalk 'n bietjie filosofies lyk, maar die objek **Niks**
het beslis uiters praktiese toepassings. Jy sal byvoorbeeld
die objek Niks as antwoord ontvang wanneer jy vra vir 'n
lyselement wat nie bestaan nie. Jy kan die objek Niks ook gebruik
as jy 'n veranderlike wil verklaar, maar nog nie 'n waarde wil spesifiseer
nie. In plaas daarvan **ken** jy eenvoudig die spesiale waarde **Niks** **toe**. In
XOScript is dit nie toegelaat om 'n veranderlike sonder waarde te verklaar nie, soos:


```
>> waarde.
```

In plaas daarvan moet jy die volgende skryf:

```
>> waarde := Niks.
```

@api_None_base

# Boolese waardes

{{messages}}

Anders as die meeste gewilde programmeertale ten tyde van skrywe,
bied XOScript slegs een enkele Ja-objek en een enkele Nee-objek.
Om dit te verduidelik: elke keer as jy **Ja** skryf, beteken dit nie dat
'n nuwe objek geskep is nie. In plaas daarvan gebruik jy altyd 'n verwysing. Dit
beteken dat wanneer jy die volgende skryf:

\>\> x := Ja.

die **x** na die objek **Ja** verwys. Voorwaardelike kode en lusse
kontroleer ook hierdie verwysing. In XOScript is die betekenis van **Ja** en **Nee**
nie vas nie. 'n XOScript-program word trouens behoorlik deurmekaar geskud deur
'n stelling soos hierdie:

Ja := Nee.

Die resultaat van sulke aksies is ongedefinieer, maar dit bly 'n geldige
aksie en is daarom formeel toegelaat. Verder is daar 'n Boolees-objek,
wat die wortelobjek van sowel **Ja** as **Nee** is, aangesien albei
afgeleides van die wortelobjek is. Die Boolees-objek self bied egter
geen praktiese toepassing nie.

## Slaggate

Wees versigtig met die gebruik van **en:** en **of:**

```
Uitvoer skryf: (Nee or: Ja or: Ja), nuwe-reël.
Uitvoer skryf: (Nee of: Ja, of: Ja), nuwe-reël.
```

Lewer

```
Nee
Ja
```
omdat die boodskap **of:** slegs 1 argument neem. Die eerste reël
stuur **of:of:** aan Nee, wat nie bestaan nie, dus ignoreer die objek
die boodskap en gee homself (Nee) terug. Aan die ander kant stuur die tweede reël
**of:** gevolg deur nog 'n **of:** (met behulp van 'n kettingsimbool, d.w.s. 'n komma: ,).


@api_Boolean_base

# Getalle

{{messages}}

Elke keer as jy 'n getal skryf, byvoorbeeld 9, -10 of 3,12, sal XOScript
agter die skerms hierdie getalle in 'n **Getal**-objek omskakel. Jy
kan boodskappe aan hierdie Getal-objek stuur, of jy kan die getal
aan 'n veranderlike toeken en daarna boodskappe stuur:

```
10 ewe?

>> tenner := 10.
tenner ewe?

```

Albei notasies is geldig. Die Getal-objek reageer op die volgende
boodskappe...

Die meeste van hierdie boodskappe spreek vanself en laat jou toe om
wiskundige bewerkings of vergelykings uit te voer.

{{note}}
Let daarop dat jy ≤ ≥ ≠ × en ÷ in plaas van hul ASCII-eweknieë mag gebruik.
Dit is 'n kwessie van voorkeur.
{{/note}}

Die verskil tussen binêre wiskundige boodskappe (+) en
hul sleutelwoordvariante (tel-by:) is dat eersgenoemde
'n nuwe getal teruggee, wat die resultaat van die bewerking is, terwyl by
laasgenoemde die objek self gewysig word. Dit word in die
volgende voorbeeld geïllustreer:

@test597

In die voorbeeld hierbo is b = 4 en a = 3. Met **tel-by: 2** word die waarde
van a met 2 verhoog, terwyl **+ 3** 'n nuwe getal skep wat
gelyk is aan a + 3. Dieselfde geld vir ander wiskundige bewerkings, bv.
vermenigvuldiging. Deur die vermenigvuldigingsimbool te gebruik, ontvang jy 'n
nuwe objek as antwoord. As jy die boodskap **vermenigvuldig-met:** gebruik,
vermenigvuldig jy die getal self.

Met die boodskap **tussen:en:**, byvoorbeeld in: **Getal
tussen: X en: Y**, kry jy 'n getal tussen X en Y. Op hierdie
manier kan enige lukrake getal gegenereer word:

```
>> a := Getal tussen: 1 en: 10.
Uitvoer skryf: a, nuwe-reël.
```

Vanaf weergawe 1.4 is die ingeboude generator van lukrake getalle in xoscript
na ons beste wete kriptografies veilig.

Jy kan 'n **kwalifiseerder** aan 'n getal heg, byvoorbeeld **6
apples**. Elke boodskap wat nie deur 'n
getal herken word nie, word as 'n kwalifiseerder beskou. Jy kan die kwalifiseerder van
'n getal verkry met die boodskap kwalifiseerder:

'n Kwalifiseerder is basies 'n Teks-objek wat saam met die Getal-objek
gestoor word. Die kwalifiseerder word ook ná die getal gedruk by 'n
**skryf:**-opdrag. Kwalifiseerders kan byvoorbeeld gebruik word om bedrae
in gemengde geldeenhede op te tel. Wanneer die bedrae opgetel word, kan jy
na die kwalifiseerders vra. Die volgende programvoorbeeld illustreer hierdie
beginsel met behulp van 'n historiese geldeenheidsakrekenaar (aangesien die wisselkoers
redelik stabiel bly!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Teks

{{messages}}

Elke keer as 'n teks tussen **blokhakies en aanhalingstekens** ['...'] geplaas word,
sal XOScript 'n nuwe teksobjek vir jou skep. Maak egter
seker dat jy die korrekte aanhalingstekens gebruik. Die aanhalingsteken aan die
begin van die teks verskil van die een aan die einde (dit laat jou toe
om die enkele aanhalingsteken te gebruik sonder om dit te ontsnap).

## UTF8

Teks in xoscript bevat gewoonlik utf8-gekodeerde teks. Hoewel
dit tegnies moontlik is om binêre of nie-utf8-inhoud in
'n teks te hê, word dit aanbeveel om blobs daarvoor te gebruik. Blobs word
deur die bedienerinprop voorsien (sien die hoofstuk ffi).
In die algemeen word blobs/ffi
per inprop/platform voorsien, aangesien hulle aan die platform
en argitektuur gekoppel is (ffi/blobs). Die kern van die skriptaal probeer
so platformonafhanklik as moontlik bly.

## Tipe-omskakeling

Jy kan 'n kopie van elke objek
met 'n ander tipe skep deur die volgende boodskappe te gebruik:

Boodskap | Resultaat
-------- | ------
getal    | Skakel om na 'n getal
teks     | Skakel om na teks
boolees  | Skakel om na 'n Boolese waarde
  
Die volgende reëls is van **toepassing**:

boodskap | Niks      | Boolees            | Getal                 | Teks      | Ander              
-------- | --------- | --------           | --------              | --------  | --------
boolees  | Nee       | n.v.t.             | 0→Nee anders→Ja       | Ja        | Meestal Ja
getal    | 0         | Nee→0 Ja→1         | n.v.t.                | ['n']→n | Meestal 1
teks     | ['Niks']  | ['Nee']/['Ja']     | ['n']                 | n.v.t.    | Hang af

## Kopiëring

Waardes in XOScript word altyd **per verwysing** deurgegee. In ander tale
hang dit af van die tipe waarde; in XOScript is daar net een manier,
per verwysing. XOScript maak nooit 'n kopie van 'n waarde nie. Om 'n objek te kopieer,
moet jy die boodskap **kopieer** stuur. 

@test611

Hier het jy dalk verwag dat die uitvoer Dolly sou wees in plaas
van Donny. Dit is egter nie die geval nie, aangesien albei name na dieselfde
objek verwys. Wanneer jy met 'n lus werk, gebeur iets soortgelyks:

@test612

XOScript gebruik inderdaad **altyd** verwysings, dus by **:quantity**
dui die lus hierbo ook die verwysing na die element
in die lys aan.

Om 'n objek te kopieer, moet jy hierdie aksie
**uitdruklik** spesifiseer:

@test613

Deur die unêre boodskap **kopieer** aan 'n teks te stuur, gee die objek
'n kopie van daardie selfde teksobjek terug. Dit is moontlik om Getal-objekte,
Boolese objekte, lyste en woordeboeke op dieselfde manier te kopieer.

Jy kan ook jou eie kopieer-implementering definieer; dit is selfs
noodsaaklik as jy jou eie objekte skep. Die verstek-
implementering van kopieer vir 'n lys maak 'n vlak kopie; dit skep 'n
nuwe lys met dieselfde elemente.

@test614

In hierdie geval word 4 slegs by die kopie gevoeg.
Omdat die kopie egter vlak is, is die objekte in albei lyste
dieselfde.

@test615

As ons dus 2 by elke naam in die kopie voeg, word die oorspronklike
lys ook geraak.

Om dit reg te stel, moet ons 'n **diep kopie** maak. So 'n kopieeraksie
vir 'n lys kan soos volg saamgestel word:

@test616

Let ook op die boodskap rekursief; dit is nodig om hierdie boodskap
voor die boodskap kopieer te stuur.

Dit is noodsaaklik om in gedagte te hou dat, hoewel 'n kopie van 'n objek
dikwels dieselfde voorkoms as die oorspronklike het, dit in werklikheid
nooit dieselfde sal wees nie. Die wortelobjek definieer 'n boodskap **gelyk:**,
wat gebruik kan word om die identiteit van objekte te vergelyk. Kyk na die
volgende voorbeeld:

@test617

## Implisiete omskakeling

XOScript gebruik **implisiete omskakeling** om objekte om te skakel. Om 'n
lys op die skerm te druk, sal XOScript byvoorbeeld intern die boodskap
*teks* aan die lys stuur. Dit kan baie nuttig wees
as jy 'n lys as 'n kommageskeide lys wil druk. Die
boodskap *teks* kan oorskryf word: 

@test620

@api_String_base
@api_Format_base


## Bedienerteks

Die volgende Teks-funksies word deur die
Server-inprop bygevoeg.

@api_String_server

# Funksies

{{messages}}

Jy kan kode tussen { en } groepeer; dit word dan 'n funksie.
In xoscript gebruik ons soms ook die term taak of bloot
kodeblok.

Jy kan 'n funksie laat loop deur die boodskap *begin* te stuur.


```
{ Uitvoer skryf: 123, nuwe-reël. } begin.
```

As jou funksie argumente neem, gebruik **pas-toe:**.

```
{ :a Uitvoer skryf: a, nuwe-reël. } pas-toe: a.
```

Sien ook die voorbeelde hieronder.
Weens die eenvoudige argitektuur kan 'n funksie slegs
een terugkeerpunt hê. Om oorhoofse koste of oormatige nesting vir
voorwaardes te vermy, kan jy 'n prosedure gebruik (wat dieselfde is as om die
vermenigvuldigingsteken met argument 1 te gebruik):

```
{
  (a = 1) ja: { x := 1. }, onderbreek.
  (a = 2) ja: { x := 2. }, onderbreek.
} prosedure.
```

Op hierdie manier word (a = 2) nie geëvalueer as a = 1 nie.
Jy het op hierdie manier ook geen geneste ja-boodskappe nodig nie.
Wanneer jy jouself voorwaardes sien nes, dink
aan die boodskap prosedure. Dit kan jou kode
makliker leesbaar maak.


Hier is 'n belangrike slaggat:

```
{
	Nee nee: {
		Uitvoer skryf: ['End the loop.'].
	}, onderbreek.
	
	Uitvoer skryf: ['Dont show me.'].

} prosedure.

```

In hierdie geval sal die teks 'Dont show me' gewys word,
omdat **onderbreek** aan Nee gestuur word. As jy
'n onderbreking wil uitvoer, moet dit as 'n boodskap aan **Ja** gestuur word.
 

```
{
	Nee nie ja: {
		Uitvoer skryf: ['End the loop.'].
	}, onderbreek.
	
	Uitvoer skryf: ['Dont show me.'].

} prosedure.

```

Sal werk soos verwag.

## Uitsonderings

Uitsonderings kan so hanteer word:

```
{ Task 1 } vang: { Task 2 }, begin.
```

Jy kan ook doelbewus 'n fout in jou program laat voorkom en
sodoende die hanteerderblok aktiveer. Dit word gedoen deur die
boodskap **fout:** aan die huidige taak te stuur, soos in hierdie volgende
illustrasie gewys word:

```
{
hierdie-taak fout: ['Whoops!'].
} vang: { :mistake
Uitvoer skryf: mistake.
}, begin.
```

## Waardes inspuit

XOScript bied vir take die opsie om waardes in te spuit. Kyk nou
na die taak hieronder:

```
>> sending := {
	Newsletter aan: eie recipient.
}.
sending stel: ['recipient']
waarde: ['info@recipient.org'].
sending begin.
```


Hierdie illustrasie toon 'n denkbeeldige taak wat 'n nuusbrief
aan 'n e-posadres of **recipient** stuur. Hierdie ontvanger kan
van buite en voordat die taak begin word, in die taak ingespuit word deur die
boodskap **stel:waarde:** aan die taak te stuur. Sodoende word die waarde van
**recipient** vooraf in die taak gestel. Hierdie waarde kan ook gewysig word
en die taak kan dan weer laat loop word. Dit is 'n nuttige metode wanneer
Taak-objekte gebruik word.

## Leë funksies

Leë take is nie toegelaat nie. In teorie sou 'n leë taak so
lyk: **{}**, maar XOScript beskou dit as 'n taalfout. As jy
'n leë taak wil verklaar, kan jy die objek Niks gebruik:

```
>> task := Niks.
```

Hoewel dit nie 'n werklike taak is nie, maar 'n Niks-objek, kan 'n begin-boodskap
steeds gestuur word:

```
>> answer := task begin.
```

Dit is in werklikheid dieselfde as:

```
>> answer := Niks begin.
```

Omdat die objek **Niks** nie die boodskap **begin** herken nie, sal
dit homself as antwoord teruggee, sodat die antwoord weer eens **Niks** is.
Dit is dus nie nodig om 'n leë taak te hê nie. Danksy die elegante
ontwerp van die programmeertaal XOScript kan jy eenvoudig die objek Niks
hiervoor gebruik.

## Dinamiese omvang

Wanneer 'n Funksie 'n veranderlike nodig het maar dit nie kan vind nie,
sal dit die veranderlikes van die Funksie wat dit **opgeroep** het, nagaan,
en verder in die ketting van Funksies op soek.
Hierdie soekproses gaan voort totdat die veranderlike gevind word.
As die veranderlike steeds nie gevind word nie, verskyn 'n foutboodskap. Hierdie metode om na 'n
veranderlike te soek, word **dinamiese omvang** genoem.

Om hierdie beginsel te illustreer:

@test618

@api_Code_base

# Wortelobjek

{{messages}}

Die objek genaamd **Objek** is die wortelobjek van alle objekte in
XOScript en voorsien die kernfunksies van die taal. 

Die boodskap wat die meeste gestuur word,
is **by:doen:**, wat die funksionaliteit van 'n objek uitbrei. Hierdie
boodskap word deur die wortelobjek ontvang, wat gevolglik die
gespesifiseerde taak aan die boodskap koppel en sodoende die afgeleide
objek uitbrei.

## Vang-alles-metodes

Gewoonlik word 'n boodskap wat nie met 'n metode in die objek ooreenstem nie,
geïgnoreer. Jy kan egter
sogenaamde **towermetodes** of **vang-alles**-metodes spesifiseer wat
opgeroep word as die boodskap nie deur die objek verstaan word nie.

Daar is 4 vang-alles-metodes beskikbaar. Elke boodskap pas by
'n spesifieke aantal argumente.

Vang-alles-boodskap     | Aantal argumente
----------------------- | -------------------
reageer:                | 0
reageer:en:             | 1
reageer:en:en:          | 2
reageer:en:en:en:       | 3


@test619

## Programmatiese boodskappe

In plaas daarvan om 'n boodskap direk aan 'n objek te stuur, kan dit ook
via 'n veranderlike gestuur word. Om dit te doen, gebruik jy die boodskap
**boodskap:argumente:**. 

@test396

@api_Object_base

# Lyste

{{messages}}

XOScript ken twee soorte versamelings: *lyste* en *woordeboeke*.
**Lyste** is opsommings van objekte in 'n *vaste volgorde*. Woordeboeke het
geen volgorde nie, maar lyk eerder op 'n legende met 'n sleutel (of term) en die
ooreenstemmende waarde. Lyste is vergelykbaar met arrays (PHP, Java, C)
en lists (Python). Woordeboeke is vergelykbaar met assosiatiewe arrays (PHP) of
dictionaries (Python) in ander programmeertale. Om 'n
nuwe Lys te skep, skryf:

```
>> fibonacci := Lys nuut.
```

Hierdie leë lyste kan gevul word met **voeg-agter:** :

```
fibonacci voeg-agter: 0.
fibonacci voeg-agter: 1.
fibonacci voeg-agter: 1.
fibonacci voeg-agter: 2.
fibonacci voeg-agter: 3.
fibonacci voeg-agter: 5.
fibonacci voeg-agter: 8.
fibonacci voeg-agter: 13.
```

As ons die lys op die skerm skryf:

```
Uitvoer skryf: fibonacci, nuwe-reël.
```

Sal ons sien:

```
Lys ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

In plaas van voeg-agter kan jy ook ; gebruik om elemente by 'n lys te voeg:


```
>> fibonacci := Lys nuut ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Die kommapunte (;) is almal binêre boodskappe wat 'n
waarde in die lys plaas.

## Aaneenskakeling

Gestel jy het 'n lys soos:

```
>> x := Lys nuut ; 1 ; 2 ; 3.
```

As jy die eerste en die laaste element wil verwyder, sou jou
boodskap wees:

```
x haal-eerste haal-laaste.
```

Ongelukkig sal die vorige notasie nie korrek werk nie. Die
boodskap **haal-eerste** gee die eerste element van die lys terug, wat
op sy beurt die ontvanger van die boodskap **haal-laaste** word. Die
boodskap **haal-laaste** word dus nie aan **x** gestuur nie, maar aan 2. 'n
Moontlike oplossing vir hierdie probleem sou wees om twee afsonderlike
sinne te skep, soos: 

```
x haal-eerste.
x haal-laaste.
```

Dit is egter taamlik onprakties, veral wanneer jy
meer as twee elemente moet verwyder. Daarom bied XOScript 'n
alternatiewe boodskapstruktuur vir hierdie soort situasies. In
**alternatiewe** boodskapstrukture word die antwoorde van objekte geïgnoreer
en kry jy telkens die ontvangende objek as antwoord terug.
'n **Alternatiewe** boodskapstruktuur word begin deur die
boodskap **doen** aan 'n objek te stuur, en die **alternatiewe** boodskap-
struktuur kan beëindig word deur die boodskap **klaar** te stuur. In die
geïllustreerde voorbeeld kan dit soos volg toegepas word:

```
>> x := Lys nuut ; 1 ; 2 ; 3.
x doen haal-eerste haal-laaste klaar.
```

@api_List_collections

# Woordeboeke

{{messages}}

**Sowel Lys as Woordeboek is versamelings. Anders as 'n
lys het 'n woordeboek egter **geen** volgorde nie. Nog 'n onderskeid tussen die twee
is dat 'n woordeboek uit objekpare bestaan. Een objek dien as inskrywing (of
sleutelwoord) om na die ander objek te soek. 'n Goeie voorbeeld van so 'n
lys is 'n pryslys, soos:


```
>> menu := Woordeboek nuut
	sit: ['£5'] by: ['apple pie'],
	sit: ['£6'] by: ['carrot cake'],
	sit: ['£3'] by: ['fudge'].
```

Soortgelyk aan 'n lys word die boodskap sit:by:
gebruik om 'n objek by 'n lys te voeg. Die verskil is dat, anders as by
'n lys, twee objekte aan mekaar gekoppel word. Die eerste objek is, soortgelyk
aan 'n lys, die objek wat jy in 'n lys sal stoor. Die tweede
objek is nie die posisie daarvan binne die versameling nie, maar die **inskrywing**
waarmee die vorige objek later weer verkry kan word. Kortom
werk 'n woordeboek 'n bietjie soos 'n woordeboek in boekvorm; deur die sleutelwoord te gebruik,
kan die betekenis gevind word. Om byvoorbeeld uit die
lys hierbo die prys van 'n fudge te verkry:

```
>> price := menu by: ['fudge'].
```

Jy kan ook die bondige notasie gebruik:

```
>> price := menu ? ['fudge'].
```

As die inskrywings wat jy gebruik om objekte te stoor geen spasies bevat nie
(en nie met ander voorafgedefinieerde boodskappe bots nie),
kan die volgende notasie ook gebruik word:

```
>> menu := Woordeboek nuut
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Die notasie hierbo lees ongetwyfeld 'n bietjie meer natuurlik.
Om die prys van 'n
fudge op te vra, kan die volgende vereenvoudigde notasie gebruik word:

```
>> price := menu fudge.
```

@api_Dict_collections

# Lêer

{{messages}}

Die objek **Lêer** bied basiese toegang tot die lêerstelsel.
Jy kan hierdie objek gebruik om hele lêers in een slag in 'n veranderlike
in te lees, of om veranderlikes in een slag na lêers te skryf. Reël-vir-reël-lees
word ook ondersteun. Dit is die mees algemene lêer-I/O-bewerkings
in 'n skriptaal. Gevorderde lêerbewerkings vereis die
gebruik van FFI via die bedienerinprop of 'n aparte IO-inprop.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Datum/Tyd

{{messages}}

Vir 'n gestruktureerde voorstelling van tyd en datum gebruik XOScript die
objek **Oomblik**. Wanneer 'n nuwe Oomblik-objek op die skerm gedruk word, word die
huidige datum en tyd gewys:

```
Uitvoer skryf: Oomblik nuut, nuwe-reël.
```

Dit kan iets soos die volgende oplewer:

```
2020-10-10 12:16:39
```

Dit is ook maklik om die afsonderlike tydkomponente uit te lees. As dit
byvoorbeeld slegs nodig is om die huidige jaar te weet, kan die boodskap
**jaar** aan die oomblik gestuur word, en die antwoord sal op sy beurt 'n
Getal-objek wees wat slegs die jaar bevat:

```
>> m := Oomblik nuut.
Uitvoer skryf: m jaar, nuwe-reël.
```

@api_Moment_system

# Program/Standaarduitvoer

{{messages}}

Die objek Program verteenwoordig die toepassing wat tans loop. Hierdie objek
bied funksionaliteit om stelselopdragte uit te voer, subprogramme in te sluit,
argumente te lees en meer. Al die stelselverwante funksies.

## Standaarduitvoer

Uitvoer is die standaard-uitvoerobjek. Dit het basies twee metodes:
**skryf:** en **nuwe-reël**. Die boodskap skryf: word gebruik om 'n teks
na stdout te stuur; die boodskap nuwe-reël druk 'n nuwereël-teken.
In plaas van **nuwe-reël** kan jy ook \\n gebruik.

Voorbeeld:

```
Uitvoer skryf: ['Hello World'], nuwe-reël.
```

resultaat:

```
Hello World
```

## Modules/Inproppe

Die wêreld van XOScript kan met nuwe stelselobjekte uitgebrei word deur
modules te installeer. 'n Nuwe stelselobjek kan by die wêreld van
XOScript gevoeg word deur die modulelêer (gewoonlik 'n lêer met die agtervoegsel .so
) in die gids mods te plaas. 

Wanneer jy 'n boodskap stuur aan die objek wat deur die
inpropmodule beskikbaar gestel word, sal XOScript dit outomaties laai.

Jy kan ook self inproppe skryf. Inproppe word in die
programmeertaal C geskryf. Jy kan 'n voorbeeldinprop in die bronkode-
pakket vind onder src/plugins/example.


## Refleksie

Daar is verskeie maniere om die stelsel
tydens die uitvoering van die program te verken. XOScript het 'n paar metodes om
vas te stel watter objekte teenwoordig is en op watter boodskappe hierdie objekte
reageer. Eerstens kan elke objek gevra word watter **tipe** dit is;
tipes in XOScript is egter vormbaar en daarom onbetroubaar.

Dit is ook moontlik om die objek Program te vra of 'n
gegewe objek reeds in die program teenwoordig is:

```
Program Tool ja: { ... }.
```

In die geval van 'n objek-
naam wat uit een enkele simbool bestaan, is dit die beste om die
volgende notasie te gebruik om verwarring te vermy:

```
Program vind: ['X'], ja: { ... }.
```

Behalwe om na objekte te vra, is dit eweneens moontlik om die
objek Program oor boodskappe te vra. Daar kan byvoorbeeld gevra word of die
objek **Getal** die boodskap **tussen:en:** ken, op die manier
wat hieronder geïllustreer word:

```
Program Number: ['between:and:'], nuwe-reël.
```

@api_Program_system

# Bediener

{{messages}}

Die Server-inprop in xoscript bied funksionaliteit om
bedienerkant-toepassings te skep. Om die bediener-
inprop te laai, gebruik:

```
Server inisialiseer.
```

Vir jou gerief word dit ook aanbeveel om
die lêers webtools.xo en template.xo te laai.

```
Program gebruik: ['webtools.xo'].
Program gebruik: ['template.xo'].

```

## Bedienerinstellings

Jy kan die volgende bedienerinstellings stel:

```
	# default values are given
	# so if you do not set anything these
	# values are used...

	Program 
	instelling: ['max-postfields']
	waarde: 40.

	Program 
	instelling: ['max-contentlength']
	waarde: 2000000. # 2MB

	Program 
	instelling: ['max-time']
	waarde: 5000. # 5sec

```

## Hallo wêreld

Hier is 'n baie eenvoudige webprogram wat jy kan gebruik met 'n
standaard CGI-bediener soos Apache2, NGINX, OpenHTTPD of enige ander
bekende bediener.

```
#!/bin/xo

Server inisialiseer.
Program gebruik: ['webtools.xo'].

>> web-document := Webdokument nuut.

web-document uitvoer: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

As jy nie die objek Webdokument wil gebruik nie, is dit goed, maar
dan moet jy self die HTTP-kopstukke skryf:

```
#!/bin/xo
Uitvoer skryf: ['Content-type: text/html; charset=utf-8 \n\n'], nuwe-reël.
Uitvoer skryf: ['hello world!'], nuwe-reël.
``` 

## Versoek

Die objek HTTP-Versoek kan gebruik word om GET/POST/COOKIE- en
UPLOAD-data te verkry:

```
>> versoek  := HTTP-Versoek nuut.
>> search   := versoek get: ['search']. # ?search=books
>> password := versoek post: ['password']. # from form
>> selected := versoek get-lys: ['sel[]']. #?sel[]=1&sel[]=2
>> selected := versoek post-lys: ['sel[]'].
>> cookie   := versoek cookie: ['session-id'].
>> upload   := versoek upload: ['file'].
>> temppath := upload ? 1.
>> filename := upload ? 0.
```

## Maksimum post/lengte

Die verstek maksimum aantal postvelde is 40 en die verstek maksimum inhouds-
lengte is 2MB. Om dit per skrip anders op te stel:

```
Program instelling: ['max-contentlength'] waarde: 1. 
Program instelling: ['max-postfields'] waarde: 1. 
```

{{note}}
As die inhoudslengte die maksimum oorskry, word die
proses beëindig omdat ons nie meer seker kan wees
dat die vrag veilig is nie.
{{/note}}

Die maxtime-limiet bepaal die maksimum tyd in ms
om stdin/postdata te lees.

```
Program instelling: ['max-time'] waarde: 5000. # 5sec
```

Dit geld slegs vir die I/O-lees van die post en voorkom
slowloris-agtige aanvalle. As jy werklik die
uitvoeringstyd van enige bewerking wil beperk, gebruik Program alarm.

## Databasis

Die Databasis-objek kan gebruik word om navrae aan MariaDB/MySQL te rig.
Om aan 'n databasis te koppel, doen:

```
>> db := Maria-DB nuut gasheer: ['localhost'],
	gebruikersnaam: ['xo'],
	wagwoord: ['pass123'],
	databasisnaam: ['xobase'],
	verbind.

```

Om 'n rekord in te voeg, gebruik:

```
>> soekparameters := db navraag: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parameters: ( Lys nuut ; ['abc'] ; 12.35 ; 6 ). # parameterized queries

{  soekparameters voer-uit. db bevestig. }
vang: { :e db rol-terug.  }, begin.
```

Let daarop dat xoscript *slegs* met transaksies werk en nooit outomaties bevestig nie.
As outomatiese bevestiging nie gedeaktiveer kan word nie, kry jy 'n verbindingsfout.
Gebruik altyd parameterbinding vir navrae; voeg nooit gebruikersinvoer direk
by die SQL nie.

Verkry die ingevoegde id soos volg:

```
Uitvoer skryf: ['INSERTED: '] + soekparameters insert-id, nuwe-reël. # insert id
```

Om rekords te haal:

```
>> soekparameters :=
db
	navraag: ['SELECT * FROM book order by id desc limit 2'], 
	haal: { :row 
		Uitvoer skryf: row id + [' '] + row description + [': '] + row price, nuwe-reël.
	}. # fetching rows

```

## Sessies

Vir volhoubaarheid kan jy data in 'n sessie-objek stoor en daaruit haal.
Skep eers 'n nuwe **Webdokument**. Die objek Webdokument bind
die versoek, kopstukke, HTML en sessie saam. Dit is omdat jy, wanneer jy
'n webwerf met jou blaaier besoek, net die HTML sien. Maar die
hele Webdokument bestaan ook uit **kopstukke**. Byvoorbeeld,
die meeste HTTP-antwoorde bevat 'n kopstuk soos: Content-type:text/html om
die blaaier te vertel dat die data wat volg as HTML weergegee moet word
(en nie byvoorbeeld soos 'n lêer afgelaai moet word nie). Sessies is 'n manier om
gebruikersdata tussen versoeke te stoor. Om hierdie data by te hou, moet ons
'n cookie stel; hierdie cookie word ook deur 'n kopstuk gestel. Daarom
kom alles saam in die Webdokument (omdat dit die volledige
dokument is wat sowel kopstukke as HTML of ander data bevat).


```
# First we make a new Web Document instance
>> web := Webdokument nuut.

# Now we start a session, this will generate a Header for a cookie and
# create a file to store your data, associated with that cookie
>> session := web sessie-begin.

# Now we can treat session like a dict
session userid: 123.
```

Om die sessie te vernietig (wanneer jy afmeld):

```
web sessie-vernietig.
```

## Kopstukke

Met die Webdokument kan jy ook ander bekende kopstukke stel.
Byvoorbeeld, as jy die gebruiker na 'n ander URL wil herlei:

```
web gaan-na: ['/other.html'].
```

Agter die skerms genereer hierdie opdrag ook die HTTP-kopstuk wat
saam met jou ander data of HTML gestuur word om die blaaier opdrag te gee om
na die gespesifiseerde teikenadres te navigeer.

Om 'n eie kopstuk by te voeg:

```
web kopstuk: ( 
	HTTP-Kop nuut
	sleutel: ['Content-Length']
	waarde: 400
).
```

Om 'n 404-bladsy te wys:

```
web nie-gevind: ['OOps..'].
```


## Sjablone

Die verstek sjabloonstelsel is baie eenvoudig. Jy hoef nie
'n nuwe sjabloonsintaksis te leer nie. Die sjabloonenjin verseker ook werklike skeiding
tussen aanbieding en besigheidslogika.

Om 'n sjabloon uit 'n lêer te skep:

```
>> tpl := web sjabloon: ['templates/ux.tpl'].
```

Die sjabloonstelsel gebruik merkers. 
Daar is drie soorte merkers: knipmerkers, plakmerkers en
gleufmerkers. Die basiese idee is baie eenvoudig: jy knip
areas uit wat deur knipmerkers aangedui word, en jy kan hulle plak by
areas wat deur plakmerkers aangedui word. Jy kan teks in
gleufmerkers inspuit.

Gegewe byvoorbeeld die volgende sjabloon, kom ons sit die
edelsteen in die juwelekissie en voeg 'n pryskaartjie by.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Jy kan dit soos volg doen:

```
>> gem := tpl uitknip: ['gem'], kopieer.
gem price: 99.
tpl plak: gem by: ['jewels'].
web uitvoer: tpl skoonmaak.
```

Die laaste reël stuur die sjabloon bloot as teks na die kliënt,
saam met die vereiste HTTP-kopstukke.

Resultaat:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Deurgee

Om lêers wat deur gebruikers opgelaai is veilig te bedien, kan jy op passthru staatmaak:

```
>> uploaded := ['smile.gif'].
Server gee-deur: uploaded voorvoegsel: ['/uploads/images/'].
Program einde.
```

Dit bedien die inhoud wat deur die gebruiker opgelaai is met die toepaslike
mime-tipe. Slegs mime-tipes op die witlys word ondersteun:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF en SVG.
SVG-, ZIP- en GZIP-lêers word as aflaai gestuur, omdat 'n SVG
skripte kan bevat wat andersins op jou domein sou loop.
Hierdie metode voorkom TOCTOU-aanvalle, padtraversering, 
uitvoering van kwaadwillige kode (inspuiting), symlink-aanvalle,
DDoS-aanvalle (lêerlimiet = 50MB), afluisteraanvalle en 
verskeie ander sekuriteitsprobleme.


## JSON

Om 'n objek as JSON te kodeer:

```
>> json := ( JSON jsonify: ( 
	Woordeboek nuut sit: ( 
		Lys nuut ; 1 ; 2 ; 3
	) by: ['abc']
)).
```

Om JSON in 'n xoscript-objek te dekodeer:

```
>> dict := ((JSON objek: json) abc ? 1).
```

JSON met meer as 500 vlakke van nesting word as ongeldig verwerp.

Om 'n Woordeboek direk as json met die korrekte kopstukke uit te voer:

```
web json: dict.
```


## Regex

Jy kan gereelde uitdrukkings gebruik deur 'n patroon te skep.
Byvoorbeeld om die hrefs en teikens van hiperskakels te vind:

```
Patroon nuut: ['href="([^"]+)" target="([^"]+)"'].
```

Pas die patroon nou soos volg op die onderwerpteks toe:

```
pattern passing: onderwerp doen: { :m :x .... }
```

Volledige voorbeeld:

```
>> onderwerp := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> pattern := Patroon nuut: ['href="([^"]+)" target="([^"]+)"'].
>> result  := pattern passing: onderwerp doen: { :m :x
	Uitvoer skryf: m, nuwe-reël.
	Uitvoer skryf: x, nuwe-reël.
	<- ['XXX'].
}.
Uitvoer skryf: result, nuwe-reël.
```

## Netwerk

Gebruik die objek Netwerk om 'n webversoek uit te voer.
Die objek Netwerk stuur altyd 'n POST-versoek, tensy jy Niks as
data stuur; dan stuur dit 'n GET-versoek.


```
Netwerk 
post: Niks 
na: ['https://redbeanphp.com'].
```

## Enkripsie

Die bedienerinprop kom met enkripsie gebaseer op XChaCha20 en Argon2.

Voorbeeld:

```
>> encrypted := Kluis enkripteer: ['hello'] sleutel: ['world'].
>> decrypted := Kluis enkripteer: encrypted sleutel: ['world'].
```

## Tokens

Om 'n kriptografies veilige token van 'n spesifieke lengte te genereer:

```
>> mytok := Kluis token: 40.
```

Dit genereer 'n token van 40 karakters.

## Formatering

Met die objek Formaat kan jy data formateer, soos opvulling of
die byvoeging van nulle. Dit gebruik die printf-sintaksis.

```
>> fmt := Formaat nuut: ['%06.0f'].
fmt pas-toe: 56. # gives 000056
```

'n Formaat kan een omskakeling bevat en dit moet by die waarde pas,
anders kry jy 'n fout:

- `pas-toe:` met 'n teks: `%s`
- `pas-toe:` met 'n getal: `%f`, `%e`, `%g` of `%a`
- `pas-toe-heelgetal:` met 'n getal: `%d`, `%i`, `%o`, `%u`, `%x` of `%c`

Waardes uit 'n versoek is teks. Om een as 'n getal te formateer,
skakel dit eers om:

```
fmt pas-toe: (versoek get: ['amount']) getal.
```

## Enkodeerders

Verskeie enkodeerders en dekodeerders is beskikbaar.
Die url-enkodeerder berei 'n url voor vir gebruik in HTML as 'n skakel:

```
Server url-kodeer: ['https://example.com?a=6&b=1 2'].
```

Om gebruikersinvoer veilig in jou HTML in te spuit sonder om XSS-
inspuitings te waag, gebruik altyd:

```
Server html-kodeer: ['<harmless>'].
```

Let daarop dat die sjabloonenjin altyd html-kodering uitvoer
as jy na 'n gleufmerker skryf. As jy die sjabloonstelsel gebruik,
hoef jy dit dus nie te gebruik nie.

## E-pos

Om 'n e-pos te stuur, gebruik die biblioteek mailtools.xo.

Voorbeeld:

```
Server inisialiseer.
Program gebruik: ['mailtools.xo'].

>> e-mail := HTML-E-pos nuut.
>> img := e-mail aanheg: ( Lêer nuut: ['myimage.png'] ).

e-mail
afsender: ['xo@xoscript.com'] naam: ['xo'],
aan: ( Lys nuut ; ['xo2@xoscipt.com'] ),
onderwerp: ['xoxo'],
boodskapteks: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), stuur.

```



## Koppeling

Met die boodskap koppel: kan jy 'n eksterne biblioteek aan
jou program koppel met behulp van libffi. Sien die hoofstuk oor ffi vir besonderhede.


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

FFI word per platform/inprop voorsien omdat dit
aan die onderliggende stelselargitektuur gekoppel is, iets wat die
kern nie veronderstel is om te doen nie.
Die bedienerinprop bied 'n voldoenende ffi/blob-implementering.
By verstek koppel die kern aan die teikenplatform
via stdin/stdout, beperkte lêer-I/O-dienste en die shell (Program stelsel:).
Bykomende integrasie word deur ffi/blobs voorsien via toepassings-
gerigte inproppe soos die bedienerinprop.

FFI staan vir Foreign Function Interface. Dit laat jou toe om funksionaliteit te gebruik wat deur ander in
ander programmeertale geskryf is en deur DLL-lêers, SO-lêers of Dylib-lêers voorsien word. Dit kan
'n verskeidenheid funksies wees, en daar is 'n groot reeks funksionaliteit beskikbaar via hierdie metode.
Kom ons begin met 'n voorbeeld:

```
Server koppel: (
 Lys nuut ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Lys nuut ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s stel-vry.
```

Die resultaat van hierdie kode is dat jy die volgende op die opdragreël sal sien:
FFI has 3 letters.
Nou dink jy waarskynlik: "Dis baie kode vir iets so eenvoudigs."
Ek bedoel, kon ons dit nie net met 'n Gui show-opdrag oplos nie? Die antwoord is 'n volmondige ja!
Maar dit is bedoel as 'n illustratiewe voorbeeld.
FFI word gewoonlik vir meer komplekse take gebruik, maar dié maak nie goeie
voorbeelde nie, daarom het ek iets eenvoudigs gekies.

Die argumente vir die koppel-metode:

- Argument #1: Die DLL- of SO-lêer wat jy wil gebruik.
- Argument #2: Die funksie in daardie lêer wat jy wil koppel.
- Argument #3: 'n Lys met die name van die datatipes van die funksie se argumente.
- Argument #4: Die naam van die funksie se terugkeertipe.
- Argument #5: Die naam van die objek waaraan jy hierdie funksie wil koppel (as dit nie bestaan nie, word dit
outomaties geskep).
- Argument #6: Die boodskap waaraan hierdie funksie gekoppel moet word.

In die voorbeeld hierbo wil ons die printf-funksie uit libc.so koppel. Jy kan die name van die data-
tipes in die dokumentasie van die sagteware waaraan jy koppel, vind. Die beskikbare tipes is:
void, pointer, float, double, int, uint, char, uchar, intX en uintX,
waar X 8, 16, 32 of 64 kan wees.

Hierdie tipes verwys na die aantal grepe wat nodig is om die data te stoor. Vir printf koppel ons aan 'n
nuwe objek genaamd Printf en die boodskap template:number:. Jy vertaal die eksterne
funksie na die XOScript-dialek voordat jy dit gebruik. Die boodskap template:number: verwag 'n
buffer met die sjabloonteks as eerste parameter. Ons skep hierdie buffer met 'n Blob-objek, wat
jou toelaat om geheue met die hand toe te ken. Jy is daarna self verantwoordelik om hierdie geheue
met die boodskap stel-vry weer vry te stel.

Jy kan 'n geheueblob op verskeie maniere vul. In ons voorbeeld vul ons dit met teks, daarom gebruik ons die
boodskap utf8: (UTF-8 is 'n kodering om teks in grepe om te skakel). Jy kan 'n blob ook met
bytes: vul deur 'n lys greepwaardes deur te gee. Om die inhoud van 'n blob te lees, gebruik vanaf:lengte:.
Jy kry die grepe as 'n lys terug. Jy kan selfs 'n C-struct met 'n Blob skep met die
boodskap struct:, deur 'n reeks C-tipes deur te gee. Dit kan nodig wees wanneer jy 'n C-
funksie in 'n eksterne sagtewarebiblioteek oproep wat 'n wyser na 'n struct verwag.

{warning}
Jy moet blobs self vrystel.
Blobs word nie deur die vullisversamelaar skoongemaak nie.
{/warning}

Aangesien blobs met eksterne funksies uit biblioteke uitgeruil kan word,
kan hulle nie outomaties deur die vullisversamelaar opgeruim word nie (hulle kan steeds deur
eksterne funksies gebruik word, of hierdie eksterne funksies wil hulle dalk
self vrystel). Daarom moet jy blobs self vrystel indien nodig.

Om 'n blob vry te stel, gebruik:

```
myblob stel-vry.
```

Om 'n struct vry te stel, gebruik:

```
mystruct stel-struct-vry stel-vry.
```

Vir 'n struct moet jy dus twee boodskappe stuur: stel-struct-vry en stel-vry, om
die geheueblok vry te stel.

@api_Blob_fficonnect
