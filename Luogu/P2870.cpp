#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 1e6 + 5;

int n, m;
char s[maxn];
int sa[maxn << 1], rk[maxn << 1], oldrk[maxn << 1], cnt[maxn], id[maxn];

inline bool cmp(int i, int j, int k)
{
    return oldrk[i] == oldrk[j] && oldrk[i + k] == oldrk[j + k];
}

int main()
{
    scanf("%d", &n);
    FOR(i, 1, n)
        while (!isalpha(s[i] = s[2 * n + 2 - i] = getchar()));

    n = 2 * n + 1;
    m = (int)'Z';

    FOR(i, 1, n) ++cnt[rk[i] = s[i]];
    FOR(i, 1, m) cnt[i] += cnt[i - 1];
    DEC(i, n, 1) sa[cnt[rk[i]]--] = i;

    for (int k = 1; k < n; k <<= 1)
    {
        int num = 0;
        FOR(i, n - k + 1, n) id[++num] = i;
        FOR(i, 1, n) if (sa[i] > k) id[++num] = sa[i] - k;
        memset(cnt, 0, sizeof cnt);
        FOR(i, 1, n) ++cnt[rk[i]];
        FOR(i, 1, m) cnt[i] += cnt[i - 1];
        DEC(i, n, 1) sa[cnt[rk[id[i]]]--] = id[i];
        memcpy(oldrk, rk, sizeof rk);
        num = 0, rk[sa[1]] = 1;
        FOR(i, 2, n) rk[sa[i]] = cmp(sa[i], sa[i - 1], k) ? num : ++num;
        m = num;
    }
    
    for (int i = 1, l = 1, r = (n - 1) >> 1; l <= r; ++i)
    {
        printf("%c", rk[l] < rk[n + 1 - r] ? s[l++] : s[r--]);
        if (i % 80 == 0) puts("");
    }

    return 0;
}