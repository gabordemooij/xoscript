# Dasar-dasar

{{messages}}


Selamat datang di XOScript
Proyek XOScript bertujuan menciptakan bahasa skrip yang sederhana dan dapat diaudit.
Sederhana belum tentu berarti mudah.
Bahasa pemrograman yang sudah Anda kenal mungkin lebih mudah digunakan daripada XOScript.
Di sini, kesederhanaan memiliki arti lain:
kemampuan untuk membentuk model mental yang lengkap tentang bahasa ini dan perilakunya.

XOScript dirancang agar muat di dalam kepala Anda.
Tata bahasa dan jumlah konsepnya sengaja dibuat sedikit.
Tidak ada kelas; objek dapat diperluas secara langsung.
Objek diteruskan melalui referensi, penyalinan dilakukan secara eksplisit,
dan fungsi memiliki satu titik keluar.

Beberapa pilihan ini sangat berbeda dari bahasa-bahasa arus utama.
XOScript, misalnya, tidak memiliki sistem tipe dan menggunakan cakupan dinamis.
Pesan yang tidak dapat ditangani akan diabaikan alih-alih menghasilkan eksepsi.
Pilihan-pilihan ini memiliki konsekuensi dan tidak dimaksudkan untuk menghilangkan galat.
Tujuannya adalah menjaga model dasar bahasa ini tetap kecil dan konsisten.

XOScript juga dapat dilokalkan, sehingga aturan bisnis dapat diungkapkan
dalam bahasa alami dan mungkin dibagikan kepada pemangku kepentingan non-teknis.

Kemampuan diaudit berarti menerapkan filosofi yang sama pada implementasinya.
Runtime ditulis dalam C, dengan lexer, parser, dan tree walker kecil yang ditulis tangan.
Pustaka standar dan runtime sebagian besar mencerminkan struktur bahasa itu sendiri,
sehingga hubungan antara kode XOScript dan implementasinya relatif langsung.

Pengujian juga sangat terkait dengan dokumentasi.
Setiap metode sebaiknya memiliki pengujian terkait yang dapat dimasukkan ke dalam manual,
sehingga dokumentasi tetap selaras dengan implementasinya.

XOScript tidak dimaksudkan untuk bersaing dengan bahasa-bahasa arus utama dalam hal
fitur atau keakraban. XOScript menjelajahi tujuan yang berbeda:
lingkungan pemrograman yang dapat dipahami seorang pengembang secara utuh.

Harapannya, bahasa yang kecil dan implementasi yang
kecil membuat perangkat lunak dapat dipahami secara praktis
dari bita hingga objek, dari sintaksis hingga runtime, dan memungkinkan Anda menulis kode dengan
percaya diri karena Anda memahami apa yang terjadi di dalam
skrip maupun apa yang terjadi di balik layar.

Arsitektur sebuah penyiapan server xoscript
sederhana, namun fleksibel.

{{architecture.png}}

Untuk menggunakan xoscript sebagai bahasa server, Anda perlu memasang
plugin server di folder bernama /mods/server. 

Alasannya, kami ingin
memisahkan inti bahasa dari fungsionalitas khusus server,
tidak seperti misalnya PHP atau Python. Jika tidak, kami harus mengirimkan
segala macam hal yang tidak berguna kepada semua orang, dan itu konyol.
Anda juga dapat memasang modul lain jika mau. Sistem ini sangat
fleksibel.

Selain itu, beberapa fungsi lebih baik diimplementasikan dalam bahasa skrip
itu sendiri, seperti templat dan penanganan sesi, sehingga kami juga
menyertakan pustaka template.xo dan webtools.xo untuk kemudahan Anda.
Alasan semua ini adalah kami tidak tahu bagaimana Anda ingin
menggunakan xoscript. Anda dapat menggunakannya sebagai bahasa skrip sisi server,
tetapi juga untuk GUI, perangkat tertanam, atau sekadar pemrosesan batch.
Bahkan jika Anda menggunakannya sebagai bahasa skrip sisi server (yang
saat ini merupakan salah satu kegunaan utamanya), Anda mungkin tetap ingin
menggunakan mesin templat atau penangan sesi yang berbeda.
Siapa kami untuk memutuskan bahwa Anda harus menggunakan milik kami?

Namun, salah satu keuntungan menggunakan mesin templat kami sendiri adalah
Anda tidak perlu mempelajari sintaksis tambahan untuk membuat templat.
Mesin templat bawaan yang disertakan dengan xoscript menerapkan pemisahan 100%
antara presentasi dan logika. Alih-alih sintaksis templat khusus,
mesin ini cukup menggunakan sistem penanda slot yang sangat fleksibel.
Untuk informasi lebih lanjut, lihat bab Server.

Perhatikan bahwa jika Anda tidak ingin menggunakan mesin templat bawaan atau
webtools bawaan, tentu saja Anda harus menyediakan
sendiri penggantinya.

Jika Anda menjalankan server web di dalam chroot, jail, atau jenis sandbox lainnya,
Anda juga perlu memasang dependensi xo di lingkungan tersebut. Anda dapat
melihat pustaka mana yang diperlukan dengan menggunakan ldd (lihat manpage Linux atau BSD).
Jika Anda ingin menggunakan perintah shell dalam skrip xo Anda, salin juga sebuah shell
(seperti bash atau ksh) ke lingkungan ini.

Kami juga ingin menekankan bahwa kami sangat serius soal kompatibilitas mundur.
Bahkan tersedia fitur kompatibilitas mundur khusus yang disebut
'version'. Secara umum, kami bertujuan agar kode Anda dapat berjalan selamanya. Jadi, Anda
tidak akan pernah perlu memperbarui kode agar tetap kompatibel dengan versi
xoscript yang lebih baru. Tujuan kami: tulis sekali, jalankan selamanya.

Bagian selanjutnya dari manual ini didedikasikan untuk menjelaskan bahasa
pemrograman xoscript secara rinci. Skrip server dibahas dalam bab
yang berjudul Server. Jika Anda pengembang perangkat lunak berpengalaman, Anda mungkin ingin
melewati beberapa bab karena sebagian terlalu rinci atau
sangat mirip dengan praktik pemrograman umum. Jadi, bagi Anda
yang sudah berpengalaman dengan beberapa bahasa pemrograman lain,
sebaiknya perlakukan manual ini sebagai panduan referensi.

## Penyiapan di Linux

Unduh apache2 dan mariadb:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Unduh xoscript.
Ganti X dengan nomor versi yang benar!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Salin berkas-berkas ke webroot dan /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Sunting konfigurasi apache2 Anda:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Ganti Virtualhost dengan:

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

Buat halaman uji:

```
sudo nano /var/www/html/test.xo
```

dan tulis program uji kecil:

```
#!/bin/xo
Server inisialisasi.
Program gunakan: ['webtools.xo'].
>> web := Dokumen-Web baru.
web keluarkan: ['Hello World'].
```

Izinkan apache2 menjalankan program Anda melalui CGI:

```
sudo chmod uog+x /var/www/html/test.xo
```

Mulai ulang apache2:

```
sudo systemctl restart apache2
```

Buka halaman uji Anda di peramban:

```
http://localhost/test.xo
```

Anda seharusnya melihat:

```
Hello World
```


## Penyiapan di OpenBSD

Sunting /etc/httpd.conf, tambahkan:


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

Jika Anda ingin menggunakan SSL:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Untuk melindungi pertukaran kunci dari serangan kuantum,
pilih cipher mlkem:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Tambahkan biner xo dan mods, serta semua dependensinya ke dalam
chroot (cari tahu dengan ldd).

## Menjalankan contoh


Untuk menjalankan salah satu program contoh dalam paket:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Misalnya, untuk menjalankan contoh FizzBuzz di Linux:

```
./example.sh fizzbuzz Linux
```

Untuk menjalankan contoh yang sama di OpenBSD:

```
./example.sh fizzbuzz OBSD
```

Untuk menjalankan contoh dengan build bersih:

```
./example.sh fizzbuzz OBSD clean
```

## Pengujian unit

Untuk menjalankan pengujian unit:

```
./runtests.sh
```

Untuk menjalankan pengujian unit tanpa melakukan build (hanya menguji):

```
./runtests.sh nobuild
```

## Build

Untuk melakukan build dari kode sumber di Linux:

```
make clean
ISO="en" make
```

Di OpenBSD:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

Untuk melakukan build plugin server di Linux:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

Untuk melakukan build plugin server di OpenBSD:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Halo dunia

Setelah berkas ditransfer ke komputer Anda, Anda dapat mengekstraknya
dan memulai xo dengan perintah berikut:

```
xo
```

Untuk menjalankan sebuah XOScript, simpan program sebagai berkas dengan menambahkan
akhiran -xo (opsional). Selain itu, sisipkan nama berkas program Anda
setelah perintah XOScript:

```
xo myprogram.xo
```

Saat Anda menjalankan perintah XOScript dengan berkas program Anda sebagai
parameter, xo akan membaca dan menjalankan berkas program tersebut.

{{note}}
Anda juga dapat memulai program dengan menyeretnya ke ikon xo.
{{/note}}

{{warning}}
Pada beberapa sistem, Anda perlu memberi xo izin untuk memuat pustaka
dinamis terlebih dahulu.
{{/warning}}

Menurut tradisi, program pertama dalam setiap bahasa pemrograman
baru haruslah semacam salam kepada dunia. Dalam XOScript, program
**Halo dunia** seperti itu terlihat seperti ini:

@test598

Jika teks ini disimpan ke sebuah berkas, misalnya hello.xo, teks tersebut dapat dijalankan
sebagai berikut: .

xo hello.xo

Hello world


Anda dapat melihat keluaran program di jendela hitam yang ditampilkan di atas.
Di sepanjang manual ini, visualisasi yang sama akan digunakan untuk menampilkan
keluaran.

{{note}}
Keluaran ditulis dengan huruf K besar.
Secara umum, objek diawali dengan huruf besar
kecuali jika objek itu berperan sebagai instans (tidak memiliki metode
sendiri, hanya data). Hal ini mencerminkan konvensi kelas dan instans
dalam bahasa pemrograman lain.
{{/note}}


## Sintaksis 

XOScript adalah bahasa pemrograman *berorientasi objek* *murni*. Artinya,
xoscript memandang segala sesuatu sebagai objek, sehingga tidak ada
*tipe data* lain. Pada dasarnya ada tiga tindakan rutin dasar
dalam program yang ditulis dalam XOScript: *menetapkan*, *mengirim pesan*,
dan *menanggapi*. Pertukaran pesan antarobjek adalah bagian kunci dari
program XOScript. Ketiga tindakan rutin tersebut diilustrasikan
di bawah ini:


Tindakan        | Contoh
--------------- | --------
penetapan       |  \>\> x := 1. 
pesan unary     | x genap?.
pesan binary    | 1 + 2.
pesan kata kunci | x dari: 0 panjang: 10.
jawaban         | <- answer.  


Bab ini akan memberi Anda gambaran umum tentang bahasa XOScript
dan menjelaskan prinsip-prinsip dasarnya. XOScript adalah bahasa kecil yang
didasarkan pada tiga tindakan (lihat ilustrasi) yang diterjemahkan menjadi
sekitar enam aturan tata bahasa. Hanya itu yang diperlukan untuk menguasai
bahasa ini.

Jangan khawatir jika semuanya tidak langsung jelas bagi Anda: semua
komponen dasar akan dibahas di bab berikutnya (3) dan aturan-aturan dasarnya akan
diulang. Namun, bab ini terutama berfungsi sebagai pengantar umum
untuk bahasa ini. Prinsip-prinsip dasarnya akan dijelaskan secara singkat
dan diilustrasikan dengan beberapa contoh yang relevan. Rincian yang belum
dibahas akan diuraikan di kemudian hari.

Komentar dalam XOScript diawali dengan simbol \#. Jadi, baris berikut
akan diabaikan:

```
# this is just a comment
```

## Variabel

Untuk menetapkan
variabel, Anda menggunakan simbol deklarasi variabel: >>. Nama
variabel boleh berisi semua tanda kecuali: <-, :=, spasi,
titik, koma, titik dua, tanda kutip [' '], dan tanda kurung ().
Selain itu, variabel tidak boleh terdiri dari beberapa baris. Harap diperhatikan
bahwa variabel tidak boleh diawali dengan angka atau tanda minus.

Berikut contoh variabel yang valid:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['dollar'].
>> +plus := Benar.
>> user-password := ['Pssst!'].
```

Contoh variabel yang tidak valid:


```
>> -123 := ['negative number'].
>> password of user := ['Classified'].
>> password.of:user := ['Classified'].
>> ,x := 10.
```

{{note}}
Anda tidak perlu meng-escape karakter apa pun
(termasuk tanda kutip, tanda kutip ganda, batas
teks) di dalam
literal teks selama hal itu tidak
menimbulkan ambiguitas bagi lexer.
{{/note}}

Setelah variabel dideklarasikan, variabel tersebut dapat digunakan dengan bebas. Artinya,
simbol deklarasi hanya perlu digunakan pertama kali
Anda menggunakan variabel tersebut (deklarasi).

Lebih tepatnya, Anda tidak dapat begitu saja menetapkan nilai ke
variabel Anda *(x := 2)*, karena Anda harus mendeklarasikan variabel terlebih dahulu *(\>\>
x := 2)*. Namun, setelah dideklarasikan, Anda boleh mengubah nilainya
tanpa menggunakan simbol deklarasi *(\>\> x := 2. x := 3.)*.

Perhatikan bahwa nilai wajib diberikan kepada variabel pada saat
deklarasi. Berbeda dengan bahasa pemrograman lain, Anda tidak diizinkan
mendeklarasikan variabel tanpa nilai. Setiap variabel harus secara eksplisit
dikaitkan dengan nilai awal. Meskipun demikian, Anda bebas menginisialisasi
variabel dengan objek **Kosong**. Dalam hal ini, variabel tersebut dapat
dianggap kosong *(\>\> x := Kosong.)*. Singkatnya, mendeklarasikan
variabel tanpa nilai awal tidak diizinkan. Jadi,

```
>> x.
```

tidak valid dan akan menghasilkan pesan galat.

{{note}}
xoscript menggunakan cakupan variabel dinamis. Untuk
rinciannya, lihat bab Fungsi.
{{/note}}


## Literal

XOScript memandang segala sesuatu sebagai objek, yaitu semua angka, teks,
dan fragmen kode. Angka seperti 1, 2, 100, -999, dan 1,234 adalah
objek Angka. Semua teks di antara tanda kutip tunggal adalah objek
Teks. Semua fragmen kode yang dikelompokkan di antara kurung kurawal {...} adalah
objek Fungsi.

Literal         | Objek akar   | Contoh
--------------- | ------------ | ----------
angka           | Angka        | 1,2,3... 
teks            | Teks         | \['hello'\]
fungsi          | Fungsi       | { 1 + 2. }.
                
     
Objek seperti angka dan teks selalu berasal dari sebuah objek
akar. Misalnya, semua angka diturunkan dari objek **Angka**. Semua
teks diturunkan dari **Teks** dan semua fragmen kode dari **Fungsi**. Pada
gilirannya, semua objek ini berasal dari **Objek**, yang sebenarnya merupakan
objek akar dari semua objek.


## Pesan

Pemrograman dalam XOScript pada dasarnya berarti
mengirim pesan ke objek. Notasi umum untuk mengirim pesan ke
sebuah objek adalah sebagai berikut:

```
<object> <message>
```

Untuk mengetahui apakah angka **2**, misalnya, adalah bilangan genap,
pesan **genap?** dikirim ke objek **2**:

```
2 genap?
```

Jawabannya adalah **Benar** (sekali lagi, sebuah objek). Pesan yang tidak dikenal
biasanya diabaikan oleh objek, sehingga tidak terjadi galat. Beberapa objek (misalnya,
angka atau teks) menanggapi pesan yang tidak dikenal dengan cara yang sudah ditentukan
(lebih lanjut tentang hal ini nanti).

Sebuah objek dapat menerima tiga jenis pesan. 

Jenis           | Jumlah argumen
--------------- | -------------------
Unary           | 0      
Binary          | 1     
Kata kunci      | 1+    


Pertama, ada **pesan
unary**, lihat contoh di atas, yang tidak memiliki argumen. Kedua,
ada **pesan kata kunci**, yang memiliki satu atau beberapa argumen,
misalnya:

```
>> x := Angka antara: 1 dan: 10.
```

Dalam hal ini, pesan **antara:dan:** dikirim ke **Angka**, yang
merupakan objek akar dari semua angka. Hasilnya adalah angka acak
antara 1 dan 10. Terakhir, ada **pesan binary**, yang hanya terdiri
dari satu karakter dan memiliki satu argumen:

```
2 + 3
```

Ini terlihat seperti penjumlahan matematika, tetapi sebenarnya hanyalah pesan biasa.
Pesan **+** dikirim ke **2**, dengan argumen **3**, yang akan mengembalikan
jawaban **5**. Pesan binary boleh ditulis tanpa titik dua.

Pesan binary dapat dirangkai:

```
>> x := 3 + 2 - 1.
```

Dalam fragmen ini, **+ 2** pertama-tama dikirim ke objek **Angka** **3**, yang
menghasilkan objek Angka **5**, setelah itu **-1** dikirim ke angka
ini. Pembaca yang jeli benar jika memperhatikan perbedaan yang
ditunjukkan protokol ini terhadap urutan operator matematika
konvensional. XOScript mengabaikan urutan matematika demi
konsistensi sistem pesannya. Akibatnya, penjumlahan:

```
2 + 3 * 5 = 25
```

bukan 17.

Hal ini memang disengaja. Tanda kurung dapat digunakan untuk mengubah urutannya:

```
2 + (3 * 5) = 17
```

Sebagian besar objek mengembalikan dirinya sendiri sebagai hasil tanggapan terhadap suatu
pesan. Hal ini berguna karena mendorong dialog lebih lanjut dengan objek
tersebut dengan mengirim pesan lanjutan:

```
Keluaran tulis:
[' hello '] pangkas huruf-besar.
```

```
HELLO
```

Di sini, dua pesan dikirim ke objek **Teks**: **pangkas**, diikuti
oleh **huruf-besar**.

Dalam fragmen berikut, penggunaan koma diperlukan untuk menunjukkan
bahwa ada pesan baru yang masuk. Jika tidak, XOScript akan bingung.

```
Keluaran tulis: ['Hello!'], baris-baru.
```

Pertama, pesan **tulis:** dikirim ke simbol pensil, diikuti oleh
**baris-baru**. Tanpa koma, XOScript akan mengira bahwa Anda ingin mengirim
**baris-baru** ke **teks** **Hello!**, suatu tindakan yang sia-sia.

Urutan pemrosesan pesan adalah sebagai berikut: dari kiri ke kanan;
mulai dengan pesan di dalam tanda kurung, diikuti oleh pesan unary. Selanjutnya,
pesan binary, lalu diakhiri dengan pesan kata kunci. Lihat contoh
di bawah ini:

```
Keluaran tulis: 0.5 bulatkan + (2 - 1), baris-baru.
```

XOScript selalu membaca dari kiri ke kanan: pertama, pesan **tulis:**
dikirim ke Keluaran dan diikuti oleh pesan **baris-baru**. Di dalam
argumen itu sendiri, XOScript membaca dari kiri ke kanan, jadi **0.5 bulatkan**
lalu **+**.

{{note}}
Pesan baris-baru menambahkan karakter baris baru ke teks.
Nama asli pesan ini (stop) terinspirasi oleh sistem telegraf.
Pesan dalam sistem telegraf 
sering menggunakan kata STOP untuk menandai akhir kalimat
(karena tanda baca tidak andal atau mahal).
{{/note}}

Selain itu, **bulatkan** didahulukan daripada **+**, karena merupakan
**pesan unary**. Karena ada tanda kurung, **2 - 1** dihitung
terlebih dahulu, setelah itu **1** ditambahkan ke hasil **0.5 bulatkan** (1).

Seluruh proses akan memberikan hasil **2**, yang juga merupakan jawaban
yang ditulis. Setelah koma, menyusul pesan baris-baru, yang memindahkan kursor
ke baris baru. Tentu saja, cara terbaik untuk memahami sepenuhnya urutan
program XOScript adalah dengan berlatih.

Perlu dicatat bahwa dalam XOScript, berbeda dengan banyak bahasa pemrograman
lain, spasi merupakan bagian mendasar dari sintaksisnya. Khususnya
dalam hal pesan binary, spasi dapat menimbulkan sedikit
kebingungan. Selalu gunakan spasi setelah pesan binary. Anda tidak dapat
langsung menempelkan angka ke pesan, misalnya: 

```
3 + 2
```

berbeda dengan 

```
3 +2
```

Contoh pertama (**3 + 2**) mengirim
pesan **+** ke angka **3**, dengan argumen angka **2**.
Hasilnya, dalam hal ini, adalah **5**. Pada contoh kedua (**3 +2**),
pesan unary **+2** dikirim ke angka **3**. Bergantung pada
konteksnya, hasilnya bisa sangat berbeda.

## Metode yang tidak ada

Mengirim pesan ke sebuah objek akan memanggil fungsi yang telah
dilampirkan ke objek tersebut dengan nama pesan itu. Jika Anda mengirim pesan
yang tidak dipahami, objek penerima akan mengabaikan pesan Anda
dan sebagai gantinya mengembalikan referensi ke dirinya sendiri untuk komunikasi lebih lanjut.
Hal ini disebut pengiriman pesan toleran.

Contoh:

```
Keluaran tulis: Objek blah, baris-baru.
```

Ini tidak akan menghasilkan galat. Ini hanya akan mencetak teks **Objek**.


## Alur kendali

Dalam XOScript tidak diperlukan aturan tata bahasa terpisah untuk *perulangan* dan
*percabangan if*. Pernyataan if hanyalah pesan **benar:** atau **salah:**
sederhana ke objek **Benar** atau objek **Salah**:

```
2 genap? benar: {
	Keluaran tulis: ['Two is an even number'], baris-baru.
}.
```
Pada contoh sebelumnya, pesan **benar:** dikirim ke **Benar** (jawaban
atas pertanyaan: apakah 2 bilangan genap?). Sebagai argumen, sebuah
fragmen kode tambahan ikut dikirim: sebuah objek **Fungsi**. Fungsi ini menulis
di layar bahwa 2 memang bilangan genap.

Tidak diperlukan pula aturan penulisan terpisah untuk *perulangan*. Untuk
menjalankan sebuah fragmen kode tiga kali, cukup kirim **\*** dengan argumen
**3** ke **Fungsi** tersebut:

@test5

Dalam fragmen kode ini, **i** adalah indeksnya. Jadi, pertama kali Fungsi
dijalankan, **i** bernilai 0, kali berikutnya dijalankan, **i** = 1, dan
seterusnya.

Mari kita lihat contoh lain. Jika tabel konversi perlu
dicetak dari *kJ* (kilojoule) ke *kkal* (kilokalori) dengan langkah 100,
lihat notasi yang benar di bawah ini:

@test599

Di sini, nomor baris saat ini diteruskan ke parameter
**:line**. Di awal sebuah fungsi, parameter fungsi
didefinisikan. Parameter yang tidak digunakan tetap kosong (**Kosong**). Parameter
selalu ditempatkan di awal fungsi, tepat setelah kurung kurawal
pembuka, dan diawali dengan titik dua.

Pesan **selama:** merupakan gabungan dari *perulangan* dan *kondisi*.
Dua fungsi dapat dihubungkan menggunakan pesan **selama:**. Fungsi penerima
akan terus berjalan sampai fungsi setelah titik dua memberikan hasil
negatif. Contoh:

@test600

Dalam fragmen kode yang diilustrasikan di atas, **1** ditambahkan ke **x** selama
**x** kurang dari **5**. Jika hal ini tidak lagi berlaku, fungsi kedua
akan menjawab dengan **Salah**, sehingga eksekusi
fungsi pertama akan berakhir. Perhatikan bahwa **x** didefinisikan di luar
fungsi dan merupakan variabel global. Untuk mempelajari lebih lanjut tentang aturan cakupan,
lihat bab tentang Fungsi.

## Interpolasi teks

Daftar *kJ/kkal* dapat dibuat lebih
rapi. Sebaiknya daftar tersebut terlihat sebagai berikut:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Jika Anda mengubah keluaran yang diinginkan menjadi templat, notasinya
dapat berupa:

```
number1 kJ ➞ number2 kcal
```

Artinya, **number1** mewakili nilai kJ dan **number2** mewakili
nilai kkal. Beginilah cara kerja interpolasi teks dalam XOScript. Tidak
diperlukan aturan tata bahasa terpisah untuk hal ini dalam XOScript. Cukup kirim
kata yang perlu diganti ke teks tersebut dengan teks pengganti
sebagai argumen:

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

Aturan substitusi ini berlaku untuk setiap pesan tak terdefinisi yang diterima
oleh objek **teks**. Setiap pesan yang tidak dikenali oleh objek
**teks** akan ditafsirkan sebagai berikut: *ganti teks pesan
dengan teks di dalam argumen pesan.* Anda dapat menyesuaikan
program sebagai berikut:


@test601


Untuk menghindari kebingungan tentang pesan mana yang dapat atau tidak dapat digunakan sebagai
pengganti, sebaiknya gunakan penanda templat seperti &lt; &gt;
untuk segmen teks dalam templat yang
perlu diganti.

## Nilai kembalian

Untuk menjawab sebuah pesan, digunakan panah kembali
(*<-*). Contoh berikut menggambarkan cara membuat tugas
untuk menghitung persentase:

@test602

Setelah tugas didefinisikan dan ditetapkan ke variabel **percentage**,
pesan **terapkan:dan:** dikirim dengan argumen **100** dan **7**.

Ini akan menjalankan tugas yang diterapkan pada **100** dan **7**, yaitu 7% dari 100.
Dengan panah kembali, jawabannya dikembalikan dari tugas ke
program utama.

## Memperluas

Meskipun kode ini valid, kode ini memiliki kelemahan
karena urutan argumennya harus diingat. Jadi, mengapa tidak
menulisnya seperti ini: *7 percent of: 100 *? Itu akan terlihat jauh lebih
*alami*. Untuk memungkinkan hal ini, kita harus menyesuaikan objek induk dari
**7**, yaitu objek **Angka**, agar memahami
pesan **percent of:**. Hal ini dapat dicapai dengan mengirim **saat:lakukan:** ke
objek Angka, seperti ini:

@test603

Karena persentasenya, dalam hal ini, adalah angka itu sendiri, kita merujuk ke diri,
kata kunci *diri*. Singkatnya, simbol diri berarti: *kirim pesan
ini ke diri-sendiri*.

# Objek

{{messages}}

Selain menyesuaikan dan memperluas objek yang sudah ada, Anda juga dapat membuat
objek baru sendiri cukup dengan mengirim pesan **baru**. Misalkan Anda
ingin membuat objek faktur yang memberlakukan urutan
penomoran; dalam hal ini, Anda terlebih dahulu memerlukan sebuah objek faktur.

Mengingat bahwa setiap objek diturunkan dari objek lain, yang pada gilirannya
akhirnya berasal dari objek akar dari semua objek yang disebut Objek,
Anda perlu memilih objek lain mana yang akan menjadi dasar
objek baru Anda. Objek baru Anda mewarisi semua sifat dari
objek yang menjadi dasarnya, yaitu objek yang semula menerima pesan
**baru**.

Dalam contoh ini, lebih disukai objek yang agak netral, yang tidak memiliki terlalu
banyak sifat warisan. Pilihannya mudah, karena dalam hal
ini objek baru dapat didasarkan pada objek akar itu sendiri, yaitu
**Objek**. Notasi sistem faktur yang dimaksud kemudian adalah
sebagai berikut:

@test604

Nomor faktur saat ini disimpan di dalam objek, itulah sebabnya ada
kata kunci **milik** yang ditempatkan di depannya. Ini disebut *properti*;
rincian lebih lanjut akan menyusul.

Beberapa perusahaan lebih suka memasukkan tahun ke dalam nomor
faktur. Dalam hal ini, Anda dapat membuat objek faktur baru yang didasarkan pada
objek faktur sebelumnya, tetapi yang memberi penggunanya kemungkinan untuk
memasukkan tahun tertentu:

@test605

Implementasi untuk pesan **angka** tidak perlu ditulis
lagi, karena diwarisi dari **objek
faktur** yang ditulis sebelumnya; dengan demikian, kode lama dapat digunakan kembali. XOScript tidak memiliki konsep
seperti kelas dan konsep-konsep terkait lainnya. Artinya, objek hanya
dapat mewarisi dari objek lain, yang juga dikenal sebagai *pewarisan
prototipe*.

Sekarang, kembali ke properti. Properti objek hanya dapat diakses
dari *dalam hierarki objek*, sehingga properti ini
tidak dapat dilihat oleh objek lain.

Berbeda dengan bahasa pemrograman lain, semua properti objek
hanya terlihat oleh objek yang membuat properti tersebut dan oleh
objek turunannya. 

Teknik yang umum digunakan adalah memakai sebuah objek sebagai semacam *cetak biru*,
seperti misalnya pada faktur yang dibahas sebelumnya.
Contoh bagus lainnya adalah **Point**. Katakanlah Anda membuat
program komputer yang melakukan perhitungan dengan menggunakan titik-titik pada peta. Anda
dapat mengembangkan objek **Point** yang berisi properti
koordinat x dan koordinat y, yang akan disediakan bagi
dunia luar melalui pesan:

@test606

Pesan **=** membandingkan kedua titik menggunakan pesan **dan:**.
Perbandingan pertama menghasilkan **Benar** atau **Salah**. Keduanya adalah objek
boolean. Jika Anda mengirim pesan **dan:** ke objek Benar, dan
objek argumen setelah titik dua juga **Benar**, maka Anda akan
kembali menerima jawaban **Benar**. Jika salah satunya **Salah**, Anda akan
menerima jawaban **Salah**. Perhatikan bahwa satu titik tidak dapat membaca koordinat
titik yang lain. Anda perlu mengirim pesan ke titik yang lain untuk meminta
data ini: **x-coordinate** dan **y-coordinate**. Bagaimanapun, seperti yang
sudah dijelaskan, properti hanya dapat diambil dari dalam
keluarga objek itu sendiri. 

Perhatikan bahwa pesan **=** digunakan di sini untuk melakukan perbandingan
titik. Pesan lain juga bisa digunakan, misalnya:
**is:** atau **equal:**, tetapi menggunakan kembali karakter **=** tampaknya
tepat dalam kasus ini.

## Pewarisan

Anda dapat menggunakan kembali kode yang ditulis sebelumnya untuk membuat hierarki
objek. Misalnya:

```
>> Animal := Objek baru.
>> Dog := Animal baru.
>> Poodle := Dog baru.
```

Dalam hal ini, **Dog** mewarisi semua perilaku dan properti
**Animal**, dan pada gilirannya objek **Animal** mewarisi semua perilaku
**Objek**, objek akar dari semua objek.


## Penimpaan


Dalam contoh berikut, dibuat jenis daftar baru:
**Combination**, yang menjamin setiap elemennya unik.
Fungsi-fungsi daftar digunakan kembali melalui pewarisan:

@test607

Perhatikan bagaimana **red** yang kedua tidak dimasukkan ke dalam daftar.

Terkadang, perilaku sebuah objek mungkin perlu ditimpa.
Misalnya, saat menjumlahkan angka dan satuan ukuran harus
diperhitungkan. Dalam contoh berikut, dibuat objek **Size**.
Objek ini mengembalikan angka yang, selama penjumlahan, memperhitungkan
satuan angka yang akan ditambahkan. Objek **Angka**
memeriksa apakah satuannya *inci* atau *kaki*. Kode programnya
dapat menyerupai berikut ini:

@test608

## Rekursi

Pada contoh sebelumnya, **tanda** plus ditimpa. Perhatikan
bahwa pada akhirnya penjumlahan terakhir tetap harus dilakukan, yang sebenarnya
terjadi pada baris berikut:

```
>> answer := diri + (angka x factor).
```

Nah, bagaimana XOScript memahami bahwa **tanda** plus ini merujuk ke
logika penjumlahan yang asli?** Misalnya, tafsiran lain
bisa jadi XOScript akan berulang kali mengirim pesan yang sama ke objek
yang sama, yang pada gilirannya akan menghasilkan **perulangan tanpa akhir**. Jelas,
bukan itu maksudnya. Begitu Anda mengirim pesan ke sebuah objek
yang akan menjalankan kode yang persis sama, XOScript akan menyadari
bahwa dalam hal ini yang dimaksud adalah pesan dasar yang ditimpa. Jadi,
program Anda akan otomatis terlindungi dari bentuk perulangan tanpa akhir
semacam ini. Namun, jika Anda memang bermaksud menjalankan fungsi yang sama dari
fungsi saat ini, Anda harus terlebih dahulu mengirim pesan
**rekursif**. Dalam hal ini, hasilnya akan berupa perulangan
tak terbatas. Namun, ada penerapan yang berguna untuk tugas rekursif,
misalnya jika Anda ingin menghitung faktorial dari suatu
angka. Dalam hal ini, cukup tambahkan pesan **factorial** ke
Angka:

@test609

Ini memerlukan rekursi. Sebenarnya, tugas yang terhubung dengan
pesan **factorial** perlu dijalankan lagi di dalam fungsi tersebut.
Jadi, fungsi faktorial perlu dipanggil dari dalam
fungsi faktorial itu sendiri. Sebagai aturan, XOScript akan mencegah rutinitas ini
karena risiko berakhir dalam perulangan tak terbatas. Karena alasan ini,
sangat penting untuk mendahului pesan dengan kata **rekursif**. Hal ini
dilakukan agar XOScript mengetahui bahwa Anda memang
bermaksud menjalankan tugas yang sama, dan bahwa Anda tidak membuat kesalahan.

## Objek mirip kelas

Meskipun xoscript tidak menyediakan kelas, meniru perilaku
mirip kelas sangat mudah. Cukup timpa pesan baru.

```
>> Animal := Objek baru.
Animal saat: ['baru'] lakukan: {
	<- diri baru inisialisasi.
}.

Animal saat: ['inisialisasi'] lakukan: {
	milik sound := ['?'].
	milik legs  := 4.
}.
```

Pada fragmen kode di atas, kita membuat objek bernama Animal.
Objek ini berfungsi sebagai *cetak biru* untuk segala jenis hewan
seperti anjing dan kucing. Objek induk Animal ditulis
dengan huruf A besar untuk menandakan bahwa ini adalah objek mirip kelas.
Selanjutnya, kita menimpa pesan baru dengan menulis metode baru kita sendiri.
Dalam hal ini, metode tersebut mengirim pesan baru ke diri, diikuti oleh pesan
inisialisasi. Karena xoscript secara bawaan memblokir rekursi, hal ini tidak akan menyebabkan
perulangan tak terbatas. Sebaliknya, pesan baru akan dikirim ke objek
induk (Objek), sehingga menghasilkan instans baru dari Animal. Jadi, kita membuat
objek baru berdasarkan objek yang sama dengan objek tempat kita membuat metode baru tadi.
Hal ini sepenuhnya valid. Sekarang kita juga mengirim pesan inisialisasi, yang memastikan
bahwa objek Animal memiliki nilai bawaan untuk propertinya. Secara bawaan,
seekor hewan memiliki 4 kaki dan suaranya tidak diketahui (karena itu ada tanda tanya).
Untuk membuat instans baru dari Animal, kita cukup menulis:

```
>> a := Animal baru.
```

Sekarang kita mendapatkan instans baru dari Animal dengan 4 kaki, suara yang tidak diketahui, dan
metode inisialisasi. Sama seperti dalam bahasa OOP lainnya, kita juga dapat
memperluas Animal:

```
>> Dog := Animal baru.
Dog saat: ['inisialisasi'] lakukan: {
	diri inisialisasi.
	milik sound := ['barks'].
}.
```

Kita dapat mengujinya dengan mudah dengan menambahkan metode teks:

```
Animal saat: ['teks'] lakukan: {
	<- milik legs teks + milik sound.
}.
```

Mari kita gabungkan semuanya:

@test13


Membuat objek yang berada dalam keadaan awal tertentu merupakan
masalah yang sering muncul. Misalkan objek **Rectangle** harus dibuat
untuk menghitung keliling dan luas. Notasi yang mungkin adalah:


```
>> Rectangle := Objek baru.

Rectangle saat: ['area'] lakukan: {
	<- milik panjang * milik width.
}.
```

Tentu saja, menetapkan panjang dan lebar merupakan prasyarat. Untuk
itu, pesan **panjang:** dan **width:** dapat ditambahkan:


```
Rectangle saat: ['length:'] lakukan: { :panjang
	milik panjang := panjang.
}.

Rectangle saat: ['width:'] lakukan: { :width
	milik width := width.
}.

```

Persegi panjang ini kemudian dapat digunakan sebagai berikut:


```
>> rectangle := Rectangle baru length: 2, width: 3.
Keluaran tulis: rectangle area.
```

Namun, jika pengaturan awal panjang dan lebar terlewatkan,
akan muncul pesan galat:

```
>> rectangle := Rectangle baru.
Keluaran tulis: rectangle area.
```

akan menghasilkan galat berikut:

```
Kunci tidak ditemukan:panjang
```

Untuk mencegah hal ini, sebaiknya sebuah persegi panjang
selalu memiliki panjang dan lebar awal, misalnya 0. Jadi, dalam
hal ini, pesan **baru** perlu **ditimpa**.

@test610

Jika kita menimpa pesan baru, pada dasarnya kita sedang meniru sebuah **kelas**.

Dunia XOScript dipenuhi dengan beragam objek yang
tersedia bagi program Anda sejak awal. Pada bab-bab berikutnya,
semua objek inti ini akan dibahas.

## Snapshot

Anda dapat menyimpan sebuah objek (beserta keadaannya saat ini) ke disk dengan:

```
myobject save-as: ['saved.bin'].
```

Untuk memuat ulang objek dari disk:

```
>> myobject := Objek load-from: ['saved.bin'].
```

Snapshot dapat digunakan untuk menyimpan keadaan tertentu atau untuk meningkatkan kinerja.
Memuat snapshot menghindari lexing, parsing, dan penyiapan aplikasi.
Selain itu, di masa mendatang, manfaat kinerja tambahan mungkin diperkenalkan
melalui snapshot, seperti optimasi pola tertentu atau deteksi dan
optimasi jalur panas (hot path).

{{warning}}
Snapshot adalah fitur eksperimental, jangan gunakan dalam lingkungan produksi.
Untuk mengaktifkan fitur eksperimental, lakukan kompilasi dengan -D EXPERIMENTS.
{{/warning}}


@test712

# Objek Kosong

{{messages}}

Objek Kosong
melambangkan kekosongan, atau lebih tepatnya, ketiadaan informasi.
Sesekali Anda akan menerima objek ini sebagai jawaban atas sebuah pesan,
jika hasilnya adalah **tidak ada apa-apa**. Pertanyaan paling mendasar
yang dapat Anda ajukan kepada objek **Kosong** adalah: **Kosong?**.
Jawabannya selalu **Benar**.

```
Keluaran tulis: Kosong Kosong?.
```

hasil:

```
Benar
```

Objek apa pun selain **Kosong** akan menjawab dengan **Salah**.
Fragmen kode di atas mungkin tampak agak filosofis, tetapi objek **Kosong**
jelas memiliki penerapan yang sangat praktis. Misalnya, Anda
akan menerima objek Kosong sebagai jawaban jika Anda meminta
elemen daftar yang tidak ada. Anda juga dapat menggunakan objek Kosong
jika ingin mendeklarasikan variabel tetapi belum ingin menentukan
nilainya. Sebagai gantinya, Anda cukup **menetapkan** nilai khusus **Kosong**. Dalam
XOScript tidak diizinkan mendeklarasikan variabel tanpa nilai, seperti:


```
>> nilai.
```

Sebagai gantinya, Anda harus menulis seperti berikut:

```
>> nilai := Kosong.
```

@api_None_base

# Boolean

{{messages}}

Berbeda dengan sebagian besar bahasa pemrograman populer pada saat tulisan ini dibuat,
XOScript hanya menyediakan satu objek Benar dan satu objek Salah.
Untuk memperjelas, setiap kali Anda menulis **Benar**, hal itu tidak berarti bahwa
objek baru telah dibuat. Sebaliknya, Anda selalu menggunakan referensi. Ini
berarti bahwa jika Anda menulis seperti berikut:

\>\> x := Benar.

**x** merujuk ke objek **Benar**. Kode bersyarat dan perulangan juga
memeriksa referensi ini. Dalam XOScript, makna **Benar** dan **Salah**
tidak tetap. Bahkan, program XOScript akan sangat terguncang oleh
pernyataan seperti ini:

Benar := Salah.

Hasil dari tindakan semacam itu tidak terdefinisi, tetapi tetap merupakan tindakan
yang valid dan karena itu secara formal diizinkan. Selain itu, ada objek
Boolean, yang merupakan objek akar dari **Benar** maupun **Salah**, karena keduanya
merupakan turunan dari objek akar tersebut. Namun, objek Boolean itu sendiri
tidak memiliki penerapan praktis apa pun.

## Jebakan

Berhati-hatilah saat menggunakan **dan:** dan **atau:**

```
Keluaran tulis: (Salah or: Benar or: Benar), baris-baru.
Keluaran tulis: (Salah atau: Benar, atau: Benar), baris-baru.
```

Menghasilkan

```
Salah
Benar
```
karena pesan **atau:** hanya menerima 1 argumen. Pesan pertama
mengirim **atau:atau:** ke Salah, yang tidak ada, sehingga objek mengabaikan
pesan tersebut dan mengembalikan dirinya sendiri (Salah). Di sisi lain, baris kedua
mengirim **atau:** diikuti oleh **atau:** lainnya (menggunakan simbol rantai, yaitu koma: ,).


@api_Boolean_base

# Angka

{{messages}}

Setiap kali Anda menulis sebuah angka, misalnya 9, -10, atau 3,12, di balik
layar XOScript akan mengubah angka-angka ini menjadi objek **Angka**. Anda
dapat mengirim pesan ke objek Angka ini, atau Anda dapat menetapkan angka tersebut
ke sebuah variabel lalu mengirim pesan setelahnya:

```
10 genap?

>> tenner := 10.
tenner genap?

```

Kedua notasi tersebut valid. Objek Angka menanggapi pesan-pesan
berikut...

Sebagian besar pesan ini sudah jelas dengan sendirinya dan memungkinkan Anda melakukan
operasi matematika atau perbandingan.

{{note}}
Perhatikan bahwa Anda boleh menggunakan ≤ ≥ ≠ × dan ÷ sebagai pengganti padanan ASCII-nya.
Ini adalah masalah selera.
{{/note}}

Perbedaan antara pesan matematika binary (+) dan
variasi kata kuncinya (tambah:) adalah bahwa yang pertama akan mengembalikan
angka baru, yaitu hasil operasi, sedangkan pada
yang kedua objek itu sendiri yang akan diubah. Hal ini diilustrasikan dalam
contoh berikut:

@test597

Pada contoh di atas, b = 4 dan a = 3. Dengan **tambah: 2** nilai
a dinaikkan sebesar 2, sedangkan **+ 3** membuat angka baru yang
sama dengan a + 3. Hal yang sama berlaku untuk proses matematika lainnya, misalnya
perkalian. Dengan menggunakan simbol perkalian, Anda akan menerima
objek baru sebagai jawaban. Jika Anda menggunakan pesan **kalikan-dengan:**,
Anda akan mengalikan angka itu sendiri.

Dengan pesan **antara:dan:**, misalnya pada: **Angka
antara: X dan: Y**, Anda akan mendapatkan angka antara X dan Y. Dengan
cara ini, angka acak apa pun dapat dihasilkan:

```
>> a := Angka antara: 1 dan: 10.
Keluaran tulis: a, baris-baru.
```

Sejak versi 1.4, pembangkit angka acak bawaan di xoscript
aman secara kriptografis sejauh yang kami ketahui.

Anda dapat melampirkan sebuah **satuan** ke angka, misalnya **6
apel**. Setiap pesan yang tidak dikenali oleh sebuah
angka akan dianggap sebagai satuan. Anda dapat mengambil satuan
sebuah angka dengan pesan satuan:

Satuan pada dasarnya adalah objek Teks yang disimpan bersama objek
Angka. Satuan juga dicetak setelah angka pada penugasan
**tulis:**. Satuan dapat digunakan, misalnya, untuk menjumlahkan nominal
dalam berbagai mata uang. Saat menjumlahkan nominal, Anda dapat menanyakan
satuannya. Contoh program berikut mengilustrasikan prinsip
ini dengan menggunakan kalkulator mata uang historis (karena nilai
tukarnya tetap cukup stabil!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Teks

{{messages}}

Setiap kali sebuah teks ditempatkan di antara **kurung siku dan tanda kutip** ['...'] ,
XOScript akan membuat objek teks baru untuk Anda. Namun, pastikan
untuk menggunakan tanda kutip yang benar. Tanda kutip di
awal teks berbeda dari tanda kutip di akhir (hal ini memungkinkan Anda
menggunakan tanda kutip tunggal tanpa perlu meng-escape-nya).

## UTF8

Teks di xoscript biasanya berisi teks yang dienkode dalam utf8. Meskipun
secara teknis dimungkinkan untuk menyimpan konten biner atau non-utf8 dalam
sebuah teks, disarankan untuk menggunakan blob untuk itu. Blob
disediakan oleh plugin server (lihat bab ffi).
Secara umum, blob/ffi disediakan
per plugin/platform, karena keduanya terikat pada platform
dan arsitektur (ffi/blob). Inti bahasa skrip ini berusaha
tetap seindependen mungkin dari platform.

## Konversi tipe

Anda dapat membuat salinan dari setiap objek
dengan tipe yang berbeda menggunakan pesan-pesan berikut:

Pesan   | Hasil
------- | ------
angka   | Mengonversi ke angka
teks    | Mengonversi ke teks
boolean | Mengonversi ke boolean
  
Aturan berikut **berlaku**:

pesan    | Kosong    | Boolean            | Angka                 | Teks      | Lainnya              
-------- | --------- | --------           | --------              | --------  | --------
boolean  | Salah     | t/a                | 0→Salah lainnya→Benar | Benar     | Umumnya Benar
angka    | 0         | Salah→0 Benar→1 | t/a                      | ['n']→n | Umumnya 1
teks     | ['Kosong']  | ['Salah']/['Benar'] | ['n']              | t/a       | Tergantung

## Penyalinan

Nilai dalam XOScript selalu diteruskan **melalui referensi**. Dalam bahasa lain
hal ini bergantung pada tipe nilainya, sedangkan dalam XOScript hanya ada satu cara,
yaitu melalui referensi. XOScript tidak pernah membuat salinan sebuah nilai. Untuk menyalin objek,
Anda perlu mengirim pesan **salin**. 

@test611

Di sini, Anda mungkin mengira keluarannya adalah Dolly, bukan
Donny. Namun, bukan itu yang terjadi karena kedua nama merujuk ke objek
yang sama. Saat bekerja dengan perulangan, hal serupa terjadi:

@test612

Sebenarnya, XOScript **selalu** menggunakan referensi, sehingga pada **:quantity**
perulangan yang diilustrasikan di atas juga menunjukkan referensi ke elemen
di dalam daftar.

Untuk menyalin sebuah objek, Anda harus menyatakan tindakan ini
secara **eksplisit**:

@test613

Dengan mengirim pesan unary **salin** ke sebuah teks, objek tersebut
mengembalikan salinan dari objek teks yang sama. Objek Angka,
objek boolean, daftar, dan kamus dapat disalin dengan cara yang sama.

Anda juga dapat mendefinisikan implementasi penyalinan Anda sendiri; hal ini bahkan
diperlukan jika Anda membuat objek sendiri. Implementasi
bawaan salin untuk daftar membuat salinan dangkal, yaitu membuat
daftar baru dengan elemen-elemen yang sama.

@test614

Dalam hal ini, 4 hanya ditambahkan ke salinannya.
Namun, karena salinannya dangkal, objek-objek di kedua daftar
tetap sama.

@test615

Jadi, jika kita menambahkan 2 ke setiap nama dalam salinan, daftar
aslinya juga ikut terpengaruh.

Untuk mengatasinya, kita perlu membuat **salinan dalam**. Tindakan penyalinan semacam itu
untuk daftar dapat disusun sebagai berikut:

@test616

Perhatikan juga pesan rekursif; pesan ini perlu
dikirim sebelum pesan salin.

Penting untuk diingat bahwa meskipun salinan sebuah objek
sering kali terlihat sama dengan aslinya, salinan itu sebenarnya
tidak pernah sama. Objek akar mendefinisikan pesan **equal:**,
yang dapat digunakan untuk membandingkan identitas objek. Perhatikan
contoh berikut:

@test617

## Konversi implisit

XOScript menggunakan **konversi implisit** untuk mengonversi objek. Untuk mencetak
sebuah daftar di layar, XOScript misalnya akan mengirim pesan
*teks* secara internal ke daftar tersebut. Hal ini bisa sangat berguna
jika Anda ingin mencetak daftar sebagai daftar yang dipisahkan koma.
Pesan *teks* dapat ditimpa: 

@test620

@api_String_base
@api_Format_base


## Teks di server

Fitur Teks berikut ditambahkan oleh
plugin Server.

@api_String_server

# Fungsi

{{messages}}

Anda dapat mengelompokkan kode di antara { dan }, sehingga menjadi sebuah fungsi.
Di xoscript kami terkadang juga menggunakan istilah tugas atau sekadar
blok kode.

Anda dapat menjalankan sebuah fungsi dengan mengirim pesan *mulai*.


```
{ Keluaran tulis: 123, baris-baru. } mulai.
```

Jika fungsi Anda menerima argumen, gunakan **terapkan:**.

```
{ :a Keluaran tulis: a, baris-baru. } terapkan: a.
```

Lihat juga contoh-contoh di bawah ini.
Karena arsitekturnya yang sederhana, sebuah fungsi hanya dapat memiliki
satu titik kembali. Untuk menghindari beban tambahan atau penumpukan berlebihan pada
kondisi, Anda dapat menggunakan prosedur (yang sama dengan menggunakan
tanda perkalian dengan argumen 1):

```
{
  (a = 1) benar: { x := 1. }, hentikan.
  (a = 2) benar: { x := 2. }, hentikan.
} prosedur.
```

Dengan cara ini, (a = 2) tidak akan dievaluasi jika a = 1.
Selain itu, dengan cara ini Anda tidak memerlukan pesan benar yang bertumpuk.
Setiap kali Anda mendapati diri Anda menumpuk kondisi, ingatlah
pesan prosedur. Pesan ini dapat membuat kode Anda
lebih mudah dibaca.


Berikut adalah jebakan penting:

```
{
	Salah salah: {
		Keluaran tulis: ['End the loop.'].
	}, hentikan.
	
	Keluaran tulis: ['Dont show me.'].

} prosedur.

```

Dalam hal ini, teks 'Dont show me' akan ditampilkan,
karena **hentikan** dikirim ke Salah. Jika Anda ingin menjalankan
penghentian, pesan tersebut harus dikirim ke **Benar**.
 

```
{
	Salah bukan benar: {
		Keluaran tulis: ['End the loop.'].
	}, hentikan.
	
	Keluaran tulis: ['Dont show me.'].

} prosedur.

```

Akan berfungsi seperti yang diharapkan.

## Eksepsi

Eksepsi dapat ditangani seperti ini:

```
{ Task 1 } tangkap: { Task 2 }, mulai.
```

Anda juga dapat dengan sengaja menimbulkan galat dalam program Anda, dan
dengan demikian mengaktifkan blok penangan. Hal ini dilakukan dengan mengirim
pesan **galat:** ke tugas saat ini seperti yang ditunjukkan pada ilustrasi
berikut:

```
{
tugas-ini galat: ['Whoops!'].
} tangkap: { :mistake
Keluaran tulis: mistake.
}, mulai.
```

## Menyuntikkan nilai

XOScript menyediakan opsi bagi tugas untuk menyuntikkan nilai. Sekarang, perhatikan
tugas di bawah ini:

```
>> sending := {
	Newsletter kepada: milik recipient.
}.
sending atur: ['recipient']
nilai: ['info@recipient.org'].
sending mulai.
```


Ilustrasi ini menyajikan tugas khayalan yang mengirim buletin
ke sebuah alamat surel atau **penerima** (recipient). Penerima ini dapat disuntikkan
ke dalam tugas dari luar dan sebelum tugas dimulai, dengan mengirim
pesan **atur:nilai:** ke tugas tersebut. Dengan begitu, nilai
**recipient** sudah ditetapkan sebelumnya di dalam tugas. Nilai ini juga dapat diubah,
lalu tugas tersebut dapat dijalankan lagi. Ini adalah metode yang berguna saat menggunakan
objek Task.

## Fungsi kosong

Tugas kosong tidak diizinkan. Secara teori, tugas kosong akan terlihat seperti
ini: **{}**, tetapi XOScript menganggapnya sebagai kesalahan bahasa. Jika Anda
ingin mendeklarasikan tugas kosong, Anda dapat menggunakan objek Kosong:

```
>> task := Kosong.
```

Meskipun ini bukan tugas sungguhan, melainkan objek Kosong, pesan mulai
tetap dapat dikirim:

```
>> answer := task mulai.
```

Sebenarnya, ini sama dengan:

```
>> answer := Kosong mulai.
```

Karena objek **Kosong** tidak mengenali pesan **mulai**, objek tersebut
akan mengembalikan dirinya sendiri sebagai jawaban, sehingga jawabannya sekali lagi **Kosong**.
Jadi, tugas kosong tidak diperlukan. Berkat desain bahasa
pemrograman XOScript yang elegan, Anda cukup menggunakan objek Kosong
untuk hal ini.

## Cakupan dinamis

Jika sebuah Fungsi membutuhkan variabel tetapi tidak dapat menemukannya,
Fungsi tersebut akan memeriksa variabel-variabel Fungsi yang **memanggilnya**,
dan terus memeriksa ke atas sepanjang rantai Fungsi.
Proses pencarian ini berlanjut sampai variabel tersebut ditemukan.
Jika variabel tetap tidak ditemukan, pesan galat akan muncul. Metode pencarian
variabel ini disebut **Cakupan Dinamis**.

Untuk mengilustrasikan prinsip ini:

@test618

@api_Code_base

# Objek akar

{{messages}}

Objek bernama **Objek** adalah objek akar dari semua objek dalam
XOScript dan menyediakan fitur-fitur inti bahasa. 

Pesan yang paling sering dikirim
adalah **saat:lakukan:**, yang memperluas fungsionalitas sebuah objek. Pesan
ini diterima oleh objek akar, yang kemudian menautkan
tugas yang ditentukan ke pesan tersebut, dan dengan demikian memperluas objek
turunan.

## Metode penangkap-semua

Biasanya, jika Anda mengirim pesan yang tidak sesuai dengan
metode apa pun dalam objek, pesan tersebut diabaikan. Namun, Anda dapat menentukan
apa yang disebut **metode ajaib** atau metode **penangkap-semua** yang akan
dipanggil jika pesan tidak dipahami oleh objek.

Tersedia 4 metode penangkap-semua. Setiap pesan sesuai dengan
jumlah argumen tertentu.

Pesan penangkap-semua | Jumlah argumen
-------------------- | -------------------
tanggapi:             | 0
tanggapi:dan:         | 1
tanggapi:dan:dan:     | 2
tanggapi:dan:dan:dan: | 3


@test619

## Pesan terprogram

Alih-alih dikirim langsung ke sebuah objek, pesan juga dapat
dikirim melalui variabel. Untuk itu, Anda menggunakan pesan
**pesan:argumen:**. 

@test396

@api_Object_base

# Daftar

{{messages}}

XOScript mengenal dua jenis koleksi: *daftar* dan *kamus*.
**Daftar** adalah enumerasi objek dalam *urutan tetap*. Kamus tidak
memiliki urutan, melainkan menyerupai legenda yang terdiri dari kunci (atau istilah) dan
nilai yang sesuai. Daftar sebanding dengan array (PHP, Java, C)
dan list (Python). Kamus sebanding dengan array asosiatif (PHP) atau
dictionary (Python) dalam bahasa pemrograman lain. Untuk membuat
Daftar baru, tulis:

```
>> fibonacci := Daftar baru.
```

Daftar kosong ini dapat diisi menggunakan **tambah-di-akhir:** :

```
fibonacci tambah-di-akhir: 0.
fibonacci tambah-di-akhir: 1.
fibonacci tambah-di-akhir: 1.
fibonacci tambah-di-akhir: 2.
fibonacci tambah-di-akhir: 3.
fibonacci tambah-di-akhir: 5.
fibonacci tambah-di-akhir: 8.
fibonacci tambah-di-akhir: 13.
```

Jika kita menulis daftar ke layar:

```
Keluaran tulis: fibonacci, baris-baru.
```

Kita akan melihat:

```
Daftar ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

Alih-alih tambah-di-akhir, Anda juga dapat menggunakan ; untuk menambahkan elemen ke daftar:


```
>> fibonacci := Daftar baru ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Titik koma (;) semuanya adalah pesan binary yang memasukkan
nilai ke dalam daftar.

## Perangkaian

Misalkan Anda memiliki daftar seperti:

```
>> x := Daftar baru ; 1 ; 2 ; 3.
```

Jika Anda ingin menghapus elemen pertama dan terakhir, maka
pesan Anda adalah:

```
x ambil-pertama ambil-terakhir.
```

Sayangnya, notasi sebelumnya tidak akan berfungsi dengan benar.
Pesan **ambil-pertama** mengembalikan elemen pertama daftar, yang
pada gilirannya akan menjadi penerima pesan **ambil-terakhir**. Jadi,
pesan **ambil-terakhir** tidak dikirim ke **x**, melainkan ke 2.
Solusi yang mungkin untuk masalah ini adalah membuat dua kalimat
terpisah, seperti: 

```
x ambil-pertama.
x ambil-terakhir.
```

Namun, hal ini agak tidak praktis, terutama jika Anda perlu
menghapus lebih dari dua elemen. Oleh karena itu, XOScript menawarkan
struktur pesan alternatif untuk situasi semacam ini. Dalam
struktur pesan **alternatif**, jawaban dari objek diabaikan
dan Anda akan mendapatkan objek penerima kembali sebagai jawaban, berulang kali.
Struktur pesan **alternatif** dimulai dengan mengirim
pesan **lakukan** ke sebuah objek, dan struktur pesan **alternatif**
dapat diakhiri dengan mengirim pesan **selesai**. Pada
contoh yang diilustrasikan, hal ini dapat diterapkan sebagai berikut:

```
>> x := Daftar baru ; 1 ; 2 ; 3.
x lakukan ambil-pertama ambil-terakhir selesai.
```

@api_List_collections

# Kamus

{{messages}}

**Daftar maupun Kamus adalah koleksi. Namun, berbeda dengan
daftar, kamus **tidak memiliki** urutan. Perbedaan lain antara keduanya
adalah bahwa kamus terdiri dari pasangan objek. Satu objek berperan sebagai entri (atau
kata kunci) untuk mencari objek lainnya. Contoh yang baik dari
daftar semacam itu adalah daftar harga, seperti:


```
>> menu := Kamus baru
	taruh: ['£5'] di: ['apple pie'],
	taruh: ['£6'] di: ['carrot cake'],
	taruh: ['£3'] di: ['fudge'].
```

Mirip dengan daftar, pesan taruh:di:
digunakan untuk menambahkan objek ke daftar. Perbedaannya adalah, berbeda dengan
daftar, dua objek ditautkan. Objek pertama, sama seperti
pada daftar, adalah objek yang akan Anda simpan dalam daftar. Objek
kedua bukanlah posisinya dalam koleksi, melainkan **entri**
yang memungkinkan objek sebelumnya diambil kembali di kemudian hari.
Singkatnya, kamus bekerja seperti kamus sungguhan; jadi, dengan menggunakan kata kunci,
maknanya dapat ditemukan. Misalnya, untuk mengambil harga fudge dari
daftar yang disebutkan di atas:

```
>> price := menu di: ['fudge'].
```

Anda juga dapat menggunakan notasi singkat:

```
>> price := menu ? ['fudge'].
```

Jika entri yang Anda gunakan untuk menyimpan objek tidak mengandung spasi
(dan tidak bertabrakan dengan pesan lain yang sudah ditentukan),
notasi berikut juga dapat digunakan:

```
>> menu := Kamus baru
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Tidak diragukan lagi bahwa notasi di atas terbaca sedikit lebih alami.
Untuk meminta harga
fudge, notasi sederhana berikut dapat digunakan:

```
>> price := menu fudge.
```

@api_Dict_collections

# Berkas

{{messages}}

Objek **Berkas** menyediakan akses dasar ke sistem berkas.
Anda dapat menggunakan objek ini untuk membaca seluruh berkas ke dalam variabel
sekaligus, atau menulis variabel ke berkas sekaligus. Pembacaan baris demi baris
juga didukung. Ini adalah operasi I/O berkas yang paling umum
dalam bahasa skrip. Operasi berkas tingkat lanjut memerlukan
penggunaan FFI melalui plugin server atau plugin IO terpisah.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Tanggal/Waktu

{{messages}}

Untuk representasi waktu dan tanggal yang terstruktur, XOScript menggunakan
objek **Momen**. Jika objek Momen baru dicetak di layar,
tanggal dan waktu saat ini akan ditampilkan:

```
Keluaran tulis: Momen baru, baris-baru.
```

Mungkin menghasilkan sesuatu seperti:

```
2020-10-10 12:16:39
```

Komponen waktu satu per satu juga mudah dibaca. Jadi,
misalnya, jika Anda hanya perlu mengetahui tahun saat ini, pesan
**tahun** dapat dikirim ke momen tersebut, dan sebagai balasannya Anda akan menerima
objek Angka yang hanya berisi tahun:

```
>> m := Momen baru.
Keluaran tulis: m tahun, baris-baru.
```

@api_Moment_system

# Program/StdOut

{{messages}}

Objek Program mewakili aplikasi yang sedang berjalan. Objek ini
menawarkan fungsionalitas untuk menjalankan perintah sistem, menyertakan subprogram,
membaca argumen, dan lainnya. Semua fungsi yang berkaitan dengan sistem.

## StdOut

Keluaran adalah objek keluaran standar. Pada dasarnya objek ini memiliki dua metode:
**tulis:** dan **baris-baru**. Pesan tulis: digunakan untuk mengirim teks
ke stdout, sedangkan pesan baris-baru mencetak karakter baris baru.
Alih-alih **baris-baru**, Anda juga dapat menggunakan \\n.

Contoh:

```
Keluaran tulis: ['Hello World'], baris-baru.
```

hasil:

```
Hello World
```

## Modul/Plugin

Dunia XOScript dapat diperluas dengan objek sistem baru dengan
memasang modul. Objek sistem baru dapat ditambahkan ke dunia
XOScript dengan menempatkan berkas modul (biasanya berkas dengan akhiran .so
) ke dalam folder mods. 

Saat Anda mengirim pesan ke objek yang disediakan melalui
modul plugin, modul tersebut akan dimuat secara otomatis oleh XOScript.

Anda juga dapat menulis plugin sendiri. Plugin ditulis dalam
bahasa pemrograman C. Anda dapat menemukan contoh plugin dalam paket
kode sumber di src/plugins/example.


## Refleksi

Ada berbagai cara untuk menjelajahi
sistem selama program berjalan. XOScript memiliki beberapa metode untuk
mendeteksi objek mana yang ada dan pesan mana yang ditanggapi
objek-objek tersebut. Pertama, setiap objek dapat ditanya apa **tipe**-nya,
tetapi tipe dalam XOScript mudah berubah dan karena itu tidak dapat diandalkan.

Anda juga dapat menanyakan kepada objek Program apakah
suatu objek sudah ada dalam program:

```
Program Tool benar: { ... }.
```

Jika nama objek
hanya terdiri dari satu simbol, sebaiknya gunakan
notasi berikut untuk menghindari kebingungan:

```
Program temukan: ['X'], benar: { ... }.
```

Selain menanyakan tentang objek, Anda juga dapat menanyakan kepada
objek Program tentang pesan. Misalnya, dapat ditanyakan apakah
objek **Angka** mengenal pesan **antara:dan:**, dengan cara
seperti yang diilustrasikan di bawah ini:

```
Program Number: ['between:and:'], baris-baru.
```

@api_Program_system

# server

{{messages}}

Plugin Server di xoscript menyediakan fungsionalitas untuk
membuat aplikasi sisi server. Untuk memuat plugin
server, gunakan:

```
Server inisialisasi.
```

Untuk kemudahan Anda, disarankan juga untuk memuat
berkas webtools.xo dan template.xo.

```
Program gunakan: ['webtools.xo'].
Program gunakan: ['template.xo'].

```

## Pengaturan server

Anda dapat mengatur pengaturan server berikut:

```
	# default values are given
	# so if you do not set anything these
	# values are used...

	Program 
	pengaturan: ['max-postfields']
	nilai: 40.

	Program 
	pengaturan: ['max-contentlength']
	nilai: 2000000. # 2MB

	Program 
	pengaturan: ['max-time']
	nilai: 5000. # 5sec

```

## Halo dunia

Berikut adalah program web yang sangat sederhana yang dapat Anda gunakan dengan
server CGI standar seperti Apache2, NGINX, OpenHTTPD, atau server terkenal
lainnya.

```
#!/bin/xo

Server inisialisasi.
Program gunakan: ['webtools.xo'].

>> web-document := Dokumen-Web baru.

web-document keluarkan: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Jika Anda tidak ingin menggunakan objek Dokumen-Web, tidak masalah, tetapi
Anda harus menulis tajuk HTTP sendiri:

```
#!/bin/xo
Keluaran tulis: ['Content-type: text/html; charset=utf-8 \n\n'], baris-baru.
Keluaran tulis: ['hello world!'], baris-baru.
``` 

## Permintaan

Objek Permintaan-HTTP dapat digunakan untuk memperoleh data GET/POST/COOKIE dan
UPLOAD:

```
>> permintaan-http  := Permintaan-HTTP baru.
>> search   := permintaan-http get: ['search']. # ?search=books
>> password := permintaan-http post: ['password']. # from form
>> selected := permintaan-http get-daftar: ['sel[]']. #?sel[]=1&sel[]=2
>> selected := permintaan-http post-daftar: ['sel[]'].
>> cookie   := permintaan-http cookie: ['session-id'].
>> upload   := permintaan-http upload: ['file'].
>> temppath := upload ? 1.
>> filename := upload ? 0.
```

## Maxpost/length

Jumlah maksimum bidang post secara bawaan adalah 40, dan panjang konten
maksimum secara bawaan adalah 2MB. Untuk mengonfigurasinya secara berbeda per skrip:

```
Program pengaturan: ['max-contentlength'] nilai: 1. 
Program pengaturan: ['max-postfields'] nilai: 1. 
```

{{note}}
Jika panjang konten melebihi batas maksimum,
proses akan dihentikan karena kami tidak dapat lagi memastikan
bahwa muatannya aman.
{{/note}}

Batas maxtime menentukan waktu maksimum dalam ms
untuk membaca stdin/data post.

```
Program pengaturan: ['max-time'] nilai: 5000. # 5sec
```

Hal ini hanya berlaku untuk pembacaan I/O dari post, sehingga mencegah
serangan seperti slowloris. Jika Anda benar-benar ingin membatasi
waktu eksekusi operasi apa pun, gunakan Program batas-waktu:.

## Basis data

Objek Database dapat digunakan untuk melakukan kueri ke MariaDB/MySQL.
Untuk tersambung ke basis data, lakukan:

```
>> db := Maria-DB baru hos: ['localhost'],
	nama-pengguna: ['xo'],
	kata-sandi: ['pass123'],
	nama-basis-data: ['xobase'],
	sambungkan.

```

Untuk menyisipkan rekaman, gunakan:

```
>> parameter-pencarian := db kueri: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], parameter: ( Daftar baru ; ['abc'] ; 12.35 ; 6 ). # parameterized queries

{  parameter-pencarian jalankan. db komit. }
tangkap: { :e db batalkan.  }, mulai.
```

Perhatikan bahwa xoscript *hanya* bekerja dengan transaksi dan tidak pernah melakukan autocommit.
Jika autocommit tidak dapat dinonaktifkan, Anda akan mendapatkan galat koneksi.
Selalu gunakan pengikatan parameter untuk kueri, jangan pernah menambahkan masukan pengguna secara langsung
ke dalam SQL.

Dapatkan id yang disisipkan seperti ini:

```
Keluaran tulis: ['INSERTED: '] + parameter-pencarian insert-id, baris-baru. # insert id
```

Untuk mengambil rekaman:

```
>> parameter-pencarian :=
db
	kueri: ['SELECT * FROM book order by id desc limit 2'], 
	ambil: { :row 
		Keluaran tulis: row id + [' '] + row description + [': '] + row price, baris-baru.
	}. # fetching rows

```

## Sesi

Untuk persistensi, Anda dapat menyimpan dan mengambil data dari objek sesi.
Pertama, buat **Dokumen-Web** baru. Objek Dokumen-Web menyatukan
permintaan, tajuk, HTML, dan sesi. Hal ini karena setiap kali Anda
mengunjungi situs web dengan peramban, Anda hanya melihat HTML-nya. Namun,
seluruh Dokumen-Web juga terdiri dari **Tajuk**. Misalnya,
sebagian besar respons HTTP menyertakan tajuk seperti: Content-type:text/html untuk
memberi tahu peramban bahwa data berikutnya harus ditampilkan sebagai HTML
(dan bukan, misalnya, diunduh seperti berkas). Sesi adalah cara untuk
menyimpan data pengguna di antara permintaan. Untuk melacak data ini, kita perlu
mengatur sebuah cookie, dan cookie ini juga diatur melalui sebuah Tajuk. Itulah sebabnya
semuanya berkumpul di dalam Dokumen-Web (karena itulah dokumen
lengkap yang berisi tajuk maupun HTML atau data lainnya).


```
# First we make a new Web Document instance
>> web := Dokumen-Web baru.

# Now we start a session, this will generate a Header for a cookie and
# create a file to store your data, associated with that cookie
>> session := web mulai-sesi.

# Now we can treat session like a dict
session userid: 123.
```

Untuk menghancurkan sesi (saat keluar):

```
web hancurkan-sesi.
```

## Tajuk

Dokumen-Web juga memungkinkan Anda mengatur tajuk terkenal lainnya.
Misalnya, jika Anda ingin mengalihkan pengguna ke URL lain:

```
web pergi-ke: ['/other.html'].
```

Di balik layar, perintah ini juga menghasilkan tajuk HTTP yang dikirim
bersama data atau HTML Anda lainnya untuk menginstruksikan peramban agar menuju
ke alamat tujuan yang ditentukan.

Untuk menambahkan tajuk khusus:

```
web tajuk: ( 
	Tajuk-HTTP baru
	kunci-tajuk: ['Content-Length']
	nilai: 400
).
```

Untuk menampilkan halaman 404:

```
web tidak-ditemukan: ['OOps..'].
```


## Templat

Sistem templat bawaan sangat sederhana. Anda tidak perlu mempelajari
sintaksis templat baru. Selain itu, mesin templat menjamin pemisahan yang nyata
antara presentasi dan logika bisnis.

Untuk membuat templat dari sebuah berkas:

```
>> tpl := web templat: ['templates/ux.tpl'].
```

Sistem templat menggunakan penanda. 
Ada tiga jenis penanda: penanda potong, penanda tempel, dan
penanda slot. Gagasan dasarnya sangat sederhana: Anda memotong
area yang ditandai oleh penanda potong dan dapat menempelkannya di
area yang ditandai oleh penanda tempel. Anda dapat menyuntikkan teks ke dalam
penanda slot.

Jadi, misalnya, dengan templat berikut, mari kita masukkan
permata ke dalam kotak perhiasan dan tambahkan label harga.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Anda dapat melakukannya sebagai berikut:

```
>> gem := tpl potong: ['gem'], salin.
gem price: 99.
tpl tempel: gem di: ['jewels'].
web keluarkan: tpl rapikan.
```

Baris terakhir cukup mengirimkan templat sebagai teks ke klien
beserta tajuk HTTP yang diperlukan.

Hasil:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Passthru

Untuk menyajikan berkas yang diunggah pengguna secara aman, Anda dapat mengandalkan passthru:

```
>> uploaded := ['smile.gif'].
Server teruskan: uploaded awalan: ['/uploads/images/'].
Program akhiri.
```

Ini akan menyajikan konten yang diunggah pengguna dengan tipe mime
yang sesuai. Hanya tipe mime dalam daftar putih yang didukung:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF, dan SVG.
Berkas SVG, ZIP, dan GZIP dikirim sebagai unduhan, karena SVG
dapat berisi skrip yang jika tidak demikian akan berjalan di domain Anda.
Metode ini mencegah serangan TOCTOU, penelusuran jalur (path traversal),
eksekusi kode berbahaya (injeksi), serangan symlink,
serangan DDoS (batas berkas = 50MB), serangan sniffing, dan
berbagai masalah keamanan lainnya.


## JSON

Untuk mengenkode objek sebagai JSON:

```
>> json := ( JSON jsonify: ( 
	Kamus baru taruh: ( 
		Daftar baru ; 1 ; 2 ; 3
	) di: ['abc']
)).
```

Untuk mendekode JSON menjadi objek xoscript:

```
>> dict := ((JSON objek: json) abc ? 1).
```

JSON dengan lebih dari 500 tingkat penumpukan ditolak sebagai tidak valid.

Untuk langsung mengeluarkan Kamus sebagai json dengan tajuk yang benar:

```
web json: dict.
```


## Regex

Anda dapat menggunakan ekspresi reguler dengan membuat sebuah pola.
Misalnya, untuk mencocokkan href dan target dari hyperlink:

```
Pola baru: ['href="([^"]+)" target="([^"]+)"'].
```

Sekarang, terapkan pola tersebut ke teks subjek seperti ini:

```
pattern cocok: subjek lakukan: { :m :x .... }
```

Contoh lengkap:

```
>> subjek := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> pattern := Pola baru: ['href="([^"]+)" target="([^"]+)"'].
>> result  := pattern cocok: subjek lakukan: { :m :x
	Keluaran tulis: m, baris-baru.
	Keluaran tulis: x, baris-baru.
	<- ['XXX'].
}.
Keluaran tulis: result, baris-baru.
```

## Jaringan

Gunakan objek Jaringan untuk melakukan permintaan web.
Objek Jaringan selalu mengirim permintaan POST, kecuali jika Anda mengirim Kosong sebagai
data, maka objek ini akan mengirim permintaan GET.


```
Jaringan 
post: Kosong 
ke: ['https://redbeanphp.com'].
```

## Enkripsi

Plugin server dilengkapi dengan enkripsi berbasis XChaCha20 dan Argon2.

Contoh:

```
>> encrypted := Brankas enkripsi: ['hello'] kunci: ['world'].
>> decrypted := Brankas enkripsi: encrypted kunci: ['world'].
```

## Token

Untuk menghasilkan token yang aman secara kriptografis dengan panjang tertentu:

```
>> mytok := Brankas token: 40.
```

Ini akan menghasilkan token sepanjang 40 karakter.

## Pemformatan

Objek Format memungkinkan Anda memformat data, seperti menambahkan padding atau
angka nol. Objek ini menggunakan sintaksis printf.

```
>> fmt := Format baru: ['%06.0f'].
fmt terapkan: 56. # gives 000056
```

Sebuah format dapat berisi satu konversi dan harus sesuai dengan nilainya,
jika tidak, Anda akan mendapatkan galat:

- `terapkan:` dengan teks: `%s`
- `terapkan:` dengan angka: `%f`, `%e`, `%g` atau `%a`
- `terapkan-bilangan-bulat:` dengan angka: `%d`, `%i`, `%o`, `%u`, `%x` atau `%c`

Nilai dari sebuah permintaan berupa teks. Untuk memformatnya sebagai angka,
konversikan terlebih dahulu:

```
fmt terapkan: (permintaan-http get: ['amount']) angka.
```

## Enkoder

Tersedia beberapa enkoder dan dekoder.
Enkoder url menyiapkan url untuk digunakan dalam HTML sebagai tautan:

```
Server url-enkode: ['https://example.com?a=6&b=1 2'].
```

Untuk menyuntikkan masukan pengguna ke dalam HTML Anda dengan aman tanpa risiko
injeksi XSS, selalu gunakan:

```
Server html-enkode: ['<harmless>'].
```

Perhatikan bahwa mesin templat akan selalu melakukan enkode html
jika Anda menulis ke penanda slot. Jadi, jika Anda menggunakan sistem templat,
Anda tidak perlu menggunakan ini.

## Pengiriman surel

Untuk mengirim surel, gunakan pustaka mailtools.xo.

Contoh:

```
Server inisialisasi.
Program gunakan: ['mailtools.xo'].

>> e-mail := Surel-HTML baru.
>> img := e-mail lampirkan: ( Berkas baru: ['myimage.png'] ).

e-mail
pengirim: ['xo@xoscript.com'] nama: ['xo'],
kepada: ( Daftar baru ; ['xo2@xoscipt.com'] ),
subjek: ['xoxo'],
badan: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), kirim.

```



## Penautan

Dengan pesan tautkan:, Anda dapat menautkan pustaka eksternal ke
program Anda menggunakan libffi. Untuk rinciannya, lihat bab tentang ffi.


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

FFI disediakan per platform/plugin karena
terikat pada arsitektur sistem yang mendasarinya, sesuatu yang
tidak seharusnya dilakukan oleh inti.
Plugin server menawarkan implementasi ffi/blob yang sesuai.
Secara bawaan, inti terhubung ke platform target
melalui stdin/stdout, layanan i/o berkas yang terbatas, dan shell (Program sistem:).
Integrasi tambahan disediakan oleh ffi/blob melalui plugin
yang berpusat pada aplikasi, seperti plugin server.

FFI adalah singkatan dari Foreign Function Interface. FFI memungkinkan Anda menggunakan fungsionalitas yang ditulis oleh orang lain dalam
bahasa pemrograman yang berbeda, yang disediakan melalui berkas DLL, berkas SO, atau berkas Dylib. Fungsionalitas ini bisa
berupa beragam fungsi, dan melalui metode ini tersedia fungsionalitas yang sangat luas.
Mari kita mulai dengan sebuah contoh:

```
Server tautkan: (
 Daftar baru ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Daftar baru ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s bebaskan.
```

Hasil dari kode ini adalah Anda akan melihat yang berikut di baris perintah:
FFI has 3 letters.
Sekarang, Anda mungkin berpikir, "Banyak sekali kode untuk sesuatu yang begitu sederhana."
Maksud saya, bukankah kita bisa menyelesaikan ini dengan perintah Gui show? Jawabannya tentu saja bisa!
Namun, ini dimaksudkan sebagai contoh ilustratif.
FFI biasanya digunakan untuk tugas-tugas yang lebih rumit, tetapi tugas-tugas itu tidak menjadi
contoh yang baik, jadi saya memilih sesuatu yang sepele.

Argumen untuk metode tautkan:

- Argumen #1: Berkas DLL atau SO yang ingin Anda gunakan.
- Argumen #2: Fungsi dalam berkas tersebut yang ingin Anda tautkan.
- Argumen #3: Daftar berisi nama-nama tipe data dari argumen fungsi.
- Argumen #4: Nama tipe kembalian fungsi.
- Argumen #5: Nama objek yang ingin Anda tautkan dengan fungsi ini (jika belum ada, objek tersebut akan dibuat
secara otomatis).
- Argumen #6: Pesan yang harus ditautkan dengan fungsi ini.

Pada contoh di atas, kita ingin menautkan fungsi printf dari libc.so. Anda dapat menemukan nama-nama
tipe data dalam dokumentasi perangkat lunak yang Anda tautkan. Tipe yang tersedia adalah:
void, pointer, float, double, int, uint, char, uchar, intX, dan uintX,
dengan X dapat bernilai 8, 16, 32, atau 64.

Tipe-tipe ini mengacu pada jumlah bita yang diperlukan untuk menyimpan data. Untuk printf, kita menautkan ke
objek baru bernama Printf dan pesan template:number:. Anda menerjemahkan fungsi
eksternal ke dalam dialek XOScript sebelum menggunakannya. Pesan template:number: mengharapkan
penyangga (buffer) berisi teks templat sebagai parameter pertamanya. Kita membuat penyangga ini menggunakan objek Blob, yang
memungkinkan Anda mengalokasikan memori secara manual. Anda bertanggung jawab untuk membebaskan memori ini setelahnya
dengan pesan bebaskan.

Anda dapat mengisi blob memori dengan berbagai cara. Dalam contoh kita, blob diisi dengan teks, sehingga kita menggunakan
pesan utf8: (UTF-8 adalah enkode untuk mengubah teks menjadi bita). Anda juga dapat mengisi blob dengan
bytes:, dengan memberikan daftar nilai bita. Untuk membaca isi sebuah blob, gunakan dari:panjang:.
Anda akan mendapatkan bita-bitanya kembali dalam bentuk daftar. Anda bahkan dapat membuat C-struct dengan Blob menggunakan
pesan struct:, dengan memberikan urutan tipe C. Hal ini mungkin diperlukan saat memanggil fungsi
C dalam pustaka perangkat lunak eksternal yang mengharapkan pointer ke sebuah struct.

{warning}
Anda harus membebaskan blob sendiri.
Blob tidak dibersihkan oleh pengumpul sampah (garbage collector).
{/warning}

Karena blob dapat dipertukarkan dengan fungsi eksternal dari pustaka,
blob tidak dapat dibersihkan secara otomatis oleh pengumpul sampah (blob mungkin masih digunakan oleh
fungsi eksternal, atau fungsi eksternal tersebut mungkin ingin membebaskannya
sendiri). Oleh karena itu, Anda perlu membebaskan blob sendiri jika diperlukan.

Untuk membebaskan blob, gunakan:

```
myblob bebaskan.
```

Untuk membebaskan struct, gunakan:

```
mystruct bebaskan-struct bebaskan.
```

Jadi, untuk struct, Anda perlu mengirim dua pesan: bebaskan-struct dan bebaskan untuk
membebaskan blok memori.

@api_Blob_fficonnect
