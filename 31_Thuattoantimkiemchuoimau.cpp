#include <iostream>
#include <string>
using namespace std;

void timChuoiMau(string T, string P)
{
    int n = T.length();
    int m = P.length();
    bool timThay = false;

    // Vòng lặp chạy dọc chuỗi văn bản gốc T
    for (int i = 0; i <= n - m; i++)
    {
        int j;

        // Kiểm tra xem chuỗi mẫu P có khớp tại vị trí i không
        for (j = 0; j < m; j++)
        {
            if (T[i + j] != P[j])
            {
                break; // Bị lệch ký tự, dừng lại ngay
            }
        }

        // Nếu duyệt qua hết chiều dài m mà không bị ngắt giữa chừng
        if (j == m)
        {
            cout << "Tim thay chuoi mau tai index: " << i << endl;
            timThay = true;
        }
    }

    if (!timThay)
    {
        cout << "Khong tim thay chuoi mau trong van ban." << endl;
    }
}

int main()
{
    string vanBan = "ABAAABCDABCXABCHIP";
    string mau = "ABC";

    cout << "Van ban: " << vanBan << endl;
    cout << "Chuoi mau can tim: " << mau << endl;

    timChuoiMau(vanBan, mau);

    return 0;
}