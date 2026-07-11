#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int KICH_THUOC_BLOCK;

struct TruyVan
{
    int L, R, id;
    // Sắp xếp các truy vấn theo block của L, nếu cùng block thì xếp theo R
    bool operator<(const TruyVan &khac) const
    {
        int block_a = L / KICH_THUOC_BLOCK;
        int block_b = khac.L / KICH_THUOC_BLOCK;
        if (block_a != block_b)
            return block_a < block_b;
        return (block_a & 1) ? (R < khac.R) : (R > khac.R); // Tối ưu đường đi của con trỏ (Z-order)
    }
};

int tanSuat[1000005]; // Mảng đếm tần suất xuất hiện của các phần tử
int soPhanTuPhanBiet = 0;

void them(int x)
{
    if (tanSuat[x] == 0)
        soPhanTuPhanBiet++;
    tanSuat[x]++;
}

void xoa(int x)
{
    tanSuat[x]--;
    if (tanSuat[x] == 0)
        soPhanTuPhanBiet--;
}

int main()
{
    vector<int> a = {1, 1, 2, 1, 3, 4, 5, 2, 8};
    int n = a.size();
    KICH_THUOC_BLOCK = sqrt(n);

    vector<TruyVan> q = {
        {0, 4, 0}, // Đoạn [1, 1, 2, 1, 3] -> 3 phần tử phân biệt (1, 2, 3)
        {1, 3, 1}, // Đoạn [1, 2, 1] -> 2 phần tử phân biệt (1, 2)
        {2, 7, 2}  // Đoạn [2, 1, 3, 4, 5, 2] -> 5 phần tử phân biệt (1, 2, 3, 4, 5)
    };

    sort(q.begin(), q.end());

    vector<int> ketQua(q.size());
    int currL = 0, currR = -1;

    for (const auto &query : q)
    {
        int L = query.L;
        int R = query.R;

        // Dịch chuyển con trỏ R sang phải
        while (currR < R)
        {
            currR++;
            them(a[currR]);
        }
        // Dịch chuyển con trỏ R sang trái
        while (currR > R)
        {
            xoa(a[currR]);
            currR--;
        }
        // Dịch chuyển con trỏ L sang trái
        while (currL > L)
        {
            currL--;
            them(a[currL]);
        }
        // Dịch chuyển con trỏ L sang phải
        while (currL < L)
        {
            xoa(a[currL]);
            currL++;
        }

        ketQua[query.id] = soPhanTuPhanBiet;
    }

    cout << "--- KET QUA THUAT TOAN MO ---\n";
    for (int i = 0; i < ketQua.size(); i++)
    {
        cout << "Truy van " << i << ": " << ketQua[i] << " phan tu phan biet.\n";
    }
    return 0;
}