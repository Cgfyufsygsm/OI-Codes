#include <cstdio>
#include <cctype>
#define int long long
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 105;
int n, k, p[maxn], sump[maxn];

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

inline int max(int a, int b) {return a > b ? a : b;}

signed main()
{
    int T = read();
    while (T--)
    {
        n = read(), k = read();
        FOR(i, 1, n) sump[i] = p[i] = read(), sump[i] += sump[i - 1];
        int ans = 0;
        FOR(i, 2, n)
        {
            if (sump[i - 1] * k < 100 * p[i])
            {
                int tmp = 100 * p[i] - k * sump[i - 1];
                if (tmp % k) ans = max(ans, tmp / k + 1);
                else ans = max(ans, tmp / k);
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}