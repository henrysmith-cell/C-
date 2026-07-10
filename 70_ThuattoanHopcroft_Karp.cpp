#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int INF = INT_MAX;

struct HopcroftKarp
{
    int n, m;
    vector<vector<int>> adj;
    vector<int> pair_u, pair_v, dist;

    HopcroftKarp(int n, int m) : n(n), m(m), adj(n + 1), pair_u(n + 1, 0), pair_v(m + 1, 0), dist(n + 1) {}

    void themCanh(int u, int v) { adj[u].push_back(v); }

    // Sử dụng BFS để tìm các đường tăng ngắn nhất và phân tầng đồ thị
    bool bfs()
    {
        queue<int> q;
        for (int u = 1; u <= n; u++)
        {
            if (pair_u[u] == 0)
            {
                dist[u] = 0;
                q.push(u);
            }
            else
                dist[u] = INF;
        }
        dist[0] = INF;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            if (dist[u] < dist[0])
            {
                for (int v : adj[u])
                {
                    if (dist[pair_v[v]] == INF)
                    {
                        dist[pair_v[v]] = dist[u] + 1;
                        q.push(pair_v[v]);
                    }
                }
            }
        }
        return (dist[0] != INF);
    }

    // Sử dụng DFS để đẩy luồng cặp ghép dọc theo các đường tăng đã phân tầng
    bool dfs(int u)
    {
        if (u != 0)
        {
            for (int v : adj[u])
            {
                if (dist[pair_v[v]] == dist[u] + 1)
                {
                    if (dfs(pair_v[v]))
                    {
                        pair_v[v] = u;
                        pair_u[u] = v;
                        return true;
                    }
                }
            }
            dist[u] = INF;
            return false;
        }
        return true;
    }

    int tinhMaxMatching()
    {
        int matching = 0;
        while (bfs())
        {
            for (int u = 1; u <= n; u++)
            {
                if (pair_u[u] == 0 && dfs(u))
                    matching++;
            }
        }
        return matching;
    }
};

int main()
{
    // Giả lập bài toán ghép cặp: 4 người đàn ông (U) và 4 người phụ nữ (V)
    HopcroftKarp hk(4, 4);
    hk.themCanh(1, 1);
    hk.themCanh(1, 2);
    hk.themCanh(2, 2);
    hk.themCanh(3, 2);
    hk.themCanh(3, 3);
    hk.themCanh(4, 3);
    hk.themCanh(4, 4);

    cout << "--- KET QUA KOSARAJU / HOPCROFT-KARP ---\n";
    cout << "So luong cap ghep toi da co the tao ra la: " << hk.tinhMaxMatching() << endl;
    return 0;
}