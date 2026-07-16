#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9;

struct Canh
{
    int to, cap, flow, cost, rev;
};

struct MCMF
{
    int n;
    vector<vector<Canh>> adj;
    vector<int> dist, parent, parent_edge;
    vector<bool> in_queue;

    MCMF(int n) : n(n), adj(n), dist(n), parent(n), parent_edge(n), in_queue(n) {}

    void themCanh(int from, int to, int cap, int cost)
    {
        adj[from].push_back({to, cap, 0, cost, (int)adj[to].size()});
        adj[to].push_back({from, 0, 0, -cost, (int)adj[from].size() - 1}); // Cạnh ngược có cost đối ngẫu
    }

    // Thuật toán SPFA tìm đường đi có chi phí nhỏ nhất
    bool spfa(int s, int t)
    {
        fill(dist.begin(), dist.end(), INF);
        fill(in_queue.begin(), in_queue.end(), false);
        queue<int> q;

        dist[s] = 0;
        q.push(s);
        in_queue[s] = true;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            in_queue[u] = false;

            for (int i = 0; i < adj[u].size(); i++)
            {
                auto &edge = adj[u][i];
                if (edge.cap - edge.flow > 0 && dist[edge.to] > dist[u] + edge.cost)
                {
                    dist[edge.to] = dist[u] + edge.cost;
                    parent[edge.to] = u;
                    parent_edge[edge.to] = i;
                    if (!in_queue[edge.to])
                    {
                        q.push(edge.to);
                        in_queue[edge.to] = true;
                    }
                }
            }
        }
        return dist[t] != INF;
    }

    // Tính toán luồng cực đại với chi phí cực tiểu
    pair<int, int> minCostMaxFlow(int s, int t)
    {
        int flow = 0, cost = 0;
        while (spfa(s, t))
        {
            // Tìm luồng tối đa có thể đẩy trên đường đi vừa tìm được
            int push = INF;
            for (int v = t; v != s; v = parent[v])
            {
                auto &edge = adj[parent[v]][parent_edge[v]];
                push = min(push, edge.cap - edge.flow);
            }

            // Thực hiện đẩy luồng và cập nhật chi phí
            for (int v = t; v != s; v = parent[v])
            {
                auto &edge = adj[parent[v]][parent_edge[v]];
                edge.flow += push;
                adj[v][edge.rev].flow -= push;
                cost += push * edge.cost;
            }
            flow += push;
        }
        return {flow, cost};
    }
};

int main()
{
    MCMF g(4);
    // Thêm các cạnh dạng: (U, V, Sức chứa, Chi phí)
    g.themCanh(0, 1, 10, 2); // S -> A
    g.themCanh(0, 2, 8, 5);  // S -> B
    g.themCanh(1, 2, 5, 1);  // A -> B
    g.themCanh(1, 3, 6, 2);  // A -> T
    g.themCanh(2, 3, 10, 3); // B -> T

    pair<int, int> result = g.minCostMaxFlow(0, 3);

    cout << "--- KET QUA MIN-COST MAX-FLOW ---\n";
    cout << "Luong cuc dai dat duoc: " << result.first << "\n";
    cout << "Chi phi nho nhat tuong ung: " << result.second << "\n";
    return 0;
}