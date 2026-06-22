#include <iostream>
using namespace std;

// Hàm tìm kiếm nhị phân trả về chỉ số phần tử, nếu không thấy trả về -1
int binarySearch(int a[], int n, int x)
{
    int left = 0;
    int right = n - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2; // Tìm phần tử ở giữa (tránh tràn số)

        if (a[mid] == x)
        {
            return mid; // Tìm thấy x tại vị trí mid
        }

        if (a[mid] < x)
        {
            left = mid + 1; // x nằm ở nửa bên phải
        }
        else
        {
            right = mid - 1; // x nằm ở nửa bên trái
        }
    }
    return -1; // Không tìm thấy
}

int main()
{
    int n, x;
    cout << "Nhap so phan tu n: ";
    cin >> n;

    int a[n];
    cout << "Nhap mang da duoc sap xep tang dan: ";
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    cout << "Nhap gia tri x can tim: ";
    cin >> x;

    int ketQua = binarySearch(a, n, x);

    if (ketQua != -1)
    {
        cout << "Tim thay " << x << " tai index: " << ketQua << endl;
    }
    else
    {
        cout << "Khong tim thay " << x << " trong mang." << endl;
    }

    return 0;
}