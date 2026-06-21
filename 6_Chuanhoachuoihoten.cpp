#include <iostream>
#include <string>
#include <sstream> // Thư viện dùng StringIO để tách từ
using namespace std;

int main() {
    string s;
    cout << "Nhap ho ten can chuan hoa: ";
    getline(cin, s);

    stringstream ss(s); // Đưa chuỗi vào luồng stream
    string tu;
    string ketQua = "";

    // Tự động tách các từ dựa vào khoảng trắng (bỏ qua mọi khoảng trắng thừa)
    while (ss >> tu) {
        // Chuyển chữ cái đầu thành viết hoa
        if (tu[0] >= 'a' && tu[0] <= 'z') {
            tu[0] = tu[0] - 32; 
        }
        
        // Chuyển các chữ cái sau thành viết thường
        for (int i = 1; i < tu.length(); i++) {
            if (tu[i] >= 'A' && tu[i] <= 'Z') {
                tu[i] = tu[i] + 32;
            }
        }

        // Nối từ vào chuỗi kết quả
        ketQua += tu + " ";
    }

    // Xóa khoảng trắng thừa ở cuối cùng chuỗi kết quả
    if (!ketQua.empty()) {
        ketQua.pop_back();
    }

    cout << "Chuoi sau khi chuan hoa: \"" << ketQua << "\"" << endl;

    return 0;
}