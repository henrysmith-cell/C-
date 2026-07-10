#include <iostream>
using namespace std;

struct Node
{
    int val;
    Node *left, *right;
    Node() : val(0), left(nullptr), right(nullptr) {}
};

// Hàm cập nhật điểm cho cây phân đoạn động
void update(Node *&cur, int start, int end, int idx, int val)
{
    // Nếu nút hiện tại chưa được cấp phát, tiến hành khởi tạo "động"
    if (cur == nullptr)
        cur = new Node();

    if (start == end)
    {
        cur->val += val; // Cập nhật giá trị tại nút lá
        return;
    }

    int mid = start + (end - start) / 2;
    if (idx <= mid)
    {
        update(cur->left, start, mid, idx, val);
    }
    else
    {
        update(cur->right, mid + 1, end, idx, val);
    }

    // Tính toán lại giá trị của nút cha dựa trên các con (nếu có)
    int leftVal = (cur->left != nullptr) ? cur->left->val : 0;
    int rightVal = (cur->right != nullptr) ? cur->right->val : 0;
    cur->val = leftVal + rightVal;
}

// Hàm truy vấn tổng đoạn [L, R] trên không gian tọa độ cực lớn
int query(Node *cur, int start, int end, int L, int R)
{
    if (cur == nullptr || end < L || start > R)
        return 0;
    if (L <= start && end <= R)
        return cur->val;

    int mid = start + (end - start) / 2;
    return query(cur->left, start, mid, L, R) + query(cur->right, mid + 1, end, L, R);
}

int main()
{
    Node *root = nullptr;
    int n = 1000000000; // Không gian tọa độ khổng lồ: 10^9

    // Cập nhật giá trị tại các vị trí nằm rất xa nhau
    update(root, 0, n - 1, 5, 10);
    update(root, 0, n - 1, 999999995, 20);

    cout << "--- KET QUA TRUY VAN TREN CAY DONG ---\n";
    cout << "Tong doan [0, 10]: " << query(root, 0, n - 1, 0, 10) << "\n";                           // Kết quả: 10
    cout << "Tong doan [999999000, 999999999]: " << query(root, 0, n - 1, 999999000, n - 1) << "\n"; // Kết quả: 20

    return 0;
}