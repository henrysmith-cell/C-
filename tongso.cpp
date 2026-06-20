#include <iostream>
using namespace std;

int main() {
    long long n;
    cout << "Nhap vao so nguyen duong n: ";
    cin >> n;

    // Kiểm tra điều kiện cơ bản
    if (n < 0) {
        cout << "Vui long nhap so duong!" << endl;
        return 1;
    }

    long long temp = n;
    int tong = 0;

    while (temp > 0) {
        tong += temp % 10; // Lấy chữ số cuối cùng
        temp /= 10;        // Xóa chữ số cuối cùng
    }

    cout << "Tong cac chu so cua " << n << " la: " << tong << endl;
    return 0;
}