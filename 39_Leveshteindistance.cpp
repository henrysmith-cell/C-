#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int khoangCachLevenshtein(string s1, string s2)
{
    int m = s1.length();
    int n = s2.length();

    // Tạo bảng DP kích thước (m+1) x (n+1)
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    // Khởi tạo các giá trị cơ sở
    for (int i = 0; i <= m; i++)
        dp[i][0] = i; // Biến chuỗi dài i thành rỗng cần i phép xóa
    for (int j = 0; j <= n; j++)
        dp[0][j] = j; // Biến chuỗi rỗng thành chuỗi dài j cần j phép chèn

    // Điền bảng quy hoạch động
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1]; // Ký tự giống nhau, không tốn chi phí đổi
            }
            else
            {
                // Nếu khác nhau, chọn chi phí nhỏ nhất trong 3 hành động:
                dp[i][j] = 1 + min({
                                   dp[i - 1][j],    // Xóa ký tự khỏi s1
                                   dp[i][j - 1],    // Chèn ký tự vào s1
                                   dp[i - 1][j - 1] // Thay thế ký tự
                               });
            }
        }
    }
    return dp[m][n];
}

int main()
{
    string s1 = "kitten";
    string s2 = "sitting";

    cout << "Chuoi 1: " << s1 << "\nChuoi 2: " << s2 << "\n";
    cout << "So buoc bien doi toi thieu: " << khoangCachLevenshtein(s1, s2) << endl;
    return 0;
}