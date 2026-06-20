#include <iostream>
#include <climits> // Thư viện để dùng INT_MIN
using namespace std;

int main() {
    int n;
    cout << "Nhap so luong phan tu (n >= 2): ";
    cin >> n;

    if (n < 2) {
        cout << "Mang phai co it nhat 2 phan tu!" << endl;
        return 1;
    }

    int a[n];
    cout << "Nhap cac phan tu cua mang: ";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int max1 = INT_MIN; // Lớn nhất
    int max2 = INT_MIN; // Lớn thứ hai

    for (int i = 0; i < n; i++) {
        if (a[i] > max1) {
            max2 = max1; // Cập nhật max2 thành max1 cũ
            max1 = a[i]; // Cập nhật max1 mới
        } else if (a[i] > max2 && a[i] != max1) {
            max2 = a[i]; // Cập nhật max2 nếu nó nhỏ hơn max1 nhưng lớn hơn max2 cũ
        }
    }

    if (max2 == INT_MIN) {
        cout << "Khong co phan tu lon thu hai." << endl;
    } else {
        cout << "Phan tu lon thu hai trong mang la: " << max2 << endl;
    }

    return 0;
}