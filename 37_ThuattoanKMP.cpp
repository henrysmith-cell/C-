#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Hàm tiền xử lý tạo mảng Pi (LPS - Longest Prefix which is also Suffix)
vector<int> tinhMangLPS(string P)
{
    int m = P.length();
    vector<int> lps(m, 0);
    int len = 0; // Chiều dài của tiền tố khớp trước đó
    int i = 1;

    while (i < m)
    {
        if (P[i] == P[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
                len = lps[len - 1];
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

void KMP(string T, string P)
{
    int n = T.length();
    int m = P.length();
    vector<int> lps = tinhMangLPS(P);

    int i = 0; // Chỉ số cho chuỗi T
    int j = 0; // Chỉ số cho chuỗi P

    while (i < n)
    {
        if (P[j] == T[i])
        {
            i++;
            j++;
        }

        if (j == m)
        {
            cout << "Tim thay chuoi mau tai index: " << i - j << "\n";
            j = lps[j - 1]; // Chuẩn bị cho lần khớp tiếp theo
        }
        else if (i < n && P[j] != T[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

int main()
{
    string vanBan = "ABABDABACDABABCABAB";
    string mau = "ABABCABAB";
    cout << "Van ban: " << vanBan << "\nMau: " << mau << "\n";
    KMP(vanBan, mau);
    return 0;
}