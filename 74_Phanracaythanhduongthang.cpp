#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;
vector<int> parentNode, depth, heavyChild, headChain, posInSegmentTree;
int curPos = 0;

// DFS lượt 1: Tính kích thước cây con, độ sâu và tìm nút con "nặng" nhất
int dfsKhaiThac(int u, int p, int d)
{
    parentNode[u] = p;
    depth[u] = d;
    int sizeMax = 0, sizeCuaU = 1;

    for (int v : adj[u])
    {
        if (v != p)
        {
            int sizeCuaV = dfsKhaiThac(v, u, d + 1);
            sizeCuaU += sizeCuaV;
            if (sizeCuaV > sizeMax)
            {
                sizeMax = sizeCuaV;
                heavyChild[u] = v; // Chọn v làm con nặng
            }
        }
    }
    return sizeCuaU;
}

// DFS lượt 2: Thực hiện phân rã cây và định vị các nút lên mảng phẳng
void decomposeHLD(int u, int h)
{
    headChain[u] = h;
    posInSegmentTree[u] = ++curPos; // Vị trí của nút u trên Segment Tree tương lai

    // Ưu tiên đi dọc theo đường nặng trước để các nút trong chuỗi nằm liên tiếp nhau
    if (heavyChild[u] != -1)
    {
        decomposeHLD(heavyChild[u], h);
    }

    // Đi qua các nhánh nhẹ và khởi đầu các chuỗi mới
    for (int v : adj[u])
    {
        if (v != parentNode[u] && v != heavyChild[u])
        {
            decomposeHLD(v, v);
        }
    }
}

int main()
{
    int n = 6;
    adj.resize(n);
    parentNode.resize(n);
    depth.resize(n);
    heavyChild.assign(n, -1);
    headChain.resize(n);
    posInSegmentTree.resize(n);

    adj[0].push_back(1);
    adj[1].push_back(0);
    adj[0].push_back(2);
    adj[2].push_back(0);
    adj[1].push_back(3);
    adj[3].push_back(1);
    adj[1].push_back(1);
    adj[1].push_back(4); // 1-4
    adj[4].push_back(1);
    adj[2].push_back(5);
    adj[5].push_back(2);

    dfsKhaiThac(0, -1, 0);
    decomposeHLD(0, 0);

    cout << "--- KET QUA PHAN RA CAY (HLD) ---\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Nut " << i << " -> Thuoc chuoi co goc la: " << headChain[i]
             << ", Vi tri index tren Segment Tree: " << posInSegmentTree[i] << "\n";
    }
    return 0;
}