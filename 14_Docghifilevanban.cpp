#include <iostream>
#include <fstream> // Thư viện bắt buộc để thao tác với File
#include <string>
using namespace std;

int main()
{
    // 1. GHI FILE
    ofstream fileGhi("data.txt"); // Mở file để ghi (Output File Stream)

    if (fileGhi.is_open())
    {
        fileGhi << "Xin chao! Day la file giu lieu.\n";
        fileGhi << "Hoc lap trinh C++ rat thu vi.\n";
        fileGhi << "Chuc ban mot ngay tot lanh!\n";
        fileGhi.close(); // Ghi xong phai dong file
        cout << "Da ghi dữ lieu vao file data.txt thanh cong!\n";
    }
    else
    {
        cout << "Khong the tao hoac mo file de ghi!" << endl;
        return 1;
    }

    cout << "\n--- Tien hanh doc lai file ---\n";

    // 2. ĐỌC FILE
    ifstream fileDoc("data.txt"); // Mở file để đọc (Input File Stream)
    string dongVanBan;

    if (fileDoc.is_open())
    {
        // Đọc từng dòng cho đến khi hết file (End Of File)
        while (getline(fileDoc, dongVanBan))
        {
            cout << dongVanBan << endl;
        }
        fileDoc.close(); // Đọc xong cũng phải đóng file
    }
    else
    {
        cout << "Khong the mo file de doc!" << endl;
    }

    return 0;
}