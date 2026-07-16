#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int kichThuocKhoi;

struct TruyVan
{
    int l, r, id;
    // Sắp xếp các truy vấn theo khối chia căn của L, nếu cùng khối thì xếp theo R
    bool operator<(const TruyVan &khac) const
    {
        int khongU = l / kichThuocKhoi;
        int khongV = khac.l / kichThuocKhoi;
        if (khongU != khongV)
            return khongU < khongV;
        return (khongU & 1) ? (r < khac.r) : (r > khac.r); // Tối ưu hóa đường đi ziczac
    }
};

vector<int> A;
vector<int> demTanSuat;
int soPhanTuPhanBiet = 0;

void add(int idx)
{
    if (demTanSuat[A[idx]] == 0)
    {
        soPhanTuPhanBiet++;
    }
    demTanSuat[A[idx]]++;
}

void remove(int idx)
{
    demTanSuat[A[idx]]--;
    if (demTanSuat[A[idx]] == 0)
    {
        soPhanTuPhanBiet--;
    }
}

int main()
{
    int n = 8;
    A = {1, 1, 2, 1, 3, 4, 5, 2};
    kichThuocKhoi = sqrt(n);

    vector<TruyVan> queries = {
        {0, 4, 0}, // Đoạn [1, 1, 2, 1, 3] -> 3 số phân biệt (1, 2, 3)
        {1, 3, 1}, // Đoạn [1, 2, 1] -> 2 số phân biệt (1, 2)
        {2, 7, 2}  // Đoạn [2, 1, 3, 4, 5, 2] -> 5 số phân biệt (1, 2, 3, 4, 5)
    };

    sort(queries.begin(), queries.end());
    demTanSuat.assign(100, 0);
    vector<int> ketQua(queries.size());

    int curL = 0, curR = -1;
    for (auto q : queries)
    {
        // Dịch chuyển con trỏ R sang phải
        while (curR < q.r)
            add(++curR);
        // Dịch chuyển con trỏ R sang trái
        while (curR > q.r)
            remove(curR--);
        // Dịch chuyển con trỏ L sang trái
        while (curL > q.l)
            add(--curL);
        // Dịch chuyển con trỏ L sang phải
        while (curL < q.l)
            remove(curL++);

        ketQua[q.id] = soPhanTuPhanBiet;
    }

    cout << "--- KET QUA THUAT TOAN MO ---\n";
    for (int i = 0; i < ketQua.size(); i++)
    {
        cout << "Truy van " << i << ": " << ketQua[i] << " phan tu phan biet\n";
    }
    return 0;
}