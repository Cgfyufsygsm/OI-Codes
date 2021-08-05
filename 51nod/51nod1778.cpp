#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 1e6 + 5;
typedef long long ll;
char s[maxn];
ll k, m, ik[maxn], c[maxn], fac[maxn], invfac[maxn];

ll qPow(ll a, ll b, ll p = m) {
    ll ret = 1;
    for (; b; b >>= 1, a = a * a % p)
        if (b & 1) ret = 1ll * ret * a % p;
    return ret;
}

int main() {
    scanf("%s", s + 1);
    scanf("%lld %lld", &k, &m);
    k %= (m - 1);
    int len = strlen(s + 1);
    ll n = 0, res = 0, sum = 0;
    FOR(i, 1, len) {
        n = (n * 10 + s[i] - '0') % m;
        res = res * 10 + s[i] - '0';
        sum = (sum * 10 + res / m) % (m - 1);
        res %= m;
    }
    ll ans = 0;
    fac[0] = 1;
    FOR(i, 1, n) fac[i] = fac[i - 1] * i % m;
    invfac[n] = qPow(fac[n], m - 2);
    DEC(i, n - 1, 0) invfac[i] = invfac[i + 1] * (i + 1) % m;
    FOR(i, 0, n) {
        ik[i] = qPow(i, k);
        c[i] = fac[n] * invfac[n - i] % m * invfac[i] % m;
    }
    FOR(i, 0, n)
        ans = (ans + (ik[i] - ik[n - i]) * (ik[i] - ik[n - i]) % m * c[i] % m) % m;
    printf("%lld\n", qPow(2, sum) * ans % m);
    return 0;
}