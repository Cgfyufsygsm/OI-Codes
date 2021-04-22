#include <cstdio>
#include <cmath>
#include <unordered_map>
#define R register
#define FOR(i, a, b) for(R int i = a; i <= b; ++i)
#define int long long

std::unordered_map<int, int> hash;

int ksm(int base, int p, int mod)
{
    int ans = 1;
    for (; p; p >>= 1)
    {
        if (p & 1)
            ans = ans * base % mod;
        base = base * base % mod;
    }
    return ans;
}

int exgcd(int a, int b, int &x, int &y)
{
    if (!b)
        return x = 1, y = 0, a;
    int tmp = exgcd(b, a % b, y, x);
    return y -= a / b * x, tmp;
}

int inv(int a, int mod)
{
    int x, y;
    exgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}

int BSGS(int a, int b, int p)
{
    hash.clear();
    if (a % p == 0)
        return -1;
    int t = ceil(sqrt(p)), val, tmp;
    hash[val = b] = 0;
    FOR(j, 1, t)
        hash[val = val * a % p] = j;
    a = ksm(a, t, p), val = 1;
    FOR(i, 1, t)
    {
        val = val * a % p;
        if (tmp = hash[val])
            return val = i * t - tmp, (val % p + p) % p;
    }
    return -1;
}

int exBSGS(int a, int b, int p)
{
    if (a == 1 || p == 1)
        return 0;
    int x, y, k = 0, na = 1, g = exgcd(a, p, x, y);
    while (g > 1)
    {
        if (b % g)
            return -1;
        ++k, b /= g, p /= g, na = (na * (a / g)) % p;
        if (na == b)
            return k;
        g = exgcd(a, p, x, y);
    }
    int ans = BSGS(a, b * inv(na, p) % p, p);
    return ans == -1 ? -1 : ans + k;
}

signed main()
{
    int a, p, b;
    for (scanf("%lld %lld %lld", &a, &p, &b); a || b || p; scanf("%lld %lld %lld", &a, &p, &b))
    {
        int ans = exBSGS(a % p, b % p, p);
        if (ans > 0)
            printf("%lld\n", ans);
        else printf("No Solution\n");
    }
    return 0;
}