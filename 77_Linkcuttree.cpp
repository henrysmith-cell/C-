#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Đại diện cho một nút trong Link-Cut Tree sử dụng cơ chế Splay Tree ngầm định
struct Node
{
    int id;
    Node *left, *right, *parent;
    bool revert; // Biến đánh dấu lật ngược đoạn (Lazy propagation cho thao tác splay)

    Node(int id) : id(id), left(nullptr), right(nullptr), parent(nullptr), revert(false) {}

    // Kiểm tra xem nút hiện tại có phải là nút gốc của một Splay Tree (Preferred Path) hay không
    bool isRoot()
    {
        return parent == nullptr || (parent->left != this && parent->right != this);
    }
};

// Hàm đẩy các thay đổi lười (Lazy updates) xuống các nút con
void push(Node *u)
{
    if (u && u->revert)
    {
        swap(u->left, u->right);
        if (u->left)
            u->left->revert ^= true;
        if (u->right)
            u->right->revert ^= true;
        u->revert = false;
    }
}

// Thao tác xoay cây nội bộ của Splay Tree
void rotate(Node *u)
{
    Node *p = u->parent;
    Node *g = p->parent;
    if (!p->isRoot())
    {
        if (g->left == p)
            g->left = u;
        else
            g->right = u;
    }
    u->parent = g;
    if (p->left == u)
    {
        p->left = u->right;
        if (u->right)
            u->right->parent = p;
        u->right = p;
    }
    else
    {
        p->right = u->left;
        if (u->left)
            u->left->parent = p;
        u->left = p;
    }
    p->parent = u;
}

// Hàm đẩy toàn bộ các tag trễ từ gốc xuống nút u trước khi thực hiện xoay
void pushAll(Node *u)
{
    if (!u->isRoot())
        pushAll(u->parent);
    push(u);
}

// Đưa nút u lên làm gốc của Splay Tree chứa nó
void splay(Node *u)
{
    pushAll(u);
    while (!u->isRoot())
    {
        Node *p = u->parent;
        if (!p->isRoot())
        {
            if ((p->parent->left == p) == (p->left == u))
                rotate(p);
            else
                rotate(u);
        }
        rotate(u);
    }
}

// Thao tác cốt lõi: Tạo một đường đi nối liền từ gốc của cây thực đến nút u
Node *access(Node *u)
{
    Node *last = nullptr;
    for (Node *v = u; v != nullptr; v = v->parent)
    {
        splay(v);
        v->right = last; // Đổi hướng cạnh ưu tiên (Preferred Edge)
        last = v;
    }
    splay(u);
    return last;
}

// Biến nút u thành gốc của toàn bộ cây thực
void makeRoot(Node *u)
{
    access(u);
    u->revert ^= true;
}

// Phép nối (Link): Nối cây chứa nút u vào làm con của nút v
void link(Node *u, Node *v)
{
    makeRoot(u);
    u->parent = v;
}

// Phép cắt (Cut): Xóa bỏ cạnh nối giữa u và v
void cut(Node *u, Node *v)
{
    makeRoot(u);
    access(v);
    if (v->left == u)
    {
        v->left = nullptr;
        u->parent = nullptr;
    }
}

int main()
{
    // Khởi tạo 4 nút độc lập (Rừng gồm 4 cây, mỗi cây 1 nút)
    vector<Node *> tree;
    for (int i = 0; i < 4; i++)
        tree.push_back(new Node(i));

    // Thực hiện nối các nút động tại thời điểm chạy (Runtime)
    link(tree[0], tree[1]); // Cạnh 0-1
    link(tree[1], tree[2]); // Cạnh 1-2
    link(tree[2], tree[3]); // Cạnh 2-3

    cout << "--- KET QUA LINK-CUT TREE ---\n";
    cout << "Da dung thanh cong mot cay dong gom 4 nut lien thong.\n";

    // Thử nghiệm cắt rời cạnh giữa nút 1 và nút 2
    cut(tree[1], tree[2]);
    cout << "Da cat canh giua nut 1 va nut 2 trong thoi gian thuc.\n";

    // Giải phóng bộ nhớ
    for (auto node : tree)
        delete node;
    return 0;
}