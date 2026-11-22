# Základy

{{messages}}


Vitajte v XOScript
Cieľom projektu XOScript je vytvoriť skriptovací jazyk, ktorý je jednoduchý a auditovateľný.
Jednoduchý nemusí nevyhnutne znamenať ľahký.
Známy programovací jazyk môže byť ľahšie použiteľný ako XOScript.
Jednoduchosť tu znamená niečo iné:
schopnosť vytvoriť si úplný mentálny model jazyka a jeho správania.

XOScript je navrhnutý tak, aby sa vám zmestil do hlavy.
Jeho gramatika a počet konceptov sú zámerne malé.
Neexistujú žiadne triedy; objekty možno rozširovať priamo.
Objekty sa odovzdávajú odkazom, kopírovanie je explicitné
a funkcie majú jediný výstupný bod.

Niektoré z týchto rozhodnutí sa výrazne líšia od bežných jazykov.
XOScript napríklad nemá typový systém a používa dynamický rozsah platnosti premenných.
Správy, ktoré nemožno spracovať, sa ignorujú namiesto toho, aby vyvolali výnimku.
Tieto rozhodnutia majú svoje dôsledky a ich cieľom nie je eliminovať chyby.
Ich cieľom je zachovať základný model jazyka malý a konzistentný.

XOScript možno tiež lokalizovať, vďaka čomu je možné vyjadriť obchodné
pravidlá v prirodzenom jazyku a prípadne ich zdieľať s netechnickými zainteresovanými stranami.

Auditovateľnosť znamená uplatnenie rovnakej filozofie na implementáciu.
Runtime je napísaný v C, s malým ručne písaným lexerom, parserom a tree walkerom.
Štandardná knižnica a runtime do veľkej miery zrkadlia štruktúru jazyka,
vďaka čomu je vzťah medzi kódom XOScript a jeho implementáciou pomerne priamy.

Testy sú tiež úzko prepojené s dokumentáciou.
Každá metóda by mala mať priradený test, ktorý možno začleniť do príručky,
čo pomáha udržiavať dokumentáciu v súlade s implementáciou.

XOScript nemá v úmysle konkurovať bežným jazykom
funkciami ani známosťou. Skúma iný cieľ:
programovacie prostredie, ktorému vývojár dokáže porozumieť ako celku.

Dúfame, že malý jazyk a malá
implementácia umožnia v praxi porozumieť softvéru
od bajtu po objekt, od syntaxe po runtime, a písať kód
s istotou, pretože rozumiete tomu, čo sa deje v
skripte, aj tomu, čo sa deje pod kapotou.

Architektúra serverového nasadenia xoscript
je jednoduchá, a predsa flexibilná.

{{architecture.png}}

Ak chcete používať xoscript ako serverový jazyk, musíte nainštalovať
serverový plugin do priečinka /mods/server. 

Je to preto, že radi
oddeľujeme jadro jazyka od funkcií špecifických pre server,
na rozdiel napríklad od PHP alebo Pythonu. Inak by sme museli každému
dodávať úplne všetko bez akéhokoľvek účelu, čo je jednoducho hlúpe.
Ak chcete, môžete nainštalovať aj ďalšie moduly. Systém je veľmi
flexibilný.

Niektoré funkcie je navyše lepšie implementovať priamo v skriptovacom
jazyku, napríklad šablóny a správu relácií, preto pre vaše pohodlie
dodávame aj knižnice template.xo a webtools.xo.
Dôvodom toho všetkého je, že nevieme, ako chcete
xoscript používať. Môžete ho používať ako serverový skriptovací jazyk,
ale aj pre GUI, vstavané zariadenia alebo len na dávkové spracovanie.
Aj keď ho používate ako serverový skriptovací jazyk (čo je
v súčasnosti jeden z hlavných prípadov použitia), možno budete chcieť
použiť iný šablónovací systém alebo iný správca relácií.
Kto sme my, aby sme rozhodovali, že máte používať ten náš?

Jednou z výhod používania nášho vlastného šablónovacieho systému však je, že
sa na tvorbu šablón nemusíte učiť ďalšiu syntax.
Predvolený šablónovací systém dodávaný s xoscript používa 100 %
oddelenie prezentácie od logiky. Namiesto špeciálnej
šablónovej syntaxe jednoducho používa veľmi flexibilný systém značiek slotov.
Viac informácií nájdete v kapitole Server.

Upozorňujeme, že ak nechcete používať predvolený šablónovací systém alebo
predvolené webtools, je samozrejmé, že musíte poskytnúť
vlastné.

Ak váš webový server beží v chroot, jail alebo inom druhu sandboxu,
musíte do tohto prostredia nainštalovať aj závislosti xo; ktoré
knižnice potrebujete, zistíte pomocou ldd (pozri manuálovú stránku Linuxu alebo BSD).
Ak chcete vo svojich xo-skriptoch používať príkazy shellu, skopírujte do tohto
prostredia aj shell (napríklad bash alebo ksh).

Radi by sme tiež poznamenali, že spätnú kompatibilitu berieme veľmi vážne.
Existuje dokonca špeciálna funkcia pre spätnú kompatibilitu nazvaná
'version'. Vo všeobecnosti sa snažíme, aby váš kód fungoval navždy. Nikdy
teda nebudete musieť aktualizovať svoj kód, aby zostal kompatibilný s novšími verziami
xoscript. Naším cieľom je: napíš raz, spúšťaj navždy.

Zvyšok tejto príručky je venovaný podrobnému vysvetleniu programovacieho
jazyka xoscript. Serverové skriptovanie je opísané v kapitole
s názvom Server. Ak ste skúsený softvérový vývojár, možno budete chcieť
niekoľko kapitol preskočiť, pretože niektoré sú príliš podrobné alebo
sú veľmi podobné všeobecným programátorským postupom. Tí z vás,
ktorí už majú skúsenosti s viacerými inými programovacími jazykmi,
by teda mali túto príručku radšej používať ako referenčnú príručku.

## Inštalácia v Linuxe

Stiahnite si apache2 a mariadb:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Stiahnite si xoscript.
Nahraďte X správnym číslom verzie!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Skopírujte súbory do webrootu a do /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Upravte konfiguráciu apache2:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Nahraďte Virtualhost týmto:

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

Vytvorte testovaciu stránku:

```
sudo nano /var/www/html/test.xo
```

a napíšte malý testovací program:

```
#!/bin/xo
Server inicializovať.
Program použiť: ['webtools.xo'].
>> web := Webový-dokument nový.
web vypísať: ['Hello World'].
```

Povoľte apache2 spúšťať váš program cez CGI:

```
sudo chmod uog+x /var/www/html/test.xo
```

Reštartujte apache2:

```
sudo systemctl restart apache2
```

Otvorte svoju testovaciu stránku v prehliadači:

```
http://localhost/test.xo
```

Mali by ste vidieť:

```
Hello World
```


## Inštalácia v OpenBSD

Upravte /etc/httpd.conf, pridajte:


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

Ak chcete používať SSL:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Ak chcete chrániť výmenu kľúčov pred kvantovými počítačmi,
zvoľte šifru mlkem:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Pridajte binárny súbor xo a moduly, ako aj všetky závislosti, do
chrootu (zistite ich pomocou ldd).

## Spúšťanie príkladov


Ak chcete spustiť jeden z príkladových programov v balíku:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Napríklad na spustenie príkladu FizzBuzz v Linuxe:

```
./example.sh fizzbuzz Linux
```

Na spustenie toho istého príkladu v OpenBSD:

```
./example.sh fizzbuzz OBSD
```

Na spustenie príkladu s čistým zostavením:

```
./example.sh fizzbuzz OBSD clean
```

## Jednotkové testy

Na spustenie jednotkových testov:

```
./runtests.sh
```

Na spustenie jednotkových testov bez zostavenia (iba testovanie):

```
./runtests.sh nobuild
```

## Zostavenie

Na zostavenie zo zdrojového kódu v Linuxe:

```
make clean
ISO="en" make
```

V OpenBSD:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

Na zostavenie serverového pluginu v Linuxe:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

Na zostavenie serverového pluginu v OpenBSD:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Ahoj svet

Po prenesení do počítača môžete súbor rozbaliť
a spustiť xo pomocou nasledujúceho príkazu:

```
xo
```

Ak chcete spustiť XOScript, uložte program ako súbor s príponou
-xo (voliteľné). Okrem toho za príkaz XOScript vložte názov súboru
vášho programu:

```
xo myprogram.xo
```

Keď spustíte príkaz XOScript a ako parameter použijete súbor
s programom, xo váš programový súbor načíta a vykoná.

{{note}}
Program môžete spustiť aj tak, že ho pretiahnete na ikonu xo.
{{/note}}

{{warning}}
Na niektorých systémoch musíte xo vopred povoliť načítavanie dynamických
knižníc.
{{/warning}}

Tradícia velí, že prvý program v každom novom programovacom
jazyku by mal byť akýmsi pozdravom svetu. V XOScript vyzerá taký
program **Hello world** takto:

@test598

Keď tento text uložíte do súboru, napr. hello.xo, môžete ho spustiť
takto: .

xo hello.xo

Hello world


Výstup programu vidíte vo vyššie zobrazenom čiernom okne.
V celej tejto príručke sa na zobrazenie výstupu
bude používať rovnaká vizualizácia.

{{note}}
Výstup sa píše s veľkým V.
Vo všeobecnosti sa názvy objektov začínajú veľkým písmenom,
pokiaľ objekt nevystupuje ako inštancia (nemá žiadne vlastné
metódy, iba údaje). Zodpovedá to konvenciám tried a inštancií
v iných programovacích jazykoch.
{{/note}}


## Syntax 

XOScript je *čisto* *objektovo orientovaný* programovací jazyk. To znamená,
že xoscript všetko považuje za objekt, a preto neexistujú
žiadne iné *dátové typy*. V programe napísanom v XOScript existujú
v podstate tri základné činnosti: *priraďovanie*, *posielanie správ*
a *odpovedanie*. Výmena správ medzi objektmi je kľúčovou súčasťou
programu v XOScript. Tieto tri jednotlivé činnosti sú znázornené
nižšie:


Činnosť         | Príklad
--------------- | --------
priradenie      |  \>\> x := 1. 
unárne správy   | x párne?.
binárna správa  | 1 + 2.
kľúčová správa  | x od: 0 dĺžka: 10.
odpoveď         | <- answer.  


Táto kapitola vám poskytne všeobecný dojem o jazyku XOScript
a opisuje jeho základné princípy. XOScript je malý jazyk
založený na troch činnostiach (pozri ilustráciu), ktoré sa premietajú do
približne šiestich gramatických pravidiel. To je všetko, čo potrebujete na zvládnutie
jazyka.

Nemusíte sa obávať, ak vám veci nie sú hneď jasné: všetky stavebné
kamene budú preskúmané v nasledujúcej kapitole (3) a základné pravidlá sa
zopakujú. Táto kapitola však slúži najmä ako všeobecný
úvod do jazyka. Základné princípy budú stručne
vysvetlené a ilustrované niekoľkými relevantnými príkladmi. Chýbajúce
podrobnosti budú vysvetlené neskôr.

Komentáre v XOScript sa začínajú symbolom \#. Nasledujúci riadok
sa teda bude ignorovať:

```
# this is just a comment
```

## Premenné

Na priradenie
premennej použijete symbol deklarácie premennej: >>. Názov
premennej môže obsahovať všetky znaky okrem: <-, :=, medzier,
bodiek, čiarok, dvojbodiek, úvodzoviek [' '] a zátvoriek ().
Premenná sa navyše nemôže skladať z viacerých riadkov. Upozorňujeme,
že premenná sa nemôže začínať číslicou ani znamienkom mínus.

Toto sú príklady platných premenných:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dollar'].
>> +plus := Pravda.
>> user-password := ['Pssst!'].
```

Neplatné premenné sú napríklad:


```
>> -123 := ['negative number'].
>> password of user := ['Classified'].
>> password.of:user := ['Classified'].
>> ,x := 10.
```

{{note}}
V textovom literáli nemusíte escapovať žiadny znak
(vrátane apostrofov, úvodzoviek a hraníc
textu), pokiaľ to lexeru
nespôsobuje nejednoznačnosť.
{{/note}}

Po deklarovaní premennej ju môžete voľne používať. To znamená,
že symbol deklarácie je potrebné použiť iba pri prvom
použití premennej (pri deklarácii).

Presnejšie povedané, nemôžete len tak začať priraďovať hodnotu
premennej *(x := 2)*, pretože premennú musíte najprv deklarovať *(\>\>
x := 2)*. Po deklarovaní však môžete meniť jej hodnotu
bez použitia symbolu deklarácie*(\>\> x := 2. x := 3.)*.

Upozorňujeme, že pri deklarácii je povinné priradiť premennej hodnotu.
Na rozdiel od iných programovacích jazykov nie je dovolené
deklarovať premennú bez hodnoty. Je nevyhnutné explicitne spojiť
každú premennú s počiatočnou hodnotou. Premennú však pokojne môžete
inicializovať objektom **Nič**. V takom prípade možno premennú
považovať za prázdnu *(\>\> x := Nič.)*. Stručne povedané, deklarovať
premennú bez počiatočnej hodnoty nie je dovolené. Teda,

```
>> x.
```

je neplatné a vyvolá chybové hlásenie.

{{note}}
xoscript používa dynamický rozsah platnosti premenných,
podrobnosti nájdete v kapitole Funkcie.
{{/note}}


## Literály

XOScript všetko považuje za objekt, t. j. všetky čísla, texty
a fragmenty kódu. Čísla, napríklad 1, 2, 100, -999 a 1,234, sú
objekty Číslo. Všetky texty medzi jednoduchými úvodzovkami sú objekty
Text. Všetky fragmenty kódu zoskupené v zložených zátvorkách {...} sú
objekty Funkcia.

Literál         | Koreňový objekt | Príklad
--------------- | ------------ | ----------
čísla           | Číslo        | 1,2,3... 
texty           | Text         | \['hello'\]
funkcia         | Funkcia      | { 1 + 2. }.
                
     
Objekty, ako sú čísla a texty, majú svoj pôvod vždy v koreňovom
objekte. Napríklad všetky čísla sú odvodené od objektu **Číslo**. Všetky
texty sú odvodené od **Text** a všetky fragmenty kódu od **Funkcia**.
Všetky tieto objekty zasa pochádzajú z **Objekt**, ktorý je v skutočnosti
koreňovým objektom všetkých objektov.


## Správy

Programovanie v XOScript v podstate znamená
posielanie správ objektom. Všeobecný zápis poslania správy
objektu je nasledujúci:

```
<object> <message>
```

Ak chcete napríklad zistiť, či je číslo **2** párne, pošle sa
objektu **2** správa **párne?**:

```
2 párne?
```

Odpoveďou bude **Pravda** (opäť objekt). Neznáme správy objekty
zvyčajne ignorujú, takže nenastane žiadna chyba. Niektoré objekty (napr.
čísla alebo texty) reagujú na neznámu správu preddefinovaným spôsobom
(viac o tom neskôr).

Objekt môže prijímať tri druhy správ. 

Typ             | Počet argumentov
--------------- | -------------------
Unárna          | 0      
Binárna         | 1     
Kľúčová         | 1+    


Po prvé, existujú **unárne
správy**, pozri príklad vyššie, ktoré sú bez argumentov. Po druhé,
existujú **kľúčové správy**, ktoré majú jeden alebo viac argumentov,
napríklad:

```
>> x := Číslo medzi: 1 a: 10.
```

V tomto prípade sa správa **medzi:a:** posiela objektu **Číslo**, ktorý
je koreňovým objektom všetkých čísel. Výsledkom bude náhodné číslo
medzi 1 a 10. Nakoniec existujú **binárne správy**, ktoré majú
iba jeden znak a jeden argument:

```
2 + 3
```

Vyzerá to ako matematický súčet, ale v skutočnosti je to len ďalšia správa.
Správa **+** sa posiela objektu **2** s argumentom **3**, čo vráti
odpoveď **5**. Binárne správy sa smú písať bez dvojbodky.

Binárne správy možno reťaziť:

```
>> x := 3 + 2 - 1.
```

V tomto fragmente sa najprv pošle **+ 2** objektu Číslo **3**, čo
vedie k objektu Číslo **5**, potom sa tomuto číslu pošle **-1**.
Pozorní čitatelia si správne všimnú nesúlad, ktorý
tento protokol vykazuje voči bežnému matematickému poradiu
operátorov. XOScript ignoruje matematické poradie v prospech
konzistentnosti svojho systému správ. Výsledkom súčtu:

```
2 + 3 * 5 = 25
```

teda nie je 17.

Je to zámerné. Na zmenu poradia možno použiť zátvorky:

```
2 + (3 * 5) = 17
```

Väčšina objektov vracia ako výsledok odpovede na určitú
správu samu seba. Je to užitočné, pretože to podporuje ďalší dialóg s týmto
objektom posielaním nadväzujúcej správy:

```
Výstup písať:
[' hello '] orezať veľké-písmená.
```

```
HELLO
```

Tu sa objektu **Text** posielajú dve správy: **orezať**, a po nej
**veľké-písmená**.

V nasledujúcom fragmente je potrebné použiť čiarku na označenie,
že prichádza nová správa. Inak by bol XOScript zmätený.

```
Výstup písať: ['Hello!'], nový-riadok.
```

Najprv sa symbolu ceruzky pošle správa **písať:** a po nej
**nový-riadok**. Bez čiarky by si XOScript myslel, že chcete poslať
**nový-riadok** objektu **text** **Hello!**, čo by bolo zbytočné.

Poradie spracovania správ je nasledujúce: zľava doprava;
začína sa správami v zátvorkách, po nich nasledujú unárne správy. Ďalej
binárne správy a nakoniec kľúčové správy. Pozrite si príklad
nižšie:

```
Výstup písať: 0.5 zaokrúhliť + (2 - 1), nový-riadok.
```

XOScript vždy číta zľava doprava: najprv sa objektu Výstup pošle správa **písať:**
a po nej nasleduje správa **nový-riadok**. V rámci
samotného argumentu XOScript číta zľava doprava, takže najprv **0.5 zaokrúhliť**
a potom **+**.

{{note}}
Správa nový-riadok pridá k textu znak nového riadka.
Názov tejto správy je inšpirovaný telegrafnými systémami.
Správy v telegrafných systémoch 
často používali slovo STOP na označenie konca vety
(pretože interpunkcia bola nespoľahlivá alebo drahá).
{{/note}}

Navyše **zaokrúhliť** má prednosť pred **+**, pretože je to
**unárna správa**. Vzhľadom na zátvorky sa najprv vypočíta **2 - 1**,
potom sa **1** pripočíta k výsledku **0.5 zaokrúhliť** (1).

Celý proces dá výsledok **2**, čo je zároveň vypísaná
odpoveď. Za čiarkou nasleduje správa nový-riadok, ktorá presunie kurzor
na nový riadok. Poradie spracovania v programoch XOScript
samozrejme najlepšie úplne pochopíte praxou.

Stojí za zmienku, že v XOScript sú na rozdiel od mnohých iných programovacích
jazykov medzery základnou súčasťou syntaxe. Najmä
pri binárnych správach môžu medzery spôsobiť určitý
zmätok. Za binárnou správou vždy použite medzeru. Číslo nemôžete
pripojiť priamo k správe, napríklad: 

```
3 + 2
```

sa líši od 

```
3 +2
```

Prvý príklad (**3 + 2**) posiela
správu **+** číslu **3** s argumentom číslo **2**.
Výsledkom bude v tomto prípade **5**. V druhom príklade (**3 +2**)
sa číslu **3** posiela unárna správa **+2**. V závislosti od
kontextu to môže viesť k úplne inému výsledku.

## Neexistujúce metódy

Poslanie správy objektu vyvolá funkciu, ktorá bola
k tomuto objektu pripojená pod názvom tejto správy. Ak pošlete správu,
ktorej objekt nerozumie, prijímajúci objekt vašu správu ignoruje
a namiesto toho vráti odkaz na seba na ďalšiu komunikáciu.
Nazýva sa to tolerantné posielanie správ.

Príklad:

```
Výstup písať: Objekt blah, nový-riadok.
```

Nevyvolá to chybu. Jednoducho sa vypíše text **Objekt**.


## Riadenie toku

V XOScript nie sú potrebné samostatné gramatické pravidlá pre *cykly* a
*podmienky*. Príkaz if je len jednoduchá správa **pravda:** alebo **nepravda:**
poslaná objektu **Pravda** alebo objektu **Nepravda**:

```
2 párne? pravda: {
	Výstup písať: ['Two is an even number'], nový-riadok.
}.
```
V predchádzajúcom príklade sa správa **pravda:** posiela objektu **Pravda** (čo je
odpoveď na otázku: je 2 párne číslo?). Ako argument sa posiela aj ďalší
fragment kódu: objekt **Funkcia**. Táto funkcia vypíše na
obrazovku, že 2 je skutočne párne číslo.

Nie sú potrebné ani samostatné pravidlá zápisu pre *cyklus*. Ak chcete
vykonať fragment kódu trikrát, jednoducho pošlite **\*** s argumentom
**3** tejto **Funkcia**:

@test5

V tomto fragmente kódu je **i** index. Pri prvom vykonaní funkcie
sa teda **i** rovná 0, pri ďalšom vykonaní **i** = 1 a
tak ďalej.

Pozrime sa na ďalší príklad. Ak treba vypísať prevodnú tabuľku
z *kJ* (kilojoulov) na *kcal* (kilokalórie) po krokoch 100,
správny zápis nájdete nižšie:

@test599

Tu sa číslo aktuálneho riadka odovzdáva parametru
**:line**. Na začiatku funkcie sa definujú parametre
funkcie. Nepoužité parametre zostávajú prázdne (**Nič**). Parametre sú
vždy umiestnené na začiatku funkcie, priamo za úvodnou
zloženou zátvorkou, a predchádza im dvojbodka.

Správa **kým:** je kombináciou *cyklu* a *podmienky*.
Pomocou správy **kým:** možno prepojiť dve funkcie. Prijímajúca funkcia
bude bežať, kým funkcia za dvojbodkou nedá negatívny
výsledok. Príklad:

@test600

Vo vyššie uvedenom fragmente kódu sa k **x** pripočítava **1**, kým
je **x** menšie ako **5**. Keď to už neplatí, druhá
funkcia odpovie **Nepravda**, a preto sa vykonávanie
prvej funkcie skončí. Upozorňujeme, že **x** bolo definované mimo
funkcie a je globálnou premennou. Viac o pravidlách rozsahu platnosti
sa dozviete v kapitole o funkciách.

## Interpolácia textu

Zoznam *kJ/kcal* by mohol byť
prehľadnejší. Najlepšie by bolo, keby zoznam vyzeral takto:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Keď požadovaný výstup prevediete na šablónu, jej zápis
by mohol byť:

```
number1 kJ ➞ number2 kcal
```

To znamená, že **number1** zastupuje hodnotu v kJ a **number2**
hodnotu v kcal. Takto funguje interpolácia textu v XOScript. Na
to nie sú v XOScript potrebné žiadne samostatné gramatické pravidlá. Jednoducho
pošlite textu slovo, ktoré treba nahradiť, a ako argument
náhradný text:

```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

Výsledok:

```
100 kj ➞ 23.9 kcal
```

Toto pravidlo nahrádzania funguje pre každú nedefinovanú správu, ktorú
prijme objekt **text**. Každá správa, ktorú objekt **text**
nerozpozná, sa interpretuje takto: *nahraď text správy
textom v argumente správy.* Program môžete upraviť
takto:


@test601


Aby ste predišli nejasnostiam, ktorú správu možno alebo nemožno použiť ako
náhradu, je najlepšie zaviesť značku šablóny, napríklad &lt; &gt;,
pre textové úseky v šablóne, ktoré
treba nahradiť.

## Návratové hodnoty

Na odpoveď na správu sa používa návratová šípka
(*<-*). Nasledujúci príklad ukazuje, ako vytvoriť úlohu
na výpočet percenta:

@test602

Po definovaní úlohy a jej priradení premennej **percentage**
sa pošle správa **aplikovať:a:** s argumentmi **100** a **7**.

Tým sa vykoná úloha aplikovaná na **100** a **7**, t. j. 7 % zo 100.
Pomocou návratovej šípky sa odpoveď vráti z úlohy späť
do hlavného programu.

## Rozširovanie

Hoci je tento kód platný, má nevýhodu,
pretože si treba pamätať poradie argumentov. Prečo ho teda
nenapísať takto: *7 percent of: 100 *? Vyzeralo by to oveľa
*prirodzenejšie*. Aby to bolo možné, musíme upraviť rodičovský objekt
**7**, ktorým je objekt **Číslo**, tak, aby rozumel
správe **percent of:**. Dosiahneme to poslaním **pri:urobiť:**
objektu Číslo, takto:

@test603

Keďže percento je v tomto prípade samotné číslo, odkazujeme na seba,
kľúčovým slovom *seba*. Stručne povedané, symbol seba znamená: *pošli túto
správu mne samému*.

# Objekty

{{messages}}

Okrem úprav a rozširovania existujúcich objektov môžete aj sami vytvárať
nové objekty jednoducho tak, že pošlete správu **nový**. Predpokladajme, že
chcete vytvoriť objekt faktúry, ktorý vynucuje číselný
rad; v takom prípade budete najprv potrebovať objekt faktúry.

Keďže každý objekt je odvodený od iného objektu, ktorý zasa
v konečnom dôsledku pochádza z koreňového objektu všetkých objektov s názvom Objekt,
treba sa rozhodnúť, na ktorom z týchto ostatných objektov bude váš
nový objekt založený. Váš nový objekt zdedí všetky vlastnosti
objektu, na ktorom je založený, teda objektu, ktorému bola správa **nový**
pôvodne poslaná.

V tomto príklade je vhodnejší skôr neutrálny objekt, ktorý nemá príliš
veľa zdedených vlastností. Voľba je jednoduchá, pretože v takom
prípade môže byť nový objekt založený priamo na koreňovom objekte, ktorým je
**Objekt**. Zápis zamýšľaného systému faktúr potom bude
takýto:

@test604

Aktuálne číslo faktúry je uložené v objekte, a preto je pred ním
umiestnené kľúčové slovo **vlastný**. Nazýva sa to *vlastnosť*;
podrobnosti budú nasledovať.

Niektoré firmy uprednostňujú, aby čísla faktúr obsahovali rok.
V takom prípade môžete vytvoriť nový objekt faktúry založený na
predchádzajúcom objekte faktúry, ktorý však používateľovi ponúka možnosť
zadať konkrétny rok:

@test605

Implementáciu správy **číslo** netreba písať
znova, pretože sa dedí z predtým napísaného **objektu
faktúry**; starý kód tak možno opätovne použiť. XOScript nepozná koncepty
ako triedy a ďalšie súvisiace koncepty. To znamená, že objekty môžu
dediť výlučne od iných objektov, čo je známe aj ako *prototypová
dedičnosť*.

Teraz sa vráťme k vlastnostiam. K vlastnostiam objektu možno pristupovať
iba *v rámci hierarchie objektov*, takže tieto vlastnosti
nemôžu vnímať iné objekty.

Na rozdiel od iných programovacích jazykov sú všetky vlastnosti objektov
viditeľné výlučne pre objekt, ktorý vlastnosť vytvoril, a pre
odvodené objekty. 

Bežne používanou technikou je použiť objekt ako akýsi *plán*,
čo je napríklad prípad faktúr, o ktorých sme hovorili skôr.
Ďalším dobrým príkladom je **Point**. Povedzme, že vytvárate
počítačový program, ktorý robí výpočty pomocou bodov na mape. Môžete
vyvinúť objekt **Point** s vlastnosťami x-ovej súradnice a
y-ovej súradnice, ktoré budú sprístupnené
vonkajšiemu svetu prostredníctvom správ:

@test606

Správa **=** porovná dva body pomocou správy **a:**.
Prvé porovnanie vedie k hodnote **Pravda** alebo **Nepravda**. Sú to logické
objekty. Keď pošlete správu **a:** objektu Pravda a
objekt argumentu za dvojbodkou je tiež **Pravda**,
dostanete ako odpoveď opäť **Pravda**. Keď je ktorýkoľvek z nich **Nepravda**,
dostanete odpoveď **Nepravda**. Upozorňujeme, že jeden bod nemôže čítať súradnice
druhého. Je potrebné poslať druhému bodu správu a požiadať ho
o tieto údaje: **x-coordinate** a **y-coordinate**. Napokon, ako už bolo
vysvetlené, vlastnosti možno získať výlučne v rámci
samotnej rodiny objektov. 

Upozorňujeme, že na porovnanie bodov sa tu používa správa **=**.
Rovnako dobre sa mohla použiť iná správa, napríklad:
**is:** alebo **equal:**, opätovné použitie znaku **=** sa však v tomto prípade
zdalo vhodné.

## Dedičnosť

Predtým napísaný kód môžete opätovne použiť na vytvorenie hierarchie
objektov. Napríklad:

```
>> Animal := Objekt nový.
>> Dog := Animal nový.
>> Poodle := Dog nový.
```

V tomto prípade **Dog** dedí všetko správanie a vlastnosti
objektu **Animal** a objekt **Animal** zasa dedí všetko správanie objektu
**Objekt**, koreňového objektu všetkých objektov.


## Prepisovanie


V nasledujúcom príklade sa vytvára nový druh zoznamu:
**Combination**, v ktorom je zaručené, že každý prvok je jedinečný.
Funkcie zoznamu sa opätovne používajú prostredníctvom dedičnosti:

@test607

Všimnite si, že druhá **red** je zo zoznamu vylúčená.

Občas môže byť potrebné prepísať správanie objektu.
Napríklad pri sčítaní čísel, keď treba brať do úvahy jednotky
merania. V nasledujúcom príklade sa vytvára objekt **Size**.
Tento objekt vracia číslo, ktoré pri sčítaní
berie do úvahy jednotku pripočítavaného čísla. Objekt **Číslo**
kontroluje, či ide o *palce* alebo *stopy*. Programový kód
by mohol vyzerať nasledovne:

@test608

## Rekurzia

V predchádzajúcom príklade sa prepisuje **znak** plus. Upozorňujeme,
že konečné sčítanie sa nakoniec aj tak musí vykonať, čo sa v skutočnosti
deje na nasledujúcom riadku:

```
>> answer := seba + (číslo x factor).
```

Ako teda XOScript pochopí, že tento **znak** plus odkazuje na
pôvodnú logiku sčítania?** Iná interpretácia by napríklad
mohla byť, že XOScript bude opakovane posielať tú istú správu tomu istému
objektu, čo by zasa viedlo k **nekonečnému cyklu**. To zjavne
nie je zámer. Hneď ako pošlete objektu správu,
ktorá by vykonala presne ten istý kód, XOScript si v tomto prípade
uvedomí, že je myslená podkladová, prepísaná správa. Váš
program je tak automaticky chránený pred touto formou nekonečných
cyklov. Ak je však vaším cieľom skutočne spustiť tú istú funkciu z
aktuálnej funkcie, bude potrebné najprv poslať správu
**rekurzívny**. V takom prípade bude výsledkom nekonečný
cyklus. Rekurzívne úlohy však majú užitočné využitie,
predpokladajme napríklad, že chcete vypočítať faktoriál daného
čísla. V takom prípade jednoducho pridajte správu **factorial** objektu
Číslo:

@test609

To si vyžaduje rekurziu. Úloha spojená so
správou **factorial** sa totiž musí v rámci tejto funkcie vykonať znova.
Je teda potrebné vyvolať funkciu faktoriálu z
vnútra samotnej funkcie faktoriálu. XOScript tomuto postupu spravidla zabráni
pre riziko, že skončí v nekonečnom cykle. Z tohto dôvodu
je nevyhnutné, aby správe predchádzalo slovo **rekurzívny**. Robí
sa to preto, aby XOScript vedel, že je vaším
zámerom vykonať tú istú úlohu a že ste neurobili chybu.

## Objekty podobné triedam

Hoci xoscript neponúka triedy, napodobniť správanie podobné
triedam je triviálne. Jednoducho prepíšte správu nový.

```
>> Animal := Objekt nový.
Animal pri: ['nový'] urobiť: {
	<- seba nový inicializovať.
}.

Animal pri: ['inicializovať'] urobiť: {
	vlastný sound := ['?'].
	vlastný legs  := 4.
}.
```

Vo vyššie uvedenom fragmente kódu vytvárame objekt s názvom Animal.
Tento objekt slúži ako *plán* pre všetky druhy zvierat,
napríklad psy a mačky. Rodičovský objekt Animal je napísaný
s veľkým A, čo naznačuje, že ide o objekt podobný triede.
Ďalej prepíšeme správu nový tak, že napíšeme vlastnú metódu nový.
V tomto prípade pošle správu nový objektu seba a po nej správu
init. Keďže xoscript predvolene blokuje rekurziu, nespôsobí to
nekonečný cyklus. Namiesto toho pošle správu nový rodičovskému
objektu (Objekt), výsledkom čoho je nová inštancia objektu Animal. Vytvárame teda
nový objekt založený na tom istom objekte, pre ktorý sme vytvorili našu metódu nový.
Je to úplne platné. Teraz posielame aj správu init, ktorá zabezpečí,
že objekt Animal má predvolené hodnoty svojich vlastností. Predvolene
má zviera 4 nohy a zvuk je neznámy (preto otáznik).
Na vytvorenie novej inštancie nášho objektu Animal by sme mohli jednoducho napísať:

```
>> a := Animal nový.
```

Teraz dostaneme novú inštanciu objektu Animal so 4 nohami, neznámym zvukom a
metódou init. Rovnako ako v iných OOP jazykoch môžeme náš objekt Animal
aj rozšíriť:

```
>> Dog := Animal nový.
Dog pri: ['inicializovať'] urobiť: {
	seba inicializovať.
	vlastný sound := ['barks'].
}.
```

Ľahko to otestujeme pridaním metódy text:

```
Animal pri: ['text'] urobiť: {
	<- vlastný legs text + vlastný sound.
}.
```

Dajme to všetko dokopy:

@test13


Vytvorenie objektu, ktorý je nastavený do daného počiatočného stavu, predstavuje
častý problém. Predpokladajme, že treba vytvoriť objekt **Rectangle**
na výpočet obvodu a obsahu. Možný zápis by bol:


```
>> Rectangle := Objekt nový.

Rectangle pri: ['area'] urobiť: {
	<- vlastný dĺžka * vlastný width.
}.
```

Nastavenie dĺžky a šírky je zjavne predpokladom. Na tento
účel možno pridať správy **dĺžka:** a **width:**:


```
Rectangle pri: ['length:'] urobiť: { :dĺžka
	vlastný dĺžka := dĺžka.
}.

Rectangle pri: ['width:'] urobiť: { :width
	vlastný width := width.
}.

```

Tento obdĺžnik potom možno použiť takto:


```
>> rectangle := Rectangle nový length: 2, width: 3.
Výstup písať: rectangle area.
```

Ak sa však počiatočné nastavenie dĺžky a šírky prehliadne,
objaví sa chybové hlásenie:

```
>> rectangle := Rectangle nový.
Výstup písať: rectangle area.
```

vyvolá nasledujúcu chybu:

```
Kľúč nebol nájdený:dĺžka
```

Aby sa tomu predišlo, je vhodnejšie, aby obdĺžnik mal
vždy počiatočnú dĺžku a šírku, napríklad 0. V tomto
prípade je teda potrebné **prepísať** správu **nový**.

@test610

Ak prepíšeme správu nový, v podstate napodobňujeme **triedu**.

Svet XOScript je plný rozmanitých objektov, ktoré sú
vášmu programu k dispozícii hneď od začiatku. V nasledujúcich kapitolách
budú opísané všetky tieto základné objekty.

## Snímky

Objekt (spolu s jeho aktuálnym stavom) môžete uložiť na disk pomocou:

```
myobject save-as: ['saved.bin'].
```

Na opätovné načítanie objektu z disku:

```
>> myobject := Objekt load-from: ['saved.bin'].
```

Snímky možno použiť na uloženie určitého stavu alebo na zlepšenie výkonu.
Načítanie snímky vynecháva lexikálnu analýzu, parsovanie a nastavenie aplikácie.
V budúcnosti môžu byť so snímkami zavedené aj ďalšie výhody
výkonu, napríklad optimalizácia určitých vzorov alebo detekcia a
optimalizácia horúcich ciest.

{{warning}}
Snímky sú experimentálna funkcia, nepoužívajte ich v produkcii.
Na aktiváciu experimentálnych funkcií kompilujte s -D EXPERIMENTS.
{{/warning}}


@test712

# Objekt Nič

{{messages}}

Objekt Nič
predstavuje prázdnotu, alebo ešte lepšie, absenciu informácie.
Občas dostanete tento objekt ako odpoveď na správu
v prípade, že výsledkom je **nič**. Najzákladnejšia otázka,
ktorú môžete objektu **Nič** položiť, je: **Nič?**.
Odpoveď bude vždy **Pravda**.

```
Výstup písať: Nič Nič?.
```

výsledok:

```
Pravda
```

Každý iný objekt ako **Nič** odpovie **Nepravda**.
Vyššie uvedený fragment kódu sa môže zdať trochu filozofický, objekt **Nič**
má však určite mimoriadne praktické využitie. Objekt Nič napríklad
dostanete ako odpoveď, ak požiadate o
prvok zoznamu, ktorý neexistuje. Objekt Nič môžete použiť aj vtedy,
ak chcete deklarovať premennú, ale ešte nechcete určiť jej
hodnotu. Namiesto toho jednoducho **priradíte** špeciálnu hodnotu **Nič**.
V XOScript nie je dovolené deklarovať premennú bez hodnoty, napríklad:


```
>> hodnota.
```

Namiesto toho musíte napísať nasledujúce:

```
>> hodnota := Nič.
```

@api_None_base

# Logické hodnoty

{{messages}}

Na rozdiel od väčšiny populárnych programovacích jazykov v čase písania
poskytuje XOScript iba jediný objekt Pravda a jediný objekt
Nepravda. Pre objasnenie: zakaždým, keď napíšete **Pravda**, neznamená to,
že sa vytvoril nový objekt. Namiesto toho vždy používate odkaz. To
znamená, že keď napíšete nasledujúce:

\>\> x := Pravda.

**x** odkazuje na objekt **Pravda**. Podmienený kód a cykly tiež
overujú tento odkaz. V XOScript nie je význam objektov **Pravda** a **Nepravda**
pevne daný. Program v XOScript totiž poriadne otrasie
príkaz, ako je tento:

Pravda := Nepravda.

Výsledok takýchto akcií nie je definovaný, zostáva to však platná
akcia, a preto je formálne povolená. Okrem toho existuje objekt
Logický, ktorý je koreňovým objektom pre **Pravda** aj **Nepravda**, keďže oba
sú odvodené od tohto koreňového objektu. Samotný objekt Logický však
nemá žiadne praktické využitie.

## Úskalia

Pri používaní **a:** a **alebo:** buďte opatrní

```
Výstup písať: (Nepravda or: Pravda or: Pravda), nový-riadok.
Výstup písať: (Nepravda alebo: Pravda, alebo: Pravda), nový-riadok.
```

Výsledkom je

```
Nepravda
Pravda
```
pretože správa **alebo:** prijíma iba 1 argument. Prvý riadok
posiela objektu Nepravda správu **alebo:alebo:**, ktorá neexistuje, takže objekt
správu ignoruje a vráti sám seba (Nepravda). Druhý riadok naopak
posiela **alebo:** a po ňom ďalšiu **alebo:** (pomocou symbolu reťazenia, t. j. čiarky: ,).


@api_Boolean_base

# Čísla

{{messages}}

Zakaždým, keď napíšete číslo, napríklad 9, -10 alebo 3,12, XOScript
ho v pozadí prevedie na objekt **Číslo**.
Tomuto objektu Číslo môžete posielať správy, alebo môžete číslo
priradiť premennej a správy posielať až potom:

```
10 párne?

>> tenner := 10.
tenner párne?

```

Oba zápisy sú platné. Objekt Číslo reaguje na nasledujúce
správy...

Väčšina týchto správ je samovysvetľujúca a umožňuje vykonávať
matematické operácie alebo porovnania.

{{note}}
Upozorňujeme, že namiesto ich ASCII náprotivkov môžete používať ≤ ≥ ≠ × a ÷.
Je to vec preferencie.
{{/note}}

Rozdiel medzi binárnymi matematickými správami (+) a
ich kľúčovými variantmi (pridať:) je v tom, že prvé vrátia
nové číslo, ktoré je výsledkom operácie, zatiaľ čo pri
druhých sa zmení samotný objekt. Ilustruje to
nasledujúci príklad:

@test597

Vo vyššie uvedenom príklade b = 4 a a = 3. Pomocou **pridať: 2** sa hodnota
a zvýši o 2, zatiaľ čo **+ 3** vytvorí nové číslo, ktoré sa
rovná a + 3. To isté platí aj pre iné matematické operácie, napr.
násobenie. Použitím symbolu násobenia dostanete ako odpoveď
nový objekt. Ak použijete správu **vynásobiť:**,
vynásobíte samotné číslo.

Pomocou správy **medzi:a:**, napríklad v: **Číslo
medzi: X a: Y**, dostanete číslo medzi X a Y. Týmto
spôsobom možno vygenerovať ľubovoľné náhodné číslo:

```
>> a := Číslo medzi: 1 a: 10.
Výstup písať: a, nový-riadok.
```

Od verzie 1.4 je vstavaný generátor náhodných čísel v xoscript
podľa našich najlepších vedomostí kryptograficky bezpečný.

K číslu môžete pripojiť **jednotka**, napríklad **6
jabĺk**. Každá správa, ktorú číslo nerozpozná,
sa bude považovať za jednotku. Jednotku
čísla môžete získať pomocou správy jednotka:

Jednotka je v podstate objekt Text, ktorý je uložený spolu s objektom
Číslo. Jednotka sa vypíše aj za číslom pri
priradení **písať:**. Jednotky možno použiť napríklad na sčítanie súm
v rôznych menách. Pri sčítaní súm sa môžete opýtať
na jednotky. Nasledujúci príklad programu ilustruje tento
princíp pomocou historickej kalkulačky mien (keďže výmenný
kurz zostáva pomerne stabilný!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Texty

{{messages}}

Zakaždým, keď umiestnite text medzi **hranaté zátvorky a úvodzovky** ['...'],
XOScript pre vás vytvorí nový textový objekt. Dbajte však
na použitie správnych úvodzoviek. Úvodzovka na
začiatku textu sa líši od úvodzovky na konci (vďaka tomu môžete
používať apostrof bez nutnosti ho escapovať).

## UTF8

Texty v xoscript zvyčajne obsahujú text v kódovaní utf8. Hoci
je technicky možné mať v texte binárny obsah alebo obsah, ktorý nie je v utf8,
odporúča sa na to používať bloby. Bloby
poskytuje serverový plugin (pozri kapitolu ffi).
Vo všeobecnosti sa bloby/ffi poskytujú
na úrovni pluginu/platformy, pretože sú viazané na platformu
a architektúru (ffi/bloby). Jadro skriptovacieho jazyka sa snaží
zostať čo najviac nezávislé od platformy.

## Pretypovanie

Pomocou nasledujúcich správ môžete vytvoriť kópiu každého objektu
s iným typom:

Správa  | Výsledok
------- | ------
číslo   | Prevedie na číslo
text    | Prevedie na text
logický | Prevedie na logickú hodnotu
  
Platia nasledujúce **pravidlá**:

správa   | Nič       | Logický            | Číslo                 | Text      | Iné              
-------- | --------- | --------           | --------              | --------  | --------
logický  | Nepravda  | n/a                | 0→Nepravda inak→Pravda | Pravda   | Väčšinou Pravda
číslo    | 0         | Nepravda→0 Pravda→1 | n/a                  | ['n']→n | Väčšinou 1
text     | ['Nič']   | ['Nepravda']/['Pravda'] | ['n']            | n/a       | Závisí od objektu

## Kopírovanie

Hodnoty sa v XOScript vždy odovzdávajú **odkazom**. V iných jazykoch
to závisí od typu hodnoty, v XOScript existuje iba jeden spôsob,
odkazom. XOScript nikdy nevytvára kópiu hodnoty. Ak chcete objekt skopírovať,
musíte poslať správu **kopírovať**. 

@test611

Tu ste možno očakávali, že výstupom bude Dolly namiesto
Donny. Nie je to však tak, pretože obe mená odkazujú na ten istý
objekt. Pri práci s cyklom nastáva niečo podobné:

@test612

XOScript totiž **vždy** používa odkazy, takže pri **:quantity**
vyššie znázornený cyklus tiež označuje odkaz na prvok
v zozname.

Ak chcete objekt skopírovať, musíte túto akciu určiť
**explicitne**:

@test613

Poslaním unárnej správy **kopírovať** textu objekt
vráti kópiu toho istého textového objektu. Rovnakým spôsobom je možné kopírovať objekty
Číslo, logické objekty, zoznamy a slovníky.

Môžete tiež definovať vlastnú implementáciu kopírovania; ak vytvárate
vlastné objekty, je to dokonca nevyhnutné. Predvolená
implementácia kopírovania pre zoznam vytvára plytkú kópiu, teda
nový zoznam s rovnakými prvkami.

@test614

V tomto prípade sa 4 pridá iba do kópie.
Keďže je však kópia plytká, objekty v oboch zoznamoch
sú tie isté.

@test615

Ak teda ku každému menu v kópii pripojíme 2, ovplyvní to
aj pôvodný zoznam.

Na nápravu potrebujeme vytvoriť **hlbokú kópiu**. Takáto akcia kopírovania
pre zoznam by mohla vyzerať takto:

@test616

Všimnite si aj správu rekurzívny; túto správu je potrebné
poslať pred správou kopírovať.

Je nevyhnutné mať na pamäti, že hoci kópia objektu
často vyzerá rovnako ako originál, v skutočnosti
nikdy nebude tým istým objektom. Koreňový objekt definuje správu **equal:**,
ktorú možno použiť na porovnanie identity objektov. Pozrite si
nasledujúci príklad:

@test617

## Implicitná konverzia

XOScript používa na konverziu objektov **implicitnú konverziu**. Ak má
napríklad vypísať zoznam na obrazovku, XOScript interne pošle zoznamu správu
*text*. To sa môže ukázať ako veľmi užitočné v
prípade, že chcete zoznam vypísať ako zoznam oddelený čiarkami.
Správu *text* možno prepísať: 

@test620

@api_String_base
@api_Format_base


## Serverové texty

Nasledujúce funkcie objektu Text pridáva
serverový plugin.

@api_String_server

# Funkcie

{{messages}}

Kód môžete zoskupiť medzi { a }, čím sa z neho stane funkcia.
V xoscript niekedy používame aj pojem úloha alebo jednoducho
blok kódu.

Funkciu môžete spustiť poslaním správy *spustiť*.


```
{ Výstup písať: 123, nový-riadok. } spustiť.
```

Ak vaša funkcia prijíma argumenty, použite **aplikovať:**.

```
{ :a Výstup písať: a, nový-riadok. } aplikovať: a.
```

Pozrite si aj príklady nižšie.
Vzhľadom na zjednodušenú architektúru môže mať funkcia iba
jeden návratový bod. Aby ste sa vyhli réžii alebo nadmernému vnáraniu
podmienok, môžete použiť procedúru (čo je to isté ako použitie
znaku násobenia s argumentom 1):

```
{
  (a = 1) pravda: { x := 1. }, prerušiť.
  (a = 2) pravda: { x := 2. }, prerušiť.
} procedúra.
```

Takto sa (a = 2) nevyhodnotí, ak a = 1.
Takto tiež nepotrebujete vnorené správy pravda.
Kedykoľvek zistíte, že vnárate podmienky, spomeňte si
na správu procedúra. Môže to váš kód
sprehľadniť.


Tu je dôležité úskalie:

```
{
	Nepravda nepravda: {
		Výstup písať: ['End the loop.'].
	}, prerušiť.
	
	Výstup písať: ['Dont show me.'].

} procedúra.

```

V tomto prípade sa zobrazí text 'Dont show me'.
Pretože **prerušiť** sa posiela objektu Nepravda. Ak chcete vykonať
prerušenie, musí sa poslať ako správa objektu **Pravda**.
 

```
{
	Nepravda nie pravda: {
		Výstup písať: ['End the loop.'].
	}, prerušiť.
	
	Výstup písať: ['Dont show me.'].

} procedúra.

```

Bude fungovať podľa očakávania.

## Výnimky

Výnimky možno spracovať takto:

```
{ Task 1 } zachytiť: { Task 2 }, spustiť.
```

Vo svojom programe môžete aj zámerne vyvolať chybu a
tým aktivovať blok obsluhy. Robí sa to poslaním
správy **chyba:** aktuálnej úlohe, ako je znázornené na nasledujúcej
ilustrácii:

```
{
táto-úloha chyba: ['Whoops!'].
} zachytiť: { :mistake
Výstup písať: mistake.
}, spustiť.
```

## Vkladanie hodnôt

XOScript ponúka pre úlohy možnosť vkladať hodnoty. Pozrite sa
na úlohu nižšie:

```
>> sending := {
	Newsletter komu: vlastný recipient.
}.
sending nastaviť: ['recipient']
hodnota: ['info@recipient.org'].
sending spustiť.
```


Táto ilustrácia predstavuje imaginárnu úlohu, ktorá posiela newsletter
na e-mailovú adresu alebo **príjemcovi**. Tohto príjemcu možno vložiť
do úlohy zvonka a pred spustením úlohy, a to poslaním
správy **nastaviť:hodnota:** úlohe. Tým sa hodnota
**recipient** v úlohe vopred nastaví. Túto hodnotu možno tiež zmeniť
a úlohu potom spustiť znova. Je to užitočná metóda pri používaní
objektov Task.

## Prázdne funkcie

Prázdne úlohy nie sú povolené. Teoreticky by prázdna úloha vyzerala
takto: **{}**, XOScript to však považuje za jazykovú chybu. Ak
chcete deklarovať prázdnu úlohu, môžete použiť objekt Nič:

```
>> task := Nič.
```

Hoci to nie je skutočná úloha, ale objekt Nič, správu spustiť
mu stále možno poslať:

```
>> answer := task spustiť.
```

V skutočnosti je to to isté ako:

```
>> answer := Nič spustiť.
```

Keďže objekt **Nič** nerozpozná správu **spustiť**,
vráti ako odpoveď sám seba, takže odpoveďou je opäť **Nič**.
Nie je teda potrebné mať prázdnu úlohu. Vďaka elegantnému
návrhu programovacieho jazyka XOScript môžete na to jednoducho použiť objekt
Nič.

## Dynamický rozsah platnosti

Keď funkcia potrebuje premennú, ale nemôže ju nájsť,
skontroluje premenné funkcie, ktorá ju **zavolala**,
a pokračuje v kontrole ďalej po reťazci funkcií.
Tento proces hľadania pokračuje, kým sa premenná nenájde.
Ak sa premenná ani potom nenájde, zobrazí sa chybové hlásenie. Tento spôsob hľadania
premennej sa nazýva **dynamický rozsah platnosti**.

Na ilustráciu tohto princípu:

@test618

@api_Code_base

# Koreňový objekt

{{messages}}

Objekt s názvom **Objekt** je koreňovým objektom všetkých objektov v
XOScript a poskytuje základné funkcie jazyka. 

Najčastejšie posielanou správou
je **pri:urobiť:**, ktorá rozširuje funkcie objektu. Túto
správu prijíma koreňový objekt, ktorý následne prepojí
zadanú úlohu so správou, a tým rozšíri odvodený
objekt.

## Metódy zachytávajúce všetko

Ak pošlete správu, ktorá nezodpovedá žiadnej
metóde objektu, zvyčajne sa ignoruje. Môžete však určiť
takzvané **magické metódy** alebo metódy **zachytávajúce všetko**, ktoré sa
vyvolajú, ak objekt správe nerozumie.

K dispozícii sú 4 metódy zachytávajúce všetko. Každá správa zodpovedá
určitému počtu argumentov.

Zachytávajúca správa | Počet argumentov
-------------------- | -------------------
odpovedať:           | 0
odpovedať:a:         | 1
odpovedať:a:a:       | 2
odpovedať:a:a:a:     | 3


@test619

## Programové správy

Namiesto priameho poslania správy objektu ju možno
poslať aj prostredníctvom premennej. Na to použijete správu
**správa:argumenty:**. 

@test396

@api_Object_base

# Zoznamy

{{messages}}

XOScript pozná dva typy kolekcií: *zoznamy* a *slovníky*.
**Zoznamy** sú výpočty objektov v *pevnom poradí*. Slovníky nemajú
žiadne poradie, namiesto toho pripomínajú legendu s kľúčom (alebo pojmom) a jeho
zodpovedajúcou hodnotou. Zoznamy sú porovnateľné s poľami (PHP, Java, C)
a zoznamami (Python). Slovníky sú porovnateľné s asociatívnymi poľami (PHP) alebo
slovníkmi (Python) v iných programovacích jazykoch. Na vytvorenie
nového objektu Zoznam napíšte:

```
>> fibonacci := Zoznam nový.
```

Tento prázdny zoznam možno naplniť pomocou **pripojiť:** :

```
fibonacci pripojiť: 0.
fibonacci pripojiť: 1.
fibonacci pripojiť: 1.
fibonacci pripojiť: 2.
fibonacci pripojiť: 3.
fibonacci pripojiť: 5.
fibonacci pripojiť: 8.
fibonacci pripojiť: 13.
```

Ak zoznam vypíšeme na obrazovku:

```
Výstup písať: fibonacci, nový-riadok.
```

Uvidíme:

```
Zoznam ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

Namiesto pripojiť môžete na pridanie prvkov do zoznamu použiť aj ;:


```
>> fibonacci := Zoznam nový ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Bodkočiarky (;) sú všetko binárne správy, ktoré vkladajú
hodnotu do zoznamu.

## Reťazenie

Predpokladajme, že máte takýto zoznam:

```
>> x := Zoznam nový ; 1 ; 2 ; 3.
```

Ak by ste chceli vymazať prvý a posledný prvok, vaša
správa by bola:

```
x vybrať-prvý vybrať-posledný.
```

Predchádzajúci zápis bohužiaľ nebude fungovať správne.
Správa **vybrať-prvý** vráti prvý prvok zoznamu, ktorý sa
následne stane príjemcom správy **vybrať-posledný**. Správa
**vybrať-posledný** sa teda neposiela objektu **x**, ale namiesto toho objektu 2.
Možným riešením tohto problému by bolo vytvoriť dve samostatné
vety, napríklad: 

```
x vybrať-prvý.
x vybrať-posledný.
```

To je však dosť nepraktické, najmä keď potrebujete
vymazať viac ako dva prvky. Preto XOScript ponúka
alternatívnu štruktúru správ pre takéto situácie. V
**alternatívnych** štruktúrach správ sa odpovede objektov ignorujú
a ako odpoveď dostávate zakaždým späť prijímajúci objekt.
**Alternatívna** štruktúra správ sa začína poslaním
správy **robiť** objektu a **alternatívnu** štruktúru
správ možno ukončiť poslaním správy **hotovo**. V
uvedenom príklade by sa to dalo použiť takto:

```
>> x := Zoznam nový ; 1 ; 2 ; 3.
x robiť vybrať-prvý vybrať-posledný hotovo.
```

@api_List_collections

# Slovníky

{{messages}}

**Zoznam aj Slovník sú kolekcie. Na rozdiel od
zoznamu však slovník **nemá** žiadne poradie. Ďalší rozdiel medzi nimi
je, že slovník sa skladá z dvojíc objektov. Jeden objekt slúži ako heslo (alebo
kľúčové slovo) na vyhľadanie druhého objektu. Dobrým príkladom
takého zoznamu je cenník, napríklad:


```
>> menu := Slovník nový
	umiestniť: ['£5'] na: ['apple pie'],
	umiestniť: ['£6'] na: ['carrot cake'],
	umiestniť: ['£3'] na: ['fudge'].
```

Podobne ako pri zozname sa na pridanie objektu do zoznamu používa
správa umiestniť:na:. Rozdiel je v tom, že na rozdiel od
zoznamu sa prepájajú dva objekty. Prvý objekt je, podobne
ako pri zozname, objekt, ktorý uložíte do zoznamu. Druhý
objekt nie je jeho pozícia v kolekcii, ale **heslo**,
ktoré umožňuje predchádzajúci objekt neskôr získať. Stručne
povedané, slovník funguje trochu ako výkladový slovník; pomocou kľúčového slova
možno nájsť význam. Napríklad na získanie ceny karamelky
z vyššie uvedeného zoznamu:

```
>> price := menu na: ['fudge'].
```

Môžete použiť aj stručný zápis:

```
>> price := menu ? ['fudge'].
```

Ak heslá, ktoré používate na ukladanie objektov, neobsahujú medzery
(a nekolidujú s inými preddefinovanými správami),
možno použiť aj nasledujúci zápis:

```
>> menu := Slovník nový
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Niet pochýb, že vyššie uvedený zápis sa číta o niečo prirodzenejšie.
Na zistenie ceny
karamelky možno použiť nasledujúci zjednodušený zápis:

```
>> price := menu fudge.
```

@api_Dict_collections

# Súbor

{{messages}}

Objekt **Súbor** poskytuje základný prístup k súborovému systému.
Pomocou tohto objektu môžete naraz načítať celé súbory do premennej
alebo naraz zapísať premenné do súborov. Podporované je aj čítanie
po riadkoch. Sú to najbežnejšie súborové V/V operácie
v skriptovacom jazyku. Pokročilé súborové operácie vyžadujú
použitie FFI prostredníctvom serverového pluginu alebo samostatného IO pluginu.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Dátum/Čas

{{messages}}

Na štruktúrovanú reprezentáciu času a dátumu používa XOScript
objekt **Okamih**. Ak sa na obrazovku vypíše nový objekt Okamih,
zobrazí sa aktuálny dátum a čas:

```
Výstup písať: Okamih nový, nový-riadok.
```

Výsledok môže vyzerať napríklad takto:

```
2020-10-10 12:16:39
```

Jednotlivé zložky času je tiež ľahké prečítať. Ak je
napríklad potrebné poznať iba aktuálny rok, okamihu možno
poslať správu **rok** a odpoveďou bude
objekt Číslo obsahujúci iba rok:

```
>> m := Okamih nový.
Výstup písať: m rok, nový-riadok.
```

@api_Moment_system

# Program/Štandardný výstup

{{messages}}

Objekt Program predstavuje práve bežiacu aplikáciu. Tento objekt
ponúka funkcie na vykonávanie systémových príkazov, vkladanie podprogramov,
čítanie argumentov a ďalšie. Všetky funkcie súvisiace so systémom.

## Štandardný výstup

Výstup je objekt štandardného výstupu. V podstate má dve metódy:
**písať:** a **nový-riadok**. Správa písať: sa používa na poslanie textu
na stdout, správa nový-riadok vypíše znak nového riadka.
Namiesto **nový-riadok** môžete použiť aj \\n.

Príklad:

```
Výstup písať: ['Hello World'], nový-riadok.
```

výsledok:

```
Hello World
```

## Moduly/Pluginy

Svet XOScript možno rozšíriť o nové systémové objekty
inštaláciou modulov. Nový systémový objekt možno do sveta
XOScript pridať umiestnením súboru modulu (zvyčajne súboru s príponou .so
) do priečinka mods. 

Keď pošlete správu objektu, ktorý je sprístupnený prostredníctvom
modulu pluginu, XOScript ho automaticky načíta.

Pluginy môžete písať aj sami. Pluginy sa píšu v
programovacom jazyku C. Príklad pluginu nájdete v balíku zdrojového
kódu v src/plugins/example.


## Reflexia

Existujú rôzne spôsoby skúmania
systému počas vykonávania programu. XOScript má niekoľko metód na
zistenie, ktoré objekty sú prítomné a na ktoré správy tieto objekty
reagujú. Po prvé, každého objektu sa možno opýtať, aký má **typ**,
typy v XOScript sú však meniteľné, a preto nespoľahlivé.

Objektu Program sa tiež možno opýtať, či je
daný objekt v programe už prítomný:

```
Program Tool pravda: { ... }.
```

V prípade názvu objektu,
ktorý sa skladá z jediného symbolu, je najlepšie použiť
nasledujúci zápis, aby sa predišlo nejasnostiam:

```
Program nájsť: ['X'], pravda: { ... }.
```

Okrem otázok na objekty sa objektu Program možno rovnako
pýtať aj na správy. Možno sa napríklad opýtať, či
objekt **Číslo** pozná správu **medzi:a:**, spôsobom,
ktorý je znázornený nižšie:

```
Program Number: ['between:and:'], nový-riadok.
```

@api_Program_system

# server

{{messages}}

Serverový plugin v xoscript ponúka funkcie na
vytváranie serverových aplikácií. Na načítanie serverového
pluginu použite:

```
Server inicializovať.
```

Pre vaše pohodlie sa odporúča načítať aj
súbory webtools.xo a template.xo.

```
Program použiť: ['webtools.xo'].
Program použiť: ['template.xo'].

```

## Nastavenia servera

Môžete nastaviť nasledujúce nastavenia servera:

```
	# default values are given
	# so if you do not set anything these
	# values are used...

	Program 
	nastavenie: ['max-postfields']
	hodnota: 40.

	Program 
	nastavenie: ['max-contentlength']
	hodnota: 2000000. # 2MB

	Program 
	nastavenie: ['max-time']
	hodnota: 5000. # 5sec

```

## Hello World

Tu je veľmi jednoduchý webový program, ktorý môžete použiť so
štandardným CGI serverom, ako je Apache2, NGINX, OpenHTTPD, alebo s akýmkoľvek iným
známym serverom.

```
#!/bin/xo

Server inicializovať.
Program použiť: ['webtools.xo'].

>> web-document := Webový-dokument nový.

web-document vypísať: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Ak nechcete používať objekt Webový-dokument, nevadí, ale
potom musíte HTTP hlavičky napísať sami:

```
#!/bin/xo
Výstup písať: ['Content-type: text/html; charset=utf-8 \n\n'], nový-riadok.
Výstup písať: ['hello world!'], nový-riadok.
``` 

## Požiadavka

Objekt HTTP-Požiadavka možno použiť na získanie údajov GET/POST/COOKIE a
UPLOAD:

```
>> požiadavka  := HTTP-Požiadavka nový.
>> search   := požiadavka get: ['search']. # ?search=books
>> password := požiadavka post: ['password']. # from form
>> selected := požiadavka get-zoznam: ['sel[]']. #?sel[]=1&sel[]=2
>> selected := požiadavka post-zoznam: ['sel[]'].
>> cookie   := požiadavka cookie: ['session-id'].
>> upload   := požiadavka upload: ['file'].
>> temppath := upload ? 1.
>> filename := upload ? 0.
```

## Maxpost/length

Predvolený maximálny počet polí POST je 40 a predvolená maximálna dĺžka
obsahu je 2MB. Na odlišné nastavenie pre jednotlivé skripty:

```
Program nastavenie: ['max-contentlength'] hodnota: 1. 
Program nastavenie: ['max-postfields'] hodnota: 1. 
```

{{note}}
Ak dĺžka obsahu prekročí maximum,
proces sa ukončí, pretože už nemôžeme mať istotu,
že je obsah bezpečný.
{{/note}}

Limit maxtime určuje maximálny čas v ms
na čítanie stdin/postdata.

```
Program nastavenie: ['max-time'] hodnota: 5000. # 5sec
```

Platí to iba pre V/V čítanie údajov POST a zabraňuje
útokom typu slowloris. Ak naozaj chcete obmedziť
čas vykonávania akejkoľvek operácie, použite Program budík:.

## Databáza

Objekt Database možno použiť na dopytovanie MariaDB/MySQL.
Na pripojenie k databáze urobte:

```
>> db := Maria-DB nový hostiteľ: ['localhost'],
	používateľ: ['xo'],
	heslo: ['pass123'],
	názov-databázy: ['xobase'],
	pripojiť-sa.

```

Na vloženie záznamu použite:

```
>> parametre-hľadania := db dopyt: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parametre: ( Zoznam nový ; ['abc'] ; 12.35 ; 6 ). # parameterized queries

{  parametre-hľadania vykonať. db potvrdiť. }
zachytiť: { :e db vrátiť-späť.  }, spustiť.
```

Upozorňujeme, že xoscript pracuje *iba* s transakciami a nikdy nepoužíva autocommit.
Ak autocommit nemožno vypnúť, dostanete chybu pripojenia.
Pri dopytoch vždy používajte viazanie parametrov, nikdy nepridávajte vstup používateľa priamo
do SQL.

ID vloženého záznamu získate takto:

```
Výstup písať: ['INSERTED: '] + parametre-hľadania insert-id, nový-riadok. # insert id
```

Na načítanie záznamov:

```
>> parametre-hľadania :=
db
	dopyt: ['SELECT * FROM book order by id desc limit 2'], 
	načítať: { :row 
		Výstup písať: row id + [' '] + row description + [': '] + row price, nový-riadok.
	}. # fetching rows

```

## Relácie

Na zachovanie údajov môžete ukladať a načítavať údaje z objektu relácie.
Najprv vytvorte nový **Webový-dokument**. Objekt Webový-dokument spája
požiadavku, hlavičky, HTML a reláciu. Je to preto, že keď
navštívite webovú stránku v prehliadači, vidíte iba HTML. Celý
Webový-dokument sa však skladá aj z **hlavičky**. Napríklad
väčšina HTTP odpovedí obsahuje hlavičku ako: Content-type:text/html, ktorá
prehliadaču oznamuje, že nasledujúce údaje sa majú zobraziť ako HTML
(a nie napríklad stiahnuť ako súbor). Relácie sú spôsob, ako
uchovávať údaje používateľa medzi požiadavkami. Na sledovanie týchto údajov musíme
nastaviť cookie a aj táto cookie sa nastavuje prostredníctvom hlavičky. Preto
sa všetko stretáva vo Webový-dokument (pretože je to úplný
dokument obsahujúci hlavičky aj HTML alebo iné údaje).


```
# First we make a new Web Document instance
>> web := Webový-dokument nový.

# Now we start a session, this will generate a Header for a cookie and
# create a file to store your data, associated with that cookie
>> session := web začať-reláciu.

# Now we can treat session like a dict
session userid: 123.
```

Na zničenie relácie (pri odhlásení):

```
web zničiť-reláciu.
```

## Hlavičky

Webový-dokument vám tiež umožňuje nastaviť ďalšie známe hlavičky.
Napríklad ak chcete používateľa presmerovať na inú URL:

```
web prejsť-na: ['/other.html'].
```

Tento príkaz pod kapotou vygeneruje aj HTTP hlavičku, ktorá sa pošle
spolu s vašimi ďalšími údajmi alebo HTML a prehliadaču prikáže prejsť
na zadanú cieľovú adresu.

Na pridanie vlastnej hlavičky:

```
web hlavička: ( 
	HTTP-Hlavička nový
	kľúč: ['Content-Length']
	hodnota: 400
).
```

Na zobrazenie stránky 404:

```
web nenájdené: ['OOps..'].
```


## Šablóny

Predvolený šablónový systém je veľmi jednoduchý. Nemusíte sa učiť
novú šablónovú syntax. Šablónovací systém navyše zaručuje skutočné oddelenie
prezentácie od obchodnej logiky.

Na vytvorenie šablóny zo súboru:

```
>> tpl := web šablóna: ['templates/ux.tpl'].
```

Šablónový systém používa značky. 
Existujú tri typy značiek: značky výrezu, značky vloženia a
značky slotov. Základná myšlienka je naozaj jednoduchá: vystrihnete
oblasti označené značkami výrezu a môžete ich vložiť do
oblastí označených značkami vloženia. Do značiek slotov môžete vkladať
texty.

Napríklad pri nasledujúcej šablóne vložme
drahokam do šperkovnice a pridajme cenovku.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Môžete to urobiť takto:

```
>> gem := tpl vystrihnúť: ['gem'], kopírovať.
gem price: 99.
tpl vložiť: gem na: ['jewels'].
web vypísať: tpl očistiť.
```

Posledný riadok jednoducho odošle šablónu ako text klientovi
spolu s požadovanými HTTP hlavičkami.

Výsledok:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

Na bezpečné poskytovanie súborov nahraných používateľmi sa môžete spoľahnúť na passthru:

```
>> uploaded := ['smile.gif'].
Server odovzdať: uploaded prefix: ['/uploads/images/'].
Program koniec.
```

Takto sa obsah nahraný používateľom poskytne so zodpovedajúcim
MIME typom. Podporované sú iba MIME typy na zozname povolených:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF a SVG.
Súbory SVG, ZIP a GZIP sa posielajú na stiahnutie, pretože SVG
môže obsahovať skripty, ktoré by sa inak spustili na vašej doméne.
Táto metóda zabraňuje útokom TOCTOU, prechádzaniu ciest,
vykonaniu škodlivého kódu (injekcii), útokom cez symbolické odkazy,
DDoS útokom (limit súboru = 50MB), útokom odpočúvaním a
rôznym ďalším bezpečnostným problémom.


## JSON

Na zakódovanie objektu ako JSON:

```
>> json := ( JSON jsonify: ( 
	Slovník nový umiestniť: ( 
		Zoznam nový ; 1 ; 2 ; 3
	) na: ['abc']
)).
```

Na dekódovanie JSON do objektu xoscript:

```
>> dict := ((JSON objekt: json) abc ? 1).
```

JSON s viac ako 500 úrovňami vnorenia sa odmietne ako neplatný.

Na priamy výstup objektu Slovník ako json so správnymi hlavičkami:

```
web json: dict.
```


## Regulárne výrazy

Regulárne výrazy môžete používať vytvorením vzoru.
Napríklad na zachytenie atribútov href a target hypertextových odkazov:

```
Vzor nový: ['href="([^"]+)" target="([^"]+)"'].
```

Teraz použite vzor na skúmaný text takto:

```
pattern zhoda: predmet urobiť: { :m :x .... }
```

Úplný príklad:

```
>> predmet := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> pattern := Vzor nový: ['href="([^"]+)" target="([^"]+)"'].
>> result  := pattern zhoda: predmet urobiť: { :m :x
	Výstup písať: m, nový-riadok.
	Výstup písať: x, nový-riadok.
	<- ['XXX'].
}.
Výstup písať: result, nový-riadok.
```

## Sieťová komunikácia

Na vykonanie webovej požiadavky použite objekt Sieť.
Objekt Sieť vždy posiela požiadavku POST, pokiaľ ako
údaje nepošlete Nič; vtedy pošle požiadavku GET.


```
Sieť 
post: Nič 
na: ['https://redbeanphp.com'].
```

## Šifrovanie

Serverový plugin obsahuje šifrovanie založené na XChaCha20 a Argon2.

Príklad:

```
>> encrypted := Trezor šifrovať: ['hello'] kľúč: ['world'].
>> decrypted := Trezor šifrovať: encrypted kľúč: ['world'].
```

## Tokeny

Na vygenerovanie kryptograficky bezpečného tokenu určitej dĺžky:

```
>> mytok := Trezor token: 40.
```

Vygeneruje sa token so 40 znakmi.

## Formátovanie

Objekt Formát umožňuje formátovať údaje, napríklad zarovnávať ich alebo
dopĺňať nuly. Používa syntax printf.

```
>> fmt := Formát nový: ['%06.0f'].
fmt aplikovať: 56. # gives 000056
```

Formát môže obsahovať jednu konverziu a tá musí zodpovedať hodnote,
inak dostanete chybu:

- `aplikovať:` s textom: `%s`
- `aplikovať:` s číslom: `%f`, `%e`, `%g` alebo `%a`
- `aplikovať-celé:` s číslom: `%d`, `%i`, `%o`, `%u`, `%x` alebo `%c`

Hodnoty z požiadavky sú texty. Ak chcete niektorú formátovať ako číslo,
najprv ju preveďte:

```
fmt aplikovať: (požiadavka get: ['amount']) číslo.
```

## Kódovače

K dispozícii je niekoľko kódovačov a dekódovačov.
Kódovač url pripraví url na použitie v HTML ako odkaz:

```
Server url-kódovať: ['https://example.com?a=6&b=1 2'].
```

Na bezpečné vloženie vstupu používateľa do HTML bez rizika XSS
injekcií vždy použite:

```
Server html-kódovať: ['<harmless>'].
```

Upozorňujeme, že šablónovací systém pri zápise do značky slotu
vždy vykoná html kódovanie. Ak teda používate šablónový systém,
toto používať nemusíte.

## Posielanie pošty

Na odoslanie e-mailu použite knižnicu mailtools.xo.

Príklad:

```
Server inicializovať.
Program použiť: ['mailtools.xo'].

>> e-mail := HTML-Email nový.
>> img := e-mail priložiť: ( Súbor nový: ['myimage.png'] ).

e-mail
odosielateľ: ['xo@xoscript.com'] názov: ['xo'],
komu: ( Zoznam nový ; ['xo2@xoscipt.com'] ),
predmet: ['xoxo'],
telo: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), odoslať.

```



## Prepájanie

Pomocou správy prepojiť: môžete k svojmu programu prepojiť externú knižnicu
pomocou libffi. Podrobnosti nájdete v kapitole o ffi.


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

FFI sa poskytuje na úrovni platformy/pluginu, pretože je
viazané na podkladovú architektúru systému, čo
jadro robiť nemá.
Serverový plugin ponúka vyhovujúcu implementáciu ffi/blobov.
Jadro sa predvolene pripája k cieľovej platforme
cez stdin/stdout, obmedzené služby súborového V/V a shell (Program systém:).
Doplnkovú integráciu poskytujú ffi/bloby prostredníctvom pluginov
zameraných na aplikácie, ako je serverový plugin.

FFI je skratka pre Foreign Function Interface (rozhranie cudzích funkcií). Umožňuje používať funkcie, ktoré napísali iní v
iných programovacích jazykoch a ktoré sa poskytujú prostredníctvom súborov DLL, SO alebo Dylib. Môže
ísť o najrôznejšie funkcie a touto metódou je k dispozícii obrovské množstvo funkcionality.
Začnime príkladom:

```
Server prepojiť: (
 Zoznam nový ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Zoznam nový ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s uvoľniť.
```

Výsledkom tohto kódu je, že na príkazovom riadku uvidíte nasledujúce:
FFI has 3 letters.
Teraz si pravdepodobne myslíte: „To je veľa kódu na niečo také jednoduché.“
Veď či by sme to nemohli vyriešiť jednoducho príkazom Gui show? Odpoveď je jednoznačne áno!
Toto je však myslené ako ilustratívny príklad.
FFI sa zvyčajne používa na zložitejšie úlohy, tie však nie sú dobrými
príkladmi, preto som zvolil niečo triviálne.

Argumenty metódy prepojiť:

- Argument č. 1: Súbor DLL alebo SO, ktorý chcete použiť.
- Argument č. 2: Funkcia v tomto súbore, ktorú chcete prepojiť.
- Argument č. 3: Zoznam s názvami dátových typov argumentov funkcie.
- Argument č. 4: Názov návratového typu funkcie.
- Argument č. 5: Názov objektu, ku ktorému chcete túto funkciu prepojiť (ak neexistuje, vytvorí sa
automaticky).
- Argument č. 6: Správa, ku ktorej sa má táto funkcia prepojiť.

Vo vyššie uvedenom príklade chceme prepojiť funkciu printf z libc.so. Názvy dátových
typov nájdete v dokumentácii softvéru, ku ktorému sa pripájate. Dostupné typy sú:
void, pointer, float, double, int, uint, char, uchar, intX a uintX,
kde X môže byť 8, 16, 32 alebo 64.

Tieto typy označujú počet bajtov potrebných na uloženie údajov. Pre printf prepájame
nový objekt s názvom Printf a správu template:number:. Externú
funkciu pred použitím preložíte do dialektu XOScript. Správa template:number: očakáva
ako prvý parameter buffer s textom šablóny. Tento buffer vytvoríme pomocou objektu Blob, ktorý
umožňuje manuálne alokovať pamäť. Za uvoľnenie tejto pamäte potom zodpovedáte vy,
a to pomocou správy uvoľniť.

Pamäťový blob môžete naplniť rôznymi spôsobmi. V našom príklade ho napĺňame textom, preto použijeme
správu utf8: (UTF-8 je kódovanie na prevod textu na bajty). Blob môžete naplniť aj pomocou
bytes:, ktorej odovzdáte zoznam hodnôt bajtov. Na prečítanie obsahu blobu použite od:dĺžka:.
Bajty dostanete späť ako zoznam. Pomocou objektu Blob môžete dokonca vytvoriť C-štruktúru, a to
správou struct:, ktorej odovzdáte postupnosť typov C. To môže byť potrebné pri volaní C
funkcie v externej softvérovej knižnici, ktorá očakáva ukazovateľ na štruktúru.

{warning}
Bloby musíte uvoľňovať sami.
Bloby neuvoľňuje garbage collector.
{/warning}

Keďže bloby možno vymieňať s externými funkciami z knižníc,
nemôže ich automaticky uvoľniť garbage collector (môžu zostať používané
externými funkciami alebo ich tieto externé funkcie môžu chcieť uvoľniť
samy). Preto musíte bloby v prípade potreby uvoľňovať sami.

Na uvoľnenie blobu použite:

```
myblob uvoľniť.
```

Na uvoľnenie štruktúry použite:

```
mystruct uvoľniť-struct uvoľniť.
```

Pri štruktúre teda musíte na dealokáciu pamäťového bloku poslať dve správy:
uvoľniť-struct a uvoľniť.

@api_Blob_fficonnect
