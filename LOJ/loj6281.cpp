#include <cstdio>
#include <cctype>
#include <cmath>
#define reg register
#define il inline
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
int a[maxn], bl[maxn], sum[maxn], block, n;

void modify(int l, int r)
{
    FOR(i, l, min(r, bl[l] * block))
        sum[bl[l]] -= a[i], a[i] = sqrt(a[i]), sum[bl[l]] += a[i];
    if (bl[l] != bl[r])
        FOR(i, (bl[r] - 1) * block + 1, r)
            sum[bl[r]] -= a[i], a[i] = sqrt(a[i]), sum[bl[r]] += a[i];
    FOR(i, bl[l] + 1, bl[r] - 1)
        if (sum[i] == block || !sum[i])
            continue;
        else
            FOR(j, (i - 1) * block + 1, i * block)
                sum[i] -= a[j], a[j] = sqrt(a[j]), sum[i] += a[j];
    return;
}

int query(int l, int r)
{
    int ret = 0;
    FOR(i, l, min(r, bl[l] * block))
        ret += a[i];
    if (bl[l] != bl[r])
        FOR(i, (bl[r] - 1) * block + 1, r)
            ret += a[i];
    FOR(i, bl[l] + 1, bl[r] - 1)
        ret += sum[i];
    return ret;
}

int main()
{
    block = sqrt(n = read());
    FOR(i, 1, n)
        a[i] = read(), bl[i] = (i - 1) / block + 1, sum[bl[i]] += a[i];
    FOR(k, 1, n)
    {
        reg int opt = read(), l = read(), r = read(), c = read();
        if (opt == 0)
            modify(l, r);
        else printf("%d\n", query(l, r));
    }
    return 0;
}