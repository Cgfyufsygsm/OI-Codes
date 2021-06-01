#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

typedef long long ll;

const int mod = 1e9 + 7;

ll read()
{
    ll s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

int num[20];

int f[20][20][2][2];

int dfs(int pos, int sum, bool lim, bool zero, int d)
{
    if (!pos) return sum;
    if (~f[pos][sum][lim][zero]) return f[pos][sum][lim][zero];
    int ret = 0;
    FOR(i, 0, 9)
    {
        if (lim && i > num[pos]) break;
        ret = (ret + dfs(pos - 1, sum + ((!zero || i) && i == d), lim && i == num[pos], zero && !i, d)) % mod;
    }
    return f[pos][sum][lim][zero] = ret;
}

int solve(ll n, int d)
{
    int len = 0;
    memset(f, -1, sizeof f);
    while (n) num[++len] = n % 10, n /= 10;
    return dfs(len, 0, 1, 1, d);
}

int ans[10];

int main()
{
    int T = read();
    while (T--)
    {
        ll l = read(), r = read();
        memset(ans, 0, sizeof ans);
        FOR(d, 0, 9)
            ans[d] = (solve(r, d) - solve(l - 1, d) + mod) % mod;
        int ret = 0;
        FOR(d, 0, 9)
            ret = (ret + 1ll * ans[d] * d % mod) % mod;
        printf("%d\n", ret);
    }
    return 0;
}