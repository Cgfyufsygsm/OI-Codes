#include <cstdio>
#include <cctype>
#include <cmath>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 2e6 + 5;
const double pi = acos(-1.0);

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

struct complex
{
    double x, y;
    complex(double xx = 0, double yy = 0)
    {
        x = xx, y = yy;
    }
} a[maxn], b[maxn];

complex operator+(const complex &a, const complex &b) {return complex(a.x + b.x, a.y + b.y);}
complex operator-(const complex &a, const complex &b) {return complex(a.x - b.x, a.y - b.y);}
complex operator*(const complex &a, const complex &b) {return complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);}

void dft(int lim, complex *a, int type)
{
    if (lim == 1) return;
    complex a1[lim >> 1], a2[lim >> 1];
    for (int i = 0; i < lim; i += 2)
        a1[i >> 1] = a[i], a2[i >> 1] = a[i + 1];
    dft(lim >> 1, a1, type);
    dft(lim >> 1, a2, type);
    complex Wn = complex(cos(2.0 * pi / lim), type * sin(2.0 * pi / lim)), w = complex(1, 0);
    for (int i = 0; i < (lim >> 1); ++i, w = w * Wn)
    {
        complex tmp = w * a2[i];
        a[i] = a1[i] + tmp;
        a[i + (lim >> 1)] = a1[i] - tmp;
    }
    return;
}

int main()
{
    int n = read(), m = read();
    FOR(i, 0, n) a[i].x = read();
    FOR(i, 0, m) b[i].x = read();
    int lim = 1;
    while (lim <= n + m) lim <<= 1;
    dft(lim, a, 1);
    dft(lim, b, 1);
    FOR(i, 0, lim)
        a[i] = a[i] * b[i];
    dft(lim, a, -1);
    FOR(i, 0, n + m)
        printf("%d ", (int)(a[i].x / lim + 0.5));
    return 0;
}