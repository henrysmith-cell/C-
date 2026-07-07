#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, timer;
vector<vector<int>> adj;
vector<int> parent, depth, heavy, head, pos;

// DFS lượt 1: Tính kích thước cây con để xác định cạnh nặng (Heavy Edge)
int dfs_sz(int u, int p, int d)
{
    int size = 1, max_c_size = 0;
    parent[u] = p;
    depth[u] = d;
    for (int v : adj[u])
    {
        if (v != p)
        {
            int c_size = dfs_sz(v, u, d + 1);
            size += c_size;
            if (c_size > max_c_size)
            {
                max_c_size = c_size;
                heavy[u] = v; // v là con nặng của u
            }
        }
    }
    return size;
}

// DFS lượt 2: Phân rã cây thành các chuỗi phẳng (Chains)
void decompose(int u, int h)
{
    head[u] = h;
    pos[u] = timer++;
    if (heavy[u] != -1)
        decompose(heavy[u], h); // Đi tiếp dọc theo chuỗi nặng
    for (int v : adj[u])
    {
        if (v != parent[u] && v != heavy[u])
        {
            decompose(v, v); // Tạo một chuỗi nặng mới bắt đầu từ đỉnh v
        }
    }
}

int main()
{
    n = 5;
    adj.resize(n);
    parent.resize(n);
    depth.resize(n);
    heavy.assign(n, -1);
    head.resize(n);
    pos.resize(n);

    adj[0].push_back(1);
    adj[1].push_back(0);
    adj[0].push_back(2);
    adj[2].push_back(0);
    adj[1].push_back(3);
    adj[3].push_back(1);
    adj[1].push_back(4);
    adj[4].push_back(1);

    timer = 0;
    dfs_sz(0, 0, 0);
    decompose(0, 0);

    cout << "--- KET QUA PHAN TACH HLD ---\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Dinh " << i << " -> Nam trong chuoi bat dau tu dinh head: " << head[i]
             << " (Vi tri tren mang phang: " << pos[i] << ")\n";
    }
    return 0;
}