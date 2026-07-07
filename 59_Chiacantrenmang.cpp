#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct SquareRootDecomposition
{
    int n, kichThuocBlock;
    vector<int> a;
    vector<int> blocks; // Lưu tổng của từng khối (block)

    SquareRootDecomposition(vector<int> &mangGoc)
    {
        a = mangGoc;
        n = a.size();
        kichThuocBlock = ceil(sqrt(n)); // Độ rộng mỗi khối bằng căn bậc hai của N
        blocks.assign(kichThuocBlock, 0);

        // Tính toán trước tổng của từng khối
        for (int i = 0; i < n; i++)
        {
            blocks[i / kichThuocBlock] += a[i];
        }
    }

    // Cập nhật phần tử tại index thành giá trị mới trong O(1)
    void update(int idx, int giaTriMoi)
    {
        int idBlock = idx / kichThuocBlock;
        blocks[idBlock] += (giaTriMoi - a[idx]); // Cập nhật tổng khối tương ứng
        a[idx] = giaTriMoi;
    }

    // Truy vấn tính tổng đoạn [L, R] trong O(căn N)
    int queryTổng(int L, int R)
    {
        int tong = 0;
        int cL = L / kichThuocBlock;
        int cR = R / kichThuocBlock;

        if (cL == cR)
        { // Nếu L và R nằm chung một khối
            for (int i = L; i <= R; i++)
                tong += a[i];
        }
        else
        {
            // Tính phần lẻ ở khối đầu tiên
            for (int i = L; i < (cL + 1) * kichThuocBlock; i++)
                tong += a[i];
            // Tính các khối nguyên nằm trọn ở giữa
            for (int i = cL + 1; i < cR; i++)
                tong += blocks[i];
            // Tính phần lẻ ở khối cuối cùng
            for (int i = cR * kichThuocBlock; i <= R; i++)
                tong += a[i];
        }
        return tong;
    }
};

int main()
{
    vector<int> mangGoc = {1, 5, 2, 4, 6, 1, 3, 5, 7, 10};
    SquareRootDecomposition srd(mangGoc);

    cout << "Tong doan [2, 7] ban dau: " << srd.queryTổng(2, 7) << "\n"; // 2+4+6+1+3+5 = 21

    // Cập nhật phần tử tại vị trí số 4 (giá trị hiện tại là 6) thành giá trị 10
    srd.update(4, 10);
    cout << "Tong doan [2, 7] sau khi update: " << srd.queryTổng(2, 7) << "\n"; // 2+4+10+1+3+5 = 25

    return 0;
}