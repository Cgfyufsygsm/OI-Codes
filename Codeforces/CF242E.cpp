#include <cstdio>
#include <cctype>
#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)
#define reg register
#define il inline
#define FOR(i, a, b) for (reg int i = a; i <= b; ++i)
#define int long long

il int read()
{
    char c = getchar();
    int s = 0;
    bool x = 0;
    while (!isdigit(c))
        x = x | (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

const int maxn = 1e5 + 5;
int n, t[maxn << 2][32], tag[maxn << 2][32];

void pushup(int k)
{
    FOR(p, 0, 29)
        t[k][p] = t[L][p] + t[R][p];
    return;
}

void build(int i, int j, int k)
{
    if (i == j)
    {
        int tmp = read();
        for (reg int p = 0; tmp; tmp >>= 1, ++p)
            t[k][p] = (tmp & 1);
        return;
    }
    build(i, M, L);
    build(M + 1, j, R);
    pushup(k);
    return;
}

void pushdown(int i, int j, int k)
{
    FOR(p, 0, 29)
    {
        if (!tag[k][p])
            continue;
        t[L][p] = (M - i + 1) - t[L][p];
        t[R][p] = (j - M) - t[R][p];
        tag[L][p] ^= 1;
        tag[R][p] ^= 1;
        tag[k][p] = 0;
    }
    return;
}

int query(int i, int j, int k, int l, int r)
{
    if (l <= i && r >= j)
    {
        int ret = 0ll;
        FOR(p, 0, 29)
            ret += (t[k][p] << p);
        return ret;
    }
    int ret = 0ll;
    pushdown(i, j, k);
    if (l <= M)
        ret += query(i, M, L, l, r);
    if (r > M)
        ret += query(M + 1, j, R, l, r);
    return ret;
}

void modify(int i, int j, int k, int l, int r, int x)
{
    if (l <= i && r >= j)
    {
        FOR(p, 0, 29)
            for (reg int p = 0; x; x >>= 1, ++p)
                if (x & 1)
                {
                    tag[k][p] ^= 1;
                    t[k][p] = j - i + 1 - t[k][p];
                }
        return;
    }
    pushdown(i, j, k);
    if (l <= M)
        modify(i, M, L, l, r, x);
    if (r > M)
        modify(M + 1, j, R, l, r, x);
    pushup(k);
    return;
}

signed main()
{
    n = read();
    build(1, n, 1);
    int m = read();
    reg int opt, l, r, x;
    while (m--)
    {
        opt = read(), l = read(), r = read();
        if (opt == 1)
            printf("%lld\n", query(1, n, 1, l, r));
        else
            modify(1, n, 1, l, r, read());
    }
    return 0;
}