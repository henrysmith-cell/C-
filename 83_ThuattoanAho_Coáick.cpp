#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

const int KICH_THUOC_ALPHABET = 26;

struct Node
{
    int child[KICH_THUOC_ALPHABET];
    int fail;                // Con trỏ thất bại (tương tự mảng lps của KMP)
    vector<int> pattern_ids; // Lưu id của các chuỗi kết thúc tại đây

    Node()
    {
        for (int i = 0; i < KICH_THUOC_ALPHABET; i++)
            child[i] = 0;
        fail = 0;
    }
};

vector<Node> trie;

void insertPattern(const string &s, int id)
{
    int u = 0;
    for (char c : s)
    {
        int idx = c - 'a';
        if (!trie[u].child[idx])
        {
            trie[u].child[idx] = trie.size();
            trie.push_back(Node());
        }
        u = trie[u].child[idx];
    }
    trie[u].pattern_ids.push_back(id);
}

// Xây dựng các đường link thất bại (Failure links) bằng BFS
void buildAhoCorasick()
{
    queue<int> q;
    for (int i = 0; i < KICH_THUOC_ALPHABET; i++)
    {
        if (trie[0].child[i])
            q.push(trie[0].child[i]);
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < KICH_THUOC_ALPHABET; i++)
        {
            int v = trie[u].child[i];
            if (v)
            {
                int f = trie[u].fail;
                while (f && !trie[f].child[i])
                    f = trie[f].fail;
                trie[v].fail = trie[f].child[i];

                // Gộp các mẫu kết thúc của nút thất bại vào nút hiện tại
                for (int id : trie[trie[v].fail].pattern_ids)
                {
                    trie[v].pattern_ids.push_back(id);
                }
                q.push(v);
            }
        }
    }
}

int main()
{
    trie.push_back(Node()); // Nút gốc
    vector<string> patterns = {"he", "she", "his", "hers"};

    for (int i = 0; i < patterns.size(); i++)
    {
        insertPattern(patterns[i], i);
    }
    buildAhoCorasick();

    string vanBan = "ahishers";
    int u = 0;
    cout << "--- KET QUA AHO-CORASICK ---\nQuét văn bản '" << vanBan << "':\n";

    for (int i = 0; i < vanBan.length(); i++)
    {
        int idx = vanBan[i] - 'a';
        while (u && !trie[u].child[idx])
            u = trie[u].fail;
        u = trie[u].child[idx];

        if (!trie[u].pattern_ids.empty())
        {
            for (int id : trie[u].pattern_ids)
            {
                cout << "Tim thay tu khoa \"" << patterns[id] << "\" ket thuc tai vi tri " << i << "\n";
            }
        }
    }
    return 0;
}