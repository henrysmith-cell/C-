#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct ThietBi
{
    string maTB;
    string tenTB;
    int namSanXuat;
};

int main()
{
    // Giả lập một dòng dữ liệu đọc được từ file CSV
    string dongCSV = "TB091,May Chieu Sony 4K,2023";

    stringstream ss(dongCSV);
    string token;
    ThietBi tb;

    // Tách cột thứ nhất: Mã thiết bị
    if (getline(ss, token, ','))
    {
        tb.maTB = token;
    }

    // Tách cột thứ hai: Tên thiết bị
    if (getline(ss, token, ','))
    {
        tb.tenTB = token;
    }

    // Tách cột thứ ba: Năm sản xuất
    if (getline(ss, token, ','))
    {
        // stoi (string to integer): Hàm chuyển chuỗi thành số nguyên
        tb.namSanXuat = stoi(token);
    }

    // In thông tin đã biểu diễn dạng Struct từ CSV
    cout << "--- KET QUA PARSE DU LIEU CSV ---\n";
    cout << "Ma Thiet Bi  : " << tb.maTB << endl;
    cout << "Ten Thiet Bi : " << tb.tenTB << endl;
    cout << "Nam San Xuat : " << tb.namSanXuat << " (Tuoi tho: " << 2026 - tb.namSanXuat << " nam)\n";

    return 0;
}