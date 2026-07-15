#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 10005;
vector<int> adj[MAXN];
int parentNode[MAXN], depth[MAXN], heavy[MAXN], head[MAXN], pos[MAXN];
int curPos;

// Segment Tree đơn giản để quản lý các giá trị đã được trải phẳng
int segTree[4 * MAXN];

void updateSeg(int node, int l, int r, int idx, int val)
{
    if (l == r)
    {
        segTree[node] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (idx <= mid)
        updateSeg(2 * node, l, mid, idx, val);
    else
        updateSeg(2 * node + 1, mid + 1, r, idx, val);
    segTree[node] = max(segTree[2 * node], segTree[2 * node + 1]);
}

int querySeg(int node, int l, int r, int ql, int qr)
{
    if (ql > r || qr < l)
        return -1e9;
    if (ql <= l && r <= qr)
        return segTree[node];
    int mid = (l + r) / 2;
    return max(querySeg(2 * node, l, mid, ql, qr), querySeg(2 * node + 1, mid + 1, r, ql, qr));
}

// Bước 1: DFS tính kích thước cây con và tìm cạnh nặng (Heavy Edge)
int dfsHLD(int u, int p, int d)
{
    parentNode[u] = p;
    depth[u] = d;
    int size = 1;
    int max_c_size = 0;
    heavy[u] = -1;
    for (int v : adj[u])
    {
        if (v != p)
        {
            int c_size = dfsHLD(v, u, d + 1);
            size += c_size;
            if (c_size > max_c_size)
            {
                max_c_size = c_size;
                heavy[u] = v;
            }
        }
    }
    return size;
}

// Bước 2: Phân tách cây thành các chuỗi (Chains) và gán vị trí trên Segment Tree
void decompose(int u, int h)
{
    head[u] = h;
    pos[u] = ++curPos;
    if (heavy[u] != -1)
    {
        decompose(heavy[u], h); // Đi tiếp trên cùng một chuỗi nặng
    }
    for (int v : adj[u])
    {
        if (v != parentNode[u] && v != heavy[u])
        {
            decompose(v, v); // Khởi động một chuỗi mới bắt đầu từ v
        }
    }
}

// Truy vấn giá trị lớn nhất trên đường đi giữa u và v trong O(log^2 N)
int queryPath(int u, int v, int n)
{
    int res = -1e9;
    while (head[u] != head[v])
    {
        if (depth[head[u]] > depth[head[v]])
            swap(u, v);
        res = max(res, querySeg(1, 1, n, pos[head[v]], pos[v]));
        v = parentNode[head[v]];
    }
    if (depth[u] > depth[v])
        swap(u, v);
    res = max(res, querySeg(1, 1, n, pos[u], pos[v]));
    return res;
}

int main()
{
    int n = 5;
    // Dựng cây nhị phân đơn giản
    adj[1].push_back(2);
    adj[2].push_back(1);
    adj[1].push_back(3);
    adj[3].push_back(1);
    adj[2].push_back(4);
    adj[4].push_back(2);
    adj[2].push_back(5);
    adj[5].push_back(2);

    curPos = 0;
    dfsHLD(1, 0, 0);
    decompose(1, 1);

    // Cập nhật giá trị cho các nút
    updateSeg(1, 1, n, pos[4], 15); // Nút 4 có giá trị 15
    updateSeg(1, 1, n, pos[2], 5);  // Nút 2 có giá trị 5
    updateSeg(1, 1, n, pos[5], 20); // Nút 5 có giá trị 20

    cout << "--- KET QUA HEAVY-LIGHT DECOMPOSITION ---\n";
    // Tìm Max trên đường đi từ nút 4 đến nút 5 (Đường đi: 4 -> 2 -> 5)
    cout << "Gia tri lon nhat tren duong di 4 den 5: " << queryPath(4, 5, n) << endl; // Kết quả: 20
    return 0;
}