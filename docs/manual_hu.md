# Alapok

{{messages}}


Üdvözöljük az XOScript világában
Az XOScript projekt célja egy egyszerű és auditálható szkriptnyelv létrehozása.
Az egyszerű nem feltétlenül jelent könnyűt.
Egy ismerős programozási nyelvet könnyebb lehet használni, mint az XOScriptet.
Itt az egyszerűség mást jelent:
azt, hogy teljes mentális modellt alkothatunk a nyelvről és a viselkedéséről.

Az XOScriptet úgy tervezték, hogy elférjen a fejünkben.
A nyelvtana és a fogalmainak száma szándékosan kicsi.
Nincsenek osztályok; az objektumok közvetlenül bővíthetők.
Az objektumok átadása hivatkozással történik, a másolás explicit,
a függvényeknek pedig egyetlen kilépési pontjuk van.

E döntések némelyike jelentősen eltér az elterjedt nyelvekétől.
Az XOScriptnek például nincs típusrendszere, és dinamikus hatókört használ.
A nem kezelhető üzeneteket figyelmen kívül hagyja, ahelyett hogy kivételt váltana ki.
Ezeknek a döntéseknek következményei vannak, és nem a hibák kiküszöbölését szolgálják.
Céljuk, hogy a nyelv mögöttes modellje kicsi és következetes maradjon.

Az XOScript lokalizálható is, így az üzleti szabályok természetes nyelven
fogalmazhatók meg, és akár nem műszaki érintettekkel is megoszthatók.

Az auditálhatóság azt jelenti, hogy ugyanezt a filozófiát alkalmazzuk a megvalósításra is.
A futtatókörnyezet C nyelven készült, egy kicsi, kézzel írt lexerrel, parserrel és fabejáróval.
A standard könyvtár és a futtatókörnyezet nagyrészt a nyelv szerkezetét követi,
így az XOScript-kód és a megvalósítása közötti kapcsolat viszonylag közvetlen.

A tesztek is szorosan kapcsolódnak a dokumentációhoz.
Minden metódushoz tartoznia kell egy tesztnek, amely beépíthető a kézikönyvbe,
így a dokumentáció összhangban marad a megvalósítással.

Az XOScript nem kíván funkciókban vagy ismertségben versenyezni
az elterjedt nyelvekkel. Más célt követ:
olyan programozási környezetet, amelyet egy fejlesztő egészében megérthet.

A remény az, hogy egy kis nyelv és egy kis
megvalósítás révén a szoftver a gyakorlatban is megérthető
a bájttól az objektumig, a szintaxistól a futtatókörnyezetig, és magabiztosan
írhatunk kódot, mert értjük, mi történik
a szkriptben, és mi történik a motorháztető alatt.

Egy xoscript-alapú szerverkörnyezet architektúrája
egyszerű, mégis rugalmas.

{{architecture.png}}

Ha az xoscriptet szerveroldali nyelvként szeretné használni, telepítenie kell a
szerverbővítményt a /mods/server nevű mappába.

Ennek az az oka, hogy szeretjük
a nyelv magját elválasztani a szerverspecifikus funkcióktól,
ellentétben például a PHP-vel vagy a Pythonnal. Különben mindenkinek
céltalanul az egész konyhát a mosogatóval együtt kellene szállítanunk, ami egyszerűen butaság.
Ha szeretné, más modulokat is telepíthet. A rendszer nagyon
rugalmas.

Emellett egyes funkciókat jobb magában a szkriptnyelvben
megvalósítani, például a sablonkezelést és a munkamenet-kezelést, ezért
a kényelem kedvéért a template.xo és a webtools.xo könyvtárat is mellékeljük.
Mindennek az az oka, hogy nem tudjuk, Ön hogyan szeretné
használni az xoscriptet. Használhatja szerveroldali szkriptnyelvként,
de grafikus felületekhez, beágyazott eszközökhöz vagy egyszerű kötegelt feldolgozáshoz is.
Még ha szerveroldali szkriptnyelvként használja is (ami
jelenleg az egyik fő felhasználási terület), előfordulhat, hogy
más sablonmotort vagy más munkamenet-kezelőt szeretne használni.
Kik vagyunk mi, hogy eldöntsük, a miénket kell használnia?

A saját sablonmotorunk használatának egyik előnye viszont, hogy
nem kell további szintaxist megtanulnia a sablonok készítéséhez.
Az xoscripttel szállított alapértelmezett sablonmotor 100%-osan
elválasztja a megjelenítést és a logikát. Különleges
sablonszintaxis helyett egyszerűen egy nagyon rugalmas helyjelölő-rendszert használ.
További információért lásd a Szerver fejezetet.

Vegye figyelembe, hogy ha nem az alapértelmezett sablonmotort vagy
az alapértelmezett webtools könyvtárat szeretné használni, akkor magától értetődően
a sajátját kell biztosítania.

Ha a webszervert chrootban, jailben vagy másfajta sandboxban futtatja,
akkor az xo függőségeit is telepítenie kell abba a környezetbe; hogy
mely könyvtárakra van szükség, azt az ldd segítségével tudhatja meg (lásd a Linux vagy BSD kézikönyvoldalát).
Ha shellparancsokat szeretne használni az xo-szkriptjeiben, másoljon egy shellt is
(például bash vagy ksh) ebbe a környezetbe.

Szeretnénk azt is megjegyezni, hogy a visszafelé kompatibilitást nagyon komolyan vesszük.
Létezik egy külön visszafelé kompatibilitási funkció is, amelynek neve
'version'. Általánosságban arra törekszünk, hogy a kódja örökké fusson. Így
soha nem kell majd frissítenie a kódját ahhoz, hogy kompatibilis maradjon az xoscript
újabb verzióival. A célunk: írd meg egyszer, fusson örökké.

A kézikönyv további része az xoscript programozási nyelv részletes
ismertetésével foglalkozik. A szerveroldali szkriptelést a Szerver című
fejezet tárgyalja. Ha tapasztalt szoftverfejlesztő, érdemes lehet
néhány fejezetet átugrania, mert némelyik kissé túl részletes, vagy
nagyon hasonlít az általános programozási gyakorlathoz. Azok tehát,
akiknek már több más programozási nyelvben is van tapasztalatuk,
jobban teszik, ha ezt a kézikönyvet referenciaként kezelik.

## Telepítés Linuxon

Töltse le az apache2-t és a mariadb-t:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Töltse le az xoscriptet.
Az X helyére írja a megfelelő verziószámot!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Másolja a fájlokat a webgyökérbe és a /bin könyvtárba:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Szerkessze az apache2 konfigurációját:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Cserélje a Virtualhost részt erre:

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

Hozzon létre egy tesztoldalt:

```
sudo nano /var/www/html/test.xo
```

és írjon egy kis tesztprogramot:

```
#!/bin/xo
Server inicializál.
Program használ: ['webtools.xo'].
>> web := Webdokumentum új.
web kiír: ['Hello World'].
```

Engedélyezze, hogy az apache2 CGI-n keresztül futtassa a programot:

```
sudo chmod uog+x /var/www/html/test.xo
```

Indítsa újra az apache2-t:

```
sudo systemctl restart apache2
```

Nyissa meg a tesztoldalt a böngészőben:

```
http://localhost/test.xo
```

A következőt kell látnia:

```
Hello World
```


## Telepítés OpenBSD-n

Szerkessze az /etc/httpd.conf fájlt, és adja hozzá:


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

Ha SSL-t szeretne használni:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Ha a kulcscserét kvantumszámítógépes támadások ellen is védeni szeretné,
válassza az mlkem titkosítót:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Helyezze el a chrootban az xo binárist és a modulokat, valamint az összes függőséget
(ezeket az ldd segítségével derítheti ki).

## Példák futtatása


A csomagban található egyik példaprogram futtatásához:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Például a FizzBuzz példa futtatása Linuxon:

```
./example.sh fizzbuzz Linux
```

Ugyanennek a példának a futtatása OpenBSD-n:

```
./example.sh fizzbuzz OBSD
```

A példa futtatása tiszta fordítással:

```
./example.sh fizzbuzz OBSD clean
```

## Egységtesztek

Az egységtesztek futtatása:

```
./runtests.sh
```

Az egységtesztek futtatása fordítás nélkül (csak tesztelés):

```
./runtests.sh nobuild
```

## Fordítás

Fordítás forráskódból Linuxon:

```
make clean
ISO="en" make
```

OpenBSD-n:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

A szerverbővítmény fordítása Linuxon:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

A szerverbővítmény fordítása OpenBSD-n:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Helló, világ

Miután a fájl a számítógépére került, kicsomagolhatja,
és a következő paranccsal indíthatja el az xo-t:

```
xo
```

Egy XOScript futtatásához mentse a programot egy fájlba, -xo
utótaggal (nem kötelező). Ezután írja a programfájl nevét
az XOScript parancs után:

```
xo myprogram.xo
```

Ha egy XOScript parancsot a programfájlt paraméterként megadva futtat,
az xo beolvassa és végrehajtja a programfájlt.

{{note}}
A programot úgy is elindíthatja, hogy az xo ikonjára húzza.
{{/note}}

{{warning}}
Egyes rendszereken előzetesen engedélyeznie kell, hogy az xo dinamikus
könyvtárakat töltsön be.
{{/warning}}

A hagyomány szerint minden új programozási nyelvben az első
programnak valamiféle köszöntésnek kell lennie a világ felé. XOScriptben egy
ilyen **Helló, világ** program így néz ki:

@test598

Ha ezt a szöveget egy fájlba mentjük, például hello.xo néven, a következőképpen
futtatható: .

xo hello.xo

Hello world


A program kimenetét a fent látható fekete ablakban láthatja.
A kézikönyvben végig ugyanezt a megjelenítést alkalmazzuk
a kimenet bemutatására.

{{note}}
A Kimenet szó nagy K betűvel íródik.
Az objektumok általában nagybetűvel kezdődnek,
kivéve, ha példányként viselkednek (nincsenek
saját metódusaik, csak adataik). Ez más programozási nyelvek
osztály- és példánykonvencióit tükrözi.
{{/note}}


## Szintaxis 

Az XOScript egy *tisztán* *objektumorientált* programozási nyelv. Ez azt
jelenti, hogy az xoscript mindent objektumnak tekint, ezért nincsenek
más *adattípusok*. Egy XOScriptben írt programban lényegében három
alapvető művelet létezik: az *értékadás*, az *üzenetküldés*
és a *válaszadás*. Az objektumok közötti üzenetváltás egy XOScript-program
kulcsfontosságú része. A három műveletet alább mutatjuk be:


Művelet         | Példa
--------------- | --------
értékadás       |  \>\> x := 1. 
unáris üzenetek | x páros?.
bináris üzenet  | 1 + 2.
kulcsszavas üzenet | x ettől: 0 hossz: 10.
válasz          | <- válasz.  


Ez a fejezet általános képet ad az XOScript nyelvről,
és ismerteti alapelveit. Az XOScript egy kis nyelv, amely
három műveletre épül (lásd az ábrát), ezek nagyjából hat nyelvtani
szabálynak felelnek meg. Ennyi kell a nyelv
elsajátításához.

Nem baj, ha elsőre nem minden egyértelmű: az összes építőelemet
a következő fejezetben (3) részletesen megvizsgáljuk, és az alapszabályokat
megismételjük. A jelen fejezet azonban főként általános
bevezetésként szolgál a nyelvhez. Az alapelveket röviden
elmagyarázzuk, és néhány releváns példával szemléltetjük. A hiányzó
részleteket később fejtjük ki.

Az XOScriptben a megjegyzéseket \# jel vezeti be. A következő sort
tehát a program figyelmen kívül hagyja:

```
# this is just a comment
```

## Változók

Változó létrehozásához
a változódeklaráció jelét használjuk: >>. A változó neve
minden jelet tartalmazhat, kivéve: <-, :=, szóközök,
pontok, vesszők, kettőspontok, idézőjelek [' '] és zárójelek ().
Ezenkívül egy változó nem állhat több sorból. Vegye figyelembe,
hogy a változó nem kezdődhet számmal vagy mínuszjellel.

Néhány példa érvényes változókra:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dollar'].
>> +plus := Igaz.
>> user-password := ['Pssst!'].
```

Érvénytelen változók például:


```
>> -123 := ['negative number'].
>> password of user := ['Classified'].
>> password.of:user := ['Classified'].
>> ,x := 10.
```

{{note}}
Egy szövegliterálban egyetlen karaktert sem kell
escape-elni (beleértve az aposztrófot, az idézőjelet
és a szöveghatárolókat sem), amíg
ez nem okoz kétértelműséget
a lexer számára.
{{/note}}

Miután egy változót deklaráltunk, szabadon használható. Ez azt jelenti,
hogy a deklarációs jelet csak a változó első használatakor
(a deklarációkor) kell kiírni.

Pontosabban: nem kezdhet el csak úgy értéket adni
a változónak *(x := 2)*, mert előbb deklarálnia kell a változót *(\>\>
x := 2)*. Ha viszont már deklarálta, megváltoztathatja az értékét
a deklarációs jel használata nélkül*(\>\> x := 2. x := 3.)*.

Vegye figyelembe, hogy a deklaráláskor kötelező értéket adni a változónak.
Más programozási nyelvekkel ellentétben nem deklarálhat változót
érték nélkül. Minden változót kifejezetten egy kezdőértékhez kell
kötni. Ugyanakkor nyugodtan inicializálhatja
a változót a **Semmi** objektummal. Ebben az esetben a változó
üresnek tekinthető *(\>\> x := Semmi.)*. Röviden: változót
kezdőérték nélkül deklarálni nem szabad. Tehát

```
>> x.
```

érvénytelen, és hibaüzenetet eredményez.

{{note}}
Az xoscript a változók dinamikus hatókörét használja;
a részletekért lásd a Függvények fejezetet.
{{/note}}


## Literálok

Az XOScript mindent objektumnak tekint, vagyis minden számot, szöveget
és kódrészletet. Az olyan számok, mint az 1, 2, 100, -999 és 1,234,
Szám objektumok. Az aposztrófok közötti összes szöveg Szöveg
objektum. A kapcsos zárójelek {...} közé foglalt összes kódrészlet
Függvény objektum.

Literál         | Gyökérobjektum | Példa
--------------- | ------------ | ----------
számok          | Szám         | 1,2,3... 
szövegek        | Szöveg       | \['hello'\]
függvény        | Függvény     | { 1 + 2. }.
                
     
Az olyan objektumok, mint a számok és a szövegek, mindig egy gyökérobjektumból
származnak. Például minden szám a **Szám** objektumból származik. Minden
szöveg a **Szöveg** objektumból, minden kódrészlet pedig a **Függvény** objektumból
származik. Ezek az objektumok pedig mind az **Objektum** objektumból erednek, amely
valójában az összes objektum gyökérobjektuma.


## Üzenetek

Az XOScriptben programozni alapvetően azt jelenti,
hogy üzeneteket küldünk objektumoknak. Egy objektumnak küldött üzenet
általános jelölése a következő:

```
<object> <message>
```

Ha például azt szeretnénk megtudni, hogy a **2** páros szám-e,
a **páros?** üzenetet küldjük a **2** objektumnak:

```
2 páros?
```

A válasz **Igaz** lesz (ez is egy objektum). Az ismeretlen üzeneteket
az objektumok általában figyelmen kívül hagyják, így nem keletkezik hiba. Egyes objektumok (például
a számok vagy a szövegek) előre meghatározott módon reagálnak egy ismeretlen üzenetre
(erről később bővebben).

Egy objektum háromféle üzenetet kaphat.

Típus           | Argumentumok száma
--------------- | -------------------
Unáris          | 0      
Bináris         | 1     
Kulcsszavas     | 1+    


Először is vannak az **unáris
üzenetek** (lásd a fenti példát), amelyeknek nincs argumentumuk. Másodszor
vannak a **kulcsszavas üzenetek**, amelyeknek egy vagy több argumentumuk van,
például:

```
>> x := Szám között: 1 és: 10.
```

Ebben az esetben a **között:és:** üzenetet a **Szám** objektumnak küldjük, amely
az összes szám gyökérobjektuma. Az eredmény egy véletlenszám lesz
1 és 10 között. Végül vannak a **bináris üzenetek**, amelyek
csak egy karakterből állnak, és egy argumentumuk van:

```
2 + 3
```

Ez matematikai összeadásnak tűnik, de valójában csak egy újabb üzenet. A
**+** üzenetet a **2** kapja **3** argumentummal, és a
**5** választ adja vissza. A bináris üzenetek kettőspont nélkül is írhatók.

A bináris üzenetek láncolhatók:

```
>> x := 3 + 2 - 1.
```

Ebben a részletben először a **+ 2** üzenetet kapja a **3** **Szám** objektum, ami
az **5** Szám objektumot eredményezi, majd ez a szám kapja a **-1** üzenetet.
A figyelmes olvasók joggal veszik észre, hogy ez a protokoll eltér
a műveletek szokásos matematikai sorrendjétől.
Az XOScript az üzenetrendszer következetessége érdekében figyelmen kívül hagyja
a matematikai sorrendet. Ennek eredményeként az összeg:

```
2 + 3 * 5 = 25
```

nem 17.

Ez szándékos. A sorrend zárójelekkel módosítható:

```
2 + (3 * 5) = 17
```

A legtöbb objektum egy adott üzenetre válaszul önmagát adja vissza
eredményként. Ez hasznos, mert lehetővé teszi, hogy a párbeszédet ezzel
az objektummal egy újabb üzenet elküldésével folytassuk:

```
Kimenet ír:
[' hello '] levág nagybetűs.
```

```
HELLO
```

Itt két üzenetet küldünk a **Szöveg** objektumnak: a **levág**, majd
a **nagybetűs** üzenetet.

A következő részletben vesszőre van szükség annak jelzésére,
hogy új üzenet következik. Enélkül az XOScript összezavarodna.

```
Kimenet ír: ['Hello!'], újsor.
```

Először az **ír:** üzenetet küldjük a ceruza szimbólumnak, majd
az **újsor** üzenetet. Vessző nélkül az XOScript azt hinné, hogy
az **újsor** üzenetet a **Hello!** **szöveg**nek szeretné küldeni, ami értelmetlen lenne.

Az üzenetek feldolgozási sorrendje a következő: balról jobbra;
először a zárójelben lévő üzenetek, majd az unáris üzenetek. Ezután
a bináris üzenetek, végül a kulcsszavas üzenetek. Lásd az alábbi
példát:

```
Kimenet ír: 0.5 kerekít + (2 - 1), újsor.
```

Az XOScript mindig balról jobbra olvas: először az **ír:** üzenetet
kapja a Kimenet, majd az **újsor** üzenet következik. Magán az
argumentumon belül az XOScript szintén balról jobbra olvas, tehát először a **0.5 kerekít**,
majd a **+** következik.

{{note}}
Az újsor üzenet egy újsor karaktert fűz a szöveghez.
Az üzenet angol neve (stop) a távírórendszerekből ered.
A távírórendszerek üzeneteiben
gyakran a STOP szó jelölte a mondat végét
(mivel az írásjelek megbízhatatlanok vagy drágák voltak).
{{/note}}

Továbbá a **kerekít** megelőzi a **+** üzenetet, mert
**unáris üzenet**. A zárójelek miatt először a **2 - 1** kerül
kiszámításra, majd az **1** hozzáadódik a **0.5 kerekít** eredményéhez (1).

Az egész folyamat eredménye **2**, és ez lesz a kiírt
válasz is. A vessző után az újsor üzenet következik, amely a kurzort
új sorba viszi. Természetesen az XOScript-programok végrehajtási sorrendjét
leginkább gyakorlással lehet teljesen megérteni.

Érdemes megjegyezni, hogy az XOScriptben, sok más programozási
nyelvvel ellentétben, a szóközök a szintaxis alapvető részét képezik.
Különösen a bináris üzeneteknél okozhatnak a szóközök némi
zavart. Bináris üzenet után mindig tegyen szóközt. A számot nem lehet
közvetlenül az üzenethez illeszteni, például:

```
3 + 2
```

különbözik ettől:

```
3 +2
```

Az első példa (**3 + 2**) a **+** üzenetet küldi
a **3** számnak, a **2** számmal mint argumentummal. Az
eredmény ebben az esetben **5** lesz. A második példában (**3 +2**)
a **+2** unáris üzenetet kapja a **3** szám. A
környezettől függően ez egészen más eredményt adhat.

## Nem létező metódusok

Egy objektumnak küldött üzenet azt a függvényt hívja meg, amelyet
az adott üzenetnéven az objektumhoz csatoltak. Ha olyan üzenetet küld,
amelyet az objektum nem ért, a fogadó objektum figyelmen kívül hagyja az üzenetet,
és ehelyett egy önmagára mutató hivatkozást ad vissza a további kommunikációhoz.
Ezt toleráns üzenetküldésnek nevezzük.

Példa:

```
Kimenet ír: Objektum blah, újsor.
```

Ez nem okoz hibát. Egyszerűen kiírja az **Objektum** szöveget.


## Vezérlési szerkezetek

Az XOScriptben nincs szükség külön nyelvtani szabályokra a *ciklusokhoz* és
az *elágazásokhoz*. Egy if-utasítás csupán egy egyszerű **igaz:** vagy **hamis:** üzenet
egy **Igaz** vagy egy **Hamis** objektumnak:

```
2 páros? igaz: {
	Kimenet ír: ['Two is an even number'], újsor.
}.
```
Az előző példában az **igaz:** üzenetet az **Igaz** kapja (a válasz
arra a kérdésre, hogy a 2 páros szám-e). Argumentumként egy további
kódrészletet küldünk: egy **Függvény** objektumot. Ez a függvény kiírja
a képernyőre, hogy a 2 valóban páros szám.

A *ciklushoz* sincs szükség külön írásszabályokra. Ha egy
kódrészletet háromszor szeretnénk végrehajtani, egyszerűen küldjük a **\*** üzenetet
**3** argumentummal az adott **Függvény** objektumnak:

@test5

Ebben a kódrészletben az **i** az index. A Függvény első
végrehajtásakor tehát az **i** értéke 0, a következő végrehajtáskor **i** = 1, és
így tovább.

Nézzünk egy másik példát. Ha egy átváltási táblázatot kell
kiírnunk *kJ*-ról (kilojoule) *kcal*-ra (kilokalória) 100-as lépésekben,
a helyes jelölés az alábbi:

@test599

Itt az aktuális sor száma a **:line** paraméterbe kerül.
A függvény elején definiáljuk a függvényparamétereket. A nem használt
paraméterek üresek maradnak (**Semmi**). A paraméterek
mindig a függvény elején állnak, közvetlenül a nyitó
kapcsos zárójel után, és kettőspont előzi meg őket.

A **míg:** üzenet a *ciklus* és a *feltétel* kombinációja.
Két függvény a **míg:** üzenettel kapcsolható össze. A fogadó függvény
addig fut, amíg a kettőspont utáni függvény negatív
eredményt nem ad. Példa:

@test600

A fent bemutatott kódrészletben az **x** értékéhez **1**-et adunk mindaddig,
amíg az **x** kisebb, mint **5**. Amikor ez már nem teljesül, a második
függvény **Hamis** választ ad, így az első függvény
végrehajtása befejeződik. Vegye figyelembe, hogy az **x** a
függvényen kívül lett definiálva, és globális változó. A hatóköri szabályokról
a Függvények fejezetben olvashat bővebben.

## Szöveginterpoláció

A *kJ/kcal* lista lehetne
mutatósabb is. Az lenne az ideális, ha a lista így nézne ki:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Ha a kívánt kimenetet sablonná alakítjuk, a jelölése
a következő lehet:

```
number1 kJ ➞ number2 kcal
```

Ez azt jelenti, hogy a **number1** a kJ-értéket, a **number2** pedig
a kcal-értéket jelöli. Így működik a szöveginterpoláció az XOScriptben.
Ehhez nincs szükség külön nyelvtani szabályokra az XOScriptben. Egyszerűen
küldje el a cserélendő szót a szövegnek, a helyettesítő szöveggel
mint argumentummal:

```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

Az eredmény:

```
100 kj ➞ 23.9 kcal
```

Ez a helyettesítési szabály minden olyan nem definiált üzenetre érvényes, amelyet
egy **szöveg** objektum kap. Minden üzenetet, amelyet a
**szöveg** objektum nem ismer fel, a következőképpen értelmez:
*cseréld le az üzenet szövegét az üzenet argumentumában lévő szövegre.* A
programot a következőképpen módosíthatja:


@test601


Hogy elkerülje a zavart azzal kapcsolatban, melyik üzenet használható
helyettesítésre és melyik nem, a legjobb, ha egy sablonjelölőt vezet be, például &lt; &gt;,
a sablon azon szövegrészeihez, amelyeket
cserélni kell.

## Visszatérési értékek

Egy üzenet megválaszolására a visszatérési nyilat
(*<-*) használjuk. A következő példa bemutatja, hogyan hozhatunk létre
egy százalékszámító feladatot:

@test602

Miután a feladatot definiáltuk és a **percentage** változóhoz rendeltük,
elküldjük neki az **alkalmaz:és:** üzenetet **100** és **7** argumentummal.

Ez végrehajtja a feladatot **100**-ra és **7**-re alkalmazva, vagyis kiszámítja 100 7%-át.
A visszatérési nyíllal a választ a feladatból visszaadjuk
a főprogramnak.

## Bővítés

Bár ez a kód érvényes, van egy hátránya:
emlékezni kell az argumentumok sorrendjére. Miért ne írhatnánk
inkább így: *7 percent of: 100 *? Ez sokkal
*természetesebbnek* tűnne. Ehhez módosítanunk kell a **7**
szülőobjektumát, vagyis a **Szám** objektumot, hogy megértse a
**percent of:** üzenetet. Ezt úgy érhetjük el, hogy a **ha:tedd:** üzenetet küldjük
a Szám objektumnak, így:

@test603

Mivel a százalék ebben az esetben maga a szám, a maga
kulcsszóval (*maga*) hivatkozunk rá. Röviden: a maga szimbólum jelentése: *küldd ezt
az üzenetet önmagamnak*.

# Objektumok

{{messages}}

A meglévő objektumok módosítása és bővítése mellett saját magunk is
létrehozhatunk új objektumokat, egyszerűen az **új** üzenet elküldésével.
Tegyük fel, hogy olyan számlaobjektumot szeretnénk létrehozni, amely
betartatja a számozási sorrendet; ebben az esetben először egy számlaobjektumra lesz szükségünk.

Mivel minden objektum egy másik objektumból származik, amely végső soron
az összes objektum gyökérobjektumából, az Objektum nevű objektumból ered,
el kell döntenünk, hogy az új objektumunk melyik másik objektumra
épüljön. Az új objektum örökli annak az objektumnak az összes tulajdonságát,
amelyre épül, vagyis amelyiknek eredetileg az **új** üzenetet küldtük.

Ebben a példában egy meglehetősen semleges objektumot részesítünk előnyben, amely nem
örököl túl sok tulajdonságot. Ez megkönnyíti a választást, mert ebben
az esetben az új objektum magára a gyökérobjektumra, az
**Objektum** objektumra épülhet. A tervezett számlázórendszer jelölése ekkor
a következő:

@test604

Az aktuális számlaszámot az objektum tárolja, ezért áll előtte
a **saját** kulcsszó. Ezt *tulajdonságnak* nevezzük;
erről később részletesebben is szó lesz.

Egyes vállalkozások szeretik, ha az évszám is szerepel a számlaszámokban.
Ebben az esetben létrehozhat egy új számlaobjektumot, amely
egy korábbi számlaobjektumra épül, de lehetővé teszi a felhasználó számára,
hogy megadjon egy adott évet:

@test605

A **szám** üzenet megvalósítását nem kell újra megírni,
mivel azt a korábban megírt **számlaobjektumtól**
örökli; így a régi kód újrafelhasználható. Az XOScriptben nincsenek
olyan fogalmak, mint az osztályok és a hozzájuk kapcsolódó fogalmak. Ez azt jelenti, hogy az objektumok
kizárólag más objektumoktól örökölhetnek; ezt *prototípusos
öröklődésnek* is nevezik.

Térjünk vissza a tulajdonságokhoz. Az objektumok tulajdonságai csak
*az objektumhierarchián belülről* érhetők el, így ezeket a tulajdonságokat
más objektumok nem láthatják.

Más programozási nyelvekkel ellentétben az objektumok összes tulajdonsága
kizárólag a tulajdonságot létrehozó objektum és a belőle
származtatott objektumok számára látható.

Gyakran alkalmazott technika, hogy egy objektumot afféle *tervrajzként* használunk,
ahogyan például a korábban tárgyalt számlák esetében is.
Egy másik jó példa a **Point** (pont). Tegyük fel, hogy olyan
számítógépes programot készít, amely egy térkép pontjaival végez számításokat.
Kifejlesztheti a **Point** objektumot, amely egy x-koordináta és egy
y-koordináta tulajdonságot tartalmaz, és ezeket üzeneteken keresztül
teszi elérhetővé a külvilág számára:

@test606

Az **=** üzenet az **és:** üzenet segítségével hasonlítja össze a két pontot. Az
első összehasonlítás eredménye **Igaz** vagy **Hamis**. Ezek logikai
objektumok. Ha az **és:** üzenetet egy Igaz objektumnak küldi, és a
kettőspont utáni argumentumobjektum szintén **Igaz**, akkor a válasz
ismét **Igaz** lesz. Ha bármelyikük **Hamis**, a válasz
**Hamis** lesz. Vegye figyelembe, hogy az egyik pont nem tudja kiolvasni
a másik koordinátáit. Ehhez üzenetet kell küldeni a másik pontnak, hogy
elkérje ezeket az adatokat: **x-coordinate** és **y-coordinate**. Végül is, ahogy
már elmagyaráztuk, a tulajdonságok kizárólag magán az objektumcsaládon
belülről érhetők el.

Vegye figyelembe, hogy itt az **=** üzenettel végezzük a pontok
összehasonlítását. Ugyanígy más üzenetet is használhattunk volna, például:
**is:** vagy **equal:**, de ebben az esetben az **=** karakter újrafelhasználása
tűnt megfelelőnek.

## Öröklődés

A korábban megírt kódot újrafelhasználhatja objektumhierarchia
létrehozására. Például:

```
>> Animal := Objektum új.
>> Dog := Animal új.
>> Poodle := Dog új.
```

Ebben az esetben a **Dog** (kutya) örökli az **Animal** (állat) összes viselkedését
és tulajdonságát, az **Animal** objektum pedig az **Objektum**
összes viselkedését, amely az összes objektum gyökérobjektuma.


## Felülírás


A következő példában egy újfajta listát hozunk létre:
a **Combination** (kombináció) listát, amelyben minden elem garantáltan egyedi. A
lista függvényeit öröklődéssel használjuk fel újra:

@test607

Figyelje meg, hogy a második **red** nem kerül be a listába.

Időnként szükség lehet egy objektum viselkedésének felülírására.
Például akkor, ha számok összeadásakor a mértékegységeket is
figyelembe kell venni. A következő példában létrehozzuk a **Size** (méret) objektumot.
Ez az objektum olyan számot ad vissza, amely az összeadás során
figyelembe veszi a hozzáadandó szám mértékegységét. A **Szám** objektum
ellenőrzi, hogy *hüvelykről* vagy *lábról* van-e szó. A programkód
a következőhöz hasonló lehet:

@test608

## Rekurzió

Az előző példában a plusz **jelet** írtuk felül. Vegye figyelembe,
hogy a végső összeadást végül mégis el kell végezni, ami valójában
a következő sorban történik:

```
>> answer := maga + (szám x factor).
```

Honnan tudja az XOScript, hogy ez a plusz **jel**
az összeadás eredeti logikájára utal?** Egy másik értelmezés szerint például
az XOScript ismételten ugyanazt az üzenetet küldené ugyanannak az
objektumnak, ami pedig **végtelen ciklust** eredményezne. Nyilvánvalóan
nem ez a szándék. Amint olyan üzenetet küld egy objektumnak,
amely pontosan ugyanazt a kódot hajtaná végre, az XOScript felismeri,
hogy ebben az esetben a mögöttes, felülírt üzenetre gondolt. A
program így automatikusan védve van az ilyen végtelen
ciklusok ellen. Ha azonban valóban az a célja, hogy ugyanazt a függvényt
az aktuális függvényből futtassa, előbb el kell küldenie a
**rekurzív** üzenetet. Ebben az esetben az eredmény végtelen
ciklus lesz. A rekurzív feladatoknak azonban vannak hasznos alkalmazásai,
például ha egy adott szám faktoriálisát szeretné kiszámítani.
Ebben az esetben egyszerűen adja hozzá a **factorial** üzenetet
a Szám objektumhoz:

@test609

Ehhez rekurzióra van szükség. A **factorial** üzenethez kapcsolt
feladatot ugyanis ugyanazon a függvényen belül újra végre kell hajtani.
A faktoriálisfüggvényt tehát magából a faktoriálisfüggvényből kell
meghívni. Az XOScript alapesetben megakadályozza ezt,
mert fennáll a végtelen ciklus veszélye. Ezért
elengedhetetlen, hogy az üzenet elé a **rekurzív** szót írja. Ezzel
jelzi az XOScriptnek, hogy valóban az a szándéka, hogy
ugyanazt a feladatot hajtsa végre, és nem hibázott.

## Osztályszerű objektumok

Bár az xoscript nem kínál osztályokat, az osztályszerű
viselkedés utánzása triviális. Egyszerűen írja felül az új üzenetet.

```
>> Animal := Objektum új.
Animal ha: ['új'] tedd: {
	<- maga új inicializál.
}.

Animal ha: ['inicializál'] tedd: {
	saját sound := ['?'].
	saját legs  := 4.
}.
```

A fenti kódrészletben létrehozunk egy Animal nevű objektumot.
Ez az objektum *tervrajzként* szolgál mindenféle állathoz,
például kutyákhoz és macskákhoz. Az Animal szülőobjektumot
nagy A betűvel írjuk, jelezve, hogy osztályszerű objektumról van szó.
Ezután felülírjuk az új üzenetet a saját új-metódusunk megírásával.
Ebben az esetben az új üzenetet küldi a maga objektumnak, majd az
init üzenetet. Mivel az xoscript alapértelmezés szerint blokkolja a rekurziót, ez nem okoz
végtelen ciklust. Ehelyett az új üzenetet a szülőobjektumnak
(Objektum) küldi, ami az Animal egy új példányát eredményezi. Így létrehozunk
egy új objektumot, amely ugyanarra az objektumra épül, amelyhez az új-metódusunkat írtuk.
Ez teljesen érvényes. Most az init üzenetet is elküldjük, ez biztosítja,
hogy az Animal objektum tulajdonságai alapértelmezett értékeket kapjanak. Alapértelmezés szerint
egy állatnak 4 lába van, a hangja pedig ismeretlen (ezért a kérdőjel).
Az Animal új példányának létrehozásához egyszerűen ezt írhatjuk:

```
>> a := Animal új.
```

Így az Animal egy új példányát kapjuk 4 lábbal, ismeretlen hanggal és
egy init metódussal. Akárcsak más OOP-nyelvekben, az Animal objektumot
is bővíthetjük:

```
>> Dog := Animal új.
Dog ha: ['inicializál'] tedd: {
	maga inicializál.
	saját sound := ['barks'].
}.
```

Ezt könnyen kipróbálhatjuk egy szöveg metódus hozzáadásával:

```
Animal ha: ['szöveg'] tedd: {
	<- saját legs szöveg + saját sound.
}.
```

Rakjuk össze az egészet:

@test13


Gyakori probléma egy adott kezdőállapotba állított objektum
létrehozása. Tegyük fel, hogy egy **Rectangle** (téglalap) objektumot kell létrehozni
a kerület és a terület kiszámításához. Egy lehetséges jelölés:


```
>> Rectangle := Objektum új.

Rectangle ha: ['area'] tedd: {
	<- saját hossz * saját width.
}.
```

Nyilvánvaló, hogy a hossz és a szélesség megadása előfeltétel. Erre
a célra hozzáadhatjuk a **length:** és a **width:** üzenetet:


```
Rectangle ha: ['length:'] tedd: { :hossz
	saját hossz := hossz.
}.

Rectangle ha: ['width:'] tedd: { :width
	saját width := width.
}.

```

Ez a téglalap ezután a következőképpen használható:


```
>> rectangle := Rectangle új length: 2, width: 3.
Kimenet ír: rectangle area.
```

Ha azonban a hossz és a szélesség kezdeti beállítása elmarad,
hibaüzenet jelenik meg:

```
>> rectangle := Rectangle új.
Kimenet ír: rectangle area.
```

a következő hibát eredményezi:

```
Kulcs nem található:hossz
```

Ennek elkerülése érdekében célszerű, ha egy téglalapnak
mindig van kezdeti hossza és szélessége, például 0. Ebben
az esetben tehát **felül kell írni** az **új** üzenetet.

@test610

Ha felülírjuk az új üzenetet, lényegében egy **osztályt** utánzunk.

Az XOScript világa sokféle objektummal van tele, amelyek
a programja számára kezdettől fogva elérhetők. A következő fejezetekben
ezeket az alapobjektumokat tárgyaljuk.

## Pillanatképek

Egy objektumot (a jelenlegi állapotával együtt) a következővel menthet lemezre:

```
myobject save-as: ['saved.bin'].
```

Az objektum újbóli betöltése lemezről:

```
>> myobject := Objektum load-from: ['saved.bin'].
```

A pillanatképekkel egy adott állapot menthető el, vagy javítható a teljesítmény.
Egy pillanatkép betöltésével elkerülhető a lexikai elemzés, a szintaktikai elemzés és az alkalmazás beállítása.
A jövőben a pillanatképek további teljesítménybeli előnyökkel is
járhatnak, például bizonyos minták optimalizálásával vagy a gyakran futó
kódútvonalak felismerésével és optimalizálásával.

{{warning}}
A pillanatképek kísérleti funkciót jelentenek, ne használja éles környezetben.
A kísérleti funkciók aktiválásához fordítson a -D EXPERIMENTS kapcsolóval.
{{/warning}}


@test712

# A Semmi objektum

{{messages}}

A Semmi objektum
az ürességet, pontosabban az információ hiányát jelöli.
Esetenként ezt az objektumot kapja válaszként egy üzenetre,
ha az eredmény **semmi**. A legfontosabb kérdés,
amelyet a **Semmi** objektumnak feltehet: **Semmi?**. A
válasz mindig **Igaz** lesz.

```
Kimenet ír: Semmi Semmi?.
```

eredmény:

```
Igaz
```

A **Semmi** objektumon kívül minden más objektum **Hamis** választ ad. A
fenti kódrészlet kissé filozofikusnak tűnhet, a **Semmi**
objektumnak azonban kifejezetten gyakorlati alkalmazásai vannak. Például
a Semmi objektumot kapja válaszként, ha egy nem létező listaelemet
kér le. A Semmi objektumot akkor is használhatja,
ha deklarálni szeretne egy változót, de még nem szeretne értéket megadni.
Ilyenkor egyszerűen a különleges **Semmi** értéket **rendeli hozzá**. Az
XOScriptben nem szabad változót érték nélkül deklarálni, például így:


```
>> érték.
```

Ehelyett a következőt kell írnia:

```
>> érték := Semmi.
```

@api_None_base

# Logikai értékek

{{messages}}

A jelen írás idején legnépszerűbb programozási nyelvek többségével ellentétben
az XOScript csak egyetlen Igaz objektumot és egyetlen Hamis
objektumot biztosít. Pontosabban: valahányszor leírja, hogy **Igaz**, az nem jelenti azt,
hogy új objektum jött létre. Ehelyett mindig egy hivatkozást használ. Ez
azt jelenti, hogy ha a következőt írja:

\>\> x := Igaz.

akkor az **x** az **Igaz** objektumra hivatkozik. A feltételes kód és a ciklusok is
ezt a hivatkozást ellenőrzik. Az XOScriptben az **Igaz** és a **Hamis** jelentése
nem rögzített. Egy XOScript-programot valójában alaposan felforgat
egy ilyen utasítás:

Igaz := Hamis.

Az ilyen műveletek eredménye nem definiált, mégis érvényes
művelet, ezért formálisan megengedett. Létezik továbbá egy Logikai
objektum, amely az **Igaz** és a **Hamis** gyökérobjektuma, mivel mindkettő
ebből a gyökérobjektumból származik. Magának a Logikai objektumnak azonban
nincs gyakorlati haszna.

## Buktatók

Legyen óvatos az **és:** és a **vagy:** használatával

```
Kimenet ír: (Hamis or: Igaz or: Igaz), újsor.
Kimenet ír: (Hamis vagy: Igaz, vagy: Igaz), újsor.
```

Eredménye

```
Hamis
Igaz
```
mert a **vagy:** üzenet csak 1 argumentumot fogad. Az első sor
a **vagy:vagy:** üzenetet küldi a Hamis objektumnak, amely nem létezik, így az objektum figyelmen kívül hagyja
az üzenetet, és önmagát adja vissza (Hamis). A második sor ezzel szemben
a **vagy:** üzenetet küldi, majd egy újabb **vagy:** üzenetet (láncolási jellel, azaz vesszővel: ,).


@api_Boolean_base

# Számok

{{messages}}

Valahányszor leír egy számot, például 9, -10 vagy 3,12, a háttérben
az XOScript ezeket a számokat **Szám** objektummá alakítja. Ennek a
Szám objektumnak üzeneteket küldhet, vagy a számot hozzárendelheti
egy változóhoz, és utána küldhet üzeneteket:

```
10 páros?

>> tenner := 10.
tenner páros?

```

Mindkét jelölés érvényes. A Szám objektum a következő
üzenetekre válaszol...

Ezeknek az üzeneteknek a többsége magától értetődő, és matematikai
műveletek vagy összehasonlítások végrehajtását teszi lehetővé.

{{note}}
Vegye figyelembe, hogy az ASCII-megfelelőik helyett a ≤ ≥ ≠ × és ÷ jeleket is használhatja.
Ez ízlés kérdése.
{{/note}}

A bináris matematikai üzenetek (+) és
kulcsszavas változataik (hozzáad:) között az a különbség, hogy az előbbiek
új számot adnak vissza, amely a művelet eredménye, míg
az utóbbiak magát az objektumot módosítják. Ezt a következő
példa szemlélteti:

@test597

A fenti példában b = 4 és a = 3. A **hozzáad: 2** üzenet 2-vel növeli
az a értékét, míg a **+ 3** egy új számot hoz létre, amely
egyenlő a + 3-mal. Ugyanez érvényes a többi matematikai műveletre is, például
a szorzásra. A szorzásjel használatakor válaszként egy
új objektumot kap. Ha a **szoroz:** üzenetet használja,
magát a számot szorozza meg.

A **között:és:** üzenettel, például így: **Szám
között: X és: Y**, egy X és Y közötti számot kap. Így
bármilyen véletlenszám előállítható:

```
>> a := Szám között: 1 és: 10.
Kimenet ír: a, újsor.
```

Az 1.4-es verziótól kezdve az xoscript beépített véletlenszám-generátora
legjobb tudomásunk szerint kriptográfiailag biztonságos.

Egy számhoz **minősítőt** csatolhat, például **6
alma**. Minden olyan üzenetet, amelyet egy szám nem ismer fel,
minősítőnek tekint. Egy szám minősítőjét a minősítő üzenettel
kérdezheti le:

A minősítő lényegében egy Szöveg objektum, amelyet a Szám
objektummal együtt tárolunk. A minősítő **ír:** hozzárendeléskor
a szám után is kiíródik. A minősítőkkel például
vegyes pénznemű összegeket adhatunk össze. Az összegek összeadásakor lekérdezhetjük
a minősítőket. A következő programpélda ezt az
elvet egy történelmi valutaátváltó segítségével mutatja be (mivel az árfolyam
meglehetősen stabil marad!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Szövegek

{{messages}}

Valahányszor egy szöveget **szögletes zárójelek és idézőjelek** ['...'] közé helyez,
az XOScript új szövegobjektumot hoz létre. Ügyeljen azonban
a megfelelő idézőjelek használatára. A szöveg elején lévő idézőjel
különbözik a végén lévőtől (így az aposztróf
escape-elés nélkül használható).

## UTF8

Az xoscript szövegei általában utf8 kódolású szöveget tartalmaznak. Bár
technikailag lehetséges bináris vagy nem utf8 tartalmat tárolni
egy szövegben, erre a célra a blobok használata ajánlott. A blobokat
a szerverbővítmény biztosítja (lásd az ffi fejezetet).
A blobokat/ffi-t általában
bővítményenként/platformonként biztosítjuk, mivel ezek a platformhoz
és az architektúrához kötődnek (ffi/blobok). A szkriptnyelv magja igyekszik
a lehető legplatformfüggetlenebb maradni.

## Típuskonverzió

Bármely objektumról készíthet egy
eltérő típusú másolatot a következő üzenetekkel:

Üzenet  | Eredmény
------- | ------
szám    | Számmá alakít
szöveg  | Szöveggé alakít
logikai | Logikai értékké alakít
  
A következő szabályok **érvényesek**:

üzenet   | Semmi     | Logikai            | Szám                  | Szöveg    | Egyéb              
-------- | --------- | --------           | --------              | --------  | --------
logikai  | Hamis     | n/a                | 0→Hamis egyébként→Igaz | Igaz     | Többnyire Igaz
szám     | 0         | Hamis→0 Igaz→1 | n/a                       | ['n']→n | Többnyire 1
szöveg   | ['Semmi'] | ['Hamis']/['Igaz'] | ['n']                 | n/a       | Változó

## Másolás

Az XOScriptben az értékek átadása mindig **hivatkozással** történik. Más nyelvekben
ez az érték típusától függ, az XOScriptben csak egyetlen mód létezik:
a hivatkozás. Az XOScript soha nem készít másolatot egy értékről. Egy objektum másolásához
a **másol** üzenetet kell elküldenie.

@test611

Itt talán arra számított, hogy a kimenet Dolly lesz Donny
helyett. Ez azonban nem így van, mivel mindkét név ugyanarra az
objektumra hivatkozik. Ciklusok használatakor valami hasonló történik:

@test612

Az XOScript ugyanis **mindig** hivatkozásokat használ, így a **:quantity**
paraméter a fenti ciklusban is a lista elemére mutató hivatkozást
jelöli.

Egy objektum másolásához ezt a műveletet
**kifejezetten** meg kell adnia:

@test613

Ha a **másol** unáris üzenetet egy szövegnek küldi, az objektum
ugyanannak a szövegobjektumnak egy másolatát adja vissza. Ugyanígy másolhatók a Szám
objektumok, a logikai objektumok, a listák és a szótárak is.

Saját másolási megvalósítást is definiálhat; ez kifejezetten
szükséges, ha saját objektumokat hoz létre. A másolás alapértelmezett
megvalósítása listák esetén sekély másolatot készít, vagyis egy
új listát hoz létre ugyanazokkal az elemekkel.

@test614

Ebben az esetben a 4 csak a másolathoz adódik hozzá.
Mivel azonban a másolat sekély, a két lista objektumai
ugyanazok.

@test615

Ha tehát a másolatban minden névhez 2-t fűzünk, az eredeti
lista is megváltozik.

Ennek orvoslására **mély másolatot** kell készítenünk. Egy ilyen másolási művelet
listák esetén a következőképpen állítható össze:

@test616

Figyelje meg a rekurzív üzenetet is; ezt az üzenetet
a másol üzenet előtt kell elküldeni.

Fontos szem előtt tartani, hogy bár egy objektum másolata
gyakran ugyanúgy néz ki, mint az eredeti, valójában
soha nem ugyanaz. A gyökérobjektum definiál egy **equal:** üzenetet,
amellyel az objektumok azonossága hasonlítható össze. Nézze meg a
következő példát:

@test617

## Implicit konverzió

Az XOScript **implicit konverziót** használ az objektumok átalakítására. Egy
lista képernyőre írásához az XOScript például belsőleg a
*szöveg* üzenetet küldi a listának. Ez nagyon hasznos lehet,
ha egy listát vesszővel elválasztott listaként szeretne kiírni. A
*szöveg* üzenet felülírható:

@test620

@api_String_base
@api_Format_base


## Szerveroldali szövegfunkciók

A következő Szöveg-funkciókat a
szerverbővítmény adja hozzá.

@api_String_server

# Függvények

{{messages}}

A kódot { és } közé csoportosíthatja, ekkor függvénnyé válik.
Az xoscriptben néha a feladat kifejezést is használjuk, vagy egyszerűen
kódblokkot mondunk.

Egy függvényt az *indít* üzenet elküldésével futtathat.


```
{ Kimenet ír: 123, újsor. } indít.
```

Ha a függvény argumentumokat fogad, használja az **alkalmaz:** üzenetet.

```
{ :a Kimenet ír: a, újsor. } alkalmaz: a.
```

Lásd az alábbi példákat is.
Az egyszerű architektúra miatt egy függvénynek csak
egyetlen visszatérési pontja lehet. Hogy elkerülje a többletterhelést vagy a feltételek
túlzott egymásba ágyazását, használhat eljárást (ami ugyanaz, mint
a szorzásjel használata 1 argumentummal):

```
{
  (a = 1) igaz: { x := 1. }, megszakít.
  (a = 2) igaz: { x := 2. }, megszakít.
} eljárás.
```

Így az (a = 2) nem értékelődik ki, ha a = 1.
Ráadásul így nincs szükség egymásba ágyazott igaz-üzenetekre sem.
Valahányszor azon kapja magát, hogy feltételeket ágyaz egymásba, gondoljon
az eljárás üzenetre. Olvashatóbbá teheti
a kódját.


Íme egy fontos buktató:

```
{
	Hamis hamis: {
		Kimenet ír: ['End the loop.'].
	}, megszakít.
	
	Kimenet ír: ['Dont show me.'].

} eljárás.

```

Ebben az esetben a 'Dont show me' szöveg megjelenik,
mert a **megszakít** üzenetet a Hamis kapja. Ha
megszakítást szeretne végrehajtani, azt üzenetként az **Igaz** objektumnak kell küldeni.
 

```
{
	Hamis nem igaz: {
		Kimenet ír: ['End the loop.'].
	}, megszakít.
	
	Kimenet ír: ['Dont show me.'].

} eljárás.

```

Ez a várt módon fog működni.

## Kivételek

A kivételeket így kezelheti:

```
{ Task 1 } elkap: { Task 2 }, indít.
```

Szándékosan is előidézhet hibát a programjában, és
ezzel aktiválhatja a kezelőblokkot. Ehhez a
**hiba:** üzenetet kell küldeni az aktuális feladatnak, ahogy a következő
példa mutatja:

```
{
ez-a-feladat hiba: ['Whoops!'].
} elkap: { :mistake
Kimenet ír: mistake.
}, indít.
```

## Értékek befecskendezése

Az XOScript lehetővé teszi, hogy a feladatokba értékeket fecskendezzünk be. Nézze meg
az alábbi feladatot:

```
>> sending := {
	Newsletter címzett: saját recipient.
}.
sending beállít: ['recipient']
érték: ['info@recipient.org'].
sending indít.
```


Ez a példa egy képzeletbeli feladatot mutat be, amely hírlevelet küld
egy e-mail-címre, vagyis egy **címzettnek** (recipient). Ez a címzett kívülről,
a feladat elindítása előtt fecskendezhető be a feladatba, a
**beállít:érték:** üzenet feladatnak való elküldésével. Ezzel a
**recipient** értéke előre beállítódik a feladatban. Ez az érték módosítható is,
majd a feladat újra futtatható. Ez hasznos módszer
Feladat objektumok használatakor.

## Üres függvények

Üres feladatok nem megengedettek. Elméletileg egy üres feladat így
nézne ki: **{}**, az XOScript azonban ezt nyelvi hibának tekinti. Ha
üres feladatot szeretne deklarálni, használhatja a Semmi objektumot:

```
>> task := Semmi.
```

Bár ez nem valódi feladat, hanem egy Semmi objektum, indít üzenet
ennek ellenére küldhető neki:

```
>> answer := task indít.
```

Ez valójában ugyanaz, mint:

```
>> answer := Semmi indít.
```

Mivel a **Semmi** objektum nem ismeri fel az **indít** üzenetet,
önmagát adja vissza válaszként, így a válasz ismét **Semmi** lesz.
Üres feladatra tehát nincs szükség. Az XOScript programozási nyelv
elegáns felépítésének köszönhetően erre egyszerűen a Semmi
objektumot használhatja.

## Dinamikus hatókör

Ha egy Függvénynek szüksége van egy változóra, de nem találja,
akkor az őt **meghívó** Függvény változóit ellenőrzi,
és így halad tovább felfelé a Függvények láncán.
Ez a keresés addig folytatódik, amíg a változó elő nem kerül.
Ha a változó így sem található, hibaüzenet jelenik meg. A változókeresés
ezen módszerét **dinamikus hatókörnek** nevezzük.

Az elv szemléltetése:

@test618

@api_Code_base

# A gyökérobjektum

{{messages}}

Az **Objektum** nevű objektum az összes objektum gyökérobjektuma
az XOScriptben, és a nyelv alapvető funkcióit biztosítja.

A leggyakrabban küldött üzenet
a **ha:tedd:**, amely egy objektum funkcionalitását bővíti. Ezt az
üzenetet a gyökérobjektum kapja, amely ennek megfelelően a
megadott feladatot az üzenethez kapcsolja, és ezzel bővíti a származtatott
objektumot.

## Mindent elkapó metódusok

Ha olyan üzenetet küld, amelynek nem felel meg
metódus az objektumban, az üzenet általában figyelmen kívül marad. Megadhat azonban
úgynevezett **mágikus metódusokat** vagy **mindent elkapó** metódusokat, amelyek
akkor hívódnak meg, ha az objektum nem érti az üzenetet.

4 mindent elkapó metódus áll rendelkezésre. Mindegyik üzenet
meghatározott számú argumentumnak felel meg.

Mindent elkapó üzenet | Argumentumok száma
-------------------- | -------------------
válaszol:            | 0
válaszol:és:         | 1
válaszol:és:és:      | 2
válaszol:és:és:és:   | 3


@test619

## Programozott üzenetek

Ahelyett, hogy közvetlenül küldene üzenetet egy objektumnak, az
üzenet egy változón keresztül is elküldhető. Ehhez az
**üzenet:érvek:** üzenetet használja.

@test396

@api_Object_base

# Listák

{{messages}}

Az XOScript kétféle gyűjteményt ismer: *listákat* és *szótárakat*.
A **listák** objektumok *rögzített sorrendű* felsorolásai. A szótáraknak
nincs sorrendjük, ehelyett egy jelmagyarázathoz hasonlítanak, amely kulcsokból (vagy kifejezésekből) és
a hozzájuk tartozó értékekből áll. A listák a tömbökhöz (PHP, Java, C)
és a listákhoz (Python) hasonlíthatók. A szótárak más programozási nyelvek
asszociatív tömbjeihez (PHP) vagy szótáraihoz (Python) hasonlíthatók. Új
Lista létrehozásához írja ezt:

```
>> fibonacci := Lista új.
```

Ez az üres lista a **hozzáfűz:** üzenettel tölthető fel:

```
fibonacci hozzáfűz: 0.
fibonacci hozzáfűz: 1.
fibonacci hozzáfűz: 1.
fibonacci hozzáfűz: 2.
fibonacci hozzáfűz: 3.
fibonacci hozzáfűz: 5.
fibonacci hozzáfűz: 8.
fibonacci hozzáfűz: 13.
```

Ha kiírjuk a listát a képernyőre:

```
Kimenet ír: fibonacci, újsor.
```

Ezt látjuk:

```
Lista ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

A hozzáfűz helyett a ; jellel is adhat elemeket egy listához:


```
>> fibonacci := Lista új ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

A pontosvesszők (;) mind bináris üzenetek, amelyek egy
értéket helyeznek a listába.

## Láncolás

Tegyük fel, hogy van egy ilyen listája:

```
>> x := Lista új ; 1 ; 2 ; 3.
```

Ha az első és az utolsó elemet szeretné törölni, akkor az
üzenete így nézne ki:

```
x első-kivétele utolsó-kivétele.
```

Sajnos az előző jelölés nem működik helyesen. Az
**első-kivétele** üzenet a lista első elemét adja vissza, amely
pedig az **utolsó-kivétele** üzenet fogadója lesz. Az
**utolsó-kivétele** üzenetet tehát nem az **x** kapja, hanem a 2. Egy
lehetséges megoldás erre a problémára, ha két külön
mondatot írunk, például:

```
x első-kivétele.
x utolsó-kivétele.
```

Ez azonban meglehetősen nehézkes, különösen ha
kettőnél több elemet kell törölni. Ezért az XOScript
alternatív üzenetszerkezetet kínál az ilyen helyzetekre. Az
**alternatív** üzenetszerkezetekben az objektumok válaszai figyelmen kívül maradnak,
és válaszként újra meg újra a fogadó objektumot kapja vissza.
Az **alternatív** üzenetszerkezetet a **tedd** üzenet objektumnak való
elküldése indítja, és az **alternatív** üzenetszerkezet
a **kész** üzenet elküldésével zárható le. A bemutatott
példában ez a következőképpen alkalmazható:

```
>> x := Lista új ; 1 ; 2 ; 3.
x tedd első-kivétele utolsó-kivétele kész.
```

@api_List_collections

# Szótárak

{{messages}}

**A Lista és a Szótár egyaránt gyűjtemény. A listával
ellentétben azonban a szótárnak **nincs** sorrendje. A kettő közötti másik különbség,
hogy a szótár objektumpárokból áll. Az egyik objektum bejegyzésként (vagy
kulcsszóként) szolgál a másik objektum megkereséséhez. Egy jó példa
egy ilyen listára az árlista, például:


```
>> menu := Szótár új
	tesz: ['£5'] ide: ['apple pie'],
	tesz: ['£6'] ide: ['carrot cake'],
	tesz: ['£3'] ide: ['fudge'].
```

A listához hasonlóan a tesz:ide: üzenettel
adhatunk objektumot a listához. A különbség az, hogy a listával
ellentétben itt két objektumot kapcsolunk össze. Az első objektum a listához
hasonlóan az az objektum, amelyet a listában tárolni szeretne. A második
objektum nem a gyűjteményen belüli pozíciója, hanem az a **bejegyzés**,
amellyel az előbbi objektum később visszakereshető.
Röviden: a szótár kicsit úgy működik, mint egy valódi szótár; a kulcsszó alapján
megtalálható a jelentés. Például a fenti listából
egy fudge árának lekérdezése:

```
>> price := menu itt: ['fudge'].
```

Használhatja a tömör jelölést is:

```
>> price := menu ? ['fudge'].
```

Ha az objektumok tárolására használt bejegyzések nem tartalmaznak szóközt
(és nem ütköznek más előre definiált üzenetekkel),
a következő jelölés is használható:

```
>> menu := Szótár új
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Kétségtelen, hogy a fenti jelölés kicsit természetesebben hangzik.
Egy fudge árának
lekérdezéséhez a következő egyszerűsített jelölés használható:

```
>> price := menu fudge.
```

@api_Dict_collections

# Fájl

{{messages}}

A **Fájl** objektum alapvető hozzáférést biztosít a fájlrendszerhez.
Ezzel az objektummal teljes fájlokat olvashat be egyszerre egy változóba,
vagy változókat írhat egyszerre fájlokba. A soronkénti olvasás
is támogatott. Ezek a leggyakoribb fájlkezelési műveletek
egy szkriptnyelvben. A haladó fájlműveletekhez
FFI szükséges a szerverbővítményen vagy egy külön IO-bővítményen keresztül.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Dátum/idő

{{messages}}

Az idő és a dátum strukturált ábrázolására az XOScript a
**Pillanat** objektumot használja. Ha egy új Pillanat objektumot kiírunk a képernyőre,
az aktuális dátum és idő jelenik meg:

```
Kimenet ír: Pillanat új, újsor.
```

Ennek eredménye valami ilyesmi lehet:

```
2020-10-10 12:16:39
```

Az egyes időösszetevők kiolvasása is egyszerű. Ha
például csak az aktuális évre van szükség, az
**év** üzenetet küldhetjük a pillanatnak, és válaszként egy
olyan Szám objektumot kapunk, amely csak az évet tartalmazza:

```
>> m := Pillanat új.
Kimenet ír: m év, újsor.
```

@api_Moment_system

# Program/szabványos kimenet

{{messages}}

A Program objektum az éppen futó alkalmazást képviseli. Ez az objektum
lehetővé teszi rendszerparancsok végrehajtását, alprogramok beillesztését,
argumentumok beolvasását és még sok mást. Vagyis az összes rendszerrel kapcsolatos funkciót.

## Szabványos kimenet

A Kimenet a szabványos kimenet objektuma. Alapvetően két metódusa van:
az **ír:** és az **újsor**. Az ír: üzenettel szöveget küldhetünk
a stdout-ra, az újsor üzenet pedig egy újsor karaktert ír ki.
Az **újsor** helyett a \\n is használható.

Példa:

```
Kimenet ír: ['Hello World'], újsor.
```

eredmény:

```
Hello World
```

## Modulok/bővítmények

Az XOScript világa új rendszerobjektumokkal bővíthető
modulok telepítésével. Új rendszerobjektumot úgy adhatunk az XOScript
világához, hogy a modulfájlt (általában egy .so
utótagú fájlt) a mods mappába helyezzük.

Ha üzenetet küld a bővítménymodul által elérhetővé tett
objektumnak, az XOScript automatikusan betölti a modult.

Bővítményeket saját maga is írhat. A bővítmények
C programozási nyelven készülnek. Egy példabővítményt a forráskód-csomagban
talál, az src/plugins/example könyvtárban.


## Reflexió

Többféle módon is
feltérképezhetjük a rendszert a program futása közben. Az XOScript néhány metódust kínál
annak megállapítására, hogy mely objektumok vannak jelen, és ezek az objektumok mely üzenetekre
válaszolnak. Először is minden objektumtól megkérdezhető, milyen **típus**ú,
az XOScriptben azonban a típusok alakíthatók, ezért megbízhatatlanok.

A Program objektumtól azt is megkérdezhetjük, hogy egy
adott objektum jelen van-e már a programban:

```
Program Tool igaz: { ... }.
```

Ha az objektum
neve egyetlen szimbólumból áll, a félreértések elkerülése érdekében
a legjobb a következő jelölést alkalmazni:

```
Program keres: ['X'], igaz: { ... }.
```

Az objektumokon kívül üzenetekről is kérdezhetjük a
Program objektumot. Megkérdezhetjük például, hogy a
**Szám** objektum ismeri-e a **között:és:** üzenetet, az alább
bemutatott módon:

```
Program Number: ['between:and:'], újsor.
```

@api_Program_system

# szerver

{{messages}}

Az xoscript szerverbővítménye szerveroldali alkalmazások
készítéséhez nyújt funkciókat. A szerverbővítmény
betöltéséhez használja ezt:

```
Server inicializál.
```

A kényelem kedvéért ajánlott a webtools.xo és a template.xo
fájlokat is betölteni.

```
Program használ: ['webtools.xo'].
Program használ: ['template.xo'].

```

## Szerverbeállítások

A következő szerverbeállításokat adhatja meg:

```
	# default values are given
	# so if you do not set anything these
	# values are used...

	Program 
	beállítás: ['max-postfields']
	érték: 40.

	Program 
	beállítás: ['max-contentlength']
	érték: 2000000. # 2MB

	Program 
	beállítás: ['max-time']
	érték: 5000. # 5sec

```

## Helló, világ

Íme egy nagyon egyszerű webes program, amelyet egy
szabványos CGI-szerverrel, például Apache2, NGINX, OpenHTTPD vagy bármely más
ismert szerverrel használhat.

```
#!/bin/xo

Server inicializál.
Program használ: ['webtools.xo'].

>> web-document := Webdokumentum új.

web-document kiír: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Ha nem szeretné a Webdokumentum objektumot használni, az sem baj, de
akkor a HTTP-fejléceket saját magának kell megírnia:

```
#!/bin/xo
Kimenet ír: ['Content-type: text/html; charset=utf-8 \n\n'], újsor.
Kimenet ír: ['hello world!'], újsor.
``` 

## Kérés

A HTTP-Kérés objektummal GET/POST/COOKIE és
UPLOAD adatokat kérhet le:

```
>> kérés  := HTTP-Kérés új.
>> search   := kérés get: ['search']. # ?search=books
>> password := kérés post: ['password']. # from form
>> selected := kérés get-lista: ['sel[]']. #?sel[]=1&sel[]=2
>> selected := kérés post-lista: ['sel[]'].
>> cookie   := kérés cookie: ['session-id'].
>> upload   := kérés upload: ['file'].
>> temppath := upload ? 1.
>> filename := upload ? 0.
```

## Maxpost/hossz

A POST-mezők alapértelmezett maximális száma 40, a tartalom alapértelmezett
maximális hossza pedig 2MB. Ezek szkriptenként eltérően is beállíthatók:

```
Program beállítás: ['max-contentlength'] érték: 1. 
Program beállítás: ['max-postfields'] érték: 1. 
```

{{note}}
Ha a tartalom hossza meghaladja a maximumot, a
folyamat leáll, mert már nem lehetünk biztosak abban,
hogy a hasznos adat biztonságos.
{{/note}}

A maxtime korlát határozza meg a stdin/POST-adatok beolvasására
fordítható maximális időt ms-ban.

```
Program beállítás: ['max-time'] érték: 5000. # 5sec
```

Ez csak a POST-adatok beolvasására (I/O) vonatkozik, és megakadályozza
a slowlorishoz hasonló támadásokat. Ha bármely művelet végrehajtási idejét
valóban korlátozni szeretné, használja a Program riasztás: üzenetét.

## Adatbázis

A Database objektummal MariaDB/MySQL-lekérdezéseket futtathat.
Adatbázishoz így csatlakozhat:

```
>> db := Maria-DB új gazdagép: ['localhost'],
	felhasználónév: ['xo'],
	jelszó: ['pass123'],
	adatbázisnév: ['xobase'],
	csatlakozik.

```

Rekord beszúrása:

```
>> keresőparaméterek := db lekérdezés: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], paraméterek: ( Lista új ; ['abc'] ; 12.35 ; 6 ). # parameterized queries

{  keresőparaméterek végrehajt. db véglegesít. }
elkap: { :e db visszavon.  }, indít.
```

Vegye figyelembe, hogy az xoscript *kizárólag* tranzakciókkal dolgozik, és soha nem véglegesít automatikusan.
Ha az automatikus véglegesítés (autocommit) nem kapcsolható ki, kapcsolódási hibát kap.
A lekérdezésekhez mindig használjon paraméterkötést, és soha ne fűzze közvetlenül
a felhasználói bemenetet az SQL-hez.

A beszúrt azonosítót így kérheti le:

```
Kimenet ír: ['INSERTED: '] + keresőparaméterek insert-id, újsor. # insert id
```

Rekordok lekérése:

```
>> keresőparaméterek :=
db
	lekérdezés: ['SELECT * FROM book order by id desc limit 2'], 
	lekér: { :row 
		Kimenet ír: row id + [' '] + row description + [': '] + row price, újsor.
	}. # fetching rows

```

## Munkamenetek

Az adatok megőrzéséhez egy munkamenet-objektumban tárolhat és onnan kérhet le adatokat.
Először hozzon létre egy új **Webdokumentum** objektumot. A Webdokumentum objektum összefogja
a kérést, a fejléceket, a HTML-t és a munkamenetet. Ennek az az oka, hogy amikor
böngészővel meglátogat egy webhelyet, csak a HTML-t látja. A
teljes Webdokumentum azonban **fejlécekből** is áll. Például
a legtöbb HTTP-válasz tartalmaz egy ilyen fejlécet: Content-type:text/html, amely
közli a böngészővel, hogy az ezt követő adatokat HTML-ként kell megjeleníteni
(és nem például fájlként letölteni). A munkamenetekkel
a felhasználói adatok kérések között is megőrizhetők. Ezen adatok nyomon követéséhez
sütit kell beállítanunk, és ez a süti is fejlécen keresztül állítódik be. Ezért
fut össze minden a Webdokumentumban (mivel ez a teljes
dokumentum, amely a fejléceket és a HTML-t vagy más adatokat is tartalmazza).


```
# First we make a new Web Document instance
>> web := Webdokumentum új.

# Now we start a session, this will generate a Header for a cookie and
# create a file to store your data, associated with that cookie
>> session := web munkamenet-indítása.

# Now we can treat session like a dict
session userid: 123.
```

A munkamenet megszüntetése (kijelentkezéskor):

```
web munkamenet-megszüntetése.
```

## Fejlécek

A Webdokumentum más ismert fejlécek beállítását is lehetővé teszi.
Ha például a felhasználót egy másik URL-re szeretné átirányítani:

```
web ugrás: ['/other.html'].
```

A háttérben ez a parancs azt a HTTP-fejlécet is előállítja, amelyet
a többi adattal vagy HTML-lel együtt küld el, hogy a böngésző
a megadott célcímre navigáljon.

Egyéni fejléc hozzáadása:

```
web fejléc: ( 
	HTTP-Fejléc új
	kulcs: ['Content-Length']
	érték: 400
).
```

404-es oldal megjelenítése:

```
web nem-található: ['OOps..'].
```


## Sablonok

Az alapértelmezett sablonrendszer nagyon egyszerű. Nem kell
új sablonszintaxist megtanulnia. A sablonmotor emellett valódi elválasztást
biztosít a megjelenítés és az üzleti logika között.

Sablon létrehozása fájlból:

```
>> tpl := web sablon: ['templates/ux.tpl'].
```

A sablonrendszer jelölőket használ.
Háromféle jelölő létezik: kivágási jelölők, beillesztési jelölők és
helyjelölők. Az alapötlet nagyon egyszerű: kivágja
a kivágási jelölőkkel azonosított területeket, és beillesztheti őket
a beillesztési jelölőkkel azonosított helyekre. A helyjelölőkbe
szövegeket fecskendezhet be.

Például a következő sablon esetén tegyük bele a
drágakövet az ékszerdobozba, és tegyünk rá egy árcédulát.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Ezt a következőképpen teheti meg:

```
>> gem := tpl kivág: ['gem'], másol.
gem price: 99.
tpl beilleszt: gem ide: ['jewels'].
web kiír: tpl tisztít.
```

Az utolsó sor egyszerűen szövegként küldi el a sablont a kliensnek
a szükséges HTTP-fejlécekkel együtt.

Eredmény:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Továbbítás

A felhasználók által feltöltött fájlok biztonságos kiszolgálásához a továbbítási funkcióra (passthru) támaszkodhat:

```
>> uploaded := ['smile.gif'].
Server továbbít: uploaded előtag: ['/uploads/images/'].
Program vége.
```

Ez a felhasználó által feltöltött tartalmat a megfelelő
MIME-típussal szolgálja ki. Csak az engedélyezett listán szereplő MIME-típusok támogatottak:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF és SVG.
Az SVG, ZIP és GZIP fájlok letöltésként kerülnek elküldésre, mivel egy SVG
olyan szkripteket tartalmazhat, amelyek egyébként az Ön tartományán futnának.
Ez a módszer megakadályozza a TOCTOU-támadásokat, az útvonal-bejárást,
a rosszindulatú kód végrehajtását (injektálás), a szimbolikus linkes támadásokat,
a DDoS-támadásokat (fájlkorlát = 50MB), a lehallgatásos (sniffing) támadásokat és
számos egyéb biztonsági problémát.


## JSON

Objektum kódolása JSON formátumba:

```
>> json := ( JSON jsonify: ( 
	Szótár új tesz: ( 
		Lista új ; 1 ; 2 ; 3
	) ide: ['abc']
)).
```

JSON dekódolása xoscript-objektummá:

```
>> dict := ((JSON objektum: json) abc ? 1).
```

Az 500-nál több beágyazási szintet tartalmazó JSON-t a rendszer érvénytelenként elutasítja.

Szótár közvetlen kiírása JSON-ként a megfelelő fejlécekkel:

```
web json: dict.
```


## Reguláris kifejezések

Reguláris kifejezéseket egy minta létrehozásával használhat.
Például a hivatkozások href és target értékeinek illesztéséhez:

```
Minta új: ['href="([^"]+)" target="([^"]+)"'].
```

Ezután alkalmazza a mintát a vizsgált szövegre így:

```
pattern egyezés: tárgy tedd: { :m :x .... }
```

Teljes példa:

```
>> tárgy := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> pattern := Minta új: ['href="([^"]+)" target="([^"]+)"'].
>> result  := pattern egyezés: tárgy tedd: { :m :x
	Kimenet ír: m, újsor.
	Kimenet ír: x, újsor.
	<- ['XXX'].
}.
Kimenet ír: result, újsor.
```

## Hálózatkezelés

Webes kérés végrehajtásához használja a Hálózat objektumot.
A Hálózat objektum mindig POST-kérést küld, kivéve, ha adatként Semmi
értéket ad meg; ekkor GET-kérést küld.


```
Hálózat 
post: Semmi 
ide: ['https://redbeanphp.com'].
```

## Titkosítás

A szerverbővítmény XChaCha20 és Argon2 alapú titkosítást tartalmaz.

Példa:

```
>> encrypted := Széf titkosít: ['hello'] kulcs: ['world'].
>> decrypted := Széf titkosít: encrypted kulcs: ['world'].
```

## Tokenek

Adott hosszúságú, kriptográfiailag biztonságos token előállítása:

```
>> mytok := Széf token: 40.
```

Ez egy 40 karakteres tokent állít elő.

## Formázás

A Formátum objektummal adatokat formázhat, például kitöltéssel vagy
nullák hozzáadásával. A printf szintaxisát használja.

```
>> fmt := Formátum új: ['%06.0f'].
fmt alkalmaz: 56. # gives 000056
```

Egy formátum egyetlen konverziót tartalmazhat, és ennek illeszkednie kell az értékhez,
különben hibát kap:

- `alkalmaz:` szöveggel: `%s`
- `alkalmaz:` számmal: `%f`, `%e`, `%g` vagy `%a`
- `alkalmaz-egész:` számmal: `%d`, `%i`, `%o`, `%u`, `%x` vagy `%c`

A kérésből származó értékek szövegek. Ha egy ilyen értéket számként szeretne formázni,
előbb alakítsa át:

```
fmt alkalmaz: (kérés get: ['amount']) szám.
```

## Kódolók

Számos kódoló és dekódoló áll rendelkezésre.
Az URL-kódoló előkészíti az URL-t arra, hogy hivatkozásként szerepeljen a HTML-ben:

```
Server url-kódolás: ['https://example.com?a=6&b=1 2'].
```

Ha a felhasználói bemenetet XSS-injektálás kockázata nélkül szeretné biztonságosan
beilleszteni a HTML-be, mindig ezt használja:

```
Server html-kódolás: ['<harmless>'].
```

Vegye figyelembe, hogy a sablonmotor mindig elvégzi a HTML-kódolást,
ha helyjelölőbe ír. Ha tehát a sablonrendszert használja,
erre nincs szükség.

## Levelezés

Levél küldéséhez használja a mailtools.xo könyvtárat.

Példa:

```
Server inicializál.
Program használ: ['mailtools.xo'].

>> e-mail := HTML-Email új.
>> img := e-mail csatol: ( Fájl új: ['myimage.png'] ).

e-mail
feladó: ['xo@xoscript.com'] név: ['xo'],
címzett: ( Lista új ; ['xo2@xoscipt.com'] ),
tárgy: ['xoxo'],
levéltörzs: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), küld.

```



## Összekapcsolás

Az összekapcsol: üzenettel külső könyvtárat kapcsolhat
a programjához a libffi segítségével. A részletekért lásd az ffi fejezetet.


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

Az FFI-t platformonként/bővítményenként biztosítjuk, mivel
a mögöttes rendszerarchitektúrához kötődik, amit a
magnak nem feladata megtenni.
A szerverbővítmény megfelelő ffi/blob-megvalósítást kínál.
Alapértelmezés szerint a mag a stdin/stdout, korlátozott fájlkezelési szolgáltatások
és a shell (Program rendszer:) révén kapcsolódik a célplatformhoz.
A kiegészítő integrációt az ffi/blobok biztosítják alkalmazásközpontú
bővítményeken, például a szerverbővítményen keresztül.

Az FFI a Foreign Function Interface (idegenfüggvény-interfész) rövidítése. Lehetővé teszi, hogy mások által
más programozási nyelveken írt funkciókat használjon, amelyeket DLL-, SO- vagy Dylib-fájlok biztosítanak. Ezek
sokféle függvényt tartalmazhatnak, és ezzel a módszerrel rengeteg funkció válik elérhetővé.
Kezdjük egy példával:

```
Server összekapcsol: (
 Lista új ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Lista új ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s felszabadít.
```

A kód eredményeként a következőt látja a parancssorban:
FFI has 3 letters.
Most valószínűleg arra gondol: „Ez rengeteg kód egy ilyen egyszerű dologhoz.”
Hiszen nem oldhatnánk ezt meg egyszerűen egy Gui show paranccsal? A válasz határozott igen!
Ez azonban csak szemléltető példa.
Az FFI-t általában összetettebb feladatokra használják, azok viszont nem
jó példák, ezért valami egyszerűt választottam.

Az összekapcsoló metódus argumentumai:

- 1. argumentum: A használni kívánt DLL- vagy SO-fájl.
- 2. argumentum: A fájlban lévő függvény, amelyet össze szeretne kapcsolni.
- 3. argumentum: Egy lista a függvény argumentumainak adattípusneveivel.
- 4. argumentum: A függvény visszatérési típusának neve.
- 5. argumentum: Annak az objektumnak a neve, amelyhez ezt a függvényt kapcsolni szeretné (ha nem létezik,
automatikusan létrejön).
- 6. argumentum: Az az üzenet, amelyhez ezt a függvényt kapcsolni kell.

A fenti példában a libc.so printf függvényét szeretnénk összekapcsolni. Az adattípusok
neveit annak a szoftvernek a dokumentációjában találja, amelyhez kapcsolódik. A rendelkezésre álló típusok:
void, pointer, float, double, int, uint, char, uchar, intX és uintX,
ahol X lehet 8, 16, 32 vagy 64.

Ezek a típusok az adatok tárolásához szükséges bájtok számára utalnak. A printf esetében egy
új, Printf nevű objektumhoz és a template:number: üzenethez kapcsolunk. A külső
függvényt használat előtt lefordítja az XOScript dialektusára. A template:number: üzenet
első paraméterként egy puffert vár a sablonszöveggel. Ezt a puffert egy Blob objektummal hozzuk létre, amely
lehetővé teszi a memória kézi lefoglalását. Önnek kell gondoskodnia arról, hogy ezt a memóriát utána
a felszabadít üzenettel felszabadítsa.

Egy memóriablob többféleképpen tölthető fel. Példánkban szöveggel töltjük fel, ezért az
utf8: üzenetet használjuk (az UTF-8 egy kódolás, amely a szöveget bájtokká alakítja). Egy blobot
a bytes: üzenettel is feltölthet, bájtértékek listáját átadva. Egy blob tartalmának kiolvasásához használja az ettől:hossz: üzenetet.
A bájtokat listaként kapja vissza. Blobbal akár C-struktúrát is létrehozhat a
struct: üzenettel, C-típusok sorozatát átadva. Erre akkor lehet szükség, ha egy külső
szoftverkönyvtár olyan C-függvényét hívja, amely struktúrára mutató pointert vár.

{warning}
A blobokat saját magának kell felszabadítania.
A szemétgyűjtő nem takarítja el a blobokat.
{/warning}

Mivel a blobok a könyvtárak külső függvényeivel cserélhetők, a szemétgyűjtő
nem tudja őket automatikusan eltakarítani (lehet, hogy a külső függvények még
használják őket, vagy ezek a külső függvények maguk szeretnék
felszabadítani őket). Ezért szükség esetén a blobokat saját magának kell felszabadítania.

Blob felszabadítása:

```
myblob felszabadít.
```

Struktúra felszabadítása:

```
mystruct struct-felszabadít felszabadít.
```

Struktúra esetén tehát két üzenetet kell küldenie: a struct-felszabadít és a felszabadít üzenetet
a memóriablokk felszabadításához.

@api_Blob_fficonnect
