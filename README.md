#  ADVENTURE TIME - SPACE SURVIOR - INT2215 - UET
### Video Demo 
## Table Of Contents <br />
* [Hướng dẫn cài đặt](#setup)
* [Mô tả chung](#info)
* [Kỹ thuật lập trình](#tech)
* [Các hướng đi trong tương lai](#future)
* [Kết luận](#summary)


* <a name="setup"/>
## 1. Hướng dẫn cài đặt
- Để khởi động trò chơi, click AdventureTime_SpaceSurvivor.exe. <br />


* <a name="info"/>
## 2. Mô tả chung <br />

### Giới thiệu
Adventure Time - Space Survivor là một trò chơi nơi kỹ năng sinh tồn của bạn sẽ được thử thách bằng cách phải vượt qua những nguy hiểm trong vũ trụ, chống lại những con quái vật đáng sợ và cố gắng sống sót đến khi hết thời gian. <br />

* <a name="tech"/>
## 4. Kỹ thuật lập trình <br />
### Xây dựng trên nền tảng C++ và SDL2 bao gồm:<br />
- SDL_Image: Hỗ trợ xử lý hình ảnh.
- SDL_Mixer: Hỗ trợ xử lý âm thanh. <br />
- SDL_TTF: Hỗ trợ xử lý fonts chữ. <br />
- Các thư viện mở rộng C++. <br />
- IDE Visual Studio Code. <br />

### Các kỹ thuật lập trình <br />
- Gồm tất cả các kỹ thuật cơ bản: <br />
- Biến (static, extern), vòng lặp, cấu trúc rẽ nhánh, mảng, chuỗi. <br />
- Con trỏ, set, map, vector <br />
- Class: Tạo, hủy, member function. <br />
- Đọc viết file binary. <br />
- Multithreading: Xử lý chức năng Battle.<br />
- Tách file giấu code.<br />
- Kỹ thuật duyệt mảng, sinh số ngẫu nhiên.<br />
- Kỹ năng refac code.
- Các kỹ thuật, syntax của SDL.
- Kỹ thuật giải phóng bộ nhớ động. <br />


### Ứng dụng
- Thuật toán sinh Khối Hình ngẫu nhiên giảm tỷ lệ sinh 2 khối giống nhau liên tiếp. <br />
- Mỗi chức năng của game (Play Single, Battle, Setting, Helps), mỗi Khối hình (Tetrads) được xác định bằng 1 đối tượng (class) riêng biệt.  <br />
- Ứng dụng đa nhiệm xử lý Battle khi có 2 người chơi cùng thao tác trên một bàn phím cùng 1 lúc.  <br />

- <a name="future"/>
## 5. Các hướng đi trong tương lai <br />
### Kết nối hóa trò chơi: Royal Battle: Nâng cấp chức năng Battle trở thành Royal Battle:<br />
- Sử dụng kết nối mạng máy tính (LAN, Router,... ) kết nối người chơi với nhau. <br />
- Sẽ thiết lập một trường cơ sở dữ liệu (database) lưu trữ trên máy chủ (server) lưu trữ thông tin người chơi. <br />
- Một Đấu Trường bao gồm khoảng 10-50-100 người chơi. <br />
- Khi một người chơi bất kỳ ăn hàng, hàng đó sẽ không biến mất mà trở thành Garbage Tetrads xuất hiện tại màn hình của người chơi khác bất kỳ (random). <br />
- Người chơi cuối cùng nằm xuống là người chiến thắng. <br />

 ### Xã hội hóa: Ứng dụng trí tuệ nhân tạo viết bot Deep Green chơi với người tự kỷ, người cô đơn,... <br />
 - Thêm chức năng chơi với máy (Play With Deep Green). <br />
 - Công việc của Deep Green:  <br />
&nbsp; - Nhận diện grid, nhận diện Khối Hình hiện tại và các khối tiếp theo <br />
&nbsp; - Xử lý dữ liệu bằng thuật toán. <br />
&nbsp; - Đưa ra vị trí và góc quay tối ưu nhất để bạn không bao giờ thắng được máy =))). <br />

### Tư bản hóa trò chơi: Hệ thống nạp tiền Pay to Play: <br />
- Người chơi sẽ nạp tiền vào game, số tiền sẽ chuyển vào tài khoản nhà phát hành. <br />
- Tiền nạp sẽ chuyển hóa thành Coin với tỷ lệ tương ứng. <br />
- Có thể dùng Coin để đổi các vật phẩm sau: <br />

&nbsp; - Skin cho Khối Hình theo cơ chế gacha (quay ngẫu nhiên từ một tập có sẵn) <br />
&nbsp; - Theme UI game mới <br />
&nbsp; - Theme Music game mới <br />
&nbsp; - Tốn Coin để giảm độ khôn của Deep Green, giúp chiến thắng bot một cách dễ dàng, giảm đi áp lực cuộc sống. <br />

* <a name="summary"/>
## 6. Kết luận
Game được hoàn thiện trong thời gian một tháng. <br />
Tham khảo các nguồn tài liệu: LazyFoo, Phattrienphanmem123az,.... <br />

### Việc hoàn thiện 1 dự án lập trình như thế này giúp em mở mang kiến thức rất nhiều.<br />
- Hiểu được mô hình phát triển 1 phần mềm <br />
- Sử dụng thành thạo class, pointer, chia tách file,...<br />
- Cách dùng github.<br />
- Học rất nhiều syntax, thuật toán mới của c++.<br />
- Hiểu sơ sơ một số khía cạnh của lập trình hướng đối tượng: kế thừa, đa hình,...<br />

### Khuyết điểm <br />
- Code chưa được tối ưu hoàn toàn. <br />
- Các syntax và thuật toán vẫn còn ngây ngô. <br />
- Một vài đoạn code thiếu trong sáng gây hoang mang cho người đọc <br />

Cuối cùng, em xin chân thành cảm ơn thầy cô đã hướng dẫn em trong suốt quá trình hoàn thiện dự án game này <br />
A Special Thanks To:<br />
- Thầy Nguyễn Việt Anh.<br />
- Cô Vương Thị Hải Yến.<br />
## Em xin trân trọng cảm ơn thầy, cô đã dành thời gian lắng nghe. <br />
