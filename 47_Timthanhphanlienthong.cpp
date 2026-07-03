#include <iostream>
#include <string>
using namespace std;

// Định nghĩa một nút trên cây Trie
struct TrieNode
{
    TrieNode *con[26]; // 26 chữ cái tiếng Anh từ 'a' đến 'z'
    bool laCuoiTu;     // Đánh dấu điểm kết thúc của một từ hoàn chỉnh

    TrieNode()
    {
        laCuoiTu = false;
        for (int i = 0; i < 26; i++)
        {
            con[i] = nullptr;
        }
    }
};

// Hàm thêm từ vào Trie
void insert(TrieNode *root, string tu)
{
    TrieNode *p = root;
    for (char c : tu)
    {
        int index = c - 'a';
        if (p->con[index] == nullptr)
        {
            p->con[index] = new TrieNode();
        }
        p = p->con[index];
    }
    p->laCuoiTu = true; // Đánh dấu kết thúc từ
}

// Hàm tìm kiếm từ trên Trie
bool search(TrieNode *root, string tu)
{
    TrieNode *p = root;
    for (char c : tu)
    {
        int index = c - 'a';
        if (p->con[index] == nullptr)
        {
            return false; // Không tìm thấy ký tự tiếp theo
        }
        p = p->con[index];
    }
    return p->laCuoiTu; // Trả về true nếu đây đúng là điểm kết thúc từ
}

int main()
{
    TrieNode *root = new TrieNode();

    insert(root, "apple");
    insert(root, "app");

    cout << "Tim 'apple': " << (search(root, "apple") ? "Co" : "Khong") << "\n";
    cout << "Tim 'app': " << (search(root, "app") ? "Co" : "Khong") << "\n";
    cout << "Tim 'banana': " << (search(root, "banana") ? "Co" : "Khong") << "\n";

    return 0;
}