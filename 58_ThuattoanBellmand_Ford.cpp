#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Canh
{
    int u, v, trongSo;
};

void bellmanFord(int nguon, int soDinh, vector<Canh> &danhSachCanh)
{
    // Khởi tạo khoảng cách ban đầu đều là vô cùng (INT_MAX)
    vector<int> dist(soDinh, INT_MAX);
    dist[nguon] = 0;

    // Bước 1: Lặp lại tối đa (V - 1) lần việc tối ưu các cạnh
    for (int i = 1; i <= soDinh - 1; i++)
    {
        for (Canh e : danhSachCanh)
        {
            if (dist[e.u] != INT_MAX && dist[e.u] + e.trongSo < dist[e.v])
            {
                dist[e.v] = dist[e.u] + e.trongSo;
            }
        }
    }

    // Bước 2: Kiểm tra chu trình âm bằng cách lặp thêm 1 lần nữa
    bool coChuTrinhAm = false;
    for (Canh e : danhSachCanh)
    {
        if (dist[e.u] != INT_MAX && dist[e.u] + e.trongSo < dist[e.v])
        {
            coChuTrinhAm = true;
            break;
        }
    }

    if (coChuTrinhAm)
    {
        cout << "Do thi co chua chu trinh am! Khong the tim duong di ngan nhat.\n";
    }
    else
    {
        cout << "--- KET QUA BELLMAN-FORD TU DINH " << nguon << " ---\n";
        for (int i = 0; i < soDinh; i++)
        {
            cout << "Den dinh " << i << " : " << dist[i] << "\n";
        }
    }
}

int main()
{
    int soDinh = 5;
    // Tạo đồ thị có cạnh âm nhưng không chứa chu trình âm
    vector<Canh> danhSachCanh = {
        {0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2}, {1, 4, 2}, {3, 2, 5}, {3, 1, 1}, {4, 3, -3}};

    bellmanFord(0, soDinh, danhSachCanh);
    return 0;
}