#include <cstdio>
#include <cctype>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define int long long

inline int read()
{
    char c = getchar();
    int s = 0, x = 0;
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

const int maxn = 2e5 + 5;
int sum[maxn], val[maxn], id[maxn];

signed main()
{
    int T = read();
    while (T--)
    {
        int n = read(), m = read();
        FOR(i, 1, n) sum[i] = sum[i - 1] + read();
        int tot = 0;
        FOR(i, 1, n)
        {
            if (!tot || sum[i] > val[tot])
                val[++tot] = sum[i], id[tot] = i;
        }
        while (m--)
        {
            int x = read();
            if (x > val[tot] && sum[n] <= 0)
                printf("-1 ");
            else
            {
                int r = 0;
                if (val[tot] < x)
                    r = (x - val[tot] + sum[n] - 1) / sum[n];
                x -= r * sum[n];
                printf("%lld ", r * n + id[std::lower_bound(val + 1, val + tot +1, x) - val] - 1);
            }
        }
        puts("");
    }
    return 0;
}