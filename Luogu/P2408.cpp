#include <cstdio>
#include <cstring>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 1e5 + 5;
int n, m, sa[maxn], rank[maxn], x[maxn], y[maxn], c[maxn], height[maxn];
char s[maxn];

void SA()
{
    FOR(i, 1, n) ++c[x[i] = s[i]];
    FOR(i, 2, m) c[i] += c[i - 1];
    DEC(i, n, 1) sa[c[x[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1)
    {
        int num = 0;
        FOR(i, n - k + 1, n) y[++num] = i;
        FOR(i, 1, n) if (sa[i] > k) y[++num] = sa[i] - k;
        FOR(i, 1, m) c[i] = 0;
        FOR(i, 1, n) ++c[x[i]];
        FOR(i, 2, m) c[i] += c[i - 1];
        DEC(i, n, 1)
        {
            sa[c[x[y[i]]]--] = y[i];
            y[i] = 0;
        }
        std::swap(x, y);
        num = 1, x[sa[1]] = 1;
        FOR(i, 2, n)
            if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k])
                x[sa[i]] = num;
            else x[sa[i]] = ++num;
        if (num == n) break;
        m = num;
    }
    return;
}

void get_height()
{
    FOR(i, 1, n) rank[sa[i]] = i;
    int k = 0;
    FOR(i, 1, n)
    {
        if (k) --k;
        while (s[i + k] == s[sa[rank[i] - 1] + k]) ++k;
        height[rank[i]] = k;
    }
    return;
}

int main()
{
    scanf("%d", &n);
    scanf("%s", s + 1);
    m = 128;
    SA();
    get_height();
    long long ans = (long long)n * (n + 1ll) / 2;
    FOR(i, 1, n) ans -= height[i];
    printf("%lld\n", ans);
    return 0;
}