#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct ThaoTac
{
    int u, cha_cu_u, v, size_cu_v;
};

struct DSURollback
{
    vector<int> parent, sz;
    stack<ThaoTac> lichSu;

    DSURollback(int n)
    {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        for (int i = 1; i <= n; i++)
            parent[i] = i;
    }

    // Tìm gốc KHÔNG sử dụng nén đường đi để bảo toàn cấu trúc phục hồi
    int findRoot(int u)
    {
        while (u != parent[u])
            u = parent[u];
        return u;
    }

    bool unionSets(int u, int v)
    {
        int rootU = findRoot(u), rootV = findRoot(v);
        if (rootU == rootV)
            return false;

        // Tối ưu gộp cây nhỏ vào cây lớn hơn
        if (sz[rootU] > sz[rootV])
            swap(rootU, rootV);

        // Lưu lại lịch sử trước khi thay đổi để phục vụ việc Rollback
        lichSu.push({rootU, parent[rootU], rootV, sz[rootV]});

        parent[rootU] = rootV;
        sz[rootV] += sz[rootU];
        return true;
    }

    // Hàm quay ngược trạng thái: Hủy bỏ 1 thao tác gộp gần nhất
    void rollback()
    {
        if (lichSu.empty())
            return;
        ThaoTac op = lichSu.top();
        lichSu.pop();
        parent[op.u] = op.cha_cu_u;
        sz[op.v] = op.size_cu_v;
    }
};

int main()
{
    DSURollback dsu(5);

    dsu.unionSets(1, 2);
    dsu.unionSets(3, 4);

    cout << "--- KET QUA DSU ROLLBACK ---\n";
    cout << "Ban dau: 1 va 2 co cung tap hop? " << (dsu.findRoot(1) == dsu.findRoot(2) ? "Co" : "Khong") << "\n";

    dsu.unionSets(2, 3); // Nối hai nhóm lại với nhau thành: 1-2-3-4
    cout << "Sau khi noi 2 voi 3: 1 va 4 chung tap hop? " << (dsu.findRoot(1) == dsu.findRoot(4) ? "Co" : "Khong") << "\n";

    dsu.rollback(); // Hủy bỏ lệnh nối (2, 3) vừa rồi
    cout << "Sau khi Rollback: 1 va 4 con chung tap hop? " << (dsu.findRoot(1) == dsu.findRoot(4) ? "Co" : "Khong") << "\n";

    return 0;