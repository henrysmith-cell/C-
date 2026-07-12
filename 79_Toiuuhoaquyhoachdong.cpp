#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int INF = INT_MAX;

int main()
{
    // Giả sử ta cần cắt một thanh gỗ tại các điểm mốc tương đối
    vector<int> diemCat = {0, 2, 4, 7, 10};
    int m = diemCat.size();

    vector<vector<int>> dp(m, vector<int>(m, 0));
    vector<vector<int>> opt(m, vector<int>(m, 0)); // Lưu vị trí chia cắt tối ưu k

    // Khởi tạo cho các đoạn có độ dài bằng 2 (không cần cắt)
    for (int i = 0; i < m - 1; i++)
    {
        opt[i][i + 1] = i;
    }

    // Lặp qua các độ dài phân đoạn từ 2 đến m
    for (int len = 2; len < m; len++)
    {
        for (int i = 0; i < m - len; i++)
        {
            int j = i + len;
            dp[i][j] = INF;

            // Giới hạn tìm kiếm của k nhờ tối ưu hóa Knuth
            int k_start = opt[i][j - 1];
            int k_end = opt[i + 1][j];

            for (int k = k_start; k <= k_end; k++)
            {
                if (k <= i || k >= j)
                    continue;
                int costHienTai = dp[i][k] + dp[k][j] + (diemCat[j] - diemCat[i]);
                if (costHienTai < dp[i][j])
                {
                    dp[i][j] = costHienTai;
                    opt[i][j] = k; // Ghi nhận vị trí tối ưu mới
                }
            }
        }
    }

    cout << "--- KET QUA TOI UU HOA KNUTH ---\n";
    cout << "Chi phi cat thanh go toi uu nhat la: " << dp[0][m - 1] << endl;
    return 0;
}