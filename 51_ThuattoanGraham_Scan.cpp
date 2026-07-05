#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

struct Diem
{
    int x, y;
};

Diem p0; // Điểm gốc có tung độ nhỏ nhất

// Tìm bình phương khoảng cách giữa 2 điểm
int binhPhuongKhoangCach(Diem d1, Diem d2)
{
    return (d1.x - d2.x) * (d1.x - d2.x) + (d1.y - d2.y) * (d1.y - d2.y);
}

// Hàm kiểm tra hướng đi của 3 điểm (Thao tác CCW - Counter-Clockwise)
// Trả về: 0 nếu thẳng hàng, 1 nếu rẽ trái (ngược chiều kim đồng hồ), 2 nếu rẽ phải
int huongRe(Diem a, Diem b, Diem c)
{
    int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (val == 0)
        return 0;
    return (val > 0) ? 2 : 1;
}

// Hàm so sánh để sắp xếp các điểm theo góc cực đối với điểm p0
bool soSanhGoc(Diem d1, Diem d2)
{
    int order = huongRe(p0, d1, d2);
    if (order == 0)
        return binhPhuongKhoangCach(p0, d2) >= binhPhuongKhoangCach(p0, d1);
    return (order == 1);
}

void timBaoLoi(vector<Diem> &dsDiem)
{
    int n = dsDiem.size();
    if (n < 3)
        return;

    // Bước 1: Tìm điểm có y nhỏ nhất (nếu bằng nhau thì chọn x nhỏ nhất)
    int ymin = dsDiem[0].y, minIdx = 0;
    for (int i = 1; i < n; i++)
    {
        int y = dsDiem[i].y;
        if ((y < ymin) || (ymin == y && dsDiem[i].x < dsDiem[minIdx].x))
        {
            ymin = dsDiem[i].y;
            minIdx = i;
        }
    }
    swap(dsDiem[0], dsDiem[minIdx]);
    p0 = dsDiem[0];

    // Bước 2: Sắp xếp các điểm còn lại theo góc cực
    sort(dsDiem.begin() + 1, dsDiem.end(), soSanhGoc);

    // Bước 3: Dùng stack để xây dựng bao lồi
    stack<Diem> st;
    st.push(dsDiem[0]);
    st.push(dsDiem[1]);
    st.push(dsDiem[2]);

    for (int i = 3; i < n; i++)
    {
        while (st.size() > 1)
        {
            Diem top2 = st.top();
            st.pop();
            Diem top1 = st.top();
            // Nếu rẽ trái thì điểm top2 hợp lệ, đẩy lại vào stack và dừng vòng lặp
            if (huongRe(top1, top2, dsDiem[i]) == 1)
            {
                st.push(top2);
                break;
            }
        }
        st.push(dsDiem[i]);
    }

    cout << "--- CAC DIEM THUOC BAO LOI ---\n";
    while (!st.empty())
    {
        Diem p = st.top();
        cout << "(" << p.x << ", " << p.y << ")\n";
        st.pop();
    }
}

int main()
{
    vector<Diem> dsDiem = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    timBaoLoi(dsDiem);
    return 0;
}