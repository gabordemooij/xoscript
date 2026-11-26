# Grunnatriði

{{messages}}


Velkomin í XOScript
Markmið XOScript-verkefnisins er að búa til forskriftarmál sem er einfalt og endurskoðanlegt.
Einfalt þýðir ekki endilega auðvelt.
Kunnuglegt forritunarmál getur verið auðveldara í notkun en XOScript.
Hér merkir einfaldleiki eitthvað annað:
að geta myndað sér heildstætt hugarlíkan af málinu og hegðun þess.

XOScript er hannað þannig að það rúmist í höfðinu á þér.
Málfræði þess og fjöldi hugtaka eru vísvitandi lítil.
Það eru engir klasar; hægt er að útvíkka hluti beint.
Hlutir eru sendir sem tilvísanir, afritun er gerð berum orðum
og föll hafa einn útgöngustað.

Sumar þessara ákvarðana eru verulega frábrugðnar algengum forritunarmálum.
XOScript hefur til dæmis ekkert tagakerfi og notar kvikt gildissvið.
Skilaboð sem ekki er hægt að meðhöndla eru hunsuð í stað þess að valda undantekningu.
Þessar ákvarðanir hafa afleiðingar og þeim er ekki ætlað að útrýma villum.
Þeim er ætlað að halda undirliggjandi líkani málsins litlu og samkvæmu.

Einnig er hægt að staðfæra XOScript, sem gerir kleift að orða viðskiptareglur
á náttúrulegu máli og jafnvel deila þeim með hagsmunaaðilum sem ekki eru tæknimenntaðir.

Endurskoðanleiki merkir að sömu hugmyndafræði er beitt á útfærsluna.
Keyrsluumhverfið er skrifað í C, með litlum handskrifuðum lesgreini, þáttara og trjágöngumanni.
Staðalsafnið og keyrsluumhverfið endurspegla að mestu uppbyggingu málsins,
sem gerir tengslin milli XOScript-kóða og útfærslu hans tiltölulega bein.

Prófanir eru einnig nátengdar handbókinni.
Hver aðferð ætti að hafa tilheyrandi prófun sem hægt er að fella inn í handbókina,
sem hjálpar til við að halda handbókinni í samræmi við útfærsluna.

XOScript er ekki ætlað að keppa við algeng forritunarmál hvað varðar
eiginleika eða kunnugleika. Það kannar annað markmið:
forritunarumhverfi sem forritari getur skilið í heild sinni.

Vonin er sú að lítið mál og lítil
útfærsla geri það raunhæft að skilja hugbúnað
frá bæti til hlutar, frá málskipan til keyrsluumhverfis, og að skrifa kóða af
öryggi vegna þess að þú skilur bæði hvað gerist í
forskriftinni og hvað gerist undir yfirborðinu.

Uppbygging xoscript-netþjónsuppsetningar
er einföld en sveigjanleg.

{{architecture.png}}

Til að nota xoscript sem netþjónsmál þarftu að setja upp
netþjónsviðbótina í möppu sem heitir /mods/server. 

Þetta er vegna þess að við viljum
aðskilja kjarna málsins frá virkni sem er sérhæfð fyrir netþjóna,
ólíkt til dæmis PHP eða Python. Annars þyrftum við að senda öllum
allt heila draslið að óþörfu, sem er einfaldlega kjánalegt.
Þú getur líka sett upp aðrar einingar ef þú vilt. Kerfið er mjög
sveigjanlegt.

Einnig eru sum föll betur útfærð í sjálfu forskriftarmálinu,
eins og sniðmát og setustjórnun, svo við sendum auk þess
með söfnin template.xo og webtools.xo þér til hægðarauka.
Ástæðan fyrir þessu öllu er sú að við vitum ekki hvernig þú vilt
nota xoscript. Þú getur notað það sem forskriftarmál á netþjóni,
en einnig fyrir myndræn notendaviðmót, ívafin tæki eða bara runuvinnslu.
Jafnvel þótt þú notir það sem forskriftarmál á netþjóni (sem er
sem stendur eitt helsta notkunartilvikið), gætirðu samt viljað
nota aðra sniðmátsvél eða annan setustjóra.
Hver erum við að ákveða að þú eigir að nota okkar?

Einn kosturinn við að nota okkar eigin sniðmátsvél er þó sá að
þú þarft ekki að læra viðbótarmálskipan til að búa til sniðmát.
Sjálfgefna sniðmátsvélin sem fylgir xoscript aðskilur framsetningu
og rökvísi að fullu. Í stað sérstakrar
sniðmátsmálskipanar notar hún einfaldlega mjög sveigjanlegt kerfi hólfamerkja.
Nánari upplýsingar er að finna í kaflanum um netþjóninn.

Athugaðu að ef þú vilt ekki nota sjálfgefnu sniðmátsvélina eða
sjálfgefnu vefverkfærin, segir það sig sjálft að þú þarft að útvega
þín eigin.

Ef þú keyrir vefþjóninn þinn í chroot, jail eða annars konar sandkassa,
þarftu einnig að setja upp þau söfn sem xo er háð í því umhverfi; þú getur
séð hvaða söfn þú þarft með því að nota ldd (sjá handbókarsíðu Linux eða BSD).
Ef þú vilt nota skeljarskipanir í xo-forskriftunum þínum skaltu einnig afrita skel
(eins og bash eða ksh) í þetta umhverfi.

Við viljum einnig taka fram að við tökum afturvirka samhæfni mjög alvarlega.
Það er meira að segja til sérstakur eiginleiki fyrir afturvirka samhæfni sem heitir
'version'. Almennt stefnum við að því að kóðinn þinn gangi að eilífu. Þú munt því
aldrei þurfa að uppfæra kóðann þinn til að hann haldist samhæfur nýrri útgáfum
af xoscript. Markmið okkar er: skrifaðu einu sinni, keyrðu að eilífu.

Afgangurinn af þessari handbók er helgaður ítarlegri útskýringu á forritunarmálinu
xoscript. Forskriftir á netþjóni eru ræddar í kaflanum
sem heitir Netþjónn. Ef þú ert reyndur hugbúnaðarforritari gætirðu viljað
sleppa nokkrum köflum, því sumir þeirra eru full ítarlegir eða
mjög líkir almennum forritunarvenjum. Þið sem
hafið þegar reynslu af nokkrum öðrum forritunarmálum
ættuð því frekar að nota þessa handbók sem uppflettirit.

## Uppsetning á Linux

Sæktu apache2 og mariadb:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Sæktu xoscript.
Skiptu X út fyrir rétt útgáfunúmer!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Afritaðu skrárnar í vefrótina og /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Breyttu apache2-stillingunum þínum:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Skiptu Virtualhost út fyrir:

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

Búðu til prófunarsíðu:

```
sudo nano /var/www/html/test.xo
```

og skrifaðu lítið prófunarforrit:

```
#!/bin/xo
Server frumstilla.
Forrit nota: ['webtools.xo'].
>> vefur := Vefskjal nýtt.
vefur skrifa-út: ['Hello World'].
```

Leyfðu apache2 að keyra forritið þitt í gegnum CGI:

```
sudo chmod uog+x /var/www/html/test.xo
```

Endurræstu apache2:

```
sudo systemctl restart apache2
```

Farðu á prófunarsíðuna þína í vafranum:

```
http://localhost/test.xo
```

Þú ættir að sjá:

```
Hello World
```


## Uppsetning á OpenBSD

Breyttu /etc/httpd.conf og bættu við:


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

Ef þú vilt nota SSL:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Til að verja lyklaskiptin gegn skammtatölvum
skaltu velja mlkem-dulmálið:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Bættu xo-keyrsluskránni og einingunum, ásamt öllum söfnum sem þau eru háð, við
chroot-umhverfið (finndu þau með ldd).

## Keyrsla dæma


Til að keyra eitt af dæmaforritunum í pakkanum:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Til dæmis, til að keyra FizzBuzz-dæmið á Linux:

```
./example.sh fizzbuzz Linux
```

Til að keyra sama dæmi á OpenBSD:

```
./example.sh fizzbuzz OBSD
```

Til að keyra dæmið með hreinni byggingu:

```
./example.sh fizzbuzz OBSD clean
```

## Einingaprófanir

Til að keyra einingaprófanirnar:

```
./runtests.sh
```

Til að keyra einingaprófanirnar án þess að byggja (aðeins prófa):

```
./runtests.sh nobuild
```

## Bygging

Til að byggja úr frumkóða á Linux:

```
make clean
ISO="en" make
```

Á OpenBSD:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

Til að byggja netþjónsviðbótina á Linux:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

Til að byggja netþjónsviðbótina á OpenBSD:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Halló heimur

Eftir að skráin hefur verið flutt yfir á tölvuna þína geturðu afþjappað hana
og ræst xo með eftirfarandi skipun:

```
xo
```

Til að keyra XOScript-forrit skaltu vista forritið sem skrá með -xo
viðskeytinu (valfrjálst). Settu auk þess skráarheiti forritsins
á eftir XOScript-skipuninni:

```
xo myprogram.xo
```

Þegar þú keyrir XOScript-skipun með forritsskrána þína sem
færibreytu les xo forritsskrána og keyrir hana.

{{note}}
Þú getur líka ræst forritið þitt með því að draga það á xo-táknmyndina.
{{/note}}

{{warning}}
Á sumum kerfum þarftu fyrst að veita xo heimild til að hlaða kvikum
söfnum.
{{/warning}}

Hefðin segir að fyrsta forritið í hverju nýju forritunarmáli
eigi að vera eins konar kveðja til heimsins. Í XOScript lítur slíkt
**Hello world** forrit svona út:

@test598

Þegar þessi texti hefur verið vistaður í skrá, t.d. hello.xo, er hægt að keyra hann
á eftirfarandi hátt: .

xo hello.xo

Hello world


Þú getur séð úttak forritsins í svarta glugganum hér að ofan.
Í allri þessari handbók verður sama framsetning notuð til að sýna
úttakið.

{{note}}
Úttak er skrifað með stórum staf.
Almennt byrja hlutir á stórum staf
nema þeir virki sem tilvik (hafa engar aðferðir
sjálfir, aðeins gögn). Þetta endurspeglar venjur um klasa og tilvik
í öðrum forritunarmálum.
{{/note}}


## Málskipan 

XOScript er *hreint* *hlutbundið* forritunarmál. Þetta þýðir
að xoscript lítur á allt sem hlut og því eru
engar aðrar *gagnagerðir*. Í grundvallaratriðum eru þrjár meginaðgerðir
í forriti sem skrifað er í XOScript: *gildisveiting*, *sending skilaboða*
og *svörun*. Skilaboðaskipti milli hluta eru kjarninn í
XOScript-forriti. Aðgerðirnar þrjár eru sýndar
hér að neðan:


Aðgerð                | Dæmi
--------------------- | --------
gildisveiting         |  \>\> x := 1. 
einundarskilaboð      | x slétt?.
tvíundarskilaboð      | 1 + 2.
lykilorðaskilaboð     | x frá: 0 lengd: 10.
svar                  | <- svar.  


Þessi kafli gefur þér almenna mynd af XOScript-málinu
og lýsir grundvallarreglum þess. XOScript er lítið mál,
byggt á þremur aðgerðum (sjá mynd) sem verða að
um það bil sex málfræðireglum. Það er allt sem þarf til að ná tökum á
málinu.

Engar áhyggjur þótt hlutirnir séu þér ekki strax ljósir: allir byggingar-
steinarnir verða skoðaðir í næsta kafla (3) og grunnreglurnar verða
endurteknar. Þessi kafli er hins vegar fyrst og fremst almenn
kynning á málinu. Grundvallarreglurnar verða útskýrðar stuttlega
og sýndar með nokkrum viðeigandi dæmum. Þau smáatriði sem vantar
verða útlistuð síðar.

Athugasemdir í XOScript byrja á \# tákninu. Eftirfarandi lína
verður því hunsuð:

```
# þetta er bara athugasemd
```

## Breytur

Til að gefa
breytu gildi notarðu yfirlýsingartákn breytu: >>. Nafn
breytu má innihalda öll tákn nema: <-, :=, bil,
punkta, kommur, tvípunkta, gæsalappir [' '] og sviga ().
Auk þess getur breyta ekki náð yfir margar línur. Athugaðu
að breyta getur ekki byrjað á tölustaf eða mínusmerki.

Þetta eru dæmi um gildar breytur:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dollari'].
>> +plus := Satt.
>> notanda-lykilorð := ['Pssst!'].
```

Ógildar breytur eru til dæmis:


```
>> -123 := ['neikvæð tala'].
>> password of notandi := ['Leynilegt'].
>> password.of:notandi := ['Leynilegt'].
>> ,x := 10.
```

{{note}}
Þú þarft ekki að lausnarita nein tákn
(þar á meðal gæsalappir, tvöfaldar gæsalappir eða
strengjamörk) í
strengjalesgildi svo lengi sem það veldur
ekki tvíræðni fyrir lesgreininn.
{{/note}}

Eftir að breyta hefur verið skilgreind má nota hana frjálst. Þetta þýðir
að aðeins þarf að nota yfirlýsingartáknið í fyrsta sinn sem
þú notar breytuna (yfirlýsingin).

Nánar tiltekið geturðu ekki bara byrjað að gefa
breytunni þinni gildi *(x := 2)*, því þú verður fyrst að lýsa breytunni yfir *(\>\>
x := 2)*. Þegar henni hefur verið lýst yfir máttu hins vegar breyta gildi hennar
án þess að nota yfirlýsingartáknið*(\>\> x := 2. x := 3.)*.

Athugaðu að skylt er að gefa breytu gildi um leið og
henni er lýst yfir. Ólíkt öðrum forritunarmálum er ekki leyfilegt
að lýsa yfir breytu án gildis. Nauðsynlegt er að tengja
hverja breytu berum orðum við upphafsgildi. Þér er þó frjálst að frumstilla
breytuna með **Ekkert** hlutnum. Í því tilviki má
líta á breytuna sem tóma *(\>\> x := None.)*. Í stuttu máli er ekki leyfilegt að lýsa yfir
breytu án upphafsgildis. Þannig er

```
>> x.
```

ógilt og mun gefa villuboð.

{{note}}
xoscript notar kvikt gildissvið breyta; nánari
upplýsingar er að finna í kaflanum Föll.
{{/note}}


## Lesgildi

XOScript lítur á allt sem hlut, þ.e. allar tölur, strengi
og kóðabúta. Tölur eins og 1, 2, 100, -999 og 1,234 eru
Tala-hlutir. Allir textar milli einfaldra gæsalappa eru Texti-hlutir.
Allir kóðabútar sem eru flokkaðir saman innan slaufusviga {...} eru
Fall-hlutir.

Lesgildi        | Rótarhlutur  | Dæmi
--------------- | ------------ | ----------
tölur           | Tala         | 1,2,3... 
strengir        | Texti        | \['hello'\]
fall            | Fall         | { 1 + 2. }.
                
     
Hlutir eins og tölur og strengir eiga alltaf uppruna sinn í
rótarhlut. Til dæmis eru allar tölur leiddar af hlutnum **Tala**. Allir
strengir eru leiddir af **Texti** og allir kóðabútar af **Fall**. Allir
þessir hlutir eru síðan komnir af **Hlutur**, sem er í raun
rótarhlutur allra hluta.


## Skilaboð

Að forrita í XOScript þýðir í grunninn að
senda hlutum skilaboð. Almennur ritháttur til að senda
hlut skilaboð er eftirfarandi:

```
<object> <message>
```

Til að komast að því hvort talan **2** sé til dæmis slétt tala eru
skilaboðin **slétt?** send hlutnum **2**:

```
2 slétt?
```

Svarið verður **Satt** (aftur hlutur). Hlutir hunsa
yfirleitt óþekkt skilaboð, svo engin villa kemur upp. Sumir hlutir (t.d.
tölur eða strengir) bregðast við óþekktum skilaboðum á fyrirfram skilgreindan hátt
(meira um það síðar).

Hlutur getur tekið við þrenns konar skilaboðum. 

Gerð                  | Fjöldi viðfanga
--------------------- | -------------------
Einundar              | 0      
Tvíundar              | 1     
Lykilorða             | 1+    


Í fyrsta lagi eru til **einundar-
skilaboð**, sjá dæmið hér að ofan, sem eru án viðfanga. Í öðru lagi
eru til **lykilorðaskilaboð**, sem hafa eitt eða fleiri viðföng,
til dæmis:

```
>> x := Tala milli: 1 og: 10.
```

Í þessu tilviki eru skilaboðin **milli:og:** send hlutnum **Tala**, sem
er rótarhlutur allra talna. Niðurstaðan verður slembitala
milli 1 og 10. Að lokum eru til **tvíundarskilaboð**, sem hafa
aðeins eitt tákn og eitt viðfang:

```
2 + 3
```

Þetta lítur út eins og stærðfræðileg samlagning, en er í raun bara önnur skilaboð.
Skilaboðin **+** eru send hlutnum **2** með viðfanginu **3**, sem skilar
svarinu **5**. Tvíundarskilaboð má skrifa án tvípunkts.

Hægt er að hlekkja tvíundarskilaboð saman:

```
>> x := 3 + 2 - 1.
```

Í þessum bút er **+ 2** fyrst sent **Tala**-hlutnum **3**, sem
gefur Tala-hlutinn **5**, og síðan er **-1** sent þessari
tölu. Glöggir lesendur taka réttilega eftir því misræmi sem
þessi samskiptaregla sýnir gagnvart hefðbundinni stærðfræðilegri forgangsröð
virkja. XOScript hunsar stærðfræðilegu forgangsröðina í þágu
samræmis í skilaboðakerfi sínu. Þar af leiðandi gefur summan:

```
2 + 3 * 5 = 25
```

ekki 17.

Þetta er gert af ásettu ráði. Nota má sviga til að breyta röðinni:

```
2 + (3 * 5) = 17
```

Flestir hlutir skila sjálfum sér sem niðurstöðu við tilteknum
skilaboðum. Þetta er gagnlegt því það hvetur til frekari samskipta við þennan
hlut með því að senda honum framhaldsskilaboð:

```
Úttak skrifa:
[' halló '] snyrta hástafir.
```

```
HALLó
```

Hér eru tvenn skilaboð send **Texti**-hlutnum: **snyrta** og síðan
**hástafir**.

Í eftirfarandi bút er nauðsynlegt að nota kommu til að gefa til kynna
að ný skilaboð séu á leiðinni. Annars ruglast XOScript.

```
Úttak skrifa: ['Hello!'], ný-lína.
```

Fyrst eru skilaboðin **skrifa:** send blýantstákninu og síðan
**ný-lína**. Án kommunnar myndi XOScript halda að þú vildir senda
**ný-lína** til **texti** **Hello!**, sem væri tilgangslaust.

Skilaboð eru unnin í eftirfarandi röð: frá vinstri til hægri;
fyrst skilaboð innan sviga, síðan einundarskilaboð. Því næst
tvíundarskilaboð og að lokum lykilorðaskilaboð. Sjá dæmið
hér að neðan:

```
Úttak skrifa: 0.5 námunda + (2 - 1), ný-lína.
```

XOScript les alltaf frá vinstri til hægri: fyrst eru skilaboðin **skrifa:**
send Úttak og síðan skilaboðin **ný-lína**. Innan
viðfangsins sjálfs les XOScript frá vinstri til hægri, svo fyrst **0.5 námunda**
og síðan **+**.

{{note}}
Skilaboðin ný-lína bæta línuskilatákni við strenginn.
Upprunalegt heiti þessara skilaboða (stop) er innblásið af ritsímakerfum.
Í skeytum ritsímakerfa
var orðið STOP oft notað til að marka lok setningar
(þar sem greinarmerki voru óáreiðanleg eða kostnaðarsöm).
{{/note}}

Auk þess hefur **námunda** forgang fram yfir **+**, því það eru
**einundarskilaboð**. Vegna svigans er **2 - 1** reiknað
fyrst, og síðan er **1** bætt við niðurstöðu **0.5 námunda** (1).

Allt ferlið gefur niðurstöðuna **2**, sem er einnig svarið sem
skrifað er út. Á eftir kommunni koma skilaboðin ný-lína, sem færa bendilinn
í nýja línu. Besta leiðin til að skilja til fulls röð
XOScript-forrita er auðvitað með æfingu.

Vert er að taka fram að í XOScript, ólíkt mörgum öðrum forritunarmálum,
eru bil grundvallarhluti málskipanarinnar. Einkum
hvað varðar tvíundarskilaboð geta bil valdið nokkrum
ruglingi. Notaðu alltaf bil á eftir tvíundarskilaboðum. Þú getur ekki
fest tölu beint við skilaboðin, til dæmis er

```
3 + 2
```

frábrugðið

```
3 +2
```

Fyrra dæmið (**3 + 2**) sendir
skilaboðin **+** til tölunnar **3** með töluna **2** sem viðfang.
Niðurstaðan verður í þessu tilviki **5**. Í seinna dæminu (**3 +2**)
eru einundarskilaboðin **+2** send tölunni **3**. Eftir
samhengi getur það gefið allt aðra niðurstöðu.

## Aðferðir sem ekki eru til

Þegar skilaboð eru send hlut er kallað á fallið sem hefur verið
tengt þessum hlut undir heiti skilaboðanna. Ef þú sendir skilaboð
sem ekki skiljast mun móttökuhluturinn hunsa skilaboðin þín
og skila í staðinn tilvísun í sjálfan sig til frekari samskipta.
Þetta kallast umburðarlynd skilaboðasending.

Dæmi:

```
Úttak skrifa: Hlutur blah, ný-lína.
```

Þetta gefur enga villu. Það prentar einfaldlega textann **Object**.


## Stýriflæði

Í XOScript er engin þörf á sérstökum málfræðireglum fyrir *lykkjur* og
*ef-setningar*. Ef-setning er einfaldlega **satt:** eða **rangt:** skilaboð
til annaðhvort **Satt** hlutar eða **Rangt** hlutar:

```
2 slétt? satt: {
	Úttak skrifa: ['Tveir er slétt tala'], ný-lína.
}.
```
Í dæminu hér að framan eru skilaboðin **satt:** send til **Satt** (svarsins
við spurningunni: er 2 slétt tala?). Sem viðfang er sendur með
viðbótarkóðabútur: **Fall**-hlutur. Þetta fall skrifar á
skjáinn að 2 sé í raun slétt tala.

Ekki er heldur þörf á sérstökum ritreglum fyrir *lykkju*. Til að
keyra kóðabút þrisvar sinnum skaltu einfaldlega senda **\*** með viðfanginu
**3** til þess **Fall**s:

@test5

Í þessum kóðabút er **i** vísirinn. Í fyrsta sinn sem fallið
er keyrt er **i** jafnt 0, í næsta sinn er **i** = 1 og
svo framvegis.

Skoðum annað dæmi. Þegar prenta þarf umreikningstöflu
úr *kJ* (kílójúlum) í *kcal* (kílókaloríur) í skrefum upp á 100,
er réttur ritháttur sýndur hér að neðan:

@test599

Hér er númer núverandi línu sent til færibreytunnar
**:line**. Í upphafi falls eru færibreytur fallsins
skilgreindar. Ónotaðar færibreytur eru tómar (**Ekkert**). Færibreytur eru
alltaf settar í upphaf fallsins, beint á eftir fyrsta
slaufusviganum, og á undan þeim kemur tvípunktur.

Skilaboðin **meðan:** eru sambland af *lykkju* og *skilyrði*.
Tengja má tvö föll saman með skilaboðunum **meðan:**. Móttökufallið
heldur áfram að keyra þar til fallið á eftir tvípunktinum gefur neikvæða
niðurstöðu. Dæmi:

@test600

Í kóðabútnum hér að ofan er **1** bætt við **x** svo lengi sem
**x** er minna en **5**. Þegar það á ekki lengur við svarar seinna
fallið með **Rangt** og þar af leiðandi lýkur keyrslu
fyrra fallsins. Athugaðu að **x** hefur verið skilgreint utan
fallsins og er víðvær breyta. Til að fræðast meira um gildissviðsreglur
skaltu lesa kaflann um föll.

## Strengjainnskot

Gera mætti *kJ/kcal*-listann
snyrtilegri. Helst ætti listinn að líta svona út:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Þegar æskilega úttakinu er breytt í sniðmát gæti ritháttur þess
verið:

```
number1 kJ ➞ number2 kcal
```

Þetta þýðir að **number1** stendur fyrir kJ-gildið og **number2** fyrir
kcal-gildið. Svona virkar strengjainnskot í XOScript. Engar
sérstakar málfræðireglur þarf til þess í XOScript. Sendu einfaldlega
orðið sem á að skipta út til textans með staðgengilstextann
sem viðfang:

```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

Niðurstaðan:

```
100 kj ➞ 23.9 kcal
```

Þessi útskiptiregla virkar fyrir öll óskilgreind skilaboð sem
**texti** hlutur tekur við. Öll skilaboð sem **texti** hluturinn
þekkir ekki eru túlkuð á eftirfarandi hátt: *skiptu texta skilaboðanna
út fyrir textann í viðfangi skilaboðanna.* Þú getur aðlagað
forritið á eftirfarandi hátt:


@test601


Til að forðast rugling um hvaða skilaboð má eða má ekki nota sem
staðgengil er best að taka upp sniðmátsmerki eins og &lt; &gt;
fyrir þá textahluta í sniðmátinu sem
þarf að skipta út.

## Skilagildi

Til að svara skilaboðum er skilaörin
(*<-*) notuð. Eftirfarandi dæmi sýnir hvernig búa má til verk
sem reiknar prósentu:

@test602

Eftir að verkið hefur verið skilgreint og því gefið breytunni **percentage**
eru skilaboðin **beita:og:** send með viðföngunum **100** og **7**.

Þetta keyrir verkið með **100** og **7**, þ.e. 7% af 100.
Með skilaörinni er svarinu skilað úr verkinu aftur
til aðalforritsins.

## Útvíkkun

Þótt þessi kóði sé gildur hefur hann þann ókost
að muna þarf röð viðfanganna. Hvers vegna ekki
að skrifa þetta svona: *7 percent of: 100 *? Það liti mun
*eðlilegar* út. Til að gera þetta mögulegt þurfum við að aðlaga yfirhlut
**7**, sem er **Tala** hluturinn, þannig að hann skilji
skilaboðin **percent of:**. Það má gera með því að senda **við:gera:** til
Tala-hlutarins, á þennan hátt:

@test603

Þar sem prósentan er í þessu tilviki talan sjálf vísum við til sjálfs sín,
lykilorðsins *sjálfur*. Í stuttu máli merkir táknið sjálfur: *sendu þessi
skilaboð til mín sjálfs*.

# Hlutir

{{messages}}

Auk þess að aðlaga og útvíkka hluti sem fyrir eru geturðu líka búið til
nýja hluti sjálf(ur) einfaldlega með því að senda skilaboðin **nýtt**. Segjum að þú
viljir búa til reikningshlut sem framfylgir númeraröð;
í því tilviki þarftu fyrst reikningshlut.

Þar sem hver hlutur er leiddur af öðrum hlut, sem aftur á móti
á endanum á uppruna sinn í rótarhlut allra hluta sem heitir Hlutur,
þarf að velja á hverjum þessara hluta
nýi hluturinn þinn á að byggjast. Nýi hluturinn erfir alla eiginleika
hlutarins sem hann byggist á, þ.e. þess sem **nýtt** skilaboðin
voru upphaflega send.

Í þessu dæmi er fremur hlutlaus hlutur æskilegur, hlutur án of
margra erfðra eiginleika. Þá er valið auðvelt, því í því
tilviki má byggja nýja hlutinn á sjálfum rótarhlutnum, sem er
**Hlutur**. Ritháttur fyrirhugaða reikningakerfisins verður þá
eftirfarandi:

@test604

Núverandi reikningsnúmer er geymt í hlutnum og þess vegna er
lykilorðið **eigin** sett framan við það. Þetta kallast *eiginleiki*;
nánar um það síðar.

Sum fyrirtæki vilja hafa ártalið með í reikningsnúmerunum.
Í því tilviki geturðu búið til nýjan reikningshlut byggðan á
fyrri reikningshlut, en sem gefur notanda sínum kost á að
slá inn tiltekið ár:

@test605

Engin þörf er á að skrifa útfærsluna fyrir skilaboðin **tala**
aftur, því hún erfist frá **reikningshlutnum** sem áður var
skrifaður; þannig má endurnýta gamlan kóða. XOScript skortir hugtök
eins og klasa og önnur skyld hugtök. Þetta þýðir að hlutir geta
eingöngu erft frá öðrum hlutum, sem einnig er kallað *frumgerðar-
erfðir*.

Snúum okkur nú aftur að eiginleikum. Aðeins er hægt að nálgast eiginleika hlutar
*innan hlutastigveldisins*, svo aðrir hlutir
geta ekki séð þessa eiginleika.

Ólíkt öðrum forritunarmálum eru allir eiginleikar hluta
eingöngu sýnilegir hlutnum sem bjó til eiginleikann og
afleiddum hlutum. 

Algeng aðferð er að nota hlut sem eins konar *teikningu*,
eins og til dæmis á við um reikningana sem fjallað var um áðan.
Annað gott dæmi er **Point**. Segjum að þú búir til
tölvuforrit sem reiknar út frá punktum á korti. Þú
getur þróað hlutinn **Point** sem inniheldur eiginleikana
x-hnit og y-hnit, sem gerðir eru aðgengilegir
umheiminum með skilaboðum:

@test606

Skilaboðin **=** bera punktana tvo saman með skilaboðunum **og:**. Fyrri
samanburðurinn gefur **Satt** eða **Rangt**. Þetta eru rökgildis-
hlutir. Þegar þú sendir skilaboðin **og:** til Satt-hlutar og
viðfangshluturinn á eftir tvípunktinum er einnig **Satt**, færðu
aftur svarið **Satt**. Þegar annar hvor er **Rangt** færðu
svarið **Rangt**. Athugaðu að einn punktur getur ekki lesið hnit
hins. Nauðsynlegt er að senda hinum punktinum skilaboð til að biðja
um þessi gögn: **x-coordinate** og **y-coordinate**. Eins og þegar hefur
verið útskýrt er jú aðeins hægt að sækja eiginleika innan
sjálfrar hlutafjölskyldunnar. 

Athugaðu að skilaboðin **=** eru hér notuð til að framkvæma samanburð
punktanna. Eins hefði mátt nota önnur skilaboð, eins og:
**is:** eða **equal:**, en það þótti viðeigandi að endurnýta **=** táknið
í þessu tilviki.

## Erfðir

Þú getur endurnýtt kóða sem áður hefur verið skrifaður til að búa til stigveldi
hluta. Til dæmis:

```
>> Dýr := Hlutur nýtt.
>> Hundur := Dýr nýtt.
>> Púðluhundur := Hundur nýtt.
```

Í þessu tilviki erfir **Dog** alla hegðun og alla eiginleika
**Animal** og hluturinn **Animal** erfir síðan alla hegðun
**Hlutur**, rótarhlutar allra hluta.


## Yfirskrift


Í eftirfarandi dæmi er búin til ný tegund lista:
**Combination**, þar sem tryggt er að hvert stak sé einstakt.
Föll listans eru endurnýtt með erfðum:

@test607

Taktu eftir því hvernig seinna **red** er útilokað frá listanum.

Stundum getur verið nauðsynlegt að yfirskrifa hegðun hlutar.
Til dæmis þegar tölur eru lagðar saman og taka þarf tillit til
mælieininga. Í eftirfarandi dæmi er hluturinn **Size**
búinn til. Þessi hlutur skilar tölu sem við samlagningu tekur
tillit til einingar tölunnar sem bæta á við. **Tala**-hluturinn
athugar hvort um *tommur* eða *fet* er að ræða. Kóðinn
gæti litið svona út:

@test608

## Endurkvæmni

Í dæminu hér að framan er plús**merkið** yfirskrifað. Athugaðu
að á endanum þarf samt að framkvæma lokasamlagninguna, sem í raun
fer fram í eftirfarandi línu:

```
>> svarið := sjálfur + (tala x stuðull).
```

Hvernig skilur XOScript þá að þetta plús**merki** vísar til
upprunalegrar samlagningarrökvísi?** Önnur túlkun gæti til dæmis
verið sú að XOScript sendi endurtekið sömu skilaboð til sama
hlutar, sem aftur myndi leiða til **endalausrar lykkju**. Það er
augljóslega ekki ætlunin. Um leið og þú sendir hlut skilaboð
sem myndu keyra nákvæmlega sama kóða áttar XOScript sig á
því að í þessu tilviki er átt við undirliggjandi, yfirskrifuðu skilaboðin. Forritið
þitt er því sjálfkrafa varið gegn endalausum lykkjum af þessu tagi.
Ef það er hins vegar í raun ætlun þín að keyra sama fall úr
núverandi falli þarftu fyrst að senda skilaboðin
**endurkvæmt**. Í því tilviki verður niðurstaðan endalaus
lykkja. Endurkvæm verk eiga sér þó gagnleg not; segjum til
dæmis að þú viljir reikna aðfeldi (hrópmerkt gildi) gefinnar
tölu. Þá bætirðu einfaldlega skilaboðunum **factorial** við
Tala:

@test609

Þetta kallar á endurkvæmni. Verkið sem tengt er
skilaboðunum **factorial** þarf í raun að keyra aftur innan þess falls.
Það er því nauðsynlegt að kalla á aðfeldisfallið innan úr
sjálfu aðfeldisfallinu. Að jafnaði kemur XOScript í veg fyrir þetta,
vegna hættunnar á að lenda í endalausri lykkju. Af þeim sökum
er nauðsynlegt að setja orðið **endurkvæmt** á undan skilaboðunum. Þetta
er gert til að láta XOScript vita að það sé
ætlun þín að keyra sama verkið og að þú hafir ekki gert mistök.

## Klasalíkir hlutir

Þótt xoscript bjóði ekki upp á klasa er auðvelt að líkja eftir
klasalíkri hegðun. Yfirskrifaðu einfaldlega nýtt-skilaboðin.

```
>> Dýr := Hlutur nýtt.
Dýr við: ['nýtt'] gera: {
	<- sjálfur nýtt frumstilla.
}.

Dýr við: ['frumstilla'] gera: {
	eigin hljóð := ['?'].
	eigin fætur  := 4.
}.
```

Í kóðabútnum hér að ofan búum við til hlut sem heitir Animal.
Þessi hlutur er *teikning* fyrir alls kyns dýr,
eins og hunda og ketti. Yfirhluturinn Animal er skrifaður
með stóru A til að gefa til kynna að þetta sé klasalíkur hlutur.
Næst yfirskrifum við nýtt-skilaboðin með því að skrifa okkar eigin nýtt-aðferð.
Í þessu tilviki sendir hún skilaboðin nýtt til sjálfur og síðan skilaboðin
frumstilla. Þar sem xoscript lokar sjálfgefið fyrir endurkvæmni veldur þetta ekki
endalausri lykkju. Þess í stað sendir það nýtt-skilaboðin til yfirhlutarins
(Hlutur), sem gefur nýtt tilvik af Animal. Við búum því til
nýjan hlut, byggðan á sama hlut og við bjuggum nýtt-aðferðina til fyrir.
Þetta er fullkomlega gilt. Nú sendum við líka skilaboðin frumstilla, sem tryggja
að Animal-hluturinn hafi sjálfgefin gildi fyrir eiginleika sína. Sjálfgefið
hefur dýr 4 fætur og hljóðið er óþekkt (þess vegna spurningarmerkið).
Til að búa til nýtt tilvik af Animal gætum við einfaldlega sagt:

```
>> a := Dýr nýtt.
```

Nú fáum við nýtt tilvik af Animal með 4 fætur, óþekkt hljóð og
frumstilla-aðferð. Rétt eins og í öðrum hlutbundnum málum getum við líka
útvíkkað Animal:

```
>> Hundur := Dýr nýtt.
Hundur við: ['frumstilla'] gera: {
	sjálfur frumstilla.
	eigin hljóð := ['geltir'].
}.
```

Við getum auðveldlega prófað þetta með því að bæta við texti-aðferð:

```
Dýr við: ['texti'] gera: {
	<- eigin fætur texti + eigin hljóð.
}.
```

Setjum þetta allt saman:

@test13


Það er algengt viðfangsefni að búa til hlut sem er settur í tiltekið
upphafsástand. Segjum að búa þurfi til hlutinn **Rectangle**
til að reikna ummál og flatarmál. Mögulegur ritháttur væri:


```
>> Rétthyrningur := Hlutur nýtt.

Rétthyrningur við: ['flatarmál'] gera: {
	<- eigin lengd * eigin breidd.
}.
```

Augljóslega er forsenda að lengd og breidd séu stillt. Í
þeim tilgangi má bæta við skilaboðunum **length:** og **width:**:


```
Rétthyrningur við: ['length:'] gera: { :lengd
	eigin lengd := lengd.
}.

Rétthyrningur við: ['width:'] gera: { :breidd
	eigin breidd := breidd.
}.

```

Þennan rétthyrning má síðan nota á eftirfarandi hátt:


```
>> rétthyrningur := Rétthyrningur nýtt length: 2, width: 3.
Úttak skrifa: rétthyrningur flatarmál.
```

Ef hins vegar gleymist að stilla upphafsgildi lengdar og breiddar
koma upp villuboð:

```
>> rétthyrningur := Rétthyrningur nýtt.
Úttak skrifa: rétthyrningur flatarmál.
```

gefur eftirfarandi villu:

```
Lykill fannst ekki:lengd
```

Til að koma í veg fyrir þetta er æskilegt að rétthyrningur hafi
alltaf upphafslengd og -breidd, til dæmis 0. Í þessu
tilviki er því nauðsynlegt að **yfirskrifa** skilaboðin **nýtt**.

@test610

Ef við yfirskrifum nýtt-skilaboðin erum við í raun að líkja eftir **klasa**.

Heimur XOScript er fullur af margvíslegum hlutum, sem eru
aðgengilegir forritinu þínu frá upphafi. Í næstu köflum
verður fjallað um alla þessa kjarnahluti.

## Skyndimyndir

Þú getur vistað hlut (ásamt núverandi ástandi hans) á disk með:

```
minnHlutur save-as: ['saved.bin'].
```

Til að hlaða hlutnum aftur af diski:

```
>> minnHlutur := Hlutur load-from: ['saved.bin'].
```

Nota má skyndimyndir til að vista tiltekið ástand eða til að bæta afköst.
Þegar skyndimynd er hlaðið sleppur maður við lesgreiningu, þáttun og uppsetningu forritsins.
Einnig gætu í framtíðinni bæst við frekari afkastakostir
skyndimynda, eins og bestun tiltekinna mynstra eða greining og
bestun heitra slóða.

{{warning}}
Skyndimyndir eru tilraunaeiginleiki; notaðu þær ekki í raunkeyrslu.
Til að virkja tilraunaeiginleika skaltu þýða með -D EXPERIMENTS.
{{/warning}}


@test712

# Hluturinn Ekkert

{{messages}}

Hluturinn Ekkert
táknar tómleika, eða öllu heldur skort á upplýsingum. Stöku
sinnum færðu þennan hlut sem svar við skilaboðum, þegar
niðurstaðan er **ekki neitt**. Mikilvægasta spurningin sem
þú getur spurt **Ekkert** hlutinn er: **Ekkert?**.
Svarið verður alltaf **Satt**.

```
Úttak skrifa: Ekkert Ekkert?.
```

niðurstaða:

```
Satt
```

Allir aðrir hlutir en **Ekkert** svara með **Rangt**. Kóðabúturinn
hér að ofan kann að virðast nokkuð heimspekilegur, en **Ekkert**
hluturinn hefur sannarlega afar hagnýt not. Til dæmis
færðu Ekkert-hlutinn sem svar ef þú biður um
stak í lista sem er ekki til. Þú getur líka notað Ekkert-hlutinn
ef þú vilt lýsa yfir breytu en vilt ekki tilgreina gildi
strax. Í staðinn **gefurðu** henni einfaldlega sérstaka gildið **Ekkert**. Í
XOScript er ekki leyfilegt að lýsa yfir breytu án gildis, eins og:


```
>> gildið.
```

Í staðinn þarftu að skrifa eftirfarandi:

```
>> gildið := Ekkert.
```

@api_None_base

# Rökgildi

{{messages}}

Ólíkt flestum vinsælum forritunarmálum þegar þetta er skrifað
býður XOScript aðeins upp á einn einasta Satt-hlut og einn einasta Rangt-hlut.
Til skýringar: í hvert sinn sem þú skrifar **Satt** þýðir það ekki að
nýr hlutur hafi verið búinn til. Þess í stað notarðu alltaf tilvísun. Þetta
þýðir að þegar þú skrifar eftirfarandi:

\>\> x := Satt.

vísar **x** til **Satt** hlutarins. Skilyrtur kóði og lykkjur
athuga einnig þessa tilvísun. Í XOScript er merking **Satt** og **Rangt**
ekki föst. Raunar fer XOScript-forrit talsvert úr skorðum við
setningu eins og þessa:

Satt := Rangt.

Niðurstaða slíkra aðgerða er óskilgreind, en þetta er engu að síður gild
aðgerð og því formlega leyfileg. Enn fremur er til Rökgildi-hlutur,
sem er rótarhlutur bæði **Satt** og **Rangt**, þar sem báðir
eru leiddir af rótarhlutnum. Rökgildi-hluturinn sjálfur hefur þó
engin hagnýt not.

## Gildrur

Farðu varlega í notkun **og:** og **eða:**

```
Úttak skrifa: (Rangt or: Satt or: Satt), ný-lína.
Úttak skrifa: (Rangt eða: Satt, eða: Satt), ný-lína.
```

Gefur

```
Rangt
Satt
```
vegna þess að skilaboðin **eða:** taka aðeins 1 viðfang. Fyrri skilaboðin
senda **eða:eða:** til Rangt, sem eru ekki til, svo hluturinn hunsar
skilaboðin og skilar sjálfum sér (Rangt). Seinni línan sendir hins vegar
**eða:** og síðan önnur **eða:** (með hlekkjunartákni, þ.e. kommu: ,).


@api_Boolean_base

# Tölur

{{messages}}

Í hvert sinn sem þú skrifar tölu, til dæmis 9, -10 eða 3,12, breytir
XOScript þessum tölum á bak við tjöldin í **Tala** hlut. Þú
getur sent þessum Tala-hlut skilaboð, eða þú getur gefið breytu töluna
sem gildi og sent skilaboðin síðan:

```
10 slétt?

>> tíkall := 10.
tíkall slétt?

```

Báðir rithættir eru gildir. Tala-hluturinn svarar eftirfarandi
skilaboðum...

Flest þessara skilaboða skýra sig sjálf og gera þér kleift að framkvæma
stærðfræðilegar aðgerðir eða samanburð.

{{note}}
Athugaðu að þú mátt nota ≤ ≥ ≠ × og ÷ í stað ASCII-hliðstæðna þeirra.
Það er smekksatriði.
{{/note}}

Munurinn á tvíundarskilaboðum í stærðfræði (+) og
lykilorðaafbrigðum þeirra (leggja-við:) er sá að hin fyrrnefndu skila
nýrri tölu, sem er niðurstaða aðgerðarinnar, en með
hinum síðarnefndu er hlutnum sjálfum breytt. Þetta er sýnt í
eftirfarandi dæmi:

@test597

Í dæminu hér að ofan er b = 4 og a = 3. Með **leggja-við: 2** er gildi
a hækkað um 2, en **+ 3** býr til nýja tölu sem er
jöfn a + 3. Sama gildir um aðrar stærðfræðilegar aðgerðir, t.d.
margföldun. Með margföldunartákninu færðu
nýjan hlut sem svar. Ef þú notar skilaboðin **margfalda-með:**
margfaldarðu töluna sjálfa.

Með skilaboðunum **milli:og:**, til dæmis í: **Tala
milli: X og: Y**, færðu tölu milli X og Y. Á þennan
hátt má búa til hvaða slembitölu sem er:

```
>> a := Tala milli: 1 og: 10.
Úttak skrifa: a, ný-lína.
```

Frá og með útgáfu 1.4 er innbyggður slembitölugjafi xoscript
dulmálsfræðilega öruggur, eftir því sem við best vitum.

Þú getur tengt **tilgreining** við tölu, til dæmis **6
epli**. Öll skilaboð sem tala þekkir ekki
eru talin tilgreining. Þú getur sótt tilgreiningu
tölu með skilaboðunum tilgreining:

Tilgreining er í grunninn Texti-hlutur sem er geymdur með Tala-
hlutnum. Tilgreiningin er einnig prentuð á eftir tölunni við
**skrifa:** úttak. Nota mætti tilgreiningar til dæmis til að leggja saman upphæðir
í blönduðum gjaldmiðlum. Þegar upphæðirnar eru lagðar saman geturðu beðið
um tilgreiningarnar. Eftirfarandi forritsdæmi sýnir þessa
reglu með sögulegri gjaldmiðlareiknivél (þar sem gengið
helst nokkuð stöðugt!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Strengir

{{messages}}

Í hvert sinn sem texti er settur milli **hornklofa og gæsalappa** ['...']
býr XOScript til nýjan strenghlut fyrir þig. Gættu þess þó
að nota réttar gæsalappir. Gæsalappirnar í
upphafi textans eru frábrugðnar þeim í lokin (þannig geturðu
notað einfalda úrfellingarkommu án þess að þurfa að lausnarita hana).

## UTF8

Strengir í xoscript innihalda yfirleitt utf8-kóðaðan texta. Þótt
tæknilega sé hægt að hafa tvíundar- eða annað en utf8-efni í
streng er mælt með því að nota blob fyrir slíkt. Blob eru
veitt af netþjónsviðbótinni (sjá kaflann ffi).
Almennt eru blob/ffi veitt
fyrir hverja viðbót/verkvang, þar sem þau tengjast verkvanginum
og högunni (ffi/blob). Kjarni forskriftarmálsins reynir að
vera eins óháður verkvangi og mögulegt er.

## Gerðarbreyting

Þú getur búið til afrit af hverjum hlut
af annarri gerð með eftirfarandi skilaboðum:

Skilaboð  | Niðurstaða
--------- | ------
tala      | Breytir í tölu
texti     | Breytir í streng
rökgildi  | Breytir í rökgildi
  
Eftirfarandi reglur **gilda**:

skilaboð | Ekkert      | Rökgildi           | Tala                  | Texti     | Annað              
-------- | ---------   | --------           | --------              | --------  | --------
rökgildi | Rangt       | á ekki við         | 0→Rangt annars→Satt   | Satt      | Oftast Satt
tala     | 0           | Rangt→0 Satt→1     | á ekki við            | ['n']→n   | Oftast 1
texti    | ['Ekkert']  | ['Rangt']/['Satt'] | ['n']                 | á ekki við | Fer eftir

## Afritun

Gildi í XOScript eru alltaf send **sem tilvísun**. Í öðrum málum
fer það eftir gerð gildisins; í XOScript er aðeins ein leið,
sem tilvísun. XOScript gerir aldrei afrit af gildi. Til að afrita hlut
þarftu að senda skilaboðin **afrita**. 

@test611

Hér hefðirðu kannski búist við að úttakið yrði Dolly en ekki
Donny. Svo er þó ekki, þar sem bæði nöfnin vísa til sama
hlutar. Þegar unnið er með lykkju gerist eitthvað svipað:

@test612

Raunar notar XOScript **alltaf** tilvísanir, svo við **:quantity**
gefur lykkjan hér að ofan einnig tilvísunina í stakið
í listanum.

Til að afrita hlut þarftu að tilgreina þessa aðgerð
**berum orðum**:

@test613

Með því að senda einundarskilaboðin **afrita** til strengs skilar hluturinn
afriti af þeim sama strenghlut. Hægt er að afrita Tala-hluti,
rökgildishluti, lista og orðabækur á sama hátt.

Þú getur líka skilgreint þína eigin útfærslu á afritun; það er jafnvel
nauðsynlegt ef þú býrð til þína eigin hluti. Sjálfgefin
útfærsla afritunar fyrir lista gerir grunnt afrit; hún býr til
nýjan lista með sömu stökum.

@test614

Í þessu tilviki er 4 aðeins bætt við afritið.
En þar sem afritið er grunnt eru hlutirnir í báðum listum
þeir sömu.

@test615

Ef við bætum 2 aftan við hvert nafn í afritinu verður upprunalegi
listinn því einnig fyrir áhrifum.

Til að ráða bót á þessu þurfum við að gera **djúpt afrit**. Slíka afritunaraðgerð
fyrir lista mætti setja saman á eftirfarandi hátt:

@test616

Taktu einnig eftir skilaboðunum endurkvæmt; nauðsynlegt er að
senda þau á undan afrita-skilaboðunum.

Mikilvægt er að hafa í huga að þótt afrit af hlut
líti oft eins út og frumritið verður það í raun
aldrei það sama. Rótarhluturinn skilgreinir skilaboðin **equal:**,
sem nota má til að bera saman auðkenni hluta. Skoðaðu
eftirfarandi dæmi:

@test617

## Óbein umbreyting

XOScript notar **óbeina umbreytingu** til að umbreyta hlutum. Til að prenta
lista á skjáinn sendir XOScript til dæmis skilaboðin
*texti* innbyrðis til listans. Þetta getur reynst mjög gagnlegt ef
þú vilt prenta lista sem kommuaðskilinn lista.
Skilaboðin *texti* má yfirskrifa: 

@test620

@api_String_base
@api_Format_base


## Strengir á netþjóni

Eftirfarandi Texti-eiginleikum er bætt við af
netþjónsviðbótinni.

@api_String_server

# Föll

{{messages}}

Þú getur flokkað kóða saman milli { og } og þá verður hann að falli.
Í xoscript notum við stundum einnig hugtakið verk, eða einfaldlega
kóðablokk.

Þú getur keyrt fall með því að senda skilaboðin *ræsa*.


```
{ Úttak skrifa: 123, ný-lína. } ræsa.
```

Ef fallið þitt tekur viðföng skaltu nota **beita:**.

```
{ :a Úttak skrifa: a, ný-lína. } beita: a.
```

Sjá einnig dæmin hér að neðan.
Vegna einfaldrar högunar getur fall aðeins haft
einn skilastað. Til að forðast aukakostnað eða óhóflega hreiðrun
skilyrða geturðu notað stefju (sem er það sama og að nota
margföldunartáknið með viðfanginu 1):

```
{
  (a = 1) satt: { x := 1. }, rjúfa.
  (a = 2) satt: { x := 2. }, rjúfa.
} stefja.
```

Á þennan hátt er (a = 2) ekki metið ef a = 1.
Auk þess þarftu ekki hreiðruð satt-skilaboð á þennan hátt.
Í hvert sinn sem þú stendur þig að því að hreiðra skilyrði skaltu hugsa
til stefja-skilaboðanna. Þau gætu gert kóðann þinn
auðlesnari.


Hér er mikilvæg gildra:

```
{
	Rangt rangt: {
		Úttak skrifa: ['Ljúktu lykkjunni.'].
	}, rjúfa.
	
	Úttak skrifa: ['Ekki sýna mig.'].

} stefja.

```

Í þessu tilviki birtist textinn 'Dont show me'.
Vegna þess að **rjúfa** er sent til Rangt. Ef þú vilt framkvæma
rof þarf að senda það sem skilaboð til **Satt**.
 

```
{
	Rangt ekki satt: {
		Úttak skrifa: ['Ljúktu lykkjunni.'].
	}, rjúfa.
	
	Úttak skrifa: ['Ekki sýna mig.'].

} stefja.

```

Virkar eins og búist er við.

## Undantekningar

Undantekningar má meðhöndla svona:

```
{ Verk 1 } grípa: { Verk 2 }, ræsa.
```

Þú getur líka valdið villu í forritinu þínu viljandi og
þannig virkjað meðhöndlunarblokkina. Það er gert með því að senda
skilaboðin **villa:** til núverandi verks eins og sýnt er á næstu
mynd:

```
{
þetta-verk villa: ['Úpps!'].
} grípa: { :mistök
Úttak skrifa: mistök.
}, ræsa.
```

## Innspýting gilda

XOScript býður upp á þann möguleika að spýta gildum inn í verk. Skoðaðu
verkið hér að neðan:

```
>> sending := {
	Fréttabréf til: eigin recipient.
}.
sending setja: ['recipient']
gildi: ['info@recipient.org'].
sending ræsa.
```


Þessi mynd sýnir ímyndað verk sem sendir fréttabréf
á netfang eða **viðtakanda**. Hægt er að spýta þessum viðtakanda
inn í verkið utan frá, áður en verkið er ræst, með því að senda
verkinu skilaboðin **setja:gildi:**. Þannig er gildi
**viðtakanda** forstillt í verkinu. Einnig má breyta þessu gildi
og keyra verkið síðan aftur. Þetta er gagnleg aðferð þegar
unnið er með verkhluti.

## Tóm föll

Tóm verk eru ekki leyfð. Fræðilega séð myndi tómt verk líta svona
út: **{}**, en XOScript lítur á þetta sem málvillu. Ef þú
vilt lýsa yfir tómu verki geturðu notað Ekkert-hlutinn:

```
>> verkefni := Ekkert.
```

Þótt þetta sé ekki raunverulegt verk heldur Ekkert-hlutur má
samt senda honum ræsa-skilaboð:

```
>> svarið := verkefni ræsa.
```

Í raun er þetta það sama og:

```
>> svarið := Ekkert ræsa.
```

Þar sem hluturinn **Ekkert** þekkir ekki skilaboðin **ræsa**
skilar hann sjálfum sér sem svari, svo svarið er enn á ný **Ekkert**.
Það er því engin þörf á tómu verki. Vegna glæsilegrar
hönnunar forritunarmálsins XOScript geturðu einfaldlega notað Ekkert-
hlutinn í þetta.

## Kvikt gildissvið

Þegar Fall þarfnast breytu en finnur hana ekki
athugar það breytur Fallsins sem **kallaði** á það
og heldur áfram að leita upp eftir keðju Fallanna.
Þessi leit heldur áfram þar til breytan finnst.
Ef breytan finnst samt ekki birtast villuboð. Þessi aðferð við að leita að
breytu kallast **kvikt gildissvið**.

Til að sýna þessa reglu:

@test618

@api_Code_base

# Rótarhlutur

{{messages}}

Hluturinn sem heitir **Hlutur** er rótarhlutur allra hluta í
XOScript og veitir kjarnaeiginleika málsins. 

Algengustu skilaboðin sem send eru
eru **við:gera:**, sem útvíkka virkni hlutar. Rótarhluturinn
tekur við þessum skilaboðum og tengir þar af leiðandi
tilgreinda verkið við skilaboðin og útvíkkar þannig afleidda
hlutinn.

## Grípa-allt-aðferðir

Venjulega eru skilaboð hunsuð ef þú sendir skilaboð sem samsvara ekki
aðferð í hlutnum. Þú getur hins vegar tilgreint
svokallaðar **töfraaðferðir** eða **grípa-allt** aðferðir sem
kallað er á ef hluturinn skilur ekki skilaboðin.

Fjórar grípa-allt-aðferðir eru í boði. Hver þeirra samsvarar
tilteknum fjölda viðfanga.

Grípa-allt-skilaboð      | Fjöldi viðfanga
------------------------ | -------------------
svara:                   | 0
svara:og:                | 1
svara:og:og:             | 2
svara:og:og:og:          | 3


@test619

## Forrituð skilaboð

Í stað þess að senda hlut skilaboð beint má einnig
senda þau með breytu. Til þess notarðu skilaboðin
**skilaboð:viðföng:**. 

@test396

@api_Object_base

# Listar

{{messages}}

XOScript þekkir tvenns konar söfn: *lista* og *orðabækur*.
**Listar** eru upptalningar hluta í *fastri röð*. Orðabækur hafa
enga röð, heldur líkjast þær skýringarlista með lykli (eða hugtaki) og
tilheyrandi gildi. Listar eru sambærilegir við fylki (PHP, Java, C)
og lista (Python). Orðabækur eru sambærilegar við tengifylki (PHP) eða
dictionaries (Python) í öðrum forritunarmálum. Til að búa til
nýjan Lista skaltu skrifa:

```
>> fibonacci := Listi nýtt.
```

Þennan tóma lista má fylla með **bæta-aftast:** :

```
fibonacci bæta-aftast: 0.
fibonacci bæta-aftast: 1.
fibonacci bæta-aftast: 1.
fibonacci bæta-aftast: 2.
fibonacci bæta-aftast: 3.
fibonacci bæta-aftast: 5.
fibonacci bæta-aftast: 8.
fibonacci bæta-aftast: 13.
```

Ef við skrifum listann út á skjáinn:

```
Úttak skrifa: fibonacci, ný-lína.
```

sjáum við:

```
Listi ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

Í stað bæta-aftast geturðu líka notað ; til að bæta stökum við lista:


```
>> fibonacci := Listi nýtt ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Semíkommurnar (;) eru allar tvíundarskilaboð sem setja
gildi í listann.

## Hlekkjun

Segjum að þú sért með lista eins og:

```
>> x := Listi nýtt ; 1 ; 2 ; 3.
```

Ef þú vilt eyða fyrsta og síðasta stakinu væru
skilaboðin þín:

```
x taka-fyrsta taka-síðasta.
```

Því miður virkar fyrri rithátturinn ekki rétt.
Skilaboðin **taka-fyrsta** skila fyrsta staki listans, sem
aftur verður viðtakandi skilaboðanna **taka-síðasta**. Skilaboðin
**taka-síðasta** eru því ekki send til **x**, heldur til 2.
Möguleg lausn á þessum vanda væri að búa til tvær aðskildar
setningar, eins og: 

```
x taka-fyrsta.
x taka-síðasta.
```

Þetta er þó fremur óhentugt, einkum þegar eyða þarf
fleiri en tveimur stökum. Þess vegna býður XOScript upp á
annars konar skilaboðauppbyggingu fyrir aðstæður af þessu tagi. Í
**annars konar** skilaboðauppbyggingu eru svör hlutanna hunsuð
og þú færð móttökuhlutinn aftur sem svar, aftur og aftur.
**Annars konar** skilaboðauppbygging hefst með því að senda
hlut skilaboðin **gera** og **annars konar** skilaboða-
uppbyggingunni má ljúka með því að senda skilaboðin **búið**. Í
dæminu sem sýnt er mætti beita þessu á eftirfarandi hátt:

```
>> x := Listi nýtt ; 1 ; 2 ; 3.
x gera taka-fyrsta taka-síðasta búið.
```

@api_List_collections

# Orðabækur

{{messages}}

**Bæði Listi og Orðabók eru söfn. Ólíkt
lista hefur orðabók **enga** röð. Annar munur á þeim
er að orðabók samanstendur af hlutapörum. Annar hluturinn er færsla (eða
lykilorð) til að leita að hinum hlutnum. Gott dæmi um
lista er verðskrá, eins og:


```
>> matseðill := Orðabók nýtt
	setja: ['£5'] við: ['eplabaka'],
	setja: ['£6'] við: ['gulrótarkaka'],
	setja: ['£3'] við: ['fudge'].
```

Rétt eins og með lista eru skilaboðin setja:við:
notuð til að bæta hlut við lista. Munurinn er sá að ólíkt
lista eru tveir hlutir tengdir saman. Fyrri hluturinn er, rétt eins og
með lista, hluturinn sem þú geymir í listanum. Seinni
hluturinn er ekki staða hans í safninu, heldur **færslan**
sem gerir kleift að sækja fyrri hlutinn síðar. Í
stuttu máli virkar orðabók svolítið eins og orðabók á pappír; með lykilorðinu
má finna merkinguna. Til dæmis, til að sækja verð á karamellu
úr listanum hér að ofan:

```
>> price := matseðill við: ['fudge'].
```

Þú mátt líka nota styttri ritháttinn:

```
>> price := matseðill ? ['fudge'].
```

Ef færslurnar sem þú notar til að geyma hluti eru án bila
(og rekast ekki á önnur fyrirfram skilgreind skilaboð)
má einnig nota næsta rithátt:

```
>> matseðill := Orðabók nýtt
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Enginn vafi leikur á því að rithátturinn hér að ofan les eðlilegar.
Til að biðja um verð á
karamellu má nota eftirfarandi einfaldaða rithátt:

```
>> price := matseðill fudge.
```

@api_Dict_collections

# Skrá

{{messages}}

Hluturinn **Skrá** veitir grunnaðgang að skráakerfinu.
Þú getur notað þennan hlut til að lesa heilar skrár inn í breytu í
einu lagi, eða skrifa breytur í skrár í einu lagi. Einnig er hægt að lesa
línu fyrir línu. Þetta eru algengustu inn- og úttaksaðgerðir með skrár
í forskriftarmáli. Ítarlegri skráaaðgerðir krefjast
notkunar FFI í gegnum netþjónsviðbótina eða sérstaka IO-viðbót.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Dagsetning/Tími

{{messages}}

Fyrir skipulega framsetningu tíma og dagsetningar notar XOScript
hlutinn **Stund**. Ef nýr Stund-hlutur er prentaður á skjáinn
birtast núverandi dagsetning og tími:

```
Úttak skrifa: Stund nýtt, ný-lína.
```

Gæti gefið eitthvað á borð við:

```
2020-10-10 12:16:39
```

Einnig er auðvelt að lesa út einstaka tímaþætti. Ef
til dæmis aðeins þarf að vita núverandi ár má senda
stundinni skilaboðin **ár** og svarið verður þá
Tala-hlutur sem inniheldur eingöngu árið:

```
>> m := Stund nýtt.
Úttak skrifa: m ár, ný-lína.
```

@api_Moment_system

# Forrit/StdOut

{{messages}}

Forrit-hluturinn táknar forritið sem er í keyrslu. Þessi hlutur
býður upp á virkni til að keyra kerfisskipanir, taka með undirforrit,
lesa viðföng og fleira. Öll kerfistengd föll.

## StdOut

Úttak er staðlaði úttakshluturinn. Hann hefur í grunninn tvær aðferðir:
**skrifa:** og **ný-lína**. Skilaboðin skrifa: eru notuð til að senda streng
í stdout, skilaboðin ný-lína prenta línuskilatákn.
Í stað **ný-lína** geturðu líka notað \\n.

Dæmi:

```
Úttak skrifa: ['Hello World'], ný-lína.
```

niðurstaða:

```
Hello World
```

## Einingar/Viðbætur

Útvíkka má heim XOScript með nýjum kerfishlutum með því að
setja upp einingar. Nýjum kerfishlut má bæta við heim
XOScript með því að setja einingarskrána (yfirleitt skrá með viðskeytinu .so
) í mods-möppuna. 

Þegar þú sendir skilaboð til hlutarins sem gerður er aðgengilegur með
viðbótareiningunni hleður XOScript henni sjálfkrafa.

Þú getur líka skrifað viðbætur sjálf(ur). Viðbætur eru skrifaðar í
forritunarmálinu C. Þú finnur dæmi um viðbót í frumkóða-
pakkanum undir src/plugins/example.


## Speglun

Ýmsar leiðir eru til að kanna kerfið
meðan forritið keyrir. XOScript hefur nokkrar aðferðir til að
greina hvaða hlutir eru til staðar og hvaða skilaboðum þessir hlutir
svara. Í fyrsta lagi má spyrja hvern hlut hvaða **gerð** hann er,
en gerðir í XOScript eru breytanlegar og því óáreiðanlegar.

Einnig er hægt að spyrja Forrit-hlutinn hvort
tiltekinn hlutur sé þegar til staðar í forritinu:

```
Forrit Verkfæri satt: { ... }.
```

Ef nafn hlutar
samanstendur af einu tákni er best að nota
eftirfarandi rithátt til að forðast rugling:

```
Forrit finna: ['X'], satt: { ... }.
```

Auk þess að spyrja um hluti er jafnframt hægt að spyrja
Forrit-hlutinn um skilaboð. Til dæmis má spyrja hvort
hluturinn **Tala** þekki skilaboðin **milli:og:**, á þann hátt
sem sýndur er hér að neðan:

```
Forrit Number: ['between:and:'], ný-lína.
```

@api_Program_system

# Netþjónn

{{messages}}

Netþjónsviðbótin í xoscript býður upp á virkni til að
búa til forrit sem keyra á netþjóni. Til að hlaða
netþjónsviðbótinni skaltu nota:

```
Server frumstilla.
```

Þér til hægðarauka er einnig mælt með að hlaða
skránum webtools.xo og template.xo.

```
Forrit nota: ['webtools.xo'].
Forrit nota: ['template.xo'].

```

## Stillingar netþjóns

Þú getur stillt eftirfarandi netþjónsstillingar:

```
	# sjálfgefin gildi eru gefin
	# svo ef þú stillir ekkert eru þessi
	# gildi notuð...

	Forrit 
	stilling: ['max-postfields']
	gildi: 40.

	Forrit 
	stilling: ['max-contentlength']
	gildi: 2000000. # 2MB

	Forrit 
	stilling: ['max-time']
	gildi: 5000. # 5sec

```

## Halló heimur

Hér er mjög einfalt vefforrit sem þú getur notað með
hefðbundnum CGI-netþjóni eins og Apache2, NGINX, OpenHTTPD eða hvaða öðrum
þekktum netþjóni sem er.

```
#!/bin/xo

Server frumstilla.
Forrit nota: ['webtools.xo'].

>> vef-skjal := Vefskjal nýtt.

vef-skjal skrifa-út: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Ef þú vilt ekki nota Vefskjal-hlutinn er það í lagi, en
þá þarftu að skrifa HTTP-hausana sjálf(ur):

```
#!/bin/xo
Úttak skrifa: ['Content-type: text/html; charset=utf-8 \n\n'], ný-lína.
Úttak skrifa: ['halló heimur!'], ný-lína.
``` 

## Beiðni

Nota má HTTP-Beiðni-hlutinn til að sækja GET/POST/COOKIE- og
UPLOAD-gögn:

```
>> beiðni  := HTTP-Beiðni nýtt.
>> search   := beiðni get: ['search']. # ?search=books
>> password := beiðni post: ['password']. # úr formi
>> valið := beiðni get-listi: ['sel[]']. #?sel[]=1&sel[]=2
>> valið := beiðni post-listi: ['sel[]'].
>> vafrakaka   := beiðni cookie: ['session-id'].
>> upphleðsla   := beiðni upload: ['file'].
>> bráðaslóð := upphleðsla ? 1.
>> skráarnafn := upphleðsla ? 0.
```

## Hámark POST/lengdar

Sjálfgefinn hámarksfjöldi POST-reita er 40 og sjálfgefin hámarks-
lengd innihalds er 2MB. Til að stilla þetta öðruvísi fyrir hverja forskrift:

```
Forrit stilling: ['max-contentlength'] gildi: 1. 
Forrit stilling: ['max-postfields'] gildi: 1. 
```

{{note}}
Ef lengd innihalds fer yfir hámarkið er
ferlið stöðvað, því við getum ekki lengur verið viss um
að gagnahleðslan sé örugg.
{{/note}}

Tímamörkin ákvarða hámarkstíma í ms
til að lesa stdin/POST-gögn.

```
Forrit stilling: ['max-time'] gildi: 5000. # 5sec
```

Þetta á aðeins við um lestur POST-gagnanna og kemur í veg fyrir
árásir á borð við slowloris. Ef þú vilt í raun takmarka
keyrslutíma hvaða aðgerðar sem er skaltu nota vekjara Forrit-hlutarins.

## Gagnagrunnur

Nota má gagnagrunnshlutinn til að senda fyrirspurnir til MariaDB/MySQL.
Til að tengjast gagnagrunni:

```
>> gg := Maria-DB nýtt hýsill: ['localhost'],
	notandanafn: ['xo'],
	lykilorð: ['pass123'],
	nafn-gagnagrunns: ['xobase'],
	tengjast.

```

Til að setja inn færslu:

```
>> leitarfæribreytur := gg fyrirspurn: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], færibreytur: ( Listi nýtt ; ['abc'] ; 12.35 ; 6 ). # fyrirspurnir með færibreytum

{  leitarfæribreytur keyra. gg staðfesta. }
grípa: { :e gg afturkalla.  }, ræsa.
```

Athugaðu að xoscript vinnur *eingöngu* með færslur (transactions) og staðfestir aldrei sjálfkrafa.
Ef ekki er hægt að slökkva á sjálfvirkri staðfestingu færðu tengivillu.
Notaðu alltaf færibreytubindingu í fyrirspurnum; bættu aldrei inntaki notanda beint
við SQL-skipunina.

Sæktu auðkenni innsettu færslunnar svona:

```
Úttak skrifa: ['SETT INN: '] + leitarfæribreytur insert-id, ný-lína. # auðkenni innsetningar
```

Til að sækja færslur:

```
>> leitarfæribreytur :=
gg
	fyrirspurn: ['SELECT * FROM book order by id desc limit 2'], 
	sækja: { :röð 
		Úttak skrifa: röð id + [' '] + röð description + [': '] + röð price, ný-lína.
	}. # sækja raðir

```

## Setur

Til að varðveita gögn geturðu geymt og sótt gögn úr setuhlut.
Búðu fyrst til nýtt **Vefskjal**. Vefskjal-hluturinn tengir saman
beiðnina, hausana, HTML-kóðann og setuna. Þetta er vegna þess að þegar þú
heimsækir vefsíðu með vafranum þínum sérðu aðeins HTML-kóðann. En
heildarvefskjalið samanstendur einnig af **hausum**. Til dæmis
innihalda flest HTTP-svör haus eins og: Content-type:text/html til að
segja vafranum að gögnin sem á eftir koma eigi að birta sem HTML
(en ekki til dæmis sækja eins og skrá). Setur eru leið til að
geyma notandagögn milli beiðna. Til að halda utan um þessi gögn þurfum við
að setja vefköku og sú vefkaka er einnig sett með haus. Þess vegna
kemur allt saman í Vefskjal-hlutnum (því hann er heildar-
skjalið sem inniheldur bæði hausa og HTML eða önnur gögn).


```
# Fyrst búum við til nýtt tilvik af Vefskjal
>> vefur := Vefskjal nýtt.

# Nú hefjum við setu, þetta býr til Haus fyrir vafraköku og
# býr til skrá til að geyma gögnin þín, tengda þeirri vafraköku
>> setan := vefur hefja-setu.

# Nú getum við meðhöndlað setan eins og Orðabók
setan userid: 123.
```

Til að eyða setunni (við útskráningu):

```
vefur eyða-setu.
```

## Hausar

Vefskjalið gerir þér einnig kleift að setja aðra þekkta hausa.
Til dæmis ef þú vilt vísa notandanum á aðra vefslóð:

```
vefur fara-á: ['/other.html'].
```

Undir yfirborðinu býr þessi skipun einnig til HTTP-hausinn sem sendur er
með öðrum gögnum eða HTML-kóða til að segja vafranum að fara
á tilgreint markvistfang.

Til að bæta við sérsniðnum haus:

```
vefur haus: ( 
	HTTP-Haus nýtt
	lykill: ['Content-Length']
	gildið: 400
).
```

Til að sýna 404-síðu:

```
vefur fannst-ekki: ['Úps..'].
```


## Sniðmát

Sjálfgefna sniðmátskerfið er mjög einfalt. Þú þarft ekki að læra
nýja sniðmátsmálskipan. Auk þess tryggir sniðmátsvélin raunverulegan aðskilnað
milli framsetningar og viðskiptarökvísi.

Til að búa til sniðmát úr skrá:

```
>> tpl := vefur sniðmát: ['templates/ux.tpl'].
```

Sniðmátskerfið notar merki. 
Merkin eru af þremur gerðum: klippimerki, límmerki og
hólfamerki. Grunnhugmyndin er mjög einföld: þú klippir út
svæði sem auðkennd eru með klippimerkjum og getur límt þau á
svæði sem auðkennd eru með límmerkjum. Þú getur spýtt strengjum inn í
hólfamerki.

Gefum okkur til dæmis eftirfarandi sniðmát; setjum
gimsteininn í skartgripaskrínið og bætum við verðmiða.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Þetta geturðu gert á eftirfarandi hátt:

```
>> gem := tpl klippa: ['gem'], afrita.
gem price: 99.
tpl líma: gem við: ['jewels'].
vefur skrifa-út: tpl fága.
```

Síðasta línan sendir einfaldlega sniðmátið sem streng til biðlarans
ásamt nauðsynlegum HTTP-hausum.

Niðurstaða:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

Til að bera fram skrár sem notendur hafa hlaðið upp á öruggan hátt geturðu reitt þig á passthru:

```
>> upphlaðið := ['smile.gif'].
Server áframsenda: upphlaðið forskeyti: ['/uploads/images/'].
Forrit enda.
```

Þetta ber fram efnið sem notandinn hlóð upp með viðeigandi
mime-gerð. Aðeins mime-gerðir á leyfislista eru studdar:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF og SVG.
SVG-, ZIP- og GZIP-skrár eru sendar til niðurhals, því SVG
getur innihaldið forskriftir sem annars myndu keyra á léninu þínu.
Þessi aðferð kemur í veg fyrir TOCTOU-árásir, slóðaflakk (path traversal),
keyrslu spilliforritakóða (innspýtingu), táknræna tengla-árásir,
DDoS-árásir (skráarhámark = 50MB), hlerunarárásir og
ýmis önnur öryggisvandamál.


## JSON

Til að kóða hlut sem JSON:

```
>> json := ( JSON jsonify: ( 
	Orðabók nýtt setja: ( 
		Listi nýtt ; 1 ; 2 ; 3
	) við: ['abc']
)).
```

Til að afkóða JSON í xoscript-hlut:

```
>> obók := ((JSON hlutur: json) abc ? 1).
```

JSON með meira en 500 stigum hreiðrunar er hafnað sem ógildu.

Til að skrifa Orðabók beint út sem json með réttum hausum:

```
vefur json: obók.
```


## Regluleg segð

Þú getur notað reglulegar segðir með því að búa til mynstur.
Til dæmis til að finna href og target í tenglum:

```
Mynstur nýtt: ['href="([^"]+)" target="([^"]+)"'].
```

Beittu nú mynstrinu á viðfangsstrenginn svona:

```
mynstrið samsvörun: efni gera: { :m :x .... }
```

Heildardæmi:

```
>> efni := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> mynstrið := Mynstur nýtt: ['href="([^"]+)" target="([^"]+)"'].
>> niðurstaða  := mynstrið samsvörun: efni gera: { :m :x
	Úttak skrifa: m, ný-lína.
	Úttak skrifa: x, ný-lína.
	<- ['XXX'].
}.
Úttak skrifa: niðurstaða, ný-lína.
```

## Netsamskipti

Notaðu Net-hlutinn til að senda vefbeiðni.
Net-hluturinn sendir alltaf POST-beiðni, nema þú sendir Ekkert sem
gögn; þá sendir hann GET-beiðni.


```
Net 
post: Ekkert 
til: ['https://redbeanphp.com'].
```

## Dulkóðun

Netþjónsviðbótinni fylgir dulkóðun byggð á XChaCha20 og Argon2.

Dæmi:

```
>> dulkóðað := Hvelfing dulkóða: ['hello'] lykill: ['world'].
>> afkóðað := Hvelfing dulkóða: dulkóðað lykill: ['world'].
```

## Tókar

Til að búa til dulmálsfræðilega öruggan tóka af tiltekinni lengd:

```
>> minnTóki := Hvelfing tóki: 40.
```

Þetta býr til tóka sem er 40 stafir.

## Sniðsetning

Snið-hluturinn gerir þér kleift að sniðsetja gögn, t.d. með fyllingu eða
með því að bæta við núllum. Hann notar printf-málskipan.

```
>> fmt := Snið nýtt: ['%06.0f'].
fmt beita: 56. # gefur 000056
```

Snið getur innihaldið eina umbreytingu og hún verður að passa við gildið,
annars færðu villu:

- `beita:` með streng: `%s`
- `beita:` með tölu: `%f`, `%e`, `%g` eða `%a`
- `beita-heiltölu:` með tölu: `%d`, `%i`, `%o`, `%u`, `%x` eða `%c`

Gildi úr beiðni eru strengir. Til að sniðsetja slíkt gildi sem tölu
skaltu fyrst umbreyta því:

```
fmt beita: (beiðni get: ['amount']) tala.
```

## Kóðarar

Nokkrir kóðarar og afkóðarar eru í boði.
URL-kóðarinn undirbýr vefslóð til notkunar í HTML sem tengil:

```
Server url-kóða: ['https://example.com?a=6&b=1 2'].
```

Til að spýta inntaki notanda á öruggan hátt inn í HTML-kóðann þinn án hættu á XSS-
innspýtingu skaltu alltaf nota:

```
Server html-kóða: ['<skaðlaust>'].
```

Athugaðu að sniðmátsvélin framkvæmir alltaf HTML-kóðun
þegar þú skrifar í hólfamerki. Ef þú notar sniðmátskerfið
þarftu því ekki að nota þetta.

## Póstsending

Til að senda póst skaltu nota safnið mailtools.xo.

Dæmi:

```
Server frumstilla.
Forrit nota: ['mailtools.xo'].

>> tölvu-póstur := HTML-Tölvupóstur nýtt.
>> img := tölvu-póstur hengja-við: ( Skrá nýtt: ['myimage.png'] ).

tölvu-póstur
sendandi: ['xo@xoscript.com'] nafn: ['xo'],
til: ( Listi nýtt ; ['xo2@xoscipt.com'] ),
efni: ['xoxo'],
meginmál: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), senda.

```



## Tenging

Með skilaboðunum tengja: geturðu tengt ytra safn við
forritið þitt með libffi. Nánari upplýsingar er að finna í kaflanum um ffi.


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

FFI er veitt fyrir hvern verkvang/viðbót því það
tengist undirliggjandi högun kerfisins, sem
kjarninn á ekki að gera.
Netþjónsviðbótin býður upp á samhæfða ffi/blob-útfærslu.
Sjálfgefið tengist kjarninn markverkvanginum
í gegnum stdin/stdout, takmarkaða inn- og úttaksþjónustu fyrir skrár og skel (Forrit kerfi:).
Frekari samþætting er veitt með ffi/blob í gegnum
forritamiðaðar viðbætur eins og netþjónsviðbótina.

FFI stendur fyrir Foreign Function Interface (viðmót fyrir framandi föll). Það gerir þér kleift að nota virkni sem aðrir hafa skrifað í
öðrum forritunarmálum og er veitt í gegnum DLL-skrár, SO-skrár eða Dylib-skrár. Þetta geta
verið margvísleg föll og gríðarlega mikil virkni er aðgengileg með þessari aðferð.
Byrjum á dæmi:

```
Server tengja: (
 Listi nýtt ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Listi nýtt ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s losa.
```

Niðurstaða þessa kóða er sú að þú sérð eftirfarandi á skipanalínunni:
FFI has 3 letters.
Nú hugsarðu líklega: „Þetta er mikill kóði fyrir eitthvað svona einfalt.“
Hefðum við ekki bara getað leyst þetta með Gui show skipun? Svarið er afdráttarlaust já!
En þetta er hugsað sem skýringardæmi.
FFI er yfirleitt notað í flóknari verkefni, en þau eru ekki góð
dæmi, svo ég valdi eitthvað einfalt.

Viðföng tengja-aðferðarinnar:

- Viðfang #1: DLL- eða SO-skráin sem þú vilt nota.
- Viðfang #2: Fallið í þeirri skrá sem þú vilt tengja.
- Viðfang #3: Listi með nöfnum gagnagerða viðfanga fallsins.
- Viðfang #4: Nafn skilagerðar fallsins.
- Viðfang #5: Nafn hlutarins sem þú vilt tengja þetta fall við (ef hann er ekki til verður hann búinn til
sjálfkrafa).
- Viðfang #6: Skilaboðin sem þetta fall á að tengjast.

Í dæminu hér að ofan viljum við tengja printf-fallið úr libc.so. Nöfn gagnagerðanna
finnurðu í skjölun hugbúnaðarins sem þú tengist. Tiltækar gerðir eru:
void, pointer, float, double, int, uint, char, uchar, intX og uintX,
þar sem X getur verið 8, 16, 32 eða 64.

Þessar gerðir vísa til fjölda bæta sem þarf til að geyma gögnin. Fyrir printf tengjum við
nýjan hlut sem heitir Printf og skilaboðin template:number:. Þú þýðir ytra
fallið yfir á XOScript-mállýskuna áður en þú notar það. Skilaboðin template:number: búast við
biðminni með sniðmátstextanum sem fyrstu færibreytu. Við búum til þetta biðminni með Blob-hlut, sem
gerir þér kleift að úthluta minni handvirkt. Þú berð ábyrgð á að losa þetta minni á eftir
með skilaboðunum losa.

Þú getur fyllt minnisblob á ýmsa vegu. Í dæminu okkar fyllum við það með texta, svo við notum
skilaboðin utf8: (UTF-8 er kóðun til að breyta texta í bæti). Þú getur líka fyllt blob með
bytes: og sent lista af bætagildum. Til að lesa innihald blobs skaltu nota frá:lengd:.
Þú færð bætin til baka sem lista. Þú getur jafnvel búið til C-struct með Blob með
skilaboðunum struct: og sent runu af C-gerðum. Þetta getur verið nauðsynlegt þegar kallað er á C-
fall í ytra hugbúnaðarsafni sem býst við bendi á struct.

{warning}
Þú þarft að losa blob sjálf(ur).
Ruslasafnarinn hreinsar ekki blob.
{/warning}

Þar sem hægt er að skiptast á blob við ytri föll úr söfnum
er ekki hægt að ruslasafna þeim sjálfkrafa (ytri föll gætu enn verið að nota þau
eða þessi ytri föll gætu viljað losa þau
sjálf). Þess vegna þarftu að losa blob sjálf(ur) ef þörf krefur.

Til að losa blob skaltu nota:

```
minnBlob losa.
```

Til að losa struct skaltu nota:

```
minnStrúktúr losa-struct losa.
```

Fyrir struct þarftu því að senda tvenn skilaboð: losa-struct og losa til að
afúthluta minnisblokkinni.

@api_Blob_fficonnect
