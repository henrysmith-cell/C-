#include <iostream>
#include <vector>
using namespace std;

// Hàm xây dựng Segment Tree
void buildTree(vector<int> &a, vector<int> &tree, int node, int start, int end)
{
    if (start == end)
    {
        // Nút lá lưu giá trị của mảng gốc
        tree[node] = a[start];
        return;
    }
    int mid = start + (end - start) / 2;
    // Xây dựng cây con bên trái
    buildTree(a, tree, 2 * node, start, mid);
    // Xây dựng cây con bên phải
    buildTree(a, tree, 2 * node + 1, mid + 1, end);
    // Giá trị nút cha bằng tổng 2 nút con
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Hàm truy vấn tổng đoạn [L, R]
int query(vector<int> &tree, int node, int start, int end, int L, int R)
{
    // Trường hợp 1: Đoạn [start, end] nằm hoàn toàn ngoài [L, R]
    if (end < L || start > R)
        return 0;

    // Trường hợp 2: Đoạn [start, end] nằm hoàn toàn trong [L, R]
    if (L <= start && end <= R)
        return tree[node];

    // Trường hợp 3: Một phần giao nhau
    int mid = start + (end - start) / 2;
    int p1 = query(tree, 2 * node, start, mid, L, R);
    int p2 = query(tree, 2 * node + 1, mid + 1, end, L, R);
    return p1 + p2;
}

int main()
{
    vector<int> a = {1, 3, 5, 7, 9, 11};
    int n = a.size();

    // Kích thước tối đa của cây phân đoạn là 4 * n
    vector<int> tree(4 * n, 0);

    buildTree(a, tree, 1, 0, n - 1);

    int L = 1, R = 3; // Tính tổng từ index 1 đến 3 (tức là 3 + 5 + 7)
    cout << "Tong cac phan tu trong doan [" << L << ", " << R << "] la: "
         << query(tree, 1, 0, n - 1, L, R) << endl;

    return 0;
}