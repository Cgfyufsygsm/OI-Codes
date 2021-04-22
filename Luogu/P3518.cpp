#include <cstdio>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

typedef long long ll;

const int maxn = 250000 + 5;
ll a[maxn], k, n, tot, ans;

inline ll gcd(ll a, ll b) {return b ? gcd(b, a % b) : a;}
inline ll max(ll a, ll b) {return a > b ? a : b;}

bool check(ll x)
{
    DEC(i, tot, 1)
        if (a[i] % x == 0)
            return false;
    return true;
}

int main()
{
    scanf("%lld %lld", &n, &k);
    FOR(i, 1, k) scanf("%lld", a + i), a[i] = gcd(a[i], n);
    std::sort(a + 1, a + k);
    tot = std::unique(a + 1, a + k) - a - 1;
    for (ll i = 1; i * i <= a[k]; ++i)
    {
        if (a[k] % i == 0)
        {
            if (check(i))
            {
                ans = n / i;
                break;
            }
            else if (check(a[k] / i))
                ans = max(n / (a[k] / i), ans);
        }
    }
    printf("%lld\n", ans);
    return 0;
}