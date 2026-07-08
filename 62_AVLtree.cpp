#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
    int key;
    Node *left, *right;
    int height;
};

// Hàm lấy chiều cao của nút
int getHeight(Node *n)
{
    return n == nullptr ? 0 : n->height;
}

// Tạo một nút mới
Node *newNode(int key)
{
    Node *node = new Node();
    node->key = key;
    node->left = node->right = nullptr;
    node->height = 1; // Nút mới ban đầu được thêm vào tầng lá
    return node;
}

// Phép xoay phải (Right Rotate) khi nhánh trái quá nặng
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x; // Nút gốc mới
}

// Phép xoay trái (Left Rotate) khi nhánh phải quá nặng
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y; // Nút gốc mới
}

// Lấy hệ số cân bằng (Balance Factor) của nút
int getBalance(Node *n)
{
    return n == nullptr ? 0 : getHeight(n->left) - getHeight(n->right);
}

// Hàm chèn phần tử đệ quy và tự cân bằng
Node *insert(Node *node, int key)
{
    if (node == nullptr)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // Không chấp nhận key trùng nhau

    // 1. Cập nhật chiều cao của nút cha
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // 2. Kiểm tra hệ số cân bằng để xem cây có bị lệch không
    int balance = getBalance(node);

    // Trường hợp Lệch Trái Trái (Left Left)
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Trường hợp Lệch Phải Phải (Right Right)
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Trường hợp Lệch Trái Phải (Left Right)
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Trường hợp Lệch Phải Trái (Right Left)
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void preOrder(Node *root)
{
    if (root != nullptr)
    {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main()
{
    Node *root = nullptr;

    // Chèn chuỗi số khiến cây nhị phân thông thường bị lệch hẳn về bên phải
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30); // Tại bước này cây tự xoay trái để cân bằng
    root = insert(root, 40);
    root = insert(root, 50);

    cout << "--- DUYET CAY AVL (PREORDER) ---\n";
    preOrder(root); // Kết quả gốc sẽ là 30 thay vì bị lệch dài từ 10
    cout << endl;

    return 0;
}