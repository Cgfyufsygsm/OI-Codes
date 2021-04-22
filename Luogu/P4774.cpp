#include <cstdio>
#include <cctype>
#include <set>
#define FOR(i, a, b) for (R int i = a; i <= b; ++i)
#define il inline
#define R register

const int maxn = 1e5 + 5;
using std::multiset;
typedef long long ll;

inline ll read()
{
    char c = getchar();
    ll s = 0;
    bool x = 0;
    while (!isdigit(c))
        x = x | (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x?-s:s;
}

template<typename T> inline T max(T a, T b) {return a > b ? a : b;}

multiset<ll> sword;
ll N, M;
ll a[maxn], p[maxn], A1[maxn], A[maxn];
ll r[maxn], m[maxn], minx;

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (!b)
    {
        x = 1, y = 0;
        return a;
    }
    R ll tmp = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return tmp;
}

ll mul(ll a, ll b, ll mod)
{
    ll ans = 0, x = a;
    b = (b + mod) % mod, a = (a + mod) % mod;
    for (; b; b >>= 1ll)
    {
        if (b & 1ll)
            ans = (ans + x) % mod;
        x = (x << 1) % mod;
    }
    return ans;
}

void init()
{
    minx = 0;
    sword.clear();
    N = read(), M = read();
    FOR(i, 1, N)
        a[i] = read();
    FOR(i, 1, N)
        p[i] = read();
    FOR(i, 1, N)
        A1[i] = read();
    FOR(i, 1, M)
        sword.insert(read());
    FOR(i, 1, N)
    {
        multiset<ll>::iterator it = sword.upper_bound(a[i]);
        if (it != sword.begin())
            --it;
        A[i] = *it;
        minx = max(minx, a[i] % A[i] == 0 ? a[i] / A[i] : a[i] / A[i] + 1);
        sword.erase(it);
        sword.insert(A1[i]);
    }
    return;
}

ll exCRT()
{
    ll lcm = 1, ans = 0, x, y, k1, k2, k3, gcd;
    FOR(i, 1, N)
    {
        k1 = mul(A[i], lcm, p[i]), k2 = p[i], k3 = ((a[i] - mul(A[i], ans, p[i])) % p[i] + p[i]) % p[i];
        gcd = exgcd(k1, k2, x, y);
        x = (x % p[i] + p[i]) % p[i];
        if (k3 % gcd)
            return -1;
        ans += mul(x, k3 / gcd, p[i] / gcd) * lcm;
        lcm = lcm * (p[i] / gcd);
    }
    if (ans < minx)
    {
        ll tmp = (minx - ans) % lcm == 0 ? (minx - ans) / lcm : (minx - ans) / lcm + 1;
        ans = ans + tmp * lcm;
    }
    return ans;
}

int main()
{
    int T = read();
    while (T--)
    {
        init();
        printf("%lld\n", exCRT());
    }
    return 0;
}