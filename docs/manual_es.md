# Base

XOScript es un lenguaje de programación puramente orientado a objetos.
Esto significa que en XOScript todo es un objeto; no existen otros tipos de datos.
Un programa informático escrito en XOScript puede constar, a grandes rasgos,
de tres tipos de acciones: asignar, enviar mensajes y responder.
El intercambio de mensajes entre objetos es la parte más
importante de un programa XOScript.

## Variables

El primer paso es asignar un objeto a una variable. Para asignar una variable, se utiliza
el símbolo de declaración de variable: >> .El nombre de una variable puede contener
todos los signos excepto: <-, := , espacios en blanco , puntos, comas, dos puntos,
comillas [''] y paréntesis (). Además, una variable no puede constar de varias líneas.
Tenga en cuenta que una variable no puede comenzar con un número o un signo menos.
Estos son ejemplos de variables válidas:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dollar'].
>> +plus := True.
>> user password := ['Pssst!'].
```

Las variables no válidas son, por ejemplo:

```
>> -123 := ['número negativo'].
>> contraseña del usuario := ['Clasificado'].
>> contraseña.del:usuario := ['Clasificado'].
>> ,x := 10.
```

Una vez declarada una variable, se puede utilizar libremente. Esto signiﬁca que solo es
necesario utilizar el símbolo de declaración la primera vez que se utiliza la variable (la
declaración).

Para ser más especíﬁcos, no se puede comenzar a declarar aleatoriamente un valor
para la variable ( x := 2 ), ya que primero se debe declarar la variable ( >> x := 2 ).
Sin embargo, una vez declarada se puede cambiar su valor sin utilizar el símbolo de
declaración ( >> x := 2. x := 3. ).

Tenga en cuenta que es obligatorio asignar un valor a una variable en el momento de la
declaración. A diferencia de otros lenguajes de programación, no se permite declarar una
variable sin valor. Es esencial vincular explícitamente cada variable a un valor inicial. No
obstante, siéntase libre de inicializar la variable con el objeto Nulo. En este caso, la
variable puede considerarse vacía ( >> x := Nulo .). En resumen, no está permitido
declarar una variable sin un valor inicial. Por lo tanto,

```
>> x
```

no es válido y mostrará un mensaje de error. (Obtenga más información sobre el objeto
Nulo en el capítulo 3).

## Acciones

XOScript percibe todo como un objeto, por lo tanto, no hay otros tipos de datos.
Básicamente, hay tres acciones rutinarias básicas en un programa escrito en XOScript:
asignar, mensajes programming y responder.
El intercambio de mensajes entre objetos latypes parte clave un programa XOScript. Las
tres acciones: Asignar, Mensajes, Respuesta.

## Objetos y mensajes

Todo es un objeto; es decir, todos los dígitos, textos y fragmentos de código. Los números,
como 1, 2, 100, -999 y 1234, son objetos numéricos. Todos los textos entre comillas simples son
objetos de texto. Todos los fragmentos de código
agrupados entre llaves {...} son objetos de tarea.

Los objetos como los números y el texto siempre tienen
su origen en un objeto base. Todos los números, por ejemplo, derivan del objeto número.
En principio, la programación implica enviar mensajes a objetos. La forma general de enviar un mensaje a un objeto es:

```
<objeto> <mensaje>
```


Por ejemplo, para comprobar si un número es par, se envía el mensaje:

```
2 ¿par?.
```

La respuesta será Verdadero (otro objeto).
Los objetos suelen ignorar los mensajes desconocidos.

objeto puede recibir tres tipos de mensajes. En primer lugar, están mensajes unitarios,
véase el ejemplo anterior, que no tienen argumentos. En segundo lugar, hay mensajes de
palabras clave, que tienen uno o varios argumentos, por ejemplo:

```
>> x := Número entre: 1 y: 10 .
```


En este caso, el mensaje entre: y: se envía a Número, que es el objeto raíz de todos
los números. El resultado será un número aleatorio entre 1 y 10. Por último, hay mensajes
binarios, que tienen solo un carácter y un argumento:

```
2 + 3
```

Esto parece una suma matemática, pero en realidad es solo otro mensaje. El mensaje +
se envía a 2, con argumento 3 que devolverá la respuesta 5. Se permite escribir mensajes
binarios sin dos puntos. Los mensajes binarios se pueden encadenar:

```
>> x := 3 + 2 - 1.
```

En este fragmento, + 2 se envía primero al objeto Número 3, lo que da como resultado
el objeto Número 5, después de lo cual se envía -1 a este número. Los lectores
observadores tienen razón al notar la discrepancia que muestra este protocolo con
respecto a las secuencias matemáticas convencionales de operadores. XOScript ignora la
secuencia matemática a favor de la coherencia en su sistema de mensajes. Como
resultado, la suma:

```
2 + 3 * 5 = 25
```

no 17. Esto es intencional. Se pueden usar paréntesis para modiﬁcar el orden de la secuencia:

```
2 + (3 * 5) = 17
```

La mayoría de los objetos se devuelven a sí mismos como resultado en respuesta a un
determinado mensaje. Esto es útil ya que estimula un diálogo adicional con este objeto al
enviarle un mensaje de seguimiento:

```
Salida escribir:
[' hello '] recortar mayúsculas.
```

Aquí, se envían dos mensajes al objeto Texto : recortar , seguido de mayúsculas.
En el siguiente fragmento, es necesario el uso de una coma para indicar que se está
entrando un nuevo mensaje. De lo contrario, XOScript se confundirá.

```
Salida escribir: ['Hola!'], detener .
```

Primero, se envía el mensaje escribir: al objeto Salida , seguido del mensaje detener .
Sin la coma, XOScript pensaría que desea enviar el mensaje detener al objeto de
Texto Hola , lo cual resultaría un resultado incorrecto.
La secuencia de proceso de mensajes es la siguiente: de izquierda a derecha; comience
con los mensajes entre paréntesis seguidos de los mensajes unitarios. A continuación,
los mensajes binarios y luego termine con los mensajes de palabras clave . Vea el
siguiente ejemplo:

```
Salida escribir: 0.5 redondear + (2 – 1), detener .
```

XOScript siempre lee de izquierda a derecha: primero, se envía el mensaje escribir: a
Salida y es seguido por el mensaje detener .Dentro del argumento en sí,(el
argumento de un mensaje es aquello que va despues de los 2 puntos :) XOScript lee de
izquierda a derecha, por lo que 0,5 redondear y luego el +.

Además, redondear tiene prioridad sobre +, porque es un mensaje unitario.
Como hay paréntesis, primero se calcula 2 – 1, después de lo cual se suma 1 al
resultado de 0,5 redondear (1). Todo el proceso dará como resultado 2,
que también es la respuesta a escribir. Después
de la coma sigue el mensaje de parada, que mueve el cursor a una nueva línea. Por
supuesto, la mejor manera de comprender completamente el orden de secuencia de los
programas de XOScript es con la práctica.
Es importante señalar que en XOScript, al contrario de muchos otros lenguajes de
programación, los espacios en blanco son una parte fundamental de su sintaxis. En
particular, cuando se trata de mensajes binarios, los espacios en blanco pueden causar
cierta confusión.
Utilice siempre un espacio en blanco después de un mensaje binario.
No puede adjuntar directamente un número al mensaje, por ejemplo: 3 + 2 es diferente
de 3 +2. El primer ejemplo (3 + 2), envía el mensaje + al número 3, con el argumento el
número 2. El resultado, en este caso, será 5. En el segundo ejemplo (3 +2), el mensaje
unario +2 se envía al número 3. Dependiendo del contexto eso podría producir un
resultado muy diferente.

## El flujo del programa

En XOScript no hay necesidad de reglas gramaticales separadas para bucles y condicionales.
Una declaración condicional es simplemente un simple mensaje verdadero: o falso: a un
objeto Verdadero o a un objeto Falso .

```
2 ¿par? verdadero: {
	Salida escribir: ['Dos es un número par'] , detener.
}.
```

Los objetos Verdadero y Falso también se conocen como objetos de toma de decisiones.
Esta denominación a veces es más precisa, porque especiﬁca que estos objetos se utilizan
para hacer que el programa maneje ciertas decisiones. Al igual que otros lenguajes de
programación, un programa escrito en XOScript sigue un curso especíﬁco y conlleva varios
patrones de ramiﬁcación. Las formas seleccionadas dentro de un programa dependen en
gran medida de estos objetos de toma de decisiones.
En el ejemplo anterior, el mensaje verdadero: se envía a Verdadero (la respuesta a la
pregunta: ¿es 2 un número par?). Como argumento, se envía un fragmento adicional de
código: un objeto Tarea. Esta tarea escribe en la pantalla que 2 es, de hecho, un número
par.
Tampoco es necesario que existan reglas de escritura independientes para un bucle. Para
ejecutar un fragmento de código tres veces, simplemente envíe * con el argumento 3 a esa
tarea:

```
{ Salida escribir: [' '], detener. } * 3.
```

Consideremos otro ejemplo. Cuando se necesita imprimir una tabla de conversión de
kJ (kilojulio) a kcal (kilocaloría) en pasos de 100, consulte a continuación la notación
correcta:

```
{ :linea
>> kJ := linea * 100.
Salida escribir: kJ, detener.
Salida escribir: kJ * 0.239, detener.
} * 10.
```


Este programa generará la siguiente lista:

Aquí, el número de la línea actual se transmite al parámetro :linea. Al comienzo de una
tarea, se deﬁnen los parámetros de la tarea. Los parámetros no utilizados permanecen
vacíos ( Nulo ). Los parámetros se colocan siempre al comienzo de la tarea, directamente
después del corchete inicial y están precedidos por dos puntos.
El mensaje mientras: es una combinación de un bucle y una condición. Se pueden vincular
dos tareas utilizando el mensaje mientras: La tarea receptora continuará ejecutándose
hasta que la tarea después de los dos puntos dé un resultado negativo. Así es como
funciona:

```
>> x := 0.
{ x añadir: 1. } mientras: { <- x < 5. }.
Salida escribir: x, detener.
```

En el fragmento de código ilustrado anteriormente, se agrega 1 a x siempre que x sea
menor que 5. Cuando este ya no sea el caso, la segunda tarea responderá Falso y, en
consecuencia, la ejecución de la primera tarea ﬁnalizará.

## Plantillas

La lista de kJ/kcal del capítulo anterior podría hacerse más presentable. Preferiblemente,
la lista sería como sigue:

```
100 kj ➞ 23,88 kcal
200 kj ➞ 47,76 kcal
```

Cuando convierte la salida que quieres obtener en una plantilla, su notación podría ser:

```
número1 kJ ➞ número2 kcal
```

Esto signiﬁca que número1 representa el valor de kJ y número2 el valor de kcal. Así es
como funciona la interpolación de cadenas en XOScript. No se necesitan reglas gramaticales
diferentes para hacer esto en XOScript. Simplemente envíe la palabra que necesita ser
reemplazada al texto con el texto sustituto como argumento:

```
>> texto :=
['número1 kJ ➞ número2 kcal']
número1: 100,
número2: 23.9.
El resultado:
```

La regla de sustitución funciona para cada mensaje indeﬁnido que recibe un objeto Texto.
Cada mensaje que no sea reconocido por el objeto Texto será interpretado de la siguiente
manera: reemplace el texto del mensaje con el texto dentro del argumento mensaje.
Puede adaptar el programa de la siguiente manera:

```
{ :linea
>> kJ := linea * 100.
>> kcal := kJ * 0.239.
Salida escribir: (
['número1 kJ ➞ número2 kcal']
número1: kJ,
número2: kcal
), detener .
} * 10.
```

Para evitar confusiones sobre qué mensaje se puede o no utilizar como sustituto, es
mejor introducir un carácter no designado, por ejemplo, un rombo ( ⬧) (U+2B27, ALT+Z),
antes de los segmentos de texto en la plantilla que se deben reemplazar. Este tipo de
carácter es a veces no recomendable en el contexto internacional.

## Respondiendo

Hasta ahora, ha enviado mensajes a objetos. Sin embargo, todavía no ha respondido usted
a ningún mensaje . Para responder un mensaje se utiliza la ﬂecha de retorno (<- ). El
siguiente ejemplo ilustra cómo crear una tarea para calcular un porcentaje:

```
>> porcentaje := {
	:numero :porciento
	<- numero / 100 * porciento.
}.
Salida escribir:
( porcentaje aplicar: 100 y: 7 ),
detener.
```

Una vez que se ha deﬁnido la tarea y se la ha asignado a la variable porcentaje, se envía
el mensaje aplicar:y: con los argumentos 100 y 7.
Esto ejecutará la tarea aplicadando a 100 y 7, es decir, 7% de 100. Al utilizar la ﬂecha de
retorno, la respuesta se devuelve desde la tarea al programa principal. Aunque este código
es válido, tiene una desventaja porque se debe recordar la secuencia de los argumentos.
Entonces, ¿por qué no escribirlo así: 7 porciento de: 100 ? Se vería mucho más natural.
Para que esto sea posible, tenemos que adaptar el objeto padre de 7, que es el objeto
Número, para que comprenda el mensaje porciento de :. Esto se puede lograr enviando
en:hacer: al objeto Número, de la siguiente manera:

```
Número en: ['porciento-de:'] hacer: {
	:número
	<- número / 100 * yo.
}.

Salida escribir:
(7 porciento-de: 100),
detener.
```

Como el porcentaje , en este caso, es el número en sí, nos referimos a yo, la palabra
clave yo. En resumen, el símbolo yo signiﬁca: envíame este mensaje a mí mismo.
Después de haber ejecutado el código mencionado anteriormente,
podemos hacer:

```
Salida escribir:
(7 porciento-de: 100),
detener.
```

Naturalmente el resultado mostrado será:


# Objetos

El mundo de XOScript está lleno de una diversidad de objetos, que están disponibles para
su programa desde el principio. 

Además de ajustar y expandir objetos existentes, también puede crear nuevos objetos
usted mismo simplemente enviando el mensaje nuevo . Supongamos que desea crear un
objeto de factura que aplique una secuencia de numeración; en ese caso, primero
necesitará un objeto de factura.

Si sabe que cada objeto deriva de otro objeto, que, a su vez, eventualmente se origina en
el objeto raíz de todos los objetos llamado Objeto, debe elegir en cuál de esos otros
objetos se basará su nuevo objeto. Su nuevo objeto hereda todas las propiedades del
objeto en el que se basa, es decir, al que se envió inicialmente el mensaje nuevo.
En este ejemplo, se preﬁere un objeto bastante neutral, uno sin demasiadas propiedades
heredadas. Esto ofrece una elección fácil, porque en ese caso el nuevo objeto puede
basarse en el objeto raíz en sí mismo, que es Objeto. La notación del sistema de facturas
deseado será entonces la siguiente:

```
>> factura := Objeto nuevo.
factura en: ['empezar'] hacer: {
	mi numero := 0.
}.
factura en: ['numero'] hacer: {
	mi numero añadir: 1.
	<- mi numero copiar bruto.
}.
```

Utilice este objeto de la siguiente manera:

```
factura empezar.
Salida escribir: factura numero, detener.
Salida escribir: factura numero, detener.
```

El número de factura actual se almacena en el objeto, por eso se coloca una palabra
clave propia delante de él. Esto se llama propiedad; más detalles a continuación.
Algunas empresas preﬁeren tener el año incorporado en los números de factura. En este
caso, puede crear un nuevo objeto de factura basado en un objeto de factura anterior,
pero que ofrece la posibilidad de su usuario de ingresar un año especíﬁco:

```
>> factura-anual := factura nuevo.
factura-anual en: ['empezar:'] hacer: { :año
	mi numero := año.
}.
```

Este objeto de factura de año se puede usar como:

```
factura-anual empezar: 202000.
Salida escribir: factura-anual numero, detener.
Salida escribir: factura-anual numero, detener.
```

No es necesario volver a escribir la implementación del mensaje número, ya que se
hereda del objeto factura escrito anteriormente; en consecuencia, se puede reutilizar
el código antiguo. XOScript carece de conceptos como clases y otros conceptos
relacionados. Esto signiﬁca que los objetos solo pueden heredar de otros objetos, también
conocido como herencia prototípica.
Ahora, volvamos a las propiedades. Las propiedades de los objetos solo se pueden
abordar desde dentro, por lo que otros objetos no pueden percibirlas. A diferencia de otros
lenguajes de programación, todas las propiedades de los objetos son visibles
exclusivamente para el objeto que ha creado la propiedad y para los objetos derivados.

## Herencia

En el capítulo 2 se ha ilustrado que los objetos pueden basarse en otros objetos.
De esta manera, se puede reutilizar el código escrito previamente para crear una
jerarquía de objetos. Por ejemplo:

```
>> Animal := Objeto nuevo.
>> Perro := Objeto nuevo.
>> Caniche := Objeto nuevo.
```

En este caso, Perro hereda todo el comportamiento de Animal y, a su vez, el objeto
Animal hereda todo el comportamiento de Objeto, el objeto raíz de todos los objetos.

## Anulación

En el siguiente ejemplo se crea un nuevo tipo de secuencia: Combinación, en la que se
garantiza que cada elemento sea único. Las funciones de la secuencia se reutilizan
mediante herencia:

```
>> Combinación := Serie nuevo.
Combinación en: ['adjuntar:'] hacer: { :elemento
>> ver := yo encontrar: elemento.
ver falso: { yo adjuntar: elemento. }.
}.
>> colores := Combinación nuevo.
colores
adjuntar: ['rojo'],
adjuntar: ['verde'],
adjuntar: ['azul'],
adjuntar: ['rojo'].
Salida escribir: colores, detener.
```

Observe cómo el segundo rojo queda excluido de la serie:
Ocasionalmente, puede ser necesario anular el comportamiento de un objeto. Por
ejemplo, al sumar números y unidades de medida, se deben tener en cuenta. En el
siguiente ejemplo, se crea el objeto Tamaño. Este objeto devuelve un número que,
durante la suma, tiene en cuenta la unidad del número que se va a sumar. El objeto
Número comprueba si se trata de pulgadas o pies.
El código de programación podría parecerse al siguiente:

```
>> Tamaño := Objeto nuevo.
Tamaño en: ['es:'] hacer: { :número
número en: ['+'] hacer: { :número
>> unidad := numéro calificador.
>> factor := 1.
unidad
en-caso-de: ['pulgadas'] hacer: { factor := 0.0833. }.
>> respuesta := yo + (número * factor).
<- respuesta.
}.
<- número.
}.
```

Este número de tamaño se puede utilizar de la siguiente manera:

```
>> tablero := Tamaño es: 6 pies.
>> borde := Tamaño es: 50 pulgadas.
Salida escribir: tablero + borde, detener.
```

Esto se mostrará como:

En el ejemplo anterior, se está anulando el signo más. Tenga en cuenta que, ﬁnalmente,
todavía se debe realizar la suma ﬁnal, que, de hecho, tiene lugar en la siguiente línea:

```
>> respuesta := yo + (número x factor).
```

Ahora bien, ¿cómo entiende XOScript que este signo más se reﬁere a la lógica original
de la suma? Por ejemplo, otra interpretación podría ser que XOScript enviará
repetidamente el mismo mensaje al mismo objeto, lo que, a su vez, daría como resultado
un bucle inﬁnito. Claramente, esta no es la intención. Tan pronto como envíe un
mensaje a un objeto, que ejecutaría exactamente el mismo código, XOScript se dará
cuenta, en este caso, de que se trata del mensaje subyacente anulado.
Por lo tanto, su programa estará automáticamente protegido contra esta forma de
bucles inﬁnitos. 

## Recursión

Sin embargo, cuando su objetivo sea, de hecho, ejecutar la misma
tarea desde la tarea actual, será necesario enviar primero el mensaje de forma
recursiva. En este caso, el resultado será un bucle inﬁnito. Sin embargo, existen
aplicaciones útiles para las tareas recursivas. Por ejemplo, supongamos que desea
calcular el factorial de un número determinado. En ese caso, simplemente agregue el
mensaje factorial a Número:

```
Número en: ['factorial'] hacer: {
>> respuesta := 1.
yo > 0 verdadero: {
>> anterior := yo.
>> siguiente := anterior - 1.
respuesta := anterior * siguiente recursivo factorial.
}.
<- respuesta.
}.
```

Esto requiere recursión. De hecho, la tarea que está conectada al mensaje factorial
debe ser ejecutada nuevamente dentro de esa tarea. Por lo tanto, es necesario invocar
la tarea factorial desde dentro de la tarea factorial misma. Como regla, XOScript evitará
esta rutina, debido al riesgo de terminar en un bucle inﬁnito. Por esta razón, es vital
preceder el mensaje con la palabra recursivo. Esto se hace para que XOScript sepa
que es tu intención ejecutar la misma tarea y que no cometiste ningún error.
El siguiente bucle muestra los factoriales de los números del 1 al 10:

```
{ :x Salida escribir : x factorial , detener. } * 10.
```

Sin la palabra recursiva, solo se produciría la multiplicación inicial. La lista quedaría
así:

## Objetos de tipo clase

La creación de un objeto que se establece en un estado inicial determinado presenta
un problema frecuente. Supongamos que se debe crear un objeto Rectángulo para
calcular el perímetro y el área. Una posible notación sería:

```
>> Rectángulo := Objeto nuevo.
Rectángulo en: ['área'] hacer: {
	<- mi longitud * mi ancho .
}.
```

Obviamente, establecer una longitud y un ancho es una condición previa. Para ese
propósito, se pueden agregar los mensajes longitud: y
ancho:

```
Rectángulo en: ['longitud:'] hacer: { :longitud
	mi longitud := longitud.
}.
Rectángulo en: ['ancho:'] hacer: { :ancho
	mi ancho := ancho.
}.
```

Este rectángulo se puede utilizar de la siguiente manera:

```
>> rectángulo := Rectángulo nuevo longitud: 2, ancho: 3.
Salida escribir: rectángulo area.
```

Sin embargo, si se pasan por alto los ajustes iniciales de longitud y ancho, aparecerá
un mensaje de error.

```
>> rectángulo := Rectángulo nuevo.
Salida escribir: rectángulo area .
```

Para evitar esto, es preferible que un rectángulo siempre tenga una longitud y un
ancho iniciales, por ejemplo 0. Por lo tanto, en este caso, es necesario anular el
mensaje nuevo.

```
Rectángulo en: ['nuevo'] hacer: {
>> rectángulo := yo nuevo.
rectángulo longitud: 0.
rectángulo ancho: 0.
<- rectángulo.
}.
```

Observe que en la segunda línea se vuelve a invocar el primer nuevo inicial. Sin
embargo, esto no resultará en un bucle inﬁnito, ya que XOScript lo evitará. 
Cuando se crea un
nuevo rectángulo, ahora medirá automáticamente 0 por 0, desde el principio. De esta
manera, no se producirá ningún error al calcular el área:

```
>> rectángulo := Rectángulo nuevo.
Salida escribir: rectángulo area.

>> rectángulo := Rectángulo nuevo longitud: 2, ancho: 3.
Salida escribir: rectángulo area.
```

# Nulo

Objeto muy básico es el objeto Nulo. Este objeto representa el vacío, o mejor aún, la
ausencia de información. En ocasiones, recibirás este objeto como respuesta a un
mensaje, en caso de que el resultado sea nada. La pregunta más esencial que puedes
hacerle al objeto Nulo es: ¿nulo?.
La respuesta siempre será Verdadero

```
Salida escribir: Nulo ¿nulo? .
```

Cualquier objeto que no sea Nulo responderá con Falso. El fragmento de código anterior
puede parecer un poco ﬁlosóﬁco, pero el objeto Nulo ciertamente tiene aplicaciones
extremadamente prácticas. Por ejemplo, recibirá el objeto Nulo como respuesta en caso de
que solicite un elemento de una serie
que no existe.
También puede usar el objeto Nulo si desea declarar una variable, pero no desea
especiﬁcar un valor aún. En su lugar, simplemente asigne el valor especial Nulo. En
XOScript no está permitido declarar una variable sin valor, como:

```
>> valor.
```

En su lugar, debe escribir lo siguiente:

```
>> valor := Nulo.
```

# Booleano

En los capítulos anteriores se han analizado en profundidad los objetos Verdadero o
Falso. Hemos utilizado estos objetos, por ejemplo, para ejecutar tareas en función de
ciertas condiciones. Verdadero y Falso se basan en el álgebra de Boole.
A diferencia de la mayoría de los lenguajes de programación más populares en el
momento de escribir este artículo, XOScript proporciona solo un único objeto Verdadero y un
único objeto Falso. Para aclarar, cada vez que escribe Verdadero no implica que se haya
creado un nuevo objeto. En cambio, siempre utiliza una referencia. Esto signiﬁca que
cuando escribe lo siguiente:

```
>> x := Verdadero.
```

La x se reﬁere al objeto Verdadero. El código condicional y los bucles también veriﬁcan
esta referencia. En XOScript, el signiﬁcado de Verdadero y Falso no es ﬁjo. De hecho, un
programa XOScript se confunde bastante con una declaración como esta:

```
Verdadero := Falso.
```

El resultado de tales acciones no está deﬁnido, pero sigue siendo una acción válida y, por
lo tanto, está permitida formalmente. Además, hay un objeto Decision, que es el objeto
raíz de Verdadero y Falso, ya que ambos son derivados del objeto raíz. Sin embargo, el
objeto Decision en sí no proporciona ninguna
aplicación práctica.
Por medio de los objetos Verdadero y Falso, puede ejecutar partes de su programa bajo
condiciones especíﬁcas:

```
>> precio := Número entre: 0 y: 20.
>> presupuesto := 10.
precio > presupuesto verdadero: {
Salida escribir: ['demasiado caro'].
}, falso: {
Salida escribir: ['¡vendido!'].
}.
```


Para facilitar la lectura, en lugar de falso: también puede utilizar el mensaje otro:. Esto es
básicamente lo mismo , porque el mensaje otro: es un sinónimo de falso:. (otro , hace
referencia a - otro caso - ) Por lo tanto, el siguiente fragmento muestra exactamente el
mismo procedimiento:

```
>> precio := Número entre: 0 y: 20.
>> presupuesto := 10.
precio > presupuesto verdadero: {
Salida escribir: ['demasiado caro'].
}, otro: {
Salida escribir: ['¡vendido!'].
}.
```

Depende totalmente de usted cuál de las dos variaciones preﬁere utilizar para facilitar la
lectura.
Los objetos de decisión también se pueden utilizar para combinar diferentes condiciones.
Por ejemplo, una tarea se puede ejecutar cuando dos cosas producen un objeto
Verdadero. O bien, si se cumple una de dos o incluso más condiciones, como se ilustra
en el siguiente ejemplo:

```
>> azúcar := Verdadero.
>> leche := Falso.
>> x := azúcar y: leche.
```

En el fragmento anterior se crean dos nuevos objetos, que son azúcar y leche. El objeto
azúcar es un objeto Verdadero mientras que leche es un objeto Falso. Ahora, cuando
quieres saber si alguien preﬁere tanto leche como azúcar en su café o té, envías el
mensaje y: a un objeto y envías el otro objeto junto con él como argumento. La respuesta
a y: será Falso, porque y: solo responde con Verdadero cuando el objeto en sí es
aﬁrmativo, así como el argumento. En cualquier otro caso, devolverá Falso. Entonces,
en este caso x es igual a Falso. Además del mensaje y:, también puedes usar o: ,
de la siguiente manera:

```
>> azúcar := Verdadero.
>> leche := Falso.
>> x := azúcar o: leche.
```

En este caso, el azúcar, coincidentemente el primer objeto indicado, responderá
Verdadero. El objeto Verdadero al que se reﬁere la variable azúcar, en realidad siempre
responde a la pregunta o: con Verdadero si efectivamente el objeto en sí es aﬁrmativo
o efectivamente el objeto en el argumento es aﬁrmativo, o si ambos son Verdadero.
En caso de que ninguno de los objetos sea Verdadero, entonces la respuesta será Falso.
Al usar el mensaje o: puede esperar Verdadero si está rodeado por dos objetos Falso.

```
>> azúcar := Falso.
>> leche := Falso.
>> x := azúcar o: leche.
```

Con el mensaje no se invierte un objeto de decisión, es decir, un Verdadero se convierte
en Falso

```
>> azúcar := Falso no.
>> leche := Falso no.
>> x := azúcar y: leche.
```

Entonces, en este caso x es Verdadero, porque tanto azúcar como leche son Falso no,
es decir, no no, por lo tanto Verdadero.
Con entonces:caso-contrario: puedes seleccionar, por medio de un objeto Verdadero o
Falso, un objeto diferente de un par de objetos. De la siguiente manera:

```
>> azúcar := Verdadero.
>> x :=
azúcar
entonces: 1 cuchara caso-contrario: Nulo.
```

En el fragmento anterior x será igual a 1 cuchara. Cuando el mensaje de recepción es
Verdadero, se seleccionará el primer objeto y si no, se seleccionará el segundo.
También puedes convertir un Verdadero o un Falso en un número enviando el número
del mensaje. El objeto Verdadero responderá con 1 y Falso responderá con 0.
Obviamente, también puedes comparar objetos Verdadero y Falso entre sí:

```
>> x := (Verdadero !=: Falso).
>> y := (Verdadero = Falso).
```

En este caso x es igual a Verdadero e y es igual a Falso.
Los mensajes continuar y salir se pueden utilizar dentro de un bucle. Por lo tanto,
cuando envía salir dentro de un bucle a un objeto Verdadero, el bucle ﬁnalizará desde
ese punto. El programa continuará en la primera instrucción después del bucle.
El mensaje continuar está relacionado con salir, sin embargo, en lugar de ﬁnalizar todo
el bucle, solo ﬁnalizará la iteración actual. La parte restante de la ronda actual se omite y
se inicia la siguiente ronda del bucle.
A continuación, se muestran algunos ejemplos:


```
{ :i
Salida escribir: i, detener.
(i > 9) salir.
} * 20.
````

Este fragmento de código en particular ilustra el efecto de la interrupción del mensaje.
Muestra una pequeña lista de los números del 1 al 10; sin embargo, tan pronto como el
número en i supera diez, el bucle se interrumpe en ese punto.

```
{ :i
(i > 10 and: i < 15) continuar.
Salida escribir: i, detener.
} * 20.
```


Este fragmento de código produce una pequeña lista de 1 a 10 seguida de 15 a 20. Los
números entre 10 y 15 se omiten. Esto se debe a que para este intervalo la condición
( i > 10 y: i < 15 ) da como resultado Verdadero, por lo que el mensaje continuar se
envía a este objeto Verdadero. Esto signiﬁca que se omite la parte restante del bucle y
comienza la siguiente iteración. Los mensajes continuar y salir son ignorados por el
objeto Falso.
Finalmente, el mensaje texto le permite crear una representación textual de un objeto
Verdadero o Falso.

# Número

Cada vez que escriba un número, por ejemplo 9, -10 o 3,12, detrás de la pantalla,XOScript
convertirá estos números en un objeto Número. Puede enviar mensajes a este objeto
Número, o puede asignar el número a una variable y enviar mensajes después:

```
10 ¿par?
```

```
>> diez := 10.
diez ¿par?
```

Ambas notaciones son válidas. El objeto Número responde a los siguientes mensajes
como: >, ≥( >=:), <, ≤ (<=:), =, ≠ (!=:), +, –, *, /, entre:y: , ¿impar? , ¿par?, añadir: ,
restar:, multiplicar-por: , dividir-por:, módulo:, elevar-a:, ¿positivo?, ¿negativo?,
redondear, redondear-al-alza , redondear-a-la-baja , raíz-cuadrada , absoluto , texto ,
bruto , caliﬁcación , booleano y caliﬁcar:
La mayoría de estos mensajes se explican por sí solos y permiten ejecutar operaciones
matemáticas (+) o comparaciones (>). La diferencia entre los mensajes matemáticos
binarios (+) y sus variaciones de palabras clave (añadir:) es que los primeros devolverán
un nuevo número, que es el resultado de la operación, mientras que con los últimos
se modiﬁcará el objeto en sí. Esto se ilustra en el siguiente ejemplo:

```
>> a := 1.
>> b := a + 3.
a añadir: 2.
Salida escribir: a, detener.
Salida escribir: b, detener.
```

En el ejemplo anterior, b = 4 y a = 3. Con añadir: 2 el valor de a se aumenta en 2,
mientras que + 3 crea un nuevo número que es igual a a + 3. Lo mismo se aplica a otros
procesos matemáticos, por ejemplo, las multiplicaciones. Al utilizar el símbolo de
multiplicación, recibirá un nuevo objeto como respuesta. En caso de que utilice el mensaje
multiplicar-por:, multiplicará el número en sí.
Con el mensaje entre: y:, por ejemplo en: Número entre: X y: Y, obtendrá un número
entre X e Y. De esta manera, se puede generar cualquier número aleatorio:

```
>> a := Número entre: 1 y: 10 .
```

Tenga en cuenta que el generador integrado de números aleatorios en XOScript no es
adecuado para aplicaciones criptográﬁcas.
Puedes adjuntar un caliﬁcador a un número, por ejemplo, 6 manzanas. Cada mensaje
que no sea reconocido por un número será considerado un caliﬁcador. Puedes recuperar
el caliﬁcador de un número por medio del caliﬁcador de mensaje:

```
>> cantidad := 6 monedas.
Salida escribir: cantidad.
Salida escribir: cantidad calificador.
```

Un caliﬁcador es básicamente un objeto de texto que se almacena con el objeto de
número. El caliﬁcador también se imprime después del número en una asignación de
escritura (escribir:) . Los caliﬁcadores se pueden utilizar para sumar cantidades en
monedas mixtas, por ejemplo. Al sumar las cantidades, puede solicitar los caliﬁcadores.
El siguiente ejemplo de programa ilustra este principio utilizando una calculadora de
moneda histórica (¡ya que el tipo de cambio se mantiene razonablemente estable!).

```
Número en: ['+'] hacer: { :cantidad
	(cantidad calificador = ['ducados']) verdadero: {
		cantidad multiplicar-por: 5.
	}.
	yo añadir: cantidad.
}.
Salida escribir: (7 florines + 3 ducados), detener.
```

En el fragmento de código anterior, el mensaje + se adapta de tal manera que se tiene
en cuenta la moneda. En este ejemplo, 1 ducado equivale a 5 ﬂorines. La palabra clave
yo indica el objeto en sí: yo se utiliza para enviar un mensaje al objeto en sí. Además,
también se puede establecer un caliﬁcador de forma explícita utilizando el caliﬁcador de
mensaje:

```
>> x := 7 calificador: ['ducatos'].
```

# Texto

Cada vez que se coloca un texto entre bloques y comillas [‘…’],
Xoscript crea un nuevo objeto de cadena. Sin embargo, asegúrese de usar
las comillas correctas. La comilla al principio del texto es diferente de la
del final (esto permite usar la comilla simple sin necesidad de escaparla).

## UTF-8

Las cadenas en xoscript suelen contener texto codificado en UTF-8.
Si bien técnicamente es posible incluir contenido binario o que
no esté codificado en UTF-8 en una cadena, se recomienda usar blobs para ello.
Los blobs los proporciona el complemento del servidor (véase el capítulo ffi).
En general, los blobs/ffi se proporcionan según el
complemento/plataforma, ya que están vinculados a la plataforma y
la arquitectura (ffi/blobs). El núcleo del lenguaje de scripting
intenta ser lo más independiente posible de la plataforma.

## Copiar

Al usar := es posible guardar objetos con un nombre determinado (es decir,
asignarlos a una variable). También es posible guardar un objeto con varios nombres.
Tenga en cuenta que esta acción es diferente a la de realizar una copia real.

```
>> oveja := ['Dolly'].
>> clone := oveja.
clone reemplazar: ['l'] con: ['n'].
Salida escribir: oveja, detener.
```

Aquí, podría haber esperado que la salida fuera Dolly, en lugar de Donny. Sin
embargo, este no es el caso, ya que ambos nombres hacen referencia al mismo
objeto. Cuando se trabaja con un bucle, ocurre algo similar:

```
>> puntos := Serie ← 1 ; 2 ; 3.
puntos cada: { :número :cantidad cantidad añadir: 1. }.
Salida escribir: puntos, detener.
```

De hecho, XOScript siempre usa referencias, por lo que en :cantidad el bucle ilustrado
anteriormente también indica la
referencia al elemento en la secuencia:

Para copiar un objeto, debes especiﬁcar esta acción explícitamente:

```
>> oveja := ['Dolly'].
>> clone := oveja copiar.
clone reemplazar: ['l'] con: ['n'].
Salida escribir: oveja, detener.
```

Al enviar el mensaje unario copiar a un objeto Texto, el objeto devuelve una copia de
ese mismo objeto Texto. Es posible copiar objetos Número, Booleano, Serie, Lista y
Momento de la misma manera.
También puede deﬁnir su propia implementación de copia, esto es incluso una
necesidad si crea sus propios objetos. Creemos una implementación de copia
alternativa para series. La implementación predeterminada de copiar para una serie
hace una copia superﬁcial, crea una nueva lista con los mismos elementos.

```
>> a := Serie ← 1 ; 2 ; 3.
>> b := a copiar ; 4.
Salida escribir: a, detener escribir: b, detener.
```

En este caso, se agrega 4 solo a la copia.
Sin embargo, debido a que la copia es superﬁcial, los objetos en ambas series son los
mismos:

```
>> oveja := Serie ← ['Dolly'] ; ['Shaun'].
>> clones := oveja copiar.
clomes cada: { :número :sheep
oveja adjuntar: ['2'].
}.
Salida escribir: oveja, detener.
Salida escribir: clones, detener.
```

Entonces, si agregamos 2 a cada nombre en la copia, la serie original también se ve
afectada. Para solucionar esto, necesitamos hacer una copia profunda. Esta acción de copia
para una secuencia podría estar compuesta de la siguiente manera:

```
Serie en: ['copiar'] hacer: {
>> copiar := Serie nueva.
yo cada: { :number :sección
copiar adjuntar: sección recursivo copiar.
}. <- copiar.
}.
```

Puedes usarla de esta manera:

```
>> oveja := Serie ← ['Dolly'] ; ['Shaun'].
>> clones := oveja copiar.
clones cada: { :número :sheep
oveja adjuntar: ['2'].
}.
Salida escribir: oveja, detener.
Salida escribir: clones, detener.
```


Si elimina la acción de copia, el resultado serían dos impresiones de la segunda
serie. A primera vista, parece que la adición simplemente copia la oveja en la serie
principal y deja de lado las subseries. Sin embargo, si el código de llamada se
ajusta a:

```
>> oveja := Serie ← ['Dolly'] ; (Serie ← ['Shaun']).
```

Entonces, a pesar de que Shaun está en una subserie, de hecho se copia
correctamente. ¿Cómo funciona esto? Bueno, tiene todo que ver con las
convenciones de nombres. Debido a que la acción de copia se ha conectado al
mensaje llamado copiar, todos los objetos responderán con su respectivo
comportamiento de copia, no importa si el objeto receptor es Texto o una (sub)Serie.
Además, tenga en cuenta que el mensaje es recursivo, este mensaje es necesario
para enviar antes del mensaje de copia. Más
sobre este mensaje en el capítulo 4.4
Es esencial tener en cuenta que, aunque una copia de un objeto a menudo tiene la
misma apariencia que el original, de hecho, nunca será el mismo. El objeto raíz
deﬁne un mensaje es-igual-a: , que puede usarse para comparar la identidad de los
objetos. Observa el siguiente ejemplo:

```
>> a := 1.
>> b := a copiar.
>> c := a.
Salida escribir: a = b, detener.
Salida escribir: a = c, detener.
Salida escribir: ( a es-igual-a: b ),
Salida escribir: ( a es-igual-a: c ),

detener.
detener.
```

En este caso, a = b, porque a es una copia de b y el mensaje ['='] mira el valor del
objeto,que en el caso anterior, es el número. Dado que a = 1 y b = 1 y 1 = 1, la
respuesta será Verdadero. Lo mismo se aplica a c. Solo cuando se utiliza el mensaje
es-igual-a: , que Número hereda de Objeto, se puede notar una diferencia.
Mientras que c es igual a a, porque aquí la referencia se asigna utilizando el símbolo
:=, a (no es igual a) b. Esto se explica por el hecho de que dentro de la
computadora

La copia de la memoria es físicamente un objeto diferente. Por lo tanto, para averiguar
si efectivamente la referencia es al mismo objeto físico en la memoria de la
computadora, puede aplicar el mensaje es-igual-a:

## Conversión implícita

XOScript utiliza la conversión implícita para convertir objetos. Para imprimir una
secuencia en la pantalla, XOScript, por ejemplo, enviará el texto del mensaje i
nternamente a la secuencia. Esto puede resultar muy útil, en caso de que
quiera imprimir una secuencia como una lista separada por comas. El texto del
mensaje se puede sobrescribir:

```
>> suma := Serie ← 1 ; 2 ; 3.
suma en: ['texto'] hacer: {
<- yo unirse: [','].
}.
Salida escribir: suma, detener.
```

Y de esta manera obtenemos

En las operaciones matemáticas con números, el número del mensaje se envía
internamente. De esta manera, es posible crear una secuencia que proporcione
automáticamente la suma durante una operación matemática:

```
>> suma := Serie ← 1 ; 2 ; 3.
suma en: ['número'] hacer: {
>> total := 0.
yo cada: { :número :elemento
total añadir: elemento.
}.
<- total.
}.
Salida escribir: 1 + suma, detener.
```

# Funciones

El objeto de tarea responde a mensajes como: empezar, *, mientras:, error:, capturar:
y proceder:. El capítulo 2 ilustró cómo un fragmento de código determinado se puede ejecutar varias
veces; es decir, enviando el mensaje * a una tarea, seguido de la cantidad de iteraciones
requeridas. Para un recordatorio rápido, aquí hay dos nuevos ejemplos de ese tipo de
mensajes. Primero, el bucle simple:

```
{ :grados
	Salida escribir:
	grados * 1.8 + 32, detener.
} * 30.
```

Este ejemplo devuelve una pequeña lista de temperaturas que van desde 1 a 30 grados
Fahrenheit

Esta secuencia se crea cuando la tarea entre corchetes {} se multiplica por el número 30.

```
>> grados := 0.
{
	Salida escribir:
	grados * 1.8 + 32, detener.
	grados añadir: 1.
} mientras: { <- grados <=: 0. }.
```

El fragmento ilustrado anteriormente devuelve el mismo resultado, sin embargo, utiliza
un bucle while. En este caso, el mensaje mientras: se envía a la tarea con el argumento
una segunda tarea. La primera tarea se ejecutará repetidamente, hasta que la segunda
tarea devuelva un Falso. Para aclarar, mientras la respuesta a la primera tarea siga
siendo Verdadera, la primera tarea continúa ejecutándose. Debido a que cada vez que
se agrega 1 a la cantidad de grados durante la ejecución de la primera tarea, la segunda
tarea devolverá Falso tan pronto como cuente 31
grados Fahrenheit.

Una forma diferente de manipular el ﬂujo del programa informático es deﬁnir un fragmento
de código con controladores en caso de error. Por ejemplo, digamos que una aplicación
de presupuesto tiene que determinar el presupuesto mensual en función de la entrada de
un usuario sobre los ingresos y la cantidad de meses.

```
>> presupuesto := ingresos / meses.
```

¿Puedes adivinar qué sucede cuando la cantidad de meses resulta ser 0? Lo que sucede
es un mensaje de error:

La primera línea del mensaje muestra que se ha producido un error que no ha sido
gestionado por el programa. La segunda línea de la salida indica el problema real, que es,
en este caso, que no se permite la división por 0. La primera línea también revela que
se puede gestionar un error. Este también es un caso de ejecución de código
condicional; sin embargo, en esta situación se escribirá y ejecutará un fragmento de
código en caso de que se produzca un error provocado por un fragmento de código
diferente. Por ejemplo, vea cómo modiﬁcar este
mensaje de error:

```
{
>> presupuesto := ingresos / meses.
} capturar: { :error
	Salida escribir: ['¡No permitido!'], detener.
}, empezar.
```

En este caso la salida será (en 0 meses)

En este caso, ha gestionado su propio manejo de errores. Tenga en cuenta que falta la
sentencia de -error no manejado - ; después de todo, usted manejó bien el error y,
según XOScript, ese es el ﬁnal.
Sin embargo, ¿cómo funciona exactamente el manejo de errores en el ejemplo anterior?
En primer lugar, hay dos tareas: la tarea original y la tarea de manejo. Estas tareas
están vinculadas por el mensaje capturar: Al recibir el mensaje capturar: una tarea con
la captura, el objeto Tarea receptor cambiará, en caso de que ocurra un error, al código
dentro del objeto Tarea que se ha asignado para realizar el manejador de errores.
Después de que los dos bloques estén vinculados, es obvio qué hacer en caso de que
ocurra un error. 

En realidad, no se está iniciando nada. Esto introduce el mensaje ﬁnal en el fragmento de
código: empezar. Esto inicia la ejecución del primer objeto Tarea, porque el mensaje
capturar: produce el propio objeto Tarea como respuesta. Además, dado que se trata de
un mensaje de palabra clave, se necesitará una coma para encadenar el nuevo mensaje
unario. Formalmente, la estructura se puede observar de la siguiente manera:

```
{ Tarea 1 } capturar: { Tarea 2 }, empezar.
```

También puede provocar que se produzca un error en su programa de forma intencionada
y, al hacerlo, activar el bloque manejador. Esto se hace enviando el mensaje error: a la
tarea actual, como se muestra en la siguiente
ilustración:

```
{
	esta-tarea error: ['Whoops!'].
} capturar: { :mistake
	Salida escribir: mistake.
}, empezar.
```

Tenga en cuenta que el objeto de error incluido en el mensaje error:, se devuelve en la
rutina del controlador. De esta manera, se pueden pasar diversos objetos de error
autoinducidos a su tarea de controlador. Además, muestra cómo puede comunicarse con
la tarea actual enviando un mensaje a esta-tarea.

En lugar de enviar el mensaje empezar, se puede utilizar el mensaje * 1 para ejecutar la
tarea una vez. Ambos mensajes terminan teniendo el mismo resultado. Un mensaje que
es muy similar a empezar (o * 1, dependiendo de cómo lo mire) es el mensaje proceder.
Este mensaje se utiliza a menudo para mejorar la legibilidad. En el siguiente ejemplo se analizarán los diversos aspectos de cómo se utiliza
el objeto Tarea en la práctica. Este próximo programa de demostración tiene como
objetivo convertir un número en números romanos. Este
ejemplo en particular se limita a números inferiores a 40.

```
>> numero := 17.
{
	{
		numero >=: 10 verdadero: {
			Salida escribir: ['X'].
			numero restar: 10.
		}, salir.
		numero >=:≥9 verdadero: {
			Salida escribir: ['IX'].
			numero restar: 9.
		}, salir.
		numero >=: 5 verdadero: {
			Salida escribir: ['V'].
			numero restar: 5.
		}, salir.
		numero >=:≥4 verdadero: {
			Salida escribir: ['IV'].
			numero restar: 4.
		}, salir.
		numero >=: 1 verdadero: {
			Salida escribir: ['I'].
			numero restar: 1.
		}, salir.
	} proceder.
} mientras: { <- numero > 0. }.
```

El programa en su forma actual devuelve el número romano correspondiente al número
17. Al modiﬁcar el valor del número 17 en la parte superior del programa por algo
diferente, por ejemplo 20, el resultado cambiará igualmente (XX). Ahora, observe más de
cerca el programa. Los corchetes más externos pertenecen al mensaje while:. En este
punto, vincula dos tareas. La primera tarea continúa ejecutándose mientras la segunda
tarea siga devolviendo Verdadero como respuesta. Esa segunda tarea es bastante
simple:

```
{ <- numero > 0. }
```

Esto signiﬁca que, mientras numero sea mayor que 0, se ejecutará la primera tarea.
La primera tarea es un poco más larga, sin embargo, es básicamente un conjunto de
tareas condicionales. Eche un vistazo al primer fragmento:


```
numero >=: 10 verdadero: {
	Salida escribir: ['X'].
	numero restar: 10.
}, salir.
```

En este caso, se pregunta si el número es mayor o igual a 10. Si la respuesta a esta
pregunta es Verdadero, se escribe el símbolo romano del número 10, que es X. Para
continuar, se restan 10 al número y se termina esta ronda. En consecuencia, el mensaje
salir salta del bucle y comprueba si el número sigue siendo mayor que 0. Si es así, se
inicia otra ronda. En el caso de que el número sea 20, se llega de nuevo a esta primera
parte. En el caso de 17, la respuesta a la pregunta si el número ≥ 10 debe leerse
claramente Falso, ya que 17 - 10 = 7, y 7 es menor que 10. En este caso, se desciende
al siguiente bloque (número ≥ 9). Nuevamente, la respuesta será Falso, ya que 7 es
menor que 9. Luego, se llega a (número ≥ 5), lo que da como resultado V. De esta
manera, se va cortando el número romano más grande posible de su número hasta que
no quede nada.
Sin embargo, hay un pequeño tecnicismo oculto en este programa. Tenga en cuenta que
también se envía el mensaje salir, en caso de que exista la posibilidad de mostrar un
número romano en la pantalla. Esto es para evitar la visualización de un número romano
más pequeño demasiado pronto. En el caso de 20 (XX), no es deseable mostrar un IX
después de la X; básicamente, el objetivo es reiniciar el proceso. De hecho, es por eso
que los comparadores de números están dentro de una tarea y el mensaje proceder se
envía a la tarea externa. Este procedimiento garantiza la posibilidad de abortar la tarea
después de que se haya realizado una comparación exitosa.
XOScript proporciona a las tareas la opción de inyectar valores. Ahora, observe la tarea a
continuación:

```
>> enviando := {
	Boletin hacia: mi recipiente.
}.
enviando asignar: ['recipiente']
valor: ['info@citrine-lang.org'].
enviando empezar.
```

Esta ilustración presenta una tarea imaginaria que envía un boletín informativo a una
dirección de correo electrónico o destinatario. Este destinatario se puede inyectar en la
tarea, de forma externa y antes de que se inicie la tarea, enviando el mensaje
asignar:valor: a la tarea. Al hacerlo, el valor del destinatario se preestablece en la
tarea. Este valor también se puede modiﬁcar y la tarea se puede volver a ejecutar. Este
es un método útil cuando se utilizan objetos de tarea

No se permiten tareas vacías. En teoría, una tarea vacía se vería así: {}, sin embargo,
XOScript percibe esto como un error de lenguaje. Si desea declarar una tarea vacía, puede
utilizar el objeto Nulo:

```
>> tarea := Nulo.
```

Aunque no se trata de una tarea real, sino de un objeto Nulo, se puede enviar un
mensaje de inicio:

```
>> respuesta := tarea empezar.
```

De hecho, es lo mismo que:

```
>> respuesta := Nulo empezar.
```

Debido a que el objeto Nulo no reconoce el mensaje empezar, se devolverá a sí mismo
como respuesta, dejando la respuesta nuevamente como Nulo. Por lo tanto, no es
necesario tener una tarea vacía. Debido al elegante diseño del lenguaje de programación
XOScript, puede simplemente utilizar el objeto Nulo para esto.

## Visibilidad

Como ya sabes, un objeto puede asignarse a una variable, pero primero debes asignar
memoria en la memoria bajo este nombre, y para ello utilizas un símbolo de declaración.
Esta acción se llama declarar una variable. Por supuesto, esto ya se ha tratado en los
capítulos anteriores. Sin embargo, no todas las secciones de la memoria son visibles
en todas partes, porque en programas grandes, que podrían llevar código de terceros,
es probable que los nombres entren en conﬂicto. Por este motivo, estas ubicaciones de
memoria están separadas entre sí, por lo que las tareas forman las líneas divisorias.
Aquí se debe tener en cuenta que una variable que se declara dentro de una tarea, solo
es visible durante la ejecución de esa tarea especíﬁca y durante la ejecución de todas
las tareas iniciadas por esta tarea. Cuando una tarea en la que se declara la variable
ha ﬁnalizado, se
olvidará de alguna manera. Observa el siguiente ejemplo:

```
>> x := 9.
{ Salida escribir: x. } empezar.
```

El número 9 se imprime en la pantalla con el programa que se muestra arriba. El
nombre de objeto x se ha declarado fuera de la tarea y, en consecuencia, es visible en
todas partes, para todas las tareas, incluso cuando x se envía como argumento al objeto
Salida. El área fuera de la tarea se puede considerar como una especie de tarea
paraguas.

Todas las variables que se declaran en esta área son visibles en todas partes en el
programa, de hecho, todas las tareas están dentro de los límites de esta tarea paraguas,
por así decirlo. Las variables que se declaran fuera de todas las tareas del programa
también se conocen como variables globales, debido a su visibilidad global.

```
{ >> x := 9. } empezar.
Salida escribir: x.
```

En este caso, aparecerá un mensaje de error. El nombre de objeto x se olvida tan
pronto como ﬁnaliza la tarea. Dado que x se ha declarado dentro de la tarea, no es
visible fuera de ella. En este caso, x vive exclusivamente dentro de la pequeña tarea
que se ha escrito. Ahora, observe el siguiente fragmento, no hay mensajes de error;
Sin embargo, ¿qué número aparecerá en la pantalla?

```
>> x := 1.
{ >> x := 9. } empezar.
Salida escribir: x.
```

Aquí, la respuesta correcta es 1 en lugar de 9. En este caso, hay dos ubicaciones en
la memoria con el nombre x. Gracias a los límites entre las tareas, no se afectan entre
sí. Durante la

ejecución de la tarea, x es igual a 9, y tan pronto como la tarea ha terminado, la otra x
se vuelve visible de nuevo y x será igual a 1.
Y ahora la versión más complicada:

```
>> y := { x := 2. }.
{ >> x := 1. y empezar. Salida escribir: x. } empezar.
```

¿Cuál aparecerá en pantalla: 1 o 2 ? Veamos. En primer lugar, se asigna un lugar en la
memoria con el nombre y para una tarea. En esa tarea en particular, el número 2 se
guarda con el nombre x.

Sin embargo, esta tarea no se inicia. En la segunda línea se crea una nueva tarea, que
comienza de inmediato. En esta nueva tarea, se declara x. Por lo tanto, se asigna un
lugar en la memoria con el nombre x. En consecuencia, con el nombre x se guarda el
número 1. En ese momento x=1. A continuación, se inicia la tarea llamada y, que se ha
escrito en la primera línea de este programa. Durante la ejecución de esa tarea, el
número 2 se guarda bajo el nombre x. ¿Es esto posible? La respuesta a esta
pregunta es un rotundo sí. Aquí, la línea crucial está efectivamente durante la
ejecución. Aunque la tarea y, desde un punto de vista visual, queda fuera de la tarea
de la línea 2, la tarea y se está ejecutando de hecho durante la ejecución de la tarea
en la segunda línea. Esto signiﬁca que, el 1 que estaba en x, se sobrescribe con el
número 2. De hecho, en ese momento x = 2. Entonces, la tarea y ha terminado y la
ejecución del programa vuelve a la tarea en la segunda línea, lista para imprimir x en
la pantalla.
Sin embargo, ¿qué hay dentro de x ahora que la tarea y ha terminado? Para aclarar,
solo x se declaró fuera de y, es decir, en la tarea que se está procesando actualmente,
la de la segunda línea, por lo que x todavía contiene el número 2 y, como resultado,
se hará visible en la pantalla. Este mecanismo, como se acaba de describir, también se
llama Alcance dinámico. A modo de comparación, en JavaScript un código similar da
como resultado 1:

```
y = function() { x = 2; };
(function(){ var x = 1; y(); console.log(x); }())
```

En los ejemplos que se muestran arriba, se utilizan objetos Tareas separados cada vez.
Esto mismo se puede ilustrar en base a otros objetos. El siguiente ejemplo ilustra cómo
el sabor del helado se modiﬁca consistentemente en malaga:

```
>> heladería := Objeto nuevo.
heladería en: ['helado'] hacer: {
	sabor := ['Malaga'].
}.
Heladería en: ['visitar'] hacer: {
	>> sabor := ['Pistachio'].
	Heladería helado.
	Salir escribir: sabor, detener.
}.
Heladería visitar.
```
En consecuencia, la salida del programa es:

```
Malaga
```

Tan pronto como la heladería recibe el mensaje helado, el sabor se ajusta a Málaga.
Para las personas que nunca han trabajado con otro lenguaje de programación que no
sea XOScript, esto no sería muy sorprendente. Después de todo, esto tiene todo el sentido
según los procedimientos generales de XOScript. Sin embargo, en la mayoría de los otros
lenguajes de programación, la salida sería Pistachio, o incluso devolverían un mensaje
de error, dependiendo de las reglas de visibilidad.

# El objeto raíz

El objeto llamado Objeto es el objeto raíz de todos los objetos en XOScript. Este objeto
raíz responde a mensajes como: hacer, hecho, en-caso-de:hacer: , en:hacer: ,
mensaje:argumentos: , responder:y: … , aprender:signiﬁca: , y recursivo. Todos
los demás objetos se derivan de este objeto, incluido el objeto Nulo. El mensaje que se
envía con más frecuencia es en:hacer: , que amplía las funcionalidades de un objeto.
Este mensaje es recibido por el objeto raíz, que en consecuencia vincula la tarea
especiﬁcada al mensaje y, al hacerlo, expande el objeto derivado. Este método ya se
mencionó en el capítulo 2, sin embargo, para completar, observe otro ejemplo.
En la siguiente ilustración, se deﬁne un objeto circular con la intención de calcular su
área en función de
su radio:

```
>> circulo := Objeto nuevo.
	circulo en: ['radio:'] hacer: { :r
	mi radio := r.
}.
círculo en: ['área'] hacer: {
	<- mi radio * 2 * 3,14.
}.
```

Se añaden dos mensajes: radio:, que se utiliza para establecer el radio del círculo, y
area, que se utiliza para calcular su area. Este objeto se puede utilizar de la siguiente
manera:

```
circulo radio: 4, área.
```

El resultado será 25,12 (tenga en cuenta que se utiliza una aproximación muy
aproximada de Pi, es decir, 3,14, por lo tanto, el resultado no es muy preciso). Este
objeto también puede basarse en otro objeto, lo que signiﬁca que un objeto deﬁnido
previamente se expande enviando mensajes en:hacer:. De esta manera, por ejemplo,
un objeto Usuario puede basarse en un objeto Persona al que se le puede agregar un
nombre de inicio de sesión:

```
>> Usuario := Persona nuevo.
Usuario en: ['login:'] hacer: { :nombre
	mi login := nombre.
}.
```


Además, los objetos del sistema pueden expandirse, como el objeto Texto con un cifrado
ROT-13. Esta es una manera fácil de cifrar textos, basada en la técnica de cifrado
Cifrado César (que es muy débil para propósitos más serios). El principio detrás de
ROT-13 es bastante simple. Cada carácter se desplaza 13 posiciones en el alfabeto.
En caso de que un carácter pase el carácter z, el conteo continúa desde a en adelante.
Por lo tanto, a se convierte en n, b se convierte en o y x se convierte en k. Por ejemplo,
cuando el texto Londres se cifra con ROT-13, mostrará Lbaqba.
Si se necesita agregar una funcionalidad de este tipo a cada texto, la manera más fácil de
hacerlo es expandir el objeto Texto en sí (ya que cada texto deriva de este mismo objeto)
utilizando el mensaje en:hacer:

```
Texto en: ['rot13'] hacer: {
	>> alfabeto :=
	['abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz'].
	>> código := [''].
	yo caracteres cada: { :i :carácter
		>> índice := alfabeto encontrar: carácter.
		>> rot13 := índice + 13.
		>> codificado := alfabeto carácter: rot13.
		código añadir: codificado.
	}.
	<- código.
}.
```

A partir de ahora, cada texto se puede cifrar de la siguiente manera:

```
Salida escribir: ['hola'] rot13, detener.
```

Un detalle curioso de ROT-13 es que cuando se implementa el cifrado por segunda vez,
el texto original vuelve a aparecer. De esta manera, el texto cifrado vuelve a ser
descifrado:

```
Salida escribir: ['hello'] rot13 rot13, detener.
```

Esto demuestra que el mensaje en:hacer: es uno de los principios más fundamentales
del lenguaje de programación XOScript. Nótese que sin este mensaje, que es parte del
objeto raíz Objeto , no sería posible ampliar las funcionalidades de los objetos.
Un segundo mensaje esencial es es-igual-a:, que devuelve Verdadero en el caso de
dos variables que apuntan hacia el mismo objeto, como:

```
>> x := 1.
>> y := x.
Salida escribir : (x es-igual-a: y), detener.
```

Observe la sutil diferencia entre = y es-igual-a: . El primero mencionado compara el
valor del contenido de dos objetos, mientras que el segundo mencionado examina la
memoria de la computadora para ver si son, de hecho, el mismo objeto.
El mensaje en-caso-de:hacer: permite ejecutar una tarea condicional, al igual que los
mensajes verdadero: y falso: . La diferencia es que puede adjuntar una tarea por valor.
El siguiente ejemplo, por ejemplo, muestra el valor en la variable x. Si el valor de x es
igual a 1, se ejecuta el primer bloque de código. Si x=2, se ejecutará la segunda tarea,
y así sucesivamente. De esta manera, selecciona el código correcto para el valor x:

```
>> x := 2.

x
en-caso-de: 1 hacer: {
	Salida escribir: ['Status: denegado'].
},
en-caso-de: 2 hacer: {
	Salida escribir: ['Status: pendiente'].
},

en-caso-de: 3 hacer: {
	Salida escribir: ['Status: aprovado'].
}.
Salida detener.

```


## Manejo de mensajes desconocidos

Si desea crear un objeto que muestre automáticamente en la pantalla todas las palabras
que le envíe (que tengan varios caracteres) en líneas individuales, podría escribir algo
como esto:

Salida Humpty Dumpty se sentó en la pared.

Puede lograr esto utilizando los llamados mensajes genéricos. Esta técnica le ayuda a
conectar una tarea a mensajes indeﬁnidos:

```
Salida en: ['responder:'] hacer: { :texto
	Salida escribir: texto, detener.
}.
```

La tarea que está conectada a responder: se ejecuta en cada mensaje desconocido.
Dado que el mensaje Humpty es desconocido, XOScript ejecutará internamente el
siguiente mensaje:

```
Salida responder: ['Humpty'].
```

Existen varias aplicaciones concebibles para los mensajes generales. Una de sus
principales aplicaciones es en combinación con el principio de uniformidad; es decir,
la traducción del software de XOScript a otros lenguajes técnicos. 

## Mensajes enviados mediante programación

En lugar de enviar un mensaje directamente a un objeto, también se puede enviar a
través de una variable. Para ello, se utiliza el mensaje mensaje:argumentos: Por
ejemplo, en el siguiente ejemplo, el resultado muestra 14
(de una manera muy elaborada):

```
>> a := (Serie ← 7).
>> b := ['añadir:'].
>> x := 7 mensaje: b argumentos: a.
Salida escribir: x, detener.
```

Especiﬁca el mensaje deseado como objeto de texto y los argumentos como serie. Un
mensaje que contiene dos parámetros (por ejemplo, entre: 0 y: 10), se especiﬁca
como entre: y:, por lo tanto, se combinan los componentes del mensaje:

```
>> a := (Serie ← 1 ; 10).
>> b := ['entre:y:'].
Salida escribir: ( Número mensaje: b argumentos: a ), detener.
```


# Series

XOScript conoce dos tipos de colecciones: series y listas. Las series son enumeraciones
de objetos en un orden ﬁjo. Las listas no tienen orden, sino que se parecen a una
leyenda que incluye una clave (o término) y su valor correspondiente. Las series son
comparables a las matrices o arreglos (PHP, Java, C) y las listas (Python). Las listas
son comparables a las matrices asociativas o arreglos asociativos (PHP) o a los
diccionarios (Python) en otros lenguajes de programación. Para crear una nueva serie,
escriba:

```
>> fibonacci := Serie nuevo.
```

Esta secuencia vacía se puede rellenar con adjuntar:

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

Este resultado revela que también se puede utilizar esta notación más corta para
declarar una serie:

```
>> fibonacci := Serie ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Este programa muestra el mismo resultado. Por supuesto, esta notación es mucho más
corta y, por lo tanto, mucho más
cómoda

La ﬂecha es un mensaje binario que crea una nueva serie y al mismo tiempo envía el
objeto subsiguiente para que se incruste instantáneamente en esta nueva serie. Los
puntos y coma (;) son todos mensajes binarios que colocan un valor en la serie.
Para averiguar la cantidad de objetos de una serie, use contar

En lugar de utilizar el punto y coma, se puede utilizar un símbolo de viñeta para añadir
algo a la serie. De esta manera, la lista se parece bastante a una de texto normal:

```
>> platos := Serie nuevo
~ ['Achicoria']
~ ['Coles de Bruselas']
~ ['Chucrut'].
```

Las series responden a mensajes como: adjuntar: , mínimo , máximo , cada: ,
anteponer: , unirse: , posición: , primero , último, penúltimo, poner:en: ,
toma-el-último , toma-el-primero , contar , desde:longitud: ,
reemplazar:longitud:con:: , por: , copiar , ordenar: , llenar:con: , y encontrar:
Otra forma de crear una serie es transformar una palabra en una serie de caracteres
dividir (es decir, dividir) un texto en una serie de palabras:

```
Salida escribir: (['abc'] caracteres), detener.

Salida escribir: (
['Chicory,Brussels sprouts,Sauerkraut']
dividir: [',']
), detener.
```

Por ejemplo, si el mensaje caracteres se envía a un texto, la respuesta será una serie
que contiene todos los caracteres separados de los que está hecho el texto. Cuando el
mensaje dividir: se envía a un texto con otro texto como argumento, el pequeño
fragmento de texto adjunto se utiliza para desglosar el texto recibido.

El texto en fragmentos de texto separados. La respuesta será una serie de estos objetos
de texto. A su vez, también es posible convertir una serie en un texto enviando el
mensaje unirse: , vea el siguiente ejemplo:

```
>> platos := Serie ←
['Achicoria'] ;
['Coles de Bruselas'] ;
['Chucrut'].
Salida escribir: (platos unirse: [' ~or~ ']), detener.
```

En este caso, el fragmento de texto adjunto se utiliza para unir los textos de la serie.
Cada objeto dentro de una serie tiene su propio lugar, que se denomina posición. El
primer objeto obtiene la posición 1, el segundo la posición 2, y así sucesivamente. Al
utilizar el mensaje posición: (o la versión más corta ? ) es posible recuperar el elemento
en la posición especiﬁcada:

```
Salida escribir: (platos posición: 3), detener.
Salida escribir: platos ? 1.
Salida escribir: platos ? 9.
```

En caso de que no haya nada en la posición solicitada, la respuesta será un objeto
Nulo. Hay tres posiciones especiales en una serie, que son sus valores: el primero,
el último y el penúltimo elemento.
Los objetos en esas posiciones se pueden recuperar utilizando los mensajes respectivos.

```
>> abc := ['ABC'] caracteres.
Salida escribir: abc primero, detener.
Salida escribir: abc último, detener.
Salida escribir: abc penúltimo, detener.
```

Para reemplazar un objeto en una posición especíﬁca dentro de la secuencia misma,
escriba: poner:en:

```
abc poner: ['2nd'] en: 2.
```

De manera similar, se puede eliminar un objeto de la serie utilizando el símbolo menos:

```
>> x := Secuencia ← 1 ; 2; 3.
Salida escribir: x, stop.
Salida escribir: x - 2.
```

Con el mensaje anteponer: es posible insertar un objeto al inicio de la serie:

```
>> x := Serie ← ['Nut'] ; ['Monkey'].
x anteponer: ['Apple pie'].
Salida escribir: x.
```

También es posible generar una serie rellenando una serie vacía con el mensaje
llenar:con: En caso de que se preﬁera rellenar de antemano con ceros las
puntuaciones máximas de un juego de ordenador,
escribir:


```
>> puntuaciones := Serie nuevo llenar: 10 con: 0.
Salida escribir: puntuaciones, detener.
```

También es posible copiar una serie:

```
>>copia := puntuaciones copiar.
```

Es posible quitar objetos de la serie cortando su inicio y ﬁnal:

```
>> palabras := Serie ← ['Tarta de manzana'] ; ['Nuez'] ; ['Mono'].
>> original := palabras copiar.
>> a := palabras toma-el-primero.
>> b := palabras toma-el-último.
Salida escribir: original, detener.
Salida escribir: a, detener.
Salida escribir: b, detener.
Salida escribir: palabras, detener.
```

En el ejemplo anterior, al utilizar el mensaje toma-el-primero , se elimina el objeto
inicial de la serie, que se coloca en consecuencia en a. Además, se elimina el último
objeto utilizando el mensaje toma-el-último, que se coloca en b. Como resultado, es el
objeto Texto del medio, “Nut”, el cual permanece. La copia original también se muestra,
demostrando así la función de copia.
El mensaje encontrar: permite encontrar información dentro de una serie:

```
>> pinturas := Serie nuevo
~ ['Fighting Temeraire']
~ ['Lady of Shalott']
~ ['Hay Wain'].

Salida escribir: ( pinturas encontrar: ['Hay Wain']), detener.
Salida escribir: ( pinturas encontrar: ['Lady of Shalott']), detener.
Salida escribir: ( pinturas encontrar: ['Sunflowers']), detener.
```

Al utilizar el mensaje cada:, es posible aplicar una tarea a cada elemento de una serie:

```
>> metros := Serie ← 1200 ; 4000 ; 6210.
metros cada: { :numero :metros
Salida escribir: metros / 0.3048 , detener.
}.
```

El ejemplo que se muestra arriba muestra una conversión de metros a pies. La tarea de
conversión se aplica a cada elemento individual de la serie. En el primer parámetro
( :numero ), la tarea recibe la posición del elemento que se va a manipular. En el segundo
parámetro ( :metros ), la tarea recibe el objeto que se coloca en la posición mencionada
anteriormente. Siéntase libre de nombrar los parámetros usted mismo, sin embargo, el
orden dentro de la tarea es ﬁjo. El primer parámetro es siempre el número de posición
y el segundo es el objeto.
Si se requiere el número más bajo, se puede enviar el mensaje mínimo. De hecho, si se
requiere el número más alto dentro de la serie, se envía el mensaje máximo.La siguiente
ilustración muestra una serie de puntajes de un juego. Se crea una nueva serie con dos
elementos que contienen los extremos de los puntajes:

```
>> puntajes := Secuencia ← 100 ; 50 ; 200 ; 350.
>> extremos := Secuencia ← puntajes mínimo ; puntajes máximo.
Salida escribir: extremos, detener
```

Esto da como resultado:

En una serie es posible ejecutar un reemplazo utilizando el mensaje
reemplazar:longitud:con
Por lo tanto, se puede utilizar para reemplazar un fragmento de serie por otra serie:

```
>> x := Serie ← 1 ; 2 ; 3 ; 4 ; 5.
>> z := Serie ← 9.
>> y := x reemplazar: 2 longitud: 1 con: z.
Salida escribir: y, detener.
```

La ordenación es una acción útil que se aplica con frecuencia a las series. Dado que
solo se ordenan las series, esta acción es única para este tipo de colección. Una serie
se puede ordenar enviando el mensaje ordenar: a un objeto Serie, junto con un
argumento que contiene una tarea de ordenación que incluye dos parámetros:

```
>> continentes := Serie nuevo
~ ['Oceania']
~ ['America']
~ ['Asia']
~ ['Europe']
~ ['Africa']
~ ['Antartica']
~ ['Australia'].
continentes ordenar: { :a :b <- a > b. }.
```

Salida escribir: continentes, detener.

La ordenación de mensajes: obtendrá de forma constante dos objetos de una serie
y, en consecuencia, solicitará que la tarea compare los dos. La tarea de ordenación
debe responder cada ronda con Verdadero o Falso.

En el fragmento ilustrado, los continentes se ordenan en orden alfabético comparando
cada par de palabras con el mensaje >. Para ordenar en orden inverso, aplique el
mensaje <.

## Estructura alternativa de mensaje

Supongamos que tiene una serie:

```
>> x := Serie ← 1 ; 2 ; 3.
```

Si desea eliminar el primer y el último elemento, su mensaje sería:

```
x toma-el-primero toma-el-último.
```

Desafortunadamente, la notación anterior no funcionará correctamente. El mensaje
toma-el-primero devuelve el primer elemento de la serie, que, a su vez, se convertirá
en el receptor del mensaje toma-el-último. Por lo tanto, el mensaje toma-el-último
no se envía a x, sino a 2. Una posible solución a este problema sería crear dos
setencias separadas, como:

```
x toma-el-primero
x toma-el-último
```

Sin embargo, esto es poco práctico, en particular cuando necesita eliminar más de dos
elementos.
Por lo tanto, XOScript ofrece una estructura de mensaje alternativa para este tipo de
situaciones. En las estructuras de mensajes alternativas, las respuestas de los objetos
se ignoran y obtendrá el objeto receptor como respuesta, una y otra vez. Una
estructura de mensaje alternativa se inicia enviando el mensaje hacer a un objeto y la
estructura de mensaje alternativa puede ﬁnalizar enviando el mensaje hecho. En el
ejemplo ilustrado, esto podría aplicarse de la siguiente manera:

```
>> x := Serie ← 1 ; 2 ; 3.
x hacer toma-el-primero toma-el-último hecho.
Salida escribir: x, detener.
```

Tenga en cuenta que para evitar sorpresas desagradables, siempre cierre con echo.
Vea lo que sucede en el próximo ejemplo:

```
>> x := Serie ← 1 ; 2.
x hacer toma-el-primero.
Salida escribir: x, detener.
```

El código anterior generará el mensaje de error: Debe responder con texto. La razón
de esto es que el mensaje de escribir: desea crear un texto de x; por lo tanto, envía
internamente el texto del mensaje. Como regla, se devuelve un objeto de texto como
respuesta, sin embargo, como la estructura de mensaje alternativa aún está activa,
se devuelve la serie en sí. Esto hace que el procesamiento posterior falle y XOScript
mostrará un mensaje de error.

# Listas

Tanto Serie como Lista son colecciones. Sin embargo, a diferencia de una serie, una
lista no tiene orden. Otra distinción entre las dos es que una lista consta de pares de
objetos. Un objeto actúa como entrada (o palabra clave) para buscar el otro objeto
(valor). Un buen ejemplo de una lista es una lista de precios, como:

```
>> menu := Lista nuevo
poner: ['£5'] en: ['tarta manzana'],
poner: ['£6'] en: ['tarta zanahoria'],
poner: ['£3'] en: ['algodón de azucar'].
```

Las listas pueden recibir los siguientes mensajes: tipo, poner:en: , entradas, valores,
en : , cada : , contiene: .
De manera similar a una serie, el mensaje poner:en: se usa para agregar un objeto a
una lista. La diferencia es que, a diferencia de una serie, se vinculan dos objetos. El
primer objeto es, de forma similar a una secuencia, el objeto que almacenarás en una
lista. El segundo objeto no es su posición dentro de la colección, sino la entrada (clave)
que permite recuperar el objeto anterior en un momento posterior. En resumen, una lista
funciona un poco como un diccionario; por lo tanto, al usar la palabra clave se puede
encontrar el signiﬁcado. Por ejemplo, para recuperar de la lista mencionada
anteriormente el precio de un dulce de azúcar:

```
>> precio := menu en: [’algodón de azucar'].
```

En este caso, también puedes usar la notación concisa:

```
>> precio := menu ? [’algodón de azucar'].
```

La respuesta mostrará £3.
Si las entradas (o claves) que aplicas para almacenar objetos no tienen espacios,
también se puede usar la siguiente notación:

```
>> menu := Lista nuevo
pastel: ['£5'],
tarta: ['£6'],
dulce: ['£3'].
```

Sin duda, la notación anterior se lee de forma más natural, porque se parece a una lista
que se usa comúnmente en un documento. Para solicitar el precio de un dulce, se puede
utilizar la siguiente notación simpliﬁcada:

```
>> precio := menu dulce.
```

# Archivos

El objeto Archivo responde a mensajes como: ruta, leer, escribir: , existe, eliminar,
tamaño y serie:.
XOScript permite la edición esencial de archivos. Para ello, utilice el objeto de sistema
Archivo.
En este ejemplo, un archivo de texto que contiene ['verduras olvidadas'] debe ordenarse
alfabéticamente:
Contenido del archivo verduras en la carpeta documentos:
Chirivía
Alcachofa de Jerusalén
Rábano de invierno
Nabo
Para imprimir el contenido de este archivo en la pantalla, escriba lo siguiente:

```
>> fichero := Archivo nuevo: Ubicación-del-archivo documentos verduras.
Salida escribir: fichero leer , detener.
```


Para ordenar el contenido y luego guardar la serie ordenada, escriba:

```
>> verduras :=
Archivo nuevo:
Ubicación-del-archivo documentos verduras ,
leer
dividir: ['↵'] ,
ordenar: { :a :b <- a > b. }.
Archivo nuevo:
Ubicación-del-archivo documentos nuevoficheroordenado ,
escribir: (verduras combinar: [’↵']).
```


Así, también en este ejemplo, se lee crea un archivo con (nuevo) despues se lee el
contenido, y se divide en líneas mediante el mensaje dividir: , como argumento
usamos el signo de nueva línea ( ↵ ). o tambien podemos usar el salto de linea
tradiccional en otros lenguajes de programación que es ( \n ) Para continuar, se ordena
según el método mencionado en capítulo 3. Finalmente, se guarda en el disco, después
de haber combinado las líneas en un solo texto.
Además de leer y escribir:, también se pueden manejar otros asuntos. Mediante el
mensaje adjuntar: , se puede agregar texto a un archivo, como en el siguiente ejemplo
Archivo nuevo: Ubicación-del-archivo documentos nuevoficheroordenado ,
adjuntar : ['Zucchini'].
La ubicación del archivo se puede recuperar con el mensaje ruta .

```
>> location := fichero ruta.
```

Para saber si un archivo existe o no, se puede enviar el mensaje existe después de lo
cual se devuelve un objeto Verdadero o Falso.

```
>> x := Archivo nuevo: Ubicación-del-archivo desconocido.
Salida escribir: x existe, detener.
```

Los archivos se pueden eliminar enviando el mensaje eliminar .

```
fichero borrar.
```

También se puede obtener el tamaño (en bytes):

```
fichero tamaño.
```

Para solicitar el contenido de una carpeta, se puede enviar el mensaje serie al objeto
Archivo como argumento la ubicación de la carpeta. Por ejemplo, si se solicita el
contenido de la carpeta documentos, se debe hacer:

```
ficheros := Archivo serie: Ubicación-del-Archivo documentos.
```

Como resultado, se devuelve una serie que contiene en cada posición una lista con las
entradas ﬁcheros y tipo que contienen el nombre del archivo y su tipo, en ese orden.

# Momentos

Para una representación estructurada de fecha y hora, XOScript utiliza el objeto Momento.
En caso de que se imprima un nuevo objeto Momento en pantalla, se muestran la fecha y
hora actuales:

```
Salida escribir: Momento nuevo, detener.
```

También es fácil leer los componentes de tiempo individuales. Así, por ejemplo, si solo es
necesario conocer el año actual, se puede enviar el mensaje año al momento y, a su vez,
la respuesta será un
objeto Número que contiene únicamente el año:

```
>> m := Momento nuevo.
Salida escribir: m año bruto, stop.
```

Tenga en cuenta que el mensaje bruto debe enviarse al objeto Número resultante. Esto
es para evitar la salida de 2,020 , que es, por supuesto, una notación correcta para
números, sin embargo, no se usa normalmente en el contexto de notaciones de años.
También es posible solicitar cuestiones que podrían ser menos obvias de determinar
al principio, por ejemplo, el día de la semana (usando el mensaje día-semanal ):

```
>> m := Momento nuevo.
Salida escribir: m día-semanal, detener.
```

Aquí, el número 3 representa el martes. Un día laborable siempre comienza el 1
(domingo), el lunes representa el segundo día, el martes el tercer día, y así
sucesivamente. El sábado es siempre el último día de la semana, según XOScript.
De la misma manera, se puede recuperar el número de la semana (semana), así como
los meses, días, horas, minutos y segundos. El siguiente ejemplo muestra cómo se
crea un nuevo objeto Momento y cómo se pueden recuperar todos los componentes
individuales de fecha y hora: el segundo, el minuto, la hora, el día,
el mes, el día del año (dia-del-año), el día de la semana (día-semanal) y la zona
horaria (zona).

```
>> ahora := Momento nuevo.
Salida escribir: ahora, detener.
Salida escribir: ahora segundo, detener.
Salida escribir: ahora minuto, detener.
Salida escribir: ahora hora, detener.
Salida escribir: ahora día, detener.
Salida escribir: ahora dia-del-año, detener.
Salida escribir: ahora día-semanal, detener.
Salida escribir: ahora mes, detener.
Salida escribir: ahora zona, detener.
```

Para cambiar uno de los componentes de tiempo, se envía un objeto Número. Por lo
tanto, para modiﬁcar el segundero a 13, se hace:

```
>> m := Momento nuevo.
m segundo: 13.
Salida escribir: m, detener.
```

También es posible conﬁgurar otros componentes de tiempo usando año: , mes: , día:
, hora: , minuto: , y segundo:

```
>> cuando := Momento nuevo
año: 2020,
mes: 12,
día: 31,
hora: 23,
minuto: 59,
segundo: 59.
Salida escribir: cuando, detener.
```

No es posible conﬁgurar ni cambiar el día de la semana ni el día del año.
Tenga en cuenta que los ajustes deben ser de mayor a menor; de hecho, conﬁgurar un
componente mayor borra los componentes menores. El siguiente ejemplo ilustra este
principio:

```
>> cuando := Momento nuevo
año: 2020,
mes: 12,
día: 31,
hora: 23,
minuto: 59,
segundo: 59,
año: 2021.
Salida escribir: cuando, detener.
Esto mostrará:
```

En este caso, los componentes de tiempo más pequeños vuelven a sus valores iniciales,
porque en el último momento se establece el año.
Si selecciona un número demasiado alto para un componente de tiempo, el reloj seguirá
contando de la manera habitual:

```
>> entonces := Momento nuevo
año: 2020,
mes: 2,
día: 30.
Salida escribir: entonces, detener.
El resultado será::
01/03/2020 00:00
```

En febrero nunca hay más de 29 días, por lo que el calendario cuenta desde el 1 de
marzo. En este caso,2020 fue un año bisiesto.
Si desea utilizar una notación diferente para la visualización del tiempo, simplemente
combine los componentes del tiempo libremente:

```
>> pantalla := ['día mes año'].
>> fecha := Momento nuevo.
pantalla
año: fecha año bruto,
mes: fecha mes,
día: fecha día.
Salida escribir: display, detener.
```

No olvides tener en cuenta las distintas zonas horarias para evitar sorpresas. La zona
horaria ( zona: ) en la variante británica de XOScript se mostrará como:

```
>> m := Momento nuevo.
Salida escribir: m zona, detener.
```


Al enviar el mensaje tiempo obtendrás la cantidad de segundos que han pasado desde
el 1 de enero de 1970. Este es un punto de referencia en el tiempo a partir del cual la
mayoría de las computadoras calculan la hora del sistema.

```
>> ahora := Momento nuevo tiempo.
Salida escribir: ahora, detener.
```

También puedes crear un nuevo Momento basado en una marca de tiempo como esta:

```
>> ahora := Momento nuevo: 0.
Salida escribir: ahora año bruto, detener.
```

Estas marcas de tiempo pueden ser útiles para compartir datos de tiempo con otros
sistemas. También se pueden utilizar para crear una descripción elegante del tiempo,
algo que se desea comúnmente en varios programas:

```
Momento en: ['describe'] hacer: {
>> ahora := Momento nuevo.
>> descripción := ['-'].
>> diferencia := ahora tiempo - yo tiempo.
{
(diferencia < 60) verdadero: {
descripción := ['ahora mismo'].
}, salir.
(diferencia < 3600) verdadero: {
>> minutos := (diferencia / 60) redondo.
descripción := ['hace algunos minutos'] algunos: minutos.
}, salir.
descripción := (
['día-mes-año']
día: (ahora día),
mes: (ahora mes),
año: (ahora año bruto)
).
} proceder.
<- descripción.
}.
>> m := Momento nuevo.
Salida escribir: m describe, detener.
>> m := Momento nuevo: (Momento nuevo tiempo - 1,500).
Salida escribir: m describe, detener.
>> m := Momento nuevo: (Momento nuevo tiempo - 5,000).
Salida escribir: m describe, detener.
```

Tenga en cuenta que en el ejemplo anterior, todo se coloca entre corchetes {},
seguido del mensaje proceder. Esta es una optimización para acelerar el programa.
Al colocar todo en un bloque de proceso, se habilita el uso del mensaje salir
después de cada condicional, para evitar que también se procesen condicionales
excesivos.
Para calcular los tiempos, simplemente sume cada componente de tiempo por
separado. Por ejemplo, en caso de que desee saber qué hora será dentro de una
hora:

```
>> m := Momento nuevo.
Salida escribir: m, detener.
m añadir: 1 hora.
Salida escribir: m, detener.
```

Vea cómo se aplica aquí un truco para mejorar la legibilidad: añadir: 1 hora. De
hecho, el mensaje hora se envía a 1, que es un caliﬁcador (explicado en el capítulo
3).
De la misma manera, puede agregar, por ejemplo, 100 segundos. No es necesario
concentrarse en la conversión a las unidades correctas, ya que el objeto Momento
lo hará por usted (usando el caliﬁcador).

Ahora, observemos un ejemplo más complicado sobre el uso de add: y subtract::

```
>> entonces := Momento nuevo
año: 2020,
mes: 2,
día: 29,
hora: 23,
minuto: 59,
segundo: 59,
restar: 1 segundo,
añadir: 2 segundo,
restar: 9000 hora.
Salida escribir: entonces, detener.
```

Para crear una copia de un momento, haga lo siguiente:

```
>> entonces := Momento nuevo.
>> ahora := entonces copiar.
Salida escribir: entonces = ahora, detener.
Salida escribir: (entonces es-igual-a: ahora), detener.
```

En el ejemplo anterior, se crea una copia del momento entonces. Ambos momentos
describen el mismo punto en el tiempo, por lo que = da como resultado Verdadero.
Sin embargo, tenga en cuenta que sigue siendo solo una copia, no el original. Debido
a que físicamente es, de hecho, un objeto diferente, en una ubicación diferente en la
memoria de la computadora, el mensaje es-igual-a: solo puede dar como resultado la
respuesta Falso.
Una característica adicional del objeto Momento es detener momentáneamente el
proceso. Puede pausar la ejecución del programa utilizando el mensaje esperar:
seguido del número de segundos. Eche un vistazo al siguiente ejemplo para ver una
breve ilustración de este principio:

```
>> antes := Momento nuevo.
Momento esperar: 2.
>> después := Momento nuevo.
Salida escribir: antes, detener.
Salida escribir: despúes, detener.
```

Después de 2 segundos, el fragmento de programa anterior mostrará el resultado
de dos momentos: el momento grabado antes de la pausa y el momento grabado
después de esa pausa. Como resultado, las descripciones de tiempo en su
pantalla deberían mostrar una diferencia de 2 segundos.

# Programa

En este capítulo se describe el objeto Programa, y este es el último objeto que se
revisará en la serie de objetos básicos del sistema. La función básica del objeto
Programa es comunicarse con el mundo exterior, de manera similar al objeto Archivo
y al objeto Salida. Estos tres representan la puerta de entrada al mundo exterior.
Además, este objeto contiene una serie de funciones que beneﬁcian la administración
avanzada de la memoria. También puede cargar otros programas de XOScript utilizando el
objeto Programa. Para combinar varios programas de XOScript, puede enviar el mensaje
utilizar: . En este ejemplo, hay dos archivos de XOScript, que se denominan herramientas
y programa:
Contenido de herramientas:

```
>> Herramienta := Objeto nuevo.
```

Contenido del programa:

```
Programa utilizar: Ubicación-del-Archivo heramientas.
Salida escribir: Heramienta tipo, detener.
```

Al ejecutar el programa XOScript titulado programa, se cargará el código del archivo
heramientas gracias al mensaje utilizar:

De esta manera, puede incluir el trabajo de otras personas en su propio programa y
hacer uso de la funcionalidad proporcionada por bibliotecas externas.
Durante la ejecución del código incluido, el directorio de trabajo se cambiará a su carpeta
principal.
Puede ejecutar comandos del sistema desde XOScript, enviando el mensaje sistema: a
Programa. Esto le permite, por ejemplo, copiar archivos, reubicarlos o invocar otro s
oftware para ejecutar tareas especíﬁcas. En un sistema Linux, por ejemplo, puede
aplicar el siguiente paso para mostrar los archivos en la
carpeta actual:

