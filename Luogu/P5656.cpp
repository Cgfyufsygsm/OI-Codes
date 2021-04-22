#include <cstdio>
#include <cctype>
#include <cmath>
#define il inline

typedef long long ll;

il ll read()
{
    char c = getchar();
    ll s = 0;
    bool x = 0;
    while (!isdigit(c))
        x = x | (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (!b)
    {
        x = 1, y = 0;
        return a;
    }
    ll tmp = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return tmp;
}

il ll ceildiv(ll a, ll b)
{
    if (a % b)
        return ceil((double)a / (double)b);
    else return a / b;
}

il ll floordiv(ll a, ll b)
{
    if (a % b)
        return floor((double)a / (double)b);
    else return a / b;
}

int main()
{
    int T = read();
    ll x0, y0, x1, y1, dx, dy, ceil, floor;
    while (T--)
    {
        ll a = read(), b = read(), c = read();
        ll gcd = exgcd(a, b, x0, y0);
        if (c % gcd)
        {
            printf("-1\n");
            continue;
        }
        x1 = c / gcd * x0, y1 = c / gcd * y0;
        dx = b / gcd, dy = a / gcd;
        ceil = ceildiv(-x1 + 1, dx), floor = floordiv(y1 - 1, dy);
        if (ceil > floor)
        {
            ll sx = ceil;
            ll sy = floor;
            printf("%lld %lld\n", x1 + sx * dx, y1 - sy * dy);
        }
        else
        {
            ll s1 = ceil, s2 = floor;
            ll xmin = x1 + s1 * dx, ymax = y1 - s1 * dy;
            ll xmax = x1 + s2 * dx, ymin = y1 - s2 * dy;
            printf("%lld %lld %lld %lld %lld\n", s2 - s1 + 1, xmin, ymin, xmax, ymax);
        }
    }
    return 0;
}