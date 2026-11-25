# Podstawy

{{messages}}


Witamy w XOScript
Celem projektu XOScript jest stworzenie języka skryptowego, który jest prosty i łatwy do audytu.
Prosty nie musi oznaczać łatwy.
Znany już język programowania może być łatwiejszy w użyciu niż XOScript.
Prostota oznacza tutaj coś innego:
możliwość zbudowania pełnego modelu myślowego języka i jego działania.

XOScript został zaprojektowany tak, aby zmieścił się w głowie.
Jego gramatyka i liczba pojęć są celowo niewielkie.
Nie ma klas; obiekty można rozszerzać bezpośrednio.
Obiekty są przekazywane przez referencję, kopiowanie jest jawne,
a funkcje mają jeden punkt wyjścia.

Niektóre z tych decyzji znacząco odbiegają od popularnych języków.
XOScript nie ma na przykład systemu typów i stosuje dynamiczny zasięg zmiennych.
Wiadomości, których nie można obsłużyć, są ignorowane, zamiast wywoływać wyjątek.
Te decyzje mają swoje konsekwencje i nie mają na celu eliminowania błędów.
Mają one sprawić, by model leżący u podstaw języka pozostał mały i spójny.

XOScript można też lokalizować, dzięki czemu reguły biznesowe da się wyrazić
w języku naturalnym i potencjalnie udostępnić je osobom nietechnicznym.

Łatwość audytu oznacza zastosowanie tej samej filozofii do implementacji.
Środowisko uruchomieniowe jest napisane w C, z małym, ręcznie napisanym lekserem, parserem i interpreterem drzewa składni.
Biblioteka standardowa i środowisko uruchomieniowe w dużej mierze odzwierciedlają strukturę języka,
dzięki czemu związek między kodem XOScript a jego implementacją jest stosunkowo bezpośredni.

Testy są również ściśle powiązane z dokumentacją.
Każda metoda powinna mieć powiązany test, który można włączyć do podręcznika,
co pomaga utrzymać dokumentację w zgodzie z implementacją.

XOScript nie ma konkurować z popularnymi językami pod względem
funkcji czy przyzwyczajeń programistów. Bada on inny cel:
środowisko programistyczne, które programista może zrozumieć w całości.

Mamy nadzieję, że mały język i mała
implementacja sprawią, że w praktyce da się zrozumieć oprogramowanie
od bajtu do obiektu, od składni do środowiska uruchomieniowego, i pisać kod
z pewnością siebie, ponieważ rozumie się zarówno to, co dzieje się
w skrypcie, jak i to, co dzieje się pod maską.

Architektura serwera opartego na xoscript
jest prosta, a zarazem elastyczna.

{{architecture.png}}

Aby używać xoscript jako języka serwerowego, należy zainstalować
wtyczkę serwera w folderze o nazwie /mods/server. 

Wynika to z tego, że chcemy
oddzielić rdzeń języka od funkcji specyficznych dla serwera,
inaczej niż na przykład PHP czy Python. W przeciwnym razie musielibyśmy
bez potrzeby dostarczać wszystkim cały zlew kuchenny, co byłoby po prostu niemądre.
Jeśli chcesz, możesz zainstalować również inne moduły. System jest bardzo
elastyczny.

Ponadto niektóre funkcje lepiej zaimplementować w samym języku
skryptowym, na przykład szablony i obsługę sesji, dlatego dodatkowo
dostarczamy dla wygody biblioteki template.xo i webtools.xo.
Powodem tego wszystkiego jest to, że nie wiemy, jak chcesz
używać xoscript. Możesz używać go jako języka skryptowego po stronie serwera,
ale także do interfejsów graficznych, urządzeń wbudowanych lub po prostu przetwarzania wsadowego.
Nawet jeśli używasz go jako języka skryptowego po stronie serwera (co jest
obecnie jednym z głównych zastosowań), możesz chcieć
użyć innego silnika szablonów lub innego mechanizmu obsługi sesji.
Kimże jesteśmy, by decydować, że masz używać naszego?

Jedną z zalet używania naszego własnego silnika szablonów jest jednak to,
że nie musisz uczyć się dodatkowej składni do tworzenia szablonów.
Domyślny silnik szablonów dostarczany z xoscript zapewnia 100%
oddzielenia prezentacji od logiki. Zamiast specjalnej
składni szablonów używa po prostu bardzo elastycznego systemu znaczników miejsc.
Więcej informacji znajdziesz w rozdziale Serwer.

Zauważ, że jeśli nie chcesz używać domyślnego silnika szablonów ani
domyślnych webtools, to oczywiście musisz dostarczyć
własne.

Jeśli uruchamiasz serwer WWW w chroot, jail lub innym rodzaju piaskownicy,
musisz także zainstalować zależności xo w tym środowisku; to, których
bibliotek potrzebujesz, sprawdzisz za pomocą ldd (zobacz stronę podręcznika man w Linux lub BSD).
Jeśli chcesz używać poleceń powłoki w swoich skryptach xo, skopiuj też powłokę
(na przykład bash lub ksh) do tego środowiska.

Chcemy też zaznaczyć, że bardzo poważnie traktujemy zgodność wsteczną.
Dostępna jest nawet specjalna funkcja zgodności wstecznej o nazwie
'wersja'. Ogólnie dążymy do tego, by Twój kod działał zawsze. Nigdy więc
nie będziesz musiał aktualizować kodu, aby zachować zgodność z nowszymi wersjami
xoscript. Nasz cel: napisz raz, uruchamiaj zawsze.

Pozostała część tego podręcznika szczegółowo wyjaśnia język programowania
xoscript. Skrypty serwerowe omówiono w rozdziale
Serwer. Jeśli jesteś doświadczonym programistą, możesz chcieć
pominąć kilka rozdziałów, ponieważ niektóre z nich są nieco zbyt szczegółowe lub
bardzo podobne do ogólnych praktyk programistycznych. Ci z was,
którzy mają już doświadczenie z kilkoma innymi językami programowania,
powinni więc traktować ten podręcznik raczej jako przewodnik referencyjny.

## Instalacja w Linux

Pobierz apache2 i mariadb:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Pobierz xoscript.
Zastąp X właściwym numerem wersji!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Skopiuj pliki do katalogu głównego serwera WWW i do /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Zmodyfikuj konfigurację apache2:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Zastąp Virtualhost następującym:

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

Utwórz stronę testową:

```
sudo nano /var/www/html/test.xo
```

i napisz mały program testowy:

```
#!/bin/xo
Server inicjuj.
Program użyj: ['webtools.xo'].
>> strona := Dokument-Web nowy.
strona wypisz: ['Hello World'].
```

Zezwól apache2 na wykonywanie programu przez CGI:

```
sudo chmod uog+x /var/www/html/test.xo
```

Uruchom ponownie apache2:

```
sudo systemctl restart apache2
```

Otwórz stronę testową w przeglądarce:

```
http://localhost/test.xo
```

Powinieneś zobaczyć:

```
Hello World
```


## Instalacja w OpenBSD

Zmodyfikuj /etc/httpd.conf, dodaj:


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

Jeśli chcesz używać SSL:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Aby zabezpieczyć wymianę kluczy przed komputerami kwantowymi,
wybierz szyfr mlkem:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Dodaj plik wykonywalny xo i moduły, a także wszelkie zależności, do
chroot (ustal je za pomocą ldd).

## Uruchamianie przykładów


Aby uruchomić jeden z przykładowych programów z pakietu:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Na przykład, aby uruchomić przykład FizzBuzz w Linux:

```
./example.sh fizzbuzz Linux
```

Aby uruchomić ten sam przykład w OpenBSD:

```
./example.sh fizzbuzz OBSD
```

Aby uruchomić przykład z czystą kompilacją:

```
./example.sh fizzbuzz OBSD clean
```

## Testy jednostkowe

Aby uruchomić testy jednostkowe:

```
./runtests.sh
```

Aby uruchomić testy jednostkowe bez kompilacji (tylko testowanie):

```
./runtests.sh nobuild
```

## Kompilacja

Aby skompilować ze źródeł w Linux:

```
make clean
ISO="en" make
```

W OpenBSD:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

Aby skompilować wtyczkę serwera w Linux:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

Aby skompilować wtyczkę serwera w OpenBSD:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Witaj, świecie

Po przesłaniu pliku na komputer możesz go rozpakować
i uruchomić xo następującym poleceniem:

```
xo
```

Aby uruchomić program XOScript, zapisz go jako plik, dodając rozszerzenie
-xo (opcjonalnie). Następnie wpisz nazwę pliku programu
po poleceniu XOScript:

```
xo myprogram.xo
```

Gdy uruchomisz polecenie XOScript, podając plik programu jako
parametr, xo wczyta i wykona ten plik.

{{note}}
Program możesz też uruchomić, przeciągając go na ikonę xo.
{{/note}}

{{warning}}
W niektórych systemach musisz wcześniej zezwolić xo na ładowanie
bibliotek dynamicznych.
{{/warning}}

Tradycja nakazuje, by pierwszy program w każdym nowym języku
programowania był swego rodzaju pozdrowieniem dla świata. W XOScript taki
program **Witaj, świecie** wygląda tak:

@test598

Gdy ten tekst zostanie zapisany do pliku, np. hello.xo, można go wykonać
w następujący sposób: .

xo hello.xo

Hello world


Wynik programu widać w pokazanym powyżej czarnym oknie.
W całym tym podręczniku ta sama forma prezentacji będzie używana do pokazywania
wyniku.

{{note}}
Wyjście piszemy wielką literą W.
Ogólnie nazwy obiektów zaczynają się wielką literą,
chyba że obiekt pełni rolę instancji (nie ma własnych
metod, tylko dane). Odpowiada to konwencji klasa kontra instancja
w innych językach programowania.
{{/note}}


## Składnia 

XOScript jest *czysto* *obiektowym* językiem programowania. Oznacza to,
że xoscript traktuje wszystko jako obiekt, dlatego nie ma
innych *typów danych*. W programie napisanym w XOScript istnieją zasadniczo trzy podstawowe
czynności: *przypisywanie*, *wysyłanie wiadomości*
i *odpowiadanie*. Wymiana wiadomości między obiektami jest kluczowym elementem
programu XOScript. Te trzy czynności przedstawiono
poniżej:


Czynność             | Przykład
-------------------- | --------
przypisanie          |  \>\> x := 1. 
wiadomość unarna     | x parzysta?.
wiadomość binarna    | 1 + 2.
wiadomość kluczowa   | x od: 0 długość: 10.
odpowiedź            | <- answer.  


Ten rozdział da Ci ogólne wyobrażenie o języku XOScript
i opisuje jego podstawowe zasady. XOScript jest małym językiem
opartym na trzech czynnościach (zobacz ilustrację), które przekładają się na
około sześć reguł gramatycznych. To wszystko, czego potrzeba, by opanować
ten język.

Nie martw się, jeśli nie wszystko będzie od razu jasne: wszystkie elementy
składowe zostaną omówione w następnym rozdziale (3), a podstawowe reguły zostaną
powtórzone. Bieżący rozdział służy jednak głównie jako ogólne
wprowadzenie do języka. Podstawowe zasady zostaną krótko
wyjaśnione i zilustrowane kilkoma odpowiednimi przykładami. Brakujące
szczegóły zostaną przedstawione później.

Komentarze w XOScript poprzedza się symbolem \#. Zatem następujący wiersz
zostanie zignorowany:

```
# to tylko komentarz
```

## Zmienne

Aby przypisać
zmienną, używa się symbolu deklaracji zmiennej: >>. Nazwa
zmiennej może zawierać wszystkie znaki z wyjątkiem: <-, :=, białych znaków,
kropek, przecinków, dwukropków, cudzysłowów [' '] i nawiasów ().
Ponadto zmienna nie może zajmować wielu wierszy. Pamiętaj,
że nazwa zmiennej nie może zaczynać się od cyfry ani znaku minus.

Oto przykłady poprawnych zmiennych:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dolar'].
>> +plus := Prawda.
>> hasło-użytkownika := ['Ciii!'].
```

Niepoprawne zmienne to na przykład:


```
>> -123 := ['liczba ujemna'].
>> password of użytkownika := ['Tajne'].
>> password.of:użytkownika := ['Tajne'].
>> ,x := 10.
```

{{note}}
Nie musisz poprzedzać znakiem ucieczki żadnego znaku
(w tym apostrofów, cudzysłowów, ograniczników
tekstu) w
literale tekstowym, o ile nie
powoduje to niejednoznaczności dla leksera.
{{/note}}

Po zadeklarowaniu zmiennej można jej swobodnie używać. Oznacza to,
że symbolu deklaracji trzeba użyć tylko przy pierwszym
użyciu zmiennej (deklaracji).

Mówiąc dokładniej, nie możesz po prostu zacząć przypisywać wartości
zmiennej *(x := 2)*, ponieważ najpierw musisz ją zadeklarować *(\>\>
x := 2)*. Jednak po zadeklarowaniu możesz zmieniać jej wartość
bez używania symbolu deklaracji*(\>\> x := 2. x := 3.)*.

Zauważ, że przy deklaracji zmiennej obowiązkowo trzeba przypisać jej wartość.
W przeciwieństwie do innych języków programowania nie wolno
zadeklarować zmiennej bez wartości. Każdą zmienną trzeba jawnie powiązać
z wartością początkową. Możesz jednak śmiało zainicjować
zmienną obiektem **Nic**. W takim przypadku zmienną można
uznać za pustą *(\>\> x := Nic.)*. Krótko mówiąc, deklarowanie
zmiennej bez wartości początkowej jest niedozwolone. Zatem

```
>> x.
```

jest niepoprawne i spowoduje komunikat o błędzie.

{{note}}
xoscript stosuje dynamiczny zasięg zmiennych;
szczegóły znajdziesz w rozdziale Funkcje.
{{/note}}


## Literały

XOScript traktuje wszystko jako obiekt, tzn. wszystkie liczby, teksty
i fragmenty kodu. Liczby, takie jak 1, 2, 100, -999 i 1,234, są
obiektami Liczba. Wszystkie teksty ujęte w apostrofy są obiektami
Tekst. Wszystkie fragmenty kodu ujęte w nawiasy klamrowe {...} są
obiektami Funkcja.

Literał         | Obiekt bazowy | Przykład
--------------- | ------------- | ----------
liczby          | Liczba        | 1,2,3... 
teksty          | Tekst         | \['hello'\]
funkcja         | Funkcja       | { 1 + 2. }.
                
     
Obiekty takie jak liczby i teksty zawsze wywodzą się z obiektu
bazowego. Na przykład wszystkie liczby wywodzą się z obiektu **Liczba**. Wszystkie
teksty wywodzą się z **Tekst**, a wszystkie fragmenty kodu z **Funkcja**. Z kolei
wszystkie te obiekty wywodzą się z **Obiekt**, który jest w istocie
obiektem bazowym wszystkich obiektów.


## Wiadomości

Programowanie w XOScript polega w zasadzie na
wysyłaniu wiadomości do obiektów. Ogólny zapis wysłania wiadomości do
obiektu wygląda następująco:

```
<object> <message>
```

Aby sprawdzić na przykład, czy liczba **2** jest parzysta, do
obiektu **2** wysyła się wiadomość **parzysta?**:

```
2 parzysta?
```

Odpowiedzią będzie **Prawda** (znów obiekt). Nieznane wiadomości są
zwykle ignorowane przez obiekty, więc nie wystąpi żaden błąd. Niektóre obiekty (np.
liczby lub teksty) reagują na nieznaną wiadomość w określony sposób
(więcej na ten temat później).

Obiekt może otrzymywać trzy rodzaje wiadomości. 

Rodzaj          | Liczba argumentów
--------------- | -------------------
Unarna          | 0      
Binarna         | 1     
Kluczowa        | 1+    


Po pierwsze istnieją **wiadomości
unarne** (zobacz przykład powyżej), które nie mają argumentów. Po drugie
istnieją **wiadomości kluczowe**, które mają jeden lub więcej argumentów,
na przykład:

```
>> x := Liczba między: 1 a: 10.
```

W tym przypadku wiadomość **między:a:** jest wysyłana do **Liczba**, który
jest obiektem bazowym wszystkich liczb. Wynikiem będzie losowa liczba
z przedziału od 1 do 10. Wreszcie istnieją **wiadomości binarne**, które mają
tylko jeden znak i jeden argument:

```
2 + 3
```

Wygląda to jak działanie matematyczne, ale w rzeczywistości jest to po prostu kolejna wiadomość.
Wiadomość **+** jest wysyłana do **2** z argumentem **3**, co zwraca
odpowiedź **5**. Wiadomości binarne można zapisywać bez dwukropka.

Wiadomości binarne można łączyć w łańcuch:

```
>> x := 3 + 2 - 1.
```

W tym fragmencie **+ 2** jest najpierw wysyłane do obiektu **Liczba** **3**, co
daje obiekt Liczba **5**, po czym do tej liczby wysyłane jest **-1**.
Uważni czytelnicy słusznie zauważą rozbieżność między
tym protokołem a konwencjonalną matematyczną kolejnością
działań. XOScript pomija matematyczną kolejność na rzecz
spójności systemu wiadomości. W rezultacie działanie:

```
2 + 3 * 5 = 25
```

a nie 17.

Jest to zamierzone. Kolejność można zmienić za pomocą nawiasów:

```
2 + (3 * 5) = 17
```

Większość obiektów w odpowiedzi na wiadomość zwraca jako wynik samych siebie.
Jest to przydatne, ponieważ zachęca do dalszego dialogu z tym
obiektem przez wysłanie mu kolejnej wiadomości:

```
Wyjście pisz:
[' witaj '] przytnij duże-litery.
```

```
WITAJ
```

Tutaj do obiektu **Tekst** wysyłane są dwie wiadomości: **przytnij**, a po niej
**duże-litery**.

W następującym fragmencie przecinek jest konieczny, aby zaznaczyć,
że nadchodzi nowa wiadomość. W przeciwnym razie XOScript się pogubi.

```
Wyjście pisz: ['Hello!'], nowa-linia.
```

Najpierw do symbolu ołówka wysyłana jest wiadomość **pisz:**, a po niej
**nowa-linia**. Bez przecinka XOScript uznałby, że chcesz wysłać
**nowa-linia** do **tekstu** **Hello!**, co byłoby bezcelowe.

Kolejność przetwarzania wiadomości jest następująca: od lewej do prawej;
najpierw wiadomości w nawiasach, potem wiadomości unarne. Następnie
wiadomości binarne, a na końcu wiadomości kluczowe. Zobacz przykład
poniżej:

```
Wyjście pisz: 0.5 zaokrąglij + (2 - 1), nowa-linia.
```

XOScript zawsze czyta od lewej do prawej: najpierw wiadomość **pisz:**
jest wysyłana do Wyjście, a po niej wiadomość **nowa-linia**. W samym
argumencie XOScript również czyta od lewej do prawej, więc najpierw **0.5 zaokrąglij**,
a potem **+**.

{{note}}
Wiadomość nowa-linia dodaje do tekstu znak nowego wiersza.
Angielska nazwa tej wiadomości (stop) jest inspirowana systemami telegraficznymi.
W wiadomościach telegraficznych
często używano słowa STOP do oznaczenia końca zdania
(ponieważ znaki interpunkcyjne były zawodne lub kosztowne).
{{/note}}

Ponadto **zaokrąglij** ma pierwszeństwo przed **+**, ponieważ jest
**wiadomością unarną**. Ze względu na nawiasy najpierw obliczane jest **2 - 1**,
po czym **1** jest dodawane do wyniku **0.5 zaokrąglij** (1).

Cały proces da wynik **2**, który jest też wypisaną
odpowiedzią. Po przecinku następuje wiadomość nowa-linia, która przenosi kursor
do nowego wiersza. Oczywiście najlepszym sposobem na pełne zrozumienie kolejności
wykonywania programów XOScript jest praktyka.

Warto zauważyć, że w XOScript, w przeciwieństwie do wielu innych języków
programowania, białe znaki są podstawowym elementem składni. Zwłaszcza
w przypadku wiadomości binarnych białe znaki mogą powodować pewne
zamieszanie. Zawsze stawiaj biały znak po wiadomości binarnej. Nie możesz
bezpośrednio dołączyć liczby do wiadomości, na przykład: 

```
3 + 2
```

różni się od 

```
3 +2
```

Pierwszy przykład (**3 + 2**) wysyła
wiadomość **+** do liczby **3** z argumentem w postaci liczby **2**.
Wynikiem w tym przypadku będzie **5**. W drugim przykładzie (**3 +2**)
do liczby **3** wysyłana jest wiadomość unarna **+2**. Zależnie od
kontekstu może to dać zupełnie inny wynik.

## Nieistniejące metody

Wysłanie wiadomości do obiektu wywołuje funkcję, która została
dołączona do tego obiektu pod nazwą tej wiadomości. Jeśli wyślesz wiadomość,
która nie jest rozumiana, obiekt odbiorcy zignoruje ją
i zamiast tego zwróci referencję do samego siebie do dalszej komunikacji.
Nazywa się to tolerancyjnym przekazywaniem wiadomości.

Przykład:

```
Wyjście pisz: Obiekt blah, nowa-linia.
```

Nie spowoduje to błędu. Po prostu zostanie wypisany tekst **Obiekt**.


## Sterowanie przepływem

W XOScript nie są potrzebne osobne reguły gramatyczne dla *pętli* i
*instrukcji warunkowych*. Instrukcja warunkowa to po prostu wiadomość **prawda:** lub **fałsz:**
wysłana do obiektu **Prawda** albo obiektu **Fałsz**:

```
2 parzysta? prawda: {
	Wyjście pisz: ['Dwa to liczba parzysta'], nowa-linia.
}.
```
W poprzednim przykładzie wiadomość **prawda:** jest wysyłana do **Prawda** (odpowiedzi
na pytanie: czy 2 jest liczbą parzystą?). Jako argument przekazywany jest
dodatkowy fragment kodu: obiekt **Funkcja**. Ta funkcja wypisuje
na ekranie, że 2 jest rzeczywiście liczbą parzystą.

Nie ma też potrzeby stosowania osobnych reguł zapisu dla *pętli*. Aby
wykonać fragment kodu trzy razy, wystarczy wysłać **\*** z argumentem
**3** do tej **Funkcja**:

@test5

W tym fragmencie kodu **i** jest indeksem. Za pierwszym razem, gdy Funkcja
jest wykonywana, **i** wynosi 0, za następnym razem **i** = 1 i
tak dalej.

Rozważmy inny przykład. Gdy trzeba wypisać tabelę przeliczeniową
z *kJ* (kilodżuli) na *kcal* (kilokalorie) w krokach co 100,
poprawny zapis wygląda tak:

@test599

Tutaj numer bieżącego wiersza jest przekazywany do parametru
**:line**. Na początku funkcji definiuje się
jej parametry. Nieużyte parametry pozostają puste (**Nic**). Parametry są
zawsze umieszczane na początku funkcji, bezpośrednio po otwierającym
nawiasie klamrowym, i poprzedza się je dwukropkiem.

Wiadomość **dopóki:** jest połączeniem *pętli* i *warunku*.
Za pomocą wiadomości **dopóki:** można połączyć dwie funkcje. Funkcja odbierająca
będzie wykonywana, dopóki funkcja po dwukropku nie da wyniku
negatywnego. Przykład:

@test600

W pokazanym powyżej fragmencie kodu do **x** dodawane jest **1**, dopóki
**x** jest mniejsze niż **5**. Gdy przestaje to być prawdą, druga
funkcja odpowie **Fałsz**, w związku z czym wykonywanie
pierwszej funkcji się zakończy. Zauważ, że **x** zostało zdefiniowane poza
funkcją i jest zmienną globalną. Aby dowiedzieć się więcej o regułach zasięgu,
zajrzyj do rozdziału o funkcjach.

## Interpolacja tekstu

Listę *kJ/kcal* można by przedstawić
bardziej estetycznie. Najlepiej, gdyby wyglądała następująco:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Gdy przekształcisz pożądany wynik w szablon, jego zapis
mógłby wyglądać tak:

```
number1 kJ ➞ number2 kcal
```

Oznacza to, że **number1** oznacza wartość w kJ, a **number2** wartość
w kcal. Tak działa interpolacja tekstu w XOScript. Nie są
do tego potrzebne żadne osobne reguły gramatyczne. Wystarczy wysłać
do tekstu słowo, które ma zostać zastąpione, z tekstem zastępczym
jako argumentem:

```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

Wynik:

```
100 kj ➞ 23.9 kcal
```

Ta reguła zastępowania działa dla każdej niezdefiniowanej wiadomości odebranej
przez obiekt **tekst**. Każda wiadomość, której obiekt **tekst**
nie rozpoznaje, jest interpretowana następująco: *zastąp tekst wiadomości
tekstem z argumentu wiadomości.* Możesz dostosować
program w następujący sposób:


@test601


Aby uniknąć wątpliwości, której wiadomości można, a której nie można użyć
do zastępowania, najlepiej wprowadzić znacznik szablonu, taki jak &lt; &gt;,
dla fragmentów tekstu w szablonie, które
mają zostać zastąpione.

## Wartości zwracane

Aby odpowiedzieć na wiadomość, używa się strzałki zwrotu
(*<-*). Poniższy przykład pokazuje, jak utworzyć zadanie
obliczające procent:

@test602

Po zdefiniowaniu zadania i przypisaniu go do zmiennej **percentage**
wysyłana jest wiadomość **zastosuj:i:** z argumentami **100** i **7**.

Spowoduje to wykonanie zadania dla **100** i **7**, tzn. obliczenie 7% ze 100.
Za pomocą strzałki zwrotu odpowiedź jest zwracana z zadania z powrotem
do programu głównego.

## Rozszerzanie

Choć ten kod jest poprawny, ma pewną wadę,
ponieważ trzeba pamiętać kolejność argumentów. Dlaczego więc nie
zapisać tego tak: *7 percent of: 100 *? Wyglądałoby to znacznie bardziej
*naturalnie*. Aby to umożliwić, musimy dostosować obiekt nadrzędny
**7**, czyli obiekt **Liczba**, tak aby rozumiał
wiadomość **percent of:**. Można to osiągnąć, wysyłając **na:wykonaj:** do
obiektu Liczba, w następujący sposób:

@test603

Ponieważ procent jest w tym przypadku samą liczbą, odwołujemy się do sam,
słowa kluczowego *sam*. Krótko mówiąc, symbol sam oznacza: *wyślij tę
wiadomość do mnie samego*.

# Obiekty

{{messages}}

Oprócz dostosowywania i rozszerzania istniejących obiektów możesz także tworzyć
nowe obiekty, po prostu wysyłając wiadomość **nowy**. Załóżmy, że
chcesz utworzyć obiekt faktury, który wymusza ciągłość
numeracji; w takim przypadku najpierw potrzebujesz obiektu faktury.

Ponieważ każdy obiekt wywodzi się z innego obiektu, który z kolei
ostatecznie pochodzi od obiektu bazowego wszystkich obiektów o nazwie Obiekt,
trzeba zdecydować, na którym z tych obiektów będzie oparty
Twój nowy obiekt. Nowy obiekt dziedziczy wszystkie właściwości
obiektu, na którym jest oparty, czyli tego, do którego pierwotnie
wysłano wiadomość **nowy**.

W tym przykładzie lepszy jest raczej neutralny obiekt, bez zbyt
wielu odziedziczonych właściwości. Wybór jest prosty, ponieważ w takim
przypadku nowy obiekt można oprzeć na samym obiekcie bazowym, czyli
**Obiekt**. Zapis zamierzonego systemu faktur będzie wtedy
następujący:

@test604

Bieżący numer faktury jest przechowywany w obiekcie, dlatego przed nim
umieszczono słowo kluczowe **własny**. Nazywa się to *właściwością*;
więcej szczegółów podamy później.

Niektóre firmy wolą, aby rok był częścią numeru
faktury. W takim przypadku możesz utworzyć nowy obiekt faktury oparty na
wcześniejszym obiekcie faktury, który jednak pozwala użytkownikowi
podać określony rok:

@test605

Nie trzeba ponownie pisać implementacji wiadomości **liczba**,
ponieważ jest ona dziedziczona z wcześniej napisanego **obiektu
faktury**; w ten sposób można ponownie wykorzystać stary kod. W XOScript nie ma pojęć
takich jak klasy i innych z nimi związanych. Oznacza to, że obiekty mogą
dziedziczyć wyłącznie po innych obiektach, co nazywa się również *dziedziczeniem
prototypowym*.

Wróćmy teraz do właściwości. Do właściwości obiektu można się odwoływać
wyłącznie *z wnętrza hierarchii obiektu*, więc te właściwości
nie są widoczne dla innych obiektów.

W przeciwieństwie do innych języków programowania wszystkie właściwości obiektów są
widoczne wyłącznie dla obiektu, który utworzył daną właściwość, oraz dla
obiektów pochodnych. 

Często stosowaną techniką jest używanie obiektu jako swego rodzaju *wzorca*,
jak na przykład w przypadku omówionych wcześniej faktur.
Innym dobrym przykładem jest **Point**. Powiedzmy, że tworzysz
program komputerowy, który wykonuje obliczenia na punktach na mapie. Możesz
opracować obiekt **Point** zawierający właściwości
współrzędnej x i współrzędnej y, które będą udostępniane
światu zewnętrznemu za pomocą wiadomości:

@test606

Wiadomość **=** porównuje dwa punkty za pomocą wiadomości **i:**.
Pierwsze porównanie daje wynik **Prawda** lub **Fałsz**. Są to obiekty
logiczne. Gdy wyślesz wiadomość **i:** do obiektu Prawda, a
obiekt argumentu po dwukropku również jest **Prawda**, to
otrzymasz w odpowiedzi znów **Prawda**. Gdy którykolwiek z nich jest **Fałsz**,
otrzymasz odpowiedź **Fałsz**. Zauważ, że jeden punkt nie może odczytać współrzędnych
drugiego. Trzeba wysłać do drugiego punktu wiadomość z prośbą
o te dane: **x-coordinate** i **y-coordinate**. Jak już bowiem
wyjaśniono, właściwości są dostępne wyłącznie z wnętrza
samej rodziny obiektów. 

Zauważ, że do porównania punktów użyto tu wiadomości **=**.
Równie dobrze można by użyć innej wiadomości, na przykład:
**is:** lub **equal:**, jednak ponowne użycie znaku **=** wydawało się
w tym przypadku właściwe.

## Dziedziczenie

Możesz ponownie wykorzystać wcześniej napisany kod, aby utworzyć hierarchię
obiektów. Na przykład:

```
>> Zwierzę := Obiekt nowy.
>> Pies := Zwierzę nowy.
>> Pudel := Pies nowy.
```

W tym przypadku **Dog** dziedziczy całe zachowanie i wszystkie właściwości
**Animal**, a obiekt **Animal** z kolei dziedziczy całe zachowanie
**Obiekt**, obiektu bazowego wszystkich obiektów.


## Nadpisywanie


W poniższym przykładzie tworzony jest nowy rodzaj listy:
**Combination**, w której każdy element jest gwarantowanie unikalny.
Funkcje listy są ponownie wykorzystywane dzięki dziedziczeniu:

@test607

Zwróć uwagę, że drugie **red** zostało pominięte na liście.

Czasami może być konieczne nadpisanie zachowania obiektu.
Na przykład gdy przy dodawaniu liczb trzeba uwzględnić jednostki
miary. W poniższym przykładzie tworzony jest obiekt **Size**.
Obiekt ten zwraca liczbę, która podczas dodawania
uwzględnia jednostkę dodawanej liczby. Obiekt **Liczba**
sprawdza, czy chodzi o *cale* czy o *stopy*. Kod programu
mógłby wyglądać następująco:

@test608

## Rekurencja

W poprzednim przykładzie nadpisano **znak** plus. Zauważ,
że ostatecznie końcowe dodawanie i tak musi zostać wykonane, co w istocie
następuje w następującym wierszu:

```
>> werdykt := sam + (liczba x współczynnik).
```

Skąd więc XOScript wie, że ten **znak** plus odnosi się do
pierwotnej logiki dodawania?** Inną możliwą interpretacją
byłoby na przykład to, że XOScript będzie wielokrotnie wysyłał tę samą wiadomość do tego samego
obiektu, co z kolei doprowadziłoby do **nieskończonej pętli**. Oczywiście
nie o to chodzi. Gdy tylko wyślesz do obiektu wiadomość,
która wykonałaby dokładnie ten sam kod, XOScript zorientuje się,
że w tym przypadku chodzi o leżącą pod spodem, nadpisaną wiadomość. Twój
program jest więc automatycznie chroniony przed tego rodzaju nieskończonymi
pętlami. Jeśli jednak rzeczywiście chcesz uruchomić tę samą funkcję z
bieżącej funkcji, musisz najpierw wysłać wiadomość
**rekurencyjny**. W tym przypadku wynikiem będzie nieskończona
pętla. Istnieją jednak przydatne zastosowania zadań rekurencyjnych; na
przykład załóżmy, że chcesz obliczyć silnię danej
liczby. W takim przypadku po prostu dodaj wiadomość **factorial** do
Liczba:

@test609

Wymaga to rekurencji. Zadanie powiązane z
wiadomością **factorial** musi zostać ponownie wykonane wewnątrz tej funkcji.
Trzeba więc wywołać funkcję silni z wnętrza
samej funkcji silni. Z zasady XOScript zapobiega takiemu postępowaniu
ze względu na ryzyko nieskończonej pętli. Dlatego
koniecznie trzeba poprzedzić wiadomość słowem **rekurencyjny**.
Robi się to, aby XOScript wiedział, że Twoim
zamiarem jest wykonanie tego samego zadania i że nie popełniłeś błędu.

## Obiekty podobne do klas

Choć xoscript nie oferuje klas, naśladowanie zachowania
podobnego do klas jest banalne. Wystarczy nadpisać wiadomość nowy.

```
>> Zwierzę := Obiekt nowy.
Zwierzę na: ['nowy'] wykonaj: {
	<- sam nowy inicjuj.
}.

Zwierzę na: ['inicjuj'] wykonaj: {
	własny dźwięk := ['?'].
	własny nogi  := 4.
}.
```

W powyższym fragmencie kodu tworzymy obiekt o nazwie Animal.
Obiekt ten służy jako *wzorzec* dla wszelkiego rodzaju zwierząt,
takich jak psy i koty. Obiekt nadrzędny Animal jest zapisany
wielką literą A, aby zaznaczyć, że jest to obiekt podobny do klasy.
Następnie nadpisujemy wiadomość nowy, pisząc własną metodę nowy.
W tym przypadku wysyła ona do sam wiadomość nowy, a po niej wiadomość
inicjuj. Ponieważ xoscript domyślnie blokuje rekurencję, nie spowoduje to
nieskończonej pętli. Zamiast tego wiadomość nowy zostanie wysłana do obiektu
nadrzędnego (Obiekt), co da nową instancję Animal. Tworzymy więc
nowy obiekt oparty na tym samym obiekcie, dla którego utworzyliśmy metodę nowy.
Jest to całkowicie poprawne. Wysyłamy teraz także wiadomość inicjuj, co zapewnia,
że obiekt Animal ma domyślne wartości swoich właściwości. Domyślnie
zwierzę ma 4 nogi, a jego odgłos jest nieznany (stąd znak zapytania).
Aby utworzyć nową instancję naszego Animal, moglibyśmy po prostu napisać:

```
>> a := Zwierzę nowy.
```

Otrzymujemy teraz nową instancję Animal z 4 nogami, nieznanym odgłosem i
metodą inicjuj. Podobnie jak w innych językach obiektowych możemy także
rozszerzyć nasz Animal:

```
>> Pies := Zwierzę nowy.
Pies na: ['inicjuj'] wykonaj: {
	sam inicjuj.
	własny dźwięk := ['szczeka'].
}.
```

Łatwo możemy to przetestować, dodając metodę tekst:

```
Zwierzę na: ['tekst'] wykonaj: {
	<- własny nogi tekst + własny dźwięk.
}.
```

Złóżmy to wszystko razem:

@test13


Częstym problemem jest tworzenie obiektu, który ma znajdować się
w określonym stanie początkowym. Załóżmy, że trzeba utworzyć obiekt **Rectangle**,
aby obliczyć obwód i pole. Możliwy zapis wyglądałby tak:


```
>> Prostokąt := Obiekt nowy.

Prostokąt na: ['pole'] wykonaj: {
	<- własny długość * własny szerokość.
}.
```

Oczywiście warunkiem wstępnym jest ustawienie długości i szerokości. W tym
celu można dodać wiadomości **długość:** i **width:**:


```
Prostokąt na: ['length:'] wykonaj: { :długość
	własny długość := długość.
}.

Prostokąt na: ['width:'] wykonaj: { :szerokość
	własny szerokość := szerokość.
}.

```

Tego prostokąta można następnie używać w następujący sposób:


```
>> prostokąt := Prostokąt nowy length: 2, width: 3.
Wyjście pisz: prostokąt pole.
```

Jeśli jednak pominie się początkowe ustawienie długości i szerokości,
pojawi się komunikat o błędzie:

```
>> prostokąt := Prostokąt nowy.
Wyjście pisz: prostokąt pole.
```

spowoduje następujący błąd:

```
Klucza nie znaleziono:długość
```

Aby temu zapobiec, lepiej, by prostokąt zawsze
miał początkową długość i szerokość, na przykład 0. W tym
przypadku trzeba więc **nadpisać** wiadomość **nowy**.

@test610

Nadpisując wiadomość nowy, w zasadzie naśladujemy **klasę**.

Świat XOScript jest pełen różnorodnych obiektów, które są
dostępne dla Twojego programu od samego początku. W kolejnych rozdziałach
zostaną omówione wszystkie te podstawowe obiekty.

## Migawki

Obiekt (wraz z jego bieżącym stanem) możesz zapisać na dysku za pomocą:

```
mójobiekt save-as: ['saved.bin'].
```

Aby ponownie wczytać obiekt z dysku:

```
>> mójobiekt := Obiekt load-from: ['saved.bin'].
```

Migawek można używać do zapisania określonego stanu lub do poprawy wydajności.
Wczytanie migawki pozwala uniknąć analizy leksykalnej, parsowania i konfiguracji aplikacji.
Ponadto w przyszłości migawki mogą przynieść dodatkowe korzyści
wydajnościowe, takie jak optymalizacja pewnych wzorców lub wykrywanie i
optymalizacja często wykonywanych ścieżek.

{{warning}}
Migawki są funkcją eksperymentalną, nie używaj ich w środowisku produkcyjnym.
Aby włączyć funkcje eksperymentalne, skompiluj z -D EXPERIMENTS.
{{/warning}}


@test712

# Obiekt Nic

{{messages}}

Obiekt Nic
reprezentuje pustkę, a jeszcze lepiej: brak informacji.
Czasami otrzymasz ten obiekt jako odpowiedź na wiadomość,
gdy wynikiem jest **nic**. Najważniejsze pytanie,
jakie możesz zadać obiektowi **Nic**, to: **Nic?**.
Odpowiedź zawsze będzie brzmiała **Prawda**.

```
Wyjście pisz: Nic Nic?.
```

wynik:

```
Prawda
```

Każdy obiekt inny niż **Nic** odpowie **Fałsz**. Powyższy
fragment kodu może wydawać się nieco filozoficzny, ale obiekt **Nic**
ma z pewnością niezwykle praktyczne zastosowania. Na przykład
otrzymasz obiekt Nic jako odpowiedź, gdy poprosisz o
element listy, który nie istnieje. Obiektu Nic możesz też użyć,
gdy chcesz zadeklarować zmienną, ale nie chcesz jeszcze określać jej
wartości. Zamiast tego po prostu **przypisujesz** specjalną wartość **Nic**. W
XOScript nie wolno deklarować zmiennej bez wartości, na przykład:


```
>> wartość.
```

Zamiast tego musisz napisać:

```
>> wartość := Nic.
```

@api_None_base

# Wartości logiczne

{{messages}}

W przeciwieństwie do większości popularnych w chwili pisania tego tekstu języków programowania
XOScript udostępnia tylko jeden obiekt Prawda i jeden obiekt Fałsz.
Innymi słowy, za każdym razem, gdy piszesz **Prawda**, nie oznacza to,
że tworzony jest nowy obiekt. Zamiast tego zawsze używasz referencji. Oznacza
to, że gdy napiszesz:

\>\> x := Prawda.

**x** odwołuje się do obiektu **Prawda**. Kod warunkowy i pętle również
sprawdzają tę referencję. W XOScript znaczenie **Prawda** i **Fałsz**
nie jest stałe. W rzeczywistości program XOScript zostaje mocno wstrząśnięty
przez instrukcję taką jak ta:

Prawda := Fałsz.

Wynik takich działań jest niezdefiniowany, jednak pozostaje to poprawnym
działaniem i jest formalnie dozwolone. Ponadto istnieje obiekt Logiczny,
który jest obiektem bazowym zarówno **Prawda**, jak i **Fałsz**, ponieważ oba
wywodzą się z tego obiektu bazowego. Sam obiekt Logiczny nie ma jednak
żadnego praktycznego zastosowania.

## Pułapki

Uważaj przy używaniu **i:** oraz **lub:**

```
Wyjście pisz: (Fałsz or: Prawda or: Prawda), nowa-linia.
Wyjście pisz: (Fałsz lub: Prawda, lub: Prawda), nowa-linia.
```

Daje

```
Fałsz
Prawda
```
ponieważ wiadomość **lub:** przyjmuje tylko 1 argument. Pierwszy wiersz
wysyła do Fałsz wiadomość **lub:lub:**, która nie istnieje, więc obiekt ignoruje
wiadomość i zwraca samego siebie (Fałsz). Natomiast drugi wiersz
wysyła **lub:**, a po nim kolejne **lub:** (za pomocą symbolu łańcucha, czyli przecinka: ,).


@api_Boolean_base

# Liczby

{{messages}}

Za każdym razem, gdy zapisujesz liczbę, na przykład 9, -10 lub 3,12,
XOScript w tle przekształca ją w obiekt **Liczba**. Możesz
wysyłać wiadomości do tego obiektu Liczba albo przypisać liczbę
do zmiennej i wysyłać wiadomości później:

```
10 parzysta?

>> dycha := 10.
dycha parzysta?

```

Oba zapisy są poprawne. Obiekt Liczba odpowiada na następujące
wiadomości...

Większość z tych wiadomości nie wymaga wyjaśnień i pozwala wykonywać
działania matematyczne lub porównania.

{{note}}
Zauważ, że zamiast ich odpowiedników ASCII możesz używać ≤ ≥ ≠ × i ÷.
To kwestia upodobań.
{{/note}}

Różnica między binarnymi wiadomościami matematycznymi (+) a
ich odmianami kluczowymi (dodaj:) polega na tym, że pierwsze zwracają
nową liczbę będącą wynikiem działania, podczas gdy w przypadku
drugich modyfikowany jest sam obiekt. Ilustruje to
następujący przykład:

@test597

W powyższym przykładzie b = 4, a a = 3. Za pomocą **dodaj: 2** wartość
a zwiększa się o 2, natomiast **+ 3** tworzy nową liczbę równą
a + 3. To samo dotyczy innych działań matematycznych, np.
mnożenia. Używając symbolu mnożenia, otrzymasz w odpowiedzi
nowy obiekt. Jeśli użyjesz wiadomości **pomnóż-przez:**,
pomnożysz samą liczbę.

Za pomocą wiadomości **między:a:**, na przykład w: **Liczba
między: X a: Y**, otrzymasz liczbę z przedziału od X do Y. W ten
sposób można wygenerować dowolną liczbę losową:

```
>> a := Liczba między: 1 a: 10.
Wyjście pisz: a, nowa-linia.
```

Od wersji 1.4 wbudowany generator liczb losowych w xoscript jest,
według naszej najlepszej wiedzy, kryptograficznie bezpieczny.

Do liczby możesz dołączyć **określenie**, na przykład **6
apples**. Każda wiadomość, której liczba nie rozpoznaje,
będzie traktowana jako określenie. Określenie liczby
możesz odczytać za pomocą wiadomości określenie:

Określenie to w zasadzie obiekt tekstowy przechowywany razem z obiektem
Liczba. Określenie jest też wypisywane po liczbie przy
wywołaniu **pisz:**. Określeń można by używać na przykład do dodawania kwot
w różnych walutach. Podczas dodawania kwot możesz zapytać
o ich określenia. Poniższy przykład programu ilustruje tę
zasadę za pomocą historycznego kalkulatora walut (ponieważ kurs
wymiany pozostaje dość stabilny!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Teksty

{{messages}}

Za każdym razem, gdy umieszczasz tekst między **nawiasami kwadratowymi i apostrofami** ['...'],
XOScript tworzy dla Ciebie nowy obiekt tekstowy. Pamiętaj jednak,
aby używać właściwych znaków cudzysłowu. Znak na
początku tekstu różni się od znaku na końcu (dzięki temu możesz
używać pojedynczego apostrofu bez poprzedzania go znakiem ucieczki).

## UTF8

Teksty w xoscript zwykle zawierają tekst zakodowany w utf8. Choć
technicznie możliwe jest umieszczenie w tekście treści binarnej lub
niezgodnej z utf8, zaleca się używanie do tego obiektów blob. Obiekty blob są
dostarczane przez wtyczkę serwera (zobacz rozdział ffi).
Ogólnie blob/ffi są dostarczane
w zależności od wtyczki/platformy, ponieważ są powiązane z platformą
i architekturą (ffi/blob). Rdzeń języka skryptowego stara się
pozostać jak najbardziej niezależny od platformy.

## Rzutowanie

Za pomocą następujących wiadomości możesz utworzyć kopię każdego obiektu
o innym typie:

Wiadomość | Wynik
--------- | ------
liczba    | Konwertuje na liczbę
tekst     | Konwertuje na tekst
logiczny  | Konwertuje na wartość logiczną
  
**Obowiązują** następujące reguły:

wiadomość | Nic       | Logiczny           | Liczba                | Tekst     | Inne              
--------- | --------- | --------           | --------              | --------  | --------
logiczny  | Fałsz     | nd.                | 0→Fałsz inne→Prawda   | Prawda    | Zwykle Prawda
liczba    | 0         | Fałsz→0 Prawda→1   | nd.                   | ['n']→n   | Zwykle 1
tekst     | ['Nic']   | ['Fałsz']/['Prawda'] | ['n']               | nd.       | Zależy

## Kopiowanie

Wartości w XOScript są zawsze przekazywane **przez referencję**. W innych językach
zależy to od typu wartości, w XOScript istnieje tylko jeden sposób:
przez referencję. XOScript nigdy nie tworzy kopii wartości. Aby skopiować obiekt,
musisz wysłać wiadomość **kopiuj**. 

@test611

Tutaj można by się spodziewać, że wynikiem będzie Dolly, a nie
Donny. Tak jednak nie jest, ponieważ obie nazwy odwołują się do tego samego
obiektu. Podobnie dzieje się podczas pracy z pętlą:

@test612

XOScript **zawsze** używa referencji, więc w **:quantity**
pokazana powyżej pętla również wskazuje referencję do elementu
listy.

Aby skopiować obiekt, musisz określić to działanie
**jawnie**:

@test613

Wysyłając do tekstu wiadomość unarną **kopiuj**, obiekt
zwraca kopię tego samego obiektu tekstowego. W ten sam sposób można kopiować obiekty
Liczba, obiekty logiczne, listy i słowniki.

Możesz też zdefiniować własną implementację kopiowania; jest to wręcz
konieczne, jeśli tworzysz własne obiekty. Domyślna
implementacja kopiowania listy tworzy płytką kopię, czyli
nową listę z tymi samymi elementami.

@test614

W tym przypadku 4 jest dodawane tylko do kopii.
Ponieważ jednak kopia jest płytka, obiekty w obu listach
są te same.

@test615

Jeśli więc dołączymy 2 do każdej nazwy w kopii, zmieni się
również oryginalna lista.

Aby temu zaradzić, musimy wykonać **głęboką kopię**. Taką operację kopiowania
dla listy można zbudować następująco:

@test616

Zwróć też uwagę na wiadomość rekurencyjny; trzeba ją
wysłać przed wiadomością kopiuj.

Należy pamiętać, że choć kopia obiektu
często wygląda tak samo jak oryginał, w rzeczywistości
nigdy nie jest tym samym obiektem. Obiekt bazowy definiuje wiadomość **equal:**,
której można użyć do porównania tożsamości obiektów. Spójrz na
następujący przykład:

@test617

## Konwersja niejawna

XOScript stosuje **konwersję niejawną** do przekształcania obiektów. Aby wypisać
listę na ekranie, XOScript na przykład wewnętrznie wysyła do listy wiadomość
*tekst*. Może się to okazać bardzo przydatne, gdy
chcesz wypisać listę jako listę rozdzieloną przecinkami.
Wiadomość *tekst* można nadpisać: 

@test620

@api_String_base
@api_Format_base


## Teksty serwerowe

Poniższe funkcje obiektu Tekst są dodawane przez
wtyczkę Server.

@api_String_server

# Funkcje

{{messages}}

Kod możesz zgrupować między { i }; staje się on wtedy funkcją.
W xoscript czasami używamy też terminu zadanie lub po prostu
blok kodu.

Funkcję możesz uruchomić, wysyłając wiadomość *uruchom*.


```
{ Wyjście pisz: 123, nowa-linia. } uruchom.
```

Jeśli funkcja przyjmuje argumenty, użyj **zastosuj:**.

```
{ :a Wyjście pisz: a, nowa-linia. } zastosuj: a.
```

Zobacz też poniższe przykłady.
Ze względu na uproszczoną architekturę funkcja może mieć tylko
jeden punkt powrotu. Aby uniknąć narzutu lub nadmiernego zagnieżdżania
warunków, możesz użyć procedury (co jest równoznaczne z użyciem
znaku mnożenia z argumentem 1):

```
{
  (a = 1) prawda: { x := 1. }, przerwij.
  (a = 2) prawda: { x := 2. }, przerwij.
} procedura.
```

W ten sposób (a = 2) nie zostanie obliczone, jeśli a = 1.
Nie potrzebujesz też w ten sposób zagnieżdżonych wiadomości prawda.
Ilekroć zauważysz, że zagnieżdżasz warunki, pomyśl
o wiadomości procedura. Może to sprawić, że Twój kod
będzie czytelniejszy.


Oto ważna pułapka:

```
{
	Fałsz fałsz: {
		Wyjście pisz: ['Zakończ pętlę.'].
	}, przerwij.
	
	Wyjście pisz: ['Nie pokazuj mnie.'].

} procedura.

```

W tym przypadku zostanie wyświetlony tekst 'Dont show me',
ponieważ **przerwij** jest wysyłane do Fałsz. Jeśli chcesz wykonać
przerwanie, trzeba je wysłać jako wiadomość do **Prawda**.
 

```
{
	Fałsz nie prawda: {
		Wyjście pisz: ['Zakończ pętlę.'].
	}, przerwij.
	
	Wyjście pisz: ['Nie pokazuj mnie.'].

} procedura.

```

Zadziała zgodnie z oczekiwaniami.

## Wyjątki

Wyjątki można obsługiwać w następujący sposób:

```
{ Zadanie 1 } przechwyć: { Zadanie 2 }, uruchom.
```

Możesz też celowo spowodować błąd w programie
i w ten sposób uruchomić blok obsługi. Robi się to, wysyłając
wiadomość **błąd:** do bieżącego zadania, jak pokazano na następnej
ilustracji:

```
{
to-zadanie błąd: ['Ojej!'].
} przechwyć: { :pomyłka
Wyjście pisz: pomyłka.
}, uruchom.
```

## Wstrzykiwanie wartości

XOScript umożliwia wstrzykiwanie wartości do zadań. Spójrz
na poniższe zadanie:

```
>> wysyłanie := {
	Biuletyn adresat: własny recipient.
}.
wysyłanie ustaw: ['recipient']
wartość: ['info@recipient.org'].
wysyłanie uruchom.
```


Ta ilustracja przedstawia wymyślone zadanie, które wysyła biuletyn
na adres e-mail, czyli do **recipient**. Tego odbiorcę można wstrzyknąć
do zadania z zewnątrz, zanim zadanie zostanie uruchomione, wysyłając do zadania
wiadomość **ustaw:wartość:**. W ten sposób wartość
**recipient** zostaje z góry ustawiona w zadaniu. Tę wartość można też zmienić,
a zadanie uruchomić ponownie. Jest to przydatna metoda przy używaniu
obiektów zadań.

## Puste funkcje

Puste zadania są niedozwolone. Teoretycznie puste zadanie wyglądałoby
tak: **{}**, jednak XOScript traktuje to jako błąd językowy. Jeśli
chcesz zadeklarować puste zadanie, możesz użyć obiektu Nic:

```
>> zadanie := Nic.
```

Choć nie jest to prawdziwe zadanie, lecz obiekt Nic, nadal można
wysłać do niego wiadomość uruchom:

```
>> werdykt := zadanie uruchom.
```

W rzeczywistości jest to to samo co:

```
>> werdykt := Nic uruchom.
```

Ponieważ obiekt **Nic** nie rozpoznaje wiadomości **uruchom**,
zwróci samego siebie jako odpowiedź, więc odpowiedzią znów będzie **Nic**.
Nie ma zatem potrzeby posiadania pustego zadania. Dzięki eleganckiemu
projektowi języka programowania XOScript możesz po prostu użyć do tego obiektu
Nic.

## Zasięg dynamiczny

Gdy Funkcja potrzebuje zmiennej, ale nie może jej znaleźć,
sprawdza zmienne Funkcji, która ją **wywołała**,
i kontynuuje sprawdzanie w górę łańcucha Funkcji.
Ten proces wyszukiwania trwa, dopóki zmienna nie zostanie znaleziona.
Jeśli zmienna nadal nie zostanie znaleziona, pojawi się komunikat o błędzie. Ten sposób wyszukiwania
zmiennej nazywa się **zasięgiem dynamicznym**.

Aby zilustrować tę zasadę:

@test618

@api_Code_base

# Obiekt bazowy

{{messages}}

Obiekt o nazwie **Obiekt** jest obiektem bazowym wszystkich obiektów w
XOScript i zapewnia podstawowe funkcje języka. 

Najczęściej wysyłaną wiadomością
jest **na:wykonaj:**, która rozszerza funkcjonalność obiektu. Tę
wiadomość odbiera obiekt bazowy, który w rezultacie wiąże
podane zadanie z wiadomością i w ten sposób rozszerza obiekt
pochodny.

## Metody przechwytujące

Zwykle jeśli wyślesz wiadomość, która nie odpowiada
żadnej metodzie obiektu, zostanie ona zignorowana. Możesz jednak określić
tak zwane **metody magiczne** lub metody **przechwytujące**, które
zostaną wywołane, jeśli obiekt nie zrozumie wiadomości.

Dostępne są 4 metody przechwytujące. Każda wiadomość odpowiada
określonej liczbie argumentów.

Wiadomość przechwytująca | Liczba argumentów
------------------------ | -------------------
odpowiedz:               | 0
odpowiedz:i:             | 1
odpowiedz:i:i:           | 2
odpowiedz:i:i:i:         | 3


@test619

## Wiadomości programowe

Zamiast wysyłać wiadomość bezpośrednio do obiektu, można ją też
wysłać za pośrednictwem zmiennej. Służy do tego wiadomość
**wiadomość:argumenty:**. 

@test396

@api_Object_base

# Listy

{{messages}}

XOScript zna dwa rodzaje kolekcji: *listy* i *słowniki*.
**Listy** to wyliczenia obiektów w *ustalonej kolejności*. Słowniki
nie mają kolejności; przypominają raczej legendę zawierającą klucz (lub hasło) i
odpowiadającą mu wartość. Listy są porównywalne z tablicami (PHP, Java, C)
i listami (Python). Słowniki są porównywalne z tablicami asocjacyjnymi (PHP) lub
słownikami (Python) w innych językach programowania. Aby utworzyć
nową Lista, napisz:

```
>> fibonacci := Lista nowy.
```

Tę pustą listę można wypełnić za pomocą **dołącz:** :

```
fibonacci dołącz: 0.
fibonacci dołącz: 1.
fibonacci dołącz: 1.
fibonacci dołącz: 2.
fibonacci dołącz: 3.
fibonacci dołącz: 5.
fibonacci dołącz: 8.
fibonacci dołącz: 13.
```

Jeśli wypiszemy listę na ekranie:

```
Wyjście pisz: fibonacci, nowa-linia.
```

Zobaczymy:

```
Lista ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

Zamiast dołącz możesz też użyć ; do dodawania elementów do listy:


```
>> fibonacci := Lista nowy ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Średniki (;) są wiadomościami binarnymi, które umieszczają
wartość na liście.

## Łączenie wiadomości

Załóżmy, że masz listę taką jak:

```
>> x := Lista nowy ; 1 ; 2 ; 3.
```

Jeśli chcesz usunąć pierwszy i ostatni element, Twoja
wiadomość wyglądałaby tak:

```
x zdejmij-pierwszy zdejmij-ostatni.
```

Niestety poprzedni zapis nie zadziała poprawnie.
Wiadomość **zdejmij-pierwszy** zwraca pierwszy element listy, który
z kolei staje się odbiorcą wiadomości **zdejmij-ostatni**. Zatem
wiadomość **zdejmij-ostatni** nie jest wysyłana do **x**, lecz do 2.
Możliwym rozwiązaniem tego problemu byłoby utworzenie dwóch osobnych
zdań, na przykład: 

```
x zdejmij-pierwszy.
x zdejmij-ostatni.
```

Jest to jednak dość niepraktyczne, zwłaszcza gdy trzeba
usunąć więcej niż dwa elementy. Dlatego XOScript oferuje
alternatywną strukturę wiadomości dla takich sytuacji. W
**alternatywnych** strukturach wiadomości odpowiedzi obiektów są ignorowane,
a jako odpowiedź za każdym razem otrzymujesz z powrotem obiekt odbiorcy.
**Alternatywną** strukturę wiadomości rozpoczyna się, wysyłając do obiektu
wiadomość **wykonuj**, a kończy się ją, wysyłając
wiadomość **gotowe**. W
pokazanym przykładzie można to zastosować następująco:

```
>> x := Lista nowy ; 1 ; 2 ; 3.
x wykonuj zdejmij-pierwszy zdejmij-ostatni gotowe.
```

@api_List_collections

# Słowniki

{{messages}}

**Zarówno Lista, jak i Słownik są kolekcjami. Jednak w przeciwieństwie do
listy słownik **nie ma** kolejności. Kolejna różnica między nimi
polega na tym, że słownik składa się z par obiektów. Jeden obiekt pełni rolę hasła (lub
słowa kluczowego), za pomocą którego wyszukuje się drugi obiekt. Dobrym przykładem
takiej listy jest cennik, na przykład:


```
>> menu := Słownik nowy
	umieść: ['£5'] w: ['szarlotka'],
	umieść: ['£6'] w: ['ciasto marchewkowe'],
	umieść: ['£3'] w: ['fudge'].
```

Podobnie jak w przypadku listy, do dodania obiektu do listy
używa się wiadomości umieść:w:. Różnica polega na tym, że w przeciwieństwie do
listy wiązane są dwa obiekty. Pierwszy obiekt jest, podobnie
jak w liście, obiektem, który przechowujesz. Drugi
obiekt nie jest jego pozycją w kolekcji, lecz **hasłem**,
które pozwala później odczytać poprzedni obiekt.
Krótko mówiąc, słownik działa trochę jak prawdziwy słownik: za pomocą słowa kluczowego
można znaleźć jego znaczenie. Na przykład, aby odczytać z
powyższej listy cenę krówki:

```
>> price := menu w: ['fudge'].
```

Możesz też użyć zwięzłego zapisu:

```
>> price := menu ? ['fudge'].
```

Jeśli hasła, których używasz do przechowywania obiektów, nie zawierają spacji
(i nie kolidują z innymi predefiniowanymi wiadomościami),
można użyć również następującego zapisu:

```
>> menu := Słownik nowy
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Bez wątpienia powyższy zapis brzmi nieco bardziej naturalnie.
Aby zapytać o cenę
krówki, można użyć następującego uproszczonego zapisu:

```
>> price := menu fudge.
```

@api_Dict_collections

# Plik

{{messages}}

Obiekt **Plik** zapewnia podstawowy dostęp do systemu plików.
Za jego pomocą możesz od razu wczytać całe pliki do zmiennej
lub od razu zapisać zmienne do plików. Obsługiwane jest też odczytywanie
wiersz po wierszu. Są to najczęstsze operacje wejścia/wyjścia na plikach
w języku skryptowym. Zaawansowane operacje na plikach wymagają
użycia FFI za pośrednictwem wtyczki serwera lub osobnej wtyczki IO.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Data/czas

{{messages}}

Do uporządkowanej reprezentacji czasu i daty XOScript używa
obiektu **Moment**. Gdy nowy obiekt Moment zostanie wypisany na ekranie,
wyświetlane są bieżąca data i godzina:

```
Wyjście pisz: Moment nowy, nowa-linia.
```

Może to dać wynik podobny do:

```
2020-10-10 12:16:39
```

Łatwo jest też odczytać poszczególne składniki czasu. Jeśli więc
na przykład potrzebujesz tylko bieżącego roku, możesz wysłać
do obiektu moment wiadomość **rok**, a odpowiedzią będzie
obiekt Liczba zawierający wyłącznie rok:

```
>> m := Moment nowy.
Wyjście pisz: m rok, nowa-linia.
```

@api_Moment_system

# Program/StdOut

{{messages}}

Obiekt Program reprezentuje aktualnie uruchomioną aplikację. Obiekt ten
oferuje funkcje do wykonywania poleceń systemowych, dołączania podprogramów,
odczytywania argumentów i nie tylko. Wszystkie funkcje związane z systemem.

## StdOut

Wyjście jest obiektem standardowego wyjścia. Ma zasadniczo dwie metody:
**pisz:** i **nowa-linia**. Wiadomość pisz: służy do wysyłania tekstu
na stdout, a wiadomość nowa-linia wypisuje znak nowego wiersza.
Zamiast **nowa-linia** możesz też użyć \\n.

Przykład:

```
Wyjście pisz: ['Hello World'], nowa-linia.
```

wynik:

```
Hello World
```

## Moduły/wtyczki

Świat XOScript można rozszerzać o nowe obiekty systemowe,
instalując moduły. Nowy obiekt systemowy można dodać do świata
XOScript, umieszczając plik modułu (zwykle plik z rozszerzeniem .so
) w folderze mods. 

Gdy wyślesz wiadomość do obiektu udostępnianego przez
moduł wtyczki, zostanie on automatycznie załadowany przez XOScript.

Wtyczki możesz też pisać samodzielnie. Wtyczki pisze się w
języku programowania C. Przykładową wtyczkę znajdziesz w pakiecie
kodu źródłowego w src/plugins/example.


## Refleksja

Istnieją różne sposoby badania systemu
w trakcie wykonywania programu. XOScript ma kilka metod pozwalających
wykryć, jakie obiekty są obecne i na jakie wiadomości te obiekty
odpowiadają. Po pierwsze, każdy obiekt można zapytać, jakiego jest **typ**u,
jednak typy w XOScript są plastyczne, a przez to zawodne.

Można też zapytać obiekt Program, czy
dany obiekt jest już obecny w programie:

```
Program Narzędzie prawda: { ... }.
```

W przypadku nazwy obiektu
składającej się z jednego symbolu najlepiej zastosować
następujący zapis, aby uniknąć nieporozumień:

```
Program znajdź: ['X'], prawda: { ... }.
```

Oprócz pytania o obiekty można również pytać
obiekt Program o wiadomości. Można na przykład zapytać, czy
obiekt **Liczba** zna wiadomość **między:a:**, w sposób
pokazany poniżej:

```
Program Number: ['between:and:'], nowa-linia.
```

@api_Program_system

# serwer

{{messages}}

Wtyczka Server w xoscript oferuje funkcje do
tworzenia aplikacji po stronie serwera. Aby załadować
wtyczkę serwera, użyj:

```
Server inicjuj.
```

Dla wygody zaleca się też załadowanie
plików webtools.xo i template.xo.

```
Program użyj: ['webtools.xo'].
Program użyj: ['template.xo'].

```

## Ustawienia serwera

Możesz ustawić następujące ustawienia serwera:

```
	# podane są wartości domyślne,
	# więc jeśli niczego nie ustawisz, użyte zostaną
	# te wartości...

	Program 
	ustawienie: ['max-postfields']
	wartość: 40.

	Program 
	ustawienie: ['max-contentlength']
	wartość: 2000000. # 2MB

	Program 
	ustawienie: ['max-time']
	wartość: 5000. # 5sec

```

## Witaj, świecie

Oto bardzo prosty program WWW, którego możesz używać ze
standardowym serwerem CGI, takim jak Apache2, NGINX, OpenHTTPD lub dowolny inny
znany serwer.

```
#!/bin/xo

Server inicjuj.
Program użyj: ['webtools.xo'].

>> dokument-www := Dokument-Web nowy.

dokument-www wypisz: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Jeśli nie chcesz używać obiektu Dokument-Web, nie ma problemu, ale
wtedy musisz samodzielnie napisać nagłówki HTTP:

```
#!/bin/xo
Wyjście pisz: ['Content-type: text/html; charset=utf-8 \n\n'], nowa-linia.
Wyjście pisz: ['witaj świecie!'], nowa-linia.
``` 

## Żądanie

Obiektu Żądanie-HTTP można używać do pobierania danych GET/POST/COOKIE i
UPLOAD:

```
>> żądanie  := Żądanie-HTTP nowy.
>> search   := żądanie get: ['search']. # ?search=books
>> password := żądanie post: ['password']. # z formularza
>> wybrane := żądanie get-lista: ['sel[]']. #?sel[]=1&sel[]=2
>> wybrane := żądanie post-lista: ['sel[]'].
>> ciasteczko   := żądanie cookie: ['session-id'].
>> przesłany   := żądanie upload: ['file'].
>> ścieżkatymcz := przesłany ? 1.
>> nazwapliku := przesłany ? 0.
```

## Maxpost/length

Domyślna maksymalna liczba pól POST wynosi 40, a domyślna maksymalna długość
treści to 2MB. Aby skonfigurować to inaczej dla poszczególnych skryptów:

```
Program ustawienie: ['max-contentlength'] wartość: 1. 
Program ustawienie: ['max-postfields'] wartość: 1. 
```

{{note}}
Jeśli długość treści przekracza maksimum,
proces zostaje zakończony, ponieważ nie możemy już mieć pewności,
że przesłane dane są bezpieczne.
{{/note}}

Limit maxtime określa maksymalny czas w ms
na odczyt stdin/danych POST.

```
Program ustawienie: ['max-time'] wartość: 5000. # 5sec
```

Dotyczy to wyłącznie odczytu wejścia/wyjścia danych POST i zapobiega
atakom typu slowloris. Jeśli naprawdę chcesz ograniczyć
czas wykonywania dowolnej operacji, użyj Program alarm:.

## Baza danych

Obiektu Database można używać do wykonywania zapytań w MariaDB/MySQL.
Aby połączyć się z bazą danych, wykonaj:

```
>> bd := Maria-DB nowy host: ['localhost'],
	użytkownik: ['xo'],
	hasło: ['pass123'],
	nazwa-bazy: ['xobase'],
	połącz.

```

Aby wstawić rekord, użyj:

```
>> parametry-wyszukiwania := bd zapytanie: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parametry: ( Lista nowy ; ['abc'] ; 12.35 ; 6 ). # zapytania sparametryzowane

{  parametry-wyszukiwania wykonaj. bd zatwierdź. }
przechwyć: { :e bd wycofaj.  }, uruchom.
```

Zauważ, że xoscript działa *wyłącznie* z transakcjami i nigdy nie zatwierdza automatycznie (autocommit).
Jeśli nie można wyłączyć autocommit, otrzymasz błąd połączenia.
Zawsze używaj wiązania parametrów w zapytaniach, nigdy nie dodawaj danych wprowadzonych przez użytkownika bezpośrednio
do SQL.

Identyfikator wstawionego rekordu uzyskasz w ten sposób:

```
Wyjście pisz: ['WSTAWIONO: '] + parametry-wyszukiwania insert-id, nowa-linia. # id wstawienia
```

Aby pobrać rekordy:

```
>> parametry-wyszukiwania :=
bd
	zapytanie: ['SELECT * FROM book order by id desc limit 2'], 
	pobierz: { :rząd 
		Wyjście pisz: rząd id + [' '] + rząd description + [': '] + rząd price, nowa-linia.
	}. # pobieranie wierszy

```

## Sesje

Aby zachować dane między żądaniami, możesz zapisywać i odczytywać je z obiektu sesji.
Najpierw utwórz nowy **Dokument-Web**. Obiekt Dokument-Web łączy
żądanie, nagłówki, HTML i sesję. Wynika to z tego, że gdy
odwiedzasz stronę internetową w przeglądarce, widzisz tylko HTML. Jednak
cały Dokument-Web składa się również z **nagłówków**. Na przykład
większość odpowiedzi HTTP zawiera nagłówek taki jak Content-type:text/html,
który informuje przeglądarkę, że następujące po nim dane mają zostać wyświetlone jako HTML
(a nie na przykład pobrane jak plik). Sesje są sposobem na
przechowywanie danych użytkownika między żądaniami. Aby śledzić te dane, musimy
ustawić ciasteczko (cookie), a ono również jest ustawiane za pomocą nagłówka. Dlatego
wszystko łączy się w Dokument-Web (ponieważ jest to pełny
dokument zawierający zarówno nagłówki, jak i HTML lub inne dane).


```
# Najpierw tworzymy nową instancję Dokument-Web
>> strona := Dokument-Web nowy.

# Teraz zaczynamy sesję; wygeneruje to nagłówek dla ciasteczka i
# utworzy plik na twoje dane, powiązany z tym ciasteczkiem
>> moja-sesja := strona rozpocznij-sesję.

# Teraz możemy traktować sesję jak Słownik
moja-sesja userid: 123.
```

Aby zniszczyć sesję (przy wylogowaniu):

```
strona zniszcz-sesję.
```

## Nagłówki

Dokument-Web pozwala też ustawiać inne znane nagłówki.
Na przykład, jeśli chcesz przekierować użytkownika pod inny URL:

```
strona przejdź-do: ['/other.html'].
```

Pod maską to polecenie generuje również nagłówek HTTP, który jest wysyłany
wraz z pozostałymi danymi lub HTML i nakazuje przeglądarce przejść
pod wskazany adres docelowy.

Aby dodać własny nagłówek:

```
strona nagłówek: ( 
	Nagłówek-HTTP nowy
	klucz: ['Content-Length']
	wartość: 400
).
```

Aby wyświetlić stronę 404:

```
strona nie-znaleziono: ['Ups..'].
```


## Szablony

Domyślny system szablonów jest bardzo prosty. Nie musisz uczyć się
nowej składni szablonów. Ponadto silnik szablonów zapewnia rzeczywiste oddzielenie
prezentacji od logiki biznesowej.

Aby utworzyć szablon z pliku:

```
>> tpl := strona szablon: ['templates/ux.tpl'].
```

System szablonów używa znaczników. 
Istnieją trzy rodzaje znaczników: znaczniki wycinania, znaczniki wklejania i
znaczniki miejsc. Podstawowa idea jest naprawdę prosta: wycinasz
obszary oznaczone znacznikami wycinania i możesz wkleić je w
obszarach oznaczonych znacznikami wklejania. Do znaczników miejsc
możesz wstawiać teksty.

Na przykład przy następującym szablonie umieśćmy
klejnot w szkatułce i dodajmy metkę z ceną.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Możesz to zrobić w następujący sposób:

```
>> gem := tpl wytnij: ['gem'], kopiuj.
gem price: 99.
tpl wklej: gem w: ['jewels'].
strona wypisz: tpl uporządkuj.
```

Ostatni wiersz po prostu wysyła szablon jako tekst do klienta
wraz z wymaganymi nagłówkami HTTP.

Wynik:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

Aby bezpiecznie udostępniać pliki przesłane przez użytkowników, możesz skorzystać z passthru:

```
>> przesłane := ['smile.gif'].
Server przekaż: przesłane prefiks: ['/uploads/images/'].
Program koniec.
```

W ten sposób treść przesłana przez użytkownika zostanie udostępniona z odpowiednim
typem MIME. Obsługiwane są tylko typy MIME z białej listy:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF i SVG.
Pliki SVG, ZIP i GZIP są wysyłane do pobrania, ponieważ plik SVG
może zawierać skrypty, które w przeciwnym razie zostałyby uruchomione w Twojej domenie.
Ta metoda zapobiega atakom TOCTOU, przechodzeniu po ścieżkach (path traversal),
wykonaniu złośliwego kodu (wstrzykiwaniu), atakom z użyciem dowiązań symbolicznych,
atakom DDoS (limit pliku = 50MB), atakom podsłuchu (sniffing) i
wielu innym problemom bezpieczeństwa.


## JSON

Aby zakodować obiekt jako JSON:

```
>> json := ( JSON jsonify: ( 
	Słownik nowy umieść: ( 
		Lista nowy ; 1 ; 2 ; 3
	) w: ['abc']
)).
```

Aby zdekodować JSON do obiektu xoscript:

```
>> słow := ((JSON obiekt: json) abc ? 1).
```

JSON z więcej niż 500 poziomami zagnieżdżenia jest odrzucany jako niepoprawny.

Aby bezpośrednio wypisać Słownik jako json z poprawnymi nagłówkami:

```
strona json: słow.
```


## Wyrażenia regularne

Wyrażeń regularnych możesz używać, tworząc wzorzec.
Na przykład, aby dopasować atrybuty href i target hiperłączy:

```
Wzorzec nowy: ['href="([^"]+)" target="([^"]+)"'].
```

Teraz zastosuj wzorzec do przeszukiwanego tekstu w następujący sposób:

```
wyrażenie dopasuj: temat wykonaj: { :m :x .... }
```

Pełny przykład:

```
>> temat := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> wyrażenie := Wzorzec nowy: ['href="([^"]+)" target="([^"]+)"'].
>> wynik  := wyrażenie dopasuj: temat wykonaj: { :m :x
	Wyjście pisz: m, nowa-linia.
	Wyjście pisz: x, nowa-linia.
	<- ['XXX'].
}.
Wyjście pisz: wynik, nowa-linia.
```

## Sieć

Do wykonania żądania WWW użyj obiektu Sieć.
Obiekt Sieć zawsze wysyła żądanie POST, chyba że jako dane wyślesz Nic;
wtedy wyśle żądanie GET.


```
Sieć 
post: Nic 
do: ['https://redbeanphp.com'].
```

## Szyfrowanie

Wtyczka serwera zawiera szyfrowanie oparte na XChaCha20 i Argon2.

Przykład:

```
>> zaszyfrowane := Sejf szyfruj: ['hello'] klucz: ['world'].
>> odszyfrowane := Sejf szyfruj: zaszyfrowane klucz: ['world'].
```

## Tokeny

Aby wygenerować kryptograficznie bezpieczny token o określonej długości:

```
>> mójtok := Sejf token: 40.
```

Spowoduje to wygenerowanie tokenu o długości 40 znaków.

## Formatowanie

Obiekt Format pozwala formatować dane, na przykład dopełniać je lub
dodawać zera. Używa składni printf.

```
>> fmt := Format nowy: ['%06.0f'].
fmt zastosuj: 56. # daje 000056
```

Format może zawierać jedną konwersję, która musi pasować do wartości,
w przeciwnym razie otrzymasz błąd:

- `zastosuj:` z tekstem: `%s`
- `zastosuj:` z liczbą: `%f`, `%e`, `%g` lub `%a`
- `zastosuj-całkowitą:` z liczbą: `%d`, `%i`, `%o`, `%u`, `%x` lub `%c`

Wartości z żądania są tekstami. Aby sformatować taką wartość jako liczbę,
najpierw ją przekonwertuj:

```
fmt zastosuj: (żądanie get: ['amount']) liczba.
```

## Kodery

Dostępnych jest kilka koderów i dekoderów.
Koder url przygotowuje adres url do użycia w HTML jako łącze:

```
Server url-koduj: ['https://example.com?a=6&b=1 2'].
```

Aby bezpiecznie wstawiać dane wprowadzone przez użytkownika do HTML bez ryzyka
ataków XSS, zawsze używaj:

```
Server html-koduj: ['<harmless>'].
```

Zauważ, że silnik szablonów zawsze wykonuje kodowanie html,
gdy zapisujesz do znacznika miejsca. Jeśli więc używasz systemu szablonów,
nie musisz tego stosować.

## Poczta

Aby wysłać wiadomość e-mail, użyj biblioteki mailtools.xo.

Przykład:

```
Server inicjuj.
Program użyj: ['mailtools.xo'].

>> wiadomość-email := HTML-Email nowy.
>> img := wiadomość-email załącz: ( Plik nowy: ['myimage.png'] ).

wiadomość-email
nadawca: ['xo@xoscript.com'] nazwa: ['xo'],
adresat: ( Lista nowy ; ['xo2@xoscipt.com'] ),
temat: ['xoxo'],
treść-wiadomości: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), wyślij.

```



## Łączenie bibliotek

Za pomocą wiadomości powiąż: możesz dołączyć do swojego programu
zewnętrzną bibliotekę, korzystając z libffi. Szczegóły znajdziesz w rozdziale o ffi.


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

FFI jest dostarczane w zależności od platformy/wtyczki, ponieważ
wiąże się z architekturą systemu bazowego, czego
rdzeń nie powinien robić.
Wtyczka serwera oferuje zgodną implementację ffi/blob.
Domyślnie rdzeń łączy się z platformą docelową
przez stdin/stdout, ograniczone usługi wejścia/wyjścia plików i powłokę (Program system:).
Dodatkową integrację zapewniają ffi/blob za pośrednictwem wtyczek
zorientowanych na aplikacje, takich jak wtyczka serwera.

FFI to skrót od Foreign Function Interface (interfejs funkcji obcych). Pozwala korzystać z funkcjonalności napisanych przez innych w
innych językach programowania, udostępnianych w plikach DLL, SO lub Dylib. Mogą to
być najróżniejsze funkcje, a dzięki tej metodzie dostępny jest ogromny zakres funkcjonalności.
Zacznijmy od przykładu:

```
Server powiąż: (
 Lista nowy ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Lista nowy ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s zwolnij.
```

W wyniku działania tego kodu zobaczysz w wierszu poleceń:
FFI has 3 letters.
Pewnie myślisz teraz: „To dużo kodu jak na coś tak prostego”.
Czy nie dałoby się tego rozwiązać poleceniem Gui show? Odpowiedź brzmi: zdecydowanie tak!
Jest to jednak przykład poglądowy.
FFI zwykle stosuje się do bardziej złożonych zadań, ale nie są one dobrymi
przykładami, więc wybrałem coś banalnego.

Argumenty metody powiąż:

- Argument nr 1: Plik DLL lub SO, którego chcesz użyć.
- Argument nr 2: Funkcja w tym pliku, którą chcesz powiązać.
- Argument nr 3: Lista z nazwami typów danych argumentów funkcji.
- Argument nr 4: Nazwa typu zwracanego przez funkcję.
- Argument nr 5: Nazwa obiektu, z którym chcesz powiązać tę funkcję (jeśli nie istnieje, zostanie utworzony
automatycznie).
- Argument nr 6: Wiadomość, z którą ta funkcja ma zostać powiązana.

W powyższym przykładzie chcemy powiązać funkcję printf z libc.so. Nazwy typów
danych znajdziesz w dokumentacji oprogramowania, z którym się łączysz. Dostępne typy to:
void, pointer, float, double, int, uint, char, uchar, intX i uintX,
gdzie X może wynosić 8, 16, 32 lub 64.

Typy te odnoszą się do liczby bajtów potrzebnych do przechowania danych. W przypadku printf łączymy ją z
nowym obiektem o nazwie Printf i wiadomością template:number:. Przed użyciem tłumaczysz zewnętrzną
funkcję na dialekt XOScript. Wiadomość template:number: oczekuje jako pierwszego parametru
bufora z tekstem szablonu. Tworzymy ten bufor za pomocą obiektu Blob, który
pozwala ręcznie przydzielać pamięć. Jesteś odpowiedzialny za późniejsze zwolnienie tej pamięci
za pomocą wiadomości zwolnij.

Blok pamięci (blob) możesz wypełnić na różne sposoby. W naszym przykładzie wypełniamy go tekstem, więc używamy
wiadomości utf8: (UTF-8 to kodowanie służące do przekształcania tekstu w bajty). Blob możesz też wypełnić za pomocą
bytes:, przekazując listę wartości bajtów. Aby odczytać zawartość obiektu blob, użyj od:długość:.
Otrzymasz bajty z powrotem jako listę. Za pomocą obiektu Blob możesz nawet utworzyć strukturę C, używając
wiadomości struct: i przekazując sekwencję typów C. Może to być konieczne przy wywoływaniu funkcji C
z zewnętrznej biblioteki oprogramowania, która oczekuje wskaźnika do struktury.

{warning}
Obiekty blob musisz zwalniać samodzielnie.
Obiekty blob nie są czyszczone przez mechanizm odśmiecania pamięci.
{/warning}

Ponieważ obiekty blob mogą być wymieniane z funkcjami zewnętrznymi z bibliotek,
nie mogą być automatycznie usuwane przez mechanizm odśmiecania pamięci (mogą nadal być używane przez
funkcje zewnętrzne albo te funkcje zewnętrzne mogą chcieć same je
zwolnić). Dlatego w razie potrzeby musisz samodzielnie zwalniać obiekty blob.

Aby zwolnić obiekt blob, użyj:

```
mójblob zwolnij.
```

Aby zwolnić strukturę, użyj:

```
mojastruct zwolnij-struct zwolnij.
```

W przypadku struktury musisz więc wysłać dwie wiadomości: zwolnij-struct i zwolnij,
aby zwolnić blok pamięci.

@api_Blob_fficonnect
