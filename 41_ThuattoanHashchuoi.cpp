#include <iostream>
#include <string>
#include <vector>
using namespace std;

const long long BASE = 311;
const long long MOD = 1e9 + 7;

// Cấu trúc quản lý Hash chuỗi
struct StringHasher
{
    vector<long long> hash, powBase;

    StringHasher(string s)
    {
        int n = s.length();
        hash.resize(n + 1, 0);
        powBase.resize(n + 1, 1);

        for (int i = 0; i < n; i++)
        {
            hash[i + 1] = (hash[i] * BASE + s[i]) % MOD;
            powBase[i + 1] = (powBase[i] * BASE) % MOD;
        }
    }

    // Lấy mã Hash của chuỗi con từ index L đến R (1-indexed)
    long long getHash(int L, int R)
    {
        long long res = (hash[R] - hash[L - 1] * powBase[R - L + 1]) % MOD;
        if (res < 0)
            res += MOD;
        return res;
    }
};

int main()
{
    string s = "abcxyzabc";
    StringHasher hasher(s);

    // So sánh đoạn "abc" đầu tiên (từ index 1 đến 3) và "abc" cuối cùng (từ index 7 đến 9)
    long long hash1 = hasher.getHash(1, 3);
    long long hash2 = hasher.getHash(7, 9);

    cout << "Chuoi goc: " << s << "\n";
    cout << "Hash cua s[1..3]: " << hash1 << "\n";
    cout << "Hash cua s[7..9]: " << hash2 << "\n";

    if (hash1 == hash2)
    {
        cout << "-> Hai chuoi con giong nhau hoan toan!\n";
    }
    else
    {
        cout << "-> Hai chuoi con khac nhau!\n";
    }
    return 0;
}