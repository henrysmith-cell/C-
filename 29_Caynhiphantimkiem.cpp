#include <iostream>
using namespace std;

// Định nghĩa một nút trên Cây
struct Node
{
    int data;
    Node *left;
    Node *right;
};

// Hàm tạo nút mới
Node *taoNode(int giaTri)
{
    Node *nodeMoi = new Node();
    nodeMoi->data = giaTri;
    nodeMoi->left = nullptr;
    nodeMoi->right = nullptr;
    return nodeMoi;
}

// Hàm chèn một giá trị vào Cây BST
Node *chen(Node *root, int giaTri)
{
    if (root == nullptr)
    {
        return taoNode(giaTri);
    }

    // Nếu giá trị nhỏ hơn nút hiện tại -> đi sang trái
    if (giaTri < root->data)
    {
        root->left = chen(root->left, giaTri);
    }
    // Nếu giá trị lớn hơn nút hiện tại -> đi sang phải
    else if (giaTri > root->data)
    {
        root->right = chen(root->right, giaTri);
    }

    return root;
}

// Hàm duyệt cây theo thứ tự In-order (Luôn cho ra mảng tăng dần)
void inOrder(Node *root)
{
    if (root != nullptr)
    {
        inOrder(root->left);       // Duyệt nhánh trái
        cout << root->data << " "; // Duyệt nút cha
        inOrder(root->right);      // Duyệt nhánh phải
    }
}

int main()
{
    Node *root = nullptr;

    // Chèn dữ liệu lộn xộn vào cây
    root = chen(root, 50);
    chen(root, 30);
    chen(root, 20);
    chen(root, 40);
    chen(root, 70);
    chen(root, 60);
    chen(root, 80);

    cout << "Cac phan tu trong cay sau khi duyet In-order: ";
    inOrder(root);
    cout << endl;

    return 0;
}