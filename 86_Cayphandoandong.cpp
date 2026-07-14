#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node *left, *right;
    Node() : value(0), left(nullptr), right(nullptr) {}
};

// Cập nhật giá trị tại vị trí pos (Điểm)
void update(Node *&cur, int l, int r, int pos, int val)
{
    if (!cur)
        cur = new Node(); // Cấp phát động nút mới khi cần thiết

    if (l == r)
    {
        cur->value += val;
        return;
    }

    int mid = l + (r - l) / 2;
    if (pos <= mid)
    {
        update(cur->left, l, mid, pos, val);
    }
    else
    {
        update(cur->right, mid + 1, r, pos, val);
    }

    // Tính toán lại giá trị nút cha từ các con (nếu con tồn tại)
    cur->value = (cur->left ? cur->left->value : 0) + (cur->right ? cur->right->value : 0);
}

// Truy vấn tổng trên đoạn [ql, qr]
int query(Node *cur, int l, int r, int ql, int qr)
{
    if (!cur || ql > r || qr < l)
        return 0; // Vùng này chưa được khởi tạo hoặc ngoài khoảng
    if (ql <= l && r <= qr)
        return cur->value;

    int mid = l + (r - l) / 2;
    return query(cur->left, l, mid, ql, qr) + query(cur->right, mid + 1, r, ql, qr);
}

// Hàm giải phóng bộ nhớ để tránh rò rỉ (Memory Leak)
void freeTree(Node *cur)
{
    if (!cur)
        return;
    freeTree(cur->left);
    freeTree(cur->right);
    delete cur;
}

int main()
{
    Node *root = nullptr;
    int limitR = 1e9; // Giới hạn tọa độ cực lớn, lên tới 1 tỷ!

    // Cập nhật điểm tại các vị trí ngẫu nhiên cực xa nhau
    update(root, 1, limitR, 5, 10);
    update(root, 1, limitR, 999999999, 25); // Vị trí sát rìa 1 tỷ

    cout << "--- KET QUA DYNAMIC SEGMENT TREE ---\n";
    cout << "Tong tren doan [1, 10]: " << query(root, 1, limitR, 1, 10) << "\n";                 // Kết quả: 10
    cout << "Tong tren doan [500, 1000000000]: " << query(root, 1, limitR, 500, limitR) << "\n"; // Kết quả: 25

    freeTree(root);
    return 0;
}