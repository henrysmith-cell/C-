#include <iostream>
#include <vector>
using namespace std;

struct Node
{
    int val;
    Node *left, *right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

// Hàm xây dựng phiên bản gốc đầu tiên (Version 0)
Node *build(vector<int> &a, int start, int end)
{
    if (start == end)
        return new Node(a[start]);
    int mid = start + (end - start) / 2;
    Node *root = new Node(0);
    root->left = build(a, start, mid);
    root->right = build(a, mid + 1, end);
    root->val = root->left->val + root->right->val;
    return root;
}

// Thao tác cập nhật tạo ra một phiên bản cây hoàn toàn mới mà không phá hủy cây cũ
Node *update(Node *prevRoot, int start, int end, int idx, int val)
{
    if (start == end)
        return new Node(val); // Tạo nút lá mới chứa giá trị mới

    int mid = start + (end - start) / 2;
    Node *cur = new Node(0);

    if (idx <= mid)
    {
        cur->right = prevRoot->right;                             // Dùng chung nhánh phải không đổi với cây cũ
        cur->left = update(prevRoot->left, start, mid, idx, val); // Tạo nhánh trái mới
    }
    else
    {
        cur->left = prevRoot->left;                                   // Dùng chung nhánh trái không đổi với cây cũ
        cur->right = update(prevRoot->right, mid + 1, end, idx, val); // Tạo nhánh phải mới
    }

    cur->val = cur->left->val + cur->right->val;
    return cur; // Trả về con trỏ gốc của phiên bản mới
}

int query(Node *root, int start, int end, int L, int R)
{
    if (end < L || start > R)
        return 0;
    if (L <= start && end <= R)
        return root->val;
    int mid = start + (end - start) / 2;
    return query(root->left, start, mid, L, R) + query(root->right, mid + 1, end, L, R);
}

int main()
{
    vector<int> a = {1, 2, 3, 4};
    int n = a.size();

    vector<Node *> versions;
    versions.push_back(build(a, 0, n - 1)); // Khởi tạo Version 0

    // Tạo Version 1 bằng cách thay đổi phần tử tại index 1 từ 2 thành 10
    versions.push_back(update(versions[0], 0, n - 1, 1, 10));

    cout << "--- DUYET TINH TONG THEO PHIEN BAN THOI GIAN ---\n";
    cout << "Tong doan [0, 2] o Version 0 (Qua khu): " << query(versions[0], 0, n - 1, 0, 2) << "\n";  // 1 + 2 + 3 = 6
    cout << "Tong doan [0, 2] o Version 1 (Hien tai): " << query(versions[1], 0, n - 1, 0, 2) << "\n"; // 1 + 10 + 3 = 14

    return 0;
}