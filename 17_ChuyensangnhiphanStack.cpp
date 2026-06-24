#include <iostream>
#include <stack> // Thư viện cấu trúc dữ liệu Ngăn xếp
using namespace std;

int main()
{
    int n;
    cout << "Nhap so thap phan n: ";
    cin >> n;

    int temp = n;
    stack<int> st; // Khai báo một stack chứa số nguyên

    // Thuật toán chia đôi lấy dư
    while (temp > 0)
    {
        st.push(temp % 2); // Đẩy số dư vào stack
        temp /= 2;
    }

    cout << "So " << n << " trong he nhi phan la: ";
    if (st.empty())
        cout << 0; // Trường hợp n = 0

    // Stack hoạt động theo cơ chế LIFO (Vào sau - Ra trước)
    while (!st.empty())
    {
        cout << st.top(); // Lấy phần tử ở đỉnh stack ra in
        st.pop();         // Xóa phần tử đó khỏi stack
    }
    cout << endl;

    return 0;
}