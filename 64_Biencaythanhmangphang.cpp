#include <iostream>
#include <vector>
using namespace std;

int timer = 0;
vector<vector<int>> adj;
vector<int> timeIn, timeOut, flatArray;

void eulerTour(int u, int p)
{
    timeIn[u] = ++timer;    // Thời điểm bắt đầu đi vào nút u
    flatArray.push_back(u); // Nạp nút u vào mảng phẳng

    for (int v : adj[u])
    {
        if (v != p)
            eulerTour(v, u);
    }

    timeOut[u] = timer; // Thời điểm rời khỏi cây con của u
}

int main()
{
    int n = 5;
    adj.resize(n);
    timeIn.resize(n);
    timeOut.resize(n);

    adj[0].push_back(1);
    adj[1].push_back(0);
    adj[0].push_back(2);
    adj[2].push_back(0);
    adj[1].push_back(3);
    adj[3].push_back(1);
    adj[1].push_back(4);
    adj[4].push_back(1);

    eulerTour(0, -1);

    cout << "--- KET QUA PHANG HOA CAY (EULER TOUR) ---\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Nut " << i << " -> Quon ly doan mảng tu index: "
             << timeIn[i] << " den " << timeOut[i] << "\n";
    }

    return 0;
}