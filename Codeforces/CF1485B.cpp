#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

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

const int maxn = 1e5 + 5;
int a[maxn], n, q, k;
int f[maxn];

int main()
{
    n = read(), q = read(), k = read();
    FOR(i, 1, n) a[i] = read();
    a[n + 1] = k + 1, a[0] = 0;
    FOR(i, 1, n)
        f[i] = f[i - 1] + (a[i + 1] - a[i - 1] - 2);
    while (q--)
    {
        int l = read(), r = read();
        int ans = f[r] - f[l - 1] + (a[l] - 1) + (k - a[r]) - (a[l] - a[l - 1] - 1) - (a[r + 1] - a[r] - 1);
        printf("%d\n", ans);
    }
    return 0;
}