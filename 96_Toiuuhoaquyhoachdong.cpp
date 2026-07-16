#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const long long INF = 1e15;

// Bài toán cắt thanh gỗ: Tìm chi phí nhỏ nhất để cắt thanh gỗ tại các điểm cho trước
long long solveKnuthOpt(int n, const vector<int> &cuts)
{
    int m = cuts.size();
    vector<vector<long long>> dp(m, vector<long long>(m, 0));
    vector<vector<int>> opt(m, vector<int>(m, 0));

    // Khởi tạo trường hợp cơ sở cho các đoạn độ dài 1
    for (int i = 0; i < m - 1; i++)
    {
        opt[i][i + 1] = i;
    }

    // Duyệt theo độ dài đoạn
    for (int len = 2; len < m; len++)
    {
        for (int i = 0; i + len < m; i++)
        {
            int j = i + len;
            dp[i][j] = INF;

            // Giới hạn vùng tìm kiếm điểm k tối ưu nhờ Knuth Optimization
            int k_min = opt[i][j - 1];
            int k_max = opt[i + 1][j];

            for (int k = k_min; k <= k_max; k++)
            {
                if (k >= i && k < j)
                {
                    long long val = dp[i][k] + dp[k + 1][j] + (cuts[j] - cuts[i]);
                    if (val < dp[i][j])
                    {
                        dp[i][j] = val;
                        opt[i][j] = k;
                    }
                }
            }
        }
    }
    return dp[0][m - 1];
}

int main()
{
    int doDaiThanhGo = 10;
    // Các điểm cần cắt trên thanh gỗ, bổ sung điểm đầu (0) và cuối (L)
    vector<int> cuts = {0, 2, 4, 7, 10};

    long long chiPhiMin = solveKnuthOpt(doDaiThanhGo, cuts);

    cout << "--- KET QUA KNUTH DP OPTIMIZATION ---\n";
    cout << "Chi phi cat thanh go nho nhat la: " << chiPhiMin << endl; // Kết quả: 20
    return 0;
}