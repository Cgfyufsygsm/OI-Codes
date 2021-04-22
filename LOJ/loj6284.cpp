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

const int maxn = 100005, inf = 1e18;
int a[maxn], bl[maxn], tag[maxn], block, n;

void reset(int x)
{
    if (tag[x] == inf)
        return;
    FOR(i, (x - 1) * block + 1, min(n, x * block))
        a[i] = tag[x];
    tag[x] = inf;
    return;
}

signed main()
{
    block = sqrt(n = read());
    FOR(i, 1, n)
        a[i] = read(), bl[i] = (i - 1) / block + 1, tag[i] = inf;
    FOR(k, 1, n)
    {
        reg int l = read(), r = read(), c = read();
        int ans = 0;
        reset(bl[l]);
        FOR(i, l, min(r, block * bl[l]))
            ans += (a[i] == c), a[i] = c;
        if (bl[l] != bl[r])
        {
            reset(bl[r]);
            FOR(i, (bl[r] - 1) * block + 1, r)
                ans += (a[i] == c), a[i] = c;
        }
        FOR(i, bl[l] + 1, bl[r] - 1)
        {
            if (tag[i] == inf)
                FOR(j, (i - 1) * block + 1, i * block)
                    ans += (a[j] == c);
            else if (tag[i] == c)
                ans += block;
            tag[i] = c;
        }
        printf("%lld\n", ans);
    }
    return 0;
}