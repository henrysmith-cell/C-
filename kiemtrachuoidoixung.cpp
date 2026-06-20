#include <iostream>
#include <string>
using namespace std;

bool kiemTraDoiXuong(string s) {
    int dau = 0;
    int cuoi = s.length() - 1;

    while (dau < cuoi) {
        // Nếu hai ký tự ở hai đầu không giống nhau thì không đối xứng
        if (s[dau] != s[cuoi]) {
            return false;
        }
        dau++;  // Tiến về phía sau
        cuoi--; // Lùi về phía trước
    }
    return true;
}

int main() {
    string s;
    cout << "Nhap vao chuoi can kiem tra: ";
    getline(cin, s); // Dùng getline để đọc được cả khoảng trắng nếu có

    if (kiemTraDoiXuong(s)) {
        cout << "\"" << s << "\" la chuoi doi xuong!" << endl;
    } else {
        cout << "\"" << s << "\" KHONG PHAI la chuoi doi xuong!" << endl;
    }

    return 0;
}