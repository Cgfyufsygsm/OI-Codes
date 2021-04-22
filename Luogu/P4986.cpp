#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

typedef double db;
const int maxn = 3e5 + 5;
const db pi = acos(-1.0), eps = 1e-8;

struct cmplx
{
    db x, y;
    cmplx(db xx = 0, db yy = 0)
    {
        x = xx, y = yy;
    }
} a[maxn], b[maxn], c[maxn], ff[maxn];

cmplx operator+(const cmplx &a, const cmplx &b) {return cmplx(a.x + b.x, a.y + b.y);}
cmplx operator-(const cmplx &a, const cmplx &b) {return cmplx(a.x - b.x, a.y - b.y);}
cmplx operator*(const cmplx &a, const cmplx &b) {return cmplx(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);}

int rev[maxn], lim, lf;
db l, r, f[maxn], df[maxn];

void DFT(cmplx *f, int lim, int type)
{
    FOR(i, 0, lim - 1)
        if (i < rev[i])
            std::swap(f[i], f[rev[i]]);
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

void square(cmplx *f)
{
    DFT(f, lim, 1);
    FOR(i, 0, lim - 1)
        f[i] = f[i] * f[i];
    return;
}

db get_val(db x, db *f)
{
    double X = 1, ret = 0;
    FOR(i, 0, lf)
        ret += X * f[i], X *= x;
    return ret;
}

int times = 30;

db Newton(db x)
{
    db c;
    while (1)
    {
        //printf("%lf\n", x);
        c = get_val(x, f);
        --times;
        if (fabs(c) < eps)
            break;
        x = x - c / get_val(x, df);
        x = std::max(x, l), x = std::min(x, r);
        if (!times) return 0;
    }
    return x;
}

int main()
{
    int la, lb, lc;
    scanf("%d %d %d %lf %lf", &la, &lb, &lc, &l, &r);
    lf = std::max(std::max(la, lb), lc) << 1;
    for (lim = 1; lim <= lf; lim <<= 1);
    FOR(i, 0, lim - 1)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
    FOR(i, 0, la)
        scanf("%lf", &a[i].x);
    FOR(i, 0, lb)
        scanf("%lf", &b[i].x);
    FOR(i, 0, lc)
        scanf("%lf", &c[i].x);
    square(a), square(b), square(c);
    FOR(i, 0, lim - 1)
        ff[i] = c[i] - a[i] - b[i];
    DFT(ff, lim, -1);
    FOR(i, 0, lf)
        f[i] = ff[i].x;
    FOR(i, 1, lf)
        df[i - 1] = i * f[i];
    db ans = Newton((l + r) / 2.0);
    if (times) printf("%.8lf\n", ans);
    else puts("Inconsistent!");
    return 0;
}