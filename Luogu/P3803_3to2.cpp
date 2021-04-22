#include <cstdio>
#include <cctype>
#include <cmath>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

typedef double db;

const int maxn = 3e6 + 5;
const db pi = acos(-1.0);

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

template<typename T> inline void myswap(T &a, T &b)
{
    T t = a;
    a = b;
    b = t;
    return;
}

struct cmplx
{
    db x, y;
    cmplx(db xx = 0, db yy = 0)
    {
        x = xx, y = yy;
    }
} a[maxn];

int rev[maxn];

cmplx operator+(const cmplx &a, const cmplx &b) {return cmplx(a.x + b.x, a.y + b.y);}
cmplx operator-(const cmplx &a, const cmplx &b) {return cmplx(a.x - b.x, a.y - b.y);}
cmplx operator*(const cmplx &a, const cmplx &b) {return cmplx(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);}

void DFT(cmplx *f, int lim, int type)
{
    FOR(i, 0, lim - 1)
        if (i < rev[i])
            myswap(f[i], f[rev[i]]);
    for (int p = 2; p <= lim; p <<= 1)
    {
        int len = p >> 1;
        cmplx Wp(cos(2 * pi / p), type * sin(2 * pi / p));
        for (int k = 0; k < lim; k += p)
        {
            cmplx w(1, 0);
            for (int l = k; l < k + len; ++l, w = w * Wp)
            {
                cmplx tmp = w * f[len + l];
                f[len + l] = f[l] - tmp;
                f[l] = f[l] + tmp;
            }
        }
    }
}

int main()
{
    int n = read(), m = read();
    FOR(i, 0, n) a[i].x = read();
    FOR(i, 0, m) a[i].y = read();
    int lim = 1;
    while (lim <= n + m) lim <<= 1;
    FOR(i, 0, lim - 1)
        rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0));
    DFT(a, lim, 1);
    FOR(i, 0, lim - 1)
        a[i] = a[i] * a[i];
    DFT(a, lim, -1);
    FOR(i, 0, n + m)
        printf("%d ", (int)(a[i].y / lim / 2.0 + 0.5));
    return 0;
}