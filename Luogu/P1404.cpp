#include <cstdio>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 1e5 + 5;
typedef long long ll;

ll a[maxn], s[maxn];
int n, m;

bool check(ll ans)
{
    FOR(i, 1, n)
        s[i] = s[i - 1] + a[i] - ans;
    ll last = 0;
    FOR(i, m, n)
    {
        if (s[i] - last >= 0) return 1;
        last = std::min(last, s[i - m + 1]);
    }
    return 0;
}

int main()
{
    scanf("%d %d", &n, &m);
    ll l = 0, r = -1, ans = 0;
    FOR(i, 1, n)
        scanf("%lld", a + i), a[i] *= 1000, r = std::max(r, a[i]);
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        check(mid) ? l = mid + 1, ans = mid : r = mid - 1;
    }
    printf("%lld\n", ans);
    return 0;
}