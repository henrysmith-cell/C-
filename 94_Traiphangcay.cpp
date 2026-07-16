#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 10005;
vector<int> adj[MAXN];
int tin[MAXN], tout[MAXN];
int thoiGian = 0;
vector<int> mangPhang;

// DFS duyệt cây và ghi nhận thời gian vào/ra của mỗi đỉnh
void dfsEulerTour(int u, int p)
{
    tin[u] = ++thoiGian;
    mangPhang.push_back(u); // Ghi nhận đỉnh vào mảng phẳng

    for (int v : adj[u])
    {
        if (v != p)
        {
            dfsEulerTour(v, u);
        }
    }
    tout[u] = thoiGian;
}

// Segment Tree đơn giản để thực hiện truy vấn trên mảng phẳng hóa
int segTree[4 * MAXN];
int val[MAXN];

void buildSeg(int node, int l, int r)
{
    if (l == r)
    {
        // Ánh xạ từ chỉ số thời gian trong Euler Tour về giá trị của đỉnh
        segTree[node] = val[mangPhang[l - 1]];
        return;
    }
    int mid = (l + r) / 2;
    buildSeg(2 * node, l, mid);
    buildSeg(2 * node + 1, mid + 1, r);
    segTree[node] = segTree[2 * node] + segTree[2 * node + 1];
}

int querySeg(int node, int l, int r, int ql, int qr)
{
    if (ql > r || qr < l)
        return 0;
    if (ql <= l && r <= qr)
        return segTree[node];
    int mid = (l + r) / 2;
    return querySeg(2 * node, l, mid, ql, qr) + querySeg(2 * node + 1, mid + 1, r, ql, qr);
}

int main()
{
    int n = 5;
    // Dựng cây: 1 nối với 2 và 3; 2 nối với 4 và 5
    adj[1].push_back(2);
    adj[2].push_back(1);
    adj[1].push_back(3);
    adj[3].push_back(1);
    adj[2].push_back(4);
    adj[4].push_back(2);
    adj[2].push_back(5);
    adj[5].push_back(2);

    // Gán giá trị ban đầu cho các nút
    val[1] = 10;
    val[2] = 5;
    val[3] = 2;
    val[4] = 7;
    val[5] = 8;

    dfsEulerTour(1, 0);
    buildSeg(1, 1, n);

    cout << "--- KET QUA EULER TOUR TECHNIQUE ---\n";
    // Tính tổng giá trị trong cây con gốc 2 (bao gồm các nút 2, 4, 5)
    // Cây con của u luôn tương ứng với đoạn [tin[u], tout[u]]
    int tongCayCon2 = querySeg(1, 1, n, tin[2], tout[2]);
    cout << "Tong gia tri cay con cua nut 2 la: " << tongCayCon2 << endl; // Kết quả: 5 + 7 + 8 = 20
    return 0;
}