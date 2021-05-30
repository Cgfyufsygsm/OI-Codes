#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

typedef long long ll;

ll n;

const ll mod = 10000007;

inline ll max(ll a, ll b) {return a > b ? a : b;}

ll f[55][55], a[55], len;

ll dfs(int pos, int st, int lim)
{
    if (pos > len) return max(st, 1);
    if (f[pos][st] != -1 && !lim) return f[pos][st];
    ll ret = 1;
    int res;
    if (lim) res = a[len - pos + 1];
    else res = 1;
    FOR(i, 0, res) (ret *= dfs(pos + 1, st + i, lim && (i == res))) %= mod;
    if (!lim) f[pos][st] = ret;
    return ret;
}

int main()
{
    scanf("%lld", &n);
    while (n) a[++len] = n & 1, n >>= 1;
    memset(f, -1, sizeof f);
    printf("%lld\n", dfs(1, 0, 1));
    return 0;
}