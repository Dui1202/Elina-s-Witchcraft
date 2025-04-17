# 🧙‍♀️ Elina's Witchcraft
Tên và Mã sinh viên: Nguyễn Thanh Duy - 24021449

Đây là một game Survival Shooter - sử dụng phép thuật để bắn những kẻ địch đang từ từ tiến tới.

Ngưỡng điểm mong muốn : 10!
---
## Cách chơi
- Di chuyển lên xuống bằng W và S.
- Bắn đạn bằng SPACE.
- Chuyển đạn bằng J/K/L - Fireball/Snowball/Windstorm.
---
## 🏆 Tại sao Game này lại xứng đáng 10/10?

### 1. 🕹️ Các tính năng cốt lõi (Core Gameplay):

- Bắn đạn với cooldown, sát thương, hiệu ứng riêng biệt:

  - Đạn có 3 loại: Fireball (Sát thương lớn), Snowball (Làm chậm kẻ địch), và Windstorm (lôi kéo kẻ địch)​
  - Mỗi loại đạn đều có cooldown riêng và có thể được nâng cấp để tăng sức mạnh và giảm thời gian hồi chiêu.
  
- Hệ thống spawn kẻ địch theo wave:

  - Có nhiều loại kẻ thù: Slime, Golem, Miku, Fire Slime, Ice Slime với animation riêng​.
. - Mỗi loại kẻ địch đều sẽ có những tính năng riêng biệt (Fire slime kháng Fireball, Ice slime kháng Iceball,...).
  - Hệ thống spawn kẻ địch theo một thứ tự ngẫu nhiên tại một vị trí ngẫu nhiên, đảm bảo từng wave riêng biệt, không cái nào giống cái nào.
  
- Kiểm tra va chạm:

  - Kiểm tra va chạm giữa đạn và kẻ địch bằng AABB Collision Detection​.
  - Va chạm dẫn đến giảm HP của kẻ thù và hủy đạn.
 
- Kiểm tra Gameover:

  - Khi kẻ thù vượt qua nhân vật, HP giảm và sẽ hiện màn hình Gameover khi HP giảm đến 0.
  
### 2. 🎨 Giao diện và trải nghiệm người dùng:

- UI đầy đủ:

  - Menu chính với nút Play, Quit.
  - Gameplay có nút Shop và Setting.
  - Giao diện khi Game Over với tùy chọn Restart và Menu​.
  - Các thanh hiển thị HP, cooldown, và Coin dễ nhìn và cập nhật một cách chính xác.
  - Các nút đều hoạt động một cách mượt mà với các Animation khi nhấn chuột hoặc giữ chuột vào nút.
  
- Hệ thống Animation:

  - Mỗi đối tượng trong game đều có Animation riêng, cập nhật theo thời gian.
  - Toàn bộ Animation đều được vẽ bằng tay, không lấy từ bất kì nguồn nào.
 
- Hệ thống Âm thanh:

  - Âm thanh theo sự kiện:
    - Âm thanh khi bắn Fireball, Snowball, và Windstorm​.
    - Âm thanh khi bấm nút, lên cấp kỹ năng.
  - Nhạc nền động:
    - Nhạc thay đổi theo trạng thái trò chơi: Menu, Gameplay, và Game Over​.
    - Giảm âm lượng khi trong trạng thái Pause game.

### 3. ⚡ Quản lí tài nguyên Game:
- Quản lí tài nguyên:

  - Tất cả texture, âm thanh và phông chữ đều được load sẵn và quản lý bởi ResourceManager​.
  - Hệ thống [Prefab](https://docs.unity3d.com/6000.0/Documentation/Manual/Prefabs.html) (được lấy cảm từ Unity) cho Animation, GameObject,... giúp tái sử dụng tài nguyên hiệu quả và tối ưu hóa bộ nhớ.
  - Hệ thống Prefab còn giúp xây dựng Game một cách dễ dàng hơn.
  
- Dọn dẹp tài nguyên:
  
  - Toàn bộ các tài nguyên đều được cho vào các vector, vậy nên khi thoát Game, các tài nguyên đều chắc chắn sẽ được giải phóng đúng cách để tránh memory leak.
 
### 4. 📚 Code quality:
- Code sạch và tách biệt module.
- Dễ dàng mở rộng và thêm các tính năng mới.

## ⭐ Tóm tắt các điểm nổi bật:

-  Game đã hoàn thiện tất cả các yêu cầu cơ bản và nâng cao cho một game Survival Shooter.
-  Các Animation đều được vẽ bằng tay để có thể hoạt động trơn tru với module Animation trong code.
-  Có đầy đủ các UI cần thiết cho một con game hoàn chỉnh.
-  Sử dụng hệ thống Prefab để có thể tái sử dụng các Gameobject, tối ưu hiệu suất game.

## Checklist
1. [x] Dùng các lệnh vẽ hình
2. [x] Texture
3. [x] Background
4. [x] Event bàn phím
5. [x] Event chuột
6. [x] Animation (hoạt hình)
7. [x] Xử lý va chạm
8. [ ] Score (có tính điểm)
9. [ ] Lưu bảng điểm
10. [x] Sound
11. [ ] Sound on off
12. [x] Background music
13. [x] Font
14. [x] Menu
15. [x] Pause/Resume
16. [x] Status bar / lives (mạng/máu...)

## Những phần code được tham khảo:
- [Hàm RenderWindow](https://www.youtube.com/watch?v=pjLpipQRMIw&list=PL2RPjWnJduNmXHRYwdtublIPdlqocBoLS&index=3).
- [Hàm Entity](https://www.youtube.com/watch?v=WK_ojz7TOdM&list=PL2RPjWnJduNmXHRYwdtublIPdlqocBoLS&index=6).
- [Hàm va chạm](https://lazyfoo.net/tutorials/SDL/27_collision_detection/index.php).
- [Hàm Vector2f](https://www.youtube.com/watch?v=ksXY1mHHi7Y&list=PL2RPjWnJduNmXHRYwdtublIPdlqocBoLS&index=9).

## Mức độ sử dụng AI:

- AI chủ yếu được sử dụng để tìm hiểu thêm về các hàm trong SDL2 và là phương án cuối cùng để Debug khi gặp Bug khó nhằn.

## Các nguồn tham khảo:
### 1. Các nguồn tự học:
- [Lazy Foo](https://lazyfoo.net/tutorials/SDL/index.php).
- [Youtube - codergopher](https://www.youtube.com/watch?v=KsG6dJlLBDw&list=PL2RPjWnJduNmXHRYwdtublIPdlqocBoLS&index=1).
- [Youtube - Let's Make Games](https://www.youtube.com/watch?v=QQzAHcojEKg&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&index=1).

### 2. Các nguồn lấy file âm thanh:
- [Menu Music - Blue Archive OST 25. Future Bossa](https://www.youtube.com/watch?v=kiwWb_1KFKs).
- [Gameplay Music - [Zachz Winner] doodle (NES 8-bit remix)](https://www.youtube.com/watch?v=HoHGQgSYiWo).
- [Gameover Music - Undertale OST: 011 - Determination](https://www.youtube.com/watch?v=W1i4mTyidOc).
- [Button SFX - 90s Game UI 6, Levelup SFX - Cute Level Up 3)](https://pixabay.com/sound-effects/search/button/?order=ec).
- [Fireball SFX](https://www.youtube.com/watch?v=xX0TbeEY_RM).
- [Snowball SFX](https://www.youtube.com/watch?v=JCu7q5gZaeA).
- [Windstorm SFX - Wind blowing sfx](https://pixabay.com/sound-effects/search/wind/).


