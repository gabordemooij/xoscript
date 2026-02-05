# Basics

{{messages}}

Welcome to xoscript. xoscript is a simple scripting language (for server-side
scripting). Simple does not mean easy. Those two concepts are often
confused. It may still be very complex to install and setup xoscript on
a server, but this complexity arises from the fact that most servers or
cloud services need to be configured to use xoscript (for instance through
CGI and a webserver). You cannot just drop xo-files on a random
budget vps that you bought, you have to configure it yourself (or
let somebody do that for you). That's just how things
work, we cannot change that. That being said, xoscript *is
actually very simple* as a language. It only has about 5 syntax rules:
assign, message, function, return and chain (to send multiple messages).
That's it. Any software developer should be able to learn the basics
within minutes. This manual is somewhat extensive because it covers
every little detail, but in essence the manual is quite short compared
to many other programming languages.

The architecture of a xoscript server setup
is also very simple, yet flexible.

{{architecture.png}}

To use xoscript as a server language, you need to install the
server plugin in a folder called /mods/server. 

This is because we like to
decouple the core language from server specific functionalities,
unlike for instance PHP or Python. Otherwise we would have to ship the
complete kitchen sink for no purpose to everyone, which is just silly.
You can install other modules if you want as well. The system is very
flexible.

Also some functions are better implemented in the scripting language
itself like templating and session handling, so additionally we
ship the template.xo and webtools.xo libraries for your convenience.
The reason for all this is that we don't know how you want to
use xoscript. You can use it as a server-side scripting language,
but also for GUIs, embedded devices or just batch processing.
Even if you use it as a server-side scripting language (which is
currently one of the primary use cases), you might still want to
use a different template engine or a different session handler.
Who are we to decide that you should use ours?

One of the advantages of using our own template engine is that
you don't have to learn additional syntax to create templates though.
The default template engine that ships with xoscript uses 100%
separation between presentation and logic. Instead of special
template syntax, it simply uses a very flexible slot marker system.
For more information, see the Server chapter.

Note that, if you don't want to use the default template engine or
the default webtools, it goes without saying that you have to provide
your own.

If you run your webserver in a chroot, jail or other kind of sandbox,
you also need to install the depencies of xo in that environment, you can
see which libraries you need by using ldd (see the manpage of Linux or BSD).
If you want to use shell commands in your xo-scripts, also copy a shell
(like bash or ksh) to this environment.

We also like to note that we take backward compatibility very serious.
There is even a special backward compatibility feature available called
'version'. In general, we aim to make your code run forever. So, you will
never have to update your code to remain compatible with newer versions
of xoscript. Our goal is: write once, run forever.

The remainer of this manual is dedicated to explaining the programming
language xoscript in detail. Server-scripting is discussed in the chapter
called Server. If you are an experienced software developer, you might want
to skip a few chapters because some of them are a bit too detailed or
are very similar to general programming practices. So for those of you
who are already have experience with several other programming languages,
you better treat this manual as a reference guide.

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
&lt;VirtualHost *:80&gt;
    &lt;Directory /var/www/html&gt;
        Options +ExecCGI
        AllowOverride All
        AddHandler cgi-script .xo
        Require all granted
    &lt;/Directory&gt;
    DocumentRoot /var/www/html
&lt;/VirtualHost&gt;
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
./example.sh &lt;name&gt; &lt;Linux/Win64&gt; [clean]
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
gmake -f makefile.obsd clean
ISO="en" gmake -f makefile.obsd
```

To build the server plugin on Linux:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

To build the server plugin on OpenBSD:

```
PACKAGE="server" NAME="server.so" gmake -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" gmake -f makefile.obsd plugin
```

## Hello world

After it has been transferred to your computer, you can extract the file
and start xo by using the following command:

```
xo
```

To run a Xoscript, store the program as a file by adding -xo
suffix (optional). In addition, insert the file name of your program
after the Xoscript command:

```
xo myprogram.xo
```

When you run a Xoscript command while using your program file as a
parameter, xo will read and execute your program file.

{{note}}
You can also start your program by dragging it to the xo pictogram.
{{/note}}

{{warning}}
On some systems you need to allow xo permissions to load dynamic
libraries beforehand.
{{/warning}}

Tradition dictates that the first program in any new programming
language should be a kind of salute to the world. In Xoscript, such a
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

Xoscript is a *pure* *object-oriented* programming language. This means
that xoscript perceives everything to be an object, therefore there are
no other *data types*. There are essentially three basic routine actions
in a program that is written in Xoscript: *assigning*, *sending messages*
and *responding*. Exchanging messages between objects is the key part of
a Xoscript program. The three individual routine actions are illustrated
below:


Action          | Example
--------------- | --------
assign          |  \>\> x := 1. 
unary Messages  | x even?.
binary message  | 1 + 2.
keyword message | x from: 0 length: 10.
answer          | <- answer.  


This chapter will give you a general impression of the language Xoscript
and describes its basic principles. Xoscript is a small language and
founded on three actions (see illustration) which translate into
approximately six grammar rules. That is all it takes to master the
language.

No worries if things are not instantly obvious to you: all building
stones will be explored in the next chapter (3) and the basic rules will
be repeated. Current chapter, however, serves mainly as a general
introduction to the language. The basic principles will be briefly
explained and illustrated by several relevant examples. Any missing
details will be outlined at a later moment.

Comments in Xoscript are prefixed with a \# symbol. So the following line
will be ignored:

```
# this is just a comment
```

## Variables

To assign
a variable you use the variable declaration symbol: >>. The name of a
variable may contain all signs except for: <-, :=, whitespaces,
periods, commas, colons, quotation marks [' '], and parentheses ().
Furthermore, a variable cannot consist of multiple lines. Please note
that a variable cannot begin with a number or a minus sign.

These are examples of valid variables:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dollar'].
>> +plus := True.
>> user-password := ['Pssst!'].
```

Invalid variables are for example:


```
>> -123 := ['negative number'].
>> password of user := ['Classified'].
>> password.of:user := ['Classified'].
>> ,x := 10.
```

{{note}}
You do not have to escape any character
(including quotes, double quotes, string
boundaries) in
a string literal as long as it does not
cause ambiguity for the lexer.
{{/note}}

After a variable has been declared, it can be used freely. This means
that it is only necessary to use the declaration symbol the first time
you use the variable (the declaration).

To be more specific, you cannot randomly start to declare a value to
your variable *(x := 2)*, as you must first declare the variable *(\>\>
x := 2)*. However, once declared you are allowed to change its value
without using the declaration symbol*(\>\> x := 2. x := 3.)*.

Note that it is mandatory to assign a value to a variable at the time of
declaring. Contrary to other programming languages, you are not allowed
to declare a variable without value. It is essential to explicitly tie
each variable to an initial value. Nonetheless, feel free to initialise
the variable with the **None** object. In this case, the variable can be
regarded as being empty *(\>\> x := None.)*. In short, to declare a
variable without an initial value is not allowed. So,

```
>> x.
```

is invalid and will give an error message.

{{note}}
xoscript uses dynamic scoping of variables, for
details consult the chapter Functions.
{{/note}}


## Literals

Xoscript perceives everything to be an object; i.e., all numbers, texts
and code fragments. Numbers, such as 1, 2, 100, -999 and 1,234 are
Number objects. All texts between single quotation marks are String
objects. All code fragments grouped between curly brackets {...} are
Function objects.

Literal         | Root object  | Example
--------------- | ------------ | ----------
numbers         | Number       | 1,2,3... 
strings         | String       | \['hello'\]
function        | Function     | { 1 + 2. }.
                
     
Objects such as numbers and strings, always find their origin in a root
object. For example, all numbers derive from the object **Number**. All
strings derive from **String** and all code fragments from **Function**. In
turn, all these objects stem from **Object**, which is, in fact, the
root object of all objects.


## Messages

Programming in Xoscript basically means
sending messages to objects. The general notation to send a message to
an object is as follows:

```
&lt;object&gt; &lt;message&gt;
```

To find out if the number **2**, for example, is an even number, the
message **even?** is sent to object **2**:

```
2 even?
```

The answer will be **True** (again, an object). Unknown messages are
usually ignored by objects; so no error will occur. Some objects (e.g.,
numbers or strings) respond to an unknown message in a predefined way
(more on this subject later).

An object can receive three kinds of messages. 

Type            | Number of arguments
--------------- | -------------------
Unary           | 0      
Binary          | 1     
Keyword         | 1+    


First, there are **unary
messages**, see example above, which are without arguments. Second,
there are **keyword messages**, which have one or multiple arguments,
for example:

```
>> x := Number between: 1 and: 10.
```

In this case the message **between:and: ** is sent to **Number**, which
is the root object of all numbers. The result will be a random number
between 1 and 10. Finally, there are **binary messages**, which have
only one character and one argument:

```
2 + 3
```

This looks like a math sum, but it actually just another message. The
message **+** is sent to **2**, with argument **3** which will return
answer **5**. Binary messages are allowed to be written without a colon.

Binary messages can be chained:

```
>> x := 3 + 2 - 1.
```

In this fragment **+ 2** is first sent to **Number** object **3**, which
results in Number object **5**, after which **-1** is sent to this
number. Observant readers are correct to notice the discrepancy which
this protocol shows regarding the conventional mathematical sequences of
operators. Xoscript ignores the mathematical sequence in favour of
consistency in its message system. As a result, the sum:

```
2 + 3 * 5 = 25
```

not 17.

This is by design. Parentheses can be used to modify the sequence order:

```
2 + (3 * 5) = 17
```

Most objects return themselves as a result in response to a certain
message. This is helpful as it encourages further dialogue with this
object by sending it a follow-up message:

```
Out write:
[' hello '] trim upper.
```

```
HELLO
```

Here, two messages are sent to the **Text** object: **trim**, followed
by **upper**.

In the following fragment, the use of a comma is necessary to indicate
that a new message is incoming. If not, Xoscript will get confused.

```
Out write: ['Hello!'], stop.
```

First, the message **write:** is sent to the pencil symbol followed by
**stop**. Without the comma, Xoscript would think that you wish to send
**stop** to **string** **Hello!**, a futile exercise.

The process sequence of messages is as follows: from left to right;
start with messages in parentheses followed by unary messages. Next,
binary messages and then end with keyword messages. See the example
below:

```
Out write: 0.5 round + (2 - 1), stop.
```

Xoscript always reads from left to right: first, the message **write:**
is sent to Out and is followed by the **stop** message. Within the
argument itself, Xoscript reads from left to right, so **0.5 round**
then **+**.

{{note}}
The stop message adds a newline character to the string.
The name of this message is inspired by telegraph systems.
Messages in telegraph systems 
often used the word STOP to mark the end of a sentence
(since punctuation was unreliable or costly).
{{/note}}

Moreover, **round** takes precedence over **+**, because it is a
**unary message**. Given the parentheses, **2 - 1** is calculated
first, after which **1** is added to the result of **0.5 round** (1).

The whole process will give the result **2**, which is also the written
answer. After the comma follows the stop message, which moves the cursor
to a new line. Of course, the best way to fully comprehend the sequence
order of Xoscript programs is with practise.

It is worthy to note that in Xoscript, contrary to many other programming
languages, whitespaces are a fundamental part of its syntax. In
particular when it comes to binary messages, whitespaces may cause some
confusion. Always use a whitespace after a binary message. You cannot
directly attach a number to the message, for example: 

```
3 + 2
```

different from 

```
3 +2
```

The first example (**3 + 2**), sends the
message **+** to the number **3**, with argument the number **2**. The
result, in this case, will be **5**. In the second example (**3 +2**) ,
the unary message **+2** is sent to number **3**. Depending on the
context that might yield a very different result.

## Non-existing methods

Sending a message to an object invokes the function that has been
attached to this object under that message name. If you send a message
that is not understood, the receiving object will ignore your message
and return a reference to itself instead for further communication.
This is called tolerant message passing.

Example:

```
Out write: Object blah, stop.
```

This will not give an error. It will simply print the text **Object**.


## Control Flow

In Xoscript there is no need for separate grammar rules for *loops* and
*ifs*. An if-statement is just a simple **true:** or **false:** message
to either a **True** object or a **False** object:

```
2 even? true: {
	Out write: ['Two is an even number'], stop.
}.
```
In the previous example, the message **true:** is sent to **True**, (the
answer to the question: is 2 an even number?) As argument an additional
fragment of code is sent along: a **Function** object. This function writes on
the screen that 2 is, in fact, an even number.

There is no need either for separate writing rules for a *loop*. To
execute a fragment of code three times, simply send **\*** with argument
**3** to that **Function**:

@test5

In this code fragment **i** is the index. So the first time the Function
is executed, **i** equals 0, the next time it gets executed, **i** = 1 and
so on.

Let's consider another example. When a conversion table needs to be
printed from *kJ* (kilojoule) into *kcal* (kilocalorie) by steps of 100,
see below for the correct notation:

@test599

Here, the number of the current line is transmitted to the parameter
**:line**. At the beginning of a function, the function parameters are being
defined. Unused parameters remain empty (**None**). Parameters are
always placed at the start of the function, directly after the initial
curly bracket and are preceded by a colon.

The message **while:**, is a combination of a *loop* and a *condition*.
Two functions can be linked using the **while:** message. The receiving function
will continue to run until the function after the colon will give a negative
result. Example:

@test600

In the above-illustrated code fragment **1** is added to **x** as long
as **x** is less than **5**. When this is no longer the case, the second
function will answer with **False**, consequently, the execution of the
first function will end. Note that **x** has been defined outside the
function and is a global variable. To learn more about scoping rules,
consult the chapter about Functions.

## String interpolation

The *kJ/kcal* list could be made more
presentable. Preferably, the list would be as follows:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

When you convert the preferred output into a template, its notation
could be:

```
number1 kJ ➞ number2 kcal
```

This means that **number1** stands for kJ-value and **number2** for
kcal-value. This is how string interpolation operates in Xoscript. There
are no separate grammar rules needed for this in Xoscript. Simply send
the word that needs to be replaced to the text with the substitute text
as argument:

```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

The result:

```
100 kj ➞ 23.9 kcal
```

This substitution rule works for each undefined message that is received
by a **string** object. Each message that is not recognised by the
**string** object, will be interpreted as follows: *replace the message
text with the text within the message argument.* You can adapt the
program as follows:


@test601


To avoid confusion about which message can or cannot be used as a
substitute, it is best to introduce a template marker like &lt; &gt;
for text segments in the template that
need to be replaced.

## Return values

To answer a message the return arrow
(*<-*) is used. The following example illustrates how to create a task
to compute a percentage:

@test602

After the task has been defined and assigned to variable **percentage**,
the message **apply:and:** is sent with arguments **100** and **7**.

This will execute the task applied to **100** and **7**, i.e., 7% of 100.
Using the return arrow, the answer is returned from the task back
to the main program.

## Extending

Although this code is valid, it has a disadvantage
because the sequence of the arguments has to be remembered. So, why not
write it like this: *7 percent of: 100 *? That would look a lot more
*natural*. To make this possible, we have to adapt the parent object of
**7**, which is the **Number** object, so that it will understand the
message **percent of:**. This can be achieved by sending **on:do:** to
the Number object, like so:

@test603

As the percentage is, in this case, the number itself, we refer to self,
the *self* keyword. In short, the symbol self signifies: *send this
message to myself*. 

# Objects

{{messages}}

Besides adjusting and expanding existing objects, you can also create
new objects yourself simply by sending the message **new**. Suppose you
would like to create an invoice object that enforces a numbering
sequence, in that case, you will first need an invoice object.

Knowing that each object derives from another object, which, in turn,
eventually originates from the root object of all objects called Object,
a choice needs to be made regarding on which of those other objects your
new object will be founded. Your new object inherits all properties of
the object on which it is founded, so, to which the **new** message
initially was sent.

In this example a rather neutral object is preferred, one without too
many inherited properties. This offers an easy choice, because in that
case the new object can be based on the root object itself which is
**Object**. The notation of the intended invoice system will then be as
follows:

@test604

The current invoice number is stored in the object, this is why there is
a **own** keyword placed in front of it. This is called a *property*;
more details will follow.

Some businesses prefer to have the year incorporated into the invoice
numbers. In this case, you can create a new invoice object founded on a
former invoice object, but which offers the possibility to its user to
enter a specified year:

@test605

There is no need to write the implementation for the message **number**
again, as it is inherited from the previously written **invoice
object**; consequently, old code can be reused. Xoscript lacks concepts
such as classes and other related concepts. This means that objects can
solely inherit from other objects, also known as *prototypical
inheritance*.

Now, to get back to properties. Object properties can only be approached
from *within the object hierarchy*, so these properties
cannot be perceived by other objects.

Contrary to other programming languages, all properties of objects are
exclusively visible to the object that has created the property and to
derived objects. 

A commonly used technique is to use an object as a kind of *blueprint*,
which is, for instance, the case with the invoices discussed earlier.
Another good example is the **Point**. Let\'s say that you create a
computer program that makes calculations by using points on a map. You
can develop the object **Point** containing the properties of an
x-coordinate and a y-coordinate, which will be made available to the
external world through messages:

@test606

The **=** message compares the two points using the message **and:**. The
first comparison results in a **True** or a **False**. These are boolean
objects. When you send the message **and:** to a True object, and the
argument object after de colon is equally **True**, then you will
receive as answer again **True**. When either one is **False**, you will
receive the answer **False**. Note that one point cannot read the coordinates of the
other one. It is necessary to send a message to the other point to ask
for this data: **x-coordinate** and **y-coordinate**. After all, as has
been explained already, properties are solely retrievable from within
the object family itself. 

Note that the message **=** is used here to execute the point
comparison. Equally, a different message could have been used, such as:
**is:** or **equal:**, however reusing the **=** character seemed
appropriate in this case.

## Inheritance

You can reuse previously written code to create a hierarchy
of objects. For example:

```
>> Animal := Object new.
>> Dog := Animal new.
>> Poodle := Dog new.
```

In this case, **Dog** inherits all the behavior and properties
of **Animal** and, in turn, the object **Animal** inherits all behavior of
**Object**, the root object of all objects.


## Overriding


In the following example a new kind of list is created:
**Combination**, in which each element is ensured to be unique. The
functions of the **Sequence** are re**used** through inheritance:

@test607

Observe how the second **red** is excluded from the sequence.

Occasionally, it may be necessary to override a behaviour of an object.
For instance, when adding numbers and units of measurements have to be
taken into account. In the following example the object **Size** is
created. This object returns a number which, during the addition, takes
into account the unit of the number to be added. The **Number** object
checks whether it is about *inches* or *foot*. The programming code
could resemble the following:

@test608

## Recursion

In the previous example, the plus **sign** is being overridden. Note
that eventually the final addition still has to be done, which, in fact,
takes place on the following line:

```
>> answer := self + (number x factor).
```

Now, how does Xoscript understand that this plus **sign** refers to
the original logic of addition?** For instance, another interpretation
could be that Xoscript will repeatedly send the same message to the same
object which, in turn, would result into an **endless loop**. Clearly,
this is not the intention. As soon as you send a message to an object,
which would **execute** the **exact** **same code, Xoscript will realise,
in this case, that the underlying, overridden message is meant. So, your
program will automatically be safeguarded against this form of endless
loops. However, when it is indeed your aim to run the same function from the
current function, it will be necessary to first send the message
**recursive**. In this case, the result will be an infinite
loop. **However there are useful applications for recursive tasks, f**or
instance, suppose that you want to calculate the factorial of a given
number. In that case, simply add the message **factorial** to
Number:

@test609

This calls for recursion. In fact, the task that is connected to the
message **factorial**, needs to be executed again within that function.
So, it is necessary to invoke the factorial function from within the
factorial function itself. As a rule, Xoscript will prevent this routine,
because of the risk of ending up in an infinite loop. For this reason,
it is vital to precede the message by the word **recursive**. This
is done in order to make Xoscript aware of the fact that it is your
intention to execute the same task, and that you did not make mistake.

## Class-like Objects

Although xoscript does not offer classes, mimicking class-like
behavior is trivial. Simply override the new message.

```
>> Animal := Object new.
Animal on: ['new'] do: {
	&lt;- self new init.
}.

Animal on: ['init'] do: {
	own sound := ['?'].
	own legs  := 4.
}.
```

In the code fragment above, we create an object called Animal.
This object serves as a *blueprint* for all kinds of animals
like dogs and cats. The parent object Animal is written
with a capital A to signify that this is a class-like object.
Next we override the new message by writing our own new-method.
In this case it sends a message new to self, followed by the message
init. Because xoscript blocks recursion by default this won't cause
an infinite loop. Instead, it will send the new message to the parent
object (Object) resulting in a new instance of Animal. So we create
a new object, based on the same object we created our new-method for.
This is perfectly valid. Now we also send the message init, this ensures
that the Animal object has default values for its properties. By default
an animal has 4 legs and the sound is unknown (hence the question mark).
To create a new instance of our Animal, we could simply say:

```
>> a := Animal new.
```

Now we get a new instance of Animal with 4 legs, unknown sound and
an init method. Just like in other OOP languages we can also
extend our Animal:

```
>> Dog := Animal new.
Dog on: ['init'] do: {
	self init.
	own sound := ['barks'].
}.
```

We can test this easily by adding a string method:

```
Animal on: ['string'] do: {
	&lt;- own legs string + own sound.
}.
```

Let's put it all together:

@test13


Creating an object that is set in a given initial state, presents a
frequent issue. Suppose an object **Rectangle** has to be created,
in order to calculate perimeter and area. A possible notation would be:


```
>> Rectangle := Object new.

Rectangle on: ['area'] do: {
	<- own length * own width.
}.
```

Obviously, setting a length and width is a precondition. For that
purpose, the messages **length:** and **width:** can be added:


```
Rectangle on: ['length:'] do: { :length
	own length := length.
}.

Rectangle on: ['width:'] do: { :width
	own width := width.
}.

```

This rectangle can then be utilised as follows:


```
>> rectangle := Rectangle new length: 2, width: 3.
Out write: rectangle area.
```

However, if the initial settings of length and width are overlooked,
an error message will occur:

```
>> rectangle := Rectangle new.
Out write: rectangle area.
```

will produce the following error:

```
Key not found: length
```

In order to prevent this, it is preferable that a rectangle should
always have an initial length and width, for example 0. So, in this
case, it is necessary to **override** the message **new**.

@test610

If we override the new-message we are basically mimicking a **class**.

The world of Xoscript is filled with a diversity of objects, which are
available to your program right from the start. In the next chapters,
all of these core objects will be discussed.

# None Object

{{messages}}

The None object
represents emptiness, or better still, the absence of information. On
occasion, you will receive this object as an answer to a message, in
case of the result being **nothing**. The most essential question
you could ask the **None** object is: **None?**. The
answer will always read **True**.

```
Out write: None None?.
```

result:

```
True
```

Any object other than **None** will reply with **False**. The
above code fragment may seem a bit philosophical, yet the **None**
object certainly has extremely practical applications. For example, you
will receive the None object as an answer in case you ask for a
sequence element that does not exist. You could also use the None object
if you like to declare a variable, but do not want to specify a value
yet. Instead, you just **assign** the special value **None**. In
Xoscript it is not allowed to declare a variable without value, such as:


```
>> value.
```

Instead, you have to write the following:

```
>> value := None.
```

@api_None_base



# Booleans

{{messages}}

Contrary to most popular programming languages at the moment of writing,
Xoscript provides for only one single True object and one single False
object. To clarify, each time you write, **True** it does not imply that
a new object has been created. Instead, you always use a reference. This
means that when you write the following:

\>\> x := True.

The **x** refers to the **True** object. Conditional code and loops also
verify this reference. In Xoscript, the meaning of **True** and **False**
is not fixed. In fact, a Xoscript program gets pretty shaken up over a
statement like this:

True := False.

The result of such actions is undefined, however it remains a valid
action and therefore formally allowed. Furthermore, there is a Boolean
object, which is the root object of both **True** and **False**, as both
are derivatives of the root object. The Boolean object itself, however,
does not provide any practical application.

## Gotchas

Be careful with using **and:** and **or:**

```
Out write: (False or: True or: True), stop.
Out write: (False or: True, or: True), stop.
```

Yields

```
False
True
```
because the message **or:** only takes 1 argument. The first message
sends **or:or:** to False, which does not exists, so the object ignores
the message and returns itself (False). On the other hand, the second line
sends **or:** followed by another **or:** (using a chain symbol, i.e. a comma: ,).


@api_Boolean_base


# Numbers

{{messages}}

Each time you write a number, for example 9, -10, or 3,12, behind the
screen, Xoscript will convert these numbers into a **Number** object. You
can send messages to this Number object, or you could assign the number
to a variable and send messages afterwards:

```
10 even?

>> tenner := 10.
tenner even?

```

Both notations are valid. The Number object responds to the following
messages...

Most of these messages are self-explanatory and allow you to execute
mathematical operations or comparisons.

{{note}}
Note that you may use ≤ ≥ ≠ × and ÷ instead their ASCII counterparts.
This is a matter of preference.
{{/note}}

The difference between binary mathematical messages (+) and
their keyword variations (add:) is that the former will return
a new number, which is the result of the operation, whereas with the
latter the object itself will be modified. This is illustrated in the
following example:

@test597

In the above example, b = 4 and a = 3. With **add: 2** the value
of a is raised by 2, while **+ 3** creates a new number that is
equal to a + 3. The same applies to other mathematical processes, e.g.,
multiplications. By using the multiplication symbol, you will receive a
new object as answer. In case you use the message **multiply-by:**,
you will multiply the number itself.

With the message **between:and:**, for example in: **Number
between: X and: Y**, you will get a number between X and Y. In this
way, any random number can be generated:

```
>> a := Number between: 1 and: 10.
Out write: a, stop.
```

As of version 1.4, the build-in generator of random numbers in xoscript is
crypogrpahically secure to the best of our knowledge.

You can attach a **qualifier** to a number, for instance, **6
apples**. Each message that does not get recognised by a
number will be considered a qualifier. You can retrieve the qualifier of
a number by means of the message qualifier:

A qualifier is basically a Text object that is stored with the Number
object. The qualifier is also printed after the number on a
**write:** assignment. Qualifiers could be used to add amounts
in mixed currencies for example. On adding the amounts, you can ask
for the qualifiers. The following program example illustrates this
principle by using a historical currency calculator (as the exchange
rate remains reasonably stable!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base


# Strings

{{messages}}

Each time a text is placed between **blocks and quotation marks** ['...'] ,
Xoscript will create a new stringobject for you. However, make
sure to use the correct quotation marks. The quotation mark at the
beginning of the text differs from the one at the end (this allows you
to use the single quote without needing to escape it).

## UTF8

Strings in xoscript usually contain utf8 encoded text. Although
it's technically possible to have binary or non-utf8 content in
a string, it is recommended to use blobs for that. Blobs are
provided by the server plugin (see chapter ffi).
In general blobs/ffi are provided
on a plugin/platform basis, since they tie into the platform
and architecture (ffi/blobs). The core of the scripting language tries to
remain as platform agnostic as possible.

## Casting

You can create a copy of each object
with a different type by using the following messages:

Message | Result
------- | ------
number  | Converts an object into a number
text    | Converts an object into text
bool    | Converts an object into a boolean object (True or False)
  
The following rules **apply**:

message  | None      | Bool               | Number                | Text      | Other              
-------- | --------- | --------           | --------              | --------  | --------
bool     | False     | n/a                | 0→False else→True     | True      | Mostly True
number   | 0         | False→0 True→1 | n/a                       | ['n']→n | Mostly 1
string   | ['None']  | ['False']/['True'] | ['n']                 | n/a       | Depends

## Copying

Values in Xoscript are always passed **by reference**. In other languages
it depends on the type of value, in Xoscript there is only one way,
by reference. Xoscript never makes a copy of a value. To copy an object,
you need to send the message **copy**. 

@test611

Here, you might have expected that the output would be Dolly, instead
of Donny. However, this is not the case as both names refer to the same
object. When working with a loop, something similar occurs:

@test612

In fact, Xoscript **always** uses references, so on **:quantity**
the above-illustrated loop also indicates the reference to the element
in the sequence.

In order to copy an object, you have to specify this action
**explicitly**:

@test613

By sending the unary message **copy** to a string, the object
returns a copy of that same string object. It is possible to copy Number
objects, boolean objects, lists and dicts in the same way.

You can also define your own copy implementation, this is even a
neccesity if you create your own objects. The default
implementation of copy for a list makes a shallow copy, it creates a
new list with the same elements.

@test614

In this case, 4 is added only to the copy.
However, because the copy is shallow, the objects in both sequences
are the same.

@test615

So if we append 2 to each name in the copy, the original
sequence is affected as well.

To remedy this we need to make a **deep copy**. Such a copy action
for a list could be composed as follows:

@test616

Also, note the message recursive, this message is necessary to
send before the copy message.

It is essential to keep in mind that although a copy of an object
often has the same appearance of the original, it will, in fact,
never be the same. The root object defines a message **equal:**,
which can be used to compare the identity of objects. Take a look at the
following example:

@test617

## Implicit Conversion

Xoscript uses **implicit conversion** to convert objects. To print a
list on screen, Xoscript will, for example, send the message
*string* internally to the list. This can proof very useful, in
case you would like to print a sequence as a comma-separated list. The
message *string* can be overwritten: 

@test620

@api_String_base


# Functions

{{messages}}

You can group code between { and }, it then becomes a function.
In xoscript we also use the term task sometimes or simply
block of code.

You can run a function by sending the message *start*.


```
{ Out write: 123, stop. } start.
```

If your function takes arguments, use **apply:**.

```
{ :a Out write: a, stop. } apply: a.
```

Also see the examples below.
Because of the simplistic architecture, a function can only have
one point of return. To avoid overhead or excessive nesting for
conditions, you can use a procedure (which is the same as using 
multiplication sign with argument 1):

```
{
  (a = 1) true: { x := 1. }, break.
  (a = 2) true: { x := 2. }, break.
} procedure.
```

This way, (a = 2) will not be evaluated if a = 1.
Also, you don't need nested true-messages this way.
Whenever you find yourself nesting conditions, think
of the procedure message. It might make your code
easier to read.


Here is an important gotcha:

```
{
	False false: {
		Out write: ['End the loop.'].
	}, break.
	
	Out write: ['Dont show me.'].

} procedure.

```

In this case, the text 'Dont show me' will be shown.
Because **break** is send to False. If you want to execute
a break, it needs to be send as a message to **True**.
 

```
{
	False not true: {
		Out write: ['End the loop.'].
	}, break.
	
	Out write: ['Dont show me.'].

} procedure.

```

Will work as expected.

## Exceptions

Exceptions can be handled like this:

```
{ Task 1 } except: { Task 2 }, start.
```

You can also cause an error to occur in your program intentionally; and
by doing so, activate the handler block. This is done by sending the
message **error:** to the current task as shown in this next
illustration:

```
{
this-task error: ['Whoops!'].
} except: { :mistake
Out write: mistake.
}, start.
```

## Injecting values

Xoscript provides for tasks the option to inject values. Now, have a look
at the task below:

```
>> sending := {
	Newsletter to: own recipient.
}.
sending set: ['recipient']
value: ['info@recipient.org'].
sending start.
```


This illustration presents an imaginary task, which sends a newsletter
to an email address or **recipient**. This recipient can be injected
into the task, externally and before the task is started, by sending the
message **set:value:** to the task. By doing so, the value of
**recipient** is preset into the task. This value can also be modified
and the task can then be run again. This is a useful method when using
Task objects.

## Empty Functions

Empty tasks are not allowed. In theory an empty task would look like
this: **{}**, however Xoscript perceives this as a language error. If you
like to declare an empty task, you can use the None object:

```
>> task := None.
```

Although, this is not a real task, but a None object, a start message
can still be sent:

```
>> answer := task start.
```

In fact this is the same as:

```
>> answer := None start.
```

Because the object **None** does not recognise the message **start**, it
will return itself as answer, leaving the answer once again **None**.
So, there is no necessity to have an empty task. Due to the elegant
design of the programming language Xoscript, you can simply use the None
object for this.

## Dynamic Scoping

When a Function needs a variable but can't find it,
it will check the variables of the Function that **called** it,
and continue checking up the chain of Functions.
This search process goes on until the variable is found.
If the variable is still not found, an error message will appear. This method of searching for a
variable is called **Dynamic Scoping**.

To illustrate this principle:

@test618

@api_Code_base


# Root Object

{{messages}}

The object named **Object** is the root object of all objects in
Xoscript and provides core language features. 

The most frequently sent message
is **on:do:**, which expands the functionalities of an object. This
message is received by the root object, which consequently links the
specified task to the message, and by doing so expands the derived
object.

## Catch-all methods

Normally if you send a message that does not correspond with
a method in the object, it gets ignored. However, you can specify
so-called **magic methods** or **catch-all** methods that will
get invoked if the message is not understood by the object.

There are 4 catch-all methods available. Each message matches
a specific number of arguments.

Catch-all message    | Number of arguments
-------------------- | -------------------
respond:             | 0
respond:and:         | 1
respond:and:and:     | 2
respond:and:and:and: | 3

Example:

@test619

## Programmatic messages

Instead of sending out a message directly to an object, it can also be
sent via a variable. To do so, you use the message
**message:arguments:**. 

@test396

@api_Object_base

# Lists

{{messages}}

Xoscript knows two types of collections: *lists* and *dicts*.
**Lists** are enumerations of objects in a *fixed order*. Dicts have
no order, instead, resemble a legenda involving a key (or term) and its
corresponding value. Lists are comparable to arrays (PHP, Java, C)
and lists (Python). Dicts are comparable to associative arrays (PHP) or
dictionaries (Python) in other programming languages. In order to create
a new List write:

```
>> fibonacci := List new.
```

This empty sequence can be filled using **append:** :

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

If we write the sequence to screen:

```
Out write: fibonacci, stop.
```

We will see:

```
List ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

Instead of append you can also use ; to add elements to a list:


```
>> fibonacci := List new ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

The semicolons (;) are all binary messages which put a
value into the sequence.

## Chaining

Suppose you have a list like:

```
>> x := List new ; 1 ; 2 ; 3.
```

If you would like to delete the first and the last element, then your
message would be:

```
x shift pop.
```

Unfortunately, the previous notation will not function correctly. The
message **shift** returns the first element of the sequence, which,
in turn, will become the receiver of the message **pop**. So, the
message **pop** is not sent to **x**, but instead to 2. A
possible solution to this problem would be to create two separate
sentences, such as: 

```
x shift.
x pop.
```

However, this is rather unpractical, in particular when you need to
delete more than two elements. Therefore, Xoscript offers an
alternative message structure for these kinds of situations. In
**alternative** message structures, the answers of objects are ignored
and you will get the receiving object back as answer, time and again.
An **alternative** message structure is initiated by sending the
message **do** to an object and the **alternative** message
structure can be ended by sending the message **done**. In the
example illustrated, this could be applied as follows:

```
>> x := List new ; 1 ; 2 ; 3.
x do shift pop done.
```

@api_List_collections


# Dicts

{{messages}}

**Both List and Dict are collections. However, contrary to a
list, a dict **has no** order. Another distinction between the two
is that a dict consists of object pairs. One object acts as entry (or
keyword) in order to search for the other object. A good example of a
list is a price list, such as:


```
>> menu := Dict new
	put: ['£5'] at: ['apple pie'],
	put: ['£6'] at: ['carrot cake'],
	put: ['£3'] at: ['fudge'].
```

Similar to a list, the message put:at:
is used to add an object to a list. The difference is that, contrary to
a list, two objects are being linked. The first object is, similar
to a list, the object that you will store in a list. The second
object is not its position within the collection, but the **entry**
which enables the previous object to be retrieved at a later time. In
short, a dict works a bit like a dictionary; so, by using the keyword
the meaning can be found. For instance, to retrieve from the
above-mentioned list the price of a fudge:

```
>> price := menu at: ['fudge'].
```

You may also use the concise notation:

```
>> price := menu ? ['fudge'].
```

Should the entries that you apply to store objects be without spaces
(and not collide with other predefined messages),
the next notation can be also be used:

```
>> menu := Dict new
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

No doubt that the above notation reads a bit more natural.
To request the price of a
fudge, the following simplified notation can be used:

```
>> price := menu fudge.
```

@api_Dict_collections

# File

{{messages}}

The **File** object provides basic access to the file system.
You can use this object to read entire files into a variable at
once, or write variables to files at once. Line by line reading
is also supported. These are the most common file I/O operations
in a scripting language. Advanced file operations require the
use of FFI through the server plugin or a separate IO plugin.

@api_File_file

# Date/Time

{{messages}}

For a structured representation of time and date, Xoscript uses the
**Moment** object. In case a new Moment object is printed on screen, the
current date and time are shown:

```
Out write: Moment new, stop.
```

Might result in something like:

```
2020-10-10 12:16:39
```

It is also easy to read out the individual time components. So, for
instance, if it is only necessary to know the current year, the message
**year** can be sent to the moment and, in turn, the reply will be a
Number object containing solely the year:

```
>> m := Moment new.
Out write: m year, stop.
```

@api_Moment_system


# Program/StdOut

{{messages}}

The Program Object represents the currently running app. This object
offers functionality to execute system commands, include sub programs,
read arguments and more. All system related functions.

## StdOut

Out is the standard output object. It basically has two methods:
**write:** and **stop**. The write: message is used to send a string
to stdout, the stop message prints a newline character.
Instead of **stop** you can also use \\n.

Example:

```
Out write: ['Hello World'], stop.
```

result:

```
Hello World
```

## Modules/Plugins

The world of Xoscript can be expanded with new system objects, by
installing modules . A new system object can be added to the world of
Xoscript by placing the module file (usually a file with the suffix .so
or .dll) into the mods folder. 

When you send a message to the object that is made available through the
plugin module, it will be automatically loaded by Xoscript.


## Reflection

There are various ways for system
exploring during program execution. Xoscript holds a couple of methods to
detect which objects are present and to which messages these objects
respond. Firstly, each object can be asked what **type** it is,
however types in Xoscript are malleable and therefore unreliable.

It is also possible to ask the Program object if a
given object is already present in the program:

```
Program Tool true: { ... }.
```

In case of an object
name which consists of one single symbol, it is best to apply the
following notation to avoid confusion:

```
Program find: ['X'], true: { ... }.
```

Besides asking about objects, it is equally possible to ask the
Program object about messages. For instance, it can be asked if the
object **Number** knows the message **between:and:**, in the way
as is illustrated below:

```
Program Number: ['between:and:'], stop.
```

@api_Program_system


# server

{{messages}}

The Server plugin in xoscript offers functionality to
create server-side applications. To load the server
plugin use:

```
Server init.
```

For your convenience it's also recommended to load
the webtools.xo and template.xo files.

```
Program use: ['webtools.xo'].
Program use: ['template.xo'].

```

## Hello World

Here is a very simple web program that you can use with a
standard CGI server like Apache2, NGINX, OpenHTTPD or any other
well known server.

```
#!/bin/xo

Server init.
Program use: ['webtools.xo'].

>> web-document := Web-Document new.

web-document out: ['
&lt;html&gt;
&lt;body&gt;
&lt;b>Hello World!&lt;/b&gt;
&lt;/body&gt;
&lt;/html&gt;'].

```

If you don't want to use the Web-Document object, that's fine, but
then you have to write the HTTP headers yourself:

```
#!/bin/xo
Out write: ['Content-type: text/html; charset=utf-8 \n\n'], stop.
Out write: ['hello world!'], stop.
``` 

## Request

The HTTP-Request object can be used to obtain GET/POST/COOKIE and
UPLOAD data:

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

The default max post fields is 40 and the default max content
length is 1000. To configure differently on a per script basis:

```
Program setting: ['max-contentlength'] value: 1. 
Program setting: ['max-postfields'] value: 1. 
```

{{note}}
If content length exceeds the maximum, the
process is killed because we cannot be sure
the payload is safe anymore.
{{/note}}




## Database

The Database object can be used to query MariaDB/MySQL.
To connect to a database do:

```
>> db := Maria-DB new host: ['localhost'],
	username: ['xo'],
	password: ['pass123'],
	dbname: ['xobase'],
	connect.

```

To insert a record use:

```
>> query := db query: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parameters: ( List new ; ['abc'] ; 12.35 ; 6 ). # parameterized queries

{  query execute. db commit. }
except: { :e db rollback.  }, start.
```

Note that xoscript *only* works with transactions and never autocommits.
If autocommit cannot be disabled you will get a connection error.
Always use parameter binding for queries, never add user input directly
to the SQL.

Obtain the inserted id like this:

```
Out write: ['INSERTED: '] + query insert-id, stop. # insert id
```

To fetch records:

```
>> query :=
db
	query: ['SELECT * FROM book order by id desc limit 2'], 
	fetch: { :row 
		Out write: row id + [' '] + row description + [': '] + row price, stop.
	}. # fetching rows

```

## Sessions

For persistence you can store and fetch data from a session object.
First create a new **Web-Document**. The Web-Document object ties together
the request, headers, HTML and session. This is because, whenever you
visit a website with your browser, you only see the HTML. But the
entire Web-Document consists of **Headers** as well. For instance,
most HTTP responses include a header like: Content-type:text/html to
tell the browser that the data that follows should be rendered as HTML
(and downloaded like a file for instance). Sessions are a way to
store user data between requests. To keep track of this data we need
to set a cookie, this cookie is also set through a Header. That's why
everything comes together in the Web-Document (because it is the full
document containing both headers and HTML or other data).


```
# First we make a new Web Document instance
>> web := Web-Document new.

# Now we start a session, this will generate a Header for a cookie and
# create a file to store your data, associated with that cookie
>> session := web session-start.

# Now we can treat session like a dict
session userid: 123.
```

To destroy the session (upon logging out):

```
web session-destroy.
```

## Headers

The Web-Document also allows you to set other well known headers.
For instance, if you want to redirect the user to another URL:

```
web goto: ['/other.html'].
```

Under the hood, this command also generates the HTTP header to send
along with your other data or HTML to instruct the browser to navigate
to the specified target address.

To add a custom header:

```
web header: ( 
	HTTP-Header new
	key: ['Content-Length']
	value: 400
).
```

To show a 404-page:

```
web not-found: ['OOps..'].
```


## Templates

The default template system is very simple. You don't have to learn
a new template syntax. Also, the template engine ensures real separation
between presentation and business logic.

To create a template from a file:

```
>> tpl := web template: ['templates/ux.tpl'].
```

The template system uses markers. 
There are three types of markers: cut markers, paste markers and
slot markers. The basic idea is really simple, you cut out
areas identified by cut markers and you can paste them at
areas identifier by paste markers. You can inject strings into
slot markers.

So for instance, given the following template, let's put the
gem in the jewel box and add a price tag.

```
&lt;!-- cut:gem --&gt;
&lt;img src="gem.gif"&gt;
&lt;b&gt;$&lt;!-- slot:price --&gt;&lt;/b&gt;
&lt;!-- /cut:gem --&gt;

&lt;div id="box"&gt;
&lt;!-- paste:jewels --&gt;
&lt;/div&gt;
```

You can do this as follows:

```
>> gem := tpl cut: ['gem'], copy.
gem price: 99.
tpl paste: gem at: ['jewels'].
web out: tpl clean.
```

The last line simply flushes the template as a string to the client
along with the required HTTP headers.

Result:

```
&lt;div id="box"&gt;
&lt;img src="gem.gif"&gt;
&lt;b&gt;$99&lt;/b&gt;
&lt;/div&gt;
```


## Passthru

To serve user uploaded files securely you can rely on passthru:

```
&gt;&gt; uploaded := ['smile.gif'].
Server passthru: uploaded prefix: ['/uploads/images/'].
Program end.
```

This will serve the user uploaded content with the appropriate
mime type. Only white listed mime types are supported:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP and PDF.
This method prevents TOCTOU-attacks, path traversals, 
malicious code execution (injection), symlink attacks,
DDoS attacks (file limit = 50MB), sniffing attacks and 
various other security issues.


## JSON

To encode an object as JSON:

```
>> json := ( JSON jsonify: ( 
	Dict new put: ( 
		List new ; 1 ; 2 ; 3
	) at: ['abc']
)).
Out write: json, stop.
```

To decode JSON into a xoscript object:

```
Out write: ((JSON object: json) abc ? 1), stop.
```

## Regex

You can use regular expressions by creating a pattern.
For instance to match the hrefs and targets of hyperlinks:

```
Pattern new: ['href="([^"]+)" target="([^"]+)"'].
```

Now, apply the pattern to the subject string like this:

```
pattern match: subject do: { :m :x .... }
```

Full example:

```
>> subject := ['&lt;html>
	&lt;a href="http://link1" target="_blank"&gt;
	&lt;a href="http://link2" target="_blank"&gt;
&lt;/html&gt;'].
>> pattern := Pattern new: ['href="([^"]+)" target="([^"]+)"'].
>> result  := pattern match: subject do: { :m :x
	Out write: m, stop.
	Out write: x, stop.
	<- ['XXX'].
}.
Out write: result, stop.
```

## Networking

Use the Net object to perform a web request.
The Net object always sends a POST request, unless you send None as
data, then it will send a GET request.


```
Net 
post: None 
to: ['https://redbeanphp.com'].
```

## Encryption

The server plugin comes with XChaCha20 and Argon2 based encryption.

Example:

```
>> encrypted := Vault encrypt: ['hello'] key: ['world'].
>> decrypted := Vault encrypt: encrypted key: ['world'].
```

## Tokens

To generate a cryptographically secure token of a specific length:

```
>> mytok := Vault token: 40.
```

This will generate a token of 40 characters.

## Formatting

The Format object allows you to format data, like padding or
adding zeroes. It uses the printf syntax.

```
>> fmt := Format new: ['%06.0f'].
fmt apply: 56. # gives 000056
```

## Encoders

Several encoders and decoders are available.
The url encoder prepares a url for use in HTML as a link:

```
Server url-encode: ['https://example.com?a=6&b=1 2'].
```

To safely inject user input into your HTML without risking XSS
injections, always use:

```
Server html-encode: ['&lt;harmless&gt;'].
```

Note that the template engine will always perform html encoding
if you write to a slot marker. So, if you use the template system
you don't have to use this.

## Linking

Using the link: message you can link an external library to
your program using libffi. For details see the chapter about ffi.


@api_MariaDB_mariadb
@api_Format_server
@api_Server_server



# ffi

{{messages}}

FFI is provided on a platform/plugin basis because it
ties into the underlying system achitecture, something the
core is not supposed to do.
The server plugin offers a compliant ffi/blob implementation.
By default the core connects to the target platform
through stdin/stdout, limited file i/o services and shell (Program os).
Auxiliary integration is provided by ffi/blobs through application
centered plugins like the server plugin.

FFI stands for Foreign Function Interface. It allows you to use functionality written by others in
different programming languages, provided through DLL files, SO files, or Dylib files. These could
be a variety of functions, and there's a vast range of available functionality through this method.
Let's start with an example:

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

The result of this code is that you’ll see the following on the command line:
FFI has 3 letters.
Now, you're probably thinking, "That's a lot of code for something so simple."
I mean, couldn't we just solve this with a Gui show command? The answer is a resounding yes!
But this is meant as an illustrative example.
FFI is usually used for more complex tasks, but those don't make good
examples, so I chose something trivial.

The arguments for link method:

- Argument #1: The DLL or SO file you want to use.
- Argument #2: The function in that file you want to link.
- Argument #3: A sequence with the names of the data types of the function’s arguments.
- Argument #4: The name of the function's return type.
- Argument #5: The name of the object you want to link this function to (if it doesn’t exist, it will be created
automatically).
- Argument #6: The message that this function should be linked to.

In the example above, we want to link the printf function from libc.so. You can find the data
type names in the documentation of the software you are linking to. The available types are:
void, pointer, float, double, int, uint, char, uchar, intX, and uintX,
where X can be 8, 16, 32, or 64.

These types refer to the number of bytes required to store the data. For printf, we are linking to a
new object called Printf and the message template:number:. You translate the external
function into the Xoscript dialect before using it. The message template:number: expects a
buffer with the template text as its first parameter. We create this buffer using a Blob object, which
allows you to manually allocate memory. You are responsible for freeing this memory afterward
with the free message.

You can fill a memory blob in various ways. In our example, we fill it with text, so we use the
utf8: message (UTF-8 is an encoding to convert text into bytes). You can also fill a blob with
bytes:, passing a list of byte values. To read the contents of a blob, use from:length:.
You'll get the bytes back as a sequence. You can even create a C-struct with a Blob using the
struct: message, passing a sequence of C types. This may be necessary when calling a C
function in an external software library that expects a pointer to a struct.

{warning}
You need to free blobs yourself.
Blobs are not cleared by the garbage collector.
{/warning}

Since blobs can be exchanged with external functions from libraries, they
cannot be garbage collected automatically (they might remain in use by 
external functions or these external functions might want to free them
themselves). Therefore you need to free blobs yourself if necessary.

To free a blob use:

```
myblob free.
```

To free struct use:

```
mystruct structfree free.
```

So for a struct, you need to send two messages: structfree and free to
deallocate the memory block.

@api_Blob_fficonnect

# Examples

{{messages}}

In this chapter, I'll try to list some example programs to give you an idea how
xoscript works.

## Server script

This is how a typical script on server might look:

```
#!/bin/xo

Server init.

# I prefer a central loader that loads
# webtools.xo and template.xo
Program use: ['app/libs/loader.xo'].

# create a new document
&gt;&gt; web-document := Web-Document new.
>> tpl := Template new: ( 
	File new: ['app/templates/greeting.tpl'], read
).

# cut the message section
&gt;&gt; message := tpl cut: ['message'].

# add a message (will be encoded properly to avoid xss)
message greeting: ['hello world!'].

# paste the element at the designated slot
tpl paste: message at: ['messages'].

# output including http headers
web-document out: tpl.
```

This would render a HTML document with a hello world message.
As you can see, this uses a very strict separation between HTML and
presentation logic (using the default template engine), so a
template developer can update the template without having to
adjust any code.

You can see the result here:

https://xoscript.com/test.xo

## Sophisticated Templates

This is an example of how you make a select in a form:

```
&gt;&gt; htmlstr := ['
&lt;html&gt;
&lt;body&gt;
&lt;form&gt;
&lt;!-- cut:products --&gt;
&lt;select name="products"&gt;
	&lt;!-- cut:product --&gt;
	&lt;option value="&lt;!-- slot:value -->"&gt;
		&lt;!-- slot:name --&gt;
	&lt;/option&gt;
	&lt;!-- /cut:product --&gt;
	&lt;!-- paste:product --&gt;
&lt;/select&gt;
&lt;!-- /cut:products --&gt;
&lt;!-- paste:products --&gt;
&lt;/form&gt;
&lt;/body&gt;
&lt;/html&gt;
'].

&gt;&gt; tpl := Template new: htmlstr.
&gt;&gt; menu := List new ; ['pizza'] ; ['pasta'].
&gt;&gt; products := tpl cut: ['products'], copy.
&gt;&gt; product := products cut: ['product'], copy.

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

This is a standard fizzbuzz example:

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

Output:

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

More examples will follow...



# Localization
