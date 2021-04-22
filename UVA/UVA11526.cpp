#include <cstdio>

typedef long long ll;

ll calc(ll n)
{
    ll ans = 0;
    for (ll l = 1, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        ans += (r - l + 1) * (n / l);
    }
    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        ll n;
        scanf("%lld", &n);
        printf("%lld\n", calc(n));
    }
    return 0;
}