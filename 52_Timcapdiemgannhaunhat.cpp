#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cfloat> // Thư viện sửa lỗi undefined identifier "DBL_MAX"
using namespace std;

struct Point
{
    double x, y;
};

// Hàm so sánh để sắp xếp theo trục X
bool compareX(Point a, Point b)
{
    return a.x < b.x;
}

// Hàm so sánh để sắp xếp theo trục Y
bool compareY(Point a, Point b)
{
    return a.y < b.y;
}

// Hàm tính khoảng cách giữa 2 điểm
double distance(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Tìm khoảng cách nhỏ nhất ở dải phân cách giữa hai nửa đồ thị
double closestStrip(vector<Point> &strip, double d)
{
    double minDist = d;
    sort(strip.begin(), strip.end(), compareY); // Sắp xếp theo trục Y

    for (size_t i = 0; i < strip.size(); i++)
    {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; j++)
        {
            minDist = min(minDist, distance(strip[i], strip[j]));
        }
    }
    return minDist;
}

// Hàm chia để trị cốt lõi
double findClosestUtil(vector<Point> &P, int start, int end)
{
    // Nếu còn ít hơn hoặc bằng 3 điểm, dùng phương pháp vét cạn (Brute Force)
    if (end - start <= 3)
    {
        double minDist = DBL_MAX; // Đã chạy mượt mà nhờ thư viện <cfloat>
        for (int i = start; i < end; i++)
        {
            for (int j = i + 1; j < end; j++)
            {
                minDist = min(minDist, distance(P[i], P[j]));
            }
        }
        return minDist;
    }

    int mid = start + (end - start) / 2;
    Point midPoint = P[mid];

    // Tính khoảng cách nhỏ nhất ở nửa trái và nửa phải độc lập
    double dl = findClosestUtil(P, start, mid);
    double dr = findClosestUtil(P, mid, end);
    double d = min(dl, dr);

    // Lọc các điểm nằm gần đường phân cách biên một khoảng nhỏ hơn d
    vector<Point> strip;
    for (int i = start; i < end; i++)
    {
        if (abs(P[i].x - midPoint.x) < d)
        {
            strip.push_back(P[i]);
        }
    }

    // So sánh khoảng cách d hiện tại với khoảng cách ở dải phân cách giữa
    return min(d, closestStrip(strip, d));
}

int main()
{
    // Khởi tạo tập hợp các điểm ngẫu nhiên trên hệ tọa độ 2D
    vector<Point> P = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};

    // Bước bắt buộc: Sắp xếp mảng theo trục X trước khi đưa vào chia để trị
    sort(P.begin(), P.end(), compareX);

    cout << "--- KET QUA TIM CAP DIEM GAN NHAT ---\n";
    cout << "Khoang cach nho nhat giua hai diem bat ky la: "
         << findClosestUtil(P, 0, P.size()) << endl;

    return 0;
}