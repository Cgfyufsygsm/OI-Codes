#include <cstdio>
#include <cctype>
#include <cstring>
#include <cmath>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define il inline

typedef double db;
typedef long long ll;
const int maxn = 4e6 + 5, lim = 262144;
const db pi = acos(-1.0);

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
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
il cmplx operator*(const cmplx &a, const cmplx &b) {return cmplx(a.x * b.x - a.y * b.y, a.x * b.y + b.x * a.y);}

int rev[maxn];

void DFT(cmplx *f, int type)
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

cmplx a[maxn];
int w[maxn];
ll sum[maxn];

int main()
{
    int T = read();
    FOR(i, 0, lim) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
    while (T--)
    {
        int n = read();
        memset(a, 0, sizeof a);
        FOR(i, 1, n) a[w[i] = read()].x += 1;
        DFT(a, 1);
        FOR(i, 0, lim - 1) a[i] = a[i] * a[i];
        DFT(a, -1);
        FOR(i, 1, n) a[w[i] * 2].x--;
        FOR(i, 0, lim - 1) sum[i] = sum[i - 1] + (ll)(a[i].x / 2.0 + 0.1);
        ll ans = 0;
        FOR(i, 1, n) ans += sum[w[i]];
        printf("%.7Lf\n", 1.0 - (long db)ans / ((long db)n * (n - 1.0) * (n - 2.0) / 6));
    }
    return 0;
}