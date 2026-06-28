#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Cặp dữ liệu: (khoảng cách, đỉnh)
typedef pair<int, int> pii;

void dijkstra(int nguon, vector<vector<pii>> &danhSachKe, int soDinh)
{
    // Khởi tạo khoảng cách ban đầu đều là vô cùng (INT_MAX)
    vector<int> dist(soDinh, INT_MAX);
    // Hàng đợi ưu tiên (đỉnh có khoảng cách nhỏ nhất luôn nằm ở đầu)
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    dist[nguon] = 0;
    pq.push({0, nguon});

    while (!pq.empty())
    {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        // Nếu khoảng cách lấy ra lớn hơn khoảng cách hiện tại đã tối ưu thì bỏ qua
        if (d > dist[u])
            continue;

        // Duyệt các đỉnh kề v của u
        for (auto &canhKee : danhSachKe[u])
        {
            int v = canhKee.first;
            int trongSo = canhKee.second;

            // Nếu tìm thấy đường đi ngắn hơn đến v qua u
            if (dist[u] + trongSo < dist[v])
            {
                dist[v] = dist[u] + trongSo;
                pq.push({dist[v], v});
            }
        }
    }

    // In kết quả
    cout << "Khoang cach ngan nhat tu dinh " << nguon << " den:\n";
    for (int i = 0; i < soDinh; i++)
    {
        cout << "Dinh " << i << " : ";
        if (dist[i] == INT_MAX)
            cout << "Khong the den\n";
        else
            cout << dist[i] << "\n";
    }
}

int main()
{
    int soDinh = 5;
    vector<vector<pii>> danhSachKe(soDinh);

    // Thêm các cạnh (u -> {v, trọng số})
    danhSachKe[0].push_back({1, 4});
    danhSachKe[0].push_back({2, 1});
    danhSachKe[2].push_back({1, 2});
    danhSachKe[2].push_back({3, 4});
    danhSachKe[1].push_back({3, 1});
    danhSachKe[3].push_back({4, 3});

    dijkstra(0, danhSachKe, soDinh);

    return 0;
}