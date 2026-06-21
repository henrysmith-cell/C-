#include <iostream>
#include <cmath> // Thư viện để dùng hàm sqrt() (căn bậc 2)
using namespace std;

bool laSoNguyenTo(int n) {
    if (n <= 1) return false; // Số <= 1 không phải số nguyên tố
    if (n <= 3) return true;  // Số 2 và 3 là số nguyên tố

    // Nếu chia hết cho 2 hoặc 3 thì không phải số nguyên tố
    if (n % 2 == 0 || n % 3 == 0) return false;

    // Kiểm tra các ước từ 5 đến căn bậc hai của n
    // Các số nguyên tố lớn hơn 3 đều có dạng 6k +/- 1
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    cout << "Nhap so nguyen n: ";
    cin >> n;

    if (laSoNguyenTo(n)) {
        cout << n << " la so nguyen to." << endl;
    } else {
        cout << n << " khong phai la so nguyen to." << endl;
    }

    return 0;
}