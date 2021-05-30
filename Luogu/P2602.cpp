#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

typedef long long ll;


const int maxl = 15;

int num[maxl];
ll f[maxl][2][maxl][2];

ll dfs(int len, bool lim, int sum, bool zero, int d)
{
    ll ret = 0;
    if (!len) return sum;
    if (f[len][lim][sum][zero] != -1) return f[len][lim][sum][zero];
    FOR(i, 0, 9)
    {
        if (lim && i > num[len]) break;
        ret += dfs(len - 1, lim && (i == num[len]), sum + ((!zero || i) && i == d), zero && !i, d);
    }
    return f[len][lim][sum][zero] = ret;
}

ll work(ll x, int d)
{
    int len = 0;
    while (x) num[++len] = x % 10, x /= 10;
    memset(f, -1, sizeof f);
    return dfs(len, 1, 0, 1, d);
}

int main()
{
    ll a, b;
    scanf("%lld %lld", &a, &b);
    FOR(i, 0, 9) printf("%lld ", work(b, i) - work(a - 1, i));
    return 0;
}