#include <iostream>
using namespace std;

// Hàm nhận vào địa chỉ của 2 biến (con trỏ)
void hoanVi(int *x, int *y)
{
    int temp = *x; // Lưu giá trị của ô nhớ mà x trỏ tới vào temp
    *x = *y;       // Gán giá trị của ô nhớ y vào ô nhớ x
    *y = temp;     // Gán giá trị temp vào ô nhớ y
}

int main()
{
    int a, b;
    cout << "Nhap a va b: ";
    cin >> a >> b;

    cout << "Truoc khi hoan vi: a = " << a << ", b = " << b << endl;

    // Truyền địa chỉ của a và b vào hàm (dùng toán tử &)
    hoanVi(&a, &b);

    cout << "Sau khi hoan vi: a = " << a << ", b = " << b << endl;

    return 0;
}