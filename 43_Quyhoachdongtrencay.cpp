#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Hàm DFS trả về độ dài đường đi dài nhất từ nút u xuống các lá của cây con
int tinhDuongKinh(int u, int p, vector<vector<int>> &adj, int &duongKinhMax)
{
    int max1 = 0, max2 = 0; // Lưu 2 nhánh dài nhất đi xuống từ u

    for (int v : adj[u])
    {
        if (v == p)
            continue; // Bỏ qua nút cha tránh lặp vô hạn

        int chieuCaoNhanh = tinhDuongKinh(v, u, adj, duongKinhMax) + 1;

        // Cập nhật 2 chiều cao lớn nhất
        if (chieuCaoNhanh > max1)
        {
            max2 = max1;
            max1 = chieuCaoNhanh;
        }
        else if (chieuCaoNhanh > max2)
        {
            max2 = chieuCaoNhanh;
        }
    }

    // Đường kính đi qua đỉnh u hiện tại sẽ bằng tổng 2 nhánh dài nhất
    duongKinhMax = max(duongKinhMax, max1 + max2);

    return max1; // Trả về nhánh dài nhất cho nút cha sử dụng
}

int main()
{
    int n = 6;
    vector<vector<int>> adj(n);

    // Tạo các cạnh của cây
    auto themCanh = [&](int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };
    themCanh(0, 1);
    themCanh(1, 2);
    themCanh(1, 3);
    themCanh(3, 4);
    themCanh(4, 5);

    int duongKinhMax = 0;
    tinhDuongKinh(0, -1, adj, duongKinhMax);

    cout << "Duong kinh lon nhat cua cay la: " << duongKinhMax << endl;
    return 0;
}