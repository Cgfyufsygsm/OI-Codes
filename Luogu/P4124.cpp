#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

typedef long long ll;

const int maxl = 15;

int num[maxl], len;
ll f[maxl][2][maxl][maxl][2][2][2];

ll dfs(int pos, bool lim, int last1, int last2, bool valid, bool _4, bool _8)
{
    if (_4 && _8) return 0;
    if (!pos) return valid;
    if (f[pos][lim][last1][last2][valid][_4][_8] != -1) return f[pos][lim][last1][last2][valid][_4][_8];
    ll ret = 0;
    FOR(i, 0, 9)
    {
        if (lim && i > num[pos]) break;
        ret += dfs(pos - 1, lim && i == num[pos], i, last1, valid || (i == last1 && i == last2), _4 || i == 4, _8 || i == 8);
    }
    return f[pos][lim][last1][last2][valid][_4][_8] = ret;
}

ll work(ll n)
{
    if (n < 1e10) return 0;
    len = 0;
    while (n) num[++len] = n % 10, n /= 10;
    memset(f, -1, sizeof f);
    ll ret = 0;
    FOR(i, 1, num[len]) ret += dfs(10, i == num[len], i, -1, 0, i == 4, i == 8);
    return ret;
}

int main()
{
    ll l, r;
    scanf("%lld %lld", &l, &r);
    printf("%lld\n", work(r) - work(l - 1));
    return 0;
}