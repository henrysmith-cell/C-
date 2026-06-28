#include <iostream>
#include <vector>
using namespace std;

void doiTien(int s, vector<int> &menhGia)
{
    cout << "So tien " << s << " duoc doi thanh:\n";

    for (int i = 0; i < menhGia.size(); i++)
    {
        // Lấy số lượng tờ tiền tối đa có thể của mệnh giá hiện tại
        int soTo = s / menhGia[i];

        if (soTo > 0)
        {
            cout << "- " << soTo << " to menh gia " << menhGia[i] << "\n";
            s = s % menhGia[i]; // Số tiền còn lại sau khi đổi
        }
    }

    if (s > 0)
    {
        cout << "Khong the doi het! Con du: " << s << "\n";
    }
}

int main()
{
    // Mệnh giá tiền sắp xếp từ lớn đến nhỏ
    vector<int> menhGia = {10, 5, 2, 1};
    int soTien = 43;

    doiTien(soTien, menhGia);

    return 0;
}