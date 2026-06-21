#include <iostream>
using namespace std;

// Hàm tìm UCLN sử dụng thuật toán Euclid (Đệ quy)
long long timUCLN(long long a, long long b) {
    if (b == 0) return a;
    return timUCLN(b, a % b);
}

// Hàm tìm BCNN dựa vào công thức: (a * b) / UCLN(a, b)
long long timBCNN(long long a, long long b, long long ucln) {
    return (a * b) / ucln;
}

int main() {
    long long a, b;
    cout << "Nhap hai so nguyen duong a va b: ";
    cin >> a >> b;

    if (a <= 0 || b <= 0) {
        cout << "Vui long nhap so nguyen duong!" << endl;
        return 1;
    }

    long long ucln = timUCLN(a, b);
    long long bcnn = timBCNN(a, b, ucln);

    cout << "Uoc chung lon nhat (UCLN): " << ucln << endl;
    cout << "Boi chung nho nhat (BCNN): " << bcnn << endl;

    return 0;
}