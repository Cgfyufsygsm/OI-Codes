#include <cstdio>
#include <cctype>
#include <cmath>
#define reg register
#define il inline
#define FOR(i, a, b) for (reg signed i = a; i <= b; ++i)
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

il int min(int a, int b) {return a < b ? a : b;}

const int maxn = 100005, mod = 10007;
int a[maxn], bl[maxn], tag1[maxn], tag2[maxn], block, n;

void reset(int x)
{
    FOR(i, (x - 1) * block + 1, min(n, x * block))
        a[i] = (a[i] * tag2[x] % mod + tag1[x]) % mod;
    tag1[x] = 0, tag2[x] = 1;
    return;
}

void add(int l, int r, int val)
{
    reset(bl[l]);
    FOR(i, l, min(r, bl[l] * block))
        a[i] = (a[i] + val) % mod;
    if (bl[l] != bl[r])
    {
        reset(bl[r]);
        FOR(i, (bl[r] - 1) * block + 1, r)
            a[i] = (a[i] + val) % mod;
    }
    FOR(i, bl[l] + 1, bl[r] - 1)
        tag1[i] = (tag1[i] + val) % mod;
    return;
}

void mul(int l, int r, int val)
{
    reset(bl[l]);
    FOR(i, l, min(r, bl[l] * block))
        a[i] = (a[i] * val) % mod;
    if (bl[l] != bl[r])
    {
        reset(bl[r]);
        FOR(i, (bl[r] - 1) * block + 1, r)
            a[i] = (a[i] * val) % mod;
    }
    FOR(i, bl[l] + 1, bl[r] - 1)
        tag1[i] = tag1[i] * val % mod, tag2[i] = tag2[i] * val % mod;
    return;
}

il int query(int i)
{
    return (a[i] * tag2[bl[i]] % mod + tag1[bl[i]]) % mod;
}

signed main()
{
    block = sqrt(n = read());
    FOR(i, 1, n)
        a[i] = read(), bl[i] = (i - 1) / block + 1, tag2[i] = 1;
    FOR(k, 1, n)
    {
        reg int opt = read(), l = read(), r = read(), c = read();
        if (opt == 0)
            add(l, r, c % mod);
        else if (opt == 1)
            mul(l, r, c % mod);
        else printf("%lld\n", query(r));
    }
    return 0;
}