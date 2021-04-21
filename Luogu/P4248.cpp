#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

typedef long long ll;
const int maxn = (500000 * 2) + 5;
int sa[maxn], rk[maxn], oldrk[maxn], id[maxn], cnt[maxn], ht[maxn];
char s[maxn];

int n, m;

inline bool cmp(int i, int j, int k) {return oldrk[i] == oldrk[j] && oldrk[i + k] == oldrk[j + k];}

int l[maxn], r[maxn], stk[maxn], top;

int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);

    m = 'z';
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
        num = 0;
        FOR(i, 1, n) rk[sa[i]] = cmp(sa[i], sa[i - 1], k) ? num : ++num;
        m = num;
        if (num == n) break;
    }

    for (int i = 1, k = 0; i <= n; ++i)
    {
        if (k) --k;
        while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
        ht[rk[i]] = k;
    }

    ll ans = (n + 1ll) * (n - 1ll) * n / 2;
    FOR(i, 2, n) l[i] = 2, r[i] = n + 1;
    
    ll ans1 = 0;
    stk[top = 1] = 1;
    FOR(i, 2, n)
    {
        while (top && ht[stk[top]] > ht[i]) r[stk[top--]] = i;
        l[i] = stk[top];
        stk[++top] = i;
    }

    FOR(i, 2, n) ans1 += 2ll * ht[i] * (i - l[i]) * (r[i] - i);

    printf("%lld\n", ans - ans1);
    return 0;
}