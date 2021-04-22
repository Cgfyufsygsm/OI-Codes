#include <cstdio>
#include <cmath>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

typedef double db;

const int maxn = 3e5 + 5;
const db pi = acos(-1.0);

struct cmplx
{
    db x, y;
    cmplx(db xx = 0, db yy = 0) {x = xx, y = yy;}
} a[maxn], b[maxn], c[maxn];

cmplx operator+(const cmplx &a, const cmplx &b) {return cmplx(a.x + b.x, a.y + b.y);}
cmplx operator-(const cmplx &a, const cmplx &b) {return cmplx(a.x - b.x, a.y - b.y);}
cmplx operator*(const cmplx &a, const cmplx &b) {return cmplx(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);}

int rev[maxn];

template<typename T> inline void swap(T &a, T &b) {T t = a; a = b; b = t; return;}

void DFT(cmplx *f, int lim, int type)
{
    FOR(i, 0, lim - 1)
        if (i < rev[i])
            swap(f[i], f[rev[i]]);
    for (int p = 2; p <= lim; p <<= 1)
    {
        int len = p >> 1;
        cmplx Wp(cos(pi / len), type * sin(pi / len));
        for (int k = 0; k < lim; k += p)
        {
            cmplx w(1, 0);
            for (int l = k; l < k + len; ++l, w = w * Wp)
            {
                cmplx tmp = w * f[l + len];
                f[l + len] = f[l] - tmp;
                f[l] = f[l] + tmp;
            }
        }
    }
    if (type == -1)
        FOR(i, 0, lim - 1)
            f[i].x /= lim;
    return;
}

int main()
{
    int n; scanf("%d", &n);
    FOR(i, 1, n)
    {
        scanf("%lf", &a[i].x);
        b[i].x = (1.0 / i / i);
        c[n - i].x = a[i].x;
    }
    int lim = 1;
    while (lim <= (n << 1)) lim <<= 1;
    FOR(i, 0, lim)
        rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0));
    DFT(a, lim, 1), DFT(b, lim, 1), DFT(c, lim, 1);
    FOR(i, 0, lim)
        a[i] = a[i] * b[i], c[i] = b[i] * c[i];
    DFT(a, lim, -1), DFT(c, lim, -1);
    FOR(i, 1, n)
        printf("%.3lf\n", a[i].x - c[n - i].x);
    return 0;
}