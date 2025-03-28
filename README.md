# 🧙‍♀️ Elina's Witchcraft
Tên và Mã sinh viên: Nguyễn Thanh Duy - 24021449

Đây là một game Survival Shooter - sử dụng phép thuật để bắn những kẻ địch đang từ từ tiến tới.

Ngưỡng điểm mong muốn : 10!

---
## 🏆 Tại sao Game này lại xứng đáng 10/10?

1. Các tính năng cốt lõi (Core Gameplay):

- Bắn đạn với cooldown, sát thương, hiệu ứng riêng biệt:
  - Đạn có 3 loại: Fireball (Sát thương lớn), Snowball (Làm chậm kẻ địch), và Windstorm (lôi kéo kẻ địch)​
  - Mỗi loại đạn đều có cooldown và có thể được nâng cấp để tăng sức mạnh và giảm thời gian hồi chiêu.
- Hệ thống spawn kẻ địch theo wave:
  - Có nhiều loại kẻ thù: Slime, Golem, Miku, Fire Slime, Ice Slime với animation riêng​.
. - Mỗi loại kẻ địch đều sẽ có những tính năng riêng biệt (Fire slime kháng Fireball, Ice slime kháng Iceball,...).
  - Hệ thống spawn kẻ địch theo một thứ tự ngẫu nhiên tại một vị trí ngẫu nhiên, đảm bảo từng wave riêng biệt, không cái nào giống cái nào.
- Kiểm tra va chạm:
  - Kiểm tra va chạm giữa đạn và kẻ địch bằng AABB Collision Detection​.
  - Va chạm dẫn đến giảm HP của kẻ thù và hủy đạn.
- Kiểm tra Gameover:
  - Khi kẻ thù vượt qua nhân vật, HP giảm và sẽ hiện màn hình Gameover khi HP giảm đến 0.
2. Giao diện và trải nghiệm người dùng:
- UI đầy đủ:
  - Menu chính với nút Play, Quit.
  - Gameplay có nút Shop và Setting.
  - Giao diện khi Game Over với tùy chọn Restart và Menu​.
  - Các thanh hiển thị HP, cooldown, và Coin dễ nhìn và cập nhật một cách chính xác.
  - Các nút đều hoạt động một cách mượt mà với các Animation khi nhấn chuột hoặc giữ chuột vào nút.
- Hệ thống Animation:
  -Mỗi đối tượng trong game đều có Animation riêng, cập nhật theo thời gian



