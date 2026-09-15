# Basics

{{messages}}


Welcome to XOScript
Le projet XOScript a pour objectif de créer un langage de script simple et auditable.
Simple ne signifie pas nécessairement facile.
Un langage de programmation familier peut être plus facile à utiliser que XOScript.
Ici, la simplicité signifie quelque chose de différent :
être capable de se construire un modèle mental complet du langage et de son comportement.

XOScript est conçu pour tenir dans votre tête.
Sa grammaire et le nombre de ses concepts sont volontairement réduits.
Il n'y a pas de classes ; les objets peuvent être étendus directement.
Les objets sont passés par référence, la copie est explicite,
et les fonctions n'ont qu'un seul point de sortie.

Certains de ces choix diffèrent sensiblement de ceux des langages courants.
XOScript n'a par exemple pas de système de types et utilise une portée dynamique.
Les messages qui ne peuvent pas être traités sont ignorés au lieu de provoquer une exception.
Ces choix ont des conséquences et ne sont pas destinés à éliminer les erreurs.
Ils visent à conserver un modèle sous-jacent du langage réduit et cohérent.

XOScript peut également être localisé, ce qui permet d'exprimer les
règles métier dans une langue naturelle et potentiellement de les partager
avec des parties prenantes non techniques.

L'auditabilité consiste également à appliquer la même philosophie à l'implémentation.
Le runtime est écrit en C, avec un lexer, un parser et un parcours de l'arbre syntaxique écrits à la main et de taille réduite.
La bibliothèque standard et le runtime reflètent en grande partie la structure du langage,
ce qui rend la relation entre le code XOScript et son implémentation relativement directe.

Les tests sont également étroitement liés à la documentation.
Chaque méthode devrait avoir un test associé qui peut être intégré au manuel,
ce qui contribue à maintenir la documentation synchronisée avec l'implémentation.

XOScript n'a pas pour objectif de concurrencer les langages courants en matière de
fonctionnalités ou de familiarité. Il explore un objectif différent :
un environnement de programmation qu'un développeur peut comprendre dans son ensemble.

L'espoir est qu'un langage de petite taille et une
implémentation de petite taille permettent de comprendre concrètement les logiciels,
de l'octet à l'objet, de la syntaxe au runtime, et d'écrire du code
avec confiance parce que l'on comprend à la fois ce qui se passe dans
le script et ce qui se passe sous le capot.

L'architecture d'une configuration de serveur xoscript
est simple, tout en restant flexible.

{{architecture.png}}

Pour utiliser xoscript comme langage côté serveur, vous devez installer le
plugin serveur dans un dossier appelé /mods/server.

Cela s'explique par notre volonté de
découpler le langage de base des fonctionnalités spécifiques au serveur,
contrairement, par exemple, à PHP ou Python. Sinon, nous devrions fournir
à tout le monde une solution complète et surchargée de fonctionnalités sans
raison valable, ce qui serait tout simplement absurde.
Vous pouvez également installer d'autres modules si vous le souhaitez. Le système est très flexible.

Certaines fonctions sont également mieux implémentées dans le langage de script
lui-même, comme la gestion des templates et des sessions. Nous fournissons donc
également les bibliothèques template.xo et webtools.xo pour vous faciliter la tâche.
La raison de tout cela est que nous ne savons pas comment vous souhaitez
utiliser xoscript. Vous pouvez l'utiliser comme langage de script côté serveur,
mais également pour des interfaces graphiques, des appareils embarqués ou simplement
pour du traitement par lots.
Même si vous l'utilisez comme langage de script côté serveur (ce qui constitue
actuellement l'un des principaux cas d'utilisation), vous pourriez tout de même
vouloir utiliser un autre moteur de templates ou un autre gestionnaire de sessions.
Qui sommes-nous pour décider que vous devez utiliser les nôtres ?

L'un des avantages de l'utilisation de notre propre moteur de templates est toutefois que
vous n'avez pas besoin d'apprendre une syntaxe supplémentaire pour créer des templates.
Le moteur de templates fourni par défaut avec xoscript utilise une séparation
à 100 % entre la présentation et la logique. Au lieu d'une syntaxe de template
spéciale, il utilise simplement un système très flexible de marqueurs d'emplacements.
Pour plus d'informations, consultez le chapitre Server.

Notez que si vous ne souhaitez pas utiliser le moteur de templates par défaut ou
les webtools par défaut, il va de soi que vous devrez fournir les vôtres.

Si vous exécutez votre serveur web dans un chroot, une jail ou tout autre type de sandbox,
vous devez également installer les dépendances de xo dans cet environnement. Vous pouvez
voir quelles bibliothèques sont nécessaires en utilisant ldd (voir la page de manuel de Linux ou BSD).
Si vous souhaitez utiliser des commandes shell dans vos scripts xo, copiez également un shell
(comme bash ou ksh) dans cet environnement.

Nous tenons également à préciser que nous accordons une grande importance à la compatibilité ascendante.
Il existe même une fonctionnalité spéciale de compatibilité ascendante appelée
'version'. De manière générale, notre objectif est que votre code fonctionne pour toujours.
Vous n'aurez donc jamais à mettre à jour votre code pour rester compatible avec les nouvelles versions
de xoscript. Notre objectif est le suivant : écrire une fois, exécuter pour toujours.

Le reste de ce manuel est consacré à l'explication détaillée du
langage de programmation xoscript. Les scripts côté serveur sont abordés dans le chapitre
appelé Server. Si vous êtes un développeur logiciel expérimenté, vous souhaiterez peut-être
sauter quelques chapitres, car certains sont un peu trop détaillés ou
très similaires aux pratiques générales de programmation. Si vous avez déjà
de l'expérience avec plusieurs autres langages de programmation,
il vaut donc mieux considérer ce manuel comme un guide de référence.

## Setup Linux

Download apache2 and mariadb:
```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Download xoscript.
Replace X with the correct version number!
```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Copy the files to the webroot and /bin:
```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Edit your apache2 config:
```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Replace Virtualhost with:
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

Create a test page:
```
sudo nano /var/www/html/test.xo
```

and write a little test program:
```
#!/bin/xo
Server init.
Program use: ['webtools.xo'].
>> web := Web-Document new.
web out: ['Hello World'].
```

Allow apache2 to execute your program through CGI:
```
sudo chmod uog+x /var/www/html/test.xo
```

Restart apache2:
```
sudo systemctl restart apache2
```

Go to your test page in the browser:
```
http://localhost/test.xo
```

You should see:
```
Hello World
```

## Setup OpenBSD

Edit /etc/httpd.conf, add:
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

Add the xo binary and mods, as well as any dependencies in the
chroot (figure out with ldd).

## Run examples

To run one of the example programs in the package:
```
./example.sh <name> <Linux/OBSD> [clean]
```

For example, to run the FizzBuzz example on Linux:
```
./example.sh fizzbuzz Linux
```

To run the same example on OpenBSD:
```
./example.sh fizzbuzz OBSD
```

To run the example with a clean build:
```
./example.sh fizzbuzz OBSD clean
```

## Unit tests

To run the unit tests:
```
./runtests.sh
```

To run the unit test without building (just testing):
```
./runtests.sh nobuild
```

## Build

To build from source on Linux:
```
make clean
ISO="en" make
```

On OpenBSD:
```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

To build the server plugin on Linux:
```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

To build the server plugin on OpenBSD:
```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Hello world

After it has been transferred to your computer, you can extract the file
and start xo by using the following command:
```
xo
```

To run a XOScript, store the program as a file by adding -xo
suffix (optional). In addition, insert the file name of your program
after the XOScript command:
```
xo myprogram.xo
```

When you run a XOScript command while using your program file as a
parameter, xo will read and execute your program file.

{{note}}
You can also start your program by dragging it to the xo pictogram.
{{/note}}

{{warning}}
On some systems you need to allow xo permissions to load dynamic
libraries beforehand.
{{/warning}}

Tradition dictates that the first program in any new programming
language should be a kind of salute to the world. In XOScript, such a
**Hello world** program looks like this:

@test598

When this text is saved to a file, e.g. hello.xo, it can be executed as
follows: .

xo hello.xo

Hello world


You can see the program output in the above-shown black window.
Throughout this manual, the same visualisation will be applied to show
the output.

{{note}}
Out is written with an uppercase O.
In general objects start with an uppercase letter
unless it acts as an instance (has no methods of
its own, just data). This mirrors class vs instance
conventions in other programming languages.
{{/note}}

## Syntax

XOScript est un langage de programmation *purement* *orienté objet*. Cela signifie
que xoscript considère tout comme un objet et qu'il n'existe donc pas d'autres
*types de données*. Il existe essentiellement trois actions fondamentales dans
un programme écrit en XOScript : *assignation*, *envoi de messages*
et *réponse*. L'échange de messages entre les objets constitue l'élément central
d'un programme XOScript. Les trois actions fondamentales sont illustrées
ci-dessous :

| Action | Exemple |
| ------ | ------- |
| assignation |  \>\> x := 1. |
| message unaire | x even?. |
| message binaire | 1 + 2. |
| message à mots-clés | x from: 0 length: 10. |
| réponse | <- answer. |

Ce chapitre vous donnera une première impression générale du langage XOScript
et décrira ses principes fondamentaux. XOScript est un petit langage fondé
sur trois actions (voir illustration), qui se traduisent par
environ six règles de grammaire. C'est tout ce qu'il faut pour maîtriser
le langage.

Ne vous inquiétez pas si certaines choses ne sont pas immédiatement évidentes :
toutes les briques seront étudiées dans le chapitre suivant (3) et les règles
fondamentales seront répétées. Le présent chapitre sert toutefois principalement
d'introduction générale au langage. Les principes fondamentaux seront expliqués
brièvement et illustrés par plusieurs exemples pertinents. Les détails manquants
seront présentés ultérieurement.

Les commentaires en XOScript sont précédés du symbole \#. La ligne suivante
sera donc ignorée :
```
# this is just a comment
```

## Variables

Pour effectuer une assignation,
vous utilisez le symbole de déclaration de variable : >>. Le nom d'une
variable peut contenir tous les caractères à l'exception de : <-, :=, espaces,
points, virgules, deux-points, guillemets [' '], et parenthèses ().
De plus, une variable ne peut pas s'étendre sur plusieurs lignes. Notez
qu'une variable ne peut pas commencer par un chiffre ou un signe moins.

Voici des exemples de variables valides :
```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dollar'].
>> +plus := True.
>> user-password := ['Pssst!'].
```

Les variables invalides sont par exemple :
```
>> -123 := ['negative number'].
>> password of user := ['Classified'].
>> password.of:user := ['Classified'].
>> ,x := 10.
```

{{note}}
Vous n'avez pas besoin d'échapper quelque caractère que ce soit
(y compris les guillemets, les guillemets doubles et les
délimiteurs de chaîne) dans
un littéral de chaîne tant que cela ne
provoque pas d'ambiguïté pour le lexer.
{{/note}}

Une fois qu'une variable a été déclarée, elle peut être utilisée librement.
Cela signifie qu'il suffit d'utiliser le symbole de déclaration la première
fois que vous utilisez la variable (lors de sa déclaration).

Plus précisément, vous ne pouvez pas commencer arbitrairement à affecter une
valeur à votre variable *(x := 2)*, car vous devez d'abord déclarer la variable
*(\>\> x := 2)*. Cependant, une fois la variable déclarée, vous pouvez modifier
sa valeur sans utiliser le symbole de déclaration *( \>\> x := 2. x := 3.)*.

Notez qu'il est obligatoire d'affecter une valeur à une variable au moment
de sa déclaration. Contrairement à d'autres langages de programmation, vous
ne pouvez pas déclarer une variable sans valeur. Il est essentiel d'associer
explicitement chaque variable à une valeur initiale. Vous pouvez néanmoins
initialiser la variable avec l'objet **None**. Dans ce cas, la variable peut
être considérée comme vide *(\>\> x := None.)*. En bref, il n'est pas permis
de déclarer une variable sans valeur initiale. Ainsi,
```
>> x.
```

est invalide et provoquera un message d'erreur.

{{note}}
xoscript utilise une portée dynamique pour les variables ;
pour plus de détails, consultez le chapitre Functions.
{{/note}}

## Literals

XOScript considère tout comme un objet, c'est-à-dire tous les nombres, les chaînes
et les fragments de code. Les nombres tels que 1, 2, 100, -999 et 1,234 sont
des objets Number. Tous les textes placés entre des guillemets simples sont des
objets String. Tous les fragments de code regroupés entre accolades {...} sont
des objets Function.

| Littéral | Objet racine | Exemple |
| -------- | ------------ | ------- |
| nombres | Number | 1,2,3... |
| chaînes | String | $begin:math:display$\'hello\'$end:math:display$ |
| fonction | Function | { 1 + 2. }. |

Les objets tels que les nombres et les chaînes trouvent toujours leur origine
dans un objet racine. Par exemple, tous les nombres dérivent de l'objet
**Number**. Toutes les chaînes dérivent de **String** et tous les fragments de
code de **Function**. À leur tour, tous ces objets proviennent de **Object**,
qui est en fait l'objet racine de tous les objets.

## Messages

Programmer en XOScript signifie essentiellement
envoyer des messages aux objets. La notation générale permettant d'envoyer un
message à un objet est la suivante :
```
<object> <message>
```

Pour déterminer si le nombre **2**, par exemple, est un nombre pair, le message
**even?** est envoyé à l'objet **2** :
```
2 even?
```

La réponse sera **True** (à nouveau, un objet). Les messages inconnus sont
généralement ignorés par les objets ; aucune erreur ne se produit donc.
Certains objets (par exemple les nombres ou les chaînes) répondent à un message
inconnu d'une manière prédéfinie (nous reviendrons plus en détail sur ce sujet).

Un objet peut recevoir trois types de messages.

| Type | Nombre d'arguments |
| ---- | ------------------ |
| Unary | 0 |
| Binary | 1 |
| Keyword | 1+ |

Tout d'abord, il existe les **messages unaires**, comme dans l'exemple
ci-dessus, qui ne prennent aucun argument. Ensuite, il existe les
**messages à mots-clés**, qui possèdent un ou plusieurs arguments, par exemple :
```
>> x := Number between: 1 and: 10.
```

Dans ce cas, le message **between:and:** est envoyé à **Number**, qui
est l'objet racine de tous les nombres. Le résultat sera un nombre aléatoire
compris entre 1 et 10. Enfin, il existe les **messages binaires**, qui
ne comportent qu'un seul caractère et un seul argument :
```
2 + 3
```

Cela ressemble à une addition mathématique, mais il s'agit en réalité
simplement d'un autre message. Le message **+** est envoyé à **2**, avec
l'argument **3**, ce qui renverra la réponse **5**. Les messages binaires
peuvent être écrits sans deux-points.

Les messages binaires peuvent être chaînés :
```
>> x := 3 + 2 - 1.
```

Dans ce fragment, **+ 2** est d'abord envoyé à l'objet **Number** **3**,
ce qui produit l'objet Number **5**, après quoi **-1** est envoyé à ce nombre.
Les lecteurs attentifs auront raison de remarquer la différence que ce
protocole présente par rapport à l'ordre conventionnel des opérateurs
mathématiques. XOScript ignore l'ordre mathématique au profit de la cohérence
de son système de messages. Ainsi, la somme :
```
2 + 3 * 5 = 25
```

et non 17.

Cela est intentionnel. Les parenthèses peuvent être utilisées pour modifier
l'ordre d'évaluation :
```
2 + (3 * 5) = 17
```

La plupart des objets renvoient eux-mêmes comme résultat en réponse à certains
messages. Cela est utile, car cela permet de poursuivre le dialogue avec cet
objet en lui envoyant un message supplémentaire :
```
Out write:
[' hello '] trim upper.
```

```
HELLO
```

Ici, deux messages sont envoyés à l'objet **String** : **trim**, suivi de
**upper**.

Dans le fragment suivant, l'utilisation d'une virgule est nécessaire pour
indiquer qu'un nouveau message arrive. Sinon, XOScript sera désorienté.
```
Out write: ['Hello!'], stop.
```

Tout d'abord, le message **write:** est envoyé au symbole crayon, suivi de
**stop**. Sans la virgule, XOScript penserait que vous souhaitez envoyer
**stop** à la **string** **Hello!**, ce qui serait un exercice futile.

La séquence de traitement des messages est la suivante : de gauche à droite ;
commencez par les messages entre parenthèses, suivis des messages unaires.
Viennent ensuite les messages binaires, puis les messages à mots-clés. Voir
l'exemple ci-dessous :
```
Out write: 0.5 round + (2 - 1), stop.
```

XOScript lit toujours de gauche à droite : tout d'abord, le message **write:**
est envoyé à Out, puis vient le message **stop**. À l'intérieur de l'argument
lui-même, XOScript lit de gauche à droite, donc **0.5 round** puis **+**.

{{note}}
Le message stop ajoute un caractère de nouvelle ligne à la chaîne.
Le nom de ce message s'inspire des systèmes télégraphiques.
Dans les systèmes télégraphiques, le mot STOP
était souvent utilisé pour marquer la fin d'une phrase
(car la ponctuation était peu fiable ou coûteuse).
{{/note}}

De plus, **round** est prioritaire sur **+**, car il s'agit d'un
**message unaire**. En raison des parenthèses, **2 - 1** est calculé
en premier, après quoi **1** est ajouté au résultat de **0.5 round** (1).

L'ensemble du processus donne le résultat **2**, qui constitue également la
réponse affichée. Après la virgule vient le message stop, qui déplace le
curseur à la ligne suivante. Bien entendu, la meilleure façon de comprendre
pleinement l'ordre d'évaluation des programmes XOScript est de pratiquer.

Il convient de noter qu'en XOScript, contrairement à de nombreux autres langages
de programmation, les espaces sont une partie fondamentale de la syntaxe.
Cela peut notamment prêter à confusion lorsqu'il s'agit de messages binaires.
Utilisez toujours un espace après un message binaire. Vous ne pouvez pas
directement accoler un nombre au message, par exemple :
```
3 + 2
```

est différent de
```
3 +2
```

Dans le premier exemple (**3 + 2**), le message **+** est envoyé au nombre
**3**, avec comme argument le nombre **2**. Le résultat sera dans ce cas **5**.
Dans le second exemple (**3 +2**), le message unaire **+2** est envoyé au
nombre **3**. Selon le contexte, cela peut produire un résultat très différent.

## Non-existing methods

L'envoi d'un message à un objet invoque la fonction qui a été
associée à cet objet sous le nom de ce message. Si vous envoyez un message
qui n'est pas compris, l'objet récepteur ignorera votre message et renverra
à la place une référence à lui-même afin de permettre la poursuite de la
communication. C'est ce que l'on appelle le passage de messages tolérant.

Exemple :
```
Out write: Object blah, stop.
```

Cela ne provoquera pas d'erreur. Le texte **Object** sera simplement affiché.

## Control Flow

En XOScript, il n'est pas nécessaire de disposer de règles de grammaire
distinctes pour les *boucles* et les *conditions*. Une instruction if
est simplement un message **true:** ou **false:** envoyé à un objet
**True** ou **False** :
```
2 even? true: {
	Out write: ['Two is an even number'], stop.
}.
```

Dans l'exemple précédent, le message **true:** est envoyé à **True** (la
réponse à la question : 2 est-il un nombre pair ?). Un fragment de code
supplémentaire est envoyé comme argument : un objet **Function**. Cette
fonction écrit à l'écran que 2 est effectivement un nombre pair.

Il n'est pas non plus nécessaire de disposer de règles d'écriture distinctes
pour une *boucle*. Pour exécuter un fragment de code trois fois, il suffit
d'envoyer **\*** avec l'argument **3** à cette **Function** :

@test5

Dans ce fragment de code, **i** est l'index. Ainsi, la première fois que la
Function est exécutée, **i** vaut 0, la fois suivante **i** = 1, et ainsi de suite.

Considérons un autre exemple. Lorsqu'une table de conversion de *kJ*
(kilojoules) en *kcal* (kilocalories) doit être affichée par pas de 100,
la notation correcte est la suivante :

@test599

Ici, le numéro de la ligne courante est transmis au paramètre **:line**.
Au début d'une fonction, les paramètres de la fonction sont définis.
Les paramètres inutilisés restent vides (**None**). Les paramètres sont
toujours placés au début de la fonction, directement après l'accolade
ouvrante initiale, et sont précédés de deux-points.

Le message **while:** est une combinaison d'une *boucle* et d'une
*condition*. Deux fonctions peuvent être liées à l'aide du message
**while:**. La fonction réceptrice continuera à s'exécuter jusqu'à ce que
la fonction située après les deux-points renvoie un résultat négatif.
Exemple :

@test600

Dans le fragment de code illustré ci-dessus, **1** est ajouté à **x** tant
que **x** est inférieur à **5**. Lorsque ce n'est plus le cas, la seconde
fonction répondra **False**, ce qui entraînera la fin de l'exécution de
la première fonction. Notez que **x** a été défini en dehors de la fonction
et qu'il s'agit donc d'une variable globale. Pour en savoir plus sur les
règles de portée, consultez le chapitre Functions.

## String interpolation

La liste *kJ/kcal* pourrait être présentée de manière plus élégante.
Idéalement, elle devrait se présenter ainsi :
```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Lorsque vous transformez la sortie souhaitée en template, sa notation
pourrait être :
```
number1 kJ ➞ number2 kcal
```

Cela signifie que **number1** représente la valeur en kJ et **number2**
la valeur en kcal. C'est ainsi que fonctionne l'interpolation de chaînes
en XOScript. Aucune règle de grammaire distincte n'est nécessaire pour
cela en XOScript. Il suffit d'envoyer au texte le mot à remplacer, avec
le texte de substitution comme argument :
```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

Le résultat :
```
100 kj ➞ 23.9 kcal
```

Cette règle de substitution fonctionne pour tout message non défini reçu
par un objet **string**. Chaque message qui n'est pas reconnu par l'objet
**string** sera interprété comme suit : *remplacer le texte du message par
le texte contenu dans son argument*. Vous pouvez adapter le programme
comme suit :

@test601

Pour éviter toute confusion concernant les messages pouvant ou non être
utilisés comme substituts, il est préférable d'introduire un marqueur de
template tel que &lt; &gt; pour les segments de texte du template
qui doivent être remplacés.

## Return values

Pour répondre à un message, on utilise la flèche de retour
(*<-*). L'exemple suivant montre comment créer une tâche permettant
de calculer un pourcentage :

@test602

Une fois la tâche définie et affectée à la variable **percentage**,
le message **apply:and:** est envoyé avec les arguments **100** et **7**.

Cela exécutera la tâche avec **100** et **7**, c'est-à-dire 7 % de 100.
À l'aide de la flèche de retour, la réponse est renvoyée de la tâche
vers le programme principal.

## Extending

Bien que ce code soit valide, il présente un inconvénient :
il faut mémoriser l'ordre des arguments. Alors, pourquoi ne pas
l'écrire ainsi : *7 percent of: 100 * ? Cela semblerait beaucoup plus
*naturel*. Pour rendre cela possible, nous devons adapter l'objet parent
de **7**, qui est l'objet **Number**, afin qu'il comprenne le message
**percent of:**. Cela peut être réalisé en envoyant **on:do:** à l'objet
Number, comme ceci :

@test603

Comme le pourcentage est, dans ce cas, le nombre lui-même, nous faisons
référence à self, le mot-clé *self*. En bref, le symbole self signifie :
*envoyer ce message à moi-même*.

# Objects

{{messages}}

En plus d'adapter et d'étendre des objets existants, vous pouvez également
créer vous-même de nouveaux objets en envoyant simplement le message
**new**. Supposons que vous souhaitiez créer un objet invoice qui impose
une séquence de numérotation ; dans ce cas, vous aurez d'abord besoin
d'un objet invoice.

Sachant que chaque objet dérive d'un autre objet qui, à son tour, trouve
finalement son origine dans l'objet racine de tous les objets appelé Object,
il faut choisir sur quel autre objet votre nouvel objet sera fondé. Votre
nouvel objet hérite de toutes les propriétés de l'objet sur lequel il est
fondé, c'est-à-dire de l'objet auquel le message **new** a initialement
été envoyé.

Dans cet exemple, on privilégie un objet plutôt neutre, qui ne possède
pas trop de propriétés héritées. Le choix est alors simple, puisque le
nouvel objet peut être basé directement sur l'objet racine lui-même,
à savoir **Object**. La notation du système de facturation souhaité sera
alors la suivante :

@test604

Le numéro de facture courant est stocké dans l'objet ; c'est pourquoi le
mot-clé **own** est placé devant celui-ci. On appelle cela une *propriété* ;
nous y reviendrons plus en détail.

Certaines entreprises préfèrent intégrer l'année dans les numéros de
facture. Dans ce cas, vous pouvez créer un nouvel objet invoice fondé sur
un ancien objet invoice, mais qui offre à son utilisateur la possibilité
de saisir une année donnée :

@test605

Il n'est pas nécessaire de réécrire l'implémentation du message **number**,
car celui-ci est hérité de l'**invoice object** précédemment écrit ; l'ancien
code peut donc être réutilisé. XOScript ne possède pas de concepts tels
que les classes ni les concepts qui leur sont associés. Cela signifie que
les objets peuvent uniquement hériter d'autres objets, ce que l'on appelle
également l'*héritage prototypal*.

Revenons maintenant aux propriétés. Les propriétés des objets ne peuvent
être consultées que *depuis l'intérieur de la hiérarchie des objets* ;
elles ne peuvent donc pas être perçues par les autres objets.

Contrairement à d'autres langages de programmation, toutes les propriétés
des objets sont exclusivement visibles par l'objet qui a créé la propriété
et par les objets qui en dérivent.

Une technique couramment utilisée consiste à employer un objet comme une
sorte de *modèle*, comme c'est par exemple le cas des factures évoquées
précédemment. Un autre bon exemple est **Point**. Supposons que vous créiez
un programme informatique qui effectue des calculs à partir de points sur
une carte. Vous pouvez développer l'objet **Point** contenant les propriétés
d'une coordonnée x et d'une coordonnée y, qui seront rendues accessibles
au monde extérieur par l'intermédiaire de messages :

@test606

Le message **=** compare les deux points à l'aide du message **and:**.
La première comparaison produit un objet **True** ou **False**. Ce sont
des objets booléens. Lorsque vous envoyez le message **and:** à un objet
True et que l'objet passé comme argument après les deux-points est également
**True**, vous recevrez à nouveau **True** comme réponse. Si l'un des deux
est **False**, vous recevrez **False**. Notez qu'un point ne peut pas lire
les coordonnées de l'autre. Il est nécessaire d'envoyer un message à
l'autre point pour lui demander ces données : **x-coordinate** et
**y-coordinate**. Après tout, comme cela a déjà été expliqué, les propriétés
ne sont accessibles qu'au sein de la famille d'objets elle-même.

Notez que le message **=** est utilisé ici pour effectuer la comparaison
des points. De la même manière, un autre message aurait pu être utilisé,
tel que **is:** ou **equal:** ; toutefois, réutiliser le caractère **=**
semblait approprié dans ce cas.

## Inheritance

Vous pouvez réutiliser du code précédemment écrit pour créer une hiérarchie
d'objets. Par exemple :
```
>> Animal := Object new.
>> Dog := Animal new.
>> Poodle := Dog new.
```

Dans ce cas, **Dog** hérite de tout le comportement et de toutes les propriétés
de **Animal** et, à son tour, l'objet **Animal** hérite de tout le comportement
de **Object**, l'objet racine de tous les objets.

## Overriding

Dans l'exemple suivant, un nouveau type de liste est créé :
**Combination**, dans lequel chaque élément est garanti comme étant unique.
Les fonctions de la liste sont réutilisées grâce à l'héritage :

@test607

Observez comment le deuxième **red** est exclu de la liste.

Il peut parfois être nécessaire de remplacer le comportement d'un objet.
Par exemple, lors de l'addition de nombres, les unités de mesure doivent
être prises en compte. Dans l'exemple suivant, l'objet **Size** est créé.
Cet objet renvoie un nombre qui, lors de l'addition, tient compte de l'unité
du nombre à ajouter. L'objet **Number** vérifie s'il s'agit d'*inches* ou
de *foot*. Le code pourrait ressembler à ceci :

@test608

## Recursion

Dans l'exemple précédent, le **signe** plus est redéfini. Notez qu'en fin
de compte, l'addition finale doit tout de même être effectuée, ce qui a
lieu sur la ligne suivante :
```
>> answer := self + (number x factor).
```

Maintenant, comment XOScript comprend-il que ce **signe** plus fait référence
à la logique d'addition originale ?** Une autre interprétation pourrait être
que XOScript envoie continuellement le même message au même objet, ce qui
entraînerait alors une **boucle infinie**. Ce n'est clairement pas l'intention.
Dès que vous envoyez à un objet un message qui exécuterait exactement le même
code, XOScript comprend que, dans ce cas, le message redéfini sous-jacent est
visé. Votre programme est donc automatiquement protégé contre cette forme
de boucle infinie. Cependant, lorsque votre intention est effectivement
d'exécuter la même fonction depuis la fonction courante, il est nécessaire
d'envoyer d'abord le message **recursive**. Dans ce cas, le résultat sera
une boucle infinie. Il existe toutefois des applications utiles de la
récursivité ; par exemple, supposons que vous souhaitiez calculer la
factorielle d'un nombre donné. Dans ce cas, il suffit d'ajouter le message
**factorial** à Number :

@test609

Cela nécessite de la récursivité. En effet, la tâche associée au message
**factorial** doit être exécutée à nouveau à l'intérieur de cette fonction.
Il est donc nécessaire d'invoquer la fonction factorial depuis la fonction
factorial elle-même. En règle générale, XOScript empêchera cette opération
en raison du risque de tomber dans une boucle infinie. Pour cette raison,
il est essentiel de faire précéder le message du mot **recursive**. Cela
permet d'indiquer à XOScript que vous avez l'intention d'exécuter la même
tâche
et que vous n'avez pas fait une erreur.

## Class-like Objects

Bien que xoscript ne propose pas de classes, il est trivial d'en imiter
le comportement. Il suffit de redéfinir le message new.
```
>> Animal := Object new.
Animal on: ['new'] do: {
	<- self new init.
}.

Animal on: ['init'] do: {
	own sound := ['?'].
	own legs  := 4.
}.
```

Dans le fragment de code ci-dessus, nous créons un objet appelé Animal.
Cet objet sert de *modèle* pour toutes sortes d'animaux, comme les chiens
et les chats. L'objet parent Animal est écrit avec un A majuscule pour
indiquer qu'il s'agit d'un objet de type *classe*. Nous redéfinissons
ensuite le message new en écrivant notre propre méthode new.
Dans ce cas, elle envoie le message new à self, suivi du message init.
Comme xoscript bloque la récursivité par défaut, cela ne provoquera pas
de boucle infinie. À la place, il enverra le message new à l'objet parent
(Object), ce qui produira une nouvelle instance de Animal. Nous créons donc
un nouvel objet basé sur le même objet pour lequel nous avons créé notre
méthode new. Cela est parfaitement valide. Nous envoyons maintenant
également le message init, ce qui garantit que l'objet Animal possède
des valeurs par défaut pour ses propriétés. Par défaut, un animal possède
4 pattes et son cri est inconnu (d'où le point d'interrogation).
Pour créer une nouvelle instance de notre Animal, nous pouvons simplement
écrire :
```
>> a := Animal new.
```

Nous obtenons alors une nouvelle instance de Animal avec 4 pattes, un cri
inconnu et une méthode init. Comme dans les autres langages de POO, nous
pouvons également étendre notre Animal :
```
>> Dog := Animal new.
Dog on: ['init'] do: {
	self init.
	own sound := ['barks'].
}.
```

Nous pouvons facilement tester cela en ajoutant une méthode string :
```
Animal on: ['string'] do: {
	<- own legs string + own sound.
}.
```

Mettons tout cela ensemble :

@test13

Créer un objet qui se trouve dans un état initial donné constitue un
problème fréquent. Supposons qu'un objet **Rectangle** doive être créé
afin de calculer son périmètre et sa surface. Une notation possible serait :
```
>> Rectangle := Object new.

Rectangle on: ['area'] do: {
	<- own length * own width.
}.
```

Il est évident que définir une longueur et une largeur constitue une
précondition. À cette fin, les messages **length:** et **width:** peuvent
être ajoutés :
```
Rectangle on: ['length:'] do: { :length
	own length := length.
}.

Rectangle on: ['width:'] do: { :width
	own width := width.
}.
```

Ce rectangle peut ensuite être utilisé comme suit :
```
>> rectangle := Rectangle new length: 2, width: 3.
Out write: rectangle area.
```

Cependant, si les valeurs initiales de length et width sont oubliées,
un message d'erreur sera généré :
```
>> rectangle := Rectangle new.
Out write: rectangle area.
```

produira l'erreur suivante :
```
Key not found: length
```

Pour éviter cela, il est préférable qu'un rectangle possède toujours une
longueur et une largeur initiales, par exemple 0. Dans ce cas, il est
nécessaire de **redéfinir** le message **new**.

@test610

Lorsque nous redéfinissons le message new, nous imitons essentiellement
une **classe**.

Le monde de XOScript regorge d'une grande diversité d'objets, qui sont
disponibles pour votre programme dès le départ. Dans les chapitres suivants,
tous ces objets fondamentaux seront présentés.

## Snapshots

Vous pouvez enregistrer un objet (ainsi que son état actuel) sur le disque avec :
```
myobject save-as: ['saved.bin'].
```

Pour recharger l'objet depuis le disque :
```
>> myobject := Object load-from: ['saved.bin'].
```

Les snapshots peuvent être utilisés pour enregistrer un certain état ou pour
améliorer les performances.
Le chargement d'un snapshot évite les étapes de lexing, de parsing et de
configuration de l'application.
À l'avenir, des gains de performances supplémentaires pourront également être
introduits avec les snapshots, comme l'optimisation de certains patterns ou la
détection et l'optimisation des chemins d'exécution fréquents.

{{warning}}
Les snapshots sont une fonctionnalité expérimentale, ne les utilisez pas en production.
Pour activer les fonctionnalités expérimentales, compilez avec -D EXPERIMENTS.
{{/warning}}

@test712

# None Object

{{messages}}

L'objet None
représente le vide, ou mieux encore, l'absence d'information. Il vous
arrivera parfois de recevoir cet objet en réponse à un message, lorsque
le résultat est **rien**. La question la plus essentielle que vous
puissiez poser à l'objet **None** est : **None?**. La
réponse sera toujours **True**.
```
Out write: None None?.
```

résultat :
```
True
```

Tout objet autre que **None** répondra par **False**. Le fragment de
code ci-dessus peut sembler quelque peu philosophique, mais l'objet **None**
a bien des applications extrêmement pratiques. Par exemple, vous
recevrez l'objet None en réponse si vous demandez un élément de liste
qui n'existe pas. Vous pouvez également utiliser l'objet None
si vous souhaitez déclarer une variable, mais que vous ne voulez pas encore
lui attribuer de valeur. Il suffit d'**affecter** la valeur spéciale **None**.
Dans XOScript, il n'est pas permis de déclarer une variable sans valeur, comme ceci :
```
>> value.
```

Vous devez plutôt écrire :
```
>> value := None.
```

@api_None_base

# Booleans

{{messages}}

Contrairement à la plupart des langages de programmation populaires au moment
de la rédaction de cette documentation, XOScript ne fournit qu'un seul objet
True et un seul objet False. Pour clarifier, chaque fois que vous écrivez
**True**, cela n'implique pas qu'un nouvel objet ait été créé. Vous
utilisez toujours une référence. Ainsi, lorsque vous écrivez :

\>\> x := True.

**x** fait référence à l'objet **True**. Le code conditionnel et les
boucles vérifient également cette référence. Dans XOScript, la signification
de **True** et **False** n'est pas fixe. En fait, un programme XOScript
est sérieusement bouleversé par une instruction telle que :

True := False.

Le résultat de telles actions est indéfini, mais l'action reste valide et est
donc formellement autorisée. Il existe en outre un objet Boolean, qui est
l'objet racine de **True** et **False**, puisque tous deux sont des dérivés
de l'objet racine. L'objet Boolean lui-même ne fournit cependant aucune
application pratique.

## Gotchas

Soyez prudent lorsque vous utilisez **and:** et **or:**
```
Out write: (False or: True or: True), stop.
Out write: (False or: True, or: True), stop.
```

produit
```
False
True
```

car le message **or:** ne prend qu'un seul argument. Le premier message
envoie **or:or:** à False, qui n'existe pas ; l'objet ignore donc le
message et retourne lui-même (False). En revanche, la seconde ligne
envoie **or:** suivi d'un autre **or:** (en utilisant un symbole de
chaînage, c'est-à-dire une virgule : ,).


@api_Boolean_base

# Numbers

{{messages}}

Chaque fois que vous écrivez un nombre, par exemple 9, -10 ou 3,12, en
arrière-plan, XOScript convertit ces nombres en un objet **Number**.
Vous pouvez envoyer des messages à cet objet Number, ou affecter le nombre
à une variable puis lui envoyer des messages :
```
10 even?

>> tenner := 10.
tenner even?
```

Les deux notations sont valides. L'objet Number répond aux messages suivants...

La plupart de ces messages sont explicites et vous permettent d'effectuer
des opérations mathématiques ou des comparaisons.

{{note}}
Notez que vous pouvez utiliser ≤ ≥ ≠ × et ÷ à la place de leurs équivalents ASCII.
C'est une question de préférence.
{{/note}}

La différence entre les messages mathématiques binaires (+) et leurs
variantes à mots-clés (add:) est que les premiers retournent un nouveau
nombre, qui est le résultat de l'opération, tandis qu'avec les secondes
l'objet lui-même est modifié. Cela est illustré dans l'exemple suivant :

@test597

Dans l'exemple ci-dessus, b = 4 et a = 3. Avec **add: 2**, la valeur
de a est augmentée de 2, tandis que **+ 3** crée un nouveau nombre qui
est égal à a + 3. Il en va de même pour les autres opérations
mathématiques, par exemple les multiplications. En utilisant le symbole
de multiplication, vous recevrez un nouvel objet en réponse. Si vous
utilisez le message **multiply-by:**, vous multiplierez le nombre lui-même.

Avec le message **between:and:**, par exemple dans : **Number
between: X and: Y**, vous obtiendrez un nombre entre X et Y. De cette
façon, n'importe quel nombre aléatoire peut être généré :
```
>> a := Number between: 1 and: 10.
Out write: a, stop.
```

Depuis la version 1.4, le générateur intégré de nombres aléatoires de xoscript
est cryptographiquement sécurisé, à notre connaissance.

Vous pouvez attacher un **qualifier** à un nombre, par exemple **6
apples**. Chaque message qui n'est pas reconnu par un
nombre sera considéré comme un qualifier. Vous pouvez récupérer le qualifier
d'un nombre au moyen du message qualifier :

Un qualifier est essentiellement un objet Text qui est stocké avec l'objet
Number. Le qualifier est également affiché après le nombre lors d'une
affectation **write:**. Les qualifiers peuvent par exemple être utilisés
pour additionner des montants dans différentes devises. Lors de l'addition
des montants, vous pouvez demander leurs qualifiers. L'exemple de programme
suivant illustre ce principe à l'aide d'un convertisseur de devises historique
(le taux de change restant raisonnablement stable !).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Strings

{{messages}}

Chaque fois qu'un texte est placé entre **blocks and quotation marks** ['...'] ,
XOScript crée pour vous un nouvel objet string. Veillez toutefois à
utiliser les guillemets appropriés. Le guillemet au début du texte diffère
de celui à la fin (cela vous permet d'utiliser l'apostrophe simple sans
avoir besoin de l'échapper).

## UTF8

Les strings dans xoscript contiennent généralement du texte encodé en UTF8.
Bien qu'il soit techniquement possible d'avoir du contenu binaire ou non-UTF8
dans une string, il est recommandé d'utiliser des blobs pour cela. Les blobs
sont fournis par le plugin server (voir le chapitre ffi).
En général, les blobs/ffi sont fournis
au niveau du plugin/de la plateforme, puisqu'ils sont liés à la plateforme
et à l'architecture (ffi/blobs). Le cœur du langage de script essaie de
rester aussi indépendant de la plateforme que possible.

## Casting

Vous pouvez créer une copie de chaque objet
avec un type différent en utilisant les messages suivants :

| Message | Result |
| ------- | ------ |
| number  | Convertit en nombre |
| string  | Convertit en string |
| bool    | Convertit en booléen |

Les règles suivantes **s'appliquent** :

| message | None | Bool | Number | Text | Other |
| ------- | ---- | ---- | ------ | ---- | ----- |
| bool | False | n/a | 0→False else→True | True | Mostly True |
| number | 0 | False→0 True→1 | n/a | ['n']→n | Mostly 1 |
| string | ['None'] | ['False']/['True'] | ['n'] | n/a | Depends |

## Copying

Les valeurs dans XOScript sont toujours transmises **par référence**. Dans
d'autres langages, cela dépend du type de valeur ; dans XOScript, il n'existe
qu'une seule manière de procéder : par référence. XOScript ne fait jamais
de copie d'une valeur. Pour copier un objet, vous devez lui envoyer le message
**copy**.

@test611

Ici, vous auriez peut-être pensé que la sortie serait Dolly au lieu de Donny.
Cependant, ce n'est pas le cas, car les deux noms font référence au même
objet. Lorsque vous travaillez avec une boucle, quelque chose de similaire
se produit :

@test612

En fait, XOScript utilise **toujours** des références, donc sur
**:quantity**, la boucle illustrée ci-dessus indique également la référence
vers l'élément de la liste.

Pour copier un objet, vous devez spécifier cette action
**explicitement** :

@test613

En envoyant le message unaire **copy** à une string, l'objet
retourne une copie de cette même string. Il est possible de copier les objets
Number, les objets booléens, les listes et les dicts de la même manière.

Vous pouvez également définir votre propre implémentation de copy, ce qui est
même nécessaire si vous créez vos propres objets. L'implémentation par défaut
de copy pour une liste effectue une copie superficielle (shallow copy) :
elle crée une nouvelle liste contenant les mêmes éléments.

@test614

Dans ce cas, 4 est ajouté uniquement à la copie.
Cependant, puisque la copie est superficielle, les objets des deux listes
sont les mêmes.

@test615

Ainsi, si nous ajoutons 2 à chaque nom dans la copie, la liste originale
est également affectée.

Pour remédier à cela, nous devons effectuer une **deep copy**. Une telle
opération de copie pour une liste pourrait être composée comme suit :

@test616

Notez également le message recursive : ce message est nécessaire avant
d'envoyer le message copy.

Il est essentiel de garder à l'esprit que, bien qu'une copie d'un objet
ait souvent la même apparence que l'original, elle ne sera en réalité
jamais identique. L'objet racine définit un message **equal:**,
qui peut être utilisé pour comparer l'identité des objets. Examinez
l'exemple suivant :

@test617

## Implicit Conversion

XOScript utilise la **conversion implicite** pour convertir les objets. Pour
afficher une liste à l'écran, XOScript enverra par exemple en interne le message
*string* à la liste. Cela peut être très utile si vous souhaitez
afficher une liste séparée par des virgules. Le message *string*
peut être redéfini :

@test620

@api_String_base
@api_Format_base

## Server strings

Les fonctionnalités String suivantes sont ajoutées par le
plugin Server.

@api_String_server

# Functions

{{messages}}

Vous pouvez regrouper du code entre { et }, ce qui en fait une fonction.
Dans xoscript, nous utilisons également parfois le terme task, ou simplement
bloc de code.

Vous pouvez exécuter une fonction en lui envoyant le message *start*.


```
{ Out write: 123, stop. } start.
```

Si votre fonction prend des arguments, utilisez **apply:**.

```
{ :a Out write: a, stop. } apply: a.
```

Voir également les exemples ci-dessous.
En raison de son architecture simplifiée, une fonction ne peut avoir
qu'un seul point de retour. Pour éviter la surcharge ou un imbrication
excessive des conditions, vous pouvez utiliser une procédure (ce qui
revient à utiliser le signe de multiplication avec l'argument 1) :

```
{
  (a = 1) true: { x := 1. }, break.
  (a = 2) true: { x := 2. }, break.
} procedure.
```

Ainsi, (a = 2) ne sera pas évalué si a = 1.
De plus, vous n'avez pas besoin d'imbriquer plusieurs true-messages de cette
manière.
Chaque fois que vous vous retrouvez à imbriquer des conditions, pensez
au message procedure. Il pourrait rendre votre code
plus facile à lire.


Voici un piège important :

```
{
	False false: {
		Out write: ['End the loop.'].
	}, break.
	
	Out write: ['Dont show me.'].

} procedure.

```

Dans ce cas, le texte 'Dont show me' sera affiché.
Parce que **break** est envoyé à False. Si vous voulez exécuter
un break, il doit être envoyé comme message à **True**.


```
{
	False not true: {
		Out write: ['End the loop.'].
	}, break.
	
	Out write: ['Dont show me.'].

} procedure.

```

Cela fonctionnera comme prévu.

## Exceptions

Les exceptions peuvent être gérées comme ceci :

```
{ Task 1 } except: { Task 2 }, start.
```

Vous pouvez également provoquer intentionnellement une erreur dans votre
programme et, ce faisant, activer le bloc de gestionnaire. Pour cela, il
suffit d'envoyer le message **error:** à la task courante, comme illustré
dans l'exemple suivant :

```
{
this-task error: ['Whoops!'].
} except: { :mistake
Out write: mistake.
}, start.
```

## Injecting values

XOScript permet aux tasks d'injecter des valeurs. Examinez maintenant
la task ci-dessous :

```
>> sending := {
	Newsletter to: own recipient.
}.
sending set: ['recipient']
value: ['info@recipient.org'].
sending start.
```


Cet exemple présente une task imaginaire qui envoie une newsletter à une
adresse e-mail ou **recipient**. Ce recipient peut être injecté dans la
task, de manière externe et avant le démarrage de la task, en envoyant le
message **set:value:** à la task. De cette manière, la valeur de
**recipient** est prédéfinie dans la task. Cette valeur peut également être
modifiée, puis la task peut être exécutée à nouveau. Il s'agit d'une méthode
utile lors de l'utilisation d'objets Task.

## Empty Functions

Les tasks vides ne sont pas autorisées. En théorie, une task vide ressemblerait
à ceci : **{}**, mais XOScript considère cela comme une erreur de langage. Si
vous souhaitez déclarer une task vide, vous pouvez utiliser l'objet None :

```
>> task := None.
```

Bien qu'il ne s'agisse pas d'une véritable task, mais d'un objet None, un
message start peut tout de même lui être envoyé :

```
>> answer := task start.
```

En fait, cela revient au même que :

```
>> answer := None start.
```

Comme l'objet **None** ne reconnaît pas le message **start**, il
retournera lui-même comme réponse, laissant à nouveau la réponse à
**None**.
Il n'est donc pas nécessaire d'avoir une task vide. Grâce à la conception
élégante du langage de programmation XOScript, vous pouvez simplement
utiliser l'objet None pour cela.

## Dynamic Scoping

Lorsqu'une fonction a besoin d'une variable mais ne peut pas la trouver,
elle vérifie les variables de la fonction qui l'a **appelée**, puis
continue à remonter la chaîne des fonctions.
Ce processus de recherche se poursuit jusqu'à ce que la variable soit trouvée.
Si la variable n'est toujours pas trouvée, un message d'erreur apparaît. Cette
méthode de recherche d'une variable est appelée **Dynamic Scoping**.

Pour illustrer ce principe :

@test618

@api_Code_base


# Root Object

{{messages}}

L'objet nommé **Object** est l'objet racine de tous les objets dans
XOScript et fournit les fonctionnalités fondamentales du langage.

Le message envoyé le plus fréquemment est
**on:do:**, qui étend les fonctionnalités d'un objet. Ce
message est reçu par l'objet racine, qui lie alors la task spécifiée au
message et, ce faisant, étend l'objet dérivé.

## Catch-all methods

Normalement, si vous envoyez un message qui ne correspond à aucune
méthode de l'objet, il est ignoré. Cependant, vous pouvez spécifier des
méthodes dites **magic methods** ou **catch-all**, qui seront
appelées si le message n'est pas compris par l'objet.

Il existe 4 méthodes catch-all disponibles. Chaque message correspond
à un nombre spécifique d'arguments.

| Catch-all message    | Number of arguments |
| -------------------- | ------------------- |
| respond:             | 0 |
| respond:and:         | 1 |
| respond:and:and:     | 2 |
| respond:and:and:and: | 3 |


@test619

## Programmatic messages

Au lieu d'envoyer directement un message à un objet, il peut également être
envoyé via une variable. Pour cela, vous utilisez le message
**message:arguments:**.

@test396

@api_Object_base

# Lists

{{messages}}

XOScript connaît deux types de collections : les *lists* et les *dicts*.
Les **lists** sont des énumérations d'objets dans un *ordre fixe*. Les dicts
n'ont pas d'ordre ; ils ressemblent plutôt à une légende associant une clé
(ou un terme) à la valeur correspondante. Les lists sont comparables aux
arrays (PHP, Java, C) et aux lists (Python).
Les dicts sont comparables aux tableaux associatifs (PHP) ou aux
dictionaries (Python) dans d'autres langages de programmation. Pour créer
une nouvelle List, écrivez :
```
>> fibonacci := List new.
```

Cette liste vide peut être remplie avec **append:** :
```
fibonacci append: 0.
fibonacci append: 1.
fibonacci append: 1.
fibonacci append: 2.
fibonacci append: 3.
fibonacci append: 5.
fibonacci append: 8.
fibonacci append: 13.
```

Si nous écrivons la liste à l'écran :
```
Out write: fibonacci, stop.
```

Nous verrons :
```
List ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

Au lieu de append, vous pouvez également utiliser ; pour ajouter des éléments
à une liste :
```
>> fibonacci := List new ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Les points-virgules (;) sont tous des messages binaires qui placent une
valeur dans la liste.

## Chaining

Supposons que vous ayez une liste telle que :
```
>> x := List new ; 1 ; 2 ; 3.
```

Si vous souhaitez supprimer le premier et le dernier élément, votre message
serait :
```
x shift pop.
```

Malheureusement, la notation précédente ne fonctionnera pas correctement. Le
message **shift** retourne le premier élément de la liste, qui, à son
tour, deviendra le récepteur du message **pop**. Ainsi, le message
**pop** n'est pas envoyé à **x**, mais à 2. Une solution possible
à ce problème serait de créer deux instructions distinctes, telles que :
```
x shift.
x pop.
```

Cependant, cela est plutôt peu pratique, en particulier lorsque vous devez
supprimer plus de deux éléments. C'est pourquoi XOScript propose une structure
de message alternative pour ce type de situation. Dans les structures de
messages **alternative**, les réponses des objets sont ignorées et vous
récupérez continuellement l'objet récepteur comme réponse.
Une structure de message **alternative** est initiée en envoyant le
message **do** à un objet et peut être terminée en envoyant le message
**done**. Dans l'exemple illustré, cela peut être appliqué comme suit :
```
>> x := List new ; 1 ; 2 ; 3.
x do shift pop done.
```

@api_List_collections

# Dicts

{{messages}}

**List et Dict sont tous deux des collections. Cependant, contrairement à
une list, un dict **n'a pas** d'ordre. Une autre distinction entre les deux
est qu'un dict est constitué de paires d'objets. Un objet agit comme entrée
(ou mot-clé) permettant de rechercher l'autre objet. Un bon exemple de list
est une liste de prix, telle que :
```
>> menu := Dict new
	put: ['£5'] at: ['apple pie'],
	put: ['£6'] at: ['carrot cake'],
	put: ['£3'] at: ['fudge'].
```

Comme pour une list, le message put:at:
est utilisé pour ajouter un objet à une collection. La différence est que,
contrairement à une list, deux objets sont liés. Le premier objet est, comme
pour une list, l'objet que vous allez stocker dans la collection. Le second
objet n'est pas sa position dans la collection, mais l'**entry**
qui permet de retrouver l'objet précédent ultérieurement. En bref, un dict
fonctionne un peu comme un dictionnaire ; en utilisant le mot-clé, on peut
retrouver la signification. Par exemple, pour récupérer dans la
collection mentionnée ci-dessus le prix d'un fudge :
```
>> price := menu at: ['fudge'].
```

Vous pouvez également utiliser la notation concise :
```
>> price := menu ? ['fudge'].
```

Si les entries que vous utilisez pour stocker les objets ne contiennent pas
d'espaces (et n'entrent pas en collision avec d'autres messages prédéfinis),
la notation suivante peut également être utilisée :
```
>> menu := Dict new
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Il ne fait aucun doute que la notation ci-dessus semble un peu plus naturelle.
Pour demander le prix d'un
fudge, la notation simplifiée suivante peut être utilisée :
```
>> price := menu fudge.
```

@api_Dict_collections

# File

{{messages}}

L'objet **File** fournit un accès de base au système de fichiers.
Vous pouvez utiliser cet objet pour lire des fichiers entiers dans une
variable en une seule fois, ou écrire des variables dans des fichiers en
une seule fois. La lecture ligne par ligne est également prise en charge.
Il s'agit des opérations d'E/S sur fichiers les plus courantes
dans un langage de script. Les opérations avancées sur les fichiers
nécessitent l'utilisation de FFI via le plugin Server ou d'un plugin IO
séparé.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Date/Time

{{messages}}

Pour une représentation structurée de la date et de l'heure, XOScript utilise
l'objet **Moment**. Lorsqu'un nouvel objet Moment est affiché à l'écran,
la date et l'heure actuelles sont affichées :
```
Out write: Moment new, stop.
```

Cela peut produire quelque chose comme :
```
2020-10-10 12:16:39
```

Il est également facile de lire les différents composants de l'heure. Ainsi,
si vous souhaitez uniquement connaître l'année en cours, vous pouvez envoyer
le message **year** au moment et, en retour, la réponse sera un objet
Number contenant uniquement l'année :
```
>> m := Moment new.
Out write: m year, stop.
```

@api_Moment_system


# Program/StdOut

{{messages}}

L'objet Program représente l'application actuellement en cours d'exécution. Cet
objet permet notamment d'exécuter des commandes système, d'inclure des
sous-programmes, de lire les arguments, etc. Il regroupe toutes les
fonctionnalités liées au système.

## StdOut

Out est l'objet de sortie standard. Il possède essentiellement deux méthodes :
**write:** et **stop**. Le message write: est utilisé pour envoyer une string
à stdout, tandis que le message stop affiche un caractère de nouvelle ligne.
Au lieu de **stop**, vous pouvez également utiliser \\n.

Exemple :
```
Out write: ['Hello World'], stop.
```

résultat :
```
Hello World
```

## Modules/Plugins

Le monde de XOScript peut être étendu avec de nouveaux objets système en
installant des modules. Un nouvel objet système peut être ajouté à
l'environnement XOScript en plaçant le fichier du module (généralement un
fichier portant le suffixe .so) dans le dossier mods.

Lorsque vous envoyez un message à l'objet rendu disponible par le module
plugin, celui-ci est automatiquement chargé par XOScript.

Vous pouvez également écrire vous-même des plugins. Les plugins sont écrits
dans le langage de programmation C. Vous trouverez un exemple de plugin dans
le paquet source, sous src/plugins/example.

## Reflection

Il existe différentes façons d'explorer le système
pendant l'exécution d'un programme. XOScript fournit quelques méthodes
permettant de détecter quels objets sont présents et à quels messages ces
objets répondent. Tout d'abord, chaque objet peut être interrogé sur son
**type**, mais les types dans XOScript sont malléables et donc peu fiables.

Il est également possible de demander à l'objet Program si un objet donné
est déjà présent dans le programme :
```
Program Tool true: { ... }.
```

Lorsqu'un nom d'objet
est constitué d'un seul symbole, il est préférable d'utiliser la
notation suivante afin d'éviter toute confusion :
```
Program find: ['X'], true: { ... }.
```

Outre les objets, il est également possible d'interroger l'objet
Program sur les messages. Par exemple, on peut lui demander si l'objet
**Number** connaît le message **between:and:**, comme illustré
ci-dessous :
```
Program Number: ['between:and:'], stop.
```

@api_Program_system

# server

{{messages}}

Le plugin Server de xoscript fournit des fonctionnalités permettant de
créer des applications côté serveur. Pour charger le plugin
Server, utilisez :
```
Server init.
```

Pour plus de commodité, il est également recommandé de charger les fichiers
webtools.xo et template.xo.

```
Program use: ['webtools.xo'].
Program use: ['template.xo'].
```

## Server Settings

Vous pouvez définir les paramètres serveur suivants :
```
	# default values are given
	# so if you do not set anything these
	# values are used...

	Program 
	setting: ['max-postfields']
	value: 40.

	Program 
	setting: ['max-contentlength']
	value: 2000000. # 2MB

	Program 
	setting: ['max-time']
	value: 5000. # 5sec
```

## Hello World

Voici un programme web très simple que vous pouvez utiliser avec un
serveur CGI standard comme Apache2, NGINX, OpenHTTPD ou tout autre
serveur bien connu.

```
#!/bin/xo

Server init.
Program use: ['webtools.xo'].

>> web-document := Web-Document new.

web-document out: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].
```

Si vous ne souhaitez pas utiliser l'objet Web-Document, aucun problème,
mais vous devrez alors écrire vous-même les en-têtes HTTP :
```
#!/bin/xo
Out write: ['Content-type: text/html; charset=utf-8 \n\n'], stop.
Out write: ['hello world!'], stop.
``` 

## Request

L'objet HTTP-Request peut être utilisé pour obtenir les données
GET/POST/COOKIE et UPLOAD :
```
>> request  := HTTP-Request new.
>> search   := request get: ['search']. # ?search=books
>> password := request post: ['password']. # from form
>> selected := request get-list: ['sel[]']. #?sel[]=1&sel[]=2
>> selected := request post-list: ['sel[]'].
>> cookie   := request cookie: ['session-id'].
>> upload   := request upload: ['file'].
>> temppath := upload ? 0.
>> filename := upload ? 1.
```

## Maxpost/length

Le nombre maximal de champs POST par défaut est de 40 et la longueur
maximale du contenu par défaut est de 2 Mo. Pour configurer ces valeurs
différemment pour chaque script :
```
Program setting: ['max-contentlength'] value: 1. 
Program setting: ['max-postfields'] value: 1. 
```

{{note}}
Si la longueur du contenu dépasse le maximum, le
processus est tué, car nous ne pouvons plus être certains
que la charge utile est sûre.
{{/note}}

La limite maxtime détermine le temps maximal, en ms,
pour lire stdin/postdata.
```
Program setting: ['max-time'] value: 5000. # 5sec
```

Cela s'applique uniquement à la lecture des données POST via les E/S, afin
de prévenir les attaques de type slowloris. Si vous souhaitez réellement
limiter le temps d'exécution d'une opération quelconque, utilisez
Program alarm.

## Database

L'objet Database peut être utilisé pour interroger MariaDB/MySQL.
Pour vous connecter à une base de données :

```
>> db := Maria-DB new host: ['localhost'],
	username: ['xo'],
	password: ['pass123'],
	dbname: ['xobase'],
	connect.
```

Pour insérer un enregistrement, utilisez :
```
>> query := db query: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parameters: ( List new ; ['abc'] ; 12.35 ; 6 ). # parameterized queries

{  query execute. db commit. }
except: { :e db rollback.  }, start.
```

Notez que xoscript fonctionne *uniquement* avec des transactions et ne fait
jamais d'autocommit. Si l'autocommit ne peut pas être désactivé, vous
obtiendrez une erreur de connexion. Utilisez toujours le paramétrage des
requêtes, et n'ajoutez jamais directement les entrées utilisateur au SQL.

Obtenez l'identifiant de l'enregistrement inséré comme ceci :
```
Out write: ['INSERTED: '] + query insert-id, stop. # insert id
```

Pour récupérer les enregistrements :
```
>> query :=
db
	query: ['SELECT * FROM book order by id desc limit 2'], 
	fetch: { :row 
		Out write: row id + [' '] + row description + [': '] + row price, stop.
	}. # fetching rows
```

## Sessions

Pour assurer la persistance, vous pouvez stocker et récupérer des données
depuis un objet session.
Commencez par créer un nouveau **Web-Document**. L'objet Web-Document
relie la requête, les en-têtes, le HTML et la session. En effet, lorsque
vous visitez un site web avec votre navigateur, vous ne voyez que le HTML.
Mais l'ensemble du Web-Document comprend également des **Headers**. Par
exemple, la plupart des réponses HTTP contiennent un en-tête tel que :
Content-type:text/html, indiquant au navigateur que les données qui suivent
doivent être interprétées comme du HTML (et téléchargées comme un fichier,
par exemple). Les sessions permettent de stocker les données utilisateur
entre les requêtes. Pour conserver ces données, nous devons définir un cookie ;
ce cookie est lui-même défini via un Header. C'est pourquoi tout est regroupé
dans le Web-Document (puisqu'il s'agit du document complet contenant à la fois
les headers et le HTML ou d'autres données).

```
# First we make a new Web Document instance
>> web := Web-Document new.

# Now we start a session, this will generate a Header for a cookie and
# create a file to store your data, associated with that cookie
>> session := web session-start.

# Now we can treat session like a dict
session userid: 123.
```

Pour détruire la session (lors de la déconnexion) :
```
web session-destroy.
```

## Headers

Le Web-Document permet également de définir d'autres en-têtes courants.
Par exemple, si vous souhaitez rediriger l'utilisateur vers une autre URL :
```
web goto: ['/other.html'].
```

En interne, cette commande génère également l'en-tête HTTP à envoyer
avec vos autres données ou votre HTML afin d'indiquer au navigateur de
naviguer vers l'adresse cible spécifiée.

Pour ajouter un en-tête personnalisé :
```
web header: ( 
	HTTP-Header new
	key: ['Content-Length']
	value: 400
).
```

Pour afficher une page 404 :
```
web not-found: ['OOps..'].
```

## Templates

Le système de templates par défaut est très simple. Vous n'avez pas besoin
d'apprendre une nouvelle syntaxe de template. De plus, le moteur de template
assure une véritable séparation entre la présentation et la logique métier.

Pour créer un template à partir d'un fichier :
```
>> tpl := web template: ['templates/ux.tpl'].
```

Le système de templates utilise des marqueurs.
Il existe trois types de marqueurs : les marqueurs cut, les marqueurs paste
et les marqueurs slot. L'idée de base est très simple : vous découpez les
zones identifiées par les marqueurs cut et vous pouvez les coller dans les
zones identifiées par les marqueurs paste. Vous pouvez injecter des strings
dans les marqueurs slot.

Ainsi, avec le template suivant, plaçons la pierre précieuse dans la boîte
à bijoux et ajoutons une étiquette de prix.
```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Vous pouvez procéder comme suit :
```
>> gem := tpl cut: ['gem'], copy.
gem price: 99.
tpl paste: gem at: ['jewels'].
web out: tpl clean.
```

La dernière ligne envoie simplement le template sous forme de string au client,
avec les en-têtes HTTP requis.

Résultat :
```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
``` 

## Passthru

Pour servir de manière sécurisée des fichiers téléversés par les utilisateurs,
vous pouvez utiliser passthru :
```
>> uploaded := ['smile.gif'].
Server passthru: uploaded prefix: ['/uploads/images/'].
Program end.
```

Cela servira le contenu téléversé avec le type MIME approprié. Seuls les types
MIME présents dans la liste blanche sont pris en charge :
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP et PDF.
Cette méthode empêche les attaques TOCTOU, les traversées de chemins,
l'exécution de code malveillant (injection), les attaques par liens symboliques,
les attaques DDoS (limite de fichier = 50 Mo), les attaques par
détection de contenu et divers autres problèmes de sécurité.

## JSON

Pour encoder un objet au format JSON :
```
>> json := ( JSON jsonify: ( 
	Dict new put: ( 
		List new ; 1 ; 2 ; 3
	) at: ['abc']
)).
```

Pour décoder du JSON en objet xoscript :
```
>> dict := ((JSON object: json) abc ? 1).
```

Pour produire directement un Dict au format JSON avec les en-têtes appropriés :
```
web json: dict.
```

## Regex

Vous pouvez utiliser des expressions régulières en créant un pattern.
Par exemple, pour faire correspondre les href et les targets des liens
hypertexte :
```
Pattern new: ['href="([^"]+)" target="([^"]+)"'].
```

Appliquez ensuite le pattern à la chaîne sujet comme ceci :
```
pattern match: subject do: { :m :x .... }
```

Exemple complet :
```
>> subject := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> pattern := Pattern new: ['href="([^"]+)" target="([^"]+)"'].
>> result  := pattern match: subject do: { :m :x
	Out write: m, stop.
	Out write: x, stop.
	<- ['XXX'].
}.
Out write: result, stop.
```

## Networking

Utilisez l'objet Net pour effectuer une requête web.
L'objet Net envoie toujours une requête POST, sauf si vous envoyez None comme
données ; dans ce cas, il envoie une requête GET.

```
Net 
post: None 
to: ['https://redbeanphp.com'].
```

## Encryption

Le plugin Server fournit un chiffrement basé sur XChaCha20 et Argon2.

Exemple :
```
>> encrypted := Vault encrypt: ['hello'] key: ['world'].
>> decrypted := Vault encrypt: encrypted key: ['world'].
```

## Tokens

Pour générer un token cryptographiquement sécurisé d'une longueur donnée :
```
>> mytok := Vault token: 40.
```

Cela génère un token de 40 caractères.

## Formatting

L'objet Format permet de formater des données, par exemple en ajoutant
du remplissage ou des zéros. Il utilise la syntaxe printf.
```
>> fmt := Format new: ['%06.0f'].
fmt apply: 56. # gives 000056
```

## Encoders

Plusieurs encodeurs et décodeurs sont disponibles.
L'encodeur URL prépare une URL pour son utilisation dans du HTML en tant que
lien :
```
Server url-encode: ['https://example.com?a=6&b=1 2'].
```

Pour injecter du contenu fourni par l'utilisateur dans votre HTML sans
risquer des injections XSS, utilisez toujours :
```
Server html-encode: ['<harmless>'].
```

Notez que le moteur de templates effectue toujours l'encodage HTML
lorsque vous écrivez dans un marqueur slot. Ainsi, si vous utilisez le
système de templates, vous n'avez pas besoin de l'utiliser.

## Mailing

Pour envoyer un e-mail, utilisez la bibliothèque mailtools.xo.

Exemple :
```
Server init.
Program use: ['mailtools.xo'].

>> e-mail := HTML-Email new.
>> img := e-mail attach: ( File new: ['myimage.png'] ).

e-mail
from: ['xo@xoscript.com'] name: ['xo'],
to: ( List new ; ['xo2@xoscipt.com'] ),
subject: ['xoxo'],
body: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), send.

```

## Linking

À l'aide du message link:, vous pouvez lier une bibliothèque externe à
votre programme en utilisant libffi. Pour plus de détails, consultez le
chapitre consacré à ffi.

@api_Request_http
@api_URL_http
@api_Pattern_pattern
@api_MariaDB_mariadb
@api_Net_net
@api_Vault_vault
@api_Server_server
@api_JSON_json

# ffi

{{messages}}

FFI est fourni au niveau de la plateforme/du plugin, car il est lié
à l'architecture du système sous-jacent, ce que le cœur du langage
n'est pas censé faire.
Le plugin Server fournit une implémentation conforme de ffi/blob.
Par défaut, le cœur se connecte à la plateforme cible
via stdin/stdout, des services d'E/S sur fichiers limités et le shell
(Program os).
L'intégration auxiliaire est fournie par ffi/blobs via des plugins
centrés sur l'application, tels que le plugin Server.

FFI signifie Foreign Function Interface. Il permet d'utiliser des fonctionnalités écrites par d'autres
personnes dans différents langages de programmation, fournies par des fichiers DLL, SO ou Dylib. Il peut
s'agir de fonctions très diverses, et cette méthode donne accès à une vaste gamme de fonctionnalités.
Commençons par un exemple :
```
Server link: (
 List new ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( List new ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s free.
```

Le résultat de ce code est que vous verrez ce qui suit sur la ligne de commande :
FFI has 3 letters.
Vous pensez probablement : « Cela fait beaucoup de code pour quelque chose d'aussi simple. »
Je veux dire, ne pourrait-on pas simplement résoudre cela avec une commande Gui show ? La réponse est un grand oui !
Mais cet exemple est uniquement destiné à illustrer le fonctionnement.
Le FFI est généralement utilisé pour des tâches plus complexes, mais celles-ci
ne constituent pas de bons exemples ; j'ai donc choisi quelque chose de trivial.

Les arguments de la méthode link :

- Argument #1 : le fichier DLL ou SO que vous souhaitez utiliser.
- Argument #2 : la fonction de ce fichier que vous souhaitez lier.
- Argument #3 : une liste contenant les noms des types de données des arguments de la fonction.
- Argument #4 : le nom du type de retour de la fonction.
- Argument #5 : le nom de l'objet auquel vous souhaitez lier cette fonction (s'il n'existe pas, il sera créé
  automatiquement).
- Argument #6 : le message auquel cette fonction doit être liée.

Dans l'exemple ci-dessus, nous voulons lier la fonction printf de libc.so. Vous pouvez trouver les noms des
types de données dans la documentation du logiciel auquel vous vous liez. Les types disponibles sont :
void, pointer, float, double, int, uint, char, uchar, intX et uintX,
où X peut être 8, 16, 32 ou 64.

Ces types correspondent au nombre d'octets nécessaires pour stocker les données. Pour printf, nous créons
un lien vers un nouvel objet appelé Printf et vers le message template:number:. Vous traduisez la
fonction externe dans le dialecte XOScript avant de l'utiliser. Le message template:number: attend un
buffer contenant le texte du template comme premier paramètre. Nous créons ce buffer à l'aide d'un objet
Blob, qui permet d'allouer manuellement de la mémoire. Vous êtes responsable de libérer cette mémoire
ensuite avec le message free.

Vous pouvez remplir un blob mémoire de différentes manières. Dans notre exemple, nous le remplissons avec
du texte, nous utilisons donc le message utf8: (UTF-8 est un encodage permettant de convertir du texte
en octets). Vous pouvez également remplir un blob avec bytes:, en lui transmettant une liste de valeurs
d'octets. Pour lire le contenu d'un blob, utilisez from:length:.
Vous récupérerez les octets sous forme de liste. Vous pouvez même créer une structure C avec un Blob en
utilisant le message struct:, auquel vous transmettez une séquence de types C. Cela peut être nécessaire
lors de l'appel d'une fonction C d'une bibliothèque logicielle externe qui attend un pointeur vers une
structure.

{warning}
Vous devez libérer vous-même les blobs.
Les blobs ne sont pas nettoyés par le garbage collector.
{/warning}

Comme les blobs peuvent être échangés avec des fonctions externes provenant de bibliothèques, ils
ne peuvent pas être nettoyés automatiquement par le garbage collector (ils peuvent rester utilisés par
des fonctions externes ou ces fonctions externes peuvent vouloir les libérer elles-mêmes).
Vous devez donc libérer vous-même les blobs lorsque cela est nécessaire.

Pour libérer un blob :
```
myblob free.
```

Pour libérer une structure :
```
mystruct structfree free.
```

Ainsi, pour une structure, vous devez envoyer deux messages : structfree et free
afin de désallouer le bloc de mémoire.

@api_Blob_fficonnect

# Examples

{{messages}}

Dans ce chapitre, je vais essayer de présenter quelques programmes d'exemple
afin de vous donner une idée du fonctionnement de xoscript.

## First impression

Un traditionnel hello world :
```
Out write: ['Hello World!'], stop.
```

## Server script

Voici à quoi peut ressembler un script serveur typique :
```
#!/bin/xo

# keep backward compat.
Program version: (
	Moment 
	zone: ['CEST'],
	from: ['2026-06-15 10:00:00']
).

Server init.

# I prefer a central loader that loads
# webtools.xo and template.xo
Program use: ['app/libs/loader.xo'].

# create a new document
>> web-document := Web-Document new.
>> tpl := Template new: ( 
	File new: ['app/templates/greeting.tpl'], read
).

# cut the message section
>> message := tpl cut: ['message'].

# add a message (will be encoded properly to avoid xss)
message greeting: ['hello world!'].

# paste the element at the designated slot
tpl paste: message at: ['messages'].

# output including http headers
web-document out: tpl.
```

Cela générera un document HTML contenant un message hello world.
Comme vous pouvez le voir, cette approche utilise une séparation très stricte
entre le HTML et la logique de présentation (à l'aide du moteur de templates
par défaut), de sorte qu'un développeur de templates puisse mettre à jour le
template sans avoir à modifier le moindre code.

Vous pouvez voir le résultat ici :

https://xoscript.com/test.xo

## Sophisticated Templates

Voici un exemple de création d'une liste déroulante dans un formulaire :
```
>> htmlstr := ['
<html>
<body>
<form>
<!-- cut:products -->
<select name="products">
	<!-- cut:product -->
	<option value="<!-- slot:value -->">
		<!-- slot:name -->
	</option>
	<!-- /cut:product -->
	<!-- paste:product -->
</select>
<!-- /cut:products -->
<!-- paste:products -->
</form>
</body>
</html>
'].

>> tpl := Template new: htmlstr.
>> menu := List new ; ['pizza'] ; ['pasta'].
>> products := tpl cut: ['products'], copy.
>> product := products cut: ['product'], copy.

menu each: { :n :item
	products paste: (
		product copy
		value: n,
		name: item
	) at: ['product'].
}.

tpl paste: products at: ['products'].
```

## FizzBuzz

Voici un exemple standard de fizzbuzz :
```
{ :i
	(i = 0) continue.
	(i % 15 = 0) true: {
		Out write: ['FizzBuzz'], stop.
	}, continue.
	(i % 3 = 0) true: {
		Out write: ['Fizz'], stop.
	}, continue.
	(i % 5 = 0) true: {
		Out write: ['Buzz'], stop.
	}, continue.
	Out write: i, stop.
} * 101.
```

Sortie :
```
1
2
Fizz
4
Buzz
Fizz
7
8
Fizz
Buzz
11
Fizz
13
14
FizzBuzz
etc...
```

D'autres exemples suivront...

# Localization

Vous pouvez utiliser xoscript dans votre langue maternelle si vous le souhaitez.
Pour cela, construisez xoscript comme ceci :
```
make clean
PACKAGE="server" make plugin-clean
iso="xx" LDFLAGS='-shared' make
iso="xx" PACKAGE="server" NAME="libctrserver.so" make plugin
```

Remplacez xx par le code ISO de la langue de votre choix et
ajoutez le dictionnaire correspondant à votre langue s'il n'est pas
encore fourni.

{{translations}}

# Credits

Développeur original de xoscript : Gabor de Mooij

Traduction et édition originales du manuel anglais : Bernadette Peeters

Nouveau manuel (anglais) : Gabor de Mooij et la communauté xoscript

XOScript utilise les projets open source suivants
et je souhaite exprimer ma gratitude envers leurs projets
en les listant ici :

CSiphash par Majek (https://github.com/majek/csiphash/)
Sous licence MIT

JSMN par ZSerge (ttps://github.com/zserge/jsmn)
Sous licence MIT

Monocypher par LoupVaillant (https://github.com/LoupVaillant/Monocypher)
Sous licence BSD2

libCCGI par Stephen C. Losen, University of Virginia
Sous licence LGPL

UTF8Encoder par Bjoern Hoehrmann
Licence permissive personnalisée (incluse dans 3rdparty_licenses.txt)