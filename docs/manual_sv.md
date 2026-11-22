# Grunder

{{messages}}


Välkommen till XOScript
Projektet XOScript syftar till att skapa ett skriptspråk som är enkelt och granskningsbart.
Enkelt betyder inte nödvändigtvis lätt.
Ett välbekant programmeringsspråk kan vara lättare att använda än XOScript.
Här betyder enkelhet något annat:
att kunna bilda sig en fullständig mental modell av språket och dess beteende.

XOScript är utformat för att rymmas i huvudet.
Dess grammatik och antalet begrepp är medvetet små.
Det finns inga klasser; objekt kan utökas direkt.
Objekt skickas som referenser, kopiering sker explicit,
och funktioner har en enda utgångspunkt.

Några av dessa val skiljer sig avsevärt från de vanligaste språken.
XOScript har till exempel inget typsystem och använder dynamisk räckvidd.
Meddelanden som inte kan hanteras ignoreras i stället för att ge upphov till ett undantag.
Dessa val har konsekvenser och är inte avsedda att eliminera fel.
De är avsedda att hålla språkets underliggande modell liten och konsekvent.

XOScript kan också lokaliseras, vilket gör det möjligt att uttrycka affärsregler
på ett naturligt språk och eventuellt dela dem med icke-tekniska intressenter.

Granskningsbarhet innebär att samma filosofi tillämpas på implementationen.
Körmiljön är skriven i C, med en liten handskriven lexer, parser och trädvandrare.
Standardbiblioteket och körmiljön speglar i stort sett språkets struktur,
vilket gör relationen mellan XOScript-kod och dess implementation relativt direkt.

Testerna är också nära kopplade till dokumentationen.
Varje metod bör ha ett tillhörande test som kan tas med i manualen,
vilket hjälper till att hålla dokumentationen i takt med implementationen.

XOScript är inte avsett att konkurrera med de vanligaste språken när det gäller
funktioner eller igenkänning. Det utforskar ett annat mål:
en programmeringsmiljö som en utvecklare kan förstå som en helhet.

Förhoppningen är att ett litet språk och en liten
implementation gör det praktiskt möjligt att förstå programvara
från byte till objekt, från syntax till körmiljö, och att skriva kod med
självförtroende eftersom du förstår både vad som händer i
skriptet och vad som händer under huven.

Arkitekturen för en xoscript-serverinstallation
är enkel men ändå flexibel.

{{architecture.png}}

För att använda xoscript som serverspråk måste du installera
serverinsticksmodulen i en mapp som heter /mods/server. 

Detta beror på att vi vill
frikoppla kärnspråket från serverspecifik funktionalitet,
till skillnad från till exempel PHP eller Python. Annars skulle vi behöva leverera
hela köksbänken utan anledning till alla, vilket helt enkelt är fånigt.
Du kan även installera andra moduler om du vill. Systemet är mycket
flexibelt.

Vissa funktioner implementeras dessutom bättre i själva skriptspråket,
som mallar och sessionshantering, så därför levererar vi
även biblioteken template.xo och webtools.xo för din bekvämlighet.
Anledningen till allt detta är att vi inte vet hur du vill
använda xoscript. Du kan använda det som ett skriptspråk på serversidan,
men också för grafiska gränssnitt, inbyggda enheter eller bara batchbearbetning.
Även om du använder det som ett skriptspråk på serversidan (vilket för
närvarande är ett av de främsta användningsområdena), kanske du ändå vill
använda en annan mallmotor eller en annan sessionshanterare.
Vilka är vi att bestämma att du ska använda våra?

En av fördelarna med att använda vår egen mallmotor är dock att
du inte behöver lära dig ytterligare syntax för att skapa mallar.
Standardmallmotorn som levereras med xoscript använder 100 %
separation mellan presentation och logik. I stället för speciell
mallsyntax använder den helt enkelt ett mycket flexibelt system med platsmarkörer.
Mer information finns i kapitlet Server.

Observera att om du inte vill använda standardmallmotorn eller
standardwebbverktygen, så säger det sig självt att du måste tillhandahålla
dina egna.

Om du kör din webbserver i en chroot, ett jail eller någon annan typ av sandlåda,
måste du även installera xo:s beroenden i den miljön. Du kan
se vilka bibliotek du behöver med hjälp av ldd (se manualsidan för Linux eller BSD).
Om du vill använda skalkommandon i dina xo-skript, kopiera även ett skal
(som bash eller ksh) till denna miljö.

Vi vill också påpeka att vi tar bakåtkompatibilitet på stort allvar.
Det finns till och med en särskild funktion för bakåtkompatibilitet som heter
'version'. Generellt sett strävar vi efter att din kod ska fungera för alltid. Du kommer alltså
aldrig att behöva uppdatera din kod för att förbli kompatibel med nyare versioner
av xoscript. Vårt mål är: skriv en gång, kör för alltid.

Resten av denna manual ägnas åt att i detalj förklara programmeringsspråket
xoscript. Serverskript behandlas i kapitlet
som heter Server. Om du är en erfaren programutvecklare kanske du vill
hoppa över några kapitel, eftersom vissa av dem är lite väl detaljerade eller
mycket lika allmän programmeringspraxis. Så för er
som redan har erfarenhet av flera andra programmeringsspråk
är det bättre att behandla denna manual som en referensguide.

## Installation på Linux

Ladda ner apache2 och mariadb:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Ladda ner xoscript.
Ersätt X med rätt versionsnummer!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Kopiera filerna till webbroten och /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Redigera din apache2-konfiguration:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Ersätt Virtualhost med:

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

Skapa en testsida:

```
sudo nano /var/www/html/test.xo
```

och skriv ett litet testprogram:

```
#!/bin/xo
Server initiera.
Program använd: ['webtools.xo'].
>> web := Webbdokument ny.
web skriv-ut: ['Hello World'].
```

Tillåt apache2 att köra ditt program via CGI:

```
sudo chmod uog+x /var/www/html/test.xo
```

Starta om apache2:

```
sudo systemctl restart apache2
```

Gå till din testsida i webbläsaren:

```
http://localhost/test.xo
```

Du bör se:

```
Hello World
```


## Installation på OpenBSD

Redigera /etc/httpd.conf och lägg till:


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

Om du vill använda SSL:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

För att skydda nyckelutbytet mot kvantdatorer,
välj chiffret mlkem:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Lägg till xo-binären och modulerna, samt eventuella beroenden, i
chrooten (ta reda på dem med ldd).

## Köra exempel


För att köra ett av exempelprogrammen i paketet:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Till exempel, för att köra FizzBuzz-exemplet på Linux:

```
./example.sh fizzbuzz Linux
```

För att köra samma exempel på OpenBSD:

```
./example.sh fizzbuzz OBSD
```

För att köra exemplet med en ren byggning:

```
./example.sh fizzbuzz OBSD clean
```

## Enhetstester

För att köra enhetstesterna:

```
./runtests.sh
```

För att köra enhetstesterna utan att bygga (bara testa):

```
./runtests.sh nobuild
```

## Bygga

För att bygga från källkod på Linux:

```
make clean
ISO="en" make
```

På OpenBSD:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

För att bygga serverinsticksmodulen på Linux:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

För att bygga serverinsticksmodulen på OpenBSD:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Hej världen

När filen har överförts till din dator kan du packa upp den
och starta xo med följande kommando:

```
xo
```

För att köra ett XOScript, spara programmet som en fil med ändelsen -xo
(valfritt). Ange dessutom filnamnet på ditt program
efter XOScript-kommandot:

```
xo myprogram.xo
```

När du kör ett XOScript-kommando med din programfil som
parameter läser och kör xo din programfil.

{{note}}
Du kan också starta ditt program genom att dra det till xo-ikonen.
{{/note}}

{{warning}}
På vissa system måste du i förväg ge xo behörighet att läsa in dynamiska
bibliotek.
{{/warning}}

Traditionen bjuder att det första programmet i varje nytt programmeringsspråk
ska vara en sorts hälsning till världen. I XOScript ser ett sådant
**Hej världen**-program ut så här:

@test598

När denna text har sparats i en fil, t.ex. hello.xo, kan den köras på
följande sätt: .

xo hello.xo

Hello world


Du kan se programmets utdata i det svarta fönstret ovan.
I hela denna manual används samma visualisering för att visa
utdata.

{{note}}
Utdata skrivs med versalt U.
Generellt börjar objekt med en versal
såvida de inte fungerar som en instans (inte har några egna metoder,
bara data). Detta speglar konventionerna för klass och instans
i andra programmeringsspråk.
{{/note}}


## Syntax 

XOScript är ett *rent* *objektorienterat* programmeringsspråk. Det innebär
att xoscript betraktar allt som ett objekt, och därför finns det
inga andra *datatyper*. Det finns i grunden tre grundläggande rutinhandlingar
i ett program som är skrivet i XOScript: *tilldela*, *skicka meddelanden*
och *svara*. Utbytet av meddelanden mellan objekt är kärnan i
ett XOScript-program. De tre enskilda rutinhandlingarna illustreras
nedan:


Handling        | Exempel
--------------- | --------
tilldelning     |  \>\> x := 1. 
unära meddelanden | x jämn?.
binärt meddelande | 1 + 2.
nyckelordsmeddelande | x från: 0 längd: 10.
svar            | <- answer.  


Detta kapitel ger dig ett allmänt intryck av språket XOScript
och beskriver dess grundprinciper. XOScript är ett litet språk och
bygger på tre handlingar (se illustrationen) som motsvarar
ungefär sex grammatikregler. Det är allt som krävs för att bemästra
språket.

Oroa dig inte om allt inte är uppenbart direkt: alla byggstenar
kommer att utforskas i nästa kapitel (3) och grundreglerna kommer
att upprepas. Det här kapitlet fungerar dock främst som en allmän
introduktion till språket. Grundprinciperna förklaras kort
och illustreras med flera relevanta exempel. Eventuella saknade
detaljer beskrivs vid ett senare tillfälle.

Kommentarer i XOScript inleds med symbolen \#. Följande rad
ignoreras alltså:

```
# this is just a comment
```

## Variabler

För att tilldela
en variabel använder du symbolen för variabeldeklaration: >>. Namnet på en
variabel får innehålla alla tecken utom: <-, :=, blanksteg,
punkter, kommatecken, kolon, citattecken [' '] och parenteser ().
Dessutom får en variabel inte bestå av flera rader. Observera
att en variabel inte får börja med en siffra eller ett minustecken.

Detta är exempel på giltiga variabler:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dollar'].
>> +plus := Sann.
>> user-password := ['Pssst!'].
```

Ogiltiga variabler är till exempel:


```
>> -123 := ['negative number'].
>> password of user := ['Classified'].
>> password.of:user := ['Classified'].
>> ,x := 10.
```

{{note}}
Du behöver inte undanta något tecken
(inklusive citattecken, dubbla citattecken och
textgränser) i
en textliteral, så länge det inte
skapar tvetydighet för lexern.
{{/note}}

När en variabel har deklarerats kan den användas fritt. Det innebär
att det bara är nödvändigt att använda deklarationssymbolen första gången
du använder variabeln (deklarationen).

För att vara mer specifik kan du inte bara börja tilldela ett värde till
din variabel *(x := 2)*, eftersom du först måste deklarera variabeln *(\>\>
x := 2)*. När den väl har deklarerats får du däremot ändra dess värde
utan att använda deklarationssymbolen*(\>\> x := 2. x := 3.)*.

Observera att det är obligatoriskt att tilldela en variabel ett värde när den
deklareras. Till skillnad från andra programmeringsspråk får du inte
deklarera en variabel utan värde. Det är nödvändigt att uttryckligen knyta
varje variabel till ett startvärde. Du får dock gärna initiera
variabeln med objektet **Inget**. I så fall kan variabeln
betraktas som tom *(\>\> x := None.)*. Kort sagt är det inte tillåtet att deklarera en
variabel utan ett startvärde. Alltså är

```
>> x.
```

ogiltigt och ger ett felmeddelande.

{{note}}
xoscript använder dynamisk räckvidd för variabler. För
detaljer, se kapitlet Funktioner.
{{/note}}


## Literaler

XOScript betraktar allt som ett objekt, dvs. alla tal, texter
och kodfragment. Tal som 1, 2, 100, -999 och 1,234 är
Tal-objekt. All text mellan enkla citattecken är Text-objekt.
Alla kodfragment som grupperas mellan klammerparenteser {...} är
Funktion-objekt.

Literal         | Rotobjekt    | Exempel
--------------- | ------------ | ----------
tal             | Tal          | 1,2,3... 
texter          | Text         | \['hello'\]
funktion        | Funktion     | { 1 + 2. }.
                
     
Objekt som tal och texter har alltid sitt ursprung i ett rotobjekt.
Till exempel härstammar alla tal från objektet **Tal**. Alla
texter härstammar från **Text** och alla kodfragment från **Funktion**.
Alla dessa objekt härstammar i sin tur från **Objekt**, som i själva verket är
rotobjektet för alla objekt.


## Meddelanden

Att programmera i XOScript innebär i grunden att
skicka meddelanden till objekt. Den allmänna notationen för att skicka ett meddelande till
ett objekt är följande:

```
<object> <message>
```

För att till exempel ta reda på om talet **2** är ett jämnt tal
skickas meddelandet **jämn?** till objektet **2**:

```
2 jämn?
```

Svaret blir **Sann** (återigen ett objekt). Okända meddelanden
ignoreras vanligtvis av objekt, så inget fel uppstår. Vissa objekt (t.ex.
tal eller texter) svarar på ett okänt meddelande på ett fördefinierat sätt
(mer om detta senare).

Ett objekt kan ta emot tre sorters meddelanden. 

Typ             | Antal argument
--------------- | -------------------
Unärt           | 0      
Binärt          | 1     
Nyckelord       | 1+    


För det första finns **unära
meddelanden**, se exemplet ovan, som saknar argument. För det andra
finns **nyckelordsmeddelanden**, som har ett eller flera argument,
till exempel:

```
>> x := Tal mellan: 1 och: 10.
```

I detta fall skickas meddelandet **mellan:och:** till **Tal**, som
är rotobjektet för alla tal. Resultatet blir ett slumpmässigt tal
mellan 1 och 10. Slutligen finns **binära meddelanden**, som bara har
ett tecken och ett argument:

```
2 + 3
```

Detta ser ut som en matematisk summa, men det är egentligen bara ytterligare ett meddelande.
Meddelandet **+** skickas till **2** med argumentet **3**, vilket returnerar
svaret **5**. Binära meddelanden får skrivas utan kolon.

Binära meddelanden kan kedjas:

```
>> x := 3 + 2 - 1.
```

I detta fragment skickas först **+ 2** till **Tal**-objektet **3**, vilket
resulterar i Tal-objektet **5**, varefter **-1** skickas till detta
tal. Uppmärksamma läsare har rätt i att notera den avvikelse som
detta protokoll uppvisar jämfört med den konventionella matematiska ordningen för
operatorer. XOScript ignorerar den matematiska ordningen till förmån för
konsekvens i sitt meddelandesystem. Som en följd blir summan:

```
2 + 3 * 5 = 25
```

inte 17.

Detta är avsiktligt. Parenteser kan användas för att ändra ordningsföljden:

```
2 + (3 * 5) = 17
```

De flesta objekt returnerar sig själva som resultat som svar på ett visst
meddelande. Detta är praktiskt, eftersom det uppmuntrar till fortsatt dialog med
objektet genom att skicka det ett uppföljande meddelande:

```
Utdata skriv:
[' hello '] trimma versaler.
```

```
HELLO
```

Här skickas två meddelanden till **Text**-objektet: **trimma**, följt
av **versaler**.

I följande fragment är kommatecknet nödvändigt för att ange
att ett nytt meddelande är på väg. Annars blir XOScript förvirrat.

```
Utdata skriv: ['Hello!'], stop.
```

Först skickas meddelandet **skriv:** till pennsymbolen, följt av
**stop**. Utan kommatecknet skulle XOScript tro att du vill skicka
**stop** till **text** **Hello!**, vilket vore meningslöst.

Meddelanden behandlas i följande ordning: från vänster till höger;
börja med meddelanden inom parentes, följt av unära meddelanden. Därefter
binära meddelanden och avsluta sedan med nyckelordsmeddelanden. Se exemplet
nedan:

```
Utdata skriv: 0.5 avrunda + (2 - 1), stop.
```

XOScript läser alltid från vänster till höger: först skickas meddelandet **skriv:**
till Utdata, och det följs av meddelandet **stop**. Inom
själva argumentet läser XOScript från vänster till höger, alltså **0.5 avrunda**
och därefter **+**.

{{note}}
Meddelandet stop lägger till ett radbrytningstecken till texten.
Namnet på detta meddelande är inspirerat av telegrafsystem.
Meddelanden i telegrafsystem 
använde ofta ordet STOP för att markera slutet på en mening
(eftersom skiljetecken var opålitliga eller dyra).
{{/note}}

Dessutom har **avrunda** företräde framför **+**, eftersom det är ett
**unärt meddelande**. På grund av parenteserna beräknas **2 - 1**
först, varefter **1** adderas till resultatet av **0.5 avrunda** (1).

Hela processen ger resultatet **2**, vilket också är det utskrivna
svaret. Efter kommatecknet följer meddelandet stop, som flyttar markören
till en ny rad. Det bästa sättet att helt förstå ordningsföljden
i XOScript-program är förstås genom övning.

Det är värt att notera att blanksteg i XOScript, till skillnad från många andra
programmeringsspråk, är en grundläggande del av syntaxen. Särskilt
när det gäller binära meddelanden kan blanksteg orsaka viss
förvirring. Använd alltid ett blanksteg efter ett binärt meddelande. Du kan inte
fästa ett tal direkt vid meddelandet, till exempel: 

```
3 + 2
```

skiljer sig från 

```
3 +2
```

Det första exemplet (**3 + 2**) skickar
meddelandet **+** till talet **3**, med talet **2** som argument.
Resultatet blir i detta fall **5**. I det andra exemplet (**3 +2**)
skickas det unära meddelandet **+2** till talet **3**. Beroende på
sammanhanget kan det ge ett helt annat resultat.

## Icke-existerande metoder

Att skicka ett meddelande till ett objekt anropar den funktion som har
kopplats till objektet under det meddelandenamnet. Om du skickar ett meddelande
som inte förstås ignorerar det mottagande objektet ditt meddelande
och returnerar i stället en referens till sig självt för fortsatt kommunikation.
Detta kallas tolerant meddelandeöverföring.

Exempel:

```
Utdata skriv: Objekt blah, stop.
```

Detta ger inget fel. Det skriver helt enkelt ut texten **Objekt**.


## Kontrollflöde

I XOScript behövs inga separata grammatikregler för *loopar* och
*villkor*. En if-sats är bara ett enkelt **sann:**- eller **falsk:**-meddelande
till antingen ett **Sann**-objekt eller ett **Falsk**-objekt:

```
2 jämn? sann: {
	Utdata skriv: ['Two is an even number'], stop.
}.
```
I föregående exempel skickas meddelandet **sann:** till **Sann** (svaret
på frågan: är 2 ett jämnt tal?). Som argument skickas ytterligare ett
kodfragment med: ett **Funktion**-objekt. Denna funktion skriver
på skärmen att 2 faktiskt är ett jämnt tal.

Det behövs inte heller några separata skrivregler för en *loop*. För att
köra ett kodfragment tre gånger skickar du helt enkelt **\*** med argumentet
**3** till den **Funktion**:

@test5

I detta kodfragment är **i** indexet. Första gången funktionen
körs är **i** lika med 0, nästa gång den körs är **i** = 1 och
så vidare.

Låt oss titta på ytterligare ett exempel. När en omräkningstabell ska
skrivas ut från *kJ* (kilojoule) till *kcal* (kilokalori) i steg om 100,
se nedan för korrekt notation:

@test599

Här överförs numret på den aktuella raden till parametern
**:line**. I början av en funktion definieras funktionens parametrar.
Oanvända parametrar förblir tomma (**Inget**). Parametrar placeras
alltid i början av funktionen, direkt efter den inledande
klammerparentesen, och föregås av ett kolon.

Meddelandet **medan:** är en kombination av en *loop* och ett *villkor*.
Två funktioner kan länkas med meddelandet **medan:**. Den mottagande funktionen
fortsätter att köras tills funktionen efter kolonet ger ett negativt
resultat. Exempel:

@test600

I kodfragmentet ovan adderas **1** till **x** så länge
**x** är mindre än **5**. När så inte längre är fallet svarar den andra
funktionen med **Falsk**, och följaktligen avslutas körningen av den
första funktionen. Observera att **x** har definierats utanför
funktionen och är en global variabel. Läs kapitlet om funktioner
för att lära dig mer om räckviddsregler.

## Textinterpolering

Listan med *kJ/kcal* skulle kunna göras mer
presentabel. Helst skulle listan se ut så här:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

När du gör om önskad utdata till en mall kan notationen
se ut så här:

```
number1 kJ ➞ number2 kcal
```

Det innebär att **number1** står för kJ-värdet och **number2** för
kcal-värdet. Så här fungerar textinterpolering i XOScript. Det
behövs inga separata grammatikregler för detta i XOScript. Skicka helt enkelt
det ord som ska ersättas till texten, med ersättningstexten
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

Denna ersättningsregel gäller för varje odefinierat meddelande som tas emot
av ett **text**-objekt. Varje meddelande som inte känns igen av
**text**-objektet tolkas på följande sätt: *ersätt meddelandetexten
med texten i meddelandets argument.* Du kan anpassa
programmet på följande sätt:


@test601


För att undvika förvirring om vilka meddelanden som kan eller inte kan användas som
ersättning är det bäst att införa en mallmarkör som &lt; &gt;
för de textsegment i mallen som
ska ersättas.

## Returvärden

För att svara på ett meddelande används returpilen
(*<-*). Följande exempel visar hur man skapar en uppgift
som beräknar en procentsats:

@test602

När uppgiften har definierats och tilldelats variabeln **percentage**
skickas meddelandet **tillämpa:och:** med argumenten **100** och **7**.

Detta kör uppgiften tillämpad på **100** och **7**, dvs. 7 % av 100.
Med hjälp av returpilen returneras svaret från uppgiften tillbaka
till huvudprogrammet.

## Utöka

Även om denna kod är giltig har den en nackdel,
eftersom man måste komma ihåg argumentens ordning. Så varför inte
skriva det så här: *7 percent of: 100 *? Det skulle se mycket mer
*naturligt* ut. För att göra detta möjligt måste vi anpassa föräldraobjektet till
**7**, vilket är objektet **Tal**, så att det förstår
meddelandet **percent of:**. Detta kan åstadkommas genom att skicka **vid:gör:** till
objektet Tal, så här:

@test603

Eftersom procentsatsen i detta fall är talet självt hänvisar vi till själv,
nyckelordet *själv*. Kort sagt betyder symbolen själv: *skicka detta
meddelande till mig själv*.

# Objekt

{{messages}}

Förutom att justera och utöka befintliga objekt kan du också skapa
nya objekt själv, helt enkelt genom att skicka meddelandet **ny**. Anta att du
vill skapa ett fakturaobjekt som upprätthåller en numreringsföljd.
I så fall behöver du först ett fakturaobjekt.

Eftersom varje objekt härstammar från ett annat objekt, som i sin tur
till slut härstammar från rotobjektet för alla objekt, som heter Objekt,
måste man välja vilket av dessa andra objekt ditt
nya objekt ska bygga på. Ditt nya objekt ärver alla egenskaper hos
det objekt som det bygger på, alltså det objekt som meddelandet **ny**
ursprungligen skickades till.

I detta exempel föredras ett ganska neutralt objekt, ett utan alltför
många ärvda egenskaper. Det gör valet enkelt, eftersom det nya objektet
i så fall kan baseras på själva rotobjektet, nämligen
**Objekt**. Notationen för det tänkta fakturasystemet blir då
följande:

@test604

Det aktuella fakturanumret lagras i objektet, och därför står
nyckelordet **egen** framför det. Detta kallas en *egenskap*;
mer detaljer följer.

Vissa företag föredrar att ha årtalet inbakat i fakturanumren.
I så fall kan du skapa ett nytt fakturaobjekt som bygger på ett
tidigare fakturaobjekt, men som ger användaren möjlighet att
ange ett visst år:

@test605

Det finns ingen anledning att skriva implementationen för meddelandet **number**
igen, eftersom den ärvs från det tidigare skrivna **fakturaobjektet**;
följaktligen kan gammal kod återanvändas. XOScript saknar begrepp
som klasser och andra närliggande begrepp. Det innebär att objekt
enbart kan ärva från andra objekt, även kallat *prototypbaserat
arv*.

Nu tillbaka till egenskaperna. Objektegenskaper kan bara nås
*inifrån objekthierarkin*, så dessa egenskaper
kan inte uppfattas av andra objekt.

Till skillnad från andra programmeringsspråk är alla egenskaper hos objekt
uteslutande synliga för det objekt som har skapat egenskapen och för
härledda objekt. 

En vanlig teknik är att använda ett objekt som en sorts *ritning*,
vilket till exempel är fallet med fakturorna som diskuterades tidigare.
Ett annat bra exempel är **Point**. Anta att du skapar ett
datorprogram som gör beräkningar med hjälp av punkter på en karta. Du
kan utveckla objektet **Point** med egenskaperna
x-koordinat och y-koordinat, som görs tillgängliga för
omvärlden via meddelanden:

@test606

Meddelandet **=** jämför de två punkterna med hjälp av meddelandet **och:**.
Den första jämförelsen resulterar i en **Sann** eller en **Falsk**. Dessa är booleska
objekt. När du skickar meddelandet **och:** till ett Sann-objekt och
argumentobjektet efter kolonet också är **Sann**, får du
återigen svaret **Sann**. När något av dem är **Falsk** får du
svaret **Falsk**. Observera att en punkt inte kan läsa den andra punktens
koordinater. Det är nödvändigt att skicka ett meddelande till den andra punkten för att be
om dessa data: **x-coordinate** och **y-coordinate**. Som redan har
förklarats kan egenskaper ju bara hämtas inifrån
själva objektfamiljen. 

Observera att meddelandet **=** används här för att utföra punktjämförelsen.
Lika gärna hade ett annat meddelande kunnat användas, till exempel
**is:** eller **equal:**, men att återanvända tecknet **=** verkade
lämpligt i detta fall.

## Arv

Du kan återanvända tidigare skriven kod för att skapa en hierarki
av objekt. Till exempel:

```
>> Animal := Objekt ny.
>> Dog := Animal ny.
>> Poodle := Dog ny.
```

I detta fall ärver **Dog** allt beteende och alla egenskaper
från **Animal**, och objektet **Animal** ärver i sin tur allt beteende från
**Objekt**, rotobjektet för alla objekt.


## Åsidosättning


I följande exempel skapas en ny sorts lista:
**Combination**, där varje element garanterat är unikt.
Listans funktioner återanvänds genom arv:

@test607

Lägg märke till hur den andra **red** utesluts från listan.

Ibland kan det vara nödvändigt att åsidosätta ett beteende hos ett objekt.
Till exempel när tal adderas och måttenheter måste
tas med i beräkningen. I följande exempel skapas objektet **Size**.
Detta objekt returnerar ett tal som vid additionen tar
hänsyn till enheten för det tal som ska adderas. Objektet **Tal**
kontrollerar om det handlar om *tum* eller *fot*. Programkoden
skulle kunna se ut så här:

@test608

## Rekursion

I föregående exempel åsidosätts plus**tecknet**. Observera
att den slutliga additionen ändå måste utföras till slut, vilket faktiskt
sker på följande rad:

```
>> answer := själv + (tal x factor).
```

Hur förstår då XOScript att detta plus**tecken** syftar på
den ursprungliga additionslogiken?** En annan tolkning kunde till exempel
vara att XOScript upprepade gånger skickar samma meddelande till samma
objekt, vilket i sin tur skulle resultera i en **oändlig loop**. Det är uppenbarligen
inte avsikten. Så snart du skickar ett meddelande till ett objekt
som skulle köra exakt samma kod, inser XOScript
i detta fall att det underliggande, åsidosatta meddelandet avses. Ditt
program skyddas alltså automatiskt mot denna form av oändliga
loopar. När det däremot verkligen är ditt mål att köra samma funktion från
den aktuella funktionen, måste du först skicka meddelandet
**rekursiv**. I detta fall blir resultatet en oändlig
loop. Det finns dock användbara tillämpningar för rekursiva uppgifter,
anta till exempel att du vill beräkna fakulteten för ett givet
tal. Lägg då helt enkelt till meddelandet **factorial** till
Tal:

@test609

Detta kräver rekursion. Den uppgift som är kopplad till
meddelandet **factorial** måste nämligen köras igen inom den funktionen.
Det är alltså nödvändigt att anropa fakultetsfunktionen inifrån
själva fakultetsfunktionen. Som regel förhindrar XOScript detta förfarande
på grund av risken att hamna i en oändlig loop. Av denna anledning
är det avgörande att föregå meddelandet med ordet **rekursiv**. Detta
görs för att göra XOScript medvetet om att det är din
avsikt att köra samma uppgift, och att du inte har gjort ett misstag.

## Klassliknande objekt

Även om xoscript inte erbjuder klasser är det trivialt att efterlikna klassliknande
beteende. Åsidosätt helt enkelt meddelandet ny.

```
>> Animal := Objekt ny.
Animal vid: ['ny'] gör: {
	<- själv ny initiera.
}.

Animal vid: ['initiera'] gör: {
	egen sound := ['?'].
	egen legs  := 4.
}.
```

I kodfragmentet ovan skapar vi ett objekt som heter Animal.
Detta objekt fungerar som en *ritning* för alla sorters djur,
som hundar och katter. Föräldraobjektet Animal skrivs
med stort A för att visa att detta är ett klassliknande objekt.
Därefter åsidosätter vi meddelandet ny genom att skriva vår egen ny-metod.
I detta fall skickar den meddelandet ny till själv, följt av meddelandet
initiera. Eftersom xoscript som standard blockerar rekursion orsakar detta inte
en oändlig loop. I stället skickas meddelandet ny till föräldraobjektet
(Objekt), vilket resulterar i en ny instans av Animal. Vi skapar alltså
ett nytt objekt baserat på samma objekt som vi skapade vår ny-metod för.
Detta är helt giltigt. Nu skickar vi också meddelandet initiera, vilket säkerställer
att Animal-objektet har standardvärden för sina egenskaper. Som standard
har ett djur 4 ben och ljudet är okänt (därav frågetecknet).
För att skapa en ny instans av vårt Animal kan vi helt enkelt skriva:

```
>> a := Animal ny.
```

Nu får vi en ny instans av Animal med 4 ben, okänt ljud och
en initiera-metod. Precis som i andra OOP-språk kan vi också
utöka vårt Animal:

```
>> Dog := Animal ny.
Dog vid: ['initiera'] gör: {
	själv initiera.
	egen sound := ['barks'].
}.
```

Vi kan enkelt testa detta genom att lägga till en text-metod:

```
Animal vid: ['text'] gör: {
	<- egen legs text + egen sound.
}.
```

Låt oss sätta ihop allt:

@test13


Att skapa ett objekt som försätts i ett givet utgångsläge är ett
vanligt problem. Anta att ett objekt **Rectangle** ska skapas
för att beräkna omkrets och area. En möjlig notation vore:


```
>> Rectangle := Objekt ny.

Rectangle vid: ['area'] gör: {
	<- egen längd * egen width.
}.
```

Att ange en längd och en bredd är uppenbarligen en förutsättning. För det
ändamålet kan meddelandena **längd:** och **width:** läggas till:


```
Rectangle vid: ['length:'] gör: { :längd
	egen längd := längd.
}.

Rectangle vid: ['width:'] gör: { :width
	egen width := width.
}.

```

Denna rektangel kan sedan användas på följande sätt:


```
>> rectangle := Rectangle ny length: 2, width: 3.
Utdata skriv: rectangle area.
```

Om man däremot förbiser att ange längd och bredd från början
uppstår ett felmeddelande:

```
>> rectangle := Rectangle ny.
Utdata skriv: rectangle area.
```

ger följande fel:

```
Nyckel hittades inte:längd
```

För att förhindra detta är det bättre att en rektangel
alltid har en startlängd och startbredd, till exempel 0. I detta
fall är det alltså nödvändigt att **åsidosätta** meddelandet **ny**.

@test610

Om vi åsidosätter meddelandet ny efterliknar vi i princip en **klass**.

XOScripts värld är fylld av en mångfald objekt som är
tillgängliga för ditt program redan från början. I de följande kapitlen
diskuteras alla dessa kärnobjekt.

## Ögonblicksbilder

Du kan spara ett objekt (tillsammans med dess aktuella tillstånd) på disk med:

```
myobject save-as: ['saved.bin'].
```

För att läsa in objektet från disk igen:

```
>> myobject := Objekt load-from: ['saved.bin'].
```

Ögonblicksbilder kan användas för att spara ett visst tillstånd eller för att förbättra prestandan.
Att läsa in en ögonblicksbild undviker lexning, parsning och programuppsättning.
I framtiden kan dessutom ytterligare prestandafördelar införas
med ögonblicksbilder, som optimering av vissa mönster eller identifiering och
optimering av heta kodvägar.

{{warning}}
Ögonblicksbilder är en experimentell funktion, använd den inte i produktion.
För att aktivera experimentella funktioner, kompilera med -D EXPERIMENTS.
{{/warning}}


@test712

# Inget-objektet

{{messages}}

Objektet Inget
representerar tomhet, eller ännu bättre, frånvaron av information.
Ibland får du detta objekt som svar på ett meddelande
när resultatet är **ingenting**. Den viktigaste frågan
du kan ställa till objektet **Inget** är: **Inget?**.
Svaret blir alltid **Sann**.

```
Utdata skriv: Inget Inget?.
```

resultat:

```
Sann
```

Alla andra objekt än **Inget** svarar med **Falsk**.
Kodfragmentet ovan kan verka lite filosofiskt, men objektet **Inget**
har definitivt ytterst praktiska tillämpningar. Du får till exempel
objektet Inget som svar om du frågar efter ett
listelement som inte finns. Du kan också använda objektet Inget
om du vill deklarera en variabel men ännu inte vill ange ett värde.
I stället **tilldelar** du bara specialvärdet **Inget**. I
XOScript är det inte tillåtet att deklarera en variabel utan värde, som:


```
>> värde.
```

I stället måste du skriva följande:

```
>> värde := Inget.
```

@api_None_base

# Booleska värden

{{messages}}

Till skillnad från de flesta populära programmeringsspråk när detta skrivs
har XOScript bara ett enda Sann-objekt och ett enda Falsk-objekt.
För att förtydliga: varje gång du skriver **Sann** innebär det inte att
ett nytt objekt har skapats. I stället använder du alltid en referens. Det
innebär att när du skriver följande:

\>\> x := Sann.

refererar **x** till objektet **Sann**. Villkorlig kod och loopar
kontrollerar också denna referens. I XOScript är betydelsen av **Sann** och **Falsk**
inte fastställd. Faktum är att ett XOScript-program blir ordentligt omskakat av
en sats som denna:

Sann := Falsk.

Resultatet av sådana handlingar är odefinierat, men det förblir en giltig
handling och är därför formellt tillåten. Dessutom finns det ett Boolesk-objekt,
som är rotobjektet för både **Sann** och **Falsk**, eftersom båda
härstammar från rotobjektet. Boolesk-objektet i sig har dock
ingen praktisk tillämpning.

## Fallgropar

Var försiktig när du använder **och:** och **eller:**

```
Utdata skriv: (Falsk or: Sann or: Sann), stop.
Utdata skriv: (Falsk eller: Sann, eller: Sann), stop.
```

Ger

```
Falsk
Sann
```
eftersom meddelandet **eller:** bara tar 1 argument. Det första meddelandet
skickar **eller:eller:** till Falsk, vilket inte finns, så objektet ignorerar
meddelandet och returnerar sig självt (Falsk). Den andra raden
skickar däremot **eller:** följt av ytterligare ett **eller:** (med hjälp av en kedjesymbol, dvs. ett kommatecken: ,).


@api_Boolean_base

# Tal

{{messages}}

Varje gång du skriver ett tal, till exempel 9, -10 eller 3,12, omvandlar
XOScript bakom kulisserna dessa tal till ett **Tal**-objekt. Du
kan skicka meddelanden till detta Tal-objekt, eller så kan du tilldela talet
till en variabel och skicka meddelanden efteråt:

```
10 jämn?

>> tenner := 10.
tenner jämn?

```

Båda notationerna är giltiga. Tal-objektet svarar på följande
meddelanden...

De flesta av dessa meddelanden är självförklarande och låter dig utföra
matematiska operationer eller jämförelser.

{{note}}
Observera att du kan använda ≤ ≥ ≠ × och ÷ i stället för deras ASCII-motsvarigheter.
Det är en smaksak.
{{/note}}

Skillnaden mellan binära matematiska meddelanden (+) och
deras nyckelordsvarianter (lägg-till:) är att de förstnämnda returnerar
ett nytt tal, som är resultatet av operationen, medan
objektet självt ändras med de sistnämnda. Detta illustreras i
följande exempel:

@test597

I exemplet ovan är b = 4 och a = 3. Med **lägg-till: 2** ökas värdet
av a med 2, medan **+ 3** skapar ett nytt tal som är
lika med a + 3. Detsamma gäller för andra matematiska operationer, t.ex.
multiplikationer. Om du använder multiplikationssymbolen får du ett
nytt objekt som svar. Om du använder meddelandet **multiplicera-med:**
multiplicerar du själva talet.

Med meddelandet **mellan:och:**, till exempel i: **Tal
mellan: X och: Y**, får du ett tal mellan X och Y. På detta
sätt kan vilket slumptal som helst genereras:

```
>> a := Tal mellan: 1 och: 10.
Utdata skriv: a, stop.
```

Från och med version 1.4 är den inbyggda slumptalsgeneratorn i xoscript
kryptografiskt säker, så vitt vi vet.

Du kan koppla en **beteckning** till ett tal, till exempel **6
apples**. Varje meddelande som inte känns igen av ett
tal betraktas som en beteckning. Du kan hämta beteckningen för
ett tal med hjälp av meddelandet beteckning:

En beteckning är i grunden ett Text-objekt som lagras tillsammans med Tal-objektet.
Beteckningen skrivs också ut efter talet vid en
**skriv:**-tilldelning. Beteckningar kan till exempel användas för att addera belopp
i blandade valutor. När beloppen adderas kan du fråga
efter beteckningarna. Följande programexempel illustrerar denna
princip med hjälp av en historisk valutakalkylator (eftersom växelkursen
förblir någorlunda stabil!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Texter

{{messages}}

Varje gång en text placeras mellan **hakparenteser och citattecken** ['...']
skapar XOScript ett nytt textobjekt åt dig. Se dock till
att använda rätt citattecken. Citattecknet i
början av texten skiljer sig från det i slutet (det gör att du kan
använda enkla citattecken utan att behöva undanta dem).

## UTF8

Texter i xoscript innehåller vanligtvis utf8-kodad text. Även om
det tekniskt sett är möjligt att ha binärt innehåll eller innehåll som inte är utf8 i
en text, rekommenderas det att använda blobbar för det. Blobbar
tillhandahålls av serverinsticksmodulen (se kapitlet ffi).
Generellt tillhandahålls blobbar/ffi
per insticksmodul/plattform, eftersom de är knutna till plattformen
och arkitekturen (ffi/blobbar). Skriptspråkets kärna försöker
förbli så plattformsoberoende som möjligt.

## Typomvandling

Du kan skapa en kopia av varje objekt
med en annan typ genom att använda följande meddelanden:

Meddelande | Resultat
------- | ------
tal     | Omvandlar till ett tal
text    | Omvandlar till en text
boolesk | Omvandlar till ett booleskt värde
  
Följande regler **gäller**:

meddelande | Inget   | Boolesk            | Tal                   | Text      | Övrigt              
-------- | --------- | --------           | --------              | --------  | --------
boolesk  | Falsk     | e/t                | 0→Falsk annars→Sann   | Sann      | Oftast Sann
tal      | 0         | Falsk→0 Sann→1 | e/t                       | ['n']→n | Oftast 1
text     | ['Inget'] | ['Falsk']/['Sann'] | ['n']                 | e/t       | Beror på

## Kopiering

Värden i XOScript skickas alltid **som referens**. I andra språk
beror det på värdets typ; i XOScript finns det bara ett sätt,
som referens. XOScript gör aldrig en kopia av ett värde. För att kopiera ett objekt
måste du skicka meddelandet **kopiera**. 

@test611

Här hade du kanske väntat dig att utdata skulle bli Dolly i stället
för Donny. Så är dock inte fallet, eftersom båda namnen refererar till samma
objekt. När man arbetar med en loop inträffar något liknande:

@test612

XOScript använder faktiskt **alltid** referenser, så vid **:quantity**
anger loopen ovan också referensen till elementet
i listan.

För att kopiera ett objekt måste du ange denna handling
**uttryckligen**:

@test613

Genom att skicka det unära meddelandet **kopiera** till en text returnerar
objektet en kopia av samma textobjekt. Det är möjligt att kopiera Tal-objekt,
booleska objekt, listor och ordböcker på samma sätt.

Du kan också definiera din egen kopieringsimplementation; det är till och med
nödvändigt om du skapar egna objekt. Standardimplementationen
av kopiera för en lista gör en ytlig kopia, den skapar en
ny lista med samma element.

@test614

I detta fall läggs 4 bara till i kopian.
Men eftersom kopian är ytlig är objekten i båda listorna
desamma.

@test615

Om vi alltså lägger till 2 sist i varje namn i kopian påverkas även den ursprungliga
listan.

För att åtgärda detta behöver vi göra en **djup kopia**. En sådan kopieringsåtgärd
för en lista kan sättas samman på följande sätt:

@test616

Lägg också märke till meddelandet rekursiv; detta meddelande måste
skickas före meddelandet kopiera.

Det är viktigt att komma ihåg att även om en kopia av ett objekt
ofta ser ut precis som originalet, så är den i själva verket
aldrig densamma. Rotobjektet definierar ett meddelande **equal:**,
som kan användas för att jämföra objekts identitet. Titta på
följande exempel:

@test617

## Implicit omvandling

XOScript använder **implicit omvandling** för att omvandla objekt. För att skriva ut en
lista på skärmen skickar XOScript till exempel meddelandet
*text* internt till listan. Detta kan visa sig mycket användbart om
du vill skriva ut en lista som en kommaseparerad lista.
Meddelandet *text* kan skrivas över: 

@test620

@api_String_base
@api_Format_base


## Servertexter

Följande Text-funktioner läggs till av
serverinsticksmodulen.

@api_String_server

# Funktioner

{{messages}}

Du kan gruppera kod mellan { och }, och då blir den en funktion.
I xoscript använder vi ibland också termen uppgift eller helt enkelt
kodblock.

Du kan köra en funktion genom att skicka meddelandet *starta*.


```
{ Utdata skriv: 123, stop. } starta.
```

Om din funktion tar argument, använd **tillämpa:**.

```
{ :a Utdata skriv: a, stop. } tillämpa: a.
```

Se även exemplen nedan.
På grund av den enkla arkitekturen kan en funktion bara ha
en returpunkt. För att undvika overhead eller överdriven nästling av
villkor kan du använda en procedur (vilket är detsamma som att använda
multiplikationstecknet med argumentet 1):

```
{
  (a = 1) sann: { x := 1. }, avbryt.
  (a = 2) sann: { x := 2. }, avbryt.
} procedur.
```

På så sätt utvärderas (a = 2) inte om a = 1.
Dessutom behöver du på detta sätt inga nästlade sann-meddelanden.
När du märker att du nästlar villkor, tänk
på meddelandet procedur. Det kan göra din kod
lättare att läsa.


Här är en viktig fallgrop:

```
{
	Falsk falsk: {
		Utdata skriv: ['End the loop.'].
	}, avbryt.
	
	Utdata skriv: ['Dont show me.'].

} procedur.

```

I detta fall visas texten 'Dont show me'.
Detta beror på att **avbryt** skickas till Falsk. Om du vill utföra
ett avbrott måste det skickas som ett meddelande till **Sann**.
 

```
{
	Falsk inte sann: {
		Utdata skriv: ['End the loop.'].
	}, avbryt.
	
	Utdata skriv: ['Dont show me.'].

} procedur.

```

Fungerar som förväntat.

## Undantag

Undantag kan hanteras så här:

```
{ Task 1 } fånga: { Task 2 }, starta.
```

Du kan också avsiktligt orsaka ett fel i ditt program och
på så sätt aktivera hanterarblocket. Detta görs genom att skicka
meddelandet **fel:** till den aktuella uppgiften, som visas i nästa
illustration:

```
{
denna-uppgift fel: ['Whoops!'].
} fånga: { :mistake
Utdata skriv: mistake.
}, starta.
```

## Injicera värden

XOScript ger uppgifter möjlighet att injicera värden. Titta nu
på uppgiften nedan:

```
>> sending := {
	Newsletter till: egen recipient.
}.
sending sätt: ['recipient']
värde: ['info@recipient.org'].
sending starta.
```


Denna illustration visar en tänkt uppgift som skickar ett nyhetsbrev
till en e-postadress eller **recipient**. Denna mottagare kan injiceras
i uppgiften utifrån, innan uppgiften startas, genom att skicka
meddelandet **sätt:värde:** till uppgiften. På så sätt förinställs värdet för
**recipient** i uppgiften. Detta värde kan också ändras,
och uppgiften kan sedan köras igen. Detta är en användbar metod när man använder
uppgiftsobjekt.

## Tomma funktioner

Tomma uppgifter är inte tillåtna. I teorin skulle en tom uppgift se ut
så här: **{}**, men XOScript betraktar detta som ett språkfel. Om du
vill deklarera en tom uppgift kan du använda objektet Inget:

```
>> task := Inget.
```

Även om detta inte är en riktig uppgift utan ett Inget-objekt kan ett starta-meddelande
ändå skickas:

```
>> answer := task starta.
```

Detta är faktiskt detsamma som:

```
>> answer := Inget starta.
```

Eftersom objektet **Inget** inte känner igen meddelandet **starta**
returnerar det sig självt som svar, vilket gör att svaret återigen blir **Inget**.
Det finns alltså inget behov av en tom uppgift. Tack vare den eleganta
utformningen av programmeringsspråket XOScript kan du helt enkelt använda objektet Inget
för detta.

## Dynamisk räckvidd

När en Funktion behöver en variabel men inte kan hitta den
kontrollerar den variablerna i den Funktion som **anropade** den,
och fortsätter sedan uppåt i kedjan av Funktioner.
Denna sökprocess fortsätter tills variabeln hittas.
Om variabeln fortfarande inte hittas visas ett felmeddelande. Denna metod för att söka efter en
variabel kallas **dynamisk räckvidd**.

För att illustrera denna princip:

@test618

@api_Code_base

# Rotobjekt

{{messages}}

Objektet som heter **Objekt** är rotobjektet för alla objekt i
XOScript och tillhandahåller språkets kärnfunktioner. 

Det oftast skickade meddelandet
är **vid:gör:**, som utökar ett objekts funktionalitet. Detta
meddelande tas emot av rotobjektet, som därmed kopplar den
angivna uppgiften till meddelandet och på så sätt utökar det härledda
objektet.

## Uppsamlingsmetoder

Om du skickar ett meddelande som inte motsvarar
en metod i objektet ignoreras det normalt. Du kan dock ange
så kallade **magiska metoder** eller **uppsamlingsmetoder** som
anropas om meddelandet inte förstås av objektet.

Det finns 4 uppsamlingsmetoder. Varje meddelande motsvarar
ett visst antal argument.

Uppsamlingsmeddelande | Antal argument
-------------------- | -------------------
svara:               | 0
svara:och:           | 1
svara:och:och:       | 2
svara:och:och:och:   | 3


@test619

## Programmatiska meddelanden

I stället för att skicka ett meddelande direkt till ett objekt kan det också
skickas via en variabel. För att göra det använder du meddelandet
**meddelande:argument:**. 

@test396

@api_Object_base

# Listor

{{messages}}

XOScript känner till två typer av samlingar: *listor* och *ordböcker*.
**Listor** är uppräkningar av objekt i en *fast ordning*. Ordböcker har
ingen ordning, utan liknar i stället en teckenförklaring med en nyckel (eller term) och dess
motsvarande värde. Listor kan jämföras med arrayer (PHP, Java, C)
och listor (Python). Ordböcker kan jämföras med associativa arrayer (PHP) eller
dictionaries (Python) i andra programmeringsspråk. För att skapa
en ny Lista skriver du:

```
>> fibonacci := Lista ny.
```

Denna tomma lista kan fyllas med hjälp av **lägg-till-sist:** :

```
fibonacci lägg-till-sist: 0.
fibonacci lägg-till-sist: 1.
fibonacci lägg-till-sist: 1.
fibonacci lägg-till-sist: 2.
fibonacci lägg-till-sist: 3.
fibonacci lägg-till-sist: 5.
fibonacci lägg-till-sist: 8.
fibonacci lägg-till-sist: 13.
```

Om vi skriver ut listan på skärmen:

```
Utdata skriv: fibonacci, stop.
```

ser vi:

```
Lista ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

I stället för lägg-till-sist kan du också använda ; för att lägga till element i en lista:


```
>> fibonacci := Lista ny ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Semikolonen (;) är alla binära meddelanden som lägger in ett
värde i listan.

## Kedjning

Anta att du har en lista som:

```
>> x := Lista ny ; 1 ; 2 ; 3.
```

Om du vill radera det första och det sista elementet skulle ditt
meddelande vara:

```
x ta-första ta-sista.
```

Tyvärr fungerar den föregående notationen inte korrekt.
Meddelandet **ta-första** returnerar listans första element, som
i sin tur blir mottagare av meddelandet **ta-sista**.
Meddelandet **ta-sista** skickas alltså inte till **x**, utan till 2. En
möjlig lösning på detta problem vore att skapa två separata
satser, som: 

```
x ta-första.
x ta-sista.
```

Detta är dock ganska opraktiskt, särskilt när du behöver
radera fler än två element. Därför erbjuder XOScript en
alternativ meddelandestruktur för den här typen av situationer. I
**alternativa** meddelandestrukturer ignoreras objektens svar
och du får mottagarobjektet tillbaka som svar gång på gång.
En **alternativ** meddelandestruktur inleds genom att skicka
meddelandet **gör** till ett objekt, och den **alternativa** meddelandestrukturen
kan avslutas genom att skicka meddelandet **klar**. I det
illustrerade exemplet kan detta tillämpas på följande sätt:

```
>> x := Lista ny ; 1 ; 2 ; 3.
x gör ta-första ta-sista klar.
```

@api_List_collections

# Ordböcker

{{messages}}

**Både Lista och Ordbok är samlingar. Till skillnad från en
lista har en ordbok dock **ingen** ordning. En annan skillnad mellan de två
är att en ordbok består av objektpar. Ett objekt fungerar som uppslagsord (eller
nyckelord) för att söka efter det andra objektet. Ett bra exempel på en
sådan lista är en prislista, som:


```
>> menu := Ordbok ny
	sätt: ['£5'] vid: ['apple pie'],
	sätt: ['£6'] vid: ['carrot cake'],
	sätt: ['£3'] vid: ['fudge'].
```

Precis som för en lista används meddelandet sätt:vid:
för att lägga till ett objekt i en lista. Skillnaden är att, till skillnad från
en lista, två objekt länkas samman. Det första objektet är, precis som
för en lista, det objekt som du lagrar i listan. Det andra
objektet är inte dess position i samlingen, utan det **uppslagsord**
som gör att det föregående objektet kan hämtas vid ett senare tillfälle.
Kort sagt fungerar en ordbok ungefär som ett lexikon: med hjälp av nyckelordet
kan betydelsen hittas. För att till exempel hämta priset på en fudge
ur listan ovan:

```
>> price := menu vid: ['fudge'].
```

Du kan också använda den koncisa notationen:

```
>> price := menu ? ['fudge'].
```

Om de uppslagsord som du använder för att lagra objekt saknar blanksteg
(och inte krockar med andra fördefinierade meddelanden)
kan även nästa notation användas:

```
>> menu := Ordbok ny
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Notationen ovan läser utan tvekan lite mer naturligt.
För att fråga efter priset på en
fudge kan följande förenklade notation användas:

```
>> price := menu fudge.
```

@api_Dict_collections

# Fil

{{messages}}

Objektet **Fil** ger grundläggande åtkomst till filsystemet.
Du kan använda detta objekt för att läsa in hela filer i en variabel
på en gång, eller skriva variabler till filer på en gång. Läsning rad för rad
stöds också. Detta är de vanligaste fil-I/O-operationerna
i ett skriptspråk. Avancerade filoperationer kräver
användning av FFI via serverinsticksmodulen eller en separat IO-insticksmodul.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Datum/tid

{{messages}}

För en strukturerad representation av tid och datum använder XOScript
objektet **Moment**. Om ett nytt Moment-objekt skrivs ut på skärmen visas
aktuellt datum och aktuell tid:

```
Utdata skriv: Moment ny, stop.
```

Kan resultera i något i stil med:

```
2020-10-10 12:16:39
```

Det är också enkelt att läsa ut de enskilda tidskomponenterna. Om det till
exempel bara är nödvändigt att veta det aktuella året kan meddelandet
**år** skickas till momentet, och svaret blir då ett
Tal-objekt som enbart innehåller året:

```
>> m := Moment ny.
Utdata skriv: m år, stop.
```

@api_Moment_system

# Program/standardutdata

{{messages}}

Program-objektet representerar den app som körs för tillfället. Detta objekt
erbjuder funktionalitet för att köra systemkommandon, inkludera delprogram,
läsa argument med mera. Alla systemrelaterade funktioner.

## Standardutdata

Utdata är standardutdataobjektet. Det har i grunden två metoder:
**skriv:** och **stop**. Meddelandet skriv: används för att skicka en text
till stdout, meddelandet stop skriver ut ett radbrytningstecken.
I stället för **stop** kan du också använda \\n.

Exempel:

```
Utdata skriv: ['Hello World'], stop.
```

resultat:

```
Hello World
```

## Moduler/insticksmoduler

XOScripts värld kan utökas med nya systemobjekt genom att
installera moduler. Ett nytt systemobjekt kan läggas till i XOScripts
värld genom att placera modulfilen (vanligtvis en fil med ändelsen .so
) i mappen mods. 

När du skickar ett meddelande till det objekt som görs tillgängligt via
insticksmodulen läses den automatiskt in av XOScript.

Du kan också skriva insticksmoduler själv. Insticksmoduler skrivs i
programmeringsspråket C. Du hittar en exempelinsticksmodul i källkodspaketet
under src/plugins/example.


## Reflektion

Det finns olika sätt att utforska systemet
medan programmet körs. XOScript har ett par metoder för att
upptäcka vilka objekt som finns och vilka meddelanden dessa objekt
svarar på. För det första kan varje objekt tillfrågas om vilken **typ** det är,
men typer i XOScript är formbara och därför opålitliga.

Det är också möjligt att fråga Program-objektet om ett
givet objekt redan finns i programmet:

```
Program Tool sann: { ... }.
```

Om ett objektnamn
består av en enda symbol är det bäst att använda
följande notation för att undvika förvirring:

```
Program hitta: ['X'], sann: { ... }.
```

Förutom att fråga om objekt är det också möjligt att fråga
Program-objektet om meddelanden. Man kan till exempel fråga om
objektet **Tal** känner till meddelandet **mellan:och:**, på det sätt
som illustreras nedan:

```
Program Number: ['between:and:'], stop.
```

@api_Program_system

# server

{{messages}}

Serverinsticksmodulen i xoscript erbjuder funktionalitet för att
skapa applikationer på serversidan. För att läsa in
serverinsticksmodulen, använd:

```
Server initiera.
```

För enkelhetens skull rekommenderas det också att läsa in
filerna webtools.xo och template.xo.

```
Program använd: ['webtools.xo'].
Program använd: ['template.xo'].

```

## Serverinställningar

Du kan ange följande serverinställningar:

```
	# default values are given
	# so if you do not set anything these
	# values are used...

	Program 
	inställning: ['max-postfields']
	värde: 40.

	Program 
	inställning: ['max-contentlength']
	värde: 2000000. # 2MB

	Program 
	inställning: ['max-time']
	värde: 5000. # 5sec

```

## Hej världen

Här är ett mycket enkelt webbprogram som du kan använda med en
vanlig CGI-server som Apache2, NGINX, OpenHTTPD eller någon annan
välkänd server.

```
#!/bin/xo

Server initiera.
Program använd: ['webtools.xo'].

>> web-document := Webbdokument ny.

web-document skriv-ut: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Om du inte vill använda objektet Webbdokument går det bra, men
då måste du skriva HTTP-huvudena själv:

```
#!/bin/xo
Utdata skriv: ['Content-type: text/html; charset=utf-8 \n\n'], stop.
Utdata skriv: ['hello world!'], stop.
``` 

## Förfrågan

Objektet HTTP-Förfrågan kan användas för att hämta GET-/POST-/COOKIE- och
UPLOAD-data:

```
>> begäran  := HTTP-Förfrågan ny.
>> search   := begäran get: ['search']. # ?search=books
>> password := begäran post: ['password']. # from form
>> selected := begäran get-lista: ['sel[]']. #?sel[]=1&sel[]=2
>> selected := begäran post-lista: ['sel[]'].
>> cookie   := begäran cookie: ['session-id'].
>> upload   := begäran upload: ['file'].
>> temppath := upload ? 1.
>> filename := upload ? 0.
```

## Maxpost/längd

Standardvärdet för maximalt antal postfält är 40 och standardvärdet för maximal
innehållslängd är 2MB. För att konfigurera detta annorlunda per skript:

```
Program inställning: ['max-contentlength'] värde: 1. 
Program inställning: ['max-postfields'] värde: 1. 
```

{{note}}
Om innehållslängden överskrider maximum
avslutas processen, eftersom vi inte längre kan vara säkra
på att innehållet är säkert.
{{/note}}

Gränsen maxtime bestämmer den maximala tiden i ms
för att läsa stdin/postdata.

```
Program inställning: ['max-time'] värde: 5000. # 5sec
```

Detta gäller endast I/O-läsningen av posten och förhindrar
slowloris-liknande attacker. Om du verkligen vill begränsa
körtiden för en operation, använd Program alarm:.

## Databas

Objektet Database kan användas för att skicka frågor till MariaDB/MySQL.
För att ansluta till en databas gör du:

```
>> db := Maria-DB ny värd: ['localhost'],
	användarnamn: ['xo'],
	lösenord: ['pass123'],
	databasnamn: ['xobase'],
	anslut.

```

För att infoga en post, använd:

```
>> sökparametrar := db fråga: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parametrar: ( Lista ny ; ['abc'] ; 12.35 ; 6 ). # parameterized queries

{  sökparametrar utför. db bekräfta. }
fånga: { :e db återställ.  }, starta.
```

Observera att xoscript *enbart* arbetar med transaktioner och aldrig gör autocommit.
Om autocommit inte kan inaktiveras får du ett anslutningsfel.
Använd alltid parameterbindning för frågor, lägg aldrig till användarindata direkt
i SQL-koden.

Hämta det infogade id:t så här:

```
Utdata skriv: ['INSERTED: '] + sökparametrar insert-id, stop. # insert id
```

För att hämta poster:

```
>> sökparametrar :=
db
	fråga: ['SELECT * FROM book order by id desc limit 2'], 
	hämta: { :row 
		Utdata skriv: row id + [' '] + row description + [': '] + row price, stop.
	}. # fetching rows

```

## Sessioner

För beständighet kan du lagra och hämta data från ett sessionsobjekt.
Skapa först ett nytt **Webbdokument**. Objektet Webbdokument knyter samman
förfrågan, huvuden, HTML och session. Detta beror på att du, när du
besöker en webbplats med din webbläsare, bara ser HTML-koden. Men hela
Webbdokumentet består även av **huvuden**. Till exempel
innehåller de flesta HTTP-svar ett huvud som: Content-type:text/html för
att tala om för webbläsaren att de data som följer ska återges som HTML
(och inte till exempel laddas ner som en fil). Sessioner är ett sätt att
lagra användardata mellan förfrågningar. För att hålla reda på dessa data måste vi
sätta en kaka (cookie), och även denna kaka sätts via ett huvud. Därför
samlas allt i Webbdokumentet (eftersom det är det fullständiga
dokumentet som innehåller både huvuden och HTML eller andra data).


```
# First we make a new Web Document instance
>> web := Webbdokument ny.

# Now we start a session, this will generate a Header for a cookie and
# create a file to store your data, associated with that cookie
>> session := web starta-session.

# Now we can treat session like a dict
session userid: 123.
```

För att förstöra sessionen (vid utloggning):

```
web förstör-session.
```

## Huvuden

Webbdokumentet låter dig också sätta andra välkända huvuden.
Om du till exempel vill omdirigera användaren till en annan URL:

```
web gå-till: ['/other.html'].
```

Under huven genererar detta kommando också det HTTP-huvud som skickas
tillsammans med dina övriga data eller din HTML för att instruera webbläsaren att navigera
till den angivna måladressen.

För att lägga till ett eget huvud:

```
web huvud: ( 
	HTTP-Huvud ny
	nyckel: ['Content-Length']
	värde: 400
).
```

För att visa en 404-sida:

```
web hittades-inte: ['OOps..'].
```


## Mallar

Standardmallsystemet är mycket enkelt. Du behöver inte lära dig
en ny mallsyntax. Dessutom säkerställer mallmotorn en verklig separation
mellan presentation och affärslogik.

För att skapa en mall från en fil:

```
>> tpl := web mall: ['templates/ux.tpl'].
```

Mallsystemet använder markörer. 
Det finns tre typer av markörer: klippmarkörer, klistermarkörer och
platsmarkörer. Grundidén är verkligen enkel: du klipper ut
områden som identifieras av klippmarkörer och kan klistra in dem i
områden som identifieras av klistermarkörer. Du kan injicera texter i
platsmarkörer.

Givet följande mall, låt oss till exempel lägga
ädelstenen i smyckeskrinet och lägga till en prislapp.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Du kan göra detta på följande sätt:

```
>> gem := tpl klipp: ['gem'], kopiera.
gem price: 99.
tpl klistra: gem vid: ['jewels'].
web skriv-ut: tpl putsa.
```

Den sista raden skickar helt enkelt mallen som en text till klienten
tillsammans med de nödvändiga HTTP-huvudena.

Resultat:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Vidarebefordring

För att servera filer som användare har laddat upp på ett säkert sätt kan du förlita dig på vidarebefordring (passthru):

```
>> uploaded := ['smile.gif'].
Server vidarebefordra: uploaded prefix: ['/uploads/images/'].
Program avsluta.
```

Detta serverar det uppladdade innehållet med lämplig
mimetyp. Endast vitlistade mimetyper stöds:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF och SVG.
SVG-, ZIP- och GZIP-filer skickas som nedladdning, eftersom en SVG
kan innehålla skript som annars skulle köras på din domän.
Denna metod förhindrar TOCTOU-attacker, sökvägstraversering,
körning av skadlig kod (injektion), symlänksattacker,
DDoS-attacker (filgräns = 50MB), avlyssningsattacker och
diverse andra säkerhetsproblem.


## JSON

För att koda ett objekt som JSON:

```
>> json := ( JSON jsonify: ( 
	Ordbok ny sätt: ( 
		Lista ny ; 1 ; 2 ; 3
	) vid: ['abc']
)).
```

För att avkoda JSON till ett xoscript-objekt:

```
>> dict := ((JSON objekt: json) abc ? 1).
```

JSON med mer än 500 nivåer av nästling avvisas som ogiltig.

För att direkt skriva ut en Ordbok som json med rätt huvuden:

```
web json: dict.
```


## Reguljära uttryck

Du kan använda reguljära uttryck genom att skapa ett mönster.
Till exempel för att matcha href-attribut och mål för hyperlänkar:

```
Mönster ny: ['href="([^"]+)" target="([^"]+)"'].
```

Tillämpa nu mönstret på den text som ska undersökas så här:

```
pattern matcha: ämne gör: { :m :x .... }
```

Fullständigt exempel:

```
>> ämne := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> pattern := Mönster ny: ['href="([^"]+)" target="([^"]+)"'].
>> result  := pattern matcha: ämne gör: { :m :x
	Utdata skriv: m, stop.
	Utdata skriv: x, stop.
	<- ['XXX'].
}.
Utdata skriv: result, stop.
```

## Nätverk

Använd objektet Nätverk för att utföra en webbförfrågan.
Objektet Nätverk skickar alltid en POST-förfrågan, såvida du inte skickar Inget som
data; då skickar det en GET-förfrågan.


```
Nätverk 
post: Inget 
till: ['https://redbeanphp.com'].
```

## Kryptering

Serverinsticksmodulen levereras med kryptering baserad på XChaCha20 och Argon2.

Exempel:

```
>> encrypted := Valv kryptera: ['hello'] nyckel: ['world'].
>> decrypted := Valv kryptera: encrypted nyckel: ['world'].
```

## Token

För att generera en kryptografiskt säker token med en viss längd:

```
>> mytok := Valv token: 40.
```

Detta genererar en token på 40 tecken.

## Formatering

Objektet Format låter dig formatera data, till exempel utfyllnad eller
att lägga till nollor. Det använder printf-syntaxen.

```
>> fmt := Format ny: ['%06.0f'].
fmt tillämpa: 56. # gives 000056
```

Ett format kan innehålla en konvertering, och den måste passa värdet,
annars får du ett fel:

- `tillämpa:` med en text: `%s`
- `tillämpa:` med ett tal: `%f`, `%e`, `%g` eller `%a`
- `tillämpa-heltal:` med ett tal: `%d`, `%i`, `%o`, `%u`, `%x` eller `%c`

Värden från en förfrågan är texter. För att formatera ett sådant som ett tal
måste du först omvandla det:

```
fmt tillämpa: (begäran get: ['amount']) tal.
```

## Kodare

Flera kodare och avkodare finns tillgängliga.
URL-kodaren förbereder en url för användning i HTML som en länk:

```
Server url-koda: ['https://example.com?a=6&b=1 2'].
```

För att säkert injicera användarindata i din HTML utan att riskera XSS-injektioner,
använd alltid:

```
Server html-koda: ['<harmless>'].
```

Observera att mallmotorn alltid utför HTML-kodning
när du skriver till en platsmarkör. Om du använder mallsystemet
behöver du alltså inte använda detta.

## E-post

För att skicka e-post, använd biblioteket mailtools.xo.

Exempel:

```
Server initiera.
Program använd: ['mailtools.xo'].

>> e-mail := HTML-E-post ny.
>> img := e-mail bifoga: ( Fil ny: ['myimage.png'] ).

e-mail
avsändare: ['xo@xoscript.com'] namn: ['xo'],
till: ( Lista ny ; ['xo2@xoscipt.com'] ),
ämne: ['xoxo'],
meddelandetext: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), skicka.

```



## Länkning

Med meddelandet länka: kan du länka ett externt bibliotek till
ditt program med hjälp av libffi. Mer information finns i kapitlet om ffi.


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

FFI tillhandahålls per plattform/insticksmodul eftersom det
är knutet till den underliggande systemarkitekturen, något som
kärnan inte ska göra.
Serverinsticksmodulen erbjuder en kompatibel ffi/blob-implementation.
Som standard ansluter kärnan till målplattformen
via stdin/stdout, begränsade fil-I/O-tjänster och skalet (Program system:).
Ytterligare integration tillhandahålls av ffi/blobbar via applikationsinriktade
insticksmoduler som serverinsticksmodulen.

FFI står för Foreign Function Interface. Det gör det möjligt att använda funktionalitet som andra har skrivit i
andra programmeringsspråk, tillhandahållen via DLL-filer, SO-filer eller Dylib-filer. Det kan
vara en mängd olika funktioner, och det finns ett enormt utbud av funktionalitet tillgänglig via denna metod.
Låt oss börja med ett exempel:

```
Server länka: (
 Lista ny ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Lista ny ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s frigör.
```

Resultatet av denna kod är att du ser följande på kommandoraden:
FFI has 3 letters.
Nu tänker du förmodligen: "Det var mycket kod för något så enkelt."
Kunde vi inte bara lösa detta med ett Gui show-kommando? Svaret är ett rungande ja!
Men detta är tänkt som ett illustrativt exempel.
FFI används vanligtvis för mer komplexa uppgifter, men sådana blir inga bra
exempel, så jag valde något trivialt.

Argumenten för metoden länka:

- Argument #1: DLL- eller SO-filen som du vill använda.
- Argument #2: Funktionen i den filen som du vill länka.
- Argument #3: En lista med namnen på datatyperna för funktionens argument.
- Argument #4: Namnet på funktionens returtyp.
- Argument #5: Namnet på det objekt som du vill länka denna funktion till (om det inte finns skapas det
automatiskt).
- Argument #6: Det meddelande som denna funktion ska länkas till.

I exemplet ovan vill vi länka funktionen printf från libc.so. Du hittar
namnen på datatyperna i dokumentationen för den programvara du länkar till. De tillgängliga typerna är:
void, pointer, float, double, int, uint, char, uchar, intX och uintX,
där X kan vara 8, 16, 32 eller 64.

Dessa typer avser det antal byte som krävs för att lagra data. För printf länkar vi till ett
nytt objekt som heter Printf och meddelandet template:number:. Du översätter den externa
funktionen till XOScript-dialekten innan du använder den. Meddelandet template:number: förväntar sig
en buffert med malltexten som första parameter. Vi skapar denna buffert med ett Blob-objekt, som
låter dig allokera minne manuellt. Du ansvarar själv för att frigöra detta minne efteråt
med meddelandet frigör.

Du kan fylla en minnesblob på olika sätt. I vårt exempel fyller vi den med text, så vi använder
meddelandet utf8: (UTF-8 är en kodning för att omvandla text till byte). Du kan också fylla en blob med
bytes: genom att skicka en lista med bytevärden. För att läsa innehållet i en blob, använd från:längd:.
Du får tillbaka byten som en lista. Du kan till och med skapa en C-struct med en Blob med hjälp av
meddelandet struct:, där du skickar en sekvens av C-typer. Detta kan vara nödvändigt när du anropar en C-funktion
i ett externt programbibliotek som förväntar sig en pekare till en struct.

{warning}
Du måste frigöra blobbar själv.
Blobbar rensas inte av skräpsamlaren.
{/warning}

Eftersom blobbar kan utbytas med externa funktioner från bibliotek
kan de inte skräpsamlas automatiskt (de kan fortfarande användas av
externa funktioner, eller så kanske dessa externa funktioner vill frigöra dem
själva). Därför måste du frigöra blobbar själv vid behov.

För att frigöra en blob, använd:

```
myblob frigör.
```

För att frigöra en struct, använd:

```
mystruct frigör-struct frigör.
```

För en struct måste du alltså skicka två meddelanden: frigör-struct och frigör för att
avallokera minnesblocket.

@api_Blob_fficonnect
