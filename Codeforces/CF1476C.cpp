#include <cstdio>
#include <cctype>
#include <cstring>
#define int long long
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 1e5 + 5;

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
inline int abs(int a) {return a >= 0 ? a : -a;}

int n, c[maxn], a[maxn], b[maxn], f[maxn];

signed main()
{
    int T = read();
    while (T--)
    {
        n = read();
        FOR(i, 1, n) c[i] = read();
        scanf("%lld", &a[1]); FOR(i, 2, n) a[i] = read();
        scanf("%lld", &b[1]); FOR(i, 2, n) b[i] = read();
        int ans = 0;
        f[1] = 0;
        FOR(i, 2, n)
        {
            if (a[i] == b[i])
                f[i] = c[i] + 1;
            else f[i] = max(f[i - 1] - abs(a[i] - b[i]) + c[i] + 1, c[i] + 1 + abs(a[i] - b[i]));
            ans = max(ans, f[i]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}