#include <iostream>
#include <algorithm> // Thư viện để dùng hàm sort()
using namespace std;

int main() {
    int n;
    cout << "Nhap so phan tu n: ";
    cin >> n;

    int a[n];
    cout << "Nhap cac phan tu: ";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Sắp xếp mảng tăng dần để các phần tử giống nhau nằm cạnh nhau
    sort(a, a + n);

    cout << "Ket qua thong ke:\n";
    int dem = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] == a[i - 1]) {
            dem++; // Nếu bằng phần tử trước đó thì tăng biến đếm
        } else {
            // Nếu gặp phần tử mới, in kết quả của phần tử cũ ra
            cout << "So " << a[i - 1] << " xuat hien " << dem << " lan.\n";
            dem = 1; // Reset lại biến đếm cho phần tử mới
        }
    }
    // In phần tử cuối cùng của mảng
    cout << "So " << a[n - 1] << " xuat hien " << dem << " lan.\n";

    return 0;
}