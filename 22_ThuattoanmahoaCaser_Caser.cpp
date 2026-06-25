#include <iostream>
#include <string>
using namespace std;

string maHoaCaesar(string text, int k)
{
    string ketQua = "";

    // Đảm bảo k nằm trong khoảng từ 0 đến 25 (vì bảng chữ cái tiếng Anh có 26 chữ)
    k = k % 26;

    for (int i = 0; i < text.length(); i++)
    {
        char c = text[i];

        if (c >= 'a' && c <= 'z')
        {
            // Dịch chuyển ký tự và vòng lại nếu vượt quá chữ 'z'
            c = 'a' + (c - 'a' + k) % 26;
        }
        // Giữ nguyên khoảng trắng hoặc ký tự đặc biệt
        ketQua += c;
    }
    return ketQua;
}

int main()
{
    string text;
    int k;
    cout << "Nhap chuoi tieng Anh (viet thuong): ";
    getline(cin, text);
    cout << "Nhap so buoc dich chuyen k: ";
    cin >> k;

    string chuoiMaHoa = maHoaCaesar(text, k);
    cout << "Chuoi sau khi ma hoa: " << chuoiMaHoa << endl;

    return 0;
}