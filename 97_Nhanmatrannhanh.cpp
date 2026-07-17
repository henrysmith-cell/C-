#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Matrix;

// Các hàm bổ trợ để cộng, trừ ma trận
Matrix add(const Matrix &A, const Matrix &B)
{
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

Matrix subtract(const Matrix &A, const Matrix &B)
{
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

// Thuật toán Strassen nhân hai ma trận kích thước N x N (với N là lũy thừa của 2)
Matrix strassen(const Matrix &A, const Matrix &B)
{
    int n = A.size();
    if (n == 1)
    {
        return {{A[0][0] * B[0][0]}};
    }

    int k = n / 2;
    Matrix a11(k, vector<int>(k)), a12(k, vector<int>(k)), a21(k, vector<int>(k)), a22(k, vector<int>(k));
    Matrix b11(k, vector<int>(k)), b12(k, vector<int>(k)), b21(k, vector<int>(k)), b22(k, vector<int>(k));

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i + k][j];
            a21[i][j] = A[i][j + k];
            a22[i][j] = A[i + k][j + k];
            b11[i][j] = B[i][j];
            b12[i][j] = B[i + k][j];
            b21[i][j] = B[i][j + k];
            b22[i][j] = B[i + k][j + k];
        }
    }

    // Tính toán 7 ma trận trung gian P1 đến P7 bằng 7 phép nhân đệ quy
    Matrix P1 = strassen(a11, subtract(b12, b22));
    Matrix P2 = strassen(add(a11, a12), b22);
    Matrix P3 = strassen(add(a21, a22), b11);
    Matrix P4 = strassen(a22, subtract(b21, b11));
    Matrix P5 = strassen(add(a11, a22), add(b11, b22));
    Matrix P6 = strassen(subtract(a12, a22), add(b21, b22));
    Matrix P7 = strassen(subtract(a11, a21), add(b11, b12));

    // Tổ hợp lại các ma trận con để ra kết quả
    Matrix c11 = add(subtract(add(P5, P4), P2), P6);
    Matrix c12 = add(P1, P2);
    Matrix c21 = add(P3, P4);
    Matrix c22 = subtract(subtract(add(P5, P1), P3), P7);

    Matrix C(n, vector<int>(n));
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i][j] = c11[i][j];
            C[i + k][j] = c12[i][j];
            C[i][j + k] = c21[i][j];
            C[i + k][j + k] = c22[i][j];
        }
    }
    return C;
}

int main()
{
    Matrix A = {{1, 2}, {3, 4}};
    Matrix B = {{5, 6}, {7, 8}};

    Matrix C = strassen(A, B);

    cout << "--- KET QUA NHAN MA TRAN STRASSEN ---\n";
    for (int i = 0; i < C.size(); i++)
    {
        for (int j = 0; j < C[i].size(); j++)
        {
            cout << C[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}