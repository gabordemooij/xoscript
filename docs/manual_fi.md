# Perusteet

{{messages}}


Tervetuloa XOScriptiin
XOScript-projektin tavoitteena on luoda skriptikieli, joka on yksinkertainen ja auditoitava.
Yksinkertainen ei välttämättä tarkoita helppoa.
Tuttu ohjelmointikieli voi olla helpompi käyttää kuin XOScript.
Tässä yksinkertaisuudella tarkoitetaan jotain muuta:
kykyä muodostaa täydellinen mielikuva kielestä ja sen toiminnasta.

XOScript on suunniteltu mahtumaan päähäsi.
Sen kielioppi ja käsitteiden määrä on tarkoituksella pidetty pienenä.
Luokkia ei ole; olioita voi laajentaa suoraan.
Oliot välitetään viittauksina, kopiointi on eksplisiittistä,
ja funktioilla on vain yksi poistumiskohta.

Osa näistä valinnoista poikkeaa merkittävästi valtavirran kielistä.
XOScriptissä ei esimerkiksi ole tyyppijärjestelmää, ja se käyttää dynaamista näkyvyyttä.
Viestit, joita ei voida käsitellä, ohitetaan sen sijaan, että ne aiheuttaisivat poikkeuksen.
Näillä valinnoilla on seurauksensa, eikä niiden tarkoitus ole poistaa virheitä.
Niiden tarkoitus on pitää kielen taustalla oleva malli pienenä ja johdonmukaisena.

XOScriptin voi myös lokalisoida, jolloin liiketoimintasäännöt voidaan
ilmaista luonnollisella kielellä ja mahdollisesti jakaa myös ei-teknisille sidosryhmille.

Auditoitavuus tarkoittaa saman filosofian soveltamista toteutukseen.
Ajoympäristö on kirjoitettu C:llä, ja siinä on pieni käsin kirjoitettu leksikaalinen analysaattori, jäsennin ja puunkulkija.
Standardikirjasto ja ajoympäristö noudattavat pitkälti kielen rakennetta,
joten XOScript-koodin ja sen toteutuksen välinen yhteys on varsin suora.

Myös testit liittyvät tiiviisti dokumentaatioon.
Jokaisella metodilla pitäisi olla oma testinsä, joka voidaan liittää käsikirjaan,
mikä auttaa pitämään dokumentaation ja toteutuksen ajan tasalla keskenään.

XOScriptin tarkoitus ei ole kilpailla valtavirran kielten kanssa
ominaisuuksissa tai tuttuudessa. Se tavoittelee toista päämäärää:
ohjelmointiympäristöä, jonka kehittäjä voi ymmärtää kokonaisuutena.

Toiveena on, että pieni kieli ja pieni
toteutus tekevät ohjelmiston ymmärtämisestä käytännöllistä
tavusta olioon ja syntaksista ajoympäristöön, ja että koodia voi kirjoittaa
varmuudella, koska ymmärtää sekä sen, mitä skriptissä tapahtuu,
että sen, mitä konepellin alla tapahtuu.

XOScript-palvelinympäristön arkkitehtuuri
on yksinkertainen mutta joustava.

{{architecture.png}}

Jotta voit käyttää XOScriptiä palvelinkielenä, sinun on asennettava
palvelinlaajennus kansioon nimeltä /mods/server.

Tämä johtuu siitä, että haluamme
erottaa ydinkielen palvelinkohtaisista toiminnoista,
toisin kuin esimerkiksi PHP tai Python. Muuten meidän pitäisi toimittaa
kaikille koko keittiön tiskiallas ilman mitään syytä, mikä on yksinkertaisesti typerää.
Voit halutessasi asentaa myös muita moduuleja. Järjestelmä on hyvin
joustava.

Lisäksi jotkin toiminnot on parempi toteuttaa itse skriptikielellä,
kuten mallipohjat ja istuntojen käsittely, joten toimitamme
lisäksi kirjastot template.xo ja webtools.xo käyttösi helpottamiseksi.
Syy kaikkeen tähän on se, ettemme tiedä, miten haluat
käyttää XOScriptiä. Voit käyttää sitä palvelinpuolen skriptikielenä,
mutta myös graafisissa käyttöliittymissä, sulautetuissa laitteissa tai pelkässä eräajossa.
Vaikka käyttäisit sitä palvelinpuolen skriptikielenä (mikä on
tällä hetkellä yksi tärkeimmistä käyttötapauksista), saatat silti haluta
käyttää toista mallipohjamoottoria tai toista istunnonkäsittelijää.
Keitä me olemme päättämään, että sinun pitäisi käyttää meidän omiamme?

Oman mallipohjamoottorimme etuna on kuitenkin se, että
sinun ei tarvitse opetella lisäsyntaksia mallipohjien luomiseen.
XOScriptin mukana tuleva oletusmallipohjamoottori erottaa
esityksen ja logiikan toisistaan sataprosenttisesti. Erityisen
mallipohjasyntaksin sijaan se käyttää hyvin joustavaa paikkamerkkijärjestelmää.
Lisätietoja on luvussa Palvelin.

Huomaa, että jos et halua käyttää oletusmallipohjamoottoria tai
oletusverkkotyökaluja, sinun on luonnollisesti tarjottava
omasi.

Jos ajat verkkopalvelintasi chrootissa, jailissa tai muussa hiekkalaatikossa,
sinun on asennettava myös xo:n riippuvuudet kyseiseen ympäristöön. Voit
selvittää tarvittavat kirjastot komennolla ldd (katso Linuxin tai BSD:n man-sivu).
Jos haluat käyttää komentotulkin komentoja xo-skripteissäsi, kopioi myös komentotulkki
(kuten bash tai ksh) tähän ympäristöön.

Haluamme myös huomauttaa, että suhtaudumme taaksepäin yhteensopivuuteen hyvin vakavasti.
Saatavilla on jopa erityinen taaksepäin yhteensopivuuden ominaisuus nimeltä
'version'. Yleisesti ottaen pyrimme siihen, että koodisi toimii ikuisesti. Sinun ei siis
koskaan tarvitse päivittää koodiasi pysyäksesi yhteensopivana XOScriptin uudempien
versioiden kanssa. Tavoitteemme on: kirjoita kerran, aja ikuisesti.

Tämän käsikirjan loppuosa on omistettu XOScript-ohjelmointikielen
yksityiskohtaiselle selittämiselle. Palvelinskriptausta käsitellään luvussa
Palvelin. Jos olet kokenut ohjelmistokehittäjä, voit halutessasi
ohittaa muutaman luvun, koska osa niistä on hieman liiankin yksityiskohtaisia tai
hyvin samankaltaisia kuin yleiset ohjelmointikäytännöt. Jos sinulla
on jo kokemusta useista muista ohjelmointikielistä,
kannattaa käyttää tätä käsikirjaa lähinnä hakuteoksena.

## Asennus Linuxiin

Lataa apache2 ja mariadb:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Lataa XOScript.
Korvaa X oikealla versionumerolla!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Kopioi tiedostot verkkojuureen ja hakemistoon /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Muokkaa apache2:n asetuksia:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Korvaa Virtualhost seuraavalla:

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

Luo testisivu:

```
sudo nano /var/www/html/test.xo
```

ja kirjoita pieni testiohjelma:

```
#!/bin/xo
Server valmistele.
Ohjelma käytä: ['webtools.xo'].
>> web := Verkkodokumentti uusi.
web tulosta: ['Hello World'].
```

Salli apache2:n suorittaa ohjelmasi CGI:n kautta:

```
sudo chmod uog+x /var/www/html/test.xo
```

Käynnistä apache2 uudelleen:

```
sudo systemctl restart apache2
```

Avaa testisivusi selaimessa:

```
http://localhost/test.xo
```

Sinun pitäisi nähdä:

```
Hello World
```


## Asennus OpenBSD:hen

Muokkaa tiedostoa /etc/httpd.conf ja lisää:


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

Jos haluat käyttää SSL:ää:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Suojataksesi avaintenvaihdon kvanttitietokoneita vastaan
valitse mlkem-salausmenetelmä:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Lisää xo-binääri ja modit sekä kaikki riippuvuudet
chrootiin (selvitä ne komennolla ldd).

## Esimerkkien ajaminen


Paketin esimerkkiohjelman ajaminen:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Esimerkiksi FizzBuzz-esimerkin ajaminen Linuxissa:

```
./example.sh fizzbuzz Linux
```

Saman esimerkin ajaminen OpenBSD:ssä:

```
./example.sh fizzbuzz OBSD
```

Esimerkin ajaminen puhtaalla käännöksellä:

```
./example.sh fizzbuzz OBSD clean
```

## Yksikkötestit

Yksikkötestien ajaminen:

```
./runtests.sh
```

Yksikkötestien ajaminen ilman käännöstä (pelkkä testaus):

```
./runtests.sh nobuild
```

## Kääntäminen

Kääntäminen lähdekoodista Linuxissa:

```
make clean
ISO="en" make
```

OpenBSD:ssä:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

Palvelinlaajennuksen kääntäminen Linuxissa:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

Palvelinlaajennuksen kääntäminen OpenBSD:ssä:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Hei maailma

Kun tiedosto on siirretty tietokoneellesi, voit purkaa sen
ja käynnistää xo:n seuraavalla komennolla:

```
xo
```

Jos haluat ajaa XOScript-ohjelman, tallenna ohjelma tiedostoon ja lisää siihen
pääte -xo (valinnainen). Kirjoita lisäksi ohjelmasi tiedostonimi
XOScript-komennon perään:

```
xo myprogram.xo
```

Kun ajat XOScript-komennon ja annat ohjelmatiedostosi
parametrina, xo lukee ohjelmatiedostosi ja suorittaa sen.

{{note}}
Voit käynnistää ohjelmasi myös vetämällä sen xo-kuvakkeen päälle.
{{/note}}

{{warning}}
Joissakin järjestelmissä xo:lle on etukäteen annettava lupa ladata dynaamisia
kirjastoja.
{{/warning}}

Perinteen mukaan minkä tahansa uuden ohjelmointikielen ensimmäisen
ohjelman pitäisi olla eräänlainen tervehdys maailmalle. XOScriptissä
tällainen **Hello world** -ohjelma näyttää tältä:

@test598

Kun tämä teksti tallennetaan tiedostoon, esim. hello.xo, sen voi suorittaa
seuraavasti: .

xo hello.xo

Hello world


Ohjelman tulosteen näet yllä olevasta mustasta ikkunasta.
Koko tämän käsikirjan ajan tulosteet esitetään samalla
tavalla.

{{note}}
Tuloste kirjoitetaan isolla alkukirjaimella.
Yleensä oliot alkavat isolla kirjaimella,
paitsi jos olio toimii instanssina (sillä ei ole
omia metodeja, vain dataa). Tämä vastaa muiden
ohjelmointikielten luokka- ja instanssikäytäntöjä.
{{/note}}


## Syntaksi

XOScript on *puhdas* *olio-ohjelmointikieli*. Tämä tarkoittaa,
että XOScript pitää kaikkea olioina, joten muita *tietotyyppejä*
ei ole. XOScriptillä kirjoitetussa ohjelmassa on pohjimmiltaan kolme
perustoimintoa: *sijoittaminen*, *viestien lähettäminen*
ja *vastaaminen*. Viestien vaihtaminen olioiden välillä on
XOScript-ohjelman keskeisin osa. Nämä kolme toimintoa on havainnollistettu
alla:


Toiminto        | Esimerkki
--------------- | --------
sijoitus        |  \>\> x := 1. 
unaariset viestit | x parillinen?.
binäärinen viesti | 1 + 2.
avainsanaviesti | x alkaen: 0 pituus: 10.
vastaus         | <- vastaus.  


Tämä luku antaa yleiskuvan XOScript-kielestä
ja kuvaa sen perusperiaatteet. XOScript on pieni kieli, joka
perustuu kolmeen toimintoon (katso kuva), joista muodostuu
noin kuusi kielioppisääntöä. Siinä on kaikki, mitä kielen
hallitsemiseen tarvitaan.

Ei hätää, jos kaikki ei heti ole selvää: kaikki rakennuspalikat
käydään läpi seuraavassa luvussa (3), ja perussäännöt
toistetaan. Tämä luku toimii kuitenkin lähinnä yleisenä
johdantona kieleen. Perusperiaatteet selitetään lyhyesti
ja niitä havainnollistetaan useilla aiheeseen liittyvillä esimerkeillä. Puuttuvat
yksityiskohdat käsitellään myöhemmin.

XOScriptin kommentit alkavat merkillä \#. Seuraava rivi
siis ohitetaan:

```
# this is just a comment
```

## Muuttujat

Muuttuja
sijoitetaan muuttujan esittelymerkillä: >>. Muuttujan nimessä
saa olla kaikkia merkkejä paitsi: <-, :=, välilyöntejä,
pisteitä, pilkkuja, kaksoispisteitä, lainausmerkkejä [' '] ja sulkeita ().
Lisäksi muuttuja ei voi jakautua usealle riville. Huomaa,
että muuttuja ei voi alkaa numerolla eikä miinusmerkillä.

Seuraavat ovat esimerkkejä kelvollisista muuttujista:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dollar'].
>> +plus := Tosi.
>> user-password := ['Pssst!'].
```

Kelvottomia muuttujia ovat esimerkiksi:


```
>> -123 := ['negative number'].
>> password of user := ['Classified'].
>> password.of:user := ['Classified'].
>> ,x := 10.
```

{{note}}
Mitään merkkiä ei tarvitse suojata
(ei myöskään lainausmerkkejä, kaksinkertaisia
lainausmerkkejä tai merkkijonon rajoja)
merkkijonoliteraalissa, kunhan se ei
aiheuta epäselvyyttä leksikaaliselle analysaattorille.
{{/note}}

Kun muuttuja on esitelty, sitä voi käyttää vapaasti. Tämä tarkoittaa,
että esittelymerkkiä tarvitsee käyttää vain silloin, kun
muuttujaa käytetään ensimmäisen kerran (esittely).

Tarkemmin sanottuna et voi noin vain alkaa antaa arvoa
muuttujallesi *(x := 2)*, vaan sinun on ensin esiteltävä muuttuja *(\>\>
x := 2)*. Esittelyn jälkeen voit kuitenkin muuttaa sen arvoa
ilman esittelymerkkiä*(\>\> x := 2. x := 3.)*.

Huomaa, että muuttujalle on pakko antaa arvo sen
esittelyhetkellä. Toisin kuin muissa ohjelmointikielissä, muuttujaa ei saa
esitellä ilman arvoa. Jokainen muuttuja on välttämätöntä sitoa
eksplisiittisesti alkuarvoon. Voit kuitenkin vapaasti alustaa
muuttujan **Tyhjä**-oliolla. Tällöin muuttujaa voidaan
pitää tyhjänä *(\>\> x := Tyhjä.)*. Lyhyesti sanottuna muuttujan
esittely ilman alkuarvoa ei ole sallittua. Siis

```
>> x.
```

on virheellinen ja antaa virheilmoituksen.

{{note}}
XOScript käyttää muuttujien dynaamista näkyvyyttä,
lisätietoja on luvussa Funktiot.
{{/note}}


## Literaalit

XOScript pitää kaikkea olioina, eli kaikkia lukuja, merkkijonoja
ja koodinpätkiä. Luvut, kuten 1, 2, 100, -999 ja 1,234, ovat
Luku-olioita. Kaikki yksinkertaisten lainausmerkkien väliset tekstit ovat Teksti-olioita.
Kaikki aaltosulkeiden {...} väliin ryhmitellyt koodinpätkät ovat
Funktio-olioita.

Literaali       | Juuriolio    | Esimerkki
--------------- | ------------ | ----------
luvut           | Luku         | 1,2,3... 
merkkijonot     | Teksti       | \['hello'\]
funktio         | Funktio      | { 1 + 2. }.
                
     
Olioiden, kuten lukujen ja merkkijonojen, alkuperä on aina juurioliossa.
Esimerkiksi kaikki luvut periytyvät oliosta **Luku**. Kaikki
merkkijonot periytyvät oliosta **Teksti** ja kaikki koodinpätkät oliosta **Funktio**.
Kaikki nämä oliot puolestaan periytyvät oliosta **Olio**, joka on itse asiassa
kaikkien olioiden juuriolio.


## Viestit

XOScriptillä ohjelmointi tarkoittaa pohjimmiltaan
viestien lähettämistä olioille. Yleinen merkintätapa viestin lähettämiseksi
oliolle on seuraava:

```
<object> <message>
```

Jos haluat esimerkiksi selvittää, onko luku **2** parillinen, oliolle **2**
lähetetään viesti **parillinen?**:

```
2 parillinen?
```

Vastaus on **Tosi** (jälleen olio). Oliot yleensä
ohittavat tuntemattomat viestit, joten virhettä ei synny. Jotkin oliot (esim.
luvut tai merkkijonot) vastaavat tuntemattomaan viestiin ennalta määritellyllä tavalla
(tästä lisää myöhemmin).

Olio voi vastaanottaa kolmenlaisia viestejä.

Tyyppi          | Argumenttien määrä
--------------- | -------------------
Unaarinen       | 0      
Binäärinen      | 1     
Avainsana       | 1+    


Ensinnäkin on **unaarisia
viestejä**, katso yllä oleva esimerkki, joilla ei ole argumentteja. Toiseksi
on **avainsanaviestejä**, joilla on yksi tai useampi argumentti,
esimerkiksi:

```
>> x := Luku väliltä: 1 ja: 10.
```

Tässä tapauksessa viesti **väliltä:ja:** lähetetään oliolle **Luku**, joka
on kaikkien lukujen juuriolio. Tuloksena on satunnainen luku
väliltä 1–10. Lopuksi on **binäärisiä viestejä**, joissa on
vain yksi merkki ja yksi argumentti:

```
2 + 3
```

Tämä näyttää yhteenlaskulta, mutta se on itse asiassa vain yksi viesti lisää.
Viesti **+** lähetetään oliolle **2** argumentilla **3**, ja se palauttaa
vastauksen **5**. Binääriset viestit saa kirjoittaa ilman kaksoispistettä.

Binäärisiä viestejä voi ketjuttaa:

```
>> x := 3 + 2 - 1.
```

Tässä katkelmassa **+ 2** lähetetään ensin **Luku**-oliolle **3**, mistä
tuloksena on Luku-olio **5**, jonka jälkeen tälle luvulle lähetetään **-1**.
Tarkkaavaiset lukijat huomaavat aivan oikein ristiriidan, joka
tällä käytännöllä on tavanomaiseen matemaattiseen operaattoreiden
laskujärjestykseen. XOScript ohittaa matemaattisen laskujärjestyksen
viestijärjestelmänsä johdonmukaisuuden hyväksi. Tämän seurauksena lauseke:

```
2 + 3 * 5 = 25
```

eikä 17.

Tämä on tarkoituksellista. Sulkeilla voi muuttaa laskujärjestystä:

```
2 + (3 * 5) = 17
```

Useimmat oliot palauttavat tuloksena itsensä vastauksena tiettyyn
viestiin. Tämä on hyödyllistä, koska se kannustaa jatkamaan vuoropuhelua
olion kanssa lähettämällä sille jatkoviestin:

```
Tuloste kirjoita:
[' hello '] siisti isot-kirjaimet.
```

```
HELLO
```

Tässä **Teksti**-oliolle lähetetään kaksi viestiä: **siisti** ja sen jälkeen
**isot-kirjaimet**.

Seuraavassa katkelmassa pilkku on tarpeen osoittamaan,
että tulossa on uusi viesti. Muuten XOScript menee sekaisin.

```
Tuloste kirjoita: ['Hello!'], rivinvaihto.
```

Ensin viesti **kirjoita:** lähetetään kynäsymbolille ja sen jälkeen
**rivinvaihto**. Ilman pilkkua XOScript luulisi, että haluat lähettää
viestin **rivinvaihto** **merkkijonolle** **Hello!**, mikä olisi turhaa.

Viestien käsittelyjärjestys on seuraava: vasemmalta oikealle;
ensin sulkeissa olevat viestit ja sen jälkeen unaariset viestit. Seuraavaksi
binääriset viestit ja lopuksi avainsanaviestit. Katso alla oleva
esimerkki:

```
Tuloste kirjoita: 0.5 pyöristä + (2 - 1), rivinvaihto.
```

XOScript lukee aina vasemmalta oikealle: ensin oliolle Tuloste lähetetään viesti **kirjoita:**,
ja sen jälkeen viesti **rivinvaihto**. Itse argumentin sisällä
XOScript lukee vasemmalta oikealle, eli ensin **0.5 pyöristä**
ja sitten **+**.

{{note}}
Viesti rivinvaihto lisää merkkijonoon rivinvaihtomerkin.
Englanninkielinen nimi stop on saanut innoituksensa lennätinjärjestelmistä.
Lennätinviesteissä käytettiin usein sanaa STOP
merkitsemään virkkeen loppua
(koska välimerkit olivat epäluotettavia tai kalliita).
{{/note}}

Lisäksi **pyöristä** on etusijalla **+**:aan nähden, koska se on
**unaarinen viesti**. Sulkeiden vuoksi **2 - 1** lasketaan
ensin, minkä jälkeen **1** lisätään lausekkeen **0.5 pyöristä** tulokseen (1).

Koko prosessin tulos on **2**, joka on myös kirjoitettu
vastaus. Pilkun jälkeen tulee viesti rivinvaihto, joka siirtää kohdistimen
uudelle riville. XOScript-ohjelmien käsittelyjärjestyksen oppii
tietysti parhaiten ymmärtämään harjoittelemalla.

On syytä huomata, että XOScriptissä, toisin kuin monissa muissa ohjelmointikielissä,
välilyönnit ovat olennainen osa syntaksia. Erityisesti
binääristen viestien kohdalla välilyönnit voivat aiheuttaa
sekaannusta. Käytä aina välilyöntiä binäärisen viestin jälkeen. Lukua ei voi
liittää suoraan viestiin, esimerkiksi:

```
3 + 2
```

eroaa lausekkeesta

```
3 +2
```

Ensimmäinen esimerkki (**3 + 2**) lähettää
viestin **+** luvulle **3** argumenttina luku **2**.
Tuloksena on tässä tapauksessa **5**. Toisessa esimerkissä (**3 +2**)
luvulle **3** lähetetään unaarinen viesti **+2**. Asiayhteydestä
riippuen tulos voi olla hyvin erilainen.

## Olemattomat metodit

Viestin lähettäminen oliolle kutsuu funktiota, joka on
liitetty olioon kyseisellä viestin nimellä. Jos lähetät viestin,
jota ei ymmärretä, vastaanottava olio ohittaa viestisi
ja palauttaa sen sijaan viittauksen itseensä jatkokommunikointia varten.
Tätä kutsutaan suvaitsevaksi viestinvälitykseksi.

Esimerkki:

```
Tuloste kirjoita: Olio blah, rivinvaihto.
```

Tämä ei aiheuta virhettä. Se yksinkertaisesti tulostaa tekstin **Olio**.


## Ohjausrakenteet

XOScriptissä ei tarvita erillisiä kielioppisääntöjä *silmukoille* ja
*ehtolauseille*. Ehtolause on vain yksinkertainen **tosi:**- tai **epätosi:**-viesti
joko **Tosi**-oliolle tai **Epätosi**-oliolle:

```
2 parillinen? tosi: {
	Tuloste kirjoita: ['Two is an even number'], rivinvaihto.
}.
```
Edellisessä esimerkissä viesti **tosi:** lähetetään oliolle **Tosi** (joka on
vastaus kysymykseen: onko 2 parillinen luku?). Argumenttina lähetetään lisäksi
koodinpätkä: **Funktio**-olio. Tämä funktio kirjoittaa
näytölle, että 2 on todellakin parillinen luku.

Myöskään *silmukalle* ei tarvita erillisiä kirjoitussääntöjä. Jos haluat
suorittaa koodinpätkän kolme kertaa, lähetä yksinkertaisesti **\*** argumentilla
**3** kyseiselle **Funktiolle**:

@test5

Tässä katkelmassa **i** on indeksi. Ensimmäisellä kerralla, kun Funktio
suoritetaan, **i** on 0, seuraavalla kerralla **i** = 1 ja
niin edelleen.

Tarkastellaan toista esimerkkiä. Kun halutaan tulostaa muuntotaulukko
*kJ*:stä (kilojoule) *kcal*:iin (kilokalori) sadan välein,
oikea merkintätapa on alla:

@test599

Tässä nykyisen rivin numero välitetään parametrille
**:line**. Funktion alussa määritellään funktion
parametrit. Käyttämättömät parametrit jäävät tyhjiksi (**Tyhjä**). Parametrit
sijoitetaan aina funktion alkuun heti avaavan aaltosulkeen
jälkeen, ja niitä edeltää kaksoispiste.

Viesti **kun:** on *silmukan* ja *ehdon* yhdistelmä.
Kaksi funktiota voidaan yhdistää viestillä **kun:**. Vastaanottava funktio
jatkaa suoritusta, kunnes kaksoispisteen jälkeinen funktio antaa kielteisen
tuloksen. Esimerkki:

@test600

Yllä olevassa koodikatkelmassa **x**:ään lisätään **1** niin kauan
kuin **x** on pienempi kuin **5**. Kun näin ei enää ole,
toinen funktio vastaa **Epätosi**, jolloin ensimmäisen
funktion suoritus päättyy. Huomaa, että **x** on määritelty
funktion ulkopuolella ja on globaali muuttuja. Lisätietoja näkyvyyssäännöistä
on Funktioita käsittelevässä luvussa.

## Merkkijonojen interpolointi

*kJ/kcal*-luettelosta voisi tehdä
esittävämmän. Mieluiten luettelo olisi seuraavanlainen:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Kun muunnat halutun tulosteen mallipohjaksi, sen merkintätapa
voisi olla:

```
number1 kJ ➞ number2 kcal
```

Tämä tarkoittaa, että **number1** vastaa kJ-arvoa ja **number2**
kcal-arvoa. Näin merkkijonojen interpolointi toimii XOScriptissä.
XOScriptissä ei tarvita tätä varten erillisiä kielioppisääntöjä. Lähetä
yksinkertaisesti korvattava sana tekstille ja anna korvaava teksti
argumenttina:

```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

Tulos:

```
100 kj ➞ 23.9 kcal
```

Tämä korvaussääntö toimii jokaiselle määrittelemättömälle viestille, jonka
**teksti**-olio vastaanottaa. Jokainen viesti, jota
**teksti**-olio ei tunnista, tulkitaan seuraavasti: *korvaa viestin
teksti viestin argumentissa olevalla tekstillä.* Voit muokata
ohjelmaa seuraavasti:


@test601


Jotta vältyttäisiin sekaannukselta siitä, mitä viestiä voi tai ei voi käyttää
korvattavana, on parasta ottaa käyttöön mallipohjamerkki, kuten &lt; &gt;,
niille mallipohjan tekstiosille, jotka
on korvattava.

## Paluuarvot

Viestiin vastataan paluunuolella
(*<-*). Seuraava esimerkki havainnollistaa, miten luodaan tehtävä,
joka laskee prosenttiosuuden:

@test602

Kun tehtävä on määritelty ja sijoitettu muuttujaan **percentage**,
sille lähetetään viesti **sovella:ja:** argumenteilla **100** ja **7**.

Tämä suorittaa tehtävän arvoilla **100** ja **7**, eli 7 % sadasta.
Paluunuolen avulla vastaus palautetaan tehtävästä takaisin
pääohjelmaan.

## Laajentaminen

Vaikka tämä koodi on kelvollista, siinä on haittapuoli,
koska argumenttien järjestys on muistettava. Miksi siis ei
kirjoitettaisi näin: *7 percent of: 100 *? Se näyttäisi paljon
*luonnollisemmalta*. Jotta tämä olisi mahdollista, meidän on muokattava
luvun **7** emo-oliota, joka on **Luku**-olio, niin että se ymmärtää
viestin **percent of:**. Tämä onnistuu lähettämällä viesti **kun:tee:**
Luku-oliolle näin:

@test603

Koska prosenttiosuus on tässä tapauksessa luku itse, viittaamme siihen sanalla itse,
eli avainsanalla *itse*. Lyhyesti sanottuna symboli itse tarkoittaa: *lähetä tämä
viesti minulle itselleni*.

# Oliot

{{messages}}

Olemassa olevien olioiden muokkaamisen ja laajentamisen lisäksi voit myös luoda
uusia olioita itse yksinkertaisesti lähettämällä viestin **uusi**. Oletetaan,
että haluat luoda laskuolion, joka valvoo laskujen numerointijärjestystä.
Tällöin tarvitset ensin laskuolion.

Koska jokainen olio periytyy jostakin toisesta oliosta, joka puolestaan
lopulta periytyy kaikkien olioiden juurioliosta nimeltä Olio,
on valittava, minkä näistä muista olioista pohjalle
uusi oliosi rakennetaan. Uusi oliosi perii kaikki sen olion ominaisuudet,
jonka pohjalle se rakennetaan, eli sen olion, jolle viesti **uusi**
alun perin lähetettiin.

Tässä esimerkissä suositaan melko neutraalia oliota, jolla ei ole kovin
paljon perittyjä ominaisuuksia. Valinta on helppo, koska tässä
tapauksessa uusi olio voidaan perustaa itse juuriolioon, joka on
**Olio**. Suunnitellun laskujärjestelmän merkintätapa on silloin
seuraava:

@test604

Nykyinen laskun numero tallennetaan olioon, minkä vuoksi sen eteen
on kirjoitettu avainsana **oma**. Tätä kutsutaan *ominaisuudeksi*;
tarkempia tietoja seuraa myöhemmin.

Jotkin yritykset haluavat, että vuosi sisältyy laskujen
numeroihin. Tässä tapauksessa voit luoda uuden laskuolion, joka perustuu
aiempaan laskuolioon, mutta joka antaa käyttäjälleen mahdollisuuden
syöttää tietyn vuoden:

@test605

Viestin **luku** toteutusta ei tarvitse kirjoittaa
uudelleen, koska se peritään aiemmin kirjoitetusta **laskuoliosta**;
näin vanhaa koodia voidaan käyttää uudelleen. XOScriptissä ei ole käsitteitä
kuten luokat ja muut niihin liittyvät käsitteet. Tämä tarkoittaa, että oliot voivat
periä ainoastaan toisilta olioilta, mikä tunnetaan myös nimellä *prototyyppipohjainen
periytyminen*.

Palataan sitten ominaisuuksiin. Olion ominaisuuksiin pääsee käsiksi vain
*oliohierarkian sisältä*, joten muut oliot eivät
näe näitä ominaisuuksia.

Toisin kuin muissa ohjelmointikielissä, kaikki olioiden ominaisuudet ovat
näkyvissä yksinomaan oliolle, joka on luonut ominaisuuden, sekä
siitä periytyville olioille.

Yleisesti käytetty tekniikka on käyttää oliota eräänlaisena *piirustuksena*,
kuten esimerkiksi aiemmin käsiteltyjen laskujen tapauksessa.
Toinen hyvä esimerkki on **Point**. Oletetaan, että luot
tietokoneohjelman, joka tekee laskelmia kartan pisteiden avulla. Voit
kehittää olion **Point**, jolla on ominaisuuksina
x-koordinaatti ja y-koordinaatti, jotka tuodaan
ulkomaailman saataville viestien kautta:

@test606

Viesti **=** vertaa kahta pistettä viestin **ja:** avulla.
Ensimmäisen vertailun tulos on **Tosi** tai **Epätosi**. Nämä ovat totuusarvo-olioita.
Kun lähetät viestin **ja:** Tosi-oliolle ja
kaksoispisteen jälkeinen argumenttiolio on myös **Tosi**, saat
vastaukseksi jälleen **Tosi**. Jos jompikumpi on **Epätosi**, saat
vastaukseksi **Epätosi**. Huomaa, että piste ei voi lukea toisen pisteen
koordinaatteja. Toiselle pisteelle on lähetettävä viesti, jolla
näitä tietoja pyydetään: **x-coordinate** ja **y-coordinate**. Kuten
jo selitettiin, ominaisuudet ovat saatavilla vain
olioperheen sisältä.

Huomaa, että pisteiden vertailuun käytetään tässä viestiä **=**.
Yhtä hyvin olisi voitu käyttää jotain muuta viestiä, kuten:
**is:** tai **equal:**, mutta merkin **=** uudelleenkäyttö tuntui
tässä tapauksessa sopivalta.

## Periytyminen

Aiemmin kirjoitettua koodia voi käyttää uudelleen oliohierarkian
luomiseen. Esimerkiksi:

```
>> Animal := Olio uusi.
>> Dog := Animal uusi.
>> Poodle := Dog uusi.
```

Tässä tapauksessa **Dog** perii kaiken olion **Animal** käyttäytymisen ja ominaisuudet,
ja olio **Animal** puolestaan perii kaiken olion
**Olio** käyttäytymisen, joka on kaikkien olioiden juuriolio.


## Korvaaminen


Seuraavassa esimerkissä luodaan uudenlainen lista:
**Combination**, jossa jokaisen alkion taataan olevan yksilöllinen.
Listan toiminnot käytetään uudelleen periytymisen avulla:

@test607

Huomaa, miten toinen **red** jätetään pois listasta.

Joskus voi olla tarpeen korvata olion käyttäytyminen.
Esimerkiksi silloin, kun lukuja lasketaan yhteen ja mittayksiköt on
otettava huomioon. Seuraavassa esimerkissä luodaan olio **Size**.
Tämä olio palauttaa luvun, joka yhteenlaskussa ottaa
huomioon lisättävän luvun yksikön. **Luku**-olio
tarkistaa, onko kyse *tuumista* vai *jaloista*. Ohjelmakoodi
voisi näyttää seuraavalta:

@test608

## Rekursio

Edellisessä esimerkissä plus**merkki** korvataan. Huomaa,
että lopullinen yhteenlasku on kuitenkin lopulta tehtävä, ja se itse asiassa
tapahtuu seuraavalla rivillä:

```
>> answer := itse + (luku x factor).
```

Miten XOScript sitten ymmärtää, että tämä plus**merkki** viittaa
alkuperäiseen yhteenlaskun logiikkaan?** Toinen tulkinta voisi
esimerkiksi olla, että XOScript lähettää toistuvasti saman viestin samalle
oliolle, mistä puolestaan seuraisi **loputon silmukka**. Tämä ei
selvästikään ole tarkoitus. Heti kun lähetät oliolle viestin,
joka suorittaisi täsmälleen saman koodin, XOScript ymmärtää,
että tässä tapauksessa tarkoitetaan alla olevaa, korvattua viestiä. Ohjelmasi
on siis automaattisesti suojattu tämänkaltaisilta loputtomilta
silmukoilta. Jos kuitenkin todella haluat ajaa saman funktion
nykyisestä funktiosta, sinun on ensin lähetettävä viesti
**rekursiivinen**. Tällöin tuloksena on loputon
silmukka. Rekursiivisille tehtäville on kuitenkin hyödyllisiä käyttökohteita;
oletetaan esimerkiksi, että haluat laskea annetun luvun kertoman.
Lisää siinä tapauksessa yksinkertaisesti viesti **factorial**
Luku-oliolle:

@test609

Tämä vaatii rekursiota. Viestiin **factorial** liitetty tehtävä
on itse asiassa suoritettava uudelleen saman funktion sisällä.
Kertomafunktiota on siis kutsuttava itse kertomafunktion
sisältä. Pääsääntöisesti XOScript estää tämän,
koska on vaarana päätyä loputtomaan silmukkaan. Tästä syystä
on välttämätöntä kirjoittaa viestin eteen sana **rekursiivinen**. Näin
XOScript saa tietää, että aiot tarkoituksella
suorittaa saman tehtävän etkä tehnyt virhettä.

## Luokkamaiset oliot

Vaikka XOScriptissä ei ole luokkia, luokkamaisen
käyttäytymisen jäljittely on helppoa. Korvaa vain viesti uusi.

```
>> Animal := Olio uusi.
Animal kun: ['uusi'] tee: {
	<- itse uusi valmistele.
}.

Animal kun: ['valmistele'] tee: {
	oma sound := ['?'].
	oma legs  := 4.
}.
```

Yllä olevassa koodikatkelmassa luodaan olio nimeltä Animal.
Tämä olio toimii *piirustuksena* kaikenlaisille eläimille,
kuten koirille ja kissoille. Emo-olio Animal kirjoitetaan
isolla A:lla osoittamaan, että kyseessä on luokkamainen olio.
Seuraavaksi korvaamme viestin uusi kirjoittamalla oman uusi-metodimme.
Tässä tapauksessa se lähettää viestin uusi oliolle itse ja sen jälkeen viestin
valmistele. Koska XOScript estää rekursion oletuksena, tämä ei aiheuta
loputonta silmukkaa. Sen sijaan se lähettää viestin uusi emo-oliolle
(Olio), jolloin tuloksena on uusi Animal-instanssi. Luomme siis
uuden olion, joka perustuu samaan olioon, jolle loimme uusi-metodimme.
Tämä on täysin kelvollista. Lähetämme lisäksi viestin valmistele, mikä varmistaa,
että Animal-oliolla on oletusarvot ominaisuuksilleen. Oletuksena
eläimellä on 4 jalkaa ja ääni on tuntematon (siksi kysymysmerkki).
Uuden Animal-instanssin luomiseksi voisimme sanoa yksinkertaisesti:

```
>> a := Animal uusi.
```

Nyt saamme uuden Animal-instanssin, jolla on 4 jalkaa, tuntematon ääni ja
valmistele-metodi. Aivan kuten muissa olio-ohjelmointikielissä, voimme myös
laajentaa Animal-oliotamme:

```
>> Dog := Animal uusi.
Dog kun: ['valmistele'] tee: {
	itse valmistele.
	oma sound := ['barks'].
}.
```

Tämän voi helposti testata lisäämällä teksti-metodin:

```
Animal kun: ['teksti'] tee: {
	<- oma legs teksti + oma sound.
}.
```

Kootaan kaikki yhteen:

@test13


Olion luominen tiettyyn alkutilaan on
usein toistuva ongelma. Oletetaan, että on luotava olio **Rectangle**
piirin ja pinta-alan laskemiseksi. Mahdollinen merkintätapa olisi:


```
>> Rectangle := Olio uusi.

Rectangle kun: ['area'] tee: {
	<- oma pituus * oma width.
}.
```

On selvää, että pituuden ja leveyden asettaminen on edellytys. Tätä
varten voidaan lisätä viestit **pituus:** ja **width:**:


```
Rectangle kun: ['length:'] tee: { :pituus
	oma pituus := pituus.
}.

Rectangle kun: ['width:'] tee: { :width
	oma width := width.
}.

```

Tätä suorakulmiota voidaan sitten käyttää seuraavasti:


```
>> rectangle := Rectangle uusi length: 2, width: 3.
Tuloste kirjoita: rectangle area.
```

Jos pituuden ja leveyden alkuasetukset kuitenkin unohtuvat,
seurauksena on virheilmoitus:

```
>> rectangle := Rectangle uusi.
Tuloste kirjoita: rectangle area.
```

tuottaa seuraavan virheen:

```
Avainta ei löytynyt:pituus
```

Tämän estämiseksi on parempi, että suorakulmiolla on
aina alkupituus ja -leveys, esimerkiksi 0. Tässä
tapauksessa on siis **korvattava** viesti **uusi**.

@test610

Kun korvaamme uusi-viestin, jäljittelemme pohjimmiltaan **luokkaa**.

XOScriptin maailma on täynnä monenlaisia olioita, jotka ovat
ohjelmasi käytettävissä heti alusta alkaen. Seuraavissa luvuissa
käsitellään kaikki nämä ydinoliot.

## Tilannevedokset

Voit tallentaa olion (ja sen nykyisen tilan) levylle seuraavasti:

```
myobject save-as: ['saved.bin'].
```

Olion lataaminen uudelleen levyltä:

```
>> myobject := Olio load-from: ['saved.bin'].
```

Tilannevedoksilla voi tallentaa tietyn tilan tai parantaa suorituskykyä.
Tilannevedoksen lataaminen ohittaa leksikaalisen analyysin, jäsentämisen ja sovelluksen alustuksen.
Lisäksi tulevaisuudessa tilannevedoksiin voidaan tuoda muitakin suorituskykyetuja,
kuten tiettyjen rakenteiden optimointi tai kuumien polkujen tunnistus ja
optimointi.

{{warning}}
Tilannevedokset ovat kokeellinen ominaisuus, älä käytä niitä tuotannossa.
Kokeelliset ominaisuudet otetaan käyttöön kääntämällä valitsimella -D EXPERIMENTS.
{{/warning}}


@test712

# Tyhjä-olio

{{messages}}

Tyhjä-olio
edustaa tyhjyyttä, tai vielä paremmin, tiedon puuttumista. Toisinaan
saat tämän olion vastauksena viestiin, kun
tulos on **ei mitään**. Tärkein kysymys, jonka
voit esittää **Tyhjä**-oliolle, on: **Tyhjä?**.
Vastaus on aina **Tosi**.

```
Tuloste kirjoita: Tyhjä Tyhjä?.
```

tulos:

```
Tosi
```

Mikä tahansa muu olio kuin **Tyhjä** vastaa **Epätosi**.
Yllä oleva koodikatkelma voi vaikuttaa hieman filosofiselta, mutta **Tyhjä**-oliolla
on ehdottomasti erittäin käytännöllisiä sovelluksia. Saat esimerkiksi
Tyhjä-olion vastauksena, jos pyydät
listan alkiota, jota ei ole olemassa. Voit käyttää Tyhjä-oliota myös silloin,
kun haluat esitellä muuttujan, mutta et vielä halua antaa sille arvoa.
Sen sijaan **sijoitat** muuttujaan vain erikoisarvon **Tyhjä**.
XOScriptissä muuttujaa ei saa esitellä ilman arvoa, esimerkiksi näin:


```
>> arvo.
```

Sen sijaan on kirjoitettava seuraavasti:

```
>> arvo := Tyhjä.
```

@api_None_base

# Totuusarvot

{{messages}}

Toisin kuin useimmat tätä kirjoitettaessa suositut ohjelmointikielet,
XOScript tarjoaa vain yhden ainoan Tosi-olion ja yhden ainoan Epätosi-olion.
Selvennykseksi: aina kun kirjoitat **Tosi**, se ei tarkoita, että
olisi luotu uusi olio. Sen sijaan käytät aina viittausta. Tämä
tarkoittaa, että kun kirjoitat seuraavaa:

\>\> x := Tosi.

**x** viittaa **Tosi**-olioon. Myös ehdollinen koodi ja silmukat
tarkistavat tämän viittauksen. XOScriptissä **Tosi**- ja **Epätosi**-olioiden merkitys
ei ole kiinteä. XOScript-ohjelma itse asiassa menee melkoisesti sekaisin
tällaisesta lauseesta:

Tosi := Epätosi.

Tällaisten toimien tulos on määrittelemätön, mutta se on silti kelvollinen
toimi ja siksi muodollisesti sallittu. Lisäksi on olemassa Totuusarvo-olio,
joka on sekä **Tosi**- että **Epätosi**-olion juuriolio, sillä molemmat
periytyvät siitä. Itse Totuusarvo-oliolla ei kuitenkaan
ole käytännön sovelluksia.

## Sudenkuopat

Ole varovainen käyttäessäsi viestejä **ja:** ja **tai:**

```
Tuloste kirjoita: (Epätosi or: Tosi or: Tosi), rivinvaihto.
Tuloste kirjoita: (Epätosi tai: Tosi, tai: Tosi), rivinvaihto.
```

Tuottaa

```
Epätosi
Tosi
```
koska viesti **tai:** ottaa vain yhden argumentin. Ensimmäinen rivi
lähettää viestin **tai:tai:** oliolle Epätosi, jota ei ole olemassa, joten olio ohittaa
viestin ja palauttaa itsensä (Epätosi). Toinen rivi taas
lähettää viestin **tai:** ja sen perään toisen **tai:**-viestin (ketjutusmerkin eli pilkun , avulla).


@api_Boolean_base

# Luvut

{{messages}}

Aina kun kirjoitat luvun, esimerkiksi 9, -10 tai 3,12, XOScript
muuntaa sen kulissien takana **Luku**-olioksi. Voit
lähettää viestejä tälle Luku-oliolle, tai voit sijoittaa luvun
muuttujaan ja lähettää viestit sen jälkeen:

```
10 parillinen?

>> tenner := 10.
tenner parillinen?

```

Molemmat merkintätavat ovat kelvollisia. Luku-olio vastaa seuraaviin
viesteihin...

Useimmat näistä viesteistä ovat itsestään selviä, ja niillä voi suorittaa
matemaattisia laskutoimituksia tai vertailuja.

{{note}}
Huomaa, että voit käyttää merkkejä ≤ ≥ ≠ × ja ÷ niiden ASCII-vastineiden sijaan.
Tämä on makuasia.
{{/note}}

Binääristen matemaattisten viestien (+) ja niiden
avainsanamuunnelmien (lisää:) ero on siinä, että edelliset palauttavat
uuden luvun, joka on laskutoimituksen tulos, kun taas
jälkimmäiset muuttavat itse oliota. Tätä havainnollistetaan
seuraavassa esimerkissä:

@test597

Yllä olevassa esimerkissä b = 4 ja a = 3. Viesti **lisää: 2** kasvattaa
a:n arvoa kahdella, kun taas **+ 3** luo uuden luvun, joka on
yhtä suuri kuin a + 3. Sama pätee muihin laskutoimituksiin, esim.
kertolaskuihin. Kertomerkkiä käyttämällä saat vastaukseksi
uuden olion. Jos käytät viestiä **kerro:**,
kerrot itse lukua.

Viestillä **väliltä:ja:**, esimerkiksi lausekkeessa **Luku
väliltä: X ja: Y**, saat luvun väliltä X–Y. Tällä
tavalla voi tuottaa minkä tahansa satunnaisluvun:

```
>> a := Luku väliltä: 1 ja: 10.
Tuloste kirjoita: a, rivinvaihto.
```

Versiosta 1.4 alkaen XOScriptin sisäänrakennettu satunnaislukugeneraattori on
parhaan tietämyksemme mukaan kryptografisesti turvallinen.

Luvulle voi liittää **määritteen**, esimerkiksi **6
omenaa**. Jokaista viestiä, jota luku ei tunnista,
pidetään määritteenä. Luvun määritteen voi hakea
viestillä määrite:

Määrite on pohjimmiltaan Teksti-olio, joka tallennetaan Luku-olion
yhteyteen. Määrite tulostetaan myös luvun perään
**kirjoita:**-käskyssä. Määritteillä voisi esimerkiksi laskea yhteen summia
eri valuutoissa. Summia yhteen laskettaessa voi kysyä
määritteitä. Seuraava ohjelmaesimerkki havainnollistaa tätä
periaatetta historiallisen valuuttalaskurin avulla (koska vaihtokurssi
pysyy kohtuullisen vakaana!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Merkkijonot

{{messages}}

Aina kun teksti sijoitetaan **hakasulkeiden ja lainausmerkkien** ['...'] väliin,
XOScript luo sinulle uuden merkkijono-olion. Varmista kuitenkin,
että käytät oikeita lainausmerkkejä. Tekstin alussa oleva lainausmerkki
eroaa lopussa olevasta (näin voit käyttää
yksinkertaista lainausmerkkiä ilman, että sitä tarvitsee suojata).

## UTF8

XOScriptin merkkijonot sisältävät yleensä utf8-koodattua tekstiä. Vaikka
merkkijonossa on teknisesti mahdollista olla binääristä tai muuta kuin utf8-sisältöä,
siihen suositellaan käytettäväksi blobeja. Blobit
tarjoaa palvelinlaajennus (katso luku ffi).
Yleisesti blobit/ffi tarjotaan
laajennus- tai alustakohtaisesti, koska ne ovat sidoksissa alustaan
ja arkkitehtuuriin (ffi/blobit). Skriptikielen ydin pyrkii
pysymään mahdollisimman alustariippumattomana.

## Tyyppimuunnokset

Jokaisesta oliosta voi luoda kopion,
jolla on eri tyyppi, seuraavilla viesteillä:

Viesti      | Tulos
----------- | ------
luku        | Muuntaa luvuksi
teksti      | Muuntaa merkkijonoksi
totuusarvo  | Muuntaa totuusarvoksi
  
Seuraavat säännöt **pätevät**:

viesti     | Tyhjä     | Totuusarvo           | Luku                    | Teksti    | Muu
---------- | --------- | --------             | --------                | --------  | --------
totuusarvo | Epätosi   | –                    | 0→Epätosi muu→Tosi      | Tosi      | Useimmiten Tosi
luku       | 0         | Epätosi→0 Tosi→1     | –                       | ['n']→n   | Useimmiten 1
teksti     | ['Tyhjä'] | ['Epätosi']/['Tosi'] | ['n']                   | –         | Vaihtelee

## Kopiointi

XOScriptissä arvot välitetään aina **viittauksina**. Muissa kielissä
se riippuu arvon tyypistä, mutta XOScriptissä on vain yksi tapa:
viittauksena. XOScript ei koskaan tee arvosta kopiota. Olion kopioimiseksi
sille on lähetettävä viesti **kopioi**.

@test611

Tässä olisit ehkä odottanut, että tuloste olisi Dolly eikä
Donny. Näin ei kuitenkaan ole, koska molemmat nimet viittaavat samaan
olioon. Silmukan kanssa työskenneltäessä tapahtuu jotain samankaltaista:

@test612

XOScript käyttää itse asiassa **aina** viittauksia, joten yllä olevassa
silmukassa **:quantity** osoittaa myös viittauksen listan
alkioon.

Olion kopioimiseksi tämä toimenpide on määriteltävä
**eksplisiittisesti**:

@test613

Kun merkkijonolle lähetetään unaarinen viesti **kopioi**, olio
palauttaa kopion samasta merkkijono-oliosta. Samalla tavalla voi kopioida
Luku-olioita, totuusarvo-olioita, listoja ja sanakirjoja.

Voit myös määritellä oman kopiointitoteutuksesi, mikä on jopa
välttämätöntä, jos luot omia olioita. Listan kopioinnin
oletustoteutus tekee matalan kopion, eli se luo
uuden listan, jossa on samat alkiot.

@test614

Tässä tapauksessa 4 lisätään vain kopioon.
Koska kopio on kuitenkin matala, molempien listojen oliot
ovat samoja.

@test615

Jos siis lisäämme kopion jokaisen nimen perään 2, myös alkuperäinen
lista muuttuu.

Tämän korjaamiseksi on tehtävä **syväkopio**. Tällainen
listan kopiointitoiminto voitaisiin koota seuraavasti:

@test616

Huomaa myös viesti rekursiivinen; tämä viesti on lähetettävä
ennen viestiä kopioi.

On tärkeää muistaa, että vaikka olion kopio
usein näyttää samalta kuin alkuperäinen, se ei
koskaan ole sama. Juuriolio määrittelee viestin **equal:**,
jolla voi verrata olioiden identiteettiä. Katso
seuraavaa esimerkkiä:

@test617

## Implisiittinen muunnos

XOScript muuntaa olioita **implisiittisellä muunnoksella**. Jos esimerkiksi
lista tulostetaan näytölle, XOScript lähettää listalle sisäisesti viestin
*teksti*. Tämä voi osoittautua erittäin hyödylliseksi, jos
haluat tulostaa listan pilkuilla erotettuna luettelona.
Viestin *teksti* voi korvata:

@test620

@api_String_base
@api_Format_base


## Palvelimen merkkijonot

Seuraavat Teksti-ominaisuudet lisää
palvelinlaajennus.

@api_String_server

# Funktiot

{{messages}}

Voit ryhmitellä koodia merkkien { ja } väliin, jolloin siitä tulee funktio.
XOScriptissä käytämme joskus myös termiä tehtävä tai yksinkertaisesti
koodilohko.

Funktion voi ajaa lähettämällä sille viestin *käynnistä*.


```
{ Tuloste kirjoita: 123, rivinvaihto. } käynnistä.
```

Jos funktiosi ottaa argumentteja, käytä viestiä **sovella:**.

```
{ :a Tuloste kirjoita: a, rivinvaihto. } sovella: a.
```

Katso myös alla olevat esimerkit.
Yksinkertaisen arkkitehtuurin vuoksi funktiolla voi olla vain
yksi paluukohta. Ehtojen aiheuttaman ylimääräisen työn tai liiallisen sisäkkäisyyden
välttämiseksi voit käyttää proseduuria (mikä on sama asia kuin
kertomerkin käyttö argumentilla 1):

```
{
  (a = 1) tosi: { x := 1. }, keskeytä.
  (a = 2) tosi: { x := 2. }, keskeytä.
} proseduuri.
```

Näin (a = 2) jätetään arvioimatta, jos a = 1.
Lisäksi et tällä tavalla tarvitse sisäkkäisiä tosi-viestejä.
Aina kun huomaat kirjoittavasi sisäkkäisiä ehtoja, muista
viesti proseduuri. Se voi tehdä koodistasi
helppolukuisempaa.


Tässä on tärkeä sudenkuoppa:

```
{
	Epätosi epätosi: {
		Tuloste kirjoita: ['End the loop.'].
	}, keskeytä.
	
	Tuloste kirjoita: ['Dont show me.'].

} proseduuri.

```

Tässä tapauksessa teksti 'Dont show me' näytetään,
koska **keskeytä** lähetetään oliolle Epätosi. Jos haluat suorittaa
keskeytyksen, se on lähetettävä viestinä oliolle **Tosi**.
 

```
{
	Epätosi ei tosi: {
		Tuloste kirjoita: ['End the loop.'].
	}, keskeytä.
	
	Tuloste kirjoita: ['Dont show me.'].

} proseduuri.

```

Toimii odotetusti.

## Poikkeukset

Poikkeuksia voi käsitellä näin:

```
{ Task 1 } sieppaa: { Task 2 }, käynnistä.
```

Voit myös tarkoituksella aiheuttaa ohjelmassasi virheen ja
näin aktivoida käsittelijälohkon. Tämä tehdään lähettämällä
nykyiselle tehtävälle viesti **virhe:**, kuten seuraavassa
esimerkissä näytetään:

```
{
tämä-tehtävä virhe: ['Whoops!'].
} sieppaa: { :mistake
Tuloste kirjoita: mistake.
}, käynnistä.
```

## Arvojen injektointi

XOScript tarjoaa tehtäville mahdollisuuden injektoida arvoja. Katso
alla olevaa tehtävää:

```
>> sending := {
	Newsletter vastaanottaja: oma recipient.
}.
sending aseta: ['recipient']
arvo: ['info@recipient.org'].
sending käynnistä.
```


Tämä esimerkki esittää kuvitteellisen tehtävän, joka lähettää uutiskirjeen
sähköpostiosoitteeseen eli **vastaanottajalle** (recipient). Tämän vastaanottajan voi injektoida
tehtävään ulkopuolelta ennen tehtävän käynnistämistä lähettämällä
tehtävälle viestin **aseta:arvo:**. Näin muuttujan
**recipient** arvo asetetaan tehtävään valmiiksi. Tätä arvoa voi myös muuttaa,
minkä jälkeen tehtävän voi ajaa uudelleen. Tämä on hyödyllinen menetelmä
Tehtävä-olioita käytettäessä.

## Tyhjät funktiot

Tyhjät tehtävät eivät ole sallittuja. Teoriassa tyhjä tehtävä näyttäisi
tältä: **{}**, mutta XOScript pitää tätä kielivirheenä. Jos
haluat esitellä tyhjän tehtävän, voit käyttää Tyhjä-oliota:

```
>> task := Tyhjä.
```

Vaikka tämä ei ole oikea tehtävä vaan Tyhjä-olio, sille voi
silti lähettää käynnistä-viestin:

```
>> answer := task käynnistä.
```

Tämä on itse asiassa sama kuin:

```
>> answer := Tyhjä käynnistä.
```

Koska olio **Tyhjä** ei tunnista viestiä **käynnistä**, se
palauttaa vastauksena itsensä, jolloin vastaus on jälleen **Tyhjä**.
Tyhjää tehtävää ei siis tarvita. XOScript-ohjelmointikielen
tyylikkään suunnittelun ansiosta voit yksinkertaisesti käyttää tähän
Tyhjä-oliota.

## Dynaaminen näkyvyys

Kun Funktio tarvitsee muuttujaa, mutta ei löydä sitä,
se tarkistaa sen Funktion muuttujat, joka **kutsui** sitä,
ja jatkaa tarkistamista Funktioiden ketjussa ylöspäin.
Tämä hakuprosessi jatkuu, kunnes muuttuja löytyy.
Jos muuttujaa ei vieläkään löydy, näyttöön tulee virheilmoitus. Tätä tapaa
etsiä muuttujaa kutsutaan **dynaamiseksi näkyvyydeksi**.

Periaatteen havainnollistamiseksi:

@test618

@api_Code_base

# Juuriolio

{{messages}}

Olio nimeltä **Olio** on kaikkien XOScriptin olioiden juuriolio,
ja se tarjoaa kielen ydinominaisuudet.

Useimmin lähetetty viesti
on **kun:tee:**, joka laajentaa olion toiminnallisuutta. Tämän
viestin vastaanottaa juuriolio, joka liittää
annetun tehtävän viestiin ja laajentaa näin periytyvää
oliota.

## Yleismetodit

Tavallisesti, jos lähetät viestin, joka ei vastaa mitään
olion metodia, viesti ohitetaan. Voit kuitenkin määritellä
niin sanottuja **taikametodeja** eli **yleismetodeja**, joita
kutsutaan, jos olio ei ymmärrä viestiä.

Käytettävissä on 4 yleismetodia. Kukin viesti vastaa
tiettyä argumenttien määrää.

Yleisviesti          | Argumenttien määrä
-------------------- | -------------------
vastaa:              | 0
vastaa:ja:           | 1
vastaa:ja:ja:        | 2
vastaa:ja:ja:ja:     | 3


@test619

## Ohjelmalliset viestit

Sen sijaan, että viesti lähetettäisiin suoraan oliolle, sen voi myös
lähettää muuttujan kautta. Tähän käytetään viestiä
**viesti:argumentit:**.

@test396

@api_Object_base

# Listat

{{messages}}

XOScript tuntee kaksi kokoelmatyyppiä: *listat* ja *sanakirjat*.
**Listat** ovat olioiden luetteloita *kiinteässä järjestyksessä*. Sanakirjoilla
ei ole järjestystä, vaan ne muistuttavat selitysluetteloa, jossa on avain (tai termi) ja sitä
vastaava arvo. Listat vastaavat taulukoita (PHP, Java, C)
ja listoja (Python). Sanakirjat vastaavat muiden ohjelmointikielten
assosiatiivisia taulukoita (PHP) tai sanakirjoja (Python). Uuden
Listan luomiseksi kirjoita:

```
>> fibonacci := Lista uusi.
```

Tämän tyhjän listan voi täyttää viestillä **lisää-loppuun:** :

```
fibonacci lisää-loppuun: 0.
fibonacci lisää-loppuun: 1.
fibonacci lisää-loppuun: 1.
fibonacci lisää-loppuun: 2.
fibonacci lisää-loppuun: 3.
fibonacci lisää-loppuun: 5.
fibonacci lisää-loppuun: 8.
fibonacci lisää-loppuun: 13.
```

Jos kirjoitamme listan näytölle:

```
Tuloste kirjoita: fibonacci, rivinvaihto.
```

Näemme:

```
Lista ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

Viestin lisää-loppuun sijaan voit lisätä alkioita listaan myös merkillä ;:


```
>> fibonacci := Lista uusi ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Puolipisteet (;) ovat kaikki binäärisiä viestejä, jotka lisäävät
arvon listaan.

## Ketjutus

Oletetaan, että sinulla on esimerkiksi tällainen lista:

```
>> x := Lista uusi ; 1 ; 2 ; 3.
```

Jos haluaisit poistaa ensimmäisen ja viimeisen alkion,
viestisi olisi:

```
x poista-ensimmäinen poista-viimeinen.
```

Valitettavasti edellinen merkintätapa ei toimi oikein.
Viesti **poista-ensimmäinen** palauttaa listan ensimmäisen alkion, josta
puolestaan tulee viestin **poista-viimeinen** vastaanottaja. Viestiä
**poista-viimeinen** ei siis lähetetä muuttujalle **x**, vaan luvulle 2.
Yksi mahdollinen ratkaisu tähän ongelmaan olisi kirjoittaa kaksi erillistä
lausetta, esimerkiksi:

```
x poista-ensimmäinen.
x poista-viimeinen.
```

Tämä on kuitenkin melko epäkäytännöllistä, erityisesti kun on
poistettava enemmän kuin kaksi alkiota. Siksi XOScript tarjoaa
tällaisia tilanteita varten vaihtoehtoisen viestirakenteen.
**Vaihtoehtoisissa** viestirakenteissa olioiden vastaukset ohitetaan,
ja saat vastaukseksi aina uudelleen vastaanottavan olion.
**Vaihtoehtoinen** viestirakenne aloitetaan lähettämällä oliolle
viesti **tee**, ja **vaihtoehtoinen** viestirakenne
lopetetaan lähettämällä viesti **valmis**. Esimerkin
tapauksessa tätä voitaisiin soveltaa seuraavasti:

```
>> x := Lista uusi ; 1 ; 2 ; 3.
x tee poista-ensimmäinen poista-viimeinen valmis.
```

@api_List_collections

# Sanakirjat

{{messages}}

**Sekä Lista että Sanakirja ovat kokoelmia. Toisin kuin listalla,
sanakirjalla **ei ole** järjestystä. Toinen ero niiden välillä
on se, että sanakirja koostuu oliopareista. Yksi olio toimii hakusanana (tai
avainsanana), jonka avulla toinen olio haetaan. Hyvä esimerkki
tällaisesta luettelosta on hinnasto, kuten:


```
>> menu := Sanakirja uusi
	aseta: ['£5'] kohtaan: ['apple pie'],
	aseta: ['£6'] kohtaan: ['carrot cake'],
	aseta: ['£3'] kohtaan: ['fudge'].
```

Listan tapaan viestiä aseta:kohtaan:
käytetään olion lisäämiseen luetteloon. Erona on se, että toisin kuin
listassa, tässä linkitetään kaksi oliota. Ensimmäinen olio on listan
tapaan se olio, jonka tallennat luetteloon. Toinen
olio ei ole sen sijainti kokoelmassa, vaan **hakusana**,
jonka avulla edellinen olio voidaan myöhemmin hakea.
Lyhyesti sanottuna sanakirja toimii vähän kuin oikea sanakirja: avainsanan avulla
löytyy merkitys. Esimerkiksi fudgen hinnan hakeminen
yllä mainitusta luettelosta:

```
>> price := menu kohdassa: ['fudge'].
```

Voit käyttää myös tiivistä merkintätapaa:

```
>> price := menu ? ['fudge'].
```

Jos olioiden tallentamiseen käyttämäsi hakusanat ovat ilman välilyöntejä
(eivätkä ole ristiriidassa muiden ennalta määriteltyjen viestien kanssa),
voidaan käyttää myös seuraavaa merkintätapaa:

```
>> menu := Sanakirja uusi
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Yllä oleva merkintätapa lukeutuu epäilemättä hieman luonnollisemmin.
Fudgen hinnan kysymiseen
voidaan käyttää seuraavaa yksinkertaistettua merkintätapaa:

```
>> price := menu fudge.
```

@api_Dict_collections

# Tiedosto

{{messages}}

**Tiedosto**-olio tarjoaa perustason pääsyn tiedostojärjestelmään.
Tällä oliolla voi lukea kokonaisia tiedostoja muuttujaan kerralla
tai kirjoittaa muuttujia tiedostoihin kerralla. Myös rivi riviltä lukeminen
on tuettu. Nämä ovat skriptikielen yleisimmät tiedostojen
I/O-toiminnot. Edistyneemmät tiedostotoiminnot edellyttävät
FFI:n käyttöä palvelinlaajennuksen tai erillisen IO-laajennuksen kautta.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Päivämäärä/aika

{{messages}}

Ajan ja päivämäärän jäsenneltyyn esittämiseen XOScript käyttää
**Hetki**-oliota. Jos uusi Hetki-olio tulostetaan näytölle,
näytetään nykyinen päivämäärä ja kellonaika:

```
Tuloste kirjoita: Hetki uusi, rivinvaihto.
```

Tulos voi olla esimerkiksi:

```
2020-10-10 12:16:39
```

Myös yksittäiset ajan osat on helppo lukea. Jos esimerkiksi
tarvitaan tietää vain kuluva vuosi, hetkelle voidaan lähettää viesti
**vuosi**, ja vastauksena saadaan
Luku-olio, joka sisältää pelkän vuoden:

```
>> m := Hetki uusi.
Tuloste kirjoita: m vuosi, rivinvaihto.
```

@api_Moment_system

# Ohjelma/vakiotuloste

{{messages}}

Ohjelma-olio edustaa parhaillaan käynnissä olevaa sovellusta. Tämä olio
tarjoaa toiminnot järjestelmäkomentojen suorittamiseen, aliohjelmien sisällyttämiseen,
argumenttien lukemiseen ja muuhun. Kaikki järjestelmään liittyvät toiminnot.

## Vakiotuloste

Tuloste on vakiotulosteolio. Sillä on pohjimmiltaan kaksi metodia:
**kirjoita:** ja **rivinvaihto**. Viestillä kirjoita: lähetetään merkkijono
vakiotulosteeseen (stdout), ja viesti rivinvaihto tulostaa rivinvaihtomerkin.
Viestin **rivinvaihto** sijaan voit käyttää myös merkintää \\n.

Esimerkki:

```
Tuloste kirjoita: ['Hello World'], rivinvaihto.
```

tulos:

```
Hello World
```

## Moduulit/laajennukset

XOScriptin maailmaa voi laajentaa uusilla järjestelmäolioilla
asentamalla moduuleja. Uuden järjestelmäolion voi lisätä
XOScriptin maailmaan sijoittamalla moduulitiedoston (yleensä tiedosto, jonka pääte on .so)
mods-kansioon.

Kun lähetät viestin oliolle, joka on saatettu käyttöön
laajennusmoduulin kautta, XOScript lataa sen automaattisesti.

Voit myös kirjoittaa laajennuksia itse. Laajennukset kirjoitetaan
C-ohjelmointikielellä. Esimerkkilaajennuksen löydät lähdekoodipaketista
hakemistosta src/plugins/example.


## Reflektio

Järjestelmää voi tutkia
ohjelman suorituksen aikana monin tavoin. XOScriptissä on muutamia metodeja,
joilla voi selvittää, mitä olioita on olemassa ja mihin viesteihin nämä oliot
vastaavat. Ensinnäkin jokaiselta oliolta voi kysyä, mikä sen **tyyppi** on,
mutta tyypit ovat XOScriptissä muokattavia ja siksi epäluotettavia.

Ohjelma-oliolta voi myös kysyä, onko
tietty olio jo olemassa ohjelmassa:

```
Ohjelma Tool tosi: { ... }.
```

Jos olion
nimi koostuu yhdestä ainoasta merkistä, on parasta käyttää
seuraavaa merkintätapaa sekaannusten välttämiseksi:

```
Ohjelma etsi: ['X'], tosi: { ... }.
```

Olioiden lisäksi Ohjelma-oliolta voi yhtä lailla kysyä
viesteistä. Siltä voi esimerkiksi kysyä, tunteeko
olio **Luku** viestin **väliltä:ja:**, alla
havainnollistetulla tavalla:

```
Ohjelma Number: ['between:and:'], rivinvaihto.
```

@api_Program_system

# palvelin

{{messages}}

XOScriptin palvelinlaajennus tarjoaa toiminnot
palvelinpuolen sovellusten luomiseen. Palvelinlaajennus
ladataan näin:

```
Server valmistele.
```

Käytön helpottamiseksi on myös suositeltavaa ladata
tiedostot webtools.xo ja template.xo.

```
Ohjelma käytä: ['webtools.xo'].
Ohjelma käytä: ['template.xo'].

```

## Palvelimen asetukset

Voit määrittää seuraavat palvelinasetukset:

```
	# default values are given
	# so if you do not set anything these
	# values are used...

	Ohjelma 
	asetus: ['max-postfields']
	arvo: 40.

	Ohjelma 
	asetus: ['max-contentlength']
	arvo: 2000000. # 2MB

	Ohjelma 
	asetus: ['max-time']
	arvo: 5000. # 5sec

```

## Hei maailma

Tässä on hyvin yksinkertainen verkko-ohjelma, jota voit käyttää
tavallisen CGI-palvelimen, kuten Apache2:n, NGINX:n, OpenHTTPD:n tai minkä tahansa muun
tunnetun palvelimen kanssa.

```
#!/bin/xo

Server valmistele.
Ohjelma käytä: ['webtools.xo'].

>> web-document := Verkkodokumentti uusi.

web-document tulosta: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Jos et halua käyttää Verkkodokumentti-oliota, sekin käy, mutta
silloin sinun on kirjoitettava HTTP-otsakkeet itse:

```
#!/bin/xo
Tuloste kirjoita: ['Content-type: text/html; charset=utf-8 \n\n'], rivinvaihto.
Tuloste kirjoita: ['hello world!'], rivinvaihto.
``` 

## Pyyntö

HTTP-Pyyntö-oliolla voi hakea GET-, POST-, COOKIE- ja
UPLOAD-tietoja:

```
>> pyyntö  := HTTP-Pyyntö uusi.
>> search   := pyyntö get: ['search']. # ?search=books
>> password := pyyntö post: ['password']. # from form
>> selected := pyyntö get-lista: ['sel[]']. #?sel[]=1&sel[]=2
>> selected := pyyntö post-lista: ['sel[]'].
>> cookie   := pyyntö cookie: ['session-id'].
>> upload   := pyyntö upload: ['file'].
>> temppath := upload ? 1.
>> filename := upload ? 0.
```

## Maxpost/length

POST-kenttien oletusenimmäismäärä on 40 ja sisällön oletusenimmäispituus
on 2 Mt. Asetukset voi määrittää skriptikohtaisesti toisin:

```
Ohjelma asetus: ['max-contentlength'] arvo: 1. 
Ohjelma asetus: ['max-postfields'] arvo: 1. 
```

{{note}}
Jos sisällön pituus ylittää enimmäismäärän,
prosessi lopetetaan, koska emme voi enää olla varmoja
siitä, että sisältö on turvallinen.
{{/note}}

Maxtime-raja määrää enimmäisajan millisekunteina
stdinin/POST-datan lukemiselle.

```
Ohjelma asetus: ['max-time'] arvo: 5000. # 5sec
```

Tämä koskee vain POST-datan I/O-lukemista ja estää
slowloris-tyyppiset hyökkäykset. Jos todella haluat rajoittaa
minkä tahansa toiminnon suoritusaikaa, käytä viestiä Ohjelma hälytys:.

## Tietokanta

Database-oliolla voi tehdä kyselyjä MariaDB:hen/MySQL:ään.
Tietokantaan yhdistetään näin:

```
>> db := Maria-DB uusi isäntä: ['localhost'],
	käyttäjänimi: ['xo'],
	salasana: ['pass123'],
	tietokannan-nimi: ['xobase'],
	yhdistä.

```

Tietueen lisääminen:

```
>> hakuparametrit := db kysely: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parametrit: ( Lista uusi ; ['abc'] ; 12.35 ; 6 ). # parameterized queries

{  hakuparametrit suorita. db vahvista. }
sieppaa: { :e db peru.  }, käynnistä.
```

Huomaa, että XOScript toimii *ainoastaan* transaktioiden kanssa eikä koskaan vahvista automaattisesti (autocommit).
Jos autocommitia ei voi poistaa käytöstä, saat yhteysvirheen.
Käytä kyselyissä aina parametrien sidontaa, älä koskaan lisää käyttäjän syötettä suoraan
SQL-lauseeseen.

Lisätyn tietueen tunnisteen saa näin:

```
Tuloste kirjoita: ['INSERTED: '] + hakuparametrit insert-id, rivinvaihto. # insert id
```

Tietueiden hakeminen:

```
>> hakuparametrit :=
db
	kysely: ['SELECT * FROM book order by id desc limit 2'], 
	hae: { :row 
		Tuloste kirjoita: row id + [' '] + row description + [': '] + row price, rivinvaihto.
	}. # fetching rows

```

## Istunnot

Pysyvyyttä varten voit tallentaa ja hakea tietoja istunto-oliosta.
Luo ensin uusi **Verkkodokumentti**. Verkkodokumentti-olio yhdistää
pyynnön, otsakkeet, HTML:n ja istunnon. Tämä johtuu siitä, että kun
vierailet verkkosivustolla selaimellasi, näet vain HTML:n. Mutta
koko Verkkodokumentti koostuu myös **otsakkeista**. Esimerkiksi
useimmat HTTP-vastaukset sisältävät otsakkeen, kuten Content-type:text/html,
joka kertoo selaimelle, että sitä seuraava data on esitettävä HTML:nä
(eikä esimerkiksi ladattava tiedostona). Istunnot ovat tapa
tallentaa käyttäjän tietoja pyyntöjen välillä. Näiden tietojen seuraamiseksi meidän on
asetettava eväste, ja myös tämä eväste asetetaan otsakkeen kautta. Siksi
kaikki kohtaa Verkkodokumentissa (koska se on koko
dokumentti, joka sisältää sekä otsakkeet että HTML:n tai muun datan).


```
# First we make a new Web Document instance
>> web := Verkkodokumentti uusi.

# Now we start a session, this will generate a Header for a cookie and
# create a file to store your data, associated with that cookie
>> session := web aloita-istunto.

# Now we can treat session like a dict
session userid: 123.
```

Istunnon tuhoaminen (uloskirjautumisen yhteydessä):

```
web tuhoa-istunto.
```

## Otsakkeet

Verkkodokumentilla voi asettaa myös muita tunnettuja otsakkeita.
Jos esimerkiksi haluat ohjata käyttäjän toiseen URL-osoitteeseen:

```
web siirry: ['/other.html'].
```

Konepellin alla tämä komento luo myös HTTP-otsakkeen, joka lähetetään
muun datan tai HTML:n mukana ja joka käskee selainta siirtymään
annettuun kohdeosoitteeseen.

Mukautetun otsakkeen lisääminen:

```
web otsake: ( 
	HTTP-Otsake uusi
	avain: ['Content-Length']
	arvo: 400
).
```

404-sivun näyttäminen:

```
web ei-löydy: ['OOps..'].
```


## Mallipohjat

Oletusmallipohjajärjestelmä on hyvin yksinkertainen. Sinun ei tarvitse opetella
uutta mallipohjasyntaksia. Lisäksi mallipohjamoottori takaa todellisen erottelun
esityksen ja liiketoimintalogiikan välillä.

Mallipohjan luominen tiedostosta:

```
>> tpl := web mallipohja: ['templates/ux.tpl'].
```

Mallipohjajärjestelmä käyttää merkkejä.
Merkkejä on kolmenlaisia: leikkausmerkkejä, liimausmerkkejä ja
paikkamerkkejä. Perusajatus on todella yksinkertainen: leikkaat
leikkausmerkeillä tunnistettuja alueita ja voit liimata niitä
liimausmerkeillä tunnistettuihin kohtiin. Paikkamerkkeihin voit
injektoida merkkijonoja.

Laitetaan esimerkiksi seuraavan mallipohjan avulla
jalokivi korurasiaan ja lisätään hintalappu.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Tämän voi tehdä seuraavasti:

```
>> gem := tpl leikkaa: ['gem'], kopioi.
gem price: 99.
tpl liimaa: gem kohtaan: ['jewels'].
web tulosta: tpl puhdista.
```

Viimeinen rivi yksinkertaisesti lähettää mallipohjan merkkijonona asiakkaalle
tarvittavien HTTP-otsakkeiden kanssa.

Tulos:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

Käyttäjien lataamia tiedostoja voi tarjota turvallisesti passthrun avulla:

```
>> uploaded := ['smile.gif'].
Server välitä: uploaded etuliite: ['/uploads/images/'].
Ohjelma lopeta.
```

Tämä tarjoaa käyttäjän lataaman sisällön asianmukaisella
MIME-tyypillä. Vain sallittujen luettelossa olevat MIME-tyypit ovat tuettuja:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF ja SVG.
SVG-, ZIP- ja GZIP-tiedostot lähetetään latauksena, koska SVG
voi sisältää skriptejä, jotka muuten suoritettaisiin verkkotunnuksessasi.
Tämä menetelmä estää TOCTOU-hyökkäykset, polun läpikäynnit,
haitallisen koodin suorittamisen (injektion), symbolisten linkkien hyökkäykset,
DDoS-hyökkäykset (tiedostoraja = 50 Mt), salakuunteluhyökkäykset ja
monet muut tietoturvaongelmat.


## JSON

Olion koodaaminen JSONiksi:

```
>> json := ( JSON jsonify: ( 
	Sanakirja uusi aseta: ( 
		Lista uusi ; 1 ; 2 ; 3
	) kohtaan: ['abc']
)).
```

JSONin purkaminen XOScript-olioksi:

```
>> dict := ((JSON olio: json) abc ? 1).
```

JSON, jossa on yli 500 sisäkkäisyystasoa, hylätään virheellisenä.

Sanakirjan tulostaminen suoraan JSONina oikeiden otsakkeiden kanssa:

```
web json: dict.
```


## Säännölliset lausekkeet

Säännöllisiä lausekkeita voi käyttää luomalla mallin.
Esimerkiksi hyperlinkkien href- ja target-arvojen etsiminen:

```
Malli uusi: ['href="([^"]+)" target="([^"]+)"'].
```

Sovella nyt mallia kohdemerkkijonoon näin:

```
pattern täsmää: aihe tee: { :m :x .... }
```

Täydellinen esimerkki:

```
>> aihe := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> pattern := Malli uusi: ['href="([^"]+)" target="([^"]+)"'].
>> result  := pattern täsmää: aihe tee: { :m :x
	Tuloste kirjoita: m, rivinvaihto.
	Tuloste kirjoita: x, rivinvaihto.
	<- ['XXX'].
}.
Tuloste kirjoita: result, rivinvaihto.
```

## Verkkoyhteydet

Verkkopyynnön voi tehdä Verkko-oliolla.
Verkko-olio lähettää aina POST-pyynnön, paitsi jos lähetät datana
Tyhjä, jolloin se lähettää GET-pyynnön.


```
Verkko 
post: Tyhjä 
kohteeseen: ['https://redbeanphp.com'].
```

## Salaus

Palvelinlaajennuksessa on XChaCha20- ja Argon2-pohjainen salaus.

Esimerkki:

```
>> encrypted := Holvi salaa: ['hello'] avain: ['world'].
>> decrypted := Holvi salaa: encrypted avain: ['world'].
```

## Tunnisteet

Tietyn pituisen kryptografisesti turvallisen tunnisteen luominen:

```
>> mytok := Holvi tunniste: 40.
```

Tämä luo 40 merkin pituisen tunnisteen.

## Muotoilu

Muoto-oliolla voi muotoilla dataa, esimerkiksi täyttää sitä välilyönneillä tai
lisätä nollia. Se käyttää printf-syntaksia.

```
>> fmt := Muoto uusi: ['%06.0f'].
fmt sovella: 56. # gives 000056
```

Muoto voi sisältää yhden muunnoksen, ja sen on sovittava arvoon,
muuten saat virheen:

- `sovella:` merkkijonon kanssa: `%s`
- `sovella:` luvun kanssa: `%f`, `%e`, `%g` tai `%a`
- `sovella-kokonaisluku:` luvun kanssa: `%d`, `%i`, `%o`, `%u`, `%x` tai `%c`

Pyynnön arvot ovat merkkijonoja. Jos haluat muotoilla sellaisen lukuna,
muunna se ensin:

```
fmt sovella: (pyyntö get: ['amount']) luku.
```

## Koodaimet

Saatavilla on useita koodaimia ja dekoodaimia.
URL-koodain valmistelee URL-osoitteen käytettäväksi HTML:ssä linkkinä:

```
Server url-koodaa: ['https://example.com?a=6&b=1 2'].
```

Jotta voit injektoida käyttäjän syötteen turvallisesti HTML:ään ilman
XSS-injektioiden vaaraa, käytä aina:

```
Server html-koodaa: ['<harmless>'].
```

Huomaa, että mallipohjamoottori tekee aina HTML-koodauksen,
kun kirjoitat paikkamerkkiin. Jos siis käytät mallipohjajärjestelmää,
tätä ei tarvitse käyttää.

## Sähköpostit

Sähköpostin lähettämiseen käytetään kirjastoa mailtools.xo.

Esimerkki:

```
Server valmistele.
Ohjelma käytä: ['mailtools.xo'].

>> e-mail := HTML-Sähköposti uusi.
>> img := e-mail liitä: ( Tiedosto uusi: ['myimage.png'] ).

e-mail
lähettäjä: ['xo@xoscript.com'] nimi: ['xo'],
vastaanottaja: ( Lista uusi ; ['xo2@xoscipt.com'] ),
aihe: ['xoxo'],
viestiteksti: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), lähetä.

```



## Linkittäminen

Viestillä linkitä: voit linkittää ulkoisen kirjaston
ohjelmaasi libffi:n avulla. Lisätietoja on ffi-luvussa.


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

FFI tarjotaan alusta- tai laajennuskohtaisesti, koska se
on sidoksissa taustalla olevaan järjestelmäarkkitehtuuriin, mitä
ytimen ei ole tarkoitus tehdä.
Palvelinlaajennus tarjoaa yhteensopivan ffi/blob-toteutuksen.
Oletuksena ydin on yhteydessä kohdealustaan
stdinin/stdoutin, rajoitettujen tiedosto-I/O-palvelujen ja komentotulkin (Ohjelma järjestelmä:) kautta.
Lisäintegraatiota tarjoavat ffi/blobit sovelluskeskeisten
laajennusten, kuten palvelinlaajennuksen, kautta.

FFI tulee sanoista Foreign Function Interface (vieraiden funktioiden rajapinta). Sen avulla voit käyttää muiden
muilla ohjelmointikielillä kirjoittamia toimintoja, joita tarjotaan DLL-, SO- tai Dylib-tiedostoina. Ne voivat
olla monenlaisia funktioita, ja tätä kautta on saatavilla valtava määrä toiminnallisuutta.
Aloitetaan esimerkillä:

```
Server linkitä: (
 Lista uusi ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Lista uusi ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s vapauta.
```

Tämän koodin tuloksena näet komentorivillä seuraavaa:
FFI has 3 letters.
Nyt luultavasti ajattelet: "Onpa paljon koodia jotain noin yksinkertaista varten."
Eikö tämän olisi voinut ratkaista Gui show -komennolla? Vastaus on painokas kyllä!
Tämä on kuitenkin tarkoitettu havainnollistavaksi esimerkiksi.
FFI:tä käytetään yleensä monimutkaisempiin tehtäviin, mutta niistä ei saa hyviä
esimerkkejä, joten valitsin jotain triviaalia.

linkitä-metodin argumentit:

- Argumentti 1: DLL- tai SO-tiedosto, jota haluat käyttää.
- Argumentti 2: Tiedoston funktio, jonka haluat linkittää.
- Argumentti 3: Lista funktion argumenttien tietotyyppien nimistä.
- Argumentti 4: Funktion paluutyypin nimi.
- Argumentti 5: Sen olion nimi, johon haluat linkittää tämän funktion (jos sitä ei ole olemassa, se luodaan
automaattisesti).
- Argumentti 6: Viesti, johon tämä funktio linkitetään.

Yllä olevassa esimerkissä haluamme linkittää printf-funktion kirjastosta libc.so. Tietotyyppien
nimet löydät linkitettävän ohjelmiston dokumentaatiosta. Käytettävissä olevat tyypit ovat:
void, pointer, float, double, int, uint, char, uchar, intX ja uintX,
missä X voi olla 8, 16, 32 tai 64.

Nämä tyypit viittaavat datan tallentamiseen tarvittavien tavujen määrään. Printf-funktion kohdalla linkitämme
uuteen olioon nimeltä Printf ja viestiin template:number:. Ulkoinen funktio
käännetään XOScript-murteelle ennen sen käyttöä. Viesti template:number: odottaa
ensimmäiseksi parametrikseen puskurin, joka sisältää mallipohjatekstin. Luomme tämän puskurin Blob-oliolla, jonka
avulla muistia voi varata käsin. Olet itse vastuussa tämän muistin vapauttamisesta jälkeenpäin
viestillä vapauta.

Muistiblobin voi täyttää monin tavoin. Esimerkissämme täytämme sen tekstillä, joten käytämme
viestiä utf8: (UTF-8 on koodaus, jolla teksti muunnetaan tavuiksi). Blobin voi täyttää myös
viestillä bytes: antamalla sille listan tavuarvoja. Blobin sisällön lukemiseen käytetään viestiä alkaen:pituus:.
Saat tavut takaisin listana. Blobilla voi jopa luoda C-structin
viestillä struct: antamalla sille sarjan C-tyyppejä. Tämä voi olla tarpeen, kun kutsutaan
ulkoisen ohjelmistokirjaston C-funktiota, joka odottaa osoitinta structiin.

{warning}
Blobit on vapautettava itse.
Roskienkerääjä ei tyhjennä blobeja.
{/warning}

Koska blobeja voidaan vaihtaa kirjastojen ulkoisten funktioiden kanssa,
roskienkerääjä ei voi kerätä niitä automaattisesti (ne saattavat olla yhä
ulkoisten funktioiden käytössä, tai nämä ulkoiset funktiot saattavat haluta vapauttaa ne
itse). Siksi blobit on tarvittaessa vapautettava itse.

Blobin vapauttaminen:

```
myblob vapauta.
```

Structin vapauttaminen:

```
mystruct vapauta-struct vapauta.
```

Structin kohdalla on siis lähetettävä kaksi viestiä, vapauta-struct ja vapauta,
muistilohkon vapauttamiseksi.

@api_Blob_fficonnect
