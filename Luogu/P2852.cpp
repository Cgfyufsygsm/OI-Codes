#include <cstdio>
#include <cctype>
#include <cstring>
#include <set>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxs = 1000000 + 5, maxn = 40000 + 5;

int n, m, k, a[maxn], sa[maxn], id[maxn], rk[maxn], oldrk[maxn], cnt[maxs], ht[maxn];

std::multiset<int> s;

inline bool cmp(int i, int j, int k)
{
    return oldrk[i] == oldrk[j] && oldrk[i + k] == oldrk[j + k];
}

inline int max(int a, int b) {return a > b ? a : b;}

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

int main()
{
    m = maxs - 5;
    n = read(), k = read() - 1;
    int ans = 0;
    FOR(i, 1, n) ++cnt[rk[i] = a[i] = read()];
    FOR(i, 1, m) cnt[i] += cnt[i - 1];
    DEC(i, n, 1) sa[cnt[rk[i]]--] = i;

    for (int w = 1; w < n; w <<= 1)
    {
        int num = 0;
        FOR(i, n - w + 1, n) id[++num] = i;
        FOR(i, 1, n) if (sa[i] > w) id[++num] = sa[i] - w;

        memset(cnt, 0, sizeof cnt);

        FOR(i, 1, n) ++cnt[rk[id[i]]];
        FOR(i, 1, m) cnt[i] += cnt[i - 1];
        DEC(i, n, 1) sa[cnt[rk[id[i]]]--] = id[i];

        memcpy(oldrk, rk, sizeof rk);

        num = 0;
        FOR(i, 1, n) rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? num : ++num;

        m = num;
    }

    for (int i = 1, j = 0; i <= n; ++i)
    {
        if (j) --j;
        while (a[i + j] == a[sa[rk[i] - 1] + j]) ++j;
        ht[rk[i]] = j;
    }

    FOR(i, 1, n)
    {
        s.insert(ht[i]);
        if (i > k)
            s.erase(s.find(ht[i - k]));
        ans = max(ans, *s.begin());
    }

    printf("%d\n", ans);
    return 0;
}