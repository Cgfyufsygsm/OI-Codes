#include <cstdio>
#include <cctype>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 2e5 + 5;

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

int n, a[maxn], m;

bool check(int mid)
{
    for (int i = mid + 1, j = n; i < j; ++i, --j)
        if (a[i] + a[j] < m) return 0;
    return 1;
}

inline int max(int a, int b) {return a > b ? a : b;}

int main()
{
    n = read() << 1, m = read();
    FOR(i, 1, n) a[i] = read();
    std::sort(a + 1, a + n + 1);
    int l = 0, r = n >> 1, pos = n + 1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid << 1)) pos = mid << 1, r = mid - 1;
        else l = mid + 1;
    }
    int ans = 0;
    for (int i = 1, j = pos; i < j; ++i, --j)
        ans = max(ans, a[i] + a[j]);
    for (int i = pos + 1, j = n; i < j; ++i, --j)
        ans = max(ans, a[i] + a[j] - m);
    printf("%d\n", ans);
    return 0;
}