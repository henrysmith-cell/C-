#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

// Định nghĩa các loại sự kiện (Event) khi đường quét đi qua
enum LoaiSuKien
{
    BAT_DAU,
    KET_THUC,
    DUONG_DOC
};

struct SuKien
{
    int x, y1, y2;
    LoaiSuKien loai;

    // Sắp xếp các sự kiện từ trái sang phải theo trục X
    bool operator<(const SuKien &khac) const
    {
        if (x != khac.x)
            return x < khac.x;
        return loai < khac.loai; // Ưu tiên xử lý sự kiện bắt đầu trước
    }
};

int main()
{
    vector<SuKien> dsSuKien;

    // Thêm đoạn thẳng nằm ngang từ (1, 3) đến (5, 3)
    dsSuKien.push_back({1, 3, 3, BAT_DAU});
    dsSuKien.push_back({5, 3, 3, KET_THUC});

    // Thêm đoạn thẳng đứng từ (3, 1) đến (3, 5)
    dsSuKien.push_back({3, 1, 5, DUONG_DOC});

    sort(dsSuKien.begin(), dsSuKien.end());

    set<int> activeY; // Quản lý tập hợp các tọa độ Y của các đường ngang đang hoạt động
    int soGiaoDiem = 0;

    for (const auto &ev : dsSuKien)
    {
        if (ev.loai == BAT_DAU)
        {
            activeY.insert(ev.y1); // Đường ngang bắt đầu xuất hiện, ghi nhận tọa độ Y
        }
        else if (ev.loai == KET_THUC)
        {
            activeY.erase(ev.y1); // Đường ngang kết thúc, xóa tọa độ Y khỏi danh sách
        }
        else if (ev.loai == DUONG_DOC)
        {
            // Khi gặp đường dọc, đếm xem có bao nhiêu đường ngang đang cắt qua khoảng trống [y1, y2]
            auto low = activeY.lower_bound(ev.y1);
            auto up = activeY.upper_bound(ev.y2);
            soGiaoDiem += distance(low, up);
        }
    }

    cout << "--- KET QUA SWEEP-LINE ---\n";
    cout << "Tong so giao diem tim duoc la: " << soGiaoDiem << endl; // Kết quả: 1 giao điểm tại (3, 3)
    return 0;
}