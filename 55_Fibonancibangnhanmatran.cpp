#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 1e9 + 7;

// Hàm nhân hai ma trận 2x2
vector<vector<long long>> nhanMaTran(vector<vector<long long>> &A, vector<vector<long long>> &B)
{
    vector<vector<long long>> C(2, vector<long long>(2, 0));
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

// Hàm tính lũy thừa nhị phân của ma trận 2x2
vector<vector<long long>> luyThuaMaTran(vector<vector<long long>> A, long long p)
{
    vector<vector<long long>> Res = {{1, 0}, {0, 1}}; // Ma trận đơn vị
    while (p > 0)
    {
        if (p & 1)
            Res = nhanMaTran(Res, A);
        A = nhanMaTran(A, A);
        p >>= 1;
    }
    return Res;
}

long long tinhFibonacci(long long n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    // Ma trận cơ sở T
    vector<vector<long long>> T = {{1, 1}, {1, 0}};
    T = luyThuaMaTran(T, n - 1);

    return T[0][0]; // F(n) nằm ở ô [0][0] của ma trận T^(n-1)
}

int main()
{
    long long n = 1000000000000000000LL; // 10^18
    cout << "So Fibonacci thu " << n << " (chia du 10^9+7) la: "
         << tinhFibonacci(n) << endl;
    return 0;
}