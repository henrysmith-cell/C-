#include <iostream>
#include <vector>
using namespace std;

struct FenwickTree
{
    int n;
    vector<int> bit;

    FenwickTree(int n)
    {
        this->n = n;
        bit.assign(n + 1, 0); // BIT dùng mảng 1-indexed (bắt đầu từ 1)
    }

    // Hàm cộng thêm giá trị 'val' vào phần tử tại vị trí 'idx'
    void update(int idx, int val)
    {
        for (; idx <= n; idx += idx & -idx)
        {
            bit[idx] += val;
        }
    }

    // Hàm tính tổng từ vị trí 1 đến vị trí 'idx'
    int query(int idx)
    {
        int sum = 0;
        for (; idx > 0; idx -= idx & -idx)
        {
            sum += bit[idx];
        }
        return sum;
    }

    // Hàm tính tổng đoạn [L, R]
    int queryDoan(int L, int R)
    {
        return query(R) - query(L - 1);
    }
};

int main()
{
    vector<int> a = {0, 3, 2, -1, 6, 5}; // Xét mảng 1-indexed, a[0] bỏ qua
    int n = a.size() - 1;

    FenwickTree tree(n);
    for (int i = 1; i <= n; i++)
    {
        tree.update(i, a[i]);
    }

    cout << "Tong doan [2, 4] ban dau: " << tree.queryDoan(2, 4) << "\n"; // 2 + (-1) + 6 = 7

    // Cập nhật: tăng phần tử tại index 3 lên 5 đơn vị (từ -1 thành 4)
    tree.update(3, 5);
    cout << "Tong doan [2, 4] sau khi cap nhat: " << tree.queryDoan(2, 4) << "\n"; // 2 + 4 + 6 = 12

    return 0;
}