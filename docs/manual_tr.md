# Temel Bilgiler

{{messages}}


XOScript'e hoş geldiniz
XOScript projesinin amacı, basit ve denetlenebilir bir betik dili oluşturmaktır.
Basit, her zaman kolay anlamına gelmez.
Tanıdık bir programlama dilini kullanmak XOScript'ten daha kolay olabilir.
Burada basitlik farklı bir anlam taşır:
dilin ve davranışının eksiksiz bir zihinsel modelini kurabilmek.

XOScript kafanıza sığacak şekilde tasarlanmıştır.
Dilbilgisi ve kavram sayısı bilinçli olarak küçük tutulmuştur.
Sınıflar yoktur; nesneler doğrudan genişletilebilir.
Nesneler başvuru (referans) ile aktarılır, kopyalama açıkça yapılır
ve fonksiyonların tek bir çıkış noktası vardır.

Bu tercihlerin bazıları yaygın dillerden önemli ölçüde farklıdır.
Örneğin XOScript'in bir tür sistemi yoktur ve dinamik kapsam kullanır.
İşlenemeyen iletiler bir istisna üretmek yerine yok sayılır.
Bu tercihlerin sonuçları vardır ve hataları ortadan kaldırmayı amaçlamazlar.
Amaçları, dilin temelindeki modeli küçük ve tutarlı tutmaktır.

XOScript ayrıca yerelleştirilebilir; bu sayede iş kurallarını doğal bir
dilde ifade etmek ve bunları teknik olmayan paydaşlarla paylaşmak mümkün olabilir.

Denetlenebilirlik, aynı felsefenin gerçekleştirime de uygulanması demektir.
Çalışma zamanı C ile yazılmıştır; küçük, elle yazılmış bir sözcük çözümleyici (lexer), ayrıştırıcı (parser) ve ağaç yürütücüden (tree walker) oluşur.
Standart kütüphane ve çalışma zamanı büyük ölçüde dilin yapısını yansıtır;
bu da XOScript kodu ile gerçekleştirimi arasındaki ilişkiyi görece doğrudan kılar.

Testler de belgelerle yakından bağlantılıdır.
Her yöntemin, kılavuza eklenebilecek ilişkili bir testi olmalıdır;
bu, belgelerin gerçekleştirimle uyumlu kalmasına yardımcı olur.

XOScript, özellikler veya tanıdıklık açısından yaygın dillerle yarışmayı
amaçlamaz. Farklı bir hedefin peşindedir:
bir geliştiricinin bütünüyle anlayabileceği bir programlama ortamı.

Umut, küçük bir dilin ve küçük bir
gerçekleştirimin yazılımı baytdan nesneye, sözdiziminden çalışma zamanına
kadar anlamayı pratik hale getirmesi ve hem betikte
olup biteni hem de perde arkasında olup biteni anladığınız için
kodu güvenle yazabilmenizdir.

Bir xoscript sunucu kurulumunun mimarisi
basit ama esnektir.

{{architecture.png}}

xoscript'i bir sunucu dili olarak kullanmak için sunucu eklentisini
/mods/server adlı bir klasöre kurmanız gerekir.

Bunun nedeni, örneğin PHP veya Python'dan farklı olarak çekirdek dili
sunucuya özgü işlevlerden ayırmayı tercih etmemizdir. Aksi halde herkese
hiçbir amaca hizmet etmeyen koca bir paket göndermek zorunda kalırdık ki bu
sadece saçma olurdu. İsterseniz başka modüller de kurabilirsiniz. Sistem
oldukça esnektir.

Ayrıca şablonlama ve oturum yönetimi gibi bazı işlevler betik dilinin
kendisiyle daha iyi gerçekleştirilir; bu yüzden kolaylık olsun diye
template.xo ve webtools.xo kütüphanelerini de birlikte sunuyoruz.
Tüm bunların nedeni, xoscript'i nasıl kullanmak istediğinizi
bilmememizdir. Onu sunucu tarafı betik dili olarak kullanabilirsiniz,
ama aynı zamanda grafik arayüzler, gömülü aygıtlar ya da yalnızca toplu işlem için de.
Onu sunucu tarafı betik dili olarak kullansanız bile (bu şu anda
başlıca kullanım alanlarından biridir), yine de farklı bir şablon motoru
veya farklı bir oturum yöneticisi kullanmak isteyebilirsiniz.
Sizin bizimkini kullanmanız gerektiğine karar vermek bize mi düşer?

Yine de kendi şablon motorumuzu kullanmanın avantajlarından biri,
şablon oluşturmak için ek bir sözdizimi öğrenmek zorunda olmamanızdır.
xoscript ile birlikte gelen varsayılan şablon motoru, sunum ile mantık
arasında %100 ayrım sağlar. Özel bir şablon sözdizimi yerine
oldukça esnek bir yuva işaretleyici sistemi kullanır.
Daha fazla bilgi için Sunucu bölümüne bakın.

Varsayılan şablon motorunu veya varsayılan web araçlarını kullanmak
istemiyorsanız, kendinizinkini sağlamanız gerektiğini söylemeye gerek yok.

Web sunucunuzu bir chroot, jail veya başka türde bir korumalı alanda
çalıştırıyorsanız, xo'nun bağımlılıklarını da o ortama kurmanız gerekir;
hangi kütüphanelere ihtiyacınız olduğunu ldd ile görebilirsiniz (Linux veya BSD'nin man sayfasına bakın).
xo betiklerinizde kabuk komutları kullanmak istiyorsanız, bu ortama bir kabuk
(bash veya ksh gibi) da kopyalayın.

Ayrıca geriye dönük uyumluluğu çok ciddiye aldığımızı belirtmek isteriz.
Hatta 'version' adlı özel bir geriye dönük uyumluluk özelliği bile
vardır. Genel olarak kodunuzun sonsuza dek çalışmasını hedefliyoruz. Yani
xoscript'in yeni sürümleriyle uyumlu kalmak için kodunuzu asla güncellemek
zorunda kalmayacaksınız. Hedefimiz: bir kez yaz, sonsuza dek çalıştır.

Bu kılavuzun geri kalanı, xoscript programlama dilini ayrıntılı olarak
açıklamaya ayrılmıştır. Sunucu betikleri Sunucu adlı bölümde ele
alınmaktadır. Deneyimli bir yazılım geliştiriciyseniz, bazı bölümler biraz
fazla ayrıntılı olduğundan ya da genel programlama pratiklerine çok benzediğinden
birkaç bölümü atlamak isteyebilirsiniz. Dolayısıyla birçok başka programlama
dilinde deneyimi olanlar bu kılavuzu bir başvuru kaynağı olarak kullansa
daha iyi olur.

## Linux Kurulumu

apache2 ve mariadb'yi indirin:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

xoscript'i indirin.
X yerine doğru sürüm numarasını yazın!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Dosyaları web köküne ve /bin dizinine kopyalayın:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

apache2 yapılandırmanızı düzenleyin:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Virtualhost bölümünü şununla değiştirin:

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

Bir test sayfası oluşturun:

```
sudo nano /var/www/html/test.xo
```

ve küçük bir test programı yazın:

```
#!/bin/xo
Server hazırla.
Program kullan: ['webtools.xo'].
>> web := Web-Belgesi yeni.
web çıktıla: ['Hello World'].
```

apache2'nin programınızı CGI üzerinden çalıştırmasına izin verin:

```
sudo chmod uog+x /var/www/html/test.xo
```

apache2'yi yeniden başlatın:

```
sudo systemctl restart apache2
```

Tarayıcıda test sayfanıza gidin:

```
http://localhost/test.xo
```

Şunu görmelisiniz:

```
Hello World
```


## OpenBSD Kurulumu

/etc/httpd.conf dosyasını düzenleyin ve şunu ekleyin:


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

SSL kullanmak istiyorsanız:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Anahtar değişimini kuantum saldırılarına karşı korumak için
mlkem şifresini seçin:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

xo ikili dosyasını ve modülleri, ayrıca tüm bağımlılıkları
chroot ortamına ekleyin (ldd ile bulun).

## Örnekleri çalıştırma


Paketteki örnek programlardan birini çalıştırmak için:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Örneğin FizzBuzz örneğini Linux'ta çalıştırmak için:

```
./example.sh fizzbuzz Linux
```

Aynı örneği OpenBSD'de çalıştırmak için:

```
./example.sh fizzbuzz OBSD
```

Örneği temiz bir derlemeyle çalıştırmak için:

```
./example.sh fizzbuzz OBSD clean
```

## Birim testleri

Birim testlerini çalıştırmak için:

```
./runtests.sh
```

Birim testlerini derlemeden (yalnızca test ederek) çalıştırmak için:

```
./runtests.sh nobuild
```

## Derleme

Linux'ta kaynaktan derlemek için:

```
make clean
ISO="en" make
```

OpenBSD'de:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

Sunucu eklentisini Linux'ta derlemek için:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

Sunucu eklentisini OpenBSD'de derlemek için:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Merhaba dünya

Dosya bilgisayarınıza aktarıldıktan sonra onu açabilir ve
aşağıdaki komutla xo'yu başlatabilirsiniz:

```
xo
```

Bir XOScript'i çalıştırmak için programı -xo sonekiyle (isteğe bağlı)
bir dosya olarak kaydedin. Ayrıca programınızın dosya adını
XOScript komutunun ardından yazın:

```
xo myprogram.xo
```

Program dosyanızı parametre olarak kullanarak bir XOScript komutu
çalıştırdığınızda, xo program dosyanızı okur ve çalıştırır.

{{note}}
Programınızı xo simgesinin üzerine sürükleyerek de başlatabilirsiniz.
{{/note}}

{{warning}}
Bazı sistemlerde, xo'nun dinamik kütüphaneleri yükleyebilmesi için
önceden izin vermeniz gerekir.
{{/warning}}

Geleneğe göre, yeni bir programlama dilindeki ilk program dünyaya
bir tür selam olmalıdır. XOScript'te böyle bir
**Hello world** programı şöyle görünür:

@test598

Bu metin bir dosyaya, örneğin hello.xo'ya kaydedildiğinde, şu şekilde
çalıştırılabilir: .

xo hello.xo

Hello world


Program çıktısını yukarıda gösterilen siyah pencerede görebilirsiniz.
Bu kılavuz boyunca çıktıyı göstermek için aynı görselleştirme
kullanılacaktır.

{{note}}
**Çıktı** büyük harfle başlar.
Genel olarak nesneler büyük harfle başlar;
ancak bir örnek (instance) gibi davranıyorsa (kendine ait
yöntemleri yoksa, yalnızca veri taşıyorsa) bu geçerli değildir. Bu, diğer programlama dillerindeki
sınıf ve örnek kurallarını yansıtır.
{{/note}}


## Sözdizimi

XOScript *saf* *nesne yönelimli* bir programlama dilidir. Bu,
xoscript'in her şeyi bir nesne olarak gördüğü, dolayısıyla başka
*veri türü* olmadığı anlamına gelir. XOScript ile yazılmış bir programda
temelde üç temel rutin eylem vardır: *atama*, *ileti gönderme*
ve *yanıtlama*. Nesneler arasında ileti alışverişi, bir XOScript
programının temel parçasıdır. Bu üç rutin eylem aşağıda
gösterilmiştir:


Eylem           | Örnek
--------------- | --------
atama           |  \>\> x := 1. 
tekli iletiler  | x even?.
ikili ileti     | 1 + 2.
anahtar sözcüklü ileti | x from: 0 length: 10.
yanıt           | <- answer.  


Bu bölüm size XOScript dili hakkında genel bir izlenim verecek
ve temel ilkelerini açıklayacaktır. XOScript küçük bir dildir ve
yaklaşık altı dilbilgisi kuralına karşılık gelen üç eyleme (bkz. şekil)
dayanır. Dilde ustalaşmak için gereken tek şey budur.

Her şey hemen açık gelmiyorsa endişelenmeyin: tüm yapı taşları
bir sonraki bölümde (3) incelenecek ve temel kurallar tekrar
edilecektir. Ancak bu bölüm esas olarak dile genel bir giriş
niteliğindedir. Temel ilkeler kısaca açıklanacak ve konuyla ilgili
birkaç örnekle gösterilecektir. Eksik kalan ayrıntılar daha sonra
ele alınacaktır.

XOScript'te yorumların başına bir \# simgesi konur. Dolayısıyla aşağıdaki
satır yok sayılır:

```
# this is just a comment
```

## Değişkenler

Bir değişken atamak için
değişken bildirim simgesini kullanırsınız: >>. Bir değişkenin adı
şunlar dışında tüm işaretleri içerebilir: <-, :=, boşluklar,
noktalar, virgüller, iki nokta üst üsteler, tırnak işaretleri [' '] ve parantezler ().
Ayrıca bir değişken birden fazla satırdan oluşamaz. Bir değişkenin
bir rakamla veya eksi işaretiyle başlayamayacağını unutmayın.

Geçerli değişkenlere örnekler:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dollar'].
>> +plus := Doğru.
>> user-password := ['Pssst!'].
```

Geçersiz değişkenlere örnekler:


```
>> -123 := ['negative number'].
>> password of user := ['Classified'].
>> password.of:user := ['Classified'].
>> ,x := 10.
```

{{note}}
Bir metin sabitinde, sözcük çözümleyici için belirsizliğe
yol açmadığı sürece hiçbir karakteri
(tırnaklar, çift tırnaklar, metin
sınırları dahil) kaçış karakteriyle
yazmanız gerekmez.
{{/note}}

Bir değişken bildirildikten sonra serbestçe kullanılabilir. Bu,
bildirim simgesini yalnızca değişkeni ilk kullandığınızda (bildirim)
kullanmanız gerektiği anlamına gelir.

Daha açık söylemek gerekirse, değişkeninize rastgele bir değer atamaya
başlayamazsınız *(x := 2)*; önce değişkeni bildirmeniz gerekir *(\>\>
x := 2)*. Ancak bir kez bildirildikten sonra, bildirim simgesini
kullanmadan değerini değiştirebilirsiniz *(\>\> x := 2. x := 3.)*.

Bildirim sırasında değişkene bir değer atamanın zorunlu olduğunu
unutmayın. Diğer programlama dillerinin aksine, bir değişkeni değer
vermeden bildiremezsiniz. Her değişkeni açıkça bir başlangıç değerine
bağlamak esastır. Bununla birlikte, değişkeni **Hiç** nesnesiyle
başlatmakta özgürsünüz. Bu durumda değişken boş kabul edilebilir
*(\>\> x := None.)*. Kısacası, bir değişkeni başlangıç değeri olmadan
bildirmeye izin verilmez. Yani,

```
>> x.
```

geçersizdir ve bir hata iletisi verir.

{{note}}
xoscript değişkenler için dinamik kapsam kullanır;
ayrıntılar için Fonksiyonlar bölümüne bakın.
{{/note}}


## Sabitler

XOScript her şeyi bir nesne olarak görür; yani tüm sayıları, metinleri
ve kod parçalarını. 1, 2, 100, -999 ve 1,234 gibi sayılar
Sayı nesneleridir. Tek tırnak işaretleri arasındaki tüm metinler Metin
nesneleridir. Süslü parantezler {...} arasında gruplanan tüm kod parçaları
Fonksiyon nesneleridir.

Sabit           | Kök nesne    | Örnek
--------------- | ------------ | ----------
sayılar         | Sayı         | 1,2,3... 
metinler        | Metin        | \['hello'\]
fonksiyon       | Fonksiyon    | { 1 + 2. }.
                
     
Sayılar ve metinler gibi nesneler kökenlerini her zaman bir kök nesnede
bulur. Örneğin tüm sayılar **Sayı** nesnesinden türer. Tüm
metinler **Metin** nesnesinden, tüm kod parçaları ise **Fonksiyon** nesnesinden türer.
Bunların hepsi de aslında tüm nesnelerin kök nesnesi olan **Nesne**
nesnesinden gelir.


## İletiler

XOScript'te programlama temelde nesnelere
ileti göndermek demektir. Bir nesneye ileti göndermenin genel gösterimi
şöyledir:

```
<object> <message>
```

Örneğin **2** sayısının çift sayı olup olmadığını öğrenmek için
**çift?** iletisi **2** nesnesine gönderilir:

```
2 çift?
```

Yanıt **Doğru** olacaktır (yine bir nesne). Bilinmeyen iletiler
nesneler tarafından genellikle yok sayılır; bu yüzden hata oluşmaz. Bazı nesneler (örneğin
sayılar veya metinler) bilinmeyen bir iletiye önceden tanımlanmış bir şekilde yanıt verir
(bu konuda daha sonra daha fazlası).

Bir nesne üç tür ileti alabilir.

Tür             | Argüman sayısı
--------------- | -------------------
Tekli           | 0      
İkili           | 1     
Anahtar sözcüklü | 1+    


İlk olarak, argümansız olan **tekli
iletiler** vardır (yukarıdaki örneğe bakın). İkinci olarak,
bir veya birden çok argümanı olan **anahtar sözcüklü iletiler** vardır,
örneğin:

```
>> x := Sayı arasında: 1 ve: 10.
```

Bu durumda **arasında:ve:** iletisi, tüm sayıların kök nesnesi olan
**Sayı** nesnesine gönderilir. Sonuç 1 ile 10 arasında rastgele bir sayı
olacaktır. Son olarak, yalnızca bir karakterden ve bir argümandan oluşan
**ikili iletiler** vardır:

```
2 + 3
```

Bu bir matematiksel toplama gibi görünür, ama aslında yalnızca başka bir iletidir.
**+** iletisi **3** argümanıyla birlikte **2** nesnesine gönderilir ve
**5** yanıtını döndürür. İkili iletilerin iki nokta üst üste olmadan yazılmasına izin verilir.

İkili iletiler zincirlenebilir:

```
>> x := 3 + 2 - 1.
```

Bu parçada önce **+ 2**, **3** **Sayı** nesnesine gönderilir; bu
**5** Sayı nesnesiyle sonuçlanır, ardından **-1** bu sayıya
gönderilir. Dikkatli okuyucular, bu protokolün geleneksel matematiksel
işlem önceliğiyle çeliştiğini haklı olarak fark edecektir.
XOScript, ileti sistemindeki tutarlılık uğruna matematiksel önceliği
yok sayar. Sonuç olarak şu toplam:

```
2 + 3 * 5 = 25
```

17 değildir.

Bu bilinçli bir tasarımdır. Sırayı değiştirmek için parantezler kullanılabilir:

```
2 + (3 * 5) = 17
```

Çoğu nesne belirli bir iletiye yanıt olarak kendisini döndürür.
Bu yararlıdır, çünkü nesneye bir sonraki iletiyi göndererek onunla
diyaloğu sürdürmeyi teşvik eder:

```
Çıktı yaz:
[' hello '] kırp büyük-harf.
```

```
HELLO
```

Burada **Metin** nesnesine iki ileti gönderilir: **kırp** ve ardından
**büyük-harf**.

Aşağıdaki parçada, yeni bir iletinin geldiğini belirtmek için virgül
kullanmak gereklidir. Aksi halde XOScript kafası karışır.

```
Çıktı yaz: ['Hello!'], yeni-satır.
```

Önce **yaz:** iletisi kalem simgesine gönderilir, ardından
**yeni-satır** gelir. Virgül olmasaydı XOScript, **yeni-satır** iletisini
**metin** **Hello!** nesnesine göndermek istediğinizi düşünürdü; bu boşuna bir çaba olurdu.

İletilerin işlenme sırası şöyledir: soldan sağa;
önce parantez içindeki iletiler, ardından tekli iletiler. Sonra
ikili iletiler ve en son anahtar sözcüklü iletiler. Aşağıdaki
örneğe bakın:

```
Çıktı yaz: 0.5 yuvarla + (2 - 1), yeni-satır.
```

XOScript her zaman soldan sağa okur: önce **yaz:** iletisi
Çıktı nesnesine gönderilir, ardından **yeni-satır** iletisi gelir. Argümanın
kendi içinde de XOScript soldan sağa okur; yani önce **0.5 yuvarla**,
sonra **+**.

{{note}}
yeni-satır iletisi metne bir satır sonu karakteri ekler.
Bu iletinin İngilizce adı (stop) telgraf sistemlerinden esinlenmiştir.
Telgraf sistemlerindeki iletilerde
cümlenin sonunu belirtmek için sıklıkla STOP sözcüğü kullanılırdı
(çünkü noktalama güvenilmez veya pahalıydı).
{{/note}}

Ayrıca **yuvarla**, bir **tekli ileti** olduğu için **+** iletisinden
önce gelir. Parantezler nedeniyle önce **2 - 1** hesaplanır,
ardından **0.5 yuvarla** sonucuna (1) **1** eklenir.

Tüm işlem **2** sonucunu verir; bu aynı zamanda yazılan
yanıttır. Virgülden sonra imleci yeni bir satıra taşıyan yeni-satır iletisi
gelir. Elbette XOScript programlarının işlem sırasını tam olarak
kavramanın en iyi yolu pratik yapmaktır.

XOScript'te, diğer birçok programlama dilinin aksine, boşlukların
sözdiziminin temel bir parçası olduğunu belirtmekte yarar var. Özellikle
ikili iletiler söz konusu olduğunda boşluklar biraz kafa karışıklığına
yol açabilir. İkili bir iletiden sonra her zaman bir boşluk kullanın.
Bir sayıyı iletiye doğrudan bitiştiremezsiniz, örneğin:

```
3 + 2
```

şundan farklıdır:

```
3 +2
```

İlk örnek (**3 + 2**), **2** sayısını argüman olarak alan **+**
iletisini **3** sayısına gönderir. Bu durumda sonuç **5** olacaktır.
İkinci örnekte (**3 +2**) ise **+2** tekli iletisi **3** sayısına
gönderilir. Bağlama göre bu çok farklı bir sonuç verebilir.

## Var olmayan yöntemler

Bir nesneye ileti göndermek, o nesneye bu ileti adıyla bağlanmış
fonksiyonu çağırır. Anlaşılmayan bir ileti gönderirseniz, alıcı nesne
iletinizi yok sayar ve iletişimi sürdürmek için bunun yerine kendisine
bir başvuru döndürür. Buna hoşgörülü ileti aktarımı denir.

Örnek:

```
Çıktı yaz: Nesne blah, yeni-satır.
```

Bu bir hata vermez. Yalnızca **Nesne** metnini yazdırır.


## Akış Denetimi

XOScript'te *döngüler* ve *if* yapıları için ayrı dilbilgisi
kurallarına gerek yoktur. Bir if ifadesi, bir **Doğru** nesnesine ya da bir
**Yanlış** nesnesine gönderilen basit bir **doğru:** veya **yanlış:** iletisidir:

```
2 çift? doğru: {
	Çıktı yaz: ['Two is an even number'], yeni-satır.
}.
```
Önceki örnekte **doğru:** iletisi **Doğru** nesnesine gönderilir (2 çift sayı
mıdır sorusunun yanıtı). Argüman olarak ek bir kod parçası
da gönderilir: bir **Fonksiyon** nesnesi. Bu fonksiyon ekrana
2'nin gerçekten çift sayı olduğunu yazar.

Bir *döngü* için de ayrı yazım kurallarına gerek yoktur. Bir
kod parçasını üç kez çalıştırmak için o **Fonksiyon** nesnesine
**3** argümanıyla **\*** göndermeniz yeterlidir:

@test5

Bu kod parçasında **i** dizindir. Yani Fonksiyon ilk kez
çalıştırıldığında **i** 0'a eşittir, sonraki çalıştırılışında **i** = 1'dir ve
bu böyle devam eder.

Başka bir örneğe bakalım. *kJ* (kilojoule) değerlerinden *kcal* (kilokalori)
değerlerine 100'lük adımlarla bir dönüşüm tablosu yazdırılması gerektiğinde
doğru gösterim aşağıdaki gibidir:

@test599

Burada geçerli satırın numarası **:line** parametresine
aktarılır. Bir fonksiyonun başında fonksiyon parametreleri
tanımlanır. Kullanılmayan parametreler boş kalır (**Hiç**). Parametreler
her zaman fonksiyonun başına, açılış süslü parantezinin hemen ardından
yerleştirilir ve önlerine iki nokta üst üste konur.

**sürece:** iletisi, bir *döngü* ile bir *koşulun* birleşimidir.
İki fonksiyon **sürece:** iletisiyle birbirine bağlanabilir. Alıcı fonksiyon,
iki noktadan sonraki fonksiyon olumsuz bir sonuç verene kadar çalışmaya
devam eder. Örnek:

@test600

Yukarıda gösterilen kod parçasında **x** değeri **5**'ten küçük olduğu
sürece **x**'e **1** eklenir. Bu artık geçerli olmadığında ikinci
fonksiyon **Yanlış** yanıtını verir ve sonuç olarak birinci
fonksiyonun çalışması sona erer. **x**'in fonksiyonun dışında
tanımlandığını ve global bir değişken olduğunu unutmayın. Kapsam kuralları
hakkında daha fazla bilgi için Fonksiyonlar bölümüne bakın.

## Metin enterpolasyonu

*kJ/kcal* listesi daha
derli toplu hale getirilebilir. Tercihen liste şöyle olmalıdır:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Tercih edilen çıktıyı bir şablona dönüştürdüğünüzde gösterimi
şöyle olabilir:

```
number1 kJ ➞ number2 kcal
```

Bu, **number1**'in kJ değerini, **number2**'nin ise kcal değerini
temsil ettiği anlamına gelir. XOScript'te metin enterpolasyonu böyle çalışır.
XOScript'te bunun için ayrı dilbilgisi kurallarına gerek yoktur.
Değiştirilmesi gereken sözcüğü, yerine geçecek metni argüman olarak
vererek metne göndermeniz yeterlidir:

```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

Sonuç:

```
100 kj ➞ 23.9 kcal
```

Bu yerine koyma kuralı, bir **metin** nesnesinin aldığı her tanımsız
ileti için geçerlidir. **metin** nesnesinin tanımadığı her ileti şu
şekilde yorumlanır: *ileti metnini, ileti argümanındaki metinle
değiştir.* Programı şu şekilde uyarlayabilirsiniz:


@test601


Hangi iletinin yerine koyma için kullanılıp kullanılamayacağı konusundaki
karışıklığı önlemek için, şablonda değiştirilmesi gereken metin
bölümleri için &lt; &gt; gibi bir şablon işaretleyici kullanmak en
iyisidir.

## Dönüş değerleri

Bir iletiyi yanıtlamak için dönüş oku
(*<-*) kullanılır. Aşağıdaki örnek, bir yüzdeyi hesaplayan bir görevin
nasıl oluşturulacağını gösterir:

@test602

Görev tanımlanıp **percentage** değişkenine atandıktan sonra,
**100** ve **7** argümanlarıyla **uygula:ve:** iletisi gönderilir.

Bu, görevi **100** ve **7** değerlerine uygulayarak, yani 100'ün %7'sini
hesaplayarak çalıştırır. Dönüş oku kullanılarak yanıt görevden ana
programa geri döndürülür.

## Genişletme

Bu kod geçerli olsa da, argümanların sırasının akılda tutulması
gerektiği için bir dezavantajı vardır. Peki neden bunu
*7 percent of: 100* gibi yazmayalım? Bu çok daha *doğal*
görünürdü. Bunu mümkün kılmak için **7**'nin üst nesnesi olan
**Sayı** nesnesini, **percent of:** iletisini anlayacak şekilde
uyarlamamız gerekir. Bu, Sayı nesnesine **olunca:yap:** göndererek
şöyle yapılabilir:

@test603

Bu durumda yüzde sayının kendisi olduğundan, kendi anahtar sözcüğü
*kendi* ile kendisine başvururuz. Kısacası kendi simgesi şu anlama gelir:
*bu iletiyi kendime gönder*.

# Nesneler

{{messages}}

Var olan nesneleri ayarlayıp genişletmenin yanı sıra, yalnızca **yeni**
iletisini göndererek kendiniz de yeni nesneler oluşturabilirsiniz.
Bir numaralandırma sırasını zorunlu kılan bir fatura nesnesi oluşturmak
istediğinizi varsayalım; bu durumda önce bir fatura nesnesine ihtiyacınız olacaktır.

Her nesnenin başka bir nesneden türediğini ve bunun da sonunda Nesne
adlı tüm nesnelerin kök nesnesinden geldiğini bildiğimize göre,
yeni nesnenizin bu diğer nesnelerden hangisine dayanacağı konusunda
bir seçim yapılması gerekir. Yeni nesneniz, dayandığı nesnenin, yani
**yeni** iletisinin başlangıçta gönderildiği nesnenin tüm özelliklerini
devralır.

Bu örnekte, çok fazla devralınmış özelliği olmayan oldukça yansız bir
nesne tercih edilir. Bu seçimi kolaylaştırır, çünkü bu durumda yeni
nesne doğrudan kök nesnenin kendisine, yani **Nesne** nesnesine
dayandırılabilir. Tasarlanan fatura sisteminin gösterimi bu durumda
şöyle olur:

@test604

Geçerli fatura numarası nesnenin içinde saklanır; bu yüzden önüne
**öz** anahtar sözcüğü konmuştur. Buna *özellik* denir;
ayrıntılar ileride verilecektir.

Bazı işletmeler yılın fatura numaralarına dahil edilmesini tercih eder.
Bu durumda, önceki bir fatura nesnesine dayanan, ancak kullanıcısına
belirli bir yıl girme olanağı sunan yeni bir fatura nesnesi
oluşturabilirsiniz:

@test605

**sayı** iletisinin gerçekleştirimini yeniden yazmaya gerek yoktur,
çünkü bu ileti daha önce yazılmış **fatura
nesnesinden** devralınır; dolayısıyla eski kod yeniden kullanılabilir. XOScript'te
sınıflar ve bunlarla ilgili diğer kavramlar yoktur. Bu, nesnelerin
yalnızca başka nesnelerden devralabileceği anlamına gelir; buna
*prototip tabanlı kalıtım* da denir.

Şimdi özelliklere dönelim. Nesne özelliklerine yalnızca
*nesne hiyerarşisinin içinden* erişilebilir; bu nedenle bu özellikler
başka nesneler tarafından görülemez.

Diğer programlama dillerinin aksine, nesnelerin tüm özellikleri
yalnızca özelliği oluşturan nesneye ve ondan türetilen nesnelere
görünürdür.

Yaygın olarak kullanılan bir teknik, bir nesneyi bir tür *şablon (blueprint)*
olarak kullanmaktır; daha önce ele alınan faturalarda olduğu gibi.
Bir başka güzel örnek de **Point** nesnesidir. Bir harita üzerindeki
noktaları kullanarak hesaplamalar yapan bir bilgisayar programı
oluşturduğunuzu düşünelim. Bir x koordinatı ve bir y koordinatı
özelliklerini içeren ve bunları iletiler aracılığıyla dış dünyaya sunan
**Point** nesnesini geliştirebilirsiniz:

@test606

**=** iletisi, **ve:** iletisini kullanarak iki noktayı karşılaştırır.
İlk karşılaştırma bir **Doğru** ya da bir **Yanlış** ile sonuçlanır. Bunlar
mantıksal (boolean) nesnelerdir. Bir Doğru nesnesine **ve:** iletisini
gönderdiğinizde ve iki noktadan sonraki argüman nesnesi de **Doğru** ise,
yanıt olarak yine **Doğru** alırsınız. Bunlardan biri **Yanlış** ise
**Yanlış** yanıtını alırsınız. Bir noktanın diğerinin koordinatlarını
okuyamadığına dikkat edin. Bu verileri istemek için diğer noktaya bir ileti
göndermek gerekir: **x-coordinate** ve **y-coordinate**. Sonuçta, daha önce
açıklandığı gibi, özelliklere yalnızca nesne ailesinin kendi içinden
erişilebilir.

Burada nokta karşılaştırmasını yapmak için **=** iletisinin kullanıldığına
dikkat edin. Aynı şekilde **is:** veya **equal:** gibi farklı bir ileti
de kullanılabilirdi; ancak bu durumda **=** karakterini yeniden kullanmak
uygun görünmüştür.

## Kalıtım

Daha önce yazılmış kodu, bir nesne hiyerarşisi oluşturmak için yeniden
kullanabilirsiniz. Örneğin:

```
>> Animal := Nesne yeni.
>> Dog := Animal yeni.
>> Poodle := Dog yeni.
```

Bu durumda **Dog**, **Animal** nesnesinin tüm davranışlarını ve özelliklerini
devralır; **Animal** nesnesi de tüm nesnelerin kök nesnesi olan
**Nesne** nesnesinin tüm davranışlarını devralır.


## Geçersiz kılma


Aşağıdaki örnekte yeni bir liste türü oluşturulur:
her öğenin benzersiz olmasının garanti edildiği **Combination**. Listenin
fonksiyonları kalıtım yoluyla yeniden kullanılır:

@test607

İkinci **red** öğesinin listeye alınmadığına dikkat edin.

Zaman zaman bir nesnenin bir davranışını geçersiz kılmak gerekebilir.
Örneğin sayılar toplanırken ölçü birimlerinin de hesaba katılması
gerektiğinde. Aşağıdaki örnekte **Size** nesnesi oluşturulur. Bu nesne,
toplama sırasında eklenecek sayının birimini hesaba katan bir sayı
döndürür. **Sayı** nesnesi bunun *inç* mi yoksa *fit* mi olduğunu
denetler. Program kodu aşağıdakine benzeyebilir:

@test608

## Özyineleme

Önceki örnekte artı **işareti** geçersiz kılınmaktadır. Sonunda
asıl toplamanın yine de yapılması gerektiğine dikkat edin; bu aslında
şu satırda gerçekleşir:

```
>> answer := kendi + (sayı x factor).
```

Peki XOScript, bu artı **işaretinin** özgün toplama mantığını kastettiğini
nasıl anlar? Örneğin başka bir yorum, XOScript'in aynı iletiyi aynı
nesneye tekrar tekrar göndermesi olabilirdi; bu da bir
**sonsuz döngüye** yol açardı. Açıktır ki amaç bu değildir. Bir nesneye,
tamamen aynı kodu çalıştıracak bir ileti gönderdiğiniz anda XOScript,
bu durumda alttaki, geçersiz kılınmış iletinin kastedildiğini anlar. Böylece
programınız bu tür sonsuz döngülere karşı otomatik olarak korunur.
Ancak gerçekten de aynı fonksiyonu geçerli fonksiyonun içinden
çalıştırmayı amaçlıyorsanız, önce **yinelemeli** iletisini göndermeniz
gerekir. Bu durumda sonuç sonsuz bir döngü olacaktır.
Yine de özyinelemeli görevlerin yararlı uygulamaları vardır; örneğin
belirli bir sayının faktöriyelini hesaplamak istediğinizi varsayalım.
Bu durumda Sayı nesnesine **factorial** iletisini eklemeniz
yeterlidir:

@test609

Bu, özyineleme gerektirir. Aslında **factorial** iletisine bağlı görevin
o fonksiyonun içinde yeniden çalıştırılması gerekir.
Yani faktöriyel fonksiyonunu, faktöriyel fonksiyonunun kendi içinden
çağırmak gerekir. Kural olarak XOScript, sonsuz bir döngüye girme riski
nedeniyle bu işlemi engeller. Bu nedenle iletinin önüne
**yinelemeli** sözcüğünü koymak çok önemlidir. Bu, XOScript'in aynı
görevi çalıştırmayı amaçladığınızın ve bir hata yapmadığınızın farkında
olması için yapılır.

## Sınıf benzeri nesneler

xoscript sınıf sunmasa da sınıf benzeri bir davranışı taklit etmek
çok kolaydır. yeni iletisini geçersiz kılmanız yeterlidir.

```
>> Animal := Nesne yeni.
Animal olunca: ['yeni'] yap: {
	<- kendi yeni hazırla.
}.

Animal olunca: ['hazırla'] yap: {
	öz sound := ['?'].
	öz legs  := 4.
}.
```

Yukarıdaki kod parçasında Animal adlı bir nesne oluşturuyoruz.
Bu nesne, köpekler ve kediler gibi her tür hayvan için bir *şablon (blueprint)*
işlevi görür. Üst nesne Animal, bunun sınıf benzeri bir nesne
olduğunu belirtmek için büyük A ile yazılmıştır.
Ardından kendi yeni yöntemimizi yazarak yeni iletisini geçersiz kılıyoruz.
Bu durumda yöntem kendi nesnesine bir yeni iletisi, ardından da
hazırla iletisini gönderir. xoscript özyinelemeyi varsayılan olarak
engellediğinden bu sonsuz bir döngüye yol açmaz. Bunun yerine yeni
iletisini üst nesneye (Nesne) gönderir ve sonuçta yeni bir Animal
örneği elde edilir. Yani yeni yöntemimizi oluşturduğumuz nesnenin
kendisine dayanan yeni bir nesne oluştururuz. Bu tamamen geçerlidir.
Şimdi ayrıca hazırla iletisini de gönderiyoruz; bu, Animal nesnesinin
özellikleri için varsayılan değerlere sahip olmasını sağlar. Varsayılan
olarak bir hayvanın 4 bacağı vardır ve sesi bilinmez (bu yüzden soru işareti).
Animal nesnemizin yeni bir örneğini oluşturmak için şunu yazmamız yeterlidir:

```
>> a := Animal yeni.
```

Şimdi 4 bacaklı, sesi bilinmeyen ve bir hazırla yöntemi olan yeni bir
Animal örneği elde ederiz. Diğer nesne yönelimli dillerde olduğu gibi
Animal nesnemizi genişletebiliriz de:

```
>> Dog := Animal yeni.
Dog olunca: ['hazırla'] yap: {
	kendi hazırla.
	öz sound := ['barks'].
}.
```

Bunu bir metin yöntemi ekleyerek kolayca sınayabiliriz:

```
Animal olunca: ['metin'] yap: {
	<- öz legs metin + öz sound.
}.
```

Hepsini bir araya getirelim:

@test13


Belirli bir başlangıç durumuna ayarlanmış bir nesne oluşturmak sık
karşılaşılan bir sorundur. Çevre ve alan hesaplamak için bir
**Rectangle** nesnesinin oluşturulması gerektiğini varsayalım.
Olası bir gösterim şöyle olabilir:


```
>> Rectangle := Nesne yeni.

Rectangle olunca: ['area'] yap: {
	<- öz uzunluk * öz width.
}.
```

Açıktır ki bir uzunluk ve genişlik belirlemek bir ön koşuldur. Bu amaçla
**uzunluk:** ve **width:** iletileri eklenebilir:


```
Rectangle olunca: ['length:'] yap: { :uzunluk
	öz uzunluk := uzunluk.
}.

Rectangle olunca: ['width:'] yap: { :width
	öz width := width.
}.

```

Bu dikdörtgen daha sonra şöyle kullanılabilir:


```
>> rectangle := Rectangle yeni length: 2, width: 3.
Çıktı yaz: rectangle area.
```

Ancak uzunluk ve genişliğin başlangıç ayarları unutulursa
bir hata iletisi oluşur:

```
>> rectangle := Rectangle yeni.
Çıktı yaz: rectangle area.
```

şu hatayı üretir:

```
Anahtar bulunamadı:uzunluk
```

Bunu önlemek için bir dikdörtgenin her zaman bir başlangıç uzunluğuna
ve genişliğine, örneğin 0'a, sahip olması tercih edilir. Bu durumda
**yeni** iletisini **geçersiz kılmak** gerekir.

@test610

yeni iletisini geçersiz kılarsak temelde bir **sınıfı** taklit etmiş oluruz.

XOScript dünyası, programınızın en başından kullanabileceği çok çeşitli
nesnelerle doludur. Sonraki bölümlerde bu çekirdek nesnelerin tümü
ele alınacaktır.

## Anlık görüntüler

Bir nesneyi (geçerli durumuyla birlikte) diske şu şekilde kaydedebilirsiniz:

```
myobject save-as: ['saved.bin'].
```

Nesneyi diskten yeniden yüklemek için:

```
>> myobject := Nesne load-from: ['saved.bin'].
```

Anlık görüntüler belirli bir durumu kaydetmek veya performansı artırmak için
kullanılabilir. Bir anlık görüntüyü yüklemek sözcük çözümlemesini, ayrıştırmayı
ve uygulama kurulumunu ortadan kaldırır.
Ayrıca gelecekte anlık görüntülerle, belirli kalıpların iyileştirilmesi
veya sık kullanılan yolların algılanıp iyileştirilmesi gibi ek performans
avantajları da sunulabilir.

{{warning}}
Anlık görüntüler deneysel bir özelliktir; üretimde kullanmayın.
Deneysel özellikleri etkinleştirmek için -D EXPERIMENTS ile derleyin.
{{/warning}}


@test712

# Hiç Nesnesi

{{messages}}

Hiç nesnesi
boşluğu, daha doğrusu bilginin yokluğunu temsil eder. Zaman zaman,
sonucun **hiçbir şey** olduğu durumlarda bir iletiye yanıt olarak bu
nesneyi alırsınız. **Hiç** nesnesine sorabileceğiniz en temel soru
şudur: **Hiç?**. Yanıt her zaman **Doğru** olacaktır.

```
Çıktı yaz: Hiç Hiç?.
```

sonuç:

```
Doğru
```

**Hiç** dışındaki her nesne **Yanlış** yanıtını verir. Yukarıdaki
kod parçası biraz felsefi görünebilir, ancak **Hiç** nesnesinin
kesinlikle son derece pratik uygulamaları vardır. Örneğin var olmayan
bir liste öğesini istediğinizde yanıt olarak Hiç nesnesini alırsınız.
Bir değişken bildirmek isteyip henüz bir değer belirtmek istemediğinizde
de Hiç nesnesini kullanabilirsiniz. Bunun yerine özel **Hiç** değerini
**atarsınız**. XOScript'te bir değişkeni değer vermeden bildirmeye izin
verilmez, örneğin:


```
>> değer.
```

Bunun yerine şunu yazmanız gerekir:

```
>> değer := Hiç.
```

@api_None_base

# Mantıksal Değerler

{{messages}}

Bu satırların yazıldığı sırada popüler olan çoğu programlama dilinin
aksine XOScript yalnızca tek bir Doğru nesnesi ve tek bir Yanlış
nesnesi sağlar. Açıklamak gerekirse, her **Doğru** yazdığınızda yeni
bir nesne oluşturulmuş olmaz. Bunun yerine her zaman bir başvuru
kullanırsınız. Bu, şunu yazdığınızda:

\>\> x := Doğru.

**x**'in **Doğru** nesnesine başvurduğu anlamına gelir. Koşullu kod ve döngüler de
bu başvuruyu doğrular. XOScript'te **Doğru** ve **Yanlış** değerlerinin
anlamı sabit değildir. Aslında bir XOScript programı şöyle bir ifadeyle
epeyce sarsılır:

Doğru := Yanlış.

Bu tür eylemlerin sonucu tanımsızdır; ancak yine de geçerli bir
eylemdir ve bu nedenle resmi olarak izin verilir. Ayrıca hem **Doğru**
hem de **Yanlış** nesnesinin kök nesnesi olan bir Mantıksal nesnesi
vardır; ikisi de bu kök nesneden türetilmiştir. Ancak Mantıksal
nesnesinin kendisinin pratik bir kullanımı yoktur.

## Tuzaklar

**ve:** ile **veya:** iletilerini kullanırken dikkatli olun

```
Çıktı yaz: (Yanlış or: Doğru or: Doğru), yeni-satır.
Çıktı yaz: (Yanlış veya: Doğru, veya: Doğru), yeni-satır.
```

Şunu verir

```
Yanlış
Doğru
```
çünkü **veya:** iletisi yalnızca 1 argüman alır. İlk satır
Yanlış nesnesine **veya:veya:** gönderir; bu ileti var olmadığı için nesne
iletiyi yok sayar ve kendisini (Yanlış) döndürür. Öte yandan ikinci satır
**veya:** iletisini ve ardından başka bir **veya:** iletisini (bir zincir simgesi, yani virgül , kullanarak) gönderir.


@api_Boolean_base

# Sayılar

{{messages}}

Bir sayı yazdığınız her seferde, örneğin 9, -10 veya 3,12, XOScript
perde arkasında bu sayıları bir **Sayı** nesnesine dönüştürür. Bu Sayı
nesnesine ileti gönderebilir ya da sayıyı bir değişkene atayıp
iletileri daha sonra gönderebilirsiniz:

```
10 çift?

>> tenner := 10.
tenner çift?

```

Her iki gösterim de geçerlidir. Sayı nesnesi aşağıdaki iletilere
yanıt verir...

Bu iletilerin çoğu kendini açıklar niteliktedir ve matematiksel işlemler
veya karşılaştırmalar yapmanızı sağlar.

{{note}}
ASCII karşılıkları yerine ≤ ≥ ≠ × ve ÷ kullanabileceğinizi unutmayın.
Bu bir tercih meselesidir.
{{/note}}

İkili matematiksel iletiler (+) ile bunların anahtar sözcüklü
çeşitleri (ekle:) arasındaki fark, birincisinin işlemin sonucu olan
yeni bir sayı döndürmesi, ikincisinde ise nesnenin kendisinin
değiştirilmesidir. Bu, aşağıdaki örnekte gösterilmiştir:

@test597

Yukarıdaki örnekte b = 4 ve a = 3'tür. **ekle: 2** ile a'nın değeri
2 artırılırken, **+ 3** a + 3'e eşit yeni bir sayı oluşturur.
Aynısı çarpma gibi diğer matematiksel işlemler için de geçerlidir.
Çarpma simgesini kullandığınızda yanıt olarak yeni bir nesne alırsınız.
**çarp:** iletisini kullanırsanız sayının kendisini çarparsınız.

**arasında:ve:** iletisiyle, örneğin **Sayı
arasında: X ve: Y** ifadesinde, X ile Y arasında bir sayı elde edersiniz. Bu
şekilde herhangi bir rastgele sayı üretilebilir:

```
>> a := Sayı arasında: 1 ve: 10.
Çıktı yaz: a, yeni-satır.
```

Sürüm 1.4'ten itibaren xoscript'in yerleşik rastgele sayı üreteci,
bildiğimiz kadarıyla kriptografik olarak güvenlidir.

Bir sayıya bir **niteleyici** ekleyebilirsiniz, örneğin **6
elma**. Bir sayının tanımadığı her ileti bir niteleyici olarak kabul
edilir. Bir sayının niteleyicisini niteleyici iletisiyle
alabilirsiniz:

Niteleyici temelde Sayı nesnesiyle birlikte saklanan bir Metin
nesnesidir. Niteleyici, bir **yaz:** işleminde sayının ardından
yazdırılır. Niteleyiciler örneğin farklı para birimlerindeki tutarları
toplamak için kullanılabilir. Tutarları toplarken niteleyicileri
sorgulayabilirsiniz. Aşağıdaki program örneği bu ilkeyi tarihsel bir
döviz hesaplayıcısı kullanarak gösterir (çünkü döviz kuru oldukça
sabit kalır!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Metinler

{{messages}}

Bir metin **köşeli parantezler ve tırnak işaretleri** ['...'] arasına
her yerleştirildiğinde XOScript sizin için yeni bir metin nesnesi oluşturur. Ancak
doğru tırnak işaretlerini kullandığınızdan emin olun. Metnin başındaki
tırnak işareti sonundakinden farklıdır (bu, tek tırnağı kaçış karakteri
gerekmeden kullanmanızı sağlar).

## UTF8

xoscript'teki metinler genellikle utf8 ile kodlanmış metin içerir.
Bir metinde ikili veya utf8 olmayan içerik bulunması teknik olarak
mümkün olsa da bunun için blob kullanılması önerilir. Blob'lar
sunucu eklentisi tarafından sağlanır (ffi bölümüne bakın).
Genel olarak blob/ffi desteği eklenti/platform bazında sağlanır,
çünkü bunlar platforma ve mimariye bağlıdır (ffi/blob). Betik dilinin
çekirdeği mümkün olduğunca platformdan bağımsız kalmaya çalışır.

## Tür dönüştürme

Aşağıdaki iletileri kullanarak her nesnenin farklı türde bir
kopyasını oluşturabilirsiniz:

İleti   | Sonuç
------- | ------
sayı    | Sayıya dönüştürür
metin   | Metne dönüştürür
mantıksal | Mantıksal değere dönüştürür
  
Aşağıdaki kurallar **geçerlidir**:

ileti    | Hiç       | Mantıksal          | Sayı                  | Metin     | Diğer              
-------- | --------- | --------           | --------              | --------  | --------
mantıksal | Yanlış   | yok                | 0→Yanlış diğer→Doğru  | Doğru     | Çoğunlukla Doğru
sayı     | 0         | Yanlış→0 Doğru→1 | yok                     | ['n']→n | Çoğunlukla 1
metin    | ['Hiç']   | ['Yanlış']/['Doğru'] | ['n']               | yok       | Duruma göre

## Kopyalama

XOScript'te değerler her zaman **başvuru ile** aktarılır. Diğer dillerde
bu, değerin türüne bağlıdır; XOScript'te ise tek bir yol vardır:
başvuru ile. XOScript asla bir değerin kopyasını oluşturmaz. Bir nesneyi
kopyalamak için **kopyala** iletisini göndermeniz gerekir.

@test611

Burada çıktının Donny yerine Dolly olmasını bekleyebilirdiniz.
Ancak durum böyle değildir, çünkü her iki ad da aynı nesneye
başvurur. Bir döngüyle çalışırken de benzer bir şey olur:

@test612

Aslında XOScript **her zaman** başvuru kullanır; bu nedenle **:quantity**
üzerinde yukarıda gösterilen döngü de listedeki öğeye yapılan
başvuruyu gösterir.

Bir nesneyi kopyalamak için bu işlemi **açıkça**
belirtmeniz gerekir:

@test613

Bir metne **kopyala** tekli iletisini göndererek nesne, aynı metin
nesnesinin bir kopyasını döndürür. Sayı nesneleri, mantıksal nesneler,
listeler ve sözlükler de aynı şekilde kopyalanabilir.

Kendi kopyalama gerçekleştiriminizi de tanımlayabilirsiniz; kendi
nesnelerinizi oluşturuyorsanız bu bir zorunluluktur bile. Bir liste için
varsayılan kopyala gerçekleştirimi yüzeysel bir kopya oluşturur; aynı
öğeleri içeren yeni bir liste oluşturur.

@test614

Bu durumda 4 yalnızca kopyaya eklenir.
Ancak kopya yüzeysel olduğundan her iki listedeki nesneler
aynıdır.

@test615

Yani kopyadaki her ada 2 eklersek özgün liste de
etkilenir.

Bunu düzeltmek için bir **derin kopya** oluşturmamız gerekir. Bir liste
için böyle bir kopyalama işlemi şöyle oluşturulabilir:

@test616

Ayrıca yinelemeli iletisine de dikkat edin; bu iletinin kopyala
iletisinden önce gönderilmesi gerekir.

Bir nesnenin kopyası çoğu zaman özgün nesneyle aynı görünse de
aslında hiçbir zaman onunla aynı olmayacağını akılda tutmak çok önemlidir.
Kök nesne, nesnelerin kimliğini karşılaştırmak için kullanılabilen
bir **equal:** iletisi tanımlar. Aşağıdaki örneğe bakın:

@test617

## Örtük dönüştürme

XOScript nesneleri dönüştürmek için **örtük dönüştürme** kullanır. Örneğin
bir listeyi ekrana yazdırmak için XOScript listeye dahili olarak *metin*
iletisini gönderir. Bu, bir listeyi virgülle ayrılmış bir liste olarak
yazdırmak istediğinizde çok yararlı olabilir. *metin* iletisi
geçersiz kılınabilir:

@test620

@api_String_base
@api_Format_base


## Sunucu metinleri

Aşağıdaki Metin özellikleri Sunucu eklentisi
tarafından eklenir.

@api_String_server

# Fonksiyonlar

{{messages}}

Kodu { ile } arasında gruplayabilirsiniz; bu durumda kod bir fonksiyon olur.
xoscript'te bazen görev terimini ya da yalnızca
kod bloğu terimini de kullanırız.

Bir fonksiyonu *başlat* iletisini göndererek çalıştırabilirsiniz.


```
{ Çıktı yaz: 123, yeni-satır. } başlat.
```

Fonksiyonunuz argüman alıyorsa **uygula:** kullanın.

```
{ :a Çıktı yaz: a, yeni-satır. } uygula: a.
```

Aşağıdaki örneklere de bakın.
Basit mimari nedeniyle bir fonksiyonun yalnızca tek bir
dönüş noktası olabilir. Koşullarda ek yükten veya aşırı iç içe
yapılardan kaçınmak için bir prosedür kullanabilirsiniz (bu, 1 argümanıyla
çarpma işaretini kullanmakla aynıdır):

```
{
  (a = 1) doğru: { x := 1. }, kır.
  (a = 2) doğru: { x := 2. }, kır.
} prosedür.
```

Bu şekilde a = 1 ise (a = 2) değerlendirilmez.
Ayrıca bu şekilde iç içe doğru iletilerine gerek kalmaz.
Koşulları iç içe yazdığınızı fark ettiğinizde
prosedür iletisini düşünün. Kodunuzu
okumayı kolaylaştırabilir.


İşte önemli bir tuzak:

```
{
	Yanlış yanlış: {
		Çıktı yaz: ['End the loop.'].
	}, kır.
	
	Çıktı yaz: ['Dont show me.'].

} prosedür.

```

Bu durumda 'Dont show me' metni gösterilir.
Çünkü **kır** iletisi Yanlış nesnesine gönderilir. Bir kırma işlemi
yürütmek istiyorsanız, iletinin **Doğru** nesnesine gönderilmesi gerekir.
 

```
{
	Yanlış değil doğru: {
		Çıktı yaz: ['End the loop.'].
	}, kır.
	
	Çıktı yaz: ['Dont show me.'].

} prosedür.

```

Beklendiği gibi çalışır.

## İstisnalar

İstisnalar şu şekilde ele alınabilir:

```
{ Task 1 } yakala: { Task 2 }, başlat.
```

Programınızda bilerek bir hata oluşmasını da sağlayabilir ve
böylece işleyici bloğu etkinleştirebilirsiniz. Bu, sonraki örnekte
gösterildiği gibi geçerli göreve **hata:** iletisi gönderilerek
yapılır:

```
{
bu-görev hata: ['Whoops!'].
} yakala: { :mistake
Çıktı yaz: mistake.
}, başlat.
```

## Değer enjekte etme

XOScript görevlere değer enjekte etme olanağı sunar. Şimdi aşağıdaki
göreve bir göz atın:

```
>> sending := {
	Newsletter alıcı: öz recipient.
}.
sending ayarla: ['recipient']
değer: ['info@recipient.org'].
sending başlat.
```


Bu örnek, bir e-posta adresine veya **recipient** (alıcı) değişkenine bülten
gönderen hayali bir görevi göstermektedir. Bu alıcı, görev başlatılmadan
önce, göreve dışarıdan **ayarla:değer:** iletisi gönderilerek göreve
enjekte edilebilir. Böylece **recipient** değeri görevde önceden
ayarlanmış olur. Bu değer değiştirilebilir ve görev daha sonra yeniden
çalıştırılabilir. Bu, Görev nesneleri kullanılırken yararlı bir yöntemdir.

## Boş fonksiyonlar

Boş görevlere izin verilmez. Teoride boş bir görev şöyle görünürdü:
**{}**; ancak XOScript bunu bir dil hatası olarak görür. Boş bir görev
bildirmek istiyorsanız Hiç nesnesini kullanabilirsiniz:

```
>> task := Hiç.
```

Bu gerçek bir görev değil, bir Hiç nesnesi olsa da yine de bir başlat
iletisi gönderilebilir:

```
>> answer := task başlat.
```

Aslında bu şununla aynıdır:

```
>> answer := Hiç başlat.
```

**Hiç** nesnesi **başlat** iletisini tanımadığından yanıt olarak
kendisini döndürür ve yanıt yine **Hiç** olur.
Dolayısıyla boş bir göreve gerek yoktur. XOScript programlama dilinin
zarif tasarımı sayesinde bunun için doğrudan Hiç nesnesini
kullanabilirsiniz.

## Dinamik kapsam

Bir Fonksiyon bir değişkene ihtiyaç duyup onu bulamadığında,
kendisini **çağıran** Fonksiyonun değişkenlerini denetler
ve Fonksiyon zinciri boyunca yukarı doğru denetlemeye devam eder.
Bu arama süreci değişken bulunana kadar sürer.
Değişken yine de bulunamazsa bir hata iletisi görüntülenir. Bir değişkeni
bu şekilde arama yöntemine **Dinamik Kapsam** denir.

Bu ilkeyi göstermek için:

@test618

@api_Code_base

# Kök Nesne

{{messages}}

**Nesne** adlı nesne, XOScript'teki tüm nesnelerin kök nesnesidir
ve dilin çekirdek özelliklerini sağlar.

En sık gönderilen ileti, bir nesnenin işlevlerini genişleten
**olunca:yap:** iletisidir. Bu ileti kök nesne tarafından alınır;
kök nesne de belirtilen görevi iletiye bağlar ve böylece türetilmiş
nesneyi genişletir.

## Her şeyi yakalayan yöntemler

Normalde nesnedeki bir yönteme karşılık gelmeyen bir ileti
gönderirseniz, ileti yok sayılır. Ancak ileti nesne tarafından
anlaşılmadığında çağrılacak, **sihirli yöntemler** veya **her şeyi yakalayan**
yöntemler olarak adlandırılan yöntemler belirtebilirsiniz.

4 adet her şeyi yakalayan yöntem vardır. Her ileti belirli
bir argüman sayısına karşılık gelir.

Her şeyi yakalayan ileti | Argüman sayısı
-------------------- | -------------------
yanıtla:             | 0
yanıtla:ve:          | 1
yanıtla:ve:ve:       | 2
yanıtla:ve:ve:ve:    | 3


@test619

## Programla oluşturulan iletiler

Bir ileti doğrudan bir nesneye gönderilmek yerine bir değişken
aracılığıyla da gönderilebilir. Bunun için
**ileti:argümanlar:** iletisini kullanırsınız.

@test396

@api_Object_base

# Listeler

{{messages}}

XOScript iki tür koleksiyon bilir: *listeler* ve *sözlükler*.
**Listeler**, nesnelerin *sabit bir sırada* sıralanmasıdır. Sözlüklerin
bir sırası yoktur; bunun yerine bir anahtar (veya terim) ve buna karşılık
gelen değerden oluşan bir açıklama tablosuna benzerler. Listeler dizilerle
(PHP, Java, C) ve listelerle (Python) karşılaştırılabilir. Sözlükler ise
diğer programlama dillerindeki ilişkisel dizilerle (PHP) veya
sözlüklerle (Python) karşılaştırılabilir. Yeni bir Liste
oluşturmak için şunu yazın:

```
>> fibonacci := Liste yeni.
```

Bu boş liste **sona-ekle:** ile doldurulabilir:

```
fibonacci sona-ekle: 0.
fibonacci sona-ekle: 1.
fibonacci sona-ekle: 1.
fibonacci sona-ekle: 2.
fibonacci sona-ekle: 3.
fibonacci sona-ekle: 5.
fibonacci sona-ekle: 8.
fibonacci sona-ekle: 13.
```

Listeyi ekrana yazarsak:

```
Çıktı yaz: fibonacci, yeni-satır.
```

Şunu görürüz:

```
Liste ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

sona-ekle yerine listeye öğe eklemek için ; da kullanabilirsiniz:


```
>> fibonacci := Liste yeni ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Noktalı virgüllerin (;) tümü, listeye bir değer koyan
ikili iletilerdir.

## Zincirleme

Şöyle bir listeniz olduğunu varsayalım:

```
>> x := Liste yeni ; 1 ; 2 ; 3.
```

İlk ve son öğeyi silmek isterseniz iletiniz
şöyle olur:

```
x ilkini-al sonuncuyu-al.
```

Ne yazık ki önceki gösterim doğru çalışmaz.
**ilkini-al** iletisi listenin ilk öğesini döndürür; bu öğe de
**sonuncuyu-al** iletisinin alıcısı olur. Yani
**sonuncuyu-al** iletisi **x**'e değil 2'ye gönderilir.
Bu soruna olası bir çözüm, iki ayrı cümle oluşturmak
olabilir, örneğin:

```
x ilkini-al.
x sonuncuyu-al.
```

Ancak bu, özellikle ikiden fazla öğe silmeniz gerektiğinde pek
pratik değildir. Bu nedenle XOScript bu tür durumlar için alternatif
bir ileti yapısı sunar. **Alternatif** ileti yapılarında nesnelerin
yanıtları yok sayılır ve her seferinde yanıt olarak alıcı nesneyi
geri alırsınız. **Alternatif** bir ileti yapısı, bir nesneye **yap**
iletisi gönderilerek başlatılır ve **alternatif** ileti yapısı
**tamam** iletisi gönderilerek sonlandırılabilir. Gösterilen
örnekte bu şöyle uygulanabilir:

```
>> x := Liste yeni ; 1 ; 2 ; 3.
x yap ilkini-al sonuncuyu-al tamam.
```

@api_List_collections

# Sözlükler

{{messages}}

**Hem Liste hem de Sözlük koleksiyondur. Ancak bir
listenin aksine bir sözlüğün **sırası yoktur**. İkisi arasındaki bir başka fark
da bir sözlüğün nesne çiftlerinden oluşmasıdır. Bir nesne, diğer nesneyi
aramak için girdi (veya anahtar sözcük) görevi görür. Bunun iyi bir
örneği şöyle bir fiyat listesidir:


```
>> menu := Sözlük yeni
	koy: ['£5'] konum: ['apple pie'],
	koy: ['£6'] konum: ['carrot cake'],
	koy: ['£3'] konum: ['fudge'].
```

Listeye benzer şekilde, bir nesneyi eklemek için koy:konum:
iletisi kullanılır. Fark şudur: bir listenin aksine iki nesne
birbirine bağlanır. Birinci nesne, listede olduğu gibi, saklayacağınız
nesnedir. İkinci nesne ise koleksiyon içindeki konumu değil,
önceki nesnenin daha sonra geri alınmasını sağlayan **girdidir**.
Kısacası bir sözlük biraz gerçek bir sözlük gibi çalışır; yani anahtar
sözcük kullanılarak anlamı bulunabilir. Örneğin yukarıda belirtilen
listeden bir fudge'ın fiyatını almak için:

```
>> price := menu konum: ['fudge'].
```

Kısa gösterimi de kullanabilirsiniz:

```
>> price := menu ? ['fudge'].
```

Nesneleri saklamak için kullandığınız girdiler boşluk içermiyorsa
(ve önceden tanımlanmış diğer iletilerle çakışmıyorsa)
aşağıdaki gösterim de kullanılabilir:

```
>> menu := Sözlük yeni
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Yukarıdaki gösterimin biraz daha doğal okunduğuna şüphe yok.
Bir fudge'ın fiyatını
istemek için aşağıdaki basitleştirilmiş gösterim kullanılabilir:

```
>> price := menu fudge.
```

@api_Dict_collections

# Dosya

{{messages}}

**Dosya** nesnesi dosya sistemine temel erişim sağlar.
Bu nesneyi tüm dosyaları tek seferde bir değişkene okumak
veya değişkenleri tek seferde dosyalara yazmak için kullanabilirsiniz.
Satır satır okuma da desteklenir. Bunlar bir betik dilindeki en
yaygın dosya G/Ç işlemleridir. Gelişmiş dosya işlemleri, sunucu
eklentisi veya ayrı bir G/Ç eklentisi üzerinden FFI kullanılmasını gerektirir.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Tarih/Saat

{{messages}}

XOScript, zaman ve tarihin yapılandırılmış bir gösterimi için
**An** nesnesini kullanır. Yeni bir An nesnesi ekrana yazdırıldığında
geçerli tarih ve saat gösterilir:

```
Çıktı yaz: An yeni, yeni-satır.
```

Şuna benzer bir sonuç verebilir:

```
2020-10-10 12:16:39
```

Zamanın tek tek bileşenlerini okumak da kolaydır. Örneğin yalnızca
geçerli yılı bilmek gerekiyorsa, ana **yıl** iletisi gönderilebilir;
yanıt da yalnızca yılı içeren bir Sayı nesnesi olacaktır:

```
>> m := An yeni.
Çıktı yaz: m yıl, yeni-satır.
```

@api_Moment_system

# Program/Standart Çıktı

{{messages}}

Program nesnesi o anda çalışan uygulamayı temsil eder. Bu nesne
sistem komutlarını çalıştırma, alt programları dahil etme, argümanları
okuma ve daha fazlası için işlevler sunar. Sistemle ilgili tüm işlevler.

## Standart Çıktı

Çıktı, standart çıktı nesnesidir. Temelde iki yöntemi vardır:
**yaz:** ve **yeni-satır**. yaz: iletisi bir metni stdout'a göndermek
için kullanılır, yeni-satır iletisi ise bir satır sonu karakteri yazdırır.
**yeni-satır** yerine \\n de kullanabilirsiniz.

Örnek:

```
Çıktı yaz: ['Hello World'], yeni-satır.
```

sonuç:

```
Hello World
```

## Modüller/Eklentiler

XOScript dünyası, modüller kurularak yeni sistem nesneleriyle
genişletilebilir. Modül dosyası (genellikle .so sonekli bir dosya)
mods klasörüne yerleştirilerek XOScript dünyasına yeni bir sistem
nesnesi eklenebilir.

Eklenti modülü aracılığıyla kullanıma sunulan nesneye bir ileti
gönderdiğinizde, modül XOScript tarafından otomatik olarak yüklenir.

Eklentileri kendiniz de yazabilirsiniz. Eklentiler C programlama
dilinde yazılır. Kaynak kod paketinde src/plugins/example altında
örnek bir eklenti bulabilirsiniz.


## Yansıma

Program çalışırken sistemi keşfetmenin
çeşitli yolları vardır. XOScript, hangi nesnelerin bulunduğunu ve bu
nesnelerin hangi iletilere yanıt verdiğini belirlemek için birkaç yöntem
içerir. İlk olarak, her nesneye ne **tür** olduğu sorulabilir;
ancak XOScript'te türler değiştirilebilir olduğundan güvenilir değildir.

Program nesnesine belirli bir nesnenin programda zaten bulunup
bulunmadığını sormak da mümkündür:

```
Program Tool doğru: { ... }.
```

Nesne adı tek bir simgeden oluşuyorsa, karışıklığı önlemek için
aşağıdaki gösterimi kullanmak en iyisidir:

```
Program bul: ['X'], doğru: { ... }.
```

Nesneler hakkında soru sormanın yanı sıra Program nesnesine iletiler
hakkında soru sormak da mümkündür. Örneğin **Sayı** nesnesinin
**arasında:ve:** iletisini bilip bilmediği, aşağıda gösterildiği
şekilde sorulabilir:

```
Program Number: ['between:and:'], yeni-satır.
```

@api_Program_system

# sunucu

{{messages}}

xoscript'teki Sunucu eklentisi, sunucu tarafı uygulamalar oluşturmak
için işlevler sunar. Sunucu eklentisini yüklemek için
şunu kullanın:

```
Server hazırla.
```

Kolaylık sağlamak için webtools.xo ve template.xo dosyalarının
da yüklenmesi önerilir.

```
Program kullan: ['webtools.xo'].
Program kullan: ['template.xo'].

```

## Sunucu ayarları

Aşağıdaki sunucu ayarlarını yapabilirsiniz:

```
	# default values are given
	# so if you do not set anything these
	# values are used...

	Program 
	ayar: ['max-postfields']
	değer: 40.

	Program 
	ayar: ['max-contentlength']
	değer: 2000000. # 2MB

	Program 
	ayar: ['max-time']
	değer: 5000. # 5sec

```

## Merhaba Dünya

Apache2, NGINX, OpenHTTPD veya bilinen herhangi bir başka sunucu gibi
standart bir CGI sunucusuyla kullanabileceğiniz çok basit bir web
programı aşağıdadır.

```
#!/bin/xo

Server hazırla.
Program kullan: ['webtools.xo'].

>> web-document := Web-Belgesi yeni.

web-document çıktıla: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Web-Belgesi nesnesini kullanmak istemiyorsanız sorun değil, ancak
bu durumda HTTP başlıklarını kendiniz yazmanız gerekir:

```
#!/bin/xo
Çıktı yaz: ['Content-type: text/html; charset=utf-8 \n\n'], yeni-satır.
Çıktı yaz: ['hello world!'], yeni-satır.
``` 

## İstek

HTTP-İstek nesnesi GET/POST/COOKIE ve UPLOAD verilerini almak için
kullanılabilir:

```
>> istek  := HTTP-İstek yeni.
>> search   := istek get: ['search']. # ?search=books
>> password := istek post: ['password']. # from form
>> selected := istek get-liste: ['sel[]']. #?sel[]=1&sel[]=2
>> selected := istek post-liste: ['sel[]'].
>> cookie   := istek cookie: ['session-id'].
>> upload   := istek upload: ['file'].
>> temppath := upload ? 1.
>> filename := upload ? 0.
```

## Azami post/uzunluk

Varsayılan azami post alanı sayısı 40, varsayılan azami içerik
uzunluğu ise 2MB'dir. Bunları betik bazında farklı yapılandırmak için:

```
Program ayar: ['max-contentlength'] değer: 1. 
Program ayar: ['max-postfields'] değer: 1. 
```

{{note}}
İçerik uzunluğu azami değeri aşarsa
süreç sonlandırılır, çünkü yükün artık
güvenli olduğundan emin olamayız.
{{/note}}

maxtime sınırı, stdin/post verisini okumak için azami süreyi
ms cinsinden belirler.

```
Program ayar: ['max-time'] değer: 5000. # 5sec
```

Bu yalnızca post verisinin G/Ç okuması için geçerlidir ve
slowloris benzeri saldırıları önler. Herhangi bir işlemin çalışma
süresini gerçekten sınırlamak istiyorsanız Program alarm: kullanın.

## Veritabanı

Veritabanı nesnesi MariaDB/MySQL sorgulamak için kullanılabilir.
Bir veritabanına bağlanmak için:

```
>> db := Maria-DB yeni sunucu-adı: ['localhost'],
	kullanıcı: ['xo'],
	parola: ['pass123'],
	veritabanı-adı: ['xobase'],
	bağlan.

```

Bir kayıt eklemek için:

```
>> arama-parametreleri := db sorgu: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parametreler: ( Liste yeni ; ['abc'] ; 12.35 ; 6 ). # parameterized queries

{  arama-parametreleri yürüt. db onayla. }
yakala: { :e db geri-al.  }, başlat.
```

xoscript'in *yalnızca* işlemlerle (transaction) çalıştığını ve asla otomatik onaylama (autocommit) yapmadığını unutmayın.
Autocommit devre dışı bırakılamazsa bir bağlantı hatası alırsınız.
Sorgularda her zaman parametre bağlama kullanın, kullanıcı girdisini asla
doğrudan SQL'e eklemeyin.

Eklenen kaydın kimliğini şu şekilde alın:

```
Çıktı yaz: ['INSERTED: '] + arama-parametreleri insert-id, yeni-satır. # insert id
```

Kayıtları getirmek için:

```
>> arama-parametreleri :=
db
	sorgu: ['SELECT * FROM book order by id desc limit 2'], 
	getir: { :row 
		Çıktı yaz: row id + [' '] + row description + [': '] + row price, yeni-satır.
	}. # fetching rows

```

## Oturumlar

Kalıcılık için bir oturum nesnesine veri kaydedebilir ve oradan veri alabilirsiniz.
Önce yeni bir **Web-Belgesi** oluşturun. Web-Belgesi nesnesi isteği,
başlıkları, HTML'yi ve oturumu bir araya getirir. Bunun nedeni şudur: bir web sitesini
tarayıcınızla her ziyaret ettiğinizde yalnızca HTML'yi görürsünüz. Ancak
Web-Belgesi'nin tamamı **Başlıklardan** da oluşur. Örneğin
çoğu HTTP yanıtı, tarayıcıya ardından gelen verinin HTML olarak
işlenmesi gerektiğini (ve örneğin bir dosya gibi indirilmemesi gerektiğini)
bildirmek için Content-type:text/html gibi bir başlık içerir. Oturumlar,
kullanıcı verilerini istekler arasında saklamanın bir yoludur. Bu verileri
izlemek için bir çerez ayarlamamız gerekir; bu çerez de bir Başlık aracılığıyla ayarlanır.
Bu yüzden her şey Web-Belgesi'nde bir araya gelir (çünkü o, hem başlıkları hem
de HTML'yi veya diğer verileri içeren belgenin tamamıdır).


```
# First we make a new Web Document instance
>> web := Web-Belgesi yeni.

# Now we start a session, this will generate a Header for a cookie and
# create a file to store your data, associated with that cookie
>> session := web oturumu-başlat.

# Now we can treat session like a dict
session userid: 123.
```

Oturumu yok etmek için (çıkış yaparken):

```
web oturumu-yok-et.
```

## Başlıklar

Web-Belgesi, bilinen diğer başlıkları ayarlamanıza da olanak tanır.
Örneğin kullanıcıyı başka bir URL'ye yönlendirmek istiyorsanız:

```
web git: ['/other.html'].
```

Perde arkasında bu komut, tarayıcıya belirtilen hedef adrese gitmesini
bildirmek için diğer verilerinizle veya HTML'nizle birlikte gönderilecek
HTTP başlığını da oluşturur.

Özel bir başlık eklemek için:

```
web başlık: ( 
	HTTP-Başlığı yeni
	anahtar: ['Content-Length']
	değer: 400
).
```

Bir 404 sayfası göstermek için:

```
web bulunamadı: ['OOps..'].
```


## Şablonlar

Varsayılan şablon sistemi çok basittir. Yeni bir şablon sözdizimi
öğrenmeniz gerekmez. Ayrıca şablon motoru sunum ile iş mantığı
arasında gerçek bir ayrım sağlar.

Bir dosyadan şablon oluşturmak için:

```
>> tpl := web şablon: ['templates/ux.tpl'].
```

Şablon sistemi işaretleyiciler kullanır.
Üç tür işaretleyici vardır: kesme işaretleyicileri, yapıştırma işaretleyicileri ve
yuva işaretleyicileri. Temel fikir gerçekten basittir: kesme işaretleyicileriyle
belirlenen alanları kesip çıkarır ve bunları yapıştırma işaretleyicileriyle
belirlenen alanlara yapıştırabilirsiniz. Yuva işaretleyicilerine metin
enjekte edebilirsiniz.

Örneğin aşağıdaki şablon verildiğinde, mücevheri mücevher kutusuna
koyalım ve bir fiyat etiketi ekleyelim.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Bunu şu şekilde yapabilirsiniz:

```
>> gem := tpl kes: ['gem'], kopyala.
gem price: 99.
tpl yapıştır: gem konum: ['jewels'].
web çıktıla: tpl arındır.
```

Son satır, şablonu gerekli HTTP başlıklarıyla birlikte bir metin olarak
istemciye gönderir.

Sonuç:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

Kullanıcıların yüklediği dosyaları güvenli bir şekilde sunmak için passthru'ya güvenebilirsiniz:

```
>> uploaded := ['smile.gif'].
Server aktar: uploaded önek: ['/uploads/images/'].
Program bitir.
```

Bu, kullanıcının yüklediği içeriği uygun mime türüyle sunar.
Yalnızca beyaz listedeki mime türleri desteklenir:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF ve SVG.
SVG, ZIP ve GZIP dosyaları indirme olarak gönderilir, çünkü bir SVG
aksi halde alan adınızda çalışacak betikler içerebilir.
Bu yöntem TOCTOU saldırılarını, yol geçişlerini (path traversal),
kötü amaçlı kod çalıştırmayı (enjeksiyon), sembolik bağlantı saldırılarını,
DDoS saldırılarını (dosya sınırı = 50MB), dinleme (sniffing) saldırılarını ve
diğer çeşitli güvenlik sorunlarını önler.


## JSON

Bir nesneyi JSON olarak kodlamak için:

```
>> json := ( JSON jsonify: ( 
	Sözlük yeni koy: ( 
		Liste yeni ; 1 ; 2 ; 3
	) konum: ['abc']
)).
```

JSON'u bir xoscript nesnesine çözmek için:

```
>> dict := ((JSON nesne: json) abc ? 1).
```

500'den fazla iç içe geçme düzeyine sahip JSON geçersiz olarak reddedilir.

Bir Sözlüğü doğru başlıklarla doğrudan json olarak çıktılamak için:

```
web json: dict.
```


## Düzenli ifadeler

Bir desen oluşturarak düzenli ifadeler kullanabilirsiniz.
Örneğin köprülerin href ve target değerlerini eşleştirmek için:

```
Desen yeni: ['href="([^"]+)" target="([^"]+)"'].
```

Şimdi deseni konu metnine şu şekilde uygulayın:

```
pattern eşleş: konu yap: { :m :x .... }
```

Tam örnek:

```
>> konu := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> pattern := Desen yeni: ['href="([^"]+)" target="([^"]+)"'].
>> result  := pattern eşleş: konu yap: { :m :x
	Çıktı yaz: m, yeni-satır.
	Çıktı yaz: x, yeni-satır.
	<- ['XXX'].
}.
Çıktı yaz: result, yeni-satır.
```

## Ağ işlemleri

Bir web isteği yapmak için Ağ nesnesini kullanın.
Ağ nesnesi, veri olarak Hiç göndermediğiniz sürece her zaman bir POST
isteği gönderir; Hiç gönderirseniz bir GET isteği gönderir.


```
Ağ 
post: Hiç 
hedef: ['https://redbeanphp.com'].
```

## Şifreleme

Sunucu eklentisi XChaCha20 ve Argon2 tabanlı şifreleme ile birlikte gelir.

Örnek:

```
>> encrypted := Kasa şifrele: ['hello'] anahtar: ['world'].
>> decrypted := Kasa şifrele: encrypted anahtar: ['world'].
```

## Jetonlar

Belirli uzunlukta kriptografik olarak güvenli bir jeton üretmek için:

```
>> mytok := Kasa jeton: 40.
```

Bu, 40 karakterlik bir jeton üretir.

## Biçimlendirme

Biçim nesnesi, doldurma veya sıfır ekleme gibi verileri biçimlendirmenize
olanak tanır. printf sözdizimini kullanır.

```
>> fmt := Biçim yeni: ['%06.0f'].
fmt uygula: 56. # gives 000056
```

Bir biçim tek bir dönüştürme içerebilir ve bu dönüştürme değere uymalıdır;
aksi halde bir hata alırsınız:

- bir metinle `uygula:`: `%s`
- bir sayıyla `uygula:`: `%f`, `%e`, `%g` veya `%a`
- bir sayıyla `uygula-tamsayı:`: `%d`, `%i`, `%o`, `%u`, `%x` veya `%c`

Bir istekten gelen değerler metindir. Birini sayı olarak biçimlendirmek için
önce dönüştürün:

```
fmt uygula: (istek get: ['amount']) sayı.
```

## Kodlayıcılar

Çeşitli kodlayıcılar ve kod çözücüler mevcuttur.
url kodlayıcı, bir url'yi HTML'de bağlantı olarak kullanılmak üzere hazırlar:

```
Server url-kodla: ['https://example.com?a=6&b=1 2'].
```

Kullanıcı girdisini XSS enjeksiyonu riskine girmeden HTML'nize
güvenli bir şekilde eklemek için her zaman şunu kullanın:

```
Server html-kodla: ['<harmless>'].
```

Bir yuva işaretleyicisine yazdığınızda şablon motorunun her zaman html
kodlaması yaptığını unutmayın. Yani şablon sistemini kullanıyorsanız
bunu kullanmanız gerekmez.

## E-posta gönderme

Bir e-posta göndermek için mailtools.xo kütüphanesini kullanın.

Örnek:

```
Server hazırla.
Program kullan: ['mailtools.xo'].

>> e-mail := HTML-Eposta yeni.
>> img := e-mail iliştir: ( Dosya yeni: ['myimage.png'] ).

e-mail
gönderen: ['xo@xoscript.com'] ad: ['xo'],
alıcı: ( Liste yeni ; ['xo2@xoscipt.com'] ),
konu: ['xoxo'],
gövde: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), gönder.

```



## Bağlama

bağla: iletisini kullanarak libffi aracılığıyla harici bir kütüphaneyi
programınıza bağlayabilirsiniz. Ayrıntılar için ffi bölümüne bakın.


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

FFI platform/eklenti bazında sağlanır, çünkü alttaki sistem
mimarisine bağlıdır; çekirdeğin yapmaması gereken bir şeydir bu.
Sunucu eklentisi uyumlu bir ffi/blob gerçekleştirimi sunar.
Varsayılan olarak çekirdek hedef platforma stdin/stdout,
sınırlı dosya G/Ç hizmetleri ve kabuk (Program sistem:) aracılığıyla bağlanır.
Ek bütünleştirme, sunucu eklentisi gibi uygulama odaklı eklentiler
aracılığıyla ffi/blob tarafından sağlanır.

FFI, Foreign Function Interface (Yabancı Fonksiyon Arayüzü) anlamına gelir. Başkalarının
farklı programlama dillerinde yazdığı ve DLL, SO veya Dylib dosyaları aracılığıyla sağlanan
işlevleri kullanmanıza olanak tanır. Bunlar çok çeşitli fonksiyonlar olabilir ve bu yöntemle
erişilebilen çok geniş bir işlev yelpazesi vardır.
Bir örnekle başlayalım:

```
Server bağla: (
 Liste yeni ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Liste yeni ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s serbest-bırak.
```

Bu kodun sonucunda komut satırında şunu görürsünüz:
FFI has 3 letters.
Şimdi muhtemelen "Bu kadar basit bir şey için ne çok kod" diye düşünüyorsunuz.
Yani bunu bir Gui show komutuyla çözemez miydik? Yanıt kesinlikle evet!
Ancak bu, açıklayıcı bir örnek olarak düşünülmüştür.
FFI genellikle daha karmaşık görevler için kullanılır, ancak bunlar iyi
örnek olmaz; bu yüzden basit bir şey seçtim.

bağla: yönteminin argümanları:

- Argüman 1: Kullanmak istediğiniz DLL veya SO dosyası.
- Argüman 2: O dosyada bağlamak istediğiniz fonksiyon.
- Argüman 3: Fonksiyonun argümanlarının veri türlerinin adlarını içeren bir liste.
- Argüman 4: Fonksiyonun dönüş türünün adı.
- Argüman 5: Bu fonksiyonu bağlamak istediğiniz nesnenin adı (yoksa otomatik olarak
oluşturulur).
- Argüman 6: Bu fonksiyonun bağlanacağı ileti.

Yukarıdaki örnekte libc.so içindeki printf fonksiyonunu bağlamak istiyoruz. Veri
türü adlarını, bağlandığınız yazılımın belgelerinde bulabilirsiniz. Kullanılabilen türler şunlardır:
void, pointer, float, double, int, uint, char, uchar, intX ve uintX;
burada X 8, 16, 32 veya 64 olabilir.

Bu türler, veriyi saklamak için gereken bayt sayısını belirtir. printf için
Printf adlı yeni bir nesneye ve template:number: iletisine bağlanıyoruz. Dış
fonksiyonu kullanmadan önce XOScript lehçesine çevirirsiniz. template:number: iletisi
ilk parametre olarak şablon metnini içeren bir arabellek bekler. Bu arabelleği,
belleği elle ayırmanıza olanak tanıyan bir Blob nesnesiyle oluşturuyoruz. Bu belleği
daha sonra serbest-bırak iletisiyle serbest bırakmak sizin sorumluluğunuzdadır.

Bir bellek blob'unu çeşitli şekillerde doldurabilirsiniz. Örneğimizde onu metinle
dolduruyoruz, bu yüzden utf8: iletisini kullanıyoruz (UTF-8, metni baytlara dönüştüren
bir kodlamadır). Bir blob'u bayt değerlerinden oluşan bir liste vererek bytes: ile de
doldurabilirsiniz. Bir blob'un içeriğini okumak için başlangıç:uzunluk: kullanın.
Baytları bir liste olarak geri alırsınız. Hatta bir dizi C türü vererek struct:
iletisiyle bir Blob kullanarak bir C yapısı (struct) bile oluşturabilirsiniz. Bu, dış bir
yazılım kütüphanesinde bir yapıya işaretçi bekleyen bir C fonksiyonunu çağırırken
gerekli olabilir.

{warning}
Blob'ları kendiniz serbest bırakmanız gerekir.
Blob'lar çöp toplayıcı tarafından temizlenmez.
{/warning}

Blob'lar kütüphanelerdeki dış fonksiyonlarla paylaşılabildiğinden çöp
toplayıcı tarafından otomatik olarak toplanamazlar (dış fonksiyonlar
tarafından kullanılmaya devam edebilirler veya bu dış fonksiyonlar onları
kendileri serbest bırakmak isteyebilir). Bu nedenle gerektiğinde blob'ları
kendiniz serbest bırakmanız gerekir.

Bir blob'u serbest bırakmak için:

```
myblob serbest-bırak.
```

Bir yapıyı serbest bırakmak için:

```
mystruct struct-serbest-bırak serbest-bırak.
```

Yani bir yapı için bellek bloğunu serbest bırakmak üzere iki ileti
göndermeniz gerekir: struct-serbest-bırak ve serbest-bırak.

@api_Blob_fficonnect
