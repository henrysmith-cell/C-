#include <iostream>
#include <vector>
#include <string>
using namespace std;

class BloomFilter
{
private:
    int size;
    vector<bool> bitArray;

    // Hàm băm thứ nhất (DJB2 Hash)
    int hash1(const string &str) const
    {
        unsigned long hash = 5381;
        for (char c : str)
            hash = ((hash << 5) + hash) + c;
        return hash % size;
    }

    // Hàm băm thứ hai (MurmurHash đơn giản)
    int hash2(const string &str) const
    {
        unsigned long hash = 0;
        for (char c : str)
        {
            hash += c;
            hash += (hash << 10);
            hash ^= (hash >> 6);
        }
        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);
        return hash % size;
    }

public:
    BloomFilter(int m) : size(m), bitArray(m, false) {}

    // Thêm phần tử vào bộ lọc bằng cách bật các bit tại vị trí băm lên true
    void insert(const string &str)
    {
        bitArray[hash1(str)] = true;
        bitArray[hash2(str)] = true;
    }

    // Kiểm tra xem phần tử có khả năng tồn tại hay không
    bool contains(const string &str)
    {
        // Chỉ cần một trong các vị trí bit bằng false, khẳng định chắc chắn 100% chưa tồn tại
        if (!bitArray[hash1(str)])
            return false;
        if (!bitArray[hash2(str)])
            return false;
        return true; // Có thể tồn tại (xác suất dương tính giả phụ thuộc vào kích thước mảng bit)
    }
};

int main()
{
    BloomFilter filter(100); // Mảng 100 bit siêu tiết kiệm bộ nhớ

    filter.insert("laptrinhvien");
    filter.insert("cpp_master");

    cout << "--- KET QUA KIEM TRA BLOOM FILTER ---\n";
    cout << "Kiem tra 'laptrinhvien': " << (filter.contains("laptrinhvien") ? "Co the co" : "Chac chan khong") << "\n";
    cout << "Kiem tra 'algorithm': " << (filter.contains("algorithm") ? "Co the co" : "Chac chan khong") << "\n";

    return 0;
}