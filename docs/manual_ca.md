# Conceptes bàsics

{{messages}}


Benvinguts a XOScript
El projecte XOScript té com a objectiu crear un llenguatge de scripting senzill i auditable.
Senzill no vol dir necessàriament fàcil.
Un llenguatge de programació conegut pot ser més fàcil d'utilitzar que XOScript.
Aquí, la senzillesa significa una altra cosa:
poder formar-se un model mental complet del llenguatge i del seu comportament.

XOScript està dissenyat per cabre al vostre cap.
La seva gramàtica i el nombre de conceptes són deliberadament petits.
No hi ha classes; els objectes es poden ampliar directament.
Els objectes es passen per referència, la còpia és explícita
i les funcions tenen un únic punt de sortida.

Algunes d'aquestes decisions difereixen força dels llenguatges més habituals.
XOScript no té sistema de tipus, per exemple, i utilitza abast dinàmic.
Els missatges que no es poden gestionar s'ignoren en lloc de produir una excepció.
Aquestes decisions tenen conseqüències i no pretenen eliminar els errors.
Pretenen mantenir petit i coherent el model subjacent del llenguatge.

XOScript també es pot localitzar, cosa que permet expressar regles de negoci
en una llengua natural i, potencialment, compartir-les amb persones implicades sense formació tècnica.

L'auditabilitat consisteix a aplicar la mateixa filosofia a la implementació.
L'entorn d'execució està escrit en C, amb un analitzador lèxic, un analitzador sintàctic i un recorregut d'arbre petits i escrits a mà.
La biblioteca estàndard i l'entorn d'execució reflecteixen en gran part l'estructura del llenguatge,
de manera que la relació entre el codi XOScript i la seva implementació és relativament directa.

Les proves també estan estretament vinculades a la documentació.
Cada mètode hauria de tenir una prova associada que es pugui incorporar al manual,
cosa que ajuda a mantenir la documentació sincronitzada amb la implementació.

XOScript no pretén competir amb els llenguatges més habituals en
funcionalitats o familiaritat. Explora un objectiu diferent:
un entorn de programació que un desenvolupador pugui entendre en conjunt.

L'esperança és que un llenguatge petit i una implementació
petita facin viable entendre el programari
des del byte fins a l'objecte, des de la sintaxi fins a l'entorn d'execució, i escriure codi amb
confiança perquè enteneu tant el que passa a
l'script com el que passa per sota.

L'arquitectura d'una instal·lació de servidor xoscript
és senzilla però flexible.

{{architecture.png}}

Per utilitzar xoscript com a llenguatge de servidor, cal instal·lar el
connector de servidor en una carpeta anomenada /mods/server. 

Això és perquè ens agrada
desacoblar el nucli del llenguatge de les funcionalitats específiques del servidor,
a diferència, per exemple, de PHP o Python. Altrament hauríem de distribuir
a tothom tot el que hi ha i més sense cap motiu, cosa que és simplement absurda.
També podeu instal·lar altres mòduls si voleu. El sistema és molt
flexible.

A més, algunes funcions s'implementen millor en el mateix llenguatge
de scripting, com ara les plantilles i la gestió de sessions, així que també
distribuïm les biblioteques template.xo i webtools.xo per a la vostra comoditat.
El motiu de tot això és que no sabem com voleu
utilitzar xoscript. El podeu utilitzar com a llenguatge de scripting al costat del servidor,
però també per a interfícies gràfiques, dispositius encastats o simplement processament per lots.
Fins i tot si l'utilitzeu com a llenguatge de scripting al costat del servidor (que
actualment és un dels casos d'ús principals), potser voldreu
utilitzar un altre motor de plantilles o un altre gestor de sessions.
Qui som nosaltres per decidir que heu d'utilitzar els nostres?

Tanmateix, un dels avantatges d'utilitzar el nostre propi motor de plantilles és que
no cal aprendre cap sintaxi addicional per crear plantilles.
El motor de plantilles per defecte que s'inclou amb xoscript fa una
separació del 100% entre presentació i lògica. En lloc d'una sintaxi especial
de plantilles, simplement utilitza un sistema de marcadors d'espais molt flexible.
Per a més informació, vegeu el capítol Servidor.

Tingueu en compte que, si no voleu utilitzar el motor de plantilles per defecte ni
les webtools per defecte, és evident que n'haureu de proporcionar
uns de propis.

Si executeu el servidor web en un chroot, una jail o un altre tipus d'entorn aïllat,
també cal instal·lar les dependències de xo en aquest entorn; podeu
veure quines biblioteques necessiteu amb ldd (vegeu la pàgina de manual de Linux o BSD).
Si voleu utilitzar ordres de shell als vostres scripts xo, copieu també un shell
(com bash o ksh) a aquest entorn.

També volem remarcar que ens prenem molt seriosament la compatibilitat amb versions anteriors.
Fins i tot hi ha una funcionalitat especial de compatibilitat amb versions anteriors anomenada
'version'. En general, pretenem que el vostre codi funcioni per sempre. Així, mai
no haureu d'actualitzar el codi per mantenir-lo compatible amb versions més noves
de xoscript. El nostre objectiu és: escriu-ho una vegada, executa-ho per sempre.

La resta d'aquest manual es dedica a explicar en detall el llenguatge
de programació xoscript. El scripting de servidor es tracta al capítol
anomenat Servidor. Si sou un desenvolupador de programari experimentat, potser voldreu
saltar-vos alguns capítols, perquè alguns són una mica massa detallats o
s'assemblen molt a les pràctiques generals de programació. Així doncs, els que
ja tingueu experiència amb diversos altres llenguatges de programació
fareu millor de tractar aquest manual com una guia de referència.

## Instal·lació a Linux

Descarregueu apache2 i mariadb:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Descarregueu xoscript.
Substituïu X pel número de versió correcte!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Copieu els fitxers a l'arrel web i a /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Editeu la configuració d'apache2:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Substituïu Virtualhost per:

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

Creeu una pàgina de prova:

```
sudo nano /var/www/html/test.xo
```

i escriviu un petit programa de prova:

```
#!/bin/xo
Server inicialitzar.
Programa utilitza: ['webtools.xo'].
>> web := Document-Web nou.
web emetre: ['Hello World'].
```

Permeteu que apache2 executi el programa mitjançant CGI:

```
sudo chmod uog+x /var/www/html/test.xo
```

Reinicieu apache2:

```
sudo systemctl restart apache2
```

Aneu a la pàgina de prova al navegador:

```
http://localhost/test.xo
```

Hauríeu de veure:

```
Hello World
```


## Instal·lació a OpenBSD

Editeu /etc/httpd.conf i afegiu-hi:


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

Si voleu utilitzar SSL:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Per protegir l'intercanvi de claus contra els ordinadors quàntics,
seleccioneu el xifratge mlkem:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Afegiu el binari xo i els mòduls, així com qualsevol dependència, al
chroot (esbrineu-les amb ldd).

## Executar exemples


Per executar un dels programes d'exemple del paquet:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Per exemple, per executar l'exemple FizzBuzz a Linux:

```
./example.sh fizzbuzz Linux
```

Per executar el mateix exemple a OpenBSD:

```
./example.sh fizzbuzz OBSD
```

Per executar l'exemple amb una compilació neta:

```
./example.sh fizzbuzz OBSD clean
```

## Proves unitàries

Per executar les proves unitàries:

```
./runtests.sh
```

Per executar les proves unitàries sense compilar (només provar):

```
./runtests.sh nobuild
```

## Compilació

Per compilar des del codi font a Linux:

```
make clean
ISO="en" make
```

A OpenBSD:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

Per compilar el connector de servidor a Linux:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

Per compilar el connector de servidor a OpenBSD:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Hola món

Un cop transferit a l'ordinador, podeu extreure el fitxer
i iniciar xo amb l'ordre següent:

```
xo
```

Per executar un XOScript, deseu el programa en un fitxer afegint-hi el
sufix -xo (opcional). A més, escriviu el nom del fitxer del programa
després de l'ordre XOScript:

```
xo myprogram.xo
```

Quan executeu una ordre XOScript amb el fitxer del programa com a
paràmetre, xo llegirà i executarà el fitxer del programa.

{{note}}
També podeu iniciar el programa arrossegant-lo a la icona de xo.
{{/note}}

{{warning}}
En alguns sistemes cal concedir prèviament a xo permisos per carregar biblioteques
dinàmiques.
{{/warning}}

La tradició mana que el primer programa en qualsevol llenguatge de programació
nou sigui una mena de salutació al món. En XOScript, un programa
**Hola món** com aquest té aquest aspecte:

@test598

Quan aquest text es desa en un fitxer, per exemple hello.xo, es pot executar
així: .

xo hello.xo

Hello world


Podeu veure la sortida del programa a la finestra negra que es mostra a dalt.
Al llarg d'aquest manual s'utilitzarà la mateixa representació per mostrar
la sortida.

{{note}}
**Sortida** s'escriu amb una S majúscula.
En general, els objectes comencen amb una lletra majúscula
tret que actuïn com a instància (no tenen mètodes
propis, només dades). Això reflecteix les convencions de classe i instància
d'altres llenguatges de programació.
{{/note}}


## Sintaxi 

XOScript és un llenguatge de programació *purament* *orientat a objectes*. Això vol dir
que xoscript considera que tot és un objecte i, per tant, no hi ha
altres *tipus de dades*. Bàsicament hi ha tres accions rutinàries bàsiques
en un programa escrit en XOScript: *assignar*, *enviar missatges*
i *respondre*. L'intercanvi de missatges entre objectes és la part clau
d'un programa XOScript. A continuació s'il·lustren les tres accions rutinàries
individuals:


Acció           | Exemple
--------------- | --------
assignar        |  \>\> x := 1. 
missatges unaris | x parell?.
missatge binari | 1 + 2.
missatge de paraula clau | x de: 0 longitud: 10.
resposta        | <- answer.  


Aquest capítol us donarà una impressió general del llenguatge XOScript
i en descriu els principis bàsics. XOScript és un llenguatge petit i
fonamentat en tres accions (vegeu la il·lustració) que es tradueixen en
aproximadament sis regles gramaticals. Això és tot el que cal per dominar el
llenguatge.

No us preocupeu si les coses no us resulten òbvies de seguida: totes les peces
s'exploraran al capítol següent (3) i les regles bàsiques es
repetiran. Tanmateix, aquest capítol serveix principalment com a introducció
general al llenguatge. Els principis bàsics s'explicaran breument
i s'il·lustraran amb diversos exemples rellevants. Els detalls que faltin
s'exposaran més endavant.

Els comentaris en XOScript comencen amb el símbol \#. Així, la línia següent
s'ignorarà:

```
# això és només un comentari
```

## Variables

Per assignar
una variable s'utilitza el símbol de declaració de variable: >>. El nom d'una
variable pot contenir tots els signes excepte: <-, :=, espais en blanc,
punts, comes, dos punts, cometes [' '] i parèntesis ().
A més, una variable no pot ocupar diverses línies. Tingueu en compte
que una variable no pot començar amb un número ni amb un signe menys.

Aquests són exemples de variables vàlides:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dòlar'].
>> +plus := Cert.
>> contrasenya-usuari := ['Pssst!'].
```

Són variables no vàlides, per exemple:


```
>> -123 := ['nombre negatiu'].
>> password of usuari := ['Confidencial'].
>> password.of:usuari := ['Confidencial'].
>> ,x := 10.
```

{{note}}
No cal escapar cap caràcter
(incloses cometes, cometes dobles, delimitadors
de text) en
un literal de text sempre que no
causi ambigüitat a l'analitzador lèxic.
{{/note}}

Un cop declarada una variable, es pot utilitzar lliurement. Això vol dir
que només cal utilitzar el símbol de declaració la primera vegada
que s'utilitza la variable (la declaració).

Per ser més concrets, no podeu començar a assignar un valor a
la variable sense més *(x := 2)*, ja que primer cal declarar la variable *(\>\>
x := 2)*. Tanmateix, un cop declarada, en podeu canviar el valor
sense utilitzar el símbol de declaració *(\>\> x := 2. x := 3.)*.

Tingueu en compte que és obligatori assignar un valor a una variable en el moment de
declarar-la. A diferència d'altres llenguatges de programació, no es permet
declarar una variable sense valor. És imprescindible vincular explícitament
cada variable a un valor inicial. Tot i així, podeu inicialitzar
la variable amb l'objecte **Res**. En aquest cas, la variable es pot
considerar buida *(\>\> x := Res.)*. En resum, no es permet declarar una
variable sense valor inicial. Així,

```
>> x.
```

no és vàlid i donarà un missatge d'error.

{{note}}
xoscript utilitza abast dinàmic per a les variables; per
a més detalls, consulteu el capítol Funcions.
{{/note}}


## Literals

XOScript considera que tot és un objecte, és a dir, tots els números, textos
i fragments de codi. Els números, com ara 1, 2, 100, -999 i 1,234, són
objectes Número. Tots els textos entre cometes simples són objectes
Text. Tots els fragments de codi agrupats entre claus {...} són
objectes Funció.

Literal         | Objecte arrel | Exemple
--------------- | ------------ | ----------
números         | Número       | 1,2,3... 
textos          | Text         | \['hello'\]
funció          | Funció       | { 1 + 2. }.
                
     
Objectes com els números i els textos sempre tenen el seu origen en un objecte
arrel. Per exemple, tots els números deriven de l'objecte **Número**. Tots
els textos deriven de **Text** i tots els fragments de codi, de **Funció**. Al
seu torn, tots aquests objectes provenen d'**Objecte**, que és, de fet, l'objecte
arrel de tots els objectes.


## Missatges

Programar en XOScript consisteix bàsicament a
enviar missatges a objectes. La notació general per enviar un missatge a
un objecte és la següent:

```
<object> <message>
```

Per saber si el número **2**, per exemple, és un número parell,
s'envia el missatge **parell?** a l'objecte **2**:

```
2 parell?
```

La resposta serà **Cert** (de nou, un objecte). Els objectes normalment
ignoren els missatges desconeguts, de manera que no es produeix cap error. Alguns objectes (per exemple,
números o textos) responen a un missatge desconegut d'una manera predefinida
(més informació sobre aquest tema més endavant).

Un objecte pot rebre tres tipus de missatges. 

Tipus           | Nombre d'arguments
--------------- | -------------------
Unari           | 0      
Binari          | 1     
De paraula clau | 1+    


En primer lloc, hi ha els **missatges
unaris**, vegeu l'exemple anterior, que no tenen arguments. En segon lloc,
hi ha els **missatges de paraula clau**, que tenen un o diversos arguments,
per exemple:

```
>> x := Número entre: 1 i: 10.
```

En aquest cas, el missatge **entre:i:** s'envia a **Número**, que
és l'objecte arrel de tots els números. El resultat serà un número aleatori
entre 1 i 10. Finalment, hi ha els **missatges binaris**, que tenen
només un caràcter i un argument:

```
2 + 3
```

Sembla una suma matemàtica, però en realitat és només un altre missatge. El
missatge **+** s'envia a **2**, amb l'argument **3**, i retorna la
resposta **5**. Els missatges binaris es poden escriure sense dos punts.

Els missatges binaris es poden encadenar:

```
>> x := 3 + 2 - 1.
```

En aquest fragment, primer s'envia **+ 2** a l'objecte **Número** **3**, cosa que
dona com a resultat l'objecte Número **5**, i després s'envia **-1** a aquest
número. Els lectors atents tenen raó en notar la discrepància que
mostra aquest protocol respecte a l'ordre matemàtic convencional dels
operadors. XOScript ignora l'ordre matemàtic en favor de la
coherència del seu sistema de missatges. Com a resultat, la suma:

```
2 + 3 * 5 = 25
```

no 17.

Això és intencionat. Es poden utilitzar parèntesis per modificar l'ordre:

```
2 + (3 * 5) = 17
```

La majoria d'objectes es retornen a si mateixos com a resultat en resposta a un
missatge. Això és útil, ja que afavoreix continuar el diàleg amb aquest
objecte enviant-li un missatge següent:

```
Sortida escriu:
[' hola '] retalla majúscules.
```

```
HOLA
```

Aquí s'envien dos missatges a l'objecte **Text**: **retalla**, seguit
de **majúscules**.

En el fragment següent, cal utilitzar una coma per indicar
que arriba un missatge nou. Si no, XOScript es confondrà.

```
Sortida escriu: ['Hello!'], salt-de-línia.
```

Primer s'envia el missatge **escriu:** al símbol del llapis, seguit de
**salt-de-línia**. Sense la coma, XOScript pensaria que voleu enviar
**salt-de-línia** al **text** **Hello!**, un exercici inútil.

L'ordre de processament dels missatges és el següent: d'esquerra a dreta;
es comença pels missatges entre parèntesis, seguits dels missatges unaris. Després,
els missatges binaris i finalment els missatges de paraula clau. Vegeu l'exemple
següent:

```
Sortida escriu: 0.5 arrodoneix + (2 - 1), salt-de-línia.
```

XOScript sempre llegeix d'esquerra a dreta: primer s'envia el missatge **escriu:**
a Sortida i després el missatge **salt-de-línia**. Dins de
l'argument mateix, XOScript llegeix d'esquerra a dreta, així que primer **0.5 arrodoneix**
i després **+**.

{{note}}
El missatge salt-de-línia afegeix un caràcter de salt de línia al text.
El nom original d'aquest missatge (stop) s'inspira en els sistemes telegràfics.
Els missatges dels sistemes telegràfics 
sovint utilitzaven la paraula STOP per marcar el final d'una frase
(ja que la puntuació era poc fiable o costosa).
{{/note}}

A més, **arrodoneix** té prioritat sobre **+**, perquè és un
**missatge unari**. Pels parèntesis, primer es calcula **2 - 1**,
i després s'afegeix **1** al resultat de **0.5 arrodoneix** (1).

Tot el procés donarà el resultat **2**, que també és la resposta
escrita. Després de la coma ve el missatge salt-de-línia, que mou el cursor
a una línia nova. Evidentment, la millor manera d'entendre del tot l'ordre
dels programes XOScript és amb la pràctica.

Val la pena remarcar que en XOScript, a diferència de molts altres llenguatges
de programació, els espais en blanc són una part fonamental de la sintaxi. En
particular, pel que fa als missatges binaris, els espais en blanc poden causar
confusió. Utilitzeu sempre un espai en blanc després d'un missatge binari. No podeu
enganxar directament un número al missatge, per exemple: 

```
3 + 2
```

és diferent de 

```
3 +2
```

El primer exemple (**3 + 2**) envia el
missatge **+** al número **3**, amb el número **2** com a argument. El
resultat, en aquest cas, serà **5**. En el segon exemple (**3 +2**),
s'envia el missatge unari **+2** al número **3**. Segons el
context, això pot donar un resultat molt diferent.

## Mètodes inexistents

Enviar un missatge a un objecte invoca la funció que s'ha
associat a aquest objecte amb aquest nom de missatge. Si envieu un missatge
que no s'entén, l'objecte receptor ignorarà el missatge
i, en canvi, retornarà una referència a si mateix per continuar la comunicació.
Això s'anomena pas de missatges tolerant.

Exemple:

```
Sortida escriu: Objecte blah, salt-de-línia.
```

Això no donarà cap error. Simplement imprimirà el text **Objecte**.


## Flux de control

En XOScript no calen regles gramaticals separades per als *bucles* i
els *condicionals*. Una sentència condicional és només un simple missatge **cert:** o **fals:**
a un objecte **Cert** o a un objecte **Fals**:

```
2 parell? cert: {
	Sortida escriu: ['Dos és un nombre parell'], salt-de-línia.
}.
```
En l'exemple anterior, el missatge **cert:** s'envia a **Cert** (la
resposta a la pregunta: és 2 un número parell?). Com a argument s'envia
un fragment de codi addicional: un objecte **Funció**. Aquesta funció escriu a
la pantalla que 2 és, efectivament, un número parell.

Tampoc no calen regles d'escriptura separades per a un *bucle*. Per
executar un fragment de codi tres vegades, simplement envieu **\*** amb l'argument
**3** a aquesta **Funció**:

@test5

En aquest fragment de codi, **i** és l'índex. Així, la primera vegada que s'executa la Funció,
**i** és igual a 0, la següent vegada que s'executa, **i** = 1, i
així successivament.

Considerem un altre exemple. Quan cal imprimir una taula de conversió
de *kJ* (quilojoules) a *kcal* (quilocalories) en passos de 100,
vegeu a continuació la notació correcta:

@test599

Aquí, el número de la línia actual es transmet al paràmetre
**:line**. Al començament d'una funció es defineixen els paràmetres
de la funció. Els paràmetres no utilitzats queden buits (**Res**). Els paràmetres
sempre es col·loquen al començament de la funció, just després de la clau
d'obertura, i van precedits de dos punts.

El missatge **mentre:** és una combinació d'un *bucle* i una *condició*.
Es poden enllaçar dues funcions amb el missatge **mentre:**. La funció receptora
continuarà executant-se fins que la funció després dels dos punts doni un resultat
negatiu. Exemple:

@test600

En el fragment de codi il·lustrat a dalt, s'afegeix **1** a **x** mentre
**x** sigui menor que **5**. Quan deixa de ser així, la segona
funció respondrà amb **Fals** i, en conseqüència, l'execució de la
primera funció acabarà. Tingueu en compte que **x** s'ha definit fora de la
funció i és una variable global. Per saber-ne més sobre les regles d'abast,
consulteu el capítol sobre Funcions.

## Interpolació de textos

La llista *kJ/kcal* es podria fer més
presentable. Preferiblement, la llista seria així:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Quan convertiu la sortida desitjada en una plantilla, la notació
podria ser:

```
number1 kJ ➞ number2 kcal
```

Això vol dir que **number1** representa el valor en kJ i **number2** el
valor en kcal. Així funciona la interpolació de textos en XOScript. No
calen regles gramaticals separades per a això en XOScript. Simplement envieu
al text la paraula que cal substituir, amb el text substitut
com a argument:

```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

El resultat:

```
100 kj ➞ 23.9 kcal
```

Aquesta regla de substitució funciona per a cada missatge no definit que rep
un objecte **text**. Cada missatge que l'objecte **text** no reconeix
s'interpretarà de la manera següent: *substitueix el text del missatge
pel text de l'argument del missatge.* Podeu adaptar el
programa de la manera següent:


@test601


Per evitar confusions sobre quins missatges es poden utilitzar o no com a
substitut, el millor és introduir un marcador de plantilla com &lt; &gt;
per als segments de text de la plantilla que
cal substituir.

## Valors de retorn

Per respondre un missatge s'utilitza la fletxa de retorn
(*<-*). L'exemple següent il·lustra com crear una tasca
per calcular un percentatge:

@test602

Després que la tasca s'hagi definit i assignat a la variable **percentage**,
s'envia el missatge **aplica:i:** amb els arguments **100** i **7**.

Això executarà la tasca aplicada a **100** i **7**, és a dir, el 7% de 100.
Amb la fletxa de retorn, la resposta es retorna des de la tasca
al programa principal.

## Ampliació

Tot i que aquest codi és vàlid, té un inconvenient,
perquè cal recordar l'ordre dels arguments. Aleshores, per què no
escriure-ho així: *7 percent of: 100 *? Semblaria molt més
*natural*. Per fer-ho possible, hem d'adaptar l'objecte pare de
**7**, que és l'objecte **Número**, perquè entengui el
missatge **percent of:**. Això es pot aconseguir enviant **en:fes:** a
l'objecte Número, així:

@test603

Com que el percentatge és, en aquest cas, el mateix número, ens hi referim amb jo,
la paraula clau *jo*. En resum, el símbol jo significa: *envia aquest
missatge a mi mateix*.

# Objectes

{{messages}}

A més d'ajustar i ampliar objectes existents, també podeu crear
objectes nous vosaltres mateixos simplement enviant el missatge **nou**. Suposem que
voleu crear un objecte factura que imposi una seqüència de
numeració; en aquest cas, primer necessitareu un objecte factura.

Sabent que cada objecte deriva d'un altre objecte, que al seu torn
acaba provenint de l'objecte arrel de tots els objectes, anomenat Objecte,
cal triar en quin d'aquests altres objectes es basarà el vostre
objecte nou. El vostre objecte nou hereta totes les propietats de
l'objecte en què es basa, és a dir, aquell al qual es va enviar
inicialment el missatge **nou**.

En aquest exemple es prefereix un objecte més aviat neutre, sense gaires
propietats heretades. Això fa que l'elecció sigui fàcil, perquè en aquest
cas l'objecte nou es pot basar en el mateix objecte arrel, que és
**Objecte**. La notació del sistema de facturació previst serà
la següent:

@test604

El número de factura actual es desa a l'objecte; per això hi ha
la paraula clau **propi** al davant. Això s'anomena una *propietat*;
més endavant se'n donaran més detalls.

Algunes empreses prefereixen incorporar l'any als números de
factura. En aquest cas, podeu crear un objecte factura nou basat en un
objecte factura anterior, però que ofereixi al seu usuari la possibilitat
d'indicar un any concret:

@test605

No cal tornar a escriure la implementació del missatge **número**,
ja que s'hereta de l'**objecte factura** escrit
anteriorment; en conseqüència, es pot reutilitzar el codi antic. XOScript no té conceptes
com les classes i altres conceptes relacionats. Això vol dir que els objectes
només poden heretar d'altres objectes, cosa que també es coneix com a *herència
prototípica*.

Tornem ara a les propietats. Només es pot accedir a les propietats d'un objecte
des de *dins de la jerarquia de l'objecte*, de manera que aquestes propietats
no les poden percebre altres objectes.

A diferència d'altres llenguatges de programació, totes les propietats dels objectes són
visibles exclusivament per a l'objecte que ha creat la propietat i per als
objectes derivats. 

Una tècnica d'ús habitual és utilitzar un objecte com una mena de *plànol*,
com és el cas, per exemple, de les factures comentades abans.
Un altre bon exemple és **Point**. Suposem que creeu un
programa informàtic que fa càlculs amb punts d'un mapa. Podeu
desenvolupar l'objecte **Point**, que conté les propietats d'una
coordenada x i una coordenada y, que es posaran a disposició del
món exterior mitjançant missatges:

@test606

El missatge **=** compara els dos punts amb el missatge **i:**. La
primera comparació dona com a resultat un **Cert** o un **Fals**. Aquests són objectes
booleans. Quan envieu el missatge **i:** a un objecte Cert, i
l'objecte argument després dels dos punts també és **Cert**, aleshores
rebreu com a resposta de nou **Cert**. Quan qualsevol dels dos és **Fals**,
rebreu la resposta **Fals**. Tingueu en compte que un punt no pot llegir les coordenades de
l'altre. Cal enviar un missatge a l'altre punt per demanar-li
aquestes dades: **x-coordinate** i **y-coordinate**. Al cap i a la fi, com ja
s'ha explicat, les propietats només es poden obtenir des de dins de
la mateixa família d'objectes. 

Tingueu en compte que aquí s'utilitza el missatge **=** per fer la comparació
dels punts. Igualment s'hauria pogut utilitzar un altre missatge, com ara
**is:** o **equal:**, però reutilitzar el caràcter **=** semblava
adequat en aquest cas.

## Herència

Podeu reutilitzar codi escrit anteriorment per crear una jerarquia
d'objectes. Per exemple:

```
>> Animal := Objecte nou.
>> Gos := Animal nou.
>> Caniche := Gos nou.
```

En aquest cas, **Dog** hereta tot el comportament i les propietats
d'**Animal** i, al seu torn, l'objecte **Animal** hereta tot el comportament
d'**Objecte**, l'objecte arrel de tots els objectes.


## Sobreescriptura


En l'exemple següent es crea un tipus nou de llista:
**Combination**, en què es garanteix que cada element sigui únic. Les
funcions de la llista es reutilitzen mitjançant l'herència:

@test607

Observeu com el segon **red** queda exclòs de la llista.

De vegades pot caldre sobreescriure un comportament d'un objecte.
Per exemple, quan se sumen números i cal tenir en compte les unitats
de mesura. En l'exemple següent es crea l'objecte **Size**.
Aquest objecte retorna un número que, durant la suma, té
en compte la unitat del número que s'hi suma. L'objecte **Número**
comprova si es tracta de *polzades* o de *peus*. El codi
podria semblar-se al següent:

@test608

## Recursió

En l'exemple anterior se sobreescriu el **signe** més. Tingueu en compte
que, al final, encara cal fer la suma definitiva, cosa que, de fet,
té lloc a la línia següent:

```
>> contestació := jo + (número x factor).
```

Ara bé, com entén XOScript que aquest **signe** més fa referència a
la lògica original de la suma? Per exemple, una altra interpretació
podria ser que XOScript enviés repetidament el mateix missatge al mateix
objecte, cosa que al seu torn resultaria en un **bucle infinit**. Clarament,
aquesta no és la intenció. Tan bon punt envieu un missatge a un objecte
que executaria exactament el mateix codi, XOScript s'adonarà que,
en aquest cas, es vol dir el missatge subjacent sobreescrit. Així, el vostre
programa queda protegit automàticament contra aquesta mena de bucles
infinits. Tanmateix, quan realment voleu executar la mateixa funció des de
la funció actual, caldrà enviar primer el missatge
**recursiu**. En aquest cas, el resultat serà un bucle
infinit. Tot i així, les tasques recursives tenen aplicacions útils; per
exemple, suposem que voleu calcular el factorial d'un número
donat. En aquest cas, simplement afegiu el missatge **factorial** a
Número:

@test609

Això requereix recursió. De fet, la tasca vinculada al
missatge **factorial** s'ha de tornar a executar dins d'aquesta funció.
Per tant, cal invocar la funció factorial des de dins de la mateixa
funció factorial. Per norma, XOScript impedeix aquesta rutina
pel risc d'acabar en un bucle infinit. Per aquest motiu,
és imprescindible fer precedir el missatge de la paraula **recursiu**. Això
es fa perquè XOScript sàpiga que la vostra
intenció és executar la mateixa tasca i que no us heu equivocat.

## Objectes semblants a classes

Tot i que xoscript no ofereix classes, imitar un comportament
semblant al de les classes és trivial. Simplement sobreescriviu el missatge nou.

```
>> Animal := Objecte nou.
Animal en: ['nou'] fes: {
	<- jo nou inicialitzar.
}.

Animal en: ['inicialitzar'] fes: {
	propi so := ['?'].
	propi potes  := 4.
}.
```

En el fragment de codi anterior creem un objecte anomenat Animal.
Aquest objecte serveix de *plànol* per a tota mena d'animals,
com gossos i gats. L'objecte pare Animal s'escriu
amb A majúscula per indicar que és un objecte semblant a una classe.
A continuació sobreescrivim el missatge nou escrivint el nostre propi mètode nou.
En aquest cas envia un missatge nou a jo, seguit del missatge
inicialitzar. Com que xoscript bloqueja la recursió per defecte, això no provocarà
un bucle infinit. En canvi, enviarà el missatge nou a l'objecte
pare (Objecte), cosa que dona com a resultat una instància nova d'Animal. Així creem
un objecte nou, basat en el mateix objecte per al qual hem creat el nostre mètode nou.
Això és perfectament vàlid. Ara també enviem el missatge inicialitzar, que garanteix
que l'objecte Animal tingui valors per defecte per a les seves propietats. Per defecte,
un animal té 4 potes i el so és desconegut (d'aquí el signe d'interrogació).
Per crear una instància nova del nostre Animal, simplement podríem dir:

```
>> a := Animal nou.
```

Ara obtenim una instància nova d'Animal amb 4 potes, so desconegut i
un mètode inicialitzar. Igual que en altres llenguatges orientats a objectes, també podem
ampliar el nostre Animal:

```
>> Gos := Animal nou.
Gos en: ['inicialitzar'] fes: {
	jo inicialitzar.
	propi so := ['borda'].
}.
```

Ho podem provar fàcilment afegint un mètode text:

```
Animal en: ['text'] fes: {
	<- propi potes text + propi so.
}.
```

Ajuntem-ho tot:

@test13


Crear un objecte que es troba en un estat inicial determinat planteja
un problema freqüent. Suposem que cal crear un objecte **Rectangle**
per calcular el perímetre i l'àrea. Una notació possible seria:


```
>> Rectangle := Objecte nou.

Rectangle en: ['àrea'] fes: {
	<- propi longitud * propi amplada.
}.
```

Evidentment, establir una longitud i una amplada és una condició prèvia. Amb aquesta
finalitat, es poden afegir els missatges **longitud:** i **width:**:


```
Rectangle en: ['length:'] fes: { :longitud
	propi longitud := longitud.
}.

Rectangle en: ['width:'] fes: { :amplada
	propi amplada := amplada.
}.

```

Aquest rectangle es pot utilitzar de la manera següent:


```
>> rectangle := Rectangle nou length: 2, width: 3.
Sortida escriu: rectangle àrea.
```

Tanmateix, si s'obliden els valors inicials de longitud i amplada,
es produirà un missatge d'error:

```
>> rectangle := Rectangle nou.
Sortida escriu: rectangle àrea.
```

produirà l'error següent:

```
Clau no trobada:longitud
```

Per evitar-ho, és preferible que un rectangle
tingui sempre una longitud i una amplada inicials, per exemple 0. Així, en aquest
cas, cal **sobreescriure** el missatge **nou**.

@test610

Si sobreescrivim el missatge nou, bàsicament estem imitant una **classe**.

El món de XOScript està ple d'una gran diversitat d'objectes, que estan
disponibles per al vostre programa des del primer moment. Als capítols següents
es tractaran tots aquests objectes del nucli.

## Instantànies

Podeu desar un objecte (juntament amb el seu estat actual) al disc amb:

```
elMeuObjecte save-as: ['saved.bin'].
```

Per tornar a carregar l'objecte des del disc:

```
>> elMeuObjecte := Objecte load-from: ['saved.bin'].
```

Les instantànies es poden utilitzar per desar un estat determinat o per millorar el rendiment.
Carregar una instantània evita l'anàlisi lèxica, l'anàlisi sintàctica i la configuració de l'aplicació.
A més, en el futur es podrien introduir avantatges de rendiment addicionals
amb les instantànies, com l'optimització de certs patrons o la detecció i
optimització dels camins crítics.

{{warning}}
Les instantànies són una funcionalitat experimental; no les utilitzeu en producció.
Per activar les funcionalitats experimentals, compileu amb -D EXPERIMENTS.
{{/warning}}


@test712

# Objecte Res

{{messages}}

L'objecte Res
representa el buit o, millor dit, l'absència d'informació. En
ocasions rebreu aquest objecte com a resposta a un missatge, quan
el resultat és **res**. La pregunta més essencial que
podeu fer a l'objecte **Res** és: **Res?**. La
resposta sempre serà **Cert**.

```
Sortida escriu: Res Res?.
```

resultat:

```
Cert
```

Qualsevol objecte que no sigui **Res** respondrà amb **Fals**. El
fragment de codi anterior pot semblar una mica filosòfic, però l'objecte **Res**
té sens dubte aplicacions extremadament pràctiques. Per exemple,
rebreu l'objecte Res com a resposta si demaneu un
element d'una llista que no existeix. També podeu utilitzar l'objecte Res
si voleu declarar una variable però encara no voleu especificar-ne cap
valor. En lloc d'això, simplement hi **assigneu** el valor especial **Res**. En
XOScript no es permet declarar una variable sense valor, com ara:


```
>> valor.
```

En lloc d'això, heu d'escriure el següent:

```
>> valor := Res.
```

@api_None_base

# Booleans

{{messages}}

A diferència de la majoria de llenguatges de programació populars en el moment d'escriure això,
XOScript només proporciona un únic objecte Cert i un únic objecte
Fals. Per aclarir-ho, cada vegada que escriviu **Cert**, no vol dir que
s'hagi creat un objecte nou. En canvi, sempre utilitzeu una referència. Això
vol dir que quan escriviu el següent:

\>\> x := Cert.

**x** fa referència a l'objecte **Cert**. El codi condicional i els bucles també
verifiquen aquesta referència. En XOScript, el significat de **Cert** i **Fals**
no és fix. De fet, un programa XOScript queda força trasbalsat per una
sentència com aquesta:

Cert := Fals.

El resultat d'aquestes accions no està definit, però continua sent una acció
vàlida i, per tant, formalment permesa. A més, hi ha un objecte Booleà,
que és l'objecte arrel tant de **Cert** com de **Fals**, ja que tots dos
en són derivats. L'objecte Booleà en si, però,
no té cap aplicació pràctica.

## Paranys

Aneu amb compte en utilitzar **i:** i **o:**

```
Sortida escriu: (Fals or: Cert or: Cert), salt-de-línia.
Sortida escriu: (Fals o: Cert, o: Cert), salt-de-línia.
```

Dona

```
Fals
Cert
```
perquè el missatge **o:** només admet 1 argument. La primera línia
envia **o:o:** a Fals, que no existeix, de manera que l'objecte ignora
el missatge i es retorna a si mateix (Fals). En canvi, la segona línia
envia **o:** seguit d'un altre **o:** (utilitzant un símbol d'encadenament, és a dir, una coma: ,).


@api_Boolean_base

# Números

{{messages}}

Cada vegada que escriviu un número, per exemple 9, -10 o 3,12, per sota,
XOScript convertirà aquests números en un objecte **Número**. Podeu
enviar missatges a aquest objecte Número, o bé podeu assignar el número
a una variable i enviar-li missatges després:

```
10 parell?

>> bitlletDeDeu := 10.
bitlletDeDeu parell?

```

Totes dues notacions són vàlides. L'objecte Número respon als missatges
següents...

La majoria d'aquests missatges s'expliquen per si mateixos i permeten fer
operacions matemàtiques o comparacions.

{{note}}
Tingueu en compte que podeu utilitzar ≤ ≥ ≠ × i ÷ en lloc dels seus equivalents ASCII.
És una qüestió de preferència.
{{/note}}

La diferència entre els missatges matemàtics binaris (+) i
les seves variants de paraula clau (suma:) és que els primers retornen
un número nou, que és el resultat de l'operació, mentre que amb els
segons es modifica el mateix objecte. Això s'il·lustra a
l'exemple següent:

@test597

En l'exemple anterior, b = 4 i a = 3. Amb **suma: 2** el valor
d'a augmenta en 2, mentre que **+ 3** crea un número nou que és
igual a a + 3. El mateix s'aplica a altres operacions matemàtiques, per exemple,
les multiplicacions. Si utilitzeu el símbol de multiplicació, rebreu un
objecte nou com a resposta. Si utilitzeu el missatge **multiplica-per:**,
multiplicareu el mateix número.

Amb el missatge **entre:i:**, per exemple a: **Número
entre: X i: Y**, obtindreu un número entre X i Y. D'aquesta
manera es pot generar qualsevol número aleatori:

```
>> a := Número entre: 1 i: 10.
Sortida escriu: a, salt-de-línia.
```

A partir de la versió 1.4, el generador integrat de números aleatoris de xoscript és
criptogràficament segur, pel que sabem.

Podeu associar un **qualificador** a un número, per exemple, **6
apples**. Cada missatge que un número no reconeix
es considerarà un qualificador. Podeu obtenir el qualificador d'un
número amb el missatge qualificador:

Un qualificador és bàsicament un objecte Text que es desa amb l'objecte
Número. El qualificador també s'imprimeix després del número en una
instrucció **escriu:**. Els qualificadors es podrien utilitzar, per exemple, per sumar imports
en monedes diferents. En sumar els imports, podeu consultar
els qualificadors. L'exemple de programa següent il·lustra aquest
principi amb una calculadora de monedes històriques (ja que el tipus de
canvi es manté raonablement estable!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Textos

{{messages}}

Cada vegada que es col·loca un text entre **claudàtors i cometes** ['...'],
XOScript us crearà un objecte text nou. Tanmateix,
assegureu-vos d'utilitzar les cometes correctes. La cometa del
començament del text és diferent de la del final (això us permet
utilitzar la cometa simple sense haver-la d'escapar).

## UTF8

Els textos de xoscript normalment contenen text codificat en utf8. Tot i que
tècnicament és possible tenir contingut binari o que no sigui utf8 en
un text, es recomana utilitzar blobs per a això. Els blobs
els proporciona el connector de servidor (vegeu el capítol ffi).
En general, els blobs i ffi es proporcionen
per connector o plataforma, ja que estan lligats a la plataforma
i a l'arquitectura (ffi/blobs). El nucli del llenguatge de scripting intenta
mantenir-se tan independent de la plataforma com sigui possible.

## Conversió de tipus

Podeu crear una còpia de qualsevol objecte
amb un tipus diferent amb els missatges següents:

Missatge | Resultat
------- | ------
número  | Converteix a número
text    | Converteix a text
booleà  | Converteix a booleà
  
S'**apliquen** les regles següents:

missatge | Res       | Booleà             | Número                | Text      | Altres              
-------- | --------- | --------           | --------              | --------  | --------
booleà   | Fals      | n/a                | 0→Fals altrament→Cert | Cert      | Gairebé sempre Cert
número   | 0         | Fals→0 Cert→1 | n/a                       | ['n']→n | Gairebé sempre 1
text     | ['Res']   | ['Fals']/['Cert'] | ['n']                 | n/a       | Depèn

## Còpia

Els valors en XOScript sempre es passen **per referència**. En altres llenguatges
depèn del tipus de valor; en XOScript només hi ha una manera:
per referència. XOScript mai no fa una còpia d'un valor. Per copiar un objecte,
cal enviar el missatge **copia**. 

@test611

Aquí potser esperàveu que la sortida fos Dolly, en lloc
de Donny. Tanmateix, no és així, ja que tots dos noms fan referència al mateix
objecte. Quan es treballa amb un bucle, passa una cosa semblant:

@test612

De fet, XOScript **sempre** utilitza referències, de manera que a **:quantity**
el bucle il·lustrat a dalt també indica la referència a l'element
de la llista.

Per copiar un objecte, cal especificar aquesta acció
**explícitament**:

@test613

En enviar el missatge unari **copia** a un text, l'objecte
retorna una còpia d'aquest mateix objecte text. Es poden copiar objectes Número,
objectes booleans, llistes i diccionaris de la mateixa manera.

També podeu definir la vostra pròpia implementació de la còpia; fins i tot és una
necessitat si creeu els vostres propis objectes. La implementació
per defecte de la còpia d'una llista fa una còpia superficial: crea una
llista nova amb els mateixos elements.

@test614

En aquest cas, el 4 només s'afegeix a la còpia.
Tanmateix, com que la còpia és superficial, els objectes de totes dues llistes
són els mateixos.

@test615

Així, si afegim 2 a cada nom de la còpia, la llista
original també es veu afectada.

Per solucionar-ho, cal fer una **còpia profunda**. Una acció de còpia
així per a una llista es podria compondre de la manera següent:

@test616

Fixeu-vos també en el missatge recursiu; cal enviar aquest missatge
abans del missatge copia.

És essencial tenir present que, tot i que la còpia d'un objecte
sovint té el mateix aspecte que l'original, de fet mai no serà
el mateix. L'objecte arrel defineix un missatge **equal:**,
que es pot utilitzar per comparar la identitat dels objectes. Vegeu
l'exemple següent:

@test617

## Conversió implícita

XOScript utilitza la **conversió implícita** per convertir objectes. Per imprimir una
llista a la pantalla, XOScript, per exemple, enviarà internament el missatge
*text* a la llista. Això pot resultar molt útil
si voleu imprimir una llista com a llista separada per comes. El
missatge *text* es pot sobreescriure: 

@test620

@api_String_base
@api_Format_base


## Textos del servidor

Les funcionalitats de Text següents les afegeix el
connector de servidor.

@api_String_server

# Funcions

{{messages}}

Podeu agrupar codi entre { i }; aleshores esdevé una funció.
En xoscript també utilitzem de vegades el terme tasca o simplement
bloc de codi.

Podeu executar una funció enviant el missatge *inicia*.


```
{ Sortida escriu: 123, salt-de-línia. } inicia.
```

Si la funció admet arguments, utilitzeu **aplica:**.

```
{ :a Sortida escriu: a, salt-de-línia. } aplica: a.
```

Vegeu també els exemples següents.
A causa de l'arquitectura simplista, una funció només pot tenir
un punt de retorn. Per evitar sobrecàrrega o un niuament excessiu de
condicions, podeu utilitzar un procediment (que és el mateix que utilitzar el
signe de multiplicació amb l'argument 1):

```
{
  (a = 1) cert: { x := 1. }, interromp.
  (a = 2) cert: { x := 2. }, interromp.
} procediment.
```

D'aquesta manera, (a = 2) no s'avaluarà si a = 1.
A més, així no calen missatges cert: niats.
Cada vegada que us trobeu niant condicions, penseu
en el missatge procediment. Pot fer que el codi
sigui més fàcil de llegir.


Aquí teniu un parany important:

```
{
	Fals fals: {
		Sortida escriu: ['Acaba el bucle.'].
	}, interromp.
	
	Sortida escriu: ['No em mostris.'].

} procediment.

```

En aquest cas, es mostrarà el text 'Dont show me'.
Perquè **interromp** s'envia a Fals. Si voleu executar
una interrupció, cal enviar-la com a missatge a **Cert**.
 

```
{
	Fals no cert: {
		Sortida escriu: ['Acaba el bucle.'].
	}, interromp.
	
	Sortida escriu: ['No em mostris.'].

} procediment.

```

Funcionarà com s'espera.

## Excepcions

Les excepcions es poden gestionar així:

```
{ Tasca 1 } captura: { Tasca 2 }, inicia.
```

També podeu provocar intencionadament un error al programa i,
d'aquesta manera, activar el bloc gestor. Això es fa enviant el
missatge **error:** a la tasca actual, tal com es mostra a la
il·lustració següent:

```
{
aquesta-tasca error: ['Ostres!'].
} captura: { :equivocació
Sortida escriu: equivocació.
}, inicia.
```

## Injecció de valors

XOScript ofereix a les tasques l'opció d'injectar-hi valors. Vegeu
la tasca següent:

```
>> enviament := {
	Butlletí destinatari: propi recipient.
}.
enviament estableix: ['recipient']
valor: ['info@recipient.org'].
enviament inicia.
```


Aquesta il·lustració presenta una tasca imaginària que envia un butlletí
a una adreça de correu electrònic o **destinatari**. Aquest destinatari es pot injectar
a la tasca des de fora i abans que s'iniciï, enviant el
missatge **estableix:valor:** a la tasca. D'aquesta manera, el valor de
**recipient** queda preestablert a la tasca. Aquest valor també es pot modificar
i aleshores es pot tornar a executar la tasca. És un mètode útil quan s'utilitzen
objectes Tasca.

## Funcions buides

No es permeten les tasques buides. En teoria, una tasca buida tindria aquest
aspecte: **{}**, però XOScript ho considera un error del llenguatge. Si
voleu declarar una tasca buida, podeu utilitzar l'objecte Res:

```
>> tasca := Res.
```

Tot i que això no és una tasca real, sinó un objecte Res, encara s'hi pot
enviar un missatge inicia:

```
>> contestació := tasca inicia.
```

De fet, això és el mateix que:

```
>> contestació := Res inicia.
```

Com que l'objecte **Res** no reconeix el missatge **inicia**,
es retornarà a si mateix com a resposta, de manera que la resposta torna a ser **Res**.
Així doncs, no cal tenir una tasca buida. Gràcies al disseny elegant
del llenguatge de programació XOScript, simplement podeu utilitzar l'objecte Res
per a això.

## Abast dinàmic

Quan una Funció necessita una variable però no la troba,
consulta les variables de la Funció que l'ha **cridada**,
i continua cercant cap amunt per la cadena de Funcions.
Aquest procés de cerca continua fins que es troba la variable.
Si la variable continua sense trobar-se, apareixerà un missatge d'error. Aquesta manera de cercar una
variable s'anomena **abast dinàmic**.

Per il·lustrar aquest principi:

@test618

@api_Code_base

# Objecte arrel

{{messages}}

L'objecte anomenat **Objecte** és l'objecte arrel de tots els objectes de
XOScript i proporciona les funcionalitats bàsiques del llenguatge. 

El missatge que s'envia amb més freqüència
és **en:fes:**, que amplia les funcionalitats d'un objecte. Aquest
missatge el rep l'objecte arrel, que en conseqüència vincula la
tasca especificada al missatge i, d'aquesta manera, amplia l'objecte
derivat.

## Mètodes comodí

Normalment, si envieu un missatge que no correspon a
cap mètode de l'objecte, s'ignora. Tanmateix, podeu especificar
els anomenats **mètodes màgics** o mètodes **comodí**, que
s'invoquen si l'objecte no entén el missatge.

Hi ha 4 mètodes comodí disponibles. Cada missatge correspon a
un nombre concret d'arguments.

Missatge comodí      | Nombre d'arguments
-------------------- | -------------------
respon:              | 0
respon:i:            | 1
respon:i:i:          | 2
respon:i:i:i:        | 3


@test619

## Missatges programàtics

En lloc d'enviar un missatge directament a un objecte, també es pot
enviar mitjançant una variable. Per fer-ho, s'utilitza el missatge
**missatge:arguments:**. 

@test396

@api_Object_base

# Llistes

{{messages}}

XOScript coneix dos tipus de col·leccions: *llistes* i *diccionaris*.
Les **llistes** són enumeracions d'objectes en un *ordre fix*. Els diccionaris no tenen
ordre; en canvi, s'assemblen a una llegenda amb una clau (o terme) i el seu
valor corresponent. Les llistes són comparables als arrays (PHP, Java, C)
i a les llistes (Python). Els diccionaris són comparables als arrays associatius (PHP) o
als diccionaris (Python) d'altres llenguatges de programació. Per crear
una Llista nova, escriviu:

```
>> fibonacci := Llista nou.
```

Aquesta llista buida es pot omplir amb **afegeix-al-final:** :

```
fibonacci afegeix-al-final: 0.
fibonacci afegeix-al-final: 1.
fibonacci afegeix-al-final: 1.
fibonacci afegeix-al-final: 2.
fibonacci afegeix-al-final: 3.
fibonacci afegeix-al-final: 5.
fibonacci afegeix-al-final: 8.
fibonacci afegeix-al-final: 13.
```

Si escrivim la llista a la pantalla:

```
Sortida escriu: fibonacci, salt-de-línia.
```

Veurem:

```
Llista ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

En lloc d'afegeix-al-final també podeu utilitzar ; per afegir elements a una llista:


```
>> fibonacci := Llista nou ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Els punts i coma (;) són tots missatges binaris que posen un
valor a la llista.

## Encadenament

Suposem que teniu una llista com aquesta:

```
>> x := Llista nou ; 1 ; 2 ; 3.
```

Si voleu suprimir el primer i l'últim element, el vostre
missatge seria:

```
x treu-primer treu-últim.
```

Malauradament, la notació anterior no funcionarà correctament. El
missatge **treu-primer** retorna el primer element de la llista, que,
al seu torn, esdevindrà el receptor del missatge **treu-últim**. Així, el
missatge **treu-últim** no s'envia a **x**, sinó a 2. Una
possible solució a aquest problema seria crear dues frases
separades, com ara: 

```
x treu-primer.
x treu-últim.
```

Tanmateix, això és força poc pràctic, sobretot quan cal
suprimir més de dos elements. Per això, XOScript ofereix una
estructura de missatges alternativa per a aquesta mena de situacions. En les
estructures de missatges **alternatives**, les respostes dels objectes s'ignoren
i rebeu com a resposta l'objecte receptor, una vegada i una altra.
Una estructura de missatges **alternativa** s'inicia enviant el
missatge **fes** a un objecte, i l'estructura de missatges **alternativa**
es pot acabar enviant el missatge **fet**. En
l'exemple il·lustrat, això es podria aplicar de la manera següent:

```
>> x := Llista nou ; 1 ; 2 ; 3.
x fes treu-primer treu-últim fet.
```

@api_List_collections

# Diccionaris

{{messages}}

**Tant Llista com Diccionari són col·leccions. Tanmateix, a diferència d'una
llista, un diccionari **no té** ordre. Una altra diferència entre tots dos
és que un diccionari consisteix en parells d'objectes. Un objecte actua com a entrada (o
paraula clau) per cercar l'altre objecte. Un bon exemple d'aquesta
mena de llista és una llista de preus, com ara:


```
>> menú := Diccionari nou
	posa: ['£5'] a: ['pastís de poma'],
	posa: ['£6'] a: ['pastís de pastanaga'],
	posa: ['£3'] a: ['fudge'].
```

Igual que en una llista, el missatge posa:a:
s'utilitza per afegir un objecte a una llista. La diferència és que, a diferència
d'una llista, es vinculen dos objectes. El primer objecte és, igual que
en una llista, l'objecte que desareu a la llista. El segon
objecte no és la seva posició dins de la col·lecció, sinó l'**entrada**
que permet recuperar més endavant l'objecte anterior. En
resum, un diccionari funciona una mica com un diccionari de paper: amb la paraula clau
es pot trobar el significat. Per exemple, per obtenir de la
llista esmentada a dalt el preu d'un fudge:

```
>> price := menú a: ['fudge'].
```

També podeu utilitzar la notació concisa:

```
>> price := menú ? ['fudge'].
```

Si les entrades que utilitzeu per desar objectes no tenen espais
(i no coincideixen amb altres missatges predefinits),
també es pot utilitzar la notació següent:

```
>> menú := Diccionari nou
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Sens dubte, la notació anterior es llegeix d'una manera una mica més natural.
Per demanar el preu d'un
fudge, es pot utilitzar la notació simplificada següent:

```
>> price := menú fudge.
```

@api_Dict_collections

# Fitxer

{{messages}}

L'objecte **Fitxer** proporciona accés bàsic al sistema de fitxers.
Podeu utilitzar aquest objecte per llegir fitxers sencers en una variable
d'una sola vegada, o per escriure variables en fitxers d'una sola vegada. També s'admet
la lectura línia a línia. Aquestes són les operacions d'E/S de fitxers més habituals
en un llenguatge de scripting. Les operacions de fitxers avançades requereixen
utilitzar FFI mitjançant el connector de servidor o un connector d'E/S separat.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Data i hora

{{messages}}

Per a una representació estructurada de l'hora i la data, XOScript utilitza
l'objecte **Moment**. Quan s'imprimeix a la pantalla un objecte Moment nou, es mostren
la data i l'hora actuals:

```
Sortida escriu: Moment nou, salt-de-línia.
```

Pot donar com a resultat alguna cosa semblant a:

```
2020-10-10 12:16:39
```

També és fàcil llegir els components individuals del temps. Així, per
exemple, si només cal saber l'any actual, es pot enviar el missatge
**any** al moment i, al seu torn, la resposta serà un
objecte Número que conté només l'any:

```
>> m := Moment nou.
Sortida escriu: m any, salt-de-línia.
```

@api_Moment_system

# Programa/Sortida estàndard

{{messages}}

L'objecte Programa representa l'aplicació que s'està executant. Aquest objecte
ofereix funcionalitats per executar ordres del sistema, incloure subprogrames,
llegir arguments i molt més. Totes les funcions relacionades amb el sistema.

## Sortida estàndard

Sortida és l'objecte de sortida estàndard. Bàsicament té dos mètodes:
**escriu:** i **salt-de-línia**. El missatge escriu: s'utilitza per enviar un text
a stdout, i el missatge salt-de-línia imprimeix un caràcter de salt de línia.
En lloc de **salt-de-línia** també podeu utilitzar \\n.

Exemple:

```
Sortida escriu: ['Hello World'], salt-de-línia.
```

resultat:

```
Hello World
```

## Mòduls i connectors

El món de XOScript es pot ampliar amb objectes de sistema nous
instal·lant mòduls. Es pot afegir un objecte de sistema nou al món de
XOScript col·locant el fitxer del mòdul (normalment un fitxer amb el sufix .so
) a la carpeta mods. 

Quan envieu un missatge a l'objecte que es posa a disposició mitjançant el
mòdul connector, XOScript el carregarà automàticament.

També podeu escriure connectors vosaltres mateixos. Els connectors s'escriuen en el
llenguatge de programació C. Podeu trobar un connector d'exemple al paquet del codi
font, a src/plugins/example.


## Reflexió

Hi ha diverses maneres d'explorar el
sistema durant l'execució del programa. XOScript té un parell de mètodes per
detectar quins objectes hi ha i a quins missatges responen
aquests objectes. En primer lloc, es pot preguntar a cada objecte de quin **tipus** és;
tanmateix, els tipus en XOScript són mal·leables i, per tant, poc fiables.

També es pot preguntar a l'objecte Programa si un
objecte determinat ja és present al programa:

```
Programa Eina cert: { ... }.
```

En el cas d'un nom d'objecte
que consisteix en un sol símbol, el millor és aplicar la
notació següent per evitar confusions:

```
Programa troba: ['X'], cert: { ... }.
```

A més de preguntar per objectes, també es pot preguntar a
l'objecte Programa per missatges. Per exemple, es pot preguntar si
l'objecte **Número** coneix el missatge **entre:i:**, de la manera
que s'il·lustra a continuació:

```
Programa Number: ['between:and:'], salt-de-línia.
```

@api_Program_system

# Servidor

{{messages}}

El connector Server de xoscript ofereix funcionalitats per
crear aplicacions al costat del servidor. Per carregar el connector
de servidor, utilitzeu:

```
Server inicialitzar.
```

Per comoditat, també es recomana carregar
els fitxers webtools.xo i template.xo.

```
Programa utilitza: ['webtools.xo'].
Programa utilitza: ['template.xo'].

```

## Configuració del servidor

Podeu establir la configuració del servidor següent:

```
	# es donen valors per defecte,
	# de manera que si no configureu res, s'utilitzen
	# aquests valors...

	Programa 
	configuració: ['max-postfields']
	valor: 40.

	Programa 
	configuració: ['max-contentlength']
	valor: 2000000. # 2MB

	Programa 
	configuració: ['max-time']
	valor: 5000. # 5sec

```

## Hola món

Aquí teniu un programa web molt senzill que podeu utilitzar amb un
servidor CGI estàndard com Apache2, NGINX, OpenHTTPD o qualsevol altre
servidor conegut.

```
#!/bin/xo

Server inicialitzar.
Programa utilitza: ['webtools.xo'].

>> doc-web := Document-Web nou.

doc-web emetre: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Si no voleu utilitzar l'objecte Document-Web, cap problema, però
aleshores heu d'escriure les capçaleres HTTP vosaltres mateixos:

```
#!/bin/xo
Sortida escriu: ['Content-type: text/html; charset=utf-8 \n\n'], salt-de-línia.
Sortida escriu: ['hola món!'], salt-de-línia.
``` 

## Petició

L'objecte Petició-HTTP es pot utilitzar per obtenir dades GET/POST/COOKIE i
UPLOAD:

```
>> petició  := Petició-HTTP nou.
>> search   := petició get: ['search']. # ?search=books
>> password := petició post: ['password']. # del formulari
>> seleccionats := petició get-llista: ['sel[]']. #?sel[]=1&sel[]=2
>> seleccionats := petició post-llista: ['sel[]'].
>> galeta   := petició cookie: ['session-id'].
>> pujada   := petició upload: ['file'].
>> camíTemporal := pujada ? 1.
>> nomfitxer := pujada ? 0.
```

## Maxpost/length

El nombre màxim de camps POST per defecte és 40 i la longitud màxima de contingut
per defecte és 2MB. Per configurar-ho de manera diferent per a cada script:

```
Programa configuració: ['max-contentlength'] valor: 1. 
Programa configuració: ['max-postfields'] valor: 1. 
```

{{note}}
Si la longitud del contingut supera el màxim, el
procés s'atura perquè ja no podem estar segurs
que la càrrega útil sigui segura.
{{/note}}

El límit maxtime determina el temps màxim en ms
per llegir stdin/les dades POST.

```
Programa configuració: ['max-time'] valor: 5000. # 5sec
```

Això només s'aplica a la lectura d'E/S de les dades POST, i evita
atacs del tipus slowloris. Si realment voleu limitar el
temps d'execució de qualsevol operació, utilitzeu l'alarma de Programa.

## Base de dades

L'objecte Database es pot utilitzar per fer consultes a MariaDB/MySQL.
Per connectar-vos a una base de dades:

```
>> bd := Maria-DB nou amfitrió: ['localhost'],
	usuari: ['xo'],
	contrasenya: ['pass123'],
	nom-base: ['xobase'],
	connecta.

```

Per inserir un registre, utilitzeu:

```
>> paràmetres-de-cerca := bd consulta: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], paràmetres: ( Llista nou ; ['abc'] ; 12.35 ; 6 ). # consultes parametritzades

{  paràmetres-de-cerca executa. bd confirma. }
captura: { :e bd desfés.  }, inicia.
```

Tingueu en compte que xoscript treballa *només* amb transaccions i mai no fa confirmacions automàtiques.
Si no es pot desactivar l'autocommit, obtindreu un error de connexió.
Utilitzeu sempre la vinculació de paràmetres a les consultes; no afegiu mai l'entrada de l'usuari directament
a l'SQL.

Obteniu l'identificador inserit així:

```
Sortida escriu: ['INSERIT: '] + paràmetres-de-cerca insert-id, salt-de-línia. # id inserit
```

Per obtenir registres:

```
>> paràmetres-de-cerca :=
bd
	consulta: ['SELECT * FROM book order by id desc limit 2'], 
	obtén: { :fila 
		Sortida escriu: fila id + [' '] + fila description + [': '] + fila price, salt-de-línia.
	}. # obtenció de files

```

## Sessions

Per a la persistència, podeu desar i obtenir dades d'un objecte de sessió.
Primer creeu un **Document-Web** nou. L'objecte Document-Web uneix
la petició, les capçaleres, l'HTML i la sessió. Això és perquè, cada vegada que
visiteu un lloc web amb el navegador, només veieu l'HTML. Però el
Document-Web sencer també consta de **capçaleres**. Per exemple,
la majoria de respostes HTTP inclouen una capçalera com Content-type:text/html per
indicar al navegador que les dades següents s'han de representar com a HTML
(i no, per exemple, descarregar-se com un fitxer). Les sessions són una manera de
desar dades de l'usuari entre peticions. Per fer el seguiment d'aquestes dades, cal
establir una galeta, i aquesta galeta també s'estableix mitjançant una capçalera. Per això
tot s'uneix al Document-Web (perquè és el document complet
que conté tant les capçaleres com l'HTML o altres dades).


```
# Primer creem una nova instància de Document-Web
>> web := Document-Web nou.

# Ara iniciem una sessió; això generarà una capçalera per a una galeta i
# crearà un fitxer per desar les vostres dades, associat a aquesta galeta
>> sessió := web iniciar-sessió.

# Ara podem tractar la sessió com un Diccionari
sessió userid: 123.
```

Per destruir la sessió (en tancar la sessió):

```
web destruir-sessió.
```

## Capçaleres

El Document-Web també permet establir altres capçaleres conegudes.
Per exemple, si voleu redirigir l'usuari a un altre URL:

```
web anar-a: ['/other.html'].
```

Per sota, aquesta ordre també genera la capçalera HTTP que s'envia
juntament amb les altres dades o l'HTML per indicar al navegador que vagi
a l'adreça de destinació especificada.

Per afegir una capçalera personalitzada:

```
web capçalera: ( 
	Capçalera-HTTP nou
	clau: ['Content-Length']
	valor: 400
).
```

Per mostrar una pàgina 404:

```
web no-trobat: ['Ups..'].
```


## Plantilles

El sistema de plantilles per defecte és molt senzill. No cal aprendre
una sintaxi de plantilles nova. A més, el motor de plantilles garanteix una separació real
entre la presentació i la lògica de negoci.

Per crear una plantilla a partir d'un fitxer:

```
>> tpl := web plantilla: ['templates/ux.tpl'].
```

El sistema de plantilles utilitza marcadors. 
Hi ha tres tipus de marcadors: marcadors de tall, marcadors d'enganxament i
marcadors d'espai. La idea bàsica és molt senzilla: retalleu
àrees identificades amb marcadors de tall i les podeu enganxar a
àrees identificades amb marcadors d'enganxament. Podeu injectar textos als
marcadors d'espai.

Així, per exemple, donada la plantilla següent, posem la
gemma al joier i afegim-hi una etiqueta de preu.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Ho podeu fer de la manera següent:

```
>> gem := tpl retallar: ['gem'], copia.
gem price: 99.
tpl enganxar: gem a: ['jewels'].
web emetre: tpl netejar.
```

L'última línia simplement envia la plantilla com a text al client
juntament amb les capçaleres HTTP necessàries.

Resultat:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

Per servir de manera segura fitxers pujats pels usuaris, podeu recórrer a passthru:

```
>> pujat := ['smile.gif'].
Server transmet: pujat prefix: ['/uploads/images/'].
Programa final.
```

Això servirà el contingut pujat per l'usuari amb el tipus
MIME adequat. Només s'admeten els tipus MIME de la llista blanca:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF i SVG.
Els fitxers SVG, ZIP i GZIP s'envien com a descàrrega, perquè un SVG
pot contenir scripts que altrament s'executarien al vostre domini.
Aquest mètode evita atacs TOCTOU, recorreguts de camins,
execució de codi maliciós (injecció), atacs amb enllaços simbòlics,
atacs DDoS (límit de fitxer = 50MB), atacs d'interceptació i
diversos altres problemes de seguretat.


## JSON

Per codificar un objecte com a JSON:

```
>> json := ( JSON jsonify: ( 
	Diccionari nou posa: ( 
		Llista nou ; 1 ; 2 ; 3
	) a: ['abc']
)).
```

Per descodificar JSON en un objecte xoscript:

```
>> dicc := ((JSON objecte: json) abc ? 1).
```

El JSON amb més de 500 nivells de niuament es rebutja com a no vàlid.

Per emetre directament un Diccionari com a json amb les capçaleres correctes:

```
web json: dicc.
```


## Expressions regulars

Podeu utilitzar expressions regulars creant un patró.
Per exemple, per trobar els href i els target dels hipervincles:

```
Patró nou: ['href="([^"]+)" target="([^"]+)"'].
```

Ara apliqueu el patró al text objectiu així:

```
model coincidència: assumpte fes: { :m :x .... }
```

Exemple complet:

```
>> assumpte := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> model := Patró nou: ['href="([^"]+)" target="([^"]+)"'].
>> resultat  := model coincidència: assumpte fes: { :m :x
	Sortida escriu: m, salt-de-línia.
	Sortida escriu: x, salt-de-línia.
	<- ['XXX'].
}.
Sortida escriu: resultat, salt-de-línia.
```

## Xarxa

Utilitzeu l'objecte Xarxa per fer una petició web.
L'objecte Xarxa sempre envia una petició POST, tret que envieu Res com a
dades; aleshores envia una petició GET.


```
Xarxa 
post: Res 
a: ['https://redbeanphp.com'].
```

## Xifratge

El connector de servidor inclou xifratge basat en XChaCha20 i Argon2.

Exemple:

```
>> xifrat := Caixa-forta xifra: ['hello'] clau: ['world'].
>> desxifrat := Caixa-forta xifra: xifrat clau: ['world'].
```

## Tokens

Per generar un token criptogràficament segur d'una longitud determinada:

```
>> elMeuToken := Caixa-forta token: 40.
```

Això generarà un token de 40 caràcters.

## Formatació

L'objecte Format permet formatar dades, per exemple omplir amb espais o
afegir zeros. Utilitza la sintaxi de printf.

```
>> fmt := Format nou: ['%06.0f'].
fmt aplica: 56. # dona 000056
```

Un format pot contenir una conversió i ha de correspondre al valor;
altrament obtindreu un error:

- `aplica:` amb un text: `%s`
- `aplica:` amb un número: `%f`, `%e`, `%g` o `%a`
- `aplica-enter:` amb un número: `%d`, `%i`, `%o`, `%u`, `%x` o `%c`

Els valors d'una petició són textos. Per formatar-ne un com a número,
convertiu-lo primer:

```
fmt aplica: (petició get: ['amount']) número.
```

## Codificadors

Hi ha diversos codificadors i descodificadors disponibles.
El codificador d'URL prepara un URL per utilitzar-lo en HTML com a enllaç:

```
Server url-codifica: ['https://example.com?a=6&b=1 2'].
```

Per injectar de manera segura l'entrada de l'usuari a l'HTML sense arriscar-vos a injeccions
XSS, utilitzeu sempre:

```
Server html-codifica: ['<inofensiu>'].
```

Tingueu en compte que el motor de plantilles sempre fa codificació html
si escriviu en un marcador d'espai. Així, si utilitzeu el sistema de plantilles,
no cal que utilitzeu això.

## Correu

Per enviar un correu, utilitzeu la biblioteca mailtools.xo.

Exemple:

```
Server inicialitzar.
Programa utilitza: ['mailtools.xo'].

>> correu-e := Correu-HTML nou.
>> img := correu-e adjuntar: ( Fitxer nou: ['myimage.png'] ).

correu-e
remitent: ['xo@xoscript.com'] nom: ['xo'],
destinatari: ( Llista nou ; ['xo2@xoscipt.com'] ),
assumpte: ['xoxo'],
cos-missatge: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), enviar.

```



## Enllaçament

Amb el missatge enllaça: podeu enllaçar una biblioteca externa al
programa mitjançant libffi. Per a més detalls, vegeu el capítol sobre ffi.


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

FFI es proporciona per plataforma o connector perquè
està lligat a l'arquitectura del sistema subjacent, cosa que el
nucli no ha de fer.
El connector de servidor ofereix una implementació conforme d'ffi/blobs.
Per defecte, el nucli es connecta a la plataforma de destinació
mitjançant stdin/stdout, serveis limitats d'E/S de fitxers i el shell (Programa sistema:).
La integració auxiliar la proporcionen els ffi/blobs mitjançant connectors
centrats en aplicacions, com el connector de servidor.

FFI vol dir Foreign Function Interface (interfície de funcions externes). Permet utilitzar funcionalitats escrites per altres en
llenguatges de programació diferents, proporcionades mitjançant fitxers DLL, SO o Dylib. Pot tractar-se
de funcions molt diverses, i amb aquest mètode hi ha disponible una gamma enorme de funcionalitats.
Comencem amb un exemple:

```
Server enllaça: (
 Llista nou ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Llista nou ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s allibera.
```

El resultat d'aquest codi és que veureu el següent a la línia d'ordres:
FFI has 3 letters.
Ara probablement esteu pensant: "És molt de codi per a una cosa tan senzilla."
Vull dir, no ho podríem resoldre simplement amb una ordre show de Gui? La resposta és un sí rotund!
Però això vol ser un exemple il·lustratiu.
FFI normalment s'utilitza per a tasques més complexes, però aquestes no fan bons
exemples, així que n'he triat un de trivial.

Els arguments del mètode enllaça:

- Argument #1: el fitxer DLL o SO que voleu utilitzar.
- Argument #2: la funció d'aquest fitxer que voleu enllaçar.
- Argument #3: una llista amb els noms dels tipus de dades dels arguments de la funció.
- Argument #4: el nom del tipus de retorn de la funció.
- Argument #5: el nom de l'objecte al qual voleu enllaçar aquesta funció (si no existeix, es crearà
automàticament).
- Argument #6: el missatge al qual s'ha d'enllaçar aquesta funció.

En l'exemple anterior, volem enllaçar la funció printf de libc.so. Podeu trobar els noms dels
tipus de dades a la documentació del programari al qual us enllaceu. Els tipus disponibles són:
void, pointer, float, double, int, uint, char, uchar, intX i uintX,
on X pot ser 8, 16, 32 o 64.

Aquests tipus fan referència al nombre de bytes necessaris per desar les dades. Per a printf, l'enllacem a un
objecte nou anomenat Printf i al missatge template:number:. Traduïu la funció
externa al dialecte XOScript abans d'utilitzar-la. El missatge template:number: espera un
buffer amb el text de plantilla com a primer paràmetre. Creem aquest buffer amb un objecte Blob, que
permet reservar memòria manualment. Sou responsables d'alliberar aquesta memòria després
amb el missatge allibera.

Podeu omplir un blob de memòria de diverses maneres. En el nostre exemple, l'omplim amb text, així que utilitzem el
missatge utf8: (UTF-8 és una codificació per convertir text en bytes). També podeu omplir un blob amb
bytes:, passant-hi una llista de valors de bytes. Per llegir el contingut d'un blob, utilitzeu de:longitud:.
Obtindreu els bytes com a llista. Fins i tot podeu crear una struct de C amb un Blob mitjançant el
missatge struct:, passant-hi una seqüència de tipus de C. Això pot ser necessari quan crideu una funció
de C d'una biblioteca de programari externa que espera un punter a una struct.

{warning}
Heu d'alliberar els blobs vosaltres mateixos.
El recol·lector d'escombraries no esborra els blobs.
{/warning}

Com que els blobs es poden intercanviar amb funcions externes de biblioteques,
el recol·lector d'escombraries no els pot alliberar automàticament (podrien continuar en ús per
funcions externes, o aquestes funcions externes podrien voler alliberar-los
elles mateixes). Per tant, cal que allibereu els blobs vosaltres mateixos si cal.

Per alliberar un blob, utilitzeu:

```
elMeuBlob allibera.
```

Per alliberar una struct, utilitzeu:

```
laMevaEstructura allibera-struct allibera.
```

Així, per a una struct, cal enviar dos missatges: allibera-struct i allibera per
desassignar el bloc de memòria.

@api_Blob_fficonnect
