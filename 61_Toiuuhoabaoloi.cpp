#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct DuongThang
{
    long long m, c; // y = m*x + c
    // Hàm tính giá trị y tại điểm x
    long long layGiaTri(long long x) { return m * x + c; }
};

// Kiểm tra xem đường thẳng thứ 3 có làm cho đường thẳng thứ 2 trở nên vô dụng (bị loại khỏi bao lồi) không
bool biGiaoNhauSom(DuongThang l1, DuongThang l2, DuongThang l3)
{
    // Giao điểm của l1 và l3 nằm bên trái giao điểm của l1 và l2
    return (double)(l3.c - l1.c) / (l1.m - l3.m) <= (double)(l2.c - l1.c) / (l1.m - l2.m);
}

struct ConvexHullTrick
{
    vector<DuongThang> baoLoi;

    // Thêm một đường thẳng mới vào tập hợp (yêu cầu hệ số góc m phải giảm dần)
    void themDuongThang(long long m, long long c)
    {
        DuongThang lMoi = {m, c};
        while (baoLoi.size() >= 2 && biGiaoNhauSom(baoLoi[baoLoi.size() - 2], baoLoi.back(), lMoi))
        {
            baoLoi.pop_back(); // Loại bỏ đường thẳng vô dụng khỏi bao lồi
        }
        baoLoi.push_back(lMoi);
    }

    // Tìm giá trị y nhỏ nhất tại vị trí x bằng tìm kiếm nhị phân trong O(log N)
    long long layMin(long long x)
    {
        int low = 0, high = baoLoi.size() - 1;
        long long minAns = baoLoi[0].layGiaTri(x);

        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            long long valMid = baoLoi[mid].layGiaTri(x);
            minAns = min(minAns, valMid);

            if (mid < baoLoi.size() - 1 && baoLoi[mid + 1].layGiaTri(x) < valMid)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return minAns;
    }
};

int main()
{
    ConvexHullTrick cht;

    // Giả lập nạp các đường thẳng từ các trạng thái DP trước đó vào hệ thống
    // Lưu ý: Hệ số góc m nạp vào phải được sắp xếp giảm dần (ví dụ: 4 -> 2 -> 1)
    cht.themDuongThang(4, 0);
    cht.themDuongThang(2, 3);
    cht.themDuongThang(1, 7);

    long long x = 2;
    cout << "--- KET QUA CONVEX HULL TRICK ---\n";
    cout << "Gia tri y nho nhat tai x = " << x << " la: " << cht.layMin(x) << endl;
    // Các đường thẳng tại x=2: 4*2+0=8; 2*2+3=7; 1*2+7=9 -> Nhỏ nhất bằng 7

    return 0;
}