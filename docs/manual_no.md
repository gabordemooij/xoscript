# Grunnleggende

{{messages}}


Velkommen til XOScript
XOScript-prosjektet har som mål å lage et skriptspråk som er enkelt og etterprøvbart.
Enkelt betyr ikke nødvendigvis lett.
Et kjent programmeringsspråk kan være lettere å bruke enn XOScript.
Her betyr enkelhet noe annet:
å kunne danne en fullstendig mental modell av språket og hvordan det oppfører seg.

XOScript er laget for å få plass i hodet ditt.
Grammatikken og antallet begreper er bevisst holdt små.
Det finnes ingen klasser; objekter kan utvides direkte.
Objekter overføres som referanser, kopiering skjer eksplisitt,
og funksjoner har ett enkelt utgangspunkt.

Noen av disse valgene skiller seg betydelig fra de vanlige språkene.
XOScript har for eksempel ikke noe typesystem, og bruker dynamisk skop.
Beskjeder som ikke kan håndteres, blir ignorert i stedet for å utløse et unntak.
Disse valgene har konsekvenser og er ikke ment å eliminere feil.
De er ment å holde språkets underliggende modell liten og konsistent.

XOScript kan også lokaliseres, slik at det blir mulig å uttrykke forretningsregler
på et naturlig språk og eventuelt dele dem med ikke-tekniske interessenter.

Etterprøvbarhet betyr å bruke den samme filosofien på implementasjonen.
Kjøremiljøet er skrevet i C, med en liten håndskrevet lekser, parser og trevandrer.
Standardbiblioteket og kjøremiljøet speiler i stor grad strukturen i språket,
slik at forholdet mellom XOScript-kode og implementasjonen er relativt direkte.

Testene er også tett knyttet til dokumentasjonen.
Hver metode bør ha en tilhørende test som kan tas inn i håndboken,
noe som bidrar til å holde dokumentasjonen i takt med implementasjonen.

XOScript er ikke ment å konkurrere med de vanlige språkene på
funksjonalitet eller kjennskap. Det utforsker et annet mål:
et programmeringsmiljø som en utvikler kan forstå som en helhet.

Håpet er at et lite språk og en liten
implementasjon gjør det praktisk mulig å forstå programvare
fra byte til objekt, fra syntaks til kjøremiljø, og å skrive kode med
trygghet fordi du forstår både hva som skjer i
skriptet og hva som skjer under panseret.

Arkitekturen i et xoscript-serveroppsett
er enkel, men likevel fleksibel.

{{architecture.png}}

For å bruke xoscript som serverspråk må du installere
servertillegget i en mappe som heter /mods/server. 

Dette er fordi vi ønsker å
skille kjernespråket fra serverspesifikk funksjonalitet,
i motsetning til for eksempel PHP eller Python. Ellers måtte vi levere
hele kjøkkenbenken til alle uten noen hensikt, noe som rett og slett er tåpelig.
Du kan også installere andre moduler hvis du vil. Systemet er svært
fleksibelt.

Noen funksjoner er dessuten bedre implementert i selve skriptspråket,
som maler og økthåndtering, så i tillegg
leverer vi bibliotekene template.xo og webtools.xo for din bekvemmelighet.
Grunnen til alt dette er at vi ikke vet hvordan du ønsker å
bruke xoscript. Du kan bruke det som et skriptspråk på serversiden,
men også for grafiske brukergrensesnitt, innebygde enheter eller bare satsvis behandling.
Selv om du bruker det som et skriptspråk på serversiden (som for
tiden er et av de viktigste bruksområdene), kan det hende du likevel vil
bruke en annen malmotor eller en annen økthåndterer.
Hvem er vi til å bestemme at du skal bruke våre?

En av fordelene ved å bruke vår egen malmotor er likevel at
du ikke trenger å lære ekstra syntaks for å lage maler.
Standardmalmotoren som følger med xoscript, har 100 %
atskillelse mellom presentasjon og logikk. I stedet for spesiell
malsyntaks bruker den ganske enkelt et svært fleksibelt system med plassmarkører.
For mer informasjon, se kapitlet Server.

Merk at hvis du ikke vil bruke standardmalmotoren eller
standard-webverktøyene, sier det seg selv at du må levere
dine egne.

Hvis du kjører webserveren din i en chroot, et jail eller en annen type sandkasse,
må du også installere avhengighetene til xo i det miljøet. Du kan
se hvilke biblioteker du trenger ved å bruke ldd (se manualsiden for Linux eller BSD).
Hvis du vil bruke skallkommandoer i xo-skriptene dine, må du også kopiere et skall
(som bash eller ksh) til dette miljøet.

Vi vil også nevne at vi tar bakoverkompatibilitet svært alvorlig.
Det finnes til og med en egen funksjon for bakoverkompatibilitet som heter
'version'. Generelt sikter vi mot at koden din skal kunne kjøre for alltid. Du vil altså
aldri måtte oppdatere koden din for å forbli kompatibel med nyere versjoner
av xoscript. Målet vårt er: skriv én gang, kjør for alltid.

Resten av denne håndboken er viet til å forklare programmeringsspråket
xoscript i detalj. Serverskripting blir behandlet i kapitlet
som heter Server. Hvis du er en erfaren programvareutvikler, vil du kanskje
hoppe over noen kapitler, fordi noen av dem er litt for detaljerte eller
ligner svært mye på generell programmeringspraksis. Dere som
allerede har erfaring med flere andre programmeringsspråk,
gjør derfor best i å behandle denne håndboken som et oppslagsverk.

## Oppsett på Linux

Last ned apache2 og mariadb:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Last ned xoscript.
Erstatt X med riktig versjonsnummer!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Kopier filene til webroten og /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Rediger apache2-konfigurasjonen din:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Erstatt Virtualhost med:

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

Lag en testside:

```
sudo nano /var/www/html/test.xo
```

og skriv et lite testprogram:

```
#!/bin/xo
Server initialiser.
Program benytt: ['webtools.xo'].
>> web := Webdokument ny.
web skriv-ut: ['Hello World'].
```

Gi apache2 tillatelse til å kjøre programmet ditt via CGI:

```
sudo chmod uog+x /var/www/html/test.xo
```

Start apache2 på nytt:

```
sudo systemctl restart apache2
```

Gå til testsiden din i nettleseren:

```
http://localhost/test.xo
```

Du skal se:

```
Hello World
```


## Oppsett på OpenBSD

Rediger /etc/httpd.conf og legg til:


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

Hvis du vil bruke SSL:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

For å beskytte nøkkelutvekslingen mot kvanteangrep
velger du chifferet mlkem:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Legg til xo-programfilen og modulene, samt eventuelle avhengigheter, i
chroot-miljøet (finn dem med ldd).

## Kjøre eksempler


Slik kjører du et av eksempelprogrammene i pakken:

```
./example.sh <name> <Linux/OBSD> [clean]
```

For eksempel, slik kjører du FizzBuzz-eksempelet på Linux:

```
./example.sh fizzbuzz Linux
```

Slik kjører du det samme eksempelet på OpenBSD:

```
./example.sh fizzbuzz OBSD
```

Slik kjører du eksempelet med en ren bygging:

```
./example.sh fizzbuzz OBSD clean
```

## Enhetstester

Slik kjører du enhetstestene:

```
./runtests.sh
```

Slik kjører du enhetstestene uten å bygge (bare testing):

```
./runtests.sh nobuild
```

## Bygging

Slik bygger du fra kildekode på Linux:

```
make clean
ISO="en" make
```

På OpenBSD:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

Slik bygger du servertillegget på Linux:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

Slik bygger du servertillegget på OpenBSD:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Hallo verden

Når filen er overført til datamaskinen din, kan du pakke den ut
og starte xo med følgende kommando:

```
xo
```

For å kjøre et XOScript lagrer du programmet som en fil med endelsen -xo
(valgfritt). Skriv i tillegg inn filnavnet til programmet ditt
etter XOScript-kommandoen:

```
xo myprogram.xo
```

Når du kjører en XOScript-kommando med programfilen din som
parameter, vil xo lese og kjøre programfilen.

{{note}}
Du kan også starte programmet ditt ved å dra det til xo-ikonet.
{{/note}}

{{warning}}
På noen systemer må du på forhånd gi xo tillatelse til å laste inn dynamiske
biblioteker.
{{/warning}}

Tradisjonen tilsier at det første programmet i ethvert nytt programmeringsspråk
skal være en slags hilsen til verden. I XOScript ser et slikt
**Hallo verden**-program slik ut:

@test598

Når denne teksten er lagret i en fil, for eksempel hello.xo, kan den kjøres
slik: .

xo hello.xo

Hello world


Du kan se utdataene fra programmet i det svarte vinduet ovenfor.
Gjennom hele denne håndboken brukes den samme visningen for å vise
utdata.

{{note}}
Utdata skrives med stor U.
Generelt begynner objekter med stor bokstav,
med mindre de fungerer som en instans (har ingen egne
metoder, bare data). Dette gjenspeiler konvensjonene for klasse og instans
i andre programmeringsspråk.
{{/note}}


## Syntaks 

XOScript er et *rent* *objektorientert* programmeringsspråk. Dette betyr
at xoscript oppfatter alt som et objekt, og derfor finnes det
ingen andre *datatyper*. Det finnes i hovedsak tre grunnleggende handlinger
i et program som er skrevet i XOScript: *tilordning*, *sending av beskjeder*
og *svar*. Utveksling av beskjeder mellom objekter er kjernen i
et XOScript-program. De tre handlingene er illustrert
nedenfor:


Handling        | Eksempel
--------------- | --------
tilordning      |  \>\> x := 1. 
unære beskjeder | x partall?.
binær beskjed   | 1 + 2.
nøkkelordbeskjed | x fra: 0 lengde: 10.
svar            | <- answer.  


Dette kapitlet gir deg et generelt inntrykk av språket XOScript
og beskriver de grunnleggende prinsippene. XOScript er et lite språk og
bygger på tre handlinger (se illustrasjonen), som tilsvarer
omtrent seks grammatikkregler. Det er alt som skal til for å mestre
språket.

Ikke bekymre deg hvis ting ikke er umiddelbart innlysende: alle byggesteinene
blir gjennomgått i neste kapittel (3), og de grunnleggende reglene blir
gjentatt. Dette kapitlet fungerer derimot hovedsakelig som en generell
introduksjon til språket. De grunnleggende prinsippene blir kort
forklart og illustrert med flere relevante eksempler. Eventuelle manglende
detaljer blir beskrevet senere.

Kommentarer i XOScript innledes med symbolet \#. Følgende linje
blir derfor ignorert:

```
# this is just a comment
```

## Variabler

For å tilordne
en variabel bruker du symbolet for variabeldeklarasjon: >>. Navnet på en
variabel kan inneholde alle tegn unntatt: <-, :=, mellomrom,
punktum, komma, kolon, anførselstegn [' '] og parenteser ().
Videre kan en variabel ikke strekke seg over flere linjer. Merk
at en variabel ikke kan begynne med et tall eller et minustegn.

Dette er eksempler på gyldige variabler:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dollar'].
>> +plus := Sann.
>> user-password := ['Pssst!'].
```

Ugyldige variabler er for eksempel:


```
>> -123 := ['negative number'].
>> password of user := ['Classified'].
>> password.of:user := ['Classified'].
>> ,x := 10.
```

{{note}}
Du trenger ikke å beskytte noe tegn
(inkludert anførselstegn, doble anførselstegn og
tekstgrenser) i
en tekstliteral, så lenge det ikke
skaper tvetydighet for lekseren.
{{/note}}

Etter at en variabel er deklarert, kan den brukes fritt. Dette betyr
at det bare er nødvendig å bruke deklarasjonssymbolet første gang
du bruker variabelen (deklarasjonen).

For å være mer presis kan du ikke bare begynne å tilordne en verdi til
variabelen din *(x := 2)*, ettersom du først må deklarere variabelen *(\>\>
x := 2)*. Når den først er deklarert, kan du derimot endre verdien
uten å bruke deklarasjonssymbolet*(\>\> x := 2. x := 3.)*.

Merk at det er obligatorisk å tilordne en verdi til en variabel når
den deklareres. I motsetning til andre programmeringsspråk har du ikke lov
til å deklarere en variabel uten verdi. Det er avgjørende å knytte
hver variabel eksplisitt til en startverdi. Du står likevel fritt til å initialisere
variabelen med objektet **Ingenting**. I så fall kan variabelen
betraktes som tom *(\>\> x := Ingenting.)*. Kort sagt er det ikke tillatt å deklarere en
variabel uten startverdi. Så

```
>> x.
```

er ugyldig og vil gi en feilmelding.

{{note}}
xoscript bruker dynamisk skop for
variabler. For detaljer, se kapitlet Funksjoner.
{{/note}}


## Literaler

XOScript oppfatter alt som et objekt, det vil si alle tall, tekster
og kodefragmenter. Tall som 1, 2, 100, -999 og 1,234 er
Tall-objekter. All tekst mellom enkle anførselstegn er Tekst-objekter.
Alle kodefragmenter som er samlet mellom krøllparenteser {...}, er
Funksjon-objekter.

Literal         | Rotobjekt    | Eksempel
--------------- | ------------ | ----------
tall            | Tall         | 1,2,3... 
tekster         | Tekst        | \['hello'\]
funksjon        | Funksjon     | { 1 + 2. }.
                
     
Objekter som tall og tekster har alltid sitt opphav i et rotobjekt.
For eksempel stammer alle tall fra objektet **Tall**. Alle
tekster stammer fra **Tekst**, og alle kodefragmenter fra **Funksjon**.
Alle disse objektene stammer i sin tur fra **Objekt**, som faktisk er
rotobjektet for alle objekter.


## Beskjeder

Å programmere i XOScript betyr i bunn og grunn å
sende beskjeder til objekter. Den generelle notasjonen for å sende en beskjed til
et objekt er som følger:

```
<object> <message>
```

For å finne ut om for eksempel tallet **2** er et partall, sendes
beskjeden **partall?** til objektet **2**:

```
2 partall?
```

Svaret blir **Sann** (igjen et objekt). Ukjente beskjeder blir
vanligvis ignorert av objekter, så det oppstår ingen feil. Noen objekter (for eksempel
tall eller tekster) svarer på en ukjent beskjed på en forhåndsdefinert måte
(mer om dette senere).

Et objekt kan motta tre typer beskjeder. 

Type            | Antall argumenter
--------------- | -------------------
Unær            | 0      
Binær           | 1     
Nøkkelord       | 1+    


For det første finnes det **unære
beskjeder**, se eksempelet ovenfor, som ikke har argumenter. For det andre
finnes det **nøkkelordbeskjeder**, som har ett eller flere argumenter,
for eksempel:

```
>> x := Tall mellom: 1 og: 10.
```

I dette tilfellet sendes beskjeden **mellom:og:** til **Tall**, som
er rotobjektet for alle tall. Resultatet blir et tilfeldig tall
mellom 1 og 10. Til slutt finnes det **binære beskjeder**, som har
bare ett tegn og ett argument:

```
2 + 3
```

Dette ser ut som et regnestykke, men det er egentlig bare en annen beskjed.
Beskjeden **+** sendes til **2** med argumentet **3**, noe som gir
svaret **5**. Binære beskjeder kan skrives uten kolon.

Binære beskjeder kan kjedes:

```
>> x := 3 + 2 - 1.
```

I dette fragmentet sendes **+ 2** først til **Tall**-objektet **3**, noe som
gir Tall-objektet **5**, og deretter sendes **-1** til dette
tallet. Oppmerksomme lesere har rett i at dette
protokollet avviker fra den vanlige matematiske rekkefølgen for
operatorer. XOScript ser bort fra den matematiske rekkefølgen til fordel for
konsistens i beskjedsystemet. Derfor blir regnestykket:

```
2 + 3 * 5 = 25
```

ikke 17.

Dette er tilsiktet. Parenteser kan brukes til å endre rekkefølgen:

```
2 + (3 * 5) = 17
```

De fleste objekter returnerer seg selv som resultat når de mottar en bestemt
beskjed. Dette er nyttig fordi det oppmuntrer til videre dialog med dette
objektet ved å sende det en oppfølgende beskjed:

```
Utdata skriv:
[' hello '] trim store-bokstaver.
```

```
HELLO
```

Her sendes to beskjeder til **Tekst**-objektet: **trim**, etterfulgt
av **store-bokstaver**.

I følgende fragment er det nødvendig å bruke et komma for å angi
at en ny beskjed kommer. Hvis ikke blir XOScript forvirret.

```
Utdata skriv: ['Hello!'], stop.
```

Først sendes beskjeden **skriv:** til blyantsymbolet, etterfulgt av
**stop**. Uten kommaet ville XOScript tro at du ønsker å sende
**stop** til **tekst** **Hello!**, noe som er meningsløst.

Rekkefølgen beskjeder behandles i, er som følger: fra venstre mot høyre;
begynn med beskjeder i parenteser, etterfulgt av unære beskjeder. Deretter
binære beskjeder, og til slutt nøkkelordbeskjeder. Se eksempelet
nedenfor:

```
Utdata skriv: 0.5 avrund + (2 - 1), stop.
```

XOScript leser alltid fra venstre mot høyre: først sendes beskjeden **skriv:**
til Utdata, etterfulgt av beskjeden **stop**. Inne i
selve argumentet leser XOScript fra venstre mot høyre, altså først **0.5 avrund**
og deretter **+**.

{{note}}
Beskjeden stop legger til et linjeskifttegn i teksten.
Navnet på denne beskjeden er inspirert av telegrafsystemer.
Meldinger i telegrafsystemer 
brukte ofte ordet STOP for å markere slutten på en setning
(fordi tegnsetting var upålitelig eller kostbar).
{{/note}}

Dessuten har **avrund** forrang foran **+**, fordi den er en
**unær beskjed**. På grunn av parentesene beregnes **2 - 1**
først, og deretter legges **1** til resultatet av **0.5 avrund** (1).

Hele prosessen gir resultatet **2**, som også er det skrevne
svaret. Etter kommaet følger beskjeden stop, som flytter markøren
til en ny linje. Den beste måten å forstå rekkefølgen i
XOScript-programmer fullt ut på, er selvsagt gjennom øvelse.

Det er verdt å merke seg at i XOScript, i motsetning til mange andre programmeringsspråk,
er mellomrom en grunnleggende del av syntaksen. Særlig
når det gjelder binære beskjeder, kan mellomrom skape en del
forvirring. Bruk alltid et mellomrom etter en binær beskjed. Du kan ikke
feste et tall direkte til beskjeden, for eksempel: 

```
3 + 2
```

er forskjellig fra 

```
3 +2
```

Det første eksempelet (**3 + 2**) sender
beskjeden **+** til tallet **3** med tallet **2** som argument.
Resultatet blir i dette tilfellet **5**. I det andre eksempelet (**3 +2**)
sendes den unære beskjeden **+2** til tallet **3**. Avhengig av
sammenhengen kan det gi et helt annet resultat.

## Ikke-eksisterende metoder

Når du sender en beskjed til et objekt, kalles funksjonen som er
knyttet til objektet under det beskjednavnet. Hvis du sender en beskjed
som ikke blir forstått, vil mottakerobjektet ignorere beskjeden din
og i stedet returnere en referanse til seg selv for videre kommunikasjon.
Dette kalles tolerant beskjedoverføring.

Eksempel:

```
Utdata skriv: Objekt blah, stop.
```

Dette gir ingen feil. Det skriver ganske enkelt ut teksten **Objekt**.


## Kontrollflyt

I XOScript er det ikke behov for egne grammatikkregler for *løkker* og
*if-setninger*. En if-setning er bare en enkel **sann:**- eller **falsk:**-beskjed
til enten et **Sann**-objekt eller et **Falsk**-objekt:

```
2 partall? sann: {
	Utdata skriv: ['Two is an even number'], stop.
}.
```
I det forrige eksempelet sendes beskjeden **sann:** til **Sann** (svaret
på spørsmålet: er 2 et partall?). Som argument sendes et ekstra
kodefragment med: et **Funksjon**-objekt. Denne funksjonen skriver på
skjermen at 2 faktisk er et partall.

Det er heller ikke behov for egne skriveregler for en *løkke*. For å
kjøre et kodefragment tre ganger sender du ganske enkelt **\*** med argumentet
**3** til den **Funksjon**:

@test5

I dette kodefragmentet er **i** indeksen. Første gang Funksjonen
kjøres, er **i** lik 0, neste gang den kjøres, er **i** = 1, og
så videre.

La oss se på et annet eksempel. Når en omregningstabell skal
skrives ut fra *kJ* (kilojoule) til *kcal* (kilokalori) i steg på 100,
ser den riktige notasjonen slik ut:

@test599

Her overføres nummeret på den gjeldende linjen til parameteren
**:line**. I begynnelsen av en funksjon defineres funksjonsparameterne.
Ubrukte parametere forblir tomme (**Ingenting**). Parametere
plasseres alltid i starten av funksjonen, rett etter den første
krøllparentesen, og innledes med et kolon.

Beskjeden **mens:** er en kombinasjon av en *løkke* og en *betingelse*.
To funksjoner kan kobles sammen med beskjeden **mens:**. Mottakerfunksjonen
fortsetter å kjøre helt til funksjonen etter kolonet gir et negativt
resultat. Eksempel:

@test600

I kodefragmentet ovenfor legges **1** til **x** så lenge
**x** er mindre enn **5**. Når dette ikke lenger er tilfelle, svarer den andre
funksjonen med **Falsk**, og dermed avsluttes kjøringen av den
første funksjonen. Merk at **x** er definert utenfor
funksjonen og er en global variabel. For å lære mer om skopregler,
se kapitlet om Funksjoner.

## Tekstinterpolering

Listen over *kJ/kcal* kunne vært gjort mer
presentabel. Helst skulle listen sett slik ut:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Når du gjør de ønskede utdataene om til en mal, kan notasjonen
være:

```
number1 kJ ➞ number2 kcal
```

Dette betyr at **number1** står for kJ-verdien og **number2** for
kcal-verdien. Slik fungerer tekstinterpolering i XOScript. Det
trengs ingen egne grammatikkregler for dette i XOScript. Send ganske enkelt
ordet som skal erstattes, til teksten, med erstatningsteksten
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

Denne erstatningsregelen gjelder for hver udefinert beskjed som mottas
av et **tekst**-objekt. Hver beskjed som ikke blir gjenkjent av
**tekst**-objektet, tolkes slik: *erstatt beskjedteksten
med teksten i beskjedens argument.* Du kan tilpasse
programmet slik:


@test601


For å unngå forvirring om hvilke beskjeder som kan eller ikke kan brukes som
erstatning, er det best å innføre en malmarkør som &lt; &gt;
for tekstbitene i malen som
skal erstattes.

## Returverdier

For å svare på en beskjed brukes returpilen
(*<-*). Følgende eksempel viser hvordan du lager en oppgave
som beregner en prosentandel:

@test602

Etter at oppgaven er definert og tilordnet variabelen **percentage**,
sendes beskjeden **bruk:og:** med argumentene **100** og **7**.

Dette kjører oppgaven på **100** og **7**, det vil si 7 % av 100.
Ved hjelp av returpilen returneres svaret fra oppgaven tilbake
til hovedprogrammet.

## Utvidelse

Selv om denne koden er gyldig, har den en ulempe,
fordi rekkefølgen på argumentene må huskes. Så hvorfor ikke
skrive det slik: *7 percent of: 100 *? Det ville sett mye mer
*naturlig* ut. For å gjøre dette mulig må vi tilpasse foreldreobjektet til
**7**, som er **Tall**-objektet, slik at det forstår
beskjeden **percent of:**. Dette oppnås ved å sende **ved:gjør:** til
Tall-objektet, slik:

@test603

Ettersom prosentandelen i dette tilfellet er selve tallet, viser vi til selv,
nøkkelordet *selv*. Kort sagt betyr symbolet selv: *send denne
beskjeden til meg-selv*.

# Objekter

{{messages}}

I tillegg til å justere og utvide eksisterende objekter kan du også lage
nye objekter selv, ganske enkelt ved å sende beskjeden **ny**. Anta at du
vil lage et fakturaobjekt som håndhever en nummereringsrekkefølge;
i så fall trenger du først et fakturaobjekt.

Ettersom hvert objekt stammer fra et annet objekt, som i sin tur
til slutt har sitt opphav i rotobjektet for alle objekter, kalt Objekt,
må det tas et valg om hvilket av disse andre objektene det
nye objektet ditt skal bygge på. Det nye objektet ditt arver alle egenskapene til
objektet det bygger på, altså objektet som beskjeden **ny**
opprinnelig ble sendt til.

I dette eksempelet foretrekkes et ganske nøytralt objekt, et uten for
mange arvede egenskaper. Det gjør valget enkelt, for i så
fall kan det nye objektet baseres på selve rotobjektet, som er
**Objekt**. Notasjonen for det tiltenkte fakturasystemet blir da
som følger:

@test604

Det gjeldende fakturanummeret lagres i objektet, og derfor står
nøkkelordet **egen** foran det. Dette kalles en *egenskap*;
flere detaljer følger.

Noen virksomheter foretrekker å ha årstallet med i fakturanumrene.
I så fall kan du lage et nytt fakturaobjekt som bygger på et
tidligere fakturaobjekt, men som gir brukeren mulighet til å
angi et bestemt år:

@test605

Det er ikke nødvendig å skrive implementasjonen for beskjeden **tall**
på nytt, siden den arves fra det tidligere skrevne **fakturaobjektet**;
dermed kan gammel kode gjenbrukes. XOScript mangler begreper
som klasser og andre beslektede begreper. Dette betyr at objekter
bare kan arve fra andre objekter, noe som også kalles *prototypisk
arv*.

Så tilbake til egenskapene. Objektegenskaper kan bare nås
*innenfra objekthierarkiet*, så disse egenskapene
kan ikke sees av andre objekter.

I motsetning til andre programmeringsspråk er alle egenskapene til objekter
utelukkende synlige for objektet som har opprettet egenskapen, og for
avledede objekter. 

En vanlig teknikk er å bruke et objekt som en slags *blåkopi*,
slik det for eksempel er tilfellet med fakturaene som ble omtalt tidligere.
Et annet godt eksempel er **Point**. La oss si at du lager et
dataprogram som utfører beregninger ved hjelp av punkter på et kart. Du
kan utvikle objektet **Point** med egenskapene en
x-koordinat og en y-koordinat, som gjøres tilgjengelige for
omverdenen gjennom beskjeder:

@test606

Beskjeden **=** sammenligner de to punktene ved hjelp av beskjeden **og:**. Den
første sammenligningen gir enten **Sann** eller **Falsk**. Dette er boolske
objekter. Når du sender beskjeden **og:** til et Sann-objekt, og
argumentobjektet etter kolonet også er **Sann**, får du
igjen **Sann** som svar. Når en av dem er **Falsk**, får du
svaret **Falsk**. Merk at det ene punktet ikke kan lese koordinatene til
det andre. Det er nødvendig å sende en beskjed til det andre punktet for å be
om disse dataene: **x-coordinate** og **y-coordinate**. Som allerede
forklart kan egenskaper jo bare hentes innenfra
selve objektfamilien. 

Merk at beskjeden **=** brukes her til å utføre sammenligningen av punktene.
Man kunne like gjerne ha brukt en annen beskjed, for eksempel
**is:** eller **equal:**, men det virket passende å gjenbruke tegnet **=**
i dette tilfellet.

## Arv

Du kan gjenbruke tidligere skrevet kode for å lage et hierarki
av objekter. For eksempel:

```
>> Animal := Objekt ny.
>> Dog := Animal ny.
>> Poodle := Dog ny.
```

I dette tilfellet arver **Dog** all oppførsel og alle egenskaper
fra **Animal**, og objektet **Animal** arver i sin tur all oppførsel fra
**Objekt**, rotobjektet for alle objekter.


## Overstyring


I følgende eksempel lages en ny type liste:
**Combination**, der hvert element garantert er unikt.
Funksjonene til listen gjenbrukes gjennom arv:

@test607

Legg merke til hvordan den andre **red** blir utelatt fra listen.

Av og til kan det være nødvendig å overstyre oppførselen til et objekt.
For eksempel når man legger sammen tall og må ta hensyn til
måleenheter. I følgende eksempel lages objektet **Size**.
Dette objektet returnerer et tall som under addisjonen tar
hensyn til enheten til tallet som skal legges til. **Tall**-objektet
sjekker om det dreier seg om *tommer* eller *fot*. Programkoden
kan se omtrent slik ut:

@test608

## Rekursjon

I det forrige eksempelet blir pluss**tegnet** overstyrt. Merk
at selve den endelige addisjonen fortsatt må utføres, og det
skjer faktisk på følgende linje:

```
>> answer := selv + (tall x factor).
```

Hvordan forstår XOScript at dette pluss**tegnet** viser til
den opprinnelige logikken for addisjon?** En annen tolkning kunne for eksempel
være at XOScript gang på gang sender den samme beskjeden til det samme
objektet, noe som i sin tur ville føre til en **uendelig løkke**. Det er
tydeligvis ikke meningen. Så snart du sender en beskjed til et objekt
som ville kjørt nøyaktig den samme koden, vil XOScript i dette tilfellet
forstå at det er den underliggende, overstyrte beskjeden som menes. Programmet
ditt er dermed automatisk beskyttet mot denne formen for uendelige
løkker. Når det derimot faktisk er målet ditt å kjøre den samme funksjonen fra
den gjeldende funksjonen, må du først sende beskjeden
**rekursiv**. I så fall blir resultatet en uendelig
løkke. Det finnes likevel nyttige bruksområder for rekursive oppgaver,
for eksempel hvis du vil beregne fakultetet av et gitt
tall. Legg i så fall ganske enkelt til beskjeden **factorial** i
Tall:

@test609

Dette krever rekursjon. Oppgaven som er knyttet til
beskjeden **factorial**, må faktisk kjøres på nytt inne i den funksjonen.
Det er altså nødvendig å kalle fakultetsfunksjonen fra innsiden av
selve fakultetsfunksjonen. Som regel vil XOScript forhindre dette,
på grunn av faren for å havne i en uendelig løkke. Av denne grunn
er det avgjørende å sette ordet **rekursiv** foran beskjeden. Dette
gjøres for å gjøre XOScript oppmerksom på at det er din
hensikt å kjøre den samme oppgaven, og at du ikke har gjort en feil.

## Klasselignende objekter

Selv om xoscript ikke har klasser, er det enkelt å etterligne
klasselignende oppførsel. Overstyr ganske enkelt beskjeden ny.

```
>> Animal := Objekt ny.
Animal ved: ['ny'] gjør: {
	<- selv ny initialiser.
}.

Animal ved: ['initialiser'] gjør: {
	egen sound := ['?'].
	egen legs  := 4.
}.
```

I kodefragmentet ovenfor lager vi et objekt som heter Animal.
Dette objektet fungerer som en *blåkopi* for alle slags dyr,
som hunder og katter. Foreldreobjektet Animal skrives
med stor A for å vise at dette er et klasselignende objekt.
Deretter overstyrer vi beskjeden ny ved å skrive vår egen ny-metode.
I dette tilfellet sender den beskjeden ny til selv, etterfulgt av beskjeden
init. Fordi xoscript blokkerer rekursjon som standard, fører ikke dette til
en uendelig løkke. I stedet sendes beskjeden ny til foreldreobjektet
(Objekt), noe som gir en ny instans av Animal. Vi lager altså
et nytt objekt basert på det samme objektet som vi laget ny-metoden vår for.
Dette er helt gyldig. Nå sender vi også beskjeden init, noe som sikrer
at Animal-objektet har standardverdier for egenskapene sine. Som standard
har et dyr 4 bein, og lyden er ukjent (derav spørsmålstegnet).
For å lage en ny instans av Animal kan vi ganske enkelt skrive:

```
>> a := Animal ny.
```

Nå får vi en ny instans av Animal med 4 bein, ukjent lyd og
en init-metode. Akkurat som i andre objektorienterte språk kan vi også
utvide Animal:

```
>> Dog := Animal ny.
Dog ved: ['initialiser'] gjør: {
	selv initialiser.
	egen sound := ['barks'].
}.
```

Vi kan enkelt teste dette ved å legge til en tekst-metode:

```
Animal ved: ['tekst'] gjør: {
	<- egen legs tekst + egen sound.
}.
```

La oss sette det hele sammen:

@test13


Å lage et objekt som settes i en gitt starttilstand, er et
vanlig problem. Anta at et objekt **Rectangle** skal lages
for å beregne omkrets og areal. En mulig notasjon kan være:


```
>> Rectangle := Objekt ny.

Rectangle ved: ['area'] gjør: {
	<- egen lengde * egen width.
}.
```

Det er åpenbart en forutsetning å angi lengde og bredde. For det
formålet kan beskjedene **lengde:** og **width:** legges til:


```
Rectangle ved: ['length:'] gjør: { :lengde
	egen lengde := lengde.
}.

Rectangle ved: ['width:'] gjør: { :width
	egen width := width.
}.

```

Dette rektangelet kan da brukes slik:


```
>> rectangle := Rectangle ny length: 2, width: 3.
Utdata skriv: rectangle area.
```

Hvis man derimot glemmer å angi startverdiene for lengde og bredde,
oppstår det en feilmelding:

```
>> rectangle := Rectangle ny.
Utdata skriv: rectangle area.
```

vil gi følgende feil:

```
Nøkkel ikke funnet:lengde
```

For å forhindre dette er det å foretrekke at et rektangel
alltid har en startlengde og -bredde, for eksempel 0. I dette
tilfellet er det derfor nødvendig å **overstyre** beskjeden **ny**.

@test610

Når vi overstyrer ny-beskjeden, etterligner vi i bunn og grunn en **klasse**.

XOScripts verden er full av ulike objekter, som er
tilgjengelige for programmet ditt helt fra starten. I de neste kapitlene
blir alle disse kjerneobjektene gjennomgått.

## Øyeblikksbilder

Du kan lagre et objekt (sammen med den gjeldende tilstanden) på disk med:

```
myobject save-as: ['saved.bin'].
```

Slik laster du objektet inn fra disk igjen:

```
>> myobject := Objekt load-from: ['saved.bin'].
```

Øyeblikksbilder kan brukes til å lagre en bestemt tilstand eller til å forbedre ytelsen.
Når et øyeblikksbilde lastes inn, unngår man leksing, parsing og oppsett av applikasjonen.
I fremtiden kan det også bli innført ytterligere ytelsesfordeler
med øyeblikksbilder, som optimalisering av visse mønstre eller oppdagelse og
optimalisering av varme stier.

{{warning}}
Øyeblikksbilder er en eksperimentell funksjon, ikke bruk den i produksjon.
For å aktivere eksperimentelle funksjoner kompilerer du med -D EXPERIMENTS.
{{/warning}}


@test712

# Objektet Ingenting

{{messages}}

Objektet Ingenting
representerer tomhet, eller enda bedre, fravær av informasjon. Av og til
får du dette objektet som svar på en beskjed, når
resultatet er **ingenting**. Det viktigste spørsmålet
du kan stille **Ingenting**-objektet, er: **Ingenting?**.
Svaret vil alltid være **Sann**.

```
Utdata skriv: Ingenting Ingenting?.
```

resultat:

```
Sann
```

Alle andre objekter enn **Ingenting** svarer med **Falsk**.
Kodefragmentet ovenfor kan virke litt filosofisk, men **Ingenting**-objektet
har absolutt svært praktiske bruksområder. For eksempel
får du Ingenting-objektet som svar hvis du ber om et
listeelement som ikke finnes. Du kan også bruke Ingenting-objektet
hvis du vil deklarere en variabel, men ikke ønsker å angi en verdi
ennå. I stedet **tilordner** du ganske enkelt spesialverdien **Ingenting**. I
XOScript er det ikke tillatt å deklarere en variabel uten verdi, slik som:


```
>> verdi.
```

I stedet må du skrive følgende:

```
>> verdi := Ingenting.
```

@api_None_base

# Boolske verdier

{{messages}}

I motsetning til de fleste populære programmeringsspråk i skrivende stund
har XOScript bare ett enkelt Sann-objekt og ett enkelt Falsk-objekt.
For å presisere: hver gang du skriver **Sann**, betyr det ikke
at et nytt objekt er opprettet. I stedet bruker du alltid en referanse. Dette
betyr at når du skriver følgende:

\>\> x := Sann.

viser **x** til **Sann**-objektet. Betinget kode og løkker
kontrollerer også denne referansen. I XOScript er betydningen av **Sann** og **Falsk**
ikke fastlagt. Et XOScript-program blir faktisk ganske rystet av en
setning som denne:

Sann := Falsk.

Resultatet av slike handlinger er udefinert, men det er fortsatt en gyldig
handling og derfor formelt tillatt. Videre finnes det et Boolsk-objekt,
som er rotobjektet for både **Sann** og **Falsk**, ettersom begge
er avledet av rotobjektet. Selve Boolsk-objektet har imidlertid
ingen praktisk anvendelse.

## Fallgruver

Vær forsiktig med å bruke **og:** og **eller:**

```
Utdata skriv: (Falsk or: Sann or: Sann), stop.
Utdata skriv: (Falsk eller: Sann, eller: Sann), stop.
```

Gir

```
Falsk
Sann
```
fordi beskjeden **eller:** bare tar 1 argument. Den første beskjeden
sender **eller:eller:** til Falsk, som ikke finnes, så objektet ignorerer
beskjeden og returnerer seg selv (Falsk). Den andre linjen
sender derimot **eller:** etterfulgt av enda en **eller:** (ved hjelp av et kjedesymbol, altså et komma: ,).


@api_Boolean_base

# Tall

{{messages}}

Hver gang du skriver et tall, for eksempel 9, -10 eller 3,12, vil XOScript
bak kulissene gjøre disse tallene om til et **Tall**-objekt. Du
kan sende beskjeder til dette Tall-objektet, eller du kan tilordne tallet
til en variabel og sende beskjeder etterpå:

```
10 partall?

>> tenner := 10.
tenner partall?

```

Begge notasjonene er gyldige. Tall-objektet svarer på følgende
beskjeder...

De fleste av disse beskjedene er selvforklarende og lar deg utføre
matematiske operasjoner eller sammenligninger.

{{note}}
Merk at du kan bruke ≤ ≥ ≠ × og ÷ i stedet for de tilsvarende ASCII-tegnene.
Dette er en smakssak.
{{/note}}

Forskjellen mellom binære matematiske beskjeder (+) og
nøkkelordvariantene deres (legg-til:) er at de første returnerer
et nytt tall, som er resultatet av operasjonen, mens
objektet selv endres med de siste. Dette illustreres i
følgende eksempel:

@test597

I eksempelet ovenfor er b = 4 og a = 3. Med **legg-til: 2** økes verdien
av a med 2, mens **+ 3** lager et nytt tall som er
lik a + 3. Det samme gjelder andre matematiske operasjoner, for eksempel
multiplikasjoner. Når du bruker multiplikasjonssymbolet, får du et
nytt objekt som svar. Hvis du bruker beskjeden **multipliser-med:**,
multipliserer du selve tallet.

Med beskjeden **mellom:og:**, for eksempel i: **Tall
mellom: X og: Y**, får du et tall mellom X og Y. På
denne måten kan et hvilket som helst tilfeldig tall genereres:

```
>> a := Tall mellom: 1 og: 10.
Utdata skriv: a, stop.
```

Fra og med versjon 1.4 er den innebygde generatoren for tilfeldige tall i xoscript
kryptografisk sikker, så vidt vi vet.

Du kan knytte en **betegnelse** til et tall, for eksempel **6
epler**. Hver beskjed som ikke blir gjenkjent av et
tall, regnes som en betegnelse. Du kan hente betegnelsen til
et tall ved hjelp av beskjeden betegnelse:

En betegnelse er i bunn og grunn et Tekst-objekt som lagres sammen med Tall-objektet.
Betegnelsen skrives også ut etter tallet ved en
**skriv:**-instruksjon. Betegnelser kan for eksempel brukes til å legge sammen beløp
i blandede valutaer. Når du legger sammen beløpene, kan du spørre
etter betegnelsene. Følgende programeksempel illustrerer dette
prinsippet med en historisk valutakalkulator (siden vekselkursen
holder seg rimelig stabil!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Tekster

{{messages}}

Hver gang en tekst plasseres mellom **hakeparenteser og anførselstegn** ['...'],
lager XOScript et nytt tekstobjekt for deg. Pass imidlertid
på å bruke riktige anførselstegn. Anførselstegnet i
begynnelsen av teksten er forskjellig fra det i slutten (dette lar deg
bruke enkle anførselstegn uten å måtte beskytte dem).

## UTF8

Tekster i xoscript inneholder vanligvis utf8-kodet tekst. Selv om
det teknisk sett er mulig å ha binært innhold eller innhold som ikke er utf8, i
en tekst, anbefales det å bruke blober til det. Blober
leveres av servertillegget (se kapitlet ffi).
Generelt leveres blober/ffi
per tillegg/plattform, siden de er knyttet til plattformen
og arkitekturen (ffi/blober). Kjernen i skriptspråket forsøker å
være så plattformuavhengig som mulig.

## Typekonvertering

Du kan lage en kopi av hvert objekt
med en annen type ved å bruke følgende beskjeder:

Beskjed | Resultat
------- | ------
tall    | Konverterer til et tall
tekst   | Konverterer til en tekst
boolsk  | Konverterer til en boolsk verdi
  
Følgende regler **gjelder**:

beskjed  | Ingenting | Boolsk             | Tall                  | Tekst     | Annet              
-------- | --------- | --------           | --------              | --------  | --------
boolsk   | Falsk     | i.a.               | 0→Falsk ellers→Sann   | Sann      | Som regel Sann
tall     | 0         | Falsk→0 Sann→1 | i.a.                      | ['n']→n | Som regel 1
tekst    | ['Ingenting']  | ['Falsk']/['Sann'] | ['n']            | i.a.      | Varierer

## Kopiering

Verdier i XOScript overføres alltid **som referanse**. I andre språk
avhenger det av verditypen; i XOScript finnes det bare én måte,
som referanse. XOScript lager aldri en kopi av en verdi. For å kopiere et objekt
må du sende beskjeden **kopier**. 

@test611

Her hadde du kanskje forventet at utdataene skulle bli Dolly i stedet
for Donny. Det er imidlertid ikke tilfellet, siden begge navnene viser til det samme
objektet. Når du arbeider med en løkke, skjer noe lignende:

@test612

XOScript bruker faktisk **alltid** referanser, så ved **:quantity**
viser løkken ovenfor også til referansen til elementet
i listen.

For å kopiere et objekt må du angi denne handlingen
**eksplisitt**:

@test613

Når den unære beskjeden **kopier** sendes til en tekst, returnerer objektet
en kopi av det samme tekstobjektet. Det er mulig å kopiere Tall-objekter,
boolske objekter, lister og ordbøker på samme måte.

Du kan også definere din egen kopiimplementasjon; dette er til og med
nødvendig hvis du lager dine egne objekter. Standardimplementasjonen
av kopier for en liste lager en grunn kopi, det vil si at den lager en
ny liste med de samme elementene.

@test614

I dette tilfellet legges 4 bare til i kopien.
Men fordi kopien er grunn, er objektene i begge listene
de samme.

@test615

Hvis vi altså legger til 2 etter hvert navn i kopien, påvirkes også den opprinnelige
listen.

For å bøte på dette må vi lage en **dyp kopi**. En slik kopieringshandling
for en liste kan settes sammen slik:

@test616

Legg også merke til beskjeden rekursiv; denne beskjeden må
sendes før beskjeden kopier.

Det er viktig å huske på at selv om en kopi av et objekt
ofte ser ut som originalen, vil den faktisk
aldri være den samme. Rotobjektet definerer en beskjed **equal:**,
som kan brukes til å sammenligne identiteten til objekter. Se på
følgende eksempel:

@test617

## Implisitt konvertering

XOScript bruker **implisitt konvertering** for å konvertere objekter. For å skrive ut en
liste på skjermen sender XOScript for eksempel beskjeden
*tekst* internt til listen. Dette kan vise seg svært nyttig hvis
du vil skrive ut en liste som en kommaseparert liste.
Beskjeden *tekst* kan overstyres: 

@test620

@api_String_base
@api_Format_base


## Servertekster

Følgende Tekst-funksjoner legges til av
Server-tillegget.

@api_String_server

# Funksjoner

{{messages}}

Du kan samle kode mellom { og }, og da blir den en funksjon.
I xoscript bruker vi også noen ganger begrepet oppgave, eller ganske enkelt
kodeblokk.

Du kan kjøre en funksjon ved å sende beskjeden *start*.


```
{ Utdata skriv: 123, stop. } start.
```

Hvis funksjonen din tar argumenter, bruker du **bruk:**.

```
{ :a Utdata skriv: a, stop. } bruk: a.
```

Se også eksemplene nedenfor.
På grunn av den enkle arkitekturen kan en funksjon bare ha
ett returpunkt. For å unngå ekstra arbeid eller overdreven nøsting av
betingelser kan du bruke en prosedyre (som er det samme som å bruke
multiplikasjonstegnet med argumentet 1):

```
{
  (a = 1) sann: { x := 1. }, avbryt.
  (a = 2) sann: { x := 2. }, avbryt.
} prosedyre.
```

På denne måten blir (a = 2) ikke evaluert hvis a = 1.
Du trenger heller ikke nøstede sann-beskjeder på denne måten.
Hver gang du merker at du nøster betingelser, bør du tenke
på beskjeden prosedyre. Den kan gjøre koden din
lettere å lese.


Her er en viktig fallgruve:

```
{
	Falsk falsk: {
		Utdata skriv: ['End the loop.'].
	}, avbryt.
	
	Utdata skriv: ['Dont show me.'].

} prosedyre.

```

I dette tilfellet blir teksten 'Dont show me' vist,
fordi **avbryt** sendes til Falsk. Hvis du vil utføre
et avbrudd, må det sendes som en beskjed til **Sann**.
 

```
{
	Falsk ikke sann: {
		Utdata skriv: ['End the loop.'].
	}, avbryt.
	
	Utdata skriv: ['Dont show me.'].

} prosedyre.

```

Dette fungerer som forventet.

## Unntak

Unntak kan håndteres slik:

```
{ Task 1 } fang: { Task 2 }, start.
```

Du kan også med vilje få en feil til å oppstå i programmet ditt, og
på den måten aktivere håndteringsblokken. Dette gjøres ved å sende
beskjeden **feil:** til den gjeldende oppgaven, som vist i neste
illustrasjon:

```
{
denne-oppgaven feil: ['Whoops!'].
} fang: { :mistake
Utdata skriv: mistake.
}, start.
```

## Injisere verdier

XOScript gir oppgaver muligheten til å få verdier injisert. Se nå
på oppgaven nedenfor:

```
>> sending := {
	Newsletter til: egen recipient.
}.
sending sett: ['recipient']
verdi: ['info@recipient.org'].
sending start.
```


Denne illustrasjonen viser en tenkt oppgave som sender et nyhetsbrev
til en e-postadresse eller **mottaker**. Denne mottakeren kan injiseres
i oppgaven utenfra, før oppgaven startes, ved å sende
beskjeden **sett:verdi:** til oppgaven. På den måten blir verdien av
**recipient** forhåndsinnstilt i oppgaven. Denne verdien kan også endres,
og oppgaven kan deretter kjøres på nytt. Dette er en nyttig metode når man bruker
oppgaveobjekter.

## Tomme funksjoner

Tomme oppgaver er ikke tillatt. I teorien ville en tom oppgave sett slik
ut: **{}**, men XOScript oppfatter dette som en språkfeil. Hvis du
vil deklarere en tom oppgave, kan du bruke Ingenting-objektet:

```
>> task := Ingenting.
```

Selv om dette ikke er en ekte oppgave, men et Ingenting-objekt, kan en start-beskjed
likevel sendes:

```
>> answer := task start.
```

Dette er faktisk det samme som:

```
>> answer := Ingenting start.
```

Fordi objektet **Ingenting** ikke gjenkjenner beskjeden **start**,
returnerer det seg selv som svar, slik at svaret igjen blir **Ingenting**.
Det er altså ikke nødvendig å ha en tom oppgave. Takket være den elegante
utformingen av programmeringsspråket XOScript kan du ganske enkelt bruke Ingenting-objektet
til dette.

## Dynamisk skop

Når en Funksjon trenger en variabel, men ikke finner den,
sjekker den variablene til Funksjonen som **kalte** den,
og fortsetter oppover i kjeden av Funksjoner.
Denne søkeprosessen fortsetter til variabelen er funnet.
Hvis variabelen fortsatt ikke blir funnet, vises en feilmelding. Denne måten å søke etter en
variabel på kalles **dynamisk skop**.

For å illustrere dette prinsippet:

@test618

@api_Code_base

# Rotobjekt

{{messages}}

Objektet som heter **Objekt**, er rotobjektet for alle objekter i
XOScript og står for språkets kjernefunksjoner. 

Den beskjeden som sendes oftest,
er **ved:gjør:**, som utvider funksjonaliteten til et objekt. Denne
beskjeden mottas av rotobjektet, som deretter knytter
den angitte oppgaven til beskjeden og på den måten utvider det avledede
objektet.

## Oppsamlingsmetoder

Hvis du sender en beskjed som ikke tilsvarer
en metode i objektet, blir den normalt ignorert. Du kan imidlertid angi
såkalte **magiske metoder** eller **oppsamlingsmetoder** som blir
kalt hvis objektet ikke forstår beskjeden.

Det finnes 4 oppsamlingsmetoder. Hver beskjed tilsvarer
et bestemt antall argumenter.

Oppsamlingsbeskjed   | Antall argumenter
-------------------- | -------------------
svar:                | 0
svar:og:             | 1
svar:og:og:          | 2
svar:og:og:og:       | 3


@test619

## Programmatiske beskjeder

I stedet for å sende en beskjed direkte til et objekt kan den også
sendes via en variabel. Til det bruker du beskjeden
**beskjed:argumenter:**. 

@test396

@api_Object_base

# Lister

{{messages}}

XOScript kjenner to typer samlinger: *lister* og *ordbøker*.
**Lister** er oppramsinger av objekter i en *fast rekkefølge*. Ordbøker har
ingen rekkefølge, men ligner i stedet en tegnforklaring med en nøkkel (eller term) og den
tilhørende verdien. Lister kan sammenlignes med arrays (PHP, Java, C)
og lists (Python). Ordbøker kan sammenlignes med assosiative arrays (PHP) eller
dictionaries (Python) i andre programmeringsspråk. For å lage
en ny Liste skriver du:

```
>> fibonacci := Liste ny.
```

Denne tomme listen kan fylles med **legg-til-sist:** :

```
fibonacci legg-til-sist: 0.
fibonacci legg-til-sist: 1.
fibonacci legg-til-sist: 1.
fibonacci legg-til-sist: 2.
fibonacci legg-til-sist: 3.
fibonacci legg-til-sist: 5.
fibonacci legg-til-sist: 8.
fibonacci legg-til-sist: 13.
```

Hvis vi skriver listen til skjermen:

```
Utdata skriv: fibonacci, stop.
```

får vi se:

```
Liste ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

I stedet for legg-til-sist kan du også bruke ; for å legge til elementer i en liste:


```
>> fibonacci := Liste ny ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Semikolonene (;) er alle binære beskjeder som legger en
verdi inn i listen.

## Kjeding

Anta at du har en liste som denne:

```
>> x := Liste ny ; 1 ; 2 ; 3.
```

Hvis du vil slette det første og det siste elementet, ville
beskjeden din vært:

```
x ta-første ta-siste.
```

Dessverre fungerer ikke den forrige notasjonen riktig.
Beskjeden **ta-første** returnerer det første elementet i listen, som
i sin tur blir mottakeren av beskjeden **ta-siste**. Beskjeden
**ta-siste** sendes altså ikke til **x**, men i stedet til 2. En
mulig løsning på dette problemet er å lage to separate
setninger, slik som: 

```
x ta-første.
x ta-siste.
```

Dette er imidlertid ganske upraktisk, særlig når du må
slette mer enn to elementer. Derfor tilbyr XOScript en
alternativ beskjedstruktur for slike situasjoner. I
**alternative** beskjedstrukturer ignoreres svarene fra objektene,
og du får mottakerobjektet tilbake som svar, gang på gang.
En **alternativ** beskjedstruktur startes ved å sende
beskjeden **gjør** til et objekt, og den **alternative** beskjedstrukturen
kan avsluttes ved å sende beskjeden **ferdig**. I det
viste eksempelet kan dette brukes slik:

```
>> x := Liste ny ; 1 ; 2 ; 3.
x gjør ta-første ta-siste ferdig.
```

@api_List_collections

# Ordbøker

{{messages}}

**Både Liste og Ordbok er samlinger. I motsetning til en
liste har en ordbok imidlertid **ingen** rekkefølge. En annen forskjell mellom de to
er at en ordbok består av objektpar. Det ene objektet fungerer som oppslagsord (eller
nøkkelord) for å finne det andre objektet. Et godt eksempel på en
slik liste er en prisliste, som:


```
>> menu := Ordbok ny
	sett: ['£5'] ved: ['apple pie'],
	sett: ['£6'] ved: ['carrot cake'],
	sett: ['£3'] ved: ['fudge'].
```

I likhet med en liste brukes beskjeden sett:ved:
til å legge til et objekt i en liste. Forskjellen er at, i motsetning til
en liste, blir to objekter koblet sammen. Det første objektet er, i likhet
med en liste, objektet du lagrer i en liste. Det andre
objektet er ikke posisjonen i samlingen, men **oppslagsordet**
som gjør det mulig å hente det første objektet senere. Kort
sagt fungerer en ordbok litt som en ordbok i papirform: ved hjelp av oppslagsordet
kan betydningen finnes. For eksempel, for å hente prisen på en fudge fra
listen ovenfor:

```
>> price := menu ved: ['fudge'].
```

Du kan også bruke den korte notasjonen:

```
>> price := menu ? ['fudge'].
```

Hvis oppslagsordene du bruker til å lagre objekter, er uten mellomrom
(og ikke kolliderer med andre forhåndsdefinerte beskjeder),
kan også følgende notasjon brukes:

```
>> menu := Ordbok ny
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Notasjonen ovenfor leses utvilsomt litt mer naturlig.
For å spørre etter prisen på en
fudge kan følgende forenklede notasjon brukes:

```
>> price := menu fudge.
```

@api_Dict_collections

# Fil

{{messages}}

Objektet **Fil** gir grunnleggende tilgang til filsystemet.
Du kan bruke dette objektet til å lese hele filer inn i en variabel på
én gang, eller skrive variabler til filer på én gang. Lesing linje for linje
støttes også. Dette er de vanligste fil-I/O-operasjonene
i et skriptspråk. Avanserte filoperasjoner krever
bruk av FFI via servertillegget eller et separat IO-tillegg.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Dato/klokkeslett

{{messages}}

For en strukturert fremstilling av klokkeslett og dato bruker XOScript
objektet **Moment**. Når et nytt Moment-objekt skrives ut på skjermen,
vises gjeldende dato og klokkeslett:

```
Utdata skriv: Moment ny, stop.
```

Kan gi noe slikt som:

```
2020-10-10 12:16:39
```

Det er også enkelt å lese ut de enkelte tidskomponentene. Hvis det
for eksempel bare er nødvendig å vite gjeldende år, kan beskjeden
**år** sendes til momentet, og svaret blir da et
Tall-objekt som bare inneholder året:

```
>> m := Moment ny.
Utdata skriv: m år, stop.
```

@api_Moment_system

# Program/StdOut

{{messages}}

Program-objektet representerer applikasjonen som kjører. Dette objektet
tilbyr funksjonalitet for å kjøre systemkommandoer, inkludere underprogrammer,
lese argumenter og mer. Kort sagt alle systemrelaterte funksjoner.

## StdOut

Utdata er standard utdataobjekt. Det har i hovedsak to metoder:
**skriv:** og **stop**. Beskjeden skriv: brukes til å sende en tekst
til stdout, og beskjeden stop skriver ut et linjeskifttegn.
I stedet for **stop** kan du også bruke \\n.

Eksempel:

```
Utdata skriv: ['Hello World'], stop.
```

resultat:

```
Hello World
```

## Moduler/tillegg

XOScripts verden kan utvides med nye systemobjekter ved å
installere moduler. Et nytt systemobjekt kan legges til i XOScripts
verden ved å plassere modulfilen (vanligvis en fil med endelsen .so)
i mappen mods. 

Når du sender en beskjed til objektet som gjøres tilgjengelig gjennom
tilleggsmodulen, blir den automatisk lastet inn av XOScript.

Du kan også skrive tillegg selv. Tillegg skrives i
programmeringsspråket C. Du finner et eksempeltillegg i kildekodepakken
under src/plugins/example.


## Refleksjon

Det finnes ulike måter å utforske
systemet på mens programmet kjører. XOScript har et par metoder for å
finne ut hvilke objekter som finnes, og hvilke beskjeder disse objektene
svarer på. For det første kan hvert objekt spørres om hvilken **type** det er,
men typer i XOScript kan formes fritt og er derfor upålitelige.

Det er også mulig å spørre Program-objektet om et
gitt objekt allerede finnes i programmet:

```
Program Tool sann: { ... }.
```

Når et objektnavn
består av ett enkelt symbol, er det best å bruke
følgende notasjon for å unngå forvirring:

```
Program finn: ['X'], sann: { ... }.
```

I tillegg til å spørre om objekter er det like gjerne mulig å spørre
Program-objektet om beskjeder. Det kan for eksempel spørres om
objektet **Tall** kjenner beskjeden **mellom:og:**, på den måten
som er vist nedenfor:

```
Program Number: ['between:and:'], stop.
```

@api_Program_system

# server

{{messages}}

Server-tillegget i xoscript tilbyr funksjonalitet for å
lage applikasjoner på serversiden. For å laste inn
servertillegget bruker du:

```
Server initialiser.
```

For enkelhets skyld anbefales det også å laste inn
filene webtools.xo og template.xo.

```
Program benytt: ['webtools.xo'].
Program benytt: ['template.xo'].

```

## Serverinnstillinger

Du kan angi følgende serverinnstillinger:

```
	# default values are given
	# so if you do not set anything these
	# values are used...

	Program 
	innstilling: ['max-postfields']
	verdi: 40.

	Program 
	innstilling: ['max-contentlength']
	verdi: 2000000. # 2MB

	Program 
	innstilling: ['max-time']
	verdi: 5000. # 5sec

```

## Hallo verden

Her er et svært enkelt webprogram som du kan bruke med en
vanlig CGI-server som Apache2, NGINX, OpenHTTPD eller en hvilken som helst annen
kjent server.

```
#!/bin/xo

Server initialiser.
Program benytt: ['webtools.xo'].

>> web-document := Webdokument ny.

web-document skriv-ut: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Hvis du ikke vil bruke Webdokument-objektet, er det greit, men
da må du skrive HTTP-hodene selv:

```
#!/bin/xo
Utdata skriv: ['Content-type: text/html; charset=utf-8 \n\n'], stop.
Utdata skriv: ['hello world!'], stop.
``` 

## Forespørsel

Objektet HTTP-Forespørsel kan brukes til å hente GET-, POST-, COOKIE- og
UPLOAD-data:

```
>> forespørsel  := HTTP-Forespørsel ny.
>> search   := forespørsel get: ['search']. # ?search=books
>> password := forespørsel post: ['password']. # from form
>> selected := forespørsel get-liste: ['sel[]']. #?sel[]=1&sel[]=2
>> selected := forespørsel post-liste: ['sel[]'].
>> cookie   := forespørsel cookie: ['session-id'].
>> upload   := forespørsel upload: ['file'].
>> temppath := upload ? 1.
>> filename := upload ? 0.
```

## Maxpost/lengde

Standard maksimalt antall POST-felt er 40, og standard maksimal innholdslengde
er 2MB. Slik konfigurerer du dette annerledes for hvert enkelt skript:

```
Program innstilling: ['max-contentlength'] verdi: 1. 
Program innstilling: ['max-postfields'] verdi: 1. 
```

{{note}}
Hvis innholdslengden overskrider maksimum, blir
prosessen avsluttet, fordi vi ikke lenger kan være sikre
på at innholdet er trygt.
{{/note}}

Grensen maxtime bestemmer maksimal tid i ms
for å lese stdin/POST-data.

```
Program innstilling: ['max-time'] verdi: 5000. # 5sec
```

Dette gjelder bare I/O-lesingen av POST-dataene, og forhindrer
slowloris-lignende angrep. Hvis du virkelig vil begrense
kjøretiden for en hvilken som helst operasjon, bruker du Program alarm.

## Database

Database-objektet kan brukes til å sende spørringer til MariaDB/MySQL.
Slik kobler du til en database:

```
>> db := Maria-DB ny vert: ['localhost'],
	brukernavn: ['xo'],
	passord: ['pass123'],
	databasenavn: ['xobase'],
	koble-til.

```

Slik setter du inn en post:

```
>> søkeparametere := db spørring: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parametere: ( Liste ny ; ['abc'] ; 12.35 ; 6 ). # parameterized queries

{  søkeparametere utfør. db bekreft. }
fang: { :e db rull-tilbake.  }, start.
```

Merk at xoscript *bare* arbeider med transaksjoner og aldri bekrefter automatisk (autocommit).
Hvis autocommit ikke kan deaktiveres, får du en tilkoblingsfeil.
Bruk alltid parameterbinding for spørringer, og legg aldri brukerinndata direkte
inn i SQL-koden.

Hent den innsatte id-en slik:

```
Utdata skriv: ['INSERTED: '] + søkeparametere insert-id, stop. # insert id
```

Slik henter du poster:

```
>> søkeparametere :=
db
	spørring: ['SELECT * FROM book order by id desc limit 2'], 
	hent: { :row 
		Utdata skriv: row id + [' '] + row description + [': '] + row price, stop.
	}. # fetching rows

```

## Økter

For å bevare data kan du lagre og hente data fra et øktobjekt.
Lag først et nytt **Webdokument**. Webdokument-objektet knytter sammen
forespørselen, hodene, HTML-koden og økten. Dette er fordi du bare ser HTML-koden
når du besøker et nettsted med nettleseren din. Men
hele Webdokumentet består også av **hoder** (headers). For eksempel
inneholder de fleste HTTP-svar et hode som: Content-type:text/html for å
fortelle nettleseren at dataene som følger, skal vises som HTML
(og ikke for eksempel lastes ned som en fil). Økter er en måte å
lagre brukerdata mellom forespørsler på. For å holde styr på disse dataene må vi
sette en informasjonskapsel (cookie), og denne settes også gjennom et hode. Derfor
kommer alt sammen i Webdokumentet (fordi det er hele
dokumentet, som inneholder både hoder og HTML eller andre data).


```
# First we make a new Web Document instance
>> web := Webdokument ny.

# Now we start a session, this will generate a Header for a cookie and
# create a file to store your data, associated with that cookie
>> session := web start-økt.

# Now we can treat session like a dict
session userid: 123.
```

Slik ødelegger du økten (ved utlogging):

```
web avslutt-økt.
```

## Hoder

Webdokumentet lar deg også angi andre kjente hoder.
Hvis du for eksempel vil videresende brukeren til en annen URL:

```
web gå-til: ['/other.html'].
```

Under panseret genererer denne kommandoen også HTTP-hodet som sendes
sammen med de andre dataene eller HTML-koden din, for å be nettleseren om å navigere
til den angitte måladressen.

Slik legger du til et egendefinert hode:

```
web hode: ( 
	HTTP-Hode ny
	nøkkel: ['Content-Length']
	verdi: 400
).
```

Slik viser du en 404-side:

```
web ikke-funnet: ['OOps..'].
```


## Maler

Standard malsystem er svært enkelt. Du trenger ikke å lære
en ny malsyntaks. Malmotoren sikrer dessuten reell atskillelse
mellom presentasjon og forretningslogikk.

Slik lager du en mal fra en fil:

```
>> tpl := web mal: ['templates/ux.tpl'].
```

Malsystemet bruker markører. 
Det finnes tre typer markører: klippmarkører, limmarkører og
plassmarkører. Grunnideen er svært enkel: du klipper ut
områder som er angitt med klippmarkører, og du kan lime dem inn i
områder som er angitt med limmarkører. Du kan injisere tekster i
plassmarkører.

Gitt for eksempel følgende mal, la oss legge
edelstenen i smykkeskrinet og legge til en prislapp.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Dette kan du gjøre slik:

```
>> gem := tpl klipp: ['gem'], kopier.
gem price: 99.
tpl lim-inn: gem ved: ['jewels'].
web skriv-ut: tpl rens.
```

Den siste linjen sender ganske enkelt malen som en tekst til klienten,
sammen med de nødvendige HTTP-hodene.

Resultat:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

For å levere filer som brukerne har lastet opp, på en sikker måte, kan du bruke passthru:

```
>> uploaded := ['smile.gif'].
Server videresend: uploaded prefiks: ['/uploads/images/'].
Program slutt.
```

Dette leverer innholdet som brukeren har lastet opp, med riktig
mime-type. Bare godkjente mime-typer støttes:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF og SVG.
SVG-, ZIP- og GZIP-filer sendes som en nedlasting, fordi en SVG
kan inneholde skript som ellers ville kjørt på domenet ditt.
Denne metoden forhindrer TOCTOU-angrep, stitraversering, 
kjøring av ondsinnet kode (injeksjon), symlenkeangrep,
DDoS-angrep (filgrense = 50MB), avlyttingsangrep og 
diverse andre sikkerhetsproblemer.


## JSON

Slik koder du et objekt som JSON:

```
>> json := ( JSON jsonify: ( 
	Ordbok ny sett: ( 
		Liste ny ; 1 ; 2 ; 3
	) ved: ['abc']
)).
```

Slik dekoder du JSON til et xoscript-objekt:

```
>> dict := ((JSON objekt: json) abc ? 1).
```

JSON med mer enn 500 nivåer av nøsting avvises som ugyldig.

Slik sender du en Ordbok direkte ut som json med riktige hoder:

```
web json: dict.
```


## Regex

Du kan bruke regulære uttrykk ved å lage et mønster.
For eksempel for å finne href-er og mål i hyperlenker:

```
Mønster ny: ['href="([^"]+)" target="([^"]+)"'].
```

Bruk nå mønsteret på emneteksten slik:

```
pattern treff: emne gjør: { :m :x .... }
```

Fullstendig eksempel:

```
>> emne := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> pattern := Mønster ny: ['href="([^"]+)" target="([^"]+)"'].
>> result  := pattern treff: emne gjør: { :m :x
	Utdata skriv: m, stop.
	Utdata skriv: x, stop.
	<- ['XXX'].
}.
Utdata skriv: result, stop.
```

## Nettverk

Bruk Nettverk-objektet til å utføre en webforespørsel.
Nettverk-objektet sender alltid en POST-forespørsel, med mindre du sender Ingenting som
data; da sender det en GET-forespørsel.


```
Nettverk 
post: Ingenting 
til: ['https://redbeanphp.com'].
```

## Kryptering

Servertillegget har kryptering basert på XChaCha20 og Argon2.

Eksempel:

```
>> encrypted := Hvelv krypter: ['hello'] nøkkel: ['world'].
>> decrypted := Hvelv krypter: encrypted nøkkel: ['world'].
```

## Tokener

Slik genererer du et kryptografisk sikkert token med en bestemt lengde:

```
>> mytok := Hvelv token: 40.
```

Dette genererer et token på 40 tegn.

## Formatering

Format-objektet lar deg formatere data, for eksempel med utfylling eller
ved å legge til nuller. Det bruker printf-syntaksen.

```
>> fmt := Format ny: ['%06.0f'].
fmt bruk: 56. # gives 000056
```

Et format kan inneholde én konvertering, og den må passe til verdien,
ellers får du en feil:

- `bruk:` med en tekst: `%s`
- `bruk:` med et tall: `%f`, `%e`, `%g` eller `%a`
- `bruk-heltall:` med et tall: `%d`, `%i`, `%o`, `%u`, `%x` eller `%c`

Verdier fra en forespørsel er tekster. For å formatere en verdi som et tall
må du først konvertere den:

```
fmt bruk: (forespørsel get: ['amount']) tall.
```

## Kodere

Flere kodere og dekodere er tilgjengelige.
URL-koderen gjør en url klar til bruk i HTML som en lenke:

```
Server url-kode: ['https://example.com?a=6&b=1 2'].
```

For å injisere brukerinndata trygt i HTML-koden din uten å risikere
XSS-injeksjoner bruker du alltid:

```
Server html-kode: ['<harmless>'].
```

Merk at malmotoren alltid utfører HTML-koding
når du skriver til en plassmarkør. Hvis du bruker malsystemet,
trenger du altså ikke å bruke dette.

## E-post

For å sende en e-post bruker du biblioteket mailtools.xo.

Eksempel:

```
Server initialiser.
Program benytt: ['mailtools.xo'].

>> e-mail := HTML-E-post ny.
>> img := e-mail legg-ved: ( Fil ny: ['myimage.png'] ).

e-mail
avsender: ['xo@xoscript.com'] navn: ['xo'],
til: ( Liste ny ; ['xo2@xoscipt.com'] ),
emne: ['xoxo'],
meldingstekst: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), send.

```



## Kobling

Med beskjeden koble: kan du koble et eksternt bibliotek til
programmet ditt ved hjelp av libffi. For detaljer, se kapitlet om ffi.


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

FFI leveres per plattform/tillegg fordi det
er knyttet til den underliggende systemarkitekturen, noe
kjernen ikke skal være.
Servertillegget tilbyr en kompatibel ffi/blob-implementasjon.
Som standard kobler kjernen seg til målplattformen
gjennom stdin/stdout, begrensede fil-I/O-tjenester og skallet (Program system).
Ytterligere integrasjon leveres av ffi/blober gjennom applikasjonsrettede
tillegg som servertillegget.

FFI står for Foreign Function Interface (grensesnitt for fremmede funksjoner). Det lar deg bruke funksjonalitet som andre har skrevet i
andre programmeringsspråk, levert gjennom DLL-filer, SO-filer eller Dylib-filer. Dette kan
være et bredt utvalg av funksjoner, og det finnes et enormt spekter av funksjonalitet tilgjengelig på denne måten.
La oss begynne med et eksempel:

```
Server koble: (
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
s frigjør.
```

Resultatet av denne koden er at du ser følgende på kommandolinjen:
FFI has 3 letters.
Nå tenker du sikkert: «Det var mye kode for noe så enkelt.»
Kunne vi ikke bare løst dette med en Gui show-kommando? Svaret er et rungende ja!
Men dette er ment som et illustrerende eksempel.
FFI brukes vanligvis til mer komplekse oppgaver, men de egner seg ikke som gode
eksempler, så jeg valgte noe trivielt.

Argumentene til metoden koble:

- Argument #1: DLL- eller SO-filen du vil bruke.
- Argument #2: Funksjonen i den filen som du vil koble til.
- Argument #3: En liste med navnene på datatypene til funksjonens argumenter.
- Argument #4: Navnet på funksjonens returtype.
- Argument #5: Navnet på objektet du vil koble denne funksjonen til (hvis det ikke finnes, blir det opprettet
automatisk).
- Argument #6: Beskjeden som denne funksjonen skal kobles til.

I eksempelet ovenfor vil vi koble til printf-funksjonen fra libc.so. Du finner navnene på
datatypene i dokumentasjonen til programvaren du kobler til. De tilgjengelige typene er:
void, pointer, float, double, int, uint, char, uchar, intX og uintX,
der X kan være 8, 16, 32 eller 64.

Disse typene viser til antall byte som kreves for å lagre dataene. For printf kobler vi til et
nytt objekt som heter Printf, og beskjeden template:number:. Du oversetter den eksterne
funksjonen til XOScript-dialekten før du bruker den. Beskjeden template:number: forventer en
buffer med malteksten som første parameter. Vi lager denne bufferen med et Blob-objekt, som
lar deg tildele minne manuelt. Du er selv ansvarlig for å frigjøre dette minnet etterpå
med beskjeden frigjør.

Du kan fylle en minneblob på ulike måter. I eksempelet vårt fyller vi den med tekst, så vi bruker
beskjeden utf8: (UTF-8 er en koding som gjør tekst om til byte). Du kan også fylle en blob med
bytes: ved å sende inn en liste med byteverdier. For å lese innholdet i en blob bruker du fra:lengde:.
Du får bytene tilbake som en liste. Du kan til og med lage en C-struct med en Blob ved hjelp av
beskjeden struct:, der du sender inn en sekvens av C-typer. Dette kan være nødvendig når du kaller en C-funksjon
i et eksternt programvarebibliotek som forventer en peker til en struct.

{warning}
Du må frigjøre blober selv.
Blober blir ikke ryddet bort av søppelinnsamleren.
{/warning}

Siden blober kan utveksles med eksterne funksjoner fra biblioteker, kan
de ikke samles inn automatisk av søppelinnsamleren (de kan fortsatt være i bruk av 
eksterne funksjoner, eller disse eksterne funksjonene vil kanskje frigjøre dem
selv). Derfor må du frigjøre blober selv når det er nødvendig.

Slik frigjør du en blob:

```
myblob frigjør.
```

Slik frigjør du en struct:

```
mystruct frigjør-struct frigjør.
```

For en struct må du altså sende to beskjeder, frigjør-struct og frigjør, for å
frigjøre minneblokken.

@api_Blob_fficonnect
