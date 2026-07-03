#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int n, logN;
vector<vector<int>> adj;
vector<int> tin, tout, doSau;
vector<vector<int>> up; // up[u][i] lưu tổ tiên thứ 2^i của u
int timer;

void dfs(int u, int p, int d)
{
    tin[u] = ++timer;
    doSau[u] = d;
    up[u][0] = p;

    for (int i = 1; i <= logN; i++)
    {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }

    for (int v : adj[u])
    {
        if (v != p)
            dfs(v, u, d + 1);
    }
    tout[u] = ++timer;
}

bool laToTien(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int timLCA(int u, int v)
{
    if (laToTien(u, v))
        return u;
    if (laToTien(v, u))
        return v;

    // Nhảy ngược lên bằng các bước lũy thừa của 2
    for (int i = logN; i >= 0; i--)
    {
        if (!laToTien(up[u][i], v))
        {
            u = up[u][i];
        }
    }
    return up[u][0];
}

int main()
{
    n = 5;
    logN = ceil(log2(n));
    adj.resize(n);
    tin.resize(n);
    tout.resize(n);
    doSau.resize(n);
    up.assign(n, vector<int>(logN + 1));

    auto themCanh = [&](int u, int v)
    { adj[u].push_back(v); adj[v].push_back(u); };
    themCanh(0, 1);
    themCanh(0, 2);
    themCanh(1, 3);
    themCanh(1, 4);

    timer = 0;
    dfs(0, 0, 0); // Chạy DFS từ gốc 0 để tiền xử lý mảng up

    cout << "LCA cua 3 va 4 la: " << timLCA(3, 4) << "\n";
    cout << "LCA cua 3 va 2 la: " << timLCA(3, 2) << "\n";

    return 0;
}