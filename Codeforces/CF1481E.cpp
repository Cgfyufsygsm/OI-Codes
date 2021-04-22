#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

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

const int maxn = 5e5 + 5;
int a[maxn], n, l[maxn], r[maxn], cnt[maxn], f[maxn];

int main()
{
    n = read();
    FOR(i, 1, n)
    {
        a[i] = read();
        if (!l[a[i]])
            l[a[i]] = i;
    }
    DEC(i, n, 1)
        if (!r[a[i]])
            r[a[i]] = i;
    DEC(i, n, 1)
    {
        ++cnt[a[i]];
        if (i < n) f[i] = max(f[i], f[i + 1]);
        if (i != l[a[i]]) f[i] = max(f[i], cnt[a[i]]);
        else f[i] = max(f[i], cnt[a[i]] + f[r[a[i]] + 1]);
    }
    printf("%d\n", n - f[1]);
    return 0;
}