#include <iostream>
#include <string>
#include <iomanip> // Thư viện để dùng setprecision định dạng số thực
using namespace std;

// Lớp cha (Base Class)
class NhanVien
{
protected: // Dùng protected để lớp con có thể truy cập trực tiếp
    string ten;
    double luongCoBan;

public:
    void nhap()
    {
        cout << "Nhap ten nhan vien: ";
        cin.ignore();
        getline(cin, ten);
        cout << "Nhap luong co ban: ";
        cin >> luongCoBan;
    }

    virtual double tinhLuong()
    { // Từ khóa virtual cho phép lớp con ghi đè (Override)
        return luongCoBan;
    }

    virtual void xuat()
    {
        cout << "Ten: " << ten << " | Luong luong: " << fixed << setprecision(0) << tinhLuong() << " VND" << endl;
    }
};

// Lớp con (Derived Class) kế thừa từ NhanVien
class NhanVienLapTrinh : public NhanVien
{
private:
    double tienOt;

public:
    void nhapDeveloper()
    {
        NhanVien::nhap(); // Gọi lại hàm nhập của lớp cha
        cout << "Nhap tien lam them gio (OT): ";
        cin >> tienOt;
    }

    // Ghi đè phương thức tính lương của lớp cha
    double tinhLuong() override
    {
        return luongCoBan + tienOt;
    }

    void xuat() override
    {
        cout << "[Dev] ";
        NhanVien::xuat(); // Gọi lại hàm xuất của lớp cha nhưng lúc này tinhLuong() đã được cập nhật
    }
};

int main()
{
    cout << "--- Nhap thong tin Nhan Vien thong thuong ---\n";
    NhanVien nv;
    nv.nhap();

    cout << "\n--- Nhap thong tin Nhan Vien Lap Trinh ---\n";
    NhanVienLapTrinh dev;
    dev.nhapDeveloper();

    cout << "\n--- KET QUA XUAT THONG TIN ---\n";
    nv.xuat();
    dev.xuat();

    return 0;
}