# Noções básicas

{{messages}}


Bem-vindo ao XOScript
O projeto XOScript tem como objetivo criar uma linguagem de scripting simples e auditável.
Simples não significa necessariamente fácil.
Uma linguagem de programação familiar pode ser mais fácil de usar do que o XOScript.
Aqui, simplicidade significa algo diferente:
ser capaz de formar um modelo mental completo da linguagem e do seu comportamento.

O XOScript foi concebido para caber na sua cabeça.
A sua gramática e o número de conceitos são deliberadamente reduzidos.
Não existem classes; os objetos podem ser estendidos diretamente.
Os objetos são passados por referência, a cópia é explícita
e as funções têm um único ponto de saída.

Algumas destas escolhas diferem significativamente das linguagens mais comuns.
O XOScript não tem, por exemplo, um sistema de tipos e utiliza âmbito dinâmico.
As mensagens que não podem ser tratadas são ignoradas em vez de produzirem uma exceção.
Estas escolhas têm consequências e não se destinam a eliminar erros.
Destinam-se a manter o modelo subjacente da linguagem pequeno e coerente.

O XOScript também pode ser localizado, o que permite exprimir regras de negócio
numa linguagem natural e, eventualmente, partilhá-las com partes interessadas sem formação técnica.

Auditabilidade significa aplicar a mesma filosofia à implementação.
O runtime está escrito em C, com um pequeno lexer, parser e tree walker escritos à mão.
A biblioteca padrão e o runtime refletem em grande medida a estrutura da linguagem,
o que torna a relação entre o código XOScript e a sua implementação relativamente direta.

Os testes também estão estreitamente ligados à documentação.
Cada método deve ter um teste associado que possa ser incorporado no manual,
o que ajuda a manter a documentação sincronizada com a implementação.

O XOScript não pretende competir com as linguagens mais comuns em
funcionalidades ou familiaridade. Explora um objetivo diferente:
um ambiente de programação que um programador consiga compreender como um todo.

A esperança é que uma linguagem pequena e uma implementação
pequena tornem viável compreender o software
do byte ao objeto, da sintaxe ao runtime, e escrever código com
confiança, porque compreende tanto o que acontece no
script como o que acontece nos bastidores.

A arquitetura de uma instalação de servidor xoscript
é simples, mas flexível.

{{architecture.png}}

Para usar o xoscript como linguagem de servidor, é necessário instalar o
plugin de servidor numa pasta chamada /mods/server. 

Isto deve-se ao facto de preferirmos
separar a linguagem base das funcionalidades específicas de servidor,
ao contrário, por exemplo, do PHP ou do Python. Caso contrário, teríamos de
distribuir tudo e mais alguma coisa a toda a gente sem qualquer propósito, o que é simplesmente absurdo.
Também pode instalar outros módulos, se quiser. O sistema é muito
flexível.

Além disso, algumas funções são mais bem implementadas na própria linguagem
de scripting, como os templates e a gestão de sessões, pelo que também
distribuímos as bibliotecas template.xo e webtools.xo para sua conveniência.
A razão de tudo isto é que não sabemos como pretende
usar o xoscript. Pode usá-lo como linguagem de scripting do lado do servidor,
mas também para GUIs, dispositivos embebidos ou simplesmente processamento em lote.
Mesmo que o use como linguagem de scripting do lado do servidor (que é
atualmente um dos principais casos de utilização), pode querer
usar um motor de templates ou um gestor de sessões diferente.
Quem somos nós para decidir que deve usar os nossos?

Uma das vantagens de usar o nosso próprio motor de templates é que
não precisa de aprender sintaxe adicional para criar templates.
O motor de templates predefinido que acompanha o xoscript separa a 100%
a apresentação da lógica. Em vez de uma sintaxe especial
de templates, usa simplesmente um sistema muito flexível de marcadores de espaços.
Para mais informações, consulte o capítulo Servidor.

Note que, se não quiser usar o motor de templates predefinido nem
as webtools predefinidas, é evidente que terá de fornecer
os seus próprios.

Se executar o seu servidor web num chroot, jail ou outro tipo de sandbox,
também precisa de instalar as dependências do xo nesse ambiente; pode
ver de que bibliotecas precisa com o ldd (consulte a manpage do Linux ou do BSD).
Se quiser usar comandos de shell nos seus scripts xo, copie também uma shell
(como bash ou ksh) para esse ambiente.

Queremos também salientar que levamos a retrocompatibilidade muito a sério.
Existe até uma funcionalidade especial de retrocompatibilidade chamada
'version'. Em geral, o nosso objetivo é que o seu código funcione para sempre. Assim,
nunca terá de atualizar o seu código para se manter compatível com versões mais recentes
do xoscript. O nosso objetivo é: escrever uma vez, executar para sempre.

O resto deste manual é dedicado a explicar em pormenor a linguagem de
programação xoscript. O scripting de servidor é abordado no capítulo
chamado Servidor. Se for um programador experiente, talvez queira
saltar alguns capítulos, porque alguns são um pouco detalhados demais ou
muito semelhantes às práticas gerais de programação. Assim, para quem
já tem experiência com várias outras linguagens de programação,
o melhor é tratar este manual como um guia de referência.

## Instalação em Linux

Descarregue o apache2 e o mariadb:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Descarregue o xoscript.
Substitua X pelo número de versão correto!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Copie os ficheiros para a webroot e para /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Edite a configuração do apache2:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Substitua Virtualhost por:

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

Crie uma página de teste:

```
sudo nano /var/www/html/test.xo
```

e escreva um pequeno programa de teste:

```
#!/bin/xo
Server inicializar.
Programa usar: ['webtools.xo'].
>> web := Documento-Web novo.
web emitir: ['Hello World'].
```

Permita que o apache2 execute o seu programa através de CGI:

```
sudo chmod uog+x /var/www/html/test.xo
```

Reinicie o apache2:

```
sudo systemctl restart apache2
```

Abra a sua página de teste no browser:

```
http://localhost/test.xo
```

Deverá ver:

```
Hello World
```


## Instalação em OpenBSD

Edite /etc/httpd.conf e acrescente:


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

Se quiser usar SSL:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Para proteger a troca de chaves contra ataques quânticos,
selecione a cifra mlkem:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Adicione o binário xo e os mods, bem como todas as dependências, ao
chroot (descubra-as com o ldd).

## Executar exemplos


Para executar um dos programas de exemplo do pacote:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Por exemplo, para executar o exemplo FizzBuzz em Linux:

```
./example.sh fizzbuzz Linux
```

Para executar o mesmo exemplo em OpenBSD:

```
./example.sh fizzbuzz OBSD
```

Para executar o exemplo com uma compilação limpa:

```
./example.sh fizzbuzz OBSD clean
```

## Testes unitários

Para executar os testes unitários:

```
./runtests.sh
```

Para executar os testes unitários sem compilar (apenas testar):

```
./runtests.sh nobuild
```

## Compilação

Para compilar a partir do código-fonte em Linux:

```
make clean
ISO="en" make
```

Em OpenBSD:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

Para compilar o plugin de servidor em Linux:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

Para compilar o plugin de servidor em OpenBSD:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Olá mundo

Depois de o ficheiro ter sido transferido para o seu computador, pode extraí-lo
e iniciar o xo com o seguinte comando:

```
xo
```

Para executar um XOScript, guarde o programa num ficheiro com o sufixo
-xo (opcional). Além disso, insira o nome do ficheiro do seu programa
a seguir ao comando XOScript:

```
xo myprogram.xo
```

Quando executa um comando XOScript usando o ficheiro do seu programa como
parâmetro, o xo lê e executa esse ficheiro.

{{note}}
Também pode iniciar o seu programa arrastando-o para o ícone do xo.
{{/note}}

{{warning}}
Em alguns sistemas, é necessário conceder previamente ao xo permissões para carregar
bibliotecas dinâmicas.
{{/warning}}

Manda a tradição que o primeiro programa em qualquer nova linguagem
de programação seja uma espécie de saudação ao mundo. Em XOScript, um
programa **Hello world** deste tipo tem o seguinte aspeto:

@test598

Quando este texto é guardado num ficheiro, por exemplo hello.xo, pode ser executado da
seguinte forma: .

xo hello.xo

Hello world


Pode ver o resultado do programa na janela preta apresentada acima.
Ao longo deste manual, será usada a mesma visualização para mostrar
o resultado.

{{note}}
Saída escreve-se com S maiúsculo.
Em geral, os objetos começam com uma letra maiúscula,
a não ser que funcionem como uma instância (não têm métodos
próprios, apenas dados). Isto reflete as convenções de classe e
instância de outras linguagens de programação.
{{/note}}


## Sintaxe 

O XOScript é uma linguagem de programação *puramente* *orientada a objetos*. Isto significa
que o xoscript considera que tudo é um objeto, pelo que não existem
outros *tipos de dados*. Existem essencialmente três ações básicas
num programa escrito em XOScript: *atribuir*, *enviar mensagens*
e *responder*. A troca de mensagens entre objetos é a parte essencial de
um programa XOScript. As três ações estão ilustradas
abaixo:


Ação                 | Exemplo
-------------------- | --------
atribuir             |  \>\> x := 1. 
mensagens unárias    | x par?.
mensagem binária     | 1 + 2.
mensagem de palavra-chave | x de: 0 comprimento: 10.
resposta             | <- answer.  


Este capítulo dá-lhe uma impressão geral da linguagem XOScript
e descreve os seus princípios básicos. O XOScript é uma linguagem pequena,
assente em três ações (ver ilustração) que se traduzem em
aproximadamente seis regras gramaticais. É tudo o que é preciso para dominar a
linguagem.

Não se preocupe se as coisas não forem imediatamente óbvias: todos os
elementos serão explorados no próximo capítulo (3) e as regras básicas serão
repetidas. O presente capítulo serve, no entanto, sobretudo como uma introdução
geral à linguagem. Os princípios básicos serão brevemente
explicados e ilustrados com vários exemplos relevantes. Os pormenores
em falta serão descritos mais adiante.

Os comentários em XOScript começam com o símbolo \#. Assim, a linha seguinte
será ignorada:

```
# isto é apenas um comentário
```

## Variáveis

Para atribuir
uma variável, usa-se o símbolo de declaração de variáveis: >>. O nome de uma
variável pode conter todos os sinais, exceto: <-, :=, espaços em branco,
pontos, vírgulas, dois pontos, aspas [' '] e parênteses ().
Além disso, uma variável não pode ocupar várias linhas. Note
que uma variável não pode começar por um número nem por um sinal de menos.

Estes são exemplos de variáveis válidas:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dólar'].
>> +plus := Sim.
>> senha-utilizador := ['Psst!'].
```

São exemplos de variáveis inválidas:


```
>> -123 := ['número negativo'].
>> password of utilizador := ['Confidencial'].
>> password.of:utilizador := ['Confidencial'].
>> ,x := 10.
```

{{note}}
Não precisa de escapar nenhum carácter
(incluindo plicas, aspas e delimitadores
de strings) num
literal de string, desde que isso não
cause ambiguidade para o lexer.
{{/note}}

Depois de uma variável ter sido declarada, pode ser usada livremente. Isto significa
que só é necessário usar o símbolo de declaração na primeira vez
que usa a variável (a declaração).

Mais concretamente, não pode começar simplesmente a atribuir um valor à
sua variável *(x := 2)*, pois tem primeiro de declarar a variável *(\>\>
x := 2)*. No entanto, depois de declarada, pode alterar o seu valor
sem usar o símbolo de declaração *(\>\> x := 2. x := 3.)*.

Note que é obrigatório atribuir um valor a uma variável no momento da
declaração. Ao contrário de outras linguagens de programação, não é permitido
declarar uma variável sem valor. É essencial associar explicitamente
cada variável a um valor inicial. Ainda assim, pode perfeitamente inicializar
a variável com o objeto **Nulo**. Nesse caso, a variável pode ser
considerada vazia *(\>\> x := Nulo.)*. Em suma, declarar uma
variável sem valor inicial não é permitido. Assim,

```
>> x.
```

é inválido e dará uma mensagem de erro.

{{note}}
O xoscript usa âmbito dinâmico de variáveis; para
mais pormenores, consulte o capítulo Funções.
{{/note}}


## Literais

O XOScript considera que tudo é um objeto, ou seja, todos os números, strings
e fragmentos de código. Os números, como 1, 2, 100, -999 e 1,234, são
objetos Número. Todos os textos entre plicas são objetos
String. Todos os fragmentos de código agrupados entre chavetas {...} são
objetos Código.

Literal         | Objeto raiz  | Exemplo
--------------- | ------------ | ----------
números         | Número       | 1,2,3... 
strings         | String       | \['hello'\]
função          | Código       | { 1 + 2. }.
                
     
Objetos como números e strings têm sempre a sua origem num objeto
raiz. Por exemplo, todos os números derivam do objeto **Número**. Todas as
strings derivam de **String** e todos os fragmentos de código de **Código**. Por
sua vez, todos estes objetos derivam de **Objeto**, que é, de facto, o
objeto raiz de todos os objetos.


## Mensagens

Programar em XOScript significa basicamente
enviar mensagens a objetos. A notação geral para enviar uma mensagem a
um objeto é a seguinte:

```
<object> <message>
```

Para saber se o número **2**, por exemplo, é par, a
mensagem **par?** é enviada ao objeto **2**:

```
2 par?
```

A resposta será **Sim** (mais uma vez, um objeto). As mensagens desconhecidas são
normalmente ignoradas pelos objetos, pelo que não ocorre nenhum erro. Alguns objetos (por exemplo,
números ou strings) respondem a uma mensagem desconhecida de uma forma predefinida
(mais sobre este assunto adiante).

Um objeto pode receber três tipos de mensagens. 

Tipo             | Número de argumentos
---------------- | -------------------
Unária           | 0      
Binária          | 1     
Palavra-chave    | 1+    


Em primeiro lugar, existem as **mensagens
unárias**, ver o exemplo acima, que não têm argumentos. Em segundo lugar,
existem as **mensagens de palavra-chave**, que têm um ou vários argumentos,
por exemplo:

```
>> x := Número entre: 1 e: 10.
```

Neste caso, a mensagem **entre:e:** é enviada a **Número**, que
é o objeto raiz de todos os números. O resultado será um número aleatório
entre 1 e 10. Por fim, existem as **mensagens binárias**, que têm
apenas um carácter e um argumento:

```
2 + 3
```

Isto parece uma soma matemática, mas é na verdade apenas mais uma mensagem. A
mensagem **+** é enviada a **2**, com o argumento **3**, o que devolve
a resposta **5**. As mensagens binárias podem ser escritas sem dois pontos.

As mensagens binárias podem ser encadeadas:

```
>> x := 3 + 2 - 1.
```

Neste fragmento, **+ 2** é primeiro enviado ao objeto **Número** **3**, o que
resulta no objeto Número **5**, após o que **-1** é enviado a este
número. Os leitores atentos notarão, com razão, a discrepância que
este protocolo apresenta em relação à ordem matemática convencional dos
operadores. O XOScript ignora a ordem matemática em favor da
coerência do seu sistema de mensagens. Consequentemente, a soma:

```
2 + 3 * 5 = 25
```

e não 17.

Isto é intencional. Podem ser usados parênteses para alterar a ordem:

```
2 + (3 * 5) = 17
```

A maioria dos objetos devolve-se a si próprio como resultado de uma determinada
mensagem. Isto é útil, pois incentiva a continuação do diálogo com esse
objeto através do envio de uma mensagem seguinte:

```
Saída escrever:
[' olá '] trim maiúsculas.
```

```
OLá
```

Aqui, são enviadas duas mensagens ao objeto **String**: **trim**, seguida
de **maiúsculas**.

No fragmento seguinte, é necessário usar uma vírgula para indicar
que vem aí uma nova mensagem. Caso contrário, o XOScript ficará confuso.

```
Saída escrever: ['Hello!'], stop.
```

Primeiro, a mensagem **escrever:** é enviada ao símbolo do lápis, seguida de
**stop**. Sem a vírgula, o XOScript pensaria que pretende enviar
**stop** à **string** **Hello!**, um exercício inútil.

A ordem de processamento das mensagens é a seguinte: da esquerda para a direita;
começa pelas mensagens entre parênteses, seguidas das mensagens unárias. Depois,
as mensagens binárias e, por fim, as mensagens de palavra-chave. Veja o exemplo
abaixo:

```
Saída escrever: 0.5 arredondado + (2 - 1), stop.
```

O XOScript lê sempre da esquerda para a direita: primeiro, a mensagem **escrever:**
é enviada a Saída e é seguida da mensagem **stop**. Dentro do
próprio argumento, o XOScript lê da esquerda para a direita, portanto **0.5 arredondado**
e depois **+**.

{{note}}
A mensagem stop acrescenta um carácter de nova linha à string.
O nome desta mensagem inspira-se nos sistemas de telégrafo.
As mensagens nos sistemas de telégrafo 
usavam frequentemente a palavra STOP para marcar o fim de uma frase
(uma vez que a pontuação era pouco fiável ou dispendiosa).
{{/note}}

Além disso, **arredondado** tem precedência sobre **+**, porque é uma
**mensagem unária**. Devido aos parênteses, **2 - 1** é calculado
primeiro, após o que **1** é somado ao resultado de **0.5 arredondado** (1).

Todo o processo dá o resultado **2**, que é também a resposta
escrita. A seguir à vírgula vem a mensagem stop, que move o cursor
para uma nova linha. Naturalmente, a melhor forma de compreender totalmente a ordem
dos programas XOScript é com a prática.

Vale a pena notar que, em XOScript, ao contrário de muitas outras linguagens
de programação, os espaços em branco são uma parte fundamental da sintaxe. Em
particular no caso das mensagens binárias, os espaços em branco podem causar alguma
confusão. Use sempre um espaço em branco a seguir a uma mensagem binária. Não pode
juntar diretamente um número à mensagem, por exemplo: 

```
3 + 2
```

é diferente de 

```
3 +2
```

O primeiro exemplo (**3 + 2**) envia a
mensagem **+** ao número **3**, com o número **2** como argumento. O
resultado, neste caso, será **5**. No segundo exemplo (**3 +2**),
a mensagem unária **+2** é enviada ao número **3**. Consoante o
contexto, isso pode dar um resultado muito diferente.

## Métodos inexistentes

Enviar uma mensagem a um objeto invoca a função que foi
associada a esse objeto com o nome dessa mensagem. Se enviar uma mensagem
que não é compreendida, o objeto recetor ignora a sua mensagem
e devolve, em vez disso, uma referência a si próprio para continuar a comunicação.
Isto chama-se passagem tolerante de mensagens.

Exemplo:

```
Saída escrever: Objeto blah, stop.
```

Isto não dará erro. Escreverá simplesmente o texto **Objeto**.


## Fluxo de controlo

Em XOScript não são necessárias regras gramaticais separadas para *ciclos* e
*ifs*. Uma instrução if é apenas uma simples mensagem **sim:** ou **não:**
enviada a um objeto **Sim** ou a um objeto **Não**:

```
2 par? sim: {
	Saída escrever: ['Dois é um número par'], stop.
}.
```
No exemplo anterior, a mensagem **sim:** é enviada a **Sim** (a
resposta à pergunta: 2 é um número par?). Como argumento, é enviado um
fragmento de código adicional: um objeto **Código**. Esta função escreve no
ecrã que 2 é, de facto, um número par.

Também não são necessárias regras de escrita separadas para um *ciclo*. Para
executar um fragmento de código três vezes, basta enviar **\*** com o argumento
**3** a esse **Código**:

@test5

Neste fragmento de código, **i** é o índice. Assim, na primeira vez que o Código
é executado, **i** é igual a 0, na vez seguinte **i** = 1 e
assim por diante.

Vejamos outro exemplo. Quando é preciso imprimir uma tabela de conversão
de *kJ* (quilojoule) para *kcal* (quilocaloria) em passos de 100,
a notação correta é a seguinte:

@test599

Aqui, o número da linha atual é transmitido ao parâmetro
**:line**. No início de uma função, são definidos os parâmetros
da função. Os parâmetros não usados permanecem vazios (**Nulo**). Os parâmetros são
sempre colocados no início da função, logo a seguir à chaveta
inicial, e são precedidos de dois pontos.

A mensagem **enquanto:** é uma combinação de um *ciclo* e de uma *condição*.
Duas funções podem ser ligadas através da mensagem **enquanto:**. A função recetora
continua a ser executada até que a função a seguir aos dois pontos dê um resultado
negativo. Exemplo:

@test600

No fragmento de código ilustrado acima, **1** é somado a **x** enquanto
**x** for menor do que **5**. Quando deixa de ser esse o caso, a segunda
função responde com **Não** e, consequentemente, a execução da
primeira função termina. Note que **x** foi definido fora da
função e é uma variável global. Para saber mais sobre as regras de âmbito,
consulte o capítulo sobre Funções.

## Interpolação de strings

A lista *kJ/kcal* poderia ficar mais
apresentável. De preferência, a lista seria a seguinte:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Quando converte o resultado pretendido num template, a sua notação
poderia ser:

```
number1 kJ ➞ number2 kcal
```

Isto significa que **number1** representa o valor em kJ e **number2** o
valor em kcal. É assim que funciona a interpolação de strings em XOScript. Não
são necessárias regras gramaticais separadas para isso em XOScript. Basta enviar
a palavra que deve ser substituída ao texto, com o texto de substituição
como argumento:

```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

O resultado:

```
100 kj ➞ 23.9 kcal
```

Esta regra de substituição funciona para todas as mensagens não definidas recebidas
por um objeto **string**. Cada mensagem que não é reconhecida pelo
objeto **string** é interpretada da seguinte forma: *substituir o texto da mensagem
pelo texto do argumento da mensagem.* Pode adaptar o
programa da seguinte forma:


@test601


Para evitar confusões sobre que mensagens podem ou não ser usadas como
substituição, o melhor é introduzir um marcador de template como &lt; &gt;
para os segmentos de texto do template que
devem ser substituídos.

## Valores de retorno

Para responder a uma mensagem, usa-se a seta de
retorno (*<-*). O exemplo seguinte ilustra como criar uma tarefa
para calcular uma percentagem:

@test602

Depois de a tarefa ter sido definida e atribuída à variável **percentage**,
a mensagem **aplicar:e:** é enviada com os argumentos **100** e **7**.

Isto executa a tarefa aplicada a **100** e **7**, ou seja, 7% de 100.
Com a seta de retorno, a resposta é devolvida da tarefa ao
programa principal.

## Estender

Embora este código seja válido, tem uma desvantagem,
porque é preciso lembrar a ordem dos argumentos. Então, porque não
escrevê-lo assim: *7 percent of: 100 *? Isso pareceria muito mais
*natural*. Para tornar isto possível, temos de adaptar o objeto pai de
**7**, que é o objeto **Número**, para que compreenda a
mensagem **percent of:**. Isto consegue-se enviando **em:fazer:** ao
objeto Número, da seguinte forma:

@test603

Como a percentagem é, neste caso, o próprio número, referimo-nos a isto,
a palavra-chave *isto*. Em suma, o símbolo isto significa: *envia esta
mensagem a mim próprio*.

# Objetos

{{messages}}

Além de ajustar e expandir objetos existentes, também pode criar
novos objetos simplesmente enviando a mensagem **novo**. Suponha que
quer criar um objeto fatura que imponha uma sequência de
numeração; nesse caso, precisa primeiro de um objeto fatura.

Sabendo que cada objeto deriva de outro objeto que, por sua vez,
acaba por ter origem no objeto raiz de todos os objetos, chamado Objeto,
é preciso escolher em qual desses outros objetos o seu
novo objeto se vai basear. O seu novo objeto herda todas as propriedades do
objeto em que se baseia, ou seja, daquele ao qual a mensagem **novo**
foi inicialmente enviada.

Neste exemplo, prefere-se um objeto bastante neutro, sem demasiadas
propriedades herdadas. Isto torna a escolha fácil, porque nesse
caso o novo objeto pode basear-se no próprio objeto raiz, que é
**Objeto**. A notação do sistema de faturação pretendido será então a
seguinte:

@test604

O número da fatura atual é guardado no objeto, e é por isso que é
colocada a palavra-chave **prop** à sua frente. A isto chama-se uma *propriedade*;
mais pormenores adiante.

Algumas empresas preferem incluir o ano nos números das
faturas. Nesse caso, pode criar um novo objeto fatura baseado num
objeto fatura anterior, mas que dá ao seu utilizador a possibilidade de
indicar um ano específico:

@test605

Não é necessário escrever novamente a implementação da mensagem **número**,
uma vez que é herdada do **objeto fatura** escrito
anteriormente; consequentemente, o código antigo pode ser reutilizado. O XOScript não tem conceitos
como classes e outros conceitos relacionados. Isto significa que os objetos só
podem herdar de outros objetos, o que também se designa por *herança
prototípica*.

Voltemos agora às propriedades. As propriedades de um objeto só podem ser acedidas
a partir de *dentro da hierarquia do objeto*, pelo que estas propriedades
não podem ser vistas por outros objetos.

Ao contrário de outras linguagens de programação, todas as propriedades dos objetos são
visíveis exclusivamente para o objeto que criou a propriedade e para
os objetos derivados. 

Uma técnica muito usada é utilizar um objeto como uma espécie de *planta*,
como acontece, por exemplo, com as faturas abordadas anteriormente.
Outro bom exemplo é o **Point**. Imagine que cria um
programa informático que faz cálculos usando pontos num mapa. Pode
desenvolver o objeto **Point**, com as propriedades de uma
coordenada x e de uma coordenada y, que serão disponibilizadas ao
mundo exterior através de mensagens:

@test606

A mensagem **=** compara os dois pontos usando a mensagem **e:**. A
primeira comparação resulta num **Sim** ou num **Não**. Estes são objetos
booleanos. Quando envia a mensagem **e:** a um objeto Sim e o
objeto argumento a seguir aos dois pontos também é **Sim**,
recebe novamente **Sim** como resposta. Quando um deles é **Não**,
recebe a resposta **Não**. Note que um ponto não consegue ler as coordenadas do
outro. É necessário enviar uma mensagem ao outro ponto para lhe pedir
estes dados: **x-coordinate** e **y-coordinate**. Afinal, como já foi
explicado, as propriedades só podem ser obtidas a partir de dentro
da própria família do objeto. 

Note que a mensagem **=** é aqui usada para fazer a comparação
dos pontos. Poderia igualmente ter sido usada outra mensagem, como
**is:** ou **equal:**; no entanto, reutilizar o carácter **=** pareceu
adequado neste caso.

## Herança

Pode reutilizar código escrito anteriormente para criar uma hierarquia
de objetos. Por exemplo:

```
>> Animal := Objeto novo.
>> Cão := Animal novo.
>> Caniche := Cão novo.
```

Neste caso, **Dog** herda todo o comportamento e todas as propriedades
de **Animal** e, por sua vez, o objeto **Animal** herda todo o comportamento de
**Objeto**, o objeto raiz de todos os objetos.


## Redefinição


No exemplo seguinte, é criado um novo tipo de lista:
**Combination**, em que se garante que cada elemento é único. As
funções da lista são reutilizadas através da herança:

@test607

Observe como o segundo **red** é excluído da lista.

Ocasionalmente, pode ser necessário redefinir um comportamento de um objeto.
Por exemplo, quando ao somar números é preciso ter em conta as unidades de
medida. No exemplo seguinte, é criado o objeto **Size**.
Este objeto devolve um número que, durante a soma, tem
em conta a unidade do número a somar. O objeto **Número**
verifica se se trata de *polegadas* ou de *pés*. O código
poderia ser semelhante ao seguinte:

@test608

## Recursividade

No exemplo anterior, o **sinal** de mais é redefinido. Note
que, no fim, a soma final continua a ter de ser feita, o que, de facto,
acontece na linha seguinte:

```
>> réplica := isto + (número x fator).
```

Mas como é que o XOScript percebe que este **sinal** de mais se refere à
lógica original da soma?** Por exemplo, outra interpretação
poderia ser que o XOScript enviasse repetidamente a mesma mensagem ao mesmo
objeto, o que, por sua vez, resultaria num **ciclo infinito**. Obviamente,
não é essa a intenção. Assim que envia uma mensagem a um objeto
que executaria exatamente o mesmo código, o XOScript percebe,
neste caso, que se pretende a mensagem subjacente, redefinida. Assim, o seu
programa fica automaticamente protegido contra este tipo de ciclos
infinitos. No entanto, quando o seu objetivo é de facto executar a mesma função a partir da
função atual, é necessário enviar primeiro a mensagem
**recursivo**. Nesse caso, o resultado será um ciclo
infinito. Existem, no entanto, aplicações úteis para tarefas recursivas, por
exemplo, suponha que quer calcular o fatorial de um determinado
número. Nesse caso, basta adicionar a mensagem **factorial** a
Número:

@test609

Isto exige recursividade. De facto, a tarefa associada à
mensagem **factorial** tem de ser executada novamente dentro dessa função.
Assim, é necessário invocar a função factorial a partir da própria
função factorial. Por regra, o XOScript impede esta rotina,
devido ao risco de acabar num ciclo infinito. Por esta razão,
é fundamental preceder a mensagem da palavra **recursivo**. Isto
serve para informar o XOScript de que é sua
intenção executar a mesma tarefa e de que não cometeu um erro.

## Objetos semelhantes a classes

Embora o xoscript não ofereça classes, imitar um comportamento
semelhante ao de classes é trivial. Basta redefinir a mensagem novo.

```
>> Animal := Objeto novo.
Animal em: ['novo'] fazer: {
	<- isto novo inicializar.
}.

Animal em: ['inicializar'] fazer: {
	prop som := ['?'].
	prop patas  := 4.
}.
```

No fragmento de código acima, criamos um objeto chamado Animal.
Este objeto serve de *planta* para todo o tipo de animais,
como cães e gatos. O objeto pai Animal é escrito
com A maiúsculo para indicar que se trata de um objeto semelhante a uma classe.
Em seguida, redefinimos a mensagem novo escrevendo o nosso próprio método novo.
Neste caso, ele envia a mensagem novo a isto, seguida da mensagem
inicializar. Como o xoscript bloqueia a recursividade por predefinição, isto não provoca
um ciclo infinito. Em vez disso, envia a mensagem novo ao objeto
pai (Objeto), o que resulta numa nova instância de Animal. Assim, criamos
um novo objeto baseado no mesmo objeto para o qual criámos o nosso método novo.
Isto é perfeitamente válido. Enviamos também a mensagem inicializar, que garante
que o objeto Animal tem valores predefinidos para as suas propriedades. Por predefinição,
um animal tem 4 patas e o som é desconhecido (daí o ponto de interrogação).
Para criar uma nova instância do nosso Animal, poderíamos simplesmente escrever:

```
>> a := Animal novo.
```

Obtemos agora uma nova instância de Animal com 4 patas, som desconhecido e
um método inicializar. Tal como noutras linguagens OOP, também podemos
estender o nosso Animal:

```
>> Cão := Animal novo.
Cão em: ['inicializar'] fazer: {
	isto inicializar.
	prop som := ['ladra'].
}.
```

Podemos testar isto facilmente acrescentando um método string:

```
Animal em: ['string'] fazer: {
	<- prop patas string + prop som.
}.
```

Vamos juntar tudo:

@test13


Criar um objeto que é colocado num determinado estado inicial é um
problema frequente. Suponha que é preciso criar um objeto **Rectangle**
para calcular o perímetro e a área. Uma notação possível seria:


```
>> Retângulo := Objeto novo.

Retângulo em: ['área'] fazer: {
	<- prop comprimento * prop largura.
}.
```

Obviamente, definir um comprimento e uma largura é uma condição prévia. Para esse
fim, podem ser adicionadas as mensagens **comprimento:** e **width:**:


```
Retângulo em: ['length:'] fazer: { :comprimento
	prop comprimento := comprimento.
}.

Retângulo em: ['width:'] fazer: { :largura
	prop largura := largura.
}.

```

Este retângulo pode então ser utilizado da seguinte forma:


```
>> retângulo := Retângulo novo length: 2, width: 3.
Saída escrever: retângulo área.
```

No entanto, se as definições iniciais de comprimento e largura forem esquecidas,
ocorre uma mensagem de erro:

```
>> retângulo := Retângulo novo.
Saída escrever: retângulo área.
```

produz o seguinte erro:

```
Chave não encontrada:comprimento
```

Para evitar isto, é preferível que um retângulo tenha
sempre um comprimento e uma largura iniciais, por exemplo 0. Assim, neste
caso, é necessário **redefinir** a mensagem **novo**.

@test610

Se redefinirmos a mensagem novo, estamos basicamente a imitar uma **classe**.

O mundo do XOScript está repleto de uma diversidade de objetos que estão
disponíveis para o seu programa desde o início. Nos próximos capítulos,
todos estes objetos centrais serão abordados.

## Snapshots

Pode guardar um objeto (juntamente com o seu estado atual) em disco com:

```
meuobjeto save-as: ['saved.bin'].
```

Para voltar a carregar o objeto a partir do disco:

```
>> meuobjeto := Objeto load-from: ['saved.bin'].
```

Os snapshots podem ser usados para guardar um determinado estado ou para melhorar o desempenho.
Carregar um snapshot evita o lexing, o parsing e a configuração da aplicação.
Além disso, no futuro, poderão ser introduzidas vantagens de desempenho adicionais
com os snapshots, como a otimização de certos padrões ou a deteção e
otimização de caminhos críticos.

{{warning}}
Os snapshots são uma funcionalidade experimental; não os use em produção.
Para ativar as funcionalidades experimentais, compile com -D EXPERIMENTS.
{{/warning}}


@test712

# Objeto Nulo

{{messages}}

O objeto Nulo
representa o vazio, ou melhor ainda, a ausência de informação. Por
vezes, receberá este objeto como resposta a uma mensagem, quando
o resultado é **nada**. A pergunta mais essencial
que pode fazer ao objeto **Nulo** é: **Nulo?**. A
resposta será sempre **Sim**.

```
Saída escrever: Nulo Nulo?.
```

resultado:

```
Sim
```

Qualquer objeto que não seja **Nulo** responderá com **Não**. O
fragmento de código acima pode parecer um pouco filosófico, mas o objeto **Nulo**
tem certamente aplicações extremamente práticas. Por exemplo,
receberá o objeto Nulo como resposta se pedir um
elemento de uma lista que não existe. Também pode usar o objeto Nulo
se quiser declarar uma variável, mas ainda não quiser especificar um
valor. Em vez disso, basta **atribuir** o valor especial **Nulo**. Em
XOScript não é permitido declarar uma variável sem valor, como:


```
>> valor.
```

Em vez disso, tem de escrever o seguinte:

```
>> valor := Nulo.
```

@api_None_base

# Booleanos

{{messages}}

Ao contrário da maioria das linguagens de programação populares à data em que este texto foi escrito,
o XOScript disponibiliza apenas um único objeto Sim e um único objeto
Não. Para esclarecer, cada vez que escreve **Sim**, isso não significa que
tenha sido criado um novo objeto. Em vez disso, usa sempre uma referência. Isto
significa que, quando escreve o seguinte:

\>\> x := Sim.

O **x** refere-se ao objeto **Sim**. O código condicional e os ciclos também
verificam esta referência. Em XOScript, o significado de **Sim** e **Não**
não é fixo. Na verdade, um programa XOScript fica bastante abalado com uma
instrução como esta:

Sim := Não.

O resultado de tais ações é indefinido; no entanto, continua a ser uma ação
válida e, portanto, formalmente permitida. Além disso, existe um objeto
Boleano, que é o objeto raiz de **Sim** e de **Não**, uma vez que ambos
derivam desse objeto raiz. O próprio objeto Boleano, no entanto,
não tem qualquer aplicação prática.

## Armadilhas

Tenha cuidado ao usar **e:** e **ou:**

```
Saída escrever: (Não or: Sim or: Sim), stop.
Saída escrever: (Não ou: Sim, ou: Sim), stop.
```

Dá

```
Não
Sim
```
porque a mensagem **ou:** aceita apenas 1 argumento. A primeira mensagem
envia **ou:ou:** a Não, que não existe, pelo que o objeto ignora
a mensagem e devolve-se a si próprio (Não). Por outro lado, a segunda linha
envia **ou:** seguida de outro **ou:** (usando um símbolo de encadeamento, ou seja, uma vírgula: ,).


@api_Boolean_base

# Números

{{messages}}

Cada vez que escreve um número, por exemplo 9, -10 ou 3,12, o XOScript
converte esse número, nos bastidores, num objeto **Número**. Pode
enviar mensagens a este objeto Número, ou pode atribuir o número
a uma variável e enviar-lhe mensagens depois:

```
10 par?

>> notaDeDez := 10.
notaDeDez par?

```

Ambas as notações são válidas. O objeto Número responde às seguintes
mensagens...

A maioria destas mensagens dispensa explicação e permite executar
operações matemáticas ou comparações.

{{note}}
Note que pode usar ≤ ≥ ≠ × e ÷ em vez dos seus equivalentes ASCII.
É uma questão de preferência.
{{/note}}

A diferença entre as mensagens matemáticas binárias (+) e
as suas variantes de palavra-chave (adicionar:) é que as primeiras devolvem
um novo número, que é o resultado da operação, enquanto com as
segundas é o próprio objeto que é modificado. Isto é ilustrado no
exemplo seguinte:

@test597

No exemplo acima, b = 4 e a = 3. Com **adicionar: 2**, o valor
de a é aumentado em 2, enquanto **+ 3** cria um novo número que é
igual a a + 3. O mesmo se aplica a outras operações matemáticas, por exemplo,
multiplicações. Ao usar o símbolo de multiplicação, recebe um
novo objeto como resposta. Se usar a mensagem **multiplicar-por:**,
multiplica o próprio número.

Com a mensagem **entre:e:**, por exemplo em: **Número
entre: X e: Y**, obtém um número entre X e Y. Desta
forma, pode ser gerado qualquer número aleatório:

```
>> a := Número entre: 1 e: 10.
Saída escrever: a, stop.
```

A partir da versão 1.4, o gerador de números aleatórios incorporado no xoscript é,
tanto quanto sabemos, criptograficamente seguro.

Pode associar um **qualificar** a um número, por exemplo, **6
maçãs**. Cada mensagem que não é reconhecida por um
número é considerada um qualificador. Pode obter o qualificador de
um número através da mensagem qualificar:

Um qualificador é basicamente um objeto de texto que é guardado com o objeto
Número. O qualificador também é escrito a seguir ao número numa
instrução **escrever:**. Os qualificadores podem ser usados, por exemplo, para somar montantes
em moedas diferentes. Ao somar os montantes, pode pedir
os qualificadores. O exemplo de programa seguinte ilustra este
princípio com uma calculadora de moedas históricas (já que a taxa
de câmbio se mantém razoavelmente estável!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Strings

{{messages}}

Cada vez que um texto é colocado entre **blocos e aspas** ['...'],
o XOScript cria um novo objeto string. No entanto, certifique-se
de que usa as aspas corretas. A aspa no
início do texto é diferente da que está no fim (isto permite-lhe
usar a plica sem precisar de a escapar).

## UTF8

As strings em xoscript contêm normalmente texto codificado em utf8. Embora
seja tecnicamente possível ter conteúdo binário ou não utf8 numa
string, recomenda-se o uso de blobs para esse fim. Os blobs são
disponibilizados pelo plugin de servidor (ver o capítulo ffi).
Em geral, os blobs/ffi são disponibilizados
por plugin/plataforma, uma vez que estão ligados à plataforma
e à arquitetura (ffi/blobs). O núcleo da linguagem de scripting procura
manter-se tão independente da plataforma quanto possível.

## Conversão de tipos

Pode criar uma cópia de qualquer objeto
com um tipo diferente usando as seguintes mensagens:

Mensagem | Resultado
-------- | ------
número   | Converte num número
string   | Converte numa string
boleano  | Converte num booleano
  
Aplicam-se as seguintes **regras**:

mensagem | Nulo      | Boleano            | Número                | Texto     | Outro              
-------- | --------- | --------           | --------              | --------  | --------
boleano  | Não       | n/a                | 0→Não senão→Sim       | Sim       | Geralmente Sim
número   | 0         | Não→0 Sim→1        | n/a                   | ['n']→n   | Geralmente 1
string   | ['Nulo']  | ['Não']/['Sim']    | ['n']                 | n/a       | Depende

## Copiar

Os valores em XOScript são sempre passados **por referência**. Noutras linguagens
depende do tipo de valor; em XOScript só existe uma forma,
por referência. O XOScript nunca faz uma cópia de um valor. Para copiar um objeto,
tem de enviar a mensagem **copiar**. 

@test611

Aqui, poderia esperar que o resultado fosse Dolly, em vez
de Donny. No entanto, não é o caso, uma vez que ambos os nomes se referem ao mesmo
objeto. Quando se trabalha com um ciclo, acontece algo semelhante:

@test612

Na verdade, o XOScript usa **sempre** referências, pelo que, em **:quantity**,
o ciclo ilustrado acima também indica a referência ao elemento
da lista.

Para copiar um objeto, tem de especificar esta ação
**explicitamente**:

@test613

Ao enviar a mensagem unária **copiar** a uma string, o objeto
devolve uma cópia desse mesmo objeto string. É possível copiar objetos
Número, objetos booleanos, listas e mapas da mesma forma.

Também pode definir a sua própria implementação de cópia; isto é mesmo uma
necessidade se criar os seus próprios objetos. A implementação
predefinida de copiar para uma lista faz uma cópia superficial: cria uma
nova lista com os mesmos elementos.

@test614

Neste caso, 4 é adicionado apenas à cópia.
No entanto, como a cópia é superficial, os objetos em ambas as listas
são os mesmos.

@test615

Assim, se acrescentarmos 2 a cada nome na cópia, a lista
original também é afetada.

Para resolver isto, precisamos de fazer uma **cópia profunda**. Uma ação de cópia deste tipo
para uma lista poderia ser composta da seguinte forma:

@test616

Note também a mensagem recursivo; é necessário enviar esta mensagem
antes da mensagem copiar.

É essencial ter em conta que, embora uma cópia de um objeto
tenha muitas vezes o mesmo aspeto do original, na verdade
nunca será o mesmo. O objeto raiz define uma mensagem **igual:**,
que pode ser usada para comparar a identidade de objetos. Veja o
exemplo seguinte:

@test617

## Conversão implícita

O XOScript usa **conversão implícita** para converter objetos. Para escrever uma
lista no ecrã, o XOScript envia, por exemplo, a mensagem
*string* internamente à lista. Isto pode revelar-se muito útil
se quiser escrever uma lista como uma lista separada por vírgulas. A
mensagem *string* pode ser redefinida: 

@test620

@api_String_base
@api_Format_base


## Strings de servidor

As seguintes funcionalidades de String são acrescentadas pelo
plugin Servidor.

@api_String_server

# Funções

{{messages}}

Pode agrupar código entre { e }; passa então a ser uma função.
Em xoscript também usamos por vezes o termo tarefa ou simplesmente
bloco de código.

Pode executar uma função enviando a mensagem *iniciar*.


```
{ Saída escrever: 123, stop. } iniciar.
```

Se a sua função receber argumentos, use **aplicar:**.

```
{ :a Saída escrever: a, stop. } aplicar: a.
```

Veja também os exemplos abaixo.
Devido à arquitetura simples, uma função só pode ter
um ponto de retorno. Para evitar sobrecarga ou aninhamento excessivo de
condições, pode usar um procedimento (o que equivale a usar o
sinal de multiplicação com o argumento 1):

```
{
  (a = 1) sim: { x := 1. }, parar.
  (a = 2) sim: { x := 2. }, parar.
} procedimento.
```

Desta forma, (a = 2) não é avaliado se a = 1.
Além disso, assim não precisa de mensagens sim aninhadas.
Sempre que der por si a aninhar condições, pense
na mensagem procedimento. Pode tornar o seu código
mais fácil de ler.


Eis uma armadilha importante:

```
{
	Não não: {
		Saída escrever: ['Terminar o ciclo.'].
	}, parar.
	
	Saída escrever: ['Não me mostres.'].

} procedimento.

```

Neste caso, o texto 'Dont show me' será mostrado,
porque **parar** é enviado a Não. Se quiser executar
um parar, este tem de ser enviado como mensagem a **Sim**.
 

```
{
	Não não sim: {
		Saída escrever: ['Terminar o ciclo.'].
	}, parar.
	
	Saída escrever: ['Não me mostres.'].

} procedimento.

```

Funcionará como esperado.

## Exceções

As exceções podem ser tratadas assim:

```
{ Tarefa 1 } pegar: { Tarefa 2 }, iniciar.
```

Também pode provocar intencionalmente um erro no seu programa e,
desse modo, ativar o bloco de tratamento. Isto faz-se enviando a
mensagem **erro:** à tarefa atual, como mostra a
ilustração seguinte:

```
{
este-bloco-de-código erro: ['Ups!'].
} pegar: { :engano
Saída escrever: engano.
}, iniciar.
```

## Injetar valores

O XOScript oferece às tarefas a possibilidade de injetar valores. Veja
a tarefa abaixo:

```
>> envio := {
	Boletim destinatário: prop recipient.
}.
envio setar: ['recipient']
valor: ['info@recipient.org'].
envio iniciar.
```


Esta ilustração apresenta uma tarefa imaginária que envia uma newsletter
para um endereço de email ou **recipient**. Este destinatário pode ser injetado
na tarefa, a partir do exterior e antes de a tarefa ser iniciada, enviando a
mensagem **setar:valor:** à tarefa. Desta forma, o valor de
**recipient** é predefinido na tarefa. Este valor também pode ser alterado
e a tarefa pode depois ser executada novamente. Este é um método útil quando se usam
objetos Task.

## Funções vazias

Não são permitidas tarefas vazias. Em teoria, uma tarefa vazia teria este
aspeto: **{}**; no entanto, o XOScript considera isto um erro de linguagem. Se
quiser declarar uma tarefa vazia, pode usar o objeto Nulo:

```
>> tarefa := Nulo.
```

Embora isto não seja uma verdadeira tarefa, mas sim um objeto Nulo, pode
mesmo assim ser-lhe enviada uma mensagem iniciar:

```
>> réplica := tarefa iniciar.
```

Na verdade, isto é o mesmo que:

```
>> réplica := Nulo iniciar.
```

Como o objeto **Nulo** não reconhece a mensagem **iniciar**,
devolve-se a si próprio como resposta, pelo que a resposta volta a ser **Nulo**.
Assim, não há necessidade de ter uma tarefa vazia. Graças ao design
elegante da linguagem de programação XOScript, pode simplesmente usar o objeto
Nulo para este fim.

## Âmbito dinâmico

Quando um Código precisa de uma variável mas não a encontra,
verifica as variáveis do Código que o **chamou**
e continua a procurar ao longo da cadeia de Códigos.
Este processo de procura continua até a variável ser encontrada.
Se a variável continuar sem ser encontrada, surge uma mensagem de erro. Este método de procura de uma
variável chama-se **âmbito dinâmico**.

Para ilustrar este princípio:

@test618

@api_Code_base

# Objeto raiz

{{messages}}

O objeto chamado **Objeto** é o objeto raiz de todos os objetos em
XOScript e disponibiliza as funcionalidades centrais da linguagem. 

A mensagem enviada com mais frequência
é **em:fazer:**, que expande as funcionalidades de um objeto. Esta
mensagem é recebida pelo objeto raiz, que associa então a
tarefa especificada à mensagem e, desse modo, expande o objeto
derivado.

## Métodos catch-all

Normalmente, se enviar uma mensagem que não corresponde a
um método do objeto, ela é ignorada. No entanto, pode especificar
os chamados **métodos mágicos** ou métodos **catch-all**, que são
invocados se a mensagem não for compreendida pelo objeto.

Existem 4 métodos catch-all disponíveis. Cada mensagem corresponde
a um número específico de argumentos.

Mensagem catch-all     | Número de argumentos
---------------------- | -------------------
responder:             | 0
responder:e:           | 1
responder:e:e:         | 2
responder:e:e:e:       | 3


@test619

## Mensagens programáticas

Em vez de enviar uma mensagem diretamente a um objeto, também é possível
enviá-la através de uma variável. Para isso, usa-se a mensagem
**menssagem:argumentos:**. 

@test396

@api_Object_base

# Listas

{{messages}}

O XOScript conhece dois tipos de coleções: *listas* e *mapas*.
As **listas** são enumerações de objetos numa *ordem fixa*. Os mapas não têm
ordem; em vez disso, assemelham-se a uma legenda que associa uma chave (ou termo) ao
valor correspondente. As listas são comparáveis aos arrays (PHP, Java, C)
e às listas (Python). Os mapas são comparáveis aos arrays associativos (PHP) ou
aos dicionários (Python) de outras linguagens de programação. Para criar
uma nova Listar, escreva:

```
>> fibonacci := Listar novo.
```

Esta lista vazia pode ser preenchida com **acrescentar:**:

```
fibonacci acrescentar: 0.
fibonacci acrescentar: 1.
fibonacci acrescentar: 1.
fibonacci acrescentar: 2.
fibonacci acrescentar: 3.
fibonacci acrescentar: 5.
fibonacci acrescentar: 8.
fibonacci acrescentar: 13.
```

Se escrevermos a lista no ecrã:

```
Saída escrever: fibonacci, stop.
```

Veremos:

```
Listar ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

Em vez de acrescentar, também pode usar ; para adicionar elementos a uma lista:


```
>> fibonacci := Listar novo ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Os pontos e vírgulas (;) são todos mensagens binárias que colocam um
valor na lista.

## Encadeamento

Suponha que tem uma lista como:

```
>> x := Listar novo ; 1 ; 2 ; 3.
```

Se quiser apagar o primeiro e o último elemento, a sua
mensagem seria:

```
x corte-esq corte-dir.
```

Infelizmente, a notação anterior não funciona corretamente. A
mensagem **corte-esq** devolve o primeiro elemento da lista, que,
por sua vez, se torna o recetor da mensagem **corte-dir**. Assim, a
mensagem **corte-dir** não é enviada a **x**, mas sim a 2. Uma
possível solução para este problema seria criar duas frases
separadas, como: 

```
x corte-esq.
x corte-dir.
```

No entanto, isto é bastante pouco prático, em particular quando é preciso
apagar mais de dois elementos. Por isso, o XOScript oferece uma
estrutura de mensagens alternativa para este tipo de situações. Nas
estruturas de mensagens **alternativas**, as respostas dos objetos são ignoradas
e recebe sempre de volta o objeto recetor como resposta.
Uma estrutura de mensagens **alternativa** é iniciada enviando a
mensagem **fazer** a um objeto e a estrutura de mensagens **alternativa**
pode ser terminada enviando a mensagem **pronto**. No
exemplo ilustrado, isto poderia ser aplicado da seguinte forma:

```
>> x := Listar novo ; 1 ; 2 ; 3.
x fazer corte-esq corte-dir pronto.
```

@api_List_collections

# Mapas

{{messages}}

**Tanto Listar como Mapa são coleções. No entanto, ao contrário de uma
lista, um mapa **não tem** ordem. Outra distinção entre os dois
é que um mapa é composto por pares de objetos. Um objeto funciona como entrada (ou
palavra-chave) para procurar o outro objeto. Um bom exemplo de uma
lista deste tipo é uma lista de preços, como:


```
>> ementa := Mapa novo
	colocar: ['£5'] em: ['tarte de maçã'],
	colocar: ['£6'] em: ['bolo de cenoura'],
	colocar: ['£3'] em: ['fudge'].
```

Tal como numa lista, a mensagem colocar:em:
é usada para adicionar um objeto a uma lista. A diferença é que, ao contrário de
uma lista, são associados dois objetos. O primeiro objeto é, tal como
numa lista, o objeto que vai guardar na lista. O segundo
objeto não é a sua posição na coleção, mas sim a **entrada**
que permite obter o objeto anterior mais tarde. Em
suma, um mapa funciona um pouco como um dicionário: através da palavra-chave
encontra-se o significado. Por exemplo, para obter da
lista acima o preço de um fudge:

```
>> price := ementa em: ['fudge'].
```

Também pode usar a notação concisa:

```
>> price := ementa ? ['fudge'].
```

Se as entradas que usa para guardar objetos não tiverem espaços
(e não colidirem com outras mensagens predefinidas),
também pode ser usada a notação seguinte:

```
>> ementa := Mapa novo
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Sem dúvida que a notação acima se lê de forma um pouco mais natural.
Para pedir o preço de um
fudge, pode ser usada a seguinte notação simplificada:

```
>> price := ementa fudge.
```

@api_Dict_collections

# Ficheiro

{{messages}}

O objeto **Arquivo** disponibiliza um acesso básico ao sistema de ficheiros.
Pode usar este objeto para ler ficheiros inteiros de uma só vez para uma variável,
ou escrever variáveis em ficheiros de uma só vez. A leitura linha a linha
também é suportada. Estas são as operações de I/O de ficheiros mais comuns
numa linguagem de scripting. As operações de ficheiros avançadas exigem o
uso de FFI através do plugin de servidor ou de um plugin de IO separado.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Data/Hora

{{messages}}

Para uma representação estruturada da hora e da data, o XOScript usa o
objeto **Momento**. Se um novo objeto Momento for escrito no ecrã, são
mostradas a data e a hora atuais:

```
Saída escrever: Momento novo, stop.
```

Pode dar algo como:

```
2020-10-10 12:16:39
```

Também é fácil ler os componentes individuais da hora. Assim, por
exemplo, se for apenas necessário saber o ano atual, a mensagem
**ano** pode ser enviada ao momento e, por sua vez, a resposta será um
objeto Número que contém apenas o ano:

```
>> m := Momento novo.
Saída escrever: m ano, stop.
```

@api_Moment_system

# Programa/StdOut

{{messages}}

O objeto Programa representa a aplicação em execução. Este objeto
oferece funcionalidades para executar comandos do sistema, incluir subprogramas,
ler argumentos e muito mais. Todas as funções relacionadas com o sistema.

## StdOut

Saída é o objeto de saída padrão. Tem basicamente dois métodos:
**escrever:** e **stop**. A mensagem escrever: é usada para enviar uma string
para o stdout; a mensagem stop escreve um carácter de nova linha.
Em vez de **stop**, também pode usar \\n.

Exemplo:

```
Saída escrever: ['Hello World'], stop.
```

resultado:

```
Hello World
```

## Módulos/Plugins

O mundo do XOScript pode ser expandido com novos objetos de sistema através da
instalação de módulos. Um novo objeto de sistema pode ser adicionado ao mundo do
XOScript colocando o ficheiro do módulo (normalmente um ficheiro com o sufixo .so)
na pasta mods. 

Quando envia uma mensagem ao objeto disponibilizado pelo
módulo de plugin, este é carregado automaticamente pelo XOScript.

Também pode escrever plugins. Os plugins são escritos na
linguagem de programação C. Pode encontrar um plugin de exemplo no pacote
do código-fonte, em src/plugins/example.


## Reflexão

Existem várias formas de explorar
o sistema durante a execução do programa. O XOScript dispõe de alguns métodos para
detetar que objetos estão presentes e a que mensagens esses objetos
respondem. Em primeiro lugar, pode perguntar-se a cada objeto de que **tipo** é;
no entanto, os tipos em XOScript são maleáveis e, por isso, pouco fiáveis.

Também é possível perguntar ao objeto Programa se um
determinado objeto já está presente no programa:

```
Programa Ferramenta sim: { ... }.
```

No caso de um nome de objeto
composto por um único símbolo, o melhor é usar a
notação seguinte para evitar confusões:

```
Programa encontre: ['X'], sim: { ... }.
```

Além de perguntar por objetos, é igualmente possível perguntar ao
objeto Programa por mensagens. Por exemplo, pode perguntar-se se o
objeto **Número** conhece a mensagem **entre:e:**, da forma
ilustrada abaixo:

```
Programa Number: ['between:and:'], stop.
```

@api_Program_system

# servidor

{{messages}}

O plugin Servidor do xoscript oferece funcionalidades para
criar aplicações do lado do servidor. Para carregar o plugin
de servidor, use:

```
Server inicializar.
```

Para sua conveniência, também se recomenda carregar
os ficheiros webtools.xo e template.xo.

```
Programa usar: ['webtools.xo'].
Programa usar: ['template.xo'].

```

## Definições do servidor

Pode configurar as seguintes definições do servidor:

```
	# são dados valores por omissão
	# portanto, se não definir nada, são
	# usados estes valores...

	Programa 
	configurar: ['max-campos']
	valor: 40.

	Programa 
	configurar: ['max-conteudo']
	valor: 2000000. # 2MB

	Programa 
	configurar: ['max-time']
	valor: 5000. # 5sec

```

## Olá mundo

Eis um programa web muito simples que pode usar com um
servidor CGI padrão, como Apache2, NGINX, OpenHTTPD ou qualquer outro
servidor conhecido.

```
#!/bin/xo

Server inicializar.
Programa usar: ['webtools.xo'].

>> doc-web := Documento-Web novo.

doc-web emitir: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Se não quiser usar o objeto Documento-Web, não há problema, mas
nesse caso tem de escrever os cabeçalhos HTTP manualmente:

```
#!/bin/xo
Saída escrever: ['Content-type: text/html; charset=utf-8 \n\n'], stop.
Saída escrever: ['olá mundo!'], stop.
``` 

## Pedido

O objeto Requisição-HTTP pode ser usado para obter dados GET/POST/COOKIE e
UPLOAD:

```
>> pedido  := Requisição-HTTP novo.
>> search   := pedido get: ['search']. # ?search=books
>> password := pedido post: ['password']. # do formulário
>> selecionados := pedido get-lista: ['sel[]']. #?sel[]=1&sel[]=2
>> selecionados := pedido post-lista: ['sel[]'].
>> cookie   := pedido cookie: ['session-id'].
>> carregamento   := pedido upload: ['file'].
>> caminhotemp := carregamento ? 1.
>> nomeficheiro := carregamento ? 0.
```

## Maxpost/length

O número máximo predefinido de campos POST é 40 e o tamanho máximo predefinido
do conteúdo é 2MB. Para configurar valores diferentes por script:

```
Programa configurar: ['max-conteudo'] valor: 1. 
Programa configurar: ['max-campos'] valor: 1. 
```

{{note}}
Se o tamanho do conteúdo exceder o máximo, o
processo é terminado, porque já não podemos ter a certeza
de que o payload é seguro.
{{/note}}

O limite maxtime determina o tempo máximo em ms
para ler o stdin/os dados POST.

```
Programa configurar: ['max-time'] valor: 5000. # 5sec
```

Isto aplica-se apenas à leitura de I/O do POST, o que impede
ataques do tipo slowloris. Se quiser realmente limitar o
tempo de execução de qualquer operação, use Programa tempo-max:.

## Base de dados

O objeto Database pode ser usado para consultar MariaDB/MySQL.
Para se ligar a uma base de dados, faça:

```
>> bd := MariaDB novo host: ['localhost'],
	utilizador: ['xo'],
	palavra-passe: ['pass123'],
	nome-database: ['xobase'],
	conectar.

```

Para inserir um registo, use:

```
>> parametros := bd consulta: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parametros: ( Listar novo ; ['abc'] ; 12.35 ; 6 ). # consultas parametrizadas

{  parametros executar. bd commit. }
pegar: { :e bd rollback.  }, iniciar.
```

Note que o xoscript funciona *apenas* com transações e nunca faz autocommit.
Se não for possível desativar o autocommit, obterá um erro de ligação.
Use sempre parameter binding nas consultas; nunca acrescente input do utilizador diretamente
ao SQL.

Obtenha o id inserido da seguinte forma:

```
Saída escrever: ['INSERIDO: '] + parametros insert-id, stop. # insert id
```

Para obter registos:

```
>> parametros :=
bd
	consulta: ['SELECT * FROM book order by id desc limit 2'], 
	buscar: { :fila 
		Saída escrever: fila id + [' '] + fila description + [': '] + fila price, stop.
	}. # obter linhas

```

## Sessões

Para persistência, pode guardar e obter dados de um objeto de sessão.
Primeiro, crie um novo **Documento-Web**. O objeto Documento-Web reúne
o pedido, os cabeçalhos, o HTML e a sessão. Isto acontece porque, sempre que
visita um website com o seu browser, só vê o HTML. Mas o
Documento-Web completo também é composto por **cabeçalhos**. Por exemplo,
a maioria das respostas HTTP inclui um cabeçalho como Content-type:text/html para
indicar ao browser que os dados que se seguem devem ser apresentados como HTML
(e não, por exemplo, descarregados como um ficheiro). As sessões são uma forma de
guardar dados do utilizador entre pedidos. Para acompanhar estes dados, precisamos
de definir um cookie, e este cookie também é definido através de um cabeçalho. É por isso que
tudo se junta no Documento-Web (porque é o documento completo,
que contém tanto os cabeçalhos como o HTML ou outros dados).


```
# Primeiro criamos uma nova instância de Documento-Web
>> web := Documento-Web novo.

# Agora iniciamos uma sessão, isto vai gerar um Cabeçalho para um cookie e
# criar um ficheiro para guardar os seus dados, associado a esse cookie
>> aSessão := web iniciar-sessão.

# Agora podemos tratar a sessão como um Mapa
aSessão userid: 123.
```

Para destruir a sessão (ao terminar a sessão):

```
web destruir-sessão.
```

## Cabeçalhos

O Documento-Web também permite definir outros cabeçalhos conhecidos.
Por exemplo, se quiser redirecionar o utilizador para outro URL:

```
web ir-para: ['/other.html'].
```

Nos bastidores, este comando também gera o cabeçalho HTTP a enviar
juntamente com os seus outros dados ou HTML, para indicar ao browser que navegue
para o endereço de destino especificado.

Para adicionar um cabeçalho personalizado:

```
web cabeçalho: ( 
	Cabeçalho-HTTP novo
	chave: ['Content-Length']
	valor: 400
).
```

Para mostrar uma página 404:

```
web não-encontrado: ['Uuups..'].
```


## Templates

O sistema de templates predefinido é muito simples. Não precisa de aprender
uma nova sintaxe de templates. Além disso, o motor de templates garante uma verdadeira separação
entre a apresentação e a lógica de negócio.

Para criar um template a partir de um ficheiro:

```
>> tpl := web modelo: ['templates/ux.tpl'].
```

O sistema de templates usa marcadores. 
Existem três tipos de marcadores: marcadores de corte, marcadores de colagem e
marcadores de espaço. A ideia básica é muito simples: recorta
áreas identificadas por marcadores de corte e pode colá-las
em áreas identificadas por marcadores de colagem. Pode injetar strings em
marcadores de espaço.

Assim, por exemplo, dado o template seguinte, vamos colocar a
gema na caixa de joias e acrescentar uma etiqueta de preço.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Pode fazer isto da seguinte forma:

```
>> gem := tpl cortar: ['gem'], copiar.
gem price: 99.
tpl colar: gem em: ['jewels'].
web emitir: tpl depurar.
```

A última linha limita-se a enviar o template como string para o cliente,
juntamente com os cabeçalhos HTTP necessários.

Resultado:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

Para servir de forma segura ficheiros carregados pelos utilizadores, pode recorrer ao passthru:

```
>> carregado := ['smile.gif'].
Server passagem: carregado prefixo: ['/uploads/images/'].
Programa fim.
```

Isto serve o conteúdo carregado pelo utilizador com o tipo mime
adequado. Só são suportados os tipos mime de uma lista de permissões:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF e SVG.
Os ficheiros SVG, ZIP e GZIP são enviados como transferência, porque um SVG
pode conter scripts que, de outro modo, seriam executados no seu domínio.
Este método impede ataques TOCTOU, path traversal, 
execução de código malicioso (injeção), ataques com symlinks,
ataques DDoS (limite de ficheiro = 50MB), ataques de sniffing e 
vários outros problemas de segurança.


## JSON

Para codificar um objeto como JSON:

```
>> json := ( JSON jsonificar: ( 
	Mapa novo colocar: ( 
		Listar novo ; 1 ; 2 ; 3
	) em: ['abc']
)).
```

Para descodificar JSON num objeto xoscript:

```
>> dic := ((JSON objeto: json) abc ? 1).
```

JSON com mais de 500 níveis de aninhamento é rejeitado como inválido.

Para emitir diretamente um Mapa como json com os cabeçalhos corretos:

```
web json: dic.
```


## Regex

Pode usar expressões regulares criando um padrão.
Por exemplo, para encontrar os hrefs e targets das hiperligações:

```
Padrão novo: ['href="([^"]+)" target="([^"]+)"'].
```

Agora, aplique o padrão à string de entrada da seguinte forma:

```
exprReg corresponder: assunto fazer: { :m :x .... }
```

Exemplo completo:

```
>> assunto := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> exprReg := Padrão novo: ['href="([^"]+)" target="([^"]+)"'].
>> resultado  := exprReg corresponder: assunto fazer: { :m :x
	Saída escrever: m, stop.
	Saída escrever: x, stop.
	<- ['XXX'].
}.
Saída escrever: resultado, stop.
```

## Rede

Use o objeto Rede para fazer um pedido web.
O objeto Rede envia sempre um pedido POST, a não ser que envie Nulo como
dados; nesse caso, envia um pedido GET.


```
Rede 
post: Nulo 
para: ['https://redbeanphp.com'].
```

## Encriptação

O plugin de servidor inclui encriptação baseada em XChaCha20 e Argon2.

Exemplo:

```
>> cifrado := Cofre encriptar: ['hello'] chave: ['world'].
>> decifrado := Cofre encriptar: cifrado chave: ['world'].
```

## Tokens

Para gerar um token criptograficamente seguro com um comprimento específico:

```
>> meutok := Cofre token: 40.
```

Isto gera um token de 40 caracteres.

## Formatação

O objeto Formato permite formatar dados, por exemplo preencher com espaços ou
acrescentar zeros. Usa a sintaxe do printf.

```
>> fmt := Formato novo: ['%06.0f'].
fmt aplicar: 56. # dá 000056
```

Um formato pode conter uma conversão, e esta tem de corresponder ao valor;
caso contrário, obtém um erro:

- `aplicar:` com uma string: `%s`
- `aplicar:` com um número: `%f`, `%e`, `%g` ou `%a`
- `aplicar-int:` com um número: `%d`, `%i`, `%o`, `%u`, `%x` ou `%c`

Os valores de um pedido são strings. Para formatar um valor como número,
converta-o primeiro:

```
fmt aplicar: (pedido get: ['amount']) número.
```

## Codificadores

Estão disponíveis vários codificadores e descodificadores.
O codificador de url prepara um url para ser usado em HTML como ligação:

```
Server url-codificar: ['https://example.com?a=6&b=1 2'].
```

Para injetar com segurança input do utilizador no seu HTML sem correr o risco de
injeções XSS, use sempre:

```
Server html-codificar: ['<inofensivo>'].
```

Note que o motor de templates faz sempre codificação html
quando escreve num marcador de espaço. Por isso, se usar o sistema de templates,
não precisa de usar isto.

## Envio de email

Para enviar um email, use a biblioteca mailtools.xo.

Exemplo:

```
Server inicializar.
Programa usar: ['mailtools.xo'].

>> correio-e := Email-HTML novo.
>> img := correio-e anexar: ( Arquivo novo: ['myimage.png'] ).

correio-e
remetente: ['xo@xoscript.com'] nome: ['xo'],
destinatário: ( Listar novo ; ['xo2@xoscipt.com'] ),
assunto: ['xoxo'],
corpo: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), enviar.

```



## Ligação

Com a mensagem ligar: pode ligar uma biblioteca externa ao
seu programa através da libffi. Para mais pormenores, consulte o capítulo sobre ffi.


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

A FFI é disponibilizada por plataforma/plugin, porque está
ligada à arquitetura do sistema subjacente, algo que o
núcleo não deve fazer.
O plugin de servidor oferece uma implementação de ffi/blob conforme.
Por predefinição, o núcleo liga-se à plataforma de destino
através de stdin/stdout, serviços limitados de I/O de ficheiros e da shell (Programa comando-do-sistema:).
A integração auxiliar é disponibilizada pelos ffi/blobs através de plugins
orientados para aplicações, como o plugin de servidor.

FFI significa Foreign Function Interface. Permite usar funcionalidades escritas por outros em
diferentes linguagens de programação, disponibilizadas através de ficheiros DLL, SO ou Dylib. Podem
ser funções muito variadas, e há uma enorme gama de funcionalidades disponíveis através deste método.
Comecemos com um exemplo:

```
Server ligar: (
 Listar novo ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Listar novo ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s livre.
```

O resultado deste código é que verá o seguinte na linha de comandos:
FFI has 3 letters.
Provavelmente está a pensar: "Isto é muito código para algo tão simples."
Afinal, não poderíamos resolver isto com um comando Gui show? A resposta é um rotundo sim!
Mas este exemplo serve apenas para ilustrar.
A FFI é normalmente usada para tarefas mais complexas, mas essas não dão bons
exemplos, por isso escolhi algo trivial.

Os argumentos do método ligar:

- Argumento n.º 1: O ficheiro DLL ou SO que pretende usar.
- Argumento n.º 2: A função desse ficheiro que pretende ligar.
- Argumento n.º 3: Uma lista com os nomes dos tipos de dados dos argumentos da função.
- Argumento n.º 4: O nome do tipo de retorno da função.
- Argumento n.º 5: O nome do objeto ao qual pretende ligar esta função (se não existir, é criado
automaticamente).
- Argumento n.º 6: A mensagem à qual esta função deve ser ligada.

No exemplo acima, queremos ligar a função printf da libc.so. Pode encontrar os nomes dos
tipos de dados na documentação do software ao qual se está a ligar. Os tipos disponíveis são:
void, pointer, float, double, int, uint, char, uchar, intX e uintX,
em que X pode ser 8, 16, 32 ou 64.

Estes tipos referem-se ao número de bytes necessários para guardar os dados. Para o printf, ligamos a um
novo objeto chamado Printf e à mensagem template:number:. A função externa é traduzida
para o dialeto XOScript antes de ser usada. A mensagem template:number: espera um
buffer com o texto do template como primeiro parâmetro. Criamos este buffer com um objeto Blob, que
permite alocar memória manualmente. É responsável por libertar esta memória depois,
com a mensagem livre.

Pode preencher um blob de memória de várias formas. No nosso exemplo, preenchemo-lo com texto, por isso usamos a
mensagem utf8: (UTF-8 é uma codificação para converter texto em bytes). Também pode preencher um blob com
bytes:, passando uma lista de valores de bytes. Para ler o conteúdo de um blob, use de:comprimento:.
Recebe os bytes de volta como uma lista. Pode até criar uma struct de C com um Blob através da
mensagem estrutura:, passando uma sequência de tipos C. Isto pode ser necessário ao chamar uma função
C de uma biblioteca de software externa que espera um ponteiro para uma struct.

{warning}
Tem de libertar os blobs manualmente.
Os blobs não são limpos pelo garbage collector.
{/warning}

Como os blobs podem ser trocados com funções externas de bibliotecas,
não podem ser recolhidos automaticamente pelo garbage collector (podem continuar a ser usados por
funções externas, ou essas funções externas podem querer libertá-los
elas próprias). Por isso, tem de libertar os blobs manualmente, se necessário.

Para libertar um blob, use:

```
meublob livre.
```

Para libertar uma struct, use:

```
minhaestrut estruturalivre livre.
```

Assim, no caso de uma struct, é preciso enviar duas mensagens, estruturalivre e livre, para
desalocar o bloco de memória.

@api_Blob_fficonnect
