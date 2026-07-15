#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node
{
    int key, priority;
    Node *left, *right;
    Node(int k) : key(k), priority(rand()), left(nullptr), right(nullptr) {}
};

// Thao tác xoay phải để bảo toàn tính chất Heap
Node *rotateRight(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    return x;
}

// Thao tác xoay trái để bảo toàn tính chất Heap
Node *rotateLeft(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    return y;
}

// Thêm một khóa mới vào Treap
Node *insert(Node *root, int key)
{
    if (!root)
        return new Node(key);

    if (key < root->key)
    {
        root->left = insert(root->left, key);
        // Nếu vi phạm tính chất Heap, thực hiện xoay
        if (root->left->priority > root->priority)
        {
            root = rotateRight(root);
        }
    }
    else
    {
        root->right = insert(root->right, key);
        if (root->right->priority > root->priority)
        {
            root = rotateLeft(root);
        }
    }
    return root;
}

// Tìm kiếm một khóa trên Treap
bool search(Node *root, int key)
{
    if (!root)
        return false;
    if (root->key == key)
        return true;
    if (key < root->key)
        return search(root->left, key);
    return search(root->right, key);
}

// In cây theo thứ tự giữa (Inorder) để kiểm tra tính chất BST (luôn tăng dần)
void inorder(Node *root)
{
    if (root)
    {
        inorder(root->left);
        cout << root->key << " (Pri: " << root->priority << ") | ";
        inorder(root->right);
    }
}

int main()
{
    srand(time(0));
    Node *root = nullptr;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);

    cout << "--- KET QUA DUYET TREAP (INORDER) ---\n";
    inorder(root);
    cout << "\n\n";

    cout << "Tim kiem khoa 40: " << (search(root, 40) ? "Tim thay" : "Khong tim thay") << "\n";
    cout << "Tim kiem khoa 90: " << (search(root, 90) ? "Tim thay" : "Khong tim thay") << "\n";
    return 0;
}