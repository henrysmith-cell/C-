#include <iostream>
#include <cmath>
using namespace std;

class PhanSo
{
private:
    int tuSo, mauSo;

    // Hàm bổ trợ tìm UCLN để rút gọn phân số
    int timUCLN(int a, int b)
    {
        if (b == 0)
            return abs(a);
        return timUCLN(b, a % b);
    }

public:
    // Phương thức nhập
    void nhap()
    {
        cout << "Nhap tu so: ";
        cin >> tuSo;
        do
        {
            cout << "Nhap mau so (khac 0): ";
            cin >> mauSo;
        } while (mauSo == 0);
    }

    // Phương thức rút gọn
    void rutGon()
    {
        int ucln = timUCLN(tuSo, mauSo);
        tuSo /= ucln;
        mauSo /= ucln;
        if (mauSo < 0)
        { // Đẩy dấu trừ lên tử nếu mẫu âm
            tuSo = -tuSo;
            mauSo = -mauSo;
        }
    }

    // Phương thức in
    void xuat()
    {
        if (mauSo == 1)
            cout << tuSo << endl;
        else
            cout << tuSo << "/" << mauSo << endl;
    }

    // Phương thức cộng hai phân số (trả về một đối tượng PhanSo mới)
    PhanSo cong(PhanSo psKhac)
    {
        PhanSo ketQua;
        ketQua.tuSo = this->tuSo * psKhac.mauSo + psKhac.tuSo * this->mauSo;
        ketQua.mauSo = this->mauSo * psKhac.mauSo;
        ketQua.rutGon(); // Rút gọn luôn kết quả
        return ketQua;
    }
};

int main()
{
    PhanSo p1, p2, tong;

    cout << "--- Nhap phan so thu nhat ---\n";
    p1.nhap();

    cout << "--- Nhap phan so thu hai ---\n";
    p2.nhap();

    cout << "\nPhan so 1 sau khi rut gon: ";
    p1.rutGon();
    p1.xuat();

    cout << "Phan so 2 sau khi rut gon: ";
    p2.rutGon();
    p2.xuat();

    tong = p1.cong(p2);
    cout << "Tong hai phan so la: ";
    tong.xuat();

    return 0;
}