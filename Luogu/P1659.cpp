#include <cstdio>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

typedef long long ll;

const int maxn = 1e6 + 5;
const ll mod = 19930726;
char s[maxn];
int n;
ll k, len[maxn], ans[maxn];

inline int min(int a, int b) {return a < b ? a : b;}

ll qpow(ll base, ll p)
{
    ll ret = 1;
    for (; p; p >>= 1)
    {
        if (p & 1)
            ret = ret * base % mod;
        base = base * base % mod;
    }
    return ret;
}

int main()
{
    scanf("%d %lld", &n, &k);
    scanf("%s", s + 1);
    s[0] = '#', s[n + 1] = '&';
    for (int i = 1, r = 0, mid = 0; i <= n; ++i)
    {
        if (i <= r)
            len[i] = min(len[(mid << 1) - i], r - i + 1);
        while (s[i - len[i]] == s[i + len[i]]) ++len[i];
        if (i + len[i] > r) r = i + len[i] - 1, mid = i;
        ++ans[1], --ans[len[i] * 2];
    }
    FOR(i, 1, n + 1) ans[i] = (ans[i] + ans[i - 1]) % mod;
    ans[0] = 1;
    DEC(i, n, 1)
    {
        if (!ans[i] || i % 2 == 0) continue;
        if (ans[i] > k) ans[i] = k;
        k -= ans[i];
        ans[0] = ans[0] * qpow(i, ans[i]) % mod;
        if (!k) break;
    }
    if (k > 0) ans[0] = -1;
    printf("%lld\n", ans[0]);
    return 0;
}