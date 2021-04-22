#include <cstdio>

typedef long long ll;
const ll prime[] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

ll n, ans, maxcnt;

void dfs(int now, ll nowprod, ll nowcnt, int nowlim)
{
    if (nowcnt > maxcnt || (nowcnt == maxcnt && nowprod < ans))
    {
        ans = nowprod;
        maxcnt = nowcnt;
    }
    for (ll i = 1, t = prime[now]; i <= nowlim && t * nowprod <= n; ++i, t *= prime[now])
        dfs(now + 1, nowprod * t, nowcnt * (i + 1), i);
}

int main()
{
    scanf("%lld", &n);
    ans = 1, maxcnt = 1;
    dfs(1, 1, 1, 30);
    printf("%d\n", ans);
    return 0;
}