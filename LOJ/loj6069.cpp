#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define il inline

const int maxn = 105;

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

il int max(int a, int b) {return a > b ? a : b;}

int n, L, mod, l, r;

int f[maxn][maxn][maxn * (maxn + 1)], c[maxn * (maxn + 1) + 5][maxn * maxn];

il void add(int &x, int y) {x = (x + y) % mod;}

struct matrix
{
    int a[maxn][maxn];
    void id()
    {
        FOR(i, 0, n) a[i][i] = 1;
        return;
    }
    matrix() {memset(a, 0, sizeof a);}
};

matrix operator*(const matrix &a, const matrix &b)
{
    matrix ret;
    FOR(i, 0, n)
        FOR(k, 0, n)
            FOR(j, 0, n)
                add(ret.a[i][j], 1ll * a.a[i][k] * b.a[k][j] % mod);
    return ret;
}

matrix ksm(matrix base, int p)
{
    matrix ret;
    ret.id();
    for (; p; p >>= 1, base = base * base)
        if (p & 1) ret = base * ret;
    return ret;
}

void init()
{
    matrix trans;
    trans.a[0][0] = 1;
    FOR(i, 1, n)
        trans.a[i][i - 1] = trans.a[i][i] = 1;
    matrix ret = ksm(trans, l);
    FOR(i, 0, n) c[0][i] = ret.a[i][0];
    FOR(i, l + 1, r)
    {
        c[i - l][0] = 1;
        FOR(j, 1, n)
            add(c[i - l][j], c[i - l - 1][j] + c[i - l - 1][j - 1]);
    }
    return;
}

int main()
{
    n = read(), L = read(), mod = read();
    f[0][0][0] = 1;
    int mx = 0;
    FOR(i, 1, n)
    {
        FOR(j, 0, mx)
        {
            FOR(k, 0, i - 1)
            {
                add(f[i][k + 1][j], 1ll * f[i - 1][k][j] * (k + 1) % mod);
                add(f[i][k][j + i], 1ll * f[i - 1][k][j] * 2 * k % mod);
                if (k >= 2)
                    add(f[i][k - 1][j + 2 * i], 1ll * f[i - 1][k][j] * (k - 1) % mod);
            }
        }
        mx += 2 * i;
    }
    l = max(L - mx - 1 + n, n), r = L - 1 + n;
    init();
    int ans = 0;
    FOR(S, 0, mx)
    {
        if (S + 1 > L) break;
        add(ans, 1ll * f[n][1][S] * c[L - S - 1 + n - l][n] % mod);
    }
    printf("%d\n", ans);
    return 0;
}