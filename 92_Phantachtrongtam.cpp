#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 10005;
set<int> adj[MAXN]; // Dùng set để dễ dàng xóa cạnh khi phân tách cây
int subSize[MAXN];

// DFS tính kích thước cây con hiện tại
int dfsCalcSize(int u, int p)
{
    subSize[u] = 1;
    for (int v : adj[u])
    {
        if (v != p)
        {
            subSize[u] += dfsCalcSize(v, u);
        }
    }
    return subSize[u];
}

// Tìm trọng tâm của cây/nhánh cây hiện tại
int getCentroid(int u, int p, int totalSize)
{
    for (int v : adj[u])
    {
        if (v != p && subSize[v] > totalSize / 2)
        {
            return getCentroid(v, u, totalSize);
        }
    }
    return u;
}

// Hàm chia để trị phân tách cây
void decomposeTree(int u, int p_centroid)
{
    int totalSize = dfsCalcSize(u, 0);
    int centroid = getCentroid(u, 0, totalSize);

    // Ở đây, ta thu được centroid của nhánh cây
    if (p_centroid != 0)
    {
        cout << "Noi canh trong cay trong tam: " << p_centroid << " -> " << centroid << "\n";
    }
    else
    {
        cout << "Goc cua cay trong tam: " << centroid << "\n";
    }

    // Xóa các liên kết của centroid hiện tại để cô lập các nhánh con
    vector<int> neighbors(adj[centroid].begin(), adj[centroid].end());
    for (int v : neighbors)
    {
        adj[centroid].erase(v);
        adj[v].erase(centroid);
        decomposeTree(v, centroid); // Đệ quy xử lý các nhánh con độc lập
    }
}

int main()
{
    int n = 5;
    // Dựng cây dạng đường thẳng: 1 - 2 - 3 - 4 - 5
    adj[1].insert(2);
    adj[2].insert(1);
    adj[2].insert(3);
    adj[3].insert(2);
    adj[3].insert(4);
    adj[4].insert(3);
    adj[4].insert(5);
    adj[5].insert(4);

    cout << "--- KET QUA CENTROID DECOMPOSITION ---\n";
    decomposeTree(1, 0);
    return 0;
}