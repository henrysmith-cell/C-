#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int KICH_THUOC_BLOCK;

// Cấu trúc quản lý thông tin một truy vấn
struct TruyVan
{
    int L, R, id;
    // Sắp xếp các truy vấn theo khối (Block) của L, nếu cùng khối thì xếp theo R
    bool operator<(const TruyVan &khac) const
    {
        if (L / KICH_THUOC_BLOCK != khac.L / KICH_THUOC_BLOCK)
            return L / KICH_THUOC_BLOCK < khac.L / KICH_THUOC_BLOCK;
        return R < khac.R;
    }
};

int main()
{
    vector<int> A = {1, 3, 2, 4, 5};
    int n = A.size();
    KICH_THUOC_BLOCK = sqrt(n); // Chia mảng thành các khối có độ rộng căn N

    vector<TruyVan> dsTruyVan = {
        {0, 2, 0}, // Đoạn [0, 2] -> index 0
        {1, 4, 1}, // Đoạn [1, 4] -> index 1
        {2, 3, 2}  // Đoạn [2, 3] -> index 2
    };
    int q = dsTruyVan.size();

    // Sắp xếp các truy vấn theo quy tắc của Mo để tối ưu đường đi con trỏ
    sort(dsTruyVan.begin(), dsTruyVan.end());

    vector<int> ketQua(q);
    int currL = 0, currR = -1;
    int tongHienTai = 0;

    for (int i = 0; i < q; i++)
    {
        int L = dsTruyVan[i].L;
        int R = dsTruyVan[i].R;

        // Mở rộng hoặc thu hẹp con trỏ R
        while (currR < R)
        {
            currR++;
            tongHienTai += A[currR];
        }
        while (currR > R)
        {
            tongHienTai -= A[currR];
            currR--;
        }

        // Mở rộng hoặc thu hẹp con trỏ L
        while (currL < L)
        {
            tongHienTai -= A[currL];
            currL++;
        }
        while (currL > L)
        {
            currL--;
            tongHienTai += A[currL];
        }

        // Lưu kết quả vào đúng ID của truy vấn ban đầu
        ketQua[dsTruyVan[i].id] = tongHienTai;
    }

    cout << "--- KET QUA CAC TRUY VAN (THEO MO'S ALGORITHM) ---\n";
    for (int i = 0; i < q; i++)
    {
        cout << "Truy van " << i << " : " << ketQua[i] << "\n";
    }

    return 0;
}