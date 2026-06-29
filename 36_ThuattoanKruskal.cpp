#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Cấu trúc đại diện cho một Cạnh của đồ thị
struct Canh
{
    int u, v, trongSo;
    // Định nghĩa phép so sánh để sắp xếp các cạnh theo trọng số tăng dần
    bool operator<(const Canh &khac) const
    {
        return trongSo < khac.trongSo;
    }
};

// Cấu trúc DSU (Disjoint Set Union) để quản lý tập hợp và kiểm tra chu trình
struct DSU
{
    vector<int> parent;
    DSU(int n)
    {
        parent.resize(n);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    int find_set(int v)
    {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]); // Tối ưu nén đường đi
    }
    bool union_sets(int a, int b)
    {
        a = find_set(a);
        b = find_set(b);
        if (a != b)
        {
            parent[b] = a;
            return true; // Gộp thành công, không tạo chu trình
        }
        return false; // Tạo chu trình
    }
};

void kruskal(int soDinh, vector<Canh> &danhSachCanh)
{
    sort(danhSachCanh.begin(), danhSachCanh.end()); // Bước 1: Sắp xếp cạnh

    DSU dsu(soDinh);
    int tongTrongSoMST = 0;
    vector<Canh> mST;

    for (Canh e : danhSachCanh)
    {
        // Bước 2: Kiểm tra xem thêm cạnh e có tạo chu trình không
        if (dsu.union_sets(e.u, e.v))
        {
            tongTrongSoMST += e.trongSo;
            mST.push_back(e);
        }
    }

    cout << "--- CAY KHUNG NHO NHAT (MST) ---\n";
    for (Canh e : mST)
    {
        cout << e.u << " - " << e.v << " : " << e.trongSo << "\n";
    }
    cout << "Tong trong so cua MST: " << tongTrongSoMST << endl;
}

int main()
{
    int soDinh = 6;
    vector<Canh> danhSachCanh = {
        {0, 1, 4}, {0, 2, 4}, {1, 2, 2}, {1, 3, 5}, {2, 3, 8}, {2, 4, 9}, {3, 4, 7}, {3, 5, 11}, {4, 5, 3}};

    kruskal(soDinh, danhSachCanh);
    return 0;
}