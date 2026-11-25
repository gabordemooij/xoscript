# Grundlæggende

{{messages}}


Velkommen til XOScript
XOScript-projektet har som mål at skabe et scriptsprog, der er enkelt og kan revideres.
Enkelt betyder ikke nødvendigvis let.
Et velkendt programmeringssprog kan være lettere at bruge end XOScript.
Her betyder enkelhed noget andet:
at man kan danne sig en fuldstændig mental model af sproget og dets opførsel.

XOScript er designet til at kunne være i dit hoved.
Grammatikken og antallet af begreber er bevidst holdt små.
Der findes ingen klasser; objekter kan udvides direkte.
Objekter overføres som referencer, kopiering sker eksplicit,
og funktioner har ét enkelt udgangspunkt.

Nogle af disse valg adskiller sig markant fra de gængse sprog.
XOScript har for eksempel intet typesystem og bruger dynamisk scoping.
Beskeder, der ikke kan håndteres, ignoreres i stedet for at udløse en undtagelse.
Disse valg har konsekvenser og er ikke tænkt som en måde at fjerne fejl på.
De skal holde sprogets underliggende model lille og konsistent.

XOScript kan også lokaliseres, så det bliver muligt at udtrykke forretningsregler
i et naturligt sprog og eventuelt dele dem med ikke-tekniske interessenter.

Reviderbarhed betyder, at den samme filosofi anvendes på implementeringen.
Afviklingsmiljøet er skrevet i C med en lille, håndskrevet lexer, parser og trævandrer.
Standardbiblioteket og afviklingsmiljøet afspejler i vid udstrækning sprogets struktur,
så forholdet mellem XOScript-kode og implementeringen er forholdsvis direkte.

Testene er også tæt forbundet med dokumentationen.
Hver metode bør have en tilhørende test, der kan indarbejdes i manualen,
så dokumentationen holdes i overensstemmelse med implementeringen.

XOScript er ikke tænkt til at konkurrere med de gængse sprog på
funktioner eller genkendelighed. Det udforsker et andet mål:
et programmeringsmiljø, som en udvikler kan forstå som en helhed.

Håbet er, at et lille sprog og en lille
implementering gør det praktisk muligt at forstå software
fra byte til objekt, fra syntaks til afviklingsmiljø, og at skrive kode med
selvtillid, fordi du forstår både hvad der sker i
scriptet, og hvad der sker under motorhjelmen.

Arkitekturen i en xoscript-serveropsætning
er enkel, men alligevel fleksibel.

{{architecture.png}}

For at bruge xoscript som serversprog skal du installere
server-pluginnet i en mappe ved navn /mods/server. 

Det skyldes, at vi gerne vil
adskille kernesproget fra serverspecifikke funktioner,
i modsætning til for eksempel PHP eller Python. Ellers ville vi være nødt til at sende
hele køkkenvasken ud til alle uden noget formål, hvilket simpelthen er fjollet.
Du kan også installere andre moduler, hvis du vil. Systemet er meget
fleksibelt.

Desuden er nogle funktioner bedre implementeret i selve scriptsproget,
som for eksempel skabeloner og sessionshåndtering, så derudover
leverer vi bibliotekerne template.xo og webtools.xo for din bekvemmelighed.
Grunden til alt dette er, at vi ikke ved, hvordan du ønsker at
bruge xoscript. Du kan bruge det som et serverside-scriptsprog,
men også til grafiske brugerflader, indlejrede enheder eller blot batchbehandling.
Selv hvis du bruger det som serverside-scriptsprog (hvilket i
øjeblikket er et af de primære anvendelsesområder), vil du måske stadig
bruge en anden skabelonmotor eller en anden sessionshåndtering.
Hvem er vi til at bestemme, at du skal bruge vores?

En af fordelene ved at bruge vores egen skabelonmotor er dog,
at du ikke behøver at lære ekstra syntaks for at lave skabeloner.
Standardskabelonmotoren, der følger med xoscript, har 100 %
adskillelse mellem præsentation og logik. I stedet for særlig
skabelonsyntaks bruger den blot et meget fleksibelt system af pladsmarkører.
Se kapitlet Server for flere oplysninger.

Bemærk, at hvis du ikke vil bruge standardskabelonmotoren eller
standard-webtools, siger det sig selv, at du skal levere
dine egne.

Hvis du kører din webserver i en chroot, et jail eller en anden form for sandkasse,
skal du også installere xo's afhængigheder i det miljø. Du kan
se, hvilke biblioteker du har brug for, ved at bruge ldd (se manualsiden for Linux eller BSD).
Hvis du vil bruge skalkommandoer i dine xo-scripts, skal du også kopiere en skal
(som bash eller ksh) til dette miljø.

Vi vil også gerne understrege, at vi tager bagudkompatibilitet meget alvorligt.
Der findes endda en særlig funktion til bagudkompatibilitet, kaldet
'version'. Generelt sigter vi efter, at din kode skal kunne køre for evigt. Du vil altså
aldrig skulle opdatere din kode for at forblive kompatibel med nyere versioner
af xoscript. Vores mål er: skriv én gang, kør for evigt.

Resten af denne manual er viet til en detaljeret forklaring af programmeringssproget
xoscript. Serverscripting behandles i kapitlet
Server. Hvis du er en erfaren softwareudvikler, kan du med fordel
springe nogle kapitler over, fordi nogle af dem er lidt for detaljerede eller
minder meget om almindelig programmeringspraksis. Så for dem af jer,
der allerede har erfaring med flere andre programmeringssprog,
er det bedst at bruge denne manual som et opslagsværk.

## Opsætning på Linux

Download apache2 og mariadb:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Download xoscript.
Erstat X med det korrekte versionsnummer!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Kopiér filerne til webroden og /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Redigér din apache2-konfiguration:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Erstat Virtualhost med:

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

Opret en testside:

```
sudo nano /var/www/html/test.xo
```

og skriv et lille testprogram:

```
#!/bin/xo
Server initialiser.
Program brug: ['webtools.xo'].
>> web := Webdokument ny.
web udskriv: ['Hello World'].
```

Tillad apache2 at køre dit program via CGI:

```
sudo chmod uog+x /var/www/html/test.xo
```

Genstart apache2:

```
sudo systemctl restart apache2
```

Gå til din testside i browseren:

```
http://localhost/test.xo
```

Du skulle gerne se:

```
Hello World
```


## Opsætning på OpenBSD

Redigér /etc/httpd.conf, og tilføj:


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

Hvis du vil bruge SSL:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

For at beskytte nøgleudvekslingen mod kvantecomputere
skal du vælge mlkem-chifferet:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Tilføj xo-programfilen og mods samt eventuelle afhængigheder i
chroot-miljøet (find dem med ldd).

## Kør eksempler


For at køre et af eksempelprogrammerne i pakken:

```
./example.sh <name> <Linux/OBSD> [clean]
```

For eksempel, for at køre FizzBuzz-eksemplet på Linux:

```
./example.sh fizzbuzz Linux
```

For at køre det samme eksempel på OpenBSD:

```
./example.sh fizzbuzz OBSD
```

For at køre eksemplet med en ren build:

```
./example.sh fizzbuzz OBSD clean
```

## Enhedstest

For at køre enhedstestene:

```
./runtests.sh
```

For at køre enhedstestene uden at bygge (kun test):

```
./runtests.sh nobuild
```

## Byg

For at bygge fra kildekoden på Linux:

```
make clean
ISO="en" make
```

På OpenBSD:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

For at bygge server-pluginnet på Linux:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

For at bygge server-pluginnet på OpenBSD:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Hej verden

Når filen er overført til din computer, kan du pakke den ud
og starte xo med følgende kommando:

```
xo
```

For at køre et XOScript skal du gemme programmet som en fil med endelsen -xo
(valgfrit). Indsæt desuden filnavnet på dit program
efter XOScript-kommandoen:

```
xo myprogram.xo
```

Når du kører en XOScript-kommando med din programfil som
parameter, vil xo læse og udføre din programfil.

{{note}}
Du kan også starte dit program ved at trække det hen på xo-ikonet.
{{/note}}

{{warning}}
På nogle systemer skal du på forhånd give xo tilladelse til at indlæse dynamiske
biblioteker.
{{/warning}}

Traditionen foreskriver, at det første program i ethvert nyt programmeringssprog
skal være en slags hilsen til verden. I XOScript ser sådan et
**Hej verden**-program sådan ud:

@test598

Når denne tekst er gemt i en fil, f.eks. hello.xo, kan den køres
sådan: .

xo hello.xo

Hello world


Du kan se programmets uddata i det sorte vindue ovenfor.
I hele denne manual bruges den samme visning til at vise
uddata.

{{note}}
Uddata skrives med stort U.
Generelt begynder objekter med et stort bogstav,
medmindre de fungerer som en instans (ikke har egne
metoder, kun data). Det svarer til konventionerne for klasse og instans
i andre programmeringssprog.
{{/note}}


## Syntaks 

XOScript er et *rent* *objektorienteret* programmeringssprog. Det betyder,
at xoscript opfatter alt som et objekt, og derfor findes der
ingen andre *datatyper*. Der er grundlæggende tre basale handlinger
i et program skrevet i XOScript: *tildeling*, *afsendelse af beskeder*
og *svar*. Udvekslingen af beskeder mellem objekter er den centrale del af
et XOScript-program. De tre handlinger er illustreret
nedenfor:


Handling        | Eksempel
--------------- | --------
tildeling       |  \>\> x := 1. 
unære beskeder  | x lige?.
binær besked    | 1 + 2.
nøgleordsbesked | x fra: 0 længde: 10.
svar            | <- answer.  


Dette kapitel giver dig et generelt indtryk af sproget XOScript
og beskriver dets grundprincipper. XOScript er et lille sprog, der er
bygget på tre handlinger (se illustrationen), som omsættes til
cirka seks grammatikregler. Det er alt, der skal til for at mestre
sproget.

Bare rolig, hvis tingene ikke umiddelbart er indlysende for dig: alle byggesten
vil blive gennemgået i næste kapitel (3), og de grundlæggende regler vil
blive gentaget. Dette kapitel fungerer dog primært som en generel
introduktion til sproget. Grundprincipperne vil kort blive
forklaret og illustreret med flere relevante eksempler. Eventuelle manglende
detaljer vil blive beskrevet senere.

Kommentarer i XOScript indledes med et \#-tegn. Den følgende linje
vil derfor blive ignoreret:

```
# dette er bare en kommentar
```

## Variabler

For at tildele
en variabel bruger du variabelerklæringssymbolet: >>. Navnet på en
variabel må indeholde alle tegn undtagen: <-, :=, mellemrum,
punktummer, kommaer, koloner, anførselstegn [' '] og parenteser ().
Desuden kan en variabel ikke strække sig over flere linjer. Bemærk,
at en variabel ikke kan begynde med et tal eller et minustegn.

Dette er eksempler på gyldige variabler:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dollar'].
>> +plus := Sand.
>> brugerkodeord := ['Pssst!'].
```

Ugyldige variabler er for eksempel:


```
>> -123 := ['negativt tal'].
>> password of bruger := ['Hemmeligt'].
>> password.of:bruger := ['Hemmeligt'].
>> ,x := 10.
```

{{note}}
Du behøver ikke at escape nogen tegn
(heller ikke enkelte eller dobbelte anførselstegn eller
tekstafgrænsere) i
en tekstkonstant, så længe det ikke
skaber tvetydighed for lexeren.
{{/note}}

Når en variabel er erklæret, kan den bruges frit. Det betyder,
at erklæringssymbolet kun skal bruges første gang,
du bruger variablen (erklæringen).

Mere præcist kan du ikke bare begynde at tildele en værdi til
din variabel *(x := 2)*, da du først skal erklære variablen *(\>\>
x := 2)*. Når den først er erklæret, må du dog ændre dens værdi
uden at bruge erklæringssymbolet*(\>\> x := 2. x := 3.)*.

Bemærk, at det er obligatorisk at tildele en variabel en værdi, når den
erklæres. I modsætning til andre programmeringssprog må du ikke
erklære en variabel uden værdi. Det er afgørende eksplicit at knytte
hver variabel til en startværdi. Du er dog velkommen til at initialisere
variablen med objektet **Intet**. I så fald kan variablen
betragtes som tom *(\>\> x := Intet.)*. Kort sagt er det ikke tilladt at erklære en
variabel uden en startværdi. Så

```
>> x.
```

er ugyldigt og vil give en fejlmeddelelse.

{{note}}
xoscript bruger dynamisk scoping af variabler. Se
kapitlet Funktioner for detaljer.
{{/note}}


## Konstanter

XOScript opfatter alt som et objekt, dvs. alle tal, tekster
og kodefragmenter. Tal som 1, 2, 100, -999 og 1,234 er
Tal-objekter. Al tekst mellem enkelte anførselstegn er Tekst-objekter.
Alle kodefragmenter grupperet mellem krøllede parenteser {...} er
Funktion-objekter.

Konstant        | Rodobjekt    | Eksempel
--------------- | ------------ | ----------
tal             | Tal          | 1,2,3... 
tekster         | Tekst        | \['hello'\]
funktion        | Funktion     | { 1 + 2. }.
                
     
Objekter som tal og tekster har altid deres oprindelse i et rodobjekt.
For eksempel nedstammer alle tal fra objektet **Tal**. Alle
tekster nedstammer fra **Tekst** og alle kodefragmenter fra **Funktion**. Alle
disse objekter nedstammer igen fra **Objekt**, som faktisk er
rodobjektet for alle objekter.


## Beskeder

At programmere i XOScript betyder grundlæggende at
sende beskeder til objekter. Den generelle notation for at sende en besked til
et objekt er som følger:

```
<object> <message>
```

For at finde ud af, om tallet **2** for eksempel er et lige tal, sendes
beskeden **lige?** til objektet **2**:

```
2 lige?
```

Svaret vil være **Sand** (igen et objekt). Ukendte beskeder bliver
normalt ignoreret af objekter, så der opstår ingen fejl. Nogle objekter (f.eks.
tal eller tekster) reagerer på en ukendt besked på en foruddefineret måde
(mere om dette emne senere).

Et objekt kan modtage tre slags beskeder. 

Type            | Antal argumenter
--------------- | -------------------
Unær            | 0      
Binær           | 1     
Nøgleord        | 1+    


For det første er der **unære
beskeder**, se eksemplet ovenfor, som er uden argumenter. For det andet
er der **nøgleordsbeskeder**, som har ét eller flere argumenter,
for eksempel:

```
>> x := Tal mellem: 1 og: 10.
```

I dette tilfælde sendes beskeden **mellem:og:** til **Tal**, som
er rodobjektet for alle tal. Resultatet vil være et tilfældigt tal
mellem 1 og 10. Endelig er der **binære beskeder**, som kun har
ét tegn og ét argument:

```
2 + 3
```

Det ligner en matematisk sum, men det er faktisk bare endnu en besked.
Beskeden **+** sendes til **2** med argumentet **3**, hvilket returnerer
svaret **5**. Binære beskeder må skrives uden kolon.

Binære beskeder kan kædes sammen:

```
>> x := 3 + 2 - 1.
```

I dette fragment sendes **+ 2** først til **Tal**-objektet **3**, hvilket
giver Tal-objektet **5**, hvorefter **-1** sendes til dette
tal. Opmærksomme læsere har ret i at bemærke den uoverensstemmelse, som
denne protokol udviser i forhold til den konventionelle matematiske rækkefølge af
operatorer. XOScript ignorerer den matematiske rækkefølge til fordel for
konsistens i sit beskedsystem. Som følge heraf giver summen:

```
2 + 3 * 5 = 25
```

ikke 17.

Det er tilsigtet. Parenteser kan bruges til at ændre rækkefølgen:

```
2 + (3 * 5) = 17
```

De fleste objekter returnerer sig selv som resultat af en given
besked. Det er nyttigt, da det opfordrer til videre dialog med dette
objekt ved at sende det en opfølgende besked:

```
Uddata skriv:
[' hej '] trim store-bogstaver.
```

```
HEJ
```

Her sendes to beskeder til **Tekst**-objektet: **trim**, efterfulgt
af **store-bogstaver**.

I det følgende fragment er et komma nødvendigt for at angive,
at en ny besked er på vej. Ellers bliver XOScript forvirret.

```
Uddata skriv: ['Hello!'], stop.
```

Først sendes beskeden **skriv:** til blyantsymbolet, efterfulgt af
**stop**. Uden kommaet ville XOScript tro, at du vil sende
**stop** til **tekst** **Hello!**, hvilket ville være formålsløst.

Beskeder behandles i følgende rækkefølge: fra venstre mod højre;
først beskeder i parenteser, derefter unære beskeder. Dernæst
binære beskeder, og til sidst nøgleordsbeskeder. Se eksemplet
nedenfor:

```
Uddata skriv: 0.5 afrund + (2 - 1), stop.
```

XOScript læser altid fra venstre mod højre: først sendes beskeden **skriv:**
til Uddata, efterfulgt af beskeden **stop**. Inden for
selve argumentet læser XOScript fra venstre mod højre, altså først **0.5 afrund**
og derefter **+**.

{{note}}
Beskeden stop tilføjer et linjeskift til teksten.
Navnet på denne besked er inspireret af telegrafsystemer.
Meddelelser i telegrafsystemer 
brugte ofte ordet STOP til at markere slutningen af en sætning
(da tegnsætning var upålidelig eller dyr).
{{/note}}

Desuden har **afrund** forrang for **+**, fordi det er en
**unær besked**. På grund af parenteserne beregnes **2 - 1**
først, hvorefter **1** lægges til resultatet af **0.5 afrund** (1).

Hele processen giver resultatet **2**, som også er det udskrevne
svar. Efter kommaet følger beskeden stop, som flytter markøren
til en ny linje. Den bedste måde at forstå rækkefølgen i
XOScript-programmer fuldt ud på er naturligvis ved at øve sig.

Det er værd at bemærke, at mellemrum i XOScript, i modsætning til mange andre programmeringssprog,
er en grundlæggende del af syntaksen. Især
når det gælder binære beskeder, kan mellemrum skabe en vis
forvirring. Brug altid et mellemrum efter en binær besked. Du kan ikke
sætte et tal direkte fast på beskeden, for eksempel er: 

```
3 + 2
```

forskelligt fra 

```
3 +2
```

Det første eksempel (**3 + 2**) sender
beskeden **+** til tallet **3** med tallet **2** som argument.
Resultatet bliver i dette tilfælde **5**. I det andet eksempel (**3 +2**)
sendes den unære besked **+2** til tallet **3**. Afhængigt af
konteksten kan det give et helt andet resultat.

## Ikke-eksisterende metoder

Når en besked sendes til et objekt, aktiveres den funktion, der er
knyttet til objektet under det beskednavn. Hvis du sender en besked,
som ikke forstås, vil det modtagende objekt ignorere din besked
og i stedet returnere en reference til sig selv til videre kommunikation.
Dette kaldes tolerant beskedudveksling.

Eksempel:

```
Uddata skriv: Objekt blah, stop.
```

Dette giver ikke en fejl. Det udskriver blot teksten **Objekt**.


## Kontrolstrukturer

I XOScript er der ikke brug for separate grammatikregler for *løkker* og
*if-sætninger*. En if-sætning er blot en simpel **sand:**- eller **falsk:**-besked
til enten et **Sand**-objekt eller et **Falsk**-objekt:

```
2 lige? sand: {
	Uddata skriv: ['To er et lige tal'], stop.
}.
```
I det foregående eksempel sendes beskeden **sand:** til **Sand** (svaret
på spørgsmålet: er 2 et lige tal?). Som argument sendes desuden et
kodefragment med: et **Funktion**-objekt. Denne funktion skriver på
skærmen, at 2 faktisk er et lige tal.

Der er heller ikke brug for separate skriveregler for en *løkke*. For at
udføre et kodefragment tre gange sender du blot **\*** med argumentet
**3** til den **Funktion**:

@test5

I dette kodefragment er **i** indekset. Første gang Funktionen
udføres, er **i** lig med 0, næste gang den udføres, er **i** = 1, og
så videre.

Lad os se på et andet eksempel. Når en omregningstabel skal
udskrives fra *kJ* (kilojoule) til *kcal* (kilokalorie) i trin på 100,
ser den korrekte notation sådan ud:

@test599

Her overføres nummeret på den aktuelle linje til parameteren
**:line**. I begyndelsen af en funktion defineres funktionens
parametre. Ubrugte parametre forbliver tomme (**Intet**). Parametre
placeres altid i starten af funktionen, direkte efter den første
krøllede parentes, og indledes med et kolon.

Beskeden **mens:** er en kombination af en *løkke* og en *betingelse*.
To funktioner kan forbindes med beskeden **mens:**. Den modtagende funktion
bliver ved med at køre, indtil funktionen efter kolonet giver et negativt
resultat. Eksempel:

@test600

I kodefragmentet ovenfor lægges **1** til **x**, så længe
**x** er mindre end **5**. Når det ikke længere er tilfældet, vil den anden
funktion svare med **Falsk**, og som følge heraf afsluttes udførelsen af den
første funktion. Bemærk, at **x** er defineret uden for
funktionen og er en global variabel. Se kapitlet om Funktioner for at
lære mere om scopingregler.

## Tekstinterpolation

*kJ/kcal*-listen kunne gøres mere
præsentabel. Helst skulle listen se sådan ud:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Når du omdanner det ønskede resultat til en skabelon, kunne notationen
være:

```
number1 kJ ➞ number2 kcal
```

Det betyder, at **number1** står for kJ-værdien og **number2** for
kcal-værdien. Sådan fungerer tekstinterpolation i XOScript. Der
kræves ingen separate grammatikregler til dette i XOScript. Send blot
det ord, der skal erstattes, til teksten med erstatningsteksten
som argument:

```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

Resultatet:

```
100 kj ➞ 23.9 kcal
```

Denne erstatningsregel gælder for enhver udefineret besked, der modtages
af et **tekst**-objekt. Enhver besked, som ikke genkendes af
**tekst**-objektet, fortolkes som følger: *erstat beskedens
tekst med teksten i beskedens argument.* Du kan tilpasse
programmet som følger:


@test601


For at undgå forvirring om, hvilke beskeder der kan eller ikke kan bruges som
erstatning, er det bedst at indføre en skabelonmarkør som &lt; &gt;
for de tekstdele i skabelonen, der
skal erstattes.

## Returværdier

For at besvare en besked bruges returpilen
(*<-*). Det følgende eksempel viser, hvordan man laver en opgave,
der beregner en procentdel:

@test602

Når opgaven er defineret og tildelt variablen **percentage**,
sendes beskeden **anvend:og:** med argumenterne **100** og **7**.

Dette udfører opgaven anvendt på **100** og **7**, dvs. 7 % af 100.
Ved hjælp af returpilen returneres svaret fra opgaven tilbage
til hovedprogrammet.

## Udvidelse

Selvom denne kode er gyldig, har den en ulempe,
fordi man skal huske rækkefølgen af argumenterne. Så hvorfor ikke
skrive det sådan her: *7 percent of: 100 *? Det ville se meget mere
*naturligt* ud. For at gøre det muligt skal vi tilpasse forældreobjektet til
**7**, som er **Tal**-objektet, så det forstår
beskeden **percent of:**. Det kan opnås ved at sende **ved:gør:** til
Tal-objektet, sådan her:

@test603

Da procentdelen i dette tilfælde er selve tallet, henviser vi til selv,
nøgleordet *selv*. Kort sagt betyder symbolet selv: *send denne
besked til mig selv*.

# Objekter

{{messages}}

Ud over at tilpasse og udvide eksisterende objekter kan du også selv
oprette nye objekter blot ved at sende beskeden **ny**. Antag, at du
gerne vil oprette et fakturaobjekt, der håndhæver en fortløbende
nummerering. I så fald skal du først have et fakturaobjekt.

Da hvert objekt nedstammer fra et andet objekt, som i sidste ende
stammer fra rodobjektet for alle objekter, kaldet Objekt,
skal der træffes et valg om, hvilket af disse andre objekter dit
nye objekt skal bygge på. Dit nye objekt arver alle egenskaber fra
det objekt, det bygger på, altså det objekt, som beskeden **ny**
oprindeligt blev sendt til.

I dette eksempel foretrækkes et forholdsvis neutralt objekt, et uden for
mange nedarvede egenskaber. Det gør valget let, for i så fald
kan det nye objekt bygge på selve rodobjektet, som er
**Objekt**. Notationen for det tiltænkte fakturasystem bliver så
som følger:

@test604

Det aktuelle fakturanummer gemmes i objektet, og derfor er
nøgleordet **egen** placeret foran det. Dette kaldes en *egenskab*;
flere detaljer følger.

Nogle virksomheder foretrækker at have årstallet indarbejdet i
fakturanumrene. I så fald kan du oprette et nyt fakturaobjekt baseret på et
tidligere fakturaobjekt, men som giver brugeren mulighed for at
angive et bestemt år:

@test605

Der er ingen grund til at skrive implementeringen af beskeden **tal**
igen, da den nedarves fra det tidligere skrevne **fakturaobjekt**;
dermed kan gammel kode genbruges. XOScript mangler begreber
som klasser og andre beslægtede begreber. Det betyder, at objekter
udelukkende kan arve fra andre objekter, også kendt som *prototypisk
nedarvning*.

Lad os nu vende tilbage til egenskaber. Objektegenskaber kan kun tilgås
*inden for objekthierarkiet*, så disse egenskaber
kan ikke ses af andre objekter.

I modsætning til andre programmeringssprog er alle egenskaber i objekter
udelukkende synlige for det objekt, der har oprettet egenskaben, og for
afledte objekter. 

En almindeligt brugt teknik er at bruge et objekt som en slags *skabelon*,
hvilket for eksempel er tilfældet med de fakturaer, der blev gennemgået tidligere.
Et andet godt eksempel er **Point**. Lad os sige, at du laver et
computerprogram, der foretager beregninger med punkter på et kort. Du
kan udvikle objektet **Point** med egenskaberne en
x-koordinat og en y-koordinat, som gøres tilgængelige for
omverdenen via beskeder:

@test606

Beskeden **=** sammenligner de to punkter ved hjælp af beskeden **og:**.
Den første sammenligning giver en **Sand** eller en **Falsk**. Det er boolske
objekter. Når du sender beskeden **og:** til et Sand-objekt, og
argumentobjektet efter kolonet ligeledes er **Sand**, så vil du
igen få svaret **Sand**. Når en af dem er **Falsk**, vil du
få svaret **Falsk**. Bemærk, at det ene punkt ikke kan læse det andet punkts
koordinater. Det er nødvendigt at sende en besked til det andet punkt for at bede
om disse data: **x-coordinate** og **y-coordinate**. Som allerede
forklaret kan egenskaber jo kun hentes inden for
selve objektfamilien. 

Bemærk, at beskeden **=** her bruges til at udføre sammenligningen af
punkterne. Der kunne lige så godt have været brugt en anden besked, som f.eks.
**is:** eller **equal:**, men det virkede passende i dette tilfælde
at genbruge tegnet **=**.

## Nedarvning

Du kan genbruge tidligere skrevet kode til at skabe et hierarki
af objekter. For eksempel:

```
>> Dyr := Objekt ny.
>> Hund := Dyr ny.
>> Puddel := Hund ny.
```

I dette tilfælde arver **Dog** al opførsel og alle egenskaber
fra **Animal**, og objektet **Animal** arver til gengæld al opførsel fra
**Objekt**, rodobjektet for alle objekter.


## Overskrivning


I det følgende eksempel oprettes en ny slags liste:
**Combination**, hvor hvert element garanteret er unikt. Listens
funktioner genbruges via nedarvning:

@test607

Læg mærke til, hvordan det andet **red** udelades fra listen.

Af og til kan det være nødvendigt at overskrive et objekts opførsel.
For eksempel når man lægger tal sammen og skal tage højde for
måleenheder. I det følgende eksempel oprettes objektet **Size**.
Dette objekt returnerer et tal, som under additionen tager
højde for enheden af det tal, der skal lægges til. **Tal**-objektet
kontrollerer, om der er tale om *inches* eller *foot*. Programkoden
kunne se sådan ud:

@test608

## Rekursion

I det foregående eksempel overskrives plus**tegnet**. Bemærk,
at den endelige addition til sidst stadig skal udføres, hvilket faktisk
sker på følgende linje:

```
>> svar := selv + (tal x faktor).
```

Hvordan forstår XOScript så, at dette plus**tegn** henviser til
den oprindelige logik for addition?** En anden fortolkning kunne for eksempel
være, at XOScript gentagne gange sender den samme besked til det samme
objekt, hvilket igen ville resultere i en **uendelig løkke**. Det er tydeligvis
ikke hensigten. Så snart du sender en besked til et objekt,
som ville udføre præcis den samme kode, vil XOScript i dette tilfælde
forstå, at det er den underliggende, overskrevne besked, der menes. Dit
program er altså automatisk beskyttet mod denne form for uendelige
løkker. Hvis det derimod faktisk er din hensigt at køre den samme funktion fra
den aktuelle funktion, er det nødvendigt først at sende beskeden
**rekursiv**. I dette tilfælde bliver resultatet en uendelig
løkke. Der findes dog nyttige anvendelser af rekursive opgaver,
for eksempel hvis du vil beregne fakultetet af et givet
tal. I så fald tilføjer du blot beskeden **factorial** til
Tal:

@test609

Dette kræver rekursion. Opgaven, der er knyttet til
beskeden **factorial**, skal nemlig udføres igen inden for den funktion.
Det er altså nødvendigt at kalde fakultetsfunktionen inde fra
selve fakultetsfunktionen. Som udgangspunkt forhindrer XOScript dette,
på grund af risikoen for at ende i en uendelig løkke. Derfor
er det afgørende at sætte ordet **rekursiv** foran beskeden. Det
gøres for at gøre XOScript opmærksom på, at det er din
hensigt at udføre den samme opgave, og at du ikke har lavet en fejl.

## Klasselignende objekter

Selvom xoscript ikke tilbyder klasser, er det trivielt at efterligne
klasselignende opførsel. Du overskriver blot beskeden ny.

```
>> Dyr := Objekt ny.
Dyr ved: ['ny'] gør: {
	<- selv ny initialiser.
}.

Dyr ved: ['initialiser'] gør: {
	egen lyd := ['?'].
	egen ben  := 4.
}.
```

I kodefragmentet ovenfor opretter vi et objekt kaldet Animal.
Dette objekt fungerer som en *skabelon* for alle slags dyr
som hunde og katte. Forældreobjektet Animal skrives
med stort A for at vise, at det er et klasselignende objekt.
Dernæst overskriver vi beskeden ny ved at skrive vores egen ny-metode.
I dette tilfælde sender den beskeden ny til selv, efterfulgt af beskeden
initialiser. Fordi xoscript som standard blokerer rekursion, giver det ikke
en uendelig løkke. I stedet sendes beskeden ny til forældreobjektet
(Objekt), hvilket resulterer i en ny instans af Animal. Vi opretter altså
et nyt objekt baseret på det samme objekt, som vi har lavet vores ny-metode til.
Det er fuldt ud gyldigt. Nu sender vi også beskeden initialiser, som sikrer,
at Animal-objektet har standardværdier for sine egenskaber. Som standard
har et dyr 4 ben, og lyden er ukendt (deraf spørgsmålstegnet).
For at oprette en ny instans af vores Animal kunne vi blot skrive:

```
>> a := Dyr ny.
```

Nu får vi en ny instans af Animal med 4 ben, ukendt lyd og
en initialiser-metode. Ligesom i andre OOP-sprog kan vi også
udvide vores Animal:

```
>> Hund := Dyr ny.
Hund ved: ['initialiser'] gør: {
	selv initialiser.
	egen lyd := ['gør'].
}.
```

Vi kan nemt teste dette ved at tilføje en tekst-metode:

```
Dyr ved: ['tekst'] gør: {
	<- egen ben tekst + egen lyd.
}.
```

Lad os samle det hele:

@test13


At oprette et objekt, der skal være i en bestemt starttilstand, er et
hyppigt problem. Antag, at der skal oprettes et objekt **Rectangle**
for at beregne omkreds og areal. En mulig notation ville være:


```
>> Rektangel := Objekt ny.

Rektangel ved: ['areal'] gør: {
	<- egen længde * egen bredde.
}.
```

Det er naturligvis en forudsætning, at længde og bredde er angivet. Til det
formål kan beskederne **længde:** og **width:** tilføjes:


```
Rektangel ved: ['length:'] gør: { :længde
	egen længde := længde.
}.

Rektangel ved: ['width:'] gør: { :bredde
	egen bredde := bredde.
}.

```

Dette rektangel kan derefter bruges som følger:


```
>> rektangel := Rektangel ny length: 2, width: 3.
Uddata skriv: rektangel areal.
```

Hvis man derimod glemmer at angive længde og bredde fra starten,
opstår der en fejlmeddelelse:

```
>> rektangel := Rektangel ny.
Uddata skriv: rektangel areal.
```

giver følgende fejl:

```
Nøgle ikke fundet:længde
```

For at forhindre dette er det at foretrække, at et rektangel
altid har en startlængde og -bredde, for eksempel 0. I dette
tilfælde er det altså nødvendigt at **overskrive** beskeden **ny**.

@test610

Når vi overskriver beskeden ny, efterligner vi grundlæggende en **klasse**.

XOScripts verden er fyldt med en mangfoldighed af objekter, som er
tilgængelige for dit program lige fra starten. I de næste kapitler
vil alle disse kerneobjekter blive gennemgået.

## Øjebliksbilleder

Du kan gemme et objekt (sammen med dets aktuelle tilstand) på disken med:

```
mitobjekt save-as: ['saved.bin'].
```

For at indlæse objektet fra disken igen:

```
>> mitobjekt := Objekt load-from: ['saved.bin'].
```

Øjebliksbilleder kan bruges til at gemme en bestemt tilstand eller til at forbedre ydeevnen.
Indlæsning af et øjebliksbillede undgår lexing, parsing og opsætning af applikationen.
I fremtiden kan der desuden komme yderligere ydelsesfordele ved
øjebliksbilleder, som f.eks. optimering af bestemte mønstre eller registrering og
optimering af hyppigt brugte kodestier.

{{warning}}
Øjebliksbilleder er en eksperimentel funktion; brug den ikke i produktion.
For at aktivere eksperimentelle funktioner skal du kompilere med -D EXPERIMENTS.
{{/warning}}


@test712

# Intet-objektet

{{messages}}

Intet-objektet
repræsenterer tomhed, eller bedre endnu, fraværet af information. Af og til
vil du modtage dette objekt som svar på en besked, hvis
resultatet er **ingenting**. Det mest grundlæggende spørgsmål,
du kan stille **Intet**-objektet, er: **Intet?**.
Svaret vil altid være **Sand**.

```
Uddata skriv: Intet Intet?.
```

resultat:

```
Sand
```

Ethvert andet objekt end **Intet** vil svare med **Falsk**. Kodefragmentet
ovenfor kan virke en smule filosofisk, men **Intet**-objektet
har bestemt yderst praktiske anvendelser. For eksempel vil du
modtage Intet-objektet som svar, hvis du beder om et
listeelement, der ikke findes. Du kan også bruge Intet-objektet,
hvis du vil erklære en variabel, men endnu ikke vil angive en
værdi. I stedet **tildeler** du blot den særlige værdi **Intet**. I
XOScript er det ikke tilladt at erklære en variabel uden værdi, som f.eks.:


```
>> værdi.
```

I stedet skal du skrive følgende:

```
>> værdi := Intet.
```

@api_None_base

# Boolske værdier

{{messages}}

I modsætning til de fleste populære programmeringssprog på skrivende tidspunkt
har XOScript kun ét enkelt Sand-objekt og ét enkelt Falsk-objekt.
For at præcisere: hver gang du skriver **Sand**, betyder det ikke,
at der er oprettet et nyt objekt. I stedet bruger du altid en reference. Det
betyder, at når du skriver følgende:

\>\> x := Sand.

henviser **x** til **Sand**-objektet. Betinget kode og løkker
kontrollerer også denne reference. I XOScript er betydningen af **Sand** og **Falsk**
ikke fastlåst. Faktisk bliver et XOScript-program ganske rystet af
en sætning som denne:

Sand := Falsk.

Resultatet af sådanne handlinger er udefineret, men det er stadig en gyldig
handling og derfor formelt tilladt. Desuden findes der et Boolsk-objekt,
som er rodobjektet for både **Sand** og **Falsk**, da begge
er afledt af rodobjektet. Selve Boolsk-objektet har dog
ingen praktisk anvendelse.

## Faldgruber

Vær forsigtig med at bruge **og:** og **eller:**

```
Uddata skriv: (Falsk or: Sand or: Sand), stop.
Uddata skriv: (Falsk eller: Sand, eller: Sand), stop.
```

Giver

```
Falsk
Sand
```
fordi beskeden **eller:** kun tager 1 argument. Den første linje
sender **eller:eller:** til Falsk, som ikke findes, så objektet ignorerer
beskeden og returnerer sig selv (Falsk). Den anden linje
sender derimod **eller:** efterfulgt af endnu en **eller:** (ved hjælp af et kædesymbol, dvs. et komma: ,).


@api_Boolean_base

# Tal

{{messages}}

Hver gang du skriver et tal, for eksempel 9, -10 eller 3,12, vil XOScript
bag kulisserne omdanne disse tal til et **Tal**-objekt. Du
kan sende beskeder til dette Tal-objekt, eller du kan tildele tallet
til en variabel og sende beskeder bagefter:

```
10 lige?

>> tier := 10.
tier lige?

```

Begge notationer er gyldige. Tal-objektet reagerer på følgende
beskeder...

De fleste af disse beskeder er selvforklarende og giver dig mulighed for at udføre
matematiske operationer eller sammenligninger.

{{note}}
Bemærk, at du kan bruge ≤ ≥ ≠ × og ÷ i stedet for deres ASCII-modstykker.
Det er en smagssag.
{{/note}}

Forskellen mellem binære matematiske beskeder (+) og
deres nøgleordsvarianter (læg-til:) er, at de første returnerer
et nyt tal, som er resultatet af operationen, mens
objektet selv ændres med de sidste. Dette illustreres i
følgende eksempel:

@test597

I eksemplet ovenfor er b = 4 og a = 3. Med **læg-til: 2** øges værdien
af a med 2, mens **+ 3** opretter et nyt tal, der er
lig med a + 3. Det samme gælder for andre matematiske operationer, f.eks.
multiplikationer. Når du bruger multiplikationstegnet, får du et
nyt objekt som svar. Hvis du bruger beskeden **gang-med:**,
ganger du selve tallet.

Med beskeden **mellem:og:**, for eksempel i: **Tal
mellem: X og: Y**, får du et tal mellem X og Y. På denne
måde kan der genereres et vilkårligt tilfældigt tal:

```
>> a := Tal mellem: 1 og: 10.
Uddata skriv: a, stop.
```

Fra og med version 1.4 er den indbyggede generator af tilfældige tal i xoscript
kryptografisk sikker, så vidt vi ved.

Du kan knytte en **betegnelse** til et tal, for eksempel **6
apples**. Enhver besked, som et tal ikke genkender,
betragtes som en betegnelse. Du kan hente et tals betegnelse
ved hjælp af beskeden betegnelse:

En betegnelse er grundlæggende et Tekst-objekt, der gemmes sammen med Tal-objektet.
Betegnelsen udskrives også efter tallet ved en
**skriv:**-instruktion. Betegnelser kan for eksempel bruges til at lægge beløb
i blandede valutaer sammen. Når du lægger beløbene sammen, kan du spørge
efter betegnelserne. Det følgende programeksempel illustrerer dette
princip med en historisk valutaberegner (da vekselkursen
forbliver rimeligt stabil!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Tekster

{{messages}}

Hver gang en tekst placeres mellem **firkantede parenteser og anførselstegn** ['...'],
opretter XOScript et nyt tekstobjekt til dig. Sørg dog
for at bruge de korrekte anførselstegn. Anførselstegnet i
begyndelsen af teksten er forskelligt fra det i slutningen (det giver dig mulighed for
at bruge det enkelte anførselstegn uden at skulle escape det).

## UTF8

Tekster i xoscript indeholder normalt utf8-kodet tekst. Selvom
det teknisk set er muligt at have binært indhold eller indhold, der ikke er utf8, i
en tekst, anbefales det at bruge blobs til det. Blobs
leveres af server-pluginnet (se kapitlet ffi).
Generelt leveres blobs/ffi
pr. plugin/platform, da de er tæt knyttet til platformen
og arkitekturen (ffi/blobs). Kernen i scriptsproget forsøger at
forblive så platformsuafhængig som muligt.

## Typekonvertering

Du kan oprette en kopi af ethvert objekt
med en anden type ved hjælp af følgende beskeder:

Besked  | Resultat
------- | ------
tal     | Konverterer til et tal
tekst   | Konverterer til en tekst
boolsk  | Konverterer til en boolsk værdi
  
Følgende regler **gælder**:

besked   | Intet     | Boolsk             | Tal                   | Tekst     | Andet              
-------- | --------- | --------           | --------              | --------  | --------
boolsk   | Falsk     | i/r                | 0→Falsk ellers→Sand   | Sand      | Oftest Sand
tal      | 0         | Falsk→0 Sand→1 | i/r                       | ['n']→n | Oftest 1
tekst    | ['Intet'] | ['Falsk']/['Sand'] | ['n']                 | i/r       | Afhænger af objektet

## Kopiering

Værdier i XOScript overføres altid **som reference**. I andre sprog
afhænger det af værditypen; i XOScript er der kun én måde,
nemlig som reference. XOScript laver aldrig en kopi af en værdi. For at kopiere et objekt
skal du sende beskeden **kopiér**. 

@test611

Her havde du måske forventet, at uddata ville være Dolly i stedet
for Donny. Det er dog ikke tilfældet, da begge navne henviser til det samme
objekt. Når man arbejder med en løkke, sker der noget lignende:

@test612

XOScript bruger faktisk **altid** referencer, så ved **:quantity**
angiver løkken ovenfor også referencen til elementet
i listen.

For at kopiere et objekt skal du angive denne handling
**eksplicit**:

@test613

Ved at sende den unære besked **kopiér** til en tekst returnerer objektet
en kopi af det samme tekstobjekt. Det er på samme måde muligt at kopiere Tal-objekter,
boolske objekter, lister og ordbøger.

Du kan også definere din egen kopi-implementering; det er endda en
nødvendighed, hvis du opretter dine egne objekter. Standardimplementeringen
af kopiér for en liste laver en overfladisk kopi; den opretter en
ny liste med de samme elementer.

@test614

I dette tilfælde tilføjes 4 kun til kopien.
Men fordi kopien er overfladisk, er objekterne i begge lister
de samme.

@test615

Så hvis vi tilføjer 2 til hvert navn i kopien, påvirkes den oprindelige
liste også.

For at afhjælpe dette skal vi lave en **dyb kopi**. En sådan kopihandling
for en liste kunne sammensættes som følger:

@test616

Bemærk også beskeden rekursiv; denne besked skal
sendes før beskeden kopiér.

Det er vigtigt at huske, at selvom en kopi af et objekt
ofte ser ud som originalen, vil den faktisk
aldrig være den samme. Rodobjektet definerer en besked **equal:**,
som kan bruges til at sammenligne objekters identitet. Se på
følgende eksempel:

@test617

## Implicit konvertering

XOScript bruger **implicit konvertering** til at konvertere objekter. For at udskrive en
liste på skærmen sender XOScript for eksempel internt beskeden
*tekst* til listen. Det kan vise sig at være meget nyttigt, hvis
du vil udskrive en liste som en kommasepareret liste.
Beskeden *tekst* kan overskrives: 

@test620

@api_String_base
@api_Format_base


## Servertekster

Følgende Tekst-funktioner tilføjes af
Server-pluginnet.

@api_String_server

# Funktioner

{{messages}}

Du kan gruppere kode mellem { og }; så bliver det en funktion.
I xoscript bruger vi også nogle gange betegnelsen opgave eller blot
kodeblok.

Du kan køre en funktion ved at sende beskeden *start*.


```
{ Uddata skriv: 123, stop. } start.
```

Hvis din funktion tager argumenter, skal du bruge **anvend:**.

```
{ :a Uddata skriv: a, stop. } anvend: a.
```

Se også eksemplerne nedenfor.
På grund af den enkle arkitektur kan en funktion kun have
ét returpunkt. For at undgå overhead eller overdreven indlejring af
betingelser kan du bruge en procedure (hvilket svarer til at bruge
multiplikationstegnet med argumentet 1):

```
{
  (a = 1) sand: { x := 1. }, afbryd.
  (a = 2) sand: { x := 2. }, afbryd.
} procedure.
```

På denne måde evalueres (a = 2) ikke, hvis a = 1.
Desuden behøver du på denne måde ikke indlejrede sand-beskeder.
Når du opdager, at du indlejrer betingelser, så tænk
på beskeden procedure. Den kan gøre din kode
lettere at læse.


Her er en vigtig faldgrube:

```
{
	Falsk falsk: {
		Uddata skriv: ['Afslut løkken.'].
	}, afbryd.
	
	Uddata skriv: ['Vis mig ikke.'].

} procedure.

```

I dette tilfælde vises teksten 'Dont show me'.
Det skyldes, at **afbryd** sendes til Falsk. Hvis du vil udføre
en afbrydelse, skal den sendes som en besked til **Sand**.
 

```
{
	Falsk ikke sand: {
		Uddata skriv: ['Afslut løkken.'].
	}, afbryd.
	
	Uddata skriv: ['Vis mig ikke.'].

} procedure.

```

Virker som forventet.

## Undtagelser

Undtagelser kan håndteres sådan her:

```
{ Opgave 1 } fang: { Opgave 2 }, start.
```

Du kan også med vilje få en fejl til at opstå i dit program og
dermed aktivere håndteringsblokken. Det gøres ved at sende
beskeden **fejl:** til den aktuelle opgave, som vist i
næste illustration:

```
{
denne-opgave fejl: ['Hovsa!'].
} fang: { :fejltagelse
Uddata skriv: fejltagelse.
}, start.
```

## Indsprøjtning af værdier

XOScript giver mulighed for at indsprøjte værdier i opgaver. Se nu
på opgaven nedenfor:

```
>> afsendelse := {
	Nyhedsbrev til: egen recipient.
}.
afsendelse sæt: ['recipient']
værdi: ['info@recipient.org'].
afsendelse start.
```


Denne illustration viser en tænkt opgave, som sender et nyhedsbrev
til en e-mailadresse eller **modtager**. Denne modtager kan indsprøjtes
i opgaven udefra, før opgaven startes, ved at sende
beskeden **sæt:værdi:** til opgaven. Derved forudindstilles værdien af
**recipient** i opgaven. Denne værdi kan også ændres,
og opgaven kan derefter køres igen. Det er en nyttig metode, når man bruger
Opgave-objekter.

## Tomme funktioner

Tomme opgaver er ikke tilladt. I teorien ville en tom opgave se sådan
ud: **{}**, men XOScript opfatter dette som en sprogfejl. Hvis du
vil erklære en tom opgave, kan du bruge Intet-objektet:

```
>> opgave := Intet.
```

Selvom dette ikke er en rigtig opgave, men et Intet-objekt, kan der
stadig sendes en start-besked:

```
>> svar := opgave start.
```

Det er faktisk det samme som:

```
>> svar := Intet start.
```

Fordi objektet **Intet** ikke genkender beskeden **start**,
returnerer det sig selv som svar, så svaret igen bliver **Intet**.
Der er altså ikke behov for en tom opgave. Takket være det elegante
design af programmeringssproget XOScript kan du blot bruge Intet-objektet
til dette.

## Dynamisk scoping

Når en Funktion har brug for en variabel, men ikke kan finde den,
kontrollerer den variablerne i den Funktion, der **kaldte** den,
og fortsætter op gennem kæden af Funktioner.
Denne søgeproces fortsætter, indtil variablen er fundet.
Hvis variablen stadig ikke findes, vises en fejlmeddelelse. Denne måde at søge efter en
variabel på kaldes **dynamisk scoping**.

For at illustrere dette princip:

@test618

@api_Code_base

# Rodobjektet

{{messages}}

Objektet med navnet **Objekt** er rodobjektet for alle objekter i
XOScript og leverer sprogets kernefunktioner. 

Den hyppigst sendte besked
er **ved:gør:**, som udvider et objekts funktionalitet. Denne
besked modtages af rodobjektet, som derefter knytter den
angivne opgave til beskeden og derved udvider det afledte
objekt.

## Opsamlingsmetoder

Hvis du sender en besked, der ikke svarer til
en metode i objektet, bliver den normalt ignoreret. Du kan dog angive
såkaldte **magiske metoder** eller **opsamlingsmetoder**, som
aktiveres, hvis objektet ikke forstår beskeden.

Der findes 4 opsamlingsmetoder. Hver besked svarer til
et bestemt antal argumenter.

Opsamlingsbesked     | Antal argumenter
-------------------- | -------------------
svar:                | 0
svar:og:             | 1
svar:og:og:          | 2
svar:og:og:og:       | 3


@test619

## Programmatiske beskeder

I stedet for at sende en besked direkte til et objekt kan den også
sendes via en variabel. Til det bruger du beskeden
**besked:argumenter:**. 

@test396

@api_Object_base

# Lister

{{messages}}

XOScript kender to typer samlinger: *lister* og *ordbøger*.
**Lister** er opremsninger af objekter i en *fast rækkefølge*. Ordbøger har
ingen rækkefølge, men ligner i stedet en signaturforklaring med en nøgle (eller et begreb) og den
tilhørende værdi. Lister kan sammenlignes med arrays (PHP, Java, C)
og lists (Python). Ordbøger kan sammenlignes med associative arrays (PHP) eller
dictionaries (Python) i andre programmeringssprog. For at oprette
en ny Liste skriver du:

```
>> fibonacci := Liste ny.
```

Denne tomme liste kan fyldes ved hjælp af **tilføj:** :

```
fibonacci tilføj: 0.
fibonacci tilføj: 1.
fibonacci tilføj: 1.
fibonacci tilføj: 2.
fibonacci tilføj: 3.
fibonacci tilføj: 5.
fibonacci tilføj: 8.
fibonacci tilføj: 13.
```

Hvis vi skriver listen ud på skærmen:

```
Uddata skriv: fibonacci, stop.
```

ser vi:

```
Liste ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

I stedet for tilføj kan du også bruge ; til at tilføje elementer til en liste:


```
>> fibonacci := Liste ny ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Semikolonerne (;) er alle binære beskeder, som sætter en
værdi ind i listen.

## Kædning

Antag, at du har en liste som:

```
>> x := Liste ny ; 1 ; 2 ; 3.
```

Hvis du vil slette det første og det sidste element, ville din
besked være:

```
x tag-første tag-sidste.
```

Desværre fungerer den foregående notation ikke korrekt.
Beskeden **tag-første** returnerer listens første element, som
til gengæld bliver modtager af beskeden **tag-sidste**. Beskeden
**tag-sidste** sendes altså ikke til **x**, men i stedet til 2. En
mulig løsning på dette problem ville være at lave to separate
sætninger, som f.eks.: 

```
x tag-første.
x tag-sidste.
```

Det er dog temmelig upraktisk, især når du skal
slette mere end to elementer. Derfor tilbyder XOScript en
alternativ beskedstruktur til den slags situationer. I
**alternative** beskedstrukturer ignoreres objekternes svar,
og du får det modtagende objekt tilbage som svar, gang på gang.
En **alternativ** beskedstruktur indledes ved at sende
beskeden **gør** til et objekt, og den **alternative** beskedstruktur
kan afsluttes ved at sende beskeden **færdig**. I det
viste eksempel kunne det anvendes som følger:

```
>> x := Liste ny ; 1 ; 2 ; 3.
x gør tag-første tag-sidste færdig.
```

@api_List_collections

# Ordbøger

{{messages}}

**Både Liste og Ordbog er samlinger. Men i modsætning til en
liste har en ordbog **ingen** rækkefølge. En anden forskel mellem de to
er, at en ordbog består af objektpar. Det ene objekt fungerer som opslag (eller
nøgleord) for at finde det andet objekt. Et godt eksempel på en
sådan liste er en prisliste, som f.eks.:


```
>> menu := Ordbog ny
	sæt: ['£5'] ved: ['æbletærte'],
	sæt: ['£6'] ved: ['gulerodskage'],
	sæt: ['£3'] ved: ['fudge'].
```

Ligesom ved en liste bruges beskeden sæt:ved:
til at tilføje et objekt til en liste. Forskellen er, at der, i modsætning til
en liste, knyttes to objekter sammen. Det første objekt er, ligesom ved
en liste, det objekt, du vil gemme i en liste. Det andet
objekt er ikke dets position i samlingen, men det **opslag**,
som gør det muligt at hente det foregående objekt senere. Kort
sagt fungerer en ordbog lidt som en ordbog i bogform; ved hjælp af nøgleordet
kan betydningen findes. For eksempel for at hente prisen på en fudge fra
listen ovenfor:

```
>> price := menu ved: ['fudge'].
```

Du kan også bruge den korte notation:

```
>> price := menu ? ['fudge'].
```

Hvis de opslag, du bruger til at gemme objekter, er uden mellemrum
(og ikke kolliderer med andre foruddefinerede beskeder),
kan den næste notation også bruges:

```
>> menu := Ordbog ny
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Der er ingen tvivl om, at notationen ovenfor læses lidt mere naturligt.
For at spørge efter prisen på en
fudge kan følgende forenklede notation bruges:

```
>> price := menu fudge.
```

@api_Dict_collections

# Fil

{{messages}}

Objektet **Fil** giver grundlæggende adgang til filsystemet.
Du kan bruge dette objekt til at læse hele filer ind i en variabel på
én gang eller skrive variabler til filer på én gang. Læsning linje for linje
understøttes også. Det er de mest almindelige fil-I/O-operationer
i et scriptsprog. Avancerede filoperationer kræver
brug af FFI via server-pluginnet eller et separat IO-plugin.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Dato/tid

{{messages}}

Til en struktureret repræsentation af tid og dato bruger XOScript
objektet **Øjeblik**. Hvis et nyt Øjeblik-objekt udskrives på skærmen,
vises den aktuelle dato og det aktuelle klokkeslæt:

```
Uddata skriv: Øjeblik ny, stop.
```

Kan give noget i retning af:

```
2020-10-10 12:16:39
```

Det er også let at aflæse de enkelte tidskomponenter. Hvis det for
eksempel kun er nødvendigt at kende det aktuelle år, kan beskeden
**år** sendes til øjeblikket, og svaret vil så være et
Tal-objekt, der kun indeholder året:

```
>> m := Øjeblik ny.
Uddata skriv: m år, stop.
```

@api_Moment_system

# Program/StdOut

{{messages}}

Program-objektet repræsenterer den app, der kører i øjeblikket. Dette objekt
tilbyder funktionalitet til at udføre systemkommandoer, inkludere underprogrammer,
læse argumenter og meget mere. Alle systemrelaterede funktioner.

## StdOut

Uddata er standarduddataobjektet. Det har grundlæggende to metoder:
**skriv:** og **stop**. Beskeden skriv: bruges til at sende en tekst
til stdout, og beskeden stop udskriver et linjeskift.
I stedet for **stop** kan du også bruge \\n.

Eksempel:

```
Uddata skriv: ['Hello World'], stop.
```

resultat:

```
Hello World
```

## Moduler/plugins

XOScripts verden kan udvides med nye systemobjekter ved at
installere moduler. Et nyt systemobjekt kan føjes til XOScripts
verden ved at placere modulfilen (normalt en fil med endelsen .so)
i mappen mods. 

Når du sender en besked til det objekt, der stilles til rådighed via
plugin-modulet, indlæses det automatisk af XOScript.

Du kan også selv skrive plugins. Plugins skrives i
programmeringssproget C. Du kan finde et eksempel-plugin i kildekodepakken
under src/plugins/example.


## Refleksion

Der er forskellige måder at udforske
systemet på under programudførelsen. XOScript har et par metoder til
at finde ud af, hvilke objekter der findes, og hvilke beskeder disse objekter
reagerer på. For det første kan ethvert objekt spørges om, hvilken **type** det er,
men typer i XOScript kan ændres og er derfor upålidelige.

Det er også muligt at spørge Program-objektet, om et
givet objekt allerede findes i programmet:

```
Program Værktøj sand: { ... }.
```

Hvis et objektnavn
består af ét enkelt symbol, er det bedst at bruge
følgende notation for at undgå forvirring:

```
Program find: ['X'], sand: { ... }.
```

Ud over at spørge om objekter er det også muligt at spørge
Program-objektet om beskeder. Det kan for eksempel spørges, om
objektet **Tal** kender beskeden **mellem:og:**, på den måde,
der er vist nedenfor:

```
Program Number: ['between:and:'], stop.
```

@api_Program_system

# server

{{messages}}

Server-pluginnet i xoscript tilbyder funktionalitet til at
lave serverside-applikationer. For at indlæse server-pluginnet
bruger du:

```
Server initialiser.
```

For nemheds skyld anbefales det også at indlæse
filerne webtools.xo og template.xo.

```
Program brug: ['webtools.xo'].
Program brug: ['template.xo'].

```

## Serverindstillinger

Du kan angive følgende serverindstillinger:

```
	# standardværdier er angivet,
	# så hvis du ikke indstiller noget, bruges
	# disse værdier...

	Program 
	indstilling: ['max-postfields']
	værdi: 40.

	Program 
	indstilling: ['max-contentlength']
	værdi: 2000000. # 2MB

	Program 
	indstilling: ['max-time']
	værdi: 5000. # 5sec

```

## Hej verden

Her er et meget simpelt webprogram, som du kan bruge med en
standard-CGI-server som Apache2, NGINX, OpenHTTPD eller enhver anden
velkendt server.

```
#!/bin/xo

Server initialiser.
Program brug: ['webtools.xo'].

>> web-dokument := Webdokument ny.

web-dokument udskriv: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Hvis du ikke vil bruge Webdokument-objektet, er det helt i orden, men
så skal du selv skrive HTTP-headerne:

```
#!/bin/xo
Uddata skriv: ['Content-type: text/html; charset=utf-8 \n\n'], stop.
Uddata skriv: ['hej verden!'], stop.
``` 

## Forespørgsel

Objektet HTTP-Forespørgsel kan bruges til at hente GET-, POST-, COOKIE- og
UPLOAD-data:

```
>> http-forespørgsel  := HTTP-Forespørgsel ny.
>> search   := http-forespørgsel get: ['search']. # ?search=books
>> password := http-forespørgsel post: ['password']. # fra formularen
>> valgte := http-forespørgsel get-liste: ['sel[]']. #?sel[]=1&sel[]=2
>> valgte := http-forespørgsel post-liste: ['sel[]'].
>> cookie   := http-forespørgsel cookie: ['session-id'].
>> upload   := http-forespørgsel upload: ['file'].
>> midlsti := upload ? 1.
>> filnavn := upload ? 0.
```

## Maxpost/længde

Standardgrænsen for antal POST-felter er 40, og standardgrænsen for
indholdslængde er 2MB. Sådan konfigurerer du det anderledes for hvert enkelt script:

```
Program indstilling: ['max-contentlength'] værdi: 1. 
Program indstilling: ['max-postfields'] værdi: 1. 
```

{{note}}
Hvis indholdslængden overstiger maksimum, bliver
processen dræbt, fordi vi ikke længere kan være sikre på,
at indholdet er sikkert.
{{/note}}

Grænsen maxtime bestemmer den maksimale tid i ms
til at læse stdin/postdata.

```
Program indstilling: ['max-time'] værdi: 5000. # 5sec
```

Dette gælder kun for I/O-læsningen af POST-data og forhindrer
slowloris-lignende angreb. Hvis du virkelig vil begrænse
udførelsestiden for en hvilken som helst operation, så brug Program alarm:.

## Database

Database-objektet kan bruges til at sende forespørgsler til MariaDB/MySQL.
Sådan opretter du forbindelse til en database:

```
>> db := Maria-DB ny vært: ['localhost'],
	brugernavn: ['xo'],
	adgangskode: ['pass123'],
	databasenavn: ['xobase'],
	tilslut.

```

Sådan indsætter du en post:

```
>> søgeparametre := db forespørgsel: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parametre: ( Liste ny ; ['abc'] ; 12.35 ; 6 ). # parameteriserede forespørgsler

{  søgeparametre udfør. db bekræft. }
fang: { :e db rul-tilbage.  }, start.
```

Bemærk, at xoscript *kun* arbejder med transaktioner og aldrig laver autocommit.
Hvis autocommit ikke kan slås fra, får du en forbindelsesfejl.
Brug altid parameterbinding i forespørgsler, og tilføj aldrig brugerinput direkte
til SQL'en.

Hent det indsatte id sådan her:

```
Uddata skriv: ['INDSAT: '] + søgeparametre insert-id, stop. # indsat id
```

Sådan henter du poster:

```
>> søgeparametre :=
db
	forespørgsel: ['SELECT * FROM book order by id desc limit 2'], 
	hent: { :række 
		Uddata skriv: række id + [' '] + række description + [': '] + række price, stop.
	}. # hentning af rækker

```

## Sessioner

For at bevare data kan du gemme og hente data fra et sessionsobjekt.
Opret først et nyt **Webdokument**. Webdokument-objektet binder
forespørgslen, headerne, HTML'en og sessionen sammen. Det skyldes, at når du
besøger et websted med din browser, ser du kun HTML'en. Men
hele Webdokumentet består også af **headere**. For eksempel
indeholder de fleste HTTP-svar en header som: Content-type:text/html for at
fortælle browseren, at de data, der følger, skal vises som HTML
(og for eksempel ikke downloades som en fil). Sessioner er en måde at
gemme brugerdata mellem forespørgsler på. For at holde styr på disse data skal vi
sætte en cookie, og denne cookie sættes også via en header. Derfor
samles det hele i Webdokumentet (fordi det er det fulde
dokument, der indeholder både headere og HTML eller andre data).


```
# Først laver vi en ny Webdokument-instans
>> web := Webdokument ny.

# Nu starter vi en session; det genererer en header til en cookie og
# opretter en fil til dine data, knyttet til den cookie
>> sessionen := web start-session.

# Nu kan vi behandle sessionen som en Ordbog
sessionen userid: 123.
```

Sådan nedlægger du sessionen (ved logud):

```
web ødelæg-session.
```

## Headere

Webdokumentet giver dig også mulighed for at sætte andre velkendte headere.
For eksempel hvis du vil omdirigere brugeren til en anden URL:

```
web gå-til: ['/other.html'].
```

Under motorhjelmen genererer denne kommando også den HTTP-header, der sendes
med dine øvrige data eller HTML, for at få browseren til at navigere
til den angivne måladresse.

Sådan tilføjer du en brugerdefineret header:

```
web header: ( 
	HTTP-Header ny
	nøgle: ['Content-Length']
	værdi: 400
).
```

Sådan viser du en 404-side:

```
web ikke-fundet: ['Ups..'].
```


## Skabeloner

Standardskabelonsystemet er meget enkelt. Du behøver ikke at lære
en ny skabelonsyntaks. Desuden sikrer skabelonmotoren en reel adskillelse
mellem præsentation og forretningslogik.

Sådan opretter du en skabelon fra en fil:

```
>> tpl := web skabelon: ['templates/ux.tpl'].
```

Skabelonsystemet bruger markører. 
Der er tre typer markører: klipmarkører, indsætmarkører og
pladsmarkører. Grundideen er virkelig enkel: du klipper
områder ud, der er afgrænset af klipmarkører, og du kan indsætte dem i
områder, der er angivet med indsætmarkører. Du kan indsætte tekster i
pladsmarkører.

Med følgende skabelon som eksempel lægger vi
ædelstenen i smykkeskrinet og tilføjer et prismærke.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Det kan du gøre sådan her:

```
>> gem := tpl klip: ['gem'], kopiér.
gem price: 99.
tpl indsæt: gem ved: ['jewels'].
web udskriv: tpl rens.
```

Den sidste linje sender simpelthen skabelonen som tekst til klienten
sammen med de nødvendige HTTP-headere.

Resultat:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

For at levere filer, som brugere har uploadet, på en sikker måde kan du bruge passthru:

```
>> uploadet := ['smile.gif'].
Server videresend: uploadet præfiks: ['/uploads/images/'].
Program afslut.
```

Dette leverer det brugeruploadede indhold med den passende
mimetype. Kun godkendte mimetyper understøttes:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF og SVG.
SVG-, ZIP- og GZIP-filer sendes som download, fordi en SVG
kan indeholde scripts, som ellers ville køre på dit domæne.
Denne metode forhindrer TOCTOU-angreb, path traversal,
udførelse af ondsindet kode (injektion), symlinkangreb,
DDoS-angreb (filgrænse = 50MB), sniffingangreb og
forskellige andre sikkerhedsproblemer.


## JSON

Sådan koder du et objekt som JSON:

```
>> json := ( JSON jsonify: ( 
	Ordbog ny sæt: ( 
		Liste ny ; 1 ; 2 ; 3
	) ved: ['abc']
)).
```

Sådan afkoder du JSON til et xoscript-objekt:

```
>> ordbogen := ((JSON objekt: json) abc ? 1).
```

JSON med mere end 500 niveauers indlejring afvises som ugyldig.

Sådan sender du en Ordbog direkte ud som json med de korrekte headere:

```
web json: ordbogen.
```


## Regex

Du kan bruge regulære udtryk ved at oprette et mønster.
For eksempel til at matche href- og target-attributterne i hyperlinks:

```
Mønster ny: ['href="([^"]+)" target="([^"]+)"'].
```

Anvend nu mønsteret på emneteksten sådan her:

```
mønstret match: emne gør: { :m :x .... }
```

Fuldt eksempel:

```
>> emne := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> mønstret := Mønster ny: ['href="([^"]+)" target="([^"]+)"'].
>> resultat  := mønstret match: emne gør: { :m :x
	Uddata skriv: m, stop.
	Uddata skriv: x, stop.
	<- ['XXX'].
}.
Uddata skriv: resultat, stop.
```

## Netværk

Brug Netværk-objektet til at udføre en webforespørgsel.
Netværk-objektet sender altid en POST-forespørgsel, medmindre du sender Intet som
data; så sender det en GET-forespørgsel.


```
Netværk 
post: Intet 
til: ['https://redbeanphp.com'].
```

## Kryptering

Server-pluginnet leveres med kryptering baseret på XChaCha20 og Argon2.

Eksempel:

```
>> krypteret := Boks kryptér: ['hello'] nøgle: ['world'].
>> dekrypteret := Boks kryptér: krypteret nøgle: ['world'].
```

## Tokens

Sådan genererer du et kryptografisk sikkert token med en bestemt længde:

```
>> mintok := Boks token: 40.
```

Dette genererer et token på 40 tegn.

## Formatering

Format-objektet giver dig mulighed for at formatere data, f.eks. udfyldning eller
tilføjelse af nuller. Det bruger printf-syntaksen.

```
>> fmt := Format ny: ['%06.0f'].
fmt anvend: 56. # giver 000056
```

Et format kan indeholde én konvertering, og den skal passe til værdien,
ellers får du en fejl:

- `anvend:` med en tekst: `%s`
- `anvend:` med et tal: `%f`, `%e`, `%g` eller `%a`
- `anvend-heltal:` med et tal: `%d`, `%i`, `%o`, `%u`, `%x` eller `%c`

Værdier fra en forespørgsel er tekster. For at formatere en af dem som et tal
skal du først konvertere den:

```
fmt anvend: (http-forespørgsel get: ['amount']) tal.
```

## Kodere

Der findes flere kodere og afkodere.
URL-koderen klargør en url til brug i HTML som et link:

```
Server url-kode: ['https://example.com?a=6&b=1 2'].
```

For sikkert at indsætte brugerinput i din HTML uden at risikere XSS-injektioner
skal du altid bruge:

```
Server html-kode: ['<harmløs>'].
```

Bemærk, at skabelonmotoren altid udfører HTML-kodning,
når du skriver til en pladsmarkør. Så hvis du bruger skabelonsystemet,
behøver du ikke at bruge dette.

## Mail

For at sende en mail bruger du biblioteket mailtools.xo.

Eksempel:

```
Server initialiser.
Program brug: ['mailtools.xo'].

>> epost := HTML-E-mail ny.
>> img := epost vedhæft: ( Fil ny: ['myimage.png'] ).

epost
afsender: ['xo@xoscript.com'] navn: ['xo'],
til: ( Liste ny ; ['xo2@xoscipt.com'] ),
emne: ['xoxo'],
brødtekst: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), send.

```



## Linkning

Med beskeden forbind: kan du linke et eksternt bibliotek til
dit program ved hjælp af libffi. Se kapitlet om ffi for detaljer.


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

FFI leveres pr. platform/plugin, fordi det
er tæt knyttet til den underliggende systemarkitektur, hvilket
kernen ikke skal være.
Server-pluginnet tilbyder en kompatibel ffi/blob-implementering.
Som standard forbinder kernen sig til målplatformen
via stdin/stdout, begrænsede fil-I/O-tjenester og skallen (Program system:).
Yderligere integration leveres af ffi/blobs via applikationsorienterede
plugins som server-pluginnet.

FFI står for Foreign Function Interface. Det giver dig mulighed for at bruge funktionalitet, som andre har skrevet i
andre programmeringssprog, og som leveres via DLL-filer, SO-filer eller Dylib-filer. Det kan
være mange forskellige funktioner, og der er et enormt udvalg af funktionalitet tilgængelig på denne måde.
Lad os starte med et eksempel:

```
Server forbind: (
 Liste ny ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Liste ny ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s frigiv.
```

Resultatet af denne kode er, at du ser følgende på kommandolinjen:
FFI has 3 letters.
Nu tænker du sikkert: "Det er meget kode til noget så simpelt."
Kunne vi ikke bare løse dette med en Gui show-kommando? Svaret er et rungende ja!
Men dette er ment som et illustrativt eksempel.
FFI bruges normalt til mere komplekse opgaver, men de er ikke gode
eksempler, så jeg valgte noget trivielt.

Argumenterne til link-metoden:

- Argument #1: Den DLL- eller SO-fil, du vil bruge.
- Argument #2: Den funktion i filen, du vil linke.
- Argument #3: En liste med navnene på datatyperne for funktionens argumenter.
- Argument #4: Navnet på funktionens returtype.
- Argument #5: Navnet på det objekt, du vil linke funktionen til (hvis det ikke findes, oprettes det
automatisk).
- Argument #6: Den besked, som funktionen skal linkes til.

I eksemplet ovenfor vil vi linke funktionen printf fra libc.so. Du kan finde
navnene på datatyperne i dokumentationen til den software, du linker til. De tilgængelige typer er:
void, pointer, float, double, int, uint, char, uchar, intX og uintX,
hvor X kan være 8, 16, 32 eller 64.

Disse typer angiver det antal bytes, der kræves for at gemme dataene. For printf linker vi til et
nyt objekt kaldet Printf og beskeden template:number:. Du oversætter den eksterne
funktion til XOScript-dialekten, før du bruger den. Beskeden template:number: forventer en
buffer med skabelonteksten som første parameter. Vi opretter denne buffer med et Blob-objekt, som
giver dig mulighed for manuelt at allokere hukommelse. Du er selv ansvarlig for at frigive denne hukommelse bagefter
med beskeden frigiv.

Du kan fylde en hukommelsesblob på forskellige måder. I vores eksempel fylder vi den med tekst, så vi bruger
beskeden utf8: (UTF-8 er en kodning, der omdanner tekst til bytes). Du kan også fylde en blob med
bytes: ved at overføre en liste med byteværdier. For at læse indholdet af en blob bruger du fra:længde:.
Du får bytene tilbage som en liste. Du kan endda oprette en C-struct med en Blob ved hjælp af
beskeden struct:, hvor du overfører en sekvens af C-typer. Det kan være nødvendigt, når du kalder en C-funktion
i et eksternt softwarebibliotek, som forventer en pointer til en struct.

{warning}
Du skal selv frigive blobs.
Blobs ryddes ikke op af garbage collectoren.
{/warning}

Da blobs kan udveksles med eksterne funktioner fra biblioteker,
kan de ikke ryddes op automatisk af garbage collectoren (de kan stadig være i brug af
eksterne funktioner, eller disse eksterne funktioner vil måske selv
frigive dem). Derfor skal du selv frigive blobs, hvis det er nødvendigt.

Sådan frigiver du en blob:

```
minblob frigiv.
```

Sådan frigiver du en struct:

```
minstruct frigiv-struct frigiv.
```

For en struct skal du altså sende to beskeder: frigiv-struct og frigiv for
at frigive hukommelsesblokken.

@api_Blob_fficonnect
