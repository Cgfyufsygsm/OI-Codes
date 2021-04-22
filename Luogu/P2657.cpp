#include <cstdio>
#include <cstring>
#include <cmath>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

int a[15], f[15][15][2][2];


int dfs(int len, int lst, int op, int zero)
{
    if (!len) return 1;
    if (~f[len][lst][op][zero]) return f[len][lst][op][zero];
    int ret = 0;
    FOR(i, 0, 9)
        if ((i <= a[len] || !op) && (abs(i - lst) >= 2 || zero))
            ret += dfs(len - 1, i, op && (i == a[len]), zero && (!i));
    return f[len][lst][op][zero] = ret;
}

int work(int x)
{
    int len = 0;
    memset(a, 0, sizeof a);
    for (; x; x /= 10)
        a[++len] = x % 10;
    memset(f, -1, sizeof f);
    return dfs(len, 11, 1, 1);
}

int main()
{
    int l, r;
    scanf("%d %d", &l, &r);
    printf("%d\n", work(r) - work(l - 1));
    return 0;
}