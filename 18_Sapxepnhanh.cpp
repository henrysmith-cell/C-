#include <iostream>
using namespace std;

// Hàm phân hoạch (Partition) bằng chốt cuối mảng
int partition(int a[], int low, int high)
{
    int pivot = a[high]; // Chọn phần tử cuối làm chốt (pivot)
    int i = low - 1;     // Chỉ số của phần tử nhỏ hơn chốt

    for (int j = low; j < high; j++)
    {
        if (a[j] < pivot)
        {
            i++;
            swap(a[i], a[j]); // Đổi chỗ nếu nhỏ hơn chốt
        }
    }
    swap(a[i + 1], a[high]); // Đưa chốt về đúng vị trí giữa
    return i + 1;            // Trả về vị trí của chốt
}

// Hàm Quick Sort đệ quy
void quickSort(int a[], int low, int high)
{
    if (low < high)
    {
        // pi là chỉ số nơi chốt đã đứng đúng vị trí
        int pi = partition(a, low, high);

        // Sắp xếp độc lập 2 nửa bên trái và bên phải chốt
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

int main()
{
    int n;
    cout << "Nhap so phan tu: ";
    cin >> n;
    int a[n];
    cout << "Nhap cac phan tu: ";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    quickSort(a, 0, n - 1);

    cout << "Mang sau khi sap xep Quick Sort: ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;

    return 0;
}