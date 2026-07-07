#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int KICH_THUOC_BLOCK;

struct TruyVan
{
    int L, R, id;
    bool operator<(const TruyVan &khac) const
    {
        if (L / KICH_THUOC_BLOCK != khac.L / KICH_THUOC_BLOCK)
            return L / KICH_THUOC_BLOCK < khac.L / KICH_THUOC_BLOCK;
        return R < khac.R;
    }
};

// Cấu trúc mô phỏng hành động "Ghi lại lịch sử" để có thể khôi phục dữ liệu
struct RollbackSystem
{
    int giaTriLuuTru;
    int *diaChiBien;
};

vector<RollbackSystem> lichSu;

void thayDoiBien(int &bien, int giaTriMoi)
{
    lichSu.push_back({bien, &bien}); // Lưu lại giá trị cũ và địa chỉ biến
    bien = giaTriMoi;
}

void rollback(int thoiDiemGoc)
{
    while (lichSu.size() > thoiDiemGoc)
    {
        RollbackSystem r = lichSu.back();
        *(r.diaChiBien) = r.giaTriLuuTru; // Khôi phục lại giá trị cũ cho biến
        lichSu.pop_back();
    }
}

int main()
{
    vector<int> A = {2, 1, 3, 2, 1};
    int n = A.size();
    KICH_THUOC_BLOCK = sqrt(n);

    vector<TruyVan> dsTruyVan = {{0, 2, 0}, {0, 4, 1}, {1, 3, 2}};
    int q = dsTruyVan.size();
    sort(dsTruyVan.begin(), dsTruyVan.end());

    vector<int> ketQua(q);
    int hienTai = 0; // Biến giả lập cấu trúc dữ liệu cần quản lý

    int blockTruoc = -1;
    int currR = -1;

    for (int i = 0; i < q; i++)
    {
        int L = dsTruyVan[i].L;
        int R = dsTruyVan[i].R;
        int blockHienTai = L / KICH_THUOC_BLOCK;

        // Nếu chuyển sang một khối L mới, Reset lại hệ thống con trỏ R
        if (blockHienTai != blockTruoc)
        {
            currR = (blockHienTai + 1) * KICH_THUOC_BLOCK - 1;
            hienTai = 0; // Reset cấu trúc dữ liệu
            lichSu.clear();
            blockTruoc = blockHienTai;
        }

        // Trường hợp đặc biệt: L và R nằm chung trong một khối nhỏ -> Vét cạn trực tiếp
        if (L / KICH_THUOC_BLOCK == R / KICH_THUOC_BLOCK)
        {
            int dapAnGoc = 0; // Tính toán thủ công trực tiếp cho đoạn ngắn
            for (int k = L; k <= R; k++)
                dapAnGoc += A[k];
            ketQua[dsTruyVan[i].id] = dapAnGoc;
            continue;
        }

        // Bước 1: Liên tục dịch con trỏ R tiến lên (Thao tác Thêm phần tử, không bao giờ lùi R)
        while (currR < R)
        {
            currR++;
            hienTai += A[currR]; // Giả lập thêm phần tử vào cấu trúc dữ liệu
        }

        // Bước 2: Lưu lại mốc thời gian hiện tại trước khi đẩy L lùi về phía trước
        int moscThoiGian = lichSu.size();
        int giaTriRong = hienTai;

        // Tạm thời thêm các phần tử từ đầu Khối hiện tại lùi về L
        int startL = (blockHienTai + 1) * KICH_THUOC_BLOCK;
        for (int k = startL - 1; k >= L; k--)
        {
            thayDoiBien(hienTai, hienTai + A[k]);
        }

        ketQua[dsTruyVan[i].id] = hienTai; // Lưu kết quả truy vấn

        // Bước 3: RÚT LẠI (Rollback) toàn bộ thao tác thêm của L để đưa trạng thái về mốc ban đầu
        rollback(moscThoiGian);
        hienTai = giaTriRong;
    }

    cout << "--- KET QUA MO KHONG XOA (ROLLBACK) ---\n";
    for (int i = 0; i < q; i++)
        cout << "Truy van " << i << " : " << ketQua[i] << "\n";

    return 0;
}