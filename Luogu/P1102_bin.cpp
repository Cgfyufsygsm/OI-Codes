#include <cstdio>
#include <cctype>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

inline int read()
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

const int maxn = 2e5 + 5;

int n, c, a[maxn];

int main()
{
    n = read(), c = read();
    FOR(i, 1, n)
        a[i] = read();
    long long ans = 0;
    std::sort(a + 1, a + n + 1);
    FOR(i, 1, n - 1)
        ans += std::upper_bound(a + 1, a + n + 1, a[i] + c) - std::lower_bound(a + 1, a + n + 1, a[i] + c);
    printf("%lld\n", ans);
    return 0;
}