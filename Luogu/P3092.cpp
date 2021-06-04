#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxk = 17, maxn = 1e5 + 5;

typedef long long ll;

ll read()
{
    ll s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

inline ll max(ll a, ll b) {return a > b ? a : b;}

ll n, k, sum[maxn], a[maxk];
ll f[1 << maxk];//用这些状态的硬币最多买到的物品

int query(ll x)
{
    int l = 1, r = n, ans;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (sum[mid] <= x) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    return ans;
}

int main()
{
    k = read(), n = read();
    FOR(i, 1, k) a[i] = read();
    FOR(i, 1, n) sum[i] = read() + sum[i - 1];
    f[0] = 0;
    ll ans = -1;
    FOR(S, 1, (1 << k) - 1)
    {
        FOR(j, 1, k)
            if ((1 << (j - 1)) & S)
                f[S] = max(f[S], query(sum[f[S ^ (1 << (j - 1))]] + a[j]));
        if (f[S] == n)
        {
            ll tmp = 0;
            FOR(j, 1, k)
                if (!(S & (1 << (j - 1))))
                    tmp += a[j];
            ans = max(tmp, ans);
        }
    }
    printf("%lld\n", ans);
    return 0;
}