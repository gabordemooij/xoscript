# Basis

{{messages}}


Wolkom by XOScript
It XOScript-projekt hat as doel in skripttaal te meitsjen dy't ienfâldich en kontrolearber is.
Ienfâldich betsjut net needsaaklik maklik.
In bekende programmeartaal kin makliker yn it gebrûk wêze as XOScript.
Hjir betsjut ienfâld wat oars:
in folslein mentaal model fan de taal en har gedrach foarmje kinne.

XOScript is sa ûntwurpen dat it yn jo holle past.
De grammatika en it tal begripen binne bewust lyts hâlden.
Der binne gjin klassen; objekten kinne streekrjocht útwreide wurde.
Objekten wurde trochjûn as referinsje, kopiearjen bart eksplisyt,
en funksjes hawwe mar ien útgongspunt.

Guon fan dizze karren wike flink ôf fan gongbere talen.
XOScript hat bygelyks gjin typesysteem en brûkt dynamyske scoping.
Berjochten dy't net ôfhannele wurde kinne, wurde negearre ynstee fan in útsûndering op te smiten.
Dizze karren hawwe gefolgen en binne net bedoeld om flaters út te bannen.
Se binne bedoeld om it ûnderlizzende model fan de taal lyts en konsekwint te hâlden.

XOScript kin ek lokalisearre wurde, sadat it mooglik is om bedriuws-
regels yn in natuerlike taal út te drukken en se mooglik te dielen mei net-technyske belanghawwenden.

Kontrolearberens betsjut dat deselde filosofy tapast wurdt op de ymplemintaasje.
De runtime is skreaun yn C, mei in lytse, mei de hân skreaune lexer, parser en tree walker.
De standertbibleteek en de runtime folgje foar it grutste part de struktuer fan de taal,
wêrtroch't de relaasje tusken XOScript-koade en de ymplemintaasje dêrfan frij direkt is.

Tests binne ek nau ferbûn mei de dokumintaasje.
Eltse metoade hoecht in byhearrende test te hawwen dy't yn de hantlieding opnommen wurde kin,
wat helpt om de dokumintaasje yn oerienstimming te hâlden mei de ymplemintaasje.

XOScript is net bedoeld om mei gongbere talen te konkurrearjen op
funksjes of bekendheid. It ûndersiket in oar doel:
in programmearomjouwing dy't in ûntwikkelder as gehiel begripe kin.

De hope is dat in lytse taal en in lytse
ymplemintaasje it praktysk mooglik meitsje om software te begripen
fan byte oant objekt, fan syntaksis oant runtime, en om koade te skriuwen mei
fertrouwen, om't jo sawol begripe wat der bart yn
it skript as wat der ûnder de motorkap bart.

De arsjitektuer fan in xoscript-serveropset
is ienfâldich, mar dochs fleksibel.

{{architecture.png}}

Om xoscript as servertaal te brûken, moatte jo de
serverplugin ynstallearje yn in map mei de namme /mods/server. 

Dat komt om't wy de
kearntaal graach los hâlde fan serverspesifike funksjonaliteit,
oars as bygelyks PHP of Python. Oars soene wy de
hiele rommelkeamer sûnder doel oan elkenien leverje moatte, en dat is gewoan dwaas.
Jo kinne ek oare modules ynstallearje as jo dat wolle. It systeem is tige
fleksibel.

Dêrneist kinne guon funksjes better yn de skripttaal
sels ymplemintearre wurde, lykas sjabloanen en sesjebehear, dus leverje wy
ek de bibleteken template.xo en webtools.xo foar jo gemak.
De reden foar dit alles is dat wy net witte hoe't jo
xoscript brûke wolle. Jo kinne it brûke as skripttaal oan de serverkant,
mar ek foar GUI's, ynbêde apparaten of gewoan batchferwurking.
Sels as jo it as skripttaal oan de serverkant brûke (wat
op it stuit ien fan de wichtichste tapassingen is), wolle jo miskien dochs
in oare sjabloanmotor of in oare sesjebehearder brûke.
Wa binne wy om te besluten dat jo uzes brûke moatte?

Ien fan de foardielen fan ús eigen sjabloanmotor is lykwols dat
jo gjin ekstra syntaksis leare hoege om sjabloanen te meitsjen.
De standert sjabloanmotor dy't mei xoscript meikomt, brûkt 100%
skieding tusken presintaasje en logika. Ynstee fan spesjale
sjabloansyntaksis brûkt er gewoan in tige fleksibel systeem fan slotmarkearrings.
Sjoch foar mear ynformaasje it haadstik Server.

Tink derom dat jo, as jo de standert sjabloanmotor of
de standert webtools net brûke wolle, fansels
sels wat oars leverje moatte.

As jo jo webserver yn in chroot, jail of in oare soarte sânbak draaie,
moatte jo de ôfhinklikheden fan xo ek yn dy omjouwing ynstallearje. Jo kinne
sjen hokker bibleteken jo nedich hawwe mei ldd (sjoch de manpage fan Linux of BSD).
As jo shellopdrachten yn jo xo-skripts brûke wolle, kopiearje dan ek in shell
(lykas bash of ksh) nei dizze omjouwing.

Wy wolle ek opmerke dat wy efterút kompatibiliteit tige serieus nimme.
Der is sels in spesjale funksje foar efterút kompatibiliteit mei de namme
'version'. Yn it algemien stribje wy dernei dat jo koade foar altyd draait. Jo sille
jo koade dus nea bywurkje hoege om kompatibel te bliuwen mei nijere ferzjes
fan xoscript. Us doel is: ien kear skriuwe, foar altyd draaie.

De rest fan dizze hantlieding is wijd oan it yn detail útlizzen fan de programmear-
taal xoscript. Serverskripting wurdt behannele yn it haadstik
mei de namme Server. As jo in betûfte softwareûntwikkelder binne, wolle jo
miskien in pear haadstikken oerslaan, om't guon dêrfan wat te detaillearre binne of
tige op algemiene programmearpraktiken lykje. Foar dyjingen fan jimme
dy't al ûnderfining hawwe mei ferskate oare programmeartalen,
is it dus better om dizze hantlieding as referinsjegids te brûken.

## Ynstallaasje op Linux

Download apache2 en mariadb:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Download xoscript.
Ferfang X troch it krekte ferzjenûmer!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Kopiearje de bestannen nei de webroot en /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Bewurkje jo apache2-konfiguraasje:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Ferfang Virtualhost troch:

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

Meitsje in testside:

```
sudo nano /var/www/html/test.xo
```

en skriuw in lyts testprogramma:

```
#!/bin/xo
Server inisjalisearje.
Programma brûke: ['webtools.xo'].
>> web := Webdokumint nĳ.
web útfiere: ['Hello World'].
```

Stean apache2 ta om jo programma fia CGI út te fieren:

```
sudo chmod uog+x /var/www/html/test.xo
```

Start apache2 opnij:

```
sudo systemctl restart apache2
```

Gean yn de browser nei jo testside:

```
http://localhost/test.xo
```

Jo soene dit sjen moatte:

```
Hello World
```


## Ynstallaasje op OpenBSD

Bewurkje /etc/httpd.conf en foegje ta:


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

As jo SSL brûke wolle:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Om de kaaiútwikseling te beskermjen tsjin kwantumkompjûters,
kies de mlkem-sifer:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Foegje de xo-binary en de mods, en ek alle ôfhinklikheden, ta oan de
chroot (fyn se út mei ldd).

## Foarbylden útfiere


Om ien fan de foarbyldprogramma's yn it pakket út te fieren:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Bygelyks, om it FizzBuzz-foarbyld op Linux út te fieren:

```
./example.sh fizzbuzz Linux
```

Om itselde foarbyld op OpenBSD út te fieren:

```
./example.sh fizzbuzz OBSD
```

Om it foarbyld mei in skjinne build út te fieren:

```
./example.sh fizzbuzz OBSD clean
```

## Unittests

Om de unittests út te fieren:

```
./runtests.sh
```

Om de unittests út te fieren sûnder te bouwen (allinnich testen):

```
./runtests.sh nobuild
```

## Bouwe

Om fan boarnekoade ôf te bouwen op Linux:

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

## Hallo wrâld

Nei't it bestân nei jo kompjûter oerbrocht is, kinne jo it útpakke
en xo starte mei de folgjende opdracht:

```
xo
```

Om in XOScript út te fieren, bewarje jo it programma as bestân mei it efterheaksel
-xo (opsjoneel). Set dêrnei de bestânsnamme fan jo programma
efter de XOScript-opdracht:

```
xo myprogram.xo
```

As jo in XOScript-opdracht útfiere mei jo programmabestân as
parameter, sil xo jo programmabestân lêze en útfiere.

{{note}}
Jo kinne jo programma ek starte troch it nei it xo-ikoan te slepen.
{{/note}}

{{warning}}
Op guon systemen moatte jo xo foarôf tastimming jaan om dynamyske
bibleteken te laden.
{{/warning}}

De tradysje skriuwt foar dat it earste programma yn elke nije programmear-
taal in soarte fan groet oan de wrâld wêze moat. Yn XOScript sjocht sa'n
**Hallo wrâld**-programma der sa út:

@test598

As dizze tekst yn in bestân bewarre wurdt, bygelyks hello.xo, kin it as
folget útfierd wurde: .

xo hello.xo

Hello world


Jo sjogge de útfier fan it programma yn it swarte finster hjirboppe.
Yn dizze hiele hantlieding wurdt deselde wize fan werjaan brûkt om de
útfier te toanen.

{{note}}
Utfier wurdt skreaun mei in haadletter U.
Yn it algemien begjinne objekten mei in haadletter,
útsein as it as eksimplaar fungearret (it hat gjin eigen
metoaden, allinnich gegevens). Dit wjerspegelet de konvinsjes fan klasse
tsjinoer eksimplaar yn oare programmeartalen.
{{/note}}


## Syntaksis 

XOScript is in *suver* *objekt-oriïntearre* programmeartaal. Dat betsjut
dat xoscript alles as in objekt sjocht, en dêrom binne der
gjin oare *gegevenstypen*. Der binne yn wêzen trije basishannelingen
yn in programma dat yn XOScript skreaun is: *tawize*, *berjochten stjoere*
en *antwurdzje*. It útwikseljen fan berjochten tusken objekten is de kearn fan
in XOScript-programma. De trije aparte basishannelingen wurde hjirûnder
yllustrearre:


Hanneling       | Foarbyld
--------------- | --------
tawize          |  \>\> x := 1. 
unêre berjochten | x even?.
binêr berjocht  | 1 + 2.
kaaiwurdberjocht | x fan: 0 lingte: 10.
antwurd         | <- antwurd.  


Dit haadstik jout jo in algemien byld fan de taal XOScript
en beskriuwt de basisprinsipes dêrfan. XOScript is in lytse taal en
basearre op trije hannelingen (sjoch yllustraasje) dy't oerienkomme mei
likernôch seis grammatikaregels. Mear is der net nedich om de
taal te behearskjen.

Gjin soargen as dingen jo net fuortendaliks dúdlik binne: alle bou-
stiennen wurde yn it folgjende haadstik (3) ferkend en de basisregels wurde
werhelle. Dit haadstik tsjinnet lykwols foaral as in algemiene
ynlieding yn de taal. De basisprinsipes wurde koart
útlein en yllustrearre mei ferskate relevante foarbylden. Untbrekkende
details wurde letter útwurke.

Kommentaar yn XOScript begjint mei in \#-teken. De folgjende rigel
wurdt dus negearre:

```
# this is just a comment
```

## Fariabelen

Om in fariabele
ta te wizen, brûke jo it symboal foar de fariabeledeklaraasje: >>. De namme fan in
fariabele mei alle tekens befetsje, útsein: <-, :=, wytromte,
punten, komma's, dûbele punten, oanhellingstekens [' '] en heakjes ().
Fierder kin in fariabele net út meardere rigels bestean. Tink derom
dat in fariabele net begjinne kin mei in sifer of in minteken.

Dit binne foarbylden fan jildige fariabelen:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dollar'].
>> +plus := Ja.
>> user-password := ['Pssst!'].
```

Unjildige fariabelen binne bygelyks:


```
>> -123 := ['negative number'].
>> password of user := ['Classified'].
>> password.of:user := ['Classified'].
>> ,x := 10.
```

{{note}}
Jo hoege gjin inkeld teken te escapen
(ynklusyf oanhellingstekens, dûbele oanhellingstekens, tekst-
grinzen) yn
in tekstliteral, salang't it gjin
dûbelsinnigens foar de lexer feroarsaket.
{{/note}}

Nei't in fariabele deklarearre is, kin dy frij brûkt wurde. Dat betsjut
dat it allinnich nedich is om it deklaraasjesymboal te brûken de earste kear dat
jo de fariabele brûke (de deklaraasje).

Om krekter te wêzen: jo kinne net samar begjinne mei it tawizen fan in wearde oan
jo fariabele *(x := 2)*, want jo moatte de fariabele earst deklarearje *(\>\>
x := 2)*. Mar as er ienris deklarearre is, meie jo de wearde feroarje
sûnder it deklaraasjesymboal te brûken *(\>\> x := 2. x := 3.)*.

Tink derom dat it ferplichte is om in wearde oan in fariabele ta te wizen op it momint fan
deklarearjen. Oars as yn oare programmeartalen meie jo
gjin fariabele sûnder wearde deklarearje. It is essinsjeel om
elke fariabele eksplisyt oan in begjinwearde te keppeljen. Jo kinne
de fariabele lykwols gerêst inisjalisearje mei it objekt **Neat**. Yn dat gefal kin de fariabele
beskôge wurde as leech *(\>\> x := Neat.)*. Koartsein, it is net tastien om in
fariabele sûnder begjinwearde te deklarearjen. Dus,

```
>> x.
```

is ûnjildich en sil in flatermelding jaan.

{{note}}
xoscript brûkt dynamyske scoping fan fariabelen, sjoch
foar details it haadstik Funksjes.
{{/note}}


## Literals

XOScript sjocht alles as in objekt, dat wol sizze alle getallen, teksten
en koadefragminten. Getallen, lykas 1, 2, 100, -999 en 1,234, binne
Getal-objekten. Alle teksten tusken inkele oanhellingstekens binne Tekst-
objekten. Alle koadefragminten dy't tusken kromme heakjes {...} groepearre binne, binne
Funksje-objekten.

Literal         | Woartelobjekt | Foarbyld
--------------- | ------------ | ----------
getallen        | Getal        | 1,2,3... 
teksten         | Tekst        | \['hallo'\]
funksje         | Funksje      | { 1 + 2. }.
                
     
Objekten lykas getallen en teksten hawwe altyd harren oarsprong yn in woartel-
objekt. Alle getallen stamme bygelyks ôf fan it objekt **Getal**. Alle
teksten stamme ôf fan **Tekst** en alle koadefragminten fan **Funksje**. Op
har beurt stamme al dizze objekten ôf fan **Objekt**, dat feitlik it
woartelobjekt fan alle objekten is.


## Berjochten

Programmearje yn XOScript betsjut yn wêzen
berjochten stjoere nei objekten. De algemiene notaasje om in berjocht nei
in objekt te stjoeren is as folget:

```
<object> <message>
```

Om út te finen oft it getal **2** bygelyks in even getal is, wurdt it
berjocht **even?** stjoerd nei objekt **2**:

```
2 even?
```

It antwurd sil **Ja** wêze (wer in objekt). Unbekende berjochten wurde
meastentiids troch objekten negearre; der ûntstiet dus gjin flater. Guon objekten (bygelyks
getallen of teksten) reagearje op in foarôf fêststelde wize op in ûnbekend berjocht
(hjir letter mear oer).

In objekt kin trije soarten berjochten ûntfange. 

Soarte           | Tal arguminten
--------------- | -------------------
Unêr            | 0      
Binêr           | 1     
Kaaiwurd        | 1+    


Earst binne der **unêre
berjochten**, sjoch it foarbyld hjirboppe, dy't gjin arguminten hawwe. Twad
binne der **kaaiwurdberjochten**, dy't ien of mear arguminten hawwe,
bygelyks:

```
>> x := Getal tusken: 1 en: 10.
```

Yn dit gefal wurdt it berjocht **tusken:en:** stjoerd nei **Getal**, dat
it woartelobjekt fan alle getallen is. It resultaat sil in willekeurich getal
tusken 1 en 10 wêze. Ta beslút binne der **binêre berjochten**, dy't
mar ien teken en ien argumint hawwe:

```
2 + 3
```

Dit liket op in wiskundige som, mar it is eins gewoan in oar berjocht. It
berjocht **+** wurdt stjoerd nei **2**, mei argumint **3**, wat it
antwurd **5** jout. Binêre berjochten meie sûnder dûbele punt skreaun wurde.

Binêre berjochten kinne oan inoar keppele wurde:

```
>> x := 3 + 2 - 1.
```

Yn dit fragmint wurdt **+ 2** earst stjoerd nei **Getal**-objekt **3**, wat
resultearret yn Getal-objekt **5**, wêrnei't **-1** nei dit
getal stjoerd wurdt. Opmerksume lêzers fernimme mei rjocht it ferskil dat
dit protokol sjen lit mei de gewoane wiskundige folchoarder fan
operatoaren. XOScript negearret de wiskundige folchoarder yn it foardiel fan
konsistinsje yn syn berjochtesysteem. As gefolch dêrfan jout de som:

```
2 + 3 * 5 = 25
```

net 17.

Dat is sa bedoeld. Heakjes kinne brûkt wurde om de folchoarder te feroarjen:

```
2 + (3 * 5) = 17
```

De measte objekten jouwe harsels werom as resultaat op in bepaald
berjocht. Dat is handich, om't it in fierdere dialooch mei dit
objekt stimulearret troch it in folgjend berjocht te stjoeren:

```
Utfier skriuwe:
[' hello '] ynkoartsje haadletters.
```

```
HELLO
```

Hjir wurde twa berjochten stjoerd nei it **Tekst**-objekt: **ynkoartsje**, folge
troch **haadletters**.

Yn it folgjende fragmint is it gebrûk fan in komma nedich om oan te jaan
dat der in nij berjocht oankomt. Oars rekket XOScript yn de war.

```
Utfier skriuwe: ['Hello!'], nije-rigel.
```

Earst wurdt it berjocht **skriuwe:** stjoerd nei it potleadsymboal, folge troch
**nije-rigel**. Sûnder de komma soe XOScript tinke dat jo
**nije-rigel** nei **tekst** **Hello!** stjoere wolle, in nutteleaze oefening.

De ferwurkingsfolchoarder fan berjochten is as folget: fan lofts nei rjochts;
begjin mei berjochten tusken heakjes, folge troch unêre berjochten. Dêrnei
binêre berjochten en einigje mei kaaiwurdberjochten. Sjoch it foarbyld
hjirûnder:

```
Utfier skriuwe: 0.5 ôfrûne + (2 - 1), nije-rigel.
```

XOScript lêst altyd fan lofts nei rjochts: earst wurdt it berjocht **skriuwe:**
stjoerd nei Utfier en folge troch it berjocht **nije-rigel**. Binnen it
argumint sels lêst XOScript fan lofts nei rjochts, dus earst **0.5 ôfrûne**
en dan **+**.

{{note}}
It berjocht nije-rigel foeget in nijeregelteken ta oan de tekst.
De namme fan dit berjocht (yn it Ingelsk stop) is ynspirearre op telegraafsystemen.
Berjochten yn telegraafsystemen 
brûkten faak it wurd STOP om it ein fan in sin oan te jaan
(om't ynterpunksje ûnbetrouber of djoer wie).
{{/note}}

Boppedat hat **ôfrûne** foarrang boppe **+**, om't it in
**unêr berjocht** is. Fanwegen de heakjes wurdt **2 - 1** earst
berekkene, wêrnei't **1** optelt wurdt by it resultaat fan **0.5 ôfrûne** (1).

It hiele proses jout it resultaat **2**, dat ek it skreaune
antwurd is. Nei de komma folget it berjocht nije-rigel, dat de rinnerke
nei in nije rigel ferpleatst. Fansels is oefenjen de bêste manier om de
folchoarder fan XOScript-programma's folslein te begripen.

It is it fermelden wurdich dat yn XOScript, oars as yn in protte oare programmear-
talen, wytromte in fûnemintele part fan de syntaksis is. Benammen
by binêre berjochten kin wytromte wat
betizing feroarsaakje. Brûk altyd in spaasje nei in binêr berjocht. Jo kinne
in getal net streekrjocht oan it berjocht fêstmeitsje, bygelyks: 

```
3 + 2
```

is oars as 

```
3 +2
```

It earste foarbyld (**3 + 2**) stjoert it
berjocht **+** nei it getal **3**, mei as argumint it getal **2**. It
resultaat sil yn dit gefal **5** wêze. Yn it twadde foarbyld (**3 +2**)
wurdt it unêre berjocht **+2** nei getal **3** stjoerd. Ofhinklik fan de
kontekst kin dat in hiel oar resultaat jaan.

## Net-besteande metoaden

It stjoeren fan in berjocht nei in objekt ropt de funksje oan dy't
ûnder dy berjochtnamme oan dit objekt keppele is. As jo in berjocht stjoere
dat net begrepen wurdt, sil it ûntfangende objekt jo berjocht negearje
en ynstee dêrfan in referinsje nei himsels weromjaan foar fierdere kommunikaasje.
Dit hjit tolerante berjochtoerdracht.

Foarbyld:

```
Utfier skriuwe: Objekt blah, nije-rigel.
```

Dit jout gjin flater. It printet gewoan de tekst **Objekt**.


## Kontrôlestream

Yn XOScript binne gjin aparte grammatikaregels nedich foar *lussen* en
*ifs*. In if-statement is gewoan in ienfâldich berjocht **ja:** of **nee:**
nei in **Ja**-objekt of in **Nee**-objekt:

```
2 even? ja: {
	Utfier skriuwe: ['Two is an even number'], nije-rigel.
}.
```
Yn it foarige foarbyld wurdt it berjocht **ja:** stjoerd nei **Ja** (it
antwurd op de fraach: is 2 in even getal?). As argumint wurdt der in ekstra
koadefragmint meistjoerd: in **Funksje**-objekt. Dizze funksje skriuwt op
it skerm dat 2 yndied in even getal is.

Der binne ek gjin aparte skriuwregels nedich foar in *lus*. Om
in koadefragmint trije kear út te fieren, stjoer gewoan **\*** mei argumint
**3** nei dy **Funksje**:

@test5

Yn dit koadefragmint is **i** de yndeks. De earste kear dat de Funksje
útfierd wurdt, is **i** dus gelyk oan 0, de folgjende kear dat er útfierd wurdt, is **i** = 1, en
sa fierder.

Litte wy noch in foarbyld besjen. As der in omrekkentabel
printe wurde moat fan *kJ* (kilojoule) nei *kcal* (kilokaloary) yn stappen fan 100,
sjoch dan hjirûnder foar de krekte notaasje:

@test599

Hjir wurdt it nûmer fan de hjoeddeiske rigel trochjûn oan de parameter
**:line**. Oan it begjin fan in funksje wurde de funksjeparameters
definiearre. Net-brûkte parameters bliuwe leech (**Neat**). Parameters wurde
altyd oan it begjin fan de funksje set, direkt nei it earste
krome heakje, en wurde foarôfgien troch in dûbele punt.

It berjocht **wylst:** is in kombinaasje fan in *lus* en in *betingst*.
Twa funksjes kinne mei it berjocht **wylst:** oan inoar keppele wurde. De ûntfangende funksje
bliuwt draaien oant de funksje nei de dûbele punt in negatyf
resultaat jout. Foarbyld:

@test600

Yn it koadefragmint hjirboppe wurdt **1** by **x** optelt salang't
**x** lytser is as **5**. As dat net mear it gefal is, sil de twadde
funksje antwurdzje mei **Nee**, en dêrtroch einiget de útfiering fan de
earste funksje. Tink derom dat **x** bûten de
funksje definiearre is en in globale fariabele is. Lês it haadstik oer Funksjes
om mear te learen oer scopingregels.

## Tekstynterpolaasje

De *kJ/kcal*-list koe wat
presintabeler makke wurde. By foarkar soe de list der sa útsjen:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

As jo de winske útfier omsette yn in sjabloan, soe de notaasje
sa wêze kinne:

```
number1 kJ ➞ number2 kcal
```

Dat betsjut dat **number1** stiet foar de kJ-wearde en **number2** foar de
kcal-wearde. Sa wurket tekstynterpolaasje yn XOScript. Der binne
hjirfoar gjin aparte grammatikaregels nedich yn XOScript. Stjoer gewoan
it wurd dat ferfongen wurde moat nei de tekst, mei de ferfangende tekst
as argumint:

```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

It resultaat:

```
100 kj ➞ 23.9 kcal
```

Dizze ferfangingsregel wurket foar elk net-definiearre berjocht dat
in **tekst**-objekt ûntfangt. Elk berjocht dat net werkend wurdt troch it
**tekst**-objekt, wurdt as folget ynterpretearre: *ferfang de berjochttekst
troch de tekst yn it argumint fan it berjocht.* Jo kinne it
programma as folget oanpasse:


@test601


Om betizing foar te kommen oer hokker berjochten wol of net as
ferfanging brûkt wurde kinne, is it it bêste om in sjabloanmarkearring lykas &lt; &gt;
yn te fieren foar tekstdielen yn it sjabloan dy't
ferfongen wurde moatte.

## Weromjouwearden

Om in berjocht te beantwurdzjen wurdt de weromjoupylk
(*<-*) brûkt. It folgjende foarbyld lit sjen hoe't jo in taak meitsje
om in persintaazje te berekkenjen:

@test602

Nei't de taak definiearre en oan fariabele **percentage** tawiisd is,
wurdt it berjocht **tapasse:en:** stjoerd mei de arguminten **100** en **7**.

Dit fiert de taak út tapast op **100** en **7**, dat wol sizze 7% fan 100.
Mei de weromjoupylk wurdt it antwurd fan de taak werom
nei it haadprogramma jûn.

## Utwreidzje

Hoewol't dizze koade jildich is, hat se in neidiel,
om't de folchoarder fan de arguminten ûnthâlden wurde moat. Dus, wêrom
soene wy it net sa skriuwe: *7 percent of: 100 *? Dat soe folle
*natuerliker* lykje. Om dit mooglik te meitsjen, moatte wy it âlderobjekt fan
**7** oanpasse, dat is it **Getal**-objekt, sadat it it
berjocht **percent of:** begrypt. Dat kin berikt wurde troch **by:dwaan:** te stjoeren nei
it Getal-objekt, sa:

@test603

Om't it persintaazje yn dit gefal it getal sels is, ferwize wy nei sels,
it kaaiwurd *sels*. Koartsein betsjut it symboal sels: *stjoer dit
berjocht nei mysels*.

# Objekten

{{messages}}

Njonken it oanpassen en útwreidzjen fan besteande objekten kinne jo ek
sels nije objekten meitsje, gewoan troch it berjocht **nĳ** te stjoeren. Stel dat jo
in faktuerobjekt meitsje wolle dat in nûmeringsfolchoarder
ôftwingt; yn dat gefal hawwe jo earst in faktuerobjekt nedich.

Om't elk objekt ôfstamt fan in oar objekt, dat op syn beurt
úteinlik ôfstamt fan it woartelobjekt fan alle objekten, Objekt neamd,
moat der in kar makke wurde op hokker fan dy oare objekten jo
nije objekt basearre wurde sil. Jo nije objekt erft alle eigenskippen fan
it objekt dêr't it op basearre is, dus it objekt dêr't it berjocht **nĳ**
oarspronklik nei stjoerd waard.

Yn dit foarbyld hat in frij neutraal objekt de foarkar, ien sûnder al te
folle erfde eigenskippen. Dat makket de kar maklik, want yn dat
gefal kin it nije objekt basearre wurde op it woartelobjekt sels, dat is
**Objekt**. De notaasje fan it bedoelde faktuersysteem is dan as
folget:

@test604

It hjoeddeiske faktuernûmer wurdt yn it objekt bewarre; dêrom stiet der
in kaaiwurd **eigen** foar. Dit hjit in *eigenskip*;
mear details folgje.

Guon bedriuwen wolle it jier graach yn de faktuernûmers
opnimme. Yn dat gefal kinne jo in nij faktuerobjekt meitsje dat basearre is op in
earder faktuerobjekt, mar dat de brûker de mooglikheid biedt om
in bepaald jier yn te fieren:

@test605

It is net nedich om de ymplemintaasje foar it berjocht **getal**
opnij te skriuwen, om't dy erfd wurdt fan it earder skreaune **faktuer-
objekt**; sadwaande kin âlde koade opnij brûkt wurde. XOScript hat gjin begripen
lykas klassen en oare dêrmei besibbe begripen. Dat betsjut dat objekten
allinnich fan oare objekten erve kinne, ek wol *prototypyske
erfskip* neamd.

No werom nei eigenskippen. Eigenskippen fan objekten binne allinnich berikber
fan *binnen de objekthiërargy* út, dus dizze eigenskippen
kinne net troch oare objekten waarnommen wurde.

Oars as yn oare programmeartalen binne alle eigenskippen fan objekten
allinnich sichtber foar it objekt dat de eigenskip makke hat en foar
ôfliede objekten. 

In faak brûkte technyk is om in objekt te brûken as in soarte fan *bouplan*,
lykas bygelyks it gefal is mei de earder besprutsen faktueren.
In oar goed foarbyld is it **Point**. Stel dat jo in
kompjûterprogramma meitsje dat berekkeningen docht mei punten op in kaart. Jo
kinne it objekt **Point** ûntwikkelje mei de eigenskippen fan in
x-koördinaat en in y-koördinaat, dy't fia berjochten beskikber steld wurde oan de
bûtenwrâld:

@test606

It berjocht **=** fergeliket de twa punten mei it berjocht **en:**. De
earste fergeliking resultearret yn in **Ja** of in **Nee**. Dat binne booleaanske
objekten. As jo it berjocht **en:** nei in Ja-objekt stjoere, en it
argumintobjekt nei de dûbele punt is likegoed **Ja**, dan krije jo
as antwurd wer **Ja**. As ien fan beide **Nee** is, krije jo
it antwurd **Nee**. Tink derom dat it iene punt de koördinaten fan it
oare net lêze kin. It is nedich om in berjocht nei it oare punt te stjoeren om
dizze gegevens op te freegjen: **x-coordinate** en **y-coordinate**. Want, sa't
al útlein is, eigenskippen binne allinnich op te heljen fan binnen
de objektfamylje sels út. 

Tink derom dat it berjocht **=** hjir brûkt wurdt om de puntfergeliking
út te fieren. Likegoed hie der in oar berjocht brûkt wurde kinnen, lykas
**is:** of **equal:**, mar it opnij brûken fan it teken **=** like
yn dit gefal passend.

## Erfskip

Jo kinne earder skreaune koade opnij brûke om in hiërargy
fan objekten te meitsjen. Bygelyks:

```
>> Animal := Objekt nĳ.
>> Dog := Animal nĳ.
>> Poodle := Dog nĳ.
```

Yn dit gefal erft **Dog** al it gedrach en alle eigenskippen
fan **Animal**, en op syn beurt erft it objekt **Animal** al it gedrach fan
**Objekt**, it woartelobjekt fan alle objekten.


## Oerskriuwe


Yn it folgjende foarbyld wurdt in nije soarte list makke:
**Combination**, dêr't elk elemint gegarandearre unyk yn is. De
funksjes fan de list wurde fia erfskip opnij brûkt:

@test607

Sjoch hoe't de twadde **red** útsletten wurdt fan de list.

Sa no en dan kin it nedich wêze om in gedrach fan in objekt oer te skriuwen.
Bygelyks as by it optellen fan getallen rekken hâlden wurde moat mei mjit-
ienheden. Yn it folgjende foarbyld wurdt it objekt **Size**
makke. Dit objekt jout in getal werom dat by it optellen
rekken hâldt mei de ienheid fan it op te tellen getal. It **Getal**-objekt
kontrolearret oft it om *inches* of *foot* giet. De programmakoade
koe der sa útsjen:

@test608

## Rekursje

Yn it foarige foarbyld wurdt it plus**teken** oerskreaun. Tink derom
dat de lêste optelling úteinlik dochs noch dien wurde moat, wat feitlik
op de folgjende rigel bart:

```
>> answer := sels + (getal x factor).
```

No, hoe begrypt XOScript dat dit plus**teken** ferwiist nei
de oarspronklike logika fan it optellen?** In oare ynterpretaasje
koe bygelyks wêze dat XOScript hieltyd wer itselde berjocht nei itselde
objekt stjoert, wat op syn beurt resultearje soe yn in **ivige lus**. Dat is
fansels net de bedoeling. Sadree't jo in berjocht nei in objekt stjoere
dat krekt deselde koade útfiere soe, begrypt XOScript
yn dit gefal dat it ûnderlizzende, oerskreaune berjocht bedoeld wurdt. Jo
programma wurdt sadwaande automatysk beskerme tsjin dizze foarm fan ivige
lussen. As it lykwols wier jo doel is om deselde funksje út de
hjoeddeiske funksje wei út te fieren, dan is it nedich om earst it berjocht
**rekursyf** te stjoeren. Yn dit gefal sil it resultaat in ûneinige
lus wêze. Der binne lykwols nuttige tapassingen foar rekursive taken,
bygelyks as jo de fakulteit fan in jûn
getal berekkenje wolle. Foegje yn dat gefal gewoan it berjocht **factorial** ta oan
Getal:

@test609

Dit freget om rekursje. De taak dy't oan it
berjocht **factorial** keppele is, moat feitlik binnen dy funksje opnij útfierd wurde.
It is dus nedich om de fakulteitsfunksje oan te roppen fan binnen de
fakulteitsfunksje sels. As regel foarkomt XOScript dizze routine,
fanwegen it risiko om yn in ûneinige lus te bedarjen. Om dy reden
is it essinsjeel om it berjocht foarôf te litten gean troch it wurd **rekursyf**. Dat
wurdt dien om XOScript bewust te meitsjen fan it feit dat it jo
bedoeling is om deselde taak út te fieren, en dat jo gjin flater makke hawwe.

## Klasse-eftige objekten

Hoewol't xoscript gjin klassen biedt, is it neidwaan fan klasse-eftich
gedrach triviaal. Skriuw gewoan it berjocht nĳ oer.

```
>> Animal := Objekt nĳ.
Animal by: ['nĳ'] dwaan: {
	<- sels nĳ inisjalisearje.
}.

Animal by: ['inisjalisearje'] dwaan: {
	eigen sound := ['?'].
	eigen legs  := 4.
}.
```

Yn it koadefragmint hjirboppe meitsje wy in objekt mei de namme Animal.
Dit objekt tsjinnet as *bouplan* foar alle soarten bisten,
lykas hûnen en katten. It âlderobjekt Animal wurdt skreaun
mei in haadletter A om oan te jaan dat dit in klasse-eftich objekt is.
Dêrnei skriuwe wy it berjocht nĳ oer troch ús eigen nĳ-metoade te skriuwen.
Yn dit gefal stjoert dy in berjocht nĳ nei sels, folge troch it berjocht
inisjalisearje. Om't xoscript rekursje standert blokkearret, feroarsaket dit
gjin ûneinige lus. Ynstee dêrfan stjoert it it berjocht nĳ nei it âlder-
objekt (Objekt), wat in nij eksimplaar fan Animal oplevert. Wy meitsje dus
in nij objekt, basearre op itselde objekt dêr't wy ús nĳ-metoade foar makke hawwe.
Dat is folslein jildich. No stjoere wy ek it berjocht inisjalisearje; dat soarget derfoar
dat it Animal-objekt standertwearden foar syn eigenskippen hat. Standert
hat in bist 4 poaten en is it lûd ûnbekend (dêrom it fraachteken).
Om in nij eksimplaar fan ús Animal te meitsjen, kinne wy gewoan sizze:

```
>> a := Animal nĳ.
```

No krije wy in nij eksimplaar fan Animal mei 4 poaten, in ûnbekend lûd en
in inisjalisearje-metoade. Krekt as yn oare OOP-talen kinne wy ús Animal ek
útwreidzje:

```
>> Dog := Animal nĳ.
Dog by: ['inisjalisearje'] dwaan: {
	sels inisjalisearje.
	eigen sound := ['barks'].
}.
```

Wy kinne dit maklik teste troch in tekst-metoade ta te foegjen:

```
Animal by: ['tekst'] dwaan: {
	<- eigen legs tekst + eigen sound.
}.
```

Litte wy alles byinoar sette:

@test13


It meitsjen fan in objekt dat yn in bepaalde begjintastân set wurdt, is in
faak foarkommend probleem. Stel dat der in objekt **Rectangle** makke wurde moat,
om omtrek en oerflak te berekkenjen. In mooglike notaasje soe wêze:


```
>> Rectangle := Objekt nĳ.

Rectangle by: ['area'] dwaan: {
	<- eigen lingte * eigen width.
}.
```

Fansels is it ynstellen fan in lingte en in breedte in betingst foarôf. Foar dat
doel kinne de berjochten **lingte:** en **width:** tafoege wurde:


```
Rectangle by: ['length:'] dwaan: { :lingte
	eigen lingte := lingte.
}.

Rectangle by: ['width:'] dwaan: { :width
	eigen width := width.
}.

```

Dizze rjochthoek kin dan as folget brûkt wurde:


```
>> rectangle := Rectangle nĳ length: 2, width: 3.
Utfier skriuwe: rectangle area.
```

As de begjinynstellingen fan lingte en breedte lykwols oer it holle sjoen wurde,
ûntstiet der in flatermelding:

```
>> rectangle := Rectangle nĳ.
Utfier skriuwe: rectangle area.
```

jout de folgjende flater:

```
Kaai net fûn:lingte
```

Om dit foar te kommen is it better dat in rjochthoek
altyd in begjinlingte en -breedte hat, bygelyks 0. Yn dit
gefal is it dus nedich om it berjocht **nĳ** te **oerskriuwen**.

@test610

As wy it berjocht nĳ oerskriuwe, dogge wy yn wêzen in **klasse** nei.

De wrâld fan XOScript is fol mei in ferskaat oan objekten, dy't
fan it begjin ôf beskikber binne foar jo programma. Yn de folgjende haadstikken
wurde al dizze kearnobjekten besprutsen.

## Snapshots

Jo kinne in objekt (tegearre mei syn hjoeddeiske tastân) op skiif bewarje mei:

```
myobject save-as: ['saved.bin'].
```

Om it objekt opnij fan skiif te laden:

```
>> myobject := Objekt load-from: ['saved.bin'].
```

Snapshots kinne brûkt wurde om in bepaalde tastân te bewarjen of om de prestaasjes te ferbetterjen.
It laden fan in snapshot foarkomt lexing, parsing en it ynrjochtsjen fan de applikaasje.
Yn de takomst kinne mei snapshots ek ekstra prestaasjefoardielen yntrodusearre wurde,
lykas optimalisaasje fan bepaalde patroanen of it opspoaren en
optimalisearjen fan hot paths.

{{warning}}
Snapshots binne in eksperimintele funksje; brûk se net yn produksje.
Kompilearje mei -D EXPERIMENTS om eksperimintele funksjes te aktivearjen.
{{/warning}}


@test712

# It objekt Neat

{{messages}}

It objekt Neat
stiet foar leechte, of better noch, it ûntbrekken fan ynformaasje. Sa
no en dan krije jo dit objekt as antwurd op in berjocht, as
it resultaat **neat** is. De meast essinsjele fraach
dy't jo it objekt **Neat** stelle kinne, is: **Neat?**. It
antwurd sil altyd **Ja** wêze.

```
Utfier skriuwe: Neat Neat?.
```

resultaat:

```
Ja
```

Elk oar objekt as **Neat** antwurdet mei **Nee**. It
koadefragmint hjirboppe liket miskien wat filosofysk, mar it objekt **Neat**
hat wis tige praktyske tapassingen. Jo krije bygelyks
it objekt Neat as antwurd as jo freegje om in
list-elemint dat net bestiet. Jo kinne it objekt Neat ek brûke
as jo in fariabele deklarearje wolle, mar noch gjin wearde opjaan wolle.
Ynstee dêrfan **wize** jo gewoan de spesjale wearde **Neat** **ta**. Yn
XOScript is it net tastien om in fariabele sûnder wearde te deklarearjen, lykas:


```
>> wearde.
```

Ynstee dêrfan moatte jo it folgjende skriuwe:

```
>> wearde := Neat.
```

@api_None_base

# Booleanen

{{messages}}

Oars as de measte populêre programmeartalen op it stuit fan skriuwen
leveret XOScript mar ien inkeld Ja-objekt en ien inkeld Nee-
objekt. Om it dúdlik te meitsjen: elke kear as jo **Ja** skriuwe, betsjut dat net dat
der in nij objekt makke is. Ynstee dêrfan brûke jo altyd in referinsje. Dat
betsjut dat as jo it folgjende skriuwe:

\>\> x := Ja.

de **x** ferwiist nei it objekt **Ja**. Betingstlike koade en lussen
kontrolearje ek dizze referinsje. Yn XOScript leit de betsjutting fan **Ja** en **Nee**
net fêst. Eins rekket in XOScript-programma aardich fan slach troch in
statement as dit:

Ja := Nee.

It resultaat fan sokke aksjes is net definiearre, mar it bliuwt in jildige
aksje en is dêrom formeel tastien. Fierder is der in Boolean-
objekt, dat it woartelobjekt is fan sawol **Ja** as **Nee**, om't beide
ôfliedingen fan it woartelobjekt binne. It Boolean-objekt sels hat lykwols
gjin inkele praktyske tapassing.

## Falkûlen

Wês foarsichtich mei it brûken fan **en:** en **of:**

```
Utfier skriuwe: (Nee or: Ja or: Ja), nije-rigel.
Utfier skriuwe: (Nee of: Ja, of: Ja), nije-rigel.
```

Jout

```
Nee
Ja
```
om't it berjocht **of:** mar 1 argumint nimt. It earste berjocht
stjoert **of:of:** nei Nee, dat net bestiet, dus it objekt negearret
it berjocht en jout himsels werom (Nee). De twadde rigel
stjoert dêrfoaroer **of:** folge troch noch in **of:** (mei in keppelteken, dat wol sizze in komma: ,).


@api_Boolean_base

# Getallen

{{messages}}

Elke kear as jo in getal skriuwe, bygelyks 9, -10 of 3,12, set XOScript
dizze getallen efter de skermen om yn in **Getal**-objekt. Jo
kinne berjochten nei dit Getal-objekt stjoere, of jo kinne it getal
oan in fariabele tawize en dêrnei berjochten stjoere:

```
10 even?

>> tenner := 10.
tenner even?

```

Beide notaasjes binne jildich. It Getal-objekt reagearret op de folgjende
berjochten...

De measte fan dizze berjochten sprekke foar harsels en meitsje it mooglik om
wiskundige operaasjes of fergelikingen út te fieren.

{{note}}
Tink derom dat jo ≤ ≥ ≠ × en ÷ brûke meie ynstee fan harren ASCII-tsjinhingers.
Dat is in kwestje fan foarkar.
{{/note}}

It ferskil tusken binêre wiskundige berjochten (+) en
harren kaaiwurdfarianten (optelle:) is dat de earste
in nij getal weromjouwe, dat it resultaat fan de operaasje is, wylst by de
lêste it objekt sels feroare wurdt. Dat wurdt yllustrearre yn it
folgjende foarbyld:

@test597

Yn it foarbyld hjirboppe is b = 4 en a = 3. Mei **optelle: 2** wurdt de wearde
fan a mei 2 ferhege, wylst **+ 3** in nij getal makket dat
gelyk is oan a + 3. Itselde jildt foar oare wiskundige bewurkingen, bygelyks
fermannichfâldigingen. Troch it fermannichfâldigingsteken te brûken, krije jo in
nij objekt as antwurd. As jo it berjocht **fermannichfâldigje-mei:** brûke,
fermannichfâldigje jo it getal sels.

Mei it berjocht **tusken:en:**, bygelyks yn: **Getal
tusken: X en: Y**, krije jo in getal tusken X en Y. Op dizze
wize kin elk willekeurich getal generearre wurde:

```
>> a := Getal tusken: 1 en: 10.
Utfier skriuwe: a, nije-rigel.
```

Sûnt ferzje 1.4 is de ynboude generator fan willekeurige getallen yn xoscript
kryptografysk feilich, foar safier't wy witte.

Jo kinne in **kwalifikaasje** oan in getal heakje, bygelyks **6
apples**. Elk berjocht dat net werkend wurdt troch in
getal, wurdt beskôge as in kwalifikaasje. Jo kinne de kwalifikaasje fan
in getal opfreegje mei it berjocht kwalifikaasje:

In kwalifikaasje is yn wêzen in Tekst-objekt dat mei it Getal-
objekt bewarre wurdt. De kwalifikaasje wurdt ek nei it getal printe by in
**skriuwe:**-opdracht. Kwalifikaasjes kinne bygelyks brûkt wurde om bedraggen
yn mingde faluta op te tellen. By it optellen fan de bedraggen kinne jo freegje
om de kwalifikaasjes. It folgjende programmafoarbyld yllustrearret dit
prinsipe mei in histoaryske falutarekkenmasine (om't de wiksel-
koers aardich stabyl bliuwt!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Teksten

{{messages}}

Elke kear as der in tekst tusken **blokjes en oanhellingstekens** ['...'] pleatst wurdt,
makket XOScript in nij tekstobjekt foar jo. Soargje der lykwols foar
dat jo de krekte oanhellingstekens brûke. It oanhellingsteken oan it
begjin fan de tekst is oars as dat oan it ein (sa kinne jo
it inkele oanhellingsteken brûke sûnder it te escapen).

## UTF8

Teksten yn xoscript befetsje meastentiids utf8-kodearre tekst. Hoewol't
it technysk mooglik is om binêre of net-utf8-ynhâld yn
in tekst te hawwen, wurdt oanret dêr blobs foar te brûken. Blobs wurde
levere troch de serverplugin (sjoch it haadstik ffi).
Yn it algemien wurde blobs/ffi levere
per plugin/platfoarm, om't se oanslute op it platfoarm
en de arsjitektuer (ffi/blobs). De kearn fan de skripttaal besiket
sa platfoarmûnôfhinklik mooglik te bliuwen.

## Type-omsetting

Jo kinne fan elk objekt in kopy meitsje
mei in oar type troch de folgjende berjochten te brûken:

Berjocht | Resultaat
------- | ------
getal   | Set om nei in getal
tekst   | Set om nei in tekst
boolean | Set om nei in boolean
  
De folgjende regels binne **fan tapassing**:

berjocht | Neat      | Bool               | Getal                 | Tekst     | Oars              
-------- | --------- | --------           | --------              | --------  | --------
boolean  | Nee       | n.f.t.             | 0→Nee oars→Ja         | Ja        | Meastal Ja
getal    | 0         | Nee→0 Ja→1     | n.f.t.                    | ['n']→n | Meastal 1
tekst    | ['Neat']  | ['Nee']/['Ja']     | ['n']                 | n.f.t.    | Hinget ôf

## Kopiearje

Wearden yn XOScript wurde altyd **as referinsje** trochjûn. Yn oare talen
hinget dat ôf fan it type wearde; yn XOScript is der mar ien manier:
as referinsje. XOScript makket nea in kopy fan in wearde. Om in objekt te kopiearjen,
moatte jo it berjocht **kopiearje** stjoere. 

@test611

Hjir hiene jo miskien ferwachte dat de útfier Dolly wêze soe, ynstee
fan Donny. Dat is lykwols net it gefal, om't beide nammen nei itselde
objekt ferwize. By it wurkjen mei in lus bart wat soartgelyks:

@test612

Eins brûkt XOScript **altyd** referinsjes, dus by **:quantity**
jout de lus hjirboppe ek de referinsje nei it elemint
yn de list oan.

Om in objekt te kopiearjen, moatte jo dizze hanneling
**eksplisyt** opjaan:

@test613

Troch it unêre berjocht **kopiearje** nei in tekst te stjoeren, jout it objekt
in kopy fan datselde tekstobjekt werom. It is mooglik om Getal-
objekten, booleaanske objekten, riges en listen op deselde wize te kopiearjen.

Jo kinne ek jo eigen ymplemintaasje fan kopiearje definiearje; dat is sels in
needsaak as jo jo eigen objekten meitsje. De standert-
ymplemintaasje fan kopiearje foar in rige makket in ûndjippe kopy: it makket in
nije rige mei deselde eleminten.

@test614

Yn dit gefal wurdt 4 allinnich oan de kopy tafoege.
Mar om't de kopy ûndjip is, binne de objekten yn beide riges
deselde.

@test615

As wy dus 2 oan elke namme yn de kopy tafoegje, wurdt de oarspronklike
rige ek beynfloede.

Om dit te ferhelpen moatte wy in **djippe kopy** meitsje. Sa'n kopiearaksje
foar in rige koe as folget gearstald wurde:

@test616

Tink ek om it berjocht rekursyf; dit berjocht moat
stjoerd wurde foar it berjocht kopiearje.

It is essinsjeel om yn gedachten te hâlden dat, hoewol't in kopy fan in objekt
faak itselde uterlik hat as it orizjineel, it feitlik
nea itselde is. It woartelobjekt definiearret in berjocht **equal:**,
dat brûkt wurde kin om de identiteit fan objekten te fergelykjen. Besjoch it
folgjende foarbyld:

@test617

## Ymplisite omsetting

XOScript brûkt **ymplisite omsetting** om objekten om te setten. Om in
rige op it skerm te printsjen, stjoert XOScript bygelyks yntern it berjocht
*tekst* nei de rige. Dat kin tige nuttich blike, as
jo in rige as in troch komma's skieden list printsje wolle. It
berjocht *tekst* kin oerskreaun wurde: 

@test620

@api_String_base
@api_Format_base


## Serverteksten

De folgjende Tekst-funksjes wurde tafoege troch de
serverplugin.

@api_String_server

# Funksjes

{{messages}}

Jo kinne koade groepearje tusken { en }; it wurdt dan in funksje.
Yn xoscript brûke wy soms ek de term taak, of gewoan
koadeblok.

Jo kinne in funksje útfiere troch it berjocht *begjinne* te stjoeren.


```
{ Utfier skriuwe: 123, nije-rigel. } begjinne.
```

As jo funksje arguminten nimt, brûk dan **tapasse:**.

```
{ :a Utfier skriuwe: a, nije-rigel. } tapasse: a.
```

Sjoch ek de foarbylden hjirûnder.
Fanwegen de ienfâldige arsjitektuer kin in funksje mar
ien weromkearpunt hawwe. Om overhead of tefolle nesting by
betingsten foar te kommen, kinne jo in proseduere brûke (wat itselde is as it brûken fan it
fermannichfâldigingsteken mei argumint 1):

```
{
  (a = 1) ja: { x := 1. }, ôfbrekke.
  (a = 2) ja: { x := 2. }, ôfbrekke.
} proseduere.
```

Op dizze wize wurdt (a = 2) net evaluearre as a = 1.
Jo hawwe sa ek gjin nestele ja:-berjochten nedich.
Elke kear as jo merke dat jo betingsten nestelje, tink dan
oan it berjocht proseduere. It kin jo koade
makliker lêsber meitsje.


Hjir is in wichtige falkûle:

```
{
	Nee nee: {
		Utfier skriuwe: ['End the loop.'].
	}, ôfbrekke.
	
	Utfier skriuwe: ['Dont show me.'].

} proseduere.

```

Yn dit gefal wurdt de tekst 'Dont show me' toand.
Om't **ôfbrekke** nei Nee stjoerd wurdt. As jo in
ôfbrekke útfiere wolle, moat it as berjocht nei **Ja** stjoerd wurde.
 

```
{
	Nee net ja: {
		Utfier skriuwe: ['End the loop.'].
	}, ôfbrekke.
	
	Utfier skriuwe: ['Dont show me.'].

} proseduere.

```

Wurket sa't ferwachte.

## Utsûnderings

Utsûnderings kinne sa ôfhannele wurde:

```
{ Task 1 } fange: { Task 2 }, begjinne.
```

Jo kinne ek mei opsetsin in flater yn jo programma feroarsaakje, en
dêrmei it ôfhannelingsblok aktivearje. Dat wurdt dien troch it
berjocht **flater:** nei de hjoeddeiske taak te stjoeren, sa't yn de folgjende
yllustraasje te sjen is:

```
{
dizze-taak flater: ['Whoops!'].
} fange: { :mistake
Utfier skriuwe: mistake.
}, begjinne.
```

## Wearden ynjektearje

XOScript biedt taken de mooglikheid om wearden te ynjektearjen. Besjoch
de taak hjirûnder ris:

```
>> sending := {
	Newsletter oan: eigen recipient.
}.
sending ynstelle: ['recipient']
wearde: ['info@recipient.org'].
sending begjinne.
```


Dizze yllustraasje lit in tinkbyldige taak sjen dy't in nijsbrief stjoert
nei in e-mailadres of **ûntfanger**. Dizze ûntfanger kin
fan bûten ôf en foardat de taak start, yn de taak ynjektearre wurde troch it
berjocht **ynstelle:wearde:** nei de taak te stjoeren. Op dizze wize wurdt de wearde fan
**recipient** foarôf yn de taak ynsteld. Dizze wearde kin ek feroare wurde
en de taak kin dan opnij útfierd wurde. Dit is in nuttige metoade by it brûken fan
Taak-objekten.

## Lege funksjes

Lege taken binne net tastien. Yn teory soe in lege taak der sa útsjen:
**{}**, mar XOScript sjocht dit as in taalflater. As jo
in lege taak deklarearje wolle, kinne jo it objekt Neat brûke:

```
>> task := Neat.
```

Hoewol't dit gjin echte taak is, mar in Neat-objekt, kin der
dochs in berjocht begjinne nei stjoerd wurde:

```
>> answer := task begjinne.
```

Eins is dit itselde as:

```
>> answer := Neat begjinne.
```

Om't it objekt **Neat** it berjocht **begjinne** net werkent,
jout it himsels werom as antwurd, sadat it antwurd wer **Neat** is.
It is dus net nedich om in lege taak te hawwen. Troch it elegante
ûntwerp fan de programmeartaal XOScript kinne jo hjir gewoan it objekt Neat
foar brûke.

## Dynamyske scoping

As in Funksje in fariabele nedich hat, mar dy net fine kin,
kontrolearret se de fariabelen fan de Funksje dy't har **oanroppen** hat,
en giet se sa troch mei kontrolearjen omheech troch de keten fan Funksjes.
Dit sykproses giet troch oant de fariabele fûn is.
As de fariabele dan noch net fûn is, ferskynt der in flatermelding. Dizze manier fan sykjen nei in
fariabele hjit **Dynamyske scoping**.

Om dit prinsipe te yllustrearjen:

@test618

@api_Code_base

# Woartelobjekt

{{messages}}

It objekt mei de namme **Objekt** is it woartelobjekt fan alle objekten yn
XOScript en leveret de kearnfunksjes fan de taal. 

It berjocht dat it meast stjoerd wurdt,
is **by:dwaan:**, dat de funksjonaliteit fan in objekt útwreidet. Dit
berjocht wurdt ûntfongen troch it woartelobjekt, dat dêrop de
opjûne taak oan it berjocht keppelet en sadwaande it ôflate
objekt útwreidet.

## Opfangmetoaden

Normaal wurdt in berjocht dat net oerienkomt mei
in metoade yn it objekt, negearre. Jo kinne lykwols
saneamde **magyske metoaden** of **opfangmetoaden** opjaan dy't
oanroppen wurde as it berjocht net begrepen wurdt troch it objekt.

Der binne 4 opfangmetoaden beskikber. Elk berjocht komt oerien mei
in bepaald tal arguminten.

Opfangberjocht       | Tal arguminten
-------------------- | -------------------
reagearje:             | 0
reagearje:en:         | 1
reagearje:en:en:     | 2
reagearje:en:en:en: | 3


@test619

## Programmatyske berjochten

Ynstee fan in berjocht streekrjocht nei in objekt te stjoeren, kin it ek
fia in fariabele stjoerd wurde. Dêrfoar brûke jo it berjocht
**berjocht:arguminten:**. 

@test396

@api_Object_base

# Riges

{{messages}}

XOScript ken twa soarten kolleksjes: *riges* en *listen*.
**Riges** binne opsommingen fan objekten yn in *fêste folchoarder*. Listen hawwe
gjin folchoarder, mar lykje ynstee op in leginda mei in kaai (of term) en de
byhearrende wearde. Riges binne te fergelykjen mei arrays (PHP, Java, C)
en lists (Python). Listen binne te fergelykjen mei assosjative arrays (PHP) of
dictionaries (Python) yn oare programmeartalen. Om in
nije Rige te meitsjen, skriuwe jo:

```
>> fibonacci := Rige nĳ.
```

Dizze lege rige kin fold wurde mei **tafoegje:** :

```
fibonacci tafoegje: 0.
fibonacci tafoegje: 1.
fibonacci tafoegje: 1.
fibonacci tafoegje: 2.
fibonacci tafoegje: 3.
fibonacci tafoegje: 5.
fibonacci tafoegje: 8.
fibonacci tafoegje: 13.
```

As wy de rige nei it skerm skriuwe:

```
Utfier skriuwe: fibonacci, nije-rigel.
```

Sjogge wy:

```
Rige ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

Ynstee fan tafoegje kinne jo ek ; brûke om eleminten oan in rige ta te foegjen:


```
>> fibonacci := Rige nĳ ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

De puntkomma's (;) binne allegear binêre berjochten dy't in
wearde yn de rige sette.

## Keppeljen

Stel dat jo in rige hawwe lykas:

```
>> x := Rige nĳ ; 1 ; 2 ; 3.
```

As jo it earste en it lêste elemint wiskje wolle, dan soe jo
berjocht wêze:

```
x nim-earste nim-lêste.
```

Spitigernôch wurket de foarige notaasje net goed. It
berjocht **nim-earste** jout it earste elemint fan de rige werom, dat
op syn beurt de ûntfanger wurdt fan it berjocht **nim-lêste**. It
berjocht **nim-lêste** wurdt dus net nei **x** stjoerd, mar nei 2. In
mooglike oplossing foar dit probleem soe wêze om twa aparte
sinnen te meitsjen, lykas: 

```
x nim-earste.
x nim-lêste.
```

Dat is lykwols nochal ûnpraktysk, benammen as jo
mear as twa eleminten wiskje moatte. Dêrom biedt XOScript in
alternative berjochtstruktuer foar dit soarte situaasjes. Yn
**alternative** berjochtstruktueren wurde de antwurden fan objekten negearre
en krije jo hieltyd wer it ûntfangende objekt werom as antwurd.
In **alternative** berjochtstruktuer wurdt begûn troch it
berjocht **dwaan** nei in objekt te stjoeren, en de **alternative** berjocht-
struktuer kin beëinige wurde troch it berjocht **klear** te stjoeren. Yn it
yllustrearre foarbyld koe dat as folget tapast wurde:

```
>> x := Rige nĳ ; 1 ; 2 ; 3.
x dwaan nim-earste nim-lêste klear.
```

@api_List_collections

# Listen

{{messages}}

**Sawol Rige as List binne kolleksjes. Mar oars as
in rige hat in list **gjin** folchoarder. In oar ferskil tusken de twa
is dat in list bestiet út objektparen. It iene objekt fungearret as yngong (of
kaaiwurd) om it oare objekt te sykjen. In goed foarbyld fan in
list is in priislist, lykas:


```
>> menu := List nĳ
	set: ['£5'] by: ['apple pie'],
	set: ['£6'] by: ['carrot cake'],
	set: ['£3'] by: ['fudge'].
```

Krekt as by in rige wurdt it berjocht set:by:
brûkt om in objekt oan in list ta te foegjen. It ferskil is dat, oars as by
in rige, twa objekten oan inoar keppele wurde. It earste objekt is, krekt as
by in rige, it objekt dat jo yn in list bewarje. It twadde
objekt is net de posysje dêrfan binnen de kolleksje, mar de **yngong**
wêrmei't it foarige objekt letter wer ophelle wurde kin. Koart-
sein wurket in list in bytsje as in wurdboek: mei it kaaiwurd
kin de betsjutting fûn wurde. Bygelyks, om út de
list hjirboppe de priis fan in fudge op te heljen:

```
>> price := menu by: ['fudge'].
```

Jo kinne ek de koarte notaasje brûke:

```
>> price := menu ? ['fudge'].
```

As de yngongen dy't jo brûke om objekten te bewarjen gjin spaasjes befetsje
(en net botse mei oare foarôf definiearre berjochten),
kin ek de folgjende notaasje brûkt wurde:

```
>> menu := List nĳ
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

De notaasje hjirboppe lêst sûnder mis wat natuerliker.
Om de priis fan in
fudge op te freegjen, kin de folgjende ferienfâldige notaasje brûkt wurde:

```
>> price := menu fudge.
```

@api_Dict_collections

# Bestand

{{messages}}

It objekt **Bestand** biedt basistagong ta it bestânsysteem.
Jo kinne dit objekt brûke om hiele bestannen yn ien kear yn in fariabele te lêzen,
of fariabelen yn ien kear nei bestannen te skriuwen. Rigel foar rigel lêze
wurdt ek stipe. Dat binne de meast foarkommende bestâns-I/O-operaasjes
yn in skripttaal. Avansearre bestânsoperaasjes fereaskje it
gebrûk fan FFI fia de serverplugin of in aparte IO-plugin.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Datum/tiid

{{messages}}

Foar in strukturearre foarstelling fan tiid en datum brûkt XOScript it
objekt **Momint**. As der in nij Momint-objekt op it skerm printe wurdt, wurde de
hjoeddeiske datum en tiid toand:

```
Utfier skriuwe: Momint nĳ, nije-rigel.
```

Kin resultearje yn sokssawat as:

```
2020-10-10 12:16:39
```

It is ek maklik om de yndividuele tiidkomponinten út te lêzen. As it
bygelyks allinnich nedich is om it hjoeddeiske jier te witten, kin it berjocht
**jier** nei it momint stjoerd wurde, en it antwurd sil dan in
Getal-objekt wêze dat allinnich it jier befettet:

```
>> m := Momint nĳ.
Utfier skriuwe: m jier, nije-rigel.
```

@api_Moment_system

# Programma/StdOut

{{messages}}

It Programma-objekt stiet foar de app dy't op dat stuit draait. Dit objekt
biedt funksjonaliteit om systeemopdrachten út te fieren, ûnderprogramma's op te nimmen,
arguminten te lêzen en mear. Alle systeemrelatearre funksjes.

## StdOut

Utfier is it standert útfierobjekt. It hat yn wêzen twa metoaden:
**skriuwe:** en **nije-rigel**. It berjocht skriuwe: wurdt brûkt om in tekst
nei stdout te stjoeren; it berjocht nije-rigel printet in nijeregelteken.
Ynstee fan **nije-rigel** kinne jo ek \\n brûke.

Foarbyld:

```
Utfier skriuwe: ['Hello World'], nije-rigel.
```

resultaat:

```
Hello World
```

## Modules/plugins

De wrâld fan XOScript kin útwreide wurde mei nije systeemobjekten troch
modules te ynstallearjen. In nij systeemobjekt kin oan de wrâld fan
XOScript tafoege wurde troch it modulebestân (meastal in bestân mei it efterheaksel .so
) yn de map mods te pleatsen. 

As jo in berjocht stjoere nei it objekt dat troch de
pluginmodule beskikber steld wurdt, wurdt it automatysk troch XOScript laden.

Jo kinne ek sels plugins skriuwe. Plugins wurde skreaun yn de
programmeartaal C. Jo kinne in foarbyldplugin fine yn it boarnekoade-
pakket ûnder src/plugins/example.


## Refleksje

Der binne ferskate manieren om it systeem
te ferkennen wylst it programma útfierd wurdt. XOScript hat in pear metoaden om
te ûntdekken hokker objekten oanwêzich binne en op hokker berjochten dizze objekten
reagearje. Earst kin elk objekt frege wurde hokker **type** it is,
mar typen binne yn XOScript feroarber en dêrom ûnbetrouber.

It is ek mooglik om it Programma-objekt te freegjen oft in
bepaald objekt al oanwêzich is yn it programma:

```
Programma Tool ja: { ... }.
```

By in objekt-
namme dy't út ien inkeld symboal bestiet, is it it bêste om de
folgjende notaasje te brûken om betizing foar te kommen:

```
Programma fine: ['X'], ja: { ... }.
```

Njonken it freegjen nei objekten is it likegoed mooglik om it
Programma-objekt nei berjochten te freegjen. It kin bygelyks frege wurde oft it
objekt **Getal** it berjocht **tusken:en:** ken, op de wize
sa't hjirûnder yllustrearre wurdt:

```
Programma Number: ['between:and:'], nije-rigel.
```

@api_Program_system

# server

{{messages}}

De serverplugin yn xoscript biedt funksjonaliteit om
applikaasjes oan de serverkant te meitsjen. Om de server-
plugin te laden, brûke jo:

```
Server inisjalisearje.
```

Foar jo gemak wurdt ek oanret om
de bestannen webtools.xo en template.xo te laden.

```
Programma brûke: ['webtools.xo'].
Programma brûke: ['template.xo'].

```

## Serverynstellingen

Jo kinne de folgjende serverynstellingen ynstelle:

```
	# default values are given
	# so if you do not set anything these
	# values are used...

	Programma 
	ynstelling: ['max-postfields']
	wearde: 40.

	Programma 
	ynstelling: ['max-contentlength']
	wearde: 2000000. # 2MB

	Programma 
	ynstelling: ['max-time']
	wearde: 5000. # 5sec

```

## Hallo wrâld

Hjir is in hiel ienfâldich webprogramma dat jo brûke kinne mei in
standert CGI-server lykas Apache2, NGINX, OpenHTTPD of in oare
bekende server.

```
#!/bin/xo

Server inisjalisearje.
Programma brûke: ['webtools.xo'].

>> web-document := Webdokumint nĳ.

web-document útfiere: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

As jo it objekt Webdokumint net brûke wolle, is dat gjin probleem, mar
dan moatte jo de HTTP-koppen sels skriuwe:

```
#!/bin/xo
Utfier skriuwe: ['Content-type: text/html; charset=utf-8 \n\n'], nije-rigel.
Utfier skriuwe: ['hello world!'], nije-rigel.
``` 

## Fersyk

It objekt HTTP-Fersyk kin brûkt wurde om GET-/POST-/COOKIE- en
UPLOAD-gegevens op te heljen:

```
>> fersyk  := HTTP-Fersyk nĳ.
>> search   := fersyk get: ['search']. # ?search=books
>> password := fersyk post: ['password']. # from form
>> selected := fersyk get-list: ['sel[]']. #?sel[]=1&sel[]=2
>> selected := fersyk post-list: ['sel[]'].
>> cookie   := fersyk cookie: ['session-id'].
>> upload   := fersyk upload: ['file'].
>> temppath := upload ? 1.
>> filename := upload ? 0.
```

## Maxpost/lingte

It standert maksimum oantal postfjilden is 40 en de standert maksimale ynhâlds-
lingte is 2MB. Om dat per skript oars yn te stellen:

```
Programma ynstelling: ['max-contentlength'] wearde: 1. 
Programma ynstelling: ['max-postfields'] wearde: 1. 
```

{{note}}
As de ynhâldslingte it maksimum oerskriuwt, wurdt it
proses beëinige, om't wy der net mear wis fan wêze kinne
dat de payload feilich is.
{{/note}}

De maxtime-limyt bepaalt de maksimale tiid yn ms
om stdin/postgegevens te lêzen.

```
Programma ynstelling: ['max-time'] wearde: 5000. # 5sec
```

Dit jildt allinnich foar it I/O-lêzen fan de post, en foarkomt
slowloris-eftige oanfallen. As jo de útfieringstiid fan elke operaasje
echt beheine wolle, brûk dan Programma alarm:.

## Databank

It Databank-objekt kin brûkt wurde om MariaDB/MySQL te befreegjen.
Om mei in databank te ferbinen, dogge jo:

```
>> db := Maria-DB nĳ host: ['localhost'],
	brûkersnamme: ['xo'],
	wachtwurd: ['pass123'],
	databanknamme: ['xobase'],
	ferbine.

```

Om in record yn te foegjen, brûke jo:

```
>> sykparameters := db fraach: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parameters: ( Rige nĳ ; ['abc'] ; 12.35 ; 6 ). # parameterized queries

{  sykparameters útfiere. db befêstigje. }
fange: { :e db weromdraaie.  }, begjinne.
```

Tink derom dat xoscript *allinnich* mei transaksjes wurket en nea automatysk commit.
As autocommit net útskeakele wurde kin, krije jo in ferbiningsflater.
Brûk foar queries altyd parameterbinding; foegje brûkersynfier nea streekrjocht
ta oan de SQL.

Helje de ynfoege id sa op:

```
Utfier skriuwe: ['INSERTED: '] + sykparameters insert-id, nije-rigel. # insert id
```

Om records op te heljen:

```
>> sykparameters :=
db
	fraach: ['SELECT * FROM book order by id desc limit 2'], 
	ophelje: { :row 
		Utfier skriuwe: row id + [' '] + row description + [': '] + row price, nije-rigel.
	}. # fetching rows

```

## Sesjes

Foar persistinsje kinne jo gegevens bewarje yn en ophelje út in sesjeobjekt.
Meitsje earst in nij **Webdokumint**. It objekt Webdokumint bynt
it fersyk, de koppen, de HTML en de sesje oan inoar. Dat komt om't jo, elke kear as jo
mei jo browser in webside besykje, allinnich de HTML sjogge. Mar it
hiele Webdokumint bestiet ek út **koppen**. Bygelyks:
de measte HTTP-antwurden befetsje in kop lykas Content-type:text/html om
de browser te fertellen dat de gegevens dy't folgje as HTML werjûn wurde moatte
(en net bygelyks as in bestân downloade). Sesjes binne in manier om
brûkersgegevens tusken fersiken te bewarjen. Om dizze gegevens by te hâlden, moatte wy
in cookie ynstelle, en dy cookie wurdt ek fia in kop ynsteld. Dêrom
komt alles gear yn it Webdokumint (om't dat it folsleine
dokumint is mei sawol koppen as HTML of oare gegevens).


```
# First we make a new Web Document instance
>> web := Webdokumint nĳ.

# Now we start a session, this will generate a Header for a cookie and
# create a file to store your data, associated with that cookie
>> session := web sesje-begjinne.

# Now we can treat session like a dict
session userid: 123.
```

Om de sesje te ferneatigjen (by it ôfmelden):

```
web sesje-fernielje.
```

## Koppen

It Webdokumint lit jo ek oare bekende koppen ynstelle.
Bygelyks as jo de brûker trochstjoere wolle nei in oare URL:

```
web gean-nei: ['/other.html'].
```

Under de motorkap makket dizze opdracht ek de HTTP-kop dy't
mei jo oare gegevens of HTML meistjoerd wurdt om de browser op te dragen
nei it opjûne doeladres te navigearjen.

Om in eigen kop ta te foegjen:

```
web kop: ( 
	HTTP-Kop nĳ
	kaai: ['Content-Length']
	wearde: 400
).
```

Om in 404-side te toanen:

```
web net-fûn: ['OOps..'].
```


## Sjabloanen

It standert sjabloansysteem is tige ienfâldich. Jo hoege gjin
nije sjabloansyntaksis te learen. Boppedat soarget de sjabloanmotor foar echte skieding
tusken presintaasje en bedriuwslogika.

Om in sjabloan út in bestân te meitsjen:

```
>> tpl := web sjabloan: ['templates/ux.tpl'].
```

It sjabloansysteem brûkt markearrings. 
Der binne trije soarten markearrings: knipmarkearrings, plakmarkearrings en
slotmarkearrings. It basisidee is echt ienfâldich: jo knippe
gebieten út dy't oanjûn wurde troch knipmarkearrings, en jo kinne se plakke op
plakken dy't oanjûn wurde troch plakmarkearrings. Jo kinne teksten ynjektearje yn
slotmarkearrings.

Litte wy bygelyks, mei it folgjende sjabloan, de
edelstien yn it sieradekistje lizze en in priiskaartsje tafoegje.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Dat kinne jo sa dwaan:

```
>> gem := tpl knippe: ['gem'], kopiearje.
gem price: 99.
tpl plakke: gem by: ['jewels'].
web útfiere: tpl skjinje.
```

De lêste rigel stjoert it sjabloan gewoan as tekst nei de client,
tegearre mei de fereaske HTTP-koppen.

Resultaat:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

Om troch brûkers opladen bestannen feilich oan te bieden, kinne jo fertrouwe op passthru:

```
>> uploaded := ['smile.gif'].
Server trochjaan: uploaded foarheaksel: ['/uploads/images/'].
Programma ein.
```

Dit biedt de troch de brûker opladen ynhâld oan mei it passende
mimetype. Allinnich mimetypen op de wite list wurde stipe:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF en SVG.
SVG-, ZIP- en GZIP-bestannen wurde as download ferstjoerd, om't in SVG
skripts befetsje kin dy't oars op jo domein útfierd wurde soene.
Dizze metoade foarkomt TOCTOU-oanfallen, path traversals,
it útfieren fan kweawillige koade (ynjeksje), symlinkoanfallen,
DDoS-oanfallen (bestânslimyt = 50MB), sniffingoanfallen en
ferskate oare feiligensproblemen.


## JSON

Om in objekt as JSON te kodearjen:

```
>> json := ( JSON jsonify: ( 
	List nĳ set: ( 
		Rige nĳ ; 1 ; 2 ; 3
	) by: ['abc']
)).
```

Om JSON te dekodearjen nei in xoscript-objekt:

```
>> dict := ((JSON objekt: json) abc ? 1).
```

JSON mei mear as 500 nivo's fan nesting wurdt as ûnjildich ôfwiisd.

Om in List streekrjocht as json út te fieren mei de krekte koppen:

```
web json: dict.
```


## Regex

Jo kinne reguliere ekspresjes brûke troch in patroan te meitsjen.
Bygelyks om de hrefs en targets fan hyperlinks te finen:

```
Patroan nĳ: ['href="([^"]+)" target="([^"]+)"'].
```

Pas it patroan no sa ta op de ûnderwerptekst:

```
pattern oerienkomst: ûnderwerp dwaan: { :m :x .... }
```

Folslein foarbyld:

```
>> ûnderwerp := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> pattern := Patroan nĳ: ['href="([^"]+)" target="([^"]+)"'].
>> result  := pattern oerienkomst: ûnderwerp dwaan: { :m :x
	Utfier skriuwe: m, nije-rigel.
	Utfier skriuwe: x, nije-rigel.
	<- ['XXX'].
}.
Utfier skriuwe: result, nije-rigel.
```

## Netwurk

Brûk it objekt Netwurk om in webfersyk út te fieren.
It objekt Netwurk stjoert altyd in POST-fersyk, útsein as jo Neat as
gegevens stjoere; dan stjoert it in GET-fersyk.


```
Netwurk 
post: Neat 
nei: ['https://redbeanphp.com'].
```

## Fersifering

De serverplugin komt mei fersifering op basis fan XChaCha20 en Argon2.

Foarbyld:

```
>> encrypted := Klûs fersiferje: ['hello'] kaai: ['world'].
>> decrypted := Klûs fersiferje: encrypted kaai: ['world'].
```

## Tokens

Om in kryptografysk feilich token fan in bepaalde lingte te generearjen:

```
>> mytok := Klûs token: 40.
```

Dit generearret in token fan 40 tekens.

## Opmaak

It objekt Formaat lit jo gegevens opmeitsje, lykas opfolje of
nullen tafoegje. It brûkt de printf-syntaksis.

```
>> fmt := Formaat nĳ: ['%06.0f'].
fmt tapasse: 56. # gives 000056
```

In formaat kin ien omsetting befetsje en dy moat by de wearde passe,
oars krije jo in flater:

- `tapasse:` mei in tekst: `%s`
- `tapasse:` mei in getal: `%f`, `%e`, `%g` of `%a`
- `tapasse-int:` mei in getal: `%d`, `%i`, `%o`, `%u`, `%x` of `%c`

Wearden út in fersyk binne teksten. Om ien as getal op te meitsjen,
set it dan earst om:

```
fmt tapasse: (fersyk get: ['amount']) getal.
```

## Kodearders

Der binne ferskate kodearders en dekodearders beskikber.
De url-kodearder makket in url klear foar gebrûk yn HTML as keppeling:

```
Server url-kodearje: ['https://example.com?a=6&b=1 2'].
```

Om brûkersynfier feilich yn jo HTML te ynjektearjen sûnder risiko op XSS-
ynjeksjes, brûke jo altyd:

```
Server html-kodearje: ['<harmless>'].
```

Tink derom dat de sjabloanmotor altyd html-kodearring útfiert
as jo nei in slotmarkearring skriuwe. As jo it sjabloansysteem brûke,
hoege jo dit dus net te brûken.

## E-mail

Brûk de bibleteek mailtools.xo om in e-mail te stjoeren.

Foarbyld:

```
Server inisjalisearje.
Programma brûke: ['mailtools.xo'].

>> e-mail := HTML-E-mail nĳ.
>> img := e-mail taheakje: ( Bestand nĳ: ['myimage.png'] ).

e-mail
ôfstjoerder: ['xo@xoscript.com'] namme: ['xo'],
oan: ( Rige nĳ ; ['xo2@xoscipt.com'] ),
ûnderwerp: ['xoxo'],
berjochttekst: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), stjoere.

```



## Keppeljen

Mei it berjocht keppelje: kinne jo in eksterne bibleteek oan
jo programma keppelje mei libffi. Sjoch foar details it haadstik oer ffi.


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

FFI wurdt per platfoarm/plugin levere, om't it
oanslút op de ûnderlizzende systeemarsjitektuer, wat de
kearn net dwaan moat.
De serverplugin biedt in konforme ffi/blob-ymplemintaasje.
Standert ferbynt de kearn mei it doelplatfoarm
fia stdin/stdout, beheinde bestâns-i/o-tsjinsten en de shell (Programma systeem:).
Oanfoljende yntegraasje wurdt levere troch ffi/blobs fia applikaasje-
rjochte plugins lykas de serverplugin.

FFI stiet foar Foreign Function Interface. It lit jo funksjonaliteit brûke dy't troch oaren skreaun is yn
oare programmeartalen, levere fia DLL-bestannen, SO-bestannen of Dylib-bestannen. Dat kinne
allerhanne funksjes wêze, en der is op dizze wize in enoarm oanbod oan funksjonaliteit beskikber.
Litte wy begjinne mei in foarbyld:

```
Server keppelje: (
 Rige nĳ ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Rige nĳ ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s frijjaan.
```

It resultaat fan dizze koade is dat jo it folgjende op de kommandorigel sjogge:
FFI has 3 letters.
No tinke jo wierskynlik: "Dat is in protte koade foar wat sa ienfâldichs."
Ik bedoel, koene wy dit net gewoan oplosse mei in Gui-show-opdracht? It antwurd is in folmondich ja!
Mar dit is bedoeld as yllustratyf foarbyld.
FFI wurdt meastal brûkt foar kompleksere taken, mar dy jouwe gjin goede
foarbylden, dus haw ik wat trivjaals keazen.

De arguminten foar de metoade keppelje:

- Argumint #1: It DLL- of SO-bestân dat jo brûke wolle.
- Argumint #2: De funksje yn dat bestân dy't jo keppelje wolle.
- Argumint #3: In rige mei de nammen fan de gegevenstypen fan de arguminten fan de funksje.
- Argumint #4: De namme fan it weromjoutype fan de funksje.
- Argumint #5: De namme fan it objekt dêr't jo dizze funksje oan keppelje wolle (as it net bestiet, wurdt it
automatysk makke).
- Argumint #6: It berjocht dêr't dizze funksje oan keppele wurde moat.

Yn it foarbyld hjirboppe wolle wy de funksje printf út libc.so keppelje. Jo kinne de nammen fan de gegevens-
typen fine yn de dokumintaasje fan de software dêr't jo nei keppelje. De beskikbere typen binne:
void, pointer, float, double, int, uint, char, uchar, intX en uintX,
dêr't X 8, 16, 32 of 64 wêze kin.

Dizze typen ferwize nei it tal bytes dat nedich is om de gegevens te bewarjen. Foar printf keppelje wy oan in
nij objekt mei de namme Printf en it berjocht template:number:. Jo sette de eksterne
funksje oer nei it XOScript-dialekt foardat jo se brûke. It berjocht template:number: ferwachtet in
buffer mei de sjabloantekst as earste parameter. Wy meitsje dizze buffer mei in Blob-objekt, dat
it mooglik makket om mei de hân ûnthâld te allokearjen. Jo binne dêrnei sels ferantwurdlik foar it frijjaan fan dit ûnthâld
mei it berjocht frijjaan.

Jo kinne in ûnthâldblob op ferskate manieren folje. Yn ús foarbyld folje wy it mei tekst, dus brûke wy it
berjocht utf8: (UTF-8 is in kodearring om tekst yn bytes om te setten). Jo kinne in blob ek folje mei
bytes:, wêrby't jo in rige mei bytewearden trochjouwe. Om de ynhâld fan in blob te lêzen, brûke jo fan:lingte:.
Jo krije de bytes dan werom as in rige. Jo kinne sels in C-struct meitsje mei in Blob troch it
berjocht struct: te brûken, mei in folchoarder fan C-typen. Dat kin nedich wêze as jo in C-
funksje yn in eksterne softwarebibleteek oanroppe dy't in pointer nei in struct ferwachtet.

{warning}
Jo moatte blobs sels frijjaan.
Blobs wurde net opromme troch de garbage collector.
{/warning}

Om't blobs útwiksele wurde kinne mei eksterne funksjes út bibleteken, kinne
se net automatysk troch de garbage collector opromme wurde (se kinne noch yn gebrûk wêze by
eksterne funksjes, of dy eksterne funksjes wolle se miskien
sels frijjaan). Dêrom moatte jo blobs as it nedich is sels frijjaan.

Om in blob frij te jaan, brûke jo:

```
myblob frijjaan.
```

Om in struct frij te jaan, brûke jo:

```
mystruct struct-frijjaan frijjaan.
```

Foar in struct moatte jo dus twa berjochten stjoere: struct-frijjaan en frijjaan, om
it ûnthâldblok frij te jaan.

@api_Blob_fficonnect
