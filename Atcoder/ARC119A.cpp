#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

typedef long long ll;

ll pow2[64], n;

int main()
{
    scanf("%lld", &n);
    pow2[0] = 1;
    FOR(i, 1, 63)
        pow2[i] = pow2[i - 1] << 1ll;
    ll ans = 2e18;
    FOR(i, 0, 63)
    {
        if (pow2[i] > n) break;
        ll a = n / pow2[i];
        ll c = n % pow2[i];
        ll cur = a + i + c;
        ans = cur < ans ? cur : ans;
    }
    printf("%lld\n", ans);
    return 0;
}