#include <cstdio>
#include <cctype>
#include <cmath>
#define reg register
#define il inline
#define int long long
#define FOR(i, a, b) for (reg signed i = a; i <= b; ++i)

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

const int maxn = 50005;
int a[maxn], bl[maxn], sum[maxn], tag[maxn], block, n;

void add(int l, int r, int val)
{
    FOR(i, l, min(r, bl[l] * block))
        a[i] += val, sum[bl[l]] += val;
    if (bl[l] != bl[r])
        FOR(i, (bl[r] - 1) * block + 1, r)
            a[i] += val, sum[bl[r]] += val;
    FOR(i, bl[l] + 1, bl[r] - 1)
        tag[i] += val;
    return;
}

int query(int l, int r, int mod)
{
    int ret = 0;
    FOR(i, l, min(r, bl[l] * block))
        ret += a[i] + tag[bl[l]], ret %= mod;
    if (bl[l] != bl[r])
        FOR(i, (bl[r] - 1) * block + 1, r)
            ret += a[i] + tag[bl[r]], ret %= mod;
    FOR(i, bl[l] + 1, bl[r] - 1)
        ret += sum[i] + tag[i] * block % mod, ret %= mod;
    return ret;
}

signed main()
{
    block = sqrt(n = read());
    FOR(i, 1, n)
        a[i] = read(), bl[i] = (i - 1) / block + 1, sum[bl[i]] += a[i];
    FOR(k, 1, n)
    {
        reg int opt = read(), l = read(), r = read(), c = read();
        if (opt == 0)
            add(l, r, c);
        else printf("%lld\n", query(l, r, c + 1));
    }
    return 0;
}