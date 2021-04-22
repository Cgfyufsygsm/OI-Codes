#include <cstdio>
#include <cstring>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 200000 + 5;
int n;
char s[maxn];
int m, c[maxn], x[maxn], y[maxn], sa[maxn], rank[maxn];

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

int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    FOR(i, n + 1, n << 1) s[i] = s[i - n];
    n <<= 1;
    m = 128;
    SA();
    FOR(i, 1, n)
        if (sa[i] <= n >> 1) printf("%c", s[sa[i] + (n >> 1) - 1]);
    return 0;
}