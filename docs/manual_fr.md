# Notions de base

{{messages}}


Bienvenue dans XOScript
Le projet XOScript vise à créer un langage de script simple et auditable.
Simple ne veut pas forcément dire facile.
Un langage de programmation familier peut être plus facile à utiliser que XOScript.
Ici, la simplicité signifie autre chose :
pouvoir se construire un modèle mental complet du langage et de son comportement.

XOScript est conçu pour tenir dans votre tête.
Sa grammaire et son nombre de concepts sont volontairement réduits.
Il n'y a pas de classes ; les objets peuvent être étendus directement.
Les objets sont passés par référence, la copie est explicite,
et les fonctions ont un seul point de sortie.

Certains de ces choix diffèrent nettement des langages courants.
XOScript n'a par exemple pas de système de types et utilise une portée dynamique.
Les messages qui ne peuvent pas être traités sont ignorés au lieu de provoquer une exception.
Ces choix ont des conséquences et ne visent pas à éliminer les erreurs.
Ils visent à garder le modèle sous-jacent du langage petit et cohérent.

XOScript peut aussi être localisé, ce qui permet d'exprimer des règles
métier dans une langue naturelle et éventuellement de les partager avec des parties prenantes non techniques.

L'auditabilité consiste à appliquer la même philosophie à l'implémentation.
L'environnement d'exécution est écrit en C, avec un petit analyseur lexical, un analyseur syntaxique et un interpréteur d'arbre écrits à la main.
La bibliothèque standard et l'environnement d'exécution reflètent largement la structure du langage,
ce qui rend la relation entre le code XOScript et son implémentation relativement directe.

Les tests sont aussi étroitement liés à la documentation.
Chaque méthode devrait avoir un test associé qui peut être intégré au manuel,
ce qui aide à garder la documentation synchronisée avec l'implémentation.

XOScript n'a pas pour but de concurrencer les langages courants sur
les fonctionnalités ou la familiarité. Il explore un autre objectif :
un environnement de programmation qu'un développeur peut comprendre dans son ensemble.

L'espoir est qu'un petit langage et une petite
implémentation permettent en pratique de comprendre un logiciel
de l'octet à l'objet, de la syntaxe à l'exécution, et d'écrire du code avec
assurance parce que vous comprenez à la fois ce qui se passe dans
le script et ce qui se passe sous le capot.

L'architecture d'une installation serveur xoscript
est simple, mais flexible.

{{architecture.png}}

Pour utiliser xoscript comme langage serveur, vous devez installer le
plugin serveur dans un dossier nommé /mods/server. 

Nous procédons ainsi parce que nous aimons
découpler le langage de base des fonctionnalités propres au serveur,
contrairement par exemple à PHP ou Python. Sinon, nous devrions livrer
tout l'attirail à tout le monde sans raison, ce qui serait tout simplement absurde.
Vous pouvez aussi installer d'autres modules si vous le souhaitez. Le système est très
flexible.

Par ailleurs, certaines fonctions sont mieux implémentées dans le langage de script
lui-même, comme les modèles et la gestion des sessions ; c'est pourquoi nous
livrons en plus les bibliothèques template.xo et webtools.xo pour votre confort.
La raison de tout cela est que nous ne savons pas comment vous voulez
utiliser xoscript. Vous pouvez l'utiliser comme langage de script côté serveur,
mais aussi pour des interfaces graphiques, des systèmes embarqués ou simplement du traitement par lots.
Même si vous l'utilisez comme langage de script côté serveur (ce qui est
actuellement l'un des principaux cas d'usage), vous voudrez peut-être
utiliser un autre moteur de modèles ou un autre gestionnaire de sessions.
Qui sommes-nous pour décider que vous devez utiliser les nôtres ?

L'un des avantages de notre propre moteur de modèles est toutefois que
vous n'avez pas besoin d'apprendre une syntaxe supplémentaire pour créer des modèles.
Le moteur de modèles par défaut livré avec xoscript sépare à 100 %
la présentation et la logique. Au lieu d'une syntaxe de modèle
spéciale, il utilise simplement un système très flexible de marqueurs d'emplacement.
Pour plus d'informations, consultez le chapitre Serveur.

Notez que si vous ne voulez pas utiliser le moteur de modèles par défaut ou
les webtools par défaut, il va sans dire que vous devez fournir
les vôtres.

Si vous exécutez votre serveur web dans un chroot, une jail ou un autre type de bac à sable,
vous devez aussi installer les dépendances de xo dans cet environnement ; vous pouvez
voir de quelles bibliothèques vous avez besoin avec ldd (voir la page de manuel de Linux ou BSD).
Si vous voulez utiliser des commandes shell dans vos scripts xo, copiez aussi un shell
(comme bash ou ksh) dans cet environnement.

Nous tenons aussi à souligner que nous prenons la rétrocompatibilité très au sérieux.
Il existe même une fonctionnalité spéciale de rétrocompatibilité appelée
'version'. En général, nous visons à ce que votre code fonctionne pour toujours. Ainsi, vous n'aurez
jamais à mettre à jour votre code pour rester compatible avec les nouvelles versions
de xoscript. Notre objectif : écrire une fois, exécuter pour toujours.

Le reste de ce manuel est consacré à l'explication détaillée du langage
de programmation xoscript. La programmation serveur est traitée dans le chapitre
intitulé Serveur. Si vous êtes un développeur expérimenté, vous voudrez peut-être
sauter quelques chapitres, car certains sont un peu trop détaillés ou
très proches des pratiques de programmation générales. Pour ceux d'entre vous
qui ont déjà l'expérience de plusieurs autres langages de programmation,
mieux vaut considérer ce manuel comme un guide de référence.

## Installation sous Linux

Téléchargez apache2 et mariadb :


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Téléchargez xoscript.
Remplacez X par le bon numéro de version !

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Copiez les fichiers dans la racine web et dans /bin :


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Modifiez votre configuration apache2 :

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Remplacez Virtualhost par :

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

Créez une page de test :

```
sudo nano /var/www/html/test.xo
```

et écrivez un petit programme de test :

```
#!/bin/xo
Server initialiser.
Programme utiliser: ['webtools.xo'].
>> web := Document-Web nouveau.
web sortir: ['Hello World'].
```

Autorisez apache2 à exécuter votre programme via CGI :

```
sudo chmod uog+x /var/www/html/test.xo
```

Redémarrez apache2 :

```
sudo systemctl restart apache2
```

Ouvrez votre page de test dans le navigateur :

```
http://localhost/test.xo
```

Vous devriez voir :

```
Hello World
```


## Installation sous OpenBSD

Modifiez /etc/httpd.conf et ajoutez :


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

Si vous voulez utiliser SSL :

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Pour protéger l'échange de clés contre les attaques quantiques,
sélectionnez le chiffrement mlkem :

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Ajoutez le binaire xo et les mods, ainsi que toutes les dépendances, dans le
chroot (à déterminer avec ldd).

## Exécuter les exemples


Pour exécuter l'un des programmes d'exemple du paquet :

```
./example.sh <name> <Linux/OBSD> [clean]
```

Par exemple, pour exécuter l'exemple FizzBuzz sous Linux :

```
./example.sh fizzbuzz Linux
```

Pour exécuter le même exemple sous OpenBSD :

```
./example.sh fizzbuzz OBSD
```

Pour exécuter l'exemple avec une compilation propre :

```
./example.sh fizzbuzz OBSD clean
```

## Tests unitaires

Pour exécuter les tests unitaires :

```
./runtests.sh
```

Pour exécuter les tests unitaires sans compiler (uniquement tester) :

```
./runtests.sh nobuild
```

## Compilation

Pour compiler à partir des sources sous Linux :

```
make clean
ISO="en" make
```

Sous OpenBSD :

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

Pour compiler le plugin serveur sous Linux :

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

Pour compiler le plugin serveur sous OpenBSD :

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Hello world

Une fois le fichier transféré sur votre ordinateur, vous pouvez l'extraire
et démarrer xo avec la commande suivante :

```
xo
```

Pour exécuter un XOScript, enregistrez le programme dans un fichier avec le suffixe
-xo (facultatif). Ensuite, indiquez le nom de fichier de votre programme
après la commande XOScript :

```
xo myprogram.xo
```

Lorsque vous exécutez une commande XOScript avec votre fichier de programme
en paramètre, xo lit et exécute votre fichier de programme.

{{note}}
Vous pouvez aussi lancer votre programme en le faisant glisser sur l'icône de xo.
{{/note}}

{{warning}}
Sur certains systèmes, vous devez d'abord accorder à xo l'autorisation de charger
des bibliothèques dynamiques.
{{/warning}}

La tradition veut que le premier programme dans tout nouveau langage
de programmation soit une sorte de salut au monde. En XOScript, un tel
programme **Hello world** ressemble à ceci :

@test598

Une fois ce texte enregistré dans un fichier, par exemple hello.xo, il peut être exécuté
ainsi : .

xo hello.xo

Hello world


Vous voyez la sortie du programme dans la fenêtre noire ci-dessus.
Tout au long de ce manuel, la même présentation sera utilisée pour montrer
la sortie.

{{note}}
Sortie s'écrit avec une majuscule.
En général, les objets commencent par une majuscule,
sauf s'ils jouent le rôle d'une instance (sans méthodes
propres, uniquement des données). Cela reflète les conventions
classe contre instance des autres langages de programmation.
{{/note}}


## Syntaxe 

XOScript est un langage de programmation *purement* *orienté objet*. Cela signifie
que xoscript considère que tout est un objet ; il n'existe donc
pas d'autres *types de données*. Un programme écrit en XOScript repose
essentiellement sur trois actions de base : *affecter*, *envoyer des messages*
et *répondre*. L'échange de messages entre objets est l'élément central d'un
programme XOScript. Ces trois actions de base sont illustrées
ci-dessous :


Action             | Exemple
------------------ | --------
affectation        |  \>\> x := 1. 
message unaire     | x pair?.
message binaire    | 1 + 2.
message à mots-clés | x de: 0 longueur: 10.
réponse            | <- answer.  


Ce chapitre vous donne une impression générale du langage XOScript
et décrit ses principes de base. XOScript est un petit langage
fondé sur trois actions (voir l'illustration), qui se traduisent en
environ six règles de grammaire. C'est tout ce qu'il faut pour maîtriser le
langage.

Pas d'inquiétude si tout ne vous paraît pas évident tout de suite : toutes les briques
seront examinées dans le chapitre suivant (3) et les règles de base y seront
répétées. Le présent chapitre sert surtout d'introduction générale
au langage. Les principes de base sont brièvement
expliqués et illustrés par plusieurs exemples pertinents. Les détails manquants
seront présentés plus tard.

En XOScript, les commentaires commencent par le symbole \#. La ligne suivante
est donc ignorée :

```
# this is just a comment
```

## Variables

Pour affecter
une variable, vous utilisez le symbole de déclaration de variable : >>. Le nom d'une
variable peut contenir tous les signes sauf : <-, :=, les espaces,
les points, les virgules, les deux-points, les guillemets [' '] et les parenthèses ().
De plus, une variable ne peut pas s'étendre sur plusieurs lignes. Notez
qu'une variable ne peut pas commencer par un chiffre ou un signe moins.

Voici des exemples de variables valides :

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dollar'].
>> +plus := Oui.
>> user-password := ['Pssst!'].
```

Voici par exemple des variables invalides :


```
>> -123 := ['negative number'].
>> password of user := ['Classified'].
>> password.of:user := ['Classified'].
>> ,x := 10.
```

{{note}}
Vous n'avez besoin d'échapper aucun caractère
(y compris les apostrophes, les guillemets doubles et les
délimiteurs de chaîne) dans
un littéral de texte tant que cela ne
crée pas d'ambiguïté pour l'analyseur lexical.
{{/note}}

Une fois qu'une variable a été déclarée, elle peut être utilisée librement. Cela signifie
qu'il suffit d'utiliser le symbole de déclaration la première fois
que vous utilisez la variable (la déclaration).

Plus précisément, vous ne pouvez pas commencer à affecter une valeur à
votre variable n'importe comment *(x := 2)*, car vous devez d'abord déclarer la variable *(\>\>
x := 2)*. En revanche, une fois la variable déclarée, vous pouvez changer sa valeur
sans utiliser le symbole de déclaration *(\>\> x := 2. x := 3.)*.

Notez qu'il est obligatoire d'affecter une valeur à une variable au moment de
sa déclaration. Contrairement à d'autres langages de programmation, vous ne pouvez pas
déclarer une variable sans valeur. Il est indispensable de lier explicitement
chaque variable à une valeur initiale. Vous pouvez néanmoins initialiser
la variable avec l'objet **Rien**. Dans ce cas, la variable peut être
considérée comme vide *(\>\> x := Rien.)*. En résumé, déclarer une
variable sans valeur initiale n'est pas permis. Ainsi,

```
>> x.
```

est invalide et produit un message d'erreur.

{{note}}
xoscript utilise une portée dynamique des variables ; pour
plus de détails, consultez le chapitre Fonctions.
{{/note}}


## Littéraux

XOScript considère que tout est un objet, c'est-à-dire tous les nombres, les textes
et les fragments de code. Les nombres comme 1, 2, 100, -999 et 1,234 sont des
objets Nombre. Tous les textes entre apostrophes sont des objets
Texte. Tous les fragments de code regroupés entre accolades {...} sont des
objets Fonction.

Littéral        | Objet racine | Exemple
--------------- | ------------ | ----------
nombres         | Nombre       | 1,2,3... 
textes          | Texte        | \['hello'\]
fonction        | Fonction     | { 1 + 2. }.
                
     
Les objets comme les nombres et les textes trouvent toujours leur origine dans un objet
racine. Par exemple, tous les nombres dérivent de l'objet **Nombre**. Tous
les textes dérivent de **Texte** et tous les fragments de code de **Fonction**. À
leur tour, tous ces objets proviennent d'**Objet**, qui est en fait
l'objet racine de tous les objets.


## Messages

Programmer en XOScript consiste essentiellement à
envoyer des messages à des objets. La notation générale pour envoyer un message à
un objet est la suivante :

```
<object> <message>
```

Pour savoir si le nombre **2**, par exemple, est un nombre pair, le
message **pair?** est envoyé à l'objet **2** :

```
2 pair?
```

La réponse sera **Oui** (encore un objet). Les messages inconnus sont
généralement ignorés par les objets ; aucune erreur ne se produit donc. Certains objets (par exemple
les nombres ou les textes) répondent à un message inconnu d'une manière prédéfinie
(nous y reviendrons plus loin).

Un objet peut recevoir trois sortes de messages. 

Type            | Nombre d'arguments
--------------- | -------------------
Unaire          | 0      
Binaire         | 1     
À mots-clés     | 1+    


Premièrement, il y a les **messages
unaires**, voir l'exemple ci-dessus, qui n'ont pas d'arguments. Deuxièmement,
il y a les **messages à mots-clés**, qui ont un ou plusieurs arguments,
par exemple :

```
>> x := Nombre entre: 1 et: 10.
```

Ici, le message **entre:et:** est envoyé à **Nombre**, qui
est l'objet racine de tous les nombres. Le résultat est un nombre aléatoire
entre 1 et 10. Enfin, il y a les **messages binaires**, qui ne comportent
qu'un seul caractère et un seul argument :

```
2 + 3
```

Cela ressemble à une addition mathématique, mais ce n'est en réalité qu'un message de plus. Le
message **+** est envoyé à **2**, avec l'argument **3**, ce qui renvoie
la réponse **5**. Les messages binaires peuvent s'écrire sans deux-points.

Les messages binaires peuvent être enchaînés :

```
>> x := 3 + 2 - 1.
```

Dans ce fragment, **+ 2** est d'abord envoyé à l'objet Nombre **3**, ce qui
donne l'objet Nombre **5**, après quoi **-1** est envoyé à ce
nombre. Les lecteurs attentifs remarqueront à juste titre l'écart que
ce protocole présente par rapport à l'ordre de priorité mathématique habituel des
opérateurs. XOScript ignore la priorité mathématique au profit de la
cohérence de son système de messages. Par conséquent, l'opération :

```
2 + 3 * 5 = 25
```

et non 17.

C'est voulu. Les parenthèses permettent de modifier l'ordre d'évaluation :

```
2 + (3 * 5) = 17
```

La plupart des objets se renvoient eux-mêmes en réponse à un
message. C'est pratique, car cela permet de poursuivre le dialogue avec cet
objet en lui envoyant un message de suite :

```
Sortie écrire:
[' hello '] rogner majuscules.
```

```
HELLO
```

Ici, deux messages sont envoyés à l'objet **Texte** : **rogner**, suivi
de **majuscules**.

Dans le fragment suivant, la virgule est nécessaire pour indiquer
qu'un nouveau message arrive. Sinon, XOScript s'y perdrait.

```
Sortie écrire: ['Hello!'], stop.
```

D'abord, le message **écrire:** est envoyé au symbole du crayon, suivi de
**stop**. Sans la virgule, XOScript penserait que vous voulez envoyer
**stop** au **texte** **Hello!**, ce qui serait inutile.

L'ordre de traitement des messages est le suivant : de gauche à droite ;
d'abord les messages entre parenthèses, puis les messages unaires. Ensuite
les messages binaires, et enfin les messages à mots-clés. Voir l'exemple
ci-dessous :

```
Sortie écrire: 0.5 arrondi + (2 - 1), stop.
```

XOScript lit toujours de gauche à droite : d'abord, le message **écrire:**
est envoyé à Sortie, suivi du message **stop**. Dans
l'argument lui-même, XOScript lit de gauche à droite, donc **0.5 arrondi**
puis **+**.

{{note}}
Le message stop ajoute un caractère de nouvelle ligne au texte.
Le nom de ce message est inspiré des systèmes télégraphiques.
Les messages télégraphiques 
utilisaient souvent le mot STOP pour marquer la fin d'une phrase
(car la ponctuation était peu fiable ou coûteuse).
{{/note}}

De plus, **arrondi** a priorité sur **+**, car c'est un
**message unaire**. En raison des parenthèses, **2 - 1** est calculé
en premier, après quoi **1** est ajouté au résultat de **0.5 arrondi** (1).

L'ensemble donne le résultat **2**, qui est aussi la réponse
écrite. Après la virgule vient le message stop, qui place le curseur
sur une nouvelle ligne. Bien sûr, la meilleure façon de bien comprendre l'ordre
d'évaluation des programmes XOScript reste la pratique.

Il convient de noter qu'en XOScript, contrairement à de nombreux autres langages
de programmation, les espaces font partie intégrante de la syntaxe. En
particulier pour les messages binaires, les espaces peuvent prêter à
confusion. Mettez toujours un espace après un message binaire. Vous ne pouvez pas
coller directement un nombre au message ; par exemple :

```
3 + 2
```

est différent de 

```
3 +2
```

Le premier exemple (**3 + 2**) envoie le
message **+** au nombre **3**, avec comme argument le nombre **2**. Le
résultat est ici **5**. Dans le second exemple (**3 +2**),
le message unaire **+2** est envoyé au nombre **3**. Selon le
contexte, le résultat peut être très différent.

## Méthodes inexistantes

Envoyer un message à un objet invoque la fonction qui a été
attachée à cet objet sous ce nom de message. Si vous envoyez un message
qui n'est pas compris, l'objet destinataire ignore votre message
et renvoie à la place une référence à lui-même pour la suite de la communication.
C'est ce qu'on appelle le passage de messages tolérant.

Exemple :

```
Sortie écrire: Objet blah, stop.
```

Cela ne produit pas d'erreur. Le texte **Objet** est simplement affiché.


## Structures de contrôle

En XOScript, il n'est pas nécessaire d'avoir des règles de grammaire séparées pour les *boucles* et
les *conditions*. Une instruction if n'est qu'un simple message **oui:** ou **non:**
envoyé à un objet **Oui** ou à un objet **Non** :

```
2 pair? oui: {
	Sortie écrire: ['Two is an even number'], stop.
}.
```
Dans l'exemple précédent, le message **oui:** est envoyé à **Oui** (la
réponse à la question : 2 est-il un nombre pair ?). Un fragment de code supplémentaire
est transmis comme argument : un objet **Fonction**. Cette fonction écrit à
l'écran que 2 est bien un nombre pair.

Il n'est pas non plus nécessaire d'avoir des règles d'écriture séparées pour une *boucle*. Pour
exécuter un fragment de code trois fois, il suffit d'envoyer **\*** avec l'argument
**3** à cette **Fonction** :

@test5

Dans ce fragment de code, **i** est l'indice. La première fois que la Fonction
est exécutée, **i** vaut 0, la fois suivante **i** = 1, et
ainsi de suite.

Prenons un autre exemple. Pour afficher une table de conversion
de *kJ* (kilojoules) en *kcal* (kilocalories) par pas de 100,
voici la notation correcte :

@test599

Ici, le numéro de la ligne courante est transmis au paramètre
**:line**. Au début d'une fonction, les paramètres de la fonction sont
définis. Les paramètres inutilisés restent vides (**Rien**). Les paramètres sont
toujours placés au début de la fonction, juste après l'accolade
ouvrante, et sont précédés de deux-points.

Le message **tant-que:** combine une *boucle* et une *condition*.
Deux fonctions peuvent être reliées par le message **tant-que:**. La fonction destinataire
continue de s'exécuter jusqu'à ce que la fonction après les deux-points donne un résultat
négatif. Exemple :

@test600

Dans le fragment de code ci-dessus, **1** est ajouté à **x** tant
que **x** est inférieur à **5**. Lorsque ce n'est plus le cas, la seconde
fonction répond **Non** et, par conséquent, l'exécution de la
première fonction s'arrête. Notez que **x** a été défini en dehors de la
fonction et est une variable globale. Pour en savoir plus sur les règles de portée,
consultez le chapitre sur les Fonctions.

## Interpolation de texte

La liste *kJ/kcal* pourrait être plus
présentable. Idéalement, la liste ressemblerait à ceci :

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Si vous transformez la sortie souhaitée en modèle, sa notation
pourrait être :

```
number1 kJ ➞ number2 kcal
```

Cela signifie que **number1** représente la valeur en kJ et **number2** la
valeur en kcal. C'est ainsi que fonctionne l'interpolation de texte en XOScript. Aucune
règle de grammaire séparée n'est nécessaire pour cela en XOScript. Il suffit d'envoyer
au texte le mot à remplacer, avec le texte de substitution comme
argument :

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

Cette règle de substitution s'applique à chaque message non défini reçu
par un objet **texte**. Chaque message qui n'est pas reconnu par l'objet
**texte** est interprété ainsi : *remplacer le texte du message
par le texte de l'argument du message.* Vous pouvez adapter le
programme comme suit :


@test601


Pour éviter toute confusion sur les messages qui peuvent ou non servir de
substitution, mieux vaut introduire un marqueur de modèle comme &lt; &gt;
pour les segments de texte du modèle qui
doivent être remplacés.

## Valeurs de retour

Pour répondre à un message, on utilise la flèche de retour
(*<-*). L'exemple suivant montre comment créer une tâche
qui calcule un pourcentage :

@test602

Une fois la tâche définie et affectée à la variable **percentage**,
le message **appliquer:et:** est envoyé avec les arguments **100** et **7**.

Cela exécute la tâche appliquée à **100** et **7**, c'est-à-dire 7 % de 100.
Grâce à la flèche de retour, la réponse est renvoyée de la tâche au
programme principal.

## Extension

Bien que ce code soit valide, il présente un inconvénient :
il faut se souvenir de l'ordre des arguments. Alors pourquoi ne pas
l'écrire ainsi : *7 percent of: 100 * ? Cela paraîtrait beaucoup plus
*naturel*. Pour rendre cela possible, nous devons adapter l'objet parent de
**7**, c'est-à-dire l'objet **Nombre**, afin qu'il comprenne le
message **percent of:**. Pour cela, on envoie **quand:faire:** à
l'objet Nombre, comme ceci :

@test603

Comme le pourcentage est ici le nombre lui-même, nous faisons référence à soi,
le mot-clé *soi*. En résumé, le symbole soi signifie : *envoyer ce
message à moi-même*.

# Objets

{{messages}}

En plus d'adapter et d'étendre des objets existants, vous pouvez aussi créer
vous-même de nouveaux objets, simplement en envoyant le message **nouveau**. Supposons que
vous vouliez créer un objet facture qui impose une séquence de
numérotation ; dans ce cas, il vous faut d'abord un objet facture.

Sachant que chaque objet dérive d'un autre objet, qui lui-même
provient en fin de compte de l'objet racine de tous les objets, appelé Objet,
il faut choisir sur lequel de ces autres objets votre
nouvel objet sera fondé. Votre nouvel objet hérite de toutes les propriétés de
l'objet sur lequel il est fondé, c'est-à-dire celui auquel le message **nouveau**
a été envoyé à l'origine.

Dans cet exemple, on préfère un objet plutôt neutre, sans trop
de propriétés héritées. Le choix est facile, car dans ce
cas le nouvel objet peut être fondé sur l'objet racine lui-même, à savoir
**Objet**. Le système de facturation envisagé s'écrit alors
ainsi :

@test604

Le numéro de facture courant est stocké dans l'objet ; c'est pourquoi
le mot-clé **propre** est placé devant. C'est ce qu'on appelle une *propriété* ;
plus de détails suivront.

Certaines entreprises préfèrent intégrer l'année dans les numéros
de facture. Dans ce cas, vous pouvez créer un nouvel objet facture fondé sur
l'objet facture précédent, mais qui permet à son utilisateur
d'indiquer une année donnée :

@test605

Il n'est pas nécessaire de réécrire l'implémentation du message **nombre**,
car elle est héritée de l'**objet facture** écrit
précédemment ; l'ancien code peut donc être réutilisé. XOScript ne connaît pas de concepts
comme les classes et les notions qui s'y rattachent. Cela signifie que les objets
ne peuvent hériter que d'autres objets, ce qu'on appelle aussi l'*héritage
par prototype*.

Revenons maintenant aux propriétés. Les propriétés d'un objet ne sont accessibles
que *depuis la hiérarchie de l'objet* ; elles
ne peuvent donc pas être perçues par d'autres objets.

Contrairement à d'autres langages de programmation, toutes les propriétés des objets sont
visibles exclusivement par l'objet qui a créé la propriété et par les
objets dérivés. 

Une technique courante consiste à utiliser un objet comme une sorte de *plan*,
comme c'est par exemple le cas avec les factures évoquées plus haut.
Un autre bon exemple est le **Point**. Supposons que vous écriviez un
programme qui effectue des calculs à partir de points sur une carte. Vous
pouvez développer l'objet **Point** contenant les propriétés d'une
coordonnée x et d'une coordonnée y, qui seront mises à la disposition du
monde extérieur au moyen de messages :

@test606

Le message **=** compare les deux points à l'aide du message **et:**. La
première comparaison donne **Oui** ou **Non**. Ce sont des objets
booléens. Lorsque vous envoyez le message **et:** à un objet Oui et que
l'objet argument après les deux-points vaut lui aussi **Oui**, vous
recevez à nouveau la réponse **Oui**. Si l'un des deux vaut **Non**, vous
recevez la réponse **Non**. Notez qu'un point ne peut pas lire les coordonnées de
l'autre. Il faut envoyer un message à l'autre point pour lui demander
ces données : **x-coordinate** et **y-coordinate**. Après tout, comme
cela a déjà été expliqué, les propriétés ne sont accessibles que depuis
la famille de l'objet elle-même. 

Notez que le message **=** est utilisé ici pour effectuer la comparaison
des points. On aurait tout aussi bien pu utiliser un autre message, comme
**is:** ou **equal:**, mais réutiliser le caractère **=** semblait
approprié dans ce cas.

## Héritage

Vous pouvez réutiliser du code écrit précédemment pour créer une hiérarchie
d'objets. Par exemple :

```
>> Animal := Objet nouveau.
>> Dog := Animal nouveau.
>> Poodle := Dog nouveau.
```

Ici, **Dog** hérite de tout le comportement et de toutes les propriétés
d'**Animal** et, à son tour, l'objet **Animal** hérite de tout le comportement
d'**Objet**, l'objet racine de tous les objets.


## Redéfinition


Dans l'exemple suivant, un nouveau type de liste est créé :
**Combination**, dans laquelle chaque élément est garanti unique. Les
fonctions de la liste sont réutilisées par héritage :

@test607

Remarquez que le second **red** est exclu de la liste.

Il peut arriver qu'il faille redéfinir un comportement d'un objet.
Par exemple, lorsqu'on additionne des nombres et qu'il faut tenir compte des
unités de mesure. Dans l'exemple suivant, l'objet **Size** est
créé. Cet objet renvoie un nombre qui, lors de l'addition, tient
compte de l'unité du nombre à ajouter. L'objet **Nombre**
vérifie s'il s'agit de *pouces* ou de *pieds*. Le code
pourrait ressembler à ceci :

@test608

## Récursivité

Dans l'exemple précédent, le **signe** plus est redéfini. Notez
qu'au bout du compte, l'addition finale doit tout de même être effectuée, ce qui
se produit en fait à la ligne suivante :

```
>> answer := soi + (nombre x factor).
```

Mais comment XOScript comprend-il que ce **signe** plus fait référence à
la logique d'addition d'origine ?** On pourrait par exemple l'interpréter
comme si XOScript envoyait sans cesse le même message au même
objet, ce qui produirait une **boucle infinie**. Ce n'est
évidemment pas l'intention. Dès que vous envoyez à un objet un message
qui exécuterait exactement le même code, XOScript comprend
que c'est le message sous-jacent, redéfini, qui est visé. Votre
programme est ainsi automatiquement protégé contre ce type de boucles
infinies. Si, en revanche, votre but est bien d'exécuter la même fonction depuis la
fonction courante, il faut d'abord envoyer le message
**récursif**. Dans ce cas, le résultat sera une boucle
infinie. Il existe cependant des applications utiles des tâches récursives ;
supposons par exemple que vous vouliez calculer la factorielle d'un
nombre donné. Dans ce cas, ajoutez simplement le message **factorial** à
Nombre :

@test609

Cela demande de la récursivité. En effet, la tâche liée au
message **factorial** doit être exécutée à nouveau à l'intérieur de cette fonction.
Il faut donc invoquer la fonction factorielle depuis la
fonction factorielle elle-même. En règle générale, XOScript empêche cela,
en raison du risque de se retrouver dans une boucle infinie. C'est pourquoi
il est indispensable de faire précéder le message du mot **récursif**. Cela
permet de signaler à XOScript que vous avez bien
l'intention d'exécuter la même tâche et que vous n'avez pas fait d'erreur.

## Objets de type classe

Bien que xoscript n'offre pas de classes, imiter un comportement
de classe est trivial. Il suffit de redéfinir le message nouveau.

```
>> Animal := Objet nouveau.
Animal quand: ['nouveau'] faire: {
	<- soi nouveau initialiser.
}.

Animal quand: ['initialiser'] faire: {
	propre sound := ['?'].
	propre legs  := 4.
}.
```

Dans le fragment de code ci-dessus, nous créons un objet appelé Animal.
Cet objet sert de *plan* pour toutes sortes d'animaux,
comme les chiens et les chats. L'objet parent Animal s'écrit
avec un A majuscule pour indiquer qu'il s'agit d'un objet de type classe.
Ensuite, nous redéfinissons le message nouveau en écrivant notre propre méthode nouveau.
Ici, elle envoie le message nouveau à soi, suivi du message
initialiser. Comme xoscript bloque la récursivité par défaut, cela ne provoque pas
de boucle infinie. Le message nouveau est au contraire envoyé à l'objet parent
(Objet), ce qui donne une nouvelle instance d'Animal. Nous créons donc
un nouvel objet, fondé sur le même objet que celui pour lequel nous avons créé notre méthode nouveau.
C'est parfaitement valide. Nous envoyons ensuite le message initialiser, ce qui garantit
que l'objet Animal a des valeurs par défaut pour ses propriétés. Par défaut,
un animal a 4 pattes et son cri est inconnu (d'où le point d'interrogation).
Pour créer une nouvelle instance de notre Animal, il suffit d'écrire :

```
>> a := Animal nouveau.
```

Nous obtenons alors une nouvelle instance d'Animal avec 4 pattes, un cri inconnu et
une méthode initialiser. Comme dans d'autres langages orientés objet, nous pouvons aussi
étendre notre Animal :

```
>> Dog := Animal nouveau.
Dog quand: ['initialiser'] faire: {
	soi initialiser.
	propre sound := ['barks'].
}.
```

Nous pouvons facilement le tester en ajoutant une méthode texte :

```
Animal quand: ['texte'] faire: {
	<- propre legs texte + propre sound.
}.
```

Assemblons le tout :

@test13


Créer un objet placé dans un état initial donné est un
problème fréquent. Supposons qu'il faille créer un objet **Rectangle**
afin de calculer son périmètre et sa surface. Une notation possible serait :


```
>> Rectangle := Objet nouveau.

Rectangle quand: ['area'] faire: {
	<- propre longueur * propre width.
}.
```

Il est évident que définir une longueur et une largeur est une condition préalable. Pour
cela, on peut ajouter les messages **longueur:** et **width:** :


```
Rectangle quand: ['length:'] faire: { :longueur
	propre longueur := longueur.
}.

Rectangle quand: ['width:'] faire: { :width
	propre width := width.
}.

```

Ce rectangle peut ensuite être utilisé comme suit :


```
>> rectangle := Rectangle nouveau length: 2, width: 3.
Sortie écrire: rectangle area.
```

Cependant, si l'on oublie de définir la longueur et la largeur initiales,
un message d'erreur apparaît :

```
>> rectangle := Rectangle nouveau.
Sortie écrire: rectangle area.
```

produit l'erreur suivante :

```
Clé introuvable:longueur
```

Pour éviter cela, il est préférable qu'un rectangle ait
toujours une longueur et une largeur initiales, par exemple 0. Dans ce
cas, il faut donc **redéfinir** le message **nouveau**.

@test610

En redéfinissant le message nouveau, nous imitons en fait une **classe**.

Le monde de XOScript est rempli d'une grande diversité d'objets, qui sont
à la disposition de votre programme dès le départ. Dans les chapitres suivants,
tous ces objets de base seront présentés.

## Instantanés

Vous pouvez enregistrer un objet (avec son état actuel) sur disque avec :

```
myobject save-as: ['saved.bin'].
```

Pour recharger l'objet depuis le disque :

```
>> myobject := Objet load-from: ['saved.bin'].
```

Les instantanés permettent d'enregistrer un état donné ou d'améliorer les performances.
Charger un instantané évite l'analyse lexicale, l'analyse syntaxique et la configuration de l'application.
À l'avenir, d'autres gains de performances pourraient aussi être apportés
par les instantanés, comme l'optimisation de certains motifs ou la détection et
l'optimisation des chemins critiques.

{{warning}}
Les instantanés sont une fonctionnalité expérimentale ; ne les utilisez pas en production.
Pour activer les fonctionnalités expérimentales, compilez avec -D EXPERIMENTS.
{{/warning}}


@test712

# Objet Rien

{{messages}}

L'objet Rien
représente le vide ou, mieux encore, l'absence d'information. Il
vous arrivera de recevoir cet objet en réponse à un message lorsque
le résultat est **rien**. La question la plus essentielle
que vous puissiez poser à l'objet **Rien** est : **Rien?**. La
réponse sera toujours **Oui**.

```
Sortie écrire: Rien Rien?.
```

résultat :

```
Oui
```

Tout objet autre que **Rien** répond **Non**. Le
fragment de code ci-dessus peut sembler un peu philosophique, mais l'objet **Rien**
a assurément des applications extrêmement pratiques. Par exemple, vous
recevez l'objet Rien en réponse lorsque vous demandez un
élément de liste qui n'existe pas. Vous pouvez aussi utiliser l'objet Rien
si vous voulez déclarer une variable sans vouloir encore préciser de
valeur. Vous **affectez** alors simplement la valeur spéciale **Rien**. En
XOScript, il n'est pas permis de déclarer une variable sans valeur, comme :


```
>> valeur.
```

Vous devez écrire à la place :

```
>> valeur := Rien.
```

@api_None_base

# Booléens

{{messages}}

Contrairement à la plupart des langages de programmation populaires au moment de la rédaction,
XOScript ne fournit qu'un seul objet Oui et un seul objet
Non. Autrement dit, chaque fois que vous écrivez **Oui**, cela ne signifie pas
qu'un nouvel objet a été créé. Vous utilisez toujours une référence. Cela
signifie que lorsque vous écrivez :

\>\> x := Oui.

**x** fait référence à l'objet **Oui**. Le code conditionnel et les boucles
vérifient eux aussi cette référence. En XOScript, la signification de **Oui** et **Non**
n'est pas figée. En fait, un programme XOScript est fortement chamboulé par une
instruction comme celle-ci :

Oui := Non.

Le résultat de telles actions est indéfini ; il s'agit pourtant d'une action
valide et donc formellement permise. Il existe par ailleurs un objet Booléen,
qui est l'objet racine de **Oui** et de **Non**, puisque tous deux
en dérivent. L'objet Booléen lui-même n'a cependant
aucune application pratique.

## Pièges

Faites attention en utilisant **et:** et **ou:**

```
Sortie écrire: (Non or: Oui or: Oui), stop.
Sortie écrire: (Non ou: Oui, ou: Oui), stop.
```

Donne

```
Non
Oui
```
car le message **ou:** ne prend qu'un seul argument. La première ligne
envoie **ou:ou:** à Non, qui n'existe pas ; l'objet ignore donc
le message et se renvoie lui-même (Non). La seconde ligne, en revanche,
envoie **ou:** suivi d'un autre **ou:** (à l'aide d'un symbole d'enchaînement, c'est-à-dire une virgule : ,).


@api_Boolean_base

# Nombres

{{messages}}

Chaque fois que vous écrivez un nombre, par exemple 9, -10 ou 3,12, XOScript
convertit en coulisse ces nombres en objet **Nombre**. Vous
pouvez envoyer des messages à cet objet Nombre, ou affecter le nombre
à une variable et lui envoyer des messages ensuite :

```
10 pair?

>> tenner := 10.
tenner pair?

```

Les deux notations sont valides. L'objet Nombre répond aux
messages suivants...

La plupart de ces messages se passent d'explication et vous permettent d'effectuer
des opérations mathématiques ou des comparaisons.

{{note}}
Notez que vous pouvez utiliser ≤ ≥ ≠ × et ÷ à la place de leurs équivalents ASCII.
C'est une question de préférence.
{{/note}}

La différence entre les messages mathématiques binaires (+) et
leurs variantes à mots-clés (additionner:) est que les premiers renvoient
un nouveau nombre, résultat de l'opération, tandis qu'avec les
secondes, l'objet lui-même est modifié. C'est ce qu'illustre
l'exemple suivant :

@test597

Dans l'exemple ci-dessus, b = 4 et a = 3. Avec **additionner: 2**, la valeur
de a est augmentée de 2, tandis que **+ 3** crée un nouveau nombre
égal à a + 3. Il en va de même pour les autres opérations mathématiques, par exemple
les multiplications. Avec le symbole de multiplication, vous recevez un
nouvel objet en réponse. Si vous utilisez le message **multiplier-par:**,
c'est le nombre lui-même qui est multiplié.

Avec le message **entre:et:**, par exemple dans **Nombre
entre: X et: Y**, vous obtenez un nombre compris entre X et Y. De
cette manière, on peut générer n'importe quel nombre aléatoire :

```
>> a := Nombre entre: 1 et: 10.
Sortie écrire: a, stop.
```

Depuis la version 1.4, le générateur intégré de nombres aléatoires de xoscript est,
à notre connaissance, cryptographiquement sûr.

Vous pouvez associer un **qualificatif** à un nombre, par exemple **6
apples**. Chaque message qui n'est pas reconnu par un
nombre est considéré comme un qualificatif. Vous pouvez obtenir le qualificatif d'un
nombre au moyen du message qualificatif :

Un qualificatif est essentiellement un objet Texte stocké avec l'objet
Nombre. Le qualificatif est aussi affiché après le nombre lors d'un
**écrire:**. Les qualificatifs peuvent par exemple servir à additionner des montants
dans des devises différentes. Lors de l'addition des montants, vous pouvez demander
les qualificatifs. L'exemple de programme suivant illustre ce
principe avec un convertisseur de devises historiques (puisque le taux de
change reste raisonnablement stable !).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Textes

{{messages}}

Chaque fois qu'un texte est placé entre **crochets et apostrophes** ['...'],
XOScript crée pour vous un nouvel objet texte. Veillez toutefois
à utiliser les bons délimiteurs. Le délimiteur au
début du texte diffère de celui de la fin (cela vous permet
d'utiliser l'apostrophe sans avoir à l'échapper).

## UTF8

Les textes en xoscript contiennent généralement du texte encodé en utf8. Bien
qu'il soit techniquement possible d'avoir un contenu binaire ou non utf8 dans
un texte, il est recommandé d'utiliser des blobs pour cela. Les blobs sont
fournis par le plugin serveur (voir le chapitre ffi).
En général, les blobs et ffi sont fournis
par plugin ou par plateforme, car ils sont liés à la plateforme
et à l'architecture (ffi/blobs). Le cœur du langage de script s'efforce de
rester aussi indépendant de la plateforme que possible.

## Conversion de type

Vous pouvez créer une copie de chaque objet
avec un autre type à l'aide des messages suivants :

Message  | Résultat
-------  | ------
nombre   | Convertit en nombre
texte    | Convertit en texte
booléen  | Convertit en booléen
  
Les règles suivantes **s'appliquent** :

message  | Rien      | Booléen            | Nombre                | Texte     | Autre              
-------- | --------- | --------           | --------              | --------  | --------
booléen  | Non       | s.o.               | 0→Non sinon→Oui       | Oui       | Oui le plus souvent
nombre   | 0         | Non→0 Oui→1        | s.o.                  | ['n']→n   | 1 le plus souvent
texte    | ['Rien']  | ['Non']/['Oui']    | ['n']                 | s.o.      | Variable

## Copie

En XOScript, les valeurs sont toujours passées **par référence**. Dans d'autres langages,
cela dépend du type de la valeur ; en XOScript, il n'y a qu'une seule manière :
par référence. XOScript ne fait jamais de copie d'une valeur. Pour copier un objet,
vous devez envoyer le message **copier**. 

@test611

Ici, vous vous attendiez peut-être à ce que la sortie soit Dolly au lieu
de Donny. Ce n'est pourtant pas le cas, car les deux noms font référence au même
objet. Il se passe quelque chose de semblable avec une boucle :

@test612

En fait, XOScript utilise **toujours** des références ; dans la boucle
ci-dessus, **:quantity** désigne donc aussi la référence à l'élément
de la liste.

Pour copier un objet, vous devez demander cette action
**explicitement** :

@test613

En envoyant le message unaire **copier** à un texte, l'objet
renvoie une copie de ce même objet texte. On peut copier de la même manière des objets
Nombre, des objets booléens, des listes et des dictionnaires.

Vous pouvez aussi définir votre propre implémentation de la copie ; c'est même une
nécessité si vous créez vos propres objets. L'implémentation
par défaut de copier pour une liste fait une copie superficielle : elle crée une
nouvelle liste avec les mêmes éléments.

@test614

Ici, 4 n'est ajouté qu'à la copie.
Mais comme la copie est superficielle, les objets des deux listes
sont les mêmes.

@test615

Si nous ajoutons donc 2 à chaque nom de la copie, la liste
d'origine est également affectée.

Pour y remédier, nous devons faire une **copie profonde**. Une telle copie
pour une liste pourrait s'écrire ainsi :

@test616

Notez aussi le message récursif : il faut l'envoyer
avant le message copier.

Il est essentiel de garder à l'esprit que, même si la copie d'un objet
ressemble souvent à l'original, elle ne sera en fait
jamais le même objet. L'objet racine définit un message **equal:**,
qui permet de comparer l'identité des objets. Voyez
l'exemple suivant :

@test617

## Conversion implicite

XOScript utilise la **conversion implicite** pour convertir des objets. Pour afficher une
liste à l'écran, XOScript envoie par exemple en interne le message
*texte* à la liste. Cela peut s'avérer très utile si
vous voulez afficher une liste sous forme de liste séparée par des virgules. Le
message *texte* peut être redéfini : 

@test620

@api_String_base
@api_Format_base


## Textes serveur

Les fonctionnalités de Texte suivantes sont ajoutées par le
plugin Serveur.

@api_String_server

# Fonctions

{{messages}}

Vous pouvez regrouper du code entre { et } ; il devient alors une fonction.
En xoscript, on emploie aussi parfois le terme tâche, ou simplement
bloc de code.

Vous pouvez exécuter une fonction en lui envoyant le message *démarrer*.


```
{ Sortie écrire: 123, stop. } démarrer.
```

Si votre fonction prend des arguments, utilisez **appliquer:**.

```
{ :a Sortie écrire: a, stop. } appliquer: a.
```

Voir aussi les exemples ci-dessous.
En raison de l'architecture simple, une fonction ne peut avoir
qu'un seul point de retour. Pour éviter une surcharge ou une imbrication excessive des
conditions, vous pouvez utiliser une procédure (ce qui revient à utiliser
le signe de multiplication avec l'argument 1) :

```
{
  (a = 1) oui: { x := 1. }, interrompre.
  (a = 2) oui: { x := 2. }, interrompre.
} procédure.
```

Ainsi, (a = 2) ne sera pas évalué si a = 1.
De plus, vous n'avez pas besoin d'imbriquer des messages oui de cette façon.
Chaque fois que vous vous surprenez à imbriquer des conditions, pensez
au message procédure. Il peut rendre votre code
plus lisible.


Voici un piège important :

```
{
	Non non: {
		Sortie écrire: ['End the loop.'].
	}, interrompre.
	
	Sortie écrire: ['Dont show me.'].

} procédure.

```

Ici, le texte 'Dont show me' sera affiché,
car **interrompre** est envoyé à Non. Si vous voulez exécuter
une interruption, elle doit être envoyée comme message à **Oui**.
 

```
{
	Non non oui: {
		Sortie écrire: ['End the loop.'].
	}, interrompre.
	
	Sortie écrire: ['Dont show me.'].

} procédure.

```

Fonctionnera comme prévu.

## Exceptions

Les exceptions peuvent être traitées ainsi :

```
{ Task 1 } intercepter: { Task 2 }, démarrer.
```

Vous pouvez aussi provoquer volontairement une erreur dans votre programme et
ainsi activer le bloc de traitement. Pour cela, on envoie le
message **erreur:** à la tâche courante, comme le montre
l'illustration suivante :

```
{
cette-tâche erreur: ['Whoops!'].
} intercepter: { :mistake
Sortie écrire: mistake.
}, démarrer.
```

## Injection de valeurs

XOScript permet d'injecter des valeurs dans les tâches. Regardez
la tâche ci-dessous :

```
>> sending := {
	Newsletter destinataire: propre recipient.
}.
sending donner: ['recipient']
valeur: ['info@recipient.org'].
sending démarrer.
```


Cette illustration présente une tâche imaginaire qui envoie une lettre d'information
à une adresse e-mail ou **destinataire**. Ce destinataire peut être injecté
dans la tâche depuis l'extérieur, avant le démarrage de la tâche, en envoyant le
message **donner:valeur:** à la tâche. De cette façon, la valeur de
**recipient** est prédéfinie dans la tâche. Cette valeur peut aussi être modifiée,
puis la tâche peut être exécutée à nouveau. C'est une méthode utile lorsqu'on utilise
des objets Task.

## Fonctions vides

Les tâches vides ne sont pas permises. En théorie, une tâche vide ressemblerait
à ceci : **{}**, mais XOScript considère cela comme une erreur de langage. Si vous
voulez déclarer une tâche vide, vous pouvez utiliser l'objet Rien :

```
>> task := Rien.
```

Bien qu'il ne s'agisse pas d'une vraie tâche mais d'un objet Rien, on peut
tout de même lui envoyer un message démarrer :

```
>> answer := task démarrer.
```

En fait, cela revient à :

```
>> answer := Rien démarrer.
```

Comme l'objet **Rien** ne reconnaît pas le message **démarrer**, il
se renvoie lui-même comme réponse, si bien que la réponse est à nouveau **Rien**.
Il n'est donc pas nécessaire d'avoir une tâche vide. Grâce à la conception
élégante du langage de programmation XOScript, vous pouvez simplement utiliser l'objet
Rien pour cela.

## Portée dynamique

Lorsqu'une Fonction a besoin d'une variable mais ne la trouve pas,
elle examine les variables de la Fonction qui l'a **appelée**,
et continue à remonter la chaîne des Fonctions.
Cette recherche se poursuit jusqu'à ce que la variable soit trouvée.
Si la variable reste introuvable, un message d'erreur apparaît. Cette manière de rechercher une
variable s'appelle la **portée dynamique**.

Pour illustrer ce principe :

@test618

@api_Code_base

# Objet racine

{{messages}}

L'objet nommé **Objet** est l'objet racine de tous les objets en
XOScript et fournit les fonctionnalités de base du langage. 

Le message le plus fréquemment envoyé
est **quand:faire:**, qui étend les fonctionnalités d'un objet. Ce
message est reçu par l'objet racine, qui lie alors la
tâche indiquée au message et étend ainsi l'objet
dérivé.

## Méthodes fourre-tout

Normalement, si vous envoyez un message qui ne correspond à aucune
méthode de l'objet, il est ignoré. Vous pouvez toutefois définir
des méthodes dites **magiques** ou **fourre-tout**, qui sont
invoquées lorsque le message n'est pas compris par l'objet.

Il existe 4 méthodes fourre-tout. Chaque message correspond
à un nombre précis d'arguments.

Message fourre-tout     | Nombre d'arguments
----------------------- | -------------------
répondre:               | 0
répondre:et:            | 1
répondre:et:et:         | 2
répondre:et:et:et:      | 3


@test619

## Messages programmatiques

Au lieu d'envoyer un message directement à un objet, on peut aussi
l'envoyer au moyen d'une variable. Pour cela, on utilise le message
**message:arguments:**. 

@test396

@api_Object_base

# Listes

{{messages}}

XOScript connaît deux types de collections : les *listes* et les *dictionnaires*.
Les **listes** sont des énumérations d'objets dans un *ordre fixe*. Les dictionnaires n'ont
pas d'ordre ; ils ressemblent plutôt à une légende associant une clé (ou un terme) à sa
valeur correspondante. Les listes sont comparables aux tableaux (PHP, Java, C)
et aux listes (Python). Les dictionnaires sont comparables aux tableaux associatifs (PHP) ou
aux dictionnaires (Python) d'autres langages de programmation. Pour créer
une nouvelle Liste, écrivez :

```
>> fibonacci := Liste nouveau.
```

Cette liste vide peut être remplie avec **ajouter:** :

```
fibonacci ajouter: 0.
fibonacci ajouter: 1.
fibonacci ajouter: 1.
fibonacci ajouter: 2.
fibonacci ajouter: 3.
fibonacci ajouter: 5.
fibonacci ajouter: 8.
fibonacci ajouter: 13.
```

Si nous écrivons la liste à l'écran :

```
Sortie écrire: fibonacci, stop.
```

Nous verrons :

```
Liste ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

Au lieu de ajouter, vous pouvez aussi utiliser ; pour ajouter des éléments à une liste :


```
>> fibonacci := Liste nouveau ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Les points-virgules (;) sont tous des messages binaires qui placent une
valeur dans la liste.

## Enchaînement

Supposons que vous ayez une liste comme :

```
>> x := Liste nouveau ; 1 ; 2 ; 3.
```

Si vous voulez supprimer le premier et le dernier élément, votre
message serait :

```
x retirer-premier retirer-dernier.
```

Malheureusement, la notation précédente ne fonctionne pas correctement. Le
message **retirer-premier** renvoie le premier élément de la liste, qui
devient à son tour le destinataire du message **retirer-dernier**. Le
message **retirer-dernier** n'est donc pas envoyé à **x**, mais à 2. Une
solution possible à ce problème serait d'écrire deux phrases
séparées, comme : 

```
x retirer-premier.
x retirer-dernier.
```

C'est toutefois peu pratique, en particulier lorsqu'il faut
supprimer plus de deux éléments. XOScript propose donc une
structure de messages alternative pour ce genre de situations. Dans les
structures de messages **alternatives**, les réponses des objets sont ignorées
et vous récupérez à chaque fois l'objet destinataire comme réponse.
Une structure de messages **alternative** commence par l'envoi du
message **faire** à un objet et se termine par l'envoi du
message **terminé**. Dans
l'exemple illustré, cela donne :

```
>> x := Liste nouveau ; 1 ; 2 ; 3.
x faire retirer-premier retirer-dernier terminé.
```

@api_List_collections

# Dictionnaires

{{messages}}

**Liste et Dictionnaire sont tous deux des collections. Cependant, contrairement à une
liste, un dictionnaire **n'a pas** d'ordre. Une autre différence entre les deux
est qu'un dictionnaire est constitué de paires d'objets. Un objet sert d'entrée (ou de
mot-clé) pour rechercher l'autre objet. Un bon exemple d'une telle
liste est une liste de prix, comme :


```
>> menu := Dictionnaire nouveau
	mettre: ['£5'] à: ['apple pie'],
	mettre: ['£6'] à: ['carrot cake'],
	mettre: ['£3'] à: ['fudge'].
```

Comme pour une liste, le message mettre:à:
sert à ajouter un objet à la liste. La différence est que, contrairement à
une liste, deux objets sont liés. Le premier objet est, comme pour
une liste, l'objet que vous stockez dans la liste. Le second
objet n'est pas sa position dans la collection, mais l'**entrée**
qui permet de retrouver plus tard l'objet précédent. En
résumé, un dictionnaire fonctionne un peu comme un dictionnaire de langue : le mot-clé
permet de trouver la signification. Par exemple, pour obtenir dans la liste
ci-dessus le prix d'un caramel :

```
>> price := menu à: ['fudge'].
```

Vous pouvez aussi utiliser la notation concise :

```
>> price := menu ? ['fudge'].
```

Si les entrées que vous utilisez pour stocker les objets ne contiennent pas d'espaces
(et n'entrent pas en conflit avec d'autres messages prédéfinis),
la notation suivante peut aussi être utilisée :

```
>> menu := Dictionnaire nouveau
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

La notation ci-dessus se lit sans doute de façon un peu plus naturelle.
Pour demander le prix d'un
caramel, on peut utiliser la notation simplifiée suivante :

```
>> price := menu fudge.
```

@api_Dict_collections

# Fichier

{{messages}}

L'objet **Fichier** offre un accès de base au système de fichiers.
Vous pouvez utiliser cet objet pour lire des fichiers entiers dans une variable en
une seule fois, ou écrire des variables dans des fichiers en une seule fois. La lecture ligne par ligne
est aussi prise en charge. Ce sont les opérations d'entrée/sortie sur fichiers les plus courantes
dans un langage de script. Les opérations avancées sur les fichiers nécessitent
FFI, via le plugin serveur ou un plugin d'E/S séparé.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Date/Heure

{{messages}}

Pour une représentation structurée de l'heure et de la date, XOScript utilise
l'objet **Moment**. Lorsqu'un nouvel objet Moment est affiché à l'écran, la
date et l'heure actuelles sont montrées :

```
Sortie écrire: Moment nouveau, stop.
```

Peut donner quelque chose comme :

```
2020-10-10 12:16:39
```

Il est aussi facile de lire les différentes composantes du temps. Par
exemple, s'il suffit de connaître l'année en cours, le message
**année** peut être envoyé au moment ; la réponse est alors un
objet Nombre contenant uniquement l'année :

```
>> m := Moment nouveau.
Sortie écrire: m année, stop.
```

@api_Moment_system

# Programme/Sortie standard

{{messages}}

L'objet Programme représente l'application en cours d'exécution. Cet objet
offre des fonctionnalités pour exécuter des commandes système, inclure des sous-programmes,
lire des arguments, et plus encore : toutes les fonctions liées au système.

## Sortie standard

Sortie est l'objet de sortie standard. Il possède essentiellement deux méthodes :
**écrire:** et **stop**. Le message écrire: sert à envoyer un texte
vers stdout ; le message stop affiche un caractère de nouvelle ligne.
Au lieu de **stop**, vous pouvez aussi utiliser \\n.

Exemple :

```
Sortie écrire: ['Hello World'], stop.
```

résultat :

```
Hello World
```

## Modules/Plugins

Le monde de XOScript peut être étendu avec de nouveaux objets système en
installant des modules. Un nouvel objet système peut être ajouté au monde de
XOScript en plaçant le fichier du module (généralement un fichier avec le suffixe .so)
dans le dossier mods. 

Lorsque vous envoyez un message à l'objet mis à disposition par le
module plugin, celui-ci est automatiquement chargé par XOScript.

Vous pouvez aussi écrire vous-même des plugins. Les plugins sont écrits dans le
langage de programmation C. Vous trouverez un exemple de plugin dans le paquet
des sources, sous src/plugins/example.


## Réflexion

Il existe plusieurs manières d'explorer le
système pendant l'exécution d'un programme. XOScript dispose de quelques méthodes pour
détecter quels objets sont présents et à quels messages ces objets
répondent. Tout d'abord, on peut demander à chaque objet de quel **type** il est ;
mais en XOScript, les types sont malléables et donc peu fiables.

On peut aussi demander à l'objet Programme si un
objet donné est déjà présent dans le programme :

```
Programme Tool oui: { ... }.
```

Lorsque le nom d'un objet
ne se compose que d'un seul symbole, mieux vaut utiliser la
notation suivante pour éviter toute confusion :

```
Programme trouver: ['X'], oui: { ... }.
```

En plus d'interroger le programme sur les objets, on peut tout aussi bien interroger
l'objet Programme sur les messages. On peut par exemple lui demander si
l'objet **Nombre** connaît le message **entre:et:**, de la manière
illustrée ci-dessous :

```
Programme Number: ['between:and:'], stop.
```

@api_Program_system

# serveur

{{messages}}

Le plugin Serveur de xoscript offre des fonctionnalités pour
créer des applications côté serveur. Pour charger le plugin
serveur, utilisez :

```
Server initialiser.
```

Pour votre confort, il est aussi recommandé de charger
les fichiers webtools.xo et template.xo.

```
Programme utiliser: ['webtools.xo'].
Programme utiliser: ['template.xo'].

```

## Paramètres du serveur

Vous pouvez définir les paramètres de serveur suivants :

```
	# default values are given
	# so if you do not set anything these
	# values are used...

	Programme 
	paramètre: ['max-postfields']
	valeur: 40.

	Programme 
	paramètre: ['max-contentlength']
	valeur: 2000000. # 2MB

	Programme 
	paramètre: ['max-time']
	valeur: 5000. # 5sec

```

## Hello World

Voici un programme web très simple que vous pouvez utiliser avec un
serveur CGI standard comme Apache2, NGINX, OpenHTTPD ou tout autre
serveur connu.

```
#!/bin/xo

Server initialiser.
Programme utiliser: ['webtools.xo'].

>> web-document := Document-Web nouveau.

web-document sortir: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Si vous ne voulez pas utiliser l'objet Document-Web, c'est possible, mais
vous devez alors écrire vous-même les en-têtes HTTP :

```
#!/bin/xo
Sortie écrire: ['Content-type: text/html; charset=utf-8 \n\n'], stop.
Sortie écrire: ['hello world!'], stop.
``` 

## Requête

L'objet Requête-HTTP permet d'obtenir les données GET/POST/COOKIE et
UPLOAD :

```
>> demande  := Requête-HTTP nouveau.
>> search   := demande get: ['search']. # ?search=books
>> password := demande post: ['password']. # from form
>> selected := demande get-liste: ['sel[]']. #?sel[]=1&sel[]=2
>> selected := demande post-liste: ['sel[]'].
>> cookie   := demande cookie: ['session-id'].
>> upload   := demande upload: ['file'].
>> temppath := upload ? 1.
>> filename := upload ? 0.
```

## Maxpost/longueur

Le nombre maximal de champs POST est par défaut de 40 et la longueur maximale
du contenu de 2 Mo par défaut. Pour configurer autrement, script par script :

```
Programme paramètre: ['max-contentlength'] valeur: 1. 
Programme paramètre: ['max-postfields'] valeur: 1. 
```

{{note}}
Si la longueur du contenu dépasse le maximum, le
processus est tué, car nous ne pouvons plus être sûrs
que les données reçues sont sans danger.
{{/note}}

La limite maxtime détermine le temps maximal en ms
pour lire stdin/les données POST.

```
Programme paramètre: ['max-time'] valeur: 5000. # 5sec
```

Cela ne s'applique qu'à la lecture des données POST, ce qui empêche
les attaques de type slowloris. Si vous voulez vraiment limiter le
temps d'exécution d'une opération, utilisez Programme alarme:.

## Base de données

L'objet Database permet d'interroger MariaDB/MySQL.
Pour se connecter à une base de données :

```
>> db := Maria-DB nouveau hôte: ['localhost'],
	utilisateur: ['xo'],
	mot-de-passe: ['pass123'],
	nom-base: ['xobase'],
	connecter.

```

Pour insérer un enregistrement, utilisez :

```
>> paramètres-recherche := db requête: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], paramètres: ( Liste nouveau ; ['abc'] ; 12.35 ; 6 ). # parameterized queries

{  paramètres-recherche exécuter. db valider. }
intercepter: { :e db annuler.  }, démarrer.
```

Notez que xoscript fonctionne *uniquement* avec des transactions et ne valide jamais automatiquement (autocommit).
Si l'autocommit ne peut pas être désactivé, vous obtenez une erreur de connexion.
Utilisez toujours la liaison de paramètres pour les requêtes ; n'ajoutez jamais directement
une saisie utilisateur au SQL.

Obtenez l'id inséré ainsi :

```
Sortie écrire: ['INSERTED: '] + paramètres-recherche insert-id, stop. # insert id
```

Pour récupérer des enregistrements :

```
>> paramètres-recherche :=
db
	requête: ['SELECT * FROM book order by id desc limit 2'], 
	récupérer: { :row 
		Sortie écrire: row id + [' '] + row description + [': '] + row price, stop.
	}. # fetching rows

```

## Sessions

Pour la persistance, vous pouvez stocker des données dans un objet session et les y récupérer.
Créez d'abord un nouveau **Document-Web**. L'objet Document-Web réunit
la requête, les en-têtes, le HTML et la session. En effet, lorsque vous
visitez un site web avec votre navigateur, vous ne voyez que le HTML. Mais le
Document-Web complet comprend aussi des **en-têtes**. Par exemple,
la plupart des réponses HTTP contiennent un en-tête comme Content-type:text/html pour
indiquer au navigateur que les données qui suivent doivent être affichées comme du HTML
(et non téléchargées comme un fichier, par exemple). Les sessions permettent de
conserver des données utilisateur entre les requêtes. Pour suivre ces données, nous devons
définir un cookie ; ce cookie est lui aussi défini au moyen d'un en-tête. C'est pourquoi
tout se rejoint dans le Document-Web (car c'est le document
complet, contenant à la fois les en-têtes et le HTML ou d'autres données).


```
# First we make a new Web Document instance
>> web := Document-Web nouveau.

# Now we start a session, this will generate a Header for a cookie and
# create a file to store your data, associated with that cookie
>> session := web démarrer-session.

# Now we can treat session like a dict
session userid: 123.
```

Pour détruire la session (lors de la déconnexion) :

```
web détruire-session.
```

## En-têtes

Le Document-Web vous permet aussi de définir d'autres en-têtes connus.
Par exemple, si vous voulez rediriger l'utilisateur vers une autre URL :

```
web aller-à: ['/other.html'].
```

En coulisse, cette commande génère aussi l'en-tête HTTP à envoyer
avec vos autres données ou votre HTML, pour indiquer au navigateur de se rendre
à l'adresse cible indiquée.

Pour ajouter un en-tête personnalisé :

```
web en-tête: ( 
	En-tête-HTTP nouveau
	clé: ['Content-Length']
	valeur: 400
).
```

Pour afficher une page 404 :

```
web introuvable: ['OOps..'].
```


## Modèles

Le système de modèles par défaut est très simple. Vous n'avez pas à apprendre
une nouvelle syntaxe de modèles. De plus, le moteur de modèles garantit une véritable séparation
entre la présentation et la logique métier.

Pour créer un modèle à partir d'un fichier :

```
>> tpl := web modèle: ['templates/ux.tpl'].
```

Le système de modèles utilise des marqueurs. 
Il existe trois types de marqueurs : les marqueurs de coupe, les marqueurs de collage et
les marqueurs d'emplacement. Le principe est vraiment simple : vous découpez
des zones délimitées par des marqueurs de coupe et vous pouvez les coller aux
endroits indiqués par des marqueurs de collage. Vous pouvez injecter des textes dans
les marqueurs d'emplacement.

Par exemple, avec le modèle suivant, plaçons la
pierre précieuse dans l'écrin et ajoutons une étiquette de prix.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Vous pouvez procéder ainsi :

```
>> gem := tpl couper: ['gem'], copier.
gem price: 99.
tpl coller: gem à: ['jewels'].
web sortir: tpl purger.
```

La dernière ligne envoie simplement le modèle sous forme de texte au client,
avec les en-têtes HTTP nécessaires.

Résultat :

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

Pour servir de manière sécurisée des fichiers envoyés par les utilisateurs, vous pouvez vous appuyer sur passthru :

```
>> uploaded := ['smile.gif'].
Server transmettre: uploaded préfixe: ['/uploads/images/'].
Programme fin.
```

Cela sert le contenu envoyé par l'utilisateur avec le type mime
approprié. Seuls les types mime d'une liste blanche sont pris en charge :
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF et SVG.
Les fichiers SVG, ZIP et GZIP sont envoyés en téléchargement, car un SVG
peut contenir des scripts qui s'exécuteraient sinon sur votre domaine.
Cette méthode empêche les attaques TOCTOU, les traversées de chemin,
l'exécution de code malveillant (injection), les attaques par lien symbolique,
les attaques DDoS (limite de fichier = 50 Mo), les attaques par reniflage et
divers autres problèmes de sécurité.


## JSON

Pour encoder un objet en JSON :

```
>> json := ( JSON jsonify: ( 
	Dictionnaire nouveau mettre: ( 
		Liste nouveau ; 1 ; 2 ; 3
	) à: ['abc']
)).
```

Pour décoder du JSON en objet xoscript :

```
>> dict := ((JSON objet: json) abc ? 1).
```

Un JSON comportant plus de 500 niveaux d'imbrication est rejeté comme invalide.

Pour envoyer directement un Dictionnaire en json avec les bons en-têtes :

```
web json: dict.
```


## Expressions régulières

Vous pouvez utiliser des expressions régulières en créant un motif.
Par exemple, pour trouver les href et les cibles des hyperliens :

```
Motif nouveau: ['href="([^"]+)" target="([^"]+)"'].
```

Appliquez ensuite le motif au texte à analyser comme ceci :

```
pattern correspondance: sujet faire: { :m :x .... }
```

Exemple complet :

```
>> sujet := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> pattern := Motif nouveau: ['href="([^"]+)" target="([^"]+)"'].
>> result  := pattern correspondance: sujet faire: { :m :x
	Sortie écrire: m, stop.
	Sortie écrire: x, stop.
	<- ['XXX'].
}.
Sortie écrire: result, stop.
```

## Réseau

Utilisez l'objet Réseau pour effectuer une requête web.
L'objet Réseau envoie toujours une requête POST, sauf si vous envoyez Rien comme
données ; il envoie alors une requête GET.


```
Réseau 
post: Rien 
vers: ['https://redbeanphp.com'].
```

## Chiffrement

Le plugin serveur fournit un chiffrement basé sur XChaCha20 et Argon2.

Exemple :

```
>> encrypted := Coffre chiffrer: ['hello'] clé: ['world'].
>> decrypted := Coffre chiffrer: encrypted clé: ['world'].
```

## Jetons

Pour générer un jeton cryptographiquement sûr d'une longueur donnée :

```
>> mytok := Coffre jeton: 40.
```

Cela génère un jeton de 40 caractères.

## Mise en forme

L'objet Format vous permet de mettre en forme des données, par exemple en complétant avec des espaces ou
en ajoutant des zéros. Il utilise la syntaxe de printf.

```
>> fmt := Format nouveau: ['%06.0f'].
fmt appliquer: 56. # gives 000056
```

Un format peut contenir une seule conversion, et celle-ci doit correspondre à la valeur ;
sinon, vous obtenez une erreur :

- `appliquer:` avec un texte : `%s`
- `appliquer:` avec un nombre : `%f`, `%e`, `%g` ou `%a`
- `appliquer-entier:` avec un nombre : `%d`, `%i`, `%o`, `%u`, `%x` ou `%c`

Les valeurs d'une requête sont des textes. Pour en mettre une en forme comme nombre,
convertissez-la d'abord :

```
fmt appliquer: (demande get: ['amount']) nombre.
```

## Encodeurs

Plusieurs encodeurs et décodeurs sont disponibles.
L'encodeur d'url prépare une url pour l'utiliser comme lien en HTML :

```
Server url-encoder: ['https://example.com?a=6&b=1 2'].
```

Pour injecter en toute sécurité une saisie utilisateur dans votre HTML sans risquer
d'injections XSS, utilisez toujours :

```
Server html-encoder: ['<harmless>'].
```

Notez que le moteur de modèles effectue toujours un encodage html
lorsque vous écrivez dans un marqueur d'emplacement. Si vous utilisez le système de modèles,
vous n'avez donc pas besoin de cela.

## Envoi de courriels

Pour envoyer un courriel, utilisez la bibliothèque mailtools.xo.

Exemple :

```
Server initialiser.
Programme utiliser: ['mailtools.xo'].

>> e-mail := E-mail-HTML nouveau.
>> img := e-mail attacher: ( Fichier nouveau: ['myimage.png'] ).

e-mail
expéditeur: ['xo@xoscript.com'] nom: ['xo'],
destinataire: ( Liste nouveau ; ['xo2@xoscipt.com'] ),
sujet: ['xoxo'],
corps: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), envoyer.

```



## Liaison

Avec le message lier:, vous pouvez lier une bibliothèque externe à
votre programme au moyen de libffi. Pour plus de détails, voir le chapitre sur ffi.


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

FFI est fourni par plateforme ou par plugin, car il
est lié à l'architecture du système sous-jacent, ce que le
cœur n'est pas censé faire.
Le plugin serveur propose une implémentation conforme de ffi/blob.
Par défaut, le cœur se connecte à la plateforme cible
via stdin/stdout, des services limités d'entrée/sortie sur fichiers et le shell (Programme système:).
L'intégration complémentaire est fournie par ffi/blobs au travers de plugins
orientés application, comme le plugin serveur.

FFI signifie Foreign Function Interface (interface de fonctions étrangères). Il vous permet d'utiliser des fonctionnalités écrites par d'autres dans
d'autres langages de programmation, fournies sous forme de fichiers DLL, SO ou Dylib. Il peut s'agir
de fonctions très variées, et cette méthode donne accès à un très large éventail de fonctionnalités.
Commençons par un exemple :

```
Server lier: (
 Liste nouveau ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Liste nouveau ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s libérer.
```

Le résultat de ce code est que vous verrez ceci sur la ligne de commande :
FFI has 3 letters.
Vous vous dites sans doute : « Cela fait beaucoup de code pour quelque chose d'aussi simple. »
Après tout, ne pourrait-on pas résoudre cela avec une commande Gui show ? La réponse est un oui retentissant !
Mais il s'agit ici d'un exemple illustratif.
FFI sert généralement à des tâches plus complexes, mais celles-ci ne font pas de bons
exemples ; j'ai donc choisi quelque chose de trivial.

Les arguments de la méthode de liaison :

- Argument n° 1 : le fichier DLL ou SO que vous voulez utiliser.
- Argument n° 2 : la fonction de ce fichier que vous voulez lier.
- Argument n° 3 : une liste avec les noms des types de données des arguments de la fonction.
- Argument n° 4 : le nom du type de retour de la fonction.
- Argument n° 5 : le nom de l'objet auquel vous voulez lier cette fonction (s'il n'existe pas, il est créé
automatiquement).
- Argument n° 6 : le message auquel cette fonction doit être liée.

Dans l'exemple ci-dessus, nous voulons lier la fonction printf de libc.so. Vous trouverez les noms
des types de données dans la documentation du logiciel auquel vous vous liez. Les types disponibles sont :
void, pointer, float, double, int, uint, char, uchar, intX et uintX,
où X peut valoir 8, 16, 32 ou 64.

Ces types désignent la taille nécessaire pour stocker les données. Pour printf, nous nous lions à un
nouvel objet appelé Printf et au message template:number:. Vous traduisez la fonction
externe dans le dialecte XOScript avant de l'utiliser. Le message template:number: attend comme
premier paramètre un tampon contenant le texte du modèle. Nous créons ce tampon avec un objet Blob, qui
vous permet d'allouer de la mémoire manuellement. C'est à vous de libérer cette mémoire ensuite
avec le message libérer.

Vous pouvez remplir un blob mémoire de diverses manières. Dans notre exemple, nous le remplissons avec du texte ; nous utilisons donc le
message utf8: (UTF-8 est un encodage qui convertit du texte en octets). Vous pouvez aussi remplir un blob avec
bytes:, en passant une liste de valeurs d'octets. Pour lire le contenu d'un blob, utilisez de:longueur:.
Vous récupérez alors les octets sous forme de liste. Vous pouvez même créer une struct C avec un Blob à l'aide du
message struct:, en passant une suite de types C. Cela peut être nécessaire pour appeler une fonction
C d'une bibliothèque logicielle externe qui attend un pointeur vers une struct.

{warning}
Vous devez libérer les blobs vous-même.
Les blobs ne sont pas nettoyés par le ramasse-miettes.
{/warning}

Comme les blobs peuvent être échangés avec des fonctions externes de bibliothèques, ils
ne peuvent pas être récupérés automatiquement par le ramasse-miettes (ils peuvent rester utilisés par
des fonctions externes, ou ces fonctions externes peuvent vouloir les libérer
elles-mêmes). Vous devez donc libérer les blobs vous-même si nécessaire.

Pour libérer un blob, utilisez :

```
myblob libérer.
```

Pour libérer une struct, utilisez :

```
mystruct libérer-struct libérer.
```

Pour une struct, vous devez donc envoyer deux messages, libérer-struct et libérer, pour
désallouer le bloc de mémoire.

@api_Blob_fficonnect
