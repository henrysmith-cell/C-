#include <iostream>
#include <vector>
using namespace std;

class MyQueue
{
private:
    vector<int> q;

public:
    // Thêm phần tử vào cuối hàng đợi
    void enqueue(int x)
    {
        q.push_back(x);
        cout << "Da them " << x << " vao hang doi.\n";
    }

    // Xóa phần tử ở đầu hàng đợi
    void dequeue()
    {
        if (q.empty())
        {
            cout << "Hang doi rong, khong the xoa!\n";
            return;
        }
        cout << "Da lay " << q.front() << " ra khoi hang doi.\n";
        q.erase(q.begin()); // Xóa phần tử đầu tiên
    }

    // Xem phần tử ở đầu hàng
    void xemDau()
    {
        if (!q.empty())
        {
            cout << "Phan tu dau hang hien tai: " << q.front() << endl;
        }
        else
        {
            cout << "Hang doi rong.\n";
        }
    }
};

int main()
{
    MyQueue hangDoi;

    hangDoi.enqueue(5);
    hangDoi.enqueue(10);
    hangDoi.enqueue(15);

    hangDoi.xemDau();

    hangDoi.dequeue();
    hangDoi.xemDau();

    return 0;
}