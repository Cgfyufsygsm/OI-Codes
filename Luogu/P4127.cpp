#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (signed i = a; i <= b; ++i)

typedef long long ll;

int a[20], sum;
ll f[20][170][170];

ll dfs(int eq, int dep, int cur, int mod)
{
    if (cur > sum)
        return 0;
    if (!dep)
        return mod == 0 && cur == sum;
    if (!eq && f[dep][cur][mod] >= 0)
        return f[dep][cur][mod];
    int ed = eq ? a[dep] : 9;
    ll ret = 0;
    FOR(i, 0, ed)
        ret += dfs(eq && (i == ed), dep - 1, cur + i, (mod * 10 + i) % sum);
    if (!eq)
        f[dep][cur][mod] = ret;
    return ret;
}

ll work(ll x)
{
    a[0] = 0;
    for (; x; x /= 10)
        a[++a[0]] = x % 10;
    ll ret = 0;
    FOR(i, 1, 9 * a[0])
    {
        sum = i;
        memset(f, -1, sizeof f);
        ret += dfs(1, a[0], 0, 0);
    }
    return ret;
}

int main()
{
    ll L, R;
    scanf("%lld %lld", &L, &R);
    printf("%lld\n", work(R) - work(L - 1));
    return 0;
}