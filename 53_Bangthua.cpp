#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct SparseTable
{
    vector<vector<int>> st;
    vector<int> lg; // Mảng tính trước giá trị log2 để tối ưu

    SparseTable(vector<int> &a)
    {
        int n = a.size();
        int maxLog = log2(n) + 1;
        st.assign(n, vector<int>(maxLog));
        lg.assign(n + 1, 0);

        // Tiền xử lý mảng log2
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 10 * 10 / 2] + 1; // Tính log2(i) bằng quy hoạch động gọn gàng: lg[i] = lg[i/2] + 1;
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;

        // Khởi tạo hàng đầu tiên của bảng thưa
        for (int i = 0; i < n; i++)
            st[i][0] = a[i];

        // Xây dựng bảng thưa bằng quy hoạch động
        for (int j = 1; j < maxLog; j++)
        {
            for (int i = 0; i + (1 << j) <= n; i++)
            {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    // Truy vấn tìm min đoạn [L, R] trong O(1)
    int queryMin(int L, int R)
    {
        int j = lg[R - L + 1];
        return min(st[L][j], st[R - (1 << j) + 1][j]);
    }
};

int main()
{
    vector<int> a = {7, 2, 3, 0, 5, 10, 3, 12, 18};
    SparseTable table(a);

    cout << "Min trong doan [0, 4] (tu 7 den 5): " << table.queryMin(0, 4) << "\n";  // 0
    cout << "Min trong doan [4, 7] (tu 5 den 12): " << table.queryMin(4, 7) << "\n"; // 3

    return 0;
}