# Grundlagen

{{messages}}


Willkommen bei XOScript
Das XOScript-Projekt hat zum Ziel, eine Skriptsprache zu schaffen, die einfach und überprüfbar ist.
Einfach bedeutet nicht unbedingt leicht.
Eine vertraute Programmiersprache ist vielleicht leichter zu benutzen als XOScript.
Einfachheit bedeutet hier etwas anderes:
sich ein vollständiges gedankliches Modell der Sprache und ihres Verhaltens bilden zu können.

XOScript ist so gestaltet, dass es in Ihren Kopf passt.
Die Grammatik und die Zahl der Konzepte sind bewusst klein gehalten.
Es gibt keine Klassen; Objekte können direkt erweitert werden.
Objekte werden als Referenz übergeben, Kopieren geschieht explizit,
und Funktionen haben einen einzigen Austrittspunkt.

Einige dieser Entscheidungen unterscheiden sich deutlich von gängigen Sprachen.
XOScript hat zum Beispiel kein Typsystem und verwendet dynamische Bindung (dynamic scoping).
Nachrichten, die nicht verarbeitet werden können, werden ignoriert, statt eine Ausnahme auszulösen.
Diese Entscheidungen haben Folgen und sollen Fehler nicht verhindern.
Sie sollen das zugrunde liegende Modell der Sprache klein und konsistent halten.

XOScript lässt sich außerdem lokalisieren. So können Geschäftsregeln
in einer natürlichen Sprache ausgedrückt und gegebenenfalls mit nicht-technischen Beteiligten geteilt werden.

Überprüfbarkeit bedeutet, dieselbe Philosophie auf die Implementierung anzuwenden.
Die Laufzeitumgebung ist in C geschrieben, mit einem kleinen handgeschriebenen Lexer, Parser und Tree Walker.
Die Standardbibliothek und die Laufzeitumgebung spiegeln weitgehend die Struktur der Sprache wider,
sodass die Beziehung zwischen XOScript-Code und seiner Implementierung relativ direkt ist.

Auch die Tests sind eng mit der Dokumentation verbunden.
Zu jeder Methode sollte es einen Test geben, der in das Handbuch übernommen werden kann.
So bleibt die Dokumentation mit der Implementierung im Einklang.

XOScript will nicht mit gängigen Sprachen in Sachen Funktionsumfang
oder Vertrautheit konkurrieren. Es verfolgt ein anderes Ziel:
eine Programmierumgebung, die ein Entwickler als Ganzes verstehen kann.

Die Hoffnung ist, dass eine kleine Sprache und eine kleine
Implementierung es praktikabel machen, Software zu verstehen,
vom Byte bis zum Objekt, von der Syntax bis zur Laufzeit, und Code mit
Zuversicht zu schreiben, weil man sowohl versteht, was im
Skript geschieht, als auch, was unter der Haube passiert.

Die Architektur einer xoscript-Serverinstallation
ist einfach und doch flexibel.

{{architecture.png}}

Um xoscript als Serversprache zu verwenden, müssen Sie das
Server-Plugin in einem Ordner namens /mods/server installieren.

Der Grund dafür ist, dass wir die Kernsprache gern von
serverspezifischen Funktionen trennen,
anders als zum Beispiel PHP oder Python. Sonst müssten wir jedem
ohne Zweck die komplette Küchenspüle mitliefern, und das wäre einfach albern.
Sie können auch weitere Module installieren, wenn Sie möchten. Das System ist sehr
flexibel.

Außerdem lassen sich manche Funktionen besser in der Skriptsprache
selbst implementieren, etwa Templates und Sitzungsverwaltung. Deshalb
liefern wir zusätzlich die Bibliotheken template.xo und webtools.xo zu Ihrer Bequemlichkeit mit.
Der Grund für all das ist, dass wir nicht wissen, wie Sie
xoscript verwenden möchten. Sie können es als serverseitige Skriptsprache verwenden,
aber auch für grafische Oberflächen, eingebettete Geräte oder einfach für Stapelverarbeitung.
Selbst wenn Sie es als serverseitige Skriptsprache verwenden (was
derzeit einer der wichtigsten Anwendungsfälle ist), möchten Sie vielleicht trotzdem
eine andere Template-Engine oder eine andere Sitzungsverwaltung verwenden.
Wer sind wir, zu bestimmen, dass Sie unsere verwenden sollen?

Ein Vorteil unserer eigenen Template-Engine ist allerdings, dass
Sie keine zusätzliche Syntax lernen müssen, um Templates zu erstellen.
Die Standard-Template-Engine, die mit xoscript ausgeliefert wird, trennt
Darstellung und Logik zu 100 %. Statt einer speziellen
Template-Syntax verwendet sie einfach ein sehr flexibles System von Platzmarkierungen (Slots).
Weitere Informationen finden Sie im Kapitel Server.

Wenn Sie die Standard-Template-Engine oder
die Standard-Webtools nicht verwenden möchten, müssen Sie selbstverständlich
Ihre eigenen bereitstellen.

Wenn Sie Ihren Webserver in einem chroot, einem Jail oder einer anderen Art von Sandbox betreiben,
müssen Sie auch die Abhängigkeiten von xo in dieser Umgebung installieren. Welche
Bibliotheken Sie benötigen, sehen Sie mit ldd (siehe die Manpage von Linux oder BSD).
Wenn Sie Shell-Befehle in Ihren xo-Skripten verwenden möchten, kopieren Sie auch eine Shell
(etwa bash oder ksh) in diese Umgebung.

Wir möchten außerdem darauf hinweisen, dass wir Abwärtskompatibilität sehr ernst nehmen.
Es gibt sogar eine spezielle Funktion für Abwärtskompatibilität namens
'version'. Grundsätzlich streben wir an, dass Ihr Code für immer läuft. Sie werden Ihren Code
also nie aktualisieren müssen, um mit neueren Versionen
von xoscript kompatibel zu bleiben. Unser Ziel lautet: einmal schreiben, für immer ausführen.

Der Rest dieses Handbuchs erklärt die Programmiersprache
xoscript im Detail. Server-Skripting wird im Kapitel
Server behandelt. Wenn Sie ein erfahrener Softwareentwickler sind, möchten Sie
vielleicht einige Kapitel überspringen, weil manche davon etwas zu ausführlich sind oder
allgemeinen Programmierpraktiken sehr ähneln. Wer also
bereits Erfahrung mit mehreren anderen Programmiersprachen hat,
behandelt dieses Handbuch am besten als Nachschlagewerk.

## Installation unter Linux

Laden Sie apache2 und mariadb herunter:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Laden Sie xoscript herunter.
Ersetzen Sie X durch die richtige Versionsnummer!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Kopieren Sie die Dateien in das Webroot und nach /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Bearbeiten Sie Ihre apache2-Konfiguration:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Ersetzen Sie Virtualhost durch:

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

Erstellen Sie eine Testseite:

```
sudo nano /var/www/html/test.xo
```

und schreiben Sie ein kleines Testprogramm:

```
#!/bin/xo
Server initialisieren.
Programm verwenden: ['webtools.xo'].
>> web := Web-Dokument neu.
web ausgeben: ['Hello World'].
```

Erlauben Sie apache2, Ihr Programm über CGI auszuführen:

```
sudo chmod uog+x /var/www/html/test.xo
```

Starten Sie apache2 neu:

```
sudo systemctl restart apache2
```

Rufen Sie Ihre Testseite im Browser auf:

```
http://localhost/test.xo
```

Sie sollten Folgendes sehen:

```
Hello World
```


## Installation unter OpenBSD

Bearbeiten Sie /etc/httpd.conf und fügen Sie hinzu:


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

Wenn Sie SSL verwenden möchten:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Um den Schlüsselaustausch gegen Quantencomputer zu schützen,
wählen Sie die mlkem-Cipher:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Fügen Sie das xo-Binary und die Mods sowie alle Abhängigkeiten in das
chroot ein (ermitteln Sie diese mit ldd).

## Beispiele ausführen


So führen Sie eines der Beispielprogramme aus dem Paket aus:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Zum Beispiel, um das FizzBuzz-Beispiel unter Linux auszuführen:

```
./example.sh fizzbuzz Linux
```

Um dasselbe Beispiel unter OpenBSD auszuführen:

```
./example.sh fizzbuzz OBSD
```

Um das Beispiel mit einem sauberen Build auszuführen:

```
./example.sh fizzbuzz OBSD clean
```

## Unit-Tests

So führen Sie die Unit-Tests aus:

```
./runtests.sh
```

So führen Sie die Unit-Tests ohne Build aus (nur testen):

```
./runtests.sh nobuild
```

## Build

So bauen Sie aus dem Quellcode unter Linux:

```
make clean
ISO="en" make
```

Unter OpenBSD:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

So bauen Sie das Server-Plugin unter Linux:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

So bauen Sie das Server-Plugin unter OpenBSD:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Hallo Welt

Nachdem die Datei auf Ihren Computer übertragen wurde, können Sie sie entpacken
und xo mit folgendem Befehl starten:

```
xo
```

Um ein XOScript auszuführen, speichern Sie das Programm als Datei mit der Endung -xo
(optional). Geben Sie außerdem den Dateinamen Ihres Programms
nach dem XOScript-Befehl an:

```
xo myprogram.xo
```

Wenn Sie einen XOScript-Befehl mit Ihrer Programmdatei als
Parameter ausführen, liest xo Ihre Programmdatei und führt sie aus.

{{note}}
Sie können Ihr Programm auch starten, indem Sie es auf das xo-Symbol ziehen.
{{/note}}

{{warning}}
Auf manchen Systemen müssen Sie xo vorher erlauben, dynamische
Bibliotheken zu laden.
{{/warning}}

Die Tradition verlangt, dass das erste Programm in einer neuen Programmiersprache
eine Art Gruß an die Welt ist. In XOScript sieht ein solches
**Hallo Welt**-Programm so aus:

@test598

Wenn dieser Text in einer Datei gespeichert wird, z. B. hello.xo, kann er
folgendermaßen ausgeführt werden: .

xo hello.xo

Hallo Welt


Die Ausgabe des Programms sehen Sie im oben gezeigten schwarzen Fenster.
In diesem Handbuch wird durchgehend dieselbe Darstellung verwendet, um
die Ausgabe zu zeigen.

{{note}}
Ausgabe wird mit einem großen A geschrieben.
Im Allgemeinen beginnen Objekte mit einem Großbuchstaben,
es sei denn, sie dienen als Instanz (haben keine eigenen
Methoden, nur Daten). Das entspricht den Konventionen
für Klassen und Instanzen in anderen Programmiersprachen.
{{/note}}


## Syntax

XOScript ist eine *rein* *objektorientierte* Programmiersprache. Das bedeutet,
dass xoscript alles als Objekt betrachtet; es gibt daher
keine anderen *Datentypen*. Im Wesentlichen gibt es drei grundlegende Routinehandlungen
in einem Programm, das in XOScript geschrieben ist: *Zuweisen*, *Nachrichten senden*
und *Antworten*. Der Austausch von Nachrichten zwischen Objekten ist der Kern eines
XOScript-Programms. Die drei einzelnen Routinehandlungen werden
unten veranschaulicht:


Handlung        | Beispiel
--------------- | --------
zuweisen        |  \>\> x := 1. 
unäre Nachrichten | x gerade?.
binäre Nachricht | 1 + 2.
Schlüsselwortnachricht | x von: 0 länge: 10.
antworten       | <- antwort.  


Dieses Kapitel vermittelt Ihnen einen allgemeinen Eindruck von der Sprache XOScript
und beschreibt ihre Grundprinzipien. XOScript ist eine kleine Sprache und
beruht auf drei Handlungen (siehe Abbildung), die sich in
etwa sechs Grammatikregeln übersetzen. Mehr braucht es nicht, um die
Sprache zu beherrschen.

Keine Sorge, wenn Ihnen nicht sofort alles klar ist: Alle Bausteine
werden im nächsten Kapitel (3) behandelt, und die Grundregeln werden
wiederholt. Das aktuelle Kapitel dient jedoch hauptsächlich als allgemeine
Einführung in die Sprache. Die Grundprinzipien werden kurz
erklärt und mit mehreren passenden Beispielen veranschaulicht. Fehlende
Details werden zu einem späteren Zeitpunkt erläutert.

Kommentare beginnen in XOScript mit dem Zeichen \#. Die folgende Zeile
wird also ignoriert:

```
# this is just a comment
```

## Variablen

Um eine Variable zuzuweisen,
verwenden Sie das Symbol für die Variablendeklaration: >>. Der Name einer
Variable darf alle Zeichen enthalten außer: <-, :=, Leerzeichen,
Punkten, Kommas, Doppelpunkten, Anführungszeichen [' '] und Klammern ().
Außerdem darf eine Variable nicht aus mehreren Zeilen bestehen. Beachten Sie,
dass eine Variable nicht mit einer Zahl oder einem Minuszeichen beginnen darf.

Dies sind Beispiele für gültige Variablen:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dollar'].
>> +plus := Ja.
>> user-password := ['Pssst!'].
```

Ungültige Variablen sind zum Beispiel:


```
>> -123 := ['negative number'].
>> password of user := ['Classified'].
>> password.of:user := ['Classified'].
>> ,x := 10.
```

{{note}}
Sie müssen in einem Textliteral kein Zeichen
maskieren (auch keine Anführungszeichen,
doppelten Anführungszeichen oder Textbegrenzer),
solange es für den Lexer nicht
zu Mehrdeutigkeiten führt.
{{/note}}

Nachdem eine Variable deklariert wurde, kann sie frei verwendet werden. Das bedeutet,
dass das Deklarationssymbol nur beim ersten Gebrauch der Variable
(der Deklaration) nötig ist.

Genauer gesagt: Sie können Ihrer Variable nicht einfach so einen Wert zuweisen
*(x := 2)*, sondern müssen die Variable zuerst deklarieren *(\>\>
x := 2)*. Nach der Deklaration dürfen Sie ihren Wert jedoch
ohne das Deklarationssymbol ändern *(\>\> x := 2. x := 3.)*.

Beachten Sie, dass einer Variable bei der Deklaration zwingend ein Wert
zugewiesen werden muss. Anders als in anderen Programmiersprachen dürfen Sie
keine Variable ohne Wert deklarieren. Jede Variable muss ausdrücklich
an einen Anfangswert gebunden werden. Sie können die Variable aber
ruhig mit dem Objekt **Nichts** initialisieren. In diesem Fall kann die Variable
als leer betrachtet werden *(\>\> x := Nichts.)*. Kurz gesagt: Eine
Variable ohne Anfangswert zu deklarieren ist nicht erlaubt. Also ist

```
>> x.
```

ungültig und führt zu einer Fehlermeldung.

{{note}}
xoscript verwendet dynamische Bindung von Variablen;
Einzelheiten finden Sie im Kapitel Funktionen.
{{/note}}


## Literale

XOScript betrachtet alles als Objekt, also alle Zahlen, Texte
und Codefragmente. Zahlen wie 1, 2, 100, -999 und 1,234 sind
Zahl-Objekte. Alle Texte zwischen einfachen Anführungszeichen sind Text-Objekte.
Alle Codefragmente, die zwischen geschweiften Klammern {...} stehen, sind
Funktion-Objekte.

Literal         | Wurzelobjekt | Beispiel
--------------- | ------------ | ----------
Zahlen          | Zahl         | 1,2,3... 
Texte           | Text         | \['hallo'\]
Funktion        | Funktion     | { 1 + 2. }.
                
     
Objekte wie Zahlen und Texte haben ihren Ursprung immer in einem Wurzelobjekt.
So stammen zum Beispiel alle Zahlen vom Objekt **Zahl** ab. Alle
Texte stammen von **Text** ab und alle Codefragmente von **Funktion**. Diese
Objekte wiederum stammen alle von **Objekt** ab, das tatsächlich das
Wurzelobjekt aller Objekte ist.


## Nachrichten

Programmieren in XOScript bedeutet im Grunde,
Nachrichten an Objekte zu senden. Die allgemeine Schreibweise, um eine Nachricht an
ein Objekt zu senden, lautet:

```
<object> <message>
```

Um zum Beispiel herauszufinden, ob die Zahl **2** gerade ist, wird
die Nachricht **gerade?** an das Objekt **2** gesendet:

```
2 gerade?
```

Die Antwort lautet **Ja** (wiederum ein Objekt). Unbekannte Nachrichten werden
von Objekten in der Regel ignoriert; es tritt also kein Fehler auf. Manche Objekte (z. B.
Zahlen oder Texte) reagieren auf eine unbekannte Nachricht auf eine vordefinierte Weise
(mehr dazu später).

Ein Objekt kann drei Arten von Nachrichten empfangen.

Art             | Anzahl der Argumente
--------------- | -------------------
Unär            | 0      
Binär           | 1     
Schlüsselwort   | 1+    


Erstens gibt es **unäre
Nachrichten** (siehe Beispiel oben), die keine Argumente haben. Zweitens
gibt es **Schlüsselwortnachrichten**, die ein oder mehrere Argumente haben,
zum Beispiel:

```
>> x := Zahl zwischen: 1 und: 10.
```

In diesem Fall wird die Nachricht **zwischen:und:** an **Zahl** gesendet, das
Wurzelobjekt aller Zahlen. Das Ergebnis ist eine Zufallszahl
zwischen 1 und 10. Schließlich gibt es **binäre Nachrichten**, die
nur aus einem Zeichen bestehen und ein Argument haben:

```
2 + 3
```

Das sieht aus wie eine Rechenaufgabe, ist aber eigentlich nur eine weitere Nachricht. Die
Nachricht **+** wird an **2** gesendet, mit dem Argument **3**, und liefert
die Antwort **5**. Binäre Nachrichten dürfen ohne Doppelpunkt geschrieben werden.

Binäre Nachrichten können verkettet werden:

```
>> x := 3 + 2 - 1.
```

In diesem Fragment wird zuerst **+ 2** an das **Zahl**-Objekt **3** gesendet, was
das Zahl-Objekt **5** ergibt, woraufhin **-1** an diese
Zahl gesendet wird. Aufmerksamen Lesern fällt zu Recht die Abweichung auf, die
dieses Protokoll gegenüber der üblichen mathematischen Rangfolge der
Operatoren zeigt. XOScript ignoriert die mathematische Rangfolge zugunsten
der Konsistenz seines Nachrichtensystems. Daher ergibt die Rechnung:

```
2 + 3 * 5 = 25
```

nicht 17.

Das ist so gewollt. Mit Klammern lässt sich die Reihenfolge ändern:

```
2 + (3 * 5) = 17
```

Die meisten Objekte geben als Antwort auf eine Nachricht sich selbst
zurück. Das ist praktisch, denn so lässt sich der Dialog mit diesem
Objekt fortsetzen, indem man ihm eine weitere Nachricht sendet:

```
Ausgabe schreiben:
[' hello '] trimmen großbuchstaben.
```

```
HELLO
```

Hier werden zwei Nachrichten an das **Text**-Objekt gesendet: **trimmen**, gefolgt
von **großbuchstaben**.

Im folgenden Fragment ist ein Komma nötig, um anzuzeigen,
dass eine neue Nachricht folgt. Sonst kommt XOScript durcheinander.

```
Ausgabe schreiben: ['Hello!'], stopp.
```

Zuerst wird die Nachricht **schreiben:** an das Stiftsymbol gesendet, gefolgt von
**stopp**. Ohne das Komma würde XOScript annehmen, dass Sie
**stopp** an den **Text** **Hallo!** senden möchten, ein sinnloses Unterfangen.

Die Verarbeitungsreihenfolge der Nachrichten ist wie folgt: von links nach rechts;
zuerst die Nachrichten in Klammern, dann unäre Nachrichten. Danach
binäre Nachrichten und zum Schluss Schlüsselwortnachrichten. Siehe das Beispiel
unten:

```
Ausgabe schreiben: 0.5 gerundet + (2 - 1), stopp.
```

XOScript liest immer von links nach rechts: Zuerst wird die Nachricht **schreiben:**
an Ausgabe gesendet, gefolgt von der Nachricht **stopp**. Innerhalb des
Arguments selbst liest XOScript ebenfalls von links nach rechts, also zuerst **0.5 gerundet**,
dann **+**.

{{note}}
Die Nachricht stopp fügt dem Text ein Zeilenumbruchzeichen hinzu.
Der Name dieser Nachricht ist von Telegrafensystemen inspiriert.
In Telegrammen wurde oft
das Wort STOP verwendet, um das Ende eines Satzes zu markieren
(da Satzzeichen unzuverlässig oder teuer waren).
{{/note}}

Außerdem hat **gerundet** Vorrang vor **+**, weil es eine
**unäre Nachricht** ist. Wegen der Klammern wird **2 - 1** zuerst
berechnet, danach wird **1** zum Ergebnis von **0.5 gerundet** (1) addiert.

Der gesamte Vorgang ergibt das Ergebnis **2**, das auch als
Antwort ausgegeben wird. Nach dem Komma folgt die Nachricht stopp, die den Cursor
in eine neue Zeile setzt. Am besten versteht man die Verarbeitungsreihenfolge
von XOScript-Programmen natürlich durch Übung.

Bemerkenswert ist, dass in XOScript, anders als in vielen anderen Programmiersprachen,
Leerzeichen ein grundlegender Teil der Syntax sind. Besonders
bei binären Nachrichten können Leerzeichen für etwas
Verwirrung sorgen. Setzen Sie nach einer binären Nachricht immer ein Leerzeichen. Sie können
eine Zahl nicht direkt an die Nachricht anhängen, zum Beispiel ist

```
3 + 2
```

etwas anderes als

```
3 +2
```

Das erste Beispiel (**3 + 2**) sendet die
Nachricht **+** an die Zahl **3**, mit der Zahl **2** als Argument. Das
Ergebnis ist in diesem Fall **5**. Im zweiten Beispiel (**3 +2**)
wird die unäre Nachricht **+2** an die Zahl **3** gesendet. Je nach
Kontext kann das ein ganz anderes Ergebnis liefern.

## Nicht vorhandene Methoden

Wenn Sie eine Nachricht an ein Objekt senden, wird die Funktion aufgerufen, die
diesem Objekt unter diesem Nachrichtennamen zugeordnet wurde. Wenn Sie eine Nachricht senden,
die nicht verstanden wird, ignoriert das empfangende Objekt Ihre Nachricht
und gibt stattdessen eine Referenz auf sich selbst für die weitere Kommunikation zurück.
Das nennt man tolerante Nachrichtenübermittlung.

Beispiel:

```
Ausgabe schreiben: Objekt blah, stopp.
```

Das führt zu keinem Fehler. Es gibt einfach den Text **Objekt** aus.


## Kontrollfluss

In XOScript braucht man keine eigenen Grammatikregeln für *Schleifen* und
*Bedingungen*. Eine if-Anweisung ist einfach eine Nachricht **ja:** oder **nein:**
an ein **Ja**-Objekt oder ein **Nein**-Objekt:

```
2 gerade? ja: {
	Ausgabe schreiben: ['Two is an even number'], stopp.
}.
```
Im vorigen Beispiel wird die Nachricht **ja:** an **Ja** gesendet (die
Antwort auf die Frage: Ist 2 eine gerade Zahl?). Als Argument wird zusätzlich
ein Codefragment mitgesendet: ein **Funktion**-Objekt. Diese Funktion schreibt
auf den Bildschirm, dass 2 tatsächlich eine gerade Zahl ist.

Auch für eine *Schleife* braucht man keine eigenen Schreibregeln. Um
ein Codefragment dreimal auszuführen, senden Sie einfach **\*** mit dem Argument
**3** an diese **Funktion**:

@test5

In diesem Codefragment ist **i** der Index. Beim ersten Ausführen der Funktion
ist **i** also 0, beim nächsten Mal ist **i** = 1 und
so weiter.

Betrachten wir ein weiteres Beispiel. Soll eine Umrechnungstabelle
von *kJ* (Kilojoule) in *kcal* (Kilokalorien) in Schritten von 100 ausgegeben werden,
sieht die richtige Schreibweise so aus:

@test599

Hier wird die Nummer der aktuellen Zeile an den Parameter
**:line** übergeben. Am Anfang einer Funktion werden die Funktionsparameter
definiert. Nicht verwendete Parameter bleiben leer (**Nichts**). Parameter stehen
immer am Anfang der Funktion, direkt nach der öffnenden
geschweiften Klammer, und beginnen mit einem Doppelpunkt.

Die Nachricht **solange:** ist eine Kombination aus einer *Schleife* und einer *Bedingung*.
Mit der Nachricht **solange:** lassen sich zwei Funktionen verknüpfen. Die empfangende Funktion
läuft so lange weiter, bis die Funktion nach dem Doppelpunkt ein negatives
Ergebnis liefert. Beispiel:

@test600

Im oben gezeigten Codefragment wird **1** zu **x** addiert, solange
**x** kleiner als **5** ist. Wenn das nicht mehr der Fall ist, antwortet die zweite
Funktion mit **Nein**, und folglich endet die Ausführung der
ersten Funktion. Beachten Sie, dass **x** außerhalb der
Funktion definiert wurde und eine globale Variable ist. Mehr über die Regeln zum Gültigkeitsbereich
erfahren Sie im Kapitel über Funktionen.

## Textinterpolation

Die *kJ/kcal*-Liste könnte ansprechender
gestaltet werden. Am liebsten sähe die Liste so aus:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Wenn Sie die gewünschte Ausgabe in eine Vorlage umwandeln, könnte die Schreibweise
so aussehen:

```
number1 kJ ➞ number2 kcal
```

Das bedeutet, dass **number1** für den kJ-Wert und **number2** für den
kcal-Wert steht. So funktioniert Textinterpolation in XOScript. Dafür
sind in XOScript keine eigenen Grammatikregeln nötig. Senden Sie einfach
das zu ersetzende Wort an den Text, mit dem Ersatztext
als Argument:

```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

Das Ergebnis:

```
100 kj ➞ 23.9 kcal
```

Diese Ersetzungsregel gilt für jede nicht definierte Nachricht, die ein
**text**-Objekt empfängt. Jede Nachricht, die das
**text**-Objekt nicht kennt, wird folgendermaßen interpretiert: *Ersetze den Nachrichtentext
durch den Text im Argument der Nachricht.* Sie können das
Programm wie folgt anpassen:


@test601


Um Unklarheiten darüber zu vermeiden, welche Nachricht als Platzhalter
verwendet werden kann und welche nicht, führen Sie am besten eine Vorlagenmarkierung wie &lt; &gt;
für die Textabschnitte in der Vorlage ein, die
ersetzt werden sollen.

## Rückgabewerte

Um auf eine Nachricht zu antworten, wird der Rückgabepfeil
(*<-*) verwendet. Das folgende Beispiel zeigt, wie man eine Aufgabe
zur Berechnung eines Prozentsatzes erstellt:

@test602

Nachdem die Aufgabe definiert und der Variable **percentage** zugewiesen wurde,
wird die Nachricht **anwenden:und:** mit den Argumenten **100** und **7** gesendet.

Dadurch wird die Aufgabe mit **100** und **7** ausgeführt, also 7 % von 100.
Mit dem Rückgabepfeil wird die Antwort von der Aufgabe an das
Hauptprogramm zurückgegeben.

## Erweitern

Dieser Code ist zwar gültig, hat aber einen Nachteil,
denn man muss sich die Reihenfolge der Argumente merken. Warum also
nicht so schreiben: *7 percent of: 100*? Das sähe viel
*natürlicher* aus. Um das zu ermöglichen, müssen wir das Elternobjekt von
**7** anpassen, also das Objekt **Zahl**, sodass es die
Nachricht **percent of:** versteht. Das erreicht man, indem man **wenn:tun:** an
das Objekt Zahl sendet, etwa so:

@test603

Da der Prozentsatz in diesem Fall die Zahl selbst ist, verweisen wir auf selbst,
das Schlüsselwort *selbst*. Kurz gesagt bedeutet das Symbol selbst: *Sende diese
Nachricht an mich selbst*.

# Objekte

{{messages}}

Neben dem Anpassen und Erweitern vorhandener Objekte können Sie auch
selbst neue Objekte erstellen, indem Sie einfach die Nachricht **neu** senden. Angenommen, Sie
möchten ein Rechnungsobjekt erstellen, das eine fortlaufende Nummerierung
erzwingt; in diesem Fall brauchen Sie zunächst ein Rechnungsobjekt.

Da jedes Objekt von einem anderen Objekt abstammt, das wiederum
letztlich vom Wurzelobjekt aller Objekte namens Objekt abstammt,
müssen Sie entscheiden, auf welchem dieser anderen Objekte Ihr
neues Objekt beruhen soll. Ihr neues Objekt erbt alle Eigenschaften des
Objekts, auf dem es beruht, also des Objekts, an das die Nachricht **neu**
ursprünglich gesendet wurde.

In diesem Beispiel ist ein eher neutrales Objekt vorzuziehen, eines ohne allzu
viele geerbte Eigenschaften. Das macht die Wahl leicht, denn in diesem
Fall kann das neue Objekt auf dem Wurzelobjekt selbst beruhen, also auf
**Objekt**. Die Schreibweise des geplanten Rechnungssystems sieht dann
so aus:

@test604

Die aktuelle Rechnungsnummer wird im Objekt gespeichert; deshalb steht
das Schlüsselwort **eigen** davor. Das nennt man eine *Eigenschaft*;
mehr dazu folgt.

Manche Unternehmen möchten das Jahr in die Rechnungsnummern
aufnehmen. In diesem Fall können Sie ein neues Rechnungsobjekt erstellen, das auf einem
früheren Rechnungsobjekt beruht, seinem Benutzer aber die Möglichkeit bietet,
ein bestimmtes Jahr anzugeben:

@test605

Die Implementierung der Nachricht **number** muss nicht
noch einmal geschrieben werden, denn sie wird vom zuvor geschriebenen **Rechnungsobjekt**
geerbt; alter Code kann also wiederverwendet werden. XOScript kennt keine Konzepte
wie Klassen und Verwandtes. Das bedeutet, dass Objekte
ausschließlich von anderen Objekten erben können, was auch als *prototypbasierte
Vererbung* bezeichnet wird.

Nun zurück zu den Eigenschaften. Auf Objekteigenschaften kann nur
*innerhalb der Objekthierarchie* zugegriffen werden; diese Eigenschaften
sind für andere Objekte also nicht sichtbar.

Anders als in anderen Programmiersprachen sind alle Eigenschaften von Objekten
ausschließlich für das Objekt sichtbar, das die Eigenschaft erstellt hat, sowie für
abgeleitete Objekte.

Eine häufig verwendete Technik besteht darin, ein Objekt als eine Art *Bauplan* zu verwenden,
wie es zum Beispiel bei den zuvor besprochenen Rechnungen der Fall ist.
Ein weiteres gutes Beispiel ist der **Point**. Angenommen, Sie erstellen ein
Computerprogramm, das mit Punkten auf einer Karte rechnet. Sie
können das Objekt **Point** mit den Eigenschaften einer
x-Koordinate und einer y-Koordinate entwickeln, die der
Außenwelt über Nachrichten zur Verfügung gestellt werden:

@test606

Die Nachricht **=** vergleicht die beiden Punkte mit Hilfe der Nachricht **und:**. Der
erste Vergleich ergibt ein **Ja** oder ein **Nein**. Das sind boolesche
Objekte. Wenn Sie die Nachricht **und:** an ein Ja-Objekt senden und
das Argumentobjekt nach dem Doppelpunkt ebenfalls **Ja** ist, erhalten Sie
als Antwort wiederum **Ja**. Wenn eines von beiden **Nein** ist, erhalten Sie
die Antwort **Nein**. Beachten Sie, dass ein Punkt die Koordinaten des
anderen nicht lesen kann. Man muss dem anderen Punkt eine Nachricht senden, um
diese Daten zu erfragen: **x-coordinate** und **y-coordinate**. Schließlich sind,
wie bereits erklärt, Eigenschaften nur innerhalb
der Objektfamilie selbst abrufbar.

Beachten Sie, dass hier die Nachricht **=** verwendet wird, um den Vergleich der Punkte
durchzuführen. Ebenso gut hätte eine andere Nachricht verwendet werden können, etwa
**is:** oder **equal:**; die Wiederverwendung des Zeichens **=** erschien
in diesem Fall jedoch passend.

## Vererbung

Sie können zuvor geschriebenen Code wiederverwenden, um eine Hierarchie
von Objekten zu erstellen. Zum Beispiel:

```
>> Animal := Objekt neu.
>> Dog := Animal neu.
>> Poodle := Dog neu.
```

In diesem Fall erbt **Dog** das gesamte Verhalten und alle Eigenschaften
von **Animal**, und das Objekt **Animal** erbt wiederum das gesamte Verhalten von
**Objekt**, dem Wurzelobjekt aller Objekte.


## Überschreiben


Im folgenden Beispiel wird eine neue Art von Liste erstellt:
**Combination**, in der jedes Element garantiert eindeutig ist. Die
Funktionen der Liste werden durch Vererbung wiederverwendet:

@test607

Beachten Sie, wie das zweite **red** aus der Liste ausgeschlossen wird.

Gelegentlich kann es nötig sein, ein Verhalten eines Objekts zu überschreiben,
zum Beispiel, wenn beim Addieren von Zahlen Maßeinheiten
berücksichtigt werden müssen. Im folgenden Beispiel wird das Objekt **Size**
erstellt. Dieses Objekt gibt eine Zahl zurück, die beim Addieren
die Einheit der zu addierenden Zahl berücksichtigt. Das Objekt **Zahl**
prüft, ob es sich um *Zoll* oder *Fuß* handelt. Der Programmcode
könnte etwa so aussehen:

@test608

## Rekursion

Im vorigen Beispiel wird das Plus**zeichen** überschrieben. Beachten Sie,
dass die eigentliche Addition am Ende trotzdem noch ausgeführt werden muss; das
geschieht tatsächlich in der folgenden Zeile:

```
>> answer := selbst + (zahl x factor).
```

Woher weiß XOScript nun, dass sich dieses Plus**zeichen** auf
die ursprüngliche Logik der Addition bezieht? Eine andere Deutung
könnte zum Beispiel sein, dass XOScript immer wieder dieselbe Nachricht an dasselbe
Objekt sendet, was wiederum zu einer **Endlosschleife** führen würde. Das ist
offensichtlich nicht beabsichtigt. Sobald Sie einem Objekt eine Nachricht senden,
die genau denselben Code ausführen würde, erkennt XOScript,
dass in diesem Fall die darunterliegende, überschriebene Nachricht gemeint ist. Ihr
Programm ist also automatisch gegen diese Form von Endlosschleifen
geschützt. Wenn Sie jedoch tatsächlich dieselbe Funktion aus der
aktuellen Funktion heraus ausführen möchten, müssen Sie zuerst die Nachricht
**rekursiv** senden. In diesem Fall ist das Ergebnis eine Endlosschleife.
Es gibt jedoch sinnvolle Anwendungen für rekursive Aufgaben. Angenommen
zum Beispiel, Sie möchten die Fakultät einer gegebenen
Zahl berechnen. Fügen Sie in diesem Fall einfach die Nachricht **factorial** zu
Zahl hinzu:

@test609

Das verlangt nach Rekursion. Die Aufgabe, die mit der
Nachricht **factorial** verbunden ist, muss nämlich innerhalb dieser Funktion erneut ausgeführt werden.
Man muss also die Fakultätsfunktion aus der
Fakultätsfunktion selbst heraus aufrufen. In der Regel verhindert XOScript dieses Vorgehen
wegen der Gefahr, in einer Endlosschleife zu landen. Aus diesem Grund
ist es unerlässlich, der Nachricht das Wort **rekursiv** voranzustellen. Damit
teilen Sie XOScript mit, dass Sie tatsächlich
dieselbe Aufgabe ausführen möchten und sich nicht vertan haben.

## Klassenähnliche Objekte

Obwohl xoscript keine Klassen bietet, ist es trivial,
klassenähnliches Verhalten nachzuahmen. Überschreiben Sie einfach die Nachricht neu.

```
>> Animal := Objekt neu.
Animal wenn: ['neu'] tun: {
	<- selbst neu initialisieren.
}.

Animal wenn: ['initialisieren'] tun: {
	eigen sound := ['?'].
	eigen legs  := 4.
}.
```

Im obigen Codefragment erstellen wir ein Objekt namens Animal.
Dieses Objekt dient als *Bauplan* für alle möglichen Tiere
wie Hunde und Katzen. Das Elternobjekt Animal wird
mit großem A geschrieben, um anzuzeigen, dass es sich um ein klassenähnliches Objekt handelt.
Als Nächstes überschreiben wir die Nachricht neu, indem wir unsere eigene neu-Methode schreiben.
In diesem Fall sendet sie die Nachricht neu an selbst, gefolgt von der Nachricht
initialisieren. Da xoscript Rekursion standardmäßig blockiert, führt das nicht zu
einer Endlosschleife. Stattdessen wird die Nachricht neu an das Elternobjekt
(Objekt) gesendet, was eine neue Instanz von Animal ergibt. Wir erstellen also
ein neues Objekt auf Grundlage desselben Objekts, für das wir unsere neu-Methode erstellt haben.
Das ist völlig in Ordnung. Nun senden wir auch die Nachricht initialisieren; sie sorgt dafür,
dass das Objekt Animal Standardwerte für seine Eigenschaften hat. Standardmäßig
hat ein Tier 4 Beine, und sein Laut ist unbekannt (daher das Fragezeichen).
Um eine neue Instanz unseres Animal zu erstellen, könnten wir einfach schreiben:

```
>> a := Animal neu.
```

Jetzt erhalten wir eine neue Instanz von Animal mit 4 Beinen, unbekanntem Laut und
einer Methode initialisieren. Wie in anderen objektorientierten Sprachen können wir unser
Animal auch erweitern:

```
>> Dog := Animal neu.
Dog wenn: ['initialisieren'] tun: {
	selbst initialisieren.
	eigen sound := ['barks'].
}.
```

Das lässt sich leicht testen, indem wir eine Methode text hinzufügen:

```
Animal wenn: ['text'] tun: {
	<- eigen legs text + eigen sound.
}.
```

Fügen wir alles zusammen:

@test13


Ein häufiges Problem ist das Erstellen eines Objekts, das sich in einem bestimmten
Anfangszustand befindet. Angenommen, es soll ein Objekt **Rectangle** erstellt werden,
um Umfang und Fläche zu berechnen. Eine mögliche Schreibweise wäre:


```
>> Rectangle := Objekt neu.

Rectangle wenn: ['area'] tun: {
	<- eigen länge * eigen width.
}.
```

Offensichtlich ist das Festlegen von Länge und Breite eine Voraussetzung. Zu diesem
Zweck können die Nachrichten **länge:** und **width:** hinzugefügt werden:


```
Rectangle wenn: ['length:'] tun: { :länge
	eigen länge := länge.
}.

Rectangle wenn: ['width:'] tun: { :width
	eigen width := width.
}.

```

Dieses Rechteck kann dann so verwendet werden:


```
>> rectangle := Rectangle neu length: 2, width: 3.
Ausgabe schreiben: rectangle area.
```

Wird jedoch vergessen, Länge und Breite anfangs festzulegen,
tritt eine Fehlermeldung auf:

```
>> rectangle := Rectangle neu.
Ausgabe schreiben: rectangle area.
```

erzeugt den folgenden Fehler:

```
Schlüssel nicht gefunden:länge
```

Um dies zu verhindern, sollte ein Rechteck vorzugsweise
immer eine Anfangslänge und -breite haben, zum Beispiel 0. In diesem
Fall muss also die Nachricht **neu** **überschrieben** werden.

@test610

Wenn wir die Nachricht neu überschreiben, ahmen wir im Grunde eine **Klasse** nach.

Die Welt von XOScript ist voller unterschiedlicher Objekte, die
Ihrem Programm von Anfang an zur Verfügung stehen. In den nächsten Kapiteln
werden alle diese Kernobjekte besprochen.

## Schnappschüsse

Sie können ein Objekt (samt seinem aktuellen Zustand) auf der Festplatte speichern mit:

```
myobject save-as: ['saved.bin'].
```

Um das Objekt wieder von der Festplatte zu laden:

```
>> myobject := Objekt load-from: ['saved.bin'].
```

Schnappschüsse können verwendet werden, um einen bestimmten Zustand zu sichern oder die Leistung zu verbessern.
Beim Laden eines Schnappschusses entfallen Lexing, Parsing und das Einrichten der Anwendung.
Außerdem könnten Schnappschüsse künftig weitere Leistungsvorteile bringen,
etwa die Optimierung bestimmter Muster oder das Erkennen und
Optimieren häufig durchlaufener Pfade (hot paths).

{{warning}}
Schnappschüsse sind eine experimentelle Funktion; verwenden Sie sie nicht in der Produktion.
Um experimentelle Funktionen zu aktivieren, kompilieren Sie mit -D EXPERIMENTS.
{{/warning}}


@test712

# Das Objekt Nichts

{{messages}}

Das Objekt Nichts
steht für Leere, oder besser gesagt, für das Fehlen von Information.
Gelegentlich erhalten Sie dieses Objekt als Antwort auf eine Nachricht,
wenn das Ergebnis **nichts** ist. Die wichtigste Frage,
die Sie dem Objekt **Nichts** stellen können, lautet: **Nichts?**. Die
Antwort lautet immer **Ja**.

```
Ausgabe schreiben: Nichts Nichts?.
```

Ergebnis:

```
Ja
```

Jedes andere Objekt als **Nichts** antwortet mit **Nein**. Das
obige Codefragment mag etwas philosophisch wirken, doch das Objekt **Nichts**
hat durchaus äußerst praktische Anwendungen. Zum Beispiel erhalten Sie
das Objekt Nichts als Antwort, wenn Sie nach einem
Listenelement fragen, das nicht existiert. Sie können das Objekt Nichts auch verwenden,
wenn Sie eine Variable deklarieren, aber noch keinen Wert angeben möchten.
Stattdessen **weisen** Sie einfach den besonderen Wert **Nichts** **zu**. In
XOScript ist es nicht erlaubt, eine Variable ohne Wert zu deklarieren, etwa so:


```
>> wert.
```

Stattdessen müssen Sie Folgendes schreiben:

```
>> wert := Nichts.
```

@api_None_base

# Wahrheitswerte

{{messages}}

Anders als die meisten zum Zeitpunkt der Abfassung populären Programmiersprachen
kennt XOScript nur ein einziges Ja-Objekt und ein einziges Nein-Objekt.
Zur Verdeutlichung: Jedes Mal, wenn Sie **Ja** schreiben, bedeutet das nicht, dass
ein neues Objekt erstellt wurde. Stattdessen verwenden Sie immer eine Referenz. Das
heißt, wenn Sie Folgendes schreiben:

\>\> x := Ja.

verweist **x** auf das Objekt **Ja**. Bedingter Code und Schleifen
prüfen ebenfalls diese Referenz. In XOScript ist die Bedeutung von **Ja** und **Nein**
nicht festgelegt. Tatsächlich gerät ein XOScript-Programm durch eine
Anweisung wie diese ziemlich durcheinander:

Ja := Nein.

Das Ergebnis solcher Aktionen ist undefiniert, dennoch bleibt es eine gültige
Aktion und ist daher formal erlaubt. Außerdem gibt es ein Objekt Wahrheitswert,
das Wurzelobjekt von **Ja** und **Nein**, da beide
von diesem Wurzelobjekt abgeleitet sind. Das Objekt Wahrheitswert selbst hat jedoch
keinen praktischen Nutzen.

## Stolperfallen

Seien Sie vorsichtig beim Verwenden von **und:** und **oder:**

```
Ausgabe schreiben: (Nein or: Ja or: Ja), stopp.
Ausgabe schreiben: (Nein oder: Ja, oder: Ja), stopp.
```

ergibt

```
Nein
Ja
```
weil die Nachricht **oder:** nur 1 Argument annimmt. Die erste Zeile
sendet **oder:oder:** an Nein; diese Nachricht existiert nicht, also ignoriert das Objekt
die Nachricht und gibt sich selbst (Nein) zurück. Die zweite Zeile dagegen
sendet **oder:** gefolgt von einem weiteren **oder:** (mit Hilfe eines Verkettungssymbols, also eines Kommas: ,).


@api_Boolean_base

# Zahlen

{{messages}}

Jedes Mal, wenn Sie eine Zahl schreiben, zum Beispiel 9, -10 oder 3,12, wandelt
XOScript diese Zahlen im Hintergrund in ein **Zahl**-Objekt um. Sie
können diesem Zahl-Objekt Nachrichten senden, oder Sie können die Zahl
einer Variable zuweisen und anschließend Nachrichten senden:

```
10 gerade?

>> tenner := 10.
tenner gerade?

```

Beide Schreibweisen sind gültig. Das Objekt Zahl reagiert auf die folgenden
Nachrichten...

Die meisten dieser Nachrichten sind selbsterklärend und ermöglichen es Ihnen,
mathematische Operationen oder Vergleiche auszuführen.

{{note}}
Beachten Sie, dass Sie ≤ ≥ ≠ × und ÷ statt ihrer ASCII-Entsprechungen verwenden können.
Das ist Geschmackssache.
{{/note}}

Der Unterschied zwischen binären mathematischen Nachrichten (+) und
ihren Schlüsselwortvarianten (hinzufügen:) besteht darin, dass erstere
eine neue Zahl zurückgeben, nämlich das Ergebnis der Operation, während bei
letzteren das Objekt selbst verändert wird. Das zeigt das
folgende Beispiel:

@test597

Im obigen Beispiel gilt b = 4 und a = 3. Mit **hinzufügen: 2** wird der Wert
von a um 2 erhöht, während **+ 3** eine neue Zahl erzeugt, die
a + 3 entspricht. Dasselbe gilt für andere Rechenoperationen, z. B.
Multiplikationen. Mit dem Multiplikationszeichen erhalten Sie
ein neues Objekt als Antwort. Wenn Sie die Nachricht **multiplizieren-mit:** verwenden,
multiplizieren Sie die Zahl selbst.

Mit der Nachricht **zwischen:und:**, zum Beispiel in **Zahl
zwischen: X und: Y**, erhalten Sie eine Zahl zwischen X und Y. Auf diese
Weise lässt sich eine beliebige Zufallszahl erzeugen:

```
>> a := Zahl zwischen: 1 und: 10.
Ausgabe schreiben: a, stopp.
```

Seit Version 1.4 ist der eingebaute Zufallszahlengenerator von xoscript
nach unserem besten Wissen kryptografisch sicher.

Sie können einer Zahl eine **qualifikation** anhängen, zum Beispiel **6
Äpfel**. Jede Nachricht, die von einer
Zahl nicht erkannt wird, wird als Qualifikation betrachtet. Die Qualifikation
einer Zahl können Sie mit der Nachricht qualifikation abrufen:

Eine Qualifikation ist im Grunde ein Text-Objekt, das zusammen mit dem Zahl-Objekt
gespeichert wird. Die Qualifikation wird bei einer
**schreiben:**-Anweisung auch hinter der Zahl ausgegeben. Qualifikationen können zum Beispiel
verwendet werden, um Beträge in gemischten Währungen zu addieren. Beim Addieren der Beträge können Sie
die Qualifikationen abfragen. Das folgende Programmbeispiel veranschaulicht dieses
Prinzip anhand eines historischen Währungsrechners (da der Wechselkurs
dort einigermaßen stabil bleibt!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Texte

{{messages}}

Jedes Mal, wenn ein Text zwischen **eckige Klammern und Anführungszeichen** ['...'] gesetzt wird,
erstellt XOScript ein neues Text-Objekt für Sie. Achten Sie jedoch
darauf, die richtigen Anführungszeichen zu verwenden. Das Anführungszeichen am
Anfang des Textes unterscheidet sich von dem am Ende (so können Sie
das einfache Anführungszeichen verwenden, ohne es maskieren zu müssen).

## UTF8

Texte enthalten in xoscript normalerweise utf8-kodierten Text. Obwohl
es technisch möglich ist, binäre oder nicht-utf8-kodierte Inhalte in
einem Text zu haben, wird empfohlen, dafür Blobs zu verwenden. Blobs werden
vom Server-Plugin bereitgestellt (siehe Kapitel ffi).
Im Allgemeinen werden Blobs/ffi
pro Plugin/Plattform bereitgestellt, da sie an die Plattform
und Architektur gebunden sind (ffi/Blobs). Der Kern der Skriptsprache versucht,
so plattformunabhängig wie möglich zu bleiben.

## Typumwandlung

Mit den folgenden Nachrichten können Sie von jedem Objekt eine Kopie
mit einem anderen Typ erstellen:

Nachricht | Ergebnis
------- | ------
zahl    | Wandelt in eine Zahl um
text    | Wandelt in einen Text um
wahrheitswert | Wandelt in einen Wahrheitswert um
  
Es **gelten** die folgenden Regeln:

Nachricht | Nichts   | Wahrheitswert      | Zahl                  | Text      | Andere              
-------- | --------- | --------           | --------              | --------  | --------
wahrheitswert | Nein | n. z.              | 0→Nein sonst→Ja       | Ja        | Meist Ja
zahl     | 0         | Nein→0 Ja→1    | n. z.                     | ['n']→n | Meist 1
text     | ['Nichts'] | ['Nein']/['Ja']   | ['n']                 | n. z.     | Unterschiedlich

## Kopieren

Werte werden in XOScript immer **als Referenz** übergeben. In anderen Sprachen
hängt das vom Typ des Wertes ab; in XOScript gibt es nur einen Weg,
nämlich als Referenz. XOScript erstellt nie eine Kopie eines Wertes. Um ein Objekt zu kopieren,
müssen Sie die Nachricht **kopieren** senden.

@test611

Hier hätten Sie vielleicht erwartet, dass die Ausgabe Dolly statt
Donny lautet. Das ist jedoch nicht der Fall, da beide Namen auf dasselbe
Objekt verweisen. Bei einer Schleife passiert etwas Ähnliches:

@test612

Tatsächlich verwendet XOScript **immer** Referenzen; auch bei **:quantity**
verweist die oben gezeigte Schleife also auf das Element
in der Liste.

Um ein Objekt zu kopieren, müssen Sie diese Aktion
**ausdrücklich** angeben:

@test613

Wenn Sie die unäre Nachricht **kopieren** an einen Text senden, gibt das Objekt
eine Kopie desselben Text-Objekts zurück. Auf dieselbe Weise lassen sich Zahl-Objekte,
boolesche Objekte, Listen und Wörterbücher kopieren.

Sie können auch Ihre eigene Implementierung von kopieren definieren; das ist sogar
notwendig, wenn Sie eigene Objekte erstellen. Die Standardimplementierung
von kopieren für eine Liste erstellt eine flache Kopie, also eine
neue Liste mit denselben Elementen.

@test614

In diesem Fall wird 4 nur zur Kopie hinzugefügt.
Da die Kopie jedoch flach ist, sind die Objekte in beiden Listen
dieselben.

@test615

Wenn wir also an jeden Namen in der Kopie 2 anhängen, ist auch die
ursprüngliche Liste betroffen.

Um das zu beheben, müssen wir eine **tiefe Kopie** erstellen. Eine solche Kopieraktion
für eine Liste könnte so aufgebaut sein:

@test616

Beachten Sie auch die Nachricht rekursiv; diese Nachricht muss
vor der Nachricht kopieren gesendet werden.

Man sollte unbedingt bedenken, dass eine Kopie eines Objekts zwar
oft genauso aussieht wie das Original, aber tatsächlich
nie dasselbe ist. Das Wurzelobjekt definiert eine Nachricht **equal:**,
mit der sich die Identität von Objekten vergleichen lässt. Sehen Sie sich das
folgende Beispiel an:

@test617

## Implizite Umwandlung

XOScript verwendet **implizite Umwandlung**, um Objekte umzuwandeln. Um eine
Liste auf dem Bildschirm auszugeben, sendet XOScript zum Beispiel intern die Nachricht
*text* an die Liste. Das kann sehr nützlich sein, wenn
Sie eine Liste als kommagetrennte Liste ausgeben möchten. Die
Nachricht *text* kann überschrieben werden:

@test620

@api_String_base
@api_Format_base


## Server-Texte

Die folgenden Text-Funktionen werden vom
Server-Plugin hinzugefügt.

@api_String_server

# Funktionen

{{messages}}

Sie können Code zwischen { und } zusammenfassen; er wird dann zu einer Funktion.
In xoscript verwenden wir manchmal auch den Begriff Aufgabe oder einfach
Codeblock.

Sie können eine Funktion ausführen, indem Sie die Nachricht *starten* senden.


```
{ Ausgabe schreiben: 123, stopp. } starten.
```

Wenn Ihre Funktion Argumente annimmt, verwenden Sie **anwenden:**.

```
{ :a Ausgabe schreiben: a, stopp. } anwenden: a.
```

Siehe auch die Beispiele unten.
Wegen der einfachen Architektur kann eine Funktion nur
einen Rückgabepunkt haben. Um Mehraufwand oder übermäßige Verschachtelung von
Bedingungen zu vermeiden, können Sie eine Prozedur verwenden (das entspricht dem
Multiplikationszeichen mit dem Argument 1):

```
{
  (a = 1) ja: { x := 1. }, abbrechen.
  (a = 2) ja: { x := 2. }, abbrechen.
} prozedur.
```

So wird (a = 2) nicht ausgewertet, wenn a = 1 ist.
Außerdem brauchen Sie auf diese Weise keine verschachtelten ja-Nachrichten.
Wann immer Sie merken, dass Sie Bedingungen verschachteln, denken Sie
an die Nachricht prozedur. Sie kann Ihren Code
leichter lesbar machen.


Hier eine wichtige Stolperfalle:

```
{
	Nein nein: {
		Ausgabe schreiben: ['End the loop.'].
	}, abbrechen.
	
	Ausgabe schreiben: ['Dont show me.'].

} prozedur.

```

In diesem Fall wird der Text 'Dont show me' angezeigt,
weil **abbrechen** an Nein gesendet wird. Wenn Sie einen
Abbruch ausführen möchten, muss er als Nachricht an **Ja** gesendet werden.
 

```
{
	Nein nicht ja: {
		Ausgabe schreiben: ['End the loop.'].
	}, abbrechen.
	
	Ausgabe schreiben: ['Dont show me.'].

} prozedur.

```

Das funktioniert wie erwartet.

## Ausnahmen

Ausnahmen können so behandelt werden:

```
{ Task 1 } abfangen: { Task 2 }, starten.
```

Sie können in Ihrem Programm auch absichtlich einen Fehler auslösen und
damit den Behandlungsblock aktivieren. Dazu senden Sie die
Nachricht **fehler:** an die aktuelle Aufgabe, wie in der folgenden
Abbildung gezeigt:

```
{
diese-aufgabe fehler: ['Whoops!'].
} abfangen: { :mistake
Ausgabe schreiben: mistake.
}, starten.
```

## Werte einschleusen

XOScript bietet für Aufgaben die Möglichkeit, Werte einzuschleusen. Sehen Sie sich
die folgende Aufgabe an:

```
>> sending := {
	Newsletter an: eigen recipient.
}.
sending setzen: ['recipient']
wert: ['info@recipient.org'].
sending starten.
```


Diese Abbildung zeigt eine fiktive Aufgabe, die einen Newsletter
an eine E-Mail-Adresse bzw. einen **Empfänger** (recipient) sendet. Dieser Empfänger kann
von außen und vor dem Start der Aufgabe in die Aufgabe eingeschleust werden, indem man die
Nachricht **setzen:wert:** an die Aufgabe sendet. Dadurch wird der Wert von
**recipient** in der Aufgabe voreingestellt. Dieser Wert kann auch geändert
und die Aufgabe anschließend erneut ausgeführt werden. Das ist eine nützliche Methode beim Arbeiten mit
Task-Objekten.

## Leere Funktionen

Leere Aufgaben sind nicht erlaubt. Theoretisch sähe eine leere Aufgabe so
aus: **{}**, doch XOScript betrachtet das als Sprachfehler. Wenn Sie
eine leere Aufgabe deklarieren möchten, können Sie das Objekt Nichts verwenden:

```
>> task := Nichts.
```

Obwohl das keine echte Aufgabe ist, sondern ein Nichts-Objekt, kann trotzdem
eine Nachricht starten gesendet werden:

```
>> answer := task starten.
```

Tatsächlich ist das dasselbe wie:

```
>> answer := Nichts starten.
```

Da das Objekt **Nichts** die Nachricht **starten** nicht kennt,
gibt es sich selbst als Antwort zurück, und die Antwort ist wiederum **Nichts**.
Eine leere Aufgabe ist also gar nicht nötig. Dank der eleganten
Gestaltung der Programmiersprache XOScript können Sie dafür einfach das Objekt Nichts
verwenden.

## Dynamische Bindung

Wenn eine Funktion eine Variable braucht, sie aber nicht findet,
prüft sie die Variablen der Funktion, die sie **aufgerufen** hat,
und setzt die Suche entlang der Kette von Funktionen fort.
Dieser Suchvorgang läuft, bis die Variable gefunden ist.
Wird die Variable dann immer noch nicht gefunden, erscheint eine Fehlermeldung. Diese Art, nach einer
Variable zu suchen, nennt man **dynamische Bindung** (Dynamic Scoping).

Zur Veranschaulichung dieses Prinzips:

@test618

@api_Code_base

# Wurzelobjekt

{{messages}}

Das Objekt namens **Objekt** ist das Wurzelobjekt aller Objekte in
XOScript und stellt grundlegende Sprachfunktionen bereit.

Die am häufigsten gesendete Nachricht
ist **wenn:tun:**, die die Funktionalität eines Objekts erweitert. Diese
Nachricht wird vom Wurzelobjekt empfangen, das daraufhin die
angegebene Aufgabe mit der Nachricht verknüpft und so das abgeleitete
Objekt erweitert.

## Auffangmethoden

Wenn Sie eine Nachricht senden, die keiner
Methode des Objekts entspricht, wird sie normalerweise ignoriert. Sie können jedoch
sogenannte **magische Methoden** oder **Auffangmethoden** (catch-all) festlegen, die
aufgerufen werden, wenn das Objekt die Nachricht nicht versteht.

Es gibt 4 Auffangmethoden. Jede Nachricht passt
zu einer bestimmten Anzahl von Argumenten.

Auffangnachricht     | Anzahl der Argumente
-------------------- | -------------------
antworten:           | 0
antworten:und:       | 1
antworten:und:und:   | 2
antworten:und:und:und: | 3


@test619

## Programmatische Nachrichten

Statt eine Nachricht direkt an ein Objekt zu senden, kann sie auch
über eine Variable gesendet werden. Dazu verwenden Sie die Nachricht
**nachricht:argumente:**.

@test396

@api_Object_base

# Listen

{{messages}}

XOScript kennt zwei Arten von Sammlungen: *Listen* und *Wörterbücher*.
**Listen** sind Aufzählungen von Objekten in einer *festen Reihenfolge*. Wörterbücher haben
keine Reihenfolge, sondern ähneln eher einer Legende aus einem Schlüssel (oder Begriff) und dem
zugehörigen Wert. Listen sind vergleichbar mit Arrays (PHP, Java, C)
und Listen (Python). Wörterbücher sind vergleichbar mit assoziativen Arrays (PHP) oder
Dictionaries (Python) in anderen Programmiersprachen. Um eine
neue Liste zu erstellen, schreiben Sie:

```
>> fibonacci := Liste neu.
```

Diese leere Liste kann mit **anhängen:** gefüllt werden:

```
fibonacci anhängen: 0.
fibonacci anhängen: 1.
fibonacci anhängen: 1.
fibonacci anhängen: 2.
fibonacci anhängen: 3.
fibonacci anhängen: 5.
fibonacci anhängen: 8.
fibonacci anhängen: 13.
```

Wenn wir die Liste auf dem Bildschirm ausgeben:

```
Ausgabe schreiben: fibonacci, stopp.
```

sehen wir:

```
Liste ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

Statt anhängen können Sie auch ; verwenden, um einer Liste Elemente hinzuzufügen:


```
>> fibonacci := Liste neu ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Die Semikolons (;) sind alle binäre Nachrichten, die einen
Wert in die Liste einfügen.

## Verkettung

Angenommen, Sie haben eine Liste wie:

```
>> x := Liste neu ; 1 ; 2 ; 3.
```

Wenn Sie das erste und das letzte Element löschen möchten, würde Ihre
Nachricht so lauten:

```
x erstes-entnehmen letztes-entnehmen.
```

Leider funktioniert die vorige Schreibweise nicht richtig. Die
Nachricht **erstes-entnehmen** gibt das erste Element der Liste zurück, das
wiederum zum Empfänger der Nachricht **letztes-entnehmen** wird. Die
Nachricht **letztes-entnehmen** wird also nicht an **x** gesendet, sondern an 2. Eine
mögliche Lösung dieses Problems wäre, zwei getrennte
Sätze zu bilden, etwa:

```
x erstes-entnehmen.
x letztes-entnehmen.
```

Das ist jedoch ziemlich unpraktisch, besonders wenn Sie
mehr als zwei Elemente löschen müssen. Deshalb bietet XOScript für solche
Situationen eine alternative Nachrichtenstruktur. In
**alternativen** Nachrichtenstrukturen werden die Antworten der Objekte ignoriert,
und Sie erhalten immer wieder das empfangende Objekt als Antwort zurück.
Eine **alternative** Nachrichtenstruktur wird eingeleitet, indem man die
Nachricht **tun** an ein Objekt sendet, und die **alternative** Nachrichtenstruktur
kann beendet werden, indem man die Nachricht **erledigt** sendet. Im
gezeigten Beispiel ließe sich das so anwenden:

```
>> x := Liste neu ; 1 ; 2 ; 3.
x tun erstes-entnehmen letztes-entnehmen erledigt.
```

@api_List_collections

# Wörterbücher

{{messages}}

**Liste und Wörterbuch sind beide Sammlungen. Anders als eine
Liste hat ein Wörterbuch jedoch **keine** Reihenfolge. Ein weiterer Unterschied zwischen beiden
besteht darin, dass ein Wörterbuch aus Objektpaaren besteht. Ein Objekt dient als Eintrag (oder
Stichwort), um das andere Objekt zu finden. Ein gutes Beispiel für eine
solche Liste ist eine Preisliste, etwa:


```
>> menu := Wörterbuch neu
	setzen: ['£5'] auf: ['apple pie'],
	setzen: ['£6'] auf: ['carrot cake'],
	setzen: ['£3'] auf: ['fudge'].
```

Ähnlich wie bei einer Liste wird die Nachricht setzen:auf:
verwendet, um ein Objekt hinzuzufügen. Der Unterschied ist, dass anders als bei
einer Liste zwei Objekte miteinander verknüpft werden. Das erste Objekt ist, ähnlich
wie bei einer Liste, das Objekt, das Sie speichern. Das zweite
Objekt ist nicht seine Position in der Sammlung, sondern der **Eintrag**,
mit dem das erste Objekt später wieder abgerufen werden kann. Kurz
gesagt funktioniert ein Wörterbuch ein wenig wie ein echtes Wörterbuch: Über das Stichwort
findet man die Bedeutung. Um zum Beispiel aus der
oben genannten Liste den Preis eines Fudge abzurufen:

```
>> price := menu bei: ['fudge'].
```

Sie können auch die Kurzschreibweise verwenden:

```
>> price := menu ? ['fudge'].
```

Wenn die Einträge, unter denen Sie Objekte speichern, keine Leerzeichen enthalten
(und nicht mit anderen vordefinierten Nachrichten kollidieren),
kann auch die folgende Schreibweise verwendet werden:

```
>> menu := Wörterbuch neu
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Zweifellos liest sich die obige Schreibweise etwas natürlicher.
Um den Preis eines
Fudge abzufragen, kann die folgende vereinfachte Schreibweise verwendet werden:

```
>> price := menu fudge.
```

@api_Dict_collections

# Datei

{{messages}}

Das Objekt **Datei** bietet grundlegenden Zugriff auf das Dateisystem.
Mit diesem Objekt können Sie ganze Dateien auf einmal in eine Variable einlesen
oder Variablen auf einmal in Dateien schreiben. Zeilenweises Lesen
wird ebenfalls unterstützt. Das sind die häufigsten Datei-Ein-/Ausgabeoperationen
in einer Skriptsprache. Für fortgeschrittene Dateioperationen ist
FFI über das Server-Plugin oder ein separates IO-Plugin erforderlich.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Datum/Uhrzeit

{{messages}}

Für eine strukturierte Darstellung von Uhrzeit und Datum verwendet XOScript das
Objekt **Moment**. Wenn ein neues Moment-Objekt auf dem Bildschirm ausgegeben wird, werden
das aktuelle Datum und die aktuelle Uhrzeit angezeigt:

```
Ausgabe schreiben: Moment neu, stopp.
```

Das kann etwa Folgendes ergeben:

```
2020-10-10 12:16:39
```

Auch die einzelnen Zeitbestandteile lassen sich leicht auslesen. Wenn Sie
zum Beispiel nur das aktuelle Jahr wissen müssen, kann die Nachricht
**jahr** an den Moment gesendet werden; die Antwort ist dann ein
Zahl-Objekt, das nur das Jahr enthält:

```
>> m := Moment neu.
Ausgabe schreiben: m jahr, stopp.
```

@api_Moment_system

# Programm/StdOut

{{messages}}

Das Objekt Programm steht für die aktuell laufende Anwendung. Dieses Objekt
bietet Funktionen, um Systembefehle auszuführen, Unterprogramme einzubinden,
Argumente zu lesen und mehr. Alle systembezogenen Funktionen.

## StdOut

Ausgabe ist das Standardausgabeobjekt. Es hat im Wesentlichen zwei Methoden:
**schreiben:** und **stopp**. Die Nachricht schreiben: sendet einen Text
an stdout, die Nachricht stopp gibt ein Zeilenumbruchzeichen aus.
Statt **stopp** können Sie auch \\n verwenden.

Beispiel:

```
Ausgabe schreiben: ['Hello World'], stopp.
```

Ergebnis:

```
Hello World
```

## Module/Plugins

Die Welt von XOScript lässt sich durch neue Systemobjekte erweitern, indem man
Module installiert. Ein neues Systemobjekt kann der Welt von
XOScript hinzugefügt werden, indem man die Moduldatei (normalerweise eine Datei mit der Endung .so)
in den Ordner mods legt.

Wenn Sie eine Nachricht an das Objekt senden, das über das
Plugin-Modul bereitgestellt wird, lädt XOScript es automatisch.

Sie können Plugins auch selbst schreiben. Plugins werden in der
Programmiersprache C geschrieben. Ein Beispiel-Plugin finden Sie im
Quellcodepaket unter src/plugins/example.


## Reflexion

Es gibt verschiedene Möglichkeiten, das System
während der Programmausführung zu erkunden. XOScript bietet einige Methoden, um
festzustellen, welche Objekte vorhanden sind und auf welche Nachrichten diese Objekte
reagieren. Zunächst kann man jedes Objekt fragen, welchen **typ** es hat;
Typen sind in XOScript jedoch veränderbar und daher unzuverlässig.

Man kann das Objekt Programm auch fragen, ob ein
bestimmtes Objekt bereits im Programm vorhanden ist:

```
Programm Tool ja: { ... }.
```

Bei einem Objektnamen,
der nur aus einem einzigen Zeichen besteht, verwendet man am besten die
folgende Schreibweise, um Verwechslungen zu vermeiden:

```
Programm finden: ['X'], ja: { ... }.
```

Neben Fragen nach Objekten kann man das
Objekt Programm ebenso nach Nachrichten fragen. Man kann zum Beispiel fragen, ob das
Objekt **Zahl** die Nachricht **zwischen:und:** kennt, und zwar so,
wie unten gezeigt:

```
Programm Number: ['between:and:'], stopp.
```

@api_Program_system

# Server

{{messages}}

Das Server-Plugin von xoscript bietet Funktionen, um
serverseitige Anwendungen zu erstellen. Um das Server-Plugin
zu laden, verwenden Sie:

```
Server initialisieren.
```

Zur Bequemlichkeit wird außerdem empfohlen,
die Dateien webtools.xo und template.xo zu laden.

```
Programm verwenden: ['webtools.xo'].
Programm verwenden: ['template.xo'].

```

## Servereinstellungen

Sie können die folgenden Servereinstellungen festlegen:

```
	# default values are given
	# so if you do not set anything these
	# values are used...

	Programm 
	einstellung: ['max-postfields']
	wert: 40.

	Programm 
	einstellung: ['max-contentlength']
	wert: 2000000. # 2MB

	Programm 
	einstellung: ['max-time']
	wert: 5000. # 5sec

```

## Hallo Welt

Hier ist ein sehr einfaches Webprogramm, das Sie mit einem
Standard-CGI-Server wie Apache2, NGINX, OpenHTTPD oder jedem anderen
bekannten Server verwenden können.

```
#!/bin/xo

Server initialisieren.
Programm verwenden: ['webtools.xo'].

>> web-document := Web-Dokument neu.

web-document ausgeben: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Wenn Sie das Objekt Web-Dokument nicht verwenden möchten, ist das in Ordnung,
dann müssen Sie die HTTP-Header aber selbst schreiben:

```
#!/bin/xo
Ausgabe schreiben: ['Content-type: text/html; charset=utf-8 \n\n'], stopp.
Ausgabe schreiben: ['hello world!'], stopp.
``` 

## Anfrage

Mit dem Objekt HTTP-Anfrage können GET-, POST-, COOKIE- und
UPLOAD-Daten abgerufen werden:

```
>> anfrage  := HTTP-Anfrage neu.
>> search   := anfrage get: ['search']. # ?search=books
>> password := anfrage post: ['password']. # from form
>> selected := anfrage get-liste: ['sel[]']. #?sel[]=1&sel[]=2
>> selected := anfrage post-liste: ['sel[]'].
>> cookie   := anfrage cookie: ['session-id'].
>> upload   := anfrage upload: ['file'].
>> temppath := upload ? 1.
>> filename := upload ? 0.
```

## Maxpost/length

Standardmäßig sind höchstens 40 POST-Felder erlaubt, und die maximale Inhaltslänge
beträgt 2 MB. Um das pro Skript anders zu konfigurieren:

```
Programm einstellung: ['max-contentlength'] wert: 1. 
Programm einstellung: ['max-postfields'] wert: 1. 
```

{{note}}
Wenn die Inhaltslänge das Maximum überschreitet, wird der
Prozess beendet, weil wir nicht mehr sicher sein können,
dass die Nutzdaten unbedenklich sind.
{{/note}}

Das Zeitlimit maxtime bestimmt die maximale Zeit in ms
zum Lesen von stdin/Postdaten.

```
Programm einstellung: ['max-time'] wert: 5000. # 5sec
```

Das gilt nur für das Einlesen der POST-Daten und verhindert
Slowloris-artige Angriffe. Wenn Sie die Ausführungszeit
einer beliebigen Operation wirklich begrenzen möchten, verwenden Sie Programm alarm:.

## Datenbank

Mit dem Objekt Database können Abfragen an MariaDB/MySQL gestellt werden.
Um eine Verbindung zu einer Datenbank herzustellen:

```
>> db := Maria-DB neu host: ['localhost'],
	benutzername: ['xo'],
	passwort: ['pass123'],
	datenbankname: ['xobase'],
	verbinden.

```

Um einen Datensatz einzufügen:

```
>> suchparameter := db abfrage: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parameter: ( Liste neu ; ['abc'] ; 12.35 ; 6 ). # parameterized queries

{  suchparameter ausführen. db bestätigen. }
abfangen: { :e db zurückrollen.  }, starten.
```

Beachten Sie, dass xoscript *ausschließlich* mit Transaktionen arbeitet und nie automatisch bestätigt (autocommit).
Wenn autocommit nicht deaktiviert werden kann, erhalten Sie einen Verbindungsfehler.
Verwenden Sie für Abfragen immer Parameterbindung und fügen Sie Benutzereingaben nie direkt
in das SQL ein.

Die eingefügte ID erhalten Sie so:

```
Ausgabe schreiben: ['INSERTED: '] + suchparameter insert-id, stopp. # insert id
```

Um Datensätze abzurufen:

```
>> suchparameter :=
db
	abfrage: ['SELECT * FROM book order by id desc limit 2'], 
	abrufen: { :row 
		Ausgabe schreiben: row id + [' '] + row description + [': '] + row price, stopp.
	}. # fetching rows

```

## Sitzungen

Für die Persistenz können Sie Daten in einem Sitzungsobjekt speichern und daraus abrufen.
Erstellen Sie zuerst ein neues **Web-Dokument**. Das Objekt Web-Dokument verbindet
Anfrage, Header, HTML und Sitzung. Der Grund: Wenn Sie
mit Ihrem Browser eine Website besuchen, sehen Sie nur das HTML. Das
gesamte Web-Dokument besteht aber auch aus **Headern**. Zum Beispiel
enthalten die meisten HTTP-Antworten einen Header wie Content-type:text/html, um
dem Browser mitzuteilen, dass die folgenden Daten als HTML dargestellt werden sollen
(und nicht etwa wie eine Datei heruntergeladen). Sitzungen sind eine Möglichkeit,
Benutzerdaten zwischen Anfragen zu speichern. Um diese Daten zuzuordnen, müssen wir
ein Cookie setzen, und auch dieses Cookie wird über einen Header gesetzt. Deshalb
kommt alles im Web-Dokument zusammen (denn es ist das vollständige
Dokument, das sowohl Header als auch HTML oder andere Daten enthält).


```
# First we make a new Web Document instance
>> web := Web-Dokument neu.

# Now we start a session, this will generate a Header for a cookie and
# create a file to store your data, associated with that cookie
>> session := web sitzung-starten.

# Now we can treat session like a dict
session userid: 123.
```

Um die Sitzung zu beenden (beim Abmelden):

```
web sitzung-beenden.
```

## Header

Mit dem Web-Dokument können Sie auch andere bekannte Header setzen.
Wenn Sie den Benutzer zum Beispiel auf eine andere URL umleiten möchten:

```
web gehe-zu: ['/other.html'].
```

Im Hintergrund erzeugt dieser Befehl auch den HTTP-Header, der
zusammen mit Ihren übrigen Daten oder Ihrem HTML gesendet wird und den Browser anweist,
zur angegebenen Zieladresse zu wechseln.

Um einen eigenen Header hinzuzufügen:

```
web kopfzeile: ( 
	HTTP-Kopfzeile neu
	schlüssel: ['Content-Length']
	wert: 400
).
```

Um eine 404-Seite anzuzeigen:

```
web nicht-gefunden: ['OOps..'].
```


## Vorlagen

Das Standard-Vorlagensystem ist sehr einfach. Sie müssen keine
neue Vorlagensyntax lernen. Außerdem sorgt die Template-Engine für eine echte Trennung
von Darstellung und Geschäftslogik.

Um eine Vorlage aus einer Datei zu erstellen:

```
>> tpl := web vorlage: ['templates/ux.tpl'].
```

Das Vorlagensystem verwendet Markierungen.
Es gibt drei Arten von Markierungen: Ausschneidemarkierungen, Einfügemarkierungen und
Platzmarkierungen (Slots). Die Grundidee ist wirklich einfach: Sie schneiden
Bereiche aus, die durch Ausschneidemarkierungen gekennzeichnet sind, und können sie an
Stellen einfügen, die durch Einfügemarkierungen gekennzeichnet sind. In Platzmarkierungen
können Sie Texte einsetzen.

Nehmen wir zum Beispiel die folgende Vorlage: Legen wir den
Edelstein in das Schmuckkästchen und fügen wir ein Preisschild hinzu.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Das geht so:

```
>> gem := tpl ausschneiden: ['gem'], kopieren.
gem price: 99.
tpl einfügen: gem auf: ['jewels'].
web ausgeben: tpl säubern.
```

Die letzte Zeile sendet die Vorlage einfach als Text an den Client,
zusammen mit den erforderlichen HTTP-Headern.

Ergebnis:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

Um von Benutzern hochgeladene Dateien sicher auszuliefern, können Sie sich auf passthru verlassen:

```
>> uploaded := ['smile.gif'].
Server durchreichen: uploaded präfix: ['/uploads/images/'].
Programm ende.
```

Dadurch werden die vom Benutzer hochgeladenen Inhalte mit dem passenden
MIME-Typ ausgeliefert. Nur MIME-Typen auf der Positivliste werden unterstützt:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF und SVG.
SVG-, ZIP- und GZIP-Dateien werden als Download gesendet, weil ein SVG
Skripte enthalten kann, die sonst auf Ihrer Domain laufen würden.
Diese Methode verhindert TOCTOU-Angriffe, Path Traversal,
die Ausführung von Schadcode (Injection), Symlink-Angriffe,
DDoS-Angriffe (Dateilimit = 50 MB), Sniffing-Angriffe und
verschiedene andere Sicherheitsprobleme.


## JSON

Um ein Objekt als JSON zu kodieren:

```
>> json := ( JSON jsonify: ( 
	Wörterbuch neu setzen: ( 
		Liste neu ; 1 ; 2 ; 3
	) auf: ['abc']
)).
```

Um JSON in ein xoscript-Objekt zu dekodieren:

```
>> dict := ((JSON objekt: json) abc ? 1).
```

JSON mit mehr als 500 Verschachtelungsebenen wird als ungültig abgelehnt.

Um ein Wörterbuch direkt mit den richtigen Headern als JSON auszugeben:

```
web json: dict.
```


## Regex

Sie können reguläre Ausdrücke verwenden, indem Sie ein Muster erstellen.
Zum Beispiel, um die hrefs und Ziele von Hyperlinks zu finden:

```
Muster neu: ['href="([^"]+)" target="([^"]+)"'].
```

Wenden Sie das Muster nun so auf den zu durchsuchenden Text an:

```
pattern treffer: betreff tun: { :m :x .... }
```

Vollständiges Beispiel:

```
>> betreff := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> pattern := Muster neu: ['href="([^"]+)" target="([^"]+)"'].
>> result  := pattern treffer: betreff tun: { :m :x
	Ausgabe schreiben: m, stopp.
	Ausgabe schreiben: x, stopp.
	<- ['XXX'].
}.
Ausgabe schreiben: result, stopp.
```

## Netzwerk

Verwenden Sie das Objekt Netz, um eine Webanfrage auszuführen.
Das Objekt Netz sendet immer eine POST-Anfrage, außer Sie senden Nichts als
Daten; dann sendet es eine GET-Anfrage.


```
Netz 
post: Nichts 
an: ['https://redbeanphp.com'].
```

## Verschlüsselung

Das Server-Plugin bietet Verschlüsselung auf Basis von XChaCha20 und Argon2.

Beispiel:

```
>> encrypted := Tresor verschlüsseln: ['hello'] schlüssel: ['world'].
>> decrypted := Tresor verschlüsseln: encrypted schlüssel: ['world'].
```

## Tokens

Um ein kryptografisch sicheres Token einer bestimmten Länge zu erzeugen:

```
>> mytok := Tresor token: 40.
```

Dadurch wird ein Token mit 40 Zeichen erzeugt.

## Formatierung

Mit dem Objekt Format können Sie Daten formatieren, etwa durch Auffüllen oder
Hinzufügen von Nullen. Es verwendet die printf-Syntax.

```
>> fmt := Format neu: ['%06.0f'].
fmt anwenden: 56. # gives 000056
```

Ein Format darf eine Umwandlung enthalten, und diese muss zum Wert passen,
sonst erhalten Sie einen Fehler:

- `anwenden:` mit einem Text: `%s`
- `anwenden:` mit einer Zahl: `%f`, `%e`, `%g` oder `%a`
- `anwenden-int:` mit einer Zahl: `%d`, `%i`, `%o`, `%u`, `%x` oder `%c`

Werte aus einer Anfrage sind Texte. Um einen davon als Zahl zu formatieren,
wandeln Sie ihn zuerst um:

```
fmt anwenden: (anfrage get: ['amount']) zahl.
```

## Kodierer

Es stehen mehrere Kodierer und Dekodierer zur Verfügung.
Der URL-Kodierer bereitet eine URL für die Verwendung als Link in HTML vor:

```
Server url-kodieren: ['https://example.com?a=6&b=1 2'].
```

Um Benutzereingaben sicher in Ihr HTML einzufügen, ohne XSS-Injections
zu riskieren, verwenden Sie immer:

```
Server html-kodieren: ['<harmless>'].
```

Beachten Sie, dass die Template-Engine immer eine HTML-Kodierung durchführt,
wenn Sie in eine Platzmarkierung schreiben. Wenn Sie das Vorlagensystem verwenden,
brauchen Sie dies also nicht.

## E-Mail-Versand

Um eine E-Mail zu senden, verwenden Sie die Bibliothek mailtools.xo.

Beispiel:

```
Server initialisieren.
Programm verwenden: ['mailtools.xo'].

>> e-mail := HTML-E-Mail neu.
>> img := e-mail beifügen: ( Datei neu: ['myimage.png'] ).

e-mail
absender: ['xo@xoscript.com'] name: ['xo'],
an: ( Liste neu ; ['xo2@xoscipt.com'] ),
betreff: ['xoxo'],
textkörper: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), senden.

```



## Verknüpfen

Mit der Nachricht verknüpfen: können Sie mit Hilfe von libffi eine externe Bibliothek mit
Ihrem Programm verknüpfen. Einzelheiten finden Sie im Kapitel über ffi.


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

FFI wird pro Plattform/Plugin bereitgestellt, weil es
an die zugrunde liegende Systemarchitektur gebunden ist, was der
Kern nicht tun soll.
Das Server-Plugin bietet eine konforme ffi/Blob-Implementierung.
Standardmäßig verbindet sich der Kern mit der Zielplattform
über stdin/stdout, eingeschränkte Datei-Ein-/Ausgabedienste und die Shell (Programm system:).
Weitergehende Integration bieten ffi/Blobs über anwendungsbezogene
Plugins wie das Server-Plugin.

FFI steht für Foreign Function Interface. Damit können Sie Funktionen nutzen, die andere in
anderen Programmiersprachen geschrieben haben und die über DLL-, SO- oder Dylib-Dateien bereitgestellt werden. Das
können die unterschiedlichsten Funktionen sein; über diesen Weg steht eine riesige Auswahl an Funktionalität zur Verfügung.
Beginnen wir mit einem Beispiel:

```
Server verknüpfen: (
 Liste neu ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Liste neu ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s freigeben.
```

Das Ergebnis dieses Codes ist, dass Sie auf der Kommandozeile Folgendes sehen:
FFI has 3 letters.
Jetzt denken Sie wahrscheinlich: „Das ist eine Menge Code für etwas so Einfaches.“
Hätte man das nicht einfach mit einem Gui-show-Befehl lösen können? Die Antwort ist ein klares Ja!
Das hier ist aber als anschauliches Beispiel gedacht.
FFI wird normalerweise für komplexere Aufgaben verwendet, doch die eignen sich nicht gut
als Beispiele, deshalb habe ich etwas Triviales gewählt.

Die Argumente der Methode verknüpfen:

- Argument Nr. 1: Die DLL- oder SO-Datei, die Sie verwenden möchten.
- Argument Nr. 2: Die Funktion in dieser Datei, die Sie verknüpfen möchten.
- Argument Nr. 3: Eine Liste mit den Namen der Datentypen der Funktionsargumente.
- Argument Nr. 4: Der Name des Rückgabetyps der Funktion.
- Argument Nr. 5: Der Name des Objekts, mit dem Sie diese Funktion verknüpfen möchten (falls es nicht existiert, wird es
automatisch erstellt).
- Argument Nr. 6: Die Nachricht, mit der diese Funktion verknüpft werden soll.

Im obigen Beispiel möchten wir die Funktion printf aus libc.so verknüpfen. Die Namen der
Datentypen finden Sie in der Dokumentation der Software, mit der Sie verknüpfen. Die verfügbaren Typen sind:
void, pointer, float, double, int, uint, char, uchar, intX und uintX,
wobei X 8, 16, 32 oder 64 sein kann.

Diese Typen beziehen sich auf die Anzahl der Bytes, die zum Speichern der Daten nötig sind. Für printf verknüpfen wir mit einem
neuen Objekt namens Printf und der Nachricht template:number:. Sie übersetzen die externe
Funktion in den XOScript-Dialekt, bevor Sie sie verwenden. Die Nachricht template:number: erwartet als ersten Parameter einen
Puffer mit dem Vorlagentext. Diesen Puffer erstellen wir mit einem Blob-Objekt, mit dem
Sie Speicher manuell reservieren können. Sie sind dafür verantwortlich, diesen Speicher anschließend
mit der Nachricht freigeben wieder freizugeben.

Sie können einen Speicher-Blob auf verschiedene Weise füllen. In unserem Beispiel füllen wir ihn mit Text, daher verwenden wir die
Nachricht utf8: (UTF-8 ist eine Kodierung, die Text in Bytes umwandelt). Sie können einen Blob auch mit
bytes: füllen und dabei eine Liste von Bytewerten übergeben. Um den Inhalt eines Blobs zu lesen, verwenden Sie von:länge:.
Sie erhalten die Bytes als Liste zurück. Sie können mit einem Blob sogar eine C-Struktur erstellen, indem Sie die
Nachricht struct: verwenden und eine Folge von C-Typen übergeben. Das kann nötig sein, wenn Sie eine C-Funktion
in einer externen Softwarebibliothek aufrufen, die einen Zeiger auf eine Struktur erwartet.

{warning}
Sie müssen Blobs selbst freigeben.
Blobs werden vom Garbage Collector nicht aufgeräumt.
{/warning}

Da Blobs mit externen Funktionen aus Bibliotheken ausgetauscht werden können,
können sie nicht automatisch vom Garbage Collector eingesammelt werden (sie könnten noch von
externen Funktionen verwendet werden, oder diese externen Funktionen möchten sie
vielleicht selbst freigeben). Deshalb müssen Sie Blobs bei Bedarf selbst freigeben.

Um einen Blob freizugeben, verwenden Sie:

```
myblob freigeben.
```

Um eine Struktur freizugeben, verwenden Sie:

```
mystruct struct-freigeben freigeben.
```

Für eine Struktur müssen Sie also zwei Nachrichten senden: struct-freigeben und freigeben, um
den Speicherblock freizugeben.

@api_Blob_fficonnect
