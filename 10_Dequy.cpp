#include <iostream>
using namespace std;

// Cách 1: Sử dụng Đệ quy (Dễ viết nhưng chạy chậm với n lớn)
long long fiboDeQuy(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return fiboDeQuy(n - 1) + fiboDeQuy(n - 2);
}

// Cách 2: Sử dụng Vòng lặp / Khử đệ quy (Chạy cực nhanh)
long long fiboVongLap(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    long long f0 = 0, f1 = 1, fn;
    for (int i = 2; i <= n; i++)
    {
        fn = f0 + f1;
        f0 = f1;
        f1 = fn;
    }
    return fn;
}

int main()
{
    int n;
    cout << "Nhap n: ";
    cin >> n;

    if (n < 0)
    {
        cout << "Vui long nhap n >= 0" << endl;
        return 1;
    }

    // Khuyên dùng vòng lặp nếu n > 40 để tránh bị treo máy do đệ quy quá nặng
    cout << "So Fibonacci thu " << n << " (Tinh bang vong lap) la: " << fiboVongLap(n) << endl;

    if (n <= 40)
    {
        cout << "So Fibonacci thu " << n << " (Tinh bang de quy) la: " << fiboDeQuy(n) << endl;
    }

    return 0;
}