#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

int read()
{
    int s = 0; int x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

const int maxn = 105;
int n, m;
int t[maxn], q[maxn];

int main()
{
    int cnt = 0;
    n = read(), m = read(), read();
    FOR(i, 1, n) t[i] = read();
    FOR(i, 1, n) q[i] = read(), cnt += (t[i] == 1 && q[i] == 1);
    int ans = 0;
    if (cnt >= m)
        ans = m + n - cnt;
    else ans = n;
    printf("%d\n", ans);
    return 0;
}