#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int baiToanCaiTui(int W, vector<int> &w, vector<int> &v, int n)
{
    // Tạo bảng phương án ma trận (n + 1) x (W + 1) điền sẵn số 0
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Xây dựng bảng dp từ dưới lên
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            if (w[i - 1] <= j)
            {
                // Chọn giải pháp tối ưu nhất giữa: Lấy đồ hoặc Không lấy đồ
                dp[i][j] = max(v[i - 1] + dp[i - 1][j - w[i - 1]], dp[i - 1][j]);
            }
            else
            {
                // Nếu món đồ nặng hơn sức chứa hiện tại j của túi, không lấy
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n][W]; // Kết quả tối ưu nằm ở ô cuối cùng
}

int main()
{
    vector<int> v = {60, 100, 120}; // Giá trị các món đồ
    vector<int> w = {10, 20, 30};   // Trọng lượng tương ứng
    int W = 50;                     // Sức chứa tối đa của túi
    int n = v.size();

    cout << "Gia tri lon nhat co the lay duoc: " << baiToanCaiTui(W, w, v, n) << endl;

    return 0;
}