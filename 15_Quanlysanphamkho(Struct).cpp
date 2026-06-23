#include <iostream>
#include <string>
using namespace std;

struct SanPham
{
    string maSP;
    string tenSP;
    int soLuong;
    double donGia;
};

int main()
{
    int n;
    cout << "Nhap so luong loai san pham: ";
    cin >> n;

    SanPham ds[n];
    double tongGiaTriKho = 0;

    for (int i = 0; i < n; i++)
    {
        cout << "\nNhap thong tin san pham thu " << i + 1 << ":\n";
        cout << "Ma SP: ";
        cin >> ds[i].maSP;
        cin.ignore();
        cout << "Ten SP: ";
        getline(cin, ds[i].tenSP);
        cout << "So luong: ";
        cin >> ds[i].soLuong;
        cout << "Don gia: ";
        cin >> ds[i].donGia;

        // Cộng dồn vào tổng giá trị kho hàng
        tongGiaTriKho += (ds[i].soLuong * ds[i].donGia);
    }

    // Tìm sản phẩm có giá trị tồn kho lớn nhất
    int viTriMax = 0;
    double giaTriMax = ds[0].soLuong * ds[0].donGia;

    for (int i = 1; i < n; i++)
    {
        double giaTriHienTai = ds[i].soLuong * ds[i].donGia;
        if (giaTriHienTai > giaTriMax)
        {
            giaTriMax = giaTriHienTai;
            viTriMax = i;
        }
    }

    cout << "\n----------------------------------------\n";
    cout << "-> Tong gia tri cua toan bo kho hang: " << tongGiaTriKho << " VND\n";
    cout << "-> San pham co gia tri ton kho lon nhat la:\n";
    cout << "   + Ma SP: " << ds[viTriMax].maSP << endl;
    cout << "   + Ten SP: " << ds[viTriMax].tenSP << endl;
    cout << "   + Gia tri ton: " << giaTriMax << " VND" << endl;

    return 0;
}