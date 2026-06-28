#include <iostream>
#include <vector>
using namespace std;

void inTatCaTapCon(vector<int> &a)
{
    int n = a.size();
    // Tổng số tập con là 2^n (tương đương phép dịch bit 1 << n)
    int tongSoTapCon = 1 << n;

    cout << "--- TAT CA CAC TAP CON ---\n";
    for (int i = 0; i < tongSoTapCon; i++)
    {
        cout << "{ ";
        for (int j = 0; j < n; j++)
        {
            // Kiểm tra xem bit thứ j của số i có được bật (bằng 1) hay không
            if ((i & (1 << j)) != 0)
            {
                cout << a[j] << " ";
            }
        }
        cout << "}\n";
    }
}

int main()
{
    vector<int> a = {1, 2, 3}; // Mảng có 3 phần tử -> 8 tập con
    inTatCaTapCon(a);
    return 0;
}