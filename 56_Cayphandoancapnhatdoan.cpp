#include <iostream>
#include <vector>
using namespace std;

struct LazySegmentTree
{
    int n;
    vector<int> tree, lazy;

    LazySegmentTree(int n)
    {
        this->n = n;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    void push(int node, int start, int end)
    {
        if (lazy[node] != 0)
        {
            tree[node] += (end - start + 1) * lazy[node]; // Cập nhật nút hiện tại
            if (start != end)
            { // Đẩy giá trị lười xuống cho 2 con
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0; // Xóa trạng thái lười ở nút cha
        }
    }

    void updateDoan(int node, int start, int end, int L, int R, int val)
    {
        push(node, start, end);
        if (start > end || start > R || end < L)
            return; // Nằm ngoài đoạn

        if (L <= start && end <= R)
        { // Nằm hoàn toàn trong đoạn
            lazy[node] += val;
            push(node, start, end);
            return;
        }

        int mid = start + (end - start) / 2;
        updateDoan(2 * node, start, mid, L, R, val);
        updateDoan(2 * node + 1, mid + 1, end, L, R, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    int queryDoan(int node, int start, int end, int L, int R)
    {
        push(node, start, end);
        if (start > end || start > R || end < L)
            return 0;

        if (L <= start && end <= R)
            return tree[node];

        int mid = start + (end - start) / 2;
        return queryDoan(2 * node, start, mid, L, R) +
               queryDoan(2 * node + 1, mid + 1, end, L, R);
    }
};

int main()
{
    int n = 5;
    LazySegmentTree st(n);

    // Cộng 5 vào các phần tử đoạn [1, 3] (Mảng gốc ban đầu toàn 0)
    st.updateDoan(1, 0, n - 1, 1, 3, 5);

    // Truy vấn tổng đoạn [2, 4]
    cout << "Tong doan [2, 4] sau khi update: "
         << st.queryDoan(1, 0, n - 1, 2, 4) << "\n"; // Các ô 2, 3 có giá trị 5; ô 4 có giá trị 0 -> Tổng = 10

    return 0;
}