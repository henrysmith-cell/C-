#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "Nhap cap ma tran n: ";
    cin >> n;

    int matrix[n][n];
    int giaTri = 1;

    // Khởi tạo 4 biên của ma trận
    int dongDau = 0, dongCuoi = n - 1;
    int cotDau = 0, cotCuoi = n - 1;

    while (giaTri <= n * n)
    {
        // 1. Chạy từ trái sang phải ở dòng đầu tiên
        for (int i = cotDau; i <= cotCuoi; i++)
        {
            matrix[dongDau][i] = giaTri++;
        }
        dongDau++; // Thu hẹp biên trên

        // 2. Chạy từ trên xuống dưới ở cột cuối cùng
        for (int i = dongDau; i <= dongCuoi; i++)
        {
            matrix[i][cotCuoi] = giaTri++;
        }
        cotCuoi--; // Thu hẹp biên phải

        // 3. Chạy từ phải sang trái ở dòng cuối cùng (nếu còn dòng)
        if (dongDau <= dongCuoi)
        {
            for (int i = cotCuoi; i >= cotDau; i--)
            {
                matrix[dongCuoi][i] = giaTri++;
            }
            dongCuoi--; // Thu hẹp biên dưới
        }

        // 4. Chạy từ dưới lên trên ở cột đầu tiên (nếu còn cột)
        if (cotDau <= cotCuoi)
        {
            for (int i = dongCuoi; i >= dongDau; i--)
            {
                matrix[i][cotDau] = giaTri++;
            }
            cotDau++; // Thu hẹp biên trái
        }
    }

    // In ma trận kết quả
    cout << "Ma tran xoan oc:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matrix[i][j] << "\t"; // Dùng \t để căn đều cột
        }
        cout << endl;
    }

    return 0;
}