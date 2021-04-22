#include <cstdio>
#include <cctype>
#include <cmath>
#include <cstring>
#include <algorithm>
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

const int maxn = 100000 + 5, sqrtn = 350;
int n, org[maxn], a[maxn], block, bl[maxn], mode[sqrtn][sqrtn], s[sqrtn][maxn];
int cnt[maxn];

void init()
{
    block = sqrt(n = read());
    FOR(i, 1, n)
        org[i] = a[i] = read(), bl[i] = (i - 1) / block + 1;
    std::sort(org + 1, org + n + 1);
    int tot = std::unique(org + 1, org + n + 1) - org - 1;
    FOR(i, 1, n)
        ++s[bl[i]][a[i] = std::lower_bound(org + 1, org + tot + 1, a[i]) - org];
    FOR(i, 1, n)
        FOR(j, 2, bl[n])
            s[j][i] += s[j - 1][i];
    FOR(i, 1, bl[n])
    {
        memset(cnt, 0, sizeof cnt);
        int tmp, maxcnt = -1e9;
        FOR(j, i, bl[n])
        {
            FOR(k, (j - 1) * block + 1, min(n, j * block))
            {
                if (++cnt[a[k]] > maxcnt)
                    tmp = a[k], maxcnt = cnt[a[k]];
                else if (cnt[a[k]] == maxcnt && a[k] < tmp)
                    tmp = a[k];
            }
            mode[i][j] = tmp;
        }
    }
    return;
}

int query(int l, int r)
{
    memset(cnt, 0, sizeof cnt);
    if (bl[r] - bl[l] <= 1)
    {
        int tmp, maxcnt = -1e9;
        FOR(i, l, r)
        {
            if (++cnt[a[i]] > maxcnt)
                tmp = a[i], maxcnt = cnt[a[i]];
            else if (cnt[a[i]] == maxcnt && a[i] < tmp)
                tmp = a[i];
        }
        return tmp;
    }
    else
    {
        int tmp = mode[bl[l] + 1][bl[r] - 1], maxcnt = cnt[tmp] = s[bl[r] - 1][tmp] - s[bl[l]][tmp];
        FOR(i, l, bl[l] * block)
        {
            if (!cnt[a[i]])
                cnt[a[i]] = s[bl[r] - 1][a[i]] - s[bl[l]][a[i]];
            if (++cnt[a[i]] > maxcnt)
                tmp = a[i], maxcnt = cnt[a[i]];
            else if (cnt[a[i]] == maxcnt && a[i] < tmp)
                tmp = a[i];
        }
        FOR(i, (bl[r] - 1) * block + 1, r)
        {
            if (!cnt[a[i]])
                cnt[a[i]] = s[bl[r] - 1][a[i]] - s[bl[l]][a[i]];
            if (++cnt[a[i]] > maxcnt)
                tmp = a[i], maxcnt = cnt[a[i]];
            else if (cnt[a[i]] == maxcnt && a[i] < tmp)
                tmp = a[i];
        }
        return tmp;
    }
}

int main()
{
    init();
    FOR(k, 1, n)
    {
        reg int l = read(), r = read();
        printf("%d\n", org[query(l, r)]);
    }
    return 0;
}