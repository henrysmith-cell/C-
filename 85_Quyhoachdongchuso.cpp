#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

string S_num;
int mucTieuSum;
long long dp[20][180][2]; // dp[vị trí][tổng chữ số hiện tại][giới hạn chặt hay không]

// Hàm đệ quy có nhớ để duyệt chữ số
long long deQuyDigitDP(int idx, int sum, bool limits)
{
    // Đi hết độ dài số
    if (idx == S_num.length())
    {
        return (sum == mucTieuSum) ? 1 : 0;
    }

    // Nếu đã tính toán trạng thái này rồi thì trả về luôn
    if (dp[idx][sum][limits] != -1)
    {
        return dp[idx][sum][limits];
    }

    long long ketQua = 0;
    // Xác định chữ số lớn nhất có thể điền ở vị trí hiện tại
    int chuSoMax = limits ? (S_num[idx] - '0') : 9;

    for (int chuSo = 0; chuSo <= chuSoMax; chuSo++)
    {
        // Trạng thái giới hạn tiếp theo sẽ chặt nếu hiện tại đang chặt và ta chọn chữ số kịch kim
        bool limitsTiepTheo = limits && (chuSo == chuSoMax);
        ketQua += deQuyDigitDP(idx + 1, sum + chuSo, limitsTiepTheo);
    }

    return dp[idx][sum][limits] = ketQua;
}

// Tính số lượng số từ 0 đến N có tổng các chữ số bằng mucTieuSum
long long tinh(long long N)
{
    if (N < 0)
        return 0;
    S_num = to_string(N);
    memset(dp, -1, sizeof(dp));
    return deQuyDigitDP(0, 0, true);
}

int main()
{
    long long A = 10, B = 100;
    mucTieuSum = 9; // Tìm các số có tổng chữ số bằng 9 (như 18, 27, 36, 45, 54, 63, 72, 81, 90...)

    // Kết quả trong đoạn [A, B] = tinh(B) - tinh(A - 1)
    long long ans = tinh(B) - tinh(A - 1);

    cout << "--- KET QUA DIGIT DP ---\n";
    cout << "So luong so trong doan [" << A << ", " << B << "] co tong chu so bang " << mucTieuSum << " la: " << ans << endl;
    return 0;
}