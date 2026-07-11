#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<long long>> MaTran;
const int MOD = 1e9 + 7;

// Hàm nhân hai ma trận đại số
MaTran nhanMaTran(const MaTran &A, const MaTran &B)
{
    int n = A.size();
    MaTran C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

// Hàm tính lũy thừa nhị phân ma trận bậc K: A^K
MaTran luyThuaMaTran(MaTran A, long long K)
{
    int n = A.size();
    // Khởi tạo ma trận đơn vị I
    MaTran ketQua(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++)
        ketQua[i][i] = 1;

    while (K > 0)
    {
        if (K % 2 == 1)
            ketQua = nhanMaTran(ketQua, A);
        A = nhanMaTran(A, A);
        K /= 2;
    }
    return ketQua;
}

int main()
{
    int n = 3;
    long long K = 5; // Tìm số đường đi có độ dài đúng 5 bước

    // Đồ thị dạng ma trận kề: 0->1, 1->2, 2->0 và có cạnh khép kín tự nối
    MaTran adj = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 0}};

    // Nâng ma trận kề lên lũy thừa K
    MaTran adjMuK = luyThuaMaTran(adj, K);

    cout << "--- SO DUONG DI CO DO DAI K = " << K << " ---\n";
    cout << "Tu dinh 0 den dinh 2 co: " << adjMuK[0][2] << " duong di thoa man.\n";

    return 0;
}