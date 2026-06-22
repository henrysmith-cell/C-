#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Định nghĩa cấu trúc SinhVien
struct SinhVien
{
    string maSV;
    string hoTen;
    double diemToan;
    double diemVan;
    double diemTB;
};

int main()
{
    int n;
    cout << "Nhap so luong sinh vien: ";
    cin >> n;

    SinhVien ds[n]; // Mảng chứa n sinh viên

    // Nhập dữ liệu
    for (int i = 0; i < n; i++)
    {
        cout << "\nNhap thong tin sinh vien thu " << i + 1 << ":\n";
        cout << "Ma SV: ";
        cin >> ds[i].maSV;
        cin.ignore(); // Xóa bộ nhớ đệm trước khi dùng getline
        cout << "Ho ten: ";
        getline(cin, ds[i].hoTen);
        cout << "Diem Toan: ";
        cin >> ds[i].diemToan;
        cout << "Diem Van: ";
        cin >> ds[i].diemVan;

        // Tự động tính điểm trung bình
        ds[i].diemTB = (ds[i].diemToan + ds[i].diemVan) / 2.0;
    }

    // In danh sách sinh viên đạt yêu cầu
    cout << "\n--- DANH SACH SINH VIEN CO DIEM TB >= 5.0 ---\n";
    bool coSV = false;
    for (int i = 0; i < n; i++)
    {
        if (ds[i].diemTB >= 5.0)
        {
            cout << "MSV: " << ds[i].maSV
                 << " | Ten: " << ds[i].hoTen
                 << " | DTB: " << ds[i].diemTB << endl;
            coSV = true;
        }
    }

    if (!coSV)
    {
        cout << "Khong co sinh vien nao dat yeu cau." << endl;
    }

    return 0;
}