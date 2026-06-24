#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "Nhap so dong n: ";
    cin >> n;

    int pas[n][n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            // Các phần tử đầu và cuối dòng luôn bằng 1
            if (j == 0 || j == i)
            {
                pas[i][j] = 1;
            }
            else
            {
                // Phần tử ở giữa bằng tổng 2 phần tử dòng trên
                pas[i][j] = pas[i - 1][j - 1] + pas[i - 1][j];
            }
            cout << pas[i][j] << " ";
        }
        cout << endl; // Xuống dòng sau mỗi hàng
    }
    return 0;
}