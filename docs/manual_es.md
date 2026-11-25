# Conceptos básicos

{{messages}}


Bienvenido a XOScript
El proyecto XOScript tiene como objetivo crear un lenguaje de scripting sencillo y auditable.
Sencillo no significa necesariamente fácil.
Un lenguaje de programación conocido puede resultar más fácil de usar que XOScript.
Aquí, sencillez significa algo distinto:
poder formarse un modelo mental completo del lenguaje y de su comportamiento.

XOScript está diseñado para caber en tu cabeza.
Su gramática y su número de conceptos son deliberadamente reducidos.
No hay clases; los objetos se pueden extender directamente.
Los objetos se pasan por referencia, la copia es explícita
y las funciones tienen un único punto de salida.

Algunas de estas decisiones difieren considerablemente de los lenguajes más extendidos.
XOScript no tiene, por ejemplo, un sistema de tipos y utiliza ámbito dinámico.
Los mensajes que no se pueden atender se ignoran en lugar de producir una excepción.
Estas decisiones tienen consecuencias y no pretenden eliminar los errores.
Su propósito es mantener pequeño y coherente el modelo subyacente del lenguaje.

XOScript también se puede localizar, lo que permite expresar reglas de negocio
en un lenguaje natural y, potencialmente, compartirlas con partes interesadas sin formación técnica.

Auditabilidad significa aplicar la misma filosofía a la implementación.
El entorno de ejecución está escrito en C, con un pequeño analizador léxico, un analizador sintáctico y un recorredor de árbol escritos a mano.
La biblioteca estándar y el entorno de ejecución reflejan en gran medida la estructura del lenguaje,
lo que hace que la relación entre el código XOScript y su implementación sea relativamente directa.

Las pruebas también están estrechamente ligadas a la documentación.
Cada método debería tener una prueba asociada que pueda incorporarse al manual,
lo que ayuda a mantener la documentación sincronizada con la implementación.

XOScript no pretende competir con los lenguajes más extendidos en
funcionalidades ni en familiaridad. Explora un objetivo diferente:
un entorno de programación que un desarrollador pueda comprender en su totalidad.

La esperanza es que un lenguaje pequeño y una implementación
pequeña hagan viable comprender el software
desde el byte hasta el objeto, desde la sintaxis hasta el entorno de ejecución, y escribir código con
confianza, porque entiendes tanto lo que ocurre en
el script como lo que ocurre por debajo.

La arquitectura de una instalación de servidor con xoscript
es sencilla, pero flexible.

{{architecture.png}}

Para usar xoscript como lenguaje de servidor, debes instalar el
plugin de servidor en una carpeta llamada /mods/server. 

Esto se debe a que preferimos
desacoplar el núcleo del lenguaje de las funcionalidades específicas del servidor,
a diferencia, por ejemplo, de PHP o Python. De lo contrario, tendríamos que entregar a todo el mundo
el paquete completo con todo incluido sin ningún propósito, lo cual es simplemente absurdo.
También puedes instalar otros módulos si lo deseas. El sistema es muy
flexible.

Además, algunas funciones se implementan mejor en el propio lenguaje
de scripting, como las plantillas y la gestión de sesiones, por lo que también
incluimos las bibliotecas template.xo y webtools.xo para tu comodidad.
El motivo de todo esto es que no sabemos cómo quieres
usar xoscript. Puedes usarlo como lenguaje de scripting del lado del servidor,
pero también para interfaces gráficas, dispositivos embebidos o simplemente procesamiento por lotes.
Incluso si lo usas como lenguaje de scripting del lado del servidor (que es
actualmente uno de los principales casos de uso), es posible que quieras
usar otro motor de plantillas u otro gestor de sesiones.
¿Quiénes somos nosotros para decidir que debes usar los nuestros?

Una de las ventajas de usar nuestro propio motor de plantillas es, eso sí, que
no tienes que aprender una sintaxis adicional para crear plantillas.
El motor de plantillas predeterminado que se incluye con xoscript ofrece una
separación del 100% entre presentación y lógica. En lugar de una sintaxis
especial de plantillas, utiliza simplemente un sistema de marcadores de ranura muy flexible.
Para más información, consulta el capítulo Servidor.

Ten en cuenta que, si no quieres usar el motor de plantillas predeterminado ni
las webtools predeterminadas, ni que decir tiene que debes proporcionar
los tuyos propios.

Si ejecutas tu servidor web en un chroot, una jail u otro tipo de entorno aislado,
también debes instalar las dependencias de xo en ese entorno; puedes
ver qué bibliotecas necesitas con ldd (consulta la página de manual de Linux o BSD).
Si quieres usar comandos de shell en tus scripts xo, copia también una shell
(como bash o ksh) a ese entorno.

También queremos señalar que nos tomamos muy en serio la compatibilidad con versiones anteriores.
Incluso existe una funcionalidad especial de compatibilidad con versiones anteriores llamada
'version'. En general, aspiramos a que tu código funcione para siempre. Así, nunca
tendrás que actualizar tu código para que siga siendo compatible con versiones más recientes
de xoscript. Nuestro objetivo es: escribir una vez, ejecutar para siempre.

El resto de este manual está dedicado a explicar en detalle el lenguaje
de programación xoscript. El scripting de servidor se trata en el capítulo
llamado Servidor. Si eres un desarrollador de software con experiencia, quizá quieras
saltarte algunos capítulos, porque algunos son demasiado detallados o
muy parecidos a las prácticas generales de programación. Así que, quienes
ya tengáis experiencia con varios otros lenguajes de programación,
haréis mejor en tratar este manual como una guía de referencia.

## Instalación en Linux

Descarga apache2 y mariadb:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Descarga xoscript.
¡Sustituye X por el número de versión correcto!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Copia los archivos al directorio raíz web y a /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Edita tu configuración de apache2:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Sustituye Virtualhost por:

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

Crea una página de prueba:

```
sudo nano /var/www/html/test.xo
```

y escribe un pequeño programa de prueba:

```
#!/bin/xo
Server iniciar.
Programa utilizar: ['webtools.xo'].
>> web := Documento-Web crear.
web salida: ['Hello World'].
```

Permite que apache2 ejecute tu programa mediante CGI:

```
sudo chmod uog+x /var/www/html/test.xo
```

Reinicia apache2:

```
sudo systemctl restart apache2
```

Abre tu página de prueba en el navegador:

```
http://localhost/test.xo
```

Deberías ver:

```
Hello World
```


## Instalación en OpenBSD

Edita /etc/httpd.conf y añade:


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

Si quieres usar SSL:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Para proteger el intercambio de claves frente a la computación cuántica,
selecciona el cifrado mlkem:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Añade el binario xo y los mods, así como todas las dependencias, al
chroot (averígualas con ldd).

## Ejecutar ejemplos


Para ejecutar uno de los programas de ejemplo del paquete:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Por ejemplo, para ejecutar el ejemplo FizzBuzz en Linux:

```
./example.sh fizzbuzz Linux
```

Para ejecutar el mismo ejemplo en OpenBSD:

```
./example.sh fizzbuzz OBSD
```

Para ejecutar el ejemplo con una compilación limpia:

```
./example.sh fizzbuzz OBSD clean
```

## Pruebas unitarias

Para ejecutar las pruebas unitarias:

```
./runtests.sh
```

Para ejecutar las pruebas unitarias sin compilar (solo probar):

```
./runtests.sh nobuild
```

## Compilación

Para compilar desde el código fuente en Linux:

```
make clean
ISO="en" make
```

En OpenBSD:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

Para compilar el plugin de servidor en Linux:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

Para compilar el plugin de servidor en OpenBSD:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Hola mundo

Una vez transferido el archivo a tu ordenador, puedes extraerlo
e iniciar xo con el siguiente comando:

```
xo
```

Para ejecutar un XOScript, guarda el programa como archivo añadiendo el sufijo
-xo (opcional). Además, escribe el nombre del archivo de tu programa
después del comando de XOScript:

```
xo myprogram.xo
```

Cuando ejecutas un comando de XOScript usando el archivo de tu programa como
parámetro, xo leerá y ejecutará ese archivo.

{{note}}
También puedes iniciar tu programa arrastrándolo sobre el icono de xo.
{{/note}}

{{warning}}
En algunos sistemas debes conceder previamente a xo permiso para cargar
bibliotecas dinámicas.
{{/warning}}

La tradición dicta que el primer programa en cualquier lenguaje de
programación nuevo sea una especie de saludo al mundo. En XOScript, un
programa **Hola mundo** de este tipo tiene este aspecto:

@test598

Cuando este texto se guarda en un archivo, p. ej. hello.xo, se puede ejecutar
de la siguiente manera: .

xo hello.xo

Hello world


Puedes ver la salida del programa en la ventana negra mostrada arriba.
A lo largo de este manual se usará la misma representación para mostrar
la salida.

{{note}}
Salida se escribe con S mayúscula.
En general, los objetos empiezan con mayúscula,
salvo que actúen como instancia (no tienen métodos
propios, solo datos). Esto refleja las convenciones
de clase frente a instancia de otros lenguajes de programación.
{{/note}}


## Sintaxis 

XOScript es un lenguaje de programación *puramente* *orientado a objetos*. Esto significa
que xoscript considera que todo es un objeto, por lo que no existen
otros *tipos de datos*. Hay esencialmente tres acciones básicas
en un programa escrito en XOScript: *asignar*, *enviar mensajes*
y *responder*. El intercambio de mensajes entre objetos es la parte clave de
un programa XOScript. Las tres acciones se ilustran
a continuación:


Acción          | Ejemplo
--------------- | --------
asignación      |  \>\> x := 1. 
mensajes unarios | x ¿par?.
mensaje binario | 1 + 2.
mensaje de palabra clave | x desde: 0 longitud: 10.
respuesta       | <- respuesta.  


Este capítulo te dará una impresión general del lenguaje XOScript
y describe sus principios básicos. XOScript es un lenguaje pequeño,
basado en tres acciones (ver ilustración) que se traducen en
aproximadamente seis reglas gramaticales. Eso es todo lo que hace falta para dominar el
lenguaje.

No te preocupes si las cosas no te resultan evidentes de inmediato: todos los
elementos básicos se analizarán en el próximo capítulo (3) y las reglas básicas
se repetirán. Este capítulo, sin embargo, sirve principalmente como introducción
general al lenguaje. Los principios básicos se explicarán brevemente
y se ilustrarán con varios ejemplos relevantes. Los detalles que falten
se tratarán más adelante.

Los comentarios en XOScript van precedidos del símbolo \#. Así, la siguiente línea
se ignorará:

```
# esto es solo un comentario
```

## Variables

Para asignar
una variable se usa el símbolo de declaración de variables: >>. El nombre de una
variable puede contener todos los signos excepto: <-, :=, espacios en blanco,
puntos, comas, dos puntos, comillas [' '] y paréntesis ().
Además, una variable no puede ocupar varias líneas. Ten en cuenta
que una variable no puede empezar con un número ni con un signo menos.

Estos son ejemplos de variables válidas:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dólar'].
>> +plus := Verdadero.
>> clave-acceso-usuario := ['¡Chisss!'].
```

Variables no válidas son, por ejemplo:


```
>> -123 := ['número negativo'].
>> password of elUsuario := ['Confidencial'].
>> password.of:elUsuario := ['Confidencial'].
>> ,x := 10.
```

{{note}}
No tienes que escapar ningún carácter
(incluidas comillas simples, comillas dobles y
delimitadores de texto) en
un literal de texto, siempre que no
cause ambigüedad para el analizador léxico.
{{/note}}

Una vez declarada una variable, se puede usar libremente. Esto significa
que solo es necesario usar el símbolo de declaración la primera vez
que usas la variable (la declaración).

Más concretamente, no puedes empezar sin más a asignar un valor a
tu variable *(x := 2)*, ya que primero debes declarar la variable *(\>\>
x := 2)*. Sin embargo, una vez declarada, puedes cambiar su valor
sin usar el símbolo de declaración *(\>\> x := 2. x := 3.)*.

Ten en cuenta que es obligatorio asignar un valor a una variable en el momento de
declararla. A diferencia de otros lenguajes de programación, no se permite
declarar una variable sin valor. Es imprescindible vincular explícitamente
cada variable a un valor inicial. No obstante, puedes inicializar
la variable con el objeto **Nulo**. En ese caso, la variable puede
considerarse vacía *(\>\> x := Nulo.)*. En resumen, declarar una
variable sin valor inicial no está permitido. Así,

```
>> x.
```

no es válido y producirá un mensaje de error.

{{note}}
xoscript usa ámbito dinámico para las variables;
para más detalles, consulta el capítulo Funciones.
{{/note}}


## Literales

XOScript considera que todo es un objeto; es decir, todos los números, textos
y fragmentos de código. Los números, como 1, 2, 100, -999 y 1,234, son
objetos Número. Todos los textos entre comillas simples son objetos
Texto. Todos los fragmentos de código agrupados entre llaves {...} son
objetos Función.

Literal         | Objeto raíz  | Ejemplo
--------------- | ------------ | ----------
números         | Número       | 1,2,3... 
textos          | Texto        | \['hola'\]
función         | Función      | { 1 + 2. }.
                
     
Los objetos como los números y los textos siempre tienen su origen en un objeto
raíz. Por ejemplo, todos los números derivan del objeto **Número**. Todos
los textos derivan de **Texto** y todos los fragmentos de código de **Función**. A
su vez, todos estos objetos provienen de **Objeto**, que es, de hecho, el
objeto raíz de todos los objetos.


## Mensajes

Programar en XOScript consiste básicamente en
enviar mensajes a objetos. La notación general para enviar un mensaje a
un objeto es la siguiente:

```
<object> <message>
```

Para averiguar si el número **2**, por ejemplo, es par, se envía
el mensaje **¿par?** al objeto **2**:

```
2 ¿par?
```

La respuesta será **Verdadero** (de nuevo, un objeto). Los mensajes desconocidos
suelen ser ignorados por los objetos; por tanto, no se produce ningún error. Algunos objetos (p. ej.,
números o textos) responden a un mensaje desconocido de una forma predefinida
(más sobre este tema más adelante).

Un objeto puede recibir tres tipos de mensajes. 

Tipo            | Número de argumentos
--------------- | -------------------
Unario          | 0      
Binario         | 1     
De palabra clave | 1+    


En primer lugar, están los **mensajes
unarios**, como en el ejemplo anterior, que no tienen argumentos. En segundo lugar,
están los **mensajes de palabra clave**, que tienen uno o varios argumentos,
por ejemplo:

```
>> x := Número entre: 1 y: 10.
```

En este caso, el mensaje **entre:y:** se envía a **Número**, que
es el objeto raíz de todos los números. El resultado será un número aleatorio
entre 1 y 10. Por último, están los **mensajes binarios**, que tienen
un solo carácter y un argumento:

```
2 + 3
```

Parece una suma matemática, pero en realidad es solo otro mensaje. El
mensaje **+** se envía a **2**, con el argumento **3**, lo que devolverá
la respuesta **5**. Los mensajes binarios pueden escribirse sin dos puntos.

Los mensajes binarios se pueden encadenar:

```
>> x := 3 + 2 - 1.
```

En este fragmento, primero se envía **+ 2** al objeto **Número** **3**, lo que
da como resultado el objeto Número **5**, tras lo cual se envía **-1** a este
número. Los lectores atentos habrán notado con razón la discrepancia que
muestra este protocolo respecto al orden matemático convencional de
los operadores. XOScript ignora el orden matemático en favor de la
coherencia de su sistema de mensajes. Como resultado, la suma:

```
2 + 3 * 5 = 25
```

no 17.

Esto es intencionado. Se pueden usar paréntesis para modificar el orden:

```
2 + (3 * 5) = 17
```

La mayoría de los objetos se devuelven a sí mismos como resultado en respuesta a un
mensaje. Esto resulta útil, ya que favorece continuar el diálogo con ese
objeto enviándole un mensaje siguiente:

```
Salida escribir:
[' hola '] recortar mayúsculas.
```

```
HOLA
```

Aquí se envían dos mensajes al objeto **Texto**: **recortar**, seguido
de **mayúsculas**.

En el siguiente fragmento, es necesario usar una coma para indicar
que llega un mensaje nuevo. De lo contrario, XOScript se confundirá.

```
Salida escribir: ['Hello!'], detener.
```

Primero, el mensaje **escribir:** se envía al símbolo del lápiz, seguido de
**detener**. Sin la coma, XOScript pensaría que quieres enviar
**detener** al **texto** **¡Hola!**, un ejercicio inútil.

El orden de procesamiento de los mensajes es el siguiente: de izquierda a derecha;
se empieza por los mensajes entre paréntesis, seguidos de los mensajes unarios. A continuación,
los mensajes binarios y, por último, los mensajes de palabra clave. Mira el ejemplo
siguiente:

```
Salida escribir: 0.5 redondeado + (2 - 1), detener.
```

XOScript siempre lee de izquierda a derecha: primero, el mensaje **escribir:**
se envía a Salida y le sigue el mensaje **detener**. Dentro del propio
argumento, XOScript lee de izquierda a derecha, así que primero **0.5 redondeado**
y después **+**.

{{note}}
El mensaje detener añade un carácter de nueva línea al texto.
El nombre de este mensaje está inspirado en los sistemas telegráficos.
Los mensajes en los sistemas telegráficos 
usaban a menudo la palabra STOP para marcar el final de una frase
(ya que la puntuación era poco fiable o costosa).
{{/note}}

Además, **redondeado** tiene prioridad sobre **+**, porque es un
**mensaje unario**. Debido a los paréntesis, primero se calcula **2 - 1**,
y después se suma **1** al resultado de **0.5 redondeado** (1).

Todo el proceso dará como resultado **2**, que es también la respuesta
escrita. Después de la coma viene el mensaje detener, que mueve el cursor
a una nueva línea. Por supuesto, la mejor manera de comprender por completo el
orden de ejecución de los programas XOScript es con la práctica.

Cabe señalar que en XOScript, a diferencia de muchos otros lenguajes de
programación, los espacios en blanco son una parte fundamental de la sintaxis. En
particular, en el caso de los mensajes binarios, los espacios en blanco pueden causar cierta
confusión. Usa siempre un espacio en blanco después de un mensaje binario. No puedes
unir directamente un número al mensaje; por ejemplo: 

```
3 + 2
```

es diferente de 

```
3 +2
```

El primer ejemplo (**3 + 2**) envía el
mensaje **+** al número **3**, con el número **2** como argumento. El
resultado, en este caso, será **5**. En el segundo ejemplo (**3 +2**),
se envía el mensaje unario **+2** al número **3**. Según el
contexto, eso podría dar un resultado muy distinto.

## Métodos inexistentes

Enviar un mensaje a un objeto invoca la función que se ha
asociado a ese objeto con ese nombre de mensaje. Si envías un mensaje
que no se entiende, el objeto receptor ignorará tu mensaje
y, en su lugar, devolverá una referencia a sí mismo para continuar la comunicación.
Esto se denomina paso de mensajes tolerante.

Ejemplo:

```
Salida escribir: Objeto blah, detener.
```

Esto no producirá ningún error. Simplemente imprimirá el texto **Objeto**.


## Flujo de control

En XOScript no hacen falta reglas gramaticales separadas para *bucles* ni
*condicionales*. Una sentencia if es simplemente un mensaje **verdadero:** o **falso:**
enviado a un objeto **Verdadero** o a un objeto **Falso**:

```
2 ¿par? verdadero: {
	Salida escribir: ['Dos es un número par'], detener.
}.
```
En el ejemplo anterior, el mensaje **verdadero:** se envía a **Verdadero** (la
respuesta a la pregunta: ¿es 2 un número par?). Como argumento se envía además
un fragmento de código: un objeto **Función**. Esta función escribe en
la pantalla que 2 es, en efecto, un número par.

Tampoco hacen falta reglas de escritura separadas para un *bucle*. Para
ejecutar un fragmento de código tres veces, basta con enviar **\*** con el argumento
**3** a esa **Función**:

@test5

En este fragmento de código, **i** es el índice. Así, la primera vez que se
ejecuta la Función, **i** vale 0, la siguiente vez que se ejecuta, **i** = 1, y
así sucesivamente.

Veamos otro ejemplo. Cuando hay que imprimir una tabla de conversión
de *kJ* (kilojulios) a *kcal* (kilocalorías) en pasos de 100,
la notación correcta es la siguiente:

@test599

Aquí, el número de la línea actual se transmite al parámetro
**:line**. Al principio de una función se definen los parámetros
de la función. Los parámetros no utilizados permanecen vacíos (**Nulo**). Los parámetros
siempre se colocan al inicio de la función, justo después de la llave
de apertura, y van precedidos de dos puntos.

El mensaje **mientras:** es una combinación de un *bucle* y una *condición*.
Se pueden enlazar dos funciones mediante el mensaje **mientras:**. La función receptora
seguirá ejecutándose hasta que la función que va después de los dos puntos dé un
resultado negativo. Ejemplo:

@test600

En el fragmento de código anterior, se suma **1** a **x** mientras
**x** sea menor que **5**. Cuando esto deja de cumplirse, la segunda
función responderá con **Falso** y, en consecuencia, la ejecución de la
primera función terminará. Ten en cuenta que **x** se ha definido fuera de la
función y es una variable global. Para saber más sobre las reglas de ámbito,
consulta el capítulo sobre Funciones.

## Interpolación de textos

La lista de *kJ/kcal* podría presentarse
mejor. Preferiblemente, la lista sería así:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Si conviertes la salida deseada en una plantilla, su notación
podría ser:

```
number1 kJ ➞ number2 kcal
```

Esto significa que **number1** representa el valor en kJ y **number2** el
valor en kcal. Así es como funciona la interpolación de textos en XOScript. No
hacen falta reglas gramaticales separadas para ello en XOScript. Basta con enviar
al texto la palabra que debe sustituirse, con el texto sustituto como
argumento:

```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

El resultado:

```
100 kj ➞ 23.9 kcal
```

Esta regla de sustitución funciona para cada mensaje no definido que recibe
un objeto **texto**. Cada mensaje que el objeto **texto** no reconoce
se interpretará de la siguiente manera: *sustituir el texto del mensaje
por el texto del argumento del mensaje.* Puedes adaptar el
programa de la siguiente manera:


@test601


Para evitar confusiones sobre qué mensaje puede usarse o no como
sustituto, lo mejor es introducir un marcador de plantilla como &lt; &gt;
para los segmentos de texto de la plantilla que
deben sustituirse.

## Valores de retorno

Para responder a un mensaje se usa la flecha
de retorno (*<-*). El siguiente ejemplo muestra cómo crear una tarea
para calcular un porcentaje:

@test602

Después de definir la tarea y asignarla a la variable **percentage**,
se envía el mensaje **aplicar:y:** con los argumentos **100** y **7**.

Esto ejecutará la tarea aplicada a **100** y **7**, es decir, el 7% de 100.
Mediante la flecha de retorno, la respuesta se devuelve desde la tarea
al programa principal.

## Extensión

Aunque este código es válido, tiene una desventaja,
porque hay que recordar el orden de los argumentos. Entonces, ¿por qué no
escribirlo así: *7 percent of: 100*? Eso parecería mucho más
*natural*. Para hacerlo posible, tenemos que adaptar el objeto padre de
**7**, que es el objeto **Número**, para que entienda el
mensaje **percent of:**. Esto se consigue enviando **al:hacer:** al
objeto Número, de esta manera:

@test603

Como el porcentaje es, en este caso, el propio número, nos referimos a yo,
la palabra clave *yo*. En resumen, el símbolo yo significa: *envía este
mensaje a mí mismo*.

# Objetos

{{messages}}

Además de ajustar y ampliar objetos existentes, también puedes crear
tú mismo objetos nuevos simplemente enviando el mensaje **crear**. Supongamos que
quieres crear un objeto factura que imponga una secuencia de
numeración; en ese caso, primero necesitarás un objeto factura.

Sabiendo que cada objeto deriva de otro objeto, que a su vez
tiene su origen en última instancia en el objeto raíz de todos los objetos, llamado Objeto,
hay que elegir en cuál de esos otros objetos se basará tu
nuevo objeto. Tu nuevo objeto hereda todas las propiedades del
objeto en el que se basa, es decir, de aquel al que se envió
inicialmente el mensaje **crear**.

En este ejemplo es preferible un objeto bastante neutro, sin demasiadas
propiedades heredadas. La elección es fácil, porque en ese
caso el nuevo objeto puede basarse en el propio objeto raíz, que es
**Objeto**. La notación del sistema de facturas previsto será entonces la
siguiente:

@test604

El número de factura actual se almacena en el objeto; por eso se
coloca delante la palabra clave **mi**. Esto se denomina *propiedad*;
más adelante se darán más detalles.

Algunas empresas prefieren incorporar el año en los números de
factura. En ese caso, puedes crear un nuevo objeto factura basado en un
objeto factura anterior, pero que ofrezca a su usuario la posibilidad de
indicar un año concreto:

@test605

No es necesario volver a escribir la implementación del mensaje **número**,
ya que se hereda del **objeto factura** escrito
anteriormente; en consecuencia, el código antiguo se puede reutilizar. XOScript carece de conceptos
como las clases y otros conceptos relacionados. Esto significa que los objetos solo
pueden heredar de otros objetos, lo que también se conoce como *herencia
prototípica*.

Volvamos ahora a las propiedades. Solo se puede acceder a las propiedades de un objeto
desde *dentro de la jerarquía del objeto*, de modo que estas propiedades
no pueden ser percibidas por otros objetos.

A diferencia de otros lenguajes de programación, todas las propiedades de los objetos son
visibles exclusivamente para el objeto que ha creado la propiedad y para los
objetos derivados. 

Una técnica muy utilizada es usar un objeto como una especie de *plano*,
como ocurre, por ejemplo, con las facturas vistas antes.
Otro buen ejemplo es **Point**. Supongamos que creas un
programa informático que hace cálculos usando puntos de un mapa. Puedes
desarrollar el objeto **Point**, que contiene las propiedades de una
coordenada x y una coordenada y, que se pondrán a disposición del
mundo exterior mediante mensajes:

@test606

El mensaje **=** compara los dos puntos usando el mensaje **y:**. La
primera comparación da como resultado un **Verdadero** o un **Falso**. Estos son objetos
booleanos. Cuando envías el mensaje **y:** a un objeto Verdadero y el
objeto argumento que va después de los dos puntos también es **Verdadero**, recibes
de nuevo como respuesta **Verdadero**. Cuando cualquiera de los dos es **Falso**,
recibes la respuesta **Falso**. Ten en cuenta que un punto no puede leer las coordenadas del
otro. Es necesario enviar un mensaje al otro punto para pedirle
estos datos: **x-coordinate** e **y-coordinate**. Al fin y al cabo, como ya
se ha explicado, las propiedades solo se pueden obtener desde dentro de
la propia familia del objeto. 

Ten en cuenta que aquí se usa el mensaje **=** para realizar la
comparación de puntos. También podría haberse usado otro mensaje, como
**is:** o **equal:**, pero reutilizar el carácter **=** parecía
apropiado en este caso.

## Herencia

Puedes reutilizar código escrito previamente para crear una jerarquía
de objetos. Por ejemplo:

```
>> Animal := Objeto crear.
>> Perro := Animal crear.
>> Caniche := Perro crear.
```

En este caso, **Dog** hereda todo el comportamiento y las propiedades
de **Animal** y, a su vez, el objeto **Animal** hereda todo el comportamiento de
**Objeto**, el objeto raíz de todos los objetos.


## Sobrescritura


En el siguiente ejemplo se crea un nuevo tipo de lista:
**Combination**, en la que se garantiza que cada elemento es único. Las
funciones de la lista se reutilizan mediante la herencia:

@test607

Observa cómo el segundo **red** queda excluido de la lista.

En ocasiones, puede ser necesario sobrescribir un comportamiento de un objeto.
Por ejemplo, cuando al sumar números hay que tener en cuenta las unidades
de medida. En el siguiente ejemplo se crea el objeto **Size**.
Este objeto devuelve un número que, durante la suma, tiene
en cuenta la unidad del número que se va a sumar. El objeto **Número**
comprueba si se trata de *pulgadas* o de *pies*. El código
podría parecerse al siguiente:

@test608

## Recursión

En el ejemplo anterior, se sobrescribe el **signo** más. Ten en cuenta
que, al final, la suma definitiva todavía tiene que realizarse, lo que, de hecho,
ocurre en la siguiente línea:

```
>> contestación := yo + (número x factor).
```

Ahora bien, ¿cómo entiende XOScript que este **signo** más se refiere a
la lógica original de la suma? Por ejemplo, otra interpretación
podría ser que XOScript envíe repetidamente el mismo mensaje al mismo
objeto, lo que a su vez provocaría un **bucle infinito**. Evidentemente,
esa no es la intención. En cuanto envías a un objeto un mensaje
que ejecutaría exactamente el mismo código, XOScript se dará cuenta,
en este caso, de que se refiere al mensaje subyacente sobrescrito. Así, tu
programa queda protegido automáticamente contra esta forma de bucles
infinitos. Sin embargo, cuando tu objetivo sea realmente ejecutar la misma función desde la
función actual, será necesario enviar primero el mensaje
**recursivo**. En ese caso, el resultado será un bucle
infinito. No obstante, las tareas recursivas tienen aplicaciones útiles; por
ejemplo, supongamos que quieres calcular el factorial de un número
dado. En ese caso, basta con añadir el mensaje **factorial** a
Número:

@test609

Esto requiere recursión. De hecho, la tarea asociada al
mensaje **factorial** debe ejecutarse de nuevo dentro de esa función.
Por tanto, es necesario invocar la función factorial desde dentro de la
propia función factorial. Por regla general, XOScript impedirá esta rutina,
por el riesgo de acabar en un bucle infinito. Por este motivo,
es fundamental anteponer al mensaje la palabra **recursivo**. Esto
se hace para que XOScript sepa que tu intención es
ejecutar la misma tarea y que no has cometido un error.

## Objetos similares a clases

Aunque xoscript no ofrece clases, imitar un comportamiento similar al de
las clases es trivial. Basta con sobrescribir el mensaje crear.

```
>> Animal := Objeto crear.
Animal al: ['crear'] hacer: {
	<- yo crear iniciar.
}.

Animal al: ['iniciar'] hacer: {
	mi sonido := ['?'].
	mi patas  := 4.
}.
```

En el fragmento de código anterior creamos un objeto llamado Animal.
Este objeto sirve como *plano* para todo tipo de animales,
como perros y gatos. El objeto padre Animal se escribe
con A mayúscula para indicar que es un objeto similar a una clase.
A continuación sobrescribimos el mensaje crear escribiendo nuestro propio método crear.
En este caso, envía el mensaje crear a yo, seguido del mensaje
iniciar. Como xoscript bloquea la recursión por defecto, esto no provocará
un bucle infinito. En su lugar, enviará el mensaje crear al objeto
padre (Objeto), lo que da como resultado una nueva instancia de Animal. Así, creamos
un nuevo objeto basado en el mismo objeto para el que creamos nuestro método crear.
Esto es perfectamente válido. Además enviamos el mensaje iniciar, que garantiza
que el objeto Animal tenga valores predeterminados para sus propiedades. Por defecto,
un animal tiene 4 patas y su sonido es desconocido (de ahí el signo de interrogación).
Para crear una nueva instancia de nuestro Animal, bastaría con escribir:

```
>> a := Animal crear.
```

Ahora obtenemos una nueva instancia de Animal con 4 patas, sonido desconocido y
un método iniciar. Igual que en otros lenguajes de POO, también podemos
extender nuestro Animal:

```
>> Perro := Animal crear.
Perro al: ['iniciar'] hacer: {
	yo iniciar.
	mi sonido := ['ladra'].
}.
```

Podemos comprobarlo fácilmente añadiendo un método texto:

```
Animal al: ['texto'] hacer: {
	<- mi patas texto + mi sonido.
}.
```

Juntémoslo todo:

@test13


Crear un objeto que se encuentre en un estado inicial determinado plantea un
problema frecuente. Supongamos que hay que crear un objeto **Rectangle**
para calcular el perímetro y el área. Una posible notación sería:


```
>> Rectángulo := Objeto crear.

Rectángulo al: ['área'] hacer: {
	<- mi longitud * mi anchura.
}.
```

Evidentemente, establecer una longitud y una anchura es un requisito previo. Para ello
se pueden añadir los mensajes **longitud:** y **width:**:


```
Rectángulo al: ['length:'] hacer: { :longitud
	mi longitud := longitud.
}.

Rectángulo al: ['width:'] hacer: { :anchura
	mi anchura := anchura.
}.

```

Este rectángulo se puede utilizar entonces de la siguiente manera:


```
>> rectángulo := Rectángulo crear length: 2, width: 3.
Salida escribir: rectángulo área.
```

Sin embargo, si se olvidan los valores iniciales de longitud y anchura,
se producirá un mensaje de error:

```
>> rectángulo := Rectángulo crear.
Salida escribir: rectángulo área.
```

producirá el siguiente error:

```
Clave no encontrada:longitud
```

Para evitarlo, es preferible que un rectángulo tenga
siempre una longitud y una anchura iniciales, por ejemplo 0. Así, en este
caso, es necesario **sobrescribir** el mensaje **crear**.

@test610

Si sobrescribimos el mensaje crear, básicamente estamos imitando una **clase**.

El mundo de XOScript está lleno de una gran variedad de objetos, que están
disponibles para tu programa desde el principio. En los próximos capítulos
se analizarán todos estos objetos fundamentales.

## Instantáneas

Puedes guardar un objeto (junto con su estado actual) en disco con:

```
miobjeto save-as: ['saved.bin'].
```

Para volver a cargar el objeto desde el disco:

```
>> miobjeto := Objeto load-from: ['saved.bin'].
```

Las instantáneas se pueden usar para guardar un estado determinado o para mejorar el rendimiento.
Cargar una instantánea evita el análisis léxico, el análisis sintáctico y la configuración de la aplicación.
Además, en el futuro podrían introducirse ventajas de rendimiento adicionales
con las instantáneas, como la optimización de ciertos patrones o la detección y
optimización de rutas críticas.

{{warning}}
Las instantáneas son una funcionalidad experimental; no las uses en producción.
Para activar las funcionalidades experimentales, compila con -D EXPERIMENTS.
{{/warning}}


@test712

# Objeto Nulo

{{messages}}

El objeto Nulo
representa el vacío o, mejor dicho, la ausencia de información. En
ocasiones recibirás este objeto como respuesta a un mensaje, cuando
el resultado sea **nada**. La pregunta más esencial
que puedes hacerle al objeto **Nulo** es: **¿nulo?**. La
respuesta siempre será **Verdadero**.

```
Salida escribir: Nulo ¿nulo?.
```

resultado:

```
Verdadero
```

Cualquier objeto distinto de **Nulo** responderá con **Falso**. El
fragmento de código anterior puede parecer algo filosófico, pero el objeto **Nulo**
tiene sin duda aplicaciones sumamente prácticas. Por ejemplo,
recibirás el objeto Nulo como respuesta si pides un
elemento de una lista que no existe. También puedes usar el objeto Nulo
si quieres declarar una variable pero todavía no quieres especificar un
valor. En su lugar, simplemente **asignas** el valor especial **Nulo**. En
XOScript no se permite declarar una variable sin valor, como en:


```
>> valor.
```

En su lugar, debes escribir lo siguiente:

```
>> valor := Nulo.
```

@api_None_base

# Booleanos

{{messages}}

A diferencia de la mayoría de los lenguajes de programación populares en el momento de escribir esto,
XOScript ofrece un único objeto Verdadero y un único objeto Falso.
Para aclararlo: cada vez que escribes **Verdadero**, no significa que
se haya creado un objeto nuevo. En su lugar, siempre usas una referencia. Esto
significa que cuando escribes lo siguiente:

\>\> x := Verdadero.

**x** hace referencia al objeto **Verdadero**. El código condicional y los bucles también
comprueban esta referencia. En XOScript, el significado de **Verdadero** y **Falso**
no es fijo. De hecho, un programa XOScript queda bastante trastocado por una
sentencia como esta:

Verdadero := Falso.

El resultado de este tipo de acciones no está definido; sin embargo, sigue siendo una
acción válida y, por tanto, formalmente permitida. Además, existe un objeto
Booleano, que es el objeto raíz tanto de **Verdadero** como de **Falso**, ya que ambos
son derivados de ese objeto raíz. Sin embargo, el propio objeto Booleano
no tiene ninguna aplicación práctica.

## Trampas

Ten cuidado al usar **y:** y **o:**

```
Salida escribir: (Falso or: Verdadero or: Verdadero), detener.
Salida escribir: (Falso o: Verdadero, o: Verdadero), detener.
```

Da como resultado

```
Falso
Verdadero
```
porque el mensaje **o:** solo acepta 1 argumento. La primera línea
envía **o:o:** a Falso, que no existe, por lo que el objeto ignora
el mensaje y se devuelve a sí mismo (Falso). En cambio, la segunda línea
envía **o:** seguido de otro **o:** (usando un símbolo de encadenamiento, es decir, una coma: ,).


@api_Boolean_base

# Números

{{messages}}

Cada vez que escribes un número, por ejemplo 9, -10 o 3,12, entre
bastidores XOScript convierte esos números en un objeto **Número**. Puedes
enviar mensajes a este objeto Número, o bien asignar el número
a una variable y enviarle mensajes después:

```
10 ¿par?

>> billeteDeDiez := 10.
billeteDeDiez ¿par?

```

Ambas notaciones son válidas. El objeto Número responde a los siguientes
mensajes...

La mayoría de estos mensajes se explican por sí mismos y te permiten realizar
operaciones matemáticas o comparaciones.

{{note}}
Ten en cuenta que puedes usar ≤ ≥ ≠ × y ÷ en lugar de sus equivalentes ASCII.
Es una cuestión de preferencia.
{{/note}}

La diferencia entre los mensajes matemáticos binarios (+) y
sus variantes de palabra clave (añadir:) es que los primeros devuelven
un número nuevo, que es el resultado de la operación, mientras que con los
segundos se modifica el propio objeto. Esto se ilustra en el
siguiente ejemplo:

@test597

En el ejemplo anterior, b = 4 y a = 3. Con **añadir: 2**, el valor
de a aumenta en 2, mientras que **+ 3** crea un número nuevo
igual a a + 3. Lo mismo se aplica a otras operaciones matemáticas, p. ej.,
las multiplicaciones. Al usar el símbolo de multiplicación, recibirás un
objeto nuevo como respuesta. Si usas el mensaje **multiplicar:**,
multiplicarás el propio número.

Con el mensaje **entre:y:**, por ejemplo en **Número
entre: X y: Y**, obtendrás un número entre X e Y. De esta
manera se puede generar cualquier número aleatorio:

```
>> a := Número entre: 1 y: 10.
Salida escribir: a, detener.
```

A partir de la versión 1.4, el generador de números aleatorios integrado en xoscript es,
hasta donde sabemos, criptográficamente seguro.

Puedes asociar un **calificador** a un número, por ejemplo, **6
manzanas**. Cada mensaje que un número no reconozca
se considerará un calificador. Puedes obtener el calificador de
un número mediante el mensaje calificador:

Un calificador es básicamente un objeto Texto que se almacena junto con el objeto
Número. El calificador también se imprime después del número en una
instrucción **escribir:**. Los calificadores podrían usarse, por ejemplo, para sumar importes
en monedas mixtas. Al sumar los importes, puedes consultar
los calificadores. El siguiente programa de ejemplo ilustra este
principio mediante una calculadora de monedas históricas (¡ya que el tipo de
cambio se mantiene razonablemente estable!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Textos

{{messages}}

Cada vez que se coloca un texto entre **corchetes y comillas** ['...'],
XOScript crea para ti un nuevo objeto texto. No obstante, asegúrate
de usar las comillas correctas. La comilla del
principio del texto es distinta de la del final (esto te permite
usar la comilla simple sin necesidad de escaparla).

## UTF8

Los textos en xoscript suelen contener texto codificado en utf8. Aunque
técnicamente es posible tener contenido binario o no utf8 en
un texto, se recomienda usar blobs para ello. Los blobs los
proporciona el plugin de servidor (consulta el capítulo ffi).
En general, los blobs/ffi se proporcionan
por plugin/plataforma, ya que están ligados a la plataforma
y a la arquitectura (ffi/blobs). El núcleo del lenguaje de scripting intenta
mantenerse lo más independiente posible de la plataforma.

## Conversión de tipos

Puedes crear una copia de cualquier objeto
con un tipo diferente usando los siguientes mensajes:

Mensaje | Resultado
------- | ------
número  | Convierte en un número
texto   | Convierte en un texto
booleano | Convierte en un booleano
  
Se **aplican** las siguientes reglas:

mensaje  | Nulo      | Booleano           | Número                | Texto     | Otro              
-------- | --------- | --------           | --------              | --------  | --------
booleano | Falso     | n/d                | 0→Falso resto→Verdadero | Verdadero | Casi siempre Verdadero
número   | 0         | Falso→0 Verdadero→1 | n/d                  | ['n']→n | Casi siempre 1
texto    | ['Nulo']  | ['Falso']/['Verdadero'] | ['n']            | n/d       | Depende

## Copia

En XOScript, los valores siempre se pasan **por referencia**. En otros lenguajes
depende del tipo de valor; en XOScript solo hay una forma:
por referencia. XOScript nunca hace una copia de un valor. Para copiar un objeto,
debes enviar el mensaje **copiar**. 

@test611

Aquí quizá esperabas que la salida fuera Dolly, en lugar
de Donny. Sin embargo, no es así, ya que ambos nombres hacen referencia al mismo
objeto. Al trabajar con un bucle ocurre algo parecido:

@test612

De hecho, XOScript usa **siempre** referencias, de modo que en **:quantity**
el bucle mostrado arriba también indica la referencia al elemento
de la lista.

Para copiar un objeto, debes indicar esta acción
de forma **explícita**:

@test613

Al enviar el mensaje unario **copiar** a un texto, el objeto
devuelve una copia de ese mismo objeto texto. Es posible copiar de la misma manera
objetos Número, objetos booleanos, listas y diccionarios.

También puedes definir tu propia implementación de copiar; esto es incluso una
necesidad si creas tus propios objetos. La implementación
predeterminada de copiar para una lista hace una copia superficial: crea una
lista nueva con los mismos elementos.

@test614

En este caso, 4 se añade solo a la copia.
Sin embargo, como la copia es superficial, los objetos de ambas listas
son los mismos.

@test615

Así que, si añadimos 2 a cada nombre de la copia, la lista
original también se ve afectada.

Para remediarlo, necesitamos hacer una **copia profunda**. Una acción de copia
de este tipo para una lista podría componerse así:

@test616

Fíjate también en el mensaje recursivo; es necesario enviar este mensaje
antes del mensaje copiar.

Es fundamental tener presente que, aunque la copia de un objeto
a menudo tiene el mismo aspecto que el original, en realidad
nunca es el mismo. El objeto raíz define un mensaje **equal:**,
que se puede usar para comparar la identidad de los objetos. Observa el
siguiente ejemplo:

@test617

## Conversión implícita

XOScript usa la **conversión implícita** para convertir objetos. Para imprimir una
lista en pantalla, XOScript enviará, por ejemplo, el mensaje
*texto* internamente a la lista. Esto puede resultar muy útil
si quieres imprimir una lista como lista separada por comas. El
mensaje *texto* se puede sobrescribir: 

@test620

@api_String_base
@api_Format_base


## Textos de servidor

Las siguientes funcionalidades de Texto las añade el
plugin Servidor.

@api_String_server

# Funciones

{{messages}}

Puedes agrupar código entre { y }; entonces se convierte en una función.
En xoscript también usamos a veces el término tarea o simplemente
bloque de código.

Puedes ejecutar una función enviándole el mensaje *empezar*.


```
{ Salida escribir: 123, detener. } empezar.
```

Si tu función acepta argumentos, usa **aplicar:**.

```
{ :a Salida escribir: a, detener. } aplicar: a.
```

Consulta también los ejemplos de abajo.
Debido a la arquitectura simplista, una función solo puede tener
un punto de retorno. Para evitar sobrecarga o un anidamiento excesivo de
condiciones, puedes usar un procedimiento (que equivale a usar el
signo de multiplicación con el argumento 1):

```
{
  (a = 1) verdadero: { x := 1. }, salir.
  (a = 2) verdadero: { x := 2. }, salir.
} proceder.
```

De esta manera, (a = 2) no se evaluará si a = 1.
Además, así no necesitas mensajes verdadero: anidados.
Siempre que te encuentres anidando condiciones, piensa
en el mensaje proceder. Puede hacer que tu código
sea más fácil de leer.


Esta es una trampa importante:

```
{
	Falso falso: {
		Salida escribir: ['Termina el bucle.'].
	}, salir.
	
	Salida escribir: ['No me muestres.'].

} proceder.

```

En este caso, se mostrará el texto 'Dont show me',
porque **salir** se envía a Falso. Si quieres ejecutar
un salir, debe enviarse como mensaje a **Verdadero**.
 

```
{
	Falso no verdadero: {
		Salida escribir: ['Termina el bucle.'].
	}, salir.
	
	Salida escribir: ['No me muestres.'].

} proceder.

```

Funcionará como se espera.

## Excepciones

Las excepciones se pueden gestionar así:

```
{ Tarea 1 } capturar: { Tarea 2 }, empezar.
```

También puedes provocar intencionadamente un error en tu programa y,
al hacerlo, activar el bloque de gestión. Para ello se envía el
mensaje **error:** a la tarea actual, como se muestra en la siguiente
ilustración:

```
{
la-tarea-actual error: ['¡Ups!'].
} capturar: { :equivocación
Salida escribir: equivocación.
}, empezar.
```

## Inyección de valores

XOScript ofrece a las tareas la opción de inyectar valores. Observa
la siguiente tarea:

```
>> envío := {
	Boletín destinatario: mi recipient.
}.
envío valor: ['recipient']
asignar: ['info@recipient.org'].
envío empezar.
```


Esta ilustración presenta una tarea imaginaria que envía un boletín
a una dirección de correo electrónico o **recipient**. Este destinatario se puede inyectar
en la tarea, desde fuera y antes de que se inicie la tarea, enviando el
mensaje **valor:asignar:** a la tarea. De este modo, el valor de
**recipient** queda preestablecido en la tarea. Este valor también se puede modificar
y la tarea puede volver a ejecutarse después. Es un método útil al usar
objetos tarea.

## Funciones vacías

No se permiten tareas vacías. En teoría, una tarea vacía tendría este
aspecto: **{}**; sin embargo, XOScript lo considera un error del lenguaje. Si
quieres declarar una tarea vacía, puedes usar el objeto Nulo:

```
>> tarea := Nulo.
```

Aunque no es una tarea de verdad, sino un objeto Nulo, aún se le puede
enviar un mensaje empezar:

```
>> contestación := tarea empezar.
```

De hecho, esto es lo mismo que:

```
>> contestación := Nulo empezar.
```

Como el objeto **Nulo** no reconoce el mensaje **empezar**,
se devolverá a sí mismo como respuesta, de modo que la respuesta vuelve a ser **Nulo**.
Así pues, no hace falta tener una tarea vacía. Gracias al elegante
diseño del lenguaje de programación XOScript, puedes usar simplemente el objeto
Nulo para ello.

## Ámbito dinámico

Cuando una Función necesita una variable pero no la encuentra,
revisa las variables de la Función que la **llamó**
y sigue revisando hacia arriba por la cadena de Funciones.
Este proceso de búsqueda continúa hasta que se encuentra la variable.
Si aun así no se encuentra la variable, aparecerá un mensaje de error. Este método de búsqueda de
una variable se denomina **ámbito dinámico**.

Para ilustrar este principio:

@test618

@api_Code_base

# Objeto raíz

{{messages}}

El objeto llamado **Objeto** es el objeto raíz de todos los objetos de
XOScript y proporciona las funcionalidades básicas del lenguaje. 

El mensaje que se envía con más frecuencia
es **al:hacer:**, que amplía las funcionalidades de un objeto. Este
mensaje lo recibe el objeto raíz, que a continuación vincula la
tarea especificada al mensaje y, de este modo, amplía el objeto
derivado.

## Métodos comodín

Normalmente, si envías un mensaje que no corresponde a
ningún método del objeto, se ignora. Sin embargo, puedes definir
los llamados **métodos mágicos** o métodos **comodín**, que se
invocarán si el objeto no entiende el mensaje.

Hay 4 métodos comodín disponibles. Cada mensaje corresponde a
un número concreto de argumentos.

Mensaje comodín          | Número de argumentos
------------------------ | -------------------
responder:               | 0
responder:y:             | 1
responder:y:y:           | 2
responder:y:y:y:         | 3


@test619

## Mensajes programáticos

En lugar de enviar un mensaje directamente a un objeto, también se puede
enviar mediante una variable. Para ello se usa el mensaje
**mensaje:argumentos:**. 

@test396

@api_Object_base

# Listas

{{messages}}

XOScript conoce dos tipos de colecciones: *listas* y *diccionarios*.
Las **listas** son enumeraciones de objetos en un *orden fijo*. Los diccionarios no
tienen orden; en su lugar, se parecen a una leyenda formada por una clave (o término) y su
valor correspondiente. Las listas son comparables a los arrays (PHP, Java, C)
y a las listas (Python). Los diccionarios son comparables a los arrays asociativos (PHP) o
a los diccionarios (Python) de otros lenguajes de programación. Para crear
una nueva Lista, escribe:

```
>> fibonacci := Lista crear.
```

Esta lista vacía se puede llenar con **adjuntar:** :

```
fibonacci adjuntar: 0.
fibonacci adjuntar: 1.
fibonacci adjuntar: 1.
fibonacci adjuntar: 2.
fibonacci adjuntar: 3.
fibonacci adjuntar: 5.
fibonacci adjuntar: 8.
fibonacci adjuntar: 13.
```

Si escribimos la lista en pantalla:

```
Salida escribir: fibonacci, detener.
```

Veremos:

```
Lista ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

En lugar de adjuntar, también puedes usar ; para añadir elementos a una lista:


```
>> fibonacci := Lista crear ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Los puntos y coma (;) son todos mensajes binarios que colocan un
valor en la lista.

## Encadenamiento

Supongamos que tienes una lista como:

```
>> x := Lista crear ; 1 ; 2 ; 3.
```

Si quieres eliminar el primer y el último elemento, tu
mensaje sería:

```
x cortar-primero cortar-último.
```

Por desgracia, la notación anterior no funcionará correctamente. El
mensaje **cortar-primero** devuelve el primer elemento de la lista, que,
a su vez, se convertirá en el receptor del mensaje **cortar-último**. Así, el
mensaje **cortar-último** no se envía a **x**, sino a 2. Una
posible solución a este problema sería escribir dos frases
separadas, como: 

```
x cortar-primero.
x cortar-último.
```

Sin embargo, esto resulta poco práctico, sobre todo cuando hay que
eliminar más de dos elementos. Por ello, XOScript ofrece una
estructura de mensajes alternativa para este tipo de situaciones. En las
estructuras de mensajes **alternativas**, las respuestas de los objetos se ignoran
y obtienes como respuesta, una y otra vez, el objeto receptor.
Una estructura de mensajes **alternativa** se inicia enviando el
mensaje **hacer** a un objeto, y la estructura de mensajes **alternativa**
se puede terminar enviando el mensaje **hecho**. En el
ejemplo ilustrado, esto podría aplicarse de la siguiente manera:

```
>> x := Lista crear ; 1 ; 2 ; 3.
x hacer cortar-primero cortar-último hecho.
```

@api_List_collections

# Diccionarios

{{messages}}

**Tanto Lista como Diccionario son colecciones. Sin embargo, a diferencia de una
lista, un diccionario **no tiene** orden. Otra diferencia entre ambos
es que un diccionario está formado por pares de objetos. Un objeto actúa como entrada (o
palabra clave) para buscar el otro objeto. Un buen ejemplo de
lista es una lista de precios, como:


```
>> menú := Diccionario crear
	poner: ['£5'] en: ['tarta de manzana'],
	poner: ['£6'] en: ['tarta de zanahoria'],
	poner: ['£3'] en: ['fudge'].
```

Al igual que en una lista, el mensaje poner:en:
se usa para añadir un objeto a una lista. La diferencia es que, a diferencia de
una lista, se vinculan dos objetos. El primer objeto es, igual que
en una lista, el objeto que vas a almacenar en una lista. El segundo
objeto no es su posición dentro de la colección, sino la **entrada**
que permite recuperar el objeto anterior más adelante. En
resumen, un diccionario funciona un poco como un diccionario de palabras; es decir, mediante la palabra clave
se puede encontrar el significado. Por ejemplo, para obtener de la
lista mencionada el precio de un fudge:

```
>> price := menú en: ['fudge'].
```

También puedes usar la notación abreviada:

```
>> price := menú ? ['fudge'].
```

Si las entradas que utilizas para almacenar objetos no tienen espacios
(y no coinciden con otros mensajes predefinidos),
también se puede usar la siguiente notación:

```
>> menú := Diccionario crear
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Sin duda, la notación anterior se lee de forma algo más natural.
Para consultar el precio de un
fudge, se puede usar la siguiente notación simplificada:

```
>> price := menú fudge.
```

@api_Dict_collections

# Archivo

{{messages}}

El objeto **Archivo** proporciona acceso básico al sistema de archivos.
Puedes usar este objeto para leer archivos completos en una variable de
una sola vez, o para escribir variables en archivos de una sola vez. También
se admite la lectura línea a línea. Estas son las operaciones de E/S de archivos más habituales
en un lenguaje de scripting. Las operaciones de archivo avanzadas requieren
el uso de FFI mediante el plugin de servidor o un plugin de E/S independiente.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Fecha/Hora

{{messages}}

Para una representación estructurada de la hora y la fecha, XOScript usa el
objeto **Momento**. Si se imprime en pantalla un nuevo objeto Momento, se
muestran la fecha y la hora actuales:

```
Salida escribir: Momento crear, detener.
```

Podría dar como resultado algo como:

```
2020-10-10 12:16:39
```

También es fácil leer los componentes individuales de la hora. Así, por
ejemplo, si solo hace falta conocer el año actual, se puede enviar el mensaje
**año** al momento y, a su vez, la respuesta será un
objeto Número que contiene únicamente el año:

```
>> m := Momento crear.
Salida escribir: m año, detener.
```

@api_Moment_system

# Programa/StdOut

{{messages}}

El objeto Programa representa la aplicación que se está ejecutando. Este objeto
ofrece funcionalidades para ejecutar comandos del sistema, incluir subprogramas,
leer argumentos y más. Todas las funciones relacionadas con el sistema.

## StdOut

Salida es el objeto de salida estándar. Básicamente tiene dos métodos:
**escribir:** y **detener**. El mensaje escribir: se usa para enviar un texto
a stdout; el mensaje detener imprime un carácter de nueva línea.
En lugar de **detener** también puedes usar \\n.

Ejemplo:

```
Salida escribir: ['Hello World'], detener.
```

resultado:

```
Hello World
```

## Módulos/Plugins

El mundo de XOScript se puede ampliar con nuevos objetos del sistema
instalando módulos. Se puede añadir un nuevo objeto del sistema al mundo de
XOScript colocando el archivo del módulo (normalmente un archivo con el sufijo .so)
en la carpeta mods. 

Cuando envías un mensaje al objeto que pone a disposición el
módulo plugin, XOScript lo carga automáticamente.

También puedes escribir plugins tú mismo. Los plugins se escriben en el
lenguaje de programación C. Puedes encontrar un plugin de ejemplo en el paquete
de código fuente, en src/plugins/example.


## Reflexión

Hay varias formas de explorar
el sistema durante la ejecución del programa. XOScript dispone de un par de métodos para
detectar qué objetos están presentes y a qué mensajes responden
esos objetos. En primer lugar, a cada objeto se le puede preguntar de qué **tipo** es;
sin embargo, los tipos en XOScript son maleables y, por tanto, poco fiables.

También es posible preguntar al objeto Programa si un
objeto determinado ya está presente en el programa:

```
Programa Herramienta verdadero: { ... }.
```

En el caso de un nombre de objeto
que consta de un único símbolo, es mejor aplicar la
siguiente notación para evitar confusiones:

```
Programa encontrar: ['X'], verdadero: { ... }.
```

Además de preguntar por objetos, también es posible preguntar al
objeto Programa por mensajes. Por ejemplo, se le puede preguntar si el
objeto **Número** conoce el mensaje **entre:y:**, de la manera
que se ilustra a continuación:

```
Programa Number: ['between:and:'], detener.
```

@api_Program_system

# Servidor

{{messages}}

El plugin Servidor de xoscript ofrece funcionalidades para
crear aplicaciones del lado del servidor. Para cargar el plugin
de servidor, usa:

```
Server iniciar.
```

Para tu comodidad, también se recomienda cargar
los archivos webtools.xo y template.xo.

```
Programa utilizar: ['webtools.xo'].
Programa utilizar: ['template.xo'].

```

## Configuración del servidor

Puedes establecer los siguientes ajustes del servidor:

```
	# se dan valores predeterminados,
	# así que si no configura nada, se usan
	# estos valores...

	Programa 
	establecer: ['campos-máximos']
	valor: 40.

	Programa 
	establecer: ['contenido-máximo']
	valor: 2000000. # 2MB

	Programa 
	establecer: ['max-time']
	valor: 5000. # 5sec

```

## Hola mundo

Este es un programa web muy sencillo que puedes usar con un
servidor CGI estándar como Apache2, NGINX, OpenHTTPD o cualquier otro
servidor conocido.

```
#!/bin/xo

Server iniciar.
Programa utilizar: ['webtools.xo'].

>> documento-web := Documento-Web crear.

documento-web salida: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Si no quieres usar el objeto Documento-Web, no pasa nada, pero
entonces tienes que escribir tú mismo las cabeceras HTTP:

```
#!/bin/xo
Salida escribir: ['Content-type: text/html; charset=utf-8 \n\n'], detener.
Salida escribir: ['¡hola mundo!'], detener.
``` 

## Petición

El objeto Petición-HTTP se puede usar para obtener datos GET/POST/COOKIE y
UPLOAD:

```
>> solicitud  := Petición-HTTP crear.
>> search   := solicitud obtener: ['search']. # ?búsqueda=libros
>> password := solicitud enviar: ['password']. # del formulario
>> seleccionados := solicitud obtener-lista: ['sel[]']. #?sel[]=1&sel[]=2
>> seleccionados := solicitud enviar-lista: ['sel[]'].
>> cookie   := solicitud cookie: ['session-id'].
>> subida   := solicitud subir: ['file'].
>> rutatemp := subida ? 1.
>> nombrearchivo := subida ? 0.
```

## Maxpost/length

El número máximo predeterminado de campos POST es 40 y la longitud máxima
predeterminada del contenido es de 2MB. Para configurarlo de otra forma en cada script:

```
Programa establecer: ['contenido-máximo'] valor: 1. 
Programa establecer: ['campos-máximos'] valor: 1. 
```

{{note}}
Si la longitud del contenido supera el máximo, el
proceso se termina, porque ya no podemos estar seguros
de que la carga útil sea segura.
{{/note}}

El límite maxtime determina el tiempo máximo en ms
para leer stdin/los datos POST.

```
Programa establecer: ['max-time'] valor: 5000. # 5sec
```

Esto solo se aplica a la lectura de E/S del POST, lo que evita
ataques del tipo slowloris. Si de verdad quieres limitar el
tiempo de ejecución de cualquier operación, usa Programa tiempo-límite:.

## Base de datos

El objeto Database se puede usar para hacer consultas a MariaDB/MySQL.
Para conectarte a una base de datos:

```
>> bd := Maria-DB crear host: ['localhost'],
	usuario: ['xo'],
	contraseña: ['pass123'],
	nombre-base-datos: ['xobase'],
	conectar.

```

Para insertar un registro, usa:

```
>> consulta := bd consultar: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parámetros: ( Lista crear ; ['abc'] ; 12.35 ; 6 ). # consultas parametrizadas

{  consulta ejecutar. bd confirmar. }
capturar: { :e bd revertir.  }, empezar.
```

Ten en cuenta que xoscript trabaja *solo* con transacciones y nunca hace autocommit.
Si no se puede desactivar el autocommit, obtendrás un error de conexión.
Usa siempre la vinculación de parámetros en las consultas; nunca añadas la entrada del usuario directamente
al SQL.

Obtén el id insertado así:

```
Salida escribir: ['INSERTADO: '] + consulta id-insertado, detener. # id insertado
```

Para obtener registros:

```
>> consulta :=
bd
	consultar: ['SELECT * FROM book order by id desc limit 2'], 
	extraer: { :fila 
		Salida escribir: fila id + [' '] + fila description + [': '] + fila price, detener.
	}. # obtención de filas

```

## Sesiones

Para la persistencia, puedes almacenar y obtener datos de un objeto de sesión.
Primero crea un nuevo **Documento-Web**. El objeto Documento-Web reúne
la petición, las cabeceras, el HTML y la sesión. Esto se debe a que, cuando
visitas un sitio web con tu navegador, solo ves el HTML. Pero el
Documento-Web completo también consta de **cabeceras**. Por ejemplo,
la mayoría de las respuestas HTTP incluyen una cabecera como Content-type:text/html para
indicar al navegador que los datos que siguen deben representarse como HTML
(y no, por ejemplo, descargarse como un archivo). Las sesiones son una forma de
almacenar datos del usuario entre peticiones. Para hacer un seguimiento de estos datos, necesitamos
establecer una cookie; esta cookie también se establece mediante una cabecera. Por eso
todo se reúne en el Documento-Web (porque es el documento completo,
que contiene tanto las cabeceras como el HTML u otros datos).


```
# Primero creamos una nueva instancia de Documento-Web
>> web := Documento-Web crear.

# Ahora iniciamos una sesión; esto generará una cabecera para una cookie y
# creará un archivo para guardar sus datos, asociado a esa cookie
>> sesión := web empezar-sesión.

# Ahora podemos tratar la sesión como un Diccionario
sesión userid: 123.
```

Para destruir la sesión (al cerrar sesión):

```
web borrar-sesión.
```

## Cabeceras

El Documento-Web también te permite establecer otras cabeceras conocidas.
Por ejemplo, si quieres redirigir al usuario a otra URL:

```
web ir-a: ['/other.html'].
```

Por debajo, este comando también genera la cabecera HTTP que se envía
junto con tus otros datos o tu HTML para indicar al navegador que navegue
a la dirección de destino especificada.

Para añadir una cabecera personalizada:

```
web cabezera: ( 
	Cabezera-HTTP crear
	clave: ['Content-Length']
	valor: 400
).
```

Para mostrar una página 404:

```
web no-encontrado: ['Uups..'].
```


## Plantillas

El sistema de plantillas predeterminado es muy sencillo. No tienes que aprender
una nueva sintaxis de plantillas. Además, el motor de plantillas garantiza una separación real
entre la presentación y la lógica de negocio.

Para crear una plantilla a partir de un archivo:

```
>> tpl := web plantilla: ['templates/ux.tpl'].
```

El sistema de plantillas usa marcadores. 
Hay tres tipos de marcadores: marcadores de corte, marcadores de pegado y
marcadores de ranura. La idea básica es muy sencilla: recortas
las zonas identificadas por marcadores de corte y puedes pegarlas en
las zonas identificadas por marcadores de pegado. Puedes inyectar textos en
los marcadores de ranura.

Así, por ejemplo, dada la siguiente plantilla, vamos a meter la
gema en el joyero y añadir una etiqueta de precio.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Puedes hacerlo de la siguiente manera:

```
>> gem := tpl cortar: ['gem'], copiar.
gem price: 99.
tpl pegar: gem en: ['jewels'].
web salida: tpl depurar.
```

La última línea simplemente envía la plantilla como texto al cliente,
junto con las cabeceras HTTP necesarias.

Resultado:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

Para servir de forma segura archivos subidos por los usuarios, puedes recurrir a passthru:

```
>> subido := ['smile.gif'].
Server acceso-directo: subido prefijo: ['/uploads/images/'].
Programa finalizar.
```

Esto servirá el contenido subido por el usuario con el tipo mime
adecuado. Solo se admiten tipos mime de una lista blanca:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF y SVG.
Los archivos SVG, ZIP y GZIP se envían como descarga, porque un SVG
puede contener scripts que, de lo contrario, se ejecutarían en tu dominio.
Este método evita ataques TOCTOU, recorridos de rutas (path traversal),
la ejecución de código malicioso (inyección), ataques mediante enlaces simbólicos,
ataques DDoS (límite de archivo = 50MB), ataques de sniffing y
otros diversos problemas de seguridad.


## JSON

Para codificar un objeto como JSON:

```
>> json := ( JSON jsonificar: ( 
	Diccionario crear poner: ( 
		Lista crear ; 1 ; 2 ; 3
	) en: ['abc']
)).
```

Para decodificar JSON en un objeto xoscript:

```
>> dicc := ((JSON objeto: json) abc ? 1).
```

Un JSON con más de 500 niveles de anidamiento se rechaza por no válido.

Para enviar directamente un Diccionario como json con las cabeceras correctas:

```
web json: dicc.
```


## Expresiones regulares

Puedes usar expresiones regulares creando un patrón.
Por ejemplo, para encontrar los hrefs y targets de los hipervínculos:

```
Patrón crear: ['href="([^"]+)" target="([^"]+)"'].
```

Ahora aplica el patrón al texto de entrada de esta manera:

```
patrón coincidir: asunto ejecutar: { :m :x .... }
```

Ejemplo completo:

```
>> asunto := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> patrón := Patrón crear: ['href="([^"]+)" target="([^"]+)"'].
>> res  := patrón coincidir: asunto ejecutar: { :m :x
	Salida escribir: m, detener.
	Salida escribir: x, detener.
	<- ['XXX'].
}.
Salida escribir: res, detener.
```

## Redes

Usa el objeto Red para realizar una petición web.
El objeto Red siempre envía una petición POST, salvo que envíes Nulo como
datos; entonces envía una petición GET.


```
Red 
enviar: Nulo 
a: ['https://redbeanphp.com'].
```

## Cifrado

El plugin de servidor incluye cifrado basado en XChaCha20 y Argon2.

Ejemplo:

```
>> cifrado := Contenedor-seguro cifrar: ['hello'] clave: ['world'].
>> descifrado := Contenedor-seguro cifrar: cifrado clave: ['world'].
```

## Tokens

Para generar un token criptográficamente seguro de una longitud determinada:

```
>> mitok := Contenedor-seguro token: 40.
```

Esto generará un token de 40 caracteres.

## Formato

El objeto Formato te permite dar formato a datos, por ejemplo rellenar o
añadir ceros. Usa la sintaxis de printf.

```
>> fmt := Formato crear: ['%06.0f'].
fmt aplicar: 56. # da 000056
```

Un formato puede contener una conversión, y esta tiene que corresponder al valor;
de lo contrario, obtendrás un error:

- `aplicar:` con un texto: `%s`
- `aplicar:` con un número: `%f`, `%e`, `%g` o `%a`
- `aplicar-a-entero:` con un número: `%d`, `%i`, `%o`, `%u`, `%x` o `%c`

Los valores de una petición son textos. Para darle formato a uno como número,
conviértelo primero:

```
fmt aplicar: (solicitud obtener: ['amount']) número.
```

## Codificadores

Hay varios codificadores y decodificadores disponibles.
El codificador de url prepara una url para usarla en HTML como enlace:

```
Server codificar-url: ['https://example.com?a=6&b=1 2'].
```

Para inyectar de forma segura la entrada del usuario en tu HTML sin arriesgarte a
inyecciones XSS, usa siempre:

```
Server codificar-html: ['<inofensivo>'].
```

Ten en cuenta que el motor de plantillas siempre realiza la codificación html
cuando escribes en un marcador de ranura. Así que, si usas el sistema de plantillas,
no necesitas usar esto.

## Correo

Para enviar un correo, usa la biblioteca mailtools.xo.

Ejemplo:

```
Server iniciar.
Programa utilizar: ['mailtools.xo'].

>> correo-e := HTML-Email crear.
>> img := correo-e anexar: ( Archivo crear: ['myimage.png'] ).

correo-e
remitente: ['xo@xoscript.com'] nombre: ['xo'],
destinatario: ( Lista crear ; ['xo2@xoscipt.com'] ),
asunto: ['xoxo'],
cuerpo: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), enviar.

```



## Vinculación

Con el mensaje vincular: puedes vincular una biblioteca externa a
tu programa usando libffi. Para más detalles, consulta el capítulo sobre ffi.


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

FFI se proporciona por plataforma/plugin, porque está
ligado a la arquitectura del sistema subyacente, algo que el
núcleo no debe hacer.
El plugin de servidor ofrece una implementación compatible de ffi/blob.
Por defecto, el núcleo se conecta con la plataforma de destino
mediante stdin/stdout, servicios limitados de E/S de archivos y la shell (Programa sistema:).
La integración adicional la proporcionan ffi/blobs mediante plugins
orientados a aplicaciones, como el plugin de servidor.

FFI significa Foreign Function Interface (interfaz de funciones externas). Te permite usar funcionalidades escritas por otros en
otros lenguajes de programación, proporcionadas mediante archivos DLL, archivos SO o archivos Dylib. Pueden
ser funciones muy variadas, y mediante este método hay disponible una enorme gama de funcionalidades.
Empecemos con un ejemplo:

```
Server vincular: (
 Lista crear ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Lista crear ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s liberar.
```

El resultado de este código es que verás lo siguiente en la línea de comandos:
FFI has 3 letters.
Probablemente estés pensando: «Eso es mucho código para algo tan sencillo».
Es decir, ¿no podríamos resolver esto simplemente con un comando Gui show? ¡La respuesta es un rotundo sí!
Pero esto pretende ser un ejemplo ilustrativo.
FFI se suele usar para tareas más complejas, pero esas no son buenos
ejemplos, así que elegí algo trivial.

Los argumentos del método link:

- Argumento n.º 1: el archivo DLL o SO que quieres usar.
- Argumento n.º 2: la función de ese archivo que quieres vincular.
- Argumento n.º 3: una lista con los nombres de los tipos de datos de los argumentos de la función.
- Argumento n.º 4: el nombre del tipo de retorno de la función.
- Argumento n.º 5: el nombre del objeto al que quieres vincular esta función (si no existe, se creará
automáticamente).
- Argumento n.º 6: el mensaje al que debe vincularse esta función.

En el ejemplo anterior, queremos vincular la función printf de libc.so. Puedes encontrar los nombres
de los tipos de datos en la documentación del software al que te vinculas. Los tipos disponibles son:
void, pointer, float, double, int, uint, char, uchar, intX y uintX,
donde X puede ser 8, 16, 32 o 64.

Estos tipos se refieren al número de bytes necesarios para almacenar los datos. Para printf, vinculamos a un
nuevo objeto llamado Printf y al mensaje template:number:. Traduces la función externa
al dialecto de XOScript antes de usarla. El mensaje template:number: espera como primer
parámetro un búfer con el texto de la plantilla. Creamos este búfer con un objeto Blob, que
te permite reservar memoria manualmente. Eres responsable de liberar después esta memoria
con el mensaje liberar.

Puedes llenar un blob de memoria de varias formas. En nuestro ejemplo, lo llenamos con texto, así que usamos el
mensaje utf8: (UTF-8 es una codificación para convertir texto en bytes). También puedes llenar un blob con
bytes:, pasándole una lista de valores de bytes. Para leer el contenido de un blob, usa desde:longitud:.
Obtendrás los bytes como una lista. Incluso puedes crear un struct de C con un Blob usando el
mensaje estructura:, pasándole una secuencia de tipos de C. Esto puede ser necesario al llamar a una función
de C de una biblioteca de software externa que espera un puntero a un struct.

{warning}
Tienes que liberar los blobs tú mismo.
El recolector de basura no limpia los blobs.
{/warning}

Como los blobs se pueden intercambiar con funciones externas de bibliotecas,
no pueden liberarse automáticamente mediante la recolección de basura (podrían seguir en uso por
funciones externas, o esas funciones externas podrían querer liberarlos
ellas mismas). Por tanto, tienes que liberar los blobs tú mismo cuando sea necesario.

Para liberar un blob, usa:

```
miblob liberar.
```

Para liberar un struct, usa:

```
miestructura liberar-estructura liberar.
```

Así que, para un struct, tienes que enviar dos mensajes: liberar-estructura y liberar para
desasignar el bloque de memoria.

@api_Blob_fficonnect
