#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Suffix
{
    int index;
    int rank[2]; // Lưu rank hiện tại và rank kế tiếp (để sắp xếp gấp đôi tiền tố)
};

// Hàm so sánh hai hậu tố dựa trên cặp rank
bool compareSuffixes(const Suffix &a, const Suffix &b)
{
    if (a.rank[0] == b.rank[0])
    {
        return a.rank[1] < b.rank[1];
    }
    return a.rank[0] < b.rank[0];
}

vector<int> buildSuffixArray(string txt)
{
    int n = txt.length();
    vector<Suffix> suffixes(n);

    // Khởi tạo rank ban đầu dựa trên ký tự đầu tiên
    for (int i = 0; i < n; i++)
    {
        suffixes[i].index = i;
        suffixes[i].rank[0] = txt[i] - 'a';
        suffixes[i].rank[1] = ((i + 1) < n) ? (txt[i + 1] - 'a') : -1;
    }

    // Sắp xếp các hậu tố dựa trên 2 ký tự đầu tiên
    sort(suffixes.begin(), suffixes.end(), compareSuffixes);

    vector<int> ind(n); // Mảng hỗ trợ ánh xạ chỉ số
    for (int k = 4; k < 2 * n; k = k * 2)
    {
        // Gán lại rank mới dựa trên kết quả sắp xếp trước đó
        int rank_hien_tai = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank_hien_tai;
        ind[suffixes[0].index] = 0;

        for (int i = 1; i < n; i++)
        {
            if (suffixes[i].rank[0] == prev_rank && suffixes[i].rank[1] == suffixes[i - 1].rank[1])
            {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank_hien_tai;
            }
            else
            {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank_hien_tai;
            }
            ind[suffixes[i].index] = i;
        }

        // Cập nhật rank[1] (rank của phần hậu tố tiếp sau có độ dài k/2)
        for (int i = 0; i < n; i++)
        {
            int nextindex = suffixes[i].index + k / 2;
            suffixes[i].rank[1] = (nextindex < n) ? suffixes[ind[nextindex]].rank[0] : -1;
        }

        // Sắp xếp lại dựa trên thông tin rank mới cập nhật
        sort(suffixes.begin(), suffixes.end(), compareSuffixes);
    }

    vector<int> suffixArr(n);
    for (int i = 0; i < n; i++)
    {
        suffixArr[i] = suffixes[i].index;
    }
    return suffixArr;
}

int main()
{
    string txt = "banana";
    vector<int> suffixArr = buildSuffixArray(txt);

    cout << "--- KET QUA SUFFIX ARRAY CHO CHUOI \"" << txt << "\" ---\n";
    for (int i = 0; i < suffixArr.size(); i++)
    {
        cout << "Index: " << suffixArr[i] << " \t Hậu tố: " << txt.substr(suffixArr[i]) << "\n";
    }
    return 0;
}