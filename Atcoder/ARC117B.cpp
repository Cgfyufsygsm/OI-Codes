#include <cstdio>
#include <cctype>
#include <algorithm>
#include <functional>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

const int mod = 1e9 + 7, maxn = 1e5 + 5;

int n, a[maxn], ans;

int main()
{
    n = read();
    FOR(i, 1, n) a[i] = read();
    std::sort(a + 1, a + n + 1);
    ans = 1;
    FOR(i, 1, n)
        ans = 1ll * ans * (a[i] - a[i - 1] + 1ll) % mod;
    printf("%d\n", ans);
    return 0;
}