#include <cstdio>
#include <cctype>
#include <cstring>
#include <cmath>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define il inline

typedef double db;
const int maxn = 8e5 + 5;
const db pi = acos(-1.0);

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

template<typename T> il void swap(T &a, T &b)
{
    T t = a;
    a = b, b = t;
    return;
}

struct cmplx
{
    db x, y;
    cmplx(){}
    cmplx(db a, db b) {x = a, y = b;}
};

il cmplx operator+(const cmplx &a, const cmplx &b) {return cmplx(a.x + b.x, a.y + b.y);}
il cmplx operator-(const cmplx &a, const cmplx &b) {return cmplx(a.x - b.x, a.y - b.y);}
il cmplx operator*(const cmplx &a, const cmplx &b) {return cmplx(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);}

int rev[maxn];

void DFT(cmplx *f, int lim, int type)
{
    FOR(i, 0, lim - 1) if (i < rev[i]) swap(f[i], f[rev[i]]);
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
    if (type == -1)
        FOR(i, 0, lim - 1)
            f[i].x /= lim;
    return;
}

int a[maxn], b[maxn], c[maxn];
cmplx f[maxn], g[maxn];

int main()
{
    int n = read();
    int lim = 1;
    while (lim <= n * 2) lim <<= 1;
    FOR(i, 0, lim - 1) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
    FOR(i, 0, n - 1) a[i] = read(), b[i] = read();
    FOR(i, 0, n - 1) f[n - 1 - i].x = a[i], g[i].x = b[i];
    DFT(f, lim, 1), DFT(g, lim, 1);
    FOR(i, 0, lim - 1) f[i] = f[i] * g[i];
    DFT(f, lim, -1);
    FOR(i, 0, n - 1)
        c[i] = (int)(f[n - i - 1].x + 0.5);
    FOR(i, 0, n - 1) printf("%d\n", c[i]);
    return 0;
}