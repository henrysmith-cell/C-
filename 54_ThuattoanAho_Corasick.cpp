#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

const int ALPHABET_SIZE = 26;

struct Node
{
    int next[ALPHABET_SIZE];
    int fail;
    vector<int> word_ids; // Lưu ID các từ kết thúc tại nút này

    Node()
    {
        fill(next, next + ALPHABET_SIZE, -1);
        fail = -1;
    }
};

vector<Node> trie;

void insert(const string &s, int id)
{
    int cur = 0;
    for (char c : s)
    {
        int idx = c - 'a';
        if (trie[cur].next[idx] == -1)
        {
            trie[cur].next[idx] = trie.size();
            trie.push_back(Node());
        }
        cur = trie[cur].next[idx];
    }
    trie[cur].word_ids.push_back(id);
}

// Xây dựng các liên kết thất bại (Failure Links) bằng BFS
void build_automaton()
{
    queue<int> q;
    trie[0].fail = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (trie[0].next[i] != -1)
        {
            trie[trie[0].next[i]].fail = 0;
            q.push(trie[0].next[i]);
        }
        else
        {
            trie[0].next[i] = 0;
        }
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            int v = trie[u].next[i];
            if (v != -1)
            {
                int f = trie[u].fail;
                while (trie[f].next[i] == -1)
                    f = trie[f].fail;
                trie[v].fail = trie[f].next[i];

                // Gộp các từ tìm thấy từ liên kết thất bại vào nút hiện tại
                trie[v].word_ids.insert(trie[v].word_ids.end(),
                                        trie[trie[v].fail].word_ids.begin(),
                                        trie[trie[v].fail].word_ids.end());
                q.push(v);
            }
            else
            {
                trie[u].next[i] = trie[trie[u].fail].next[i];
            }
        }
    }
}

int main()
{
    trie.push_back(Node()); // Tạo nút gốc 0
    vector<string> mau = {"he", "she", "his", "hers"};

    for (int i = 0; i < mau.size(); i++)
    {
        insert(mau[i], i);
    }
    build_automaton();

    string vanBan = "ahishers";
    int cur = 0;
    cout << "Van ban goc: " << vanBan << "\n--- KET QUA QUET VAN BAN ---\n";

    for (int i = 0; i < vanBan.length(); i++)
    {
        cur = trie[cur].next[vanBan[i] - 'a'];
        if (!trie[cur].word_ids.empty())
        {
            for (int id : trie[cur].word_ids)
            {
                cout << "Tim thay tu '" << mau[id] << "' ket thuc tai index: " << i << "\n";
            }
        }
    }
    return 0;
}