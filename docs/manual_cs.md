# Základy

{{messages}}


Vítejte v XOScriptu
Cílem projektu XOScript je vytvořit skriptovací jazyk, který je jednoduchý a auditovatelný.
Jednoduchý ještě nutně neznamená snadný.
Známý programovací jazyk může být snazší na používání než XOScript.
Jednoduchost zde znamená něco jiného:
možnost vytvořit si úplný mentální model jazyka a jeho chování.

XOScript je navržen tak, aby se vešel do hlavy.
Jeho gramatika i počet konceptů jsou záměrně malé.
Neexistují žádné třídy; objekty lze rozšiřovat přímo.
Objekty se předávají odkazem, kopírování je explicitní
a funkce mají jediný bod výstupu.

Některé z těchto voleb se výrazně liší od běžných jazyků.
XOScript například nemá typový systém a používá dynamický rozsah platnosti.
Zprávy, které nelze zpracovat, jsou ignorovány, místo aby vyvolaly výjimku.
Tyto volby mají své důsledky a jejich účelem není odstranit chyby.
Jejich účelem je udržet základní model jazyka malý a konzistentní.

XOScript lze také lokalizovat, takže je možné vyjádřit obchodní
pravidla v přirozeném jazyce a případně je sdílet s netechnickými zúčastněnými stranami.

Auditovatelnost znamená uplatnit stejnou filozofii i na implementaci.
Běhové prostředí je napsáno v C, s malým ručně psaným lexerem, parserem a procházením stromu.
Standardní knihovna a běhové prostředí do značné míry kopírují strukturu jazyka,
takže vztah mezi kódem v XOScriptu a jeho implementací je poměrně přímý.

Testy jsou také úzce propojeny s dokumentací.
Každá metoda by měla mít přidružený test, který lze začlenit do příručky,
což pomáhá udržovat dokumentaci v souladu s implementací.

XOScript nemá v úmyslu konkurovat běžným jazykům
funkcemi ani známostí. Zkoumá jiný cíl:
programovací prostředí, kterému vývojář dokáže porozumět jako celku.

Doufáme, že malý jazyk a malá
implementace umožní v praxi porozumět softwaru
od bajtu po objekt, od syntaxe po běhové prostředí, a psát kód
s jistotou, protože rozumíte tomu, co se děje
ve skriptu, i tomu, co se děje pod kapotou.

Architektura serverové sestavy xoscriptu
je jednoduchá, a přesto flexibilní.

{{architecture.png}}

Chcete-li používat xoscript jako serverový jazyk, musíte nainstalovat
serverový plugin do složky s názvem /mods/server. 

Je to proto, že chceme
oddělit jádro jazyka od funkcí specifických pro server,
na rozdíl například od PHP nebo Pythonu. Jinak bychom museli všem dodávat
úplně všechno bez jakéhokoli účelu, což je prostě hloupé.
Pokud chcete, můžete nainstalovat i další moduly. Systém je velmi
flexibilní.

Některé funkce je také lepší implementovat přímo ve skriptovacím jazyce,
například šablony a správu relací, a proto navíc
dodáváme pro vaše pohodlí knihovny template.xo a webtools.xo.
Důvodem toho všeho je, že nevíme, jak chcete
xoscript používat. Můžete ho používat jako serverový skriptovací jazyk,
ale také pro grafická rozhraní, vestavěná zařízení nebo jen dávkové zpracování.
I když ho používáte jako serverový skriptovací jazyk (což je
v současnosti jeden z hlavních způsobů použití), možná budete chtít
použít jiný šablonovací systém nebo jinou správu relací.
Kdo jsme my, abychom rozhodovali, že máte používat ten náš?

Jednou z výhod našeho vlastního šablonovacího systému však je, že
se k tvorbě šablon nemusíte učit žádnou další syntaxi.
Výchozí šablonovací systém dodávaný s xoscriptem používá 100%
oddělení prezentace a logiky. Místo speciální
šablonové syntaxe jednoduše používá velmi flexibilní systém značek slotů.
Více informací najdete v kapitole Server.

Pokud nechcete používat výchozí šablonovací systém ani
výchozí webtools, je samozřejmé, že musíte dodat
vlastní.

Pokud provozujete webový server v chrootu, jailu nebo jiném druhu sandboxu,
musíte do tohoto prostředí nainstalovat také závislosti xo; které
knihovny potřebujete, zjistíte pomocí ldd (viz manuálovou stránku Linuxu nebo BSD).
Pokud chcete ve svých xo-skriptech používat příkazy shellu, zkopírujte do tohoto prostředí také shell
(například bash nebo ksh).

Chceme také zdůraznit, že zpětnou kompatibilitu bereme velmi vážně.
Existuje dokonce speciální funkce pro zpětnou kompatibilitu nazvaná
'version'. Obecně se snažíme, aby váš kód běžel navždy. Nikdy tedy
nebudete muset svůj kód aktualizovat, aby zůstal kompatibilní s novějšími verzemi
xoscriptu. Naším cílem je: napiš jednou, spouštěj navždy.

Zbytek této příručky je věnován podrobnému vysvětlení programovacího
jazyka xoscript. Serverové skriptování je popsáno v kapitole
nazvané Server. Pokud jste zkušený vývojář softwaru, možná budete chtít
několik kapitol přeskočit, protože některé jsou až příliš podrobné nebo
jsou velmi podobné obecným programátorským postupům. Ti z vás,
kteří již mají zkušenosti s několika jinými programovacími jazyky,
by tedy měli tuto příručku brát spíše jako referenční příručku.

## Instalace na Linuxu

Stáhněte apache2 a mariadb:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Stáhněte xoscript.
Nahraďte X správným číslem verze!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Zkopírujte soubory do kořenového adresáře webu a do /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Upravte konfiguraci apache2:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Nahraďte Virtualhost tímto:

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

Vytvořte testovací stránku:

```
sudo nano /var/www/html/test.xo
```

a napište malý testovací program:

```
#!/bin/xo
Server inicializovat.
Program použít: ['webtools.xo'].
>> web := Webový-dokument nový.
web vypsat: ['Hello World'].
```

Povolte apache2 spouštět váš program přes CGI:

```
sudo chmod uog+x /var/www/html/test.xo
```

Restartujte apache2:

```
sudo systemctl restart apache2
```

Otevřete svou testovací stránku v prohlížeči:

```
http://localhost/test.xo
```

Měli byste vidět:

```
Hello World
```


## Instalace na OpenBSD

Upravte /etc/httpd.conf a přidejte:


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

Pokud chcete používat SSL:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Chcete-li výměnu klíčů ochránit proti kvantovým počítačům,
zvolte šifru mlkem:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Přidejte do chrootu binární soubor xo a moduly a také všechny závislosti
(zjistíte je pomocí ldd).

## Spouštění příkladů


Spuštění jednoho z ukázkových programů v balíčku:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Například spuštění příkladu FizzBuzz na Linuxu:

```
./example.sh fizzbuzz Linux
```

Spuštění stejného příkladu na OpenBSD:

```
./example.sh fizzbuzz OBSD
```

Spuštění příkladu s čistým sestavením:

```
./example.sh fizzbuzz OBSD clean
```

## Jednotkové testy

Spuštění jednotkových testů:

```
./runtests.sh
```

Spuštění jednotkových testů bez sestavení (pouze testování):

```
./runtests.sh nobuild
```

## Sestavení

Sestavení ze zdrojových kódů na Linuxu:

```
make clean
ISO="en" make
```

Na OpenBSD:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

Sestavení serverového pluginu na Linuxu:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

Sestavení serverového pluginu na OpenBSD:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Hello world

Jakmile je soubor přenesen do vašeho počítače, můžete ho rozbalit
a spustit xo následujícím příkazem:

```
xo
```

Chcete-li spustit XOScript, uložte program jako soubor a přidejte příponu -xo
(volitelné). Dále za příkaz XOScriptu vložte název souboru
svého programu:

```
xo myprogram.xo
```

Když spustíte příkaz XOScriptu a jako parametr použijete soubor
s programem, xo tento soubor přečte a provede.

{{note}}
Program můžete spustit také tak, že ho přetáhnete na ikonu xo.
{{/note}}

{{warning}}
Na některých systémech musíte xo předem povolit načítání dynamických
knihoven.
{{/warning}}

Tradice velí, že první program v každém novém programovacím
jazyce by měl být jakýmsi pozdravem světu. V XOScriptu vypadá
takový program **Hello world** takto:

@test598

Když tento text uložíte do souboru, např. hello.xo, můžete ho spustit
takto: .

xo hello.xo

Hello world


Výstup programu vidíte ve výše zobrazeném černém okně.
V celé této příručce bude pro zobrazení výstupu použito
stejné znázornění.

{{note}}
Výstup se píše s velkým V.
Obecně objekty začínají velkým písmenem,
pokud nevystupují jako instance (nemají žádné vlastní
metody, jen data). To odpovídá konvencím tříd a instancí
v jiných programovacích jazycích.
{{/note}}


## Syntaxe 

XOScript je *čistě* *objektově orientovaný* programovací jazyk. To znamená,
že xoscript vnímá vše jako objekt, a proto neexistují
žádné jiné *datové typy*. V programu napsaném v XOScriptu existují v podstatě tři základní
úkony: *přiřazování*, *posílání zpráv*
a *odpovídání*. Výměna zpráv mezi objekty je klíčovou součástí
programu v XOScriptu. Tyto tři jednotlivé úkony jsou znázorněny
níže:


Úkon            | Příklad
--------------- | --------
přiřazení       |  \>\> x := 1. 
unární zprávy   | x sudý?.
binární zpráva  | 1 + 2.
klíčová zpráva  | x od: 0 délka: 10.
odpověď         | <- answer.  


Tato kapitola vám poskytne celkový dojem z jazyka XOScript
a popíše jeho základní principy. XOScript je malý jazyk
založený na třech úkonech (viz znázornění), které se promítají přibližně do
šesti gramatických pravidel. To je vše, co je potřeba k ovládnutí
jazyka.

Nemějte obavy, pokud vám věci nebudou hned zřejmé: všechny stavební
kameny prozkoumáme v další kapitole (3) a základní pravidla
zopakujeme. Tato kapitola však slouží hlavně jako obecný
úvod do jazyka. Základní principy budou stručně
vysvětleny a znázorněny několika vhodnými příklady. Chybějící
podrobnosti doplníme později.

Komentáře v XOScriptu začínají symbolem \#. Následující řádek
bude tedy ignorován:

```
# toto je jen komentář
```

## Proměnné

K přiřazení
proměnné použijte symbol deklarace proměnné: >>. Název
proměnné může obsahovat všechny znaky kromě: <-, :=, bílých znaků,
teček, čárek, dvojteček, uvozovek [' '] a závorek ().
Proměnná navíc nemůže zabírat více řádků. Upozorňujeme,
že proměnná nemůže začínat číslicí ani znaménkem minus.

Toto jsou příklady platných proměnných:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dolar'].
>> +plus := Pravda.
>> heslo-uživatele := ['Pst!'].
```

Neplatné proměnné jsou například:


```
>> -123 := ['záporné číslo'].
>> password of uživatel := ['Tajné'].
>> password.of:uživatel := ['Tajné'].
>> ,x := 10.
```

{{note}}
V řetězcovém literálu nemusíte escapovat žádný znak
(včetně apostrofů, uvozovek a hranic
řetězce), pokud to
nezpůsobí nejednoznačnost pro lexer.
{{/note}}

Po deklaraci lze proměnnou volně používat. To znamená,
že symbol deklarace je nutné použít jen při prvním
použití proměnné (deklaraci).

Konkrétněji řečeno, nemůžete jen tak začít přiřazovat hodnotu
své proměnné *(x := 2)*, protože proměnnou musíte nejprve deklarovat *(\>\>
x := 2)*. Jakmile je však deklarována, smíte její hodnotu měnit
bez použití symbolu deklarace*(\>\> x := 2. x := 3.)*.

Při deklaraci je povinné proměnné přiřadit hodnotu.
Na rozdíl od jiných programovacích jazyků nesmíte
deklarovat proměnnou bez hodnoty. Každou proměnnou je nezbytné explicitně svázat
s počáteční hodnotou. Proměnnou však klidně můžete inicializovat
objektem **Nic**. V takovém případě lze proměnnou
považovat za prázdnou *(\>\> x := Nic.)*. Stručně řečeno, deklarovat
proměnnou bez počáteční hodnoty není dovoleno. Tedy

```
>> x.
```

je neplatné a vyvolá chybové hlášení.

{{note}}
xoscript používá dynamický rozsah platnosti proměnných;
podrobnosti najdete v kapitole Funkce.
{{/note}}


## Literály

XOScript vnímá vše jako objekt, tj. všechna čísla, řetězce
i fragmenty kódu. Čísla jako 1, 2, 100, -999 a 1,234 jsou
objekty Číslo. Všechny texty mezi apostrofy jsou objekty
Řetězec. Všechny fragmenty kódu seskupené mezi složenými závorkami {...} jsou
objekty Funkce.

Literál         | Kořenový objekt | Příklad
--------------- | ------------ | ----------
čísla           | Číslo        | 1,2,3... 
řetězce         | Řetězec      | \['hello'\]
funkce          | Funkce       | { 1 + 2. }.
                
     
Objekty jako čísla a řetězce mají vždy svůj původ v kořenovém
objektu. Například všechna čísla jsou odvozena od objektu **Číslo**. Všechny
řetězce jsou odvozeny od **Řetězec** a všechny fragmenty kódu od **Funkce**.
Všechny tyto objekty zase pocházejí z objektu **Objekt**, který je ve skutečnosti
kořenovým objektem všech objektů.


## Zprávy

Programování v XOScriptu v podstatě znamená
posílání zpráv objektům. Obecný zápis poslání zprávy
objektu je následující:

```
<object> <message>
```

Chceme-li například zjistit, zda je číslo **2** sudé, pošleme
objektu **2** zprávu **sudý?**:

```
2 sudý?
```

Odpovědí bude **Pravda** (opět objekt). Neznámé zprávy objekty
obvykle ignorují, takže nedojde k žádné chybě. Některé objekty (např.
čísla nebo řetězce) reagují na neznámou zprávu předem definovaným způsobem
(více o tom později).

Objekt může přijímat tři druhy zpráv. 

Typ             | Počet parametrů
--------------- | -------------------
Unární          | 0      
Binární         | 1     
Klíčová         | 1+    


Zaprvé existují **unární
zprávy**, viz příklad výše, které nemají žádné parametry. Zadruhé
existují **klíčové zprávy**, které mají jeden nebo více parametrů,
například:

```
>> x := Číslo mezi: 1 a: 10.
```

V tomto případě je zpráva **mezi:a:** poslána objektu **Číslo**, který
je kořenovým objektem všech čísel. Výsledkem bude náhodné číslo
mezi 1 a 10. A konečně existují **binární zprávy**, které mají
jen jeden znak a jeden parametr:

```
2 + 3
```

Vypadá to jako matematický součet, ale ve skutečnosti je to jen další zpráva.
Zpráva **+** je poslána objektu **2** s parametrem **3**, což vrátí
odpověď **5**. Binární zprávy se smějí psát bez dvojtečky.

Binární zprávy lze řetězit:

```
>> x := 3 + 2 - 1.
```

V tomto fragmentu je nejprve **+ 2** posláno objektu **Číslo** **3**, což
vede k objektu Číslo **5**, a poté je tomuto číslu posláno **-1**.
Pozorní čtenáři si správně všimnou nesouladu, který
tento protokol vykazuje vůči obvyklému matematickému pořadí
operátorů. XOScript ignoruje matematické pořadí ve prospěch
konzistence svého systému zpráv. V důsledku toho dává součet:

```
2 + 3 * 5 = 25
```

nikoli 17.

Je to záměr. Pořadí lze upravit pomocí závorek:

```
2 + (3 * 5) = 17
```

Většina objektů vrací v odpovědi na určitou zprávu jako výsledek
sama sebe. To je užitečné, protože to podporuje další dialog s tímto
objektem posláním navazující zprávy:

```
Výstup psát:
[' nazdar '] odstranit-okolní-mezery velkými-písmeny.
```

```
NAZDAR
```

Zde jsou objektu **Řetězec** poslány dvě zprávy: **odstranit-okolní-mezery** a po ní
**velkými-písmeny**.

V následujícím fragmentu je nutné použít čárku, aby bylo zřejmé,
že přichází nová zpráva. Jinak by se XOScript zmátl.

```
Výstup psát: ['Hello!'], nový-řádek.
```

Nejprve je symbolu tužky poslána zpráva **psát:** a po ní
**nový-řádek**. Bez čárky by si XOScript myslel, že chcete poslat
**nový-řádek** **řetězci** **Hello!**, což je marné počínání.

Zprávy se zpracovávají v tomto pořadí: zleva doprava;
začíná se zprávami v závorkách, po nich následují unární zprávy. Dále
binární zprávy a nakonec klíčové zprávy. Viz příklad
níže:

```
Výstup psát: 0.5 zaokrouhlit + (2 - 1), nový-řádek.
```

XOScript vždy čte zleva doprava: nejprve je objektu Výstup poslána zpráva **psát:**
a po ní zpráva **nový-řádek**. I uvnitř samotného
parametru čte XOScript zleva doprava, tedy nejprve **0.5 zaokrouhlit**
a poté **+**.

{{note}}
Zpráva nový-řádek přidá k řetězci znak nového řádku.
Název této zprávy (v angličtině stop) je inspirován telegrafními systémy.
Zprávy v telegrafních systémech 
často používaly slovo STOP k označení konce věty
(protože interpunkce byla nespolehlivá nebo drahá).
{{/note}}

Navíc má **zaokrouhlit** přednost před **+**, protože jde o
**unární zprávu**. Díky závorkám se nejprve vypočítá **2 - 1**,
poté se **1** přičte k výsledku **0.5 zaokrouhlit** (1).

Celý postup dá výsledek **2**, což je také vypsaná
odpověď. Za čárkou následuje zpráva nový-řádek, která přesune kurzor
na nový řádek. Nejlepším způsobem, jak plně pochopit pořadí
zpracování programů v XOScriptu, je samozřejmě praxe.

Stojí za zmínku, že v XOScriptu jsou na rozdíl od mnoha jiných programovacích
jazyků bílé znaky základní součástí syntaxe. Zejména
u binárních zpráv mohou bílé znaky způsobit určitý
zmatek. Za binární zprávou vždy použijte mezeru. Číslo nemůžete
připojit přímo ke zprávě, například: 

```
3 + 2
```

se liší od 

```
3 +2
```

První příklad (**3 + 2**) posílá
číslu **3** zprávu **+** s parametrem číslo **2**.
Výsledkem bude v tomto případě **5**. Ve druhém příkladu (**3 +2**)
je číslu **3** poslána unární zpráva **+2**. V závislosti na
kontextu to může vést k velmi odlišnému výsledku.

## Neexistující metody

Poslání zprávy objektu vyvolá funkci, která byla
k tomuto objektu připojena pod názvem dané zprávy. Pokud pošlete zprávu,
které objekt nerozumí, přijímající objekt vaši zprávu ignoruje
a místo toho vrátí odkaz sám na sebe pro další komunikaci.
Tomu se říká tolerantní předávání zpráv.

Příklad:

```
Výstup psát: Objekt blah, nový-řádek.
```

Tím nevznikne žádná chyba. Jednoduše se vypíše text **Objekt**.


## Řízení toku

V XOScriptu nejsou potřeba samostatná gramatická pravidla pro *cykly* a
*podmínky*. Podmínka if je jen obyčejná zpráva **pravda:** nebo **nepravda:**
poslaná buď objektu **Pravda**, nebo objektu **Nepravda**:

```
2 sudý? pravda: {
	Výstup psát: ['Dvojka je sudé číslo'], nový-řádek.
}.
```
V předchozím příkladu je zpráva **pravda:** poslána objektu **Pravda** (což je
odpověď na otázku: je 2 sudé číslo?). Jako parametr je spolu s ní poslán další
fragment kódu: objekt **Funkce**. Tato funkce vypíše na
obrazovku, že 2 je skutečně sudé číslo.

Ani pro *cyklus* nejsou potřeba samostatná pravidla zápisu. Chcete-li
fragment kódu provést třikrát, jednoduše pošlete této **Funkci** zprávu **\***
s parametrem **3**:

@test5

V tomto fragmentu kódu je **i** index. Když se tedy Funkce
provádí poprvé, **i** se rovná 0, při dalším provedení **i** = 1 a
tak dále.

Podívejme se na další příklad. Má-li se vypsat převodní tabulka
z *kJ* (kilojoulů) na *kcal* (kilokalorie) po krocích 100,
správný zápis vidíte níže:

@test599

Zde se číslo aktuálního řádku předává parametru
**:line**. Na začátku funkce se definují její
parametry. Nepoužité parametry zůstávají prázdné (**Nic**). Parametry jsou
vždy umístěny na začátku funkce, hned za úvodní
složenou závorkou, a předchází jim dvojtečka.

Zpráva **zatímco:** je kombinací *cyklu* a *podmínky*.
Pomocí zprávy **zatímco:** lze propojit dvě funkce. Přijímající funkce
poběží, dokud funkce za dvojtečkou nedá záporný
výsledek. Příklad:

@test600

Ve výše znázorněném fragmentu kódu se k **x** přičítá **1**, dokud
je **x** menší než **5**. Jakmile to již neplatí, druhá
funkce odpoví **Nepravda**, a v důsledku toho provádění
první funkce skončí. Všimněte si, že **x** bylo definováno mimo
funkci a je globální proměnnou. Chcete-li se dozvědět více o pravidlech rozsahu platnosti,
přečtěte si kapitolu o funkcích.

## Interpolace řetězců

Seznam *kJ/kcal* by mohl být
úhlednější. Nejlépe by vypadal takto:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Když požadovaný výstup převedete na šablonu, její zápis
by mohl být:

```
number1 kJ ➞ number2 kcal
```

To znamená, že **number1** zastupuje hodnotu v kJ a **number2**
hodnotu v kcal. Takto funguje interpolace řetězců v XOScriptu.
XOScript k tomu nepotřebuje žádná samostatná gramatická pravidla. Jednoduše
pošlete textu slovo, které je třeba nahradit, s náhradním textem
jako parametrem:

```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

Výsledek:

```
100 kj ➞ 23.9 kcal
```

Toto pravidlo nahrazování platí pro každou nedefinovanou zprávu, kterou
obdrží objekt **řetězec**. Každá zpráva, kterou objekt
**řetězec** nerozpozná, bude interpretována takto: *nahraď text zprávy
textem v parametru zprávy.* Program můžete upravit
takto:


@test601


Abyste se vyhnuli nejasnostem, kterou zprávu lze nebo nelze použít
k nahrazení, je nejlepší zavést šablonovou značku jako &lt; &gt;
pro textové úseky v šabloně, které
je třeba nahradit.

## Návratové hodnoty

K odpovědi na zprávu se používá návratová šipka
(*<-*). Následující příklad ukazuje, jak vytvořit úlohu
pro výpočet procent:

@test602

Poté, co byla úloha definována a přiřazena proměnné **percentage**,
je jí poslána zpráva **aplikovat:a:** s parametry **100** a **7**.

Tím se úloha provede na **100** a **7**, tj. 7 % ze 100.
Pomocí návratové šipky se odpověď vrátí z úlohy zpět
do hlavního programu.

## Rozšiřování

Ačkoli je tento kód platný, má nevýhodu,
protože je nutné si pamatovat pořadí parametrů. Proč ho tedy
nenapsat takto: *7 percent of: 100 *? To by vypadalo mnohem
*přirozeněji*. Abychom to umožnili, musíme upravit rodičovský objekt
čísla **7**, což je objekt **Číslo**, aby rozuměl
zprávě **percent of:**. Toho lze dosáhnout posláním **při:udělat:**
objektu Číslo, takto:

@test603

Protože procentem je v tomto případě samotné číslo, odkazujeme na sebe,
klíčové slovo *sebe*. Stručně řečeno, symbol sebe znamená: *pošli tuto
zprávu mně samotnému*.

# Objekty

{{messages}}

Kromě úprav a rozšiřování existujících objektů můžete také sami vytvářet
nové objekty, a to jednoduše posláním zprávy **nový**. Předpokládejme, že
chcete vytvořit objekt faktury, který vynucuje číselnou
řadu; v takovém případě budete nejprve potřebovat objekt faktury.

Protože každý objekt je odvozen od jiného objektu, který zase
nakonec pochází z kořenového objektu všech objektů nazvaného Objekt,
je třeba se rozhodnout, na kterém z těchto jiných objektů bude váš
nový objekt založen. Váš nový objekt zdědí všechny vlastnosti
objektu, na kterém je založen, tedy objektu, kterému byla zpráva **nový**
původně poslána.

V tomto příkladu je vhodnější spíše neutrální objekt, takový, který nemá
příliš mnoho zděděných vlastností. Volba je snadná, protože
v tom případě může být nový objekt založen přímo na kořenovém objektu, kterým je
**Objekt**. Zápis zamýšleného systému faktur pak bude
následující:

@test604

Aktuální číslo faktury je uloženo v objektu, a proto je před ním
umístěno klíčové slovo **vlastní**. Tomu se říká *vlastnost*;
další podrobnosti budou následovat.

Některé firmy dávají přednost tomu, aby čísla faktur obsahovala rok.
V takovém případě můžete vytvořit nový objekt faktury založený na
dřívějším objektu faktury, který však uživateli nabízí možnost
zadat konkrétní rok:

@test605

Implementaci zprávy **číslo** není třeba psát
znovu, protože je zděděna z dříve napsaného **objektu
faktury**; starý kód tak lze znovu použít. XOScript nezná koncepty
jako třídy a další související koncepty. To znamená, že objekty mohou
dědit pouze od jiných objektů, čemuž se také říká *prototypová
dědičnost*.

Nyní se vraťme k vlastnostem. K vlastnostem objektu lze přistupovat pouze
*zevnitř hierarchie objektu*, takže tyto vlastnosti
nemohou vnímat jiné objekty.

Na rozdíl od jiných programovacích jazyků jsou všechny vlastnosti objektů
viditelné výhradně pro objekt, který vlastnost vytvořil, a pro
odvozené objekty. 

Běžně používanou technikou je použít objekt jako jakýsi *plán*,
což je například případ výše popsaných faktur.
Dalším dobrým příkladem je **Point**. Řekněme, že vytváříte
počítačový program, který provádí výpočty s body na mapě. Můžete
vytvořit objekt **Point** obsahující vlastnosti
souřadnice x a souřadnice y, které budou vnějšímu světu zpřístupněny
prostřednictvím zpráv:

@test606

Zpráva **=** porovnává dva body pomocí zprávy **a:**.
Výsledkem prvního porovnání je **Pravda** nebo **Nepravda**. To jsou logické
objekty. Když pošlete zprávu **a:** objektu Pravda a
objekt parametru za dvojtečkou je rovněž **Pravda**, dostanete
jako odpověď opět **Pravda**. Když je kterýkoli z nich **Nepravda**, dostanete
odpověď **Nepravda**. Všimněte si, že jeden bod nemůže číst souřadnice
druhého. Je nutné poslat druhému bodu zprávu a požádat ho
o tato data: **x-coordinate** a **y-coordinate**. Jak už bylo
vysvětleno, vlastnosti lze získat pouze zevnitř
samotné rodiny objektů. 

Všimněte si, že k porovnání bodů se zde používá zpráva **=**.
Stejně tak bylo možné použít jinou zprávu, například
**is:** nebo **equal:**, ale opětovné použití znaku **=** se v tomto případě zdálo
vhodné.

## Dědičnost

Dříve napsaný kód můžete znovu použít k vytvoření hierarchie
objektů. Například:

```
>> Zvíře := Objekt nový.
>> Pes := Zvíře nový.
>> Pudl := Pes nový.
```

V tomto případě **Dog** dědí veškeré chování a vlastnosti
objektu **Animal** a objekt **Animal** zase dědí veškeré chování
objektu **Objekt**, kořenového objektu všech objektů.


## Přepisování


V následujícím příkladu se vytváří nový druh seznamu:
**Combination**, v němž je zaručeno, že každý prvek je jedinečný.
Funkce seznamu jsou znovu použity prostřednictvím dědičnosti:

@test607

Všimněte si, že druhé **red** je ze seznamu vyřazeno.

Občas může být nutné přepsat chování objektu.
Například když se sčítají čísla a je třeba brát v úvahu jednotky
měření. V následujícím příkladu se vytváří objekt **Size**.
Tento objekt vrací číslo, které při sčítání bere
v úvahu jednotku přičítaného čísla. Objekt **Číslo**
kontroluje, zda jde o *palce* nebo *stopy*. Programový kód
by mohl vypadat takto:

@test608

## Rekurze

V předchozím příkladu je přepsáno **znaménko** plus. Všimněte si,
že nakonec je stále nutné provést konečné sčítání, které ve skutečnosti
probíhá na následujícím řádku:

```
>> odpověď := sebe + (číslo x faktor).
```

Jak tedy XOScript pozná, že toto **znaménko** plus odkazuje na
původní logiku sčítání?** Jiná interpretace by například
mohla být, že XOScript bude opakovaně posílat stejnou zprávu stejnému
objektu, což by zase vedlo k **nekonečné smyčce**. To zjevně
není záměrem. Jakmile pošlete objektu zprávu,
která by provedla přesně tentýž kód, XOScript si
v takovém případě uvědomí, že je myšlena podkladová, přepsaná zpráva. Váš
program je tak automaticky chráněn před touto formou nekonečných
smyček. Pokud je však vaším cílem skutečně spustit stejnou funkci z
aktuální funkce, je nutné nejprve poslat zprávu
**rekurzivní**. V takovém případě bude výsledkem nekonečná
smyčka. Pro rekurzivní úlohy však existují užitečná použití,
předpokládejme například, že chcete vypočítat faktoriál daného
čísla. V takovém případě jednoduše přidejte zprávu **factorial** objektu
Číslo:

@test609

To vyžaduje rekurzi. Úloha spojená se
zprávou **factorial** totiž musí být uvnitř této funkce provedena znovu.
Je tedy nutné vyvolat funkci faktoriálu zevnitř
samotné funkce faktoriálu. Zpravidla XOScript tomuto postupu zabrání
kvůli riziku, že skončí v nekonečné smyčce. Z tohoto důvodu
je zásadní uvést před zprávou slovo **rekurzivní**. To
se dělá proto, aby XOScript věděl, že je vaším
záměrem provést stejnou úlohu a že jste neudělali chybu.

## Objekty podobné třídám

Ačkoli xoscript třídy nenabízí, napodobit chování podobné
třídám je triviální. Stačí přepsat zprávu nový.

```
>> Zvíře := Objekt nový.
Zvíře při: ['nový'] udělat: {
	<- sebe nový inicializovat.
}.

Zvíře při: ['inicializovat'] udělat: {
	vlastní zvuk := ['?'].
	vlastní nohy  := 4.
}.
```

Ve výše uvedeném fragmentu kódu vytváříme objekt nazvaný Animal.
Tento objekt slouží jako *plán* pro všechny druhy zvířat,
jako jsou psi a kočky. Rodičovský objekt Animal je napsán
s velkým A, aby bylo zřejmé, že jde o objekt podobný třídě.
Poté přepíšeme zprávu nový tím, že napíšeme vlastní metodu nový.
V tomto případě pošle zprávu nový objektu sebe, a po ní zprávu
inicializovat. Protože xoscript ve výchozím stavu blokuje rekurzi, nezpůsobí to
nekonečnou smyčku. Místo toho pošle zprávu nový rodičovskému
objektu (Objekt), což vede k nové instanci Animal. Vytvoříme tedy
nový objekt založený na stejném objektu, pro který jsme vytvořili svou metodu nový.
To je naprosto platné. Nyní posíláme také zprávu inicializovat, která zajistí,
že objekt Animal má pro své vlastnosti výchozí hodnoty. Ve výchozím stavu
má zvíře 4 nohy a jeho zvuk není znám (proto otazník).
K vytvoření nové instance našeho Animal bychom mohli jednoduše napsat:

```
>> a := Zvíře nový.
```

Nyní získáme novou instanci Animal se 4 nohama, neznámým zvukem a
metodou inicializovat. Stejně jako v jiných OOP jazycích můžeme také
náš Animal rozšířit:

```
>> Pes := Zvíře nový.
Pes při: ['inicializovat'] udělat: {
	sebe inicializovat.
	vlastní zvuk := ['štěká'].
}.
```

Snadno to otestujeme přidáním metody řetězec:

```
Zvíře při: ['řetězec'] udělat: {
	<- vlastní nohy řetězec + vlastní zvuk.
}.
```

Dejme to všechno dohromady:

@test13


Vytvoření objektu, který je nastaven do daného počátečního stavu, představuje
častý problém. Předpokládejme, že je třeba vytvořit objekt **Rectangle**
pro výpočet obvodu a obsahu. Možný zápis by byl:


```
>> Obdélník := Objekt nový.

Obdélník při: ['plocha'] udělat: {
	<- vlastní délka * vlastní šířka.
}.
```

Nastavení délky a šířky je zjevně předpokladem. Za tímto
účelem lze přidat zprávy **délka:** a **width:**:


```
Obdélník při: ['length:'] udělat: { :délka
	vlastní délka := délka.
}.

Obdélník při: ['width:'] udělat: { :šířka
	vlastní šířka := šířka.
}.

```

Tento obdélník pak lze použít takto:


```
>> obdélník := Obdélník nový length: 2, width: 3.
Výstup psát: obdélník plocha.
```

Pokud se však na počáteční nastavení délky a šířky zapomene,
objeví se chybové hlášení:

```
>> obdélník := Obdélník nový.
Výstup psát: obdélník plocha.
```

vyvolá následující chybu:

```
Klíč nebyl nalezen: délka
```

Aby se tomu předešlo, je vhodnější, aby obdélník
vždy měl počáteční délku a šířku, například 0. V tomto
případě je tedy nutné **přepsat** zprávu **nový**.

@test610

Když přepíšeme zprávu nový, v podstatě napodobujeme **třídu**.

Svět XOScriptu je plný rozmanitých objektů, které má
váš program k dispozici hned od začátku. V dalších kapitolách
budou probrány všechny tyto základní objekty.

## Snímky

Objekt (spolu s jeho aktuálním stavem) můžete uložit na disk pomocí:

```
můj-objekt save-as: ['saved.bin'].
```

Opětovné načtení objektu z disku:

```
>> můj-objekt := Objekt load-from: ['saved.bin'].
```

Snímky lze použít k uložení určitého stavu nebo ke zlepšení výkonu.
Načtení snímku se vyhne lexikální analýze, parsování a nastavení aplikace.
V budoucnu mohou být se snímky zavedeny i další výkonnostní výhody,
například optimalizace určitých vzorů nebo detekce a
optimalizace často prováděných cest.

{{warning}}
Snímky jsou experimentální funkcí, nepoužívejte je v produkčním prostředí.
Experimentální funkce aktivujete kompilací s -D EXPERIMENTS.
{{/warning}}


@test712

# Objekt Nic

{{messages}}

Objekt Nic
představuje prázdnotu, nebo lépe řečeno nepřítomnost informace.
Tento objekt občas dostanete jako odpověď na zprávu
v případě, že výsledkem je **nic**. Nejzásadnější otázka,
kterou můžete objektu **Nic** položit, je: **Nic?**.
Odpověď bude vždy znít **Pravda**.

```
Výstup psát: Nic Nic?.
```

výsledek:

```
Pravda
```

Každý jiný objekt než **Nic** odpoví **Nepravda**.
Výše uvedený fragment kódu se může zdát poněkud filozofický, objekt **Nic**
však rozhodně má velmi praktická použití. Objekt Nic například
dostanete jako odpověď, když se zeptáte na
prvek seznamu, který neexistuje. Objekt Nic můžete použít také,
když chcete deklarovat proměnnou, ale zatím nechcete určit hodnotu.
Místo toho jí jen **přiřadíte** speciální hodnotu **Nic**.
V XOScriptu není dovoleno deklarovat proměnnou bez hodnoty, například:


```
>> hodnota.
```

Místo toho musíte napsat následující:

```
>> hodnota := Nic.
```

@api_None_base

# Logické hodnoty

{{messages}}

Na rozdíl od většiny populárních programovacích jazyků v době psaní
poskytuje XOScript pouze jediný objekt Pravda a jediný objekt Nepravda.
Pro upřesnění: pokaždé, když napíšete **Pravda**, neznamená to, že
byl vytvořen nový objekt. Místo toho vždy používáte odkaz. To
znamená, že když napíšete následující:

\>\> x := Pravda.

**x** odkazuje na objekt **Pravda**. Podmíněný kód a cykly také
ověřují tento odkaz. V XOScriptu není význam **Pravda** a **Nepravda**
pevně daný. Program v XOScriptu se ve skutečnosti pořádně otřese po
příkazu, jako je tento:

Pravda := Nepravda.

Výsledek takových akcí není definován, přesto zůstává platnou
akcí, a proto je formálně povolen. Kromě toho existuje objekt Logický,
který je kořenovým objektem objektů **Pravda** i **Nepravda**, protože oba
jsou odvozeny od tohoto kořenového objektu. Samotný objekt Logický však
nemá žádné praktické použití.

## Záludnosti

Buďte opatrní při používání **a:** a **nebo:**

```
Výstup psát: (Nepravda or: Pravda or: Pravda), nový-řádek.
Výstup psát: (Nepravda nebo: Pravda, nebo: Pravda), nový-řádek.
```

Vrátí

```
Nepravda
Pravda
```
protože zpráva **nebo:** přijímá jen 1 parametr. První řádek
posílá objektu Nepravda zprávu **nebo:nebo:**, která neexistuje, takže objekt
zprávu ignoruje a vrátí sám sebe (Nepravda). Naproti tomu druhý řádek
posílá **nebo:** a po ní další **nebo:** (pomocí symbolu řetězení, tj. čárky: ,).


@api_Boolean_base

# Čísla

{{messages}}

Pokaždé, když napíšete číslo, například 9, -10 nebo 3,12, XOScript
ho v pozadí převede na objekt **Číslo**. Tomuto objektu Číslo
můžete posílat zprávy, nebo můžete číslo přiřadit
proměnné a zprávy posílat až potom:

```
10 sudý?

>> desítka := 10.
desítka sudý?

```

Oba zápisy jsou platné. Objekt Číslo reaguje na následující
zprávy...

Většina těchto zpráv je samovysvětlující a umožňuje provádět
matematické operace nebo porovnání.

{{note}}
Místo jejich ASCII protějšků můžete používat ≤ ≥ ≠ × a ÷.
Je to věc vkusu.
{{/note}}

Rozdíl mezi binárními matematickými zprávami (+) a
jejich klíčovými variantami (přičíst:) spočívá v tom, že první vracejí
nové číslo, které je výsledkem operace, zatímco u
druhých se mění samotný objekt. Ukazuje to
následující příklad:

@test597

Ve výše uvedeném příkladu je b = 4 a a = 3. Pomocí **přičíst: 2** se hodnota
a zvýší o 2, zatímco **+ 3** vytvoří nové číslo, které se
rovná a + 3. Totéž platí pro další matematické operace, např.
násobení. Použitím symbolu násobení dostanete jako odpověď
nový objekt. Pokud použijete zprávu **vynásobit:**,
vynásobíte samotné číslo.

Zprávou **mezi:a:**, například v: **Číslo
mezi: X a: Y**, dostanete číslo mezi X a Y. Tímto
způsobem lze vygenerovat libovolné náhodné číslo:

```
>> a := Číslo mezi: 1 a: 10.
Výstup psát: a, nový-řádek.
```

Od verze 1.4 je vestavěný generátor náhodných čísel v xoscriptu
podle našeho nejlepšího vědomí kryptograficky bezpečný.

K číslu můžete připojit **jednotka** (jednotku), například **6
apples**. Každá zpráva, kterou číslo nerozpozná,
bude považována za jednotku. Jednotku
čísla můžete získat pomocí zprávy jednotka:

Jednotka je v podstatě textový objekt, který je uložen spolu s objektem
Číslo. Jednotka se také vypíše za číslem při
příkazu **psát:**. Jednotky lze použít například ke sčítání částek
v různých měnách. Při sčítání částek se můžete zeptat
na jejich jednotky. Následující ukázkový program tento
princip ilustruje pomocí kalkulačky historické měny (protože směnný
kurz zůstává poměrně stabilní!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Řetězce

{{messages}}

Pokaždé, když umístíte text mezi **hranaté závorky a apostrofy** ['...'],
XOScript pro vás vytvoří nový objekt řetězce. Dbejte však na to,
abyste použili správné uvozovací znaky. Uvozovací znak na
začátku textu se liší od znaku na konci (díky tomu můžete
použít apostrof, aniž byste ho museli escapovat).

## UTF8

Řetězce v xoscriptu obvykle obsahují text kódovaný v utf8. Přestože
je technicky možné mít v řetězci binární obsah nebo obsah, který není v utf8,
doporučuje se k tomu používat bloby. Bloby
poskytuje serverový plugin (viz kapitolu ffi).
Obecně jsou bloby/ffi poskytovány
podle pluginu/platformy, protože jsou svázány s platformou
a architekturou (ffi/bloby). Jádro skriptovacího jazyka se snaží
zůstat co nejvíce nezávislé na platformě.

## Přetypování

Kopii každého objektu
s jiným typem můžete vytvořit pomocí následujících zpráv:

Zpráva   | Výsledek
-------- | ------
číslo    | Převede na číslo
řetězec  | Převede na řetězec
logický  | Převede na logickou hodnotu
  
**Platí** následující pravidla:

zpráva   | Nic       | Logický            | Číslo                 | Text      | Jiné              
-------- | --------- | --------           | --------              | --------  | --------
logický  | Nepravda  | n/a                | 0→Nepravda jinak→Pravda | Pravda  | Většinou Pravda
číslo    | 0         | Nepravda→0 Pravda→1 | n/a                  | ['n']→n | Většinou 1
řetězec  | ['Nic']   | ['Nepravda']/['Pravda'] | ['n']            | n/a       | Podle okolností

## Kopírování

Hodnoty se v XOScriptu vždy předávají **odkazem**. V jiných jazycích
to závisí na typu hodnoty, v XOScriptu existuje jen jediný způsob,
odkazem. XOScript nikdy nevytváří kopii hodnoty. Chcete-li objekt zkopírovat,
musíte poslat zprávu **kopírovat**. 

@test611

Zde byste možná čekali, že výstupem bude Dolly, a ne
Donny. Tak tomu však není, protože obě jména odkazují na tentýž
objekt. Při práci s cyklem dochází k něčemu podobnému:

@test612

XOScript ve skutečnosti **vždy** používá odkazy, takže u **:quantity**
výše znázorněný cyklus také ukazuje odkaz na prvek
v seznamu.

Chcete-li objekt zkopírovat, musíte tuto akci uvést
**explicitně**:

@test613

Posláním unární zprávy **kopírovat** řetězci vrátí objekt
kopii téhož objektu řetězce. Stejným způsobem lze kopírovat objekty
Číslo, logické objekty, seznamy a slovníky.

Můžete také definovat vlastní implementaci kopírování; pokud vytváříte
vlastní objekty, je to dokonce nezbytné. Výchozí
implementace kopírování seznamu vytváří mělkou kopii, tj. vytvoří
nový seznam se stejnými prvky.

@test614

V tomto případě je 4 přidáno jen do kopie.
Protože je však kopie mělká, objekty v obou seznamech
jsou tytéž.

@test615

Pokud tedy ke každému jménu v kopii připojíme 2, je ovlivněn
i původní seznam.

Abychom to napravili, musíme vytvořit **hlubokou kopii**. Taková akce kopírování
pro seznam by mohla být sestavena takto:

@test616

Všimněte si také zprávy rekurzivní; tuto zprávu je nutné
poslat před zprávou kopírovat.

Je nezbytné mít na paměti, že ačkoli kopie objektu
často vypadá stejně jako originál, ve skutečnosti
nikdy nebude tentýž objekt. Kořenový objekt definuje zprávu **equal:**,
kterou lze použít k porovnání identity objektů. Podívejte se na
následující příklad:

@test617

## Implicitní převod

XOScript používá k převodu objektů **implicitní převod**. Chce-li například
vypsat seznam na obrazovku, pošle XOScript seznamu interně zprávu
*řetězec*. To se může ukázat jako velmi užitečné v
případě, že chcete seznam vypsat jako seznam oddělený čárkami.
Zprávu *řetězec* lze přepsat: 

@test620

@api_String_base
@api_Format_base


## Serverové řetězce

Následující funkce objektu Řetězec přidává
serverový plugin.

@api_String_server

# Funkce

{{messages}}

Kód můžete seskupit mezi { a }, čímž se z něj stane funkce.
V xoscriptu někdy používáme také termín úloha nebo jednoduše
blok kódu.

Funkci spustíte posláním zprávy *spustit*.


```
{ Výstup psát: 123, nový-řádek. } spustit.
```

Pokud vaše funkce přijímá parametry, použijte **aplikovat:**.

```
{ :a Výstup psát: a, nový-řádek. } aplikovat: a.
```

Viz také příklady níže.
Kvůli jednoduché architektuře může mít funkce jen
jeden bod návratu. Abyste se vyhnuli režii nebo nadměrnému vnořování
podmínek, můžete použít postup (což je totéž jako použití
znaménka násobení s parametrem 1):

```
{
  (a = 1) pravda: { x := 1. }, přestat.
  (a = 2) pravda: { x := 2. }, přestat.
} postup.
```

Tímto způsobem se (a = 2) nevyhodnotí, pokud a = 1.
Navíc tak nepotřebujete vnořené zprávy pravda.
Kdykoli zjistíte, že vnořujete podmínky, vzpomeňte si
na zprávu postup. Váš kód tak může být
čitelnější.


Zde je důležitá záludnost:

```
{
	Nepravda nepravda: {
		Výstup psát: ['Ukonči smyčku.'].
	}, přestat.
	
	Výstup psát: ['Neukazuj mě.'].

} postup.

```

V tomto případě se text 'Dont show me' zobrazí,
protože **přestat** je posláno objektu Nepravda. Chcete-li provést
přerušení, musí být posláno jako zpráva objektu **Pravda**.
 

```
{
	Nepravda ne pravda: {
		Výstup psát: ['Ukonči smyčku.'].
	}, přestat.
	
	Výstup psát: ['Neukazuj mě.'].

} postup.

```

Bude fungovat podle očekávání.

## Výjimky

Výjimky lze zpracovat takto:

```
{ Úkol 1 } chytit: { Úkol 2 }, spustit.
```

Ve svém programu můžete také úmyslně vyvolat chybu, a
tím aktivovat obslužný blok. To se provede posláním
zprávy **chyba:** aktuální úloze, jak ukazuje následující
ukázka:

```
{
tato-úloha chyba: ['Jejda!'].
} chytit: { :omyl
Výstup psát: omyl.
}, spustit.
```

## Vkládání hodnot

XOScript umožňuje do úloh vkládat hodnoty. Podívejte se
na úlohu níže:

```
>> odesílání := {
	Zpravodaj komu: vlastní recipient.
}.
odesílání nastavit: ['recipient']
na: ['info@recipient.org'].
odesílání spustit.
```


Tato ukázka představuje smyšlenou úlohu, která posílá zpravodaj
na e-mailovou adresu neboli **příjemci** (recipient). Tohoto příjemce lze do úlohy vložit
zvenčí a před spuštěním úlohy, a to posláním
zprávy **nastavit:na:** úloze. Tím se hodnota
**recipient** v úloze předem nastaví. Tuto hodnotu lze také změnit
a úlohu pak spustit znovu. Je to užitečná metoda při práci s
objekty úloh.

## Prázdné funkce

Prázdné úlohy nejsou dovoleny. Teoreticky by prázdná úloha vypadala
takto: **{}**, XOScript to však vnímá jako jazykovou chybu. Pokud
chcete deklarovat prázdnou úlohu, můžete použít objekt Nic:

```
>> úkol := Nic.
```

Ačkoli to není skutečná úloha, ale objekt Nic, zprávu spustit
mu lze přesto poslat:

```
>> odpověď := úkol spustit.
```

Ve skutečnosti je to totéž jako:

```
>> odpověď := Nic spustit.
```

Protože objekt **Nic** nerozpozná zprávu **spustit**,
vrátí jako odpověď sám sebe, takže odpovědí je opět **Nic**.
Prázdná úloha tedy není nutná. Díky elegantnímu
návrhu programovacího jazyka XOScript můžete k tomuto účelu jednoduše použít objekt
Nic.

## Dynamický rozsah platnosti

Když Funkce potřebuje proměnnou, ale nemůže ji najít,
prohledá proměnné Funkce, která ji **zavolala**,
a pokračuje v hledání dále po řetězci Funkcí.
Tento proces hledání pokračuje, dokud se proměnná nenajde.
Pokud se proměnná přesto nenajde, objeví se chybové hlášení. Tento způsob hledání
proměnné se nazývá **dynamický rozsah platnosti**.

Ukázka tohoto principu:

@test618

@api_Code_base

# Kořenový objekt

{{messages}}

Objekt nazvaný **Objekt** je kořenovým objektem všech objektů v
XOScriptu a poskytuje základní funkce jazyka. 

Nejčastěji posílanou zprávou
je **při:udělat:**, která rozšiřuje funkce objektu. Tuto
zprávu přijímá kořenový objekt, který následně propojí
zadanou úlohu se zprávou, a tím rozšíří odvozený
objekt.

## Záchytné metody

Pokud pošlete zprávu, která neodpovídá žádné
metodě objektu, je obvykle ignorována. Můžete však určit
takzvané **magické metody** neboli **záchytné** metody, které
se vyvolají, pokud objekt zprávě nerozumí.

K dispozici jsou 4 záchytné metody. Každá zpráva odpovídá
určitému počtu parametrů.

Záchytná zpráva      | Počet parametrů
-------------------- | -------------------
odpovědět:           | 0
odpovědět:a:         | 1
odpovědět:a:a:       | 2
odpovědět:a:a:a:     | 3


@test619

## Programové zprávy

Místo poslání zprávy přímo objektu ji lze také
poslat prostřednictvím proměnné. K tomu slouží zpráva
**zpráva:parametry:**. 

@test396

@api_Object_base

# Seznamy

{{messages}}

XOScript zná dva typy kolekcí: *seznamy* a *slovníky*.
**Seznamy** jsou výčty objektů v *pevném pořadí*. Slovníky nemají
žádné pořadí, místo toho připomínají legendu, v níž je klíč (neboli pojem) a jemu
odpovídající hodnota. Seznamy jsou srovnatelné s poli (PHP, Java, C)
a seznamy (Python). Slovníky jsou srovnatelné s asociativními poli (PHP) nebo
slovníky (Python) v jiných programovacích jazycích. Chcete-li vytvořit
nový Seznam, napište:

```
>> fibonacci := Seznam nový.
```

Tento prázdný seznam lze naplnit pomocí **připojit:** :

```
fibonacci připojit: 0.
fibonacci připojit: 1.
fibonacci připojit: 1.
fibonacci připojit: 2.
fibonacci připojit: 3.
fibonacci připojit: 5.
fibonacci připojit: 8.
fibonacci připojit: 13.
```

Pokud seznam vypíšeme na obrazovku:

```
Výstup psát: fibonacci, nový-řádek.
```

Uvidíme:

```
Seznam ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

Místo připojit můžete k přidání prvků do seznamu použít také ;:


```
>> fibonacci := Seznam nový ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Středníky (;) jsou všechny binární zprávy, které vkládají
hodnotu do seznamu.

## Řetězení

Předpokládejme, že máte seznam jako:

```
>> x := Seznam nový ; 1 ; 2 ; 3.
```

Pokud byste chtěli smazat první a poslední prvek, vaše
zpráva by byla:

```
x vysunout-začátek vysunout-konec.
```

Předchozí zápis bohužel nebude fungovat správně.
Zpráva **vysunout-začátek** vrací první prvek seznamu, který
se zase stane příjemcem zprávy **vysunout-konec**. Zpráva
**vysunout-konec** tedy není poslána objektu **x**, ale číslu 2.
Možným řešením tohoto problému by bylo vytvořit dvě samostatné
věty, například: 

```
x vysunout-začátek.
x vysunout-konec.
```

To je však poměrně nepraktické, zejména když potřebujete
smazat více než dva prvky. Proto XOScript nabízí pro tyto
situace alternativní strukturu zpráv. V
**alternativních** strukturách zpráv jsou odpovědi objektů ignorovány
a jako odpověď dostáváte znovu a znovu přijímající objekt.
**Alternativní** struktura zpráv se zahájí posláním
zprávy **udělat** objektu a **alternativní** strukturu
zpráv lze ukončit posláním zprávy **hotovo**. V
uvedeném příkladu by to šlo použít takto:

```
>> x := Seznam nový ; 1 ; 2 ; 3.
x udělat vysunout-začátek vysunout-konec hotovo.
```

@api_List_collections

# Slovníky

{{messages}}

**Seznam i Slovník jsou kolekce. Na rozdíl od
seznamu však slovník **nemá žádné** pořadí. Další rozdíl mezi nimi
spočívá v tom, že slovník se skládá z dvojic objektů. Jeden objekt slouží jako heslo (neboli
klíčové slovo), pomocí něhož se hledá druhý objekt. Dobrým příkladem
seznamu je ceník, například:


```
>> nabídka := Slovník nový
	umístit: ['£5'] na: ['jablečný koláč'],
	umístit: ['£6'] na: ['mrkvový dort'],
	umístit: ['£3'] na: ['fudge'].
```

Podobně jako u seznamu se k přidání objektu do seznamu používá zpráva umístit:na:.
Rozdíl je v tom, že na rozdíl od
seznamu se propojují dva objekty. První objekt je, podobně
jako u seznamu, objekt, který do seznamu uložíte. Druhý
objekt není jeho pozicí v kolekci, ale **heslem**,
které umožňuje předchozí objekt později získat. Stručně
řečeno, slovník funguje trochu jako výkladový slovník: pomocí hesla
lze najít význam. Například chcete-li z výše
uvedeného seznamu zjistit cenu karamelky:

```
>> price := nabídka na: ['fudge'].
```

Můžete použít také stručný zápis:

```
>> price := nabídka ? ['fudge'].
```

Pokud hesla, která používáte k ukládání objektů, neobsahují mezery
(a nekolidují s jinými předdefinovanými zprávami),
lze použít i následující zápis:

```
>> nabídka := Slovník nový
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Výše uvedený zápis se bezpochyby čte o něco přirozeněji.
K zjištění ceny
karamelky lze použít následující zjednodušený zápis:

```
>> price := nabídka fudge.
```

@api_Dict_collections

# Soubor

{{messages}}

Objekt **Soubor** poskytuje základní přístup k souborovému systému.
Pomocí tohoto objektu můžete načíst celé soubory do proměnné
najednou nebo najednou zapsat proměnné do souborů. Podporováno je také
čtení po řádcích. To jsou nejběžnější operace se soubory
ve skriptovacím jazyce. Pokročilé operace se soubory vyžadují
použití FFI prostřednictvím serverového pluginu nebo samostatného IO pluginu.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Datum a čas

{{messages}}

Pro strukturovanou reprezentaci času a data používá XOScript
objekt **Okamžik**. Pokud se nový objekt Okamžik vypíše na obrazovku,
zobrazí se aktuální datum a čas:

```
Výstup psát: Okamžik nový, nový-řádek.
```

Výsledkem může být například:

```
2020-10-10 12:16:39
```

Je také snadné přečíst jednotlivé složky času. Pokud tedy
například potřebujete znát jen aktuální rok, můžete okamžiku
poslat zprávu **rok** a odpovědí bude
objekt Číslo obsahující pouze rok:

```
>> m := Okamžik nový.
Výstup psát: m rok, nový-řádek.
```

@api_Moment_system

# Program/Standardní výstup

{{messages}}

Objekt Program představuje právě běžící aplikaci. Tento objekt
nabízí funkce pro spouštění systémových příkazů, vkládání podprogramů,
čtení parametrů a další. Všechny funkce související se systémem.

## Standardní výstup

Výstup je objekt standardního výstupu. Má v podstatě dvě metody:
**psát:** a **nový-řádek**. Zpráva psát: slouží k poslání řetězce
na stdout, zpráva nový-řádek vypíše znak nového řádku.
Místo **nový-řádek** můžete použít také \\n.

Příklad:

```
Výstup psát: ['Hello World'], nový-řádek.
```

výsledek:

```
Hello World
```

## Moduly/pluginy

Svět XOScriptu lze rozšířit o nové systémové objekty
instalací modulů. Nový systémový objekt lze do světa
XOScriptu přidat umístěním souboru modulu (obvykle souboru s příponou .so)
do složky mods. 

Když pošlete zprávu objektu, který je zpřístupněn
prostřednictvím modulu pluginu, XOScript ho automaticky načte.

Pluginy můžete psát i sami. Pluginy se píší v
programovacím jazyce C. Ukázkový plugin najdete v balíčku zdrojového
kódu v src/plugins/example.


## Reflexe

Existují různé způsoby, jak
zkoumat systém během provádění programu. XOScript obsahuje několik metod pro
zjištění, které objekty jsou přítomny a na které zprávy tyto objekty
reagují. Zaprvé se lze každého objektu zeptat, jakého je **typ** (typu),
typy jsou však v XOScriptu proměnlivé, a proto nespolehlivé.

Objektu Program se lze také zeptat, zda je
daný objekt již v programu přítomen:

```
Program Nástroj pravda: { ... }.
```

V případě názvu objektu,
který se skládá z jediného symbolu, je nejlepší použít
následující zápis, aby nedošlo k nejasnostem:

```
Program hledat: ['X'], pravda: { ... }.
```

Kromě dotazů na objekty je stejně tak možné ptát se
objektu Program na zprávy. Lze se ho například zeptat, zda
objekt **Číslo** zná zprávu **mezi:a:**, způsobem,
který je znázorněn níže:

```
Program Number: ['between:and:'], nový-řádek.
```

@api_Program_system

# server

{{messages}}

Plugin Server v xoscriptu nabízí funkce pro
tvorbu serverových aplikací. Serverový plugin
načtete pomocí:

```
Server inicializovat.
```

Pro vaše pohodlí se také doporučuje načíst
soubory webtools.xo a template.xo.

```
Program použít: ['webtools.xo'].
Program použít: ['template.xo'].

```

## Nastavení serveru

Můžete nastavit následující nastavení serveru:

```
	# jsou dány výchozí hodnoty,
	# takže pokud nic nenastavíte, použijí se
	# tyto hodnoty...

	Program 
	nastavení: ['max-postfields']
	hodnota: 40.

	Program 
	nastavení: ['max-contentlength']
	hodnota: 2000000. # 2MB

	Program 
	nastavení: ['max-time']
	hodnota: 5000. # 5sec

```

## Hello World

Zde je velmi jednoduchý webový program, který můžete použít se
standardním CGI serverem, jako je Apache2, NGINX, OpenHTTPD, nebo s jakýmkoli jiným
známým serverem.

```
#!/bin/xo

Server inicializovat.
Program použít: ['webtools.xo'].

>> webový-dokument := Webový-dokument nový.

webový-dokument vypsat: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Pokud nechcete používat objekt Webový-dokument, nevadí, ale
pak musíte HTTP hlavičky napsat sami:

```
#!/bin/xo
Výstup psát: ['Content-type: text/html; charset=utf-8 \n\n'], nový-řádek.
Výstup psát: ['nazdar světe!'], nový-řádek.
``` 

## Požadavek

Objekt HTTP-Požadavek lze použít k získání dat GET/POST/COOKIE a
UPLOAD:

```
>> požadavek  := HTTP-Požadavek nový.
>> search   := požadavek get: ['search']. # ?search=books
>> password := požadavek post: ['password']. # z formuláře
>> vybrané := požadavek get-seznam: ['sel[]']. #?sel[]=1&sel[]=2
>> vybrané := požadavek post-seznam: ['sel[]'].
>> cookie   := požadavek cookie: ['session-id'].
>> nahraný-soubor   := požadavek upload: ['file'].
>> dočasná-cesta := nahraný-soubor ? 1.
>> název-souboru := nahraný-soubor ? 0.
```

## Maxpost/length

Výchozí maximální počet polí POST je 40 a výchozí maximální délka
obsahu je 2MB. Jiné nastavení pro jednotlivé skripty:

```
Program nastavení: ['max-contentlength'] hodnota: 1. 
Program nastavení: ['max-postfields'] hodnota: 1. 
```

{{note}}
Pokud délka obsahu překročí maximum,
proces je ukončen, protože si již nemůžeme být jisti,
že je obsah bezpečný.
{{/note}}

Limit maxtime určuje maximální dobu v ms
pro čtení stdin/postdata.

```
Program nastavení: ['max-time'] hodnota: 5000. # 5sec
```

To se týká pouze I/O čtení dat POST a zabraňuje
útokům typu slowloris. Pokud opravdu chcete omezit
dobu provádění jakékoli operace, použijte Program budík:.

## Databáze

Objekt Database lze použít k dotazování MariaDB/MySQL.
K připojení k databázi použijte:

```
>> db := Maria-DB nový hostitel: ['localhost'],
	uživatel: ['xo'],
	heslo: ['pass123'],
	název-databáze: ['xobase'],
	připojit.

```

K vložení záznamu použijte:

```
>> parametry-hledání := db dotaz: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parametry: ( Seznam nový ; ['abc'] ; 12.35 ; 6 ). # parametrizované dotazy

{  parametry-hledání provést. db potvrdit. }
chytit: { :e db vrátit-zpět.  }, spustit.
```

Upozorňujeme, že xoscript pracuje *pouze* s transakcemi a nikdy nepotvrzuje automaticky (autocommit).
Pokud nelze autocommit vypnout, dostanete chybu připojení.
U dotazů vždy používejte vázání parametrů, nikdy nepřidávejte uživatelský vstup přímo
do SQL.

Vložené id získáte takto:

```
Výstup psát: ['VLOŽENO: '] + parametry-hledání insert-id, nový-řádek. # id vložení
```

Načtení záznamů:

```
>> parametry-hledání :=
db
	dotaz: ['SELECT * FROM book order by id desc limit 2'], 
	načíst: { :řádka 
		Výstup psát: řádka id + [' '] + řádka description + [': '] + řádka price, nový-řádek.
	}. # načítání řádků

```

## Relace

Pro trvalost můžete ukládat a načítat data z objektu relace.
Nejprve vytvořte nový **Webový-dokument**. Objekt Webový-dokument spojuje
požadavek, hlavičky, HTML a relaci. Je to proto, že když
navštívíte webovou stránku v prohlížeči, vidíte jen HTML. Celý
Webový-dokument se však skládá také z **hlaviček**. Například
většina HTTP odpovědí obsahuje hlavičku jako: Content-type:text/html,
která prohlížeči sděluje, že následující data se mají vykreslit jako HTML
(a ne například stáhnout jako soubor). Relace jsou způsob, jak
ukládat uživatelská data mezi požadavky. Abychom tato data mohli sledovat, musíme
nastavit cookie, a tato cookie se také nastavuje prostřednictvím hlavičky. Proto
se vše spojuje ve Webovém-dokumentu (protože je to úplný
dokument obsahující hlavičky i HTML nebo jiná data).


```
# Nejprve vytvoříme novou instanci Webový-dokument
>> web := Webový-dokument nový.

# Nyní spustíme relaci; tím se vygeneruje hlavička pro cookie a
# vytvoří se soubor pro vaše data, spojený s touto cookie
>> relace := web zahájit-relaci.

# Nyní můžeme s relací zacházet jako se Slovníkem
relace userid: 123.
```

Zrušení relace (při odhlášení):

```
web zničit-relaci.
```

## Hlavičky

Webový-dokument vám také umožňuje nastavit další známé hlavičky.
Například pokud chcete uživatele přesměrovat na jinou URL:

```
web přejít-na: ['/other.html'].
```

Tento příkaz pod kapotou také vygeneruje HTTP hlavičku, která se pošle
spolu s vašimi dalšími daty nebo HTML a dá prohlížeči pokyn přejít
na zadanou cílovou adresu.

Přidání vlastní hlavičky:

```
web hlavička: ( 
	HTTP-Hlavička nový
	klíč: ['Content-Length']
	hodnota: 400
).
```

Zobrazení stránky 404:

```
web nenalezeno: ['Jejda..'].
```


## Šablony

Výchozí šablonovací systém je velmi jednoduchý. Nemusíte se učit
novou šablonovou syntaxi. Šablonovací systém navíc zajišťuje skutečné oddělení
prezentace a obchodní logiky.

Vytvoření šablony ze souboru:

```
>> tpl := web šablona: ['templates/ux.tpl'].
```

Šablonovací systém používá značky. 
Existují tři typy značek: značky výřezu, značky vložení a
značky slotů. Základní myšlenka je opravdu jednoduchá: vyříznete
oblasti označené značkami výřezu a můžete je vložit na
místa označená značkami vložení. Do značek slotů můžete
vkládat řetězce.

Například v následující šabloně vložme
drahokam do šperkovnice a přidejme cenovku.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Můžete to udělat takto:

```
>> gem := tpl vyříznout: ['gem'], kopírovat.
gem price: 99.
tpl vložit: gem na: ['jewels'].
web vypsat: tpl uklidit.
```

Poslední řádek jednoduše odešle šablonu jako řetězec klientovi
spolu s požadovanými HTTP hlavičkami.

Výsledek:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

K bezpečnému poskytování souborů nahraných uživateli se můžete spolehnout na passthru:

```
>> nahráno := ['smile.gif'].
Server předat: nahráno prefix: ['/uploads/images/'].
Program konec.
```

Tím se obsah nahraný uživatelem poskytne s odpovídajícím
typem MIME. Podporovány jsou pouze povolené typy MIME:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF a SVG.
Soubory SVG, ZIP a GZIP se odesílají ke stažení, protože SVG
může obsahovat skripty, které by se jinak spustily na vaší doméně.
Tato metoda zabraňuje útokům TOCTOU, procházení cest (path traversal),
spouštění škodlivého kódu (injection), útokům přes symbolické odkazy,
útokům DDoS (limit souboru = 50MB), odposlechům (sniffing) a
různým dalším bezpečnostním problémům.


## JSON

Zakódování objektu jako JSON:

```
>> json := ( JSON jsonify: ( 
	Slovník nový umístit: ( 
		Seznam nový ; 1 ; 2 ; 3
	) na: ['abc']
)).
```

Dekódování JSON do objektu xoscriptu:

```
>> slovn := ((JSON objekt: json) abc ? 1).
```

JSON s více než 500 úrovněmi vnoření je odmítnut jako neplatný.

Přímý výstup Slovníku jako json se správnými hlavičkami:

```
web json: slovn.
```


## Regulární výrazy

Regulární výrazy můžete používat vytvořením vzoru.
Například pro nalezení odkazů href a cílů hypertextových odkazů:

```
Vzor nový: ['href="([^"]+)" target="([^"]+)"'].
```

Nyní aplikujte vzor na zkoumaný řetězec takto:

```
vzorek shoda: předmět udělat: { :m :x .... }
```

Úplný příklad:

```
>> předmět := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> vzorek := Vzor nový: ['href="([^"]+)" target="([^"]+)"'].
>> výsledek  := vzorek shoda: předmět udělat: { :m :x
	Výstup psát: m, nový-řádek.
	Výstup psát: x, nový-řádek.
	<- ['XXX'].
}.
Výstup psát: výsledek, nový-řádek.
```

## Síťová komunikace

K provedení webového požadavku použijte objekt Síť.
Objekt Síť vždy posílá požadavek POST, pokud jako data nepošlete
Nic; pak pošle požadavek GET.


```
Síť 
post: Nic 
na: ['https://redbeanphp.com'].
```

## Šifrování

Serverový plugin obsahuje šifrování založené na XChaCha20 a Argon2.

Příklad:

```
>> zašifrováno := Trezor šifrovat: ['hello'] klíč: ['world'].
>> dešifrováno := Trezor šifrovat: zašifrováno klíč: ['world'].
```

## Tokeny

Vygenerování kryptograficky bezpečného tokenu určité délky:

```
>> můj-token := Trezor token: 40.
```

Tím se vygeneruje token o 40 znacích.

## Formátování

Objekt Formát umožňuje formátovat data, například doplňovat mezerami nebo
přidávat nuly. Používá syntaxi printf.

```
>> fmt := Formát nový: ['%06.0f'].
fmt aplikovat: 56. # dává 000056
```

Formát může obsahovat jeden převod a ten musí odpovídat hodnotě,
jinak dostanete chybu:

- `aplikovat:` s řetězcem: `%s`
- `aplikovat:` s číslem: `%f`, `%e`, `%g` nebo `%a`
- `aplikovat-celé:` s číslem: `%d`, `%i`, `%o`, `%u`, `%x` nebo `%c`

Hodnoty z požadavku jsou řetězce. Chcete-li jednu z nich formátovat jako číslo,
nejprve ji převeďte:

```
fmt aplikovat: (požadavek get: ['amount']) číslo.
```

## Kodéry

K dispozici je několik kodérů a dekodérů.
Kodér url připraví url pro použití v HTML jako odkaz:

```
Server url-kódovat: ['https://example.com?a=6&b=1 2'].
```

Chcete-li bezpečně vložit uživatelský vstup do HTML bez rizika
útoků XSS, vždy použijte:

```
Server html-kódovat: ['<neškodné>'].
```

Upozorňujeme, že šablonovací systém vždy provádí kódování HTML,
pokud zapisujete do značky slotu. Pokud tedy používáte šablonovací systém,
nemusíte toto používat.

## Posílání pošty

K odeslání e-mailu použijte knihovnu mailtools.xo.

Příklad:

```
Server inicializovat.
Program použít: ['mailtools.xo'].

>> e-mail := HTML-Email nový.
>> img := e-mail přiložit: ( Soubor nový: ['myimage.png'] ).

e-mail
odesílatel: ['xo@xoscript.com'] název: ['xo'],
komu: ( Seznam nový ; ['xo2@xoscipt.com'] ),
předmět: ['xoxo'],
tělo: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), odeslat.

```



## Propojování

Pomocí zprávy propojit: můžete ke svému programu připojit externí
knihovnu pomocí libffi. Podrobnosti najdete v kapitole o ffi.


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

FFI je poskytováno podle platformy/pluginu, protože je
svázáno s podkladovou architekturou systému, což
jádro dělat nemá.
Serverový plugin nabízí vyhovující implementaci ffi/blobů.
Ve výchozím stavu se jádro připojuje k cílové platformě
prostřednictvím stdin/stdout, omezených služeb souborového I/O a shellu (Program systém:).
Další integraci poskytují ffi/bloby prostřednictvím pluginů zaměřených
na aplikace, jako je serverový plugin.

FFI znamená Foreign Function Interface (rozhraní pro cizí funkce). Umožňuje používat funkce, které napsali jiní v
jiných programovacích jazycích a které jsou poskytovány v souborech DLL, SO nebo Dylib. Může jít
o nejrůznější funkce a touto cestou je k dispozici obrovské množství funkcionality.
Začněme příkladem:

```
Server propojit: (
 Seznam nový ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Seznam nový ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s uvolnit.
```

Výsledkem tohoto kódu je, že na příkazovém řádku uvidíte následující:
FFI has 3 letters.
Teď si asi říkáte: „To je hodně kódu na něco tak jednoduchého.“
Nešlo by to přece vyřešit příkazem Gui show? Odpověď zní jednoznačně ano!
Tohle je však myšleno jako názorný příklad.
FFI se obvykle používá pro složitější úlohy, ty však nejsou dobrými
příklady, a tak jsem zvolil něco triviálního.

Parametry metody propojit:

- Parametr č. 1: Soubor DLL nebo SO, který chcete použít.
- Parametr č. 2: Funkce v tomto souboru, kterou chcete připojit.
- Parametr č. 3: Seznam s názvy datových typů parametrů funkce.
- Parametr č. 4: Název návratového typu funkce.
- Parametr č. 5: Název objektu, ke kterému chcete tuto funkci připojit (pokud neexistuje, bude vytvořen
automaticky).
- Parametr č. 6: Zpráva, ke které má být tato funkce připojena.

Ve výše uvedeném příkladu chceme připojit funkci printf z libc.so. Názvy datových
typů najdete v dokumentaci softwaru, ke kterému se připojujete. Dostupné typy jsou:
void, pointer, float, double, int, uint, char, uchar, intX a uintX,
kde X může být 8, 16, 32 nebo 64.

Tyto typy odkazují na počet bajtů potřebných k uložení dat. U printf se připojujeme k
novému objektu nazvanému Printf a zprávě template:number:. Externí
funkci před použitím převedete do dialektu XOScriptu. Zpráva template:number: očekává
jako svůj první parametr buffer s textem šablony. Tento buffer vytvoříme pomocí objektu Blob, který
umožňuje ručně alokovat paměť. Za následné uvolnění této paměti
zprávou uvolnit odpovídáte vy.

Paměťový blob můžete naplnit různými způsoby. V našem příkladu ho plníme textem, takže používáme
zprávu utf8: (UTF-8 je kódování pro převod textu na bajty). Blob můžete naplnit také
pomocí bytes:, které předáte seznam hodnot bajtů. Ke čtení obsahu blobu použijte od:délka:.
Bajty dostanete zpět jako seznam. Pomocí objektu Blob můžete dokonce vytvořit C-strukturu
zprávou struct:, které předáte posloupnost typů jazyka C. To může být nutné při volání funkce
jazyka C v externí softwarové knihovně, která očekává ukazatel na strukturu.

{warning}
Bloby musíte uvolňovat sami.
Bloby nejsou uklízeny garbage collectorem.
{/warning}

Protože bloby lze vyměňovat s externími funkcemi z knihoven,
nemohou být automaticky uklízeny garbage collectorem (mohou zůstat používány
externími funkcemi nebo je tyto externí funkce mohou chtít uvolnit
samy). Proto musíte bloby v případě potřeby uvolňovat sami.

Uvolnění blobu:

```
můj-blob uvolnit.
```

Uvolnění struktury:

```
můj-struct uvolnit-struct uvolnit.
```

U struktury tedy musíte k dealokaci paměťového bloku poslat dvě zprávy:
uvolnit-struct a uvolnit.

@api_Blob_fficonnect
