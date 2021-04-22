#include <cstdio>
#include <cmath>
#include <queue>
#include <algorithm>
#define int long long

int gcd(int a, int b)
{
    if (!b) return a;
    return gcd(b, a % b);
}

int phi(int n)
{
    int ans = n, sq = sqrt(n);
    for (int i = 2; i <= sq; ++i)
    {
        if (n % i == 0)
        {
            ans = ans / i * (i - 1);
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1)
        ans = ans / n * (n - 1);
    return ans;
}

int mul(int a, int b, int mod)
{
    int ans = 0, x = a;
    b = (b + mod) % mod, a = (a + mod) % mod;
    for (; b; b >>= 1ll)
    {
        if (b & 1ll)
            ans = (ans + x) % mod;
        x = (x << 1) % mod;
    }
    return ans;
}

int ksm(int base, int p, int mod)
{
    int ans = 1;
    base %= mod;
    for (; p; p >>= 1)
    {
        if (p & 1)
            ans = mul(ans, base, mod);
        base = mul(base, base, mod);
    }
    return ans;
}

std::vector<int> fact;

signed main()
{
    int n;
    for (signed kase = 1; ; ++kase)
    {
        scanf("%lld", &n);
        if (!n)
            return 0;
        int d = gcd(n, 8);
        int phip = phi(9 * n / d), sqrtp = sqrt(phip);
        fact.clear();
        for (int i = 2; i <= sqrtp; ++i)
            if (phip % i == 0)
            {
                fact.push_back(i);
                if (phip / i != i)
                    fact.push_back(phip / i);
            }
        std::sort(fact.begin(), fact.end());
        int ans = 0;
        for (int i = 0; i < fact.size(); ++i)
        {
            if (ksm(10, fact[i], 9 * n / d) == 1)
            {
                ans = fact[i];
                break;
            }
        }
        printf("Case %d: %lld\n", kase, ans);
    }
    return 0;
}