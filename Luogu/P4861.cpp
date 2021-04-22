#include <cstdio>
#include <cmath>
#include <map>
#define int long long
#define R register
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

std::map<int, int> hash;

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

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

signed main()
{
    int m, k;
    scanf("%lld %lld", &m, &k);
    if (gcd(k, m) != 1)
        return printf("Let's go Blue Jays!\n"), 0;
    int t = ceil(sqrt(m));
    hash[1] = 0;
    int val = 1;
    FOR(j, 1, t)
        hash[val = val * k % m] = j;
    k = ksm(k, t, m);
    int ans = 1, tmp;
    FOR(i, 1, t)
    {
        ans = ans * k % m;
        if (tmp = hash[ans])
        {
            int ret = i * t - tmp;
            if (ret > 0)
                return printf("%lld\n", ret), 0;
        }
    }
    return printf("Let's go Blue Jays!\n"), 0;
}