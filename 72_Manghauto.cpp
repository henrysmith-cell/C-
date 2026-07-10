#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Suffix
{
    int index;
    int rank[2]; // Lưu thứ hạng hiện tại và thứ hạng tiếp theo (phục vụ nhân đôi bước nhảy)
};

// Hàm so sánh để sắp xếp hai hậu tố
bool soSanhSuffix(Suffix a, Suffix b)
{
    if (a.rank[0] == b.rank[0])
        return a.rank[1] < b.rank[1];
    return a.rank[0] < b.rank[0];
}

vector<int> buildSuffixArray(string s)
{
    int n = s.length();
    vector<Suffix> suffixes(n);

    // Bước khởi tạo: Sắp xếp theo ký tự đầu tiên
    for (int i = 0; i < n; i++)
    {
        suffixes[i].index = i;
        suffixes[i].rank[0] = s[i] - 'a';
        suffixes[i].rank[1] = ((i + 1) < n) ? (s[i + 1] - 'a') : -1;
    }
    sort(suffixes.begin(), suffixes.end(), soSanhSuffix);

    vector<int> ind(n); // Mảng bổ trợ ánh xạ index
    // Tiến hành nhân đôi bước nhảy: 2, 4, 8, ... cho đến khi phủ hết chuỗi
    for (int k = 4; k < 2 * n; k = k * 2)
    {
        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = max(0, rank); // rank hiện tại luôn >= 0
        ind[suffixes[0].index] = 0;

        // Cập nhật lại thứ hạng (rank) mới dựa trên kết quả sắp xếp trước đó
        for (int i = 1; i < n; i++)
        {
            if (suffixes[i].rank[0] == prev_rank && suffixes[i].rank[1] == suffixes[i - 1].rank[1])
            {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            }
            else
            {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            ind[suffixes[i].index] = i;
        }

        // Cập nhật lại rank[1] (thành phần thứ hai sau khi nhảy k/2 bước)
        for (int i = 0; i < n; i++)
        {
            int nextindex = suffixes[i].index + k / 2;
            suffixes[i].rank[1] = (nextindex < n) ? suffixes[ind[nextindex]].rank[0] : -1;
        }
        sort(suffixes.begin(), suffixes.end(), soSanhSuffix);
    }

    vector<int> suffixArr(n);
    for (int i = 0; i < n; i++)
        suffixArr[i] = suffixes[i].index;
    return suffixArr;
}

int main()
{
    string s = "banana";
    vector<int> suffixArr = buildSuffixArray(s);

    cout << "--- SUFFIX ARRAY CUA CHUOI: " << s << " ---\n";
    for (int i = 0; i < s.length(); i++)
    {
        cout << "Vi tri " << i << " : Bat dau tu index " << suffixArr[i]
             << " -> \"" << s.substr(suffixArr[i]) << "\"\n";
    }
    return 0;
}