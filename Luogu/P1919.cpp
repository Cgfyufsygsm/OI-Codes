#include <cstdio>
#include <cstring>
#include <cmath>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

template<typename T> inline void myswap(T &a, T &b) {T t = a; a = b; b = t; return;}

typedef double db;

const int maxn = 3000000 + 5;
const db pi = acos(-1.0);

struct cmplx
{
    db x, y;
    cmplx(db xx = 0, db yy = 0) {x = xx, y = yy;}
} a[maxn], b[maxn];

cmplx operator+(const cmplx &a, const cmplx &b) {return cmplx(a.x + b.x, a.y + b.y);}
cmplx operator-(const cmplx &a, const cmplx &b) {return cmplx(a.x - b.x, a.y - b.y);}
cmplx operator*(const cmplx &a, const cmplx &b) {return cmplx(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);}

char s1[maxn], s2[maxn];
int rev[maxn], ans[maxn];

void DFT(cmplx *f, int lim, int type)
{
    FOR(i, 0, lim - 1)
        if (i < rev[i])
            myswap(f[i], f[rev[i]]);
    for (int p = 2; p <= lim; p <<= 1)
    {
        int len = p >> 1;
        cmplx Wp(cos(2.0 * pi / p), type * sin(2.0 * pi / p));
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
    return;
}

int main()
{
    scanf("%s\n%s", s1, s2);
    int n1 = -1, n2 = -1;
    DEC(i, strlen(s1) - 1, 0) a[++n1].x = s1[i] - '0';
    DEC(i, strlen(s2) - 1, 0) b[++n2].x = s2[i] - '0';
    int lim = 1;
    while (lim <= n1 + n2) lim <<= 1;
    FOR(i, 0, lim - 1)
        rev[i] = ((rev[i >> 1] >> 1) | (((i & 1) ? (lim >> 1) : 0)));
    DFT(a, lim, 1);
    DFT(b, lim, 1);
    FOR(i, 0, lim)
        a[i] = a[i] * b[i];
    DFT(a, lim, -1);
    FOR(i, 0, lim)
        ans[i] = (int)(a[i].x / lim + 0.5);
    FOR(i, 0, lim)
        if (ans[i] >= 10) ans[i + 1] += ans[i] / 10, ans[i] %= 10, lim += (i == lim);
    while (!ans[lim] && lim > -1) --lim;
    if (lim == -1) puts("0");
    else DEC(i, lim, 0) printf("%d", ans[i]);
    return 0;
}