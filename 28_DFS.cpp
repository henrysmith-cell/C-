#include <iostream>
#include <vector>
using namespace std;

// Hàm đệ quy thực hiện DFS
void DFS(int u, vector<int> danhSachKe[], vector<bool> &daTham)
{
    // Đánh dấu đỉnh u đã được thăm
    daTham[u] = true;
    cout << u << " ";

    // Duyệt qua tất cả các đỉnh v kề với u
    for (int v : danhSachKe[u])
    {
        if (!daTham[v])
        {
            DFS(v, danhSachKe, daTham); // Đệ quy sâu xuống đỉnh v
        }
    }
}

int main()
{
    int soDinh = 6;
    vector<int> danhSachKe[6];
    vector<bool> daTham(soDinh, false);

    // Tạo các cạnh nối giữa các đỉnh đồ thị
    danhSachKe[0].push_back(1);
    danhSachKe[0].push_back(2);
    danhSachKe[1].push_back(0);
    danhSachKe[1].push_back(3);
    danhSachKe[1].push_back(4);
    danhSachKe[2].push_back(0);
    danhSachKe[2].push_back(5);
    danhSachKe[3].push_back(1);
    danhSachKe[4].push_back(1);
    danhSachKe[5].push_back(2);

    cout << "Thu tu duyet DFS bat dau tu dinh 0: ";
    DFS(0, danhSachKe, daTham);
    cout << endl;

    return 0;
}