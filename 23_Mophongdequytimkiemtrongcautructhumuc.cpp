#include <iostream>
#include <string>
using namespace std;

// Hàm đệ quy mô phỏng quét cây thư mục
// level dùng để tạo khoảng thụt đầu dòng (giúp dễ nhìn cấu trúc)
bool quetThuMuc(string tenThuMucHienTai, string tenFileCanTim, int level)
{
    // Tạo khoảng trống thụt lề dựa trên độ sâu (level)
    for (int i = 0; i < level; i++)
        cout << "  |";
    cout << "--[Thu muc: " << tenThuMucHienTai << "]\n";

    // Mô phỏng giả định: Nếu tới thư mục tên là "Dich", ta tìm thấy file
    if (tenThuMucHienTai == "Dich")
    {
        for (int i = 0; i <= level; i++)
            cout << "  |";
        cout << "--> TIM THAY FILE: " << tenFileCanTim << " o day!\n";
        return true;
    }

    // Giả định mỗi thư mục chỉ có tối đa 2 thư mục con để rẽ nhánh (Cây nhị phân)
    if (level < 2)
    { // Giới hạn độ sâu tối đa bằng 2 để tránh lặp vô hạn
        // Quét nhánh con thứ nhất
        if (quetThuMuc(tenThuMucHienTai + ".1", tenFileCanTim, level + 1))
            return true;

        // Nếu nhánh 1 không có, quét tiếp nhánh con thứ hai
        if (quetThuMuc(tenThuMucHienTai + ".2", tenFileCanTim, level + 1))
            return true;
    }

    return false; // Không tìm thấy ở nhánh này
}

int main()
{
    string fileCanTim = "BaoCao.docx";
    cout << "Bat dau quet o o dia C:\\...\n\n";

    // Giả sử nhánh "C.1.2" đổi tên thành "Dich" để thử nghiệm thuật toán tìm kiếm
    // Hệ thống sẽ duyệt đệ quy theo chiều sâu (DFS)
    bool timThay = quetThuMuc("C:", fileCanTim, 0);

    cout << "\n----------------------------------------\n";
    if (timThay)
    {
        cout << "Ket qua: Da tim thay file thanh cong!" << endl;
    }
    else
    {
        cout << "Ket qua: Khong tim thay file tren toan he thong." << endl;
    }

    return 0;
}