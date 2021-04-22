#include <cstdio>
#include <cctype>
#include <cmath>
#define reg register
#define il inline
#define FOR(i, a, b) for (reg signed i = a; i <= b; ++i)

typedef long long ll;

il ll read()
{
    char c = getchar();
    ll s = 0;
    bool x = 0;
    while (!isdigit(c))
        x = x | (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

il ll min(ll a, ll b) {return a < b ? a : b;}

const int maxn = 1e5 + 5;
int n, m, block, bl[maxn];
ll a[maxn], sum[maxn], tag[maxn];

void add(int l, int r, ll val)
{
    FOR(i, l, min(bl[l] * block, n))
        a[i] += val, sum[bl[l]] += val;
    if (bl[l] != bl[r])
        FOR(i, (bl[r] - 1) * block + 1, r)
            a[i] += val, sum[bl[r]] += val;
    FOR(i, bl[l] + 1, bl[r] - 1)
        tag[i] += val;
    return;
}

ll query(int l, int r)
{
    ll ret = 0;
    FOR(i, l, min(bl[l] * block, n))
        ret += a[i] + tag[bl[l]];
    if (bl[l] != bl[r])
        FOR(i, (bl[r] - 1) * block + 1, r)
            ret += a[i] + tag[bl[r]];
    FOR(i, bl[l] + 1, bl[r] - 1)
        ret += sum[i] + tag[i] * block;
    return ret;
}

int main()
{
    block = sqrt(n = read()), m = read();
    FOR(i, 1, n)
        a[i] = read(), bl[i] = (i - 1) / block + 1, sum[bl[i]] += a[i];
    reg ll opt, x, y;
    FOR(i, 1, m)
    {
        opt = read(), x = read(), y = read();
        if (opt == 1)
            add(x, y, read());
        else
            printf("%lld\n", query(x, y));
    }
    return 0;
}