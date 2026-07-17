#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 10005;
vector<int> adj[MAXN];
int trongSo[MAXN];
int dp[MAXN][2]; // dp[u][0]: Max khi không chọn u, dp[u][1]: Max khi có chọn u

void dfsTreeDP(int u, int p)
{
    dp[u][0] = 0;
    dp[u][1] = trongSo[u];

    for (int v : adj[u])
    {
        if (v != p)
        {
            dfsTreeDP(v, u); // Đệ quy tính toán cho con trước

            // Nếu không chọn u, con v chọn hay không chọn đều được, ta lấy cái lớn hơn
            dp[u][0] += max(dp[v][0], dp[v][1]);

            // Nếu có chọn u, bắt buộc không được chọn con v
            dp[u][1] += dp[v][0];
        }
    }
}

int main()
{
    int n = 5;
    // Gán trọng số cho các đỉnh 1 đến 5
    trongSo[1] = 10;
    trongSo[2] = 20;
    trongSo[3] = 15;
    trongSo[4] = 30;
    trongSo[5] = 25;

    // Dựng cấu trúc cây
    adj[1].push_back(2);
    adj[2].push_back(1);
    adj[1].push_back(3);
    adj[3].push_back(1);
    adj[2].push_back(4);
    adj[4].push_back(2);
    adj[2].push_back(5);
    adj[5].push_back(2);

    // Chạy Tree DP bắt đầu từ gốc là đỉnh 1
    dfsTreeDP(1, 0);

    // Kết quả lớn nhất tại gốc có thể là chọn gốc hoặc không chọn gốc
    int ans = max(dp[1][0], dp[1][1]);

    cout << "--- KET QUA TREE DP (MAX INDEPENDENT SET) ---\n";
    cout << "Tong trong so lon nhat cua tap doc lap la: " << ans << endl;
    return 0;
}