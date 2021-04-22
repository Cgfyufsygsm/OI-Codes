#include <cstdio>

typedef long long ll;

inline ll min(ll a, ll b){return a < b ? a : b;}

int main()
{
    ll n, k;
    scanf("%lld %lld", &n, &k);
    ll ans = n * k;
    n = min(n, k);
    for (ll l = 1, r; l <= n; l = r + 1)
    {
        r = min(k / (k / l), n);
        ans -= (r - l + 1) * (k / l * l) + ((r - l + 1) * (r - l) * (k / l)) / 2;
    }
    printf("%lld\n", ans);
    return 0;
}