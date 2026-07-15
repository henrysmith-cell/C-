#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
using namespace std;

using cd = complex<double>;
const double PI = acos(-1);

// Hàm biến đổi Fourier nhanh (FFT) giải thuật Cooley-Tukey
void fft(vector<cd> &a, bool invert)
{
    int n = a.size();
    if (n == 1)
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++)
    {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double angle = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(angle), sin(angle));
    for (int i = 0; 2 * i < n; i++)
    {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (invert)
        {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

// Nhân hai đa thức bằng FFT
vector<int> multiplyPolynomials(vector<int> const &a, vector<int> const &b)
{
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1; // Đưa về độ dài lũy thừa của 2
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
    {
        fa[i] *= fb[i];
    }
    fft(fa, true); // Biến đổi ngược (IFFT)

    vector<int> result(n);
    for (int i = 0; i < n; i++)
    {
        result[i] = round(fa[i].real());
    }
    return result;
}

int main()
{
    // Đa thức A(x) = 1 + 2x (hệ số [1, 2])
    // Đa thức B(x) = 3 + 4x (hệ số [3, 4])
    // Tích C(x) = 3 + 10x + 8x^2 (hệ số mong muốn [3, 10, 8])
    vector<int> a = {1, 2};
    vector<int> b = {3, 4};

    vector<int> c = multiplyPolynomials(a, b);

    cout << "--- KET QUA NHAN DA THUC BANG FFT ---\n";
    cout << "He so cua da thuc tich: ";
    for (int i = 0; i < a.size() + b.size() - 1; i++)
    {
        cout << c[i] << " ";
    }
    cout << endl;
    return 0;
}