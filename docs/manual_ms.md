# Asas

{{messages}}


Selamat datang ke XOScript
Projek XOScript bertujuan untuk mencipta bahasa skrip yang ringkas dan boleh diaudit.
Ringkas tidak semestinya bermaksud mudah.
Bahasa pengaturcaraan yang sudah biasa mungkin lebih mudah digunakan daripada XOScript.
Di sini, keringkasan membawa maksud yang berbeza:
keupayaan untuk membentuk model mental yang lengkap tentang bahasa ini dan kelakuannya.

XOScript direka supaya muat di dalam kepala anda.
Tatabahasanya dan bilangan konsepnya sengaja dikekalkan kecil.
Tiada kelas; objek boleh diperluas secara langsung.
Objek dihantar melalui rujukan, penyalinan dilakukan secara eksplisit,
dan fungsi mempunyai satu titik keluar sahaja.

Sebahagian daripada pilihan ini sangat berbeza daripada bahasa arus perdana.
Sebagai contoh, XOScript tidak mempunyai sistem jenis dan menggunakan skop dinamik.
Mesej yang tidak dapat dikendalikan akan diabaikan dan tidak menghasilkan pengecualian.
Pilihan ini mempunyai akibatnya dan tidak bertujuan untuk menghapuskan ralat.
Tujuannya ialah mengekalkan model asas bahasa ini supaya kecil dan konsisten.

XOScript juga boleh disetempatkan, jadi peraturan perniagaan boleh dinyatakan
dalam bahasa semula jadi dan mungkin dikongsi dengan pihak berkepentingan bukan teknikal.

Kebolehauditan bermaksud falsafah yang sama digunakan pada pelaksanaannya.
Masa jalan ditulis dalam C, dengan lexer, parser dan tree walker kecil yang ditulis tangan.
Pustaka standard dan masa jalan sebahagian besarnya mencerminkan struktur bahasa ini,
menjadikan hubungan antara kod XOScript dengan pelaksanaannya agak langsung.

Ujian juga berkait rapat dengan dokumentasi.
Setiap kaedah sepatutnya mempunyai ujian berkaitan yang boleh dimasukkan ke dalam manual,
bagi membantu memastikan dokumentasi selari dengan pelaksanaan.

XOScript tidak bertujuan untuk bersaing dengan bahasa arus perdana dari segi
ciri atau kebiasaan. Ia meneroka matlamat yang berbeza:
persekitaran pengaturcaraan yang boleh difahami oleh pembangun secara keseluruhan.

Harapannya, bahasa yang kecil dan pelaksanaan yang kecil
menjadikan perisian praktikal untuk difahami
dari bait hingga objek, dari sintaks hingga masa jalan, dan membolehkan anda menulis kod dengan
yakin kerana anda memahami apa yang berlaku di dalam
skrip dan apa yang berlaku di sebalik tabir.

Seni bina persediaan pelayan xoscript
adalah ringkas, namun fleksibel.

{{architecture.png}}

Untuk menggunakan xoscript sebagai bahasa pelayan, anda perlu memasang
pemalam pelayan dalam folder bernama /mods/server. 

Ini kerana kami suka
memisahkan bahasa teras daripada fungsi khusus pelayan,
tidak seperti PHP atau Python, misalnya. Jika tidak, kami terpaksa menghantar
segala-galanya kepada semua orang tanpa tujuan, dan itu sungguh tidak masuk akal.
Anda juga boleh memasang modul lain jika mahu. Sistem ini sangat
fleksibel.

Selain itu, sesetengah fungsi lebih baik dilaksanakan dalam bahasa skrip
itu sendiri, seperti templat dan pengendalian sesi, jadi kami turut
menyediakan pustaka template.xo dan webtools.xo untuk kemudahan anda.
Sebab semua ini ialah kami tidak tahu bagaimana anda mahu
menggunakan xoscript. Anda boleh menggunakannya sebagai bahasa skrip sisi pelayan,
tetapi juga untuk GUI, peranti terbenam atau sekadar pemprosesan kelompok.
Walaupun anda menggunakannya sebagai bahasa skrip sisi pelayan (yang
kini merupakan salah satu kegunaan utamanya), anda mungkin masih mahu
menggunakan enjin templat lain atau pengendali sesi lain.
Siapakah kami untuk menentukan bahawa anda mesti menggunakan milik kami?

Namun, salah satu kelebihan menggunakan enjin templat kami sendiri ialah
anda tidak perlu mempelajari sintaks tambahan untuk mencipta templat.
Enjin templat lalai yang disertakan bersama xoscript menggunakan pemisahan 100%
antara persembahan dan logik. Daripada sintaks templat
khas, ia hanya menggunakan sistem penanda slot yang sangat fleksibel.
Untuk maklumat lanjut, lihat bab Pelayan.

Perlu diingat, jika anda tidak mahu menggunakan enjin templat lalai atau
webtools lalai, sudah tentu anda perlu menyediakan
milik anda sendiri.

Jika anda menjalankan pelayan web dalam chroot, jail atau sejenis kotak pasir lain,
anda juga perlu memasang kebergantungan xo dalam persekitaran tersebut. Anda boleh
melihat pustaka yang diperlukan dengan menggunakan ldd (lihat manpage Linux atau BSD).
Jika anda mahu menggunakan arahan shell dalam skrip xo anda, salin juga shell
(seperti bash atau ksh) ke persekitaran ini.

Kami juga ingin menyatakan bahawa kami mengambil serius keserasian ke belakang.
Malah terdapat ciri keserasian ke belakang khas yang dipanggil
'version'. Secara umumnya, kami berhasrat supaya kod anda berjalan selama-lamanya. Jadi, anda
tidak perlu mengemas kini kod anda untuk kekal serasi dengan versi xoscript
yang lebih baharu. Matlamat kami: tulis sekali, jalan selama-lamanya.

Baki manual ini dikhaskan untuk menerangkan bahasa pengaturcaraan
xoscript secara terperinci. Skrip pelayan dibincangkan dalam bab
bertajuk Pelayan. Jika anda pembangun perisian yang berpengalaman, anda mungkin mahu
melangkau beberapa bab kerana sesetengahnya agak terlalu terperinci atau
sangat serupa dengan amalan pengaturcaraan umum. Jadi, bagi anda
yang sudah berpengalaman dengan beberapa bahasa pengaturcaraan lain,
lebih baik anda menganggap manual ini sebagai panduan rujukan.

## Persediaan Linux

Muat turun apache2 dan mariadb:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Muat turun xoscript.
Gantikan X dengan nombor versi yang betul!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Salin fail ke webroot dan /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Sunting konfigurasi apache2 anda:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Gantikan Virtualhost dengan:

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

Cipta halaman ujian:

```
sudo nano /var/www/html/test.xo
```

dan tulis atur cara ujian kecil:

```
#!/bin/xo
Server mulakan-awal.
Atur-cara guna: ['webtools.xo'].
>> web := Dokumen-Web baharu.
web keluarkan: ['Hello World'].
```

Benarkan apache2 melaksanakan atur cara anda melalui CGI:

```
sudo chmod uog+x /var/www/html/test.xo
```

Mulakan semula apache2:

```
sudo systemctl restart apache2
```

Pergi ke halaman ujian anda dalam pelayar:

```
http://localhost/test.xo
```

Anda sepatutnya melihat:

```
Hello World
```


## Persediaan OpenBSD

Sunting /etc/httpd.conf, tambah:


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

Jika anda mahu menggunakan SSL:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Untuk melindungi pertukaran kunci daripada serangan kuantum,
pilih sifer mlkem:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Tambah binari xo dan mods, serta sebarang kebergantungan, ke dalam
chroot (ketahui dengan ldd).

## Menjalankan contoh


Untuk menjalankan salah satu atur cara contoh dalam pakej:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Sebagai contoh, untuk menjalankan contoh FizzBuzz di Linux:

```
./example.sh fizzbuzz Linux
```

Untuk menjalankan contoh yang sama di OpenBSD:

```
./example.sh fizzbuzz OBSD
```

Untuk menjalankan contoh dengan binaan bersih:

```
./example.sh fizzbuzz OBSD clean
```

## Ujian unit

Untuk menjalankan ujian unit:

```
./runtests.sh
```

Untuk menjalankan ujian unit tanpa membina (hanya menguji):

```
./runtests.sh nobuild
```

## Membina

Untuk membina daripada kod sumber di Linux:

```
make clean
ISO="en" make
```

Di OpenBSD:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

Untuk membina pemalam pelayan di Linux:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

Untuk membina pemalam pelayan di OpenBSD:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Hello world

Selepas fail dipindahkan ke komputer anda, anda boleh mengekstrak fail itu
dan memulakan xo dengan menggunakan arahan berikut:

```
xo
```

Untuk menjalankan XOScript, simpan atur cara sebagai fail dengan menambah akhiran
-xo (pilihan). Di samping itu, masukkan nama fail atur cara anda
selepas arahan XOScript:

```
xo myprogram.xo
```

Apabila anda menjalankan arahan XOScript dengan fail atur cara anda sebagai
parameter, xo akan membaca dan melaksanakan fail atur cara anda.

{{note}}
Anda juga boleh memulakan atur cara anda dengan menyeretnya ke ikon xo.
{{/note}}

{{warning}}
Pada sesetengah sistem, anda perlu memberi kebenaran kepada xo terlebih dahulu
untuk memuatkan pustaka dinamik.
{{/warning}}

Mengikut tradisi, atur cara pertama dalam mana-mana bahasa
pengaturcaraan baharu ialah sejenis ucapan salam kepada dunia. Dalam XOScript, atur cara
**Hello world** sedemikian kelihatan seperti ini:

@test598

Apabila teks ini disimpan ke dalam fail, contohnya hello.xo, ia boleh dilaksanakan seperti
berikut: .

xo hello.xo

Hello world


Anda boleh melihat output atur cara dalam tetingkap hitam yang ditunjukkan di atas.
Sepanjang manual ini, paparan yang sama akan digunakan untuk menunjukkan
output.

{{note}}
Keluaran ditulis dengan huruf besar K.
Secara umumnya, objek bermula dengan huruf besar
kecuali jika ia bertindak sebagai instans (tidak mempunyai kaedah
sendiri, hanya data). Ini mencerminkan konvensyen kelas lawan instans
dalam bahasa pengaturcaraan lain.
{{/note}}


## Sintaks 

XOScript ialah bahasa pengaturcaraan *berorientasikan objek* yang *tulen*. Ini bermaksud
xoscript menganggap segala-galanya sebagai objek, oleh itu tiada
*jenis data* lain. Pada asasnya terdapat tiga tindakan rutin asas
dalam atur cara yang ditulis dalam XOScript: *menetapkan*, *menghantar mesej*
dan *menjawab*. Pertukaran mesej antara objek ialah bahagian utama
atur cara XOScript. Ketiga-tiga tindakan rutin ini digambarkan
di bawah:


Tindakan        | Contoh
--------------- | --------
penetapan       |  \>\> x := 1. 
mesej unari     | x genap?.
mesej binari    | 1 + 2.
mesej kata kunci | x dari: 0 panjang: 10.
jawapan         | <- answer.  


Bab ini akan memberi anda gambaran umum tentang bahasa XOScript
dan menerangkan prinsip asasnya. XOScript ialah bahasa yang kecil dan
diasaskan pada tiga tindakan (lihat ilustrasi) yang diterjemahkan kepada
lebih kurang enam peraturan tatabahasa. Itu sahaja yang diperlukan untuk menguasai
bahasa ini.

Jangan risau jika perkara tidak jelas dengan serta-merta: semua blok
binaan akan diterokai dalam bab seterusnya (3) dan peraturan asas akan
diulang. Walau bagaimanapun, bab ini terutamanya berfungsi sebagai
pengenalan umum kepada bahasa ini. Prinsip asas akan diterangkan secara ringkas
dan digambarkan dengan beberapa contoh yang berkaitan. Sebarang butiran
yang tertinggal akan dihuraikan kemudian.

Komen dalam XOScript diawali dengan simbol \#. Jadi baris berikut
akan diabaikan:

```
# this is just a comment
```

## Pemboleh ubah

Untuk menetapkan
pemboleh ubah, anda menggunakan simbol pengisytiharan pemboleh ubah: >>. Nama
pemboleh ubah boleh mengandungi semua tanda kecuali: <-, :=, ruang kosong,
titik, koma, titik bertindih, tanda petik [' '], dan kurungan ().
Tambahan pula, pemboleh ubah tidak boleh terdiri daripada beberapa baris. Sila ambil perhatian
bahawa pemboleh ubah tidak boleh bermula dengan nombor atau tanda tolak.

Berikut ialah contoh pemboleh ubah yang sah:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dollar'].
>> +plus := Benar.
>> user-password := ['Pssst!'].
```

Contoh pemboleh ubah yang tidak sah ialah:


```
>> -123 := ['negative number'].
>> password of user := ['Classified'].
>> password.of:user := ['Classified'].
>> ,x := 10.
```

{{note}}
Anda tidak perlu meloloskan sebarang aksara
(termasuk tanda petik, tanda petik berganda, sempadan
teks) dalam
literal teks selagi ia tidak
menimbulkan kekaburan bagi lexer.
{{/note}}

Selepas pemboleh ubah diisytiharkan, ia boleh digunakan dengan bebas. Ini bermaksud
simbol pengisytiharan hanya perlu digunakan pada kali pertama
anda menggunakan pemboleh ubah itu (pengisytiharan).

Secara lebih khusus, anda tidak boleh sesuka hati mula memberikan nilai kepada
pemboleh ubah anda *(x := 2)*, kerana anda mesti mengisytiharkan pemboleh ubah itu dahulu *(\>\>
x := 2)*. Namun, setelah diisytiharkan, anda dibenarkan mengubah nilainya
tanpa menggunakan simbol pengisytiharan*(\>\> x := 2. x := 3.)*.

Ambil perhatian bahawa anda wajib memberikan nilai kepada pemboleh ubah semasa
mengisytiharkannya. Berbeza dengan bahasa pengaturcaraan lain, anda tidak dibenarkan
mengisytiharkan pemboleh ubah tanpa nilai. Setiap pemboleh ubah mesti
diikat secara eksplisit kepada nilai awal. Walau bagaimanapun, anda bebas memulakan
pemboleh ubah dengan objek **Tiada**. Dalam kes ini, pemboleh ubah boleh
dianggap kosong *(\>\> x := Tiada.)*. Ringkasnya, mengisytiharkan
pemboleh ubah tanpa nilai awal tidak dibenarkan. Jadi,

```
>> x.
```

adalah tidak sah dan akan menghasilkan mesej ralat.

{{note}}
xoscript menggunakan skop dinamik untuk pemboleh ubah. Untuk
butiran, rujuk bab Fungsi.
{{/note}}


## Literal

XOScript menganggap segala-galanya sebagai objek; iaitu semua nombor, teks
dan serpihan kod. Nombor seperti 1, 2, 100, -999 dan 1,234 ialah
objek Nombor. Semua teks di antara tanda petik tunggal ialah objek
Teks. Semua serpihan kod yang dikumpulkan di antara kurungan kerinting {...} ialah
objek Fungsi.

Literal         | Objek akar   | Contoh
--------------- | ------------ | ----------
nombor          | Nombor       | 1,2,3... 
teks            | Teks         | \['hello'\]
fungsi          | Fungsi       | { 1 + 2. }.
                
     
Objek seperti nombor dan teks sentiasa berasal daripada objek
akar. Contohnya, semua nombor berasal daripada objek **Nombor**. Semua
teks berasal daripada **Teks** dan semua serpihan kod daripada **Fungsi**. Seterusnya,
semua objek ini berasal daripada **Objek**, yang sebenarnya merupakan
objek akar bagi semua objek.


## Mesej

Pengaturcaraan dalam XOScript pada asasnya bermaksud
menghantar mesej kepada objek. Tatatanda umum untuk menghantar mesej kepada
objek adalah seperti berikut:

```
<object> <message>
```

Untuk mengetahui sama ada nombor **2**, misalnya, ialah nombor genap,
mesej **genap?** dihantar kepada objek **2**:

```
2 genap?
```

Jawapannya ialah **Benar** (sekali lagi, sebuah objek). Mesej yang tidak dikenali
biasanya diabaikan oleh objek; jadi tiada ralat akan berlaku. Sesetengah objek (contohnya
nombor atau teks) membalas mesej yang tidak dikenali dengan cara yang telah ditetapkan
(lebih lanjut tentang perkara ini kemudian).

Sesebuah objek boleh menerima tiga jenis mesej. 

Jenis           | Bilangan argumen
--------------- | -------------------
Unari           | 0      
Binari          | 1     
Kata kunci      | 1+    


Pertama, terdapat **mesej
unari**, lihat contoh di atas, yang tidak mempunyai argumen. Kedua,
terdapat **mesej kata kunci**, yang mempunyai satu atau beberapa argumen,
contohnya:

```
>> x := Nombor antara: 1 dan: 10.
```

Dalam kes ini, mesej **antara:dan:** dihantar kepada **Nombor**, yang
merupakan objek akar bagi semua nombor. Hasilnya ialah nombor rawak
antara 1 dan 10. Akhir sekali, terdapat **mesej binari**, yang hanya mempunyai
satu aksara dan satu argumen:

```
2 + 3
```

Ini kelihatan seperti hasil tambah matematik, tetapi sebenarnya ia hanyalah satu lagi mesej.
Mesej **+** dihantar kepada **2**, dengan argumen **3**, yang akan mengembalikan
jawapan **5**. Mesej binari dibenarkan ditulis tanpa titik bertindih.

Mesej binari boleh dirantaikan:

```
>> x := 3 + 2 - 1.
```

Dalam serpihan ini, **+ 2** dihantar dahulu kepada objek **Nombor** **3**, yang
menghasilkan objek Nombor **5**, selepas itu **-1** dihantar kepada nombor
ini. Pembaca yang teliti betul apabila menyedari percanggahan yang
ditunjukkan oleh protokol ini berbanding urutan operator matematik
yang lazim. XOScript mengabaikan urutan matematik demi
konsistensi dalam sistem mesejnya. Akibatnya, hasil kira:

```
2 + 3 * 5 = 25
```

bukan 17.

Ini memang disengajakan. Kurungan boleh digunakan untuk mengubah urutan:

```
2 + (3 * 5) = 17
```

Kebanyakan objek mengembalikan diri mereka sendiri sebagai hasil apabila membalas
sesuatu mesej. Ini berguna kerana ia menggalakkan dialog lanjut dengan objek
ini dengan menghantar mesej susulan kepadanya:

```
Keluaran tulis:
[' hello '] pangkas huruf-besar.
```

```
HELLO
```

Di sini, dua mesej dihantar kepada objek **Teks**: **pangkas**, diikuti
oleh **huruf-besar**.

Dalam serpihan berikut, penggunaan koma diperlukan untuk menunjukkan
bahawa mesej baharu akan datang. Jika tidak, XOScript akan keliru.

```
Keluaran tulis: ['Hello!'], baris-baharu.
```

Pertama, mesej **tulis:** dihantar kepada simbol pensel diikuti oleh
**baris-baharu**. Tanpa koma, XOScript akan menyangka bahawa anda mahu menghantar
**baris-baharu** kepada **teks** **Hello!**, satu usaha yang sia-sia.

Urutan pemprosesan mesej adalah seperti berikut: dari kiri ke kanan;
mulakan dengan mesej dalam kurungan diikuti oleh mesej unari. Seterusnya,
mesej binari dan akhirnya mesej kata kunci. Lihat contoh
di bawah:

```
Keluaran tulis: 0.5 bundarkan + (2 - 1), baris-baharu.
```

XOScript sentiasa membaca dari kiri ke kanan: pertama, mesej **tulis:**
dihantar kepada Keluaran dan diikuti oleh mesej **baris-baharu**. Di dalam
argumen itu sendiri, XOScript membaca dari kiri ke kanan, jadi **0.5 bundarkan**
kemudian **+**.

{{note}}
Mesej baris-baharu menambah aksara baris baharu pada teks.
Nama asal mesej ini (stop) diilhamkan oleh sistem telegraf.
Mesej dalam sistem telegraf 
sering menggunakan perkataan STOP untuk menandakan akhir ayat
(kerana tanda baca tidak boleh dipercayai atau mahal).
{{/note}}

Tambahan pula, **bundarkan** didahulukan berbanding **+**, kerana ia ialah
**mesej unari**. Disebabkan kurungan, **2 - 1** dikira
dahulu, selepas itu **1** ditambah kepada hasil **0.5 bundarkan** (1).

Keseluruhan proses akan memberikan hasil **2**, yang juga merupakan jawapan
yang ditulis. Selepas koma terdapat mesej baris-baharu, yang menggerakkan kursor
ke baris baharu. Sudah tentu, cara terbaik untuk memahami sepenuhnya urutan
atur cara XOScript ialah dengan berlatih.

Perlu diberi perhatian bahawa dalam XOScript, berbeza dengan banyak bahasa
pengaturcaraan lain, ruang kosong ialah bahagian asas sintaksnya.
Khususnya bagi mesej binari, ruang kosong boleh menimbulkan sedikit
kekeliruan. Sentiasa gunakan ruang kosong selepas mesej binari. Anda tidak boleh
melekatkan nombor terus pada mesej, contohnya: 

```
3 + 2
```

berbeza daripada 

```
3 +2
```

Contoh pertama (**3 + 2**) menghantar
mesej **+** kepada nombor **3**, dengan argumen nombor **2**.
Hasilnya, dalam kes ini, ialah **5**. Dalam contoh kedua (**3 +2**),
mesej unari **+2** dihantar kepada nombor **3**. Bergantung pada
konteks, ini mungkin memberikan hasil yang sangat berbeza.

## Kaedah yang tidak wujud

Menghantar mesej kepada objek akan memanggil fungsi yang telah
dilampirkan pada objek tersebut di bawah nama mesej itu. Jika anda menghantar mesej
yang tidak difahami, objek penerima akan mengabaikan mesej anda
dan sebaliknya mengembalikan rujukan kepada dirinya sendiri untuk komunikasi lanjut.
Ini dipanggil penghantaran mesej bertoleransi.

Contoh:

```
Keluaran tulis: Objek blah, baris-baharu.
```

Ini tidak akan menghasilkan ralat. Ia hanya akan mencetak teks **Objek**.


## Aliran kawalan

Dalam XOScript, tidak perlu ada peraturan tatabahasa berasingan untuk *gelung* dan
*if*. Pernyataan if hanyalah mesej **benar:** atau **palsu:** yang ringkas
kepada sama ada objek **Benar** atau objek **Palsu**:

```
2 genap? benar: {
	Keluaran tulis: ['Two is an even number'], baris-baharu.
}.
```
Dalam contoh sebelumnya, mesej **benar:** dihantar kepada **Benar** (jawapan
kepada soalan: adakah 2 nombor genap?). Sebagai argumen, satu serpihan
kod tambahan turut dihantar: objek **Fungsi**. Fungsi ini menulis
pada skrin bahawa 2 sememangnya nombor genap.

Tidak perlu juga ada peraturan penulisan berasingan untuk *gelung*. Untuk
melaksanakan serpihan kod tiga kali, hanya hantar **\*** dengan argumen
**3** kepada **Fungsi** itu:

@test5

Dalam serpihan kod ini, **i** ialah indeks. Jadi kali pertama Fungsi
dilaksanakan, **i** bersamaan 0, kali berikutnya ia dilaksanakan, **i** = 1 dan
seterusnya.

Mari kita lihat satu lagi contoh. Apabila jadual penukaran perlu
dicetak daripada *kJ* (kilojoule) kepada *kcal* (kilokalori) dengan langkah 100,
lihat di bawah untuk tatatanda yang betul:

@test599

Di sini, nombor baris semasa dihantar kepada parameter
**:line**. Pada permulaan fungsi, parameter fungsi
ditakrifkan. Parameter yang tidak digunakan kekal kosong (**Tiada**). Parameter
sentiasa diletakkan pada permulaan fungsi, terus selepas kurungan kerinting
pembuka, dan didahului oleh titik bertindih.

Mesej **selagi:** ialah gabungan *gelung* dan *syarat*.
Dua fungsi boleh dipautkan menggunakan mesej **selagi:**. Fungsi penerima
akan terus berjalan sehingga fungsi selepas titik bertindih memberikan
hasil negatif. Contoh:

@test600

Dalam serpihan kod yang digambarkan di atas, **1** ditambah kepada **x** selagi
**x** kurang daripada **5**. Apabila ini tidak lagi berlaku, fungsi kedua
akan menjawab dengan **Palsu**, dan akibatnya pelaksanaan
fungsi pertama akan tamat. Ambil perhatian bahawa **x** telah ditakrifkan di luar
fungsi dan merupakan pemboleh ubah global. Untuk mengetahui lebih lanjut tentang peraturan skop,
rujuk bab tentang Fungsi.

## Interpolasi teks

Senarai *kJ/kcal* boleh dijadikan lebih
kemas. Sebaik-baiknya, senarai itu adalah seperti berikut:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Apabila anda menukar output pilihan itu kepada templat, tatatandanya
boleh jadi:

```
number1 kJ ➞ number2 kcal
```

Ini bermaksud **number1** mewakili nilai kJ dan **number2** mewakili
nilai kcal. Beginilah cara interpolasi teks berfungsi dalam XOScript. Tiada
peraturan tatabahasa berasingan diperlukan untuk ini dalam XOScript. Hanya hantar
perkataan yang perlu diganti kepada teks, dengan teks pengganti sebagai
argumen:

```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

Hasilnya:

```
100 kj ➞ 23.9 kcal
```

Peraturan penggantian ini berfungsi untuk setiap mesej tidak ditakrifkan yang diterima
oleh objek **teks**. Setiap mesej yang tidak dikenali oleh objek
**teks** akan ditafsirkan seperti berikut: *gantikan teks mesej
dengan teks dalam argumen mesej.* Anda boleh menyesuaikan
atur cara seperti berikut:


@test601


Untuk mengelakkan kekeliruan tentang mesej yang boleh atau tidak boleh digunakan sebagai
pengganti, sebaiknya perkenalkan penanda templat seperti &lt; &gt;
untuk segmen teks dalam templat yang
perlu diganti.

## Nilai pulangan

Untuk menjawab mesej, anak panah pulangan
(*<-*) digunakan. Contoh berikut menunjukkan cara mencipta tugas
untuk mengira peratusan:

@test602

Selepas tugas itu ditakrifkan dan ditetapkan kepada pemboleh ubah **percentage**,
mesej **gunakan-pada:dan:** dihantar dengan argumen **100** dan **7**.

Ini akan melaksanakan tugas itu pada **100** dan **7**, iaitu 7% daripada 100.
Dengan menggunakan anak panah pulangan, jawapan dikembalikan daripada tugas itu kepada
atur cara utama.

## Memperluas

Walaupun kod ini sah, ia mempunyai kelemahan
kerana urutan argumen perlu diingat. Jadi, mengapa tidak
menulisnya seperti ini: *7 percent of: 100 *? Itu akan kelihatan jauh lebih
*semula jadi*. Untuk membolehkan ini, kita perlu menyesuaikan objek induk bagi
**7**, iaitu objek **Nombor**, supaya ia memahami
mesej **percent of:**. Ini boleh dicapai dengan menghantar **apabila:lakukan:** kepada
objek Nombor, seperti berikut:

@test603

Oleh sebab peratusan dalam kes ini ialah nombor itu sendiri, kita merujuk kepada diri,
kata kunci *diri*. Ringkasnya, simbol diri bermaksud: *hantar mesej
ini kepada diri-sendiri*.

# Objek

{{messages}}

Selain menyesuaikan dan meluaskan objek sedia ada, anda juga boleh mencipta
objek baharu sendiri hanya dengan menghantar mesej **baharu**. Katakan anda
mahu mencipta objek invois yang menguatkuasakan urutan
penomboran; dalam kes itu, anda memerlukan objek invois terlebih dahulu.

Memandangkan setiap objek berasal daripada objek lain, yang seterusnya
akhirnya berasal daripada objek akar bagi semua objek yang dipanggil Objek,
satu pilihan perlu dibuat tentang objek lain yang mana akan menjadi asas
objek baharu anda. Objek baharu anda mewarisi semua sifat objek
yang menjadi asasnya, iaitu objek yang pada mulanya menerima mesej
**baharu**.

Dalam contoh ini, objek yang agak neutral lebih diutamakan, iaitu objek yang tidak mempunyai
terlalu banyak sifat warisan. Ini memudahkan pilihan, kerana dalam kes
itu objek baharu boleh berasaskan objek akar itu sendiri, iaitu
**Objek**. Tatatanda sistem invois yang dimaksudkan adalah seperti
berikut:

@test604

Nombor invois semasa disimpan dalam objek, sebab itulah terdapat
kata kunci **milik** yang diletakkan di hadapannya. Ini dipanggil *sifat*;
butiran lanjut akan menyusul.

Sesetengah perniagaan lebih suka memasukkan tahun ke dalam nombor
invois. Dalam kes ini, anda boleh mencipta objek invois baharu yang berasaskan
objek invois sebelumnya, tetapi yang memberi penggunanya kemungkinan untuk
memasukkan tahun tertentu:

@test605

Tidak perlu menulis pelaksanaan untuk mesej **nombor**
sekali lagi, kerana ia diwarisi daripada **objek
invois** yang ditulis sebelumnya; akibatnya, kod lama boleh diguna semula. XOScript tidak mempunyai konsep
seperti kelas dan konsep lain yang berkaitan. Ini bermaksud objek hanya
boleh mewarisi daripada objek lain, yang juga dikenali sebagai *pewarisan
prototaip*.

Sekarang, kembali kepada sifat. Sifat objek hanya boleh dicapai
dari *dalam hierarki objek*, jadi sifat ini
tidak dapat dilihat oleh objek lain.

Berbeza dengan bahasa pengaturcaraan lain, semua sifat objek
hanya kelihatan kepada objek yang mencipta sifat itu dan kepada
objek terbitan. 

Teknik yang biasa digunakan ialah menggunakan objek sebagai sejenis *pelan tindakan*,
seperti dalam kes invois yang dibincangkan sebelum ini.
Satu lagi contoh yang baik ialah **Point**. Katakan anda mencipta
atur cara komputer yang membuat pengiraan menggunakan titik pada peta. Anda
boleh membangunkan objek **Point** yang mengandungi sifat
koordinat-x dan koordinat-y, yang akan disediakan kepada
dunia luar melalui mesej:

@test606

Mesej **=** membandingkan dua titik itu menggunakan mesej **dan:**.
Perbandingan pertama menghasilkan **Benar** atau **Palsu**. Kedua-duanya ialah objek
boolean. Apabila anda menghantar mesej **dan:** kepada objek Benar, dan
objek argumen selepas titik bertindih juga **Benar**, maka anda akan
menerima jawapan **Benar** sekali lagi. Apabila salah satunya **Palsu**, anda akan
menerima jawapan **Palsu**. Ambil perhatian bahawa satu titik tidak boleh membaca koordinat
titik yang lain. Mesej perlu dihantar kepada titik yang lain untuk meminta
data ini: **x-coordinate** dan **y-coordinate**. Lagipun, seperti yang
telah diterangkan, sifat hanya boleh diperoleh dari dalam
keluarga objek itu sendiri. 

Ambil perhatian bahawa mesej **=** digunakan di sini untuk melaksanakan perbandingan
titik. Mesej lain juga boleh digunakan, seperti:
**is:** atau **equal:**, namun menggunakan semula aksara **=** kelihatan
sesuai dalam kes ini.

## Pewarisan

Anda boleh menggunakan semula kod yang ditulis sebelum ini untuk mencipta hierarki
objek. Contohnya:

```
>> Animal := Objek baharu.
>> Dog := Animal baharu.
>> Poodle := Dog baharu.
```

Dalam kes ini, **Dog** mewarisi semua kelakuan dan sifat
**Animal** dan, seterusnya, objek **Animal** mewarisi semua kelakuan
**Objek**, objek akar bagi semua objek.


## Penggantian


Dalam contoh berikut, sejenis senarai baharu dicipta:
**Combination**, yang memastikan setiap elemennya unik.
Fungsi senarai diguna semula melalui pewarisan:

@test607

Perhatikan bagaimana **red** yang kedua dikecualikan daripada senarai.

Kadangkala, kelakuan sesuatu objek mungkin perlu digantikan.
Contohnya, apabila menambah nombor dan unit ukuran perlu
diambil kira. Dalam contoh berikut, objek **Size**
dicipta. Objek ini mengembalikan nombor yang, semasa penambahan, mengambil
kira unit nombor yang hendak ditambah. Objek **Nombor**
menyemak sama ada ia melibatkan *inci* atau *kaki*. Kod pengaturcaraannya
boleh menyerupai yang berikut:

@test608

## Rekursi

Dalam contoh sebelumnya, **tanda** tambah digantikan. Ambil perhatian
bahawa akhirnya penambahan terakhir masih perlu dilakukan, yang sebenarnya
berlaku pada baris berikut:

```
>> answer := diri + (nombor x factor).
```

Jadi, bagaimanakah XOScript memahami bahawa **tanda** tambah ini merujuk kepada
logik penambahan asal?** Sebagai contoh, tafsiran lain
mungkin ialah XOScript akan berulang kali menghantar mesej yang sama kepada objek
yang sama, yang seterusnya akan menghasilkan **gelung tanpa henti**. Jelas sekali,
ini bukan niatnya. Sebaik sahaja anda menghantar mesej kepada objek
yang akan melaksanakan kod yang sama, XOScript akan menyedari,
dalam kes ini, bahawa mesej asas yang telah digantikan itulah yang dimaksudkan. Jadi, atur cara
anda akan dilindungi secara automatik daripada gelung tanpa henti jenis ini.
Walau bagaimanapun, jika memang matlamat anda untuk menjalankan fungsi yang sama dari
fungsi semasa, anda perlu terlebih dahulu menghantar mesej
**rekursif**. Dalam kes ini, hasilnya ialah gelung
tak terhingga. Namun begitu, terdapat kegunaan yang berfaedah bagi tugas rekursif,
misalnya, katakan anda mahu mengira faktorial bagi sesuatu
nombor. Dalam kes itu, hanya tambah mesej **factorial** kepada
Nombor:

@test609

Ini memerlukan rekursi. Malah, tugas yang disambungkan kepada
mesej **factorial** perlu dilaksanakan semula di dalam fungsi tersebut.
Jadi, fungsi faktorial perlu dipanggil dari dalam fungsi
faktorial itu sendiri. Sebagai peraturan, XOScript akan menghalang rutin ini,
kerana risiko berakhir dalam gelung tak terhingga. Atas sebab ini,
mesej itu mesti didahului dengan perkataan **rekursif**. Ini
dilakukan supaya XOScript sedar bahawa memang
niat anda untuk melaksanakan tugas yang sama, dan bahawa anda tidak tersilap.

## Objek seperti kelas

Walaupun xoscript tidak menyediakan kelas, meniru kelakuan seperti
kelas adalah sangat mudah. Hanya gantikan mesej baharu.

```
>> Animal := Objek baharu.
Animal apabila: ['baharu'] lakukan: {
	<- diri baharu mulakan-awal.
}.

Animal apabila: ['mulakan-awal'] lakukan: {
	milik sound := ['?'].
	milik legs  := 4.
}.
```

Dalam serpihan kod di atas, kita mencipta objek bernama Animal.
Objek ini berfungsi sebagai *pelan tindakan* untuk pelbagai jenis haiwan
seperti anjing dan kucing. Objek induk Animal ditulis
dengan huruf besar A untuk menandakan bahawa ini ialah objek seperti kelas.
Seterusnya, kita menggantikan mesej baharu dengan menulis kaedah baharu kita sendiri.
Dalam kes ini, ia menghantar mesej baharu kepada diri, diikuti oleh mesej
mulakan-awal. Oleh sebab xoscript menyekat rekursi secara lalai, ini tidak akan menyebabkan
gelung tak terhingga. Sebaliknya, ia akan menghantar mesej baharu kepada objek
induk (Objek), lalu menghasilkan instans baharu Animal. Jadi kita mencipta
objek baharu, berasaskan objek yang sama yang kita cipta kaedah baharu kita untuknya.
Ini sah sepenuhnya. Sekarang kita juga menghantar mesej mulakan-awal, yang memastikan
objek Animal mempunyai nilai lalai bagi sifat-sifatnya. Secara lalai,
seekor haiwan mempunyai 4 kaki dan bunyinya tidak diketahui (sebab itu ada tanda soal).
Untuk mencipta instans baharu Animal kita, kita boleh menulis:

```
>> a := Animal baharu.
```

Sekarang kita mendapat instans baharu Animal dengan 4 kaki, bunyi yang tidak diketahui dan
kaedah mulakan-awal. Sama seperti dalam bahasa OOP lain, kita juga boleh
meluaskan Animal kita:

```
>> Dog := Animal baharu.
Dog apabila: ['mulakan-awal'] lakukan: {
	diri mulakan-awal.
	milik sound := ['barks'].
}.
```

Kita boleh menguji ini dengan mudah dengan menambah kaedah teks:

```
Animal apabila: ['teks'] lakukan: {
	<- milik legs teks + milik sound.
}.
```

Mari kita gabungkan semuanya:

@test13


Mencipta objek yang ditetapkan dalam keadaan awal tertentu ialah
masalah yang kerap berlaku. Katakan objek **Rectangle** perlu dicipta
untuk mengira perimeter dan luas. Tatatanda yang mungkin ialah:


```
>> Rectangle := Objek baharu.

Rectangle apabila: ['area'] lakukan: {
	<- milik panjang * milik width.
}.
```

Jelas sekali, menetapkan panjang dan lebar ialah prasyarat. Untuk
tujuan itu, mesej **panjang:** dan **width:** boleh ditambah:


```
Rectangle apabila: ['length:'] lakukan: { :panjang
	milik panjang := panjang.
}.

Rectangle apabila: ['width:'] lakukan: { :width
	milik width := width.
}.

```

Segi empat tepat ini kemudian boleh digunakan seperti berikut:


```
>> rectangle := Rectangle baharu length: 2, width: 3.
Keluaran tulis: rectangle area.
```

Walau bagaimanapun, jika tetapan awal panjang dan lebar terlepas pandang,
mesej ralat akan muncul:

```
>> rectangle := Rectangle baharu.
Keluaran tulis: rectangle area.
```

akan menghasilkan ralat berikut:

```
Kunci tidak dijumpai:panjang
```

Untuk mengelakkan perkara ini, sebaiknya segi empat tepat
sentiasa mempunyai panjang dan lebar awal, contohnya 0. Jadi, dalam
kes ini, mesej **baharu** perlu **digantikan**.

@test610

Jika kita menggantikan mesej baharu, pada asasnya kita meniru **kelas**.

Dunia XOScript dipenuhi dengan pelbagai objek, yang
tersedia untuk atur cara anda sejak awal lagi. Dalam bab-bab seterusnya,
semua objek teras ini akan dibincangkan.

## Petikan keadaan

Anda boleh menyimpan objek (bersama keadaan semasanya) ke cakera dengan:

```
myobject save-as: ['saved.bin'].
```

Untuk memuatkan semula objek daripada cakera:

```
>> myobject := Objek load-from: ['saved.bin'].
```

Petikan keadaan boleh digunakan untuk menyimpan keadaan tertentu atau untuk meningkatkan prestasi.
Memuatkan petikan keadaan mengelakkan proses lexing, parsing dan persediaan aplikasi.
Selain itu, pada masa hadapan, faedah prestasi tambahan mungkin diperkenalkan
dengan petikan keadaan, seperti pengoptimuman corak tertentu atau pengesanan dan
pengoptimuman laluan panas.

{{warning}}
Petikan keadaan ialah ciri eksperimen, jangan gunakannya dalam pengeluaran.
Untuk mengaktifkan ciri eksperimen, kompil dengan -D EXPERIMENTS.
{{/warning}}


@test712

# Objek Tiada

{{messages}}

Objek Tiada
mewakili kekosongan, atau lebih tepat lagi, ketiadaan maklumat. Kadangkala,
anda akan menerima objek ini sebagai jawapan kepada mesej, sekiranya
hasilnya ialah **tiada apa-apa**. Soalan paling penting
yang boleh anda tanyakan kepada objek **Tiada** ialah: **Tiada?**.
Jawapannya akan sentiasa **Benar**.

```
Keluaran tulis: Tiada Tiada?.
```

hasil:

```
Benar
```

Sebarang objek selain **Tiada** akan menjawab dengan **Palsu**.
Serpihan kod di atas mungkin kelihatan agak falsafah, namun objek **Tiada**
sememangnya mempunyai kegunaan yang sangat praktikal. Contohnya, anda
akan menerima objek Tiada sebagai jawapan sekiranya anda meminta
elemen senarai yang tidak wujud. Anda juga boleh menggunakan objek Tiada
jika anda mahu mengisytiharkan pemboleh ubah, tetapi belum mahu menentukan nilainya
lagi. Sebaliknya, anda hanya **menetapkan** nilai khas **Tiada**. Dalam
XOScript, anda tidak dibenarkan mengisytiharkan pemboleh ubah tanpa nilai, seperti:


```
>> nilai.
```

Sebaliknya, anda perlu menulis yang berikut:

```
>> nilai := Tiada.
```

@api_None_base



# Boolean

{{messages}}

Berbeza dengan kebanyakan bahasa pengaturcaraan popular pada masa penulisan ini,
XOScript hanya menyediakan satu objek Benar dan satu objek Palsu
sahaja. Untuk menjelaskan, setiap kali anda menulis **Benar**, ini tidak bermaksud
objek baharu telah dicipta. Sebaliknya, anda sentiasa menggunakan rujukan. Ini
bermaksud apabila anda menulis yang berikut:

\>\> x := Benar.

**x** merujuk kepada objek **Benar**. Kod bersyarat dan gelung juga
mengesahkan rujukan ini. Dalam XOScript, makna **Benar** dan **Palsu**
tidak tetap. Malah, atur cara XOScript akan menjadi kucar-kacir dengan
pernyataan seperti ini:

Benar := Palsu.

Hasil tindakan sebegini tidak ditakrifkan, namun ia tetap tindakan
yang sah dan oleh itu dibenarkan secara formal. Tambahan pula, terdapat objek
Boolean, iaitu objek akar bagi **Benar** dan **Palsu**, kerana kedua-duanya
ialah terbitan objek akar tersebut. Walau bagaimanapun, objek Boolean itu sendiri
tidak mempunyai sebarang kegunaan praktikal.

## Perangkap

Berhati-hati apabila menggunakan **dan:** dan **atau:**

```
Keluaran tulis: (Palsu or: Benar or: Benar), baris-baharu.
Keluaran tulis: (Palsu atau: Benar, atau: Benar), baris-baharu.
```

Menghasilkan

```
Palsu
Benar
```
kerana mesej **atau:** hanya menerima 1 argumen. Baris pertama
menghantar **atau:atau:** kepada Palsu, yang tidak wujud, jadi objek itu mengabaikan
mesej tersebut dan mengembalikan dirinya sendiri (Palsu). Sebaliknya, baris kedua
menghantar **atau:** diikuti oleh satu lagi **atau:** (menggunakan simbol rantai, iaitu koma: ,).


@api_Boolean_base


# Nombor

{{messages}}

Setiap kali anda menulis nombor, contohnya 9, -10, atau 3,12, di sebalik
tabir XOScript akan menukar nombor ini kepada objek **Nombor**. Anda
boleh menghantar mesej kepada objek Nombor ini, atau anda boleh menetapkan nombor itu
kepada pemboleh ubah dan menghantar mesej selepas itu:

```
10 genap?

>> tenner := 10.
tenner genap?

```

Kedua-dua tatatanda adalah sah. Objek Nombor membalas mesej-mesej
berikut...

Kebanyakan mesej ini sudah jelas maksudnya dan membolehkan anda melaksanakan
operasi matematik atau perbandingan.

{{note}}
Ambil perhatian bahawa anda boleh menggunakan ≤ ≥ ≠ × dan ÷ sebagai ganti padanan ASCII-nya.
Ini soal pilihan.
{{/note}}

Perbezaan antara mesej matematik binari (+) dan
variasi kata kuncinya (tambah:) ialah yang pertama akan mengembalikan
nombor baharu, iaitu hasil operasi tersebut, manakala dengan
yang kedua, objek itu sendiri akan diubah. Ini digambarkan dalam
contoh berikut:

@test597

Dalam contoh di atas, b = 4 dan a = 3. Dengan **tambah: 2**, nilai
a dinaikkan sebanyak 2, manakala **+ 3** mencipta nombor baharu yang
sama dengan a + 3. Perkara yang sama terpakai pada proses matematik lain, contohnya
pendaraban. Dengan menggunakan simbol darab, anda akan menerima
objek baharu sebagai jawapan. Sekiranya anda menggunakan mesej **darab-dengan:**,
anda akan mendarab nombor itu sendiri.

Dengan mesej **antara:dan:**, contohnya dalam: **Nombor
antara: X dan: Y**, anda akan mendapat nombor antara X dan Y. Dengan
cara ini, sebarang nombor rawak boleh dijana:

```
>> a := Nombor antara: 1 dan: 10.
Keluaran tulis: a, baris-baharu.
```

Sejak versi 1.4, penjana nombor rawak terbina dalam xoscript
selamat secara kriptografi setakat pengetahuan kami.

Anda boleh melampirkan **unit** pada nombor, contohnya, **6
apples**. Setiap mesej yang tidak dikenali oleh
nombor akan dianggap sebagai unit. Anda boleh mendapatkan unit
sesuatu nombor dengan menggunakan mesej unit:

Unit pada asasnya ialah objek Teks yang disimpan bersama objek
Nombor. Unit juga dicetak selepas nombor dalam
arahan **tulis:**. Unit boleh digunakan untuk menjumlahkan amaun
dalam mata wang bercampur, misalnya. Semasa menjumlahkan amaun, anda boleh meminta
unitnya. Contoh atur cara berikut menggambarkan prinsip
ini dengan menggunakan kalkulator mata wang bersejarah (kerana kadar
pertukarannya kekal agak stabil!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base


# Teks

{{messages}}

Setiap kali teks diletakkan di antara **kurungan siku dan tanda petik** ['...'],
XOScript akan mencipta objek teks baharu untuk anda. Walau bagaimanapun, pastikan
anda menggunakan tanda petik yang betul. Tanda petik di
permulaan teks berbeza daripada tanda petik di hujungnya (ini membolehkan anda
menggunakan tanda petik tunggal tanpa perlu meloloskannya).

## UTF8

Teks dalam xoscript biasanya mengandungi teks berkod utf8. Walaupun
secara teknikal mungkin untuk mempunyai kandungan binari atau bukan utf8 dalam
teks, adalah disyorkan untuk menggunakan blob bagi tujuan itu. Blob
disediakan oleh pemalam pelayan (lihat bab ffi).
Secara umumnya, blob/ffi disediakan
mengikut pemalam/platform, kerana ia terikat pada platform
dan seni bina (ffi/blob). Teras bahasa skrip ini berusaha untuk
kekal sebebas mungkin daripada platform.

## Penukaran jenis

Anda boleh mencipta salinan setiap objek
dengan jenis yang berbeza dengan menggunakan mesej berikut:

Mesej   | Hasil
------- | ------
nombor  | Menukar kepada nombor
teks    | Menukar kepada teks
boolean | Menukar kepada boolean
  
Peraturan berikut **terpakai**:

mesej    | Tiada     | Boolean            | Nombor                | Teks      | Lain-lain              
-------- | --------- | --------           | --------              | --------  | --------
boolean  | Palsu     | t/b                | 0→Palsu lain→Benar    | Benar     | Kebanyakannya Benar
nombor   | 0         | Palsu→0 Benar→1 | t/b                      | ['n']→n | Kebanyakannya 1
teks     | ['Tiada'] | ['Palsu']/['Benar'] | ['n']                | t/b       | Bergantung

## Penyalinan

Nilai dalam XOScript sentiasa dihantar **melalui rujukan**. Dalam bahasa lain,
ini bergantung pada jenis nilai, tetapi dalam XOScript hanya ada satu cara,
iaitu melalui rujukan. XOScript tidak pernah membuat salinan sesuatu nilai. Untuk menyalin objek,
anda perlu menghantar mesej **salin**. 

@test611

Di sini, anda mungkin menjangkakan output Dolly, bukannya
Donny. Namun, ini tidak berlaku kerana kedua-dua nama merujuk kepada objek
yang sama. Apabila bekerja dengan gelung, sesuatu yang serupa berlaku:

@test612

Malah, XOScript **sentiasa** menggunakan rujukan, jadi pada **:quantity**,
gelung yang digambarkan di atas juga menunjukkan rujukan kepada elemen
dalam senarai.

Untuk menyalin objek, anda perlu menyatakan tindakan ini
secara **eksplisit**:

@test613

Dengan menghantar mesej unari **salin** kepada teks, objek itu
mengembalikan salinan objek teks yang sama. Objek Nombor,
objek boolean, senarai dan kamus boleh disalin dengan cara yang sama.

Anda juga boleh mentakrifkan pelaksanaan salin anda sendiri; ini malah
satu keperluan jika anda mencipta objek anda sendiri. Pelaksanaan
lalai salin bagi senarai membuat salinan cetek, iaitu ia mencipta
senarai baharu dengan elemen yang sama.

@test614

Dalam kes ini, 4 hanya ditambah kepada salinan.
Walau bagaimanapun, oleh sebab salinan itu cetek, objek dalam kedua-dua senarai
adalah sama.

@test615

Jadi, jika kita menambah 2 pada setiap nama dalam salinan, senarai
asal turut terjejas.

Untuk mengatasi perkara ini, kita perlu membuat **salinan dalam**. Tindakan salin sedemikian
untuk senarai boleh disusun seperti berikut:

@test616

Ambil perhatian juga mesej rekursif; mesej ini perlu
dihantar sebelum mesej salin.

Adalah penting untuk diingat bahawa walaupun salinan sesuatu objek
selalunya kelihatan sama seperti yang asal, ia sebenarnya
tidak akan pernah sama. Objek akar mentakrifkan mesej **equal:**,
yang boleh digunakan untuk membandingkan identiti objek. Lihat
contoh berikut:

@test617

## Penukaran tersirat

XOScript menggunakan **penukaran tersirat** untuk menukar objek. Untuk mencetak
senarai pada skrin, XOScript, misalnya, akan menghantar mesej
*teks* secara dalaman kepada senarai itu. Ini boleh menjadi sangat berguna
sekiranya anda mahu mencetak senarai sebagai senarai yang dipisahkan dengan koma.
Mesej *teks* boleh ditulis ganti: 

@test620

@api_String_base
@api_Format_base


## Teks pelayan

Ciri Teks berikut ditambah oleh
pemalam Pelayan.

@api_String_server


# Fungsi

{{messages}}

Anda boleh mengumpulkan kod di antara { dan }, lalu ia menjadi fungsi.
Dalam xoscript, kami juga kadangkala menggunakan istilah tugas atau hanya
blok kod.

Anda boleh menjalankan fungsi dengan menghantar mesej *mula*.


```
{ Keluaran tulis: 123, baris-baharu. } mula.
```

Jika fungsi anda menerima argumen, gunakan **gunakan-pada:**.

```
{ :a Keluaran tulis: a, baris-baharu. } gunakan-pada: a.
```

Lihat juga contoh-contoh di bawah.
Disebabkan seni binanya yang ringkas, fungsi hanya boleh mempunyai
satu titik pulangan. Untuk mengelakkan overhed atau sarangan berlebihan bagi
syarat, anda boleh menggunakan prosedur (yang sama dengan menggunakan
tanda darab dengan argumen 1):

```
{
  (a = 1) benar: { x := 1. }, henti.
  (a = 2) benar: { x := 2. }, henti.
} prosedur.
```

Dengan cara ini, (a = 2) tidak akan dinilai jika a = 1.
Selain itu, anda tidak memerlukan mesej benar: bersarang dengan cara ini.
Setiap kali anda mendapati diri anda menyarangkan syarat, fikirkan
mesej prosedur. Ia mungkin menjadikan kod anda
lebih mudah dibaca.


Berikut ialah satu perangkap penting:

```
{
	Palsu palsu: {
		Keluaran tulis: ['End the loop.'].
	}, henti.
	
	Keluaran tulis: ['Dont show me.'].

} prosedur.

```

Dalam kes ini, teks 'Dont show me' akan dipaparkan.
Ini kerana **henti** dihantar kepada Palsu. Jika anda mahu melaksanakan
henti, ia perlu dihantar sebagai mesej kepada **Benar**.
 

```
{
	Palsu bukan benar: {
		Keluaran tulis: ['End the loop.'].
	}, henti.
	
	Keluaran tulis: ['Dont show me.'].

} prosedur.

```

Akan berfungsi seperti yang dijangkakan.

## Pengecualian

Pengecualian boleh dikendalikan seperti ini:

```
{ Task 1 } tangkap: { Task 2 }, mula.
```

Anda juga boleh menyebabkan ralat berlaku dalam atur cara anda dengan sengaja; dan
dengan berbuat demikian, mengaktifkan blok pengendali. Ini dilakukan dengan menghantar
mesej **ralat:** kepada tugas semasa seperti yang ditunjukkan dalam ilustrasi
berikut:

```
{
tugas-ini ralat: ['Whoops!'].
} tangkap: { :mistake
Keluaran tulis: mistake.
}, mula.
```

## Menyuntik nilai

XOScript menyediakan pilihan untuk menyuntik nilai ke dalam tugas. Sekarang, lihat
tugas di bawah:

```
>> sending := {
	Newsletter kepada: milik recipient.
}.
sending tetapkan: ['recipient']
nilai: ['info@recipient.org'].
sending mula.
```


Ilustrasi ini menunjukkan tugas khayalan, yang menghantar surat berita
ke alamat e-mel atau **recipient**. Penerima ini boleh disuntik
ke dalam tugas, dari luar dan sebelum tugas dimulakan, dengan menghantar
mesej **tetapkan:nilai:** kepada tugas itu. Dengan berbuat demikian, nilai
**recipient** ditetapkan terlebih dahulu dalam tugas. Nilai ini juga boleh diubah
dan tugas itu kemudian boleh dijalankan semula. Ini kaedah yang berguna apabila menggunakan
objek Tugas.

## Fungsi kosong

Tugas kosong tidak dibenarkan. Secara teori, tugas kosong akan kelihatan seperti
ini: **{}**, namun XOScript menganggapnya sebagai ralat bahasa. Jika anda
mahu mengisytiharkan tugas kosong, anda boleh menggunakan objek Tiada:

```
>> task := Tiada.
```

Walaupun ini bukan tugas sebenar, tetapi objek Tiada, mesej mula
masih boleh dihantar:

```
>> answer := task mula.
```

Malah, ini sama dengan:

```
>> answer := Tiada mula.
```

Oleh sebab objek **Tiada** tidak mengenali mesej **mula**, ia
akan mengembalikan dirinya sendiri sebagai jawapan, menjadikan jawapannya sekali lagi **Tiada**.
Jadi, tidak perlu ada tugas kosong. Berkat reka bentuk
bahasa pengaturcaraan XOScript yang elegan, anda hanya boleh menggunakan objek
Tiada untuk ini.

## Skop dinamik

Apabila Fungsi memerlukan pemboleh ubah tetapi tidak dapat menemuinya,
ia akan menyemak pemboleh ubah Fungsi yang **memanggilnya**,
dan terus menyemak ke atas rantaian Fungsi.
Proses carian ini berterusan sehingga pemboleh ubah itu ditemui.
Jika pemboleh ubah itu masih tidak ditemui, mesej ralat akan muncul. Kaedah mencari
pemboleh ubah ini dipanggil **Skop Dinamik**.

Untuk menggambarkan prinsip ini:

@test618

@api_Code_base

# Objek Akar

{{messages}}

Objek bernama **Objek** ialah objek akar bagi semua objek dalam
XOScript dan menyediakan ciri teras bahasa. 

Mesej yang paling kerap dihantar
ialah **apabila:lakukan:**, yang meluaskan fungsi sesuatu objek. Mesej
ini diterima oleh objek akar, yang kemudiannya memautkan
tugas yang ditentukan kepada mesej itu, dan dengan berbuat demikian meluaskan objek
terbitan.

## Kaedah tangkap-semua

Biasanya, jika anda menghantar mesej yang tidak sepadan dengan
kaedah dalam objek, mesej itu diabaikan. Walau bagaimanapun, anda boleh menentukan
apa yang dipanggil **kaedah ajaib** atau kaedah **tangkap-semua** yang akan
dipanggil jika mesej itu tidak difahami oleh objek.

Terdapat 4 kaedah tangkap-semua. Setiap mesej sepadan dengan
bilangan argumen tertentu.

Mesej tangkap-semua  | Bilangan argumen
-------------------- | -------------------
balas:               | 0
balas:dan:           | 1
balas:dan:dan:       | 2
balas:dan:dan:dan:   | 3


@test619

## Mesej secara atur cara

Daripada menghantar mesej terus kepada objek, mesej juga boleh
dihantar melalui pemboleh ubah. Untuk berbuat demikian, anda menggunakan mesej
**mesej:argumen:**. 

@test396

@api_Object_base

# Senarai

{{messages}}

XOScript mengenali dua jenis koleksi: *senarai* dan *kamus*.
**Senarai** ialah penyenaraian objek dalam *urutan tetap*. Kamus tidak
mempunyai urutan, sebaliknya menyerupai petunjuk yang melibatkan kunci (atau istilah) dan
nilai yang sepadan dengannya. Senarai setanding dengan tatasusunan (PHP, Java, C)
dan list (Python). Kamus setanding dengan tatasusunan bersekutu (PHP) atau
dictionary (Python) dalam bahasa pengaturcaraan lain. Untuk mencipta
Senarai baharu, tulis:

```
>> fibonacci := Senarai baharu.
```

Senarai kosong ini boleh diisi menggunakan **tambah-di-hujung:** :

```
fibonacci tambah-di-hujung: 0.
fibonacci tambah-di-hujung: 1.
fibonacci tambah-di-hujung: 1.
fibonacci tambah-di-hujung: 2.
fibonacci tambah-di-hujung: 3.
fibonacci tambah-di-hujung: 5.
fibonacci tambah-di-hujung: 8.
fibonacci tambah-di-hujung: 13.
```

Jika kita menulis senarai itu ke skrin:

```
Keluaran tulis: fibonacci, baris-baharu.
```

Kita akan melihat:

```
Senarai ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

Sebagai ganti tambah-di-hujung:, anda juga boleh menggunakan ; untuk menambah elemen pada senarai:


```
>> fibonacci := Senarai baharu ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Koma bertitik (;) semuanya ialah mesej binari yang meletakkan
nilai ke dalam senarai.

## Perantaian

Katakan anda mempunyai senarai seperti:

```
>> x := Senarai baharu ; 1 ; 2 ; 3.
```

Jika anda mahu memadam elemen pertama dan terakhir, maka mesej
anda ialah:

```
x ambil-pertama ambil-terakhir.
```

Malangnya, tatatanda sebelumnya tidak akan berfungsi dengan betul.
Mesej **ambil-pertama** mengembalikan elemen pertama senarai, yang
seterusnya akan menjadi penerima mesej **ambil-terakhir**. Jadi,
mesej **ambil-terakhir** tidak dihantar kepada **x**, tetapi kepada 2.
Penyelesaian yang mungkin bagi masalah ini ialah membuat dua
ayat berasingan, seperti: 

```
x ambil-pertama.
x ambil-terakhir.
```

Walau bagaimanapun, ini agak tidak praktikal, terutamanya apabila anda perlu
memadam lebih daripada dua elemen. Oleh itu, XOScript menawarkan
struktur mesej alternatif untuk situasi sebegini. Dalam
struktur mesej **alternatif**, jawapan objek diabaikan
dan anda akan mendapat objek penerima kembali sebagai jawapan, setiap kali.
Struktur mesej **alternatif** dimulakan dengan menghantar
mesej **lakukan** kepada objek dan struktur mesej **alternatif**
boleh ditamatkan dengan menghantar mesej **selesai**. Dalam
contoh yang digambarkan, ini boleh digunakan seperti berikut:

```
>> x := Senarai baharu ; 1 ; 2 ; 3.
x lakukan ambil-pertama ambil-terakhir selesai.
```

@api_List_collections


# Kamus

{{messages}}

**Kedua-dua Senarai dan Kamus ialah koleksi. Walau bagaimanapun, berbeza dengan
senarai, kamus **tidak mempunyai** urutan. Satu lagi perbezaan antara kedua-duanya
ialah kamus terdiri daripada pasangan objek. Satu objek bertindak sebagai entri (atau
kata kunci) untuk mencari objek yang lain. Contoh yang baik bagi
senarai sedemikian ialah senarai harga, seperti:


```
>> menu := Kamus baharu
	letak: ['£5'] di: ['apple pie'],
	letak: ['£6'] di: ['carrot cake'],
	letak: ['£3'] di: ['fudge'].
```

Sama seperti senarai, mesej letak:di:
digunakan untuk menambah objek pada senarai. Perbezaannya ialah, berbeza dengan
senarai, dua objek dipautkan. Objek pertama, sama seperti
senarai, ialah objek yang akan anda simpan dalam senarai. Objek
kedua bukanlah kedudukannya dalam koleksi, tetapi **entri**
yang membolehkan objek sebelumnya diperoleh semula kemudian. Ringkasnya,
kamus berfungsi sedikit seperti kamus bahasa; jadi, dengan menggunakan kata kunci,
maknanya boleh ditemui. Contohnya, untuk mendapatkan harga fudge daripada
senarai yang disebutkan di atas:

```
>> price := menu di: ['fudge'].
```

Anda juga boleh menggunakan tatatanda ringkas:

```
>> price := menu ? ['fudge'].
```

Sekiranya entri yang anda gunakan untuk menyimpan objek tidak mengandungi ruang
(dan tidak bertembung dengan mesej lain yang telah ditakrifkan),
tatatanda berikut juga boleh digunakan:

```
>> menu := Kamus baharu
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Tidak syak lagi bahawa tatatanda di atas dibaca dengan lebih semula jadi.
Untuk meminta harga
fudge, tatatanda ringkas berikut boleh digunakan:

```
>> price := menu fudge.
```

@api_Dict_collections

# Fail

{{messages}}

Objek **Fail** menyediakan akses asas kepada sistem fail.
Anda boleh menggunakan objek ini untuk membaca keseluruhan fail ke dalam pemboleh ubah
sekali gus, atau menulis pemboleh ubah ke fail sekali gus. Pembacaan baris demi baris
juga disokong. Ini ialah operasi I/O fail yang paling biasa
dalam bahasa skrip. Operasi fail lanjutan memerlukan
penggunaan FFI melalui pemalam pelayan atau pemalam IO yang berasingan.

@api_File_file
@api_File_vault
@api_File_fficonnect


# Tarikh/Masa

{{messages}}

Untuk perwakilan masa dan tarikh yang berstruktur, XOScript menggunakan
objek **Detik**. Sekiranya objek Detik baharu dicetak pada skrin,
tarikh dan masa semasa akan dipaparkan:

```
Keluaran tulis: Detik baharu, baris-baharu.
```

Mungkin menghasilkan sesuatu seperti:

```
2020-10-10 12:16:39
```

Komponen masa secara individu juga mudah dibaca. Jadi,
contohnya, jika hanya perlu mengetahui tahun semasa, mesej
**tahun** boleh dihantar kepada detik itu dan, seterusnya, jawapannya ialah
objek Nombor yang hanya mengandungi tahun:

```
>> m := Detik baharu.
Keluaran tulis: m tahun, baris-baharu.
```

@api_Moment_system


# Atur-cara/StdOut

{{messages}}

Objek Atur-cara mewakili aplikasi yang sedang berjalan. Objek ini
menyediakan fungsi untuk melaksanakan arahan sistem, memasukkan sub-atur cara,
membaca argumen dan banyak lagi. Semua fungsi yang berkaitan dengan sistem.

## StdOut

Keluaran ialah objek output standard. Pada asasnya ia mempunyai dua kaedah:
**tulis:** dan **baris-baharu**. Mesej tulis: digunakan untuk menghantar teks
ke stdout, manakala mesej baris-baharu mencetak aksara baris baharu.
Sebagai ganti **baris-baharu**, anda juga boleh menggunakan \\n.

Contoh:

```
Keluaran tulis: ['Hello World'], baris-baharu.
```

hasil:

```
Hello World
```

## Modul/Pemalam

Dunia XOScript boleh diluaskan dengan objek sistem baharu, dengan
memasang modul. Objek sistem baharu boleh ditambah ke dunia
XOScript dengan meletakkan fail modul (biasanya fail dengan akhiran .so)
ke dalam folder mods. 

Apabila anda menghantar mesej kepada objek yang disediakan melalui
modul pemalam, ia akan dimuatkan secara automatik oleh XOScript.

Anda juga boleh menulis pemalam sendiri. Pemalam ditulis dalam
Bahasa Pengaturcaraan C. Anda boleh menemui contoh pemalam dalam pakej kod
sumber di bawah src/plugins/example.


## Refleksi

Terdapat pelbagai cara untuk meneroka sistem
semasa pelaksanaan atur cara. XOScript mempunyai beberapa kaedah untuk
mengesan objek yang wujud dan mesej yang dibalas oleh objek-objek
ini. Pertama, setiap objek boleh ditanya apakah **jenis**nya,
namun jenis dalam XOScript mudah diubah dan oleh itu tidak boleh dipercayai.

Objek Atur-cara juga boleh ditanya sama ada
sesuatu objek sudah wujud dalam atur cara:

```
Atur-cara Tool benar: { ... }.
```

Bagi nama objek
yang terdiri daripada satu simbol sahaja, sebaiknya gunakan
tatatanda berikut untuk mengelakkan kekeliruan:

```
Atur-cara cari: ['X'], benar: { ... }.
```

Selain bertanya tentang objek, objek Atur-cara juga boleh ditanya
tentang mesej. Contohnya, ia boleh ditanya sama ada
objek **Nombor** mengenali mesej **antara:dan:**, dengan cara
seperti yang digambarkan di bawah:

```
Atur-cara Number: ['between:and:'], baris-baharu.
```

@api_Program_system

# Pelayan

{{messages}}

Pemalam Pelayan dalam xoscript menyediakan fungsi untuk
mencipta aplikasi sisi pelayan. Untuk memuatkan pemalam
pelayan, gunakan:

```
Server mulakan-awal.
```

Untuk kemudahan anda, adalah juga disyorkan untuk memuatkan
fail webtools.xo dan template.xo.

```
Atur-cara guna: ['webtools.xo'].
Atur-cara guna: ['template.xo'].

```

## Tetapan pelayan

Anda boleh menetapkan tetapan pelayan berikut:

```
	# default values are given
	# so if you do not set anything these
	# values are used...

	Atur-cara 
	tetapan: ['max-postfields']
	nilai: 40.

	Atur-cara 
	tetapan: ['max-contentlength']
	nilai: 2000000. # 2MB

	Atur-cara 
	tetapan: ['max-time']
	nilai: 5000. # 5sec

```

## Hello World

Berikut ialah atur cara web yang sangat ringkas yang boleh anda gunakan dengan
pelayan CGI standard seperti Apache2, NGINX, OpenHTTPD atau mana-mana pelayan
terkenal yang lain.

```
#!/bin/xo

Server mulakan-awal.
Atur-cara guna: ['webtools.xo'].

>> web-document := Dokumen-Web baharu.

web-document keluarkan: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Jika anda tidak mahu menggunakan objek Dokumen-Web, tidak mengapa, tetapi
anda perlu menulis pengepala HTTP sendiri:

```
#!/bin/xo
Keluaran tulis: ['Content-type: text/html; charset=utf-8 \n\n'], baris-baharu.
Keluaran tulis: ['hello world!'], baris-baharu.
``` 

## Permintaan

Objek Permintaan-HTTP boleh digunakan untuk mendapatkan data GET/POST/COOKIE dan
UPLOAD:

```
>> permintaan-http  := Permintaan-HTTP baharu.
>> search   := permintaan-http get: ['search']. # ?search=books
>> password := permintaan-http post: ['password']. # from form
>> selected := permintaan-http get-senarai: ['sel[]']. #?sel[]=1&sel[]=2
>> selected := permintaan-http post-senarai: ['sel[]'].
>> cookie   := permintaan-http cookie: ['session-id'].
>> upload   := permintaan-http upload: ['file'].
>> temppath := upload ? 1.
>> filename := upload ? 0.
```

## Maxpost/panjang

Nilai lalai bagi bilangan maksimum medan post ialah 40 dan panjang kandungan
maksimum lalai ialah 2MB. Untuk mengkonfigurasinya secara berbeza bagi setiap skrip:

```
Atur-cara tetapan: ['max-contentlength'] nilai: 1. 
Atur-cara tetapan: ['max-postfields'] nilai: 1. 
```

{{note}}
Jika panjang kandungan melebihi had maksimum,
proses akan dihentikan kerana kami tidak lagi dapat memastikan
muatan itu selamat.
{{/note}}

Had maxtime menentukan masa maksimum dalam ms
untuk membaca stdin/postdata.

```
Atur-cara tetapan: ['max-time'] nilai: 5000. # 5sec
```

Ini hanya terpakai pada pembacaan I/O bagi post, bagi mencegah
serangan seperti slowloris. Jika anda benar-benar mahu mengehadkan
masa pelaksanaan sebarang operasi, gunakan had-masa: Atur-cara.

## Pangkalan data

Objek pangkalan data boleh digunakan untuk membuat pertanyaan pada MariaDB/MySQL.
Untuk menyambung ke pangkalan data:

```
>> db := Maria-DB baharu hos: ['localhost'],
	nama-pengguna: ['xo'],
	kata-laluan: ['pass123'],
	nama-pangkalan-data: ['xobase'],
	sambung.

```

Untuk memasukkan rekod, gunakan:

```
>> parameter-carian := db pertanyaan: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parameter: ( Senarai baharu ; ['abc'] ; 12.35 ; 6 ). # parameterized queries

{  parameter-carian laksana. db sahkan. }
tangkap: { :e db batalkan.  }, mula.
```

Ambil perhatian bahawa xoscript *hanya* berfungsi dengan transaksi dan tidak pernah melakukan autocommit.
Jika autocommit tidak dapat dinyahdayakan, anda akan mendapat ralat sambungan.
Sentiasa gunakan pengikatan parameter untuk pertanyaan, jangan sekali-kali menambah input pengguna terus
ke dalam SQL.

Dapatkan id yang dimasukkan seperti ini:

```
Keluaran tulis: ['INSERTED: '] + parameter-carian insert-id, baris-baharu. # insert id
```

Untuk mengambil rekod:

```
>> parameter-carian :=
db
	pertanyaan: ['SELECT * FROM book order by id desc limit 2'], 
	dapatkan: { :row 
		Keluaran tulis: row id + [' '] + row description + [': '] + row price, baris-baharu.
	}. # fetching rows

```

## Sesi

Untuk kegigihan data, anda boleh menyimpan dan mengambil data daripada objek sesi.
Mula-mula cipta **Dokumen-Web** baharu. Objek Dokumen-Web menghimpunkan
permintaan, pengepala, HTML dan sesi. Ini kerana, setiap kali anda
melawat laman web dengan pelayar anda, anda hanya melihat HTML. Tetapi
keseluruhan Dokumen-Web juga terdiri daripada **Pengepala**. Contohnya,
kebanyakan respons HTTP mengandungi pengepala seperti: Content-type:text/html untuk
memberitahu pelayar bahawa data yang menyusul perlu dipaparkan sebagai HTML
(dan bukan dimuat turun seperti fail, misalnya). Sesi ialah cara untuk
menyimpan data pengguna antara permintaan. Untuk menjejaki data ini, kita perlu
menetapkan kuki, dan kuki ini juga ditetapkan melalui Pengepala. Itulah sebabnya
segala-galanya bergabung dalam Dokumen-Web (kerana ia ialah dokumen
penuh yang mengandungi kedua-dua pengepala dan HTML atau data lain).


```
# First we make a new Web Document instance
>> web := Dokumen-Web baharu.

# Now we start a session, this will generate a Header for a cookie and
# create a file to store your data, associated with that cookie
>> session := web mulakan-sesi.

# Now we can treat session like a dict
session userid: 123.
```

Untuk memusnahkan sesi (semasa log keluar):

```
web musnahkan-sesi.
```

## Pengepala

Dokumen-Web juga membolehkan anda menetapkan pengepala terkenal yang lain.
Contohnya, jika anda mahu mengubah hala pengguna ke URL lain:

```
web pergi-ke: ['/other.html'].
```

Di sebalik tabir, arahan ini juga menjana pengepala HTTP untuk dihantar
bersama data atau HTML anda yang lain bagi mengarahkan pelayar menavigasi
ke alamat sasaran yang ditentukan.

Untuk menambah pengepala tersuai:

```
web pengepala: ( 
	Pengepala-HTTP baharu
	kunci-pengepala: ['Content-Length']
	nilai: 400
).
```

Untuk memaparkan halaman 404:

```
web tidak-dijumpai: ['OOps..'].
```


## Templat

Sistem templat lalai sangat ringkas. Anda tidak perlu mempelajari
sintaks templat baharu. Selain itu, enjin templat memastikan pemisahan sebenar
antara persembahan dan logik perniagaan.

Untuk mencipta templat daripada fail:

```
>> tpl := web templat: ['templates/ux.tpl'].
```

Sistem templat menggunakan penanda.
Terdapat tiga jenis penanda: penanda potong, penanda tampal dan
penanda slot. Idea asasnya sangat ringkas: anda memotong
kawasan yang dikenal pasti oleh penanda potong dan anda boleh menampalnya di
kawasan yang dikenal pasti oleh penanda tampal. Anda boleh menyuntik teks ke dalam
penanda slot.

Jadi, contohnya, berdasarkan templat berikut, mari kita letakkan
permata ke dalam kotak barang kemas dan tambah tanda harga.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Anda boleh melakukannya seperti berikut:

```
>> gem := tpl potong: ['gem'], salin.
gem price: 99.
tpl tampal: gem di: ['jewels'].
web keluarkan: tpl rapikan.
```

Baris terakhir hanya menghantar templat sebagai teks kepada klien
bersama pengepala HTTP yang diperlukan.

Hasil:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

Untuk menyajikan fail yang dimuat naik oleh pengguna dengan selamat, anda boleh bergantung pada passthru:

```
>> uploaded := ['smile.gif'].
Server teruskan: uploaded awalan: ['/uploads/images/'].
Atur-cara tamat.
```

Ini akan menyajikan kandungan yang dimuat naik oleh pengguna dengan jenis mime
yang sesuai. Hanya jenis mime dalam senarai putih yang disokong:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF dan SVG.
Fail SVG, ZIP dan GZIP dihantar sebagai muat turun, kerana SVG
boleh mengandungi skrip yang sebaliknya akan berjalan pada domain anda.
Kaedah ini mencegah serangan TOCTOU, perentasan laluan,
pelaksanaan kod berniat jahat (suntikan), serangan symlink,
serangan DDoS (had fail = 50MB), serangan menghidu dan
pelbagai isu keselamatan lain.


## JSON

Untuk mengekod objek sebagai JSON:

```
>> json := ( JSON jsonify: ( 
	Kamus baharu letak: ( 
		Senarai baharu ; 1 ; 2 ; 3
	) di: ['abc']
)).
```

Untuk menyahkod JSON kepada objek xoscript:

```
>> dict := ((JSON objek: json) abc ? 1).
```

JSON dengan lebih daripada 500 tahap sarangan ditolak sebagai tidak sah.

Untuk mengeluarkan Kamus secara terus sebagai json dengan pengepala yang betul:

```
web json: dict.
```


## Regex

Anda boleh menggunakan ungkapan nalar dengan mencipta corak.
Contohnya, untuk memadankan href dan sasaran pautan hiper:

```
Corak baharu: ['href="([^"]+)" target="([^"]+)"'].
```

Sekarang, gunakan corak itu pada teks subjek seperti ini:

```
pattern padan: subjek lakukan: { :m :x .... }
```

Contoh penuh:

```
>> subjek := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> pattern := Corak baharu: ['href="([^"]+)" target="([^"]+)"'].
>> result  := pattern padan: subjek lakukan: { :m :x
	Keluaran tulis: m, baris-baharu.
	Keluaran tulis: x, baris-baharu.
	<- ['XXX'].
}.
Keluaran tulis: result, baris-baharu.
```

## Rangkaian

Gunakan objek Rangkaian untuk melakukan permintaan web.
Objek Rangkaian sentiasa menghantar permintaan POST, kecuali jika anda menghantar Tiada sebagai
data; maka ia akan menghantar permintaan GET.


```
Rangkaian 
post: Tiada 
ke: ['https://redbeanphp.com'].
```

## Penyulitan

Pemalam pelayan disertakan dengan penyulitan berasaskan XChaCha20 dan Argon2.

Contoh:

```
>> encrypted := Peti-besi sulitkan: ['hello'] kunci: ['world'].
>> decrypted := Peti-besi sulitkan: encrypted kunci: ['world'].
```

## Token

Untuk menjana token yang selamat secara kriptografi dengan panjang tertentu:

```
>> mytok := Peti-besi token: 40.
```

Ini akan menjana token sepanjang 40 aksara.

## Pemformatan

Objek Format membolehkan anda memformat data, seperti menambah pelapik atau
menambah sifar. Ia menggunakan sintaks printf.

```
>> fmt := Format baharu: ['%06.0f'].
fmt gunakan-pada: 56. # gives 000056
```

Sesuatu format boleh mengandungi satu penukaran dan ia mesti sesuai dengan nilai,
jika tidak, anda akan mendapat ralat:

- `gunakan-pada:` dengan teks: `%s`
- `gunakan-pada:` dengan nombor: `%f`, `%e`, `%g` atau `%a`
- `gunakan-pada-integer:` dengan nombor: `%d`, `%i`, `%o`, `%u`, `%x` atau `%c`

Nilai daripada permintaan ialah teks. Untuk memformatnya sebagai nombor,
tukarkannya terlebih dahulu:

```
fmt gunakan-pada: (permintaan-http get: ['amount']) nombor.
```

## Pengekod

Beberapa pengekod dan penyahkod tersedia.
Pengekod url menyediakan url untuk digunakan dalam HTML sebagai pautan:

```
Server url-kodkan: ['https://example.com?a=6&b=1 2'].
```

Untuk menyuntik input pengguna ke dalam HTML anda dengan selamat tanpa risiko suntikan
XSS, sentiasa gunakan:

```
Server html-kodkan: ['<harmless>'].
```

Ambil perhatian bahawa enjin templat akan sentiasa melakukan pengekodan html
jika anda menulis ke penanda slot. Jadi, jika anda menggunakan sistem templat,
anda tidak perlu menggunakan ini.

## Mel

Untuk menghantar mel, gunakan pustaka mailtools.xo.

Contoh:

```
Server mulakan-awal.
Atur-cara guna: ['mailtools.xo'].

>> e-mail := E-mel-HTML baharu.
>> img := e-mail lampirkan: ( Fail baharu: ['myimage.png'] ).

e-mail
pengirim: ['xo@xoscript.com'] nama: ['xo'],
kepada: ( Senarai baharu ; ['xo2@xoscipt.com'] ),
subjek: ['xoxo'],
badan: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), hantar.

```



## Pemautan

Dengan menggunakan mesej pautkan:, anda boleh memautkan pustaka luaran kepada
atur cara anda menggunakan libffi. Untuk butiran, lihat bab tentang ffi.


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

FFI disediakan mengikut platform/pemalam kerana ia
terikat pada seni bina sistem asas, sesuatu yang
tidak sepatutnya dilakukan oleh teras.
Pemalam pelayan menawarkan pelaksanaan ffi/blob yang mematuhi piawaian.
Secara lalai, teras berhubung dengan platform sasaran
melalui stdin/stdout, perkhidmatan i/o fail yang terhad dan shell (sistem: Atur-cara).
Integrasi tambahan disediakan oleh ffi/blob melalui pemalam
berpusatkan aplikasi seperti pemalam pelayan.

FFI bermaksud Foreign Function Interface (antara muka fungsi asing). Ia membolehkan anda menggunakan fungsi yang ditulis oleh orang lain dalam
bahasa pengaturcaraan yang berbeza, yang disediakan melalui fail DLL, fail SO atau fail Dylib. Fungsi ini boleh
terdiri daripada pelbagai jenis, dan terdapat pelbagai fungsi yang tersedia melalui kaedah ini.
Mari kita mulakan dengan satu contoh:

```
Server pautkan: (
 Senarai baharu ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Senarai baharu ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s bebaskan.
```

Hasil kod ini ialah anda akan melihat yang berikut pada baris arahan:
FFI has 3 letters.
Sekarang, anda mungkin berfikir, "Banyaknya kod untuk sesuatu yang begitu mudah."
Maksud saya, tidakkah kita boleh menyelesaikannya dengan arahan Gui show sahaja? Jawapannya sudah tentu boleh!
Tetapi ini dimaksudkan sebagai contoh ilustrasi.
FFI biasanya digunakan untuk tugas yang lebih kompleks, tetapi tugas sebegitu tidak menjadi
contoh yang baik, jadi saya memilih sesuatu yang remeh.

Argumen bagi kaedah pautkan:

- Argumen #1: Fail DLL atau SO yang anda mahu gunakan.
- Argumen #2: Fungsi dalam fail itu yang anda mahu pautkan.
- Argumen #3: Senarai yang mengandungi nama jenis data bagi argumen fungsi tersebut.
- Argumen #4: Nama jenis pulangan fungsi tersebut.
- Argumen #5: Nama objek yang anda mahu pautkan fungsi ini kepadanya (jika ia tidak wujud, ia akan dicipta
secara automatik).
- Argumen #6: Mesej yang fungsi ini patut dipautkan kepadanya.

Dalam contoh di atas, kita mahu memautkan fungsi printf daripada libc.so. Anda boleh menemui nama
jenis data dalam dokumentasi perisian yang anda pautkan. Jenis yang tersedia ialah:
void, pointer, float, double, int, uint, char, uchar, intX, dan uintX,
dengan X boleh jadi 8, 16, 32, atau 64.

Jenis ini merujuk kepada bilangan bait yang diperlukan untuk menyimpan data. Bagi printf, kita memautkan kepada
objek baharu bernama Printf dan mesej template:number:. Anda menterjemah fungsi
luaran ke dalam dialek XOScript sebelum menggunakannya. Mesej template:number: menjangkakan
penimbal dengan teks templat sebagai parameter pertamanya. Kita mencipta penimbal ini menggunakan objek Blob, yang
membolehkan anda memperuntukkan memori secara manual. Anda bertanggungjawab membebaskan memori ini selepas itu
dengan mesej bebaskan.

Anda boleh mengisi blob memori dengan pelbagai cara. Dalam contoh kita, kita mengisinya dengan teks, jadi kita menggunakan
mesej utf8: (UTF-8 ialah pengekodan untuk menukar teks kepada bait). Anda juga boleh mengisi blob dengan
bytes:, dengan memberikan senarai nilai bait. Untuk membaca kandungan blob, gunakan dari:panjang:.
Anda akan mendapat bait itu kembali sebagai senarai. Anda juga boleh mencipta C-struct dengan Blob menggunakan
mesej struct:, dengan memberikan urutan jenis C. Ini mungkin perlu apabila memanggil fungsi
C dalam pustaka perisian luaran yang menjangkakan penuding kepada struct.

{warning}
Anda perlu membebaskan blob sendiri.
Blob tidak dikosongkan oleh pengumpul sampah.
{/warning}

Oleh sebab blob boleh ditukar dengan fungsi luaran daripada pustaka, blob
tidak boleh dikumpul oleh pengumpul sampah secara automatik (ia mungkin masih digunakan oleh
fungsi luaran atau fungsi luaran ini mungkin mahu membebaskannya
sendiri). Oleh itu, anda perlu membebaskan blob sendiri jika perlu.

Untuk membebaskan blob, gunakan:

```
myblob bebaskan.
```

Untuk membebaskan struct, gunakan:

```
mystruct bebaskan-struct bebaskan.
```

Jadi bagi struct, anda perlu menghantar dua mesej: bebaskan-struct dan bebaskan untuk
menyahperuntukkan blok memori.

@api_Blob_fficonnect
