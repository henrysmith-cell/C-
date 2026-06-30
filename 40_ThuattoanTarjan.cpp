#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

void TarjanDFS(int u, vector<vector<int>> &adj, vector<int> &disc, vector<int> &low,
               stack<int> &st, vector<bool> &inStack, int &timer)
{
    disc[u] = low[u] = ++timer;
    st.push(u);
    inStack[u] = true;

    for (int v : adj[u])
    {
        if (disc[v] == -1)
        { // Nếu v chưa được thăm
            TarjanDFS(v, adj, disc, low, st, inStack, timer);
            low[u] = min(low[u], low[v]);
        }
        else if (inStack[v])
        { // Nếu v nằm trong ngăn xếp hiện tại
            low[u] = min(low[u], disc[v]);
        }
    }

    // Nếu u là đỉnh gốc của một SCC
    if (low[u] == disc[u])
    {
        cout << "SCC: ";
        while (true)
        {
            int v = st.top();
            st.pop();
            inStack[v] = false;
            cout << v << " ";
            if (u == v)
                break;
        }
        cout << "\n";
    }
}

int main()
{
    int soDinh = 5;
    vector<vector<int>> adj(soDinh);
    // Tạo các cạnh có hướng
    adj[1].push_back(0);
    adj[0].push_back(2);
    adj[2].push_back(1);
    adj[0].push_back(3);
    adj[3].push_back(4);

    vector<int> disc(soDinh, -1), low(soDinh, -1);
    vector<bool> inStack(soDinh, false);
    stack<int> st;
    int timer = 0;

    cout << "--- CAC THANH PHAN LIEN THONG MANH (SCC) ---\n";
    for (int i = 0; i < soDinh; i++)
    {
        if (disc[i] == -1)
        {
            TarjanDFS(i, adj, disc, low, st, inStack, timer);
        }
    }
    return 0;
}