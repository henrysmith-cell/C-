#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct TreapNode
{
    int key, priority;
    TreapNode *left, *right;
    TreapNode(int k) : key(k), priority(rand() % 100), left(nullptr), right(nullptr) {}
};

// Hàm chia một Treap thành 2 Treap độc lập dựa trên khóa khóa phân tách K
void split(TreapNode *root, int key, TreapNode *&l, TreapNode *&r)
{
    if (!root)
    {
        l = r = nullptr;
    }
    else if (root->key <= key)
    {
        split(root->right, key, root->right, r);
        l = root;
    }
    else
    {
        split(root->left, key, l, root->left);
        r = root;
    }
}

// Hàm gộp hai Treap l và r thành một Treap duy nhất (Yêu cầu mọi khóa ở l đều nhỏ hơn ở r)
void merge(TreapNode *&root, TreapNode *l, TreapNode *r)
{
    if (!l || !r)
    {
        root = l ? l : r;
    }
    else if (l->priority > r->priority)
    {
        merge(l->right, l->right, r);
        root = l;
    }
    else
    {
        merge(r->left, l, r->left);
        root = r;
    }
}

// Thêm một phần tử mới vào Treap
void insert(TreapNode *&root, int key)
{
    TreapNode *l;
    TreapNode *r;
    TreapNode *nn = new TreapNode(key);
    split(root, key, l, r);
    merge(l, l, nn);
    merge(root, l, r);
}

// Duyệt cây theo thứ tự giữa (In-order) để in ra dãy số đã sắp xếp
void inorder(TreapNode *root)
{
    if (!root)
        return;
    inorder(root->left);
    cout << root->key << " (prio:" << root->priority << ") ";
    inorder(root->right);
}

int main()
{
    srand(time(0));
    TreapNode *root = nullptr;

    // Chèn dữ liệu theo thứ tự nguy hiểm tăng dần
    insert(root, 10);
    insert(root, 20);
    insert(root, 30);
    insert(root, 40);
    insert(root, 50);

    cout << "--- DUYET IN-ORDER TREAP ---\nDãy phần tử đã tự động sắp xếp và cân bằng:\n";
    inorder(root);
    cout << "\n";

    return 0;
}