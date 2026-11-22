# Basis

{{messages}}


Welkom bij XOScript
Het XOScript-project heeft als doel een scripttaal te maken die eenvoudig en controleerbaar is.
Eenvoudig betekent niet per se makkelijk.
Een vertrouwde programmeertaal kan makkelijker in gebruik zijn dan XOScript.
Eenvoud betekent hier iets anders:
een volledig mentaal model kunnen vormen van de taal en haar gedrag.

XOScript is ontworpen om in je hoofd te passen.
De grammatica en het aantal concepten zijn bewust klein gehouden.
Er zijn geen klassen; objecten kunnen direct worden uitgebreid.
Objecten worden doorgegeven als referentie, kopiëren gebeurt expliciet
en functies hebben één enkel uitgangspunt.

Sommige van deze keuzes wijken sterk af van gangbare talen.
XOScript heeft bijvoorbeeld geen typesysteem en gebruikt dynamische scoping.
Berichten die niet kunnen worden afgehandeld, worden genegeerd in plaats van een exceptie te veroorzaken.
Deze keuzes hebben gevolgen en zijn niet bedoeld om fouten uit te bannen.
Ze zijn bedoeld om het onderliggende model van de taal klein en consistent te houden.

XOScript kan ook worden gelokaliseerd, waardoor het mogelijk is bedrijfsregels
in een natuurlijke taal uit te drukken en die eventueel te delen met niet-technische belanghebbenden.

Controleerbaarheid betekent dat dezelfde filosofie wordt toegepast op de implementatie.
De runtime is geschreven in C, met een kleine, met de hand geschreven lexer, parser en tree walker.
De standaardbibliotheek en de runtime volgen grotendeels de structuur van de taal,
waardoor de relatie tussen XOScript-code en de implementatie ervan vrij direct is.

Tests zijn ook nauw verbonden met de documentatie.
Elke methode hoort een bijbehorende test te hebben die in de handleiding kan worden opgenomen,
zodat de documentatie gelijk blijft lopen met de implementatie.

XOScript is niet bedoeld om met gangbare talen te concurreren op
functionaliteit of bekendheid. Het verkent een ander doel:
een programmeeromgeving die een ontwikkelaar als geheel kan begrijpen.

De hoop is dat een kleine taal en een kleine
implementatie het haalbaar maken om software te begrijpen
van byte tot object, van syntaxis tot runtime, en om code te schrijven met
vertrouwen, omdat je begrijpt wat er gebeurt in
het script en wat er onder de motorkap gebeurt.

De architectuur van een xoscript-serveropstelling
is eenvoudig en toch flexibel.

{{architecture.png}}

Om xoscript als servertaal te gebruiken, moet je de
serverplugin installeren in een map met de naam /mods/server. 

Dat komt doordat we
de kern van de taal graag loskoppelen van serverspecifieke functionaliteit,
anders dan bijvoorbeeld PHP of Python. Anders zouden we iedereen
de hele gootsteen erbij moeten leveren zonder dat het ergens voor nodig is, en dat is gewoon onzinnig.
Je kunt desgewenst ook andere modules installeren. Het systeem is zeer
flexibel.

Bovendien kunnen sommige functies beter in de scripttaal zelf
worden geïmplementeerd, zoals sjablonen en sessiebeheer, dus leveren we
daarnaast voor je gemak de bibliotheken template.xo en webtools.xo mee.
De reden voor dit alles is dat we niet weten hoe jij
xoscript wilt gebruiken. Je kunt het gebruiken als scripttaal aan de serverkant,
maar ook voor GUI's, embedded apparaten of gewoon batchverwerking.
Zelfs als je het als scripttaal aan de serverkant gebruikt (wat
momenteel een van de belangrijkste toepassingen is), wil je misschien toch
een andere sjabloon-engine of een andere sessie-afhandeling gebruiken.
Wie zijn wij om te bepalen dat je de onze moet gebruiken?

Een van de voordelen van onze eigen sjabloon-engine is overigens dat
je geen extra syntaxis hoeft te leren om sjablonen te maken.
De standaard sjabloon-engine die met xoscript wordt meegeleverd, hanteert 100%
scheiding tussen presentatie en logica. In plaats van speciale
sjabloonsyntaxis gebruikt hij simpelweg een zeer flexibel systeem van plekmarkeringen.
Zie het hoofdstuk Server voor meer informatie.

Merk op dat je, als je de standaard sjabloon-engine of
de standaard webtools niet wilt gebruiken, vanzelfsprekend
je eigen moet aanleveren.

Als je je webserver in een chroot, jail of een ander soort sandbox draait,
moet je ook de afhankelijkheden van xo in die omgeving installeren. Je kunt
zien welke bibliotheken je nodig hebt met ldd (zie de manpage van Linux of BSD).
Als je shellopdrachten in je xo-scripts wilt gebruiken, kopieer dan ook een shell
(zoals bash of ksh) naar deze omgeving.

We willen ook opmerken dat we achterwaartse compatibiliteit zeer serieus nemen.
Er is zelfs een speciale functie voor achterwaartse compatibiliteit beschikbaar, genaamd
'version'. In het algemeen streven we ernaar dat je code voor altijd blijft werken. Je hoeft je code dus
nooit bij te werken om compatibel te blijven met nieuwere versies
van xoscript. Ons doel is: één keer schrijven, voor altijd draaien.

De rest van deze handleiding is gewijd aan een gedetailleerde uitleg van de programmeertaal
xoscript. Scripting aan de serverkant wordt besproken in het hoofdstuk
Server. Als je een ervaren softwareontwikkelaar bent, wil je misschien
een paar hoofdstukken overslaan, omdat sommige ervan wat te gedetailleerd zijn of
sterk lijken op algemene programmeerpraktijken. Dus voor degenen onder jullie
die al ervaring hebben met meerdere andere programmeertalen:
gebruik deze handleiding liever als naslagwerk.

## Installatie Linux

Download apache2 en mariadb:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Download xoscript.
Vervang X door het juiste versienummer!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Kopieer de bestanden naar de webroot en /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Bewerk je apache2-configuratie:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Vervang Virtualhost door:

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

Maak een testpagina:

```
sudo nano /var/www/html/test.xo
```

en schrijf een klein testprogramma:

```
#!/bin/xo
Server initialiseren.
Programma gebruik: ['webtools.xo'].
>> web := Webdocument nieuw.
web uitvoeren: ['Hello World'].
```

Sta apache2 toe je programma via CGI uit te voeren:

```
sudo chmod uog+x /var/www/html/test.xo
```

Herstart apache2:

```
sudo systemctl restart apache2
```

Ga in de browser naar je testpagina:

```
http://localhost/test.xo
```

Je zou het volgende moeten zien:

```
Hello World
```


## Installatie OpenBSD

Bewerk /etc/httpd.conf en voeg toe:


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

Als je SSL wilt gebruiken:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Kies de mlkem-cipher om de sleuteluitwisseling
te beschermen tegen kwantumaanvallen:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Voeg het xo-programma en de mods, plus eventuele afhankelijkheden, toe aan de
chroot (zoek ze uit met ldd).

## Voorbeelden uitvoeren


Om een van de voorbeeldprogramma's uit het pakket uit te voeren:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Om bijvoorbeeld het FizzBuzz-voorbeeld op Linux uit te voeren:

```
./example.sh fizzbuzz Linux
```

Om hetzelfde voorbeeld op OpenBSD uit te voeren:

```
./example.sh fizzbuzz OBSD
```

Om het voorbeeld met een schone build uit te voeren:

```
./example.sh fizzbuzz OBSD clean
```

## Unittests

Om de unittests uit te voeren:

```
./runtests.sh
```

Om de unittests uit te voeren zonder te bouwen (alleen testen):

```
./runtests.sh nobuild
```

## Bouwen

Om vanuit de broncode te bouwen op Linux:

```
make clean
ISO="en" make
```

Op OpenBSD:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

Om de serverplugin op Linux te bouwen:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

Om de serverplugin op OpenBSD te bouwen:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Hallo wereld

Nadat het bestand naar je computer is overgebracht, kun je het uitpakken
en xo starten met de volgende opdracht:

```
xo
```

Om een XOScript uit te voeren, sla je het programma op als bestand, met het
achtervoegsel -xo (optioneel). Zet daarnaast de bestandsnaam van je programma
achter de XOScript-opdracht:

```
xo myprogram.xo
```

Wanneer je een XOScript-opdracht uitvoert met je programmabestand als
parameter, leest xo je programmabestand en voert het uit.

{{note}}
Je kunt je programma ook starten door het naar het xo-pictogram te slepen.
{{/note}}

{{warning}}
Op sommige systemen moet je xo vooraf toestemming geven om dynamische
bibliotheken te laden.
{{/warning}}

De traditie schrijft voor dat het eerste programma in elke nieuwe programmeertaal
een soort groet aan de wereld moet zijn. In XOScript ziet zo'n
**Hallo wereld**-programma er als volgt uit:

@test598

Wanneer deze tekst wordt opgeslagen in een bestand, bijvoorbeeld hello.xo, kan het als
volgt worden uitgevoerd: .

xo hello.xo

Hallo wereld


Je ziet de uitvoer van het programma in het hierboven getoonde zwarte venster.
In deze hele handleiding wordt dezelfde weergave gebruikt om
de uitvoer te tonen.

{{note}}
Uit wordt geschreven met een hoofdletter U.
In het algemeen beginnen objecten met een hoofdletter,
tenzij ze fungeren als instantie (geen eigen methoden
hebben, alleen gegevens). Dit weerspiegelt de conventies voor klasse en instantie
in andere programmeertalen.
{{/note}}


## Syntaxis 

XOScript is een *puur* *objectgeoriënteerde* programmeertaal. Dit betekent
dat xoscript alles als een object beschouwt; er zijn dus
geen andere *gegevenstypen*. Er zijn in wezen drie basishandelingen
in een programma dat in XOScript is geschreven: *toekennen*, *berichten sturen*
en *antwoorden*. Het uitwisselen van berichten tussen objecten is de kern van
een XOScript-programma. De drie afzonderlijke basishandelingen worden hieronder
geïllustreerd:


Handeling         | Voorbeeld
----------------- | --------
toekennen         |  \>\> x := 1. 
unaire berichten  | x even?.
binair bericht    | 1 + 2.
sleutelwoordbericht | x van: 0 lengte: 10.
antwoord          | <- antwoord.  


Dit hoofdstuk geeft je een algemene indruk van de taal XOScript
en beschrijft de basisprincipes ervan. XOScript is een kleine taal,
gebaseerd op drie handelingen (zie illustratie) die zich vertalen in
ongeveer zes grammaticaregels. Meer is er niet nodig om de
taal te beheersen.

Geen zorgen als niet alles je meteen duidelijk is: alle bouwstenen
worden in het volgende hoofdstuk (3) verkend en de basisregels worden
herhaald. Dit hoofdstuk dient echter vooral als algemene
inleiding tot de taal. De basisprincipes worden kort
uitgelegd en geïllustreerd met een aantal relevante voorbeelden. Ontbrekende
details komen later aan bod.

Commentaar in XOScript begint met een \#-teken. De volgende regel
wordt dus genegeerd:

```
# this is just a comment
```

## Variabelen

Om een variabele
toe te kennen, gebruik je het declaratiesymbool voor variabelen: >>. De naam van een
variabele mag alle tekens bevatten behalve: <-, :=, witruimte,
punten, komma's, dubbele punten, aanhalingstekens [' '] en haakjes ().
Verder mag een variabele niet uit meerdere regels bestaan. Let op
dat een variabele niet met een cijfer of een minteken mag beginnen.

Dit zijn voorbeelden van geldige variabelen:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dollar'].
>> +plus := Ja.
>> user-password := ['Pssst!'].
```

Ongeldige variabelen zijn bijvoorbeeld:


```
>> -123 := ['negative number'].
>> password of user := ['Classified'].
>> password.of:user := ['Classified'].
>> ,x := 10.
```

{{note}}
Je hoeft geen enkel teken te escapen
(ook geen aanhalingstekens, dubbele aanhalingstekens of
tekstgrenzen) in
een tekstliteral, zolang het geen
dubbelzinnigheid voor de lexer veroorzaakt.
{{/note}}

Nadat een variabele is gedeclareerd, kan hij vrij worden gebruikt. Dit betekent
dat je het declaratiesymbool alleen hoeft te gebruiken de eerste keer
dat je de variabele gebruikt (de declaratie).

Om precies te zijn: je kunt niet zomaar een waarde aan
je variabele toekennen *(x := 2)*, want je moet de variabele eerst declareren *(\>\>
x := 2)*. Eenmaal gedeclareerd mag je de waarde echter wijzigen
zonder het declaratiesymbool te gebruiken *(\>\> x := 2. x := 3.)*.

Merk op dat het verplicht is om bij het declareren een waarde aan een variabele
toe te kennen. Anders dan in andere programmeertalen mag je
een variabele niet zonder waarde declareren. Het is essentieel om
elke variabele expliciet aan een beginwaarde te koppelen. Je mag
de variabele echter gerust initialiseren met het object **Niets**. In dat geval kan de variabele
als leeg worden beschouwd *(\>\> x := Niets.)*. Kortom, een
variabele declareren zonder beginwaarde is niet toegestaan. Dus

```
>> x.
```

is ongeldig en geeft een foutmelding.

{{note}}
xoscript gebruikt dynamische scoping van variabelen; raadpleeg
voor details het hoofdstuk Functies.
{{/note}}


## Literals

XOScript beschouwt alles als een object, dat wil zeggen alle getallen, teksten
en codefragmenten. Getallen zoals 1, 2, 100, -999 en 1,234 zijn
Getal-objecten. Alle teksten tussen enkele aanhalingstekens zijn Tekst-objecten.
Alle codefragmenten die tussen accolades {...} zijn gegroepeerd, zijn
Functie-objecten.

Literal         | Basisobject  | Voorbeeld
--------------- | ------------ | ----------
getallen        | Getal        | 1,2,3... 
teksten         | Tekst        | \['hallo'\]
functie         | Functie      | { 1 + 2. }.
                
     
Objecten zoals getallen en teksten vinden altijd hun oorsprong in een basisobject.
Zo stammen alle getallen af van het object **Getal**. Alle
teksten stammen af van **Tekst** en alle codefragmenten van **Functie**. Op
hun beurt stammen al deze objecten af van **Object**, dat in feite het
basisobject van alle objecten is.


## Berichten

Programmeren in XOScript betekent in feite
berichten sturen naar objecten. De algemene notatie om een bericht naar
een object te sturen is als volgt:

```
<object> <message>
```

Om bijvoorbeeld uit te zoeken of het getal **2** een even getal is, wordt het
bericht **even?** naar object **2** gestuurd:

```
2 even?
```

Het antwoord is **Ja** (weer een object). Onbekende berichten worden
door objecten meestal genegeerd; er treedt dus geen fout op. Sommige objecten (bijvoorbeeld
getallen of teksten) reageren op een vooraf bepaalde manier op een onbekend bericht
(hierover later meer).

Een object kan drie soorten berichten ontvangen. 

Soort           | Aantal argumenten
--------------- | -------------------
Unair           | 0      
Binair          | 1     
Sleutelwoord    | 1+    


Ten eerste zijn er **unaire
berichten**, zie het voorbeeld hierboven, die geen argumenten hebben. Ten tweede
zijn er **sleutelwoordberichten**, die een of meer argumenten hebben,
bijvoorbeeld:

```
>> x := Getal tussen: 1 en: 10.
```

In dit geval wordt het bericht **tussen:en:** naar **Getal** gestuurd, dat
het basisobject van alle getallen is. Het resultaat is een willekeurig getal
tussen 1 en 10. Ten slotte zijn er **binaire berichten**, die
slechts één teken en één argument hebben:

```
2 + 3
```

Dit ziet eruit als een rekensom, maar het is eigenlijk gewoon een ander bericht. Het
bericht **+** wordt naar **2** gestuurd, met argument **3**, wat als
antwoord **5** oplevert. Binaire berichten mogen zonder dubbele punt worden geschreven.

Binaire berichten kunnen aan elkaar worden geschakeld:

```
>> x := 3 + 2 - 1.
```

In dit fragment wordt **+ 2** eerst naar **Getal**-object **3** gestuurd, wat
resulteert in Getal-object **5**, waarna **-1** naar dit
getal wordt gestuurd. Oplettende lezers merken terecht de afwijking op die
dit protocol vertoont ten opzichte van de gebruikelijke wiskundige volgorde van
bewerkingen. XOScript negeert de wiskundige volgorde ten gunste van
consistentie in zijn berichtensysteem. Daardoor is de som:

```
2 + 3 * 5 = 25
```

niet 17.

Dit is zo bedoeld. Met haakjes kun je de volgorde aanpassen:

```
2 + (3 * 5) = 17
```

De meeste objecten geven zichzelf terug als resultaat op een bepaald
bericht. Dat is handig, omdat het uitnodigt tot een verdere dialoog met dit
object door het een vervolgbericht te sturen:

```
Uit schrijf:
[' hello '] kern hoofdletters.
```

```
HELLO
```

Hier worden twee berichten naar het object **Tekst** gestuurd: **kern**, gevolgd
door **hoofdletters**.

In het volgende fragment is een komma nodig om aan te geven
dat er een nieuw bericht aankomt. Zo niet, dan raakt XOScript in de war.

```
Uit schrijf: ['Hello!'], stop.
```

Eerst wordt het bericht **schrijf:** naar het potloodsymbool gestuurd, gevolgd door
**stop**. Zonder de komma zou XOScript denken dat je
**stop** naar **tekst** **Hello!** wilt sturen, een zinloze bezigheid.

De verwerkingsvolgorde van berichten is als volgt: van links naar rechts;
begin met berichten tussen haakjes, gevolgd door unaire berichten. Daarna
binaire berichten en tot slot sleutelwoordberichten. Zie het voorbeeld
hieronder:

```
Uit schrijf: 0.5 afgerond + (2 - 1), stop.
```

XOScript leest altijd van links naar rechts: eerst wordt het bericht **schrijf:**
naar Uit gestuurd, gevolgd door het bericht **stop**. Binnen het
argument zelf leest XOScript ook van links naar rechts, dus eerst **0.5 afgerond**
en dan **+**.

{{note}}
Het bericht stop voegt een regeleinde toe aan de tekst.
De naam van dit bericht is geïnspireerd op telegraafsystemen.
In berichten in telegraafsystemen 
werd vaak het woord STOP gebruikt om het einde van een zin aan te geven
(omdat leestekens onbetrouwbaar of duur waren).
{{/note}}

Bovendien gaat **afgerond** voor **+**, omdat het een
**unair bericht** is. Vanwege de haakjes wordt **2 - 1** eerst
berekend, waarna **1** wordt opgeteld bij het resultaat van **0.5 afgerond** (1).

Het hele proces levert het resultaat **2** op, wat ook het geschreven
antwoord is. Na de komma volgt het bericht stop, dat de cursor
naar een nieuwe regel verplaatst. Uiteraard leer je de verwerkingsvolgorde
van XOScript-programma's het best begrijpen door te oefenen.

Het is goed om op te merken dat witruimte in XOScript, anders dan in veel andere
programmeertalen, een wezenlijk onderdeel van de syntaxis is. Vooral
bij binaire berichten kan witruimte voor
verwarring zorgen. Gebruik altijd een spatie na een binair bericht. Je kunt
een getal niet direct aan het bericht vastplakken, bijvoorbeeld: 

```
3 + 2
```

is anders dan 

```
3 +2
```

Het eerste voorbeeld (**3 + 2**) stuurt het
bericht **+** naar het getal **3**, met als argument het getal **2**. Het
resultaat is in dit geval **5**. In het tweede voorbeeld (**3 +2**)
wordt het unaire bericht **+2** naar het getal **3** gestuurd. Afhankelijk van de
context kan dat een heel ander resultaat opleveren.

## Niet-bestaande methoden

Een bericht naar een object sturen roept de functie aan die
onder die berichtnaam aan dit object is gekoppeld. Als je een bericht stuurt
dat niet wordt begrepen, negeert het ontvangende object je bericht
en geeft het in plaats daarvan een referentie naar zichzelf terug voor verdere communicatie.
Dit heet tolerante berichtoverdracht.

Voorbeeld:

```
Uit schrijf: Object blah, stop.
```

Dit geeft geen fout. Het drukt gewoon de tekst **Object** af.


## Programmaverloop

In XOScript zijn geen aparte grammaticaregels nodig voor *lussen* en
*als-constructies*. Een als-opdracht is gewoon een eenvoudig bericht **ja:** of **nee:**
aan een **Ja**-object of een **Nee**-object:

```
2 even? ja: {
	Uit schrijf: ['Two is an even number'], stop.
}.
```
In het vorige voorbeeld wordt het bericht **ja:** naar **Ja** gestuurd (het
antwoord op de vraag: is 2 een even getal?). Als argument wordt een extra
codefragment meegestuurd: een **Functie**-object. Deze functie schrijft op
het scherm dat 2 inderdaad een even getal is.

Ook voor een *lus* zijn geen aparte schrijfregels nodig. Om
een codefragment drie keer uit te voeren, stuur je eenvoudig **\*** met argument
**3** naar die **Functie**:

@test5

In dit codefragment is **i** de index. De eerste keer dat de Functie
wordt uitgevoerd, is **i** dus 0, de volgende keer is **i** = 1, enzovoort.

Laten we nog een voorbeeld bekijken. Als er een omrekentabel moet worden
afgedrukt van *kJ* (kilojoule) naar *kcal* (kilocalorie) in stappen van 100,
zie dan hieronder voor de juiste notatie:

@test599

Hier wordt het nummer van de huidige regel doorgegeven aan de parameter
**:line**. Aan het begin van een functie worden de functieparameters
gedefinieerd. Ongebruikte parameters blijven leeg (**Niets**). Parameters staan
altijd aan het begin van de functie, direct na de openingsaccolade,
en worden voorafgegaan door een dubbele punt.

Het bericht **zolang:** is een combinatie van een *lus* en een *voorwaarde*.
Twee functies kunnen met het bericht **zolang:** aan elkaar worden gekoppeld. De ontvangende functie
blijft draaien totdat de functie na de dubbele punt een negatief
resultaat geeft. Voorbeeld:

@test600

In het hierboven getoonde codefragment wordt **1** bij **x** opgeteld zolang
**x** kleiner is dan **5**. Wanneer dat niet meer het geval is, antwoordt de tweede
functie met **Nee**, waardoor de uitvoering van de
eerste functie stopt. Merk op dat **x** buiten de
functie is gedefinieerd en een globale variabele is. Raadpleeg het hoofdstuk over Functies
voor meer informatie over scopingregels.

## Tekstinterpolatie

De *kJ/kcal*-lijst zou er
netter uit kunnen zien. Bij voorkeur ziet de lijst er als volgt uit:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Wanneer je de gewenste uitvoer omzet in een sjabloon, zou de notatie
kunnen zijn:

```
number1 kJ ➞ number2 kcal
```

Dit betekent dat **number1** staat voor de kJ-waarde en **number2** voor de
kcal-waarde. Zo werkt tekstinterpolatie in XOScript. Er zijn
in XOScript geen aparte grammaticaregels voor nodig. Stuur simpelweg
het woord dat moet worden vervangen naar de tekst, met de vervangende tekst
als argument:

```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

Het resultaat:

```
100 kj ➞ 23.9 kcal
```

Deze vervangingsregel werkt voor elk niet-gedefinieerd bericht dat door
een **tekst**-object wordt ontvangen. Elk bericht dat niet door het
**tekst**-object wordt herkend, wordt als volgt geïnterpreteerd: *vervang de berichttekst
door de tekst in het berichtargument.* Je kunt het
programma als volgt aanpassen:


@test601


Om verwarring te voorkomen over welk bericht wel of niet als
vervanging kan worden gebruikt, kun je het best een sjabloonmarkering zoals &lt; &gt;
invoeren voor tekstdelen in het sjabloon die
moeten worden vervangen.

## Retourwaarden

Om een bericht te beantwoorden, wordt de retourpijl
(*<-*) gebruikt. Het volgende voorbeeld laat zien hoe je een taak maakt
om een percentage te berekenen:

@test602

Nadat de taak is gedefinieerd en aan de variabele **percentage** is toegekend,
wordt het bericht **toepassen:en:** gestuurd met de argumenten **100** en **7**.

Dit voert de taak uit op **100** en **7**, oftewel 7% van 100.
Met de retourpijl wordt het antwoord vanuit de taak teruggegeven
aan het hoofdprogramma.

## Uitbreiden

Hoewel deze code geldig is, heeft hij een nadeel,
omdat je de volgorde van de argumenten moet onthouden. Dus waarom
schrijf je het niet zo: *7 percent of: 100 *? Dat ziet er een stuk
*natuurlijker* uit. Om dit mogelijk te maken, moeten we het ouderobject van
**7** aanpassen, namelijk het object **Getal**, zodat het het
bericht **percent of:** begrijpt. Dat bereik je door **bij:doen:** naar
het object Getal te sturen, zoals hieronder:

@test603

Omdat het percentage in dit geval het getal zelf is, verwijzen we naar zelf,
het sleutelwoord *zelf*. Kortom, het symbool zelf betekent: *stuur dit
bericht naar mijzelf*.

# Objecten

{{messages}}

Naast het aanpassen en uitbreiden van bestaande objecten kun je ook zelf
nieuwe objecten maken, simpelweg door het bericht **nieuw** te sturen. Stel dat je
een factuurobject wilt maken dat een doorlopende
nummering afdwingt; in dat geval heb je eerst een factuurobject nodig.

Omdat elk object afstamt van een ander object, dat op zijn beurt
uiteindelijk voortkomt uit het basisobject van alle objecten, Object genaamd,
moet je kiezen op welk van die andere objecten je
nieuwe object gebaseerd wordt. Je nieuwe object erft alle eigenschappen van
het object waarop het gebaseerd is, dus van het object waarnaar het bericht **nieuw**
oorspronkelijk werd gestuurd.

In dit voorbeeld gaat de voorkeur uit naar een vrij neutraal object, een zonder al te
veel geërfde eigenschappen. Dat maakt de keuze makkelijk, want in dat
geval kan het nieuwe object gebaseerd worden op het basisobject zelf, namelijk
**Object**. De notatie van het beoogde factuursysteem is dan als
volgt:

@test604

Het huidige factuurnummer wordt in het object opgeslagen; daarom staat het
sleutelwoord **eigen** ervoor. Dit heet een *eigenschap*;
meer details volgen nog.

Sommige bedrijven willen het jaartal graag in de factuurnummers
opnemen. In dat geval kun je een nieuw factuurobject maken dat gebaseerd is op een
eerder factuurobject, maar dat de gebruiker de mogelijkheid biedt
een bepaald jaar op te geven:

@test605

Het is niet nodig de implementatie van het bericht **getal**
opnieuw te schrijven, omdat deze wordt geërfd van het eerder geschreven **factuurobject**;
oude code kan dus worden hergebruikt. XOScript kent geen concepten
zoals klassen en andere verwante concepten. Dit betekent dat objecten
uitsluitend van andere objecten kunnen erven, ook wel *prototypische
overerving* genoemd.

Dan nu terug naar eigenschappen. Objecteigenschappen zijn alleen benaderbaar
van *binnen de objecthiërarchie*, dus deze eigenschappen
zijn niet waarneembaar voor andere objecten.

Anders dan in andere programmeertalen zijn alle eigenschappen van objecten
uitsluitend zichtbaar voor het object dat de eigenschap heeft gemaakt en voor
afgeleide objecten. 

Een veelgebruikte techniek is om een object te gebruiken als een soort *blauwdruk*,
zoals bijvoorbeeld het geval is bij de eerder besproken facturen.
Een ander goed voorbeeld is het **Point**. Stel dat je een
computerprogramma maakt dat berekeningen uitvoert met punten op een kaart. Je
kunt dan het object **Point** ontwikkelen met als eigenschappen een
x-coördinaat en een y-coördinaat, die via berichten beschikbaar worden gesteld aan de
buitenwereld:

@test606

Het bericht **=** vergelijkt de twee punten met behulp van het bericht **en:**. De
eerste vergelijking levert een **Ja** of een **Nee** op. Dit zijn booleaanse
objecten. Als je het bericht **en:** naar een Ja-object stuurt en het
argumentobject na de dubbele punt is eveneens **Ja**, dan krijg je
als antwoord weer **Ja**. Als een van beide **Nee** is, krijg
je het antwoord **Nee**. Merk op dat het ene punt de coördinaten van het
andere niet kan lezen. Je moet een bericht naar het andere punt sturen om
deze gegevens op te vragen: **x-coordinate** en **y-coordinate**. Zoals
al is uitgelegd, zijn eigenschappen immers alleen opvraagbaar van binnen
de objectfamilie zelf. 

Merk op dat hier het bericht **=** wordt gebruikt om de vergelijking van de punten
uit te voeren. Er had evengoed een ander bericht gebruikt kunnen worden, zoals
**is:** of **equal:**, maar het hergebruiken van het teken **=** leek
in dit geval passend.

## Overerving

Je kunt eerder geschreven code hergebruiken om een hiërarchie
van objecten te maken. Bijvoorbeeld:

```
>> Animal := Object nieuw.
>> Dog := Animal nieuw.
>> Poodle := Dog nieuw.
```

In dit geval erft **Dog** al het gedrag en alle eigenschappen
van **Animal** en erft het object **Animal** op zijn beurt al het gedrag van
**Object**, het basisobject van alle objecten.


## Overschrijven


In het volgende voorbeeld wordt een nieuw soort lijst gemaakt:
**Combination**, waarin elk element gegarandeerd uniek is. De
functies van de lijst worden via overerving hergebruikt:

@test607

Zie hoe de tweede **red** uit de lijst wordt geweerd.

Soms kan het nodig zijn gedrag van een object te overschrijven.
Bijvoorbeeld wanneer bij het optellen van getallen rekening moet worden gehouden met
maateenheden. In het volgende voorbeeld wordt het object **Size**
gemaakt. Dit object geeft een getal terug dat bij het optellen
rekening houdt met de eenheid van het getal dat wordt opgeteld. Het object **Getal**
controleert of het om *inches* of *foot* gaat. De programmacode
zou er zo uit kunnen zien:

@test608

## Recursie

In het vorige voorbeeld wordt het plus**teken** overschreven. Merk op
dat de uiteindelijke optelling toch nog moet worden uitgevoerd, wat in feite
op de volgende regel gebeurt:

```
>> answer := zelf + (getal x factor).
```

Hoe begrijpt XOScript nu dat dit plus**teken** verwijst naar
de oorspronkelijke logica van het optellen?** Een andere interpretatie
zou bijvoorbeeld kunnen zijn dat XOScript steeds hetzelfde bericht naar hetzelfde
object stuurt, wat op zijn beurt tot een **oneindige lus** zou leiden. Dat is
uiteraard niet de bedoeling. Zodra je een bericht naar een object stuurt
dat exact dezelfde code zou uitvoeren, begrijpt XOScript
in dit geval dat het onderliggende, overschreven bericht wordt bedoeld. Je
programma is dus automatisch beschermd tegen deze vorm van oneindige
lussen. Als het echter juist je bedoeling is dezelfde functie vanuit de
huidige functie uit te voeren, moet je eerst het bericht
**recursief** sturen. In dat geval is het resultaat een oneindige
lus. Er zijn echter nuttige toepassingen voor recursieve taken; stel
bijvoorbeeld dat je de faculteit van een bepaald
getal wilt berekenen. Voeg in dat geval simpelweg het bericht **factorial** toe aan
Getal:

@test609

Dit vraagt om recursie. De taak die aan het
bericht **factorial** is gekoppeld, moet namelijk binnen die functie opnieuw worden uitgevoerd.
Het is dus nodig de faculteitsfunctie aan te roepen vanuit de
faculteitsfunctie zelf. In de regel voorkomt XOScript dit,
vanwege het risico in een oneindige lus te belanden. Daarom
is het essentieel het bericht te laten voorafgaan door het woord **recursief**. Dit
gebeurt om XOScript duidelijk te maken dat het je
bedoeling is dezelfde taak uit te voeren, en dat je geen vergissing hebt gemaakt.

## Klasse-achtige objecten

Hoewel xoscript geen klassen biedt, is het nabootsen van klasse-achtig
gedrag triviaal. Overschrijf simpelweg het bericht nieuw.

```
>> Animal := Object nieuw.
Animal bij: ['nieuw'] doen: {
	<- zelf nieuw initialiseren.
}.

Animal bij: ['initialiseren'] doen: {
	eigen sound := ['?'].
	eigen legs  := 4.
}.
```

In het codefragment hierboven maken we een object met de naam Animal.
Dit object dient als *blauwdruk* voor allerlei soorten dieren,
zoals honden en katten. Het ouderobject Animal wordt geschreven
met een hoofdletter A om aan te geven dat dit een klasse-achtig object is.
Vervolgens overschrijven we het bericht nieuw door onze eigen nieuw-methode te schrijven.
In dit geval stuurt die het bericht nieuw naar zelf, gevolgd door het bericht
init. Omdat xoscript recursie standaard blokkeert, leidt dit niet tot
een oneindige lus. In plaats daarvan wordt het bericht nieuw naar het ouderobject
(Object) gestuurd, wat resulteert in een nieuwe instantie van Animal. We maken dus
een nieuw object, gebaseerd op hetzelfde object waarvoor we onze nieuw-methode hebben gemaakt.
Dit is volkomen geldig. Daarnaast sturen we het bericht init; dat zorgt ervoor
dat het object Animal standaardwaarden voor zijn eigenschappen heeft. Standaard
heeft een dier 4 poten en is het geluid onbekend (vandaar het vraagteken).
Om een nieuwe instantie van ons Animal te maken, kunnen we simpelweg zeggen:

```
>> a := Animal nieuw.
```

Nu krijgen we een nieuwe instantie van Animal met 4 poten, een onbekend geluid en
een init-methode. Net als in andere OOP-talen kunnen we ons Animal ook
uitbreiden:

```
>> Dog := Animal nieuw.
Dog bij: ['initialiseren'] doen: {
	zelf initialiseren.
	eigen sound := ['barks'].
}.
```

We kunnen dit eenvoudig testen door een tekst-methode toe te voegen:

```
Animal bij: ['tekst'] doen: {
	<- eigen legs tekst + eigen sound.
}.
```

Laten we alles samenvoegen:

@test13


Een object maken dat zich in een bepaalde begintoestand bevindt, is een
veelvoorkomend vraagstuk. Stel dat er een object **Rectangle** moet worden gemaakt
om omtrek en oppervlakte te berekenen. Een mogelijke notatie zou zijn:


```
>> Rectangle := Object nieuw.

Rectangle bij: ['area'] doen: {
	<- eigen lengte * eigen width.
}.
```

Het instellen van een lengte en breedte is uiteraard een voorwaarde. Daarvoor
kunnen de berichten **length:** en **width:** worden toegevoegd:


```
Rectangle bij: ['length:'] doen: { :lengte
	eigen lengte := lengte.
}.

Rectangle bij: ['width:'] doen: { :width
	eigen width := width.
}.

```

Deze rechthoek kan dan als volgt worden gebruikt:


```
>> rectangle := Rectangle nieuw length: 2, width: 3.
Uit schrijf: rectangle area.
```

Als het instellen van lengte en breedte echter wordt vergeten,
verschijnt er een foutmelding:

```
>> rectangle := Rectangle nieuw.
Uit schrijf: rectangle area.
```

geeft de volgende fout:

```
Sleutel niet gevonden: lengte
```

Om dit te voorkomen, is het beter dat een rechthoek
altijd een beginlengte en -breedte heeft, bijvoorbeeld 0. In dit
geval is het dus nodig het bericht **nieuw** te **overschrijven**.

@test610

Als we het bericht nieuw overschrijven, bootsen we in feite een **klasse** na.

De wereld van XOScript is gevuld met een verscheidenheid aan objecten die
vanaf het begin beschikbaar zijn voor je programma. In de volgende hoofdstukken
worden al deze kernobjecten besproken.

## Momentopnamen

Je kunt een object (samen met zijn huidige toestand) op schijf opslaan met:

```
myobject save-as: ['saved.bin'].
```

Om het object weer van schijf te laden:

```
>> myobject := Object load-from: ['saved.bin'].
```

Momentopnamen kunnen worden gebruikt om een bepaalde toestand op te slaan of om de prestaties te verbeteren.
Het laden van een momentopname vermijdt lexing, parsing en het opzetten van de applicatie.
Ook kunnen er in de toekomst extra prestatievoordelen worden ingevoerd
met momentopnamen, zoals optimalisatie van bepaalde patronen of het opsporen en
optimaliseren van veelgebruikte codepaden.

{{warning}}
Momentopnamen zijn een experimentele functie; gebruik ze niet in productie.
Compileer met -D EXPERIMENTS om experimentele functies te activeren.
{{/warning}}


@test712

# Het object Niets

{{messages}}

Het object Niets
staat voor leegte, of beter nog: de afwezigheid van informatie. Af en
toe krijg je dit object als antwoord op een bericht, wanneer
het resultaat **niets** is. De belangrijkste vraag die
je het object **Niets** kunt stellen, is: **Niets?**. Het
antwoord luidt altijd **Ja**.

```
Uit schrijf: Niets Niets?.
```

resultaat:

```
Ja
```

Elk ander object dan **Niets** antwoordt met **Nee**. Het
codefragment hierboven lijkt misschien wat filosofisch, maar het object **Niets**
heeft zeker uiterst praktische toepassingen. Je krijgt
bijvoorbeeld het object Niets als antwoord wanneer je vraagt om een
lijstelement dat niet bestaat. Je kunt het object Niets ook gebruiken
als je een variabele wilt declareren, maar nog geen waarde wilt opgeven.
In plaats daarvan **ken** je dan gewoon de speciale waarde **Niets** **toe**. In
XOScript is het niet toegestaan een variabele zonder waarde te declareren, zoals:


```
>> waarde.
```

In plaats daarvan moet je het volgende schrijven:

```
>> waarde := Niets.
```

@api_None_base

# Booleans

{{messages}}

Anders dan de meeste populaire programmeertalen op het moment van schrijven
kent XOScript slechts één enkel Ja-object en één enkel Nee-object.
Ter verduidelijking: telkens wanneer je **Ja** schrijft, betekent dat niet dat
er een nieuw object is gemaakt. Je gebruikt in plaats daarvan altijd een referentie. Dit
betekent dat wanneer je het volgende schrijft:

\>\> x := Ja.

de **x** verwijst naar het object **Ja**. Voorwaardelijke code en lussen
controleren ook deze referentie. In XOScript ligt de betekenis van **Ja** en **Nee**
niet vast. Een XOScript-programma raakt zelfs flink van slag door
een opdracht als deze:

Ja := Nee.

Het resultaat van zulke handelingen is niet gedefinieerd, maar het blijft een geldige
handeling en is daarom formeel toegestaan. Verder is er een object Boolean,
het basisobject van zowel **Ja** als **Nee**, aangezien beide
afgeleiden van dit basisobject zijn. Het object Boolean zelf heeft echter
geen praktische toepassing.

## Valkuilen

Wees voorzichtig met het gebruik van **en:** en **of:**

```
Uit schrijf: (Nee or: Ja or: Ja), stop.
Uit schrijf: (Nee of: Ja, of: Ja), stop.
```

Levert op

```
Nee
Ja
```
omdat het bericht **of:** maar 1 argument aanneemt. Het eerste bericht
stuurt **of:of:** naar Nee, dat niet bestaat, dus negeert het object
het bericht en geeft het zichzelf terug (Nee). De tweede regel daarentegen
stuurt **of:** gevolgd door nog een **of:** (met een schakelsymbool, namelijk een komma: ,).


@api_Boolean_base

# Getallen

{{messages}}

Telkens wanneer je een getal schrijft, bijvoorbeeld 9, -10 of 3,12, zet
XOScript dat getal achter de schermen om in een **Getal**-object. Je
kunt berichten naar dit Getal-object sturen, of je kunt het getal
aan een variabele toekennen en daarna berichten sturen:

```
10 even?

>> tenner := 10.
tenner even?

```

Beide notaties zijn geldig. Het object Getal reageert op de volgende
berichten...

De meeste van deze berichten spreken voor zich en laten je
wiskundige bewerkingen of vergelijkingen uitvoeren.

{{note}}
Merk op dat je ≤ ≥ ≠ × en ÷ mag gebruiken in plaats van hun ASCII-tegenhangers.
Dat is een kwestie van voorkeur.
{{/note}}

Het verschil tussen binaire wiskundige berichten (+) en
hun sleutelwoordvarianten (optellen:) is dat de eerste
een nieuw getal teruggeven, namelijk het resultaat van de bewerking, terwijl bij
de laatste het object zelf wordt gewijzigd. Dit wordt geïllustreerd in het
volgende voorbeeld:

@test597

In het bovenstaande voorbeeld is b = 4 en a = 3. Met **optellen: 2** wordt de waarde
van a met 2 verhoogd, terwijl **+ 3** een nieuw getal maakt dat
gelijk is aan a + 3. Hetzelfde geldt voor andere wiskundige bewerkingen, zoals
vermenigvuldigingen. Met het vermenigvuldigingsteken krijg je een
nieuw object als antwoord. Gebruik je het bericht **keer:**,
dan vermenigvuldig je het getal zelf.

Met het bericht **tussen:en:**, bijvoorbeeld in: **Getal
tussen: X en: Y**, krijg je een getal tussen X en Y. Op deze
manier kun je elk willekeurig getal genereren:

```
>> a := Getal tussen: 1 en: 10.
Uit schrijf: a, stop.
```

Vanaf versie 1.4 is de ingebouwde generator van willekeurige getallen in xoscript
cryptografisch veilig, voor zover wij weten.

Je kunt een **kwalificering** aan een getal koppelen, bijvoorbeeld **6
apples**. Elk bericht dat niet door een
getal wordt herkend, wordt als kwalificering beschouwd. Je kunt de kwalificering van
een getal opvragen met het bericht kwalificering:

Een kwalificering is in feite een Tekst-object dat bij het Getal-object
wordt opgeslagen. De kwalificering wordt ook achter het getal afgedrukt bij een
**schrijf:**-opdracht. Kwalificeringen kunnen bijvoorbeeld worden gebruikt om bedragen
in gemengde valuta op te tellen. Bij het optellen van de bedragen kun je
de kwalificeringen opvragen. Het volgende programmavoorbeeld illustreert dit
principe met een historische valutacalculator (omdat de wisselkoers
redelijk stabiel blijft!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Teksten

{{messages}}

Telkens wanneer een tekst tussen **blokhaken en aanhalingstekens** ['...'] wordt geplaatst,
maakt XOScript een nieuw tekstobject voor je aan. Zorg er wel voor
dat je de juiste aanhalingstekens gebruikt. Het aanhalingsteken aan het
begin van de tekst verschilt van dat aan het einde (zo kun je
het enkele aanhalingsteken gebruiken zonder het te hoeven escapen).

## UTF8

Teksten in xoscript bevatten meestal utf8-gecodeerde tekst. Hoewel
het technisch mogelijk is binaire of niet-utf8-inhoud in
een tekst te hebben, wordt aangeraden daarvoor blobs te gebruiken. Blobs worden
geleverd door de serverplugin (zie het hoofdstuk ffi).
In het algemeen worden blobs/ffi per plugin/platform
geleverd, omdat ze aansluiten op het platform
en de architectuur (ffi/blobs). De kern van de scripttaal probeert
zo platformonafhankelijk mogelijk te blijven.

## Typeconversie

Je kunt van elk object een kopie maken
met een ander type door de volgende berichten te gebruiken:

Bericht | Resultaat
------- | ------
getal   | Zet om naar een getal
tekst   | Zet om naar een tekst
bool    | Zet om naar een boolean
  
De volgende regels **gelden**:

bericht  | Niets     | Boolean            | Getal                 | Tekst     | Overig              
-------- | --------- | --------           | --------              | --------  | --------
bool     | Nee       | n.v.t.             | 0→Nee anders→Ja       | Ja        | Meestal Ja
getal    | 0         | Nee→0 Ja→1 | n.v.t.                    | ['n']→n | Meestal 1
tekst    | ['Niets'] | ['Nee']/['Ja'] | ['n']                 | n.v.t.    | Hangt ervan af

## Kopiëren

Waarden in XOScript worden altijd **als referentie** doorgegeven. In andere talen
hangt het af van het type waarde; in XOScript is er maar één manier:
als referentie. XOScript maakt nooit een kopie van een waarde. Om een object te kopiëren,
moet je het bericht **kopieer** sturen. 

@test611

Hier had je misschien verwacht dat de uitvoer Dolly zou zijn in plaats
van Donny. Dat is echter niet zo, omdat beide namen naar hetzelfde
object verwijzen. Bij het werken met een lus gebeurt iets vergelijkbaars:

@test612

XOScript gebruikt namelijk **altijd** referenties, dus bij **:quantity**
geeft de hierboven getoonde lus ook de referentie naar het element
in de lijst aan.

Om een object te kopiëren, moet je deze handeling
**expliciet** aangeven:

@test613

Door het unaire bericht **kopieer** naar een tekst te sturen, geeft het object
een kopie van datzelfde tekstobject terug. Op dezelfde manier kun je Getal-objecten,
booleaanse objecten, reeksen en lijsten kopiëren.

Je kunt ook je eigen implementatie van kopiëren definiëren; dat is zelfs
noodzakelijk als je je eigen objecten maakt. De standaardimplementatie
van kopieer voor een reeks maakt een ondiepe kopie: er wordt een
nieuwe reeks gemaakt met dezelfde elementen.

@test614

In dit geval wordt 4 alleen aan de kopie toegevoegd.
Omdat de kopie echter ondiep is, zijn de objecten in beide reeksen
dezelfde.

@test615

Als we dus aan elke naam in de kopie 2 toevoegen, wordt de oorspronkelijke
reeks ook beïnvloed.

Om dit te verhelpen, moeten we een **diepe kopie** maken. Zo'n kopieerhandeling
voor een reeks kan als volgt worden opgebouwd:

@test616

Let ook op het bericht recursief; dit bericht moet worden
gestuurd vóór het bericht kopieer.

Het is essentieel om te onthouden dat een kopie van een object
er weliswaar vaak hetzelfde uitziet als het origineel, maar in feite
nooit hetzelfde is. Het basisobject definieert een bericht **equal:**,
waarmee de identiteit van objecten kan worden vergeleken. Bekijk het
volgende voorbeeld:

@test617

## Impliciete conversie

XOScript gebruikt **impliciete conversie** om objecten om te zetten. Om bijvoorbeeld een
reeks op het scherm af te drukken, stuurt XOScript intern het bericht
*tekst* naar de reeks. Dit kan heel nuttig blijken als
je een reeks als door komma's gescheiden lijst wilt afdrukken. Het
bericht *tekst* kan worden overschreven: 

@test620

@api_String_base
@api_Format_base


## Serverteksten

De volgende Tekst-functies worden toegevoegd door de
serverplugin.

@api_String_server

# Functies

{{messages}}

Je kunt code groeperen tussen { en }; het wordt dan een functie.
In xoscript gebruiken we soms ook de term taak, of gewoon
codeblok.

Je kunt een functie uitvoeren door het bericht *start* te sturen.


```
{ Uit schrijf: 123, stop. } start.
```

Als je functie argumenten aanneemt, gebruik dan **toepassen:**.

```
{ :a Uit schrijf: a, stop. } toepassen: a.
```

Zie ook de voorbeelden hieronder.
Vanwege de eenvoudige architectuur kan een functie maar
één terugkeerpunt hebben. Om overhead of overmatige nesting van
voorwaarden te vermijden, kun je een procedure gebruiken (wat hetzelfde is als het
vermenigvuldigingsteken met argument 1 gebruiken):

```
{
  (a = 1) ja: { x := 1. }, afbreken.
  (a = 2) ja: { x := 2. }, afbreken.
} procedure.
```

Op deze manier wordt (a = 2) niet geëvalueerd als a = 1.
Bovendien heb je zo geen geneste ja-berichten nodig.
Wanneer je merkt dat je voorwaarden aan het nesten bent, denk dan
aan het bericht procedure. Het kan je code
makkelijker leesbaar maken.


Hier is een belangrijke valkuil:

```
{
	Nee nee: {
		Uit schrijf: ['End the loop.'].
	}, afbreken.
	
	Uit schrijf: ['Dont show me.'].

} procedure.

```

In dit geval wordt de tekst 'Dont show me' getoond,
omdat **afbreken** naar Nee wordt gestuurd. Als je een
afbreking wilt uitvoeren, moet die als bericht naar **Ja** worden gestuurd.
 

```
{
	Nee niet ja: {
		Uit schrijf: ['End the loop.'].
	}, afbreken.
	
	Uit schrijf: ['Dont show me.'].

} procedure.

```

Werkt zoals verwacht.

## Excepties

Excepties kunnen als volgt worden afgehandeld:

```
{ Task 1 } afhandelen: { Task 2 }, start.
```

Je kunt ook opzettelijk een fout in je programma laten optreden en
daarmee het afhandelingsblok activeren. Dit doe je door het
bericht **fout:** naar de huidige taak te sturen, zoals te zien is in de volgende
illustratie:

```
{
deze-taak fout: ['Whoops!'].
} afhandelen: { :mistake
Uit schrijf: mistake.
}, start.
```

## Waarden injecteren

XOScript biedt bij taken de mogelijkheid waarden te injecteren. Bekijk
de taak hieronder eens:

```
>> sending := {
	Newsletter aan: eigen recipient.
}.
sending gebruik: ['recipient']
waarde: ['info@recipient.org'].
sending start.
```


Deze illustratie toont een denkbeeldige taak die een nieuwsbrief verstuurt
naar een e-mailadres of **ontvanger**. Deze ontvanger kan van buitenaf,
voordat de taak wordt gestart, in de taak worden geïnjecteerd door het
bericht **gebruik:waarde:** naar de taak te sturen. Zo wordt de waarde van
**ontvanger** vooraf in de taak ingesteld. Deze waarde kan ook worden gewijzigd,
waarna de taak opnieuw kan worden uitgevoerd. Dit is een handige methode bij het gebruik van
taakobjecten.

## Lege functies

Lege taken zijn niet toegestaan. In theorie zou een lege taak er zo
uitzien: **{}**, maar XOScript beschouwt dit als een taalfout. Als je
een lege taak wilt declareren, kun je het object Niets gebruiken:

```
>> task := Niets.
```

Hoewel dit geen echte taak is maar een Niets-object, kan er toch
een start-bericht naar worden gestuurd:

```
>> answer := task start.
```

Dit is in feite hetzelfde als:

```
>> answer := Niets start.
```

Omdat het object **Niets** het bericht **start** niet herkent,
geeft het zichzelf terug als antwoord, waardoor het antwoord opnieuw **Niets** is.
Een lege taak is dus niet nodig. Dankzij het elegante
ontwerp van de programmeertaal XOScript kun je hiervoor simpelweg het object
Niets gebruiken.

## Dynamische scoping

Wanneer een Functie een variabele nodig heeft maar die niet kan vinden,
controleert hij de variabelen van de Functie die hem heeft **aangeroepen**,
en gaat hij zo verder omhoog in de keten van Functies.
Dit zoekproces gaat door totdat de variabele is gevonden.
Als de variabele dan nog steeds niet is gevonden, verschijnt er een foutmelding. Deze manier van zoeken naar
een variabele heet **dynamische scoping**.

Om dit principe te illustreren:

@test618

@api_Code_base

# Basisobject

{{messages}}

Het object met de naam **Object** is het basisobject van alle objecten in
XOScript en levert de kernfuncties van de taal. 

Het vaakst verstuurde bericht
is **bij:doen:**, dat de functionaliteit van een object uitbreidt. Dit
bericht wordt ontvangen door het basisobject, dat vervolgens de
opgegeven taak aan het bericht koppelt en zo het afgeleide
object uitbreidt.

## Vangnetmethoden

Normaal gesproken wordt een bericht dat niet overeenkomt met
een methode in het object genegeerd. Je kunt echter
zogenaamde **magische methoden** of **vangnetmethoden** opgeven die
worden aangeroepen als het object het bericht niet begrijpt.

Er zijn 4 vangnetmethoden beschikbaar. Elk bericht hoort bij
een bepaald aantal argumenten.

Vangnetbericht                            | Aantal argumenten
----------------------------------------- | -------------------
reactie:                                  | 0
reactie:argument:                         | 1
reactie:argument:argument:                | 2
reactie:argument:argument:argument:       | 3


@test619

## Programmatische berichten

In plaats van een bericht rechtstreeks naar een object te sturen, kun je het ook
via een variabele versturen. Daarvoor gebruik je het bericht
**bericht:argumenten:**. 

@test396

@api_Object_base

# Reeksen

{{messages}}

XOScript kent twee soorten verzamelingen: *reeksen* en *lijsten*.
**Reeksen** zijn opsommingen van objecten in een *vaste volgorde*. Lijsten hebben
geen volgorde, maar lijken op een legenda met een sleutel (of term) en de
bijbehorende waarde. Reeksen zijn vergelijkbaar met arrays (PHP, Java, C)
en lists (Python). Lijsten zijn vergelijkbaar met associatieve arrays (PHP) of
dictionaries (Python) in andere programmeertalen. Om een
nieuwe Reeks te maken, schrijf je:

```
>> fibonacci := Reeks nieuw.
```

Deze lege reeks kan worden gevuld met **toevoegen:** :

```
fibonacci toevoegen: 0.
fibonacci toevoegen: 1.
fibonacci toevoegen: 1.
fibonacci toevoegen: 2.
fibonacci toevoegen: 3.
fibonacci toevoegen: 5.
fibonacci toevoegen: 8.
fibonacci toevoegen: 13.
```

Als we de reeks naar het scherm schrijven:

```
Uit schrijf: fibonacci, stop.
```

Zien we:

```
Reeks ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

In plaats van toevoegen kun je ook ; gebruiken om elementen aan een reeks toe te voegen:


```
>> fibonacci := Reeks nieuw ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

De puntkomma's (;) zijn allemaal binaire berichten die een
waarde in de reeks plaatsen.

## Ketenen

Stel dat je een reeks hebt zoals:

```
>> x := Reeks nieuw ; 1 ; 2 ; 3.
```

Als je het eerste en het laatste element wilt verwijderen, dan zou je
bericht luiden:

```
x lknip rknip.
```

Helaas werkt de vorige notatie niet correct. Het
bericht **lknip** geeft het eerste element van de reeks terug, dat
op zijn beurt de ontvanger wordt van het bericht **rknip**. Het
bericht **rknip** wordt dus niet naar **x** gestuurd, maar naar 2. Een
mogelijke oplossing voor dit probleem is het maken van twee afzonderlijke
zinnen, zoals: 

```
x lknip.
x rknip.
```

Dit is echter nogal onpraktisch, vooral als je meer
dan twee elementen moet verwijderen. Daarom biedt XOScript voor dit soort situaties een
alternatieve berichtstructuur. In
**alternatieve** berichtstructuren worden de antwoorden van objecten genegeerd
en krijg je telkens opnieuw het ontvangende object terug als antwoord.
Een **alternatieve** berichtstructuur begin je door het
bericht **doen** naar een object te sturen, en de **alternatieve** berichtstructuur
kan worden beëindigd door het bericht **klaar** te sturen. In het
getoonde voorbeeld kan dit als volgt worden toegepast:

```
>> x := Reeks nieuw ; 1 ; 2 ; 3.
x doen lknip rknip klaar.
```

@api_List_collections

# Lijsten

{{messages}}

**Zowel Reeks als Lijst zijn verzamelingen. Anders dan een
reeks heeft een lijst echter **geen** volgorde. Een ander verschil tussen de twee
is dat een lijst uit paren van objecten bestaat. Het ene object fungeert als ingang (of
trefwoord) om het andere object te zoeken. Een goed voorbeeld van een
lijst is een prijslijst, zoals:


```
>> menu := Lijst nieuw
	zet: ['£5'] bij: ['apple pie'],
	zet: ['£6'] bij: ['carrot cake'],
	zet: ['£3'] bij: ['fudge'].
```

Net als bij een reeks wordt het bericht zet:bij:
gebruikt om een object aan een lijst toe te voegen. Het verschil is dat, anders dan bij
een reeks, twee objecten aan elkaar worden gekoppeld. Het eerste object is, net als
bij een reeks, het object dat je in een lijst opslaat. Het tweede
object is niet de positie binnen de verzameling, maar de **ingang**
waarmee het eerste object later kan worden opgevraagd. Kortom,
een lijst werkt een beetje als een woordenboek: aan de hand van het trefwoord
vind je de betekenis. Om bijvoorbeeld uit de
hierboven genoemde lijst de prijs van een fudge op te vragen:

```
>> price := menu bij: ['fudge'].
```

Je kunt ook de beknopte notatie gebruiken:

```
>> price := menu ? ['fudge'].
```

Als de ingangen die je gebruikt om objecten op te slaan geen spaties bevatten
(en niet botsen met andere vooraf gedefinieerde berichten),
kan ook de volgende notatie worden gebruikt:

```
>> menu := Lijst nieuw
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Ongetwijfeld leest de bovenstaande notatie wat natuurlijker.
Om de prijs van een
fudge op te vragen, kan de volgende vereenvoudigde notatie worden gebruikt:

```
>> price := menu fudge.
```

@api_Dict_collections

# Bestand

{{messages}}

Het object **Bestand** biedt basistoegang tot het bestandssysteem.
Met dit object kun je hele bestanden in één keer in een variabele inlezen,
of variabelen in één keer naar bestanden schrijven. Regel voor regel lezen
wordt ook ondersteund. Dit zijn de meest voorkomende bestands-I/O-bewerkingen
in een scripttaal. Geavanceerde bestandsbewerkingen vereisen het
gebruik van FFI via de serverplugin of een aparte IO-plugin.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Datum/tijd

{{messages}}

Voor een gestructureerde weergave van tijd en datum gebruikt XOScript het
object **Moment**. Wanneer een nieuw Moment-object op het scherm wordt afgedrukt, worden de
huidige datum en tijd getoond:

```
Uit schrijf: Moment nieuw, stop.
```

Dit kan iets opleveren als:

```
2020-10-10 12:16:39
```

Het is ook eenvoudig om de afzonderlijke tijdcomponenten uit te lezen. Als je
bijvoorbeeld alleen het huidige jaar hoeft te weten, kun je het bericht
**jaar** naar het moment sturen; het antwoord is dan een
Getal-object dat alleen het jaar bevat:

```
>> m := Moment nieuw.
Uit schrijf: m jaar, stop.
```

@api_Moment_system

# Programma/StdOut

{{messages}}

Het object Programma vertegenwoordigt de app die op dat moment draait. Dit object
biedt functionaliteit om systeemopdrachten uit te voeren, subprogramma's op te nemen,
argumenten te lezen en meer. Alle systeemgerelateerde functies dus.

## StdOut

Uit is het standaard uitvoerobject. Het heeft in feite twee methoden:
**schrijf:** en **stop**. Het bericht schrijf: wordt gebruikt om een tekst
naar stdout te sturen; het bericht stop drukt een regeleinde af.
In plaats van **stop** kun je ook \\n gebruiken.

Voorbeeld:

```
Uit schrijf: ['Hello World'], stop.
```

resultaat:

```
Hello World
```

## Modules/plugins

De wereld van XOScript kan worden uitgebreid met nieuwe systeemobjecten door
modules te installeren. Een nieuw systeemobject kan aan de wereld van
XOScript worden toegevoegd door het modulebestand (meestal een bestand met het achtervoegsel .so
) in de map mods te plaatsen. 

Wanneer je een bericht stuurt naar het object dat via de
pluginmodule beschikbaar wordt gesteld, wordt deze automatisch door XOScript geladen.

Je kunt ook zelf plugins schrijven. Plugins worden geschreven in de
programmeertaal C. Een voorbeeldplugin vind je in het broncodepakket
onder src/plugins/example.


## Reflectie

Er zijn verschillende manieren om het systeem
te verkennen tijdens de uitvoering van een programma. XOScript heeft een aantal methoden om
te achterhalen welke objecten aanwezig zijn en op welke berichten deze objecten
reageren. Ten eerste kun je elk object vragen van welk **type** het is,
maar typen zijn in XOScript kneedbaar en daardoor onbetrouwbaar.

Je kunt het object Programma ook vragen of een
bepaald object al in het programma aanwezig is:

```
Programma Tool ja: { ... }.
```

Bij een objectnaam
die uit één enkel symbool bestaat, kun je het best de
volgende notatie gebruiken om verwarring te voorkomen:

```
Programma zoek: ['X'], ja: { ... }.
```

Naast vragen over objecten kun je het
object Programma ook vragen stellen over berichten. Je kunt bijvoorbeeld vragen of het
object **Getal** het bericht **tussen:en:** kent, op de manier
die hieronder wordt geïllustreerd:

```
Programma Number: ['between:and:'], stop.
```

@api_Program_system

# Server

{{messages}}

De serverplugin in xoscript biedt functionaliteit om
applicaties aan de serverkant te maken. Om de serverplugin
te laden, gebruik je:

```
Server initialiseren.
```

Voor het gemak wordt ook aangeraden de bestanden
webtools.xo en template.xo te laden.

```
Programma gebruik: ['webtools.xo'].
Programma gebruik: ['template.xo'].

```

## Serverinstellingen

Je kunt de volgende serverinstellingen opgeven:

```
	# default values are given
	# so if you do not set anything these
	# values are used...

	Programma 
	instelling: ['max-postvelden']
	is: 40.

	Programma 
	instelling: ['max-contentlengte']
	is: 2000000. # 2MB

	Programma 
	instelling: ['max-time']
	is: 5000. # 5sec

```

## Hallo wereld

Hier is een heel eenvoudig webprogramma dat je kunt gebruiken met een
standaard CGI-server zoals Apache2, NGINX, OpenHTTPD of een andere
bekende server.

```
#!/bin/xo

Server initialiseren.
Programma gebruik: ['webtools.xo'].

>> web-document := Webdocument nieuw.

web-document uitvoeren: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Als je het object Webdocument niet wilt gebruiken, is dat prima, maar
dan moet je de HTTP-headers zelf schrijven:

```
#!/bin/xo
Uit schrijf: ['Content-type: text/html; charset=utf-8 \n\n'], stop.
Uit schrijf: ['hello world!'], stop.
``` 

## Verzoek

Het object HTTP-Request kan worden gebruikt om GET-, POST-, COOKIE- en
UPLOAD-gegevens op te halen:

```
>> verzoek  := HTTP-Request nieuw.
>> search   := verzoek get: ['search']. # ?search=books
>> password := verzoek post: ['password']. # from form
>> selected := verzoek get-list: ['sel[]']. #?sel[]=1&sel[]=2
>> selected := verzoek post-list: ['sel[]'].
>> cookie   := verzoek cookie: ['session-id'].
>> upload   := verzoek upload: ['file'].
>> temppath := upload ? 1.
>> filename := upload ? 0.
```

## Maxpost/lengte

Het standaard maximum aantal postvelden is 40 en de standaard maximale
inhoudslengte is 2MB. Om dit per script anders in te stellen:

```
Programma instelling: ['max-contentlengte'] is: 1. 
Programma instelling: ['max-postvelden'] is: 1. 
```

{{note}}
Als de inhoudslengte het maximum overschrijdt, wordt het
proces beëindigd, omdat we er dan niet meer zeker van kunnen zijn
dat de payload veilig is.
{{/note}}

De limiet maxtime bepaalt de maximale tijd in ms
voor het lezen van stdin/postgegevens.

```
Programma instelling: ['max-time'] is: 5000. # 5sec
```

Dit geldt alleen voor het inlezen (I/O) van de post en voorkomt
aanvallen in de stijl van slowloris. Als je echt de
uitvoeringstijd van een bewerking wilt begrenzen, gebruik dan Programma maxtijd:.

## Databank

Het object Database kan worden gebruikt om MariaDB/MySQL te bevragen.
Om verbinding te maken met een databank:

```
>> db := Maria-DB nieuw host: ['localhost'],
	gebruikersnaam: ['xo'],
	wachtwoord: ['pass123'],
	databanknaam: ['xobase'],
	verbinden.

```

Om een record in te voegen, gebruik je:

```
>> zoekparameters := db query: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parameters: ( Reeks nieuw ; ['abc'] ; 12.35 ; 6 ). # parameterized queries

{  zoekparameters uitvoeren. db bevestigen. }
afhandelen: { :e db terugdraaien.  }, start.
```

Merk op dat xoscript *uitsluitend* met transacties werkt en nooit automatisch commit.
Als autocommit niet kan worden uitgeschakeld, krijg je een verbindingsfout.
Gebruik voor queries altijd parameterbinding en voeg gebruikersinvoer nooit direct
aan de SQL toe.

Haal het ingevoegde id als volgt op:

```
Uit schrijf: ['INSERTED: '] + zoekparameters insert-id, stop. # insert id
```

Om records op te halen:

```
>> zoekparameters :=
db
	query: ['SELECT * FROM book order by id desc limit 2'], 
	ophalen: { :row 
		Uit schrijf: row id + [' '] + row description + [': '] + row price, stop.
	}. # fetching rows

```

## Sessies

Voor persistentie kun je gegevens opslaan in en ophalen uit een sessieobject.
Maak eerst een nieuw **Webdocument**. Het object Webdocument brengt
het verzoek, de headers, de HTML en de sessie samen. Dat komt doordat je, wanneer je
met je browser een website bezoekt, alleen de HTML ziet. Maar het
volledige Webdocument bestaat ook uit **koppen** (headers). Zo
bevatten de meeste HTTP-antwoorden een header als Content-type:text/html om
de browser te vertellen dat de gegevens die volgen als HTML moeten worden weergegeven
(en bijvoorbeeld niet als bestand gedownload). Sessies zijn een manier om
gebruikersgegevens tussen verzoeken te bewaren. Om deze gegevens bij te houden, moeten we
een cookie instellen, en ook dit cookie wordt via een header ingesteld. Daarom
komt alles samen in het Webdocument (omdat dat het volledige
document is, met zowel de headers als de HTML of andere gegevens).


```
# First we make a new Web Document instance
>> web := Webdocument nieuw.

# Now we start a session, this will generate a Header for a cookie and
# create a file to store your data, associated with that cookie
>> session := web sessie-starten.

# Now we can treat session like a dict
session userid: 123.
```

Om de sessie te vernietigen (bij het uitloggen):

```
web sessie-vernietigen.
```

## Koppen

Met het Webdocument kun je ook andere bekende headers instellen.
Bijvoorbeeld als je de gebruiker naar een andere URL wilt doorsturen:

```
web ga-naar: ['/other.html'].
```

Onder de motorkap genereert deze opdracht ook de HTTP-header die
samen met je andere gegevens of HTML wordt meegestuurd om de browser opdracht te geven
naar het opgegeven doeladres te navigeren.

Om een eigen header toe te voegen:

```
web kop: ( 
	HTTP-Kop nieuw
	sleutel: ['Content-Length']
	waarde: 400
).
```

Om een 404-pagina te tonen:

```
web niet-gevonden: ['OOps..'].
```


## Sjablonen

Het standaard sjabloonsysteem is heel eenvoudig. Je hoeft geen
nieuwe sjabloonsyntaxis te leren. Bovendien zorgt de sjabloon-engine voor een echte scheiding
tussen presentatie en bedrijfslogica.

Om een sjabloon uit een bestand te maken:

```
>> tpl := web sjabloon: ['templates/ux.tpl'].
```

Het sjabloonsysteem gebruikt markeringen. 
Er zijn drie soorten markeringen: knipmarkeringen, plakmarkeringen en
plekmarkeringen. Het basisidee is heel eenvoudig: je knipt
gebieden uit die door knipmarkeringen worden aangeduid, en je kunt ze plakken op
gebieden die door plakmarkeringen worden aangeduid. In
plekmarkeringen kun je teksten injecteren.

Laten we bijvoorbeeld, uitgaande van het volgende sjabloon, het
juweel in het juwelenkistje leggen en er een prijskaartje aan hangen.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Dat doe je als volgt:

```
>> gem := tpl knippen: ['gem'], kopieer.
gem price: 99.
tpl plakken: gem bij: ['jewels'].
web uitvoeren: tpl opschonen.
```

De laatste regel stuurt het sjabloon simpelweg als tekst naar de client,
samen met de benodigde HTTP-headers.

Resultaat:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

Om door gebruikers geüploade bestanden veilig aan te bieden, kun je passthru gebruiken:

```
>> uploaded := ['smile.gif'].
Server doorgave: uploaded prefix: ['/uploads/images/'].
Programma einde.
```

Dit biedt de door de gebruiker geüploade inhoud aan met het juiste
mimetype. Alleen mimetypes op de witte lijst worden ondersteund:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF en SVG.
SVG-, ZIP- en GZIP-bestanden worden als download verstuurd, omdat een SVG
scripts kan bevatten die anders op jouw domein zouden worden uitgevoerd.
Deze methode voorkomt TOCTOU-aanvallen, path traversal, 
uitvoering van kwaadaardige code (injectie), symlinkaanvallen,
DDoS-aanvallen (bestandslimiet = 50MB), snifferaanvallen en 
diverse andere beveiligingsproblemen.


## JSON

Om een object als JSON te coderen:

```
>> json := ( JSON jsonify: ( 
	Lijst nieuw zet: ( 
		Reeks nieuw ; 1 ; 2 ; 3
	) bij: ['abc']
)).
```

Om JSON te decoderen naar een xoscript-object:

```
>> dict := ((JSON object: json) abc ? 1).
```

JSON met meer dan 500 niveaus van nesting wordt als ongeldig geweigerd.

Om een Lijst direct als json met de juiste headers uit te voeren:

```
web json: dict.
```


## Regex

Je kunt reguliere expressies gebruiken door een patroon te maken.
Bijvoorbeeld om de hrefs en targets van hyperlinks te vinden:

```
Patroon nieuw: ['href="([^"]+)" target="([^"]+)"'].
```

Pas het patroon nu als volgt toe op de onderwerptekst:

```
pattern overeenkomst: onderwerp doen: { :m :x .... }
```

Volledig voorbeeld:

```
>> onderwerp := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> pattern := Patroon nieuw: ['href="([^"]+)" target="([^"]+)"'].
>> result  := pattern overeenkomst: onderwerp doen: { :m :x
	Uit schrijf: m, stop.
	Uit schrijf: x, stop.
	<- ['XXX'].
}.
Uit schrijf: result, stop.
```

## Netwerken

Gebruik het object Net om een webverzoek uit te voeren.
Het object Net verstuurt altijd een POST-verzoek, tenzij je Niets als
gegevens meestuurt; dan verstuurt het een GET-verzoek.


```
Net 
post: Niets 
to: ['https://redbeanphp.com'].
```

## Versleuteling

De serverplugin wordt geleverd met versleuteling op basis van XChaCha20 en Argon2.

Voorbeeld:

```
>> encrypted := Kluis versleutel: ['hello'] sleutel: ['world'].
>> decrypted := Kluis versleutel: encrypted sleutel: ['world'].
```

## Tokens

Om een cryptografisch veilig token van een bepaalde lengte te genereren:

```
>> mytok := Kluis token: 40.
```

Dit genereert een token van 40 tekens.

## Opmaak

Met het object Format kun je gegevens opmaken, bijvoorbeeld met opvulling of
voorloopnullen. Het gebruikt de printf-syntaxis.

```
>> fmt := Format nieuw: ['%06.0f'].
fmt toepassen: 56. # gives 000056
```

Een format kan één conversie bevatten, en die moet bij de waarde passen,
anders krijg je een fout:

- `toepassen:` met een tekst: `%s`
- `toepassen:` met een getal: `%f`, `%e`, `%g` of `%a`
- `toepassen-int:` met een getal: `%d`, `%i`, `%o`, `%u`, `%x` of `%c`

Waarden uit een verzoek zijn teksten. Om er een als getal op te maken,
zet je hem eerst om:

```
fmt toepassen: (verzoek get: ['amount']) getal.
```

## Encoders

Er zijn verschillende encoders en decoders beschikbaar.
De url-encoder bereidt een url voor op gebruik als link in HTML:

```
Server url-coderen: ['https://example.com?a=6&b=1 2'].
```

Om gebruikersinvoer veilig in je HTML te injecteren zonder risico op XSS-injecties,
gebruik je altijd:

```
Server html-coderen: ['<harmless>'].
```

Merk op dat de sjabloon-engine altijd html-codering toepast
als je naar een plekmarkering schrijft. Als je het sjabloonsysteem gebruikt,
hoef je dit dus niet te gebruiken.

## E-mail

Gebruik de bibliotheek mailtools.xo om een e-mail te versturen.

Voorbeeld:

```
Server initialiseren.
Programma gebruik: ['mailtools.xo'].

>> e-mail := HTML-E-mail nieuw.
>> img := e-mail bijvoegen: ( Bestand nieuw: ['myimage.png'] ).

e-mail
afzender: ['xo@xoscript.com'] naam: ['xo'],
aan: ( Reeks nieuw ; ['xo2@xoscipt.com'] ),
onderwerp: ['xoxo'],
berichttekst: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), versturen.

```



## Koppelen

Met het bericht koppel: kun je met behulp van libffi een externe bibliotheek aan
je programma koppelen. Zie voor details het hoofdstuk over ffi.


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

FFI wordt per platform/plugin geleverd, omdat het
aansluit op de onderliggende systeemarchitectuur, iets wat de
kern niet hoort te doen.
De serverplugin biedt een conforme ffi/blob-implementatie.
Standaard maakt de kern verbinding met het doelplatform
via stdin/stdout, beperkte bestands-I/O-diensten en de shell (Programma opdrachtregel:).
Aanvullende integratie wordt geleverd door ffi/blobs via applicatiegerichte
plugins zoals de serverplugin.

FFI staat voor Foreign Function Interface. Hiermee kun je functionaliteit gebruiken die door anderen in
andere programmeertalen is geschreven en die beschikbaar is via DLL-bestanden, SO-bestanden of Dylib-bestanden. Dat kunnen
allerlei functies zijn, en via deze methode is een enorm scala aan functionaliteit beschikbaar.
Laten we beginnen met een voorbeeld:

```
Server koppel: (
 Reeks nieuw ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Reeks nieuw ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s vrij.
```

Het resultaat van deze code is dat je het volgende op de opdrachtregel ziet:
FFI has 3 letters.
Nu denk je waarschijnlijk: "Dat is wel erg veel code voor iets zo eenvoudigs."
Hadden we dit niet gewoon met een Gui show-opdracht kunnen oplossen? Het antwoord is volmondig ja!
Maar dit is bedoeld als illustratief voorbeeld.
FFI wordt meestal voor complexere taken gebruikt, maar die zijn geen goede
voorbeelden, dus heb ik iets triviaals gekozen.

De argumenten voor de methode koppel:

- Argument #1: Het DLL- of SO-bestand dat je wilt gebruiken.
- Argument #2: De functie in dat bestand die je wilt koppelen.
- Argument #3: Een reeks met de namen van de gegevenstypen van de argumenten van de functie.
- Argument #4: De naam van het retourtype van de functie.
- Argument #5: De naam van het object waaraan je deze functie wilt koppelen (als het niet bestaat, wordt het
automatisch aangemaakt).
- Argument #6: Het bericht waaraan deze functie moet worden gekoppeld.

In het voorbeeld hierboven willen we de functie printf uit libc.so koppelen. De namen van de
gegevenstypen vind je in de documentatie van de software waaraan je koppelt. De beschikbare typen zijn:
void, pointer, float, double, int, uint, char, uchar, intX en uintX,
waarbij X 8, 16, 32 of 64 kan zijn.

Deze typen verwijzen naar het aantal bytes dat nodig is om de gegevens op te slaan. Voor printf koppelen we aan een
nieuw object met de naam Printf en het bericht template:number:. Je vertaalt de externe
functie naar het XOScript-dialect voordat je hem gebruikt. Het bericht template:number: verwacht als
eerste parameter een buffer met de sjabloontekst. Deze buffer maken we met een Blob-object, waarmee
je handmatig geheugen kunt toewijzen. Je bent er zelf verantwoordelijk voor dit geheugen daarna weer
vrij te geven met het bericht vrij.

Je kunt een geheugenblob op verschillende manieren vullen. In ons voorbeeld vullen we hem met tekst, dus gebruiken we het
bericht utf8: (UTF-8 is een codering om tekst om te zetten in bytes). Je kunt een blob ook vullen met
bytes:, waarbij je een reeks bytewaarden meegeeft. Om de inhoud van een blob te lezen, gebruik je van:lengte:.
Je krijgt de bytes dan terug als reeks. Je kunt met een Blob zelfs een C-struct maken via het
bericht struct:, waarbij je een reeks C-typen meegeeft. Dit kan nodig zijn wanneer je een C-functie
in een externe softwarebibliotheek aanroept die een pointer naar een struct verwacht.

{warning}
Je moet blobs zelf vrijgeven.
Blobs worden niet opgeruimd door de garbage collector.
{/warning}

Omdat blobs kunnen worden uitgewisseld met externe functies uit bibliotheken,
kunnen ze niet automatisch door de garbage collector worden opgeruimd (ze kunnen nog in gebruik zijn door 
externe functies, of die externe functies willen ze misschien zelf
vrijgeven). Daarom moet je blobs zo nodig zelf vrijgeven.

Om een blob vrij te geven, gebruik je:

```
myblob vrij.
```

Om een struct vrij te geven, gebruik je:

```
mystruct structvrij vrij.
```

Voor een struct moet je dus twee berichten sturen, structvrij en vrij, om
het geheugenblok vrij te geven.

@api_Blob_fficonnect
