#include <iostream>
#include <vector>
using namespace std;

struct DuongThang
{
    long long m, c; // y = m*x + c
    // Tính giá trị y tại hoành độ x
    long long layGiaTri(long long x) { return m * x + c; }
};

class ConvexHullTrick
{
private:
    vector<DuongThang> hull;

    // Kiểm tra xem đường thẳng l2 có trở nên vô dụng giữa l1 và l3 hay không
    bool laGiaoDiemTep(DuongThang l1, DuongThang l2, DuongThang l3)
    {
        // Giao điểm (l1, l3) nằm bên trái giao điểm (l1, l2)
        return (double)(l3.c - l1.c) / (l1.m - l3.m) <= (double)(l2.c - l1.c) / (l1.m - l2.m);
    }

public:
    // Thêm đường thẳng mới vào tập hợp (yêu cầu độ dốc m giảm dần)
    void themDuongThang(long long m, long long c)
    {
        DuongThang dl = {m, c};
        while (hull.size() >= 2 && laGiaoDiemTep(hull[hull.size() - 2], hull.back(), dl))
        {
            hull.pop_back();
        }
        hull.push_back(dl);
    }

    // Truy vấn giá trị nhỏ nhất tại x bằng chặt nhị phân
    long long query(long long x)
    {
        int l = 0, r = hull.size() - 1;
        long long ans = hull[0].layGiaTri(x);
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            long long v1 = hull[mid].layGiaTri(x);
            ans = min(ans, v1);
            if (mid + 1 < hull.size() && hull[mid + 1].layGiaTri(x) < v1)
            {
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        return ans;
    }
};

int main()
{
    ConvexHullTrick cht;
    // Thêm các đường thẳng vào tập hợp theo thứ tự hệ số góc giảm dần
    cht.themDuongThang(4, 0);  // y = 4x + 0
    cht.themDuongThang(2, 3);  // y = 2x + 3
    cht.themDuongThang(0, 10); // y = 0x + 10

    cout << "--- KET QUA CONVEX HULL TRICK ---\n";
    cout << "Gia tri y nho nhat tai x = 1: " << cht.query(1) << "\n"; // y = 2(1)+3 = 5
    cout << "Gia tri y nho nhat tai x = 5: " << cht.query(5) << "\n"; // y = 0(5)+10 = 10
    return 0;
}