#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

struct DoThiEuler
{
    int v;
    vector<vector<int>> adj;
    vector<int> viTriCanh; // Đánh dấu vị trí cạnh tiếp theo để tránh duyệt trùng

    DoThiEuler(int v) : v(v), adj(v), viTriCanh(v, 0) {}

    void themCanh(int u, int v)
    {
        adj[u].push_back(v);
    }

    void timChuTrinhEuler(int u_goc)
    {
        stack<int> currPath;
        vector<int> eulerCircuit;

        currPath.push(u_goc);
        int u_hienTai = u_goc;

        while (!currPath.empty())
        {
            // Nếu đỉnh hiện tại vẫn còn cạnh chưa đi qua
            if (viTriCanh[u_hienTai] < adj[u_hienTai].size())
            {
                currPath.push(u_hienTai);
                // Lấy cạnh tiếp theo và tăng con trỏ chỉ mục lên (thay cho việc xóa cạnh)
                int u_tiepTheo = adj[u_hienTai][viTriCanh[u_hienTai]++];
                u_hienTai = u_tiepTheo;
            }
            // Nếu đã đi vào "ngõ cụt" (hết cạnh), ghi nhận đỉnh này vào chu trình
            else
            {
                eulerCircuit.push_back(u_hienTai);
                u_hienTai = currPath.top();
                currPath.pop();
            }
        }

        reverse(eulerCircuit.begin(), eulerCircuit.end());

        cout << "--- CHU TRINH EULER TIM DUOC ---\n";
        for (int i = 0; i < eulerCircuit.size(); i++)
        {
            cout << eulerCircuit[i] << (i == eulerCircuit.size() - 1 ? "" : " -> ");
        }
        cout << "\n";
    }
};

int main()
{
    // Khởi tạo đồ thị có hướng thỏa mãn điều kiện Euler (Bậc vào = Bậc ra)
    DoThiEuler g(3);
    g.themCanh(0, 1);
    g.themCanh(1, 2);
    g.themCanh(2, 0);

    g.timChuTrinhEuler(0);
    return 0;
}