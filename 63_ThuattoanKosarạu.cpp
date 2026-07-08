#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Hàm DFS lượt 1: Đẩy các đỉnh vào stack theo thứ tự kết thúc duyệt
void dfs1(int u, vector<vector<int>> &adj, vector<bool> &visited, stack<int> &st)
{
    visited[u] = true;
    for (int v : adj[u])
    {
        if (!visited[v])
            dfs1(v, adj, visited, st);
    }
    st.push(u);
}

// Hàm DFS lượt 2: Duyệt trên đồ thị đảo ngược để bóc tách SCC
void dfs2(int u, vector<vector<int>> &adjT, vector<bool> &visited)
{
    visited[u] = true;
    cout << u << " ";
    for (int v : adjT[u])
    {
        if (!visited[v])
            dfs2(v, adjT, visited);
    }
}

int main()
{
    int soDinh = 5;
    vector<vector<int>> adj(soDinh);
    vector<vector<int>> adjT(soDinh); // Đồ thị đảo ngược (Transpose Graph)

    auto themCanh = [&](int u, int v)
    {
        adj[u].push_back(v);
        adjT[v].push_back(u); // Đảo ngược chiều cạnh
    };

    themCanh(1, 0);
    themCanh(0, 2);
    themCanh(2, 1);
    themCanh(0, 3);
    themCanh(3, 4);

    // Bước 1: Gọi DFS trên đồ thị gốc để thiết lập thứ tự topo trong stack
    stack<int> st;
    vector<bool> visited(soDinh, false);
    for (int i = 0; i < soDinh; i++)
    {
        if (!visited[i])
            dfs1(i, adj, visited, st);
    }

    // Bước 2: Reset lại mảng đánh dấu và tiến hành bóc từng SCC bằng đồ thị đảo ngược
    fill(visited.begin(), visited.end(), false);
    cout << "--- CAC THANH PHAN LIEN THONG MANH (KOSARAJU) ---\n";
    while (!st.empty())
    {
        int u = st.top();
        st.pop();

        if (!visited[u])
        {
            cout << "SCC: ";
            dfs2(u, adjT, visited);
            cout << "\n";
        }
    }

    return 0;
}