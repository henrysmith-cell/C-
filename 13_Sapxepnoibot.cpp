#include <iostream>
using namespace std;

void bubbleSort(int a[], int n)
{
    // Vòng lặp ngoài kiểm soát số lượt quét
    for (int i = 0; i < n - 1; i++)
    {
        bool coDoiCho = false; // Tối ưu: kiểm tra xem lượt này có cần đổi chỗ không

        // Vòng lặp trong so sánh các cặp phần tử cạnh nhau
        for (int j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                // Đổi chỗ nếu phần tử trước lớn hơn phần tử sau
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                coDoiCho = true;
            }
        }

        // Nếu suốt một lượt quét không có phần tử nào đổi chỗ -> mảng đã sắp xếp xong
        if (!coDoiCho)
            break;

        // In mảng ra để theo dõi tiến trình
        cout << "Luot thu " << i + 1 << ": ";
        for (int k = 0; k < n; k++)
            cout << a[k] << " ";
        cout << endl;
    }
}

int main()
{
    int n;
    cout << "Nhap so phan tu n: ";
    cin >> n;

    int a[n];
    cout << "Nhap cac phan tu cua mang: ";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    cout << "\n--- Qua trinh sap xep ---\n";
    bubbleSort(a, n);

    cout << "\nMang sau khi sap xep hoan chinh: ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;

    return 0;
}