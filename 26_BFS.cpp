#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Hàm thực hiện thuật toán BFS
void BFS(int nguon, vector<int> danhSachKe[], int soDinh)
{
    vector<bool> daTham(soDinh, false); // Mảng đánh dấu các đỉnh đã thăm
    queue<int> q;

    // Bắt đầu từ đỉnh nguồn
    daTham[nguon] = true;
    q.push(nguon);

    cout << "Thu tu duyet BFS tu dinh " << nguon << ": ";

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        cout << u << " ";

        // Duyệt qua tất cả các đỉnh kề với u
        for (int v : danhSachKe[u])
        {
            if (!daTham[v])
            {
                daTham[v] = true;
                q.push(v); // Đẩy đỉnh kề chưa thăm vào hàng đợi
            }
        }
    }
    cout << endl;
}

int main()
{
    int soDinh = 5;
    vector<int> danhSachKe[5];

    // Mô phỏng tạo các cạnh nối giữa các đỉnh đồ thị
    danhSachKe[0].push_back(1);
    danhSachKe[0].push_back(2);
    danhSachKe[1].push_back(0);
    danhSachKe[1].push_back(3);
    danhSachKe[2].push_back(0);
    danhSachKe[2].push_back(4);
    danhSachKe[3].push_back(1);
    danhSachKe[4].push_back(2);

    // Chạy BFS bắt đầu từ đỉnh 0
    BFS(0, danhSachKe, soDinh);

    return 0;
}