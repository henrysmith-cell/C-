#include <iostream>
using namespace std;

// Định nghĩa cấu trúc của một cái nút (Node)
struct Node
{
    int data;   // Dữ liệu lưu trong Node
    Node *next; // Con trỏ trỏ đến Node tiếp theo
};

// Hàm tạo ra một Node mới
Node *taoNode(int giaTri)
{
    Node *nodeMoi = new Node(); // Cấp phát động
    nodeMoi->data = giaTri;
    nodeMoi->next = nullptr;
    return nodeMoi;
}

// Hàm chèn một Node vào đầu danh sách (sử dụng con trỏ cấp 2 hoặc tham chiếu &)
void chenVaoDau(Node *&head, int giaTri)
{
    Node *nodeMoi = taoNode(giaTri);
    nodeMoi->next = head; // Node mới trỏ tới Node đầu hiện tại
    head = nodeMoi;       // Cập nhật lại Node đầu là Node mới
}

// Hàm in danh sách liên kết
void inDanhSach(Node *head)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        cout << temp->data << " -> ";
        temp = temp->next; // Chuyển sang Node tiếp theo
    }
    cout << "NULL\n";
}

int main()
{
    Node *head = nullptr; // Khởi tạo danh sách rỗng

    chenVaoDau(head, 10);
    chenVaoDau(head, 20);
    chenVaoDau(head, 30);

    cout << "Danh sach lien ket don da tao: ";
    inDanhSach(head);

    // Giải phóng bộ nhớ trước khi thoát chương trình
    while (head != nullptr)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}