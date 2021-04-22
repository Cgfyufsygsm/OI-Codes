#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

typedef long long ll;
typedef double db;

int read()
{
    int s = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

template<typename T> inline T max(T a, T b) {return a > b ? a : b;}
template<typename T> inline T min(T a, T b) {return a < b ? a : b;}

const int maxn = 500000 + 5;
int a[maxn], b[maxn], posa[maxn], posb[maxn], n, m;
ll k;
std::vector<int> same;

ll gcd(ll a, ll b)
{
    return !b ? a : gcd(b, a % b);
}

ll lcm(ll a, ll b)
{
    return a / gcd(a, b) * b;
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

int main()
{
    n = read(), m = read();
    scanf("%lld", &k);
    FOR(i, 1, n) posa[a[i] = read()] = i;
    FOR(i, 1, m) posb[b[i] = read()] = i;
    if (n < m) std::swap(n, m), std::swap(a, b), std::swap(posa, posb);
    ll period = lcm(n, m);
    ll pa = period / n, pb = period / m;
    FOR(i, 1, max(n, m))
    {
        if (!(posa[i] && posb[i])) continue;
        ll a = n, b = -m, c = posb[i] - posa[i];
        //printf("%dk1 + %dk2 = %d\n", a, b, c);
        ll x0, y0;
        ll gcdab = exgcd(a, b, x0, y0);
        if (c % gcdab) continue;
        x0 *= (c / gcdab), y0 *= (c / gcdab);
        ll dx = b / gcdab, dy = a / gcdab;
        //printf("x0y0 %d %d\n", x0, y0);
        //printf("dx %d dy %d\n", dx, dy);
        db low = -1e9, up = 1e9;
        db x1 = ((db)(pa - x0)) / (db)dx, x2 = (db)(-x0) / (db)dx;
        db y1 = ((db)(y0 - pb)) / (db)dy, y2 = (db)y0 / (db)dy;
        //printf("%lf %lf %lf %lf\n", x1, x2, y1, y2);
        if (x1 < x2) low = max(low, ceil(x1)), up = min(up, x2);
        else low = max(low, x2), up = min(up, floor(x1));
        if (y1 < y2) low = max(low, ceil(y1)), up = min(up, y2);
        else low = max(low, y2), up = min(up, floor(y1));
        int lowi = ceil(low), upi = floor(up);
        //printf("i %d low%d high%d\n", i, lowi, upi);
        if (upi < lowi) continue;
        ll x = x0 + lowi * dx, y = y0 + upi * dy;
        same.push_back(x * n + posa[i]);
    }
    //for (auto i : same) printf("%d ", i);
    ll ans = 0;
    ll rounds = k / (period - same.size());
    ans += rounds * period;
    k %= (period - same.size());
    if (k)
    {
        for (int i = 0; i < same.size(); ++i)
        {
            int cur = same[i] - (i - 1 >= 0 ? same[i - 1] : 0);
            if (k > cur)
                ans += cur + 1;
            else
            {
                ans += k;
                break;
            }
            
        }
    }
    printf("%d\n", ans);
    return 0;
}