#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using ll = long long;

ll m, k;
ll f[80][80], a[80];

ll solve(int now, int cnt, int lim) {
    if (!now) return (cnt == k);
    if (~f[now][cnt] && !lim) return f[now][cnt];
    int up = lim ? a[now] : 1;
    ll res = 0;
    FOR(i, 0, up)
        if (cnt + (i == 1) <= k)
            res += solve(now - 1, cnt + (i == 1), lim && (i == up));
    if (!lim) f[now][cnt] = res;
    return res;
}

ll check(ll mid) {
    a[0] = 0;
    for (ll x = mid << 1ll; x; x >>= 1) a[++a[0]] = (x & 1);
    ll ret = solve(a[0], 0, 1);
    a[0] = 0;
    for (ll x = mid; x; x >>= 1) a[++a[0]] = (x & 1);
    ret -= solve(a[0], 0, 1);
    return ret;
}

int main() {
    scanf("%lld %lld", &m, &k);
    memset(f, -1, sizeof f);
    ll l = 1, r = (ll)1e18 + 1;
    while (l < r) {
        ll mid = (l + r) >> 1, tmp = check(mid);
        if (tmp == m)
            return printf("%lld\n", mid), 0;
        else if (tmp < m) l = mid + 1;
        else r = mid;
    }
    return 0;
}