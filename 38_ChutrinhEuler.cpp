#include <iostream>
#include <vector>
#include <stack>
#include <map>
using namespace std;

void timChuTrinhEuler(int dinhBatDau, vector<map<int, int>> &danhSachKe)
{
    stack<int> curr_path;
    vector<int> euler_circuit;

    curr_path.push(dinhBatDau);
    int curr_v = dinhBatDau;

    while (!curr_path.empty())
    {
        // Nếu đỉnh hiện tại vẫn còn cạnh nối chưa đi qua
        if (!danhSachKe[curr_v].empty())
        {
            curr_path.push(curr_v);

            // Lấy một đỉnh kề ngẫu nhiên
            int next_v = danhSachKe[curr_v].begin()->first;

            // Xóa cạnh u - v vừa đi qua (vì mỗi cạnh chỉ đi một lần)
            danhSachKe[curr_v][next_v]--;
            if (danhSachKe[curr_v][next_v] == 0)
                danhSachKe[curr_v].erase(next_v);

            danhSachKe[next_v][curr_v]--;
            if (danhSachKe[next_v][curr_v] == 0)
                danhSachKe[next_v].erase(curr_v);

            curr_v = next_v; // Di chuyển sang đỉnh tiếp theo
        }
        else
        {
            // Nếu không đi tiếp được nữa, ghi nhận đỉnh này vào chu trình và quay lui
            euler_circuit.push_back(curr_v);
            curr_v = curr_path.top();
            curr_path.pop();
        }
    }

    cout << "Chu trinh Euler: ";
    for (int i = euler_circuit.size() - 1; i >= 0; i--)
    {
        cout << euler_circuit[i] << (i == 0 ? "" : " -> ");
    }
    cout << endl;
}

int main()
{
    int soDinh = 5;
    // Sử dụng map trong vector để dễ dàng xóa cạnh khi duyệt qua
    vector<map<int, int>> danhSachKe(soDinh);

    // Tạo đồ thị Euler (tất cả các đỉnh có bậc chẵn: 0-1-2-0, 0-3-4-0)
    auto themCanh = [&](int u, int v)
    {
        danhSachKe[u][v]++;
        danhSachKe[v][u]++;
    };
    themCanh(0, 1);
    themCanh(1, 2);
    themCanh(2, 0);
    themCanh(0, 3);
    themCanh(3, 4);
    themCanh(4, 0);

    timChuTrinhEuler(0, danhSachKe);
    return 0;
}