#include <iostream>
#include <vector>
using namespace std;

void sangEratosthenes(int n)
{
    // Khởi tạo mảng đánh dấu, mặc định coi tất cả là số nguyên tố (true)
    vector<bool> laSoNguyenTo(n + 1, true);
    laSoNguyenTo[0] = laSoNguyenTo[1] = false; // 0 và 1 không phải số nguyên tố

    for (int p = 2; p * p <= n; p++)
    {
        // Nếu p là số nguyên tố, tiến hành loại bỏ tất cả các bội số của nó
        if (laSoNguyenTo[p])
        {
            for (int i = p * p; i <= n; i += p)
            {
                laSoNguyenTo[i] = false;
            }
        }
    }

    // In ra kết quả các số nguyên tố còn sót lại
    cout << "Cac so nguyen to <= " << n << " la: ";
    for (int p = 2; p <= n; p++)
    {
        if (laSoNguyenTo[p])
        {
            cout << p << " ";
        }
    }
    cout << "\n";
}

int main()
{
    int n = 30;
    sangEratosthenes(n);
    return 0;
}