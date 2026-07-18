# Basis

XOScript is een pure objectgeoriënteerde programmeertaal. Dat wil zeggen dat alles in XOScript een
object is. Er zijn verder geen andere datatypen. Een computerprogramma dat geschreven is in
XOScript kan grofweg uit drie soorten handelingen bestaan: toewijzen, berichten sturen en
antwoorden. De uitwisseling van berichten tussen objecten is het belangrijkste onderdeel van een
XOScript-programma.

## Variabelen

Om een variabele te
declareren, gebruikt u het aanwijspictogram: >>. Een naam van een variabele mag uit alle tekens
bestaan behalve <-, :=, spaties, punten, komma’s, dubbele punten, dubbele aanhalingstekens [''] en
boogjes (). Ook mag een variabelenaam geen meerdere regels beslaan. In plaats van een spatie mag
u voor de leesbaarheid wel de haarspatie gebruiken in een variabelenaam. Een variabele mag verder
niet beginnen met een getal of een minteken.

Hier zijn voorbeelden van geldige variabelen:

```
>> wachtwoord := ['Geheim'].
>> ♡♡♡ := 3.
>> $ := ['dollar'].
>> +plus := Ja.
>> wachtwoord-van-gebruiker := ['Pssst!'].
```

Ongeldige namen zijn bijvoorbeeld:

```
>> -123 := ['Negatief getal'].
>> wachtwoord van gebruiker := ['Geheim'].
>> wachtwoord.van:gebruiker := ['Geheim'].
>> ,x := 10.
```

Nadat een variabele is gedeclareerd, kan deze vrijelijk worden gebruikt. U hoeft het
aanwijspictogram dus alleen bij de eerste keer dat u de variabele gebruikt (de declaratie) te
gebruiken. U mag dus niet zomaar beginnen met het toewijzen van een waarde aan uw variabele (x
:= 2), u moet de variabele eerst declareren (>> x := 2). Eenmaal gedeclareerd mag u de waarde
wel wijzigen zonder aanwijspictogram (>> x := 2. x := 3.). Let erop dat u verplicht bent om
bij het declareren van een variabele een waarde toe te kennen. In tegenstelling tot andere
programmeertalen mag u geen variabele declareren zonder waarde. U dient elke variabele expliciet
te voorzien van een beginwaarde. U mag de variabele wel initialiseren met het Niets-object als u dat
wilt, in dat geval kan de variabele beschouwd worden als zijnde leeg (>> x := Niets.).

## Objecten

XOScript ‘denkt’ in objecten. Alles is een object. Alle getallen, teksten en stukken code. Getallen
zoals 1, 2, 100, -999 en 1,234 zijn Getal-objecten. Teksten tussen aanhalingstekens zijn Tekstobjecten.
Stukken code die gegroepeerd zijn door middel van accolades {…} zijn Functie-objecten.

Objecten zoals getallen en teksten stammen altijd af van een moederobject. Alle getallen zijn
bijvoorbeeld afgeleid van het object Getal. Alle stukken code van Functie. Alle teksten van Tekst.
Deze objecten stammen, op hun beurt weer af van Object, dit is het moederobject van alle objecten.

## Berichten

U schrijft een XOScript-programma door berichten naar objecten te sturen. De algemene notatie voor
het sturen van een bericht naar een object is:

```
<object> <bericht>
```

Willen we bijvoorbeeld weten of het getal 2 een even getal is, dan kunnen we het bericht even?
sturen naar het object 2:

```
2 even?
```

Het antwoord dat we terug krijgen is Ja (ook weer een object). Onbekende berichten worden
meestal door objecten genegeerd, er komt dus geen foutmelding. Sommige objecten (zoals getallen
en teksten) reageren op een vooraf afgesproken manier op het ontvangen van een onbekend bericht
(hierover later meer). Bovenstaande operatie geeft als resultaat ook weer een object, het Ja-object.
Er zijn drie soorten berichten die u kunt sturen naar een object. Ten eerste is er het enkelvoudig
bericht, zoals hierboven, dat is een bericht zonder argumenten. Ten tweede is er het meervoudige
bericht, met één of meer argumenten:

```
>> x := Getal tussen: 1 en: 10.
```

In dit geval sturen we het bericht tussen:en: naar Getal, dit is het moederobject van alle getallen.
Het resultaat zal zijn, een willekeurig getal tussen 1 en 10 (eveneens een object). Ten derde is er het
tweevoudige bericht, dit berichttype bestaat altijd uit slechts één teken en heeft altijd precies één
argument:

```
2 + 3
```

Dit ziet eruit als een rekensom, maar in XOScript sturen we het bericht + naar 2, met als argument 3,
waarop we als antwoord 5 terugkrijgen. U schrijft tweevoudige berichten doorgaans zonder dubbele
punt, dit in tegenstelling tot meervoudige berichten, waarbij de argumenten altijd vooraf worden
gegaan door een dubbele punt (meervoudige berichten mogen wel, net als tweevoudige berichten uit
1 teken bestaan, dus het meervoudige bericht a: is toegestaan). We kunnen tweevoudige berichten
als volgt aaneenschakelen:

```
>> x := 3 + 2 - 1.
```

In het bovenstaande fragment sturen we eerst + 2 naar Getal-object 3, dat levert Getal-object 5 op,
naar dit getal sturen we vervolgens - 1. De oplettende lezer zal opmerken dat deze conventie in
strijd is met de rekenkundige volgorde van operatoren, dit is correct. XOScript negeert de
rekenkundige volgorde van bewerkingen ten faveure van de consistentie van het berichtensysteem.
De rekensom 2 + 3 * 5 geeft in XOScript dus het antwoord 25 en niet 17. Met boogjes kunt u de
volgorde veranderen: 2 + (3 * 5) geeft wel 17.
Sommige objecten geven zichzelf terug als antwoord op een bepaald bericht, dat is handig, want
daarmee kunt u het gesprek met dit object continueren door een vervolgbericht te sturen:

```
Uit schrijf: [' hallo ']
kern
hoofdletters.
```

Resultaat:

```
HALLO
```

We sturen hier twee berichten naar het Tekst-object, eerst verwijder omliggende spaties en daarna
hoofdletters. De nieuwe regel ertussen is voor de leesbaarheid en optioneel. Na een meervoudig
bericht moeten we in dit geval wel een komma gebruiken om aan te geven dat er een nieuw bericht
volgt, anders raakt XOScript in de war, dit is bijvoorbeeld het geval indien we het bericht schrijf:
wensen op te volgen met een volgend bericht:

```
Uit schrijf: ['Hallo!'], stop.
```

We sturen hier eerst het bericht schrijf: en daarna stop naar de pen. Zonder de komma zou XOScript
denken dat u stop naar Tekst Hallo! wilt sturen, een nutteloze exercitie.

In het vorige voorbeeld zouden we het stop-bericht ook met een komma toevoegen:

```
Uit schrijf: [' hallo '] kern hoofdletters, stop.
```

Met de komma hervat u dus de communicatiestroom met het eerdere object.
Nog een voorbeeld:

```
Uit schrijf: 1 + 2 stop.
```

Is niet goed, want u stuurt stop naar 2.

```
Uit schrijf: 1 + 2, stop.
```

Is wel goed, u stuurt stop naar de Pen.

De volgorde van verwerking van berichten is: van links naar rechts, berichten tussen boogjes eerst,
dan de enkelvoudige berichten, dan de tweevoudige berichten en tenslotte de meervoudige
berichten. Dus in het volgende voorbeeld:

```
Uit schrijf: 0.5 afgerond + (2 - 1), stop.
```

leest XOScript van links naar rechts, dus eerst wordt het bericht schrijf gestuurd naar de pen, daarna
het stop-bericht. Binnen het argument in het schrijfbericht leest XOScript van links naar rechts, dus
eerst 0,5 afgerond en dan de +. Bovendien is afgerond een enkelvoudig bericht, dus dit bericht
krijgt voorrang boven de +, vanwege de boogjes wordt 2 – 1 eerst uitgerekend en dan wordt 1
opgeteld bij het resultaat van 0,5 afgerond (1), zo verkrijgen we uiteindelijk het antwoord 2. Dit is
dan ook het antwoord dat wordt opgeschreven, na de komma volgt het stop-bericht waarmee de
cursor op een nieuwe regel wordt gezet. De beste manier om de volgorde van XOScript-programma’s
goed te doorgronden is ermee te oefenen.


Let op het gebruik van spaties, in tegenstelling tot veel andere programmeertalen spelen spaties een
belangrijke rol in XOScript. Vooral bij tweevoudige berichten kunnen spaties verwarrend zijn. U moet
een spatie gebruiken na een tweevoudig bericht, u mag niet direct een getal vastplakken aan het
bericht: 3 + 2 is iets anders dan 3 +2. Het eerste voorbeeld (3 + 2) is het bericht + naar getal 3 met
als argument het getal 2, het resultaat is 5. Het tweede voorbeeld (3 +2) is het enkelvoudige bericht
+2 naar getal 3. Aangezien +2 standaard niet is gedefinieerd in XOScript zal de uitkomst daarom
gelijk zijn aan 3 +2. Als een getal een bericht niet kent, zal het worden opgevat als kwalificering,
zoals ‘liters’ of ‘meters’ en de tekst zal bij het getal gevoegd worden. Meer hierover in hoofdstuk 3.
Indien u het bericht +2 wel gedefinieerd zou hebben dan zou de uitvoering van (3 +2) wel degelijk
een resultaat kunnen hebben, maar dat ligt dan aan de door u opgestelde definitie van het bericht,
dus als +2 bijvoorbeeld 1 zou optellen bij het ontvangende bericht zou u ervoor kunnen zorgen dat 3
+2 als antwoord 4 geeft!

Let op! Berichten mogen niet beginnen met een getal of minteken. Berichten mogen ook geen
speciale tekens bevatten zoals { }, dubbele punten, boogjes, punten of komma’s.

## Onbekende berichten

Het verzenden van een bericht naar een object roept de functie
aan die aan dit object is gekoppeld onder de naam van dat bericht.
Als u een bericht verzendt dat niet wordt begrepen, negeert
het ontvangende object uw bericht en retourneert in plaats daarvan
een verwijzing naar zichzelf voor verdere communicatie.

Dit wordt tolerante berichtoverdracht genoemd.

Voorbeeld:

```
Uit: Object blah, stop.
```

Dit geeft geen foutmelding. Het print simpelweg de tekst **Object**.

## Programmaverloop

Voor lussen en voorwaardelijke uitvoering van code (for en ifs) zijn in XOScript geen aparte
grammaticaregels nodig, een if-statement is niks meer dan het bericht ja: of nee: naar een 
Jaobject, of een Nee-object:

```
2 even? ja: {
	Uit
	schrijf: ['Twee is een even getal.'],
	stop.
}.
```

Ja/Nee-objecten noemen we ook wel beslissingsobjecten. Deze naamgeving is soms duidelijker
omdat het aangeeft dat we deze objecten gebruiken om het programma bepaalde beslissingen te
laten nemen. Net als andere programmeertalen, volgt een programma geschreven in XOScript een
bepaalde route en kent het vertakkingen. De gekozen paden binnen een programma worden voor
een groot deel bepaald door deze beslissingsobjecten. In dit geval sturen we het bericht ja: naar Ja
(het antwoord op de vraag of 2 een even getal is). Als argument sturen we een ander stukje code
mee, namelijk een Functie-object. Deze taak schrijft op het scherm dat 2 een even getal is.
Evenmin hebben we aparte schrijfregels nodig voor een lus, willen we bijvoorbeeld een stuk code 3
keer uitvoeren, dan sturen we * met argument 3 naar die code:

```
{ Uit schrijf: ['♣'], stop. } * 3.
```

Resultaat:

```
♣
♣
♣
```

Willen we bijvoorbeeld een omzettingstabel afdrukken van kj (kilojoules) naar kcal (kilocalorie) in
stappen van 100, dan schrijven we:

```
{ :regel
	>> aantal := regel * 100.
	Uit schrijf: aantal, stop.
	Uit schrijf: aantal * 0.239, stop.
} * 10.
```

Dit programma produceert de volgende lijst:

```
100
23.9
200
47.8
...
800
191.2
900
215.1
1000
239
```

Hierbij wordt het nummer van de huidige regel doorgegeven in de parameter :regel. Aan het begin
van een taak worden de parameters gedefinieerd. Ongebruikte parameters blijven leeg (Niets).
Parameters staan altijd aan het begin van de taak, direct na de openingsaccolade en worden
voorafgegaan door een dubbele punt.

Het zolang-bericht vormt eigenlijk een combinatie tussen een herhaling en een voorwaardelijke
uitvoering. Met het bericht zolang kunt u twee taken aan elkaar knopen. De ontvangende taak voert
zichzelf net zo lang uit totdat de taak na de dubbele punt een negatief resultaat geeft. In de praktijk
ziet dat er zo uit:

```
>> x := 0.
{ x optellen: 1. }
zolang: { <- x < 5. }.
Uit schrijf: x, stop.
```

Resultaat:

```
5
```

In het bovenstaande codefragment tellen we net zolang 1 op bij x todat x niet langer kleiner is dan
5, op dat moment antwoordt de tweede taak met Nee en wordt de uitvoering van de eerste taak
gestaakt.

##  Sjablonen

De kj/kcal-lijst uit het vorige hoofdstuk is nog niet zo netjes, liever zouden we iets zien als:

```
100 kj ➞ 23,9 kcal
...
```

Als we de gewenste uitvoer omzetten naar een sjabloon, dan zouden we dit kunnen noteren als:
getal1 kj ➞ getal2 kcal
Hierbij is getal1 dus de kj-waarde en getal2 de kcal-waarde. In XOScript is dit hoe
tekenreeksinterpolatie werkt. XOScript heeft geen aparte grammaticaregels nodig hiervoor, u stuurt
gewoon het te vervangen woord naar de tekst met als argument de vervangende tekst:

```
>> tekst := ['getal1 kj ➞ getal2 kcal']
getal1: 100,
getal2: 23.9.
```

Het resultaat:

```
100 kj ➞ 23.9 kcal
```

Deze substitutieregel werkt voor elk ongedefinieerd bericht dat ontvangen wordt door een Tekstobject.
Elk bericht dat het Tekst-object niet herkent, wordt begrepen als: vervang de tekst die het
bericht vormt door de tekst in het argument van het bericht.

Passen we nu ons programma aan, dan krijgen we:

```
{ :regel
	>> kj
	:= regel * 100.
	>> kcal := regel * 0.239.
	Uit schrijf: (
		['getal1 kj ➞ getal2 kcal']
		getal1: kj,
		getal2: kcal
	), stop.
} * 10.
```

Als er verwarring dreigt op te treden over welk bericht nu wel of niet gebruikt mag worden voor
substitutie, dan kunt u voor de zekerheid de te vervangen tekstsegmenten in het sjabloon vooraf
laten gaan door een betekenisloos teken, zoals de lozenge ⬧ (U+2B27, ALT+Z). In internationale
context is dit soms aan te raden.

## Respons

Tot nu toe hebben we berichten gestuurd naar objecten, maar nog nooit zelf repons gegeven. Om te
antwoorden op een bericht, gebruikt u het antwoordpijltje (<-). In het volgende voorbeeld maken we
een taak om een percentage te berekenen:

```
>> percentage := { :getal :procent
	<- getal / 100 * procent.
}.

percentage toepassen: 100 en: 7.
```


Nadat we de taak hebben gedefinieerd en toegewezen aan variabele percentage sturen we het
bericht toepassen:, met argumenten 100 en 7. Hiermee wordt de taak uitgevoerd, toegepast op 100
en 7. Zo nemen we 7% van 100. Met de pijl sturen we het antwoord vanuit de taak terug naar het
hoofdprogramma.

## Uitbreiden

Hoewel deze code geldig is, kleeft er een nadeel aan, we moeten namelijk de
volgorde van de argumenten onthouden. Waarom kunnen we het niet zo opschrijven: 7 procent
van: 100 ? Om dat mogelijk te maken moeten we het moederobject van 7, het Getal-object
aanpassen zodat het het bericht procent van: begrijpt. Dat doen we door bij:doen: te sturen naar
het Getal-object met als argument de uit te voeren taak:

```
Getal bij: ['procent-van:'] doen: { :getal
>> procent := zelf.
}.

<- getal / 100 * procent.
```

Het bericht bij:doen: wordt begrepen door Object, het moederobject van alle objecten. Op het
moment dat Object dit bericht ontvangt zal het het kindobject, in dit geval Getal, uitbreiden met de
opgegeven taak tussen de accolades {} en deze taak koppelen aan het bericht van onze keuze,
namelijk procent van:. U kunt dus de functionaliteit van objecten uitbreiden met hetzelfde
mechanisme als waarmee u de functionaliteiten aanspreekt: via berichten. Een taak welke deel
uitmaakt van een object wordt ook wel een ‘methode’ genoemd.
Omdat het percentage in dit geval het getal zelf is, verwijzen we naar zelf, het zelf symbool. Het
pictogram zelf betekent dus: stuur dit bericht naar mijzelf. Na het uitvoeren van bovenstaande
code, kunnen we zeggen:

```
Uit schrijf: (7 procent-van: 100), stop.
```

Het resultaat van deze operatie is natuurlijk 7.


# Objecten

Naast het aanpassen en uitbreiden van bestaande objecten, kunnen we ook zelf nieuwe objecten
maken, dat doen we door het bericht nieuw te sturen. Stel dat we bijvoorbeeld voor een
facturatiesysteem een factuurobject willen hebben dat een opeenvolgende factuurnummering
afdwingt, dan hebben we allereerst een factuurobject nodig. Omdat elk object afstamt van een ander
object en uiteindelijk van het moederobject van alle objecten genaamd Object, moeten we altijd
kiezen op welk van die andere objecten we ons nieuwe object gaan baseren. Ons nieuwe object
overerft alle functionaliteiten van het object waarop het is gebaseerd
(waarnaar we dus het nieuwbericht hebben gestuurd). In dit voorbeeld willen we graag een vrij neutraal object zonder al te veel
overerfde functionaliteiten, de keuze is dan makkelijk, in dat geval baseren we ons nieuwe object op
Object, het moederobject zelf. We kunnen ons facturatiesysteem in de dop dan zo schrijven:

```
>>factuur := Object nieuw.
	factuur bij: ['begin'] doen: {
	eigen nummer := 0.
}.
factuur bij: ['nummer'] doen: {
	eigen nummer optellen: 1.
	<- eigen nummer kopieer ruw.
}.
```

We gebruiken dit object als volgt:

```
factuur begin.
Uit schrijf: factuur nummer, stop.
Uit schrijf: factuur nummer, stop.
```

Uitvoer:

```
1
2
```

Het huidige factuurnummer is opgeslagen in het object, vandaar dat we er een sleutelpictogram
(eigen) voor zetten. We noemen dit een eigenschap, daar komen we zo op terug.

Sommige bedrijven gebruiken liever factuurnummers waarin het jaartal verwerkt is. We kunnen dan
een nieuw factuurobject maken dat gebaseerd is op ons eerdere factuurobject maar dat de gebruiker
ervan de mogelijkheid biedt een jaartal op te geven:

```
>> jaartalfactuur := factuur nieuw.
jaartalfactuur bij: ['begin:'] doen: { :jaargang
	eigen nummer := jaargang.
}.
```


Dit jaartalfactuurobject gebruiken we dan zo:

```
jaartalfactuur begin: 202000.
Uit schrijf: jaartalfactuur nummer, stop.
Uit schrijf: jaartalfactuur nummer, stop.
```

Resultaat:

```
202001
202002
```

## Overerving

U kunt een hiërarchie van objecten maken. Bijvoorbeeld:

```
>> Dier := Object nieuw.
>> Hond := Dier nieuw.
>> Poedel := Hond nieuw.
```

In dit geval overerft Hond al het gedrag van Dier en het Dier-object op zijn beurt overerft weer al
het gedrag van Object, het moederobject van alle objecten.

## Overscrhijving

In het volgende voorbeeld maken we een nieuw soort reeks: Combinatie, waarbij elk element
gegarandeerd uniek is. We hergebruiken de functies van de Reeks dankzij overerving:

```
>> Combinatie :=

Reeks nieuw.

Combinatie bij: ['toevoegen:'] doen: { :element
	(zelf zoek: element) nee: {
		zelf toevoegen: element.
	}.
}.
>> kleurcombinatie := Combinatie nieuw.
kleurcombinatie
toevoegen: ['rood'],
toevoegen: ['groen'],
toevoegen: ['blauw'],
toevoegen: ['rood'].
Uit schrijf: kleurcombinatie, stop.
```

In dit geval wordt de tweede rood niet opgenomen in de reeks:

```
Reeks ← ['rood'] ; ['groen'] ; ['blauw']
```

Soms willen we het gedrag van een object overschrijven. Bijvoorbeeld bij het optellen van getallen,
als we rekening willen houden met eenheden. In het volgende voorbeeld maken we een object
genaamd Afmeting. Dit object geeft een getal terug dat bij de optelling rekening houdt met de
enheid van het op te tellen getal, zo kijkt het Getal-object of het om meters of centimeters gaat. De
programmacode zou er zo uit kunnen zien:

```
>> Afmeting := Object nieuw.
Afmeting bij: ['is:'] doen: { :getal
getal bij: ['+'] doen: { :getal
>> eenheid := getal kwalificering.
>> factor := 1.
eenheid
geval: ['centimeter'] doen: { factor := 0,01.

}.
>> antwoord := zelf + (getal * factor).
antwoord meter.
}.

<- antwoord.

<- getal.
}.
```

We kunnen dit afmetingsgetal als volgt gebruiken:

```
>> plank := Afmeting is: 6 meter.
>> rand := Afmeting is: 50 centimeter.
Uit schrijf: plank + rand, stop.
```

Het resultaat:

```
6,5 meter
```

In het bovenstaande voorbeeld overschrijven we het gedrag van het plusteken. Maar uiteindelijk
moeten we natuurlijk nog wel de uiteindelijke optelling doen, dat gebeurt op deze regel:

```
>> antwoord := zelf + (getal * factor).
```

Hoe weet XOScript nu dat het + teken hier verwijst naar de originele logica van het optellen? Een
andere interpretatie zou namelijk kunnen zijn dat XOScript weer opnieuw hetzelfde bericht verstuurt
naar hetzelfde object en dat we in een eindeloze lus terechtkomen. Dat is natuurlijk niet de
bedoeling! Op het moment dat u een bericht verstuurt naar een object waardoor dezelfde code zou
worden uitgevoerd, weet XOScript dat u het achterliggende, overschreven bericht bedoeld. Uw
programma wordt dus altijd automatisch tegen deze vorm van eindeloze lussen beveiligd.
Wilt u daarentegen wel dezelfde taak uitvoeren vanuit de huidige taak, dan moet u eerst het bericht
recursief sturen naar het object waarnaar u hetzelfde bericht wilt sturen, in dit geval zou u dan in
een oneindige lus terechtkomen.

## Recursie

Stel dat u bijvoorbeeld van een getal de faculteit wilt berekenen, in dat geval voegt u het bericht
faculteit toe aan Getal:

```
Getal bij: ['faculteit'] doen: {
	>> antwoord := 1.
	(zelf > 0) ja: {
		>> dit-getal := zelf.
		>> volgende-getal := dit-getal - 1.
		antwoord := (dit-getal * volgende-getal recursief faculteit).
	}.
	<- antwoord.
}.
```

Hiervoor hebben we recursie nodig. De taak die gekoppeld is aan het bericht faculteit moet
namelijk opnieuw worden uitgevoerd binnen die taak. Dus we willen de faculteitstaak aanroepen
vanuit de faculteitstaak zelf. Standaard steekt XOScript daar een stokje voor, omdat u het gevaar loopt
om in een oneindige lus verzeild te raken. Om die reden moeten we het bericht vooraf laten gaan
door het woordje recursief. Hiermee informeren we XOScript van het feit dat het echt onze bedoeling
is om dezelfde taak opnieuw uit te laten voeren en we geen vergissing hebben gemaakt. De
volgende lus toont de faculteiten voor de getallen 1-10:

```
{ :x Uit schrijf: x faculteit, stop. } * 10.

1
2
6
24
120
720
5.040
40.320
362.880
3.628.800
```

Zonder het woordje recursief zou alleen de eerste vermenigvuldiging plaatsvinden.

## Klasse-objecten

Een veelvoorkomend probleem is dat we een object willen maken dat van begin af aan in een
bepaalde toestand verkeert. Stel bijvoorbeeld dat we een object Rechthoek willen maken waarmee
we omtrek en oppervlakte kunnen berekenen. We zouden dit als volgt kunnen schrijven:

```
>> Rechthoek := Object nieuw.
Rechthoek bij: ['oppervlak'] doen: {
<- (eigen lengte * eigen breedte).
}.
```

Voorwaarde is natuurlijk wel dat we een lengte en breedte instellen, hiervoor zouden we de
berichten lengte: en breedte: kunnen toevoegen.

```
Rechthoek bij: ['lengte:'] doen: { :lengte
eigen lengte := lengte.
}.
Rechthoek bij: ['breedte:'] doen: { :breedte
eigen breedte := breedte.
}.
```

We kunnen onze rechthoek vervolgens gebruiken:

```
>> rechthoek := Rechthoek nieuw lengte: 2, breedte: 3.
```

Het probleem is echter dat als we vergeten om een lengte en breedte op te geven, we een
foutmelding krijgen:

```
>> rechthoek := Rechthoek nieuw.
Uit schrijf: rechthoek oppervlak.
```

```
Onafgehandelde fout opgetreden.
Sleutel niet gevonden: lengte
#3 lengte (testje.ctr: 5)
#2 oppervlak (testje.ctr: 18)
#1 schrijf: (testje.ctr: 18)
```


Om dit te voorkomen zouden we eigenlijk liever willen dat een rechthoek altijd een lengte en
breedte heeft, bijvoorbeeld 0. In dat geval moeten we dus het nieuw bericht overschrijven.

```
Rechthoek bij: ['nieuw'] doen: {
>> rechthoek := zelf nieuw.
rechthoek lengte: 0.
rechthoek breedte: 0.
<- rechthoek.
}.
```

Op regel 2 ziet u dat we de echte nieuw weer aanroepen. We komen hier niet in een oneindige lus
terecht doordat XOScript ons hiertegen beschermt. Het achterliggende mechanisme hiervan hebben we
eerder besproken in hoofdstuk 4.4. Als we nu een nieuwe rechthoek maken, krijgt deze van begin af
aan de afmetingen 0 bij 0, op die manier kan er geen fout optreden bij het berekenen van de
oppervlakte:

```
>> rechthoek := Rechthoek nieuw.
Uit schrijf: rechthoek oppervlak.
```

```
0
```

```
>> rechthoek := Rechthoek nieuw lengte: 2, breedte: 3.
Uit schrijf: rechthoek oppervlak.
```

```
6
```

# Het Niets Object

Een ander bijzonder simpel object is het Niets-object. Dit object representeert leegte, of de
afwezigheid van informatie. Dit object krijgt u soms terug als antwoord op een bericht, als de
uitkomst niets is. De belangrijkste vraag die u aan het Niets-object kunt stellen is Niets?, het
antwoord is altijd Ja.

```
Uit schrijf: Niets Niets?.
```

```
Ja
```

Elk ander object dan Niets zal Nee antwoorden (tenzij u dit zelf aanpast). Bovenstaand
codefragment oogt enigszins filosofisch, toch heeft het Niets-object wel degelijk zeer praktische
toepassingen. U zult het Niets-object als antwoord krijgen als u bijvoorbeeld een element uit een
reeks opvraagt dat niet bestaat. Deze techniek wordt ook wel het Null object pattern genoemd. U
kunt het Niets-object ook gebruiken als u een variabele declareert en nog geen waarde wilt
toekennen, in plaats daarvan kent u dan de speciale waarde Niets toe.
Het is in XOScript niet toegestaan om een variabele te declareren zonder waarde:

```
>> waarde.
```

is dus niet toegestaan. In plaats daarvan schrijft u:

```
>> waarde := Niets.
```

# Beslissingsobject

In tegenstelling tot de meeste populaire programmeertalen op het moment van schrijven,
biedt Xoscript slechts één enkel True-object en één enkel False-object.
Om dit te verduidelijken: elke keer dat je **Ja** schrijft, betekent dit niet dat er een nieuw object wordt aangemaakt. In plaats daarvan gebruik je altijd een referentie. Dit betekent dat wanneer je het volgende schrijft:

```
>> x := Ja.
```

De **x** verwijst naar het **Ja**-object. Voorwaardelijke code en lussen controleren deze referentie ook.
In Xoscript is de betekenis van **Ja** en **Nee** niet vastgelegd. Sterker nog,
een Xoscript-programma raakt behoorlijk in de war door een
instructie als deze:

```
True := False.
```

Het resultaat van dergelijke acties is ongedefinieerd, maar het blijft een geldige
actie en is daarom formeel toegestaan. Bovendien is er een Booleaans
object, dat het basisobject is van zowel **Ja** als **Nee**, aangezien
beide afgeleid zijn van het basisobject. Het Booleaanse object zelf biedt echter geen praktische toepassing.

## Valkuilen

Wees voorzichtig met het gebruik van **en:** en **of:**,
als u meerdere wilt combineren gebruikt u de komma:

```
melk en: suiker, of: zoetje.
```

Zonder de komma zou het bericht **en:of:** verstuurd zijn, en
dat bestaat niet.

# Getallen

Telkens als u een getal opschrijft, zoals 9, -10 of 3,12, maakt XOScript daar achter de schermen een
Getal-object van. U kunt dan berichten sturen naar het Getal-object of u kunt het getal toewijzen
aan een variabele en daarna berichten sturen:

```
25 even?
```

```
>> geeltje := 25.
geeltje even?
```

Beide notaties zijn geldig.
Het Getal-object reageert op berichten zoals: > , ≥ ,< , ≤ ,= , ≠ , + , – , * , / ,tussen:en:, oneven?,
even?, optellen: ,’aftrekken:’, vermenigvuldigen met:,’delen door:’,’modulus:’, tot de macht:,
positief?, negatief?, afgerond, afgerond naar beneden, afgerond naar boven, vierkantswortel,
absoluut, tekst, ja of nee, ruw, kwalificering en kwalificering:.
De meeste van deze berichten spreken voor zich, zo kunt u rekenkundige operaties uitvoeren met
+ , – , * , / en vergelijken met > , ≥ , < , ≤ , = , en ≠. Het verschil tussen tweevoudige
rekenkundige berichten (+) en hun meervoudige varianten (optellen:) is dat u bij de eerste een
nieuw getal terugkrijgt dat de uitkomst is van de operatie, terwijl bij de laatste het object zelf wordt
aangepast. Het volgende voorbeeld illustreert dit:
>> a := 1.
>> b := a + 3.
a optellen: 2.
Uit schrijf: a, stop.
Uit schrijf: b, stop.
3
4

In bovenstaand voorbeeld is b = 4 en a = 3. Met optellen: 2 verhogen we de waarde van a met 2
terwijl we met + 3 een nieuw getal krijgen dat gelijk is aan a + 3. Hetzelfde verschil is van
toepassing op andere rekenkundige bewerkingen zoals vermenigvuldigen, gebruikt u het keerteken
dan krijgt u een nieuw object als antwoord, gebruikt u het bericht vermenigvuldig met: dan
vermenigvuldigt u het getal zelf.
Met het bericht tussen:en: als in: Getal tussen: X en: Y krijgt u een getal tussen X en Y. Op deze
manier kunt u een willekeurig getal laten genereren:

```
>> a := Getal tussen: 1 en: 10.
Uit schrijf: a, stop.
```

Aan een getal kunt u een kwalificering hangen, bijvoorbeeld: 6 appels. Elk bericht dat een getal niet
herkent, wordt beschouwd als een kwalificering. U kunt de kwalificering van een getal ophalen met
het bericht kwalificering:

```
>> bedrag := 6 muntjes.
Uit schrijf: bedrag.
Uit schrijf: bedrag kwalificering.
```

```
6 muntjes
muntjes
```

Een kwalificering is dus eigenlijk een Tekst-object dat bewaard blijft bij het Getal-object. De
kwalificering wordt ook afgedrukt achter het getal bij een schrijf:-opdracht. U kunt kwalificeringen
gebruiken om bijvoorbeeld bedragen in verschillende valuta op te tellen. Bij de optelling van de
bedragen vraagt u dan de kwalificering uit. In het volgende voorbeeldprogramma illustreren we dit
principe aan de hand van een historische valutacalculator, het voordeel hiervan is dat de wisselkoers
enigszins stabiel blijft ;-) .

```
Getal bij: ['+'] doen: { :aantal
	(aantal kwalificering = ['dukaten']) ja: {
		aantal vermenigvuldig-met: 5.
	}.
	zelf optellen: aantal.
}.
Uit schrijf: (7 florijnen + 3 dukaten), stop.
```

```
22 florijnen
```

In het bovenstaande codefragment passen we het +-bericht aan zodat rekening wordt gehouden met
de munteenheid, in ons voorbeeld is 1 dukaat evenveel waard als 5 florijnen. Het zelf-pictogram
duidt het object zelf aan: zelf hiermee kunnen we een bericht aan het object zelf sturen.

U kunt een kwalificering trouwens ook expliciet instellen met het bericht kwalificering::

```
>> x := 7 kwalificering: ['dukaten'].
```

# Teksten

Telkens als u een tekst tussen aanhalingstekens ['...'] zet, maakt XOScript voor u een nieuw Tekstobject.
U kunt berichten naar dit Tekst-object sturen, net zoals u berichten naar andere objecten kunt sturen.
Dat kan nadat u de tekst heeft toegewezen aan een variabele maar ook al direct daarvoor:

```
>> aantal-letters := ['Hallo'] lengte.
>> groet := ['Hallo'].
```

## Conversies

Soms krijgt u een getal terug in de vorm van een tekst.
Bijvoorbeeld als invoer van de gebruiker:

```
>> x := Programma vraag.
```

Het antwoord
komt als tekst in de variabele x.
Om van deze tekst een getal te maken, sturen we het bericht getal,
vanaf dat moment kunnen we getalberichten sturen. In het algemeen geldt dat u een kopie van elk
object kunt maken met een ander type. U gebruikt hiervoor de volgende berichten: getal, bool, tekst.

## Kopiëren

Met de := kunnen we objecten opslaan onder een bepaalde naam. We kunnen een object ook onder
meerdere namen opslaan. Houd u er rekening mee dat dit niet hetzelfde is als een kopie maken.

```
>> schaap := ['Dolly'].
>> kloon := schaap.
kloon
vervang: ['l'] door: ['n'].
Uit schrijf: schaap, stop.
```

```
Donny
```

Om een object te kopiëren moet u dit expliciet aangeven:

```
>> kloon := schaap kopieer.
```

Door het enkelvoudige bericht kopieer te sturen naar een Tekst-object zal deze antwoorden met een
kopie van dat Tekst-object. Op dezelfde manier kunt u Getal-objecten, Lijsten, Reeksen, Ja/Neeobjecten,
Reeksen, Lijsten en Moment-objecten kopiëren. Andere objecten kunt u niet zomaar
kopiëren. De reden hiervoor is dat het niet altijd duidelijk is hoe de kopieeractie moet worden
uitgevoerd, in dat geval dient u dit zelf te specificeren. In het geval van een reeks bijvoorbeeld, rijst
de vraag of subreeksen onderdeel moeten uitmaken van de kopie, en zo ja, hoe diep gaan we dan?
De standaard kopie-implementatie van Reeks maakt een oppervlakkige kopie.

## Impliciete conversie

XOScript converteert intern objecten.
Om een reeks af te drukken op het scherm, stuurt XOScript
bijvoorbeeld intern het bericht tekst naar de reeks. U kunt hier handig gebruik van maken. Stel dat
u bijvoorbeeld een reeks wilt afdrukken als een kommagescheiden opsomming, dan kunt u het
bericht tekst overschrijven:

```
>> som := Reeks ← 1 ; 2 ; 3.
som bij: ['tekst'] doen: {
	<- zelf samenvoegen: [','].
}.
Uit schrijf: som, stop.
```

```
1,2,3
```

Bij rekenkundige operaties op getallen wordt intern het bericht getal verstuurd. Zo kunt u
bijvoorbeeld een reeks maken die bij een rekenkundige operatie automatisch de som geeft:

```
som bij: ['getal'] doen: {
	>> totaal := 0.
	zelf elk: { :nummer :element totaal optellen: element. }.
	<- totaal.
}.
```

# Functies

U maakt een Functie door een reeks instructies tussen { en } te zetten.

```
{ :graden
	Uit schrijf: (graden * 1,8 + 32), stop.
} * 30.
```

We produceren deze reeks door de taak tussen de accolades {} te vermenigvuldigen met het getal
30.

```
>> graden := 0.
{
	Uit schrijf: (graden * 1,8 + 32), stop.
	graden optellen: 1.
} zolang: { <- (graden ≤ 30). }.
```

Bovenstaand fragment geeft dezelfde uitvoer, maar gebruikt een zolang-lus.
U kunt een functie ook  uitvoeren door het bericht *start* te verzenden.

```
{ Uit schrijf: 123, stop. } start.

```

Als uw functie argumenten accepteert, gebruikt u **toepassen:**.

```
{ :a Uit schrijf: a, stop. } toepassen: a.

```

Vanwege de eenvoudige architectuur kan een functie slechts
één retourpunt hebben. Om overhead of overmatige nesting voor
voorwaarden te vermijden, kunt u het bericht afbreken gebruiken
in combinatie met een procedure (wat hetzelfde is als het gebruik van
het vermenigvuldigingsteken met argument 1):

```
{

(a = 1) ja: { x := 1. }, afbreken.

(a = 2) ja: { x := 2. }, afbreken.

} procedure.

```

Op deze manier wordt (a = 2) niet geëvalueerd als a = 1.
Ook heeft u op deze manier geen geneste ja-berichten nodig.

Denk altijd aan het bericht van de procedure als u voorwaarden nestelt.
Het kan de code leesbaarder maken.

Hier is een belangrijke valkuil:

```
{
	Nee nee: {
		Uit schrijf: ['Einde van de lus.'].
	}, afbreken.
	Uit schrijf: ['Niet weergeven.'].
} procedure.

```

In dit geval wordt de tekst 'Niet weergeven' weergegeven.

Omdat **afbreken** naar Nee wordt gestuurd. Als u afbreken wilt uitvoeren,
moet dit als bericht naar **Ja** worden gestuurd.


```
{
	Nee niet ja: {
		Uit schrijf: ['Einde van de lus.'].
	}, afbreken.
	Uit schrijf: ['Niet weergeven.'].
} procedure.

``

Zal werken zoals verwacht.

## Uitzonderingen

Een alternatieve manier om de loop van het computerprogramma te beïnvloeden is door een stuk
code met afhandelingen te definiëren in het geval van een fout. Stel dat een budgetapplicatie het
maandelijks budget moet vaststellen op basis van een door de gebruiker opgegeven inkomen en het
aantal maanden.

```
>> budget := jaarinkomen / maanden.
```

Wat gebeurt er nu als het aantal maanden op de één of andere manier 0 blijkt te zijn? Dan krijgen
we een foutmelding:

```
Onafgehandelde fout opgetreden.
Deling door nul.
```

De eerste regel van het foutbericht geeft aan dat er zich een fout heeft voorgedaan die niet werd
afgehandeld door het programma. De tweede regel in de uitvoer vertelt waar het probleem hem
precies in zit: delen door nul is niet toegestaan. De eerste zin verraadt ook dat u dus een fout kunt
afhandelen. Dit is ook een vorm van voorwaardelijke uitvoering van code, alleen nu gaan we een
stuk code schrijven dat wordt uitgevoerd in het geval dat een ander stuk code een fout oplevert. 


Stel
dat we bijvoorbeeld het foutbericht willen aanpassen, dan doen we dat zo:

```
{
>> budget := jaarinkomen / maanden.
} afhandelen: {
	Uit schrijf: ['Mag niet!'], stop.
}, start.
```

In dit geval zal het resultaat zijn (bij 0 maanden):

```
Mag niet!
```

## Zichtbaarheid

U weet dat u een object kunt toewijzen aan een variabele, maar u moet wel eerst een plek in het
geheugen reserveren onder deze naam, dat doet u met het aanwijspictogram. Dit noemen we het
declareren van een variabele. In de voorgaande hoofdstukken hebben we dit allemaal al besproken.
Niet alle delen van het geheugen zijn overal zichtbaar, want in grote programma’s waarin u ook
code van derden verwerkt zou u anders bijna zeker in elkaars vaarwater terecht komen. Om die
reden worden deze geheugenplekken van elkaar gescheiden, hierbij vormen taken de scheidslijnen.
Er geldt dat een variabele die binnen een taak is gedeclareerd alleen zichtbaar is tijdens de
uitvoering van die taak en tijdens de uitvoering van alle taken die door deze taak worden gestart.
Als de taak waarin de variabele is gedeclareerd is afgelopen, wordt deze variabele vergeten. Bekijk
het volgende voorbeeld eens:

```
>> x := 9.
{ Uit schrijf: x.

} start.
```

Het bovenstaande programma drukt het getal 9 af op het scherm. Objectnaam x is buiten de taak
gedeclareerd en is dus overal zichtbaar, voor alle taken, dus ook wanneer we x als argument
meesturen aan het Pen-object. U kunt het gebied buiten de taak beschouwen als een soort
overkoepelende taak. Alle variabelen die u hier declareert zijn overal in het programma zichtbaar,
immers, alle taken vallen als het ware binnen deze overkoepelende taak. We noemen variabelen die
u buiten alle taken in het programma declareert ook wel globale variabelen vanwege hun globale
zichtbaarheid.

```
{ >> x := 9. } start.
Uit schrijf: x.
```

In dit geval krijgen we een foutmelding. Objectnaam x is namelijk vergeten zodra de taak is
afgelopen. Aangezien x is gedeclareerd binnen de taak is hij daarbuiten niet zichtbaar. In dit geval
leeft x dus exclusief binnen het kleine taakje dat we hebben uitgeschreven. Kijk nu eens naar het
volgende fragement, er komt geen foutmelding, maar welk getal gaat er op het scherm verschijnen?

```
>> x := 1.
{ >> x := 9. } start.
Uit schrijf: x.
```

Het juiste antwoord is 1, niet 9. Er zijn in dit geval twee plekken in het geheugen met de naam x.
Dankzij de afbakening tussen de taken storen ze elkaar niet. Tijdens de uitvoering van de taak is x
gelijk aan 9, en zodra die taak is afgelopen, wordt de andere x weer zichtbaar en is x gelijk aan 1.


Nu de lastigste versie:

```
>> y := { x := 2. }.
{ >> x := 1. y start. Uit schrijf: x. } start.
```

Wat gaat er op het scherm verschijnen, 1 of 2? Eerst reserveren we een plek in het geheugen onder
naam y voor een taak. In die taak wordt getal 2 opgeslagen onder de naam x. Deze taak wordt
echter niet gestart. Op de tweede regel maken we een nieuwe taak die meteen wordt gestart. In deze
nieuwe taak declareren we x. We reserveren dus een plek in het geheugen onder de naam x. Onder
de naam x slaan we vervolgens het getal 1 op. Op dat moment is x = 1. Dan wordt de taak met de
naam y gestart die we op de eerste regel van ons programma hebben geschreven. Tijdens de
uitvoering van die taak wordt het getal 2 opgeslagen onder de naam x. Kan dat? Het antwoord
hierop is: ja. De cruciale regel is hier namelijk tijdens de uitvoering. Hoewel taak y visueel gezien
niet binnen de taak op regel 2 valt, wordt taak y wel uitgevoerd tijdens de uitvoering van de taak op
de tweede regel. Dit betekent dat de 1 die in x zat, wordt overschreven met het getal 2. Dus op dit
moment is x = 2. Vervolgens is de taak y afgelopen en keert de uitvoering van het programma terug
naar de taak op de tweede regel, klaar om x af te drukken op het scherm. Maar wat zit er nu in x?
Functie y is immers afgelopen? Dat klopt, maar x is buiten y gedeclareerd, namelijk in de taak waarin
we nu bezig zijn, de taak op de tweede regel, dus x bevat nog steeds het getal 2 en dus wordt dit ook
zichtbaar op het scherm. Het mechanisme dat ik hier zojuist beschreven heb, wordt ook wel
Dynamic Scoping genoemd.

# Moederobject

Het object met de naam Object is de moeder van alle objecten in XOScript. Het moederobject
antwoordt op de volgende berichten: bool, getal, tekst, gelijk:, doen, klaar, geval:doen:,
bericht:argumenten:, bij:doen:, reageer:en…, leer:betekent: en recursief. Elk ander object is
afgeleid van dit object, zelfs het Niets-object.
Het meest gestuurde bericht is bij:doen:, hiermee worden de functionaliteiten van een object
uitgebreid. Dit bericht wordt opgevangen door het moederobject dat vervolgens de opgegeven taak
koppelt aan het bericht en hiermee het afgeleide object uitbreidt.

## Algemene berichten

Normaal gesproken wordt een bericht dat niet overeenkomt met
een methode in het object genegeerd.
U kunt echter zogenaamde **magische methoden** of **vangstmethoden**
specificeren die worden aangeroepen als het object het bericht niet begrijpt.

Er zijn 4 vangstmethoden beschikbaar.
Elk bericht komt overeen met een specifiek aantal argumenten.

Vangstmethode     | Aantal argumenten
------------------|-------------------
reageer:          | 0
reageer:en:       | 1
reageer:en:en:    | 2
reageer:en:en:en: | 3


## Programmatische berichten

In plaats van zelf een bericht te sturen naar een object kunt u dit ook doen via een variabele.
Hiervoor gebruikt u het bericht bericht:argumenten: Het volgende voorbeeld levert bijvoorbeeld
14 op (op zeer omslachtige wijze):

```
>> a := (Reeks ← 7).
>> b := ['optellen:'].
>> x := 7 bericht: b argumenten: a.
```

Uitvoer:

```
14
```

# Reeksen

XOScript kent twee soorten verzamelingen: reeksen en lijsten. Reeksen zijn opsommingen van
objecten met een vaste volgorde. Lijsten hebben geen volgorde, maar lijken meer op een
woordenboek, waarbij sprake is van een ingang (of term) en de bijbehorende betekenis (waarde).

Voorbeeld van het gebruik van een Reeks:

```
>> continenten := Reeks
~ ['Oceanië']
~ ['Amerika']
~ ['Azië']
~ ['Europa']
~ ['Afrika']
~ ['Antarctica']
~ ['Australië'].
continenten sorteren: { :a :b
<- a > b.
}.
Uit schrijf: continenten, stop.
```

```
Reeks ← ['Afrika'] ; ['Amerika'] ; ['Antarctica'] ;
['Australië'] ; ['Azië'] ; ['Europa'] ; ['Oceanië']
```

## Kettingbericht

Stel, u heeft een reeks:

```
>> x := Reeks ← 1 ; 2 ; 3.
```

U wilt het eerste en laatste element verwijderen. In dat geval zou u willen zeggen:

```
x
neem eerste
neem laatste.
```

Helaas gaat dat mis, het bericht neem eerste geeft namelijk het eerste element uit de reeks terug,
dat wordt dan dus de ontvanger van het bericht neem laatste. U stuurt het bericht neem laatste dus
niet naar x maar naar 2. Een mogelijke oplossing voor dit probleem is om er twee zinnen van te
maken:

```
x neem eerste
x neem laatste
```

Maar dat is natuurlijk onhandig, vooral als u meer dan twee elementen wilt weghalen. Voor dit soort
situaties biedt XOScript de aangepaste berichtstructuur. Bij een aangepaste berichtstructuur worden de
antwoorden van objecten genegeerd en krijgt u steeds als antwoord weer het ontvangende object
terug. U start een aangepaste berichtstructuur door het bericht doen te sturen naar een object en u
beëindigt de aangepaste berichtstructuur met het bericht klaar. In ons voorbeeld zouden we de
aangepaste structuur als volgt kunnen toepassen:

```
x
doen
neem eerste
neem laatste
klaar.
```

Let er wel op dat u afsluit met klaar anders komt u voor verrassingen te staan. 

# Lijsten

Net als Reeks is Lijst ook een verzameling. Om een lijst te maken gebruikt u het Lijst-object. In
tegenstelling tot een reeks is een lijst ongeordend. Een ander verschil met een reeks is dat een lijst
bestaat uit objectparen, hierbij fungeert het ene object als ingang (of trefwoord) waarmee het andere
object opgezocht kan worden. Een goed voorbeeld van een lijst is een prijslijst:

```
>> menu :=
Lijst nieuw
zet: ['€7,-'] bij: ['pannenkoek'],
zet: ['€10,-'] bij: ['appelpannenkoek'],
zet: ['€12,-'] bij: ['kaaspannenkoek'].
```

```
>> prijs := menu bij: ['kaaspannenkoek'].
>> prijs := menu ? ['kaaspannenkoek'].
```

Als de ingangen waaronder u objecten wilt opslaan geen spaties bevatten, dan mag u ook de
volgende notatie gebruiken om een lijst op te stellen:

```
>> menu := Lijst nieuw pannenkoek: ['€7,-'],
appelpannenkoek: ['€10,-'],
kaaspannenkoek: ['€12,-'].
```

Deze notatie leest waarschijnlijk natuurlijker omdat dit meer lijkt op een lijst zoals deze voor zou
kunnen komen in een document. Om de prijs van de appelpannenkoek op te vragen, kunnen we ook
gebruikmaken van deze vereenvoudigde notatie:

```
>> prijs := menu appelpannenkoek.
```

# Bestanden

U kunt bestanden lezen en schrijven met het Bestand-object. Hier volgt een voorbeeld:

```
>> inlezen := Bestand nieuw: ['adressen.txt'], lezen.

Bestand nieuw: ['sensordata.dat'], 
schrijf: data.
```

# Datum en Tijd

We kunnen een moment in de tijd beschrijven met een Tekst-object: 28-07-2020 15.14:39 maar dat
rekent wel lastig. Hoe tellen we hier bijvoorbeeld 5.30 bij op? We zouden de tekst kunnen
uitpluizen en omzetten naar diverse Getal-objecten, maar dat is allemaal vrij ingewikkeld. Daarom
biedt XOScript het Moment-object voor een gestructureerde representatie van datum en tijd.

```
>> m := Moment nieuw.
Uit schrijf: m jaar, stop.
```

Geeft ons het jaar...

```
2020
```


# Programma/Uitvoer

U kunt verschillende
XOScript-programma’s combineren door het bericht gebruik: te sturen.
Stel dat we bijvoorbeeld 2 XOScript-bestanden hebben, gereedschap en programma:
Inhoud van gereedschap:

```
>> Gereedschap := Object nieuw.
```

Inhoud van programma:

```
Programma gebruik: Bestandslocatie gereedschap.
Uit schrijf: Gereedschap type, stop.
```

Na uitvoeren van het programma ziet u:

```
Object
```

De objecten Programma en Uit bieden allebei functionaliteiten rondon in/uitvoerstromen
van het programma.

## Uitbreidingen

U kunt de wereld van XOScript uitbreiden met nieuwe systeemobjecten door het installeren van
uitbreidingspakketten. U kunt een nieuw systeemobject aan de wereld van XOScript toevoegen door
het uitbreidingsbestand (meestal een bestand met de uitgang .so) in de mods-map te
plaatsen. Stel dat we bijvoorbeeld een reeks willen omzetten naar het JSON-protocol, dan kunnen
we hiervoor gebruikmaken van de JSON-uitbreiding die we installeren met:

```
mods/json/libctrjson.so
```

De exacte bestandsuitgang verschilt per systeem. Bovenstaand voorbeeld betreft de situatie op een
Linux-systeem. De bestandslocatie van een uitbreidingsbestand ziet er altijd zo uit:

```
mods/<Objectnaam>/libctr<Objectnaam>.<uitgang>
```

Wanneer u een bericht stuurt naar het object dat door het uitbreidingspakket beschikbaar wordt
gesteld, wordt het automatisch door XOScript ingeladen.
