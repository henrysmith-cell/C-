#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Canh
{
    int to, cap, flow, rev;
};

struct DothiDinic
{
    int n;
    vector<vector<Canh>> adj;
    vector<int> level; // Lưu mức của các đỉnh trong đồ thị phân tầng
    vector<int> ptr;   // Con trỏ tối ưu hóa DFS (để tránh duyệt lại các cạnh đã bão hòa)

    DothiDinic(int n) : n(n), adj(n), level(n), ptr(n) {}

    void themCanh(int from, int to, int cap)
    {
        adj[from].push_back({to, cap, 0, (int)adj[to].size()});
        adj[to].push_back({from, 0, 0, (int)adj[from].size() - 1}); // Cạnh ngược với dung lượng bằng 0
    }

    // Tạo đồ thị phân tầng bằng BFS
    bool bfs(int s, int t)
    {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            for (auto &edge : adj[v])
            {
                if (edge.cap - edge.flow > 0 && level[edge.to] == -1)
                {
                    level[edge.to] = level[v] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level[t] != -1; // Trả về true nếu vẫn tìm được đường đi tới đích t
    }

    // Tìm luồng chặn bằng DFS
    int dfs(int v, int t, int pushed)
    {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;

        for (int &cid = ptr[v]; cid < adj[v].size(); ++cid)
        {
            auto &edge = adj[v][cid];
            int truyen = edge.to;
            if (level[v] + 1 != level[truyen] || edge.cap - edge.flow == 0)
                continue;

            int canPush = min(pushed, edge.cap - edge.flow);
            int pushed_that_way = dfs(truyen, t, canPush);

            if (pushed_that_way == 0)
                continue;

            edge.flow += pushed_that_way;
            adj[truyen][edge.rev].flow -= pushed_that_way; // Cập nhật cạnh ngược
            return pushed_that_way;
        }
        return 0;
    }

    // Hàm tính toán luồng cực đại tổng thể
    int maxFlow(int s, int t)
    {
        int flow = 0;
        while (bfs(s, t))
        {
            fill(ptr.begin(), ptr.end(), 0);
            while (int pushed = dfs(s, t, 1e9))
            {
                flow += pushed;
            }
        }
        return flow;
    }
};

int main()
{
    // Khởi tạo đồ thị có 4 đỉnh (đánh số 0, 1, 2, 3)
    DothiDinic g(4);
    g.themCanh(0, 1, 10); // S -> A
    g.themCanh(0, 2, 10); // S -> B
    g.themCanh(1, 2, 2);  // A -> B
    g.themCanh(1, 3, 10); // A -> T
    g.themCanh(2, 3, 10); // B -> T

    cout << "--- KET QUA THUAT TOAN DINIC ---\n";
    cout << "Luong cuc dai tu nguon (0) den dich (3) la: " << g.maxFlow(0, 3) << endl;
    return 0;
}