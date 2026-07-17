#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAXM = 200010;
vector<int> primes;
bool is_prime[MAXM];
int pi_table[MAXM];

void sieve()
{
    fill(is_prime, is_prime + MAXM, true);
    is_prime[0] = is_prime[1] = false;
    int count = 0;
    for (int i = 2; i < MAXM; i++)
    {
        if (is_prime[i])
        {
            primes.push_back(i);
            count++;
        }
        pi_table[i] = count;
        for (int p : primes)
        {
            if (i * p >= MAXM)
                break;
            is_prime[i * p] = false;
            if (i % p == 0)
                break;
        }
    }
}

// Hàm phi(x, a) đếm số lượng số <= x không chia hết cho a số nguyên tố đầu tiên
long long phi(long long x, int a)
{
    if (a == 0)
        return x;
    if (x <= 0)
        return 0;
    if (primes[a - 1] >= x)
        return 1;
    // Nhánh cắt tối ưu bằng bảng tính sẵn
    if (x < MAXM && a < 100)
    {
        long long res = x;
        for (int i = 0; i < a; i++)
            res -= x / primes[i]; // Có thể tối ưu thêm bằng DP
        return res;
    }
    return phi(x, a - 1) - phi(x / primes[a - 1], a - 1);
}

// Hàm Meissel-Lehmer tính pi(N)
long long pi(long long N)
{
    if (N < MAXM)
        return pi_table[N];

    long long a = pi(root(N, 3)); // căn bậc 3 của N
    long long b = pi(sqrt(N));    // căn bậc 2 của N
    long long c = pi(root(N, 3)); // biến bổ trợ

    long long sum = phi(N, a) + (long long)(b + a - 2) * (b - a + 1) / 2;

    for (int i = a + 1; i <= b; i++)
    {
        sum -= pi(N / primes[i - 1]);
    }
    return sum;
}

// Hàm bổ trợ tính căn bậc 3 nguyên
long long root(long long n, int r)
{
    if (r == 3)
        return pow(n, 1.0 / 3.0) + 1e-9;
    return sqrt(n);
}

int main()
{
    sieve();
    long long N = 1000000000LL; // 1 tỷ

    cout << "--- KET QUA THUAT TOAN MEISSEL-LEHMER ---\n";
    cout << "So luong so nguyen to <= " << N << " la: " << pi(N) << endl;
    // Kết quả chính xác: 50,847,534
    return 0;
}