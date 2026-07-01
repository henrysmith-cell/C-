#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

string S;
long long dp[20][2]; // dp[vị trí chữ số][biến giới hạn tight]

// Hàm đệ quy Digit DP
long long tinhDigitDP(int index, bool tight)
{
    // Đi đến chữ số cuối cùng thành công tức là tìm được 1 số hợp lệ
    if (index == S.length())
        return 1;

    // Nếu trạng thái này đã được tính toán trước đó thì trả về luôn
    if (dp[index][tight] != -1)
        return dp[index][tight];

    long long ketQua = 0;
    // Xác định giới hạn của chữ số tại vị trí 'index'
    int gioiHan = tight ? (S[index] - '0') : 9;

    for (int chuSo = 0; chuSo <= gioiHan; chuSo++)
    {
        if (chuSo == 4)
            continue; // Bỏ qua nếu gặp chữ số 4 theo yêu cầu đề bài

        // Chữ số tiếp theo sẽ bị thắt chặt (tight) nếu chữ số hiện tại chạm giới hạn
        bool tightTiepTheo = tight && (chuSo == gioiHan);
        ketQua += tinhDigitDP(index + 1, tightTiepTheo);
    }

    return dp[index][tight] = ketQua; // Lưu lại kết quả cấu trúc cấu hình
}

long long giaiBaiToan(long long n)
{
    if (n < 0)
        return 0;
    S = to_string(n);
    memset(dp, -1, sizeof(dp));      // Khởi tạo mảng dp toàn bộ là -1
    return tinhDigitDP(0, true) - 1; // Trừ đi số 0 (vì đề bài yêu cầu từ 1 đến N)
}

int main()
{
    long long n = 15;
    cout << "So luong so tu 1 den " << n << " khong chua chu so 4 la: "
         << giaiBaiToan(n) << endl;
    return 0;
}