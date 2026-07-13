#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;
vector<int> trongSo;
vector<vector<int>> dp;

void dfsTreeDP(int u, int p)
{
    dp[u][1] = trongSo[u]; // Nếu chọn u, khởi tạo bằng trọng số của u
    dp[u][0] = 0;          // Nếu không chọn u, khởi tạo bằng 0

    for (int v : adj[u])
    {
        if (v != p)
        {
            dfsTreeDP(v, u);
            // Nếu u được chọn, các con v CHẮC CHẮN không được chọn
            dp[u][1] += dp[v][0];
            // Nếu u KHÔNG được chọn, các con v có thể chọn hoặc không (lấy Max)
            dp[u][0] += max(dp[v][0], dp[v][1]);
        }
    }
}

int main()
{
    int n = 5;
    adj.resize(n);
    trongSo = {10, 2, 3, 7, 5};
    dp.assign(n, vector<int>(2, 0));

    // Dựng cây
    adj[0].push_back(1);
    adj[1].push_back(0);
    adj[0].push_back(2);
    adj[2].push_back(0);
    adj[1].push_back(3);
    adj[3].push_back(1);
    adj[1].push_back(4);
    adj[4].push_back(1);

    // Chạy Tree DP từ gốc là đỉnh 0
    dfsTreeDP(0, -1);

    cout << "--- KET QUA TREE DP ---\n";
    cout << "Tong trong so lon nhat co the chon la: " << max(dp[0][0], dp[0][1]) << endl;
    return 0;
}