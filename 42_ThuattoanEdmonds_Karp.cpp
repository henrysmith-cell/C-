#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

// Dùng BFS để tìm đường đi ngắn nhất còn sức chứa từ S đến T
int bfs(int s, int t, vector<int> &parent, vector<vector<int>> &capacity, vector<vector<int>> &adj)
{
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INT_MAX});

    while (!q.empty())
    {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur])
        {
            if (parent[next] == -1 && capacity[cur][next] > 0)
            {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}

int edmondsKarp(int s, int t, int n, vector<vector<int>> &capacity, vector<vector<int>> &adj)
{
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    // Liên tục tìm đường tăng luồng cho đến khi không bơm thêm được nữa
    while ((new_flow = bfs(s, t, parent, capacity, adj)))
    {
        flow += new_flow;
        int cur = t;
        while (cur != s)
        {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow; // Trừ sức chứa cạnh thuận
            capacity[cur][prev] += new_flow; // Cộng sức chứa cạnh nghịch
            cur = prev;
        }
    }
    return flow;
}

int main()
{
    int n = 4; // Đồ thị gồm 4 đỉnh từ 0 đến 3
    vector<vector<int>> capacity(n, vector<int>(n, 0));
    vector<vector<int>> adj(n);

    auto themCanh = [&](int u, int v, int cap)
    {
        adj[u].push_back(v);
        adj[v].push_back(u); // Cạnh ngược phục vụ đồ thị thặng dư
        capacity[u][v] = cap;
    };

    themCanh(0, 1, 20);
    themCanh(0, 2, 10);
    themCanh(1, 2, 5);
    themCanh(1, 3, 10);
    themCanh(2, 3, 20);

    cout << "Luong cuc dai co the bom tu 0 den 3 la: " << edmondsKarp(0, 3, n, capacity, adj) << endl;
    return 0;
}