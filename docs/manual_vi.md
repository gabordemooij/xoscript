# Cơ bản

{{messages}}


Chào mừng đến với XOScript
Dự án XOScript hướng tới việc tạo ra một ngôn ngữ kịch bản đơn giản và có thể kiểm toán được.
Đơn giản không nhất thiết có nghĩa là dễ.
Một ngôn ngữ lập trình quen thuộc có thể dễ sử dụng hơn XOScript.
Ở đây, sự đơn giản mang một ý nghĩa khác:
khả năng hình thành một mô hình tư duy hoàn chỉnh về ngôn ngữ và hành vi của nó.

XOScript được thiết kế để bạn có thể nắm trọn trong đầu.
Ngữ pháp và số lượng khái niệm của nó được cố ý giữ ở mức tối thiểu.
Không có lớp (class); các đối tượng có thể được mở rộng trực tiếp.
Đối tượng được truyền theo tham chiếu, việc sao chép phải được thực hiện tường minh,
và các hàm chỉ có một điểm thoát duy nhất.

Một số lựa chọn này khác biệt đáng kể so với các ngôn ngữ phổ biến.
Chẳng hạn, XOScript không có hệ thống kiểu và sử dụng phạm vi động (dynamic scoping).
Các thông điệp không thể xử lý sẽ bị bỏ qua thay vì gây ra ngoại lệ.
Những lựa chọn này có hệ quả của chúng và không nhằm mục đích loại bỏ lỗi.
Chúng nhằm giữ cho mô hình nền tảng của ngôn ngữ nhỏ gọn và nhất quán.

XOScript cũng có thể được bản địa hóa, giúp diễn đạt các quy tắc nghiệp vụ
bằng ngôn ngữ tự nhiên và có thể chia sẻ chúng với những bên liên quan không chuyên về kỹ thuật.

Khả năng kiểm toán có nghĩa là áp dụng cùng một triết lý cho phần cài đặt.
Môi trường thực thi được viết bằng C, với một bộ phân tích từ vựng, bộ phân tích cú pháp và bộ duyệt cây nhỏ, viết tay.
Thư viện chuẩn và môi trường thực thi phần lớn phản ánh cấu trúc của ngôn ngữ,
khiến mối quan hệ giữa mã XOScript và phần cài đặt của nó tương đối trực tiếp.

Các bài kiểm thử cũng gắn chặt với tài liệu.
Mỗi phương thức nên có một bài kiểm thử tương ứng có thể được đưa vào sổ tay,
giúp tài liệu luôn đồng bộ với phần cài đặt.

XOScript không nhằm cạnh tranh với các ngôn ngữ phổ biến về
tính năng hay sự quen thuộc. Nó theo đuổi một mục tiêu khác:
một môi trường lập trình mà lập trình viên có thể hiểu được toàn bộ.

Hy vọng là một ngôn ngữ nhỏ và một phần cài đặt
nhỏ sẽ giúp việc hiểu phần mềm trở nên khả thi,
từ byte đến đối tượng, từ cú pháp đến môi trường thực thi, và giúp bạn viết mã một cách
tự tin vì bạn hiểu cả những gì xảy ra trong
kịch bản lẫn những gì xảy ra bên dưới.

Kiến trúc của một hệ thống máy chủ xoscript
đơn giản nhưng linh hoạt.

{{architecture.png}}

Để sử dụng xoscript làm ngôn ngữ phía máy chủ, bạn cần cài đặt
plugin máy chủ vào một thư mục có tên /mods/server. 

Lý do là chúng tôi muốn
tách biệt ngôn ngữ lõi khỏi các chức năng dành riêng cho máy chủ,
khác với PHP hay Python chẳng hạn. Nếu không, chúng tôi sẽ phải gửi
toàn bộ mọi thứ cho tất cả mọi người mà chẳng để làm gì, điều đó thật vô lý.
Bạn cũng có thể cài đặt các mô-đun khác nếu muốn. Hệ thống rất
linh hoạt.

Ngoài ra, một số chức năng được cài đặt tốt hơn bằng chính ngôn ngữ kịch bản,
như xử lý mẫu trang và quản lý phiên, vì vậy chúng tôi còn
cung cấp thêm các thư viện template.xo và webtools.xo để bạn tiện sử dụng.
Lý do của tất cả những điều này là chúng tôi không biết bạn muốn
sử dụng xoscript như thế nào. Bạn có thể dùng nó làm ngôn ngữ kịch bản phía máy chủ,
nhưng cũng có thể dùng cho giao diện đồ họa, thiết bị nhúng hoặc chỉ để xử lý theo lô.
Ngay cả khi bạn dùng nó làm ngôn ngữ kịch bản phía máy chủ (hiện là
một trong những trường hợp sử dụng chính), bạn vẫn có thể muốn
dùng một bộ máy mẫu trang khác hoặc một trình xử lý phiên khác.
Chúng tôi là ai mà quyết định rằng bạn phải dùng của chúng tôi?

Tuy vậy, một trong những ưu điểm của việc dùng bộ máy mẫu trang của chúng tôi là
bạn không phải học thêm cú pháp để tạo mẫu trang.
Bộ máy mẫu trang mặc định đi kèm xoscript tách biệt 100%
giữa phần trình bày và phần logic. Thay vì dùng cú pháp mẫu trang
đặc biệt, nó chỉ đơn giản sử dụng một hệ thống đánh dấu khe rất linh hoạt.
Để biết thêm thông tin, hãy xem chương Máy chủ.

Lưu ý rằng nếu bạn không muốn dùng bộ máy mẫu trang mặc định hoặc
webtools mặc định thì dĩ nhiên bạn phải tự cung cấp
phần thay thế của riêng mình.

Nếu bạn chạy máy chủ web trong chroot, jail hoặc một loại sandbox khác,
bạn cũng cần cài đặt các thư viện phụ thuộc của xo trong môi trường đó; bạn có thể
xem mình cần những thư viện nào bằng cách dùng ldd (xem trang man của Linux hoặc BSD).
Nếu bạn muốn dùng các lệnh shell trong kịch bản xo, hãy sao chép thêm một shell
(như bash hoặc ksh) vào môi trường này.

Chúng tôi cũng muốn lưu ý rằng chúng tôi rất coi trọng khả năng tương thích ngược.
Thậm chí còn có một tính năng tương thích ngược đặc biệt gọi là
'version'. Nói chung, chúng tôi hướng tới việc mã của bạn có thể chạy mãi mãi. Vì vậy, bạn sẽ
không bao giờ phải cập nhật mã để duy trì khả năng tương thích với các phiên bản mới hơn
của xoscript. Mục tiêu của chúng tôi là: viết một lần, chạy mãi mãi.

Phần còn lại của sổ tay này dành để giải thích chi tiết ngôn ngữ
lập trình xoscript. Lập trình kịch bản phía máy chủ được trình bày trong chương
có tên Máy chủ. Nếu bạn là một lập trình viên giàu kinh nghiệm, bạn có thể muốn
bỏ qua một vài chương vì một số chương hơi quá chi tiết hoặc
rất giống với các thực hành lập trình chung. Vì vậy, với những ai
đã có kinh nghiệm với nhiều ngôn ngữ lập trình khác,
tốt hơn hết là hãy xem sổ tay này như một tài liệu tham khảo.

## Cài đặt trên Linux

Tải về apache2 và mariadb:


```
sudo apt-get install apache2 mariadb-server
sudo a2enmod cgi
```

Tải về xoscript.
Hãy thay X bằng số phiên bản chính xác!

```
wget https://xoscript.com/downloads/xoserver-linux-1_5_X.tar.gz
tar xvf xoserver*.tar.gz
```

Sao chép các tệp vào thư mục gốc web và /bin:


```
sudo cp bin/xo /bin/xo
sudo cp -R bin/mods /var/www/html/
sudo cp *.xo /var/www/html/
```

Chỉnh sửa cấu hình apache2:

```
sudo nano /etc/apache2/sites-enabled/000-default.conf
```

Thay thế Virtualhost bằng:

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

Tạo một trang thử nghiệm:

```
sudo nano /var/www/html/test.xo
```

và viết một chương trình thử nghiệm nhỏ:

```
#!/bin/xo
Server khởi-tạo.
Chương-trình dùng: ['webtools.xo'].
>> trang-web := Tài-liệu-Web mới.
trang-web xuất: ['Hello World'].
```

Cho phép apache2 thực thi chương trình của bạn qua CGI:

```
sudo chmod uog+x /var/www/html/test.xo
```

Khởi động lại apache2:

```
sudo systemctl restart apache2
```

Mở trang thử nghiệm của bạn trong trình duyệt:

```
http://localhost/test.xo
```

Bạn sẽ thấy:

```
Hello World
```


## Cài đặt trên OpenBSD

Chỉnh sửa /etc/httpd.conf, thêm vào:


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

Nếu bạn muốn dùng SSL:

```
listen on * tls port 443
tls {
	certificate "/etc/ssl/mycert.crt"
	key "/etc/ssl/private/mykey.key"
}
```

Để bảo vệ quá trình trao đổi khóa trước máy tính lượng tử,
hãy chọn bộ mã hóa mlkem:

```
tls {
 ... 
 ecdhe "X25519MLKEM768"
 ...
}
```

Thêm tệp thực thi xo và các mod, cũng như mọi thư viện phụ thuộc vào
chroot (xác định bằng ldd).

## Chạy các ví dụ


Để chạy một trong các chương trình ví dụ trong gói:

```
./example.sh <name> <Linux/OBSD> [clean]
```

Ví dụ, để chạy ví dụ FizzBuzz trên Linux:

```
./example.sh fizzbuzz Linux
```

Để chạy cùng ví dụ đó trên OpenBSD:

```
./example.sh fizzbuzz OBSD
```

Để chạy ví dụ với một bản dựng sạch:

```
./example.sh fizzbuzz OBSD clean
```

## Kiểm thử đơn vị

Để chạy các bài kiểm thử đơn vị:

```
./runtests.sh
```

Để chạy kiểm thử đơn vị mà không cần dựng (chỉ kiểm thử):

```
./runtests.sh nobuild
```

## Biên dịch

Để biên dịch từ mã nguồn trên Linux:

```
make clean
ISO="en" make
```

Trên OpenBSD:

```
make -f makefile.obsd clean
ISO="en" make -f makefile.obsd
```

Để biên dịch plugin máy chủ trên Linux:

```
PACKAGE="server" NAME="server.so" make plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make plugin
```

Để biên dịch plugin máy chủ trên OpenBSD:

```
PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin-clean
ISO="en" PACKAGE="server" NAME="server.so" make -f makefile.obsd plugin
```

## Xin chào thế giới

Sau khi tệp đã được chuyển về máy tính, bạn có thể giải nén tệp
và khởi động xo bằng lệnh sau:

```
xo
```

Để chạy một chương trình XOScript, hãy lưu chương trình thành một tệp có thêm hậu tố
-xo (không bắt buộc). Ngoài ra, hãy chèn tên tệp chương trình của bạn
sau lệnh XOScript:

```
xo myprogram.xo
```

Khi bạn chạy lệnh XOScript với tệp chương trình của mình làm
tham số, xo sẽ đọc và thực thi tệp chương trình đó.

{{note}}
Bạn cũng có thể khởi động chương trình bằng cách kéo nó vào biểu tượng xo.
{{/note}}

{{warning}}
Trên một số hệ thống, bạn cần cấp trước cho xo quyền tải các thư viện
động.
{{/warning}}

Theo truyền thống, chương trình đầu tiên trong bất kỳ ngôn ngữ lập trình
mới nào cũng phải là một lời chào gửi đến thế giới. Trong XOScript, một chương trình
**Hello world** như vậy trông như sau:

@test598

Khi văn bản này được lưu vào một tệp, ví dụ hello.xo, nó có thể được thực thi như
sau: .

xo hello.xo

Hello world


Bạn có thể thấy kết quả của chương trình trong cửa sổ đen ở trên.
Xuyên suốt sổ tay này, cách trình bày tương tự sẽ được dùng để hiển thị
kết quả.

{{note}}
Xuất được viết với chữ X viết hoa.
Nói chung, tên đối tượng bắt đầu bằng chữ cái viết hoa
trừ khi nó đóng vai trò một thể hiện (không có phương thức
riêng, chỉ có dữ liệu). Điều này phản ánh quy ước lớp và thể hiện
trong các ngôn ngữ lập trình khác.
{{/note}}


## Cú pháp 

XOScript là một ngôn ngữ lập trình *hướng đối tượng* *thuần túy*. Điều này có nghĩa
là xoscript coi mọi thứ đều là đối tượng, do đó không có
*kiểu dữ liệu* nào khác. Về cơ bản, có ba hành động thường gặp
trong một chương trình viết bằng XOScript: *gán*, *gửi thông điệp*
và *trả lời*. Trao đổi thông điệp giữa các đối tượng là phần cốt lõi của
một chương trình XOScript. Ba hành động riêng lẻ này được minh họa
dưới đây:


Hành động            | Ví dụ
-------------------- | --------
gán                  |  \>\> x := 1. 
thông điệp đơn nguyên | x even?.
thông điệp nhị phân   | 1 + 2.
thông điệp từ khóa    | x from: 0 length: 10.
trả lời              | <- answer.  


Chương này sẽ mang đến cho bạn một cái nhìn tổng quan về ngôn ngữ XOScript
và mô tả các nguyên tắc cơ bản của nó. XOScript là một ngôn ngữ nhỏ,
được xây dựng trên ba hành động (xem minh họa), tương ứng với
khoảng sáu quy tắc ngữ pháp. Chỉ cần như vậy là đủ để làm chủ
ngôn ngữ này.

Đừng lo nếu mọi thứ chưa rõ ràng ngay với bạn: tất cả các viên gạch
nền tảng sẽ được khám phá trong chương tiếp theo (3) và các quy tắc cơ bản sẽ
được nhắc lại. Tuy nhiên, chương hiện tại chủ yếu đóng vai trò giới thiệu chung
về ngôn ngữ. Các nguyên tắc cơ bản sẽ được giải thích ngắn gọn
và minh họa bằng một số ví dụ liên quan. Những chi tiết còn thiếu
sẽ được trình bày sau.

Chú thích trong XOScript bắt đầu bằng ký hiệu \#. Vì vậy, dòng sau
sẽ bị bỏ qua:

```
# đây chỉ là một chú thích
```

## Biến

Để gán
một biến, bạn dùng ký hiệu khai báo biến: >>. Tên của một
biến có thể chứa mọi ký tự ngoại trừ: <-, :=, khoảng trắng,
dấu chấm, dấu phẩy, dấu hai chấm, dấu nháy [' '] và dấu ngoặc đơn ().
Hơn nữa, một biến không thể trải dài trên nhiều dòng. Xin lưu ý
rằng tên biến không thể bắt đầu bằng chữ số hoặc dấu trừ.

Đây là các ví dụ về biến hợp lệ:

```
>> password := ['Secret'].
>> ♡♡♡ := 3.
>> $ := ['đô la'].
>> +plus := Đúng.
>> mật-mã-người-dùng := ['Suỵt!'].
```

Các biến không hợp lệ chẳng hạn như:


```
>> -123 := ['số âm'].
>> password of người-dùng := ['Tối mật'].
>> password.of:người-dùng := ['Tối mật'].
>> ,x := 10.
```

{{note}}
Bạn không cần thoát bất kỳ ký tự nào
(kể cả dấu nháy đơn, dấu nháy kép, ký hiệu
giới hạn chuỗi) trong
một chuỗi literal, miễn là nó không
gây nhập nhằng cho bộ phân tích từ vựng.
{{/note}}

Sau khi một biến đã được khai báo, nó có thể được sử dụng tự do. Điều này có nghĩa
là chỉ cần dùng ký hiệu khai báo ở lần đầu tiên
bạn dùng biến (lần khai báo).

Cụ thể hơn, bạn không thể tùy ý bắt đầu gán một giá trị cho
biến của mình *(x := 2)*, vì trước tiên bạn phải khai báo biến *(\>\>
x := 2)*. Tuy nhiên, khi đã khai báo, bạn được phép thay đổi giá trị của nó
mà không cần dùng ký hiệu khai báo*(\>\> x := 2. x := 3.)*.

Lưu ý rằng bắt buộc phải gán giá trị cho biến tại thời điểm
khai báo. Khác với các ngôn ngữ lập trình khác, bạn không được phép
khai báo một biến mà không có giá trị. Điều cốt yếu là phải gắn tường minh
mỗi biến với một giá trị ban đầu. Tuy nhiên, bạn hoàn toàn có thể khởi tạo
biến bằng đối tượng **Rỗng**. Khi đó, biến có thể được
xem là trống *(\>\> x := None.)*. Tóm lại, khai báo một
biến mà không có giá trị ban đầu là không được phép. Vì vậy,

```
>> x.
```

là không hợp lệ và sẽ gây ra thông báo lỗi.

{{note}}
xoscript sử dụng phạm vi động cho biến; để biết
chi tiết, hãy tham khảo chương Hàm.
{{/note}}


## Literal

XOScript coi mọi thứ đều là đối tượng; tức là tất cả các số, chuỗi
và đoạn mã. Các số như 1, 2, 100, -999 và 1,234 là
các đối tượng Số. Mọi văn bản nằm giữa hai dấu nháy đơn là các đối tượng
Chuỗi. Mọi đoạn mã được nhóm trong dấu ngoặc nhọn {...} là các đối tượng
Hàm.

Literal         | Đối tượng gốc | Ví dụ
--------------- | ------------- | ----------
số              | Số            | 1,2,3... 
chuỗi           | Chuỗi         | \['hello'\]
hàm             | Hàm           | { 1 + 2. }.
                
     
Các đối tượng như số và chuỗi luôn có nguồn gốc từ một đối tượng
gốc. Ví dụ, tất cả các số đều bắt nguồn từ đối tượng **Số**. Tất cả
các chuỗi bắt nguồn từ **Chuỗi** và tất cả các đoạn mã từ **Hàm**. Đến
lượt mình, tất cả các đối tượng này đều bắt nguồn từ **Đối-tượng**, mà thực chất là
đối tượng gốc của mọi đối tượng.


## Thông điệp

Lập trình trong XOScript về cơ bản là
gửi thông điệp đến các đối tượng. Cách viết chung để gửi một thông điệp đến
một đối tượng như sau:

```
<object> <message>
```

Chẳng hạn, để kiểm tra xem số **2** có phải là số chẵn hay không,
thông điệp **chẵn?** được gửi đến đối tượng **2**:

```
2 chẵn?
```

Câu trả lời sẽ là **Đúng** (lại là một đối tượng). Các thông điệp không xác định
thường bị các đối tượng bỏ qua; vì vậy sẽ không có lỗi xảy ra. Một số đối tượng (ví dụ:
số hoặc chuỗi) phản hồi thông điệp không xác định theo một cách định sẵn
(sẽ nói thêm về chủ đề này sau).

Một đối tượng có thể nhận ba loại thông điệp. 

Loại            | Số lượng đối số
--------------- | -------------------
Đơn nguyên      | 0      
Nhị phân        | 1     
Từ khóa         | 1+    


Thứ nhất, có các **thông điệp
đơn nguyên**, xem ví dụ ở trên, là các thông điệp không có đối số. Thứ hai,
có các **thông điệp từ khóa**, có một hoặc nhiều đối số,
ví dụ:

```
>> x := Số giữa: 1 và: 10.
```

Trong trường hợp này, thông điệp **giữa:và:** được gửi đến **Số**, là
đối tượng gốc của mọi số. Kết quả sẽ là một số ngẫu nhiên
từ 1 đến 10. Cuối cùng, có các **thông điệp nhị phân**, chỉ có
một ký tự và một đối số:

```
2 + 3
```

Trông giống như một phép cộng toán học, nhưng thực ra đó chỉ là một thông điệp khác.
Thông điệp **+** được gửi đến **2**, với đối số **3**, và sẽ trả về
câu trả lời **5**. Thông điệp nhị phân được phép viết mà không có dấu hai chấm.

Các thông điệp nhị phân có thể được nối chuỗi:

```
>> x := 3 + 2 - 1.
```

Trong đoạn mã này, **+ 2** trước tiên được gửi đến đối tượng **Số** **3**,
cho ra đối tượng Số **5**, sau đó **-1** được gửi đến số
này. Những độc giả tinh ý sẽ nhận ra sự khác biệt mà
giao thức này thể hiện so với thứ tự ưu tiên toán tử toán học thông thường.
XOScript bỏ qua thứ tự toán học để ưu tiên
tính nhất quán trong hệ thống thông điệp của nó. Kết quả là phép tính:

```
2 + 3 * 5 = 25
```

chứ không phải 17.

Điều này là có chủ ý. Có thể dùng dấu ngoặc đơn để thay đổi thứ tự thực hiện:

```
2 + (3 * 5) = 17
```

Hầu hết các đối tượng trả về chính chúng làm kết quả khi phản hồi một
thông điệp nào đó. Điều này rất hữu ích vì nó khuyến khích tiếp tục đối thoại với
đối tượng đó bằng cách gửi cho nó một thông điệp tiếp theo:

```
Xuất ghi:
[' xin chào '] cắt-khoảng-trắng chữ-hoa.
```

```
XIN CHàO
```

Ở đây, hai thông điệp được gửi đến đối tượng **Chuỗi**: **cắt-khoảng-trắng**, tiếp theo
là **chữ-hoa**.

Trong đoạn mã sau, cần dùng dấu phẩy để chỉ ra
rằng một thông điệp mới sắp đến. Nếu không, XOScript sẽ bị nhầm lẫn.

```
Xuất ghi: ['Hello!'], xuống-dòng.
```

Trước tiên, thông điệp **ghi:** được gửi đến biểu tượng bút chì, tiếp theo là
**xuống-dòng**. Nếu không có dấu phẩy, XOScript sẽ nghĩ rằng bạn muốn gửi
**xuống-dòng** đến **chuỗi** **Hello!**, một việc vô ích.

Thứ tự xử lý các thông điệp như sau: từ trái sang phải;
bắt đầu với các thông điệp trong dấu ngoặc đơn, tiếp đến là các thông điệp đơn nguyên. Sau đó
là các thông điệp nhị phân và cuối cùng là các thông điệp từ khóa. Xem ví dụ
dưới đây:

```
Xuất ghi: 0.5 làm-tròn + (2 - 1), xuống-dòng.
```

XOScript luôn đọc từ trái sang phải: trước tiên, thông điệp **ghi:**
được gửi đến Xuất và tiếp theo là thông điệp **xuống-dòng**. Bên trong
chính đối số, XOScript cũng đọc từ trái sang phải, nên **0.5 làm-tròn**
rồi đến **+**.

{{note}}
Thông điệp xuống-dòng thêm một ký tự xuống dòng vào chuỗi.
Tên tiếng Anh của thông điệp này (stop) lấy cảm hứng từ hệ thống điện báo.
Các bức điện trong hệ thống điện báo
thường dùng từ STOP để đánh dấu kết thúc một câu
(vì dấu câu không đáng tin cậy hoặc tốn kém).
{{/note}}

Hơn nữa, **làm-tròn** được ưu tiên hơn **+**, vì nó là một
**thông điệp đơn nguyên**. Do có dấu ngoặc đơn, **2 - 1** được tính
trước, sau đó **1** được cộng vào kết quả của **0.5 làm-tròn** (1).

Toàn bộ quá trình sẽ cho kết quả **2**, cũng chính là câu trả lời
được ghi ra. Sau dấu phẩy là thông điệp xuống-dòng, đưa con trỏ
xuống một dòng mới. Tất nhiên, cách tốt nhất để hiểu đầy đủ thứ tự
thực hiện của các chương trình XOScript là thực hành.

Cần lưu ý rằng trong XOScript, khác với nhiều ngôn ngữ lập trình
khác, khoảng trắng là một phần cơ bản của cú pháp. Đặc
biệt khi nói đến thông điệp nhị phân, khoảng trắng có thể gây ra một số
nhầm lẫn. Luôn dùng một khoảng trắng sau thông điệp nhị phân. Bạn không thể
gắn trực tiếp một số vào thông điệp, ví dụ: 

```
3 + 2
```

khác với 

```
3 +2
```

Ví dụ đầu tiên (**3 + 2**) gửi
thông điệp **+** đến số **3**, với đối số là số **2**. Kết
quả trong trường hợp này sẽ là **5**. Trong ví dụ thứ hai (**3 +2**),
thông điệp đơn nguyên **+2** được gửi đến số **3**. Tùy vào
ngữ cảnh, điều đó có thể cho ra một kết quả rất khác.

## Phương thức không tồn tại

Gửi một thông điệp đến một đối tượng sẽ gọi hàm đã được
gắn vào đối tượng đó dưới tên thông điệp ấy. Nếu bạn gửi một thông điệp
không được hiểu, đối tượng nhận sẽ bỏ qua thông điệp của bạn
và thay vào đó trả về một tham chiếu đến chính nó để tiếp tục giao tiếp.
Điều này được gọi là truyền thông điệp khoan dung.

Ví dụ:

```
Xuất ghi: Đối-tượng blah, xuống-dòng.
```

Điều này sẽ không gây ra lỗi. Nó chỉ đơn giản in ra văn bản **Đối-tượng**.


## Luồng điều khiển

Trong XOScript, không cần các quy tắc ngữ pháp riêng cho *vòng lặp* và
*câu lệnh if*. Một câu lệnh if chỉ đơn giản là một thông điệp **đúng:** hoặc **sai:**
gửi đến một đối tượng **Đúng** hoặc một đối tượng **Sai**:

```
2 chẵn? đúng: {
	Xuất ghi: ['Hai là số chẵn'], xuống-dòng.
}.
```
Trong ví dụ trên, thông điệp **đúng:** được gửi đến **Đúng** (câu
trả lời cho câu hỏi: 2 có phải là số chẵn không?). Kèm theo làm đối số là một
đoạn mã bổ sung: một đối tượng **Hàm**. Hàm này ghi lên
màn hình rằng 2 quả thực là một số chẵn.

Cũng không cần các quy tắc viết riêng cho *vòng lặp*. Để
thực thi một đoạn mã ba lần, chỉ cần gửi **\*** với đối số
**3** đến **Hàm** đó:

@test5

Trong đoạn mã này, **i** là chỉ số. Vì vậy, lần đầu tiên Hàm
được thực thi, **i** bằng 0, lần thực thi tiếp theo, **i** = 1 và
cứ thế tiếp tục.

Hãy xem xét một ví dụ khác. Khi cần in một bảng chuyển đổi
từ *kJ* (kilojoule) sang *kcal* (kilocalorie) theo bước 100,
xem cách viết đúng dưới đây:

@test599

Ở đây, số thứ tự của dòng hiện tại được truyền vào tham số
**:line**. Ở đầu một hàm, các tham số của hàm được
định nghĩa. Các tham số không được dùng sẽ để trống (**Rỗng**). Tham số luôn
được đặt ở đầu hàm, ngay sau dấu ngoặc nhọn mở
và có dấu hai chấm đứng trước.

Thông điệp **trong-khi:** là sự kết hợp giữa *vòng lặp* và *điều kiện*.
Hai hàm có thể được liên kết bằng thông điệp **trong-khi:**. Hàm nhận
sẽ tiếp tục chạy cho đến khi hàm sau dấu hai chấm cho kết quả
phủ định. Ví dụ:

@test600

Trong đoạn mã minh họa ở trên, **1** được cộng vào **x** chừng nào
**x** còn nhỏ hơn **5**. Khi điều này không còn đúng nữa, hàm
thứ hai sẽ trả lời **Sai**, do đó việc thực thi
hàm thứ nhất sẽ kết thúc. Lưu ý rằng **x** được định nghĩa bên ngoài
hàm và là một biến toàn cục. Để tìm hiểu thêm về quy tắc phạm vi,
hãy tham khảo chương về Hàm.

## Nội suy chuỗi

Danh sách *kJ/kcal* có thể được trình bày
đẹp hơn. Tốt nhất, danh sách sẽ trông như sau:

```
100 kj ➞ 23.88 kcal

200 kj ➞ 47.76 kcal
```

Khi bạn chuyển kết quả mong muốn thành một mẫu, cách viết của nó
có thể là:

```
number1 kJ ➞ number2 kcal
```

Điều này có nghĩa là **number1** đại diện cho giá trị kJ và **number2** cho
giá trị kcal. Đây là cách nội suy chuỗi hoạt động trong XOScript. Không
cần quy tắc ngữ pháp riêng nào cho việc này trong XOScript. Chỉ cần gửi
từ cần được thay thế đến văn bản, với văn bản thay thế làm
đối số:

```
>> text :=

['number1 kJ ➞ number2 kcal']

number1: 100,

number2: 23.9.
```

Kết quả:

```
100 kj ➞ 23.9 kcal
```

Quy tắc thay thế này áp dụng cho mọi thông điệp không được định nghĩa mà
một đối tượng **chuỗi** nhận được. Mỗi thông điệp không được đối tượng
**chuỗi** nhận diện sẽ được hiểu như sau: *thay văn bản của thông điệp
bằng văn bản trong đối số của thông điệp.* Bạn có thể điều chỉnh
chương trình như sau:


@test601


Để tránh nhầm lẫn về việc thông điệp nào có thể hoặc không thể được dùng làm
từ thay thế, tốt nhất nên đưa vào một dấu đánh dấu mẫu như &lt; &gt;
cho các đoạn văn bản trong mẫu cần
được thay thế.

## Giá trị trả về

Để trả lời một thông điệp, mũi tên trả về
(*<-*) được sử dụng. Ví dụ sau minh họa cách tạo một tác vụ
để tính phần trăm:

@test602

Sau khi tác vụ được định nghĩa và gán cho biến **percentage**,
thông điệp **áp-dụng:và:** được gửi với các đối số **100** và **7**.

Điều này sẽ thực thi tác vụ áp dụng cho **100** và **7**, tức là 7% của 100.
Nhờ mũi tên trả về, câu trả lời được trả từ tác vụ về
chương trình chính.

## Mở rộng

Mặc dù đoạn mã này hợp lệ, nó có một nhược điểm
là phải nhớ thứ tự của các đối số. Vậy tại sao không
viết như thế này: *7 percent of: 100 *? Trông sẽ *tự nhiên* hơn
nhiều. Để làm được điều này, chúng ta phải điều chỉnh đối tượng cha của
**7**, tức là đối tượng **Số**, để nó hiểu được
thông điệp **percent of:**. Điều này có thể thực hiện bằng cách gửi **khi:làm:** đến
đối tượng Số, như sau:

@test603

Vì phần trăm trong trường hợp này chính là bản thân con số, chúng ta tham chiếu đến bản-thân,
từ khóa *bản-thân*. Tóm lại, ký hiệu bản-thân có nghĩa là: *gửi thông điệp
này đến chính-mình*.

# Đối tượng

{{messages}}

Ngoài việc điều chỉnh và mở rộng các đối tượng có sẵn, bạn cũng có thể tự tạo
các đối tượng mới chỉ bằng cách gửi thông điệp **mới**. Giả sử bạn
muốn tạo một đối tượng hóa đơn đảm bảo thứ tự đánh số
liên tục; khi đó, trước tiên bạn cần một đối tượng hóa đơn.

Biết rằng mỗi đối tượng đều bắt nguồn từ một đối tượng khác, và đối tượng đó
cuối cùng lại bắt nguồn từ đối tượng gốc của mọi đối tượng có tên là Đối-tượng,
bạn cần chọn xem đối tượng mới của mình sẽ được xây dựng dựa trên
đối tượng nào trong số đó. Đối tượng mới của bạn kế thừa mọi thuộc tính của
đối tượng mà nó được xây dựng dựa trên, tức là đối tượng mà thông điệp **mới**
ban đầu được gửi đến.

Trong ví dụ này, một đối tượng khá trung tính được ưu tiên, tức là một đối tượng không có quá
nhiều thuộc tính kế thừa. Việc lựa chọn khá dễ dàng, vì trong trường hợp đó
đối tượng mới có thể dựa trên chính đối tượng gốc, tức là
**Đối-tượng**. Cách viết của hệ thống hóa đơn dự kiến sẽ như
sau:

@test604

Số hóa đơn hiện tại được lưu trong đối tượng, đó là lý do có
từ khóa **riêng** đặt phía trước nó. Đây được gọi là một *thuộc tính*;
chi tiết sẽ được trình bày sau.

Một số doanh nghiệp muốn đưa năm vào số hóa đơn.
Trong trường hợp này, bạn có thể tạo một đối tượng hóa đơn mới dựa trên
một đối tượng hóa đơn trước đó, nhưng cho phép người dùng
nhập một năm cụ thể:

@test605

Không cần viết lại phần cài đặt cho thông điệp **số**,
vì nó được kế thừa từ **đối tượng hóa đơn** đã viết trước đó;
do đó, mã cũ có thể được tái sử dụng. XOScript không có các khái niệm
như lớp và các khái niệm liên quan khác. Điều này có nghĩa là các đối tượng chỉ có thể
kế thừa từ các đối tượng khác, còn được gọi là *kế thừa
nguyên mẫu*.

Bây giờ, hãy quay lại với thuộc tính. Thuộc tính của đối tượng chỉ có thể được truy cập
từ *bên trong hệ thống phân cấp của đối tượng*, vì vậy các thuộc tính này
không thể được các đối tượng khác nhìn thấy.

Khác với các ngôn ngữ lập trình khác, mọi thuộc tính của đối tượng
chỉ hiển thị với đối tượng đã tạo ra thuộc tính đó và với
các đối tượng dẫn xuất. 

Một kỹ thuật thường dùng là sử dụng một đối tượng như một loại *bản thiết kế*,
chẳng hạn như trường hợp các hóa đơn đã nói ở trên.
Một ví dụ hay khác là **Point**. Giả sử bạn tạo một
chương trình máy tính thực hiện các phép tính dựa trên các điểm trên bản đồ. Bạn
có thể xây dựng đối tượng **Point** chứa các thuộc tính
tọa độ x và tọa độ y, được cung cấp cho
thế giới bên ngoài thông qua các thông điệp:

@test606

Thông điệp **=** so sánh hai điểm bằng thông điệp **và:**.
Phép so sánh đầu tiên cho kết quả **Đúng** hoặc **Sai**. Đây là các đối tượng
lôgic. Khi bạn gửi thông điệp **và:** đến một đối tượng Đúng, và
đối tượng đối số sau dấu hai chấm cũng là **Đúng**, bạn sẽ
nhận lại câu trả lời **Đúng**. Khi một trong hai là **Sai**, bạn sẽ
nhận được câu trả lời **Sai**. Lưu ý rằng một điểm không thể đọc tọa độ của
điểm kia. Cần phải gửi một thông điệp đến điểm kia để yêu cầu
dữ liệu này: **x-coordinate** và **y-coordinate**. Suy cho cùng, như đã
giải thích, các thuộc tính chỉ có thể được truy xuất từ bên trong
chính họ đối tượng đó. 

Lưu ý rằng thông điệp **=** được dùng ở đây để thực hiện việc so sánh
điểm. Cũng có thể dùng một thông điệp khác, chẳng hạn như
**is:** hoặc **equal:**, tuy nhiên việc tái sử dụng ký tự **=** có vẻ
phù hợp trong trường hợp này.

## Kế thừa

Bạn có thể tái sử dụng mã đã viết trước đó để tạo một hệ thống phân cấp
các đối tượng. Ví dụ:

```
>> Động-vật := Đối-tượng mới.
>> Chó := Động-vật mới.
>> Chó-xù := Chó mới.
```

Trong trường hợp này, **Dog** kế thừa toàn bộ hành vi và thuộc tính
của **Animal**, và đến lượt mình, đối tượng **Animal** kế thừa toàn bộ hành vi của
**Đối-tượng**, đối tượng gốc của mọi đối tượng.


## Ghi đè


Trong ví dụ sau, một loại danh sách mới được tạo ra:
**Combination**, trong đó mỗi phần tử được đảm bảo là duy nhất. Các
chức năng của danh sách được tái sử dụng thông qua kế thừa:

@test607

Hãy để ý cách **red** thứ hai bị loại khỏi danh sách.

Đôi khi, có thể cần ghi đè một hành vi của một đối tượng.
Chẳng hạn, khi cộng các số mà phải tính đến
đơn vị đo lường. Trong ví dụ sau, đối tượng **Size** được
tạo ra. Đối tượng này trả về một số mà trong phép cộng sẽ
tính đến đơn vị của số được cộng vào. Đối tượng **Số**
kiểm tra xem đó là *inch* hay *foot*. Mã chương trình
có thể trông như sau:

@test608

## Đệ quy

Trong ví dụ trước, **dấu** cộng đã bị ghi đè. Lưu ý
rằng cuối cùng phép cộng thực sự vẫn phải được thực hiện, và việc này
diễn ra ở dòng sau:

```
>> câu-trả-lời := bản-thân + (số x hệ-số).
```

Vậy làm thế nào XOScript hiểu rằng **dấu** cộng này chỉ đến
logic cộng ban đầu?** Chẳng hạn, một cách hiểu khác
có thể là XOScript sẽ liên tục gửi cùng một thông điệp đến cùng một
đối tượng, và điều đó sẽ dẫn đến một **vòng lặp vô tận**. Rõ ràng,
đó không phải là ý định. Ngay khi bạn gửi một thông điệp đến một đối tượng
mà sẽ thực thi chính xác cùng một đoạn mã, XOScript sẽ nhận ra
rằng trong trường hợp này, thông điệp nền bên dưới đã bị ghi đè mới là thứ được nhắm đến. Vì vậy,
chương trình của bạn sẽ tự động được bảo vệ khỏi dạng vòng lặp vô tận
này. Tuy nhiên, khi bạn thực sự muốn chạy cùng một hàm từ
hàm hiện tại, trước tiên cần gửi thông điệp
**đệ-quy**. Trong trường hợp này, kết quả sẽ là một vòng lặp
vô hạn. Tuy nhiên, có những ứng dụng hữu ích cho các tác vụ đệ quy,
chẳng hạn giả sử bạn muốn tính giai thừa của một số
cho trước. Khi đó, chỉ cần thêm thông điệp **factorial** vào
Số:

@test609

Điều này đòi hỏi đệ quy. Thực tế, tác vụ gắn với
thông điệp **factorial** cần được thực thi lại bên trong chính hàm đó.
Vì vậy, cần gọi hàm giai thừa từ bên trong
chính hàm giai thừa. Theo quy tắc, XOScript sẽ ngăn chặn thao tác này,
vì nguy cơ rơi vào vòng lặp vô hạn. Vì lý do này,
điều thiết yếu là phải đặt từ **đệ-quy** trước thông điệp. Việc này
được thực hiện để XOScript biết rằng bạn
có ý định thực thi cùng một tác vụ, và bạn không mắc lỗi.

## Đối tượng giống lớp

Mặc dù xoscript không cung cấp lớp, việc mô phỏng hành vi
giống lớp rất đơn giản. Chỉ cần ghi đè thông điệp mới.

```
>> Động-vật := Đối-tượng mới.
Động-vật khi: ['mới'] làm: {
	<- bản-thân mới khởi-tạo.
}.

Động-vật khi: ['khởi-tạo'] làm: {
	riêng âm-thanh := ['?'].
	riêng số-chân  := 4.
}.
```

Trong đoạn mã trên, chúng ta tạo một đối tượng có tên Animal.
Đối tượng này đóng vai trò *bản thiết kế* cho mọi loại động vật
như chó và mèo. Đối tượng cha Animal được viết
với chữ A viết hoa để biểu thị rằng đây là một đối tượng giống lớp.
Tiếp theo, chúng ta ghi đè thông điệp mới bằng cách viết phương thức mới của riêng mình.
Trong trường hợp này, nó gửi thông điệp mới đến bản-thân, tiếp theo là thông điệp
khởi-tạo. Vì xoscript chặn đệ quy theo mặc định nên điều này sẽ không gây ra
vòng lặp vô hạn. Thay vào đó, nó sẽ gửi thông điệp mới đến đối tượng
cha (Đối-tượng), tạo ra một thể hiện mới của Animal. Như vậy, chúng ta tạo
một đối tượng mới, dựa trên chính đối tượng mà chúng ta đã viết phương thức mới cho nó.
Điều này hoàn toàn hợp lệ. Bây giờ chúng ta cũng gửi thông điệp khởi-tạo, điều này đảm bảo
rằng đối tượng Animal có các giá trị mặc định cho các thuộc tính của nó. Theo mặc định,
một con vật có 4 chân và tiếng kêu chưa xác định (do đó có dấu chấm hỏi).
Để tạo một thể hiện mới của Animal, chúng ta chỉ cần viết:

```
>> a := Động-vật mới.
```

Bây giờ chúng ta có một thể hiện mới của Animal với 4 chân, tiếng kêu chưa xác định và
một phương thức khởi-tạo. Giống như trong các ngôn ngữ OOP khác, chúng ta cũng có thể
mở rộng Animal:

```
>> Chó := Động-vật mới.
Chó khi: ['khởi-tạo'] làm: {
	bản-thân khởi-tạo.
	riêng âm-thanh := ['sủa'].
}.
```

Chúng ta có thể kiểm tra điều này dễ dàng bằng cách thêm một phương thức chuỗi:

```
Động-vật khi: ['chuỗi'] làm: {
	<- riêng số-chân chuỗi + riêng âm-thanh.
}.
```

Hãy ghép tất cả lại với nhau:

@test13


Việc tạo một đối tượng ở một trạng thái ban đầu cho trước là một
vấn đề thường gặp. Giả sử cần tạo một đối tượng **Rectangle**
để tính chu vi và diện tích. Một cách viết có thể là:


```
>> Hình-chữ-nhật := Đối-tượng mới.

Hình-chữ-nhật khi: ['diện-tích'] làm: {
	<- riêng độ-dài * riêng chiều-rộng.
}.
```

Hiển nhiên, việc thiết lập chiều dài và chiều rộng là điều kiện tiên quyết. Vì
mục đích đó, có thể thêm các thông điệp **độ-dài:** và **width:**:


```
Hình-chữ-nhật khi: ['length:'] làm: { :độ-dài
	riêng độ-dài := độ-dài.
}.

Hình-chữ-nhật khi: ['width:'] làm: { :chiều-rộng
	riêng chiều-rộng := chiều-rộng.
}.

```

Hình chữ nhật này sau đó có thể được sử dụng như sau:


```
>> hình-chữ-nhật := Hình-chữ-nhật mới length: 2, width: 3.
Xuất ghi: hình-chữ-nhật diện-tích.
```

Tuy nhiên, nếu quên thiết lập ban đầu cho chiều dài và chiều rộng,
một thông báo lỗi sẽ xuất hiện:

```
>> hình-chữ-nhật := Hình-chữ-nhật mới.
Xuất ghi: hình-chữ-nhật diện-tích.
```

sẽ gây ra lỗi sau:

```
Không tìm thấy khóa:độ-dài
```

Để ngăn chặn điều này, tốt hơn là một hình chữ nhật luôn
có chiều dài và chiều rộng ban đầu, chẳng hạn là 0. Vì vậy, trong
trường hợp này, cần **ghi đè** thông điệp **mới**.

@test610

Khi ghi đè thông điệp mới, về cơ bản chúng ta đang mô phỏng một **lớp**.

Thế giới XOScript chứa đầy những đối tượng đa dạng,
sẵn có cho chương trình của bạn ngay từ đầu. Trong các chương tiếp theo,
tất cả các đối tượng lõi này sẽ được trình bày.

## Ảnh chụp trạng thái

Bạn có thể lưu một đối tượng (cùng với trạng thái hiện tại của nó) xuống đĩa bằng:

```
đối-tượng-của-tôi save-as: ['saved.bin'].
```

Để tải lại đối tượng từ đĩa:

```
>> đối-tượng-của-tôi := Đối-tượng load-from: ['saved.bin'].
```

Ảnh chụp trạng thái có thể được dùng để lưu một trạng thái nhất định hoặc để cải thiện hiệu năng.
Việc tải một ảnh chụp trạng thái giúp tránh được phân tích từ vựng, phân tích cú pháp và thiết lập ứng dụng.
Ngoài ra, trong tương lai, ảnh chụp trạng thái có thể mang lại thêm các lợi ích về hiệu năng,
như tối ưu hóa một số mẫu nhất định hoặc phát hiện và
tối ưu hóa các đường dẫn nóng.

{{warning}}
Ảnh chụp trạng thái là một tính năng thử nghiệm, đừng dùng nó trong môi trường sản xuất.
Để kích hoạt các tính năng thử nghiệm, hãy biên dịch với -D EXPERIMENTS.
{{/warning}}


@test712

# Đối tượng Rỗng

{{messages}}

Đối tượng Rỗng
đại diện cho sự trống rỗng, hay chính xác hơn, sự vắng mặt của thông tin. Đôi
khi, bạn sẽ nhận được đối tượng này làm câu trả lời cho một thông điệp, trong
trường hợp kết quả là **không có gì**. Câu hỏi quan trọng nhất
mà bạn có thể hỏi đối tượng **Rỗng** là: **Rỗng?**. Câu
trả lời sẽ luôn là **Đúng**.

```
Xuất ghi: Rỗng Rỗng?.
```

kết quả:

```
Đúng
```

Mọi đối tượng khác ngoài **Rỗng** sẽ trả lời **Sai**. Đoạn mã
trên có vẻ hơi triết lý, nhưng đối tượng **Rỗng**
chắc chắn có những ứng dụng vô cùng thực tế. Ví dụ, bạn
sẽ nhận được đối tượng Rỗng làm câu trả lời khi bạn yêu cầu một
phần tử danh sách không tồn tại. Bạn cũng có thể dùng đối tượng Rỗng
khi muốn khai báo một biến nhưng chưa muốn chỉ định giá trị
cho nó. Thay vào đó, bạn chỉ cần **gán** giá trị đặc biệt **Rỗng**. Trong
XOScript, không được phép khai báo một biến mà không có giá trị, chẳng hạn như:


```
>> giá-trị.
```

Thay vào đó, bạn phải viết như sau:

```
>> giá-trị := Rỗng.
```

@api_None_base

# Giá trị lôgic

{{messages}}

Khác với hầu hết các ngôn ngữ lập trình phổ biến tại thời điểm viết tài liệu này,
XOScript chỉ cung cấp duy nhất một đối tượng Đúng và duy nhất một đối tượng
Sai. Nói rõ hơn, mỗi lần bạn viết **Đúng**, điều đó không có nghĩa là
một đối tượng mới đã được tạo ra. Thay vào đó, bạn luôn dùng một tham chiếu. Điều này
có nghĩa là khi bạn viết như sau:

\>\> x := Đúng.

thì **x** tham chiếu đến đối tượng **Đúng**. Mã điều kiện và vòng lặp cũng
kiểm tra tham chiếu này. Trong XOScript, ý nghĩa của **Đúng** và **Sai**
không cố định. Thực tế, một chương trình XOScript sẽ bị đảo lộn khá nhiều bởi một
câu lệnh như thế này:

Đúng := Sai.

Kết quả của những hành động như vậy là không xác định, tuy nhiên đó vẫn là một hành động
hợp lệ và do đó được cho phép về mặt hình thức. Ngoài ra, còn có một đối tượng
Lôgic, là đối tượng gốc của cả **Đúng** và **Sai**, vì cả hai
đều là dẫn xuất của đối tượng gốc này. Tuy nhiên, bản thân đối tượng Lôgic
không có ứng dụng thực tế nào.

## Những điểm dễ nhầm lẫn

Hãy cẩn thận khi dùng **và:** và **hoặc:**

```
Xuất ghi: (Sai or: Đúng or: Đúng), xuống-dòng.
Xuất ghi: (Sai hoặc: Đúng, hoặc: Đúng), xuống-dòng.
```

Cho ra

```
Sai
Đúng
```
vì thông điệp **hoặc:** chỉ nhận 1 đối số. Thông điệp thứ nhất
gửi **hoặc:hoặc:** đến Sai, một thông điệp không tồn tại, vì vậy đối tượng bỏ qua
thông điệp và trả về chính nó (Sai). Mặt khác, dòng thứ hai
gửi **hoặc:** tiếp theo là một **hoặc:** khác (dùng ký hiệu nối chuỗi, tức là dấu phẩy: ,).


@api_Boolean_base

# Số

{{messages}}

Mỗi lần bạn viết một số, chẳng hạn 9, -10 hoặc 3,12, thì ở phía sau
màn hình, XOScript sẽ chuyển các số này thành một đối tượng **Số**. Bạn
có thể gửi thông điệp đến đối tượng Số này, hoặc bạn có thể gán số đó
cho một biến rồi gửi thông điệp sau:

```
10 chẵn?

>> tờ-mười := 10.
tờ-mười chẵn?

```

Cả hai cách viết đều hợp lệ. Đối tượng Số phản hồi các
thông điệp sau...

Hầu hết các thông điệp này đều tự giải thích và cho phép bạn thực hiện
các phép toán hoặc phép so sánh.

{{note}}
Lưu ý rằng bạn có thể dùng ≤ ≥ ≠ × và ÷ thay cho các ký hiệu ASCII tương ứng.
Đây là vấn đề sở thích.
{{/note}}

Sự khác biệt giữa các thông điệp toán học nhị phân (+) và
các biến thể từ khóa của chúng (cộng:) là loại thứ nhất sẽ trả về
một số mới, là kết quả của phép toán, trong khi với
loại thứ hai, chính đối tượng sẽ bị thay đổi. Điều này được minh họa trong
ví dụ sau:

@test597

Trong ví dụ trên, b = 4 và a = 3. Với **cộng: 2**, giá trị
của a được tăng thêm 2, trong khi **+ 3** tạo ra một số mới
bằng a + 3. Điều tương tự áp dụng cho các phép toán khác, ví dụ
phép nhân. Khi dùng ký hiệu nhân, bạn sẽ nhận được một
đối tượng mới làm câu trả lời. Trong trường hợp bạn dùng thông điệp **nhân-với:**,
bạn sẽ nhân chính con số đó.

Với thông điệp **giữa:và:**, chẳng hạn trong: **Số
giữa: X và: Y**, bạn sẽ nhận được một số nằm giữa X và Y. Bằng
cách này, có thể tạo ra bất kỳ số ngẫu nhiên nào:

```
>> a := Số giữa: 1 và: 10.
Xuất ghi: a, xuống-dòng.
```

Kể từ phiên bản 1.4, bộ sinh số ngẫu nhiên tích hợp trong xoscript
an toàn về mặt mật mã theo hiểu biết tốt nhất của chúng tôi.

Bạn có thể gắn một **đơn-vị** cho một số, chẳng hạn **6
apples**. Mọi thông điệp không được một số nhận diện
sẽ được coi là một đơn vị. Bạn có thể lấy đơn vị của
một số bằng thông điệp đơn-vị:

Về cơ bản, đơn vị là một đối tượng văn bản được lưu cùng với đối tượng
Số. Đơn vị cũng được in ra sau con số khi thực hiện
**ghi:**. Chẳng hạn, đơn vị có thể được dùng để cộng các khoản tiền
bằng nhiều loại tiền tệ khác nhau. Khi cộng các khoản tiền, bạn có thể hỏi
các đơn vị của chúng. Ví dụ chương trình sau minh họa
nguyên tắc này bằng một máy tính quy đổi tiền tệ lịch sử (vì tỷ giá
vẫn tương đối ổn định!).

@test305

@api_Number_base
@api_Int64_base
@api_Hx_base
@api_Oct_base
@api_Bin_base

# Chuỗi

{{messages}}

Mỗi lần một văn bản được đặt giữa **ngoặc vuông và dấu nháy** ['...'],
XOScript sẽ tạo một đối tượng chuỗi mới cho bạn. Tuy nhiên, hãy
đảm bảo dùng đúng dấu nháy. Dấu nháy ở
đầu văn bản khác với dấu nháy ở cuối (điều này cho phép bạn
dùng dấu nháy đơn mà không cần thoát nó).

## UTF8

Chuỗi trong xoscript thường chứa văn bản được mã hóa utf8. Mặc dù
về mặt kỹ thuật có thể chứa nội dung nhị phân hoặc không phải utf8 trong
một chuỗi, bạn nên dùng blob cho mục đích đó. Blob được
cung cấp bởi plugin máy chủ (xem chương ffi).
Nói chung, blob/ffi được cung cấp
theo từng plugin/nền tảng, vì chúng gắn liền với nền tảng
và kiến trúc (ffi/blob). Phần lõi của ngôn ngữ kịch bản cố gắng
độc lập với nền tảng nhiều nhất có thể.

## Chuyển kiểu

Bạn có thể tạo một bản sao của mỗi đối tượng
với một kiểu khác bằng các thông điệp sau:

Thông điệp | Kết quả
---------- | ------
số         | Chuyển thành số
chuỗi      | Chuyển thành chuỗi
lôgic      | Chuyển thành giá trị lôgic
  
Các quy tắc sau được **áp dụng**:

thông điệp | Rỗng      | Lôgic              | Số                    | Văn bản   | Khác              
---------- | --------- | --------           | --------              | --------  | --------
lôgic      | Sai       | không áp dụng      | 0→Sai còn lại→Đúng    | Đúng      | Phần lớn là Đúng
số         | 0         | Sai→0 Đúng→1       | không áp dụng         | ['n']→n   | Phần lớn là 1
chuỗi      | ['Rỗng']  | ['Sai']/['Đúng']   | ['n']                 | không áp dụng | Tùy trường hợp

## Sao chép

Giá trị trong XOScript luôn được truyền **theo tham chiếu**. Trong các ngôn ngữ khác,
điều này phụ thuộc vào kiểu giá trị; trong XOScript chỉ có một cách duy nhất,
đó là theo tham chiếu. XOScript không bao giờ tạo bản sao của một giá trị. Để sao chép một đối tượng,
bạn cần gửi thông điệp **sao-chép**. 

@test611

Ở đây, bạn có thể đã nghĩ rằng kết quả sẽ là Dolly, thay vì
Donny. Tuy nhiên, không phải vậy, vì cả hai tên đều tham chiếu đến cùng một
đối tượng. Khi làm việc với vòng lặp, điều tương tự cũng xảy ra:

@test612

Thực tế, XOScript **luôn** dùng tham chiếu, vì vậy tại **:quantity**,
vòng lặp minh họa ở trên cũng chỉ đến tham chiếu tới phần tử
trong danh sách.

Để sao chép một đối tượng, bạn phải chỉ định hành động này
một cách **tường minh**:

@test613

Bằng cách gửi thông điệp đơn nguyên **sao-chép** đến một chuỗi, đối tượng
trả về một bản sao của chính đối tượng chuỗi đó. Có thể sao chép các đối tượng
Số, đối tượng lôgic, danh sách và từ điển theo cùng cách.

Bạn cũng có thể định nghĩa cách cài đặt sao chép của riêng mình; điều này thậm chí là
cần thiết nếu bạn tạo các đối tượng của riêng mình. Cách cài đặt
mặc định của sao-chép cho một danh sách tạo ra một bản sao nông, tức là nó tạo một
danh sách mới với cùng các phần tử.

@test614

Trong trường hợp này, 4 chỉ được thêm vào bản sao.
Tuy nhiên, vì đây là bản sao nông, các đối tượng trong cả hai danh sách
là như nhau.

@test615

Vì vậy, nếu chúng ta thêm 2 vào cuối mỗi tên trong bản sao, danh sách
gốc cũng bị ảnh hưởng.

Để khắc phục điều này, chúng ta cần tạo một **bản sao sâu**. Một thao tác sao chép như vậy
cho danh sách có thể được viết như sau:

@test616

Ngoài ra, hãy chú ý thông điệp đệ-quy; thông điệp này cần được
gửi trước thông điệp sao-chép.

Điều cốt yếu cần ghi nhớ là mặc dù bản sao của một đối tượng
thường trông giống bản gốc, nhưng thực tế nó
không bao giờ là cùng một đối tượng. Đối tượng gốc định nghĩa một thông điệp **equal:**,
có thể dùng để so sánh danh tính của các đối tượng. Hãy xem
ví dụ sau:

@test617

## Chuyển đổi ngầm định

XOScript dùng **chuyển đổi ngầm định** để chuyển đổi các đối tượng. Chẳng hạn, để in một
danh sách ra màn hình, XOScript sẽ gửi nội bộ thông điệp
*chuỗi* đến danh sách. Điều này có thể rất hữu ích trong
trường hợp bạn muốn in một danh sách dưới dạng danh sách phân tách bằng dấu phẩy. Thông
điệp *chuỗi* có thể được ghi đè: 

@test620

@api_String_base
@api_Format_base


## Chuỗi trên máy chủ

Các tính năng Chuỗi sau đây được bổ sung bởi
plugin Máy chủ.

@api_String_server

# Hàm

{{messages}}

Bạn có thể nhóm mã giữa { và }, khi đó nó trở thành một hàm.
Trong xoscript, đôi khi chúng tôi cũng dùng thuật ngữ tác vụ hoặc đơn giản là
khối mã.

Bạn có thể chạy một hàm bằng cách gửi thông điệp *chạy*.


```
{ Xuất ghi: 123, xuống-dòng. } chạy.
```

Nếu hàm của bạn nhận đối số, hãy dùng **áp-dụng:**.

```
{ :a Xuất ghi: a, xuống-dòng. } áp-dụng: a.
```

Xem thêm các ví dụ bên dưới.
Do kiến trúc đơn giản, một hàm chỉ có thể có
một điểm trả về. Để tránh chi phí thừa hoặc lồng nhau quá mức cho
các điều kiện, bạn có thể dùng một thủ tục (tương đương với việc dùng
dấu nhân với đối số 1):

```
{
  (a = 1) đúng: { x := 1. }, ngắt.
  (a = 2) đúng: { x := 2. }, ngắt.
} thủ-tục.
```

Bằng cách này, (a = 2) sẽ không được đánh giá nếu a = 1.
Ngoài ra, theo cách này bạn không cần các thông điệp đúng: lồng nhau.
Mỗi khi bạn thấy mình lồng các điều kiện, hãy nghĩ
đến thông điệp thủ-tục. Nó có thể giúp mã của bạn
dễ đọc hơn.


Đây là một điểm dễ nhầm lẫn quan trọng:

```
{
	Sai sai: {
		Xuất ghi: ['Kết thúc vòng lặp.'].
	}, ngắt.
	
	Xuất ghi: ['Đừng hiển thị tôi.'].

} thủ-tục.

```

Trong trường hợp này, văn bản 'Dont show me' sẽ được hiển thị.
Bởi vì **ngắt** được gửi đến Sai. Nếu bạn muốn thực hiện
ngắt, nó cần được gửi dưới dạng thông điệp đến **Đúng**.
 

```
{
	Sai phủ-định đúng: {
		Xuất ghi: ['Kết thúc vòng lặp.'].
	}, ngắt.
	
	Xuất ghi: ['Đừng hiển thị tôi.'].

} thủ-tục.

```

Sẽ hoạt động như mong đợi.

## Ngoại lệ

Ngoại lệ có thể được xử lý như sau:

```
{ Tác-vụ 1 } bắt-lỗi: { Tác-vụ 2 }, chạy.
```

Bạn cũng có thể cố ý gây ra lỗi trong chương trình của mình, và
bằng cách đó kích hoạt khối xử lý. Việc này được thực hiện bằng cách gửi
thông điệp **lỗi:** đến tác vụ hiện tại như minh họa
sau đây:

```
{
tác-vụ-này lỗi: ['Ối chà!'].
} bắt-lỗi: { :lỗi-lầm
Xuất ghi: lỗi-lầm.
}, chạy.
```

## Tiêm giá trị

XOScript cho phép tiêm giá trị vào các tác vụ. Bây giờ, hãy xem
tác vụ dưới đây:

```
>> việc-gửi := {
	Bản-tin đến: riêng recipient.
}.
việc-gửi đặt: ['recipient']
giá-trị: ['info@recipient.org'].
việc-gửi chạy.
```


Minh họa này trình bày một tác vụ giả định, gửi một bản tin
đến một địa chỉ email hoặc **người nhận**. Người nhận này có thể được tiêm
vào tác vụ từ bên ngoài và trước khi tác vụ được khởi chạy, bằng cách gửi
thông điệp **đặt:giá-trị:** đến tác vụ. Bằng cách đó, giá trị của
**recipient** được thiết lập sẵn trong tác vụ. Giá trị này cũng có thể được thay đổi
và sau đó tác vụ có thể được chạy lại. Đây là một phương pháp hữu ích khi dùng
các đối tượng tác vụ.

## Hàm rỗng

Không được phép có tác vụ rỗng. Về lý thuyết, một tác vụ rỗng sẽ trông như
thế này: **{}**, tuy nhiên XOScript coi đây là một lỗi ngôn ngữ. Nếu bạn
muốn khai báo một tác vụ rỗng, bạn có thể dùng đối tượng Rỗng:

```
>> việc := Rỗng.
```

Mặc dù đây không phải là một tác vụ thực sự mà là một đối tượng Rỗng, bạn vẫn
có thể gửi thông điệp chạy đến nó:

```
>> câu-trả-lời := việc chạy.
```

Thực tế, điều này giống với:

```
>> câu-trả-lời := Rỗng chạy.
```

Vì đối tượng **Rỗng** không nhận diện thông điệp **chạy**, nó
sẽ trả về chính nó làm câu trả lời, nên câu trả lời một lần nữa là **Rỗng**.
Vì vậy, không cần thiết phải có tác vụ rỗng. Nhờ thiết kế thanh lịch
của ngôn ngữ lập trình XOScript, bạn chỉ cần dùng đối tượng Rỗng
cho việc này.

## Phạm vi động

Khi một Hàm cần một biến nhưng không tìm thấy nó,
nó sẽ kiểm tra các biến của Hàm đã **gọi** nó,
và tiếp tục kiểm tra ngược lên chuỗi các Hàm.
Quá trình tìm kiếm này tiếp diễn cho đến khi tìm thấy biến.
Nếu vẫn không tìm thấy biến, một thông báo lỗi sẽ xuất hiện. Phương pháp tìm kiếm
biến này được gọi là **Phạm vi động**.

Để minh họa nguyên tắc này:

@test618

@api_Code_base

# Đối tượng gốc

{{messages}}

Đối tượng có tên **Đối-tượng** là đối tượng gốc của mọi đối tượng trong
XOScript và cung cấp các tính năng cốt lõi của ngôn ngữ. 

Thông điệp được gửi thường xuyên nhất
là **khi:làm:**, dùng để mở rộng chức năng của một đối tượng. Thông
điệp này được đối tượng gốc nhận, sau đó nó liên kết
tác vụ được chỉ định với thông điệp, và bằng cách đó mở rộng đối tượng
dẫn xuất.

## Phương thức bắt tất cả

Thông thường, nếu bạn gửi một thông điệp không tương ứng với
một phương thức nào trong đối tượng, nó sẽ bị bỏ qua. Tuy nhiên, bạn có thể chỉ định
các **phương thức ma thuật** hay phương thức **bắt tất cả**, chúng sẽ
được gọi nếu đối tượng không hiểu thông điệp.

Có 4 phương thức bắt tất cả. Mỗi thông điệp tương ứng với
một số lượng đối số cụ thể.

Thông điệp bắt tất cả | Số lượng đối số
--------------------- | -------------------
đáp:                  | 0
đáp:và:               | 1
đáp:và:và:            | 2
đáp:và:và:và:         | 3


@test619

## Thông điệp lập trình

Thay vì gửi trực tiếp một thông điệp đến một đối tượng, nó cũng có thể được
gửi thông qua một biến. Để làm vậy, bạn dùng thông điệp
**thông-điệp:đối-số:**. 

@test396

@api_Object_base

# Danh sách

{{messages}}

XOScript có hai loại tập hợp: *danh sách* và *từ điển*.
**Danh sách** là các dãy đối tượng theo *thứ tự cố định*. Từ điển
không có thứ tự; thay vào đó, chúng giống như một bảng chú giải gồm khóa (hay thuật ngữ) và
giá trị tương ứng. Danh sách tương tự như mảng (PHP, Java, C)
và list (Python). Từ điển tương tự như mảng kết hợp (PHP) hay
dictionary (Python) trong các ngôn ngữ lập trình khác. Để tạo
một Danh-sách mới, hãy viết:

```
>> fibonacci := Danh-sách mới.
```

Danh sách rỗng này có thể được điền bằng **thêm-cuối:** :

```
fibonacci thêm-cuối: 0.
fibonacci thêm-cuối: 1.
fibonacci thêm-cuối: 1.
fibonacci thêm-cuối: 2.
fibonacci thêm-cuối: 3.
fibonacci thêm-cuối: 5.
fibonacci thêm-cuối: 8.
fibonacci thêm-cuối: 13.
```

Nếu chúng ta ghi danh sách ra màn hình:

```
Xuất ghi: fibonacci, xuống-dòng.
```

Chúng ta sẽ thấy:

```
Danh-sách ← 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13
```

Thay vì thêm-cuối, bạn cũng có thể dùng ; để thêm phần tử vào danh sách:


```
>> fibonacci := Danh-sách mới ; 0 ; 1 ; 1 ; 2 ; 3 ; 5 ; 8 ; 13.
```

Các dấu chấm phẩy (;) đều là thông điệp nhị phân đưa một
giá trị vào danh sách.

## Nối chuỗi thông điệp

Giả sử bạn có một danh sách như:

```
>> x := Danh-sách mới ; 1 ; 2 ; 3.
```

Nếu bạn muốn xóa phần tử đầu tiên và phần tử cuối cùng, thông điệp
của bạn sẽ là:

```
x lấy-đầu lấy-cuối.
```

Đáng tiếc là cách viết trên sẽ không hoạt động đúng. Thông
điệp **lấy-đầu** trả về phần tử đầu tiên của danh sách, và phần tử này
đến lượt mình sẽ trở thành đối tượng nhận thông điệp **lấy-cuối**. Vì vậy,
thông điệp **lấy-cuối** không được gửi đến **x**, mà đến 2. Một
giải pháp khả dĩ cho vấn đề này là tạo hai câu
riêng biệt, chẳng hạn như: 

```
x lấy-đầu.
x lấy-cuối.
```

Tuy nhiên, cách này khá bất tiện, đặc biệt khi bạn cần
xóa nhiều hơn hai phần tử. Vì vậy, XOScript cung cấp một
cấu trúc thông điệp thay thế cho những tình huống như thế này. Trong
cấu trúc thông điệp **thay thế**, câu trả lời của các đối tượng bị bỏ qua
và bạn sẽ luôn nhận lại đối tượng nhận làm câu trả lời.
Cấu trúc thông điệp **thay thế** được bắt đầu bằng cách gửi
thông điệp **làm** đến một đối tượng, và cấu trúc thông điệp **thay thế**
có thể được kết thúc bằng cách gửi thông điệp **xong**. Trong
ví dụ minh họa, điều này có thể được áp dụng như sau:

```
>> x := Danh-sách mới ; 1 ; 2 ; 3.
x làm lấy-đầu lấy-cuối xong.
```

@api_List_collections

# Từ điển

{{messages}}

**Cả Danh sách và Từ điển đều là tập hợp. Tuy nhiên, khác với
danh sách, từ điển **không có** thứ tự. Một điểm khác biệt nữa giữa hai loại
là từ điển bao gồm các cặp đối tượng. Một đối tượng đóng vai trò khóa (hay
từ khóa) để tìm kiếm đối tượng còn lại. Một ví dụ điển hình về
danh sách loại này là bảng giá, chẳng hạn như:


```
>> thực-đơn := Từ-điển mới
	đặt: ['£5'] tại: ['bánh táo'],
	đặt: ['£6'] tại: ['bánh cà rốt'],
	đặt: ['£3'] tại: ['fudge'].
```

Tương tự như danh sách, thông điệp đặt:tại:
được dùng để thêm một đối tượng vào danh sách. Điểm khác biệt là, khác với
danh sách, ở đây hai đối tượng được liên kết với nhau. Đối tượng thứ nhất, tương tự
như với danh sách, là đối tượng mà bạn sẽ lưu vào danh sách. Đối tượng thứ hai
không phải là vị trí của nó trong tập hợp, mà là **khóa**
cho phép truy xuất đối tượng thứ nhất về sau. Tóm
lại, từ điển hoạt động giống như một cuốn từ điển; tức là, nhờ từ khóa
mà có thể tìm được ý nghĩa. Chẳng hạn, để lấy từ
danh sách nói trên giá của một chiếc kẹo fudge:

```
>> price := thực-đơn tại: ['fudge'].
```

Bạn cũng có thể dùng cách viết ngắn gọn:

```
>> price := thực-đơn ? ['fudge'].
```

Nếu các khóa mà bạn dùng để lưu đối tượng không chứa khoảng trắng
(và không trùng với các thông điệp đã định nghĩa sẵn khác),
cũng có thể dùng cách viết sau:

```
>> thực-đơn := Từ-điển mới
	pie:   ['£5'],
	cake:  ['£6'],
	fudge: ['£3'].
```

Chắc chắn cách viết trên đọc tự nhiên hơn một chút.
Để hỏi giá của một chiếc
kẹo fudge, có thể dùng cách viết rút gọn sau:

```
>> price := thực-đơn fudge.
```

@api_Dict_collections

# Tệp

{{messages}}

Đối tượng **Tệp** cung cấp quyền truy cập cơ bản vào hệ thống tệp.
Bạn có thể dùng đối tượng này để đọc toàn bộ tệp vào một biến
một lần, hoặc ghi các biến vào tệp một lần. Việc đọc từng dòng
cũng được hỗ trợ. Đây là các thao tác nhập/xuất tệp phổ biến nhất
trong một ngôn ngữ kịch bản. Các thao tác tệp nâng cao đòi hỏi
dùng FFI thông qua plugin máy chủ hoặc một plugin IO riêng.

@api_File_file
@api_File_vault
@api_File_fficonnect

# Ngày/Giờ

{{messages}}

Để biểu diễn thời gian và ngày tháng một cách có cấu trúc, XOScript dùng
đối tượng **Thời-điểm**. Khi một đối tượng Thời-điểm mới được in ra màn hình,
ngày và giờ hiện tại sẽ được hiển thị:

```
Xuất ghi: Thời-điểm mới, xuống-dòng.
```

Có thể cho ra kết quả như sau:

```
2020-10-10 12:16:39
```

Việc đọc từng thành phần thời gian riêng lẻ cũng rất dễ dàng. Chẳng
hạn, nếu chỉ cần biết năm hiện tại, có thể gửi thông điệp
**năm** đến thời điểm đó, và câu trả lời sẽ là một
đối tượng Số chỉ chứa năm:

```
>> m := Thời-điểm mới.
Xuất ghi: m năm, xuống-dòng.
```

@api_Moment_system

# Chương trình/Đầu ra chuẩn

{{messages}}

Đối tượng Chương-trình đại diện cho ứng dụng đang chạy. Đối tượng này
cung cấp chức năng thực thi lệnh hệ thống, nạp chương trình con,
đọc đối số và hơn thế nữa. Tức là mọi chức năng liên quan đến hệ thống.

## Đầu ra chuẩn

Xuất là đối tượng đầu ra chuẩn. Về cơ bản, nó có hai phương thức:
**ghi:** và **xuống-dòng**. Thông điệp ghi: được dùng để gửi một chuỗi
ra stdout, còn thông điệp xuống-dòng in ra một ký tự xuống dòng.
Thay vì **xuống-dòng**, bạn cũng có thể dùng \\n.

Ví dụ:

```
Xuất ghi: ['Hello World'], xuống-dòng.
```

kết quả:

```
Hello World
```

## Mô-đun/Plugin

Thế giới XOScript có thể được mở rộng với các đối tượng hệ thống mới bằng cách
cài đặt mô-đun. Một đối tượng hệ thống mới có thể được thêm vào thế giới
XOScript bằng cách đặt tệp mô-đun (thường là tệp có hậu tố .so
) vào thư mục mods. 

Khi bạn gửi một thông điệp đến đối tượng được cung cấp bởi
mô-đun plugin, XOScript sẽ tự động nạp nó.

Bạn cũng có thể tự viết plugin. Plugin được viết bằng
ngôn ngữ lập trình C. Bạn có thể tìm một plugin ví dụ trong gói mã
nguồn tại src/plugins/example.


## Phản chiếu

Có nhiều cách để khám phá
hệ thống trong khi chương trình đang chạy. XOScript có một vài phương thức để
phát hiện những đối tượng nào đang hiện diện và các đối tượng đó phản hồi
những thông điệp nào. Thứ nhất, có thể hỏi mỗi đối tượng xem nó thuộc **kiểu** gì,
tuy nhiên các kiểu trong XOScript có thể thay đổi và do đó không đáng tin cậy.

Cũng có thể hỏi đối tượng Chương-trình xem một
đối tượng cho trước đã có mặt trong chương trình hay chưa:

```
Chương-trình Công-cụ đúng: { ... }.
```

Trong trường hợp tên
đối tượng chỉ gồm một ký hiệu duy nhất, tốt nhất nên dùng
cách viết sau để tránh nhầm lẫn:

```
Chương-trình tìm: ['X'], đúng: { ... }.
```

Ngoài việc hỏi về đối tượng, cũng có thể hỏi
đối tượng Chương-trình về thông điệp. Chẳng hạn, có thể hỏi xem
đối tượng **Số** có biết thông điệp **giữa:và:** hay không, theo cách
được minh họa dưới đây:

```
Chương-trình Number: ['between:and:'], xuống-dòng.
```

@api_Program_system

# máy chủ

{{messages}}

Plugin Máy chủ trong xoscript cung cấp chức năng để
tạo các ứng dụng phía máy chủ. Để nạp plugin
máy chủ, hãy dùng:

```
Server khởi-tạo.
```

Để thuận tiện, bạn cũng nên nạp
các tệp webtools.xo và template.xo.

```
Chương-trình dùng: ['webtools.xo'].
Chương-trình dùng: ['template.xo'].

```

## Thiết lập máy chủ

Bạn có thể thiết lập các thông số máy chủ sau:

```
	# các giá trị mặc định đã được cho sẵn,
	# nên nếu bạn không đặt gì, các
	# giá trị này sẽ được dùng...

	Chương-trình 
	thiết-lập: ['max-postfields']
	giá-trị: 40.

	Chương-trình 
	thiết-lập: ['max-contentlength']
	giá-trị: 2000000. # 2MB

	Chương-trình 
	thiết-lập: ['max-time']
	giá-trị: 5000. # 5sec

```

## Xin chào thế giới

Đây là một chương trình web rất đơn giản mà bạn có thể dùng với một
máy chủ CGI tiêu chuẩn như Apache2, NGINX, OpenHTTPD hoặc bất kỳ máy chủ
phổ biến nào khác.

```
#!/bin/xo

Server khởi-tạo.
Chương-trình dùng: ['webtools.xo'].

>> tài-liệu-web := Tài-liệu-Web mới.

tài-liệu-web xuất: ['
<html>
<body>
<b>Hello World!</b>
</body>
</html>'].

```

Nếu bạn không muốn dùng đối tượng Tài-liệu-Web cũng không sao, nhưng
khi đó bạn phải tự viết các tiêu đề HTTP:

```
#!/bin/xo
Xuất ghi: ['Content-type: text/html; charset=utf-8 \n\n'], xuống-dòng.
Xuất ghi: ['xin chào thế giới!'], xuống-dòng.
``` 

## Yêu cầu

Đối tượng Yêu-cầu-HTTP có thể được dùng để lấy dữ liệu GET/POST/COOKIE và
UPLOAD:

```
>> yêu-cầu-http  := Yêu-cầu-HTTP mới.
>> search   := yêu-cầu-http get: ['search']. # ?search=books
>> password := yêu-cầu-http post: ['password']. # từ biểu mẫu
>> đã-chọn := yêu-cầu-http get-danh-sách: ['sel[]']. #?sel[]=1&sel[]=2
>> đã-chọn := yêu-cầu-http post-danh-sách: ['sel[]'].
>> cookie   := yêu-cầu-http cookie: ['session-id'].
>> tệp-tải-lên   := yêu-cầu-http upload: ['file'].
>> đường-dẫn-tạm := tệp-tải-lên ? 1.
>> tên-tệp := tệp-tải-lên ? 0.
```

## Giới hạn post/độ dài

Số trường post tối đa mặc định là 40 và độ dài nội dung tối đa
mặc định là 2MB. Để cấu hình khác đi cho từng kịch bản:

```
Chương-trình thiết-lập: ['max-contentlength'] giá-trị: 1. 
Chương-trình thiết-lập: ['max-postfields'] giá-trị: 1. 
```

{{note}}
Nếu độ dài nội dung vượt quá mức tối đa,
tiến trình sẽ bị hủy vì chúng tôi không còn chắc chắn
rằng dữ liệu gửi lên còn an toàn.
{{/note}}

Giới hạn maxtime xác định thời gian tối đa tính bằng ms
để đọc stdin/dữ liệu post.

```
Chương-trình thiết-lập: ['max-time'] giá-trị: 5000. # 5sec
```

Điều này chỉ áp dụng cho việc đọc I/O của dữ liệu post, nhằm ngăn chặn
các cuộc tấn công kiểu slowloris. Nếu bạn thực sự muốn giới hạn
thời gian thực thi của bất kỳ thao tác nào, hãy dùng hẹn-giờ: của Chương-trình.

## Cơ sở dữ liệu

Đối tượng cơ sở dữ liệu có thể được dùng để truy vấn MariaDB/MySQL.
Để kết nối tới cơ sở dữ liệu:

```
>> csdl := Maria-DB mới máy-trạm: ['localhost'],
	tên-người-dùng: ['xo'],
	mật-khẩu: ['pass123'],
	tên-cơ-sở-dữ-liệu: ['xobase'],
	kết-nối.

```

Để chèn một bản ghi, hãy dùng:

```
>> tham-số-tìm-kiếm := csdl truy-vấn: ['
	INSERT INTO book (id, description, price, rating) 
	VALUES (NULL, ?, ?, ?)
'], tham-số: ( Danh-sách mới ; ['abc'] ; 12.35 ; 6 ). # truy vấn có tham số

{  tham-số-tìm-kiếm thực-thi. csdl xác-nhận. }
bắt-lỗi: { :e csdl hoàn-tác.  }, chạy.
```

Lưu ý rằng xoscript *chỉ* làm việc với giao dịch và không bao giờ tự động commit.
Nếu không thể tắt autocommit, bạn sẽ gặp lỗi kết nối.
Luôn dùng ràng buộc tham số cho truy vấn, không bao giờ đưa trực tiếp dữ liệu người dùng nhập
vào SQL.

Lấy id vừa chèn như sau:

```
Xuất ghi: ['ĐÃ CHÈN: '] + tham-số-tìm-kiếm insert-id, xuống-dòng. # id vừa chèn
```

Để lấy các bản ghi:

```
>> tham-số-tìm-kiếm :=
csdl
	truy-vấn: ['SELECT * FROM book order by id desc limit 2'], 
	lấy: { :hàng 
		Xuất ghi: hàng id + [' '] + hàng description + [': '] + hàng price, xuống-dòng.
	}. # lấy các hàng

```

## Phiên

Để lưu trữ lâu dài, bạn có thể lưu và lấy dữ liệu từ một đối tượng phiên.
Trước tiên, hãy tạo một **Tài-liệu-Web** mới. Đối tượng Tài-liệu-Web kết nối
yêu cầu, tiêu đề, HTML và phiên với nhau. Lý do là, mỗi khi bạn
truy cập một trang web bằng trình duyệt, bạn chỉ thấy HTML. Nhưng
toàn bộ Tài-liệu-Web còn bao gồm cả các **tiêu đề**. Chẳng hạn,
hầu hết các phản hồi HTTP đều có một tiêu đề như: Content-type:text/html để
báo cho trình duyệt biết rằng dữ liệu tiếp theo cần được hiển thị dưới dạng HTML
(chứ không phải tải xuống như một tệp chẳng hạn). Phiên là một cách để
lưu dữ liệu người dùng giữa các yêu cầu. Để theo dõi dữ liệu này, chúng ta cần
đặt một cookie, và cookie này cũng được đặt thông qua một tiêu đề. Đó là lý do
mọi thứ đều được kết hợp trong Tài-liệu-Web (vì nó là toàn bộ
tài liệu chứa cả tiêu đề lẫn HTML hoặc dữ liệu khác).


```
# Trước tiên ta tạo một thể hiện Tài-liệu-Web mới
>> trang-web := Tài-liệu-Web mới.

# Giờ ta bắt đầu một phiên; việc này tạo một tiêu-đề cho cookie và
# tạo một tệp lưu dữ liệu của bạn, gắn với cookie đó
>> phiên-làm-việc := trang-web bắt-đầu-phiên.

# Giờ ta có thể dùng phiên như một Từ-điển
phiên-làm-việc userid: 123.
```

Để hủy phiên (khi đăng xuất):

```
trang-web hủy-phiên.
```

## Tiêu đề

Tài-liệu-Web cũng cho phép bạn đặt các tiêu đề phổ biến khác.
Chẳng hạn, nếu bạn muốn chuyển hướng người dùng đến một URL khác:

```
trang-web đi-đến: ['/other.html'].
```

Ở bên dưới, lệnh này cũng tạo ra tiêu đề HTTP để gửi
kèm với dữ liệu hoặc HTML khác của bạn, nhằm chỉ dẫn trình duyệt điều hướng
đến địa chỉ đích đã chỉ định.

Để thêm một tiêu đề tùy chỉnh:

```
trang-web tiêu-đề: ( 
	Tiêu-đề-HTTP mới
	khóa-tiêu-đề: ['Content-Length']
	giá-trị: 400
).
```

Để hiển thị trang 404:

```
trang-web không-tìm-thấy: ['Ối..'].
```


## Mẫu trang

Hệ thống mẫu trang mặc định rất đơn giản. Bạn không phải học
một cú pháp mẫu trang mới. Ngoài ra, bộ máy mẫu trang đảm bảo sự tách biệt thực sự
giữa phần trình bày và logic nghiệp vụ.

Để tạo một mẫu trang từ tệp:

```
>> tpl := trang-web mẫu-trang: ['templates/ux.tpl'].
```

Hệ thống mẫu trang dùng các dấu đánh dấu.
Có ba loại dấu đánh dấu: dấu cắt, dấu dán và
dấu khe. Ý tưởng cơ bản thực sự rất đơn giản: bạn cắt ra
các vùng được xác định bởi dấu cắt và có thể dán chúng vào
các vùng được xác định bởi dấu dán. Bạn có thể chèn chuỗi vào
các dấu khe.

Chẳng hạn, với mẫu trang sau, hãy đặt
viên đá quý vào hộp trang sức và gắn thêm nhãn giá.

```
<!-- cut:gem -->
<img src="gem.gif">
<b>$<!-- slot:price --></b>
<!-- /cut:gem -->

<div id="box">
<!-- paste:jewels -->
</div>
```

Bạn có thể làm như sau:

```
>> gem := tpl cắt: ['gem'], sao-chép.
gem price: 99.
tpl dán: gem tại: ['jewels'].
trang-web xuất: tpl tinh-chỉnh.
```

Dòng cuối cùng chỉ đơn giản đẩy mẫu trang dưới dạng chuỗi tới máy khách
cùng với các tiêu đề HTTP cần thiết.

Kết quả:

```
<div id="box">
<img src="gem.gif">
<b>$99</b>
</div>
```


## Chuyển tiếp tệp

Để phục vụ các tệp do người dùng tải lên một cách an toàn, bạn có thể dựa vào passthru:

```
>> đã-tải-lên := ['smile.gif'].
Server chuyển-tiếp: đã-tải-lên tiền-tố: ['/uploads/images/'].
Chương-trình kết-thúc.
```

Thao tác này sẽ phục vụ nội dung do người dùng tải lên với kiểu
mime phù hợp. Chỉ các kiểu mime trong danh sách trắng được hỗ trợ:
GIF, JPG, PNG, WEBP, MP4, WEBM, MP3, ZIP, GZIP, PDF và SVG.
Các tệp SVG, ZIP và GZIP được gửi dưới dạng tải xuống, vì một tệp SVG
có thể chứa kịch bản mà nếu không sẽ chạy trên tên miền của bạn.
Phương pháp này ngăn chặn các cuộc tấn công TOCTOU, duyệt đường dẫn,
thực thi mã độc (chèn mã), tấn công symlink,
tấn công DDoS (giới hạn tệp = 50MB), tấn công nghe lén và
nhiều vấn đề bảo mật khác.


## JSON

Để mã hóa một đối tượng thành JSON:

```
>> chuỗi-json := ( JSON jsonify: ( 
	Từ-điển mới đặt: ( 
		Danh-sách mới ; 1 ; 2 ; 3
	) tại: ['abc']
)).
```

Để giải mã JSON thành một đối tượng xoscript:

```
>> tđ := ((JSON đối-tượng: chuỗi-json) abc ? 1).
```

JSON có hơn 500 cấp lồng nhau sẽ bị từ chối vì không hợp lệ.

Để xuất trực tiếp một Từ-điển dưới dạng json với các tiêu đề đúng:

```
trang-web json: tđ.
```


## Biểu thức chính quy

Bạn có thể dùng biểu thức chính quy bằng cách tạo một mẫu.
Chẳng hạn, để khớp các href và target của siêu liên kết:

```
Mẫu mới: ['href="([^"]+)" target="([^"]+)"'].
```

Bây giờ, hãy áp dụng mẫu cho chuỗi cần xét như sau:

```
mẫu-regex khớp: chủ-đề làm: { :m :x .... }
```

Ví dụ đầy đủ:

```
>> chủ-đề := ['<html>
	<a href="http://link1" target="_blank">
	<a href="http://link2" target="_blank">
</html>'].
>> mẫu-regex := Mẫu mới: ['href="([^"]+)" target="([^"]+)"'].
>> đáp-số  := mẫu-regex khớp: chủ-đề làm: { :m :x
	Xuất ghi: m, xuống-dòng.
	Xuất ghi: x, xuống-dòng.
	<- ['XXX'].
}.
Xuất ghi: đáp-số, xuống-dòng.
```

## Mạng

Dùng đối tượng Mạng để thực hiện một yêu cầu web.
Đối tượng Mạng luôn gửi yêu cầu POST, trừ khi bạn gửi Rỗng làm
dữ liệu, khi đó nó sẽ gửi yêu cầu GET.


```
Mạng 
post: Rỗng 
tới: ['https://redbeanphp.com'].
```

## Mã hóa

Plugin máy chủ đi kèm cơ chế mã hóa dựa trên XChaCha20 và Argon2.

Ví dụ:

```
>> đã-mã-hóa := Két mã-hóa: ['hello'] khóa: ['world'].
>> đã-giải-mã := Két mã-hóa: đã-mã-hóa khóa: ['world'].
```

## Mã thông báo

Để tạo một mã thông báo an toàn về mặt mật mã với độ dài cụ thể:

```
>> mã-thẻ-của-tôi := Két mã-thông-báo: 40.
```

Lệnh này sẽ tạo ra một mã thông báo gồm 40 ký tự.

## Định dạng

Đối tượng Định-dạng cho phép bạn định dạng dữ liệu, chẳng hạn như đệm hoặc
thêm số không. Nó dùng cú pháp printf.

```
>> đd := Định-dạng mới: ['%06.0f'].
đd áp-dụng: 56. # cho ra 000056
```

Một định dạng có thể chứa một phép chuyển đổi và phép chuyển đổi đó phải phù hợp với giá trị,
nếu không bạn sẽ gặp lỗi:

- `áp-dụng:` với một chuỗi: `%s`
- `áp-dụng:` với một số: `%f`, `%e`, `%g` hoặc `%a`
- `áp-dụng-số-nguyên:` với một số: `%d`, `%i`, `%o`, `%u`, `%x` hoặc `%c`

Các giá trị từ một yêu cầu là chuỗi. Để định dạng một giá trị như vậy thành số,
trước tiên hãy chuyển đổi nó:

```
đd áp-dụng: (yêu-cầu-http get: ['amount']) số.
```

## Bộ mã hóa

Có sẵn một số bộ mã hóa và giải mã.
Bộ mã hóa url chuẩn bị một url để dùng trong HTML làm liên kết:

```
Server url-mã-hóa: ['https://example.com?a=6&b=1 2'].
```

Để chèn dữ liệu người dùng nhập vào HTML một cách an toàn mà không có nguy cơ bị tấn công
XSS, hãy luôn dùng:

```
Server html-mã-hóa: ['<harmless>'].
```

Lưu ý rằng bộ máy mẫu trang sẽ luôn thực hiện mã hóa html
khi bạn ghi vào một dấu khe. Vì vậy, nếu bạn dùng hệ thống mẫu trang
thì không cần dùng cách này.

## Gửi thư

Để gửi thư, hãy dùng thư viện mailtools.xo.

Ví dụ:

```
Server khởi-tạo.
Chương-trình dùng: ['mailtools.xo'].

>> lá-thư := Thư-HTML mới.
>> img := lá-thư đính-kèm: ( Tệp mới: ['myimage.png'] ).

lá-thư
người-gửi: ['xo@xoscript.com'] tên: ['xo'],
đến: ( Danh-sách mới ; ['xo2@xoscipt.com'] ),
chủ-đề: ['xoxo'],
thân-thư: (['
<html>
<body>
<h1>hello!</h1>
<img src="<cid>">
</body>
</html>	
'] <cid>: img), gửi.

```



## Liên kết thư viện

Với thông điệp liên-kết:, bạn có thể liên kết một thư viện bên ngoài với
chương trình của mình bằng libffi. Để biết chi tiết, hãy xem chương về ffi.


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

FFI được cung cấp theo từng nền tảng/plugin vì nó
gắn liền với kiến trúc hệ thống bên dưới, điều mà phần
lõi không được phép làm.
Plugin máy chủ cung cấp một cài đặt ffi/blob tuân thủ chuẩn.
Theo mặc định, phần lõi kết nối với nền tảng đích
thông qua stdin/stdout, các dịch vụ nhập/xuất tệp hạn chế và shell (Chương-trình hệ-thống:).
Việc tích hợp bổ trợ được cung cấp bởi ffi/blob thông qua các plugin
hướng ứng dụng như plugin máy chủ.

FFI là viết tắt của Foreign Function Interface (giao diện hàm ngoại). Nó cho phép bạn dùng chức năng do người khác viết bằng
các ngôn ngữ lập trình khác, được cung cấp qua các tệp DLL, tệp SO hoặc tệp Dylib. Đó có thể
là đủ loại hàm khác nhau, và có rất nhiều chức năng sẵn có thông qua phương pháp này.
Hãy bắt đầu với một ví dụ:

```
Server liên-kết: (
 Danh-sách mới ;
 ['/usr/lib/x86_64-linux-gnu/libc.so.6'] ;
 ['printf'] ;
 ( Danh-sách mới ; ['pointer'] ; ['int'] ) ;
 ['void'] ;
 ['Printf'] ;
 ['template:number:']
).
>> s := Blob utf8: ['FFI has %d letters.\n'].
Printf template: s number: 3.
s giải-phóng.
```

Kết quả của đoạn mã này là bạn sẽ thấy dòng sau trên dòng lệnh:
FFI has 3 letters.
Có lẽ bây giờ bạn đang nghĩ: "Nhiều mã quá cho một việc đơn giản như vậy."
Ý tôi là, chẳng phải chúng ta có thể giải quyết việc này bằng một lệnh hiển thị Gui sao? Câu trả lời chắc chắn là có!
Nhưng đây chỉ là một ví dụ minh họa.
FFI thường được dùng cho các tác vụ phức tạp hơn, nhưng những tác vụ đó không phải là
ví dụ hay, vì vậy tôi chọn một việc đơn giản.

Các đối số của phương thức liên-kết:

- Đối số #1: Tệp DLL hoặc SO mà bạn muốn dùng.
- Đối số #2: Hàm trong tệp đó mà bạn muốn liên kết.
- Đối số #3: Một danh sách tên các kiểu dữ liệu của các đối số của hàm.
- Đối số #4: Tên kiểu trả về của hàm.
- Đối số #5: Tên của đối tượng mà bạn muốn liên kết hàm này vào (nếu nó chưa tồn tại, nó sẽ được tạo
tự động).
- Đối số #6: Thông điệp mà hàm này sẽ được liên kết với.

Trong ví dụ trên, chúng ta muốn liên kết hàm printf từ libc.so. Bạn có thể tìm tên các kiểu
dữ liệu trong tài liệu của phần mềm mà bạn liên kết tới. Các kiểu có sẵn là:
void, pointer, float, double, int, uint, char, uchar, intX và uintX,
trong đó X có thể là 8, 16, 32 hoặc 64.

Các kiểu này chỉ số byte cần thiết để lưu dữ liệu. Với printf, chúng ta liên kết tới một
đối tượng mới tên là Printf và thông điệp template:number:. Bạn chuyển hàm bên ngoài
sang phương ngữ XOScript trước khi sử dụng. Thông điệp template:number: nhận một
bộ đệm chứa văn bản mẫu làm tham số đầu tiên. Chúng ta tạo bộ đệm này bằng một đối tượng Blob,
cho phép bạn cấp phát bộ nhớ thủ công. Bạn có trách nhiệm giải phóng bộ nhớ này sau đó
bằng thông điệp giải-phóng.

Bạn có thể điền dữ liệu vào một blob bộ nhớ theo nhiều cách. Trong ví dụ của chúng ta, ta điền văn bản vào nó, vì vậy ta dùng
thông điệp utf8: (UTF-8 là một cách mã hóa để chuyển văn bản thành byte). Bạn cũng có thể điền vào blob bằng
bytes:, truyền vào một danh sách các giá trị byte. Để đọc nội dung của một blob, hãy dùng từ:độ-dài:.
Bạn sẽ nhận lại các byte dưới dạng một danh sách. Bạn thậm chí có thể tạo một C-struct bằng Blob với
thông điệp struct:, truyền vào một dãy các kiểu C. Điều này có thể cần thiết khi gọi một hàm C
trong một thư viện phần mềm bên ngoài nhận con trỏ tới một struct.

{warning}
Bạn cần tự giải phóng các blob.
Blob không được bộ thu gom rác dọn dẹp.
{/warning}

Vì blob có thể được trao đổi với các hàm bên ngoài từ thư viện, chúng
không thể được thu gom rác tự động (chúng có thể vẫn đang được các hàm bên ngoài
sử dụng, hoặc các hàm bên ngoài đó có thể muốn tự giải phóng
chúng). Vì vậy, bạn cần tự giải phóng blob khi cần thiết.

Để giải phóng một blob, hãy dùng:

```
blob-của-tôi giải-phóng.
```

Để giải phóng struct, hãy dùng:

```
cấu-trúc-của-tôi giải-phóng-struct giải-phóng.
```

Như vậy, với một struct, bạn cần gửi hai thông điệp: giải-phóng-struct và giải-phóng để
thu hồi khối bộ nhớ.

@api_Blob_fficonnect
