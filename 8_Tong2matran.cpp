#include <iostream>
using namespace std;

int main()
{
    int m, n;
    cout << "Nhap so dong m va so cot n: ";
    cin >> m >> n;

    int A[m][n], B[m][n], C[m][n];

    cout << "Nhap ma tran A:\n";
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i][j];
        }
    }

    cout << "Nhap ma tran B:\n";
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> B[i][j];
        }
    }

    // Tính tổng hai ma trận
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    cout << "Ma tran tong C la:\n";
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << C[i][j] << " ";
        }
        cout << endl; // Xuống dòng khi hết một hàng
    }

    return 0;
}