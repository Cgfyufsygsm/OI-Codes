#include <cstdio>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

typedef long long ll;

const ll mod = 998244353;
ll p, fac[2000005], cnt;

ll phi(ll n) {
    ll ans = n;
    for (ll i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            ans = ans / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    }
    if (n != 1) ans = ans / n * (n - 1);
    return ans % mod;
}

int main() {
    scanf("%lld", &p);
    --p;
    for (ll i = 1; i * i <= p; ++i) {
        if (p % i == 0) {
            fac[++cnt] = i;
            if (p / i != i)
                fac[++cnt] = p / i;
        }
    }
    ll ans = 0;
    FOR(i, 1, cnt)
        ans = (ans + p / fac[i] % mod * phi(p / fac[i]) % mod) % mod;
    printf("%lld\n", (ans + 1) % mod);
}