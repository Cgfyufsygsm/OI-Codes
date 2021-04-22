#include <cstdio>
#include <cctype>
#include <cstring>
#define init(a) memset((a), 0, sizeof (a))
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 2e5 + 5;
int a[maxn], b[maxn], k;
int dega[maxn], degb[maxn];

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

int main()
{
    int T = read();
    while (T--)
    {
        init(dega), init(degb);
        a[0] = read(), b[0] = read(), k = read();
        long long ans = 0;
        FOR(i, 1, k)
            a[i] = read(), ++dega[a[i]];
        FOR(i, 1, k)
            b[i] = read(), ++degb[b[i]];
        FOR(i, 1, k)
            ans += (k - degb[b[i]] - dega[a[i]] + 1);
        ans >>= 1LL;
        printf("%lld\n", ans);
    }
    return 0;
}