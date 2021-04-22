#include <cstdio>
#include <cctype>
#include <cmath>
#include <map>

#define int long long
#define dbg printf("debug")
#define R register
#define FOR(i, a, b) for (R int i = a; i <= b; ++i)
#define il inline

std::map<int, int> hash;

il int read()
{
    char c = getchar();
    int s = 0;
    bool x = 0;
    while (!isdigit(c))
        x = x | (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x?-s:s;
}

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

il int exgcd(int a, int b, int &x, int &y)
{
    if (!b)
        return x = 1, y = 0, a;
    int tmp = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return tmp;
}

int BSGS(int a, int b, int p)
{
    hash.clear();
    if (a % p == 0 && b)
        return -1;
    int t = ceil(sqrt(p));
    int val = b;
    hash[val] = 0;
    FOR(j, 1, t)
    {
        val = val * a % p;
        hash[val] = j;
    }
    a = ksm(a, t, p), val = 1;
    int tmp;
    FOR(i, 1, t)
    {
        val = val * a % p;
        if (tmp = hash[val])
        {
            int q = i * t - tmp;
            return (q % p + p) % p;
        }
    }
    return -1;
}

il int calc(int k, int y, int z, int p)
{
    int val;
    if (k == 1)
        return printf("%lld\n", ksm(y, z, p));
    if (k == 2)
    {
        int xx, yy;
        int gcd = exgcd(y, p, xx, yy);
        if (z % gcd)
            return printf("Orz, I cannot find x!\n");
        int x1 = xx * (z / gcd), dx = p / gcd;
        return printf("%lld\n", (x1 % dx + dx) % dx);
    }
    if (k == 3)
    {
        if ((val = BSGS(y, z, p)) != -1)
            return printf("%lld\n", val);
        return printf("Orz, I cannot find x!\n");
    }
}

signed main()
{
    int t = read(), k = read();
    while (t--)
    {
        int y = read(), z = read(), p = read();
        calc(k, y, z, p);
    }
    return 0;
}